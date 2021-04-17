
#include "debugger.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>

#define MAX_PACKET_SIZE     0x4000
#define MAX_DEBUGGER_THREADS    8

#define GDB_ANY_THREAD      0
#define GDB_ALL_THREADS     -1 

#define GDB_STACKSIZE           0x400
#define GDB_DEBUGGER_THREAD_ID  0xDBDB
#define GDB_POLL_DELAY          (OS_CPU_COUNTER / 2)
#define GDB_QUICK_POLL_DELAY    (OS_CPU_COUNTER / 100)
#define GDB_QUICK_POLL_COUNT    20

#define GDB_BRANCH_DELAY        0x80000000

#define GDB_IS_ATTACHED         (1 << 0)
#define GDB_IS_WAITING_STOP     (1 << 1)

#define GDB_TRAP_IS_BREAK_CODE  0x123

#define GDB_BREAK_INSTRUCTION(code) (0x0000000D | (((code) & 0xfffff) << 6))
#define GDB_TRAP_INSTRUCTION(code) (0x00000034 | (((code) & 0x3ff) << 6))
#define GDB_GET_TRAP_CODE(instr) (((instr) >> 6) & 0x3ff)

#define GDB_GET_EXC_CODE(cause) (((cause) >> 2) & 0x1f)

extern OSThread *	__osGetCurrFaultedThread(void);
extern OSThread *	__osGetNextFaultedThread(OSThread *);

// defined by makerom
extern char     _codeSegmentDataStart[];
extern char     _codeSegmentTextStart[];

#define strStartsWith(str, constStr) (strncmp(str, constStr, sizeof constStr - 1) == 0)

static OSThread* gdbTargetThreads[MAX_DEBUGGER_THREADS];
static OSId gdbCurrentThreadG;
static OSId gdbCurrentThreadg;
static OSId gdbCurrentThreadc;
static char gdbPacketBuffer[MAX_PACKET_SIZE];
static char gdbOutputBuffer[MAX_PACKET_SIZE];
static int gdbNextBufferTarget;
static int gdbNextSearchIndex;
static int gdbRunFlags;
static int gdbQuickPollCount;

static OSThread gdbDebuggerThread;
static u64 gdbDebuggerThreadStack[GDB_STACKSIZE/sizeof(u64)];

static OSTimer gdbPollTimer;
static OSMesgQueue gdbPollMesgQ;
static OSMesg gdbPollMesgQMessage;

static struct GDBBreakpoint gdbBreakpoints[GDB_MAX_BREAK_POINTS];

void __gdbSetWatch(u32 value);
u32 __gdbGetWatch();

static int gdbSignals[32] = {
    2, // SIGINT
    11, // SIGSEGV
    11, // SIGSEGV
    11, // SIGSEGV
    11, // SIGSEGV
    11, // SIGSEGV
    10, // SIGBUS
    10, // SIGBUS
    12, // SIGSYS
    5, // SIGTRAP
    4, // SIGILL
    30, // SIGUSR1
    8, // SIGFPE
    5, // SIGTRAP
    0, // reserved
    8, // SIGFPE
    0, // reserved
    0, // reserved
    0, // reserved
    0, // reserved
    0, // reserved
    0, // reserved
    0, // reserved
    5, // SIGTRAP
    0, // reserved
    0, // reserved
    0, // reserved
    0, // reserved
    0, // reserved
    0, // reserved
    0, // reserved
    0, // reserved
};

u32 gdbGetFaultAddress(OSThread* thread) {
    if (thread->context.cause & GDB_BRANCH_DELAY) {
        // pc points to a branch instruction
        return thread->context.pc + 4;
    } else {
        return thread->context.pc;
    }
}

OSThread* gdbFindThread(OSId id) {
    int i;
    for (i = 0; i < MAX_DEBUGGER_THREADS; ++i) {
        if (gdbTargetThreads[i] && (
            id == GDB_ANY_THREAD ||
            osGetThreadId(gdbTargetThreads[i]) == id
        )) {
            return gdbTargetThreads[i];
        }
    }
    return NULL;
}

