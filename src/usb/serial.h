
#ifndef __SERIAL_H
#define __SERIAL_H

#include <ultra64.h>

// #define USE_UNF_LOADER  1

enum GDBError {
    GDBErrorNone,
    GDBErrorUSBTimeout,
    GDBErrorUSBNoData,
    GDBErrorBadPacket,
    GDBErrorMessageTooLong,
    GDBErrorBadFooter,
    GDBErrorDMA,
    GDBErrorBufferTooSmall,
};

enum GDBDataType {
    GDBDataTypeNone,
    GDBDataTypeText,
    GDBDataTypeRawBinary,
    GDBDataTypeScreenshot,
    GDBDataTypeGDB,
};

enum GDBCartType {
    GDBCartTypeNone,
    GDBCartTypeX7,
    GDBCartTypeCen64,
};

extern u8 (*gdbSerialCanRead)();

enum GDBError gdbSerialInit(OSPiHandle* handler, OSMesgQueue* dmaMessageQ);

enum GDBError gdbSendMessage(enum GDBDataType type, char* src, u32 len);

enum GDBError gdbPollHeader(enum GDBDataType* type, u32* len);
enum GDBError gdbReadData(char* target, u32 len, u32* dataRead);
enum GDBError gdbFinishRead();

#endif