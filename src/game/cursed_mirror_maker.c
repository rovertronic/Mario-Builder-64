//object includes (a lot)
#include "text_strings.h"
#include "types.h"
#include "actors/common0.h"
#include "actors/common1.h"
#include "actors/group2.h"
#include "actors/group12.h"
#include "actors/group13.h"
#include "area.h"
#include "audio/external.h"
#include "behavior_actions.h"
#include "behavior_data.h"
#include "camera.h"
#include "debug.h"
#include "dialog_ids.h"
#include "engine/behavior_script.h"
#include "engine/graph_node.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "engine/surface_load.h"
#include "game_init.h"
#include "ingame_menu.h"
#include "interaction.h"
#include "level_misc_macros.h"
#include "level_table.h"
#include "level_update.h"
#include "levels/bob/header.h"
#include "levels/bowser_3/header.h"
#include "levels/castle_inside/header.h"
#include "levels/hmc/header.h"
#include "levels/menu/header.h"
#include "main.h"
#include "mario.h"
#include "mario_actions_cutscene.h"
#include "mario_step.h"
#include "obj_behaviors.h"
#include "obj_behaviors_2.h"
#include "object_constants.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "paintings.h"
#include "platform_displacement.h"
#include "rendering_graph_node.h"
#include "save_file.h"
#include "seq_ids.h"
#include "sm64.h"
#include "spawn_object.h"
#include "spawn_sound.h"
#include "rumble_init.h"
#include "puppylights.h"
#include "rovent.h"
#include "cursed_mirror_maker.h"
#include "actors/group0.h"
#include "levels/bob/header.h"
#include "sram.h"
#include "level_geo.h"
#include "src/buffers/framebuffers.h"
#include "memory.h"

#include "libcart/include/cart.h"
#include "libcart/ff/ff.h"

u8 cmm_mode = CMM_MODE_UNINITIALIZED;
u8 cmm_target_mode = CMM_MODE_MAKE;
u8 cmm_joystick_timer = 0;
s8 cmm_cursor_pos[3] = {0};

Vec3f cmm_camera_pos = {0.0f};
Vec3f cmm_camera_foc = {0.0f};
s16 cmm_camera_angle = 0;
u8 cmm_camera_rot_offset = 0;
s8 cmm_camera_zoom_index = 2;
f32 cmm_current_camera_zoom[2] = {1500.0f,800.0f};

u8 cmm_place_mode = CMM_PM_NONE;

s8 cmm_id_selection = 0;
u8 cmm_rot_selection = 0;
s16 cmm_param_selection = 0;
s16 cmm_mat_selection = 0;

struct cmm_grid_obj cmm_grid_data[64][32][64] = {0};

Gfx cmm_terrain_gfx[CMM_GFX_SIZE]; //gfx
Gfx cmm_terrain_gfx_tp[CMM_GFX_TP_SIZE];//transparent
u32 cmm_terrain_vtx[CMM_VTX_SIZE];

u32 cmm_gfx_total = 0;
u32 cmm_vtx_total = 0;
u32 cmm_gfx_tp_total = 0;

struct cmm_tile cmm_tile_data[CMM_TILE_POOL_SIZE];
struct cmm_obj cmm_object_data[200];
u16 cmm_tile_data_indices[NUM_MATERIALS_PER_THEME + 5] = {0};
u16 cmm_tile_count = 0;
u16 cmm_object_count = 0;
u16 cmm_building_collision = 0; // 0 = building gfx, 1 = building collision

struct Object *cmm_preview_object;
struct Object *cmm_boundary_object[6]; //one for each side

Trajectory cmm_trajectory_list[5][160];
u16 cmm_trajectory_edit_index = 0;
u8 cmm_trajectory_to_edit = 0;
u8 cmm_trajectories_used = 0; //bitfield
u8 cmm_txt_recording[] = {TXT_RECORDING};
Vtx cmm_trajectory_vtx[240];
Gfx cmm_trajectory_gfx[100]; //gfx

//play mode stuff
u8 cmm_play_stars = 0;
u8 cmm_play_stars_max = 0;
u32 cmm_play_stars_bitfield = 0;
u32 cmm_play_badge_bitfield = 0;

//LEVEL SETTINGS INDEX
u8 cmm_lopt_costume = 0;
u8 cmm_lopt_seq = 0;
u8 cmm_lopt_envfx = 0;
u8 cmm_lopt_theme = 0;
u8 cmm_lopt_bg = 0;
u8 cmm_lopt_plane = 0;
u8 cmm_lopt_game = 0;//0 = BTCM, 1 = VANILLA

//UI
u8 cmm_menu_state = CMM_MAKE_MAIN;
s8 cmm_ui_index = 0;
s8 cmm_toolbox_index = 0;
u8 cmm_ui_do_render = TRUE;
u8 cmm_do_save = FALSE;

struct cmm_hack_save cmm_save;

u8 cmm_settings_index = 0;
u8 cmm_settings_index_changed = FALSE;

void df_badge(struct Object * obj, int param) {
    obj->oBehParams2ndByte = param;
}

void df_tree(struct Object * obj, int param) {
    switch(param) {
        case 1:
            obj->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_TREE_2];
        break;
        case 2:
            obj->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_TREE_3];
        break;
        case 3:
            obj->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_TREE_4];
        break;
    }
}

void df_boss(struct Object * obj, int param) {
    switch(param) {
        case 1:
            obj->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_WHOMP_MAKER];
            obj->oAnimations = whomp_seg6_anims_06020A04;
            super_cum_working(obj,0);
            obj_scale(obj,2.0f);
        break;
        case 3:
            obj->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_WIGGLER_HEAD];
            obj->oAnimations = wiggler_seg5_anims_0500EC8C;
            super_cum_working(obj,0);
            obj_scale(obj,4.0f);
        break;
    }
}

void df_exbox(struct Object * obj, int param) {
    switch(param) {
        case 0:
            obj->oAnimState = 0;
        break;
        case 1:
            obj->oAnimState = 1;
        break;
        case 2:
            obj->oAnimState = 2;
        break;
        case 3:
            obj->oAnimState = 3;
        break;
        default:
            obj->oAnimState = 4;
        break;
    }
}

#include "src/game/cursed_mirror_maker_data.inc.c"

void reset_play_state(void) {
    cmm_play_stars = 0;
    cmm_play_stars_bitfield = 0;
    cmm_play_badge_bitfield = 0;
}

u32 coords_in_range(s8 pos[3]) {
    if (pos[0] < GRID_MIN_COORD || pos[0] > GRID_MAX_COORD - 1) return FALSE;
    if (pos[1] < 0 || pos[1] > 31) return FALSE;
    if (pos[2] < GRID_MIN_COORD || pos[2] > GRID_MAX_COORD - 1) return FALSE;
    return TRUE;
}

s32 tile_sanity_check(void) {
    u8 allow = TRUE;

    if (cmm_tile_count >= CMM_TILE_POOL_SIZE) {
        allow = FALSE;
    }
    if (cmm_vtx_total >= CMM_VTX_SIZE - 30) {
        allow = FALSE;
    }
    if (cmm_gfx_total >= CMM_GFX_SIZE - 30) {
        allow = FALSE;
    }
    if (cmm_gfx_tp_total >= CMM_GFX_TP_SIZE - 30) {
        allow = FALSE;
    }

    if (!allow) {
        //error sound
        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
    }
    return allow;
}

s32 object_sanity_check(void) {
    u8 allow = TRUE;

    if (cmm_object_count >= 200) {
        allow = FALSE;
    }

    if (!allow) {
        //error sound
        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
    }
    return allow;
}

ALWAYS_INLINE void place_terrain_data(s8 pos[3], u32 type, u32 rot, u32 mat) {
    cmm_grid_data[pos[0]][pos[1]][pos[2]].rot = rot;
    cmm_grid_data[pos[0]][pos[1]][pos[2]].type = type + 1;
    cmm_grid_data[pos[0]][pos[1]][pos[2]].mat = mat;
    cmm_grid_data[pos[0]][pos[1]][pos[2]].waterlogged = 0;
}

ALWAYS_INLINE void remove_terrain_data(s8 pos[3]) {
    cmm_grid_data[pos[0]][pos[1]][pos[2]].rot = 0;
    cmm_grid_data[pos[0]][pos[1]][pos[2]].type = 0;
    cmm_grid_data[pos[0]][pos[1]][pos[2]].mat = 0;
    cmm_grid_data[pos[0]][pos[1]][pos[2]].waterlogged = 0;
}

ALWAYS_INLINE struct cmm_grid_obj *get_grid_tile(s8 pos[3]) {
    return &cmm_grid_data[pos[0]][pos[1]][pos[2]];
}

u32 get_faceshape(s8 pos[3], u32 dir) {
    s8 tileType = get_grid_tile(pos)->type - 1;
    if (tileType == -1 || tileType == TILE_TYPE_WATER) return CMM_FACESHAPE_EMPTY; // no tile
    if (tileType == TILE_TYPE_CULL) return CMM_FACESHAPE_EMPTY;

    u8 rot = get_grid_tile(pos)->rot;
    dir = ROTATE_DIRECTION(dir,((4-rot) % 4)) ^ 1;

    struct cmm_terrain_block *terrain = cmm_tile_types[tileType].terrain;
    for (u32 i = 0; i < terrain->numQuads; i++) {
        struct cmm_terrain_quad *quad = &terrain->quads[i];
        if (quad->cullDir == dir) {
            return quad->faceshape;
        }
    }
    for (u32 i = 0; i < terrain->numTris; i++) {
        struct cmm_terrain_tri *tri = &terrain->tris[i];
        if (tri->cullDir == dir) {
            return tri->faceshape;
        }
    }
    return CMM_FACESHAPE_EMPTY;
}

ALWAYS_INLINE void place_occupy_data(s8 pos[3]) {
    cmm_grid_data[pos[0]][pos[1]][pos[2]].occupied = TRUE;
}

ALWAYS_INLINE void remove_occupy_data(s8 pos[3]) {
    cmm_grid_data[pos[0]][pos[1]][pos[2]].occupied = FALSE;
}

ALWAYS_INLINE s32 get_occupy_data(s8 pos[3]) {
    if (!coords_in_range(pos)) return FALSE;
    return cmm_grid_data[pos[0]][pos[1]][pos[2]].occupied;
}

s8 cullOffsetLUT[6][3] = {
    {0, 1, 0},
    {0, -1, 0},
    {1, 0, 0},
    {-1, 0, 0},
    {0, 0, 1},
    {0, 0, -1},
};

