#include "gfx.h"
#include "tile.h"

#include "mb64/data.h"
#include "mb64/collision.h"
#include "mb64/editor/boundary.h"
#include "mb64/editor/main.h"
#include "mb64/editor/object.h"
#include "mb64/editor/trajectory.h"
#include "mb64/menu/misc.h"
#include "mb64/menu/settings.h"

#include <PR/gbi.h>
#include "actors/maker/header.h"
#include "game/emutest.h"
#include "game/rendering_graph_node.h"
#include "engine/math_util.h"
#include "game/ingame_menu.h"

Gfx mb64_terrain_gfx[MB64_GFX_SIZE]; //gfx
Gfx *mb64_terrain_gfx_tp;
Vtx mb64_terrain_vtx[MB64_VTX_SIZE];

Gfx preview_gfx[50];
Vtx preview_vtx[100];

static void render_preview_block(u32 matid, u32 topmatid, s8 pos[3], struct mb64_terrain *terrain, u32 rot, u32 processType, u32 disableZ) {
    mb64_curr_mat_has_topside = (topmatid != matid);

    u8 matType = mb64_mat_table[matid].type;

    if (do_process(&matType, processType)) {
        set_render_mode( matType, disableZ);
        gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], mb64_mat_table[matid].gfx);
        mb64_render_vertical = mb64_mat_table[matid].vertical;
        // Important to not use matType here so that it's still opaque for screens
        if (((matType == MAT_CUTOUT) ||
            ((mb64_mat_table[matid].type < MAT_CUTOUT) && (mb64_mat_table[topmatid].type >= MAT_CUTOUT)))
            && !disableZ) {
            gSPClearGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK);
        }
        process_tile(pos, terrain, rot);
        display_cached_tris();
    }

    if (mb64_curr_mat_has_topside) {
        u8 topMatType = mb64_mat_table[topmatid].type;
        if (!do_process(&topMatType, processType)) return;
        Gfx *sidetex = get_sidetex(topmatid);
        if (sidetex != NULL) {
            mb64_use_alt_uvs = TRUE;
            mb64_render_vertical = TRUE;
            mb64_growth_render_type = 2;
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], sidetex);

            // DECAL MODE
            if (matType != MAT_TRANSPARENT) { // Render in decal mode for cutouts, opaque and screen
                set_render_mode( MAT_DECAL, disableZ);
                process_tile(pos, terrain, rot);
                display_cached_tris();
            }
            // OPAQUE MODE
            if (matType >= MAT_CUTOUT) { // Render in cutout mode for cutouts and transparent
                set_render_mode( MAT_CUTOUT, disableZ);
                process_tile(pos, terrain, rot);
                display_cached_tris();
            }

            mb64_use_alt_uvs = FALSE;
        }
        mb64_growth_render_type = 1;

        set_render_mode( topMatType, disableZ);
        gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], mb64_mat_table[topmatid].gfx);
        mb64_render_vertical = mb64_mat_table[topmatid].vertical;
        process_tile(pos, terrain, rot);
        display_cached_tris();
    }
    gSPSetGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK);
}