OSThread* gdbNextThread(OSThread* curr, OSId id) {
    if (id == GDB_ALL_THREADS) {
        int i;
        for (i = 0; i < MAX_DEBUGGER_THREADS; ++i) {
            if (curr == NULL && gdbTargetThreads[i]) {
                return gdbTargetThreads[i];
            } else if (curr != NULL && gdbTargetThreads[i] == curr) {
                curr = NULL;
            }
        }

        return NULL;
    } else {
        if (curr) {
            return NULL;
        } else {
            return gdbFindThread(id);
        }
    }
}

int gdbReadHexDigit(char character) {
    if (character >= 'a' && character <= 'f') {
        return 10 + character - 'a';
    } else if (character >= 'A' && character <= 'F') {
        return 10 + character - 'A';
    } else if (character >= '0' && character <= '9') {
        return character - '0';
    } else {
        return -1;
    }   
}

u32 gdbParseHex(char* src, u32 maxBytes) {
    u32 result = 0;
    int currentChar;
    u32 maxCharacters = maxBytes * 2;

    for (currentChar = 0; currentChar < maxCharacters; ++currentChar) {
        int digit = gdbReadHexDigit(*src);

        if (digit != -1) {
            result = (result << 4) + digit;
        } else {
            break;
        }

        ++src;
    }

    return result;
}

OSId gdbParseThreadId(char* src) {
    if (src[0] == '-') {
        return GDB_ALL_THREADS;
    } else {
        return gdbParseHex(src, 4);
    }
}

static char gdbHexLetters[16] = "0123456789abcdef";

char* gdbWriteHex(char* target, u8* src, u32 bytes) {
    u32 i;
    for (i = 0; i < bytes; ++i) {
        *target++ = gdbHexLetters[(*src) >> 4];
        *target++ = gdbHexLetters[(*src) & 0xF];
        ++src;
    }
    return target;
}

char* gdbReadHex(u8* target, char* src, u32 maxBytes) {
    u32 i;
    for (i = 0; i < maxBytes; ++i) {
        int firstDigit = gdbReadHexDigit(*src++);

        if (firstDigit == -1) {
            return src;
        } else {
            int secondDigit = gdbReadHexDigit(*src++);

            if (secondDigit == -1) {
                *target++ = firstDigit << 4;
                return src;
            } else {
                *target++ = (firstDigit << 4) | secondDigit;
            }
        }
    }
    return src;
}

void* gdbTranslateAddr(void* in) {
    u32 physicalAddr = osVirtualToPhysical(in);

    if (physicalAddr >= osMemSize) {
        return 0;
    } else {
        return (void*)(PHYS_TO_K0(physicalAddr));
    }
}

void gdbCopy(char* dst, char* src, int len)
{
    while (len)
    {
        *dst++ = *src++;
        --len;
    }
}

int gdbIsAlphaNum(int chr)
{
    return chr >= 'a' && chr <= 'z' || chr >= 'A' && chr <= 'Z' || chr >= '0' && chr <= '9';
}

int gdbApplyChecksum(char* message)
{
    char* messageStart = message;
    if (*message == '$') {
        ++message;
    }
    
    u8 checksum = 0;
    while (*message)
    {
        if (*message == '#') {
            ++message;
            break;
        }

        checksum += (u8)*message;
        ++message;
    }

    sprintf(message, "%02x", checksum);

    return (message - messageStart) + 2;
    return strlen(messageStart);
}

void gdbWriteInstruction(u32 addr, u32 value) {
    *((u32*)addr) = value;
    osWritebackDCache((void*)addr, sizeof(u32));
    osInvalICache((void*)addr, sizeof(u32));
}

struct GDBBreakpoint* gdbFindBreakpoint(u32 addr) {
    int i;
    struct GDBBreakpoint* firstEmpty = NULL;
    for (i = 0; i < GDB_MAX_BREAK_POINTS; ++i) {
        if (!firstEmpty && gdbBreakpoints[i].type == GDBBreakpointTypeNone) {
            firstEmpty = &gdbBreakpoints[i];
        } else if (gdbBreakpoints[i].type != GDBBreakpointTypeNone && gdbBreakpoints[i].addr == addr) {
            return &gdbBreakpoints[i];
        }
    }

    return firstEmpty;
}

struct GDBBreakpoint* gdbInsertBreakPoint(u32 addr, enum GDBBreakpointType type) {
    struct GDBBreakpoint* result = gdbFindBreakpoint(addr);