u32 should_cull(s8 pos[3], u32 direction, u32 faceshape, u32 rot) {
    if (direction == CMM_NO_CULLING) return FALSE;
    direction = ROTATE_DIRECTION(direction, rot);

    s8 newpos[3];
    vec3_sum(newpos, pos, cullOffsetLUT[direction]);
    if (!coords_in_range(newpos)) return TRUE;
    u8 tileType = get_grid_tile(newpos)->type - 1;
    if (tileType == TILE_TYPE_CULL) return TRUE;
    if (cmm_building_collision && tileType == TILE_TYPE_TROLL) return FALSE;

    u8 otherMat = get_grid_tile(newpos)->mat;
    if (MATERIAL(otherMat).type != 0) {
        u8 curMat = get_grid_tile(pos)->mat;
        if (curMat != otherMat) return FALSE;
    }

    u32 otherFaceshape = get_faceshape(newpos, direction);

    if (otherFaceshape == CMM_FACESHAPE_EMPTY) return FALSE;
    if (otherFaceshape == CMM_FACESHAPE_FULL) return TRUE;
    if (faceshape == CMM_FACESHAPE_FULL) return FALSE;
    if (faceshape == CMM_FACESHAPE_TOPTRI) {
        if (otherFaceshape == CMM_FACESHAPE_TOPTRI) {
            u8 otherrot = get_grid_tile(newpos)->rot;
            return (otherrot == rot);
        } else return FALSE;
    }
    return (faceshape == (otherFaceshape^1));
}

u32 *cmm_curr_vtx;
Gfx *cmm_curr_gfx;
u16 cmm_gfx_index;

u32 should_render_grass_side(s8 pos[3], u32 direction, u32 faceshape, u32 rot, u32 grassType) {
    s8 newpos[3];
    vec3_set(newpos, pos[0], pos[1]+1, pos[2]);
    if (should_cull(pos, direction, faceshape, rot)) return FALSE;
    if (!coords_in_range(newpos)) return TRUE;
    u8 otherFaceshape;
    switch (grassType) {
        case CMM_GROWTH_UNDERSLOPE:
            direction = CMM_DIRECTION_POS_Z;
            // fallthrough
        case CMM_GROWTH_NORMAL_SIDE:
            // Shape of face of above block on same side
            otherFaceshape = get_faceshape(newpos, ROTATE_DIRECTION(direction, rot)^1);
            switch (otherFaceshape) {
                case CMM_FACESHAPE_FULL:
                case CMM_FACESHAPE_TRI_1:
                case CMM_FACESHAPE_TRI_2:
                    return FALSE;
            }
            return TRUE;

        // These types are very tricky.
        // If the below face is the same material and is the right shape,
        // an extra decal is printed onto it.
        case CMM_GROWTH_SLOPE_SIDE_L:
        case CMM_GROWTH_SLOPE_SIDE_R:
            // Check if below block is in range
            vec3_set(newpos, pos[0], pos[1]-1, pos[2]);
            if (!coords_in_range(newpos)) return TRUE;

            // Check if below block matches material
            u8 curMat = get_grid_tile(pos)->mat;
            u8 belowMat = get_grid_tile(newpos)->mat;
            if (curMat != belowMat) return TRUE;

            // Check if below block is right shape and culled
            // Shape of face of above block on same side
            otherFaceshape = get_faceshape(newpos, ROTATE_DIRECTION(direction, rot)^1);
            if (should_cull(newpos, direction, otherFaceshape, rot)) return TRUE;
            
            // Calculate effective rotation of face to print. very ugly
            u8 targetRot;
            switch (direction) {
                case CMM_DIRECTION_POS_X:
                    targetRot = 1;
                    break;
                case CMM_DIRECTION_NEG_X:
                    targetRot = 3;
                    break;
                case CMM_DIRECTION_POS_Z:
                    targetRot = 0;
                    break;
                case CMM_DIRECTION_NEG_Z:
                    targetRot = 2;
                    break;
            }
            targetRot = (targetRot + rot) % 4;

            switch (otherFaceshape) {
                default:
                    return TRUE;
                // Face is full quad
                case CMM_FACESHAPE_FULL:
                    // Fill in correct UVs
                    if (grassType == CMM_GROWTH_SLOPE_SIDE_L)
                        cmm_terrain_slopebelowdecal_quad.decaluvs = slope_decal_below_uvsquad_l;
                    else
                        cmm_terrain_slopebelowdecal_quad.decaluvs = slope_decal_below_uvsquad_r;
                    
                    render_quad(&cmm_terrain_slopebelowdecal_quad, cmm_curr_gfx, newpos, targetRot, TRUE);
                    return TRUE;
                case CMM_FACESHAPE_DOWNTRI_1:
                    if (grassType == CMM_GROWTH_SLOPE_SIDE_R)
                        render_tri(&cmm_terrain_slopebelowdecal_downtri1, cmm_curr_gfx, newpos, targetRot, TRUE);
                    return TRUE; 
                case CMM_FACESHAPE_DOWNTRI_2:
                    if (grassType == CMM_GROWTH_SLOPE_SIDE_L)
                        render_tri(&cmm_terrain_slopebelowdecal_downtri2, cmm_curr_gfx, newpos, targetRot, TRUE);
                    return TRUE;
            }
            

        case CMM_GROWTH_DIAGONAL_SIDE:
            otherFaceshape = get_faceshape(newpos, CMM_DIRECTION_UP);
            if (otherFaceshape == CMM_FACESHAPE_FULL) return FALSE;
            if (otherFaceshape != CMM_FACESHAPE_TOPTRI) return TRUE;
            u8 otherrot = get_grid_tile(newpos)->rot;
            return (otherrot != rot);
    }
    return FALSE;
}


s32 handle_wait_vblank(OSMesgQueue *mq) {
    // returns true if it lasts longer than 3 seconds (3 * 1000us * 1000ms)
    OSMesg msg;
    OSTimer timer;
    osSetTimer(&timer, OS_USEC_TO_CYCLES(3000000), 0, mq, (OSMesg)(111*3*2));
    osRecvMesg(mq, &msg, OS_MESG_BLOCK);
    osStopTimer(&timer);

    return msg == (OSMesg)(111*3*2);
}

void generate_path_gfx(void) {
    u16 gfx_index = 0;
    u16 vtx_index = 0;

    gSPDisplayList(&cmm_trajectory_gfx[gfx_index++], mat_maker_MakerLineMat);

    for (u8 i=1;i<cmm_trajectory_edit_index;i++) {
        make_vertex(cmm_trajectory_vtx, vtx_index+0, ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)+1])+0), ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)+2])+20), ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)+3])), -16, 1008, 0x0, 0x7F, 0x0, 0xFF);
        make_vertex(cmm_trajectory_vtx, vtx_index+1, ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)+1])+20), ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)+2])+0), ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)+3])), 1008, 1008, 0x0, 0x7F, 0x0, 0xFF);
        make_vertex(cmm_trajectory_vtx, vtx_index+2, ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)-3])+0), ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)-2])+20), ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)-1])), 1008, -16, 0x0, 0x7F, 0x0, 0xFF);
        make_vertex(cmm_trajectory_vtx, vtx_index+3, ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)-3])-20), ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)-2])+0), ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)-1])), -16, -16, 0x0, 0x7F, 0x0, 0xFF);

        gSPVertex(&cmm_trajectory_gfx[gfx_index++], cmm_trajectory_vtx + vtx_index, 4, 0);
        gSP2Triangles(&cmm_trajectory_gfx[gfx_index++], 0, 1, 2, 0, 0, 2, 3, 0);
        vtx_index+=4;
    }

    gSPEndDisplayList(&cmm_trajectory_gfx[gfx_index]);
}

void cmm_transform_vtx_with_rot(s8 v[][3], s8 oldv[][3], u32 numVtx, u32 rot) {
    for (u32 i = 0; i < numVtx; i++) {
        s8 x = oldv[i][0];
        s8 z = oldv[i][2];
        switch (rot) {
            case 0: v[i][0] = x; v[i][2] = z; break;
            case 1: v[i][0] = z; v[i][2] = 16-x; break;
            case 2: v[i][0] = 16-x; v[i][2] = 16-z; break;
            case 3: v[i][0] = 16-z; v[i][2] = x; break;
        }
        v[i][1] = oldv[i][1];
    }
}

void render_get_normal_and_uvs(s8 v[3][3], u32 uvProjDir, u32 rot, u8 *uAxis, u8 *vAxis, s8 n[3]) {
    // Find normal
    Vec3f normal;
    find_vector_perpendicular_to_plane(normal, v[0], v[1], v[2]);
    vec3_normalize(normal);
    n[0] = normal[0] * 0x7F;
    n[1] = normal[1] * 0x7F;
    n[2] = normal[2] * 0x7F;
    // Find UVs
    if (rot & 1) uvProjDir = 2 - uvProjDir;
    switch (uvProjDir) {
        case 0: *uAxis = 2; *vAxis = 1; break;
        case 1: *uAxis = 2; *vAxis = 0; break;
        case 2: *uAxis = 0; *vAxis = 1; break;
    }
}

void render_quad(struct cmm_terrain_quad *quad, Gfx gfx[], s8 pos[3], u32 rot, u32 isDecal) {
    s8 n[3];
    u8 uAxis, vAxis;

    s8 newVtx[4][3];
    cmm_transform_vtx_with_rot(newVtx, quad->vtx, 4, rot);
    render_get_normal_and_uvs(newVtx, quad->uvProjDir, rot, &uAxis, &vAxis, n);

    for (u32 i = 0; i < 4; i++) {
        s16 u, v;
        if (isDecal && quad->decaluvs) {
            u = 16 - (*quad->decaluvs)[i][0];
            v = 16 - (*quad->decaluvs)[i][1];
        } else {
            u = 16 - newVtx[i][uAxis];
            v = 16 - newVtx[i][vAxis];
        }
        make_vertex(cmm_curr_vtx, i,
            GRID_TO_POS(pos[0])  + ((newVtx[i][0] - 8) * (TILE_SIZE/16)),
            GRIDY_TO_POS(pos[1]) + ((newVtx[i][1] - 8) * (TILE_SIZE/16)),
            GRID_TO_POS(pos[2])  + ((newVtx[i][2] - 8) * (TILE_SIZE/16)),
            u * (1024/16) - 16, v * (1024/16) - 16,
            n[0], n[1], n[2], 0xFF);
    }
    gSPVertex(&gfx[cmm_gfx_index++], cmm_curr_vtx, 4, 0);
    gSP2Triangles(&gfx[cmm_gfx_index++], 0, 1, 2, 0, 1, 3, 2, 0);
    cmm_curr_vtx += 4 * 4;
}

