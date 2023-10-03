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
#include "geo_misc.h"

#include "libcart/include/cart.h"
#include "libcart/ff/ff.h"

extern void super_cum_working(struct Object *obj, s32 animIndex);

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
Gfx *cmm_terrain_gfx_tp;
Gfx *cmm_trajectory_gfx;
Vtx cmm_terrain_vtx[CMM_VTX_SIZE];
Vtx *cmm_trajectory_vtx;

u32 cmm_gfx_total = 0;
u32 cmm_vtx_total = 0;

struct cmm_tile cmm_tile_data[CMM_TILE_POOL_SIZE];
struct cmm_obj cmm_object_data[CMM_MAX_OBJS];
u16 cmm_tile_data_indices[NUM_MATERIALS_PER_THEME + 5] = {0};
u16 cmm_tile_count = 0;
u16 cmm_object_count = 0;
u16 cmm_building_collision = FALSE; // 0 = building gfx, 1 = building collision

struct Object *cmm_preview_object;
struct Object *cmm_boundary_object[6]; //one for each side

Trajectory cmm_trajectory_list[CMM_MAX_TRAJECTORIES][CMM_TRAJECTORY_LENGTH][4];
u16 cmm_trajectory_edit_index = 0;
u8 cmm_trajectory_to_edit = 0;
u8 cmm_trajectories_used = 0;
u8 cmm_txt_recording[] = {TXT_RECORDING};

Vtx *cmm_curr_vtx;
Gfx *cmm_curr_gfx;
u16 cmm_gfx_index;

u8 cmm_use_alt_uvs = FALSE;
u8 cmm_render_flip_normals = FALSE;
u8 cmm_growth_render_type = 0;
u8 cmm_curr_mat_has_topside = FALSE;

TerrainData cmm_curr_coltype = SURFACE_DEFAULT;

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
u8 cmm_lopt_size = 0;
u8 cmm_lopt_template = 0;

//UI
u8 cmm_menu_state = CMM_MAKE_MAIN;
s8 cmm_ui_index = 0;
s8 cmm_toolbox_index = 0;
u8 cmm_ui_do_render = TRUE;
u8 cmm_do_save = FALSE;

char *cmm_error_message = NULL;
u16 cmm_error_timer = 0;
f32 cmm_error_vels[3];

struct cmm_level_save cmm_save;

u8 cmm_settings_index = 0;
u8 cmm_settings_index_changed = FALSE;

u8 cmm_num_vertices_cached = 0;
u8 cmm_num_tris_cached = 0;
u8 cmm_cached_tris[16][3];

void play_place_sound(u32 soundBits) {
    play_sound(soundBits, gGlobalSoundSource);
}

void df_badge(struct Object * obj, int param) {
    obj->oBehParams2ndByte = param;
}

void df_reds_marker(struct Object * obj, UNUSED int param) {
    obj->oFaceAnglePitch = 0x4000;
    vec3_set(obj->header.gfx.scale, 1.5f, 1.5f, 0.75f);
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
        case 0:
            obj->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_KINGBOMB_MAKER];
            obj->oAnimations = (struct Animation **)king_bobomb_seg5_anims_0500FE30;
            super_cum_working(obj,0);
            obj_scale(obj,1.0f);
            break;
        case 1:
            obj->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_WHOMP_MAKER];
            obj->oAnimations = (struct Animation **)whomp_seg6_anims_06020A04;
            super_cum_working(obj,0);
            obj_scale(obj,2.0f);
            break;
        case 3:
            obj->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_WIGGLER_HEAD];
            obj->oAnimations = (struct Animation **)wiggler_seg5_anims_0500EC8C;
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

void cmm_show_error_message(char *message) {
    if ((message != cmm_error_message) || (cmm_error_timer < 30)) {
        cmm_error_message = message;
        cmm_error_timer = 120;
        cmm_error_vels[0] = 280;
        cmm_error_vels[1] = 0;
        cmm_error_vels[2] = 0;
    } else {
        if (cmm_error_timer < 90) cmm_error_timer = 90;
    }
    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
}

void reset_play_state(void) {
    cmm_play_stars = 0;
    cmm_play_stars_bitfield = 0;
    cmm_play_badge_bitfield = 0;
}

u8 cmm_grid_min = 0;
u8 cmm_grid_size = 64;

u32 coords_in_range(s8 pos[3]) {
    if (pos[0] < cmm_grid_min || pos[0] > cmm_grid_min + cmm_grid_size - 1) return FALSE;
    if (pos[1] < 0 || pos[1] > 31) return FALSE;
    if (pos[2] < cmm_grid_min || pos[2] > cmm_grid_min + cmm_grid_size - 1) return FALSE;
    return TRUE;
}

s32 tile_sanity_check(void) {
    if (cmm_tile_count >= CMM_TILE_POOL_SIZE) {
        cmm_show_error_message("Tile limit reached! (max 10,000)");
        return FALSE;
    }
    if (cmm_vtx_total >= CMM_VTX_SIZE - 30) {
        cmm_show_error_message("Vertex limit reached! (max 25,000)");
        return FALSE;
    }
    if (cmm_gfx_total >= CMM_GFX_SIZE - 30) {
        cmm_show_error_message("Graphics pool is full!");
        return FALSE;
    }

    return TRUE;
}

