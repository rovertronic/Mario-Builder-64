#ifndef DEBUG_BOX_H
#define DEBUG_BOX_H

#ifdef VISUAL_DEBUG

/**
 * @file debug_box.h
 * Draws debug boxes, see debug_box.c for details
 */

#include "types.h"

/**
 * The max amount of debug boxes before debug_box() just returns.
 * You can set this to something higher, but you might run out of space in the gfx pool.
 */
#define MAX_DEBUG_BOXES 512

#define DEBUG_SHAPE_BOX 0x0
#define DEBUG_SHAPE_CYLINDER 0x1

extern u8 hitboxView;
extern u8 surfaceView;
extern void debug_box_input(void);

void debug_box_color(u32 color);
void debug_box(Vec3f center, Vec3f bounds, s32 type);
void debug_box_rot(Vec3f center, Vec3f bounds, s16 yaw, s32 type);

void debug_box_pos(Vec3f pMin, Vec3f pMax, s32 type);
void debug_box_pos_rot(Vec3f pMin, Vec3f pMax, s16 yaw, s32 type);

void render_debug_boxes(void);
extern void visual_surface_loop(void);

#endif

#endif /* DEBUG_BOX_H */
