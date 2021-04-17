
#include "serial.h"

u8 (*gdbSerialCanRead)();

#if USE_UNF_LOADER
#include "usb.h"

u32 gdbPendingUNFHeader;
u32 gdbPendingUNFData;

u8 gdbSerialCanRead_UNF() {
    if (gdbPendingUNFHeader == 0) {
        gdbPendingUNFHeader = usb_poll();
    }

    return gdbPendingUNFHeader != 0;
}

enum GDBError gdbSerialInit(OSPiHandle* handler, OSMesgQueue* dmaMessageQ) {
    usb_initialize();
    gdbSerialCanRead = gdbSerialCanRead_UNF;
    return GDBErrorNone;
}

enum GDBError gdbSendMessage(enum GDBDataType type, char* src, u32 len) {
    usb_write(type, src, len);
    return GDBErrorNone;
}

enum GDBError gdbPollHeader(enum GDBDataType* type, u32* len) {
    if (gdbSerialCanRead_UNF()) {
        *type = USBHEADER_GETTYPE(gdbPendingUNFHeader);
        gdbPendingUNFData = USBHEADER_GETSIZE(gdbPendingUNFHeader);
        *len = gdbPendingUNFData;
        gdbPendingUNFHeader = 0;
        return GDBErrorNone;
    } else {
        return GDBErrorUSBNoData;
    }
}

enum GDBError gdbReadData(char* target, u32 len, u32* dataRead) {
    if (len > gdbPendingUNFData) {
        len = gdbPendingUNFData;
    }
    gdbPendingUNFData -= len;
    usb_read(target, len);
    *dataRead = len;
}

enum GDBError gdbFinishRead() {
    usb_skip(gdbPendingUNFData);
    gdbPendingUNFData = 0;
}

#else // USE_UNF_LOADER

#include <string.h>

#define GDB_USB_SERIAL_SIZE 512

static OSMesgQueue* __gdbDmaMessageQ;

#define KSEG0           0x80000000
#define KSEG1           0xA0000000

#define REG_BASE        0x1F800000
#define REG_ADDR(reg)   (KSEG1 | REG_BASE | (reg))

#define USB_LE_CFG      0x8000
#define USB_LE_CTR      0x4000

#define USB_CFG_ACT     0x0200
#define USB_CFG_RD      0x0400
#define USB_CFG_WR      0x0000

#define USB_STA_ACT     0x0200
#define USB_STA_RXF     0x0400
#define USB_STA_TXE     0x0800
#define USB_STA_PWR     0x1000
#define USB_STA_BSY     0x2000

#define USB_CMD_RD_NOP  (USB_LE_CFG | USB_LE_CTR | USB_CFG_RD)
#define USB_CMD_RD      (USB_LE_CFG | USB_LE_CTR | USB_CFG_RD | USB_CFG_ACT)
#define USB_CMD_WR_NOP  (USB_LE_CFG | USB_LE_CTR | USB_CFG_WR)
#define USB_CMD_WR      (USB_LE_CFG | USB_LE_CTR | USB_CFG_WR | USB_CFG_ACT)

#define HEADER_TEXT_LENGTH      4
#define MESSAGE_HEADER_SIZE     8
#define MESSAGE_FOOTER_SIZE     4

#define GDB_IS_READING  1

#define ALIGN_16_BYTES(input)   (((input) + 0xF) & ~0xF)
#define ALIGN_8_BYTES(input)   (((input) + 0x7) & ~0x7)
#define ALIGN_2_BYTES(input)   (((input) + 0x1) & ~0x1)

#define USB_MIN_SIZE            16

// used to ensure that the memory buffers are aligned to 8 bytes
long long __gdbAlignAndFlags;
char gdbSerialSendBuffer[GDB_USB_SERIAL_SIZE];
char gdbSerialReadBuffer[GDB_USB_SERIAL_SIZE];
static OSPiHandle gdbSerialHandle;
static OSMesgQueue gdbSerialSemaphore;
static OSMesg gdbSerialSemaphoreMsg;

static char gdbHeaderText[] = "DMA@";
static char gdbFooterText[] = "CMPH";

enum GDBError (*gdbSerialRead)(char* target, u32 len);
enum GDBError (*gdbSerialWrite)(char* src, u32 len);
enum GDBCartType gdbCartType;