    if (result) {
        if (result->type == GDBBreakpointTypeNone) {
            result->prevValue = *((u32*)addr);
            gdbWriteInstruction(addr, GDB_TRAP_INSTRUCTION(GDB_TRAP_IS_BREAK_CODE));
            result->type = type;
        } else if (result->type < type) {
            result->type = type;
        }
        result->addr = addr;
    }

    return result;
}

void gdbDisableBreakpoint(struct GDBBreakpoint* breakpoint) {
    if (breakpoint && breakpoint->type == GDBBreakpointTypeUser) {
        gdbWriteInstruction(breakpoint->addr, breakpoint->prevValue);
        breakpoint->type = GDBBreakpointTypeUserUnapplied;
    }
}

void gdbRenableBreakpoint(struct GDBBreakpoint* breakpoint) {
    if (breakpoint && breakpoint->type == GDBBreakpointTypeUserUnapplied) {
        breakpoint->prevValue = *((u32*)breakpoint->addr);
        gdbWriteInstruction(breakpoint->addr, GDB_TRAP_INSTRUCTION(GDB_TRAP_IS_BREAK_CODE));
        breakpoint->type = GDBBreakpointTypeUser;
    }
}

void gdbRemoveBreakpoint(struct GDBBreakpoint* brk) {
    if (brk && brk->type != GDBBreakpointTypeNone) {
        if (brk->type != GDBBreakpointTypeUserUnapplied) {
            gdbWriteInstruction(brk->addr, brk->prevValue);
        }
        brk->prevValue = 0;
        brk->addr = 0;
        brk->type = GDBBreakpointTypeNone;
    }
}

enum GDBError gdbParsePacket(char* input, u32 len, char **commandStart, char **packetEnd)
{
    char* stringEnd = input + len;
    while (input < stringEnd)
    {
        if (*input == '$') {
            ++input;
            *commandStart = input;
            break;
        }
        ++input;
    }

    while (input < stringEnd) {
        if (*input == '#') {
            *packetEnd = input;
            ++input;
            return GDBErrorNone;
        }
        else
        {
            ++input;
        }
    } 

    return GDBErrorBadPacket;
}

void gdbWaitForStop() {
    gdbRunFlags |= GDB_IS_WAITING_STOP;
}

enum GDBError gdbSendStopReply(OSThread* thread) {
    char* current = gdbOutputBuffer;
    int excCode = GDB_GET_EXC_CODE(thread->context.cause);
    current += sprintf(current, "$T%02x", gdbSignals[excCode]);
    u32 breakAddr = gdbGetFaultAddress(thread);

    u32 instr = *((u32*)breakAddr);
    u32 trapCode = GDB_GET_TRAP_CODE(instr);

    // check for breakpoint or trap
    if (
        // breakpoint
        excCode == 9 || 
        // breakpoint simulated with trap code
        excCode == 13 && trapCode == GDB_TRAP_IS_BREAK_CODE && GDB_TRAP_INSTRUCTION(trapCode) == instr) {
        current += sprintf(current, "swbreak:");
    }

    current += sprintf(current, "thread:%d;", osGetThreadId(thread));
    *current++ = '#';
    *current++ = '\0';

    int i;
    for (i = 0; i < GDB_MAX_BREAK_POINTS; ++i) {
        gdbRenableBreakpoint(&gdbBreakpoints[i]);
    }

    return gdbSendMessage(GDBDataTypeGDB, gdbOutputBuffer, gdbApplyChecksum(gdbOutputBuffer));
}

void gdbResumeThread(OSThread* thread) {
    if (thread->context.pc == (u32)gdbBreak) {
        // hacky way to skip breakpoint instruction
        thread->context.pc = (u32)thread->context.ra;
    }
    if ((GDB_GET_EXC_CODE(thread->context.cause) & CAUSE_EXCMASK) == EXC_WATCH) {
        // TODO restore watch point
        __gdbSetWatch(0);
    }
    gdbDisableBreakpoint(gdbFindBreakpoint(thread->context.pc));
    // clear fault flag
    thread->flags &= ~OS_FLAG_FAULT;

    // step commands will frequently string to together a lot
    // of nearby breakpoints. This is to make sure stepping
    // doesn't cause a huge delay
    gdbQuickPollCount = GDB_QUICK_POLL_COUNT;
    osStartThread(thread);
}