s32 object_sanity_check(void) {
    if (cmm_object_count >= CMM_MAX_OBJS) {
        cmm_show_error_message("Object limit reached! (max 512)");
        return FALSE;
    }

    if (cmm_object_place_types[cmm_id_selection].useTrajectory) {
        if (cmm_trajectories_used >= CMM_MAX_TRAJECTORIES) {
            cmm_show_error_message("Trajectory limit reached! (max 20)");
            return FALSE;
        }
    }

    if (cmm_object_place_types[cmm_id_selection].hasStar) {
        // Count stars
        u8 numStars;
        for (u32 i = 0; i < cmm_object_count; i++) {
            if (cmm_object_place_types[cmm_object_data[i].type].hasStar) {
                numStars++;
            }
        }
        if (numStars >= 32) {
            cmm_show_error_message("Star limit reached! (max 32)");
            return FALSE;
        }
    }

    if (cmm_id_selection == OBJECT_TYPE_RCS) {
        for (u32 i = 0; i < cmm_object_count; i++) {
            if (cmm_object_data[i].type == OBJECT_TYPE_RCS) {
                cmm_show_error_message("Red Coin Star already placed!");
                return FALSE;
            }
        }
    }

    return TRUE;
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
    if (tileType == -1 || !cmm_tile_terrains[tileType]) return CMM_FACESHAPE_EMPTY;

    u8 rot = get_grid_tile(pos)->rot;
    dir = ROTATE_DIRECTION(dir,((4-rot) % 4)) ^ 1;

    struct cmm_terrain *terrain = cmm_tile_terrains[tileType];
    for (u32 i = 0; i < terrain->numQuads; i++) {
        struct cmm_terrain_quad *quad = &terrain->quads[i];
        if (quad->faceDir == dir) {
            return quad->faceshape;
        }
    }
    for (u32 i = 0; i < terrain->numTris; i++) {
        struct cmm_terrain_tri *tri = &terrain->tris[i];
        if (tri->faceDir == dir) {
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

s32 should_cull(s8 pos[3], s32 direction, s32 faceshape, s32 rot) {
    if (faceshape == CMM_FACESHAPE_EMPTY) return FALSE;
    direction = ROTATE_DIRECTION(direction, rot);

    s8 newpos[3];
    vec3_sum(newpos, pos, cullOffsetLUT[direction]);
    if (!coords_in_range(newpos)) return TRUE;
    s32 tileType = get_grid_tile(newpos)->type - 1;
    switch(tileType) {
        case TILE_TYPE_CULL:
            return TRUE;
        case TILE_TYPE_TROLL:
            if (cmm_building_collision) return FALSE;
            break;
    }

    s32 otherMat = get_grid_tile(newpos)->mat;
    if (MATERIAL(otherMat).type >= MAT_CUTOUT) {
        s32 curMat = get_grid_tile(pos)->mat;
        if (curMat != otherMat) return FALSE;
    }

    s32 otherFaceshape = get_faceshape(newpos, direction);

    if (otherFaceshape == CMM_FACESHAPE_EMPTY) return FALSE;
    if (otherFaceshape == CMM_FACESHAPE_FULL) return TRUE;
    if (faceshape == CMM_FACESHAPE_FULL) return FALSE;
    if (faceshape == CMM_FACESHAPE_TOPTRI) {
        if (otherFaceshape == CMM_FACESHAPE_TOPTRI) {
            u8 otherrot = get_grid_tile(newpos)->rot;
            return (otherrot == rot);
        } else return FALSE;
    }
    if (faceshape == CMM_FACESHAPE_BOTTOMSLAB || faceshape == CMM_FACESHAPE_TOPSLAB) {
        return (otherFaceshape == faceshape);
    }
    return (faceshape == (otherFaceshape^1));
}

// Additional culling check for certain grass overhangs. Assumes should_cull has already failed.
s32 should_cull_topslab_check(s8 pos[3], s32 direction, s32 rot) {
    direction = ROTATE_DIRECTION(direction, rot);

    s8 newpos[3];
    vec3_sum(newpos, pos, cullOffsetLUT[direction]);
    //if (!coords_in_range(newpos)) return TRUE;

    s32 otherFaceshape = get_faceshape(newpos, direction);
    if (otherFaceshape == CMM_FACESHAPE_TOPSLAB) return TRUE;
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

void cache_tri(u8 v1, u8 v2, u8 v3) {
    cmm_cached_tris[cmm_num_tris_cached][0] = cmm_num_vertices_cached + v1;
    cmm_cached_tris[cmm_num_tris_cached][1] = cmm_num_vertices_cached + v2;
    cmm_cached_tris[cmm_num_tris_cached][2] = cmm_num_vertices_cached + v3;
    cmm_num_tris_cached++;
}

void display_cached_tris(void) {
    if (cmm_num_vertices_cached == 0) return;
    gSPVertex(&cmm_curr_gfx[cmm_gfx_index++], cmm_curr_vtx, cmm_num_vertices_cached, 0);
    u32 i = 0;
    while (i < cmm_num_tris_cached) {
        // odd number of triangles and last one left
        if ((cmm_num_tris_cached - i) == 1) {
            gSP1Triangle(&cmm_curr_gfx[cmm_gfx_index++], cmm_cached_tris[i][0], cmm_cached_tris[i][1], cmm_cached_tris[i][2], 0);
            i++;
        } else {
            gSP2Triangles(&cmm_curr_gfx[cmm_gfx_index++], cmm_cached_tris[i][0], cmm_cached_tris[i][1], cmm_cached_tris[i][2], 0, cmm_cached_tris[i+1][0], cmm_cached_tris[i+1][1], cmm_cached_tris[i+1][2], 0);
            i+=2;
        }
    }
    cmm_curr_vtx += cmm_num_vertices_cached;
    cmm_num_tris_cached = 0;
    cmm_num_vertices_cached = 0;
}

void check_cached_tris(void) {
    if (cmm_num_vertices_cached > 28) {
        display_cached_tris();
    }
}

void draw_dotted_line(s16 pos1[3], s16 pos2[3]) {
    s16 yaw = atan2s(pos2[2] - pos1[2], pos2[0] - pos1[0]);
    f32 length = sqrtf(sqr(pos2[0] - pos1[0]) + sqr(pos2[1] - pos1[1]) + sqr(pos2[2] - pos1[2]));

    make_vertex(cmm_curr_vtx, cmm_num_vertices_cached,     pos1[0] + 10*coss(yaw), pos1[1], pos1[2] - 10*sins(yaw), 0, 0, 0, 0, 0, 0xFF);
    make_vertex(cmm_curr_vtx, cmm_num_vertices_cached + 1, pos1[0] - 10*coss(yaw), pos1[1], pos1[2] + 10*sins(yaw), 0, 0, 0, 0, 0, 0xFF);
    make_vertex(cmm_curr_vtx, cmm_num_vertices_cached + 2, pos2[0] + 10*coss(yaw), pos2[1], pos2[2] - 10*sins(yaw), 0, length, 0, 0, 0, 0xFF);
    make_vertex(cmm_curr_vtx, cmm_num_vertices_cached + 3, pos2[0] - 10*coss(yaw), pos2[1], pos2[2] + 10*sins(yaw), 0, length, 0, 0, 0, 0xFF);

    cache_tri(0, 1, 2);
    cache_tri(1, 3, 2);
    cmm_num_vertices_cached += 4;
    check_cached_tris();

    make_vertex(cmm_curr_vtx, cmm_num_vertices_cached,     pos1[0], pos1[1] - 10, pos1[2], 0, 0, 0, 0, 0, 0xFF);
    make_vertex(cmm_curr_vtx, cmm_num_vertices_cached + 1, pos1[0], pos1[1] + 10, pos1[2], 0, 0, 0, 0, 0, 0xFF);
    make_vertex(cmm_curr_vtx, cmm_num_vertices_cached + 2, pos2[0], pos2[1] - 10, pos2[2], 0, length, 0, 0, 0, 0xFF);
    make_vertex(cmm_curr_vtx, cmm_num_vertices_cached + 3, pos2[0], pos2[1] + 10, pos2[2], 0, length, 0, 0, 0, 0xFF);

    cache_tri(0, 1, 2);
    cache_tri(1, 3, 2);
    cmm_num_vertices_cached += 4;
    check_cached_tris();
}

void generate_trajectory_gfx(void) {
    cmm_curr_gfx = cmm_trajectory_gfx;
    cmm_curr_vtx = cmm_trajectory_vtx;
    cmm_gfx_index = 0;

    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], mat_maker_MakerLineMat_layer1);

    for (u32 traj = 0; traj < cmm_trajectories_used; traj++) {
        Trajectory *curr_trajectory = cmm_trajectory_list[traj][0];
        u32 i = 0;
        s16 pos1[3], pos2[3];

        while (curr_trajectory[i*4 + 4] == i+1) {
            vec3_set(pos1, curr_trajectory[(i*4)+1], curr_trajectory[(i*4)+2], curr_trajectory[(i*4)+3]);
            vec3_set(pos2, curr_trajectory[(i*4)+5], curr_trajectory[(i*4)+6], curr_trajectory[(i*4)+7]);
            draw_dotted_line(pos1, pos2);
            i++;
        }
        if (traj == cmm_trajectory_to_edit && cmm_menu_state == CMM_MAKE_TRAJECTORY) {
            vec3_set(pos1, curr_trajectory[(i*4)+1], curr_trajectory[(i*4)+2], curr_trajectory[(i*4)+3]);
            vec3_set(pos2, GRID_TO_POS(cmm_cursor_pos[0]), GRIDY_TO_POS(cmm_cursor_pos[1]), GRID_TO_POS(cmm_cursor_pos[2]));
            draw_dotted_line(pos1, pos2);
        }
        display_cached_tris();
    }

    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], mat_revert_maker_MakerLineMat_layer1);
    gSPEndDisplayList(&cmm_curr_gfx[cmm_gfx_index]);
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

s32 render_get_normal_and_uvs(s8 v[3][3], u32 direction, u32 rot, u8 *uAxis, u8 *vAxis, s8 n[3]) {
    // Find normal
    Vec3f normal;
    find_vector_perpendicular_to_plane(normal, v[0], v[1], v[2]);
    vec3_normalize(normal);
    n[0] = normal[0] * 0x7F;
    n[1] = normal[1] * 0x7F;
    n[2] = normal[2] * 0x7F;
    // Find UVs
    direction = ROTATE_DIRECTION(direction, rot);
    switch (direction) {
        case CMM_DIRECTION_NEG_X: *uAxis = 2; *vAxis = 1; return TRUE;
        case CMM_DIRECTION_POS_X: *uAxis = 2; *vAxis = 1; return FALSE;
        case CMM_DIRECTION_DOWN: *uAxis = 2; *vAxis = 0; return TRUE;
        case CMM_DIRECTION_UP: *uAxis = 2; *vAxis = 0; return FALSE;
        case CMM_DIRECTION_NEG_Z: *uAxis = 0; *vAxis = 1; return FALSE;
        case CMM_DIRECTION_POS_Z: *uAxis = 0; *vAxis = 1; return TRUE;
    }
}

void render_quad(struct cmm_terrain_quad *quad, s8 pos[3], u32 rot) {
    s8 n[3];
    u8 uAxis, vAxis;

    s8 newVtx[4][3];
    cmm_transform_vtx_with_rot(newVtx, quad->vtx, 4, rot);
    s32 flipU = render_get_normal_and_uvs(newVtx, quad->faceDir, rot, &uAxis, &vAxis, n);

    for (u32 i = 0; i < 4; i++) {
        s16 u, v;
        if (cmm_use_alt_uvs && quad->altuvs) {
            u = 16 - (*quad->altuvs)[i][0];
            v = 16 - (*quad->altuvs)[i][1];
        } else {
            u = newVtx[i][uAxis];
            if (!flipU) u = 16 - u;
            v = 16 - newVtx[i][vAxis];
        }
        make_vertex(cmm_curr_vtx, cmm_num_vertices_cached + i,
            GRID_TO_POS(pos[0])  + ((newVtx[i][0] - 8) * 16),
            GRIDY_TO_POS(pos[1]) + ((newVtx[i][1] - 8) * 16),
            GRID_TO_POS(pos[2])  + ((newVtx[i][2] - 8) * 16),
            u * 64 - 16, v * 64 - 16,
            n[0], n[1], n[2], 0xFF);
    }
    
    if (cmm_render_flip_normals) {
        cache_tri(0, 2, 1);
        cache_tri(1, 2, 3);
    } else {
        cache_tri(0, 1, 2);
        cache_tri(1, 3, 2);
    }
    cmm_num_vertices_cached += 4;
    check_cached_tris();
}

void render_tri(struct cmm_terrain_tri *tri, s8 pos[3], u32 rot) {
    s8 n[3];
    u8 uAxis, vAxis;

    s8 newVtx[3][3];
    cmm_transform_vtx_with_rot(newVtx, tri->vtx, 3, rot);
    s32 flipU = render_get_normal_and_uvs(newVtx, tri->faceDir, rot, &uAxis, &vAxis, n);

    for (u32 i = 0; i < 3; i++) {
        s16 u, v;
        if (cmm_use_alt_uvs && tri->altuvs) {
            u = 16 - (*tri->altuvs)[i][0];
            v = 16 - (*tri->altuvs)[i][1];
        } else {
            u = newVtx[i][uAxis];
            if (!flipU) u = 16 - u;
            v = 16 - newVtx[i][vAxis];
        }
        make_vertex(cmm_curr_vtx, cmm_num_vertices_cached + i,
            GRID_TO_POS(pos[0]) + ((newVtx[i][0] - 8) * 16),
            GRIDY_TO_POS(pos[1])+ ((newVtx[i][1] - 8) * 16),
            GRID_TO_POS(pos[2]) + ((newVtx[i][2] - 8) * 16),
            u * 64 - 16, v * 64 - 16,
            n[0], n[1], n[2], 0xFF);
    }

    cache_tri(0, 1, 2);
    cmm_num_vertices_cached += 3;
    check_cached_tris();
}

// Create new static surface
extern struct Surface *alloc_surface(u32 dynamic);
extern void add_surface(struct Surface *surface, s32 dynamic);
void cmm_create_surface(TerrainData v1[3], TerrainData v2[3], TerrainData v3[3]) { 
    struct Surface *surface = alloc_surface(FALSE);

    vec3_copy(surface->vertex1, v1);
    vec3_copy(surface->vertex2, v2);
    vec3_copy(surface->vertex3, v3);

    s16 min,max;
    min_max_3s(v1[1], v2[1], v3[1], &min, &max);
    surface->lowerY = (min - SURFACE_VERTICAL_BUFFER);
    surface->upperY = (max + SURFACE_VERTICAL_BUFFER);

    surface->type = cmm_curr_coltype;
    add_surface(surface, FALSE);
};

extern TerrainData sVertexData[900];

TerrainData colVtxs[4][3];

void cmm_create_quad(struct cmm_terrain_quad *quad, s8 pos[3], u32 rot) {
    s8 newVtx[4][3];
    cmm_transform_vtx_with_rot(newVtx, quad->vtx, 4, rot);
    for (u32 k = 0; k < 4; k++) {
        colVtxs[k][0] = GRID_TO_POS(pos[0])  + ((newVtx[k][0] - 8) * (TILE_SIZE/16)),
        colVtxs[k][1] = GRIDY_TO_POS(pos[1]) + ((newVtx[k][1] - 8) * (TILE_SIZE/16)),
        colVtxs[k][2] = GRID_TO_POS(pos[2])  + ((newVtx[k][2] - 8) * (TILE_SIZE/16));
    }
    cmm_create_surface(colVtxs[0], colVtxs[1], colVtxs[2]);
    cmm_create_surface(colVtxs[1], colVtxs[3], colVtxs[2]);
}

void cmm_create_tri(struct cmm_terrain_tri *tri, s8 pos[3], u32 rot) {
    s8 newVtx[3][3];
    cmm_transform_vtx_with_rot(newVtx, tri->vtx, 3, rot);
    for (u32 k = 0; k < 3; k++) {
        colVtxs[k][0] = GRID_TO_POS(pos[0])  + ((newVtx[k][0] - 8) * (TILE_SIZE/16)),
        colVtxs[k][1] = GRIDY_TO_POS(pos[1]) + ((newVtx[k][1] - 8) * (TILE_SIZE/16)),
        colVtxs[k][2] = GRID_TO_POS(pos[2])  + ((newVtx[k][2] - 8) * (TILE_SIZE/16));
    }
    cmm_create_surface(colVtxs[0], colVtxs[1], colVtxs[2]);
}

void process_quad(s8 pos[3], struct cmm_terrain_quad *quad, u32 rot) {
    if (!cmm_building_collision)
        render_quad(quad, pos, rot);
    else
        cmm_create_quad(quad, pos, rot);
}

void process_tri(s8 pos[3], struct cmm_terrain_tri *tri, u32 rot) {
    if (!cmm_building_collision)
        render_tri(tri, pos, rot);
    else
        cmm_create_tri(tri, pos, rot);
}

u32 render_grass_side_normal(s8 abovePos[3], u32 dir) {
    u8 otherFaceshape = get_faceshape(abovePos, dir);
    switch (otherFaceshape) {
        case CMM_FACESHAPE_TRI_1:
        case CMM_FACESHAPE_TRI_2:
        case CMM_FACESHAPE_FULL:
        case CMM_FACESHAPE_BOTTOMSLAB:
            if (MATERIAL(get_grid_tile(abovePos)->mat).type >= MAT_CUTOUT)
                return TRUE;
            return FALSE;
    }
    return TRUE;
}


u32 should_render_grass_side(s8 pos[3], u32 direction, u32 faceshape, u32 rot, u32 grassType) {
    s8 newpos[3];
    vec3_set(newpos, pos[0], pos[1]+1, pos[2]);
    if (should_cull(pos, direction, faceshape, rot)) return FALSE;
    if (!coords_in_range(newpos)) return TRUE;
    u8 otherFaceshape;
    switch (grassType) {
        case CMM_GROWTH_UNDERSLOPE:
        case CMM_GROWTH_UNDERSLOPE_L:
            direction = grassType == CMM_GROWTH_UNDERSLOPE ? CMM_DIRECTION_POS_Z : CMM_DIRECTION_POS_X;
            // fallthrough
        case CMM_GROWTH_NORMAL_SIDE:
            // Shape of face of above block on same side
            if (MATERIAL(get_grid_tile(newpos)->mat).type >= MAT_CUTOUT)
                return TRUE;
            if (should_cull_topslab_check(pos, direction, rot)) return FALSE;
            otherFaceshape = get_faceshape(newpos, ROTATE_DIRECTION(direction, rot)^1);
            switch (otherFaceshape) {
                case CMM_FACESHAPE_TRI_1:
                case CMM_FACESHAPE_TRI_2:
                case CMM_FACESHAPE_FULL:
                case CMM_FACESHAPE_BOTTOMSLAB:
                    return FALSE;
            }
            return TRUE;
        case CMM_GROWTH_UNDERSLOPE_CORNER:
        // some very cursed logic here, this is solely for upside-down inside corners
            if (MATERIAL(get_grid_tile(newpos)->mat).type >= MAT_CUTOUT)
                return TRUE;
            u8 faceshape1 = get_faceshape(newpos, ROTATE_DIRECTION(CMM_DIRECTION_POS_Z, rot)^1);
            u8 faceshape2 = get_faceshape(newpos, ROTATE_DIRECTION(CMM_DIRECTION_POS_X, rot)^1);
            // this is basically just checking for if a normal slope corner is on top at the right angle
            if (faceshape1 == CMM_FACESHAPE_TRI_1 && faceshape2 == CMM_FACESHAPE_TRI_2)
                return FALSE;
            // don't display if either face on top of the inside corner is full
            return !((faceshape1 == CMM_FACESHAPE_FULL || faceshape1 == CMM_FACESHAPE_BOTTOMSLAB)
                || (faceshape2 == CMM_FACESHAPE_FULL || faceshape2 == CMM_FACESHAPE_BOTTOMSLAB));
            
        case CMM_GROWTH_UNCONDITIONAL:
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
            if (should_cull_topslab_check(newpos, direction, rot)) return TRUE;
            
            // Calculate effective rotation of face to print. very ugly
            u8 targetRot = 0;
            switch (direction) {
                case CMM_DIRECTION_POS_X:
                    targetRot = 1;
                    break;
                case CMM_DIRECTION_NEG_X:
                    targetRot = 3;
                    break;
                //case CMM_DIRECTION_POS_Z:
                    //targetRot = 0;
                    //break;
                case CMM_DIRECTION_NEG_Z:
                    targetRot = 2;
                    break;
            }
            targetRot = (targetRot + rot) % 4;

            s32 index;
            s32 isQuad;

            switch (otherFaceshape) {
                default:
                    return TRUE;
                // Face is full quad
                case CMM_FACESHAPE_FULL:
                    index = 0;
                    isQuad = TRUE;
                    break;
                case CMM_FACESHAPE_DOWNTRI_1:
                    index = 1;
                    isQuad = FALSE;
                    break;
                case CMM_FACESHAPE_DOWNTRI_2:
                    index = 2;
                    isQuad = FALSE;
                    break;
                case CMM_FACESHAPE_TOPSLAB:
                    index = 3;
                    isQuad = TRUE;
                    break;
            }

            s32 side = (grassType == CMM_GROWTH_SLOPE_SIDE_L ? 0 : 1);

            if (isQuad) {
                struct cmm_terrain_quad *quad = slope_decal_below_surfs[index];
                quad->altuvs = slope_decal_below_uvs[index][side];
                if (quad->altuvs != NULL) {
                    render_quad(quad, newpos, targetRot);
                }
            } else {
                struct cmm_terrain_tri *tri = slope_decal_below_surfs[index];
                tri->altuvs = slope_decal_below_uvs[index][side];
                if (tri->altuvs != NULL) {
                    render_tri(tri, newpos, targetRot);
                }
            }
            return TRUE;
        case CMM_GROWTH_DIAGONAL_SIDE:
            otherFaceshape = get_faceshape(newpos, CMM_DIRECTION_UP);
            if (otherFaceshape == CMM_FACESHAPE_FULL) return FALSE;
            if (otherFaceshape != CMM_FACESHAPE_TOPTRI) return TRUE;
            u8 otherrot = get_grid_tile(newpos)->rot;
            return (otherrot != rot);
    }
    return FALSE;
}

void process_quad_with_growth(s8 pos[3], struct cmm_terrain_quad *quad, u32 rot) {
    switch (cmm_growth_render_type) {
        case 0: // regular tex
            if (cmm_curr_mat_has_topside && (quad->growthType == CMM_GROWTH_FULL)) return;
            if (should_cull(pos, quad->faceDir, quad->faceshape, rot)) return;
            break;
        case 1: // grass top
            if (quad->growthType != CMM_GROWTH_FULL) return;
            if (should_cull(pos, quad->faceDir, quad->faceshape, rot)) return;
            break;
        case 2: // grass decal
            if (quad->growthType == CMM_GROWTH_FULL || quad->growthType == CMM_GROWTH_NONE) return;
            if (!should_render_grass_side(pos, quad->faceDir, quad->faceshape, rot, quad->growthType)) return;
            break;
    }
    process_quad(pos, quad, rot);
}

void process_tri_with_growth(s8 pos[3], struct cmm_terrain_tri *tri, u32 rot) {
    switch (cmm_growth_render_type) {
        case 0: // regular tex
            if (cmm_curr_mat_has_topside && (tri->growthType == CMM_GROWTH_FULL)) return;
            if (should_cull(pos, tri->faceDir, tri->faceshape, rot)) return;
            break;
        case 1: // grass top
            if (tri->growthType != CMM_GROWTH_FULL) return;
            if (should_cull(pos, tri->faceDir, tri->faceshape, rot)) return;
            break;
        case 2: // grass decal
            if (tri->growthType == CMM_GROWTH_FULL || tri->growthType == CMM_GROWTH_NONE) return;
            if (!should_render_grass_side(pos, tri->faceDir, tri->faceshape, rot, tri->growthType)) return;
            break;
    }
    process_tri(pos, tri, rot);
}

void process_tile(s8 pos[3], struct cmm_terrain *terrain, u32 rot) {
    for (u32 j = 0; j < terrain->numQuads; j++) {
        struct cmm_terrain_quad *quad = &terrain->quads[j];
        process_quad_with_growth(pos, quad, rot);
    }
    for (u32 j = 0; j < terrain->numTris; j++) {
        struct cmm_terrain_tri *tri = &terrain->tris[j];
        process_tri_with_growth(pos, tri, rot);
    }
}

// Find if specific tile of water is fullblock or shallow
u32 is_water_fullblock(s8 pos[3]) {
    s8 abovePos[3];
    vec3_set(abovePos, pos[0], pos[1]+1, pos[2]);
    if (!coords_in_range(abovePos)) return FALSE;
    // Full block if above block is water
    if (get_grid_tile(abovePos)->waterlogged) return TRUE;
    // Full block if waterlogging a block and it has a solid top face
    if ((get_grid_tile(pos)->type - 1) != TILE_TYPE_WATER) {
        if (get_faceshape(pos, CMM_DIRECTION_DOWN) == CMM_FACESHAPE_FULL) return TRUE;
    }
    // Full block if above block has solid bottom face
    if (get_faceshape(abovePos, CMM_DIRECTION_UP) == CMM_FACESHAPE_FULL) return TRUE;
    return FALSE;
}

// return type of render to use
// 0: cull
// 1: normal (low side)
// 2: full (full side)
// 3: top (thin top at side)
u32 get_water_side_render(s8 pos[3], u32 dir, u32 isFullblock) {
    s8 adjacentPos[3];
    vec3_sum(adjacentPos, pos, cullOffsetLUT[dir]);

    // Don't OoB cull the top face
    if (!coords_in_range(adjacentPos) && dir == CMM_DIRECTION_UP) return 1;

    if (cmm_building_collision) {
        if (get_grid_tile(adjacentPos)->waterlogged) return 0;
        return isFullblock ? 2 : 1;
    }

    // Apply normal side culling
    if (should_cull(pos, dir, CMM_FACESHAPE_FULL, 0)) return 0;

    if (get_grid_tile(adjacentPos)->waterlogged) {
        // Check if this is a full block, next to a non-full block.
        // If so, use special thin side
        if (dir != CMM_DIRECTION_UP && dir != CMM_DIRECTION_DOWN) {
            if (isFullblock && !is_water_fullblock(adjacentPos)) {
                return 3;
            }
        }
        // Full block next to full block so cull
        return 0;
    }

    // Check if the block that's waterlogged has a full face on the same side
    if (get_faceshape(pos, dir^1) == CMM_FACESHAPE_FULL) {
        return 0;
    }

    return isFullblock ? 2 : 1;
}

void render_water(s8 pos[3]) {
    u32 isFullblock = is_water_fullblock(pos);
    for (u32 j = 0; j < 6; j++) {
        u8 sideRender = get_water_side_render(pos, cmm_terrain_fullblock_quads[j].faceDir, isFullblock);
        if (sideRender != 0) {
            struct cmm_terrain_quad *quad = &cmm_terrain_water_quadlists[sideRender - 1][j];
            if (cmm_building_collision) {
                if (quad->faceDir == CMM_DIRECTION_UP) {
                    cmm_curr_coltype = SURFACE_NEW_WATER;
                } else if (quad->faceDir == CMM_DIRECTION_DOWN) {
                    cmm_curr_coltype = SURFACE_NEW_WATER_BOTTOM;
                } else {
                    continue;
                }
            }
            process_quad(pos, quad, 0);
        }
    }
}

void render_floor(void) {
    s16 vertex = 128 * cmm_grid_size;
    s16 uv = 256 * cmm_grid_size;
    make_vertex(cmm_curr_vtx, 0, vertex, 0, vertex, -uv, -uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 1, vertex, 0,      0,  uv, -uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 2,      0, 0, vertex, -uv,  uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 3,      0, 0,      0,  uv,  uv, 0x0, 0x7F, 0x0, 0xFF);

    make_vertex(cmm_curr_vtx, 4,       0, 0, vertex, -uv, -uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 5,       0, 0,      0,  uv, -uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 6, -vertex, 0, vertex, -uv,  uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 7, -vertex, 0,      0,  uv,  uv, 0x0, 0x7F, 0x0, 0xFF);

    make_vertex(cmm_curr_vtx, 8,  vertex, 0,       0, -uv, -uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 9,  vertex, 0, -vertex,  uv, -uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 10,      0, 0,       0, -uv,  uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 11,      0, 0, -vertex,  uv,  uv, 0x0, 0x7F, 0x0, 0xFF);

    make_vertex(cmm_curr_vtx, 12,       0, 0,       0, -uv, -uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 13,       0, 0, -vertex,  uv, -uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 14, -vertex, 0,       0, -uv,  uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 15, -vertex, 0, -vertex,  uv,  uv, 0x0, 0x7F, 0x0, 0xFF);

    gSPVertex(&cmm_curr_gfx[cmm_gfx_index++], cmm_curr_vtx, 16, 0);

    gSP2Triangles(&cmm_curr_gfx[cmm_gfx_index++], 0, 1, 2, 0, 1, 3, 2, 0);
    gSP2Triangles(&cmm_curr_gfx[cmm_gfx_index++], 4, 5, 6, 0, 5, 7, 6, 0);
    gSP2Triangles(&cmm_curr_gfx[cmm_gfx_index++], 8, 9, 10, 0, 9, 11, 10, 0);
    gSP2Triangles(&cmm_curr_gfx[cmm_gfx_index++], 12, 13, 14, 0, 13, 15, 14, 0);
    cmm_curr_vtx += 16;
}

#define FENCE_TILETYPE_INDEX (NUM_MATERIALS_PER_THEME)
#define WATER_TILETYPE_INDEX (NUM_MATERIALS_PER_THEME + 1)
#define CULL_TILETYPE_INDEX (NUM_MATERIALS_PER_THEME + 2)

u32 get_tiletype_index(u32 type, u32 mat) {
    switch (type) {
        case TILE_TYPE_FENCE:
            return FENCE_TILETYPE_INDEX;
        case TILE_TYPE_WATER:
            return WATER_TILETYPE_INDEX;
        case TILE_TYPE_CULL:
            return CULL_TILETYPE_INDEX;
        default:
            if (cmm_tile_terrains[type]) {
                return mat;
            }
    }
    return NUM_MATERIALS_PER_THEME + 3;
}


#define retroland_filter_on() if (cmm_lopt_theme == CMM_THEME_RETRO) gDPSetTextureFilter(&cmm_curr_gfx[cmm_gfx_index++], G_TF_POINT)
#define retroland_filter_off() if (cmm_lopt_theme == CMM_THEME_RETRO) gDPSetTextureFilter(&cmm_curr_gfx[cmm_gfx_index++], G_TF_BILERP)

// For render or collision specific code
#define PROC_COLLISION(statement) if (cmm_building_collision)  { statement; }
#define PROC_RENDER(statement)    if (!cmm_building_collision) { statement; }

void process_tiles(void) {
    u32 startIndex, endIndex;
    u8 tileType, rot;
    s8 pos[3];

    for (u32 mat = 0; mat < NUM_MATERIALS_PER_THEME; mat++) {
        cmm_growth_render_type = 0;

        PROC_COLLISION( cmm_curr_coltype = MATERIAL(mat).col; )
        PROC_RENDER( gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], MATERIAL(mat).gfx); )

        cmm_curr_mat_has_topside = HAS_TOPMAT(mat);

        startIndex = cmm_tile_data_indices[mat];
        endIndex = cmm_tile_data_indices[mat+1];
        for (u32 i = startIndex; i < endIndex; i++) {
            tileType = cmm_tile_data[i].type;
            PROC_COLLISION( if (tileType == TILE_TYPE_TROLL) continue; )
            rot = cmm_tile_data[i].rot;
            vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);

            process_tile(pos, cmm_tile_terrains[tileType], rot);
        }

        PROC_RENDER( display_cached_tris(); gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE); gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2); )
        
        if (cmm_curr_mat_has_topside) {
            // Only runs when rendering
            if (!cmm_building_collision && (SIDETEX(mat) != NULL)) {
                cmm_use_alt_uvs = TRUE;
                gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], SIDETEX(mat));
                cmm_growth_render_type = 2;
                for (u32 i = startIndex; i < endIndex; i++) {
                    tileType = cmm_tile_data[i].type;
                    rot = cmm_tile_data[i].rot;
                    vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);

                    process_tile(pos, cmm_tile_terrains[tileType], rot);
                }
                display_cached_tris();
                cmm_use_alt_uvs = FALSE;
                gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE);
                gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
            }

            PROC_COLLISION( cmm_curr_coltype = TOPMAT(mat).col; )
            PROC_RENDER( gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], TOPMAT(mat).gfx); )

            cmm_growth_render_type = 1;
            for (u32 i = startIndex; i < endIndex; i++) {
                tileType = cmm_tile_data[i].type;
                PROC_COLLISION( if (tileType == TILE_TYPE_TROLL) continue; )
                rot = cmm_tile_data[i].rot;
                vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);

                process_tile(pos, cmm_tile_terrains[tileType], rot);
            }
            PROC_RENDER( display_cached_tris(); gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE);)
        }
    }
}

void generate_terrain_gfx(void) {
    u8 tileType, rot;
    s8 pos[3];

    while (sCurrentDisplaySPTask != NULL) {
        osRecvMesg(&gGameVblankQueue, &gMainReceivedMesg, OS_MESG_BLOCK);
    }

    cmm_curr_gfx = cmm_terrain_gfx;
    cmm_curr_vtx = cmm_terrain_vtx;
    cmm_gfx_index = 0;
    cmm_building_collision = FALSE;

    cmm_use_alt_uvs = FALSE;
    cmm_render_flip_normals = FALSE;

    retroland_filter_on();

    // This does the funny virtuaplex effect
    for (u32 mat = 0; mat < NUM_MATERIALS_PER_THEME; mat++) {
        if (TILE_MATDEF(mat).mat == CMM_MAT_VP_SCREEN) {
            gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], GBL_c1(G_BL_CLR_MEM, G_BL_0, G_BL_CLR_MEM, G_BL_1) | GBL_c2(G_BL_CLR_MEM, G_BL_0, G_BL_CLR_MEM, G_BL_1), Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP | ZMODE_OPA);
            u32 startIndex = cmm_tile_data_indices[mat];
            u32 endIndex = cmm_tile_data_indices[mat+1];
            for (u32 i = startIndex; i < endIndex; i++) {
                tileType = cmm_tile_data[i].type;
                rot = cmm_tile_data[i].rot;
                vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
                process_tile(pos, cmm_tile_terrains[tileType], rot);
            }
            display_cached_tris();
            gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE);
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
        gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE);
    }

    // Fences

    u32 startIndex = cmm_tile_data_indices[FENCE_TILETYPE_INDEX];
    u32 endIndex = cmm_tile_data_indices[FENCE_TILETYPE_INDEX+1];
    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], FENCE_TEX());
    cmm_use_alt_uvs = TRUE;
    cmm_growth_render_type = 0;
    for (u32 i = startIndex; i < endIndex; i++) {
        s8 pos[3];
        vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
        process_tile(pos, &cmm_terrain_fence, cmm_tile_data[i].rot);
    }
    display_cached_tris();
    gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE);
    cmm_use_alt_uvs = FALSE;

    process_tiles();

    retroland_filter_off();
    gSPEndDisplayList(&cmm_curr_gfx[cmm_gfx_index++]);

    cmm_terrain_gfx_tp = &cmm_curr_gfx[cmm_gfx_index];
    retroland_filter_on();
    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], WATER_TEX());
    // Render water twice. This is so that all interior faces are rendered before all exterior faces,
    // to make the layering a little better.
    cmm_render_flip_normals = TRUE;
    for (u32 i = 0; i < cmm_tile_count; i++) {
        if (cmm_tile_data[i].waterlogged) {
            vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
            render_water(pos);
        }
    }
    cmm_render_flip_normals = FALSE;
    for (u32 i = 0; i < cmm_tile_count; i++) {
        if (cmm_tile_data[i].waterlogged) {
            vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
            render_water(pos);
        }
    }
    display_cached_tris();
    retroland_filter_off();
    gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE);
    gSPEndDisplayList(&cmm_curr_gfx[cmm_gfx_index++]);

    cmm_trajectory_gfx = &cmm_curr_gfx[cmm_gfx_index];
    cmm_trajectory_vtx = cmm_curr_vtx;

    generate_trajectory_gfx();

    cmm_vtx_total = cmm_curr_vtx - cmm_terrain_vtx;
    cmm_gfx_total = (cmm_curr_gfx + cmm_gfx_index) - cmm_terrain_gfx;
};