enum GDBEVRegister {
    GDB_EV_REGISTER_USB_CFG = 0x0004,
    GDB_EV_REGISTER_USB_TIMER = 0x000C,
    GDB_EV_REGISTER_VERSION = 0x0014,
    GDB_EV_REGISTER_USB_DATA = 0x0400,
    GDB_EV_REGISTER_SYS_CFG = 0x8000,
    GDB_EV_REGISTER_KEY = 0x8004,
};

enum GDBError gdbDMARead(void* ram, u32 piAddress, u32 len) {
	OSIoMesg dmaIoMesgBuf;

    dmaIoMesgBuf.hdr.pri = OS_MESG_PRI_NORMAL;
    dmaIoMesgBuf.hdr.retQueue = __gdbDmaMessageQ;
    dmaIoMesgBuf.dramAddr = ram;
    dmaIoMesgBuf.devAddr = piAddress & 0x1FFFFFFF;
    dmaIoMesgBuf.size = len;

    osInvalDCache(ram, len);
    if (osEPiStartDma(&gdbSerialHandle, &dmaIoMesgBuf, OS_READ) == -1)
    {
        return GDBErrorDMA;
    }

    osRecvMesg(__gdbDmaMessageQ, NULL, OS_MESG_BLOCK);

    return GDBErrorNone;
}

enum GDBError gdbDMAWrite(void* ram, u32 piAddress, u32 len) {
	OSIoMesg dmaIoMesgBuf;

    dmaIoMesgBuf.hdr.pri = OS_MESG_PRI_NORMAL;
    dmaIoMesgBuf.hdr.retQueue = __gdbDmaMessageQ;
    dmaIoMesgBuf.dramAddr = ram;
    dmaIoMesgBuf.devAddr = piAddress & 0x1FFFFFFF;
    dmaIoMesgBuf.size = len;

    osWritebackDCache(ram, len);
    if (osEPiStartDma(&gdbSerialHandle, &dmaIoMesgBuf, OS_WRITE) == -1)
    {
        return GDBErrorDMA;
    }

    osRecvMesg(__gdbDmaMessageQ, NULL, OS_MESG_BLOCK);

    return GDBErrorNone;
}

u32 gdbReadReg(enum GDBEVRegister reg) {
    return *((u32*)REG_ADDR(reg));
}

void gdbWriteReg(enum GDBEVRegister reg, u32 value) {
    *((u32*)REG_ADDR(reg)) = value;
}

enum GDBError gdbUsbBusy() {
    u32 tout = 0;
    enum GDBError err;
    u32 registerValue;

    do {
        if (tout++ > 8192) {
            gdbWriteReg(GDB_EV_REGISTER_USB_CFG, USB_CMD_RD_NOP);
            return GDBErrorUSBTimeout;
        }
        registerValue = gdbReadReg(GDB_EV_REGISTER_USB_CFG);
    } while ((registerValue & USB_STA_ACT) != 0);

    return GDBErrorNone;
}

u8 gdbSerialCanRead_X7() {
    return (gdbReadReg(GDB_EV_REGISTER_USB_CFG) & (USB_STA_PWR | USB_STA_RXF)) == USB_STA_PWR;
}

enum GDBError gdbSerialRead_X7(char* target, u32 len) {
    while (len) {
        int chunkSize = GDB_USB_SERIAL_SIZE;
        if (chunkSize > len) {
            chunkSize = len;
        }
        int baddr = GDB_USB_SERIAL_SIZE - chunkSize;

        gdbWriteReg(GDB_EV_REGISTER_USB_CFG, USB_CMD_RD | baddr);

        enum GDBError err = gdbUsbBusy();
        if (err != GDBErrorNone) return err;

        err = gdbDMARead(target, REG_ADDR(GDB_EV_REGISTER_USB_DATA + baddr), chunkSize);
        if (err != GDBErrorNone) return err;

        target += chunkSize;
        len -= chunkSize;
    }

    return GDBErrorNone;
}

u8 gdbSerialCanWrite() {
    return (gdbReadReg(GDB_EV_REGISTER_USB_CFG) & (USB_STA_PWR | USB_STA_TXE)) == USB_STA_PWR;
}

enum GDBError gdbWaitForWritable() {
    u32 timeout = 0;