void render_tri(struct cmm_terrain_tri *tri, Gfx gfx[], s8 pos[3], u32 rot, u32 isDecal) {
    s8 n[3];
    u8 uAxis, vAxis;

    s8 newVtx[3][3];
    cmm_transform_vtx_with_rot(newVtx, tri->vtx, 3, rot);
    render_get_normal_and_uvs(newVtx, tri->uvProjDir, rot, &uAxis, &vAxis, n);

    for (u32 i = 0; i < 3; i++) {
        s16 u, v;
        if (isDecal && tri->decaluvs) {
            u = 16 - (*tri->decaluvs)[i][0];
            v = 16 - (*tri->decaluvs)[i][1];
        } else {
            u = 16 - newVtx[i][uAxis];
            v = 16 - newVtx[i][vAxis];
        }
        make_vertex(cmm_curr_vtx, i,
            GRID_TO_POS(pos[0]) + ((newVtx[i][0] - 8) * (TILE_SIZE/16)),
            GRIDY_TO_POS(pos[1])+ ((newVtx[i][1] - 8) * (TILE_SIZE/16)),
            GRID_TO_POS(pos[2]) + ((newVtx[i][2] - 8) * (TILE_SIZE/16)),
            u * (1024/16) - 16, v * (1024/16) - 16,
            n[0], n[1], n[2], 0xFF);
    }
    gSPVertex(&gfx[cmm_gfx_index++], cmm_curr_vtx, 3, 0);
    gSP1Triangle(&gfx[cmm_gfx_index++], 0, 1, 2, 0);
    cmm_curr_vtx += 3 * 4;
}

void render_block_main(s8 pos[3], u32 tileType, u32 mat, u32 rot) {
    struct cmm_terrain_block *terrain = cmm_tile_types[tileType].terrain;
    u8 hasTopside = HAS_TOPMAT(mat);
    for (u32 j = 0; j < terrain->numQuads; j++) {
        struct cmm_terrain_quad *quad = &terrain->quads[j];
        if (!should_cull(pos, quad->cullDir, quad->faceshape, rot)) {
            if (!hasTopside || (quad->growthType != CMM_GROWTH_FULL)) {
                render_quad(quad, cmm_curr_gfx, pos, rot, FALSE);
            }
        }
    }
    for (u32 j = 0; j < terrain->numTris; j++) {
        struct cmm_terrain_tri *tri = &terrain->tris[j];
        if (!should_cull(pos, tri->cullDir, tri->faceshape, rot)) {
            if (!hasTopside || (tri->growthType != CMM_GROWTH_FULL)) {
                render_tri(tri, cmm_curr_gfx, pos, rot, FALSE);
            }
        }
    }
}

void render_block_grass_top(s8 pos[3], u32 tileType, u32 rot) {
    struct cmm_terrain_block *terrain = cmm_tile_types[tileType].terrain;
    for (u32 j = 0; j < terrain->numQuads; j++) {
        struct cmm_terrain_quad *quad = &terrain->quads[j];
        if (quad->growthType == CMM_GROWTH_FULL) {
            if (!should_cull(pos, quad->cullDir, quad->faceshape, rot)) {
                render_quad(quad, cmm_curr_gfx, pos, rot, FALSE);
            }
        }
    }
    
    for (u32 j = 0; j < terrain->numTris; j++) {
        struct cmm_terrain_tri *tri = &terrain->tris[j];
        if (tri->growthType == CMM_GROWTH_FULL) {
            if (!should_cull(pos, tri->cullDir, tri->faceshape, rot)) {
                render_tri(tri, cmm_curr_gfx, pos, rot, FALSE);
            }
        }
    }
}

void render_block_grass_side(s8 pos[3], u32 tileType, u32 rot) {
    struct cmm_terrain_block *terrain = cmm_tile_types[tileType].terrain;
    for (u32 j = 0; j < terrain->numQuads; j++) {
        struct cmm_terrain_quad *quad = &terrain->quads[j];
        if (quad->growthType != CMM_GROWTH_FULL && quad->growthType != CMM_GROWTH_NONE) {
            if (should_render_grass_side(pos, quad->cullDir, quad->faceshape, rot, quad->growthType)) {
                render_quad(quad, cmm_curr_gfx, pos, rot, TRUE);
            }
        }
    }

    for (u32 j = 0; j < terrain->numTris; j++) {
        struct cmm_terrain_tri *tri = &terrain->tris[j];
        if (tri->growthType != CMM_GROWTH_FULL && tri->growthType != CMM_GROWTH_NONE) {
            if (should_render_grass_side(pos, tri->cullDir, tri->faceshape, rot, tri->growthType)) {
                render_tri(tri, cmm_curr_gfx, pos, rot, TRUE);
            }
        }
    }
}

// Find if specific tile of water is fullblock or shallow
u32 is_water_fullblock(s8 pos[3]) {
    return 0;
}

// return type of render to use
// 0: cull
// 1: normal (low side)
// 2: full (full side)
// 3: top (thin top at side)
u32 get_water_side_render(s8 pos[3], u32 dir) {
    return 1;
}

void render_water(s8 pos[3]) {
    struct cmm_terrain_block *terrain = &cmm_terrain_fullblock;
    for (u32 j = 0; j < 6; j++) {
        render_quad(&cmm_terrain_shallowwater_quads[j], cmm_curr_gfx, pos, 0, FALSE);
    }
}

void render_floor(void) {
    make_vertex(cmm_curr_vtx, 0,  4096, 0, -4096,  16384, -16384, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 1, -4096, 0, -4096, -16384, -16384, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 2, -4096, 0,  4096, -16384,  16384, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 3,  4096, 0,  4096,  16384,  16384, 0x0, 0x7F, 0x0, 0xFF);
    gSPVertex(&cmm_curr_gfx[cmm_gfx_index++], cmm_curr_vtx, 4, 0);
    gSP2Triangles(&cmm_curr_gfx[cmm_gfx_index++], 0, 1, 2, 0, 0, 2, 3, 0);
    cmm_curr_vtx += 4 * 4;
}

void generate_terrain_gfx(void) {
    u16 gfx_tdecal_index = 0;
    u16 gfx_tp_index = 0;
    u16 mtx_index = 0;

    u8 tileType, rot;
    s8 pos[3];

    while (sCurrentDisplaySPTask != NULL) {
        osRecvMesg(&gGameVblankQueue, &gMainReceivedMesg, OS_MESG_BLOCK);
    }

    cmm_curr_gfx = cmm_terrain_gfx;
    cmm_curr_vtx = cmm_terrain_vtx;
    cmm_gfx_index = 0;
    cmm_building_collision = 0;

    // Align to 16 bytes for vertices
    cmm_curr_vtx = (u32 *)((((u32)cmm_curr_vtx) & ~15) + 16);

    // This does the funny virtuaplex effect
    for (u32 mat = 0; mat < NUM_MATERIALS_PER_THEME; mat++) {
        if (TILE_MATDEF(mat).mat == CMM_MAT_VP_SCREEN) {
            gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], GBL_c1(G_BL_CLR_MEM, G_BL_0, G_BL_CLR_MEM, G_BL_1) | GBL_c2(G_BL_CLR_MEM, G_BL_0, G_BL_CLR_MEM, G_BL_1), Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP | ZMODE_OPA);
            for (u32 i = cmm_tile_data_indices[mat]; i < cmm_tile_data_indices[mat+1]; i++) {
                tileType = cmm_tile_data[i].type;
                rot = cmm_tile_data[i].rot;
                vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
                //render_block_main(pos, tileType, mat, rot);
            }
            gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        }
    }

    //BOTTOM PLANE
    if (cmm_lopt_plane != 0) {
        u8 planeMat = cmm_theme_table[cmm_lopt_theme].floors[cmm_lopt_plane - 1];
        if (HAS_TOPMAT(planeMat)) {
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], TOPMAT(planeMat).gfx);
        } else {
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], MATERIAL(planeMat).gfx);
        }
        render_floor();
    }

    // Tiles with models
    /**
    for (u32 i = 0; i < cmm_tile_count; i++) {
        if (!cmm_tile_types[cmm_tile_data[i].type].terrain) {
            if (cmm_tile_data[i].type == TILE_TYPE_CULL) {
                continue;
            }
            Mat4 mtx;
            Vec3f pos;
            vec3_set(pos, cmm_tile_data[i].x*TILE_SIZE, cmm_tile_data[i].y*TILE_SIZE, cmm_tile_data[i].z*TILE_SIZE);
            Vec3s rot;
            vec3_set(rot, 0, cmm_tile_data[i].rot*90, 0);
            mtxf_rotate_zxy_and_translate(mtx, pos, rot);
            guMtxF2L(mtx, cmm_curr_vtx);

            if (!cmm_tile_types[cmm_tile_data[i].type].transparent) {
                //opaque
                gSPMatrix(&cmm_curr_gfx[cmm_gfx_index++], VIRTUAL_TO_PHYSICAL(cmm_curr_vtx), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
                gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], cmm_tile_types[cmm_tile_data[i].type].model);
                gSPPopMatrix(&cmm_curr_gfx[cmm_gfx_index++], G_MTX_MODELVIEW);
            } else {
                //transparent
                gSPMatrix(&cmm_terrain_gfx_tp[gfx_tp_index++], VIRTUAL_TO_PHYSICAL(cmm_curr_vtx), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
                gSPDisplayList(&cmm_terrain_gfx_tp[gfx_tp_index++], cmm_tile_types[cmm_tile_data[i].type].model);
                gSPPopMatrix(&cmm_terrain_gfx_tp[gfx_tp_index++], G_MTX_MODELVIEW);
            }
            cmm_curr_vtx += 16;
        }
    }**/

    for (u32 mat = 0; mat < NUM_MATERIALS_PER_THEME; mat++) {
        gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], MATERIAL(mat).gfx);
        for (u32 i = cmm_tile_data_indices[mat]; i < cmm_tile_data_indices[mat+1]; i++) {
            tileType = cmm_tile_data[i].type;
            rot = cmm_tile_data[i].rot;
            vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);

            render_block_main(pos, tileType, mat, rot);
        }
        gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        if (HAS_TOPMAT(mat)) {
            if (SIDETEX(mat) != NULL) {
                gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], SIDETEX(mat));
                for (u32 i = cmm_tile_data_indices[mat]; i < cmm_tile_data_indices[mat+1]; i++) {
                    tileType = cmm_tile_data[i].type;
                    rot = cmm_tile_data[i].rot;
                    vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);

                    render_block_grass_side(pos, tileType, rot);
                }
                gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], &mat_revert_maker_MakerGrassSide_layer1);
            }
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], TOPMAT(mat).gfx);
            for (u32 i = cmm_tile_data_indices[mat]; i < cmm_tile_data_indices[mat+1]; i++) {
                tileType = cmm_tile_data[i].type;
                rot = cmm_tile_data[i].rot;
                vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);

                render_block_grass_top(pos, tileType, rot);
            }
        }
    }


    //cmm_curr_gfx = cmm_terrain_gfx_tp;
    //cmm_gfx_index = 0;
    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], &mat_maker_MakerWater);
    for (u32 i = 0; i < cmm_tile_count; i++) {
        //render_floor();
        if (cmm_tile_data[i].waterlogged) {
            //render_floor();
            tileType = TILE_TYPE_BLOCK;
            vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);

            render_water(pos);
        }
    }
    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], &mat_revert_maker_MakerWater);

    gSPEndDisplayList(&cmm_terrain_gfx[cmm_gfx_index]);
    gSPEndDisplayList(&cmm_terrain_gfx_tp[gfx_tp_index]);

    //print_text_fmt_int(110, 56, "OPAQUE %d", gfx_index);
    //print_text_fmt_int(110, 76, "DECAL %d", gfx_tdecal_index);
    //print_text_fmt_int(110, 96, "TILES %d", cmm_tile_count);
    //print_text_fmt_int(110, 116, "TYPE %d", cmm_tile_data[cmm_tile_count-1].type);

    cmm_vtx_total = cmm_curr_vtx - cmm_terrain_vtx;
    cmm_gfx_total = cmm_gfx_index;
    cmm_gfx_tp_total = gfx_tp_index;
};