enum GDBError gdbReplyRegisters() {
    char* current = gdbOutputBuffer;
    *current++ = '$';

    OSThread* thread = gdbFindThread(gdbCurrentThreadg);

    if (thread) {
        /* 0~ GPR0-31(yes, include zero),[32]PS(status),LO,HI,BadVAddr,Cause,PC,[38]FPR0-31,[70]fpcs,fpir,[72]..(dsp?),[90]end */
        current += sprintf(current, "%08x%08x", 0, 0); // zero
        current = gdbWriteHex(current, (u8*)&thread->context, offsetof(__OSThreadContext, gp));
        current += sprintf(current, "%08x%08x", 0, 0); // k0
        current += sprintf(current, "%08x%08x", 0, 0); // k1
        current = gdbWriteHex(current, (u8*)&thread->context.gp, offsetof(__OSThreadContext, lo) - offsetof(__OSThreadContext, gp));

        current += sprintf(current, "%08x%08x", 0, thread->context.sr);
        current = gdbWriteHex(current, (u8*)&thread->context.lo, sizeof(u64) * 2);
        current += sprintf(current, "%08x%08x", 0, thread->context.badvaddr);
        current += sprintf(current, "%08x%08x", 0, thread->context.cause);
        if (thread->context.pc == (u32)gdbBreak) {
            // when inside gdbBreak, report the breakpoint to be at where the function was called
            current += sprintf(current, "%08x%08x", 0, (u32)thread->context.ra);
        } else {
            current += sprintf(current, "%08x%08x", 0, thread->context.pc);
        }

        current = gdbWriteHex(current, (u8*)&thread->context.fp0, sizeof(__OSThreadContext) - offsetof(__OSThreadContext, fp0));
        current += sprintf(current, "%08x%08x", 0, thread->context.fpcsr);
    }

    *current++ = '#';
    *current++ = '\0';

    return gdbSendMessage(GDBDataTypeGDB, gdbOutputBuffer, gdbApplyChecksum(gdbOutputBuffer));
}

enum GDBError gdbWriteRegisters(char* commandStart, char *packetEnd) {
    
    OSThread* thread = gdbFindThread(gdbCurrentThreadg);

    char* current = commandStart + 1;
    u32 messageLength = (u32)(packetEnd - current);

    if (messageLength != 880) {
        return GDBErrorBadPacket;
    }

    if (thread) {
        current += 16; // zero register
        current = gdbReadHex((u8*)&thread->context, current, offsetof(__OSThreadContext, gp));
        current += 32; // k0 and k1
        current = gdbReadHex((u8*)&thread->context.gp, current, offsetof(__OSThreadContext, lo) - offsetof(__OSThreadContext, gp));
        current += 8; current = gdbReadHex((u8*)&thread->context.sr, current, sizeof(u32));
        current = gdbReadHex((u8*)&thread->context.lo, current, sizeof(u64) * 2);
        current += 8; current = gdbReadHex((u8*)&thread->context.badvaddr, current, sizeof(u32));
        current += 8; current = gdbReadHex((u8*)&thread->context.cause, current, sizeof(u32));
        current += 8; current = gdbReadHex((u8*)&thread->context.pc, current, sizeof(u32));
        current = gdbReadHex((u8*)&thread->context.fp0, current, sizeof(__OSThreadContext) - offsetof(__OSThreadContext, fp0));
        current += 8; current = gdbReadHex((u8*)&thread->context.fpcsr, current, sizeof(u32));
    }
    
    return gdbSendMessage(GDBDataTypeGDB, "$OK#9a", strlen("$OK#9a"));
}

enum GDBError gdbReplyMemory(char* commandStart, char *packetEnd) {
    u32 prevWatch = __gdbGetWatch();
    // clear the watch so the debugger thread doesn't get the interrupt
    __gdbSetWatch(0);
    char* current = gdbOutputBuffer;
    *current++ = '$';

    char* lenText = commandStart + 1;

    while (*lenText != ',') {
        if (lenText == packetEnd) {
            return GDBErrorBadPacket;
        }
        ++lenText;
    }

    u8* dataSrc = gdbTranslateAddr((u8*)gdbParseHex(commandStart + 1, 4));
    u32 len = gdbParseHex(lenText + 1, 4);

