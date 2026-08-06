#pragma once

#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include "types.h"

#define MB64_GFX_SIZE 20000
#define MB64_VTX_SIZE 50000

void generate_terrain_gfx(void);
Gfx *mb64_append(s32 callContext, UNUSED struct GraphNode *node, UNUSED Mat4 mtx);
void custom_theme_draw_block(f32 xpos, f32 ypos, s32 index);

extern u8 mb64_append_frameone_bandaid_fix;

extern u32 mb64_gfx_total;
extern u32 mb64_vtx_total;

extern Gfx mb64_terrain_gfx[MB64_GFX_SIZE];
extern Gfx *mb64_terrain_gfx_opa;
extern Gfx *mb64_terrain_gfx_tp;

extern Vtx *mb64_curr_vtx;
extern Gfx *mb64_curr_gfx;
extern u16 mb64_gfx_index;

extern u8 mb64_num_vertices_cached;

void cache_tri(u8 v1, u8 v2, u8 v3);
void check_cached_tris(void);
s32 find_duplicate_vertex(s32 vx, s32 vy, s32 vz, u8 n0, u8 n1, u8 n2, s16 u, s16 v);

void draw_dotted_line(s16 pos1[3], s16 pos2[3]);
void display_cached_tris(void);
