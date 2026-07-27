#include "boundary.h"
#include "mb64/collision.h"
#include "main.h"

#include <PR/gbi.h>
#include "behavior_data.h"
#include "game/object_list_processor.h"
#include "game/object_helpers.h"
#include "actors/maker/header.h"
#include "engine/surface_load.h"
#include "engine/math_util.h"
#include "game/rendering_graph_node.h"

// Takes a bottom and top in number of blocks
void render_boundary(struct mb64_boundary_quad *quadList, u32 count, s16 yBottom, s16 yTop, u32 fade) {
    for (u32 i = 0; i < count; i++) {
        render_boundary_quad(&quadList[i], yBottom * TILE_SIZE, yTop - yBottom, fade);
    }
    display_cached_tris();
}

// Takes a height in SM64 units, no verticality
void render_boundary_precise(struct mb64_boundary_quad *quadList, u32 count, s16 yBottom, u32 fade) {
    for (u32 i = 0; i < count; i++) {
        render_boundary_quad(&quadList[i], yBottom, 0, fade);
    }
    display_cached_tris();
}

struct mb64_boundary_quad floor_boundary[] = {
    {{{32, 0, 32}, {32, 0, 0}, {0, 0, 32}, {0, 0, 0}}, {-16, 16}, {-16, 16}, FALSE, FALSE, FALSE},
    {{{0, 0, 32}, {0, 0, 0}, {-32, 0, 32}, {-32, 0, 0}}, {-16, 16}, {-16, 16}, FALSE, FALSE, FALSE},
    {{{32, 0, 0}, {32, 0, -32}, {0, 0, 0}, {0, 0, -32}}, {-16, 16}, {-16, 16}, FALSE, FALSE, FALSE},
    {{{0, 0, 0}, {0, 0, -32}, {-32, 0, 0}, {-32, 0, -32}}, {-16, 16}, {-16, 16}, FALSE, FALSE, FALSE},
};

struct mb64_boundary_quad floor_edge_boundary[] = {
    {{{48, 0, 32}, {48, 0, 0}, {32, 0, 32}, {32, 0, 0}}, {-16, 16}, {-8, 8}, FALSE, FALSE, FALSE},
    {{{48, 0, 32}, {32, 0, 32}, {48, 0, 48}, {32, 0, 48}}, {-8, 8}, {8, -8}, FALSE, FALSE, TRUE},
    {{{32, 0, 48}, {32, 0, 32}, {0, 0, 48}, {0, 0, 32}}, {-8, 8}, {-16, 16}, FALSE, FALSE, FALSE},

    {{{-32, 0, 32}, {-32, 0, 0}, {-48, 0, 32}, {-48, 0, 0}}, {-16, 16}, {-8, 8}, FALSE, FALSE, FALSE},
    {{{-32, 0, 48}, {-32, 0, 32}, {-48, 0, 48}, {-48, 0, 32}}, {-8, 8}, {-8, 8}, FALSE, FALSE, FALSE},
    {{{0, 0, 48}, {0, 0, 32}, {-32, 0, 48}, {-32, 0, 32}}, {-8, 8}, {-16, 16}, FALSE, FALSE, FALSE},

    {{{48, 0, 0}, {48, 0, -32}, {32, 0, 0}, {32, 0, -32}}, {-16, 16}, {-8, 8}, FALSE, FALSE, FALSE},
    {{{48, 0, -32}, {48, 0, -48}, {32, 0, -32}, {32, 0, -48}}, {-8, 8}, {-8, 8}, FALSE, FALSE, FALSE},
    {{{32, 0, -32}, {32, 0, -48}, {0, 0, -32}, {0, 0, -48}}, {-8, 8}, {-16, 16}, FALSE, FALSE, FALSE},

    {{{-32, 0, 0}, {-32, 0, -32}, {-48, 0, 0}, {-48, 0, -32}}, {-16, 16}, {-8, 8}, FALSE, FALSE, FALSE},
    {{{-32, 0, -48}, {-48, 0, -48}, {-32, 0, -32}, {-48, 0, -32}}, {-8, 8}, {8, -8}, FALSE, FALSE, TRUE},
    {{{0, 0, -32}, {0, 0, -48}, {-32, 0, -32}, {-32, 0, -48}}, {-8, 8}, {-16, 16}, FALSE, FALSE, FALSE},
};

