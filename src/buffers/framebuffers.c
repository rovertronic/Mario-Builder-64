#include <ultra64.h>

#include "config.h"

// 0x70800 bytes
__attribute__((aligned (64))) u16 gFrameBuffers[3][SCREEN_WIDTH * SCREEN_HEIGHT];
