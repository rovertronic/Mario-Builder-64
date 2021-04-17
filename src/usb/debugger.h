
#ifndef __DEBUGGER_H
#define __DEBUGGER_H

#include <ultra64.h>
#include "serial.h"

enum GDBBreakpointType {
    GDBBreakpointTypeNone,
    GDBBreakpointTypeTemporary,
    GDBBreakpointTypeUser,
    GDBBreakpointTypeUserUnapplied,
};

struct GDBBreakpoint {
    u32 addr;
    u32 prevValue;
    enum GDBBreakpointType type; 
};

#define GDB_MAX_BREAK_POINTS    32

/**
 * Initializes the debugger
 * @param handler Pi Handler used for DMA, this is return value 
 *  of osCartRomInit
 * @param dmaMessageQ The message queue used to coordinate use of 
 *  the DMA. This should be the same message queue used for DMA
 *  actions in the rest of your program
 * @param forThreads an array of threads you want the debugger to
 *  watch connect to. If a thread isn't included in this array
 *  it will be ignored by the debugger
 * @param forThreadsLen the length of the forThreads array
 */
enum GDBError gdbInitDebugger(OSPiHandle* handler, OSMesgQueue* dmaMessageQ, OSThread** forThreads, u32 forThreadsLen);
enum GDBError gdbCheckForPacket();

/**
 * A hard coded breakpoint you can include in compiled code
 */
void gdbBreak();

/**
 * Gets the address of the current memory watch point
 */
void* getWatchPoint();
/**
 * Sets a watch point. When a thread reads or writes to the given
 * address. It will pause in the debugger
 * @param addr The address to watch
 * @param read a non zero value signals that a thread will break when addr is read
 * @param write a non zero value signals that a thread will break when addr is written
 */
void gdbSetWatchPoint(void* addr, int read, int write);
/**
 * Removes the current watch point this is the same as doing gdbSetWatchPoint(0, 0, 0)
 */ 
void gdbClearWatchPoint();

#endif