struct mb64_boundary_quad wall_boundary[] = {
    {{{32, 1, 0}, {32, 1, -32}, {32, 0, 0}, {32, 0, -32}}, {16, -16}, {-8, 8}, FALSE, TRUE, FALSE},
    {{{32, 1, 32}, {32, 1, 0}, {32, 0, 32}, {32, 0, 0}}, {16, -16}, {-8, 8}, FALSE, TRUE, FALSE},

    {{{0, 1, 32}, {32, 1, 32}, {0, 0, 32}, {32, 0, 32}}, {16, -16}, {-8, 8}, FALSE, TRUE, FALSE},
    {{{-32, 1, 32}, {0, 1, 32}, {-32, 0, 32}, {0, 0, 32}}, {16, -16}, {-8, 8}, FALSE, TRUE, FALSE},

    {{{-32, 1, 0}, {-32, 1, 32}, {-32, 0, 0}, {-32, 0, 32}}, {16, -16}, {-8, 8}, FALSE, TRUE, FALSE},
    {{{-32, 1, -32}, {-32, 1, 0}, {-32, 0, -32}, {-32, 0, 0}}, {16, -16}, {-8, 8}, FALSE, TRUE, FALSE},

    {{{0, 1, -32}, {-32, 1, -32}, {0, 0, -32}, {-32, 0, -32}}, {16, -16}, {-8, 8}, FALSE, TRUE, FALSE},
    {{{32, 1, -32}, {0, 1, -32}, {32, 0, -32}, {0, 0, -32}}, {16, -16}, {-8, 8}, FALSE, TRUE, FALSE},
};

void render_boundary_decal_edge(Gfx *sidetex, s32 yBottom, u32 sideMatType) {
    if (sideMatType != MAT_TRANSPARENT) {
        set_render_mode( MAT_DECAL, FALSE);
        gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], sidetex);
        render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), yBottom, yBottom+1, 0);
    }
    if (sideMatType >= MAT_CUTOUT) {
        set_render_mode( MAT_CUTOUT, FALSE);
        gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], sidetex);
        render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), yBottom, yBottom+1, 0);
    }
}

void generate_boundary_quad_collision(struct mb64_boundary_quad *quadList, u32 count, s16 yBottom, s16 yTop, s16 size, u32 reverse) {
    TerrainData newVtxs[4][3];
    s16 yHeight = yTop - yBottom;
    for (u32 i = 0; i < count; i++) {
        for (u32 j = 0; j < 4; j++) {
            newVtxs[j][0] = quadList[i].vtx[j][0]*size*4;
            newVtxs[j][1] = (quadList[i].vtx[j][1]*yHeight + yBottom)*TILE_SIZE;
            newVtxs[j][2] = quadList[i].vtx[j][2]*size*4;
        }
        if (reverse) {
            mb64_create_surface(newVtxs[0], newVtxs[2], newVtxs[1], TRUE);
            mb64_create_surface(newVtxs[1], newVtxs[2], newVtxs[3], TRUE);
        } else {
            mb64_create_surface(newVtxs[0], newVtxs[1], newVtxs[2], TRUE);
            mb64_create_surface(newVtxs[1], newVtxs[3], newVtxs[2], TRUE);
        }
    }
}