Gfx preview_gfx[32];
Mtx preview_mtx[2];
Vtx preview_vtx[64];

extern void geo_append_display_list(void *displayList, s32 layer);

Gfx *ccm_append(s32 callContext, UNUSED struct GraphNode *node, UNUSED Mat4 mtx) {
    if (callContext == GEO_CONTEXT_RENDER) {
        geo_append_display_list(cmm_terrain_gfx, LAYER_OPAQUE);
        geo_append_display_list(cmm_terrain_gfx_tp, LAYER_TRANSPARENT);

        //this extra append is for the editor tile preview
        if (cmm_mode == CMM_MODE_MAKE) {
            geo_append_display_list(cmm_trajectory_gfx, LAYER_OPAQUE);
            //generate dl
            if (cmm_place_mode == CMM_PM_OBJ || cmm_place_mode == CMM_PM_NONE) return NULL;
            u8 preview_mtx_index = 0;
            cmm_curr_gfx = preview_gfx;
            cmm_curr_vtx = preview_vtx;
            cmm_gfx_index = 0;

            cmm_building_collision = FALSE;
            cmm_growth_render_type = 0;

            retroland_filter_on();

            if (cmm_place_mode == CMM_PM_WATER) {
                gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], WATER_TEX());
                gSPGeometryMode(&cmm_curr_gfx[cmm_gfx_index++], 0, G_CULL_BACK);
                render_water(cmm_cursor_pos);
                display_cached_tris();
                retroland_filter_off();
                gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE);
                gSPEndDisplayList(&cmm_curr_gfx[cmm_gfx_index]);

                geo_append_display_list(cmm_curr_gfx, LAYER_TRANSPARENT);
                return NULL;
            }

            struct cmm_terrain *terrain = cmm_tile_terrains[cmm_id_selection];
            
            if (cmm_id_selection == TILE_TYPE_FENCE) {
                gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], FENCE_TEX());
                cmm_use_alt_uvs = TRUE;
                process_tile(cmm_cursor_pos, &cmm_terrain_fence, cmm_rot_selection);
                display_cached_tris();
                cmm_use_alt_uvs = FALSE;
            } else if (terrain) {
                cmm_curr_mat_has_topside = HAS_TOPMAT(cmm_mat_selection);
                if (TILE_MATDEF(cmm_mat_selection).mat == CMM_MAT_VP_SCREEN) {
                    gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], GBL_c1(G_BL_CLR_MEM, G_BL_0, G_BL_CLR_MEM, G_BL_1) | GBL_c2(G_BL_CLR_MEM, G_BL_0, G_BL_CLR_MEM, G_BL_1), Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP | ZMODE_OPA);
                    process_tile(cmm_cursor_pos, terrain, cmm_rot_selection);
                    display_cached_tris();
                    gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE);
                    gSPEndDisplayList(&cmm_curr_gfx[cmm_gfx_index]);
                    geo_append_display_list(cmm_curr_gfx, LAYER_FORCE);

                    cmm_curr_gfx += cmm_gfx_index;
                    cmm_gfx_index = 0;
                }
                gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], MATERIAL(cmm_mat_selection).gfx);
                process_tile(cmm_cursor_pos, terrain, cmm_rot_selection);
                display_cached_tris();
                gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE);

                if (cmm_curr_mat_has_topside) {
                    Gfx *sidetex = SIDETEX(cmm_mat_selection);
                    if (sidetex != NULL) {
                        cmm_use_alt_uvs = TRUE;
                        cmm_growth_render_type = 2;

                        gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], sidetex);
                        process_tile(cmm_cursor_pos, terrain, cmm_rot_selection);
                        display_cached_tris();
                        cmm_use_alt_uvs = FALSE;
                    }
                    cmm_growth_render_type = 1;

                    gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE);
                    gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
                    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], TOPMAT(cmm_mat_selection).gfx);
                    process_tile(cmm_cursor_pos, terrain, cmm_rot_selection);
                    display_cached_tris();
                }

            } else if (cmm_id_selection == TILE_TYPE_CULL) {
                guTranslate(&preview_mtx[preview_mtx_index], GRID_TO_POS(cmm_cursor_pos[0]), GRIDY_TO_POS(cmm_cursor_pos[1]), GRID_TO_POS(cmm_cursor_pos[2]));
                preview_mtx_index++;
                guRotate(&preview_mtx[preview_mtx_index],90.0f*cmm_rot_selection,0.0f,1.0f,0.0f);
                gSPMatrix(&cmm_curr_gfx[cmm_gfx_index++], VIRTUAL_TO_PHYSICAL(&preview_mtx[preview_mtx_index-1]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
                gSPMatrix(&cmm_curr_gfx[cmm_gfx_index++], VIRTUAL_TO_PHYSICAL(&preview_mtx[preview_mtx_index]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
                //gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], MATERIAL(cmm_param_selection).gfx);
                gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], &cull_cull_mesh);
                gSPPopMatrix(&cmm_curr_gfx[cmm_gfx_index++], G_MTX_MODELVIEW);
                preview_mtx_index++;
            }

            gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE);
            gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
            retroland_filter_off();
            gSPEndDisplayList(&cmm_curr_gfx[cmm_gfx_index]);

            geo_append_display_list(cmm_curr_gfx, LAYER_OPAQUE);
        }
    }
    return NULL;
}