Gfx preview_gfx[32];
Mtx preview_mtx[2];
Vtx preview_vtx[64];

Gfx *ccm_append(s32 callContext, UNUSED struct GraphNode *node, UNUSED Mat4 mtx) {

    if (callContext == GEO_CONTEXT_CREATE) {
        generate_terrain_gfx();
        generate_path_gfx();
    }
    if (callContext == GEO_CONTEXT_RENDER) {
        geo_append_display_list(cmm_terrain_gfx, LAYER_OPAQUE);
        geo_append_display_list(cmm_terrain_gfx_tp, LAYER_TRANSPARENT);

        if (cmm_menu_state == CMM_MAKE_TRAJECTORY) {
            geo_append_display_list(cmm_trajectory_gfx, LAYER_OPAQUE);
        }

        //this extra append is for the editor tile preview
        if ((cmm_mode == CMM_MODE_MAKE)&&(cmm_place_mode == CMM_PM_TILE)) {
            //generate dl
            u8 preview_mtx_index = 0;
            cmm_curr_gfx = preview_gfx;
            cmm_curr_vtx = preview_vtx;
            cmm_gfx_index = 0;

            if (cmm_tile_types[cmm_id_selection].model) {
                guTranslate(&preview_mtx[preview_mtx_index], GRID_TO_POS(cmm_cursor_pos[0]), GRIDY_TO_POS(cmm_cursor_pos[1]), GRID_TO_POS(cmm_cursor_pos[2]));
                preview_mtx_index++;
                guRotate(&preview_mtx[preview_mtx_index],90.0f*cmm_rot_selection,0.0f,1.0f,0.0f);
                gSPMatrix(&cmm_curr_gfx[cmm_gfx_index++], VIRTUAL_TO_PHYSICAL(&preview_mtx[preview_mtx_index-1]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
                gSPMatrix(&cmm_curr_gfx[cmm_gfx_index++], VIRTUAL_TO_PHYSICAL(&preview_mtx[preview_mtx_index]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
                //gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], MATERIAL(cmm_param_selection).gfx);
                gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], cmm_tile_types[cmm_id_selection].model);
                gSPPopMatrix(&cmm_curr_gfx[cmm_gfx_index++], G_MTX_MODELVIEW);
                preview_mtx_index++;
            } else if (cmm_tile_types[cmm_id_selection].terrain) {
                gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], MATERIAL(cmm_mat_selection).gfx);
                render_block_main(cmm_cursor_pos, cmm_id_selection, cmm_mat_selection, cmm_rot_selection);
                if (HAS_TOPMAT(cmm_mat_selection)) {
                    if (SIDETEX(cmm_mat_selection) != NULL) {
                        gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], SIDETEX(cmm_mat_selection));
                        render_block_grass_side(cmm_cursor_pos, cmm_id_selection, cmm_rot_selection);
                        gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], &mat_revert_maker_MakerGrassSide_layer1);
                    }
                    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], TOPMAT(cmm_mat_selection).gfx);
                    render_block_grass_top(cmm_cursor_pos, cmm_id_selection, cmm_rot_selection);
                }
            }

            gSPEndDisplayList(&cmm_curr_gfx[cmm_gfx_index]);

            if (!cmm_tile_types[cmm_id_selection].transparent) {
                geo_append_display_list(cmm_curr_gfx, LAYER_OPAQUE);
            } else {
                geo_append_display_list(cmm_curr_gfx, LAYER_TRANSPARENT);
            }
        }

    }
    return NULL;
}

// Create new static surface
extern struct Surface *alloc_surface(u32 dynamic);
extern void add_surface(struct Surface *surface, s32 dynamic);
void cmm_create_surface(TerrainData v1[3], TerrainData v2[3], TerrainData v3[3], TerrainData type) { 
    struct Surface *surface = alloc_surface(FALSE);

    Vec3f n;
    find_vector_perpendicular_to_plane(n, v1, v2, v3);
    if (!vec3f_normalize2(n)) return NULL;

    vec3_copy(surface->vertex1, v1);
    vec3_copy(surface->vertex2, v2);
    vec3_copy(surface->vertex3, v3);

    surface->normal.x = n[0];
    surface->normal.y = n[1];
    surface->normal.z = n[2];

    surface->originOffset = -vec3_dot(n, v1);

    s16 min,max;
    min_max_3s(v1[1], v2[1], v3[1], &min, &max);
    surface->lowerY = (min - SURFACE_VERTICAL_BUFFER);
    surface->upperY = (max + SURFACE_VERTICAL_BUFFER);

    surface->type = type;
    add_surface(surface, FALSE);
};

TerrainData floorVtxs[4][3] = {
    {-4096, 0, 4096},
    {4096, 0, 4096},
    {-4096, 0, -4096},
    {4096, 0, -4096},
};

extern TerrainData sVertexData[900];

TerrainData colVtxs[4][3];

void generate_terrain_collision(void) {
    s16 i;
    gCurrStaticSurfacePool = main_pool_alloc(main_pool_available() - 0x10, MEMORY_POOL_LEFT);
    gCurrStaticSurfacePoolEnd = gCurrStaticSurfacePool;
    gSurfaceNodesAllocated = gNumStaticSurfaceNodes;
    gSurfacesAllocated = gNumStaticSurfaces;
    cmm_building_collision = 1;
    //the first thing to do is to generate the plane... there's only 2 types so it's a hardcoded switchcase
    TerrainData floorType, topFloorType, floorY;

    if (cmm_lopt_plane == 0) {
        floorY = -2500;
        topFloorType = SURFACE_DEATH_PLANE;
    } else {
        floorY = 0;
        u8 mat = cmm_theme_table[cmm_lopt_theme].floors[cmm_lopt_plane - 1];
        if (HAS_TOPMAT(mat)) {
            topFloorType = TOPMAT(mat).col;
        } else {
            topFloorType = MATERIAL(mat).col;
        }
    }
    for (u32 i = 0; i < 4; i++) {
        floorVtxs[i][1] = floorY;
    }
    cmm_create_surface(floorVtxs[0], floorVtxs[1], floorVtxs[2], topFloorType);
    cmm_create_surface(floorVtxs[1], floorVtxs[3], floorVtxs[2], topFloorType);

    for (i=0; i<cmm_tile_count; i++) {
        struct cmm_terrain_block *terrain = cmm_tile_types[cmm_tile_data[i].type].terrain;
        if (terrain) {
            if (cmm_tile_data[i].type == TILE_TYPE_TROLL) {
                continue;
            }
            if (cmm_tile_data[i].type == TILE_TYPE_WATER) {
                continue;
            }
            floorType = MATERIAL(cmm_tile_data[i].mat).col;
            if (HAS_TOPMAT(cmm_tile_data[i].mat)) {
                topFloorType = TOPMAT(cmm_tile_data[i].mat).col;
            } else {
                topFloorType = floorType;
            }
            s8 pos[3];
            s8 newVtx[4][3];
            vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
            for (u32 j = 0; j < terrain->numQuads; j++) {
                struct cmm_terrain_quad *quad = &terrain->quads[j];
                if (!should_cull(pos, quad->cullDir, quad->faceshape, cmm_tile_data[i].rot)) {
                    TerrainData surfType = (quad->growthType == CMM_GROWTH_FULL) ? topFloorType : floorType;
                    cmm_transform_vtx_with_rot(newVtx, quad->vtx, 4, cmm_tile_data[i].rot);
                    for (u32 k = 0; k < 4; k++) {
                        colVtxs[k][0] = GRID_TO_POS(pos[0])  + ((newVtx[k][0] - 8) * (TILE_SIZE/16)),
                        colVtxs[k][1] = GRIDY_TO_POS(pos[1]) + ((newVtx[k][1] - 8) * (TILE_SIZE/16)),
                        colVtxs[k][2] = GRID_TO_POS(pos[2])  + ((newVtx[k][2] - 8) * (TILE_SIZE/16));
                    }
                    cmm_create_surface(colVtxs[0], colVtxs[1], colVtxs[2], surfType);
                    cmm_create_surface(colVtxs[1], colVtxs[3], colVtxs[2], surfType);
                }
            }
            for (u32 j = 0; j < terrain->numTris; j++) {
                struct cmm_terrain_tri *tri = &terrain->tris[j];
                if (!should_cull(pos, tri->cullDir, tri->faceshape, cmm_tile_data[i].rot)) {
                    TerrainData surfType = (tri->growthType == CMM_GROWTH_FULL) ? topFloorType : floorType;
                    cmm_transform_vtx_with_rot(newVtx, tri->vtx, 3, cmm_tile_data[i].rot);
                    for (u32 k = 0; k < 3; k++) {
                        colVtxs[k][0] = GRID_TO_POS(pos[0])  + ((newVtx[k][0] - 8) * (TILE_SIZE/16)),
                        colVtxs[k][1] = GRIDY_TO_POS(pos[1]) + ((newVtx[k][1] - 8) * (TILE_SIZE/16)),
                        colVtxs[k][2] = GRID_TO_POS(pos[2])  + ((newVtx[k][2] - 8) * (TILE_SIZE/16));
                    }
                    cmm_create_surface(colVtxs[0], colVtxs[1], colVtxs[2], surfType);
                }
            }
        } else if (cmm_tile_types[cmm_tile_data[i].type].collision_data) {
            Vec3f pos = {GRID_TO_POS(cmm_tile_data[i].x), GRIDY_TO_POS(cmm_tile_data[i].y), GRID_TO_POS(cmm_tile_data[i].z)};
            Vec3s rot = {0,cmm_tile_data[i].rot*0x4000,0};
            mtxf_rotate_zxy_and_translate(o->transform,pos,rot);

            //this code was written by accident... the collision doesn't generate properly without it though???
            o->oPosX = GRID_TO_POS(cmm_tile_data[0].x);
            o->oPosY = GRIDY_TO_POS(cmm_tile_data[0].y);
            o->oPosZ = GRID_TO_POS(cmm_tile_data[0].z);
            o->oFaceAngleYaw = (cmm_tile_data[i].rot*0x4000);
            
            TerrainData *collisionData = segmented_to_virtual(cmm_tile_types[cmm_tile_data[i].type].collision_data);
            collisionData++;
            transform_object_vertices(&collisionData, sVertexData);

            // TERRAIN_LOAD_CONTINUE acts as an "end" to the terrain data.
            while (*collisionData != TERRAIN_LOAD_CONTINUE) {
                load_object_surfaces(&collisionData, sVertexData, FALSE);
            }
        }
    }

    cmm_building_collision = 0;
    u32 surfacePoolData = (uintptr_t)gCurrStaticSurfacePoolEnd - (uintptr_t)gCurrStaticSurfacePool;
    gTotalStaticSurfaceData += surfacePoolData;
    main_pool_realloc(gCurrStaticSurfacePool, surfacePoolData);

    gNumStaticSurfaceNodes = gSurfaceNodesAllocated;
    gNumStaticSurfaces = gSurfacesAllocated;
}

