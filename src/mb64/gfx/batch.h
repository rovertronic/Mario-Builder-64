#pragma once

#define MB64_GFX_SIZE 20000
#define MB64_VTX_SIZE 50000

#include <PR/ultratypes.h>
#include <PR/gbi.h>

extern u32 mb64_gfx_total;
extern u32 mb64_vtx_total;

extern Vtx *mb64_curr_vtx;
extern Gfx *mb64_curr_gfx;
extern u16 mb64_gfx_index;

extern u8 mb64_num_vertices_cached;

void cache_tri(u8 v1, u8 v2, u8 v3);
void check_cached_tris(void);
s32 find_duplicate_vertex(s32 vx, s32 vy, s32 vz, u8 n0, u8 n1, u8 n2, s16 u, s16 v);

void draw_dotted_line(s16 pos1[3], s16 pos2[3]);
void display_cached_tris(void);
