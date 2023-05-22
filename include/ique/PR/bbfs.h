#ifndef __bb_fs_h__
#define __bb_fs_h__

#include <PR/bbtypes.h>

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

/*
 *  BBplayer file system data structures
 */

#define BB_FL_PAGE_SIZE		512
#define BB_FL_SPARE_SIZE	16
#define BB_FL_BLOCK_SIZE	16384
#define BB_FL_BYTE_TO_BLOCK(x)	((u32)(x)>>14)
#define BB_FL_BLOCK_TO_BYTE(x)	((u32)(x)<<14)
#define BB_FL_KB_TO_BLOCK(x)	((u32)(x)>>4)
#define BB_FL_BLOCK_TO_KB(x)	((u32)(x)<<4)
#define BB_FL_BYTE_TO_PAGE(x)	((u32)(x)>>9)
#define BB_FL_PAGE_TO_BYTE(x)	((u32)(x)<<9)
#define BB_FL_BLOCK_PAGES	(BB_FL_BLOCK_SIZE/BB_FL_PAGE_SIZE)
#define BB_FL_ECC0_OFF		(525-512)
#define BB_FL_ECC1_OFF		(520-512)
#define BB_FL_BLOCK_STATUS_OFF	(517-512)
#define BB_FL_BLOCK_LINK_OFF	(512-512)
#define BB_FL_BLOCK_LINK_SIZE   2
#define BB_FL_SEQ_OFF		(514-512)

/* 
 * FAT entries are 16-bit block numbers, each pointing to the
 * next block in a file or a system-specific code
 * Block numbers are relative to the start of the device.
 */
typedef u16 BbFatEntry;	

#define BB_FAT_AVAIL		0x0000	/* available block */
#define BB_FAT_LAST		0xFFFF	/* last block of a file */
#define BB_FAT_BAD		0xFFFE	/* unreadable/writable block */
#define BB_FAT_RESERVED		0xFFFD	/* reserved block */

#define BB_FAT16_ENTRIES	4096	/* enough to span 64MB */
#define BB_FAT16_ENTRIES_SHIFT	12	/* enough to span 64MB */

#define BB_INODE16_ENTRIES	409	/* remainder of space in FAT block */
#define BB_INODE16_NAMELEN	11	/* maximum name length */

#define BB_FAT16_MAGIC		"BBFS"
#define BB_FAT16_LINK_MAGIC	"BBFL"

#define BB_FAT16_CKSUM		0xcad7

#define BB_FAT16_BLOCKS		16	/* number of copies of the fat */
#define BB_SYSTEM_AREA_SIZE	0x100000 /* 384KB reserved for system area */
#define BB_BIG_FILE_THRESHOLD	0x100000	/* allocation hint */

/*
 * Inode entries contain the file name, type, first block address 
 * and file size.  There are a fixed number of inodes immediately
 * following the FAT entries.
 */

/*
 * All fields are big-endian
 */

typedef struct {
    u8 name[BB_INODE16_NAMELEN];	/* 8.3 name */
    u8 type;		/* unused type field */
    u16 block;		/* address of first block in file */
    u16 pad;		/* to align on 4-byte boundary */
    u32 size;		/* size of file in bytes */
} BbInode;

typedef struct {		/* FAT for a 16K block size */
    BbFatEntry entry[BB_FAT16_ENTRIES];
    BbInode inode[BB_INODE16_ENTRIES];
    u8 magic[4];		/* 'BBFS' */
    u32 seq;			/* highest number is current */
    u16 link;			/* link to another FAT */
    u16 cksum;			/* mod 2^16 checksum */
} BbFat16;

#define BB_FAT16_NEXT(fat,n)	(fat)[(n)>>BB_FAT16_ENTRIES_SHIFT].entry[(n)&(BB_FAT16_ENTRIES-1)]

#endif
#endif