    if ((u32)dataSrc < K0BASE) {
        while ((u32)dataSrc < K0BASE && len > 0) {
            *current++ = '0';
            *current++ = '0';
            ++dataSrc;
            --len;
        }
    }

    if (len > 0) {
        u32 maxLen;
        if ((u32)dataSrc < osMemSize + K0BASE) {
            maxLen = (osMemSize + K0BASE) - (u32)dataSrc;
        }

        if (len > maxLen) {
            len = maxLen;
        }

        char* strEnd = gdbWriteHex(current, dataSrc, len);

        current = strEnd;
    }

    *current++ = '#';
    *current++ = '\0';
    __gdbSetWatch(prevWatch);
    return gdbSendMessage(GDBDataTypeGDB, gdbOutputBuffer, gdbApplyChecksum(gdbOutputBuffer));
}

enum GDBError gdbWriteMemory(char *commandStart, char* packetEnd) {
    u32 prevWatch = __gdbGetWatch();
    // clear the watch so the debugger thread doesn't get the interrupt
    __gdbSetWatch(0);
    char* current = gdbOutputBuffer;
    *current++ = '$';

    char* lenText = commandStart + 1;

    while (*lenText != ',') {
        if (lenText == packetEnd) {
            return GDBErrorBadPacket;
        }
        ++lenText;
    }

    char* dataText = lenText + 1;

    while (*dataText != ':') {
        if (dataText == packetEnd) {
            return GDBErrorBadPacket;
        }
        ++dataText;
    }

    ++dataText;

    u8* dataTarget = gdbTranslateAddr((u8*)gdbParseHex(commandStart + 1, 4));
    if (dataTarget) {
        u32 len = gdbParseHex(lenText + 1, 4);
        gdbReadHex(dataTarget, dataText, len);
    }
    __gdbSetWatch(prevWatch);
    return gdbSendMessage(GDBDataTypeGDB, "$OK#9a", strlen("$OK#9a"));
}

enum GDBError gdbHandleQuery(char* commandStart, char *packetEnd) {
    if (strStartsWith(commandStart, "qSupported")) {
        strcpy(gdbOutputBuffer, "$PacketSize=4000;vContSupported+;swbreak+#");
        return gdbSendMessage(GDBDataTypeGDB, gdbOutputBuffer, gdbApplyChecksum(gdbOutputBuffer));
    } else if (strStartsWith(commandStart, "qTStatus")) {
        return gdbSendMessage(GDBDataTypeGDB, "$#00", strlen("$#00"));
    } else if (strStartsWith(commandStart, "qfThreadInfo")) {
        strcpy(gdbOutputBuffer, "$m");
        char* outputWrite = gdbOutputBuffer + 2;
        int i;
        int first = 1;
        for (i = 0; i < MAX_DEBUGGER_THREADS; ++i) {
            if (gdbTargetThreads[i]) {
                if (first) {    
                    first = 0;
                    outputWrite += sprintf(outputWrite, "%x", osGetThreadId(gdbTargetThreads[i]));
                } else {
                    outputWrite += sprintf(outputWrite, ",%x", osGetThreadId(gdbTargetThreads[i]));
                }
            }
        }
        *outputWrite++ = '#';
        *outputWrite++ = '\0';
        return gdbSendMessage(GDBDataTypeGDB, gdbOutputBuffer, gdbApplyChecksum(gdbOutputBuffer));
    } else if (strStartsWith(commandStart, "qsThreadInfo")) {
        strcpy(gdbOutputBuffer, "$l#");
        return gdbSendMessage(GDBDataTypeGDB, gdbOutputBuffer, gdbApplyChecksum(gdbOutputBuffer));
    } else if (strStartsWith(commandStart, "qAttached")) {
        strcpy(gdbOutputBuffer, "$0#");
        return gdbSendMessage(GDBDataTypeGDB, gdbOutputBuffer, gdbApplyChecksum(gdbOutputBuffer));
    } else if (strStartsWith(commandStart, "qC")) {
        strcpy(gdbOutputBuffer, "$QC");
        char* outputWrite = gdbOutputBuffer + 3;
        int i;
        for (i = 0; i < MAX_DEBUGGER_THREADS; ++i) {
            if (gdbTargetThreads[i]) {
                outputWrite += sprintf(outputWrite, "%x", osGetThreadId(gdbTargetThreads[i]));
                break;
            }
        }

        if (i == MAX_DEBUGGER_THREADS) {
            strcpy(gdbOutputBuffer, "$E00#");
        } else {
            *outputWrite++ = '#';
            *outputWrite++ = '\0';
        }
        return gdbSendMessage(GDBDataTypeGDB, gdbOutputBuffer, gdbApplyChecksum(gdbOutputBuffer));
    } else if (strStartsWith(commandStart, "qTfV")) {
        return gdbSendMessage(GDBDataTypeGDB, "$#00", strlen("$#00"));
    } else if (strStartsWith(commandStart, "qTfP")) {
        return gdbSendMessage(GDBDataTypeGDB, "$#00", strlen("$#00"));
    } else if (strStartsWith(commandStart, "qOffsets")) {
        // 0x20 is a magic number. I don't know why but it makes the addresses line up correctly
        sprintf(gdbOutputBuffer, "$Text=%x;Data=%x;Bss=%x#", 0, 0, 0);
        return gdbSendMessage(GDBDataTypeGDB, gdbOutputBuffer, gdbApplyChecksum(gdbOutputBuffer));
    } else if (strStartsWith(commandStart, "qSymbol")) {
        return gdbSendMessage(GDBDataTypeGDB, "$OK#9a", strlen("$OK#9a"));
    } else if (strStartsWith(commandStart, "qThreadExtraInfo")) {
        OSId threadId = gdbParseHex(commandStart + sizeof("qThreadExtraInfo"), 4);

        OSThread* thread = gdbFindThread(threadId);

        if (thread) {
            int strLen = sprintf(gdbOutputBuffer + 0x200, "state %d priority %d", thread->state, thread->priority);
            gdbOutputBuffer[0] = '$';
            char* nextOut = gdbWriteHex(gdbOutputBuffer + 1, gdbOutputBuffer + 0x200, strLen);
            *nextOut++ = '#';
        return gdbSendMessage(GDBDataTypeGDB, gdbOutputBuffer, gdbApplyChecksum(gdbOutputBuffer));
        } else {
            return gdbSendMessage(GDBDataTypeGDB, "$#00", strlen("$#00"));
        }
    }

