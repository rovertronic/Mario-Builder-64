# UltraSM64

- This repo contains a full decompilation of Super Mario 64 (J), (U), (E), and (SH).
- Naming and documentation of the source code and data structures are in progress.
- Efforts to decompile the Shindou ROM steadily advance.
- It will be edited to allow for the usage of the final "N64 OS" library, version ``2.0L``
- Support for Shindou Rumble Pak code may be included in the future.
- It will be patched with someone2639's shiftable segments patch
- It will have extremely WIP HVQM full motion video support
- Getting UNFLoader (flashcart USB library) to work with the game is in progress.

## FAQ

Q: Why in the hell are you bundling your own build of ``ld``?

A: Newer binutils (Like the one bundled with Ubuntu, 2.34) break linking with libultra builds due to local asm symbols.

This puts me at a crossroads of either touching leaked code and requiring GCC, or just using an older linker that works just fine.

I went with the latter.

Thanks to "someone2639 on soundcloud xd" for this hacky-ass idea

Q: Will this allow me to use Rumble/FlashRAM/Transfer Pak/microcode swapping/Other Cool N64 Features?

A: Theoretically, all yes.

## Installation help


Go read the original repo README.md
