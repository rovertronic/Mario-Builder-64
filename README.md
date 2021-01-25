# UltraSM64

- This repo contains a full decompilation of Super Mario 64 (J), (U), (E), and (SH).
- Naming and documentation of the source code and data structures are in progress.
- It has been edited to allow for the usage of the final "N64 OS" library, version ``2.0L``
- Shindou Rumble Pak code is on for all regions.
- Targeting the iQue Player is supported.
- Saving to 32kbyte/256kbit SRAM is supported.
- Using gzip DEFLATE compression is supported.
- It has been patched with someone2639's shiftable segments patch
- Getting HVQM FMV support to work with the game is in progress.
- Getting UNFLoader (flashcart USB library) to work with the game is in progress.

## Multi-Save support

The repository supports SRAM in addition to EEPROM. The standard save data functions are #ifdef'd to accommedate this.

To build with SRAM support, run make with ``SAVETYPE=sram``.

I may attempt FlashRAM in the future.

## Multi-Console support

The repository supports targeting the iQue Player in addition to the N64. The iQue libultra is ***NOT*** compatible with N64 in many ways, so it is currently NOT possible to have one build for both consoles.

To target iQue, run make with the ``CONSOLE=BB`` argument.

## Compression

The repository supports using DEFLATE compression instead of Nintendo's Yay0. This boasts a better compression ratio, but at a slight cost to load times.

On average I'd estimate that the bottleneck on decompression is about 1-2 seconds.

To switch to gzip, run make with the ``COMPRESS=gzip`` argument.

Additionally, the repo also supports compressing with ``libdeflate-gzip``. This compresses at a slightly better ratio than standard ``gzip``, with no real downside from a decompression standpoint.

To use ``libdeflate-gzip``, first clone the [repo](https://github.com/ebiggers/libdeflate), then make and make install it.

Then run make for sm64 with ``GZIPVER=libdef`` in addition to ``COMPRESS=gzip``

This argument makes the makefile use ``libdeflate`` with it's highest compression setting, ``-12``.


## FAQ

Q: Why in the hell are you bundling your own build of ``ld``?

A: Newer binutils (Like the one bundled with Ubuntu, 2.34) break linking with libultra builds due to local asm symbols.

This puts me at a crossroads of either touching leaked code and requiring GCC, or just using an older linker that works just fine.

I went with the latter.

Thanks to "someone2639" for this hacky-ass idea

Q: Will this allow me to use FlashRAM/Transfer Pak/microcode swapping/Other Cool N64 Features?

A: Theoretically, all yes.

## Installation help


Go read the original repo README.md