void generate_boundary_collision(void) {
    *gSurfaceNodesAllocated = 0;
    *gSurfacesAllocated = 0;
    
    bzero(gStaticSurfacePartition, sizeof(gStaticSurfacePartition));

    mb64_curr_poly_vert_count = 4;

    u32 deathsize = ((mb64_curr_boundary & MB64_BOUNDARY_OUTER_FLOOR) || (mb64_curr_boundary & MB64_BOUNDARY_CEILING))? mb64_grid_size : (mb64_grid_size + 16);
    mb64_curr_coltype = SURFACE_DEATH_PLANE;
    generate_boundary_quad_collision(floor_boundary, ARRAY_COUNT(floor_boundary), -40, -40, deathsize, FALSE);

    if (mb64_curr_boundary & MB64_BOUNDARY_INNER_FLOOR) {
        mb64_curr_coltype = TOPMAT(mb64_lopt_boundary_mat).col;
        generate_boundary_quad_collision(floor_boundary, ARRAY_COUNT(floor_boundary), -32, -32, mb64_grid_size, FALSE);
    }
    mb64_curr_coltype = MATERIAL(mb64_lopt_boundary_mat).col;
    if (MATERIAL(mb64_lopt_boundary_mat).type == MAT_TRANSPARENT) {
        mb64_curr_coltype = SURFACE_DEFAULT;
    }
    if (mb64_curr_boundary & MB64_BOUNDARY_INNER_WALLS) {
        s32 bottomY = (mb64_curr_boundary & MB64_BOUNDARY_INNER_FLOOR) ? -32 : -40;
        s32 topY = mb64_lopt_boundary_height-32;
        generate_boundary_quad_collision(wall_boundary, ARRAY_COUNT(wall_boundary), bottomY, topY, mb64_grid_size, FALSE);
    } else if (mb64_curr_boundary & MB64_BOUNDARY_OUTER_WALLS) {
        generate_boundary_quad_collision(wall_boundary, ARRAY_COUNT(wall_boundary), -42, -32, mb64_grid_size, TRUE);
    }
    if (mb64_curr_boundary & MB64_BOUNDARY_CEILING) {
        generate_boundary_quad_collision(floor_boundary, ARRAY_COUNT(floor_boundary), mb64_lopt_boundary_height-32, mb64_lopt_boundary_height-32, mb64_grid_size, TRUE);
    }

    gNumStaticSurfaceNodes = *gSurfaceNodesAllocated;
    gNumStaticSurfaces = *gSurfacesAllocated;
}