    while (!gdbSerialCanWrite()) {
        if (++timeout == 8192) {
            return GDBErrorUSBTimeout;
        }
    }

    return GDBErrorNone;
}

enum GDBError gdbSerialWrite_X7(char* src, u32 len) {
    enum GDBError err = gdbWaitForWritable();
    if (err != GDBErrorNone) return err;

    gdbWriteReg(GDB_EV_REGISTER_USB_CFG, USB_CMD_WR_NOP);

    while (len) {
        int chunkSize = GDB_USB_SERIAL_SIZE;
        if (chunkSize > len) {
            chunkSize = len;
        }
        int baddr = GDB_USB_SERIAL_SIZE - chunkSize;
        err = gdbDMAWrite(src, REG_ADDR(GDB_EV_REGISTER_USB_DATA + baddr), chunkSize);
        if (err != GDBErrorNone) return err;

        gdbWriteReg(GDB_EV_REGISTER_USB_CFG, USB_CMD_WR | baddr);

        err = gdbUsbBusy();
        if (err != GDBErrorNone) return err;

        src += chunkSize;
        len -= chunkSize;
    }

    return GDBErrorNone;
}

u8 gdbSerialCanRead_cen64() {
    return *((volatile u32*)(0xA0000000 | 0x18000004));
}

enum GDBError gdbSerialRead_cen64(char* target, u32 len) {
    while (len--) {
        *target++ = *((volatile u32*)(0xA0000000 | 0x18000000));
    }
    return GDBErrorNone;
}

enum GDBError gdbSerialWrite_cen64(char* target, u32 len) {
    while (len--) {
        *((volatile u32*)(0xA0000000 | 0x18000000)) = *target++;
    }
    return GDBErrorNone;
}

enum GDBError gdbSerialInit(OSPiHandle* handler, OSMesgQueue* dmaMessageQ)
{
    gdbSerialHandle = *handler;

    volatile u32* cen64Check = (volatile u32*)(0xA0000000 | 0x18000008);
    if (*cen64Check == 0xcece) {
        gdbSerialCanRead = gdbSerialCanRead_cen64;
        gdbSerialRead = gdbSerialRead_cen64;
        gdbSerialWrite = gdbSerialWrite_cen64;
        gdbCartType = GDBCartTypeCen64;
    } else {
        gdbSerialCanRead = gdbSerialCanRead_X7;
        gdbSerialRead = gdbSerialRead_X7;
        gdbSerialWrite = gdbSerialWrite_X7;
        gdbCartType = GDBCartTypeX7;

        gdbSerialHandle.latency = 0x04;
        gdbSerialHandle.pulse = 0x0C;

        OSIntMask prev = osGetIntMask();
        osSetIntMask(0);
        gdbSerialHandle.next = __osPiTable;
        __osPiTable = &gdbSerialHandle;
        osSetIntMask(prev);

        __gdbDmaMessageQ = dmaMessageQ;

        osCreateMesgQueue(&gdbSerialSemaphore, &gdbSerialSemaphoreMsg, 1);

        gdbWriteReg(GDB_EV_REGISTER_KEY, 0xAA55);
        gdbWriteReg(GDB_EV_REGISTER_SYS_CFG, 0);
        gdbWriteReg(GDB_EV_REGISTER_USB_CFG, USB_CMD_RD_NOP);
    }

    return GDBErrorNone;
}

enum GDBError __gdbSendMessage(enum GDBDataType type, char* src, u32 len) {
    if (len >= 0x1000000) {
        return GDBErrorMessageTooLong;
    }

    u32 header = (type << 24) | (0xFFFFFF & len);
    strcpy(gdbSerialSendBuffer, gdbHeaderText);
    memcpy(gdbSerialSendBuffer + HEADER_TEXT_LENGTH, (char*)&header, sizeof(u32));

    u32 firstChunkLength = len;

    if (firstChunkLength > GDB_USB_SERIAL_SIZE - MESSAGE_HEADER_SIZE) {
        firstChunkLength = GDB_USB_SERIAL_SIZE - MESSAGE_HEADER_SIZE;
    }

    enum GDBError err;

    memcpy(gdbSerialSendBuffer + MESSAGE_HEADER_SIZE, src, firstChunkLength);