void generate_object_preview(void) {
    struct Object *preview_object;
    u8 i;

    preview_object = cur_obj_nearest_object_with_behavior(bhvStaticObject);
    while(preview_object) {
        mark_obj_for_deletion(preview_object);
        preview_object = cur_obj_nearest_object_with_behavior(bhvStaticObject);
    }

    for(i=0;i<cmm_object_count;i++){
        preview_object = spawn_object(gMarioObject, cmm_object_types[cmm_object_data[i].type].model_id ,bhvStaticObject);
        preview_object->oPosX = GRID_TO_POS(cmm_object_data[i].x);
        preview_object->oPosY = GRIDY_TO_POS(cmm_object_data[i].y) - TILE_SIZE/2 + cmm_object_types[cmm_object_data[i].type].y_offset;
        preview_object->oPosZ = GRID_TO_POS(cmm_object_data[i].z);
        preview_object->oFaceAngleYaw = cmm_object_data[i].rot*0x4000;
        obj_scale(preview_object, cmm_object_types[cmm_object_data[i].type].scale);
        if (cmm_object_types[cmm_object_data[i].type].billboarded) {
            preview_object->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
        }
        if (cmm_object_types[cmm_object_data[i].type].anim) {
            preview_object->oAnimations = cmm_object_types[cmm_object_data[i].type].anim;
            super_cum_working(preview_object,0);
            preview_object->header.gfx.animInfo.animAccel = 0.0f;
        }
        if (cmm_object_types[cmm_object_data[i].type].disp_func) {
            (cmm_object_types[cmm_object_data[i].type].disp_func)(preview_object,cmm_object_data[i].param);
        }
    }
}

void generate_objects_to_level(void) {
    struct Object *obj;
    u8 i;
    cmm_play_stars_max = 0;
    for(i=0;i<cmm_object_count;i++){
        //obj = create_object(cmm_object_types[cmm_object_data[i].type].behavior);
        //obj->behavior = cmm_object_types[cmm_object_data[i].type].behavior;
        //obj->header.gfx.sharedChild = gLoadedGraphNodes[cmm_object_types[cmm_object_data[i].type].model_id];

        obj = spawn_object(gMarioObject, cmm_object_types[cmm_object_data[i].type].model_id , cmm_object_types[cmm_object_data[i].type].behavior);

        obj->oPosX = GRID_TO_POS(cmm_object_data[i].x);
        obj->oPosY = GRIDY_TO_POS(cmm_object_data[i].y) - TILE_SIZE/2 +cmm_object_types[cmm_object_data[i].type].y_offset;
        obj->oPosZ = GRID_TO_POS(cmm_object_data[i].z);
        obj->oFaceAngleYaw = cmm_object_data[i].rot*0x4000;
        obj->oMoveAngleYaw = cmm_object_data[i].rot*0x4000;
        obj->oBehParams2ndByte = cmm_object_data[i].param;

        //assign star ids
        for (u8 j=0;j<sizeof(cmm_star_objects);j++) {
            if (cmm_object_data[i].type == cmm_star_objects[j]) {
                if (cmm_play_stars_max < 32) {
                    obj->oBehParams = ((cmm_play_stars_max << 24)|(o->oBehParams2ndByte << 16));
                    cmm_play_stars_max++;
                }
                break;
            }
        }
    }
}

#define WATER_TILETYPE_INDEX (NUM_MATERIALS_PER_THEME + 1)

u32 get_tiletype_index(u32 type, u32 mat) {
    switch (type) {
        case TILE_TYPE_FENCE:
            return NUM_MATERIALS_PER_THEME;
        case TILE_TYPE_WATER:
            return WATER_TILETYPE_INDEX;
        case TILE_TYPE_CULL:
            return NUM_MATERIALS_PER_THEME + 2;
        default:
            if (cmm_tile_types[type].terrain) {
                return mat;
            }
    }
    return NUM_MATERIALS_PER_THEME + 3;
}

// shift all indices past the given one by 1
// return index to insert a new block at
u32 shift_tile_data_indices(u32 tiletypeIndex) {
    u32 tiledataIndex = cmm_tile_data_indices[tiletypeIndex + 1];
    // Shift all indices forward one
    for (u32 i = tiletypeIndex + 1; i < ARRAY_COUNT(cmm_tile_data_indices); i++) {
        cmm_tile_data_indices[i]++;
    }

    // Shift all data forward one
    for (u32 i = cmm_tile_count; i > tiledataIndex; i--) {
        cmm_tile_data[i] = cmm_tile_data[i - 1];
    }
    return tiledataIndex;
}

void place_tile(s8 pos[3]) {
    if ((!cmm_tile_types[cmm_id_selection].model) || (cmm_id_selection == TILE_TYPE_CULL)) {
        place_terrain_data(pos, cmm_id_selection, cmm_rot_selection, cmm_mat_selection);
    }
    u32 index = get_tiletype_index(cmm_id_selection, cmm_mat_selection);
    u32 newtileIndex = shift_tile_data_indices(index);
    
    cmm_tile_data[newtileIndex].x = pos[0];
    cmm_tile_data[newtileIndex].y = pos[1];
    cmm_tile_data[newtileIndex].z = pos[2];
    cmm_tile_data[newtileIndex].type = cmm_id_selection;
    cmm_tile_data[newtileIndex].mat = cmm_mat_selection;
    cmm_tile_data[newtileIndex].rot = cmm_rot_selection;
    cmm_tile_data[newtileIndex].waterlogged = FALSE;
    cmm_tile_count++;
}

void place_water(s8 pos[3]) {
    struct cmm_grid_obj *tile = get_grid_tile(pos);
    if (!tile->waterlogged) {
        if (tile->type != 0) {
            tile->waterlogged = TRUE;
            u32 tileIndex = get_tiletype_index(tile->type, tile->mat);
            for (u32 i = cmm_tile_data_indices[tileIndex]; i < cmm_tile_data_indices[tileIndex + 1]; i++) {
                if (cmm_tile_data[i].x == pos[0] && cmm_tile_data[i].y == pos[1] && cmm_tile_data[i].z == pos[2]) {
                    cmm_tile_data[i].waterlogged = TRUE;
                    break;
                }
                // should not be possible to reach here
            }
        } else {
            // empty currently, so add water
            place_terrain_data(pos, TILE_TYPE_WATER, 0, 0);
            tile->waterlogged = TRUE;
            u32 newtileIndex = shift_tile_data_indices(WATER_TILETYPE_INDEX);

            cmm_tile_data[newtileIndex].x = pos[0];
            cmm_tile_data[newtileIndex].y = pos[1];
            cmm_tile_data[newtileIndex].z = pos[2];
            cmm_tile_data[newtileIndex].type = TILE_TYPE_WATER; // should be unused
            cmm_tile_data[newtileIndex].mat = 0; // should be unused
            cmm_tile_data[newtileIndex].rot = 0;
            cmm_tile_data[newtileIndex].waterlogged = TRUE;
            cmm_tile_count++;
        }
    }
}

void place_object(s8 pos[3]) {
    if (cmm_object_count < 200) {
        cmm_object_data[cmm_object_count].x = pos[0];
        cmm_object_data[cmm_object_count].y = pos[1];
        cmm_object_data[cmm_object_count].z = pos[2];
        cmm_object_data[cmm_object_count].type = cmm_id_selection;
        cmm_object_data[cmm_object_count].rot = cmm_rot_selection;
        cmm_object_data[cmm_object_count].param = cmm_param_selection;

        if (cmm_object_types[cmm_id_selection].use_trajectory) {
            u8 trajectory_found = FALSE;
            for (u8 i=0;i<5;i++) {
                if (!((cmm_trajectories_used>>i) & 1)) {
                    cmm_trajectories_used |= (1 << i);
                    cmm_trajectory_to_edit = i;
                    cmm_object_data[cmm_object_count].param = i;
                    trajectory_found = TRUE;
                    break;
                }
            }

            if (!trajectory_found) {
                play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                cmm_object_count --;
                remove_occupy_data(cmm_cursor_pos);
            } else {
                cmm_menu_state = CMM_MAKE_TRAJECTORY;
                o->oAction = 5; //trajectory editor
                cmm_trajectory_edit_index = 0;
                generate_path_gfx();
            }
        }

        cmm_object_count++;
    } else {
        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
    }
}

