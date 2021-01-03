#ifndef __os_bb_metadata_h__
#define __os_bb_metadata_h__

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include <PR/bbtypes.h>

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

typedef struct {
    u32 eepromAddress;
    u32 eepromSize;
    u32 flashAddress;
    u32 flashSize;
    u32 sramAddress;
    u32 sramSize;
    u32 pakAddress[MAXCONTROLLERS];
    u32 pakSize;
} OSBbStateVector;

typedef struct {
    OSBbStateVector state;

    u32 romBase;
    s32 tvType;
    u32 memSize;
    u32 errataSize;
    u32 errataAddress;
    
    u32 magic;
} OSBbLaunchMetaData;

#define BB_METADATA_MAGIC    0x43414d00
#define BB_MAX_AUXDATA_SIZE       32768
#define BB_MAX_AUXDATA               16
#define BB_STATENAME_LEN             16

/* Extract permitted auxdata from the metadata */
#define BB_AUXDATA_COUNT(md)    ((md)->magic & 0xFF)

extern s32 osBbSaveState(char stateName[] /* OUTPUT, 8.3 filename */, BbTicketId* tid);
extern s32 osBbLoadState(const char *name, BbTicketId tid, OSBbStateVector *sv, s32 bindings[MAXCONTROLLERS]);
extern s32 osBbGetLaunchMetaData(OSBbLaunchMetaData *md, u16 *blockList, s32 listSize);
extern u32 osBbLoadApp(OSBbLaunchMetaData *md, u16* blockList, s32 listSize, s32 loadAll);
extern s32 osBbExecApp(u32 addr);
extern s32 osBbVerifyFile(const char *name, u8 block[BB_FL_BLOCK_SIZE]);
extern s32 osBbVerifySig(const char *name, BbEccSig sig, u8 block[BB_FL_BLOCK_SIZE]);
extern s32 osBbSignFile(const char *name, u8 block[BB_FL_BLOCK_SIZE]);
extern s32 osBbDeleteSignedFile(const char *name, u8 block[BB_FL_BLOCK_SIZE]);

extern void osBbInitState(const char *name);
extern s32  osBbAuxDataGetLimit();
extern s32  osBbAuxDataSetLimit(u8 limit);

/* State functions to be used by games */
extern s32 osBbGameCommitState();
extern s32 osBbAuxDataInit(void* buf, u32 len);
extern s32 osBbAuxDataSave(u8 id, const void* buf, u32 len);
extern s32 osBbAuxDataLoad(u8 id, void* buf, u32 len);
extern s32 osBbAuxDataDelete(u8 id);
extern s32 osBbAuxDataSize(u8 id);
extern s32 osBbAuxDataIds(u8 ids[BB_MAX_AUXDATA]);

#endif  /* defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) */

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif
