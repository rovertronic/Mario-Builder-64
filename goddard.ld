OUTPUT_ARCH (mips)

#define LINKER /* Removes externs from preprocessed script */
#include "segments.h"
#include "config.h"
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

SECTIONS {
      __romPos = 0;
      BEGIN_SEG(goddard_sz, 0x80345678)
      {
            KEEP(BUILD_DIR/src/menu*.o(.text));
            KEEP(BUILD_DIR/src/menu*.o(.data*));
            KEEP(BUILD_DIR/src/menu*.o(.rodata*));
      #ifdef KEEP_MARIO_HEAD
            KEEP(BUILD_DIR/libgoddard.a:*.o(.text));
            KEEP(BUILD_DIR/libgoddard.a:gd_main.o(.data*));
            KEEP(BUILD_DIR/libgoddard.a:draw_objects.o(.data*));
            KEEP(BUILD_DIR/libgoddard.a:objects.o(.data*));
            KEEP(BUILD_DIR/libgoddard.a:particles.o(.data*));
            KEEP(BUILD_DIR/libgoddard.a:dynlist_proc.o(.data*));
            KEEP(BUILD_DIR/libgoddard.a:debug_utils.o(.data*));
            KEEP(BUILD_DIR/libgoddard.a:joints.o(.data*));
            KEEP(BUILD_DIR/libgoddard.a:shape_helper.o(.data*));
            KEEP(BUILD_DIR/libgoddard.a:renderer.o(.data*));
            KEEP(BUILD_DIR/libgoddard.a:gd_main.o(.rodata*));
            KEEP(BUILD_DIR/libgoddard.a:gd_memory.o(.rodata*));
            KEEP(BUILD_DIR/libgoddard.a:draw_objects.o(.rodata*));
            KEEP(BUILD_DIR/libgoddard.a:objects.o(.rodata*));
            KEEP(BUILD_DIR/libgoddard.a:skin_movement.o(.rodata*));
            KEEP(BUILD_DIR/libgoddard.a:particles.o(.rodata*));
            KEEP(BUILD_DIR/libgoddard.a:dynlist_proc.o(.rodata*));
            KEEP(BUILD_DIR/libgoddard.a:old_menu.o(.rodata*));
            KEEP(BUILD_DIR/libgoddard.a:debug_utils.o(.rodata*));
            KEEP(BUILD_DIR/libgoddard.a:joints.o(.rodata*));
            KEEP(BUILD_DIR/libgoddard.a:skin.o(.rodata*));
            KEEP(BUILD_DIR/libgoddard.a:gd_math.o(.rodata*));
            KEEP(BUILD_DIR/libgoddard.a:shape_helper.o(.rodata*));
            KEEP(BUILD_DIR/libgoddard.a:renderer.o(.rodata*));
      #endif
            . = ALIGN(16);
            KEEP(BUILD_DIR/src/menu*.o(.bss*));
      #ifdef KEEP_MARIO_HEAD
            KEEP(BUILD_DIR/libgoddard.a:*.o(.bss*));
      #endif
            . = ALIGN(16);
      }
      END_SEG(goddard_sz)

      GODDARD_SIZE = SIZEOF(.goddard_sz);

      /DISCARD/ :
      {
            *(*);
      }
}
