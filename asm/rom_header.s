/*
 * Super Mario 64 ROM header
 * Only the first 0x18 bytes matter to the console.
 */
#include "config.h"
.byte  0x80, 0x37, 0x12, 0x40   /* PI BSD Domain 1 register */
.word  0x0000000F               /* Clockrate setting*/
.word  entry_point              /* Entrypoint */

/* Revision */
#if defined(SRAM)
.word  0x0000344C
#elif defined(EEP16K)
.word  0x0000244C
#elif defined(SRAM768K)
.word  0x0000444C
#elif defined(FLASHRAM)
.word  0x0000544C
#else
.word  0x0000144C
#endif

.word  0x00000000               /* Checksum 1 */
.word  0x00000000               /* Checksum 2 */
.word  0x00000000               /* Unknown */
.word  0x00000000               /* Unknown */
.ascii INTERNAL_ROM_NAME   /* Internal ROM name */
.word  0x00000000               /* Unknown */
.word  0x0000004E               /* Cartridge */
.ascii "ED"                     /* Cartridge ID */

/* Region */
#if defined(VERSION_JP) || defined(VERSION_SH)
    .ascii "J"                  /* NTSC-J (Japan) */
#else
    .ascii "E"                  /* NTSC-U (North America) */
#endif
    .byte  0x00                 /* Version */