void process_boundary(u32 processRenderMode) {
    u8 planeMat = mb64_lopt_boundary_mat;
    struct mb64_material *mat, *sidemat;
    mat = &TOPMAT(planeMat);
    sidemat = &MATERIAL(planeMat);

    // Outer walls (Plateau)
    if (mb64_curr_boundary & MB64_BOUNDARY_OUTER_WALLS) {
        u8 sidematType = sidemat->type;
        u8 showBackface = ((mat->type >= MAT_CUTOUT) && (sidemat->type <= MAT_CUTOUT)) || (sidemat->type == MAT_CUTOUT);
        mb64_render_flip_normals = TRUE;

        if (do_process(&sidematType, processRenderMode)) {
            set_render_mode( sidematType, FALSE);
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], sidemat->gfx);
            if (showBackface) {
                mb64_render_flip_normals = FALSE;
                render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), -33, -32, 0);
                mb64_render_flip_normals = TRUE;
            }
            render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), -33, -32, 0);

            Gfx *sidetex = get_sidetex(TILE_MATDEF(planeMat).topmat);
            if (sidetex && HAS_TOPMAT(planeMat)) {
                render_boundary_decal_edge(sidetex, -33, sidematType);
            }
        }
        // Fade at bottom
        gSPSetGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK);
        if (processRenderMode == PROCESS_TILE_TRANSPARENT) {
            gDPPipeSync(&mb64_curr_gfx[mb64_gfx_index++]);
            gDPSetRenderMode(&mb64_curr_gfx[mb64_gfx_index++], G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], sidemat->gfx);
            if (showBackface) {
                mb64_render_flip_normals = FALSE;
                render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), -42, -33, 1);
                mb64_render_flip_normals = TRUE;
            }
            render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), -42, -33, 1);
        }
        mb64_render_flip_normals = FALSE;
    }

    // Main floor
    if (mb64_curr_boundary & MB64_BOUNDARY_INNER_FLOOR) {
        u8 matType = mat->type;
        if (do_process(&matType, processRenderMode)) {
            set_render_mode( matType, FALSE);
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], mat->gfx);
            render_boundary(floor_boundary, ARRAY_COUNT(floor_boundary), -32, -32, 0);
        }
    }

    // Inner walls
    if ((mb64_curr_boundary & MB64_BOUNDARY_INNER_WALLS)) {
        u8 sidematType = sidemat->type;
        u8 showBackface = (sidemat->type == MAT_CUTOUT);
        u32 renderWalls = TRUE; // Whether to render main solid walls
        u32 renderFade = FALSE; // Whether to render fade at bottom
        s32 bottomY = -32;
        s32 topY = mb64_lopt_boundary_height-32;
        if (showBackface) {
            gSPClearGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK);
        }
        
        if (!(mb64_curr_boundary & MB64_BOUNDARY_INNER_FLOOR)) {
            renderFade = TRUE;
            bottomY -= 1; // Make sure decal has a solid face to print on
        } else {
            renderWalls = (mb64_lopt_boundary_height > 0);
        }

        Gfx *sidetex = get_sidetex(TILE_MATDEF(planeMat).topmat);
        u32 renderTopDecal = sidetex && HAS_TOPMAT(planeMat) && !(mb64_curr_boundary & MB64_BOUNDARY_CEILING);
        if (renderTopDecal) topY -= 1;

        if (renderWalls && do_process(&sidematType, processRenderMode)) {
            set_render_mode( sidematType, FALSE);
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], sidemat->gfx);
            if (topY > bottomY + 32) {
                render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), bottomY, bottomY + 32, 0);
                render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), bottomY + 32, topY, 0);
            } else {
                render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), bottomY, topY, 0);
            }

            if (renderTopDecal) {
                // Render rim of regular material before decal
                render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), topY, topY + 1, 0);
                render_boundary_decal_edge(sidetex, topY, sidematType);
            }
        }
        gSPSetGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK);
        // Fade if no floor
        if (renderFade) {
            // Black floor to block out skybox
            if ((processRenderMode == PROCESS_TILE_NORMAL) && (mb64_lopt_bg != 4) && (mb64_lopt_bg != 9)) {
                gDPPipeSync(&mb64_curr_gfx[mb64_gfx_index++]);
                gDPSetRenderMode(&mb64_curr_gfx[mb64_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
                gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], &mat_maker_MakerBlack);
                render_boundary(floor_boundary, ARRAY_COUNT(floor_boundary), -40, -40, 0);
            } else if (processRenderMode == PROCESS_TILE_TRANSPARENT) {
                gDPPipeSync(&mb64_curr_gfx[mb64_gfx_index++]);
                gDPSetRenderMode(&mb64_curr_gfx[mb64_gfx_index++], G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
repeatBackface:
                gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], sidemat->gfx);
                render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), -40, bottomY, 0);
                gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], &mat_maker_MakerBlack);
                render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), -40, bottomY, 2);
                if (showBackface) {
                    mb64_render_flip_normals = TRUE;
                    showBackface = FALSE;
                    goto repeatBackface; // im such an awesome coder
                }
                mb64_render_flip_normals = FALSE;
            }
        }
    }

    // Outer floor
    if (mb64_curr_boundary & MB64_BOUNDARY_OUTER_FLOOR) {
        s32 y = -32;
        if (mb64_curr_boundary & MB64_BOUNDARY_INNER_WALLS) {
            y = mb64_lopt_boundary_height-32;
        }
        u32 topMatOpaque = (mat->type < MAT_CUTOUT);
        if (topMatOpaque && (processRenderMode == PROCESS_TILE_VPLEX)) {
            gDPPipeSync(&mb64_curr_gfx[mb64_gfx_index++]);
            gDPSetRenderMode(&mb64_curr_gfx[mb64_gfx_index++], G_RM_VPLEX_SCREEN, G_RM_VPLEX_SCREEN2);
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], mat->gfx);
            render_boundary(floor_edge_boundary, ARRAY_COUNT(floor_edge_boundary), y, y, 0);
        }

        if (processRenderMode == PROCESS_TILE_TRANSPARENT) {
            if (topMatOpaque) {
                gDPPipeSync(&mb64_curr_gfx[mb64_gfx_index++]);
                gDPSetRenderMode(&mb64_curr_gfx[mb64_gfx_index++], G_RM_AA_ZB_XLU_DECAL, G_RM_AA_ZB_XLU_DECAL2);
            } else {
                gDPPipeSync(&mb64_curr_gfx[mb64_gfx_index++]);
                gDPSetRenderMode(&mb64_curr_gfx[mb64_gfx_index++], G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
            }
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], mat->gfx);
            render_boundary(floor_edge_boundary, ARRAY_COUNT(floor_edge_boundary), y, y, 0);
        }
    }

    // Ceiling
    if (mb64_curr_boundary & MB64_BOUNDARY_CEILING) {
        u8 sidematType = sidemat->type;
        u8 showBackface = (sidemat->type == MAT_CUTOUT);
        if (showBackface) {
            gSPClearGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK);
        }
        s32 y = mb64_lopt_boundary_height-32;
        if (do_process(&sidematType, processRenderMode)) {
            mb64_render_flip_normals = TRUE;
            set_render_mode( sidematType, FALSE);
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], sidemat->gfx);
            render_boundary(floor_boundary, ARRAY_COUNT(floor_boundary), y, y, 0);
            mb64_render_flip_normals = FALSE;
        }
        gSPSetGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK);
    }
}

