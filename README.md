# UltraSM64-extbounds
**AFTER CLONING THE REPO, CHECK OUT THE `include/config.h` FILE BEFORE ANYTHING ELSE! IT THERE'S A LOT OF STUFF IN THIS REPO THAT CAN BE TOGGLED THERE.**

This repo needs gcc in order to be able to build it. To install it, run `sudo apt install gcc-mips-linux-gnu`

This is a fork of the ultrasm64 repo by CrashOveride which includes the following commonly used patches (patches marked with `*` are toggleable in `config.h`): 

**Collision:**
- Slope fix and exposed ceilings fix
- No false ledgegrabs fix * 
- Jump kick fix * 
- 46 degree wallkicks * 
- Pole fix
- Possibility of disabling BLJs *
- Hanging fix (mario can grab hangable ceilings from any state, instead of only jump or double jump) *
- Increased maximum pole length (The game will read bparam1 and bparam2 together as a single value, so you can have a very long pole) *
- Platform Displacement 2 by Arthurtilly *
- Water Surface Type patch by thecozies
- Rounded corners by FramePerfection, merged by Cheezepin

**Common Hack Changes:**
- Better extended boundaries by anonymous_moose
- Mario head skip *
- Peach letter cutscene skip *
- Exit course while moving *
- Toggle to disable fall damage and the fall damage sound *
- Nonstop stars *
- Removed course-specific camera processing *
- You can increase the number of frames that you have to perform a firsty *

**Hacker QOL:**
- Global, non-level based, star IDs (off by default) *
- FPS counter (use the function `print_fps(x,y)` anywhere that runs code every frame)
- Automatic console/emulator detection. If emulator is detected, LODs are disabled. *
- Ability to configure whether there's a 100 coin star at all and how many coins are required to spawn it *
- Ability to easily change the warp that EXIT COURSE takes you to via config.h, or disable it entirely
- 16 bit model IDs by someone2639. This means you can have up to 65536 models (lol)
- Apply_patch.sh improved
- Removed the ifdef hell in `file_select.c` and `ingame_menu.c`
- Added Blake's custom function for object model stuff: `obj_set_model` and `obj_has_model`
- The "far" variable is now u16, allowing you to increase the farclip (the max distance at which geometry is rendered). However, when increasing the farclip, make sure to increase the nearclip by the same ratio, or rendering will break on console and LLE plugins. 
- Many general use defines for object struct members, meant for use in custom object behaviors. Check `object_fields.h` for more info on this. (By MrComit)
- Included `actors/group0.c` in `behavior_data.c`

**Other Bugfixes:**
- Castle music fix (Fixes the castle music sometimes triggering after getting a dialog) *
- bparam4 fix (the game no longer uses bparam4 to check if an object is mario and therefore you can safely use it)
- Instant warp offset fix (makes the instant warp offset work even when warping to a different area) *
- haveyourcake, also known as cake screen fix. Made by Wiseguy and ported/PR'd by Cheezepin
- Tree particle fix (Whether a tree uses snow particles or not is decided via the model IDs instead of the course number)
- Coordinate overflow fix by falcobuster. Your levels will render correctly on console and LLE emulators even when using 2x or 4x bounds, while not hurting anything on HLE plugins. *This is automatic now, you don't have to set WORLD_SCALE manually.*
- A couple vanilla texture fixes

**Neat Misc. Changes:**
- Instant Input patch by Wiseguy (Removes all input lag caused by plugins supporting framebuffer)
  - This means that you'll have to do your framebuffer effects on buffer 0 for emulator, but NOT for console. You can use the `gIsConsole` variable to check for console when doing your framebuffer effects.
- Widescreen (16:9) support toggleable by pressing `L` in the pause menu. *
- S2DEX engine by someone2639! To use it, compile with `make TEXT_ENGINE=s2dex_text_engine` or just set `TEXT_ENGINE` to `s2dex_text_engine` in the makefile.

# UltraSM64

- This repo contains a full decompilation of Super Mario 64 (J), (U), (E), and (SH).
- Naming and documentation of the source code and data structures are in progress.
- It has been edited to allow for the usage of the final "N64 OS" library, version ``2.0L``
- Shindou Rumble Pak code is on for all regions.
- Targeting the iQue Player is supported.
- Saving to 32kbyte/256kbit SRAM is supported.
- Newer compression options are supported.
- UNFLoader (flashcart USB library) is supported, allowing for debugging on EverDrive/64Drive.
- It has been patched with someone2639's shiftable segments patch
- Getting HVQM FMV support to work with the game is WIP.

Requirements are the same as regular SM64, however a GCC MIPS cross compiler is also required. If you're on Debian-like Linux, you can use the ``gcc-mips-linux-gnu`` package. The toolchain that comes with my SDK is also supported.

## UNFLoader support

The repository supports UNFLoader for debugging.
To build with UNF, run make with ``UNF=1``.

Further instructions can be found at the [official repository](https://github.com/buu342/N64-UNFLoader)

## Multi-Save support
The repository supports SRAM in addition to EEPROM. The standard save data functions are #ifdef'd to accommedate this.
To build with SRAM support, run make with ``SAVETYPE=sram``.

I may attempt FlashRAM in the future.

## Multi-Console support
The repository supports targeting the iQue Player in addition to the N64. The iQue libultra is ***NOT*** compatible with N64 in many ways, so it is currently NOT possible to have one build for both consoles.
To target iQue, run make with the ``CONSOLE=bb`` argument.

## Compression
The repository supports using DEFLATE compression instead of Nintendo's Yay0. This boasts a better compression ratio, but at a slight cost to load times.
On average I'd estimate that the bottleneck on decompression is about 1-2 seconds.

To switch to gzip, run make with the ``COMPRESS=gzip`` argument.

The repo also supports gziping with ``libdeflate-gzip``. This compresses at a slightly better ratio than standard ``gzip``, with no real downside from a decompression standpoint.
To use ``libdeflate-gzip``, first clone the [repo](https://github.com/ebiggers/libdeflate), then make and make install it.
Then run make for sm64 with ``GZIPVER=libdef`` in addition to ``COMPRESS=gzip``

The repo also supports RNC (Rob Northen Compression). RNC has two methods. 
Method 1 is designed to compress as small as possible, while method 2 is designed so that decompression is as fast as possible.

Both methods are fast. Method 1 has better compression than 2, so I suggest using method 1 if using RNC.
To switch to RNC, run make with either ``COMPRESS=rnc1`` or ``COMPRESS=rnc2``, depending on preferred method.

The repo also supports building a ROM with no compression.
This is not recommended as it increases ROM size significantly, with little point other than load times decreased to almost nothing.
To switch to no compression, run make with the ``COMPRESS=uncomp`` argument.

## FAQ

Q: Why in the hell are you bundling your own build of ``ld``?

A: Newer binutils (Like the one bundled with Ubuntu, 2.34) break linking with libultra builds due to local asm symbols.
This puts me at a crossroads of either touching leaked code and requiring GCC, or just using an older linker that works just fine.
I went with the latter.
Thanks to "someone2639" for this hacky-ass idea

Q: Will this allow me to use FlashRAM/Transfer Pak/microcode swapping/Other Cool N64 Features?

A: Theoretically, all yes.

## Installation help

Go read the original SM64 repo README.md
