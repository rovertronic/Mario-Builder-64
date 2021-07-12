/*
 * Super Mario 64 ROM header
 * Only the first 0x18 bytes matter to the console.
 */
#include "config.h"
.byte  0x80, 0x37, 0x12, 0x40   /* PI BSD Domain 1 register */
.word  0x0000000F               /* Clockrate setting*/
.word  entry_point              /* Entrypoint */

/* Revision */
.word  0x0000144C

.word  0x00000000               /* Checksum 1 */
.word  0x00000000               /* Checksum 2 */
.word  0x00000000               /* Unknown */
.word  0x00000000               /* Unknown */
.if VERSION_SH == 1
.ascii INTERNAL_ROM_NAME   /* Internal ROM name */
.else
.ascii INTERNAL_ROM_NAME   /* Internal ROM name */
.endif
.word  0x00000000               /* Unknown */
.word  0x0000004E               /* Cartridge */
.ascii "SM"                     /* Cartridge ID */

/* Region */
.if VERSION_US == 1
    .ascii "E"                  /* NTSC-U (North America) */
.elseif (VERSION_JP == 1 || VERSION_SH == 1)
    .ascii "J"                  /* NTSC-J (Japan) */
.else
    .ascii "P"                  /* PAL (Europe) */
.endif

    .byte  0x00                 /* Version */