Gfx water_gfx[50];
Vtx water_vtx[100];

void render_water_plane(void) {
    if (mb64_lopt_waterlevel != 0) {
        mb64_curr_vtx = water_vtx;
        mb64_curr_gfx = water_gfx;
        mb64_gfx_index = 0;

        retroland_filter_on();
        set_render_mode( MAT_TRANSPARENT, FALSE);
        gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], WATER_TEX());
        gSPClearGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK);
        render_boundary_precise(floor_boundary, ARRAY_COUNT(floor_boundary), mb64_play_s16_water_level, 0);
        render_boundary_precise(floor_edge_boundary, ARRAY_COUNT(floor_edge_boundary), mb64_play_s16_water_level, 0);
        gSPSetGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK);
        gDPPipeSync(&mb64_curr_gfx[mb64_gfx_index++]);
        gDPSetRenderMode(&mb64_curr_gfx[mb64_gfx_index++], G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2);
        gDPSetTextureLUT(&mb64_curr_gfx[mb64_gfx_index++], G_TT_NONE);
        retroland_filter_off();
        gSPEndDisplayList(&mb64_curr_gfx[mb64_gfx_index]);

        geo_append_display_list(water_gfx, LAYER_TRANSPARENT);
    }
}

static struct Object *mb64_boundary_object[6];

void init_boundary_wall_objects(struct Object *parent) {
    for (u8 i = 0; i < 6; i++) {
        mb64_boundary_object[i] = spawn_object(parent, MODEL_MAKER_BOUNDARY, bhvStaticObject);
    }
    mb64_boundary_object[2]->oFaceAngleRoll = -0x4000;
    mb64_boundary_object[3]->oFaceAngleRoll = -0x4000;
    mb64_boundary_object[4]->oFaceAnglePitch = 0x4000;
    mb64_boundary_object[5]->oFaceAnglePitch = 0x4000;
}

void update_boundary_wall(struct Object *source) {
    for (u8 i = 0; i < 6; i++) {
        vec3_copy(&mb64_boundary_object[i]->oPosVec, &source->oPosVec);
    }
    mb64_boundary_object[0]->oPosY = GRID_TO_POS(0);
    mb64_boundary_object[1]->oPosY = GRID_TO_POS(64);
    mb64_boundary_object[2]->oPosX = GRID_TO_POS(mb64_grid_min);
    mb64_boundary_object[3]->oPosX = GRID_TO_POS(mb64_grid_min + mb64_grid_size);
    mb64_boundary_object[4]->oPosZ = GRID_TO_POS(mb64_grid_min);
    mb64_boundary_object[5]->oPosZ = GRID_TO_POS(mb64_grid_min + mb64_grid_size);

    if (mb64_menu_state == MB64_MAKE_SCREENSHOT) {
        for (int i = 0; i < 6; i++) {
            mb64_boundary_object[i]->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
        }
    } else {
        for (int i = 0; i < 6; i++) {
            mb64_boundary_object[i]->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        }
    }
}
