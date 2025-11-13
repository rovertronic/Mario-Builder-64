#pragma once

extern TerrainData mb64_curr_coltype;
extern u16 mb64_build_collision_type;

extern s32 mb64_min_coord;
extern s32 mb64_max_coord;

void block_floor_collision(f32 x, f32 y, f32 z);
void block_ceil_collision(f32 x, f32 y, f32 z);
void block_wall_collision(f32 x, f32 y, f32 z, f32 r);