    if (GDB_USB_SERIAL_SIZE >= MESSAGE_HEADER_SIZE + firstChunkLength + MESSAGE_FOOTER_SIZE) {
        // entire message fits into a single 512 byte buffer
        strcpy(gdbSerialSendBuffer + MESSAGE_HEADER_SIZE + firstChunkLength, gdbFooterText);
        err = gdbSerialWrite(gdbSerialSendBuffer, ALIGN_2_BYTES(MESSAGE_HEADER_SIZE + firstChunkLength + MESSAGE_FOOTER_SIZE));
        if (err != GDBErrorNone) return err;
    } else {
        // header partially fits
        if (GDB_USB_SERIAL_SIZE > MESSAGE_HEADER_SIZE + firstChunkLength) {
            memcpy(gdbSerialSendBuffer + MESSAGE_HEADER_SIZE + firstChunkLength, gdbFooterText, GDB_USB_SERIAL_SIZE - MESSAGE_HEADER_SIZE - firstChunkLength);
        }

        err = gdbSerialWrite(gdbSerialSendBuffer, GDB_USB_SERIAL_SIZE);
        if (err != GDBErrorNone) return err;
        src += firstChunkLength;
        len -= firstChunkLength;

        while (len >= GDB_USB_SERIAL_SIZE) {
            if ((int)src == ((int)src & !0x7)) {
                err = gdbSerialWrite(src, GDB_USB_SERIAL_SIZE);
            } else {
                memcpy(gdbSerialSendBuffer, src, GDB_USB_SERIAL_SIZE);
                gdbSerialWrite(gdbSerialSendBuffer, GDB_USB_SERIAL_SIZE);
            }
            if (err != GDBErrorNone) return err;
            src += GDB_USB_SERIAL_SIZE;
            len -= GDB_USB_SERIAL_SIZE;
        }

        if (len) {
            memcpy(gdbSerialSendBuffer, src, len);
        }

        if (len + MESSAGE_FOOTER_SIZE <= GDB_USB_SERIAL_SIZE) {
            strcpy(gdbSerialSendBuffer + len, gdbFooterText);
            err = gdbSerialWrite(gdbSerialSendBuffer, len + MESSAGE_FOOTER_SIZE);
            if (err != GDBErrorNone) return err;
        } else {
            memcpy(gdbSerialSendBuffer + len, gdbFooterText, GDB_USB_SERIAL_SIZE - len);
            err = gdbSerialWrite(gdbSerialSendBuffer, GDB_USB_SERIAL_SIZE);
            if (err != GDBErrorNone) return err;
            strcpy(gdbSerialSendBuffer, &gdbFooterText[GDB_USB_SERIAL_SIZE - len]);
            err = gdbSerialWrite(gdbSerialSendBuffer, MESSAGE_FOOTER_SIZE + len - GDB_USB_SERIAL_SIZE);
            if (err != GDBErrorNone) return err;
        }
    }

    return GDBErrorNone;
}

enum GDBError gdbSendMessage(enum GDBDataType type, char* src, u32 len) {
    // usb_write(type, src, len);
    // return GDBErrorNone;
    OSMesg msg = 0;
    // osSendMesg(&gdbSerialSemaphore, msg, OS_MESG_BLOCK);
    enum GDBError result = __gdbSendMessage(type, src, len);
    // osRecvMesg(&gdbSerialSemaphore, &msg, OS_MESG_NOBLOCK);
    return result;
}

static u32 gdbReadHead;
static u32 gdbMaxReadHead;
static u32 gdbRemainingLen;

enum GDBError gdbPollHeader(enum GDBDataType* type, u32* len) {
    if (!gdbSerialCanRead()) {
        return GDBErrorUSBNoData;
    }

    enum GDBError err = gdbSerialRead(gdbSerialReadBuffer, USB_MIN_SIZE);
    if (err != GDBErrorNone)  return err;

    if (strncmp(gdbSerialReadBuffer, gdbHeaderText, HEADER_TEXT_LENGTH) == 0) {
        *type = gdbSerialReadBuffer[4];
        gdbRemainingLen = 0xFFFFFF & *((u32*)&gdbSerialReadBuffer[4]);
        *len = gdbRemainingLen;
        gdbReadHead = MESSAGE_HEADER_SIZE;
        gdbMaxReadHead = USB_MIN_SIZE;
        __gdbAlignAndFlags |= GDB_IS_READING;

        u32 dataWithLength = gdbRemainingLen + MESSAGE_HEADER_SIZE + MESSAGE_FOOTER_SIZE;
        return GDBErrorNone;
    }

