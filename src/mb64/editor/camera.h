#pragma once

#include "types.h"

extern Vec3f mb64_camera_pos;
extern Vec3f mb64_camera_pos_prev;
extern Vec3f mb64_camera_foc;
extern f32 mb64_camera_fov;
extern s16 mb64_camera_angle;
extern u8 mb64_camera_rot_offset;
extern s8 mb64_camera_zoom_index;
extern f32 mb64_camera_zoom_table[][2];
extern f32 mb64_current_camera_zoom[2];
extern s16 mb64_freecam_pitch;
extern s16 mb64_freecam_yaw;
extern u8 mb64_freecam_snap;
extern u8 mb64_freecam_snap_timer;

s32 snap_cursor(void);
void wrap_cursor(void);
u32 main_cursor_logic(void);
void freecam_camera_init(void);
void freecam_return(void);
void freecam_camera_main(void);