TerrainData floorVtxs[4][3] = {
    {-1, 0, 1},
    {1, 0, 1},
    {-1, 0, -1},
    {1, 0, -1},
};

void generate_terrain_collision(void) {
    s16 i;
    gCurrStaticSurfacePool = main_pool_alloc(main_pool_available() - 0x10, MEMORY_POOL_LEFT);
    gCurrStaticSurfacePoolEnd = gCurrStaticSurfacePool;
    gSurfaceNodesAllocated = gNumStaticSurfaceNodes;
    gSurfacesAllocated = gNumStaticSurfaces;
    cmm_building_collision = TRUE;
    //the first thing to do is to generate the plane... there's only 2 types so it's a hardcoded switchcase
    TerrainData floorY;

    if (cmm_lopt_plane == 0) {
        floorY = -2500;
        cmm_curr_coltype = SURFACE_DEATH_PLANE;
    } else {
        floorY = 0;
        u8 mat = cmm_theme_table[cmm_lopt_theme].floors[cmm_lopt_plane - 1];
        if (HAS_TOPMAT(mat)) {
            cmm_curr_coltype = TOPMAT(mat).col;
        } else {
            cmm_curr_coltype = MATERIAL(mat).col;
        }
    }
    TerrainData newVtxs[4][3];
    for (u32 i = 0; i < 4; i++) {
        newVtxs[i][1] = floorY;
        newVtxs[i][0] = floorVtxs[i][0] * cmm_grid_size * 128;
        newVtxs[i][2] = floorVtxs[i][2] * cmm_grid_size * 128;

    }
    cmm_create_surface(newVtxs[0], newVtxs[1], newVtxs[2]);
    cmm_create_surface(newVtxs[1], newVtxs[3], newVtxs[2]);

    process_tiles();

    cmm_curr_coltype = SURFACE_NO_CAM_COLLISION;
    for (i = cmm_tile_data_indices[FENCE_TILETYPE_INDEX]; i < cmm_tile_data_indices[FENCE_TILETYPE_INDEX+1]; i++) {
        s8 pos[3];
        vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
        process_tile(pos, &cmm_terrain_fence_col, cmm_tile_data[i].rot);
    }

    for (i = 0; i < cmm_tile_count; i++) {
        if (cmm_tile_data[i].waterlogged) {
            s8 pos[3];
            vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
            render_water(pos);
        }
    }

    cmm_building_collision = FALSE;
    u32 surfacePoolData = (uintptr_t)gCurrStaticSurfacePoolEnd - (uintptr_t)gCurrStaticSurfacePool;
    gTotalStaticSurfaceData += surfacePoolData;
    main_pool_realloc(gCurrStaticSurfacePool, surfacePoolData);

    gNumStaticSurfaceNodes = gSurfaceNodesAllocated;
    gNumStaticSurfaces = gSurfacesAllocated;
}