void generate_terrain_gfx(void) {
    s8 pos[3];
    mb64_curr_gfx = mb64_terrain_gfx;
    mb64_curr_vtx = mb64_terrain_vtx;
    mb64_gfx_index = 0;
    mb64_build_collision_type = 0;

    mb64_use_alt_uvs = FALSE;
    mb64_render_flip_normals = FALSE;
    mb64_render_vertical = FALSE;
    mb64_curr_mat_has_topside = FALSE;
    mb64_growth_render_type = 0;
    mb64_uv_offset = (mb64_lopt_theme == MB64_THEME_MC ? -32 : -16);

    retroland_filter_on();

    // Recalculate level boundary
    mb64_curr_boundary = mb64_boundary_table[mb64_lopt_boundary];
    if (mb64_curr_boundary & MB64_BOUNDARY_INNER_FLOOR) {
        if (mb64_lopt_boundary_height == 0) {
            mb64_curr_boundary &= ~MB64_BOUNDARY_CEILING;
            mb64_curr_boundary &= ~MB64_BOUNDARY_INNER_WALLS;
        }
        if (!(mb64_curr_boundary & (MB64_BOUNDARY_INNER_WALLS | MB64_BOUNDARY_OUTER_WALLS))) {
            mb64_curr_boundary |= MB64_BOUNDARY_OUTER_FLOOR;
        }
    }

    process_tiles(PROCESS_TILE_VPLEX);
    mb64_curr_poly_vert_count = 4;
    process_boundary(PROCESS_TILE_VPLEX);

    //BOTTOM PLANE
    process_boundary(PROCESS_TILE_NORMAL);

    // Special Tiles
    mb64_growth_render_type = 0;
    mb64_use_alt_uvs = TRUE;
    u32 startIndex;
    u32 endIndex;

    // Bars
    u8 connections[5];
    startIndex = mb64_tile_data_indices[BARS_TILETYPE_INDEX];
    endIndex = mb64_tile_data_indices[BARS_TILETYPE_INDEX+1];
    set_render_mode( MAT_CUTOUT, FALSE);
    gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], BARS_TEX());
    for (u32 i = startIndex; i < endIndex; i++) {
        vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);
        check_bar_connections(pos, connections);
        render_bars_side(pos, connections);
    }
    display_cached_tris();
    gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], BARS_TOPTEX());
    gSPClearGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK);
    for (u32 i = startIndex; i < endIndex; i++) {
        vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);
        check_bar_connections(pos, connections);
        render_bars_top(pos, connections);
    }
    display_cached_tris();
    gSPSetGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK);

    // Fences

    startIndex = mb64_tile_data_indices[FENCE_TILETYPE_INDEX];
    endIndex = mb64_tile_data_indices[FENCE_TILETYPE_INDEX+1];
    gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], FENCE_TEX());
    mb64_growth_render_type = 3; // fence
    for (u32 i = startIndex; i < endIndex; i++) {
        vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);
        process_tile(pos, &mb64_terrain_fence, mb64_tile_data[i].rot);
    }
    display_cached_tris();

    process_tiles(PROCESS_TILE_NORMAL);

    retroland_filter_off();
    gDPSetTextureLUT(&mb64_curr_gfx[mb64_gfx_index++], G_TT_NONE);
    gDPPipeSync(&mb64_curr_gfx[mb64_gfx_index++]);
    gDPSetRenderMode(&mb64_curr_gfx[mb64_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gSPEndDisplayList(&mb64_curr_gfx[mb64_gfx_index++]);

    mb64_terrain_gfx_tp = &mb64_curr_gfx[mb64_gfx_index];
    retroland_filter_on();

    mb64_curr_poly_vert_count = 4;
    process_boundary(PROCESS_TILE_TRANSPARENT);

    set_render_mode( MAT_TRANSPARENT, FALSE);
    gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], WATER_TEX());

    mb64_play_s16_water_level = -8224+(mb64_lopt_waterlevel*TILE_SIZE); // Update water plane height

    // Render water blocks, interiors
    mb64_render_flip_normals = TRUE;
    for (u32 i = 0; i < mb64_tile_count; i++) {
        if (mb64_tile_data[i].waterlogged) {
            if (((mb64_tile_data[i].type == TILE_TYPE_BLOCK) || (mb64_tile_data[i].type == TILE_TYPE_TROLL)) &&
                !fullblock_can_be_waterlogged(mb64_tile_data[i].mat)) continue;
            vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);
            render_water(pos);
        }
    }
    // Render water blocks, exteriors
    mb64_render_flip_normals = FALSE;
    for (u32 i = 0; i < mb64_tile_count; i++) {
        if (mb64_tile_data[i].waterlogged) {
            if (((mb64_tile_data[i].type == TILE_TYPE_BLOCK) || (mb64_tile_data[i].type == TILE_TYPE_TROLL)) &&
                !fullblock_can_be_waterlogged(mb64_tile_data[i].mat)) continue;
            vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);
            render_water(pos);
        }
    }
    display_cached_tris();

    process_tiles(PROCESS_TILE_TRANSPARENT);
    gDPPipeSync(&mb64_curr_gfx[mb64_gfx_index++]);
    gDPSetRenderMode(&mb64_curr_gfx[mb64_gfx_index++], G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
    retroland_filter_off();
    gDPSetTextureLUT(&mb64_curr_gfx[mb64_gfx_index++], G_TT_NONE);
    gSPEndDisplayList(&mb64_curr_gfx[mb64_gfx_index++]);

    mb64_trajectory_gfx = &mb64_curr_gfx[mb64_gfx_index];
    mb64_trajectory_vtx = mb64_curr_vtx;

    generate_trajectory_gfx();

    mb64_vtx_total = mb64_curr_vtx - mb64_terrain_vtx;
    mb64_gfx_total = (mb64_curr_gfx + mb64_gfx_index) - mb64_terrain_gfx;

    osViSetSpecialFeatures(OS_VI_DITHER_FILTER_OFF);
    osViSetSpecialFeatures(OS_VI_DIVOT_OFF);

    if (mb64_vtx_total >= MB64_VTX_SIZE) {
        show_error("CRITICAL WARNING: Vertex limit exceeded.");
    } else if (mb64_vtx_total >= MB64_VTX_SIZE - 30) {
        show_error("WARNING: Vertex limit is about to overflow.\nCreate any more vertices and you're cooked.");
    }
};