u8 joystick_direction(void) {
    if (cmm_joystick_timer > 0) {
        cmm_joystick_timer--;
    }

    if ((gPlayer1Controller->rawStickX < 10)&&(gPlayer1Controller->rawStickX > -10)&&(gPlayer1Controller->rawStickY < 10)&&(gPlayer1Controller->rawStickY > -10)) {
        cmm_joystick_timer = 0;
    }

    if (cmm_joystick_timer == 0) {
        if (gPlayer1Controller->rawStickX > 60) {
            cmm_joystick_timer = 5;
            return 3;
        }
        if (gPlayer1Controller->rawStickX < -60) {
            cmm_joystick_timer = 5;
            return 1;
        }
        if (gPlayer1Controller->rawStickY > 60) {
            cmm_joystick_timer = 5;
            return 4;
        }
        if (gPlayer1Controller->rawStickY < -60) {
            cmm_joystick_timer = 5;
            return 2;
        }
    }

    return 0;
}

void place_thing_action(void) {
     if (cmm_place_mode == CMM_PM_WATER) {
        if (tile_sanity_check()) {
            place_water(cmm_cursor_pos);
            generate_terrain_gfx();
        }
        return;
    }
    //tiles and objects share occupancy data
    if (!get_occupy_data(cmm_cursor_pos)) {
        if (cmm_place_mode == CMM_PM_TILE) {
            //CMM_PM_TILE
            if (tile_sanity_check()) {
                place_occupy_data(cmm_cursor_pos);
                place_tile(cmm_cursor_pos);
                generate_terrain_gfx();
            }
        } else if (cmm_place_mode == CMM_PM_OBJ){
            //CMM_PM_OBJECT
            if (object_sanity_check()) {
                place_occupy_data(cmm_cursor_pos);
                place_object(cmm_cursor_pos);
                generate_object_preview();
            }
        }
    }
}

//function name is delete tile, it deletes objects too
void delete_tile_action(void) {
    u8 mode = 0;
    s16 index = -1;

    //0 = searching
    //1 = targeting
    //(sport mode reference)

    for (u32 i = 0; i < cmm_tile_count; i++) {
        //search for tile to delete
        if ((cmm_tile_data[i].x == cmm_cursor_pos[0])&&(cmm_tile_data[i].y == cmm_cursor_pos[1])&&(cmm_tile_data[i].z == cmm_cursor_pos[2])) {
            index = i;
            remove_occupy_data(cmm_cursor_pos);
            remove_terrain_data(cmm_cursor_pos);
            cmm_tile_count--;
        }
    }

    if (index != -1) {
        u32 tiletypeIndex = get_tiletype_index(cmm_tile_data[index].type, cmm_tile_data[index].mat);

        for (u32 i = tiletypeIndex + 1; i < ARRAY_COUNT(cmm_tile_data_indices); i++) {
            cmm_tile_data_indices[i]--;
        }
        for (u32 i = index; i < cmm_tile_count; i++) {
            cmm_tile_data[i] = cmm_tile_data[i+1];
        }
        generate_terrain_gfx();
    }

    index = -1;
    for (u32 i=0;i<cmm_object_count;i++) {
        if ((cmm_object_data[i].x == cmm_cursor_pos[0])&&(cmm_object_data[i].y == cmm_cursor_pos[1])&&(cmm_object_data[i].z == cmm_cursor_pos[2])) {
            index = i;
            remove_occupy_data(cmm_cursor_pos);
            cmm_object_count--;

            if (cmm_object_types[cmm_object_data[i].type].use_trajectory) { 
                //unlink trajectory
                cmm_trajectories_used &= ~(1<<cmm_object_data[i].param);
            }
        }
    }
    if (index != -1) {
        for (u32 i = index; i < cmm_object_count; i++) {
            cmm_object_data[i] = cmm_object_data[i+1];
        }
        generate_object_preview();
    }
}

void update_painting() {
    s16 x;
    s16 y;
    u16 *u16_array = segmented_to_virtual(b_LevelPainting_rgba16);
    for (x = 4; x < 28; x++) {
        for (y = 4; y < 28; y++) {
            u16_array[(y*32)+x] = cmm_save.lvl[0].piktcher[y-4][x-4];
        } 
    }
}

//if (gSramProbe != 0) {

TCHAR cmm_file_name[30];
FIL cmm_file;
FILINFO cmm_file_info;

void save_level(u8 index) {
    s16 i;
    s16 j;

    bzero(&cmm_save.lvl[index], sizeof(cmm_save.lvl[index]));
    //bzero(&cmm_grid_data, sizeof(cmm_grid_data));

    cmm_save.lvl[index].tile_count = cmm_tile_count;
    cmm_save.lvl[index].object_count = cmm_object_count;

    cmm_save.lvl[index].option[0] = cmm_lopt_costume;
    cmm_save.lvl[index].option[1] = cmm_lopt_seq;
    cmm_save.lvl[index].option[2] = cmm_lopt_envfx;
    cmm_save.lvl[index].option[3] = cmm_lopt_theme;
    cmm_save.lvl[index].option[4] = cmm_lopt_bg;
    cmm_save.lvl[index].option[5] = cmm_lopt_plane;
    cmm_save.lvl[index].option[18] = cmm_trajectories_used;
    cmm_save.lvl[index].option[19] = cmm_lopt_game;

    //SAVE
    for (i = 0; i < cmm_tile_count; i++) {
        //Save tiles
        bcopy(&cmm_tile_data[i],&cmm_save.lvl[index].tiles[i],sizeof(cmm_tile_data[i]));
    }

    for (i = 0; i < cmm_object_count; i++) {
        //Save Objects
        bcopy(&cmm_object_data[i],&cmm_save.lvl[index].objects[i],sizeof(cmm_object_data[i]));
    }

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 40; j++) {
            cmm_save.lvl[index].trajectories[i][j].t = cmm_trajectory_list[i][(j*4)+0];
            cmm_save.lvl[index].trajectories[i][j].x = POS_TO_GRID(cmm_trajectory_list[i][(j*4)+1]);
            cmm_save.lvl[index].trajectories[i][j].y = POS_TO_GRIDY(cmm_trajectory_list[i][(j*4)+2]);
            cmm_save.lvl[index].trajectories[i][j].z = POS_TO_GRID(cmm_trajectory_list[i][(j*4)+3]);
        }
    }

    for (i=0;i<784;i++) {
        //take a "screenshot" of the level
        cmm_save.lvl[index].piktcher[i/28][i%28] = gFramebuffers[(sRenderingFramebuffer+2)%3][ ((i/28)*320*8)+((i%28)*11)];
    }

    update_painting();

    //block_until_rumble_pak_free();
    //nuPiWriteSram(0,&cmm_save, sizeof(cmm_save));
    //release_rumble_pak_control();

    u32 bytes_written;
    f_open(&cmm_file,&cmm_file_name, FA_READ | FA_WRITE | FA_CREATE_ALWAYS);
    f_write(&cmm_file,&cmm_save,sizeof(cmm_save),&bytes_written);
    f_close(&cmm_file);
}

void load_level(u8 index) {
    s16 i;
    s16 j;
    u8 fresh = FALSE;

    bzero(&cmm_save.lvl[index], sizeof(cmm_save.lvl[index]));
    bzero(&cmm_grid_data, sizeof(cmm_grid_data));

    //LOAD
    //block_until_rumble_pak_free();
    //nuPiReadSram(0,&cmm_save, sizeof(cmm_save));
    //release_rumble_pak_control();

    u32 bytes_read;
    FRESULT code = f_stat(&cmm_file_name,&cmm_file_info);
    if (code == FR_OK) {
        //file exists, load it
        f_open(&cmm_file,&cmm_file_name, FA_READ | FA_WRITE);
        f_read(&cmm_file,&cmm_save,sizeof(cmm_save),&bytes_read);
        f_close(&cmm_file);
    } else {
        //Load into a fresh level
        fresh = TRUE;
        bzero(&cmm_save, sizeof(cmm_save));

        //Set version
        cmm_save.lvl[0].version = CMM_VERSION;

        //Place spawn location
        cmm_save.lvl[0].object_count = 1;
        cmm_save.lvl[0].objects[0].x = 32;
        cmm_save.lvl[0].objects[0].z = 32;
        cmm_save.lvl[0].objects[0].y = 4;
        cmm_save.lvl[0].objects[0].type = OBJECT_TYPE_SPAWN;

        cmm_save.lvl[index].option[19] = cmm_lopt_game;
    }

    cmm_tile_count = cmm_save.lvl[index].tile_count;
    cmm_object_count = cmm_save.lvl[index].object_count;

    cmm_lopt_costume = cmm_save.lvl[index].option[0];
    cmm_lopt_seq = cmm_save.lvl[index].option[1];
    cmm_lopt_envfx = cmm_save.lvl[index].option[2];
    cmm_lopt_theme = cmm_save.lvl[index].option[3];
    cmm_lopt_bg = cmm_save.lvl[index].option[4];

    cmm_settings_buttons[5].size = cmm_theme_table[cmm_lopt_theme].numFloors + 1;
    cmm_lopt_plane = cmm_save.lvl[index].option[5];

    cmm_trajectories_used = cmm_save.lvl[index].option[18];
    cmm_lopt_game = cmm_save.lvl[index].option[19];

    //configure toolbox depending on game style
    switch(cmm_lopt_game) {
        case CMM_GAME_BTCM:
            bcopy(&cmm_toolbox_btcm,&cmm_toolbox,sizeof(cmm_toolbox));
        break;
        case CMM_GAME_VANILLA:
            bcopy(&cmm_toolbox_vanilla,&cmm_toolbox,sizeof(cmm_toolbox));
        break;
    }

    load_segment_decompress_skybox(0xA,cmm_skybox_table[cmm_lopt_bg*2],cmm_skybox_table[cmm_lopt_bg*2+1]);

    u32 oldIndex = 0;
    cmm_tile_data_indices[0] = 0;
    // Load tiles and build index list. Assume all tiles are in order
    for (i = 0; i < cmm_tile_count; i++) {
        bcopy(&cmm_save.lvl[index].tiles[i],&cmm_tile_data[i],sizeof(cmm_tile_data[i]));
        u32 curIndex = get_tiletype_index(cmm_tile_data[i].type, cmm_tile_data[i].mat);

        if (curIndex != oldIndex) {
            // These tiles do not exist in the level so fill in the indices
            for (u32 j = oldIndex + 1; j < curIndex; j++) {
                cmm_tile_data_indices[j] = cmm_tile_data_indices[oldIndex];
            }
            cmm_tile_data_indices[curIndex] = i;

            oldIndex = curIndex;
        }

        s8 pos[3];
        vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z)

        if ((!cmm_tile_types[cmm_tile_data[i].type].model) || cmm_tile_data[i].type == TILE_TYPE_CULL) {
            place_terrain_data(pos, cmm_tile_data[i].type, cmm_tile_data[i].rot, cmm_tile_data[i].mat);
        }
        place_occupy_data(pos);
    }
    // Fill in remaining indices that were unused
    for (u32 i = oldIndex + 1; i < ARRAY_COUNT(cmm_tile_data_indices); i++) {
        cmm_tile_data_indices[i] = cmm_tile_count;
    }

    for (i = 0; i < cmm_object_count; i++) {
        bcopy(&cmm_save.lvl[index].objects[i],&cmm_object_data[i],sizeof(cmm_object_data[i]));
        s8 pos[3];
        vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z)
        place_occupy_data(pos);
    }

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 40; j++) {
            cmm_trajectory_list[i][(j*4)+0] = cmm_save.lvl[index].trajectories[i][j].t;
            cmm_trajectory_list[i][(j*4)+1] = GRID_TO_POS(cmm_save.lvl[index].trajectories[i][j].x);
            cmm_trajectory_list[i][(j*4)+2] = GRIDY_TO_POS(cmm_save.lvl[index].trajectories[i][j].y);
            cmm_trajectory_list[i][(j*4)+3] = GRID_TO_POS(cmm_save.lvl[index].trajectories[i][j].z);
        }
    }

    if (!fresh) {
        update_painting();
    }
}

