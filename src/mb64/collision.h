#pragma once

#include "mb64/gfx/tile.h"

struct MarioState;

extern TerrainData mb64_curr_coltype;
extern u16 mb64_build_collision_type;

u32 coords_in_range(s8 pos[3]);
void mb64_create_surface(TerrainData v1[3], TerrainData v2[3], TerrainData v3[3], u32 isStatic);
void mb64_create_poly(struct mb64_terrain_poly *poly, s8 pos[3], u32 rot);

void block_floor_collision(f32 x, f32 y, f32 z);
void block_ceil_collision(f32 x, f32 y, f32 z);
void block_wall_collision(f32 x, f32 y, f32 z, f32 r);
void check_poles(struct MarioState *m);