u8 mb64_append_frameone_bandaid_fix = FALSE; // N64-Only RCP Lockup 1 found day before release. This seems to fix it. May God be with me, Amen.
Gfx *mb64_append(s32 callContext, UNUSED struct GraphNode *node, UNUSED Mat4 mtx) {
    if (callContext == GEO_CONTEXT_RENDER) {
        if (!mb64_append_frameone_bandaid_fix) {
            mb64_append_frameone_bandaid_fix = TRUE;
            return NULL;
        }

        geo_append_display_list(mb64_terrain_gfx, LAYER_OPAQUE);
        geo_append_display_list(mb64_terrain_gfx_tp, LAYER_TRANSPARENT);

        //this extra append is for the editor tile preview
        if (mb64_mode == MB64_MODE_MAKE) {
            if (!mb64_prepare_level_screenshot) {
                geo_append_display_list(mb64_trajectory_gfx, LAYER_OPAQUE);
            }
            //generate dl
            if (mb64_place_mode != MB64_PM_TILE) {
                render_water_plane();
                return NULL;
            }
            mb64_curr_gfx = preview_gfx;
            mb64_curr_vtx = preview_vtx;
            mb64_gfx_index = 0;
            mb64_growth_render_type = 0;
            mb64_use_alt_uvs = FALSE;

            mb64_build_collision_type = 0;

            retroland_filter_on();

            if (mb64_id_selection == TILE_TYPE_WATER) {
                gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], WATER_TEX());
                gSPGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], 0, G_CULL_BACK);
                mb64_curr_poly_vert_count = 4;
                render_water(mb64_cursor_pos);
                display_cached_tris();
                retroland_filter_off();
                gDPSetTextureLUT(&mb64_curr_gfx[mb64_gfx_index++], G_TT_NONE);
                gSPEndDisplayList(&mb64_curr_gfx[mb64_gfx_index]);

                geo_append_display_list(mb64_curr_gfx, LAYER_TRANSPARENT_INTER);

                render_water_plane();
                return NULL;
            }

            struct mb64_terrain *terrain = mb64_terrain_info_list[mb64_id_selection].terrain;
            u8 mat = TILE_MATDEF(mb64_mat_selection).mat;
            u8 topmat = TILE_MATDEF(mb64_mat_selection).topmat;
            if (mb64_id_selection == TILE_TYPE_POLE) {
                terrain = &mb64_terrain_pole;
                mat = mb64_theme_table[mb64_lopt_theme].pole;
                topmat = mat;
                mb64_use_alt_uvs = TRUE;
                mb64_growth_render_type = 4; // pole
            }

            if (terrain) {
                // Handle Virtuaplex screen effect
                if (mat == MB64_MAT_VP_SCREEN || topmat == MB64_MAT_VP_SCREEN) {
                    render_preview_block(mat, topmat, mb64_cursor_pos, terrain, mb64_rot_selection, PROCESS_TILE_VPLEX, FALSE);

                    gSPEndDisplayList(&mb64_curr_gfx[mb64_gfx_index]);
                    geo_append_display_list(mb64_curr_gfx, LAYER_FORCE);

                    mb64_curr_gfx += mb64_gfx_index;
                    mb64_gfx_index = 0;
                }
                render_preview_block(mat, topmat, mb64_cursor_pos, terrain, mb64_rot_selection, PROCESS_TILE_BOTH, FALSE);

            } else if (mb64_id_selection != TILE_TYPE_CULL) {
                mb64_use_alt_uvs = TRUE;
                mb64_curr_poly_vert_count = 4;
                if (mb64_id_selection == TILE_TYPE_FENCE) {
                    gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], FENCE_TEX());
                    set_render_mode( MAT_CUTOUT, FALSE);
                    mb64_growth_render_type = 3; // fence
                    process_tile(mb64_cursor_pos, &mb64_terrain_fence, mb64_rot_selection);
                } else if (mb64_id_selection == TILE_TYPE_BARS) {
                    set_render_mode( MAT_CUTOUT, FALSE);
                    gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], BARS_TEX());
                    u8 connections[5];
                    check_bar_connections(mb64_cursor_pos, connections);
                    render_bars_side(mb64_cursor_pos, connections);
                    display_cached_tris();
                    gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], BARS_TOPTEX());
                    gSPClearGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK);
                    render_bars_top(mb64_cursor_pos, connections);
                }
                display_cached_tris();
                gSPSetGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK);
                mb64_use_alt_uvs = FALSE;
            }

            gDPPipeSync(&mb64_curr_gfx[mb64_gfx_index++]);
            gDPSetRenderMode(&mb64_curr_gfx[mb64_gfx_index++], G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2);
            gDPSetTextureLUT(&mb64_curr_gfx[mb64_gfx_index++], G_TT_NONE);
            retroland_filter_off();
            gSPEndDisplayList(&mb64_curr_gfx[mb64_gfx_index]);

            geo_append_display_list(mb64_curr_gfx, LAYER_TRANSPARENT_INTER);
        }

        render_water_plane();
    }
    return NULL;
}