    return gdbSendMessage(GDBDataTypeGDB, "$#00", strlen("$#00"));
}

enum GDBError gdbHandleV(char* commandStart, char *packetEnd) {
    if (strStartsWith(commandStart, "vMustReplyEmpty")) {
        return gdbSendMessage(GDBDataTypeGDB, "$#00", strlen("$#00"));
    } else if (strStartsWith(commandStart, "vCont")) {
        if (commandStart[5] == '?') {
            strcpy(gdbOutputBuffer, "$c;t#");
            return gdbSendMessage(GDBDataTypeGDB, gdbOutputBuffer, gdbApplyChecksum(gdbOutputBuffer));
        } else {
            OSId threadId;

            char* idLoc = commandStart + 6;
            while (idLoc < packetEnd && *idLoc++ != ':');

            if (idLoc < packetEnd && *idLoc != '#') {
                threadId = gdbParseThreadId(idLoc);
            } else {
                threadId = GDB_ALL_THREADS;
            }

            OSThread *thread = NULL;

            while ((thread = gdbNextThread(thread, threadId))) {
                switch (commandStart[6])
                {
                case 'c':
                {
                    gdbResumeThread(thread);
                    break;
                }
                case 's':
                {
                    // TODO
                    break;
                }
                case 't':
                {
                    osStopThread(thread);
                    break;
                }
                case 'r':
                {
                    // TODO
                    break;
                }
                }
            }

            gdbWaitForStop();
            return GDBErrorNone;
        }
    } else if (strStartsWith(commandStart, "vKill")) {
        int i;
        for (i = 0; i < GDB_MAX_BREAK_POINTS; ++i) {
            gdbRemoveBreakpoint(&gdbBreakpoints[i]);
        }
        for (i = 0; i < MAX_DEBUGGER_THREADS; ++i) {
            if (gdbTargetThreads[i] && gdbTargetThreads[i]->state == OS_STATE_STOPPED) {
                gdbResumeThread(gdbTargetThreads[i]);
            }
        }
        gdbRunFlags &= ~GDB_IS_ATTACHED;
        return gdbSendMessage(GDBDataTypeGDB, "$OK#9a", strlen("$OK#9a"));
    }

