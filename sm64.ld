OUTPUT_ARCH (mips)

#define LINKER /* Removes externs from preprocessed script */
#define TARGET_N64
#include "include/segments.h"
#include "include/config.h"
#undef LINKER

#define BEGIN_SEG(name, addr) \
    _##name##SegmentStart = ADDR(.name); \
    _##name##SegmentRomStart = __romPos; \
    .name addr : AT(__romPos)

#define END_SEG(name) \
    _##name##SegmentEnd = ADDR(.name) + SIZEOF(.name); \
    _##name##SegmentRomEnd = __romPos + SIZEOF(.name); \
    __romPos += SIZEOF(.name);

#define BEGIN_NOLOAD(name) \
    _##name##SegmentBssStart = ADDR(.name.noload); \
    .name.noload (NOLOAD) :

#define END_NOLOAD(name) \
    _##name##SegmentBssEnd = ADDR(.name.noload) + SIZEOF(.name.noload); \
    _##name##SegmentBssSize = SIZEOF(.name.noload);

#define YAY0_SEG(name, segAddr) \
   BEGIN_SEG(name##_yay0, segAddr) \
   { \
      KEEP(BUILD_DIR/bin/name.szp.o(.data*)); \
      . = ALIGN(0x10); \
   } \
   END_SEG(name##_yay0) \
   _##name##_mio0SegmentRomStart = _##name##_yay0SegmentRomStart; \
   _##name##_mio0SegmentRomEnd   = _##name##_yay0SegmentRomEnd;

#define YAY0_EU_SEG(name, segAddr) \
   BEGIN_SEG(name##_yay0, segAddr) \
   { \
      KEEP(BUILD_DIR/bin/eu/name.szp.o(.data*)); \
      . = ALIGN(0x10); \
   } \
   END_SEG(name##_yay0) \
   _##name##_mio0SegmentRomStart = _##name##_yay0SegmentRomStart; \
   _##name##_mio0SegmentRomEnd   = _##name##_yay0SegmentRomEnd;

#define STANDARD_OBJECTS(name, segAddr, geoAddr) \
   BEGIN_SEG(name##_yay0, segAddr) \
   { \
      KEEP(BUILD_DIR/actors/name.szp.o(.data*)); \
      . = ALIGN(0x10); \
   } \
   END_SEG(name##_yay0) \
   BEGIN_SEG(name##_geo, geoAddr) \
   { \
      KEEP(BUILD_DIR/actors/name##_geo.o(.*data*)); \
      KEEP(BUILD_DIR/actors/name##_geo.o(.rodata*)); \
      KEEP(BUILD_DIR/actors/name##_geo.o(.text*)); \
   } \
   END_SEG(name##_geo) \
   BEGIN_NOLOAD(name##_geo) \
   { \
      KEEP(BUILD_DIR/actors/name##_geo.o(.bss*)); \
   } \
   END_NOLOAD(name##_geo) \
   _##name##_mio0SegmentRomStart = _##name##_yay0SegmentRomStart; \
   _##name##_mio0SegmentRomEnd = _##name##_yay0SegmentRomEnd;

SECTIONS
{
   __romPos = 0;

   BEGIN_SEG(boot, 0x04000000)
   {
      KEEP(BUILD_DIR/asm/rom_header.o(.text*));
      KEEP(BUILD_DIR/asm/ipl3.o(.text*));
   }
   END_SEG(boot)

   . = (RAM_START + 0x400);
   BEGIN_NOLOAD(zbuffer)
   {
      BUILD_DIR/src/buffers/zbuffer.o(.bss*);
   }
   END_NOLOAD(zbuffer)

   . = _zbufferSegmentBssEnd;
   BEGIN_NOLOAD(buffers)
   {
      BUILD_DIR/src/buffers/buffers.o(.bss*);
      BUILD_DIR/src/audio/globals_start.o(.bss*);
      BUILD_DIR/src/audio/synthesis.o(.bss*);
      BUILD_DIR/src/audio/heap.o(.bss*);
      BUILD_DIR/src/audio/load.o(.bss*);
      BUILD_DIR/src/audio/data.o(.bss*);
      BUILD_DIR/src/audio*.o(.bss*);
      . = ALIGN(0x10);
      BUILD_DIR/src/buffers/gfx_output_buffer.o(.bss*);
   }
   END_NOLOAD(buffers)

   . = _buffersSegmentBssEnd;

/* hardcoded symbols to satisfy preliminary link for map parser */
#ifndef DEBUG_MAP_STACKTRACE
      _mapDataSegmentRomStart = 0;
      gMapEntries   = 0;
      gMapEntrySize = 0;
      gMapStrings   = 0;
#endif

   BEGIN_SEG(main, .) SUBALIGN(16)
   {
      KEEP(BUILD_DIR/asm/entry.o(.text*));
      KEEP(BUILD_DIR/asm/n64_assert.o(.text*));
#ifdef EEP
      KEEP(BUILD_DIR/asm/vc_bin.o(.text*));
#endif
      KEEP(BUILD_DIR/asm/round.o(.text*));
      KEEP(BUILD_DIR/asm/fcr31.o(.text*));

      BUILD_DIR/src/boot*.o(.text*);
      BUILD_DIR/src/usb*.o(.text*);
      BUILD_DIR/src/audio*.o(.text*);
#ifdef LIBPL
      BUILD_DIR/lib/libpl*.o(.text*);
#endif
      BUILD_DIR/lib/librtc*.o(.text*);
      *ULTRALIB.a:*.o(.text*);
      *libnustd.a:*.o(.text*);
      *libgcc.a:*.o(.text*);
      BUILD_DIR/lib/libcart*.o(.text*);
      lib/rspboot.o(.text*);
#include "rsptext.inc.ld"
      BUILD_DIR/lib/aspMain.o(.text*);
      lib/PR/audio/n_aspMain.o(.text*);
      _mainSegmentTextEnd = .;

      /* data */
      BUILD_DIR/asm/n64_assert.o(.*data*);
      BUILD_DIR/src/boot*.o(.*data*);
      BUILD_DIR/src/audio*.o(.*data*);
#ifdef LIBPL
      BUILD_DIR/lib/libpl*.o(.*data*);
#endif
      BUILD_DIR/lib/librtc*.o(.*data*);
      *ULTRALIB.a:*.o(.data*);
      BUILD_DIR/lib/libcart*.o(.data*);
#include "rspdata.inc.ld"
      BUILD_DIR/lib/aspMain.o(.data*);
      lib/PR/audio/n_aspMain.o(.data*);

      /* rodata */
      BUILD_DIR/src/boot*.o(.rodata*);
      BUILD_DIR/src/usb*.o(.rodata*);
      BUILD_DIR/src/audio*.o(.rodata*);
#ifdef LIBPL
      BUILD_DIR/lib/libpl*.o(.rodata*);
#endif
      BUILD_DIR/lib/librtc*.o(.rodata*);
      *ULTRALIB.a:*.o(.rodata*);
      *libgcc.a:*.o(.rodata*);

      BUILD_DIR/lib/libcart*.o(.rodata*);
   }
   END_SEG(main)
   BEGIN_NOLOAD(main)
   {
      BUILD_DIR/src/boot*.o(.*bss*);
      BUILD_DIR/src/usb*.o(.*bss*);
      BUILD_DIR/src/audio*.o(.*bss*);
#ifdef LIBPL
      BUILD_DIR/lib/libpl*.o(.*bss*);
#endif
      BUILD_DIR/lib/librtc*.o(.*bss*);
      *ULTRALIB.a:*.o(COMMON);
      *ULTRALIB.a:*.o(.scommon);
      *ULTRALIB.a:*.o(.*bss*);
      BUILD_DIR/lib/libcart*.o(.bss*);
      . = ALIGN(0x8);
   }
   END_NOLOAD(main)

   . = _mainSegmentBssEnd;

   BEGIN_SEG(engine, .)
   {
      BUILD_DIR/src/game*.o(.text*);
      BUILD_DIR/src/game/behavior_actions.o(.text*);
      BUILD_DIR/src/game/obj_behaviors_2.o(.text*);
      BUILD_DIR/src/game/obj_behaviors.o(.text*);
      BUILD_DIR/src/game/object_helpers.o(.text*);
      BUILD_DIR/src/game/rendering_graph_node.o(.text*);
      BUILD_DIR/src/engine/math_util.o(.text*);
      BUILD_DIR/src/engine/surface_collision.o(.text*);
      BUILD_DIR/src/engine/surface_load.o(.text*);
      BUILD_DIR/src/engine/graph_node.o(.text*);
      BUILD_DIR/src/engine*.o(.text*);
      BUILD_DIR/src/mb64*.o(.text*);
      _engineSegmentTextEnd = .;
      /* data */
      BUILD_DIR/src/game*.o(.data*);
      BUILD_DIR/src/engine*.o(.data*);
      BUILD_DIR/src/usb*.o(.data*);
      BUILD_DIR/src/mb64*.o(.data*);
      /* sdata */
      BUILD_DIR/src/game*.o(.sdata*);
      BUILD_DIR/src/engine*.o(.sdata*);
      BUILD_DIR/src/usb*.o(.data*);
      BUILD_DIR/src/mb64*.o(.sdata*);
      /* rodata */
      BUILD_DIR/src/game*.o(.rodata*);
      BUILD_DIR/src/engine*.o(.rodata*);
      BUILD_DIR/src/usb*.o(.rodata*);
      BUILD_DIR/src/mb64*.o(.rodata*);
      . = ALIGN(0x10);
   }
   END_SEG(engine)
   BEGIN_NOLOAD(engine)
   {
      BUILD_DIR/src/game*.o(.*bss*);
      BUILD_DIR/src/engine*.o(.bss*);
      BUILD_DIR/src/mb64*.o(.*bss*);
      . = ALIGN(0x40);
   }
   END_NOLOAD(engine)

   . = _engineSegmentBssEnd;
   BEGIN_NOLOAD(framebuffers)
   {
      BUILD_DIR/src/buffers/framebuffers.o(.bss*);
   }
   END_NOLOAD(framebuffers)

   __mainPoolStart = .;
   __mainPoolSize  = (RAM_END - .);

   __expansionRamStart = (RAM_START + (RAM_1MB * 4));
#ifndef USE_EXT_RAM
   #ifndef PRELIMINARY
         ASSERT((. <= __expansionRamStart), "Error: RDRAM expanded into Expansion RAM, despite Expansion RAM not being defined.")
   #endif
#endif

   /* load YAY0 and level data */
   YAY0_SEG(segment2, 0x02000000)
   YAY0_SEG(mb64_buttons, 0x03000000)
#ifdef VERSION_EU
   YAY0_EU_SEG(translation_en, 0x19000000)
   YAY0_EU_SEG(translation_fr, 0x19000000)
   YAY0_EU_SEG(translation_de, 0x19000000)
#endif

   /* mario actor group */
   STANDARD_OBJECTS(group_global,  0x04000000, 0x17000000)

   STANDARD_OBJECTS(group_btcm, 0x06000000, 0x0D000000)
   STANDARD_OBJECTS(group_vanilla, 0x06000000, 0x0D000000)

   /* use segmented addressing for behaviors */
   BEGIN_SEG(behavior, 0x13000000)
   {
      KEEP(BUILD_DIR/data/behavior_data.o(.data*));
      KEEP(BUILD_DIR/data/behavior_data.o(.rodata*));
      KEEP(BUILD_DIR/data/behavior_data.o(.text*));
   }
   END_SEG(behavior)
   BEGIN_NOLOAD(behavior)
   {
      KEEP(BUILD_DIR/data/behavior_data.o(.bss*));
   }
   END_NOLOAD(behavior)


   /* 0x8016F000 21D7D0-255EC0 [386F0] */
   BEGIN_SEG(menu_seg, (RAM_END - MENU_SEG_SIZE))
   {
      KEEP(BUILD_DIR/src/menu*.o(.text*));
      _menu_segSegmentTextEnd = .;
      KEEP(BUILD_DIR/src/menu*.o(.data*));
      KEEP(BUILD_DIR/src/menu*.o(.rodata*));
      . = ALIGN(16);
   }
   END_SEG(menu_seg)
   BEGIN_NOLOAD(menu_seg)
   {
      KEEP(BUILD_DIR/src/menu*.o(.bss*));
      . = ALIGN(16);
   }
   END_NOLOAD(menu_seg)

#ifdef PRELIMINARY
      MENU_SEG_SIZE = SIZEOF(.menu_seg) + SIZEOF(.menu_seg.noload);
#else
      ASSERT((. <= (SEG_POOL_START + POOL_SIZE)), "Error: extended past pool end.")
#endif

   gMainLevels = __romPos;

   /* Menu scene (entry + splash + file select); XOR with game at 0x0E */
   BEGIN_SEG(menu, 0x0E000000)
   {
      KEEP(BUILD_DIR/data/scenes/entry.o(.data*));
      KEEP(BUILD_DIR/data/scenes/menu/script.o(.*data*));
      KEEP(BUILD_DIR/data/scenes/menu/script.o(.rodata*));
      KEEP(BUILD_DIR/data/scenes/menu/script.o(.text*));
      KEEP(BUILD_DIR/data/scenes/menu/geo.o(.data*));
      KEEP(BUILD_DIR/data/scenes/menu/geo.o(.rodata*));
      KEEP(BUILD_DIR/data/scenes/menu/geo.o(.text*));
   }
   END_SEG(menu)
   BEGIN_NOLOAD(menu)
   {
      KEEP(BUILD_DIR/data/scenes/entry.o(.bss*));
      KEEP(BUILD_DIR/data/scenes/menu/script.o(.bss*));
      KEEP(BUILD_DIR/data/scenes/menu/geo.o(.bss*));
   }
   END_NOLOAD(menu)
   BEGIN_SEG(menu_segment_7, 0x07000000)
   {
      KEEP(BUILD_DIR/data/scenes/menu/seg7.szp.o(.data*));
      . = ALIGN(0x10);
   }
   END_SEG(menu_segment_7)

   YAY0_SEG(water_skybox,       0x0A000000)
   YAY0_SEG(ccm_skybox,         0x0A000000)
   YAY0_SEG(clouds_skybox,      0x0A000000)
   YAY0_SEG(bitfs_skybox,       0x0A000000)
   YAY0_SEG(wdw_skybox,         0x0A000000)
   YAY0_SEG(cloud_floor_skybox, 0x0A000000)
   YAY0_SEG(ssl_skybox,         0x0A000000)
   YAY0_SEG(bbh_skybox,         0x0A000000)
   YAY0_SEG(bidw_skybox,        0x0A000000)
   YAY0_SEG(bits_skybox,        0x0A000000)

   // Texture bins
   YAY0_SEG(effect,   0x0B000000)

   BEGIN_SEG(game, 0x0E000000)
   {
      KEEP(BUILD_DIR/data/scenes/game/script.o(.*data*));
      KEEP(BUILD_DIR/data/scenes/game/script.o(.text*));
      KEEP(BUILD_DIR/data/scenes/game/script.o(.rodata*));
      KEEP(BUILD_DIR/data/scenes/game/geo.o(.*data*));
      KEEP(BUILD_DIR/data/scenes/game/geo.o(.text*));
      KEEP(BUILD_DIR/data/scenes/game/geo.o(.rodata*));
      KEEP(BUILD_DIR/data/scenes/scripts.o(.data*));
      KEEP(BUILD_DIR/data/scenes/scripts.o(.rodata*));
   }
   END_SEG(game)
   BEGIN_NOLOAD(game)
   {
      KEEP(BUILD_DIR/data/scenes/game/script.o(.bss*));
      KEEP(BUILD_DIR/data/scenes/game/geo.o(.bss*));
      KEEP(BUILD_DIR/data/scenes/scripts.o(.bss*));
   }
   END_NOLOAD(game)

   /* 4E9FA0-? [?] */
   BEGIN_SEG(assets, __romPos)
   {
      KEEP(BUILD_DIR/assets/mario_anim_data.o(.data*));
      KEEP(BUILD_DIR/assets/mario_anim_data.o(.rodata*));
      KEEP(BUILD_DIR/sound/sound_data.o(.data*));
   }
   END_SEG(assets)

#ifdef DEBUG_MAP_STACKTRACE
   BEGIN_SEG(mapData, (RAM_END - 0x00100000)) {
      KEEP(BUILD_DIR/asm/debug/map.o(.data*));
   }
   END_SEG(mapData)
#endif
   /* DWARF debug sections.
      Symbols in the DWARF debugging sections are relative to the beginning
      of the section so we begin them at 0.  */
   /* DWARF 1 */
   .debug          0 : { *(.debug) }
   .line           0 : { *(.line) }
   /* GNU DWARF 1 extensions */
   .debug_srcinfo  0 : { *(.debug_srcinfo) }
   .debug_sfnames  0 : { *(.debug_sfnames) }
   /* DWARF 1.1 and DWARF 2 */
   .debug_aranges  0 : { *(.debug_aranges) }
   .debug_pubnames 0 : { *(.debug_pubnames) }
   /* DWARF 2 */
   .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
   .debug_abbrev   0 : { *(.debug_abbrev) }
   .debug_line     0 : { *(.debug_line .debug_line.* .debug_line_end ) }
   .debug_frame    0 : { *(.debug_frame) }
   .debug_str      0 : { *(.debug_str) }
   .debug_loc      0 : { *(.debug_loc) }
   .debug_macinfo  0 : { *(.debug_macinfo) }
   /* SGI/MIPS DWARF 2 extensions */
   .debug_weaknames 0 : { *(.debug_weaknames) }
   .debug_funcnames 0 : { *(.debug_funcnames) }
   .debug_typenames 0 : { *(.debug_typenames) }
   .debug_varnames  0 : { *(.debug_varnames) }
   /* DWARF 3 */
   .debug_pubtypes 0 : { *(.debug_pubtypes) }
   .debug_ranges   0 : { *(.debug_ranges) }
   /* DWARF Extension.  */
   .debug_macro    0 : { *(.debug_macro) }
   .gnu.attributes 0 : { KEEP (*(.gnu.attributes)) }
   /* Discard everything not specifically mentioned above. */
   /DISCARD/ :
   {
      *(*);
   }
}
