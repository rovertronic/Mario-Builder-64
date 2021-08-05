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

BEGIN_NOLOAD(goddard_sz)
   {
      BUILD_DIR/src/menu*.o(.text);
      BUILD_DIR/src/menu*.o(.data*);
      BUILD_DIR/src/menu*.o(.rodata*);
#ifdef KEEP_MARIO_HEAD
      BUILD_DIR/libgoddard.a:*.o(.text);
      /* goddard subsystem data */
      BUILD_DIR/libgoddard.a:gd_main.o(.data*);
      BUILD_DIR/libgoddard.a:draw_objects.o(.data*);
      BUILD_DIR/libgoddard.a:objects.o(.data*);
      BUILD_DIR/libgoddard.a:particles.o(.data*);
      BUILD_DIR/libgoddard.a:dynlist_proc.o(.data*);
      BUILD_DIR/libgoddard.a:debug_utils.o(.data*);
      BUILD_DIR/libgoddard.a:joints.o(.data*);
      BUILD_DIR/libgoddard.a:shape_helper.o(.data*);
      BUILD_DIR/libgoddard.a:renderer.o(.data*);
      /* goddard subsystem rodata */
      BUILD_DIR/libgoddard.a:gd_main.o(.rodata*);
      BUILD_DIR/libgoddard.a:gd_memory.o(.rodata*);
      BUILD_DIR/libgoddard.a:draw_objects.o(.rodata*);
      BUILD_DIR/libgoddard.a:objects.o(.rodata*);
      BUILD_DIR/libgoddard.a:skin_movement.o(.rodata*);
      BUILD_DIR/libgoddard.a:particles.o(.rodata*);
      BUILD_DIR/libgoddard.a:dynlist_proc.o(.rodata*);
      BUILD_DIR/libgoddard.a:old_menu.o(.rodata*);
      BUILD_DIR/libgoddard.a:debug_utils.o(.rodata*);
      BUILD_DIR/libgoddard.a:joints.o(.rodata*);
      BUILD_DIR/libgoddard.a:skin.o(.rodata*);
      BUILD_DIR/libgoddard.a:gd_math.o(.rodata*);
      BUILD_DIR/libgoddard.a:shape_helper.o(.rodata*);
      BUILD_DIR/libgoddard.a:renderer.o(.rodata*);
#endif
      . = ALIGN(16);
      BUILD_DIR/src/menu*.o(.bss*);
#ifdef KEEP_MARIO_HEAD
      BUILD_DIR/libgoddard.a:*.o(.bss*);
#endif
      . = ALIGN(16);
   }
END_NOLOAD(goddard_sz)

GODDARD_SIZE = SIZEOF(.goddard_sz.noload);