    return gdbSendMessage(GDBDataTypeGDB, "$#00", strlen("$#00"));
}

enum GDBError gdbHandlePacket(char* commandStart, char *packetEnd) {
    switch (*commandStart) {
        case 'q':
            return gdbHandleQuery(commandStart, packetEnd);
        case 'v':
            return gdbHandleV(commandStart, packetEnd);
        case 'H':
        {
            OSId threadId;

            if (commandStart[2] == '-') {
                threadId = -1;
            } else {
                threadId = gdbParseHex(commandStart + 2, 4);
            }

            switch (commandStart[1]) {
            case 'G':
                gdbCurrentThreadG = threadId;
                break;
            case 'g':
                gdbCurrentThreadg = threadId;
                break;
            case 'c':
                gdbCurrentThreadc = threadId;
                break;
            }

            return gdbSendMessage(GDBDataTypeGDB, "$OK#9a", strlen("$OK#9a"));
        }
        case '!':
            return gdbSendMessage(GDBDataTypeGDB, "$#00", strlen("$#00"));
        case '?':
            return gdbSendStopReply(gdbFindThread(GDB_ANY_THREAD));
        case 'g':
            return gdbReplyRegisters();
        case 'G':
            return gdbWriteRegisters(commandStart, packetEnd);
        case 'm':
            return gdbReplyMemory(commandStart, packetEnd);
        case 'M':
            return gdbWriteMemory(commandStart, packetEnd);
        case 'D':
            gdbRunFlags &= ~GDB_IS_ATTACHED;
            return gdbSendMessage(GDBDataTypeGDB, "$OK#9a", strlen("$OK#9a"));
        case 'z':
        case 'Z':
        {
            if (commandStart[1] == '0') {
                u32 addr = gdbParseHex(&commandStart[3], 4);

                if (*commandStart == 'z') {
                    gdbRemoveBreakpoint(gdbFindBreakpoint(addr));
                } else {
                    struct GDBBreakpoint* brk = gdbInsertBreakPoint(addr, GDBBreakpointTypeUser);

                    if (!brk) {
                        strcpy(gdbOutputBuffer, "$E00#");
                        return gdbSendMessage(GDBDataTypeGDB, gdbOutputBuffer, gdbApplyChecksum(gdbOutputBuffer));
                    }
                }

                return gdbSendMessage(GDBDataTypeGDB, "$OK#9a", strlen("$OK#9a"));
            } else {
                break;
            }
        }
    }

    return gdbSendMessage(GDBDataTypeGDB, "$#00", strlen("$#00"));
}

enum GDBError gdbCheckForPacket() {
    char* commandStart;
    char* packetEnd;

    if (gdbSerialCanRead()) {
        enum GDBDataType type;
        u32 len;
        enum GDBError err = gdbPollHeader(&type, &len);
        if (err != GDBErrorNone) return err;
        gdbPacketBuffer[len] = '\0';
        err = gdbReadData(gdbPacketBuffer, len, &len);
        if (err != GDBErrorNone) return err;
        err = gdbFinishRead();
        if (err != GDBErrorNone) return err;

        if (type == GDBDataTypeGDB) {
            if (*gdbPacketBuffer == 0x03) {
                if (gdbRunFlags & GDB_IS_WAITING_STOP) {
                    OSThread* targetThread = gdbFindThread(GDB_ANY_THREAD);

                    if (targetThread) {
                        osStopThread(targetThread);
                        gdbRunFlags &= ~GDB_IS_WAITING_STOP;
                        gdbSendStopReply(targetThread);
                    }
                }
            } else {
                err = gdbParsePacket(gdbPacketBuffer, len, &commandStart, &packetEnd);
                if (err != GDBErrorNone) return err;

                err = gdbSendMessage(GDBDataTypeGDB, "+", strlen("+"));
                if (err != GDBErrorNone) return err;

                err = gdbHandlePacket(commandStart, packetEnd);
                if (err != GDBErrorNone) return err;
            }
        }

        return GDBErrorNone;
    }

    return GDBErrorUSBNoData;
}