static void prepare_block_draw(f32 xpos, f32 ypos) {
    Mat4 mtx1, mtx2;
    Vec3f pos;
    Vec3s rot;

    Mtx *perspMtx = alloc_display_list(sizeof(*perspMtx));
    guFrustum(perspMtx, -SCREEN_WIDTH/2 + xpos, SCREEN_WIDTH/2 + xpos, -SCREEN_HEIGHT/2 - ypos, SCREEN_HEIGHT/2 - ypos, 128, 4000, 0.005f);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(perspMtx), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);

    Lights1* curLight = (Lights1*)alloc_display_list(sizeof(Lights1));
    extern Lights1 *defaultLight;
    bcopy(&defaultLight, curLight, sizeof(Lights1));

    curLight->l->l.dir[0] = (s8)(globalLightDirection[0]);
    curLight->l->l.dir[1] = (s8)(globalLightDirection[1]);
    curLight->l->l.dir[2] = (s8)(globalLightDirection[2]);

    gSPSetLights1(gDisplayListHead++, (*curLight));

    Mtx *mtx = alloc_display_list(sizeof(*mtx));
    vec3_set(pos, 0, 0, -1500);
    vec3_set(rot, 0, (s16)(0x200*gGlobalTimer), 0);
    mtxf_rotate_zxy_and_translate(mtx1, gVec3fZero, rot);
    vec3_set(rot, 0x1800, 0, 0);
    mtxf_rotate_zxy_and_translate(mtx2, pos, rot);
    mtxf_mul(mtx1, mtx1, mtx2);
    mtxf_to_mtx(mtx, mtx1);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_PUSH);
    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);

    mb64_build_collision_type = 0;
    mb64_growth_render_type = 0;
    mb64_render_culling_off = TRUE;
    mb64_curr_mat_has_topside = FALSE;
    mb64_use_alt_uvs = FALSE;
    mb64_render_flip_normals = FALSE;
}