    return GDBErrorUSBNoData;
}

enum GDBError gdbReadData(char* target, u32 len, u32* dataRead) {
    if (len > gdbRemainingLen) {
        len = gdbRemainingLen;
    }

    u32 pendingData = gdbMaxReadHead - gdbReadHead;
    *dataRead = 0;

    if (len <= pendingData) {
        memcpy(target, &gdbSerialReadBuffer[gdbReadHead], len);
        gdbReadHead += len;
        gdbRemainingLen -= len;
        *dataRead += len;
        return GDBErrorNone;
    }

    if (pendingData > 0) {
        memcpy(target, &gdbSerialReadBuffer[gdbReadHead], pendingData);
        target += pendingData;
        len -= pendingData;
        *dataRead += pendingData;
        gdbRemainingLen -= pendingData;
    }

    gdbReadHead = 0;
    gdbMaxReadHead = 0;

    enum GDBError err;

    while (len > GDB_USB_SERIAL_SIZE) {
        // if data is aligned, read directly into the buffer
        if ((u32)target == ALIGN_8_BYTES((u32)target)) {
            u32 bytesToRead = len & ~0x1FF;
            err = gdbSerialRead(target, bytesToRead);
            if (err != GDBErrorNone) return err;
            len -= bytesToRead;
            gdbRemainingLen -= bytesToRead;
            *dataRead += bytesToRead;
            target += bytesToRead;
        } else {
            err = gdbSerialRead(gdbSerialReadBuffer, GDB_USB_SERIAL_SIZE);
            if (err != GDBErrorNone) return err;
            memcpy(target, gdbSerialReadBuffer, GDB_USB_SERIAL_SIZE);
            len -= GDB_USB_SERIAL_SIZE;
            gdbRemainingLen -= GDB_USB_SERIAL_SIZE;
            *dataRead += GDB_USB_SERIAL_SIZE;
            target += GDB_USB_SERIAL_SIZE;
        }
    }

    u32 dataToRead = ALIGN_16_BYTES(gdbRemainingLen + MESSAGE_FOOTER_SIZE);

    if (dataToRead > GDB_USB_SERIAL_SIZE) {
        dataToRead = GDB_USB_SERIAL_SIZE;
    }

    err = gdbSerialRead(gdbSerialReadBuffer, dataToRead);
    if (err != GDBErrorNone) return err;

    gdbMaxReadHead = dataToRead;

    memcpy(target, gdbSerialReadBuffer, len);
    gdbReadHead += len;
    gdbRemainingLen -= len;
    *dataRead += len;

    if (gdbRemainingLen == 0 && (__gdbAlignAndFlags & GDB_IS_READING)) {
        gdbRemainingLen = MESSAGE_FOOTER_SIZE;
        // this prevents an infinite loop when reading the footer
        __gdbAlignAndFlags &= ~GDB_IS_READING;
        char footerCheck[4];
        u32 footerDataRead;
        err = gdbReadData(footerCheck, MESSAGE_FOOTER_SIZE, &footerDataRead);
        if (err != GDBErrorNone) return err;
        gdbRemainingLen = 0;

        if (footerDataRead == MESSAGE_FOOTER_SIZE && 
            strncmp(gdbFooterText, footerCheck, MESSAGE_FOOTER_SIZE) != 0) {
            return GDBErrorBadFooter;
        }
    }

    return GDBErrorNone;
}

enum GDBError gdbFinishRead() {
    u32 actuallyRead;
    enum GDBError err;
    while (gdbRemainingLen > 0) {
        if (gdbRemainingLen > GDB_USB_SERIAL_SIZE) {
            err = gdbReadData(gdbSerialReadBuffer, GDB_USB_SERIAL_SIZE, &actuallyRead);
            if (err != GDBErrorNone) return err;
        } else {
            err = gdbReadData(gdbSerialReadBuffer, gdbRemainingLen, &actuallyRead);
            if (err != GDBErrorNone) return err;
        }
    }
    return GDBErrorNone;
}

#endif // USE_UNF_LOADER