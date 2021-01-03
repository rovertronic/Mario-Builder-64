#ifndef __os_bb_fs_h__
#define __os_bb_fs_h__

#include <PR/ultratypes.h>
#include <PR/bbfs.h>

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

/**************************************************************************
 *
 * Type definitions
 *
 */

typedef struct {
#ifndef WIN32
    u8 root[2*16*1024] __attribute__((aligned(16))); /* room for two FATs */
#else
    u8 root[2*16*1024]; /* room for two FATs */
#endif
} OSBbFs;

typedef struct {
    u16 files;
    u16 blocks;
    u16 freeFiles;
    u16 freeBlocks;
} OSBbStatFs;

typedef struct {
    char name[BB_INODE16_NAMELEN+2]; /* extra space for '.' and 0 termination */
    u8 type;
    u32 size;
} OSBbDirEnt;

typedef struct {
    u8 type;
    u32 size;
} OSBbStatBuf;

#endif /* defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) */

/**************************************************************************
 *
 * Global definitions
 *
 */


#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

/**************************************************************************
 *
 * Macro definitions
 *
 */

#define BBFS_ERR_NO_CARD	(-1)	/* card not present */
#define BBFS_ERR_FAIL		(-2)	/* operation failed */
#define BBFS_ERR_INVALID	(-3)	/* invalid parameters */
#define BBFS_ERR_CHANGED	(-4)    /* card changed */
#define BBFS_ERR_UNINIT		(-5)	/* fs uninitialized */
#define BBFS_ERR_EXISTS		(-6)	/* file exists */
#define BBFS_ERR_SPACE		(-7)	/* no space */
#define BBFS_ERR_ENTRY		(-8)	/* no entry */

/* Used for saving auxilliary game state data */
#define BBFS_ERR_STATE          (-9)   /* invalid state */
#define BBFS_ERR_STATE_LIMIT   (-10)   /* state limit reached */

/**************************************************************************
 *
 * Extern variables
 *
 */


/**************************************************************************
 *
 * Function prototypes
 *
 */

s32 osBbFInit(OSBbFs* fs);
s32 osBbFStatFs(OSBbStatFs* fs);
s32 osBbFReadDir(OSBbDirEnt* dir, u32 count);
s32 osBbFOpen(const char* name, const char* mode);
s32 osBbFCreate(const char*name, u8 type, u32 len);
s32 osBbFDelete(const char* name);
s32 osBbFRename(const char* old, const char* new);
s32 osBbFClose(s32 fd);
s32 osBbFRead(s32 fd, u32 off, void* buf, u32 len);
s32 osBbFWrite(s32 fd, u32 off, const void* buf, u32 len);
s32 osBbFStat(s32 fd, OSBbStatBuf* sb, u16* blockList, u32 listLen);
s32 osBbFShuffle(s32 sfd, s32 dfd, s32 release, void* buf, u32 len);
s32 osBbFRepairBlock(s32 fd, u32 off, void* buf, u32 len);
s32 osBbFAutoSync(u32 on);
s32 osBbFSync(void);
#endif

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif
#endif /*__os_bb_fs_h__*/