void cmm_init() {
    load_level(0);
}

void sb_init(void) {
    struct Object *spawn_obj;

    vec3_set(cmm_cursor_pos, 32, 4, 32);
    cmm_ui_index = 0;
    vec3f_copy(&cmm_camera_foc,&o->oPosVec);
    load_segment_decompress_skybox(0xA,cmm_skybox_table[cmm_lopt_bg*2],cmm_skybox_table[cmm_lopt_bg*2+1]);

    switch(cmm_mode) {
        case CMM_MODE_MAKE:
            o->oAction = 1;
            o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            generate_object_preview();
            generate_terrain_gfx();
            cmm_preview_object = spawn_object(o,MODEL_NONE,bhvPreviewObject);

            //init visual tile bounds
            for (u8 i=0; i<6; i++) {
                cmm_boundary_object[i] = spawn_object(o,MODEL_MAKER_BOUNDARY,bhvPreviewObject);
            }
            cmm_boundary_object[2]->oFaceAngleRoll = -0x4000;
            cmm_boundary_object[3]->oFaceAngleRoll = -0x4000;
            cmm_boundary_object[4]->oFaceAnglePitch = 0x4000;
            cmm_boundary_object[5]->oFaceAnglePitch = 0x4000;
        break;
        case CMM_MODE_PLAY:
            generate_terrain_collision();
            generate_objects_to_level();
            load_obj_warp_nodes();

            spawn_obj = cur_obj_nearest_object_with_behavior(bhvSpawn);
            if (spawn_obj) {
                vec3f_copy(&gMarioState->pos,&spawn_obj->oPosVec);
                gMarioState->pos[1] -= TILE_SIZE/2;

                struct Object *warpobj = cur_obj_nearest_object_with_behavior(bhvInstantActiveWarp);
                if (warpobj) {
                    vec3f_copy(&warpobj->oPosVec,&spawn_obj->oPosVec);
                    warpobj->oPosY -= TILE_SIZE/2;
                }
            }

            gMarioState->CostumeID = cmm_lopt_costume;

            o->oAction = 2;
            o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;

            play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, seq_musicmenu_array[cmm_lopt_seq]), 0);
        break;
    }
}