static void finish_block_draw() {
    mb64_render_culling_off = FALSE;

    gSPDisplayList(gDisplayListHead++, mb64_curr_gfx);
    
    mb64_curr_gfx += mb64_gfx_index;
    mb64_gfx_index = 0;

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    create_dl_ortho_matrix();
}

void custom_theme_draw_block(f32 xpos, f32 ypos, s32 index) {
    xpos = -xpos;
    prepare_block_draw(xpos, ypos);

    s8 pos[3];
    vec3_set(pos,32,32,32);

    Vtx *startVtx = mb64_curr_vtx;

    if (index < NUM_MATERIALS_PER_THEME) {
        u8 renderedMat = mb64_curr_custom_theme.mats[index];
        u8 renderedTopmat = mb64_curr_custom_theme.topmats[index];
        if (!mb64_curr_custom_theme.topmatsEnabled[index]) renderedTopmat = renderedMat;

        render_preview_block(renderedMat, renderedTopmat, pos, &mb64_terrain_fullblock, 0, PROCESS_TILE_BOTH, TRUE);
    } else {
        mb64_use_alt_uvs = TRUE;
        mb64_curr_poly_vert_count = 4;
        if (index == 10) { // Poles
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], mb64_mat_table[mb64_curr_custom_theme.pole].gfx);
            set_render_mode( mb64_mat_table[mb64_curr_custom_theme.pole].type, TRUE);
            mb64_growth_render_type = 4; // poles
            process_tile(pos, &mb64_terrain_pole, 0);
        } else if (index == 11) { // Fence
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], mb64_fence_texs[mb64_curr_custom_theme.fence]);
            set_render_mode( MAT_CUTOUT, TRUE);
            mb64_growth_render_type = 3; // fence
            process_tile(pos, &mb64_terrain_fence, 0);
        } else if (index == 12) { // Iron Mesh
            set_render_mode( MAT_CUTOUT, TRUE);
            u8 connections[5] = {1,0,1,0,1};
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], mb64_bar_texs[mb64_curr_custom_theme.bars][1]);
            render_bars_top(pos, connections);
            display_cached_tris();
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], mb64_bar_texs[mb64_curr_custom_theme.bars][0]);
            render_bars_side(pos, connections);
        } else if (index == 13) { // Water
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], mb64_water_texs[mb64_curr_custom_theme.water]);
            set_render_mode( MAT_TRANSPARENT, TRUE);
            render_water(pos);
        }
        display_cached_tris();
        mb64_use_alt_uvs = FALSE;
    }

    gDPPipeSync(&mb64_curr_gfx[mb64_gfx_index++]);
    gDPSetRenderMode(&mb64_curr_gfx[mb64_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gDPSetTextureLUT(&mb64_curr_gfx[mb64_gfx_index++], G_TT_NONE);
    gSPEndDisplayList(&mb64_curr_gfx[mb64_gfx_index++]);

    for (Vtx *vtx = startVtx; vtx < mb64_curr_vtx; vtx++) {
        vtx->v.ob[0] -= TILE_SIZE/2;
        if (index != 11) vtx->v.ob[2] -= TILE_SIZE/2;
    }

    finish_block_draw();
}