void generate_object_preview(void) {
    struct Object *preview_object;
    u32 i;

    preview_object = cur_obj_nearest_object_with_behavior(bhvStaticObject);
    while(preview_object) {
        unload_object(preview_object);
        preview_object = cur_obj_nearest_object_with_behavior(bhvStaticObject);
    }

    for(i=0;i<cmm_object_count;i++){
        if (gFreeObjectList.next == NULL) break;
        struct cmm_object_info *info = cmm_object_place_types[cmm_object_data[i].type].info;
        preview_object = spawn_object(gMarioObject, info->model_id ,bhvStaticObject);
        preview_object->oPosX = GRID_TO_POS(cmm_object_data[i].x);
        preview_object->oPosY = GRIDY_TO_POS(cmm_object_data[i].y) - TILE_SIZE/2 + info->y_offset;
        preview_object->oPosZ = GRID_TO_POS(cmm_object_data[i].z);
        preview_object->oFaceAngleYaw = cmm_object_data[i].rot*0x4000;
        obj_scale(preview_object, info->scale);
        if (info->billboarded) {
            preview_object->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
        }
        if (info->anim) {
            preview_object->oAnimations = (struct Animation **)info->anim;
            super_cum_working(preview_object,0);
            preview_object->header.gfx.animInfo.animAccel = 0.0f;
        }
        if (info->disp_func) {
            (info->disp_func)(preview_object,cmm_object_data[i].param);
        }
    }
}