void sb_loop(void) {
    Vec3f cam_pos_offset = {0.0f,cmm_current_camera_zoom[1],0};
    u8 joystick = joystick_direction();
    u8 cursor_did_move = FALSE;
    u8 drag_updown = FALSE;

    if (cmm_do_save) {
        cmm_do_save = FALSE;
        save_level(0);
    }
    //print_text_fmt_int(180, 200, "BUF %d", gGfxPoolEnd - (u8 *) gDisplayListHead);

    cmm_camera_angle = approach_s16_asymptotic(cmm_camera_angle,cmm_camera_rot_offset*0x4000,4);
    cam_pos_offset[0] = sins(cmm_camera_angle+0x8000)*cmm_current_camera_zoom[0];
    cam_pos_offset[2] = coss(cmm_camera_angle+0x8000)*cmm_current_camera_zoom[0];

    cmm_current_camera_zoom[0] = lerp(cmm_current_camera_zoom[0], cmm_camera_zoom_table[cmm_camera_zoom_index][0],0.2f);
    cmm_current_camera_zoom[1] = lerp(cmm_current_camera_zoom[1], cmm_camera_zoom_table[cmm_camera_zoom_index][1],0.2f);

    switch(o->oAction) {
        case 0: //init

        break;
        case 1: //MAKE MODE MAIN
            //START MOVE CURSOR
            if (joystick != 0) {
                switch(((joystick-1)+cmm_camera_rot_offset)%4) {
                    case 0:
                        cmm_cursor_pos[0]++;
                    break;
                    case 1:
                        cmm_cursor_pos[2]--;
                    break;
                    case 2:
                        cmm_cursor_pos[0]--;
                    break;
                    case 3:
                        cmm_cursor_pos[2]++;
                    break;
                }
            }

            if (gPlayer1Controller->buttonPressed & U_CBUTTONS) {
                cmm_cursor_pos[1]++;
                drag_updown=TRUE;
            }
            if (gPlayer1Controller->buttonPressed & D_CBUTTONS) {
                cmm_cursor_pos[1]--;
                drag_updown=TRUE;
            }
            if (gPlayer1Controller->buttonPressed & R_CBUTTONS) {
                cmm_camera_rot_offset++;
            }
            if (gPlayer1Controller->buttonPressed & L_CBUTTONS) {
                cmm_camera_rot_offset--;
            }
            cmm_camera_rot_offset = (cmm_camera_rot_offset % 4)+4;

            cmm_cursor_pos[0] = ((cmm_cursor_pos[0] - GRID_MIN_COORD + GRID_SIZE) % GRID_SIZE) + GRID_MIN_COORD;
            cmm_cursor_pos[2] = ((cmm_cursor_pos[2] - GRID_MIN_COORD + GRID_SIZE) % GRID_SIZE) + GRID_MIN_COORD;
            cmm_cursor_pos[1]=(cmm_cursor_pos[1]+32)%32;
            //END MOVE CURSOR

            if (gPlayer1Controller->buttonPressed & L_TRIG) {
                cmm_ui_index--;
                cmm_param_selection = 0;
            }
            if (gPlayer1Controller->buttonPressed & R_TRIG) {
                cmm_ui_index++;
                cmm_param_selection = 0;
            }
            cmm_id_selection = cmm_ui_buttons[cmm_ui_bar[cmm_ui_index]].id;
            cmm_place_mode = cmm_ui_buttons[cmm_ui_bar[cmm_ui_index]].placeMode;
            cmm_ui_index = (cmm_ui_index+9)%9;

            //parameter changing
            if (gPlayer1Controller->buttonPressed & L_JPAD) {
                cmm_param_selection --;
            }
            if (gPlayer1Controller->buttonPressed & R_JPAD) {
                cmm_param_selection ++;
            }

            //camera zooming
            if (gPlayer1Controller->buttonPressed & U_JPAD) {
                cmm_camera_zoom_index--;
            }
            if (gPlayer1Controller->buttonPressed & D_JPAD) {
                cmm_camera_zoom_index++;
            }
            cmm_camera_zoom_index = (cmm_camera_zoom_index+5)%5;
  

            if (cmm_ui_index<6) {
                //drag
                if ((joystick > 0)||(drag_updown)) {
                    if (gPlayer1Controller->buttonDown & B_BUTTON) {
                        delete_tile_action();
                    }
                    if (gPlayer1Controller->buttonDown & A_BUTTON) {
                        place_thing_action();
                    }
                }
                //delete
                if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                    delete_tile_action();
                }
            }

            //Single A press
            if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                switch(cmm_ui_index) {
                    case 8://save data
                        if (mount_success == FR_OK) {
                            cmm_do_save = TRUE;
                            cmm_ui_do_render = FALSE;
                        } else {
                            play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                        }
                    break;
                    case 7://settings
                        cmm_menu_state = CMM_MAKE_SETTINGS;
                        o->oAction = 4;
                    break;
                    case 6://test
                        cmm_target_mode = CMM_MODE_PLAY;
                        reset_play_state();
                        level_trigger_warp(gMarioState, WARP_OP_LOOK_UP);
                        sSourceWarpNodeId = 0x0A;
                        o->oAction = 2;
                    break;
                    default://everything else places
                        place_thing_action();
                    break; 
                }
            }

            if (o->oAction != 1) {
                return;
            }

            if (gPlayer1Controller->buttonPressed & START_BUTTON) {
                o->oAction = 3;
                cmm_menu_state = CMM_MAKE_TOOLBOX;
                if (cmm_ui_index > 5) {
                    cmm_ui_index = 5;
                }
            }

            if (gPlayer1Controller->buttonPressed & Z_TRIG) {
                cmm_rot_selection++;
                cmm_rot_selection%=4;
            }

            cmm_camera_foc[0] = lerp(cmm_camera_foc[0], GRID_TO_POS(cmm_cursor_pos[0]),  0.2f);
            cmm_camera_foc[1] = lerp(cmm_camera_foc[1], GRIDY_TO_POS(cmm_cursor_pos[1]), 0.2f);
            cmm_camera_foc[2] = lerp(cmm_camera_foc[2], GRID_TO_POS(cmm_cursor_pos[2]),  0.2f);

            vec3f_copy(&cmm_camera_pos,&cmm_camera_foc);
            vec3f_add(&cmm_camera_pos,&cam_pos_offset);

            o->oPosX = GRID_TO_POS(cmm_cursor_pos[0]); 
            o->oPosY = GRIDY_TO_POS(cmm_cursor_pos[1]); 
            o->oPosZ = GRID_TO_POS(cmm_cursor_pos[2]); 

            for (u8 i=0; i<6; i++) {
                vec3f_copy(&cmm_boundary_object[i]->oPosVec,&o->oPosVec);
            }
            cmm_boundary_object[0]->oPosY = GRIDY_TO_POS(0);
            cmm_boundary_object[1]->oPosY = GRIDY_TO_POS(32);
            cmm_boundary_object[2]->oPosX = GRID_TO_POS(GRID_MIN_COORD);
            cmm_boundary_object[3]->oPosX = GRID_TO_POS(GRID_MAX_COORD);
            cmm_boundary_object[4]->oPosZ = GRID_TO_POS(GRID_MIN_COORD);
            cmm_boundary_object[5]->oPosZ = GRID_TO_POS(GRID_MAX_COORD);

            if (cmm_place_mode == CMM_PM_OBJ) {
                if (cmm_object_types[cmm_id_selection].param_max != 0) {
                    s16 max = cmm_object_types[cmm_id_selection].param_max;
                    cmm_param_selection = (cmm_param_selection+max)%max;
                }
                vec3f_copy(&cmm_preview_object->oPosX,&o->oPosX);
                cmm_preview_object->oPosY += cmm_object_types[cmm_id_selection].y_offset - TILE_SIZE/2;
                obj_scale(cmm_preview_object, cmm_object_types[cmm_id_selection].scale);
                cmm_preview_object->header.gfx.sharedChild =  gLoadedGraphNodes[cmm_object_types[cmm_id_selection].model_id];
                cmm_preview_object->oFaceAngleYaw = cmm_rot_selection*0x4000;
                if (cmm_object_types[cmm_id_selection].billboarded) {
                    cmm_preview_object->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
                } else {
                    cmm_preview_object->header.gfx.node.flags &= ~GRAPH_RENDER_BILLBOARD;
                }
                if (cmm_object_types[cmm_id_selection].anim) {
                    cmm_preview_object->oAnimations = cmm_object_types[cmm_id_selection].anim;
                    super_cum_working(cmm_preview_object,0);
                }
                if (cmm_object_types[cmm_id_selection].disp_func) {
                    (cmm_object_types[cmm_id_selection].disp_func)(cmm_preview_object,cmm_param_selection);
                }
            } else {
                cmm_preview_object->header.gfx.sharedChild =  gLoadedGraphNodes[MODEL_NONE];
            }
            if (cmm_place_mode == CMM_PM_TILE) {
                if (cmm_tile_types[cmm_id_selection].terrain) {
                    if (gPlayer1Controller->buttonPressed & L_JPAD) {
                        cmm_mat_selection --;
                    }
                    if (gPlayer1Controller->buttonPressed & R_JPAD) {
                        cmm_mat_selection ++;
                    }
                }
                cmm_mat_selection = (cmm_mat_selection+NUM_MATERIALS_PER_THEME)%NUM_MATERIALS_PER_THEME;
            }

            if (!cmm_ui_do_render) {
                o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            } else {
                o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            }
        break;
        case 2://PLAY MODE

        break;
        case 3: //MAKE MODE TOOLBOX
            //TOOLBOX CONTROLS
            if (joystick != 0) {
                switch((joystick-1)%4) {
                    case 0:
                        cmm_toolbox_index--;
                    break;
                    case 1:
                        cmm_toolbox_index+=9;
                    break;
                    case 2:
                        cmm_toolbox_index++;
                    break;
                    case 3:
                        cmm_toolbox_index-=9;
                    break;
                }
            }
            cmm_toolbox_index = (cmm_toolbox_index+sizeof(cmm_toolbox))%sizeof(cmm_toolbox);

            //TOOLBAR CONTROLS
            if (gPlayer1Controller->buttonPressed & L_TRIG) {
                cmm_ui_index--;
            }
            if (gPlayer1Controller->buttonPressed & R_TRIG) {
                cmm_ui_index++;
            }
            cmm_id_selection = cmm_ui_buttons[cmm_ui_bar[cmm_ui_index]].id;
            cmm_place_mode = cmm_ui_buttons[cmm_ui_bar[cmm_ui_index]].placeMode;
            cmm_ui_index = (cmm_ui_index+6)%6;

            //PRESS A TO MOVE FROM TOOLBOX TO TOOLBAR
            if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                //You can not put a blank button into the toolbox
                if ( cmm_toolbox[cmm_toolbox_index] != CMM_BUTTON_BLANK) {
                    cmm_param_selection = 0;
                    cmm_ui_bar[cmm_ui_index] = cmm_toolbox[cmm_toolbox_index];
                } else {
                    //error sound
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
            }

            if (gPlayer1Controller->buttonPressed & (START_BUTTON|B_BUTTON)) {
                o->oAction = 1;
                cmm_menu_state = CMM_MAKE_MAIN;
            }
        break;
        case 4: //settings
            if (joystick != 0) {
                switch((joystick-1)%4) {
                    case 0:
                        (*cmm_settings_buttons[cmm_settings_index].value) += cmm_settings_buttons[cmm_settings_index].size-1;
                        (*cmm_settings_buttons[cmm_settings_index].value) %= cmm_settings_buttons[cmm_settings_index].size;
                        cmm_settings_index_changed = TRUE;
                    break;
                    case 1:
                        cmm_settings_index++;
                    break;
                    case 2:
                        (*cmm_settings_buttons[cmm_settings_index].value) ++;
                        (*cmm_settings_buttons[cmm_settings_index].value) %= cmm_settings_buttons[cmm_settings_index].size;
                        cmm_settings_index_changed = TRUE;
                    break;
                    case 3:
                        cmm_settings_index+=SETTINGS_SIZE-1;
                    break;
                }
            }
            cmm_settings_index %= SETTINGS_SIZE;

            //hardcoded settings application
            if (cmm_settings_index_changed) {
                cmm_settings_index_changed = FALSE;
                switch(cmm_settings_index) {
                    case 4: //theme
                        generate_terrain_gfx();
                        cmm_settings_buttons[5].size = cmm_theme_table[cmm_lopt_theme].numFloors + 1;
                        if (cmm_lopt_plane > cmm_settings_buttons[5].size - 1) {
                            cmm_lopt_plane = cmm_settings_buttons[5].size - 1;
                        }
                    break;
                    case 3: //sky box
                        load_segment_decompress_skybox(0xA,cmm_skybox_table[cmm_lopt_bg*2],cmm_skybox_table[cmm_lopt_bg*2+1]);
                    break;
                    case 5://bottom floor
                        generate_terrain_gfx();
                    break;
                }
            }

            if (gPlayer1Controller->buttonPressed & (START_BUTTON|B_BUTTON)) {
                o->oAction = 1;
                cmm_menu_state = CMM_MAKE_MAIN;
            }
        break;
        case 5: //trajectory maker
            //START MOVE CURSOR
            
            if (joystick != 0) {
                switch(((joystick-1)+cmm_camera_rot_offset)%4) {
                    case 0:
                        cmm_cursor_pos[0]++;
                        cursor_did_move = TRUE;
                    break;
                    case 1:
                        cmm_cursor_pos[2]--;
                        cursor_did_move = TRUE;
                    break;
                    case 2:
                        cmm_cursor_pos[0]--;
                        cursor_did_move = TRUE;
                    break;
                    case 3:
                        cmm_cursor_pos[2]++;
                        cursor_did_move = TRUE;
                    break;
                }
            }

            if (gPlayer1Controller->buttonPressed & U_CBUTTONS) {
                cmm_cursor_pos[1]++;
                cursor_did_move = TRUE;
            }
            if (gPlayer1Controller->buttonPressed & D_CBUTTONS) {
                cmm_cursor_pos[1]--;
                cursor_did_move = TRUE;
            }
            if (gPlayer1Controller->buttonPressed & R_CBUTTONS) {
                cmm_camera_rot_offset++;
            }
            if (gPlayer1Controller->buttonPressed & L_CBUTTONS) {
                cmm_camera_rot_offset--;
            }
            cmm_camera_rot_offset = (cmm_camera_rot_offset % 4)+4;

            //camera zooming
            if (gPlayer1Controller->buttonPressed & U_JPAD) {
                cmm_camera_zoom_index--;
            }
            if (gPlayer1Controller->buttonPressed & D_JPAD) {
                cmm_camera_zoom_index++;
            }
            cmm_camera_zoom_index = (cmm_camera_zoom_index+5)%5;

            cmm_cursor_pos[0] = ((cmm_cursor_pos[0] - GRID_MIN_COORD + GRID_SIZE) % GRID_SIZE) + GRID_MIN_COORD;
            cmm_cursor_pos[2] = ((cmm_cursor_pos[2] - GRID_MIN_COORD + GRID_SIZE) % GRID_SIZE) + GRID_MIN_COORD;
            cmm_cursor_pos[1]=(cmm_cursor_pos[1]+32)%32;
            //END MOVE CURSOR

            cmm_camera_foc[0] = lerp(cmm_camera_foc[0], GRID_TO_POS(cmm_cursor_pos[0]), 0.2f);
            cmm_camera_foc[1] = lerp(cmm_camera_foc[1], GRIDY_TO_POS(cmm_cursor_pos[1]), 0.2f);
            cmm_camera_foc[2] = lerp(cmm_camera_foc[2], GRID_TO_POS(cmm_cursor_pos[2]), 0.2f);

            vec3f_copy(&cmm_camera_pos,&cmm_camera_foc);
            vec3f_add(&cmm_camera_pos,&cam_pos_offset);

            o->oPosX = GRID_TO_POS(cmm_cursor_pos[0]); 
            o->oPosY = GRIDY_TO_POS(cmm_cursor_pos[1]); 
            o->oPosZ = GRID_TO_POS(cmm_cursor_pos[2]);

            if (o->oTimer == 0) {
                cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index*4 + 0] = cmm_trajectory_edit_index;
                cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index*4 + 1] = o->oPosX;
                cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index*4 + 2] = o->oPosY;
                cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index*4 + 3] = o->oPosZ;
                cmm_trajectory_edit_index++; 
            } else {
                if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                    cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index*4 + 0] = cmm_trajectory_edit_index;
                    cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index*4 + 1] = o->oPosX;
                    cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index*4 + 2] = o->oPosY;
                    cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index*4 + 3] = o->oPosZ;
                    cmm_trajectory_edit_index++;
                    generate_path_gfx();
                }
            }

            if ((gPlayer1Controller->buttonPressed & START_BUTTON)||(cmm_trajectory_edit_index == 39)) {
                cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index*4 + 0] = -1;
                o->oAction = 1;
                cmm_menu_state = CMM_MAKE_MAIN;
                generate_path_gfx();
            }
        break;
    }
}

#include "src/game/cursed_mirror_maker_menu.inc.c"
