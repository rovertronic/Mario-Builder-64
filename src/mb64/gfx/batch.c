#include "gfx.h"

#include <PR/gbi.h>
#include "engine/math_util.h"
#include "game/geo_misc.h"

u32 mb64_gfx_total = 0;
u32 mb64_vtx_total = 0;

Vtx *mb64_curr_vtx;
Gfx *mb64_curr_gfx;
u16 mb64_gfx_index;

u8 mb64_num_vertices_cached = 0;
static u8 mb64_num_tris_cached = 0;
static u8 mb64_cached_tris[64][3];

void cache_tri(u8 v1, u8 v2, u8 v3) {
    mb64_cached_tris[mb64_num_tris_cached][0] = v1;
    mb64_cached_tris[mb64_num_tris_cached][1] = v2;
    mb64_cached_tris[mb64_num_tris_cached][2] = v3;
    mb64_num_tris_cached++;
}

void display_cached_tris(void) {
    if (mb64_num_vertices_cached == 0) return;
    gSPVertex(&mb64_curr_gfx[mb64_gfx_index++], mb64_curr_vtx, mb64_num_vertices_cached, 0);
    u32 i = 0;
    while (i < mb64_num_tris_cached) {
        // odd number of triangles and last one left
        if ((mb64_num_tris_cached - i) == 1) {
            gSP1Triangle(&mb64_curr_gfx[mb64_gfx_index++], mb64_cached_tris[i][0], mb64_cached_tris[i][1], mb64_cached_tris[i][2], 0);
            i++;
        } else {
            gSP2Triangles(&mb64_curr_gfx[mb64_gfx_index++], mb64_cached_tris[i][0], mb64_cached_tris[i][1], mb64_cached_tris[i][2], 0, mb64_cached_tris[i+1][0], mb64_cached_tris[i+1][1], mb64_cached_tris[i+1][2], 0);
            i+=2;
        }
    }
    mb64_curr_vtx += mb64_num_vertices_cached;
    mb64_num_tris_cached = 0;
    mb64_num_vertices_cached = 0;
}

void check_cached_tris(void) {
    if (mb64_num_vertices_cached > 28 || mb64_num_tris_cached > 62) {
        display_cached_tris();
    }
}

void draw_dotted_line(s16 pos1[3], s16 pos2[3]) {
    f32 dx2 = sqr(pos2[0] - pos1[0]);
    f32 dy2 = sqr(pos2[1] - pos1[1]);
    f32 dz2 = sqr(pos2[2] - pos1[2]);
    f32 length = sqrtf(dx2 + dy2 + dz2);

    s16 yaw = atan2s(pos2[2] - pos1[2], pos2[0] - pos1[0]);
    s16 pitch = atan2s(sqrtf(dx2 + dz2), pos2[1] - pos1[1]);
    
    f32 sy = 10*sins(yaw);
    f32 cy = 10*coss(yaw);
    f32 sp = 10*sins(pitch);
    f32 cp = 10*coss(pitch);
    f32 spsy = sp*sins(yaw);
    f32 spcy = sp*coss(yaw);

    make_vertex(mb64_curr_vtx, mb64_num_vertices_cached,     pos1[0] + cy, pos1[1], pos1[2] - sy, 0, 0, 0, 0, 0, 0xFF);
    make_vertex(mb64_curr_vtx, mb64_num_vertices_cached + 1, pos1[0] - cy, pos1[1], pos1[2] + sy, 0, 0, 0, 0, 0, 0xFF);
    make_vertex(mb64_curr_vtx, mb64_num_vertices_cached + 2, pos2[0] + cy, pos2[1], pos2[2] - sy, 0, length, 0, 0, 0, 0xFF);
    make_vertex(mb64_curr_vtx, mb64_num_vertices_cached + 3, pos2[0] - cy, pos2[1], pos2[2] + sy, 0, length, 0, 0, 0, 0xFF);

    cache_tri(mb64_num_vertices_cached, mb64_num_vertices_cached+1, mb64_num_vertices_cached+2);
    cache_tri(mb64_num_vertices_cached+1, mb64_num_vertices_cached+3, mb64_num_vertices_cached+2);
    mb64_num_vertices_cached += 4;
    check_cached_tris();

    make_vertex(mb64_curr_vtx, mb64_num_vertices_cached,     pos1[0] + spsy, pos1[1] - cp, pos1[2] + spcy, 0, 0, 0, 0, 0, 0xFF);
    make_vertex(mb64_curr_vtx, mb64_num_vertices_cached + 1, pos1[0] - spsy, pos1[1] + cp, pos1[2] - spcy, 0, 0, 0, 0, 0, 0xFF);
    make_vertex(mb64_curr_vtx, mb64_num_vertices_cached + 2, pos2[0] + spsy, pos2[1] - cp, pos2[2] + spcy, 0, length, 0, 0, 0, 0xFF);
    make_vertex(mb64_curr_vtx, mb64_num_vertices_cached + 3, pos2[0] - spsy, pos2[1] + cp, pos2[2] - spcy, 0, length, 0, 0, 0, 0xFF);

    cache_tri(mb64_num_vertices_cached, mb64_num_vertices_cached+1, mb64_num_vertices_cached+2);
    cache_tri(mb64_num_vertices_cached+1, mb64_num_vertices_cached+3, mb64_num_vertices_cached+2);
    mb64_num_vertices_cached += 4;
    check_cached_tris();
}

s32 find_duplicate_vertex(s32 vx, s32 vy, s32 vz, u8 n0, u8 n1, u8 n2, s16 u, s16 v) {
    for (int i = 0; i < mb64_num_vertices_cached; i++) {
        if (mb64_curr_vtx[i].v.ob[0] == vx && mb64_curr_vtx[i].v.ob[1] == vy && mb64_curr_vtx[i].v.ob[2] == vz) {
            if (mb64_curr_vtx[i].v.tc[0] == u && mb64_curr_vtx[i].v.tc[1] == v) {
                if (mb64_curr_vtx[i].v.cn[0] == n0 && mb64_curr_vtx[i].v.cn[1] == n1 && mb64_curr_vtx[i].v.cn[2] == n2) {
                    return i;
                }
            }
        }
    }
    return -1;
}