void generate_objects_to_level(void) {
    struct Object *obj;
    u32 i;
    cmm_play_stars_max = 0;
    for(i=0;i<cmm_object_count;i++){
        struct cmm_object_info *info = cmm_object_place_types[cmm_object_data[i].type].info;

        obj = spawn_object(gMarioObject, info->model_id, info->behavior);

        obj->oPosX = GRID_TO_POS(cmm_object_data[i].x);
        obj->oPosY = GRIDY_TO_POS(cmm_object_data[i].y) - TILE_SIZE/2 + info->y_offset;
        obj->oPosZ = GRID_TO_POS(cmm_object_data[i].z);
        obj->oFaceAngleYaw = cmm_object_data[i].rot*0x4000;
        obj->oMoveAngleYaw = cmm_object_data[i].rot*0x4000;
        obj->oBehParams2ndByte = cmm_object_data[i].param;

        //assign star ids
        if (cmm_object_place_types[cmm_object_data[i].type].hasStar) {
            if (cmm_play_stars_max < 32) {
                obj->oBehParams = ((cmm_play_stars_max << 24)|(o->oBehParams2ndByte << 16));
                cmm_play_stars_max++;
            }
        }
    }
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

u32 is_cull_marker_useless(s8 pos[3]) {
    s8 adjacentPos[3];

    for (u8 dir = 0; dir < 6; dir++) {
        vec3_sum(adjacentPos, pos, cullOffsetLUT[dir]);
        u8 tileType = get_grid_tile(adjacentPos)->type;
        if (tileType != 0 && (tileType != TILE_TYPE_CULL + 1)) {
            return FALSE;
        }
    }

    return TRUE;
}

void place_tile(s8 pos[3]) {
    u8 waterlogged = FALSE;
    // Placing tile upon water automatically waterlogs new tile
    // But delete the old tile first
    if ((get_grid_tile(pos)->type - 1) == TILE_TYPE_WATER) {
        waterlogged = TRUE;
        for (u32 i = 0; i < cmm_tile_count; i++) {
        //search for tile to delete
            if ((cmm_tile_data[i].x == pos[0])&&(cmm_tile_data[i].y == pos[1])&&(cmm_tile_data[i].z == pos[2])) {
                cmm_tile_count--;
                for (u32 j = WATER_TILETYPE_INDEX + 1; j < ARRAY_COUNT(cmm_tile_data_indices); j++) {
                    cmm_tile_data_indices[j]--;
                }
                for (u32 j = i; j < cmm_tile_count; j++) {
                    cmm_tile_data[j] = cmm_tile_data[j+1];
                }
                break;
            }
        }
    }

    if (cmm_id_selection == TILE_TYPE_BLOCK) {
        waterlogged = FALSE;
    }
    // If placing a cull marker, check that its actually next to a tile
    if (cmm_id_selection == TILE_TYPE_CULL && is_cull_marker_useless(pos)) {
        return;
    }

    if (cmm_tile_terrains[cmm_id_selection] != NULL) {
        TerrainData coltype;
        if (HAS_TOPMAT(cmm_mat_selection)) {
            coltype = TOPMAT(cmm_mat_selection).col;
        } else {
            coltype = MATERIAL(cmm_mat_selection).col;
        }
        if (coltype == SURFACE_BURNING) {
            play_place_sound(SOUND_GENERAL_LOUD_BUBBLE | SOUND_VIBRATO);
        } else {
            play_place_sound(SOUND_ACTION_TERRAIN_STEP + get_terrain_sound_addend(coltype));
        }
    } else {
        switch (cmm_id_selection ) {
            case TILE_TYPE_FENCE:
                if (cmm_lopt_theme == CMM_THEME_RHR) {
                    play_place_sound(SOUND_ACTION_TERRAIN_STEP + (SOUND_TERRAIN_STONE << 16));
                } else {
                    play_place_sound(SOUND_ACTION_TERRAIN_STEP + (SOUND_TERRAIN_SPOOKY << 16));
                }
                break;
        }
    }

    place_terrain_data(pos, cmm_id_selection, cmm_rot_selection, cmm_mat_selection);
    get_grid_tile(pos)->waterlogged = waterlogged;
    u32 index = get_tiletype_index(cmm_id_selection, cmm_mat_selection);
    u32 newtileIndex = shift_tile_data_indices(index);

    cmm_tile_data[newtileIndex].x = pos[0];
    cmm_tile_data[newtileIndex].y = pos[1];
    cmm_tile_data[newtileIndex].z = pos[2];
    cmm_tile_data[newtileIndex].type = cmm_id_selection;
    cmm_tile_data[newtileIndex].mat = cmm_mat_selection;
    cmm_tile_data[newtileIndex].rot = cmm_rot_selection;
    cmm_tile_data[newtileIndex].waterlogged = waterlogged;
    cmm_tile_count++;
}

void place_water(s8 pos[3]) {
    struct cmm_grid_obj *tile = get_grid_tile(pos);
    s8 tileType = tile->type - 1;
    if (tile->waterlogged) return;

    if (tile->type != 0) {
        // cant waterlog a full block
        if (tileType == TILE_TYPE_BLOCK) {
            return;
        }
        play_place_sound(SOUND_ACTION_TERRAIN_STEP + (SOUND_TERRAIN_WATER << 16));
        tile->waterlogged = TRUE;
        u32 tileIndex = get_tiletype_index(tileType, tile->mat);
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
        play_place_sound(SOUND_ACTION_TERRAIN_STEP + (SOUND_TERRAIN_WATER << 16));
    }
}

void place_object(s8 pos[3]) {
    cmm_object_data[cmm_object_count].x = pos[0];
    cmm_object_data[cmm_object_count].y = pos[1];
    cmm_object_data[cmm_object_count].z = pos[2];
    cmm_object_data[cmm_object_count].type = cmm_id_selection;
    cmm_object_data[cmm_object_count].rot = cmm_rot_selection;
    cmm_object_data[cmm_object_count].param = cmm_param_selection;

    if (cmm_object_place_types[cmm_id_selection].useTrajectory) {
        cmm_trajectory_to_edit = cmm_trajectories_used;
        cmm_object_data[cmm_object_count].param = cmm_trajectories_used;
        cmm_trajectories_used++;

        cmm_menu_state = CMM_MAKE_TRAJECTORY;
        o->oAction = 5; //trajectory editor
        cmm_trajectory_edit_index = 0;
    }

    cmm_object_count++;
    play_place_sound(cmm_object_place_types[cmm_id_selection].info->soundBits);
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

void remove_trajectory(u32 index) {
    // Scan all objects
    // If their trajectory index is past the one being deleted, lower it by 1
    for (u32 i = 0; i < cmm_object_count; i++) {
        if (cmm_object_place_types[cmm_object_data[i].type].useTrajectory) {
            if (cmm_object_data[i].param > index) {
                cmm_object_data[i].param--;
            }
        }
    }
    // Move trajectories back by one
    for (u32 i = index; i < cmm_trajectories_used - 1; i++) {
        bcopy(cmm_trajectory_list[i + 1], cmm_trajectory_list[i], sizeof(cmm_trajectory_list[0]));
    }
    // Zero out the last one
    bzero(cmm_trajectory_list[cmm_trajectories_used - 1], sizeof(cmm_trajectory_list[0]));
    cmm_trajectories_used--;
}

//function name is delete tile, it deletes objects too
void delete_tile_action(s8 pos[3]) {
    s16 index = -1;

    for (u32 i = 0; i < cmm_tile_count; i++) {
        //search for tile to delete
        if ((cmm_tile_data[i].x == pos[0])&&(cmm_tile_data[i].y == pos[1])&&(cmm_tile_data[i].z == pos[2])) {
            index = i;
            remove_occupy_data(pos);
            remove_terrain_data(pos);
            play_place_sound(SOUND_GENERAL_DOOR_INSERT_KEY | SOUND_VIBRATO);
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
        delete_useless_cull_markers();
        generate_terrain_gfx();
    }

    index = -1;
    for (u32 i=0;i<cmm_object_count;i++) {
        if ((cmm_object_data[i].x == pos[0])&&(cmm_object_data[i].y == pos[1])&&(cmm_object_data[i].z == pos[2])) {
            index = i;
            remove_occupy_data(pos);
            play_place_sound(SOUND_GENERAL_DOOR_INSERT_KEY | SOUND_VIBRATO);

            if (cmm_object_place_types[cmm_object_data[i].type].useTrajectory) { 
                remove_trajectory(cmm_object_data[i].param);
                generate_trajectory_gfx();
            }
            cmm_object_count--;
        }
    }
    if (index != -1) {
        for (u32 i = index; i < cmm_object_count; i++) {
            cmm_object_data[i] = cmm_object_data[i+1];
        }
        generate_object_preview();
    }
}

void delete_useless_cull_markers() {
    for (u32 i = cmm_tile_data_indices[CULL_TILETYPE_INDEX]; i < cmm_tile_data_indices[CULL_TILETYPE_INDEX + 1]; i++) {
        s8 pos[3];
        vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);

        if (!is_cull_marker_useless(pos)) {
            continue;
        }

        // Useless, delete
        remove_occupy_data(pos);
        remove_terrain_data(pos);
        cmm_tile_count--;

        for (u32 j = CULL_TILETYPE_INDEX + 1; j < ARRAY_COUNT(cmm_tile_data_indices); j++) {
            cmm_tile_data_indices[j]--;
        }
        for (u32 j = i; j < cmm_tile_count; j++) {
            cmm_tile_data[j] = cmm_tile_data[j+1];
        }

        i--;
    }
}

void update_painting() {
    s16 x;
    s16 y;
    u16 *u16_array = segmented_to_virtual(b_LevelPainting_rgba16);
    for (x = 4; x < 28; x++) {
        for (y = 4; y < 28; y++) {
            u16_array[(y*32)+x] = cmm_save.piktcher[y-4][x-4];
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

    bzero(&cmm_save, sizeof(cmm_save));
    //bzero(&cmm_grid_data, sizeof(cmm_grid_data));

    cmm_save.tile_count = cmm_tile_count;
    cmm_save.object_count = cmm_object_count;

    cmm_save.option[0] = cmm_lopt_costume;
    cmm_save.option[1] = cmm_lopt_seq;
    cmm_save.option[2] = cmm_lopt_envfx;
    cmm_save.option[3] = cmm_lopt_theme;
    cmm_save.option[4] = cmm_lopt_bg;
    cmm_save.option[5] = cmm_lopt_plane;
    cmm_save.option[7] = cmm_lopt_size;
    cmm_save.option[19] = cmm_lopt_game;

    //SAVE
    for (i = 0; i < cmm_tile_count; i++) {
        //Save tiles
        bcopy(&cmm_tile_data[i],&cmm_save.tiles[i],sizeof(cmm_tile_data[i]));
    }

    for (i = 0; i < cmm_object_count; i++) {
        //Save Objects
        bcopy(&cmm_object_data[i],&cmm_save.objects[i],sizeof(cmm_object_data[i]));
    }

    for (i = 0; i < CMM_MAX_TRAJECTORIES; i++) {
        for (j = 0; j < CMM_TRAJECTORY_LENGTH; j++) {
            cmm_save.trajectories[i][j].t = cmm_trajectory_list[i][j][0];
            cmm_save.trajectories[i][j].x = POS_TO_GRID(cmm_trajectory_list[i][j][1]);
            cmm_save.trajectories[i][j].y = POS_TO_GRIDY(cmm_trajectory_list[i][j][2]);
            cmm_save.trajectories[i][j].z = POS_TO_GRID(cmm_trajectory_list[i][j][3]);
        }
    }

    for (i=0;i<784;i++) {
        //take a "screenshot" of the level
        cmm_save.piktcher[i/28][i%28] = gFramebuffers[(sRenderingFramebuffer+2)%3][ ((i/28)*320*8)+((i%28)*11)];
    }

    update_painting();

    //block_until_rumble_pak_free();
    //nuPiWriteSram(0,&cmm_save, sizeof(cmm_save));
    //release_rumble_pak_control();

    u32 bytes_written;
    f_open(&cmm_file,cmm_file_name, FA_READ | FA_WRITE | FA_CREATE_ALWAYS);
    f_write(&cmm_file,&cmm_save,sizeof(cmm_save),&bytes_written);
    f_close(&cmm_file);
}

void load_level(u8 index) {
    s16 i;
    s16 j;
    u8 fresh = FALSE;

    bzero(&cmm_save, sizeof(cmm_save));
    bzero(&cmm_grid_data, sizeof(cmm_grid_data));

    //LOAD
    //block_until_rumble_pak_free();
    //nuPiReadSram(0,&cmm_save, sizeof(cmm_save));
    //release_rumble_pak_control();

    u32 bytes_read;
    FRESULT code = f_stat(cmm_file_name,&cmm_file_info);
    if (code == FR_OK) {
        //file exists, load it
        f_open(&cmm_file,cmm_file_name, FA_READ | FA_WRITE);
        f_read(&cmm_file,&cmm_save,sizeof(cmm_save),&bytes_read);
        f_close(&cmm_file);
    } else {
        //Load into a fresh level
        fresh = TRUE;
        bzero(&cmm_save, sizeof(cmm_save));

        //Set version
        cmm_save.version = CMM_VERSION;

        //Place spawn location
        cmm_save.object_count = 1;
        cmm_save.objects[0].x = 32;
        cmm_save.objects[0].z = 32;
        cmm_save.objects[0].y = cmm_templates[cmm_lopt_template].spawnHeight;
        cmm_save.objects[0].type = OBJECT_TYPE_SPAWN;

        cmm_save.option[19] = cmm_lopt_game;
        cmm_save.option[7] = cmm_lopt_size;

        cmm_save.option[1] = cmm_templates[cmm_lopt_template].music;
        cmm_save.option[2] = cmm_templates[cmm_lopt_template].envfx;
        cmm_save.option[3] = cmm_templates[cmm_lopt_template].theme;
        cmm_save.option[4] = cmm_templates[cmm_lopt_template].bg;
        cmm_save.option[5] = cmm_templates[cmm_lopt_template].plane;

        if (cmm_templates[cmm_lopt_template].platform) {
            u8 i = 0;
            for (s8 x = -1; x <= 1; x++) {
                for (s8 z = -1; z <= 1; z++) {
                    cmm_save.tiles[i].x = 32+x;
                    cmm_save.tiles[i].y = 0;
                    cmm_save.tiles[i].z = 32+z;
                    cmm_save.tiles[i].type = TILE_TYPE_BLOCK;
                    cmm_save.tiles[i].mat = 0;
                    i++;
                }
            }
            cmm_save.tile_count = i;
        }
    }

    cmm_tile_count = cmm_save.tile_count;
    cmm_object_count = cmm_save.object_count;

    cmm_lopt_costume = cmm_save.option[0];
    cmm_lopt_seq = cmm_save.option[1];
    cmm_lopt_envfx = cmm_save.option[2];
    cmm_lopt_theme = cmm_save.option[3];
    cmm_lopt_bg = cmm_save.option[4];

    cmm_settings_buttons[5].size = cmm_theme_table[cmm_lopt_theme].numFloors + 1;
    cmm_lopt_plane = cmm_save.option[5];
    cmm_lopt_size = cmm_save.option[7];
    switch (cmm_lopt_size) {
        case 0:
            cmm_grid_min = 16;
            cmm_grid_size = 32;
            break;
        case 1:
            cmm_grid_min = 8;
            cmm_grid_size = 48;
            break;
        case 2:
            cmm_grid_min = 0;
            cmm_grid_size = 64;
            break;
    }

    cmm_lopt_game = cmm_save.option[19];

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
        bcopy(&cmm_save.tiles[i],&cmm_tile_data[i],sizeof(cmm_tile_data[i]));
        u32 curIndex = get_tiletype_index(cmm_tile_data[i].type, cmm_tile_data[i].mat);

        if (curIndex != oldIndex) {
            // These tiles do not exist in the level so fill in the indices
            cmm_tile_data_indices[oldIndex + 1] = i;
            for (u32 j = oldIndex + 1; j < curIndex; j++) {
                cmm_tile_data_indices[j + 1] = cmm_tile_data_indices[j];
            }
            oldIndex = curIndex;
        }

        s8 pos[3];
        vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z)

        place_terrain_data(pos, cmm_tile_data[i].type, cmm_tile_data[i].rot, cmm_tile_data[i].mat);
        get_grid_tile(pos)->waterlogged = cmm_tile_data[i].waterlogged;
        if (cmm_tile_data[i].type != TILE_TYPE_WATER) place_occupy_data(pos);
    }
    // Fill in remaining indices that were unused
    for (u32 i = oldIndex + 1; i < ARRAY_COUNT(cmm_tile_data_indices); i++) {
        cmm_tile_data_indices[i] = cmm_tile_count;
    }

    for (i = 0; i < cmm_object_count; i++) {
        bcopy(&cmm_save.objects[i],&cmm_object_data[i],sizeof(cmm_object_data[i]));
        s8 pos[3];
        vec3_set(pos, cmm_object_data[i].x, cmm_object_data[i].y, cmm_object_data[i].z)
        place_occupy_data(pos);
        if (cmm_object_place_types[cmm_object_data[i].type].useTrajectory) {
            cmm_trajectories_used++;
        }
    }

    for (i = 0; i < CMM_MAX_TRAJECTORIES; i++) {
        for (j = 0; j < CMM_TRAJECTORY_LENGTH; j++) {
            cmm_trajectory_list[i][j][0] = cmm_save.trajectories[i][j].t;
            cmm_trajectory_list[i][j][1] = GRID_TO_POS(cmm_save.trajectories[i][j].x);
            cmm_trajectory_list[i][j][2] = GRIDY_TO_POS(cmm_save.trajectories[i][j].y);
            cmm_trajectory_list[i][j][3] = GRID_TO_POS(cmm_save.trajectories[i][j].z);
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

    vec3_set(cmm_cursor_pos, 32, 0, 32);
    cmm_ui_index = 0;
    vec3_copy(cmm_camera_foc,&o->oPosVec);
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
                vec3_copy(gMarioState->pos,&spawn_obj->oPosVec);
                gMarioState->pos[1] -= TILE_SIZE/2;

                struct Object *warpobj = cur_obj_nearest_object_with_behavior(bhvInstantActiveWarp);
                if (warpobj) {
                    vec3_copy(&warpobj->oPosVec,&spawn_obj->oPosVec);
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

u32 main_cursor_logic(u32 joystick) {
    u8 cursorMoved = FALSE;
    if (joystick != 0) {
        switch(((joystick-1)+cmm_camera_rot_offset)%4) {
            case 0:
                cmm_cursor_pos[0]++;
                cursorMoved = TRUE;
            break;
            case 1:
                cmm_cursor_pos[2]--;
                cursorMoved = TRUE;
            break;
            case 2:
                cmm_cursor_pos[0]--;
                cursorMoved = TRUE;
            break;
            case 3:
                cmm_cursor_pos[2]++;
                cursorMoved = TRUE;
            break;
        }
    }

    if (gPlayer1Controller->buttonPressed & U_CBUTTONS) {
        cmm_cursor_pos[1]++;
        cursorMoved = TRUE;
    }
    if (gPlayer1Controller->buttonPressed & D_CBUTTONS) {
        cmm_cursor_pos[1]--;
        cursorMoved = TRUE;
    }
    if (gPlayer1Controller->buttonPressed & R_CBUTTONS) {
        cmm_camera_rot_offset++;
    }
    if (gPlayer1Controller->buttonPressed & L_CBUTTONS) {
        cmm_camera_rot_offset--;
    }
    cmm_camera_rot_offset = (cmm_camera_rot_offset % 4)+4;

    if (cursorMoved) {
        cmm_cursor_pos[0] = ((cmm_cursor_pos[0] - cmm_grid_min + cmm_grid_size) % cmm_grid_size) + cmm_grid_min;
        cmm_cursor_pos[2] = ((cmm_cursor_pos[2] - cmm_grid_min + cmm_grid_size) % cmm_grid_size) + cmm_grid_min;
        cmm_cursor_pos[1]=(cmm_cursor_pos[1]+32)%32;
    }

    //camera zooming
    if (gPlayer1Controller->buttonPressed & U_JPAD) {
        cmm_camera_zoom_index--;
    }
    if (gPlayer1Controller->buttonPressed & D_JPAD) {
        cmm_camera_zoom_index++;
    }
    cmm_camera_zoom_index = (cmm_camera_zoom_index+5)%5;

    cmm_camera_foc[0] = lerp(cmm_camera_foc[0], GRID_TO_POS(cmm_cursor_pos[0]),  0.2f);
    cmm_camera_foc[1] = lerp(cmm_camera_foc[1], GRIDY_TO_POS(cmm_cursor_pos[1]), 0.2f);
    cmm_camera_foc[2] = lerp(cmm_camera_foc[2], GRID_TO_POS(cmm_cursor_pos[2]),  0.2f);

    o->oPosX = GRID_TO_POS(cmm_cursor_pos[0]); 
    o->oPosY = GRIDY_TO_POS(cmm_cursor_pos[1]); 
    o->oPosZ = GRID_TO_POS(cmm_cursor_pos[2]); 

    for (u8 i=0; i<6; i++) {
        vec3_copy(&cmm_boundary_object[i]->oPosVec,&o->oPosVec);
    }
    cmm_boundary_object[0]->oPosY = GRIDY_TO_POS(0);
    cmm_boundary_object[1]->oPosY = GRIDY_TO_POS(32);
    cmm_boundary_object[2]->oPosX = GRID_TO_POS(cmm_grid_min);
    cmm_boundary_object[3]->oPosX = GRID_TO_POS(cmm_grid_min + cmm_grid_size);
    cmm_boundary_object[4]->oPosZ = GRID_TO_POS(cmm_grid_min);
    cmm_boundary_object[5]->oPosZ = GRID_TO_POS(cmm_grid_min + cmm_grid_size);

    return cursorMoved;
}

u8 cmm_upsidedown_tile = FALSE;

void sb_loop(void) {
    Vec3f cam_pos_offset = {0.0f,cmm_current_camera_zoom[1],0};
    u8 joystick = joystick_direction();
    u8 cursorMoved = FALSE;

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
            cursorMoved = main_cursor_logic(joystick);

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

            if (cmm_upsidedown_tile) {
                switch (cmm_id_selection) {
                    case TILE_TYPE_SLOPE:
                    case TILE_TYPE_DSLOPE:
                        cmm_id_selection = TILE_TYPE_DSLOPE;
                        break;
                    case TILE_TYPE_CORNER:
                    case TILE_TYPE_DCORNER:
                        cmm_id_selection = TILE_TYPE_DCORNER;
                        break;
                    case TILE_TYPE_ICORNER:
                    case TILE_TYPE_DICORNER:
                        cmm_id_selection = TILE_TYPE_DICORNER;
                        break;
                    case TILE_TYPE_SLAB:
                    case TILE_TYPE_DSLAB:
                        cmm_id_selection = TILE_TYPE_DSLAB;
                        break;
                    default:
                        cmm_upsidedown_tile = FALSE;
                }
            }

            //parameter changing
            if (gPlayer1Controller->buttonPressed & L_JPAD) {
                cmm_param_selection --;
            }
            if (gPlayer1Controller->buttonPressed & R_JPAD) {
                cmm_param_selection ++;
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
            } else if (gPlayer1Controller->buttonDown & A_BUTTON && cursorMoved) {
                if (cmm_ui_index < 6) {
                    place_thing_action();
                }
            }

            if (gPlayer1Controller->buttonPressed & B_BUTTON || ((gPlayer1Controller->buttonDown & B_BUTTON) && cursorMoved)) {
                delete_tile_action(cmm_cursor_pos);
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
                if (gPlayer1Controller->buttonDown & B_BUTTON) {
                    cmm_upsidedown_tile ^= 1;
                } else {
                    cmm_rot_selection++;
                    cmm_rot_selection%=4;
                }
            }

            if (cmm_place_mode == CMM_PM_OBJ) {
                if (cmm_object_place_types[cmm_id_selection].maxParams != 0) {
                    s16 max = cmm_object_place_types[cmm_id_selection].maxParams;
                    cmm_param_selection = (cmm_param_selection+max)%max;
                }

                struct cmm_object_info *info = cmm_object_place_types[cmm_id_selection].info;
                vec3_copy(&cmm_preview_object->oPosVec,&o->oPosVec);
                cmm_preview_object->oPosY += info->y_offset - TILE_SIZE/2;
                obj_scale(cmm_preview_object, info->scale);
                cmm_preview_object->header.gfx.sharedChild =  gLoadedGraphNodes[info->model_id];
                cmm_preview_object->oFaceAngleYaw = cmm_rot_selection*0x4000;
                if (info->billboarded) {
                    cmm_preview_object->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
                } else {
                    cmm_preview_object->header.gfx.node.flags &= ~GRAPH_RENDER_BILLBOARD;
                }
                if (info->anim) {
                    cmm_preview_object->oAnimations = (struct Animation **)info->anim;
                    super_cum_working(cmm_preview_object,0);
                }
                if (info->disp_func) {
                    (info->disp_func)(cmm_preview_object,cmm_param_selection);
                }
            } else {
                cmm_preview_object->header.gfx.sharedChild =  gLoadedGraphNodes[MODEL_NONE];
            }
            if (cmm_place_mode == CMM_PM_TILE) {
                if (cmm_tile_terrains[cmm_id_selection]) {
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
            cmm_preview_object->header.gfx.sharedChild =  gLoadedGraphNodes[MODEL_NONE];
            cursorMoved = main_cursor_logic(joystick);

            if (cursorMoved) {
                generate_trajectory_gfx();
            }

            if (o->oTimer == 0) {
                // Initial placement on top of the object
                cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index][0] = cmm_trajectory_edit_index;
                cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index][1] = o->oPosX;
                cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index][2] = o->oPosY;
                cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index][3] = o->oPosZ;
                cmm_trajectory_edit_index++; 
            } else {
                if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                    if (cmm_trajectory_edit_index == CMM_TRAJECTORY_LENGTH - 1) {
                        cmm_show_error_message("Maximum trajectory length reached! (max 50)");
                    // i fucking hate this, worst code ever. this hopefully won't have floating point inaccuracies
                    } else if (cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index - 1][1] == o->oPosX
                            && cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index - 1][2] == o->oPosY
                            && cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index - 1][3] == o->oPosZ) {
                        cmm_show_error_message("");
                    } else {
                        cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index][0] = cmm_trajectory_edit_index;
                        cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index][1] = o->oPosX;
                        cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index][2] = o->oPosY;
                        cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index][3] = o->oPosZ;
                        cmm_trajectory_edit_index++;
                        play_place_sound(SOUND_MENU_CLICK_FILE_SELECT | SOUND_VIBRATO);
                        generate_trajectory_gfx();
                    }
                } else if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                    if (cmm_trajectory_edit_index <= 1) {
                        cmm_show_error_message("Nothing to delete!");
                    } else {
                        cmm_trajectory_edit_index--;
                        cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index][0] = -1;
                        play_place_sound(SOUND_GENERAL_DOOR_INSERT_KEY | SOUND_VIBRATO);
                        generate_trajectory_gfx();
                    }
                }
            }

            if (gPlayer1Controller->buttonPressed & START_BUTTON) {
                cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index][0] = -1;
                o->oAction = 1;
                cmm_menu_state = CMM_MAKE_MAIN;
                generate_trajectory_gfx();
            }
        break;
    }

    vec3_copy(cmm_camera_pos,cmm_camera_foc);
    vec3_add(cmm_camera_pos,cam_pos_offset);
}

#include "src/game/cursed_mirror_maker_menu.inc.c"