void gdbErrorHandler(s16 code, s16 numArgs, ...) {
   va_list valist;

    gdbSendMessage(
        GDBDataTypeText, 
        gdbPacketBuffer, 
        sprintf(gdbPacketBuffer, "code %04X args %04X", code, numArgs)
    );
}

void gdbDebuggerLoop(void *arg) {
    OSMesg msg;
    osCreateMesgQueue(&gdbPollMesgQ, &gdbPollMesgQMessage, 1);

    // give time for the main thead to hit the starting breakpiont
    osSetTimer(&gdbPollTimer, GDB_POLL_DELAY, 0, &gdbPollMesgQ, NULL);
    osRecvMesg(&gdbPollMesgQ, &msg, OS_MESG_BLOCK);

    gdbRunFlags |= GDB_IS_ATTACHED;
    while (gdbRunFlags & GDB_IS_ATTACHED) {
        while (gdbCheckForPacket() == GDBErrorNone);

        if (gdbRunFlags & GDB_IS_WAITING_STOP) {
            osSetTimer(&gdbPollTimer, gdbQuickPollCount ? GDB_QUICK_POLL_DELAY : GDB_POLL_DELAY, 0, &gdbPollMesgQ, NULL);

            if (gdbQuickPollCount > 0) {
                --gdbQuickPollCount;
            }

            int i;
            // while program is running, decrease polling rate
            osRecvMesg(&gdbPollMesgQ, &msg, OS_MESG_BLOCK);

            for (i = 0; i < MAX_DEBUGGER_THREADS; ++i) {
                if (gdbTargetThreads[i] && (gdbTargetThreads[i]->flags & OS_FLAG_FAULT)) {
                    gdbRunFlags &= ~GDB_IS_WAITING_STOP;
                    gdbSendStopReply(gdbTargetThreads[i]);
                    break;
                }
            }
        }
    }
    osDestroyThread(&gdbDebuggerThread);
}

enum GDBError gdbInitDebugger(OSPiHandle* handler, OSMesgQueue* dmaMessageQ, OSThread** forThreads, u32 forThreadsLen)
{
    enum GDBError err = gdbSerialInit(handler, dmaMessageQ);
    if (err != GDBErrorNone) return err;

    OSThread* primaryThread = NULL;
    OSId currThread = osGetThreadId(NULL);

    int i;
    for (i = 0; i < forThreadsLen && i < MAX_DEBUGGER_THREADS; ++i) {
        gdbTargetThreads[i] = forThreads[i];

        if (osGetThreadId(forThreads[i]) == currThread) {
            primaryThread = forThreads[i];
        }
    }
    
    for (;i < MAX_DEBUGGER_THREADS; ++i) {
        gdbTargetThreads[i] = NULL;
    }

    osCreateThread(&gdbDebuggerThread, GDB_DEBUGGER_THREAD_ID, gdbDebuggerLoop, NULL, gdbDebuggerThreadStack + GDB_STACKSIZE/sizeof(u64), 11);
    osStartThread(&gdbDebuggerThread);

    // The main thread needs to be paused before interrupts work
    // I'm not sure why
    if (primaryThread != NULL) {
        osStopThread(primaryThread);
        gdbBreak();
    }
    
    return GDBErrorNone;

}

void* getWatchPoint() {
    return (void*)(__gdbGetWatch() & ~0x7);
}

void gdbSetWatchPoint(void* addr, int read, int write) {
    __gdbSetWatch(((u32)addr & 0x1ffffff8) | (read ? 0x2 : 0) | (write ? 0x1 : 0));
}

void gdbClearWatchPoint() {
    __gdbSetWatch(0);
}

/**
 * Implement gdbBreak in assembly to ensure that `teq` is the first instruction of the function
 */
asm(
".global gdbBreak\n"
".balign 4\n"
"gdbBreak:\n"
    "teq $0, $0\n"
    "jr $ra\n"
    "nop\n"

".global __gdbSetWatch\n"
".balign 4\n"
"__gdbSetWatch:\n"
    "MTC0 $a0, $18\n"
    "jr $ra\n"
    "nop\n"

".global __gdbGetWatch\n"
".balign 4\n"
"__gdbGetWatch:\n"
    "MFC0 $v0, $18\n"
    "jr $ra\n"
    "nop\n"
);