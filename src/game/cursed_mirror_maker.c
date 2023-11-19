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
#include "mario_actions_automatic.h"
#include "levels/scripts.h"

#include "libcart/include/cart.h"
#include "libcart/ff/ff.h"

extern void super_cum_working(struct Object *obj, s32 animIndex);

u8 cmm_level_action = CMM_LA_MAKING;
u8 cmm_mode = CMM_MODE_UNINITIALIZED;
u8 cmm_target_mode = CMM_MODE_MAKE;
u8 cmm_joystick_timer = 0;
s8 cmm_cursor_pos[3] = {32,0,32};

Vec3f cmm_camera_pos = {0.0f,0.0f,0.0f};
Vec3f cmm_camera_foc = {0.0f,0.0f,0.0f};
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
u16 cmm_tile_data_indices[NUM_MATERIALS_PER_THEME + 10] = {0};
u16 cmm_tile_count = 0;
u16 cmm_object_count = 0;
u16 cmm_building_collision = FALSE; // 0 = building gfx, 1 = building collision

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
u8 cmm_uv_scaling = 64;
s8 cmm_uv_offset = -16;
u8 cmm_render_flip_normals = FALSE;
u8 cmm_growth_render_type = 0;
u8 cmm_curr_mat_has_topside = FALSE;

TerrainData cmm_curr_coltype = SURFACE_DEFAULT;

//play mode stuff
u8 cmm_play_stars = 0;
u8 cmm_play_stars_max = 0;
u64 cmm_play_stars_bitfield = 0;
u32 cmm_play_badge_bitfield = 0;

//LEVEL SETTINGS INDEX
u8 cmm_lopt_costume = 0;

u8 cmm_lopt_seq = 0; // Song index
u8 cmm_lopt_seq_album = 0; // Category
u8 cmm_lopt_seq_song = 0; // Song index within category

u8 cmm_lopt_envfx = 0;
u8 cmm_lopt_theme = 0;
u8 cmm_lopt_bg = 0;
u8 cmm_lopt_plane = 0;
u8 cmm_lopt_game = 0;//0 = BTCM, 1 = VANILLA
u8 cmm_lopt_size = 0;
u8 cmm_lopt_template = 0;
u8 cmm_lopt_coinstar = 0;
u8 cmm_lopt_waterlevel = 0;

//UI
u8 cmm_menu_state = CMM_MAKE_MAIN;
s8 cmm_menu_index = 0;
s8 cmm_toolbar_index = 0;
s8 cmm_toolbox_index = 0;
u8 cmm_ui_do_render = TRUE;
u8 cmm_do_save = FALSE;

char *cmm_error_message = NULL;
u16 cmm_error_timer = 0;
f32 cmm_error_vels[3];

struct cmm_level_save_header cmm_save;
char cmm_username[31];
u8 cmm_has_username = FALSE;

u8 cmm_num_vertices_cached = 0;
u8 cmm_num_tris_cached = 0;
u8 cmm_cached_tris[16][3];

struct ExclamationBoxContents *cmm_exclamation_box_contents;

void play_place_sound(u32 soundBits) {
    play_sound(soundBits, gGlobalSoundSource);
}

void df_star(UNUSED s32 context) {
    o->oFaceAngleYaw += 0x800;
}

void df_heart(UNUSED s32 context) {
    o->oFaceAngleYaw += 400;
}
void df_corkbox(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) o->oAnimState = 1;
}

void df_reds_marker(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) {
        o->oFaceAnglePitch = 0x4000;
        vec3_set(o->header.gfx.scale, 1.5f, 1.5f, 0.75f);
        o->oPosY -= (TILE_SIZE/2 - 60);
    }
    o->oFaceAngleYaw += 0x100;
}

void df_tree(s32 context) {
    if (context != CMM_DF_CONTEXT_INIT) return;
    switch(o->oBehParams2ndByte) {
        case 1:
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_TREE_2];
            break;
        case 2:
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_TREE_3];
            break;
        case 3:
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_TREE_4];
            break;
    }
}

void df_exbox(s32 context) {
    if (context != CMM_DF_CONTEXT_INIT) return;
    if (cmm_lopt_game == CMM_GAME_VANILLA) {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_VEXCLAMATION_BOX];
    }
    o->oAnimState = cmm_exclamation_box_contents[o->oBehParams2ndByte].animState;
}

void df_vexbox(s32 context) {
    if (context != CMM_DF_CONTEXT_INIT) return;
    switch(o->oBehParams2ndByte) {
        case 0:
            o->oAnimState = 0;
            break;
        case 1:
            o->oAnimState = 1;
            break;
        case 2:
            o->oAnimState = 2;
            break;
        default:
            o->oAnimState = 3;
            break;
    }
}

void df_koopa(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) super_cum_working(o, 7);
}
void df_chuckya(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) super_cum_working(o, 4);
}
void df_kingbomb(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) super_cum_working(o, 5);
}
void df_checkerboard_elevator(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) o->header.gfx.scale[1] = 2.0f;
}

void df_mri(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) {
        o->oGraphYOffset = 100.0f;
        struct Object * iris = spawn_object(o,MODEL_MAKER_MRI_2, VIRTUAL_TO_PHYSICAL(o->behavior));

        obj_copy_pos_and_angle(iris, o);
        iris->oPosX += sins(o->oFaceAngleYaw)*100.0f;
        iris->oPosZ += coss(o->oFaceAngleYaw)*100.0f;
        iris->oPosY += 100.0f;
    }
}
void df_booser(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) super_cum_working(o, BOWSER_ANIM_IDLE);
}

extern s8 sCloudPartHeights[];
void df_lakitu(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) {
        for (int i = 0; i < 5; i++) {
            struct Object * cloudPart = spawn_object(o,MODEL_MIST,VIRTUAL_TO_PHYSICAL(o->behavior));
            obj_scale(cloudPart,2.0f);
            cloudPart->oOpacity = 255;
            obj_set_billboard(cloudPart);
            obj_scale(cloudPart,2.0f);
            cloudPart->oPosY += sCloudPartHeights[i];
            cloudPart->oPosX += sins(0x3333*i)*40.0f;
            cloudPart->oPosZ += coss(0x3333*i)*40.0f;
        }
    }
}

void df_snufit(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) o->oSnufitBodyScale = 1000.0f;
}

extern enum CMM_THEMES cmm_themes;
void df_bully(s32 context) {
    if ((context == CMM_DF_CONTEXT_INIT)&&(cmm_lopt_theme == CMM_THEME_SNOW)) {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_CHILL_BULLY];
    }
}

extern s16 sCoinArrowPositions[][2];
void df_coin_formation(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) {
        Vec3i pos = { 0, 0, 0 };
        s32 spawnCoin    = TRUE;
        u32 index = 0;

        while (spawnCoin && index < 8) {
            switch (o->oBehParams2ndByte & COIN_FORMATION_BP_SHAPE_MASK) {
                case COIN_FORMATION_BP_SHAPE_HORIZONTAL_LINE:
                    pos[2] = 160 * (index - 2);
                    if (index > 4) spawnCoin = FALSE;
                    break;
                case COIN_FORMATION_BP_SHAPE_VERTICAL_LINE:
                    pos[1] = index << 7;
                    if (index > 4) spawnCoin = FALSE;
                    break;
                case COIN_FORMATION_BP_SHAPE_HORIZONTAL_RING:
                    pos[0] = sins(index << 13) * 300.0f;
                    pos[2] = coss(index << 13) * 300.0f;
                    break;
                case COIN_FORMATION_BP_SHAPE_VERTICAL_RING:
                    pos[0] = coss(index << 13) * 200.0f;
                    pos[1] = sins(index << 13) * 200.0f + 200.0f;
                    break;
                case COIN_FORMATION_BP_SHAPE_ARROW:
                    pos[0] = sCoinArrowPositions[index][0];
                    pos[2] = sCoinArrowPositions[index][1];
                    break;

            }

            if (spawnCoin) {
                struct Object *newCoin =spawn_object_relative(index, pos[0], pos[1], pos[2], o, MODEL_YELLOW_COIN, VIRTUAL_TO_PHYSICAL(o->behavior));
                obj_set_billboard(newCoin);
            }
            index ++;
        }
    }
}

void df_grindel(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) {
        o->oFaceAngleYaw += 0x4000;
        o->oMoveAngleYaw += 0x4000;
    }
}

#include "src/game/cursed_mirror_maker_data.inc.c"

void bhv_preview_object_init(void) {
    if (!o->oPreviewObjDisplayFunc) return;
    ((DisplayFunc)o->oPreviewObjDisplayFunc)(CMM_DF_CONTEXT_INIT);
}
void bhv_preview_object_loop(void) {
    if (!o->oPreviewObjDisplayFunc) return;
    ((DisplayFunc)o->oPreviewObjDisplayFunc)(CMM_DF_CONTEXT_MAIN);
}

void cmm_show_error_message(char *message) {
    if ((message != cmm_error_message) || (cmm_error_timer < 30)) {
        cmm_error_message = message;
        cmm_error_timer = 120;
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
        s32 numStars = 0;
        for (s32 i = 0; i < cmm_object_count; i++) {
            if (cmm_object_place_types[cmm_object_data[i].type].hasStar) {
                numStars++;
            }
        }
        if (numStars >= 63) {
            cmm_show_error_message("Star limit reached! (max 63)");
            return FALSE;
        }
    }

    if ((cmm_id_selection == OBJECT_TYPE_STAR) && (cmm_param_selection == 1)) {
        for (u32 i = 0; i < cmm_object_count; i++) {
            if ((cmm_object_data[i].type == OBJECT_TYPE_STAR) && (cmm_object_data[i].param2 == 1)) {
                cmm_show_error_message("Red Coin Star already placed!");
                return FALSE;
            }
        }
    }

    return TRUE;
}

struct Object * get_spawn_preview_object() {
    uintptr_t *behaviorAddr = segmented_to_virtual(bhvPreviewObject);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *obj = (struct Object *) listHead->next;

    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr
            && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED
            && obj != o
        ) {
            if (obj->header.gfx.sharedChild == gLoadedGraphNodes[MODEL_SPAWN]) {
                return obj;
            }
        }

        obj = (struct Object *) obj->header.next;
    }

    return NULL;
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
    struct cmm_terrain *terrain;
    s8 tileType = get_grid_tile(pos)->type - 1;
    if (tileType == -1) return CMM_FACESHAPE_EMPTY;

    if (tileType == TILE_TYPE_POLE) terrain = &cmm_terrain_pole;
    else terrain = cmm_tile_terrains[tileType];

    if (!terrain) return CMM_FACESHAPE_EMPTY;

    u8 rot = get_grid_tile(pos)->rot;
    dir = ROTATE_DIRECTION(dir,((4-rot) % 4)) ^ 1;

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
    if (!coords_in_range(newpos)) {
        if (direction == CMM_DIRECTION_UP) return FALSE;
        return TRUE;
    }
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
    if ((faceshape == CMM_FACESHAPE_TOPTRI) || (faceshape == CMM_FACESHAPE_TOPHALF)) {
        if (otherFaceshape == faceshape) {
            u8 otherrot = get_grid_tile(newpos)->rot;
            return (otherrot == rot);
        } else return FALSE;
    }
    if (faceshape == CMM_FACESHAPE_BOTTOMSLAB || faceshape == CMM_FACESHAPE_TOPSLAB || faceshape == CMM_FACESHAPE_POLETOP) {
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

void rotate_obj_toward_trajectory_angle(struct Object * obj, u32 traj_id) {
    if ((cmm_trajectory_list[traj_id][0][0] == -1)||(cmm_trajectory_list[traj_id][1][0] == -1)) return;

    s16 angle_to_trajectory;
    if (!trajectory_get_target_angle(&angle_to_trajectory, &cmm_trajectory_list[traj_id][0], &cmm_trajectory_list[traj_id][1])) {
        return;
    }

    if ( obj_has_model(obj ,MODEL_CHECKERBOARD_PLATFORM) ) {
        angle_to_trajectory += 0x4000;
    }

    obj->oFaceAngleYaw = angle_to_trajectory;
    obj->oMoveAngleYaw = angle_to_trajectory;
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

    make_vertex(cmm_curr_vtx, cmm_num_vertices_cached,     pos1[0] + cy, pos1[1], pos1[2] - sy, 0, 0, 0, 0, 0, 0xFF);
    make_vertex(cmm_curr_vtx, cmm_num_vertices_cached + 1, pos1[0] - cy, pos1[1], pos1[2] + sy, 0, 0, 0, 0, 0, 0xFF);
    make_vertex(cmm_curr_vtx, cmm_num_vertices_cached + 2, pos2[0] + cy, pos2[1], pos2[2] - sy, 0, length, 0, 0, 0, 0xFF);
    make_vertex(cmm_curr_vtx, cmm_num_vertices_cached + 3, pos2[0] - cy, pos2[1], pos2[2] + sy, 0, length, 0, 0, 0, 0xFF);

    cache_tri(0, 1, 2);
    cache_tri(1, 3, 2);
    cmm_num_vertices_cached += 4;
    check_cached_tris();

    make_vertex(cmm_curr_vtx, cmm_num_vertices_cached,     pos1[0] + spsy, pos1[1] - cp, pos1[2] + spcy, 0, 0, 0, 0, 0, 0xFF);
    make_vertex(cmm_curr_vtx, cmm_num_vertices_cached + 1, pos1[0] - spsy, pos1[1] + cp, pos1[2] - spcy, 0, 0, 0, 0, 0, 0xFF);
    make_vertex(cmm_curr_vtx, cmm_num_vertices_cached + 2, pos2[0] + spsy, pos2[1] - cp, pos2[2] + spcy, 0, length, 0, 0, 0, 0xFF);
    make_vertex(cmm_curr_vtx, cmm_num_vertices_cached + 3, pos2[0] - spsy, pos2[1] + cp, pos2[2] - spcy, 0, length, 0, 0, 0, 0xFF);

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

    for (s32 traj = 0; traj < cmm_trajectories_used; traj++) {
        Trajectory (*curr_trajectory)[4] = cmm_trajectory_list[traj];
        s16 pos1[3], pos2[3];
        s32 isLoop = FALSE;

        // Find object corresponding to this trajectory
        for (s32 i = 0; i < cmm_object_count; i++) {
            if (cmm_object_place_types[cmm_object_data[i].type].useTrajectory) {
                if (cmm_object_data[i].param2 == traj) {
                    // Check if it loops or not
                    if (cmm_object_data[i].param1) {
                        isLoop = TRUE;
                        gDPSetPrimColor(&cmm_curr_gfx[cmm_gfx_index++], 0, 0, 0, 0, 255, 255);
                    } else {
                        gDPSetPrimColor(&cmm_curr_gfx[cmm_gfx_index++], 0, 0, 255, 255, 0, 255);
                    }
                    break;
                }
            }
        }
        s32 i;
        for (i = 0; curr_trajectory[i+1][0] == i+1; i++) {
            vec3_set(pos1, curr_trajectory[i][1], curr_trajectory[i][2], curr_trajectory[i][3]);
            vec3_set(pos2, curr_trajectory[i+1][1], curr_trajectory[i+1][2], curr_trajectory[i+1][3]);
            draw_dotted_line(pos1, pos2);
        }
        if (traj == cmm_trajectory_to_edit && cmm_menu_state == CMM_MAKE_TRAJECTORY) {
            vec3_set(pos1, curr_trajectory[i][1], curr_trajectory[i][2], curr_trajectory[i][3]);
            vec3_set(pos2, GRID_TO_POS(cmm_cursor_pos[0]), GRIDY_TO_POS(cmm_cursor_pos[1]), GRID_TO_POS(cmm_cursor_pos[2]));
            draw_dotted_line(pos1, pos2);
        }
        if (isLoop) {
            vec3_copy(pos1, pos2);
            vec3_set(pos2, curr_trajectory[0][1], curr_trajectory[0][2], curr_trajectory[0][3]);
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
        /*case CMM_DIRECTION_POS_Z:*/ default: *uAxis = 0; *vAxis = 1; return TRUE;
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
            u * cmm_uv_scaling + cmm_uv_offset, v * cmm_uv_scaling + cmm_uv_offset,
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
            u * cmm_uv_scaling + cmm_uv_offset, v * cmm_uv_scaling + cmm_uv_offset,
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
    if (MATERIAL(get_grid_tile(newpos)->mat).type >= MAT_CUTOUT) {
        return TRUE;
    }
    u8 otherFaceshape;
    switch (grassType) {
        case CMM_GROWTH_UNDERSLOPE:
        case CMM_GROWTH_UNDERSLOPE_L:
            direction = grassType == CMM_GROWTH_UNDERSLOPE ? CMM_DIRECTION_POS_Z : CMM_DIRECTION_POS_X;
            // fallthrough
        case CMM_GROWTH_NORMAL_SIDE:
        case CMM_GROWTH_HALF_SIDE:
            // Shape of face of above block on same side
            if (should_cull_topslab_check(pos, direction, rot)) return FALSE;
            otherFaceshape = get_faceshape(newpos, ROTATE_DIRECTION(direction, rot)^1);
            switch (otherFaceshape) {
                case CMM_FACESHAPE_TRI_1:
                case CMM_FACESHAPE_TRI_2:
                case CMM_FACESHAPE_FULL:
                case CMM_FACESHAPE_BOTTOMSLAB:
                    return FALSE;
            }
            if ((grassType == CMM_GROWTH_HALF_SIDE) && (faceshape == otherFaceshape)) {
                return FALSE;
            }
            return TRUE;
        case CMM_GROWTH_UNDERSLOPE_CORNER:
            ;// some very cursed logic here, this is solely for upside-down inside corners
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
        case CMM_GROWTH_VSLAB_SIDE:
            otherFaceshape = get_faceshape(newpos, CMM_DIRECTION_UP);
            if (otherFaceshape == CMM_FACESHAPE_FULL) return FALSE;
            if (otherFaceshape != (grassType == CMM_GROWTH_DIAGONAL_SIDE ? CMM_FACESHAPE_TOPTRI : CMM_FACESHAPE_TOPHALF)) return TRUE;
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

#define BAR_CONNECTED_SIDE(bar) ((bar) & 1)
#define BAR_CONNECTED_TOP(bar) (((bar) >> 1) & 0x1)
#define BAR_CONNECTED_BOTTOM(bar) (((bar) >> 2) & 0x1)

void check_bar_side_connections(s8 pos[3], u8 connections[4]) {
    s8 adjacentPos[3];

    for (u32 rot = 0; rot < 4; rot++) {
        connections[rot] = 0;
        s32 dir = ROTATE_DIRECTION(CMM_DIRECTION_POS_Z, rot);
        vec3_sum(adjacentPos, pos, cullOffsetLUT[dir]);
        if (!coords_in_range(adjacentPos)) continue;

        // If adjacent block is a bar, return true
        if (get_grid_tile(adjacentPos)->type - 1 == TILE_TYPE_BARS) {
            connections[rot] = 1; continue;
        }

        // Else check its a full block
        if (get_faceshape(adjacentPos, dir) == CMM_FACESHAPE_FULL) connections[rot] = 1;
    }
}

void check_bar_connections(s8 pos[3], u8 connections[5]) {
    check_bar_side_connections(pos, connections);
    connections[4] = 0;
    // Check top
    s8 adjacentPos[3];
    u8 adjacentConnections[4];

    for (u32 updown = 0; updown < 2; updown++) { // 0 = Up, 1 = Down
        vec3_sum(adjacentPos, pos, cullOffsetLUT[updown]);
        if (coords_in_range(adjacentPos)) {
            if (get_faceshape(adjacentPos, updown) == CMM_FACESHAPE_FULL) {
                for (u32 rot = 0; rot < 4; rot++) {
                    connections[rot] |= (1 << (updown+1)); // Apply top flag to all bars
                }
                connections[4] |= (1 << (updown + 1));
            } else if (get_grid_tile(adjacentPos)->type - 1 == TILE_TYPE_BARS) {
                check_bar_side_connections(adjacentPos, adjacentConnections);
                for (u32 rot = 0; rot < 4; rot++) {
                    connections[rot] |= adjacentConnections[rot] << (updown+1); // Apply top flag to all bars
                }
                connections[4] |= (1 << (updown + 1));
            }
        }
    }
}

void render_bars(s8 pos[3]) {
    u8 connections[5];
    check_bar_connections(pos, connections);

    for (u32 rot = 0; rot < 4; rot++) {
        u32 leftRot = (rot + 3) % 4;
        u32 rightRot = (rot + 1) % 4;
        if (BAR_CONNECTED_SIDE(connections[rot])) {
            for (u32 j = 0; j < 4; j++) {
                if (j == 2 && BAR_CONNECTED_TOP(connections[rot])) continue;
                if (j == 3 && BAR_CONNECTED_BOTTOM(connections[rot])) continue;
                struct cmm_terrain_quad *quad = &cmm_terrain_bars_connected_quads[j];
                process_quad(pos, quad, rot);
            }
        }
        if (!BAR_CONNECTED_SIDE(connections[rot]) ||
            (BAR_CONNECTED_SIDE(connections[leftRot]) && BAR_CONNECTED_SIDE(connections[rightRot]))) {
            process_quad(pos, cmm_terrain_bars_unconnected_quad, rot);
        }
    }
    if (!BAR_CONNECTED_TOP(connections[4])) process_quad(pos, &cmm_terrain_bars_center_quads[0], 0);
    if (!BAR_CONNECTED_BOTTOM(connections[4])) process_quad(pos, &cmm_terrain_bars_center_quads[1], 0);
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
            process_quad(pos, quad, 0);
        }
    }
}

void render_floor(s16 y) {
    s16 vertex = 128 * cmm_grid_size;
    s16 uv = 256 * cmm_grid_size;
    make_vertex(cmm_curr_vtx, 0, vertex, y, vertex, -uv, -uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 1, vertex, y,      0,  uv, -uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 2,      0, y, vertex, -uv,  uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 3,      0, y,      0,  uv,  uv, 0x0, 0x7F, 0x0, 0xFF);

    make_vertex(cmm_curr_vtx, 4,       0, y, vertex, -uv, -uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 5,       0, y,      0,  uv, -uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 6, -vertex, y, vertex, -uv,  uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 7, -vertex, y,      0,  uv,  uv, 0x0, 0x7F, 0x0, 0xFF);

    make_vertex(cmm_curr_vtx, 8,  vertex, y,       0, -uv, -uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 9,  vertex, y, -vertex,  uv, -uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 10,      0, y,       0, -uv,  uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 11,      0, y, -vertex,  uv,  uv, 0x0, 0x7F, 0x0, 0xFF);

    make_vertex(cmm_curr_vtx, 12,       0, y,       0, -uv, -uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 13,       0, y, -vertex,  uv, -uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 14, -vertex, y,       0, -uv,  uv, 0x0, 0x7F, 0x0, 0xFF);
    make_vertex(cmm_curr_vtx, 15, -vertex, y, -vertex,  uv,  uv, 0x0, 0x7F, 0x0, 0xFF);

    gSPVertex(&cmm_curr_gfx[cmm_gfx_index++], cmm_curr_vtx, 16, 0);

    if (cmm_render_flip_normals) {
        gSP2Triangles(&cmm_curr_gfx[cmm_gfx_index++], 0, 2, 1, 0, 1, 2, 3, 0);
        gSP2Triangles(&cmm_curr_gfx[cmm_gfx_index++], 4, 6, 5, 0, 5, 6, 7, 0);
        gSP2Triangles(&cmm_curr_gfx[cmm_gfx_index++], 8, 10, 9, 0, 9, 10, 11, 0);
        gSP2Triangles(&cmm_curr_gfx[cmm_gfx_index++], 12, 14, 13, 0, 13, 14, 15, 0);
    } else {
        gSP2Triangles(&cmm_curr_gfx[cmm_gfx_index++], 0, 1, 2, 0, 1, 3, 2, 0);
        gSP2Triangles(&cmm_curr_gfx[cmm_gfx_index++], 4, 5, 6, 0, 5, 7, 6, 0);
        gSP2Triangles(&cmm_curr_gfx[cmm_gfx_index++], 8, 9, 10, 0, 9, 11, 10, 0);
        gSP2Triangles(&cmm_curr_gfx[cmm_gfx_index++], 12, 13, 14, 0, 13, 15, 14, 0);
    }
    cmm_curr_vtx += 16;
}

enum tiletypeIndices {
    FENCE_TILETYPE_INDEX = NUM_MATERIALS_PER_THEME,
    POLE_TILETYPE_INDEX,
    BARS_TILETYPE_INDEX,
    CULL_TILETYPE_INDEX,
    WATER_TILETYPE_INDEX,
    END_TILE_INDEX
};

u32 get_tiletype_index(u32 type, u32 mat) {
    switch (type) {
        case TILE_TYPE_FENCE:
            return FENCE_TILETYPE_INDEX;
        case TILE_TYPE_POLE:
            return POLE_TILETYPE_INDEX;
        case TILE_TYPE_BARS:
            return BARS_TILETYPE_INDEX;
        case TILE_TYPE_WATER:
            return WATER_TILETYPE_INDEX;
        case TILE_TYPE_CULL:
            return CULL_TILETYPE_INDEX;
        default:
            if (cmm_tile_terrains[type]) {
                return mat;
            }
    }
    return END_TILE_INDEX;
}


Gfx *get_sidetex(s32 mat) {
    s32 matid = TILE_MATDEF(mat).topmat;
    for (s32 i = 0; i < ARRAY_COUNT(cmm_topmat_table); i++) {
        if (cmm_topmat_table[i].mat == matid) {
            return cmm_topmat_table[i].decaltex;
        }
    }
    return NULL;
}


#define retroland_filter_on() if (cmm_lopt_theme == CMM_THEME_RETRO) { gDPSetTextureFilter(&cmm_curr_gfx[cmm_gfx_index++], G_TF_POINT); if (!gIsGliden) {cmm_uv_offset = 0;} }
#define retroland_filter_off() if (cmm_lopt_theme == CMM_THEME_RETRO) { gDPSetTextureFilter(&cmm_curr_gfx[cmm_gfx_index++], G_TF_BILERP); cmm_uv_offset = -16; }
#define cutout_turn_culling_off(mat) if (MATERIAL(mat).type == MAT_CUTOUT) { gSPClearGeometryMode(&cmm_curr_gfx[cmm_gfx_index++], G_CULL_BACK); cmm_uv_scaling = 128; }
#define cutout_turn_culling_on(mat) if (MATERIAL(mat).type == MAT_CUTOUT) { gSPSetGeometryMode(&cmm_curr_gfx[cmm_gfx_index++], G_CULL_BACK); cmm_uv_scaling = 64; }

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
        PROC_RENDER( gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], MATERIAL(mat).gfx); \
                     cutout_turn_culling_off(mat); )

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

        PROC_RENDER( display_cached_tris(); \
                     gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2); \
                     cutout_turn_culling_on(mat); )
        
        if (cmm_curr_mat_has_topside) {
            Gfx *sidetex = get_sidetex(mat);
            // Only runs when rendering
            if (!cmm_building_collision && (sidetex)) {
                cmm_use_alt_uvs = TRUE;
                gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], sidetex);
                cmm_growth_render_type = 2;
                for (u32 i = startIndex; i < endIndex; i++) {
                    tileType = cmm_tile_data[i].type;
                    rot = cmm_tile_data[i].rot;
                    vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);

                    process_tile(pos, cmm_tile_terrains[tileType], rot);
                }
                display_cached_tris();
                cmm_use_alt_uvs = FALSE;
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
            PROC_RENDER( display_cached_tris(); )
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
        render_floor(0);
        gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE);
    }

    // Special Tiles
    cmm_growth_render_type = 0;
    cmm_use_alt_uvs = TRUE;
    u32 startIndex;
    u32 endIndex;

    // Bars
    cmm_uv_scaling = 128;
    startIndex = cmm_tile_data_indices[BARS_TILETYPE_INDEX];
    endIndex = cmm_tile_data_indices[BARS_TILETYPE_INDEX+1];
    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], BARS_TEX());
    for (u32 i = startIndex; i < endIndex; i++) {
        s8 pos[3];
        vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
        render_bars(pos);
    }
    display_cached_tris();
    cmm_uv_scaling = 64;
    gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);

    // Poles

    startIndex = cmm_tile_data_indices[POLE_TILETYPE_INDEX];
    endIndex = cmm_tile_data_indices[POLE_TILETYPE_INDEX+1];
    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], POLE_TEX());
    for (u32 i = startIndex; i < endIndex; i++) {
        s8 pos[3];
        vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
        process_tile(pos, &cmm_terrain_pole, cmm_tile_data[i].rot);
    }
    display_cached_tris();

    // Fences

    startIndex = cmm_tile_data_indices[FENCE_TILETYPE_INDEX];
    endIndex = cmm_tile_data_indices[FENCE_TILETYPE_INDEX+1];
    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], FENCE_TEX());
    for (u32 i = startIndex; i < endIndex; i++) {
        s8 pos[3];
        vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
        process_tile(pos, &cmm_terrain_fence, cmm_tile_data[i].rot);
    }
    display_cached_tris();
    gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    cmm_use_alt_uvs = FALSE;

    process_tiles();

    retroland_filter_off();
    gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE);
    gSPEndDisplayList(&cmm_curr_gfx[cmm_gfx_index++]);

    cmm_terrain_gfx_tp = &cmm_curr_gfx[cmm_gfx_index];
    retroland_filter_on();
    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], WATER_TEX());

    // Render main water plane, top side
    if (cmm_lopt_waterlevel != 0) {
        render_floor(cmm_lopt_waterlevel * TILE_SIZE - 32);
    }
    // Render water blocks, interiors
    cmm_render_flip_normals = TRUE;
    for (u32 i = 0; i < cmm_tile_count; i++) {
        if (cmm_tile_data[i].waterlogged) {
            vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
            render_water(pos);
        }
    }
    // Render water blocks, exteriors
    cmm_render_flip_normals = FALSE;
    for (u32 i = 0; i < cmm_tile_count; i++) {
        if (cmm_tile_data[i].waterlogged) {
            vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
            render_water(pos);
        }
    }
    display_cached_tris();
    cmm_render_flip_normals = TRUE;
    // Render main water plane, bottom side
    if (cmm_lopt_waterlevel != 0) {
        render_floor(cmm_lopt_waterlevel * TILE_SIZE - 32);
    }
    cmm_render_flip_normals = FALSE;
    retroland_filter_off();
    gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE);
    gSPEndDisplayList(&cmm_curr_gfx[cmm_gfx_index++]);

    cmm_trajectory_gfx = &cmm_curr_gfx[cmm_gfx_index];
    cmm_trajectory_vtx = cmm_curr_vtx;

    generate_trajectory_gfx();

    cmm_vtx_total = cmm_curr_vtx - cmm_terrain_vtx;
    cmm_gfx_total = (cmm_curr_gfx + cmm_gfx_index) - cmm_terrain_gfx;
};

Gfx preview_gfx[50];
Mtx preview_mtx[2];
Vtx preview_vtx[100];

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
            
            if (terrain) {
                cmm_curr_mat_has_topside = HAS_TOPMAT(cmm_mat_selection);
                if (TILE_MATDEF(cmm_mat_selection).mat == CMM_MAT_VP_SCREEN) {
                    gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], GBL_c1(G_BL_CLR_MEM, G_BL_0, G_BL_CLR_MEM, G_BL_1) | GBL_c2(G_BL_CLR_MEM, G_BL_0, G_BL_CLR_MEM, G_BL_1), Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP | ZMODE_OPA);
                    process_tile(cmm_cursor_pos, terrain, cmm_rot_selection);
                    display_cached_tris();
                    gSPEndDisplayList(&cmm_curr_gfx[cmm_gfx_index]);
                    geo_append_display_list(cmm_curr_gfx, LAYER_FORCE);

                    cmm_curr_gfx += cmm_gfx_index;
                    cmm_gfx_index = 0;
                }
                gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], MATERIAL(cmm_mat_selection).gfx);
                cutout_turn_culling_off(cmm_mat_selection);
                process_tile(cmm_cursor_pos, terrain, cmm_rot_selection);
                display_cached_tris();
                cutout_turn_culling_on(cmm_mat_selection);

                if (cmm_curr_mat_has_topside) {
                    Gfx *sidetex = get_sidetex(cmm_mat_selection);
                    if (sidetex != NULL) {
                        cmm_use_alt_uvs = TRUE;
                        cmm_growth_render_type = 2;

                        gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], sidetex);
                        process_tile(cmm_cursor_pos, terrain, cmm_rot_selection);
                        display_cached_tris();
                        cmm_use_alt_uvs = FALSE;
                    }
                    cmm_growth_render_type = 1;

                    gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
                    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], TOPMAT(cmm_mat_selection).gfx);
                    process_tile(cmm_cursor_pos, terrain, cmm_rot_selection);
                    display_cached_tris();
                }
                gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE);

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
            } else {
                cmm_use_alt_uvs = TRUE;
                if (cmm_id_selection == TILE_TYPE_FENCE) {
                    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], FENCE_TEX());
                    process_tile(cmm_cursor_pos, &cmm_terrain_fence, cmm_rot_selection);
                } else if (cmm_id_selection == TILE_TYPE_POLE) {
                    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], POLE_TEX());
                    process_tile(cmm_cursor_pos, &cmm_terrain_pole, cmm_rot_selection);
                } else if (cmm_id_selection == TILE_TYPE_BARS) {
                    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], BARS_TEX());
                    cmm_uv_scaling = 128;
                    render_bars(cmm_cursor_pos);
                    cmm_uv_scaling = 64;
                }
                display_cached_tris();
                cmm_use_alt_uvs = FALSE;
                gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE);
            }

            gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
            retroland_filter_off();
            gSPEndDisplayList(&cmm_curr_gfx[cmm_gfx_index]);

            geo_append_display_list(cmm_curr_gfx, LAYER_OPAQUE);
        }
    }
    return NULL;
}


void generate_poles(void) {
    gPoleArray = main_pool_alloc(main_pool_available() - 0x10, MEMORY_POOL_LEFT);
    gNumPoles = 0;

    // Iterate over all poles
    u32 startIndex = cmm_tile_data_indices[POLE_TILETYPE_INDEX];
    u32 endIndex = cmm_tile_data_indices[POLE_TILETYPE_INDEX+1];

    for (u32 i = startIndex; i < endIndex; i++) {
        s8 pos[3];
        vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
        
        // If there is a pole below, skip
        pos[1] -= 1;
        if (pos[1] >= 0 && (get_grid_tile(pos)->type - 1 == TILE_TYPE_POLE)) {
            continue;
        }

        s32 poleLength = 1;
        // Scan upwards until no more poles or top of grid reached
        pos[1] += 2;
        while (pos[1] < 32 && (get_grid_tile(pos)->type - 1 == TILE_TYPE_POLE)) {
            poleLength++;
            pos[1]++;
        }

        gPoleArray[gNumPoles].pos[0] = GRID_TO_POS(cmm_tile_data[i].x);
        gPoleArray[gNumPoles].pos[1] = GRIDY_TO_POS(cmm_tile_data[i].y) - TILE_SIZE/2;
        gPoleArray[gNumPoles].pos[2] = GRID_TO_POS(cmm_tile_data[i].z);
        gPoleArray[gNumPoles].height = poleLength * TILE_SIZE;
        gPoleArray[gNumPoles].poleType = 0;
        gNumPoles++;
    }

    // Trees
    for (u32 i = 0; i < cmm_object_count; i++) {
        if (cmm_object_data[i].type != OBJECT_TYPE_TREE) {
            continue;
        }
        gPoleArray[gNumPoles].pos[0] = GRID_TO_POS(cmm_object_data[i].x);
        gPoleArray[gNumPoles].pos[1] = GRIDY_TO_POS(cmm_object_data[i].y) - TILE_SIZE/2;
        gPoleArray[gNumPoles].pos[2] = GRID_TO_POS(cmm_object_data[i].z);
        gPoleArray[gNumPoles].height = 500;
        gPoleArray[gNumPoles].poleType = (cmm_object_data[i].param2 == 2 ? 2 : 1);
        gNumPoles++;
    }

    main_pool_realloc(gPoleArray, gNumPoles * sizeof(struct Pole));
}


TerrainData floorVtxs[4][3] = {
    {-1, 0, 1},
    {1, 0, 1},
    {-1, 0, -1},
    {1, 0, -1},
};

void generate_terrain_collision(void) {
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
    for (u32 i = cmm_tile_data_indices[FENCE_TILETYPE_INDEX]; i < cmm_tile_data_indices[FENCE_TILETYPE_INDEX+1]; i++) {
        s8 pos[3];
        vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
        process_tile(pos, &cmm_terrain_fence_col, cmm_tile_data[i].rot);
    }
    cmm_curr_coltype = SURFACE_VANISH_CAP_WALLS;
    for (u32 i = cmm_tile_data_indices[BARS_TILETYPE_INDEX]; i < cmm_tile_data_indices[BARS_TILETYPE_INDEX+1]; i++) {
        s8 pos[3];
        vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
        render_bars(pos);
    }

    cmm_building_collision = FALSE;
    u32 surfacePoolData = (uintptr_t)gCurrStaticSurfacePoolEnd - (uintptr_t)gCurrStaticSurfacePool;
    gTotalStaticSurfaceData += surfacePoolData;
    main_pool_realloc(gCurrStaticSurfacePool, surfacePoolData);

    gNumStaticSurfaceNodes = gSurfaceNodesAllocated;
    gNumStaticSurfaces = gSurfacesAllocated;

    generate_poles();
}


s32 cmm_get_water_level(s32 x, s32 y, s32 z) {
    s32 waterPlaneHeight = (cmm_lopt_waterlevel == 0 ? FLOOR_LOWER_LIMIT : cmm_lopt_waterlevel * TILE_SIZE - 32);
    if (y < waterPlaneHeight) {
        return waterPlaneHeight;
    }
    // Convert world coordinates into grid coordinates
    s8 pos[3];
    vec3_set(pos, (x + 32*TILE_SIZE) / TILE_SIZE, y / TILE_SIZE, (z + 32*TILE_SIZE) / TILE_SIZE);

    // Check if out of range
    if (pos[1] < 0) return waterPlaneHeight;
    if (pos[1] > 31) pos[1] = 31;
    // If block contains water, scan upwards, otherwise scan downwards
    if (get_grid_tile(pos)->waterlogged) {
        // Find grid Y coordinate of highest water block.
        // Stop scanning once we hit a non-water block or the top is reached
        pos[1]++;
        while (pos[1] < 32 && get_grid_tile(pos)->waterlogged) {
            pos[1]++;
        }
        pos[1]--;
    } else {
        // Find grid Y coordinate of lowest non-water block.
        // Stop scanning once we hit a water block or the bottom is reached
        pos[1]--;
        while (pos[1] > -1 && !get_grid_tile(pos)->waterlogged) {
            pos[1]--;
        }
        if (pos[1] == -1) {
            return waterPlaneHeight;
        }
    }

    if (is_water_fullblock(pos)) {
        return (pos[1] + 1) * TILE_SIZE;
    }
    return (pos[1] + 1) * TILE_SIZE - (TILE_SIZE / 16);
}

struct Object *spawn_preview_object(s8 pos[3], s32 rot, s32 param1, s32 param2, struct cmm_object_info *info, const BehaviorScript *script, u8 useTrajectory) {
    struct Object *preview_object = spawn_object(gMarioObject, info->model_id, script);
    preview_object->oPosX = GRID_TO_POS(pos[0]);
    preview_object->oPosY = GRIDY_TO_POS(pos[1]) - TILE_SIZE/2 + info->y_offset;
    preview_object->oPosZ = GRID_TO_POS(pos[2]);
    preview_object->oFaceAngleYaw = rot*0x4000;
    preview_object->oBehParams2ndByte = param2;
    preview_object->oPreviewObjDisplayFunc = info->disp_func;
    preview_object->oOpacity = 255;
    obj_scale(preview_object, info->scale);
    if (info->billboarded) {
        preview_object->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
    }
    if (info->anim) {
        preview_object->oAnimations = (struct Animation **)info->anim;
        super_cum_working(preview_object,0);
        preview_object->header.gfx.animInfo.animAccel = 0.0f;
    }
    if (useTrajectory && param1 == 0) {
        rotate_obj_toward_trajectory_angle(preview_object,param2);
    }
    return preview_object;
}

void generate_object_preview(void) {
    s32 totalCoins = 0;
    s32 doubleCoins = FALSE;
    struct Object *preview_object = cur_obj_nearest_object_with_behavior(bhvPreviewObject);
    while (preview_object) {
        unload_object(preview_object);
        preview_object = cur_obj_nearest_object_with_behavior(bhvPreviewObject);
    }

    for(u32 i = 0; i < cmm_object_count; i++){
        if (gFreeObjectList.next == NULL) break;
        struct cmm_object_info *info = cmm_object_place_types[cmm_object_data[i].type].info;
        s32 param = cmm_object_data[i].param2;
        u8 useTrajectory = cmm_object_place_types[cmm_object_data[i].type].useTrajectory;

        if (cmm_object_place_types[cmm_object_data[i].type].multipleObjs) {
            info = &info[param];
            param = 0;
        }

        s8 pos[3];
        vec3_set(pos, cmm_object_data[i].x, cmm_object_data[i].y, cmm_object_data[i].z);

        spawn_preview_object(pos, cmm_object_data[i].rot, cmm_object_data[i].param1, param, info, bhvPreviewObject, useTrajectory);
        totalCoins += info->numCoins;

        if (info == &cmm_object_type_exclamationbox) {
            totalCoins += cmm_exclamation_box_contents[param].numCoins;
        }
        if (info == &cmm_object_type_badge && param == 8) { // Greed badge
            doubleCoins = TRUE;
        }
    }
    if (doubleCoins) totalCoins *= 2;

    u32 length = MIN(totalCoins / 20, 50);
    cmm_settings_general_buttons[4].size = length + 1;

    if (cmm_lopt_coinstar > length) {
        cmm_lopt_coinstar = length;
    }
}

void generate_objects_to_level(void) {
    struct Object *obj;
    u32 i;
    cmm_play_stars_max = 0;
    for(i=0;i<cmm_object_count;i++){
        struct cmm_object_info *info = cmm_object_place_types[cmm_object_data[i].type].info;
        s32 param1 = cmm_object_data[i].param1;
        s32 param2 = cmm_object_data[i].param2;

        if (cmm_object_place_types[cmm_object_data[i].type].multipleObjs) {
            info = &info[param2];
            param2 = 0;
        }

        obj = spawn_object(gMarioObject, info->model_id, info->behavior);

        obj->oPosX = GRID_TO_POS(cmm_object_data[i].x);
        obj->oPosY = GRIDY_TO_POS(cmm_object_data[i].y) - TILE_SIZE/2 + info->y_offset;
        obj->oPosZ = GRID_TO_POS(cmm_object_data[i].z);
        obj->oFaceAngleYaw = cmm_object_data[i].rot*0x4000;
        obj->oMoveAngleYaw = cmm_object_data[i].rot*0x4000;
        obj->oBehParams2ndByte = param2;
        obj->oBehParams = (param1 << 24) | (param2 << 16);

        //assign star ids
        if (cmm_object_place_types[cmm_object_data[i].type].hasStar) {
            if (cmm_play_stars_max < 63) {
                obj->oBehParams = ((cmm_play_stars_max << 24)|(o->oBehParams2ndByte << 16));
                cmm_play_stars_max++;
            }
        }
    }
    if (cmm_lopt_coinstar > 0) cmm_play_stars_max++; // 100 coin star
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
            case TILE_TYPE_POLE:
            case TILE_TYPE_BARS:
                play_place_sound(SOUND_ACTION_TERRAIN_STEP + (SOUND_TERRAIN_STONE << 16));
                break;
            case TILE_TYPE_CULL:
                play_place_sound(SOUND_GENERAL_DOOR_INSERT_KEY | SOUND_VIBRATO);
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


void remove_trajectory(u32 index) {
    // Scan all objects
    // If their trajectory index is past the one being deleted, lower it by 1
    for (u32 i = 0; i < cmm_object_count; i++) {
        if (cmm_object_place_types[cmm_object_data[i].type].useTrajectory) {
            if (cmm_object_data[i].param2 > index) {
                cmm_object_data[i].param2--;
            }
        }
    }
    // Move trajectories back by one
    for (s32 i = index; i < cmm_trajectories_used - 1; i++) {
        bcopy(cmm_trajectory_list[i + 1], cmm_trajectory_list[i], sizeof(cmm_trajectory_list[0]));
    }
    // Zero out the last one
    bzero(cmm_trajectory_list[cmm_trajectories_used - 1], sizeof(cmm_trajectory_list[0]));
    cmm_trajectories_used--;
}


void delete_object(s8 pos[3], s32 index) {
    remove_occupy_data(pos);

    if (cmm_object_place_types[cmm_object_data[index].type].useTrajectory) { 
        remove_trajectory(cmm_object_data[index].param2);
        generate_trajectory_gfx();
    }

    cmm_object_count--;
    for (u32 i = index; i < cmm_object_count; i++) {
        cmm_object_data[i] = cmm_object_data[i+1];
    }
    generate_object_preview();
}


void place_object(s8 pos[3]) {
    // If spawn, delete old spawn
    if (cmm_id_selection == OBJECT_TYPE_SPAWN) {
        for (s32 i = 0; i < cmm_object_count; i++) {
            if (cmm_object_data[i].type == OBJECT_TYPE_SPAWN) {
                s8 pos[3];
                vec3_set(pos, cmm_object_data[i].x, cmm_object_data[i].y, cmm_object_data[i].z);
                delete_object(pos, i);
                break;
            }
        }
    }

    cmm_object_data[cmm_object_count].x = pos[0];
    cmm_object_data[cmm_object_count].y = pos[1];
    cmm_object_data[cmm_object_count].z = pos[2];
    cmm_object_data[cmm_object_count].type = cmm_id_selection;
    cmm_object_data[cmm_object_count].rot = cmm_rot_selection;

    if (cmm_object_place_types[cmm_id_selection].useTrajectory) {
        cmm_trajectory_to_edit = cmm_trajectories_used;
        cmm_object_data[cmm_object_count].param1 = cmm_param_selection;
        cmm_object_data[cmm_object_count].param2 = cmm_trajectories_used;
        cmm_trajectories_used++;

        cmm_menu_state = CMM_MAKE_TRAJECTORY;
        cmm_trajectory_list[cmm_trajectory_to_edit][0][0] = -1;
        cmm_trajectory_edit_index = 0;
    } else {
        cmm_object_data[cmm_object_count].param2 = cmm_param_selection;
    }

    cmm_object_count++;

    if (cmm_object_place_types[cmm_id_selection].multipleObjs) {
        play_place_sound(cmm_object_place_types[cmm_id_selection].info[cmm_param_selection].soundBits);
    } else {
        play_place_sound(cmm_object_place_types[cmm_id_selection].info->soundBits);
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

    for (u32 i=0;i<cmm_object_count;i++) {
        if ((cmm_object_data[i].x == pos[0])&&(cmm_object_data[i].y == pos[1])&&(cmm_object_data[i].z == pos[2])) {
            if (cmm_object_data[i].type == OBJECT_TYPE_SPAWN) {
                cmm_show_error_message("Cannot delete spawn point!");
                break;
            }
            delete_object(pos, i);
            play_place_sound(SOUND_GENERAL_DOOR_INSERT_KEY | SOUND_VIBRATO);
            break;
        }
    }
}


void update_painting() {
    s16 x;
    s16 y;
    u16 *u16_array = segmented_to_virtual(bigpainting2_bigger_painting_rgba16);
    for (x = 0; x < 64; x++) {
        for (y = 0; y < 64; y++) {
            u16_array[(y*64)+x] = cmm_save.piktcher[y][x];
        } 
    }
}

//if (gSramProbe != 0) {
#include "src/game/cursed_mirror_maker_painting_frames.inc.c"

TCHAR cmm_file_name[30];
FIL cmm_file;
FILINFO cmm_file_info;

char file_header_string[] = "MB64-v0.0";

void save_level(void) {
    s16 i;
    s16 j;

    bzero(&cmm_save, sizeof(cmm_save));

    //file header
    for (i=0;i<10;i++) {
        cmm_save.file_header[i] = file_header_string[i];
    }

    //author
    if (cmm_has_username) {
        i = 0;
        do {
            cmm_save.author[i] = cmm_username[i];
            i++;
        } while (cmm_username[i-1] != '\0');
    } else {
        cmm_save.author[0] = '\0';
    }

    cmm_save.tile_count = cmm_tile_count;
    cmm_save.object_count = cmm_object_count;

    cmm_save.option[0] = cmm_lopt_costume;
    cmm_save.option[1] = cmm_lopt_seq;
    cmm_save.option[2] = cmm_lopt_envfx;
    cmm_save.option[3] = cmm_lopt_theme;
    cmm_save.option[4] = cmm_lopt_bg;
    cmm_save.option[5] = cmm_lopt_plane;
    cmm_save.option[6] = cmm_lopt_coinstar;
    cmm_save.option[7] = cmm_lopt_size;
    cmm_save.option[8] = cmm_lopt_waterlevel;
    cmm_save.option[19] = cmm_lopt_game;

    for (i = 0; i < CMM_MAX_TRAJECTORIES; i++) {
        for (j = 0; j < CMM_TRAJECTORY_LENGTH; j++) {
            cmm_save.trajectories[i][j].t = cmm_trajectory_list[i][j][0];
            cmm_save.trajectories[i][j].x = POS_TO_GRID(cmm_trajectory_list[i][j][1]);
            cmm_save.trajectories[i][j].y = POS_TO_GRIDY(cmm_trajectory_list[i][j][2]);
            cmm_save.trajectories[i][j].z = POS_TO_GRID(cmm_trajectory_list[i][j][3]);
        }
    }

    for (i=0;i<4096;i++) {
        //take a "screenshot" of the level & burn in a painting frame
        if (cmm_painting_frame_1_rgba16[(i*2)+1]==0x00) {
            //painting
            cmm_save.piktcher[i/64][i%64] = (gFramebuffers[(sRenderingFramebuffer+2)%3][ ((s32)((i/64)*3.75f))*320 + (s32)((i%64)*3.75f+40) ] | 1);
        } else {
            //painting frame
            cmm_save.piktcher[i/64][i%64] = ((cmm_painting_frame_1_rgba16[(i*2)]<<8) | cmm_painting_frame_1_rgba16[(i*2)+1]);
        }
    }

    update_painting();


    f_chdir(cmm_level_dir_name);
    u32 bytes_written;
    f_open(&cmm_file,cmm_file_name, FA_READ | FA_WRITE | FA_CREATE_ALWAYS);
    //write header
    f_write(&cmm_file,&cmm_save,sizeof(cmm_save),&bytes_written);
    //write tiles
    f_write(&cmm_file,&cmm_tile_data,(sizeof(cmm_tile_data[0])*cmm_tile_count),&bytes_written);
    //write objects
    f_write(&cmm_file,&cmm_object_data,(sizeof(cmm_object_data[0])*cmm_object_count),&bytes_written);

    f_close(&cmm_file);

    f_chdir("..");
}

void load_level(void) {
    s16 i;
    s16 j;
    u8 fresh = FALSE;

    bzero(&cmm_save, sizeof(cmm_save));
    bzero(&cmm_grid_data, sizeof(cmm_grid_data));

    f_chdir(cmm_level_dir_name); //chdir exits after the ifelse statement
    FRESULT code = f_stat(cmm_file_name,&cmm_file_info);
    if (code == FR_OK) {
        u32 bytes_read;
        //file exists, load it
        f_open(&cmm_file,cmm_file_name, FA_READ | FA_WRITE);
        //read header
        f_read(&cmm_file,&cmm_save,sizeof(cmm_save),&bytes_read);
        //read tiles
        f_read(&cmm_file,&cmm_tile_data,sizeof(cmm_tile_data[0])*cmm_save.tile_count,&bytes_read);
        //read objects
        f_read(&cmm_file,&cmm_object_data,sizeof(cmm_object_data[0])*cmm_save.object_count,&bytes_read);

        f_close(&cmm_file);
    } else {
        //Load into a fresh level
        fresh = TRUE;

        //Set version
        cmm_save.version = CMM_VERSION;

        //Place spawn location
        cmm_save.object_count = 1;
        cmm_object_data[0].x = 32;
        cmm_object_data[0].z = 32;
        cmm_object_data[0].y = cmm_templates[cmm_lopt_template].spawnHeight;
        cmm_object_data[0].type = OBJECT_TYPE_SPAWN;

        cmm_save.option[19] = cmm_lopt_game;
        cmm_save.option[7] = cmm_lopt_size;

        cmm_save.option[1] = cmm_templates[cmm_lopt_template].music[cmm_lopt_game];
        cmm_save.option[2] = cmm_templates[cmm_lopt_template].envfx;
        cmm_save.option[3] = cmm_templates[cmm_lopt_template].theme;
        cmm_save.option[4] = cmm_templates[cmm_lopt_template].bg;
        cmm_save.option[5] = cmm_templates[cmm_lopt_template].plane;

        if (cmm_templates[cmm_lopt_template].platform) {
            u8 i = 0;
            for (s8 x = -1; x <= 1; x++) {
                for (s8 z = -1; z <= 1; z++) {
                    cmm_tile_data[i].x = 32+x;
                    cmm_tile_data[i].y = 0;
                    cmm_tile_data[i].z = 32+z;
                    cmm_tile_data[i].type = TILE_TYPE_BLOCK;
                    cmm_tile_data[i].mat = 0;
                    i++;
                }
            }
            cmm_save.tile_count = i;
        }
    }
    f_chdir("..");

    cmm_tile_count = cmm_save.tile_count;
    cmm_object_count = cmm_save.object_count;

    cmm_lopt_costume = cmm_save.option[0];

    cmm_lopt_seq = cmm_save.option[1];
    set_album_and_song_from_seq();
    bcopy(&cmm_settings_music_albums[cmm_lopt_seq_album], &cmm_settings_music_buttons[2], sizeof(struct cmm_settings_button));
    cmm_lopt_envfx = cmm_save.option[2];
    cmm_lopt_theme = cmm_save.option[3];
    cmm_lopt_bg = cmm_save.option[4];

    cmm_settings_terrain_buttons[2].size = cmm_theme_table[cmm_lopt_theme].numFloors + 1;
    cmm_lopt_plane = cmm_save.option[5];
    cmm_lopt_coinstar = cmm_save.option[6];
    cmm_lopt_size = cmm_save.option[7];
    cmm_lopt_waterlevel = cmm_save.option[8];
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

    //init theme specific things
    switch(cmm_lopt_game) {
        case CMM_GAME_BTCM:
            bcopy(&cmm_toolbox_btcm,&cmm_toolbox,sizeof(cmm_toolbox));
            cmm_exclamation_box_contents = sExclamationBoxContents_btcm;
            cmm_object_type_preview_mario.model_id = MODEL_MARIO;
            cmm_settings_menu_lengths[0] = ARRAY_COUNT(cmm_settings_general_buttons); // includes costume
            cmm_settings_menus[0] = draw_cmm_settings_general;
            break;
        case CMM_GAME_VANILLA:
            bcopy(&cmm_toolbox_vanilla,&cmm_toolbox,sizeof(cmm_toolbox));
            cmm_exclamation_box_contents = sExclamationBoxContents_vanilla;
            //cmm_object_type_preview_mario.model_id = MODEL_MARIO2;
            cmm_settings_menu_lengths[0] = ARRAY_COUNT(cmm_settings_general_buttons_vanilla); // no costume
            cmm_settings_menus[0] = draw_cmm_settings_general_vanilla;
            break;
    }
    //reset toolbar
    bcopy(&cmm_toolbar_defaults,&cmm_toolbar,sizeof(cmm_toolbar_defaults));

    load_segment_decompress_skybox(0xA,cmm_skybox_table[cmm_lopt_bg*2],cmm_skybox_table[cmm_lopt_bg*2+1]);

    u32 oldIndex = 0;
    cmm_tile_data_indices[0] = 0;
    // Load tiles and build index list. Assume all tiles are in order
    for (i = 0; i < cmm_tile_count; i++) {
        //bcopy(&cmm_save.tiles[i],&cmm_tile_data[i],sizeof(cmm_tile_data[i]));
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
        //bcopy(&cmm_save.objects[i],&cmm_object_data[i],sizeof(cmm_object_data[i]));
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
    load_level();
    if (cmm_level_action == CMM_LA_PLAYING) {
        generate_terrain_gfx();
        generate_terrain_collision();
    } else {
        vec3_set(cmm_cursor_pos, 32, 0, 32);
        cmm_camera_foc[0] = GRID_TO_POS(32);
        cmm_camera_foc[1] = 0.0f;
        cmm_camera_foc[2] = GRID_TO_POS(32);
    }
}

void sb_init(void) {
    struct Object *spawn_obj;

    cmm_toolbar_index = 0;
    load_segment_decompress_skybox(0xA,cmm_skybox_table[cmm_lopt_bg*2],cmm_skybox_table[cmm_lopt_bg*2+1]);

    switch(cmm_mode) {
        case CMM_MODE_MAKE:
            cmm_menu_state = CMM_MAKE_MAIN;
            o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            generate_object_preview();
            generate_terrain_gfx();

            //init visual tile bounds
            for (u8 i=0; i<6; i++) {
                cmm_boundary_object[i] = spawn_object(o,MODEL_MAKER_BOUNDARY,bhvStaticObject);
            }
            cmm_boundary_object[2]->oFaceAngleRoll = -0x4000;
            cmm_boundary_object[3]->oFaceAngleRoll = -0x4000;
            cmm_boundary_object[4]->oFaceAnglePitch = 0x4000;
            cmm_boundary_object[5]->oFaceAnglePitch = 0x4000;

            if (gMarioState->Options & (1<<OPT_MUSIC)) {
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, seq_musicmenu_array[cmm_lopt_seq]), 0);
            }
        break;
        case CMM_MODE_PLAY:
            cmm_menu_state = CMM_MAKE_PLAY;
            generate_terrain_collision();
            generate_objects_to_level();
            load_obj_warp_nodes();

            spawn_obj = cur_obj_nearest_object_with_behavior(bhvSpawn);
            if (spawn_obj) {
                if (cmm_level_action == CMM_LA_MAKING) {
                    gMarioState->pos[0] = (f32)(GRID_TO_POS(cmm_cursor_pos[0]));
                    gMarioState->pos[1] = (f32)(GRIDY_TO_POS(cmm_cursor_pos[1]));
                    gMarioState->pos[2] = (f32)(GRID_TO_POS(cmm_cursor_pos[2]));
                    set_mario_action(gMarioState,ACT_IDLE,0);
                    gMarioState->faceAngle[1] = cmm_rot_selection*0x4000;
                } else {
                    gMarioState->faceAngle[1] = spawn_obj->oFaceAngleYaw;
                    vec3_copy(gMarioState->pos,&spawn_obj->oPosVec);
                }
                gMarioState->pos[1] -= TILE_SIZE/2;

                reset_camera(gCurrentArea->camera);

                struct Object *warpobj = cur_obj_nearest_object_with_behavior(bhvSpinAirborneWarp);
                if (warpobj) {
                    vec3_copy(&warpobj->oPosVec,&spawn_obj->oPosVec);
                    warpobj->oPosY -= TILE_SIZE/2;
                }
            }

            o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;

            if (gMarioState->Options & (1<<OPT_MUSIC)) {
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, seq_musicmenu_array[cmm_lopt_seq]), 0);
            }
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

    o->oPosX = GRID_TO_POS(cmm_cursor_pos[0]); 
    o->oPosY = GRIDY_TO_POS(cmm_cursor_pos[1]); 
    o->oPosZ = GRID_TO_POS(cmm_cursor_pos[2]); 

    return cursorMoved;
}

void update_boundary_wall() {
    for (u8 i=0; i<6; i++) {
        vec3_copy(&cmm_boundary_object[i]->oPosVec,&o->oPosVec);
    }
    cmm_boundary_object[0]->oPosY = GRIDY_TO_POS(0);
    cmm_boundary_object[1]->oPosY = GRIDY_TO_POS(32);
    cmm_boundary_object[2]->oPosX = GRID_TO_POS(cmm_grid_min);
    cmm_boundary_object[3]->oPosX = GRID_TO_POS(cmm_grid_min + cmm_grid_size);
    cmm_boundary_object[4]->oPosZ = GRID_TO_POS(cmm_grid_min);
    cmm_boundary_object[5]->oPosZ = GRID_TO_POS(cmm_grid_min + cmm_grid_size);

    if (!cmm_ui_do_render) {
        for (int i=0; i<6; i++) {
            cmm_boundary_object[i]->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
        }
    } else {
        for (int i=0; i<6; i++) {
            cmm_boundary_object[i]->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        }
    }
}

void delete_preview_object(void) {
    struct Object *previewObj = cur_obj_nearest_object_with_behavior(bhvCurrPreviewObject);
    while (previewObj) {
        unload_object(previewObj);
        previewObj = cur_obj_nearest_object_with_behavior(bhvCurrPreviewObject);
    }
}

void (*cmm_option_changed_func)(void) = NULL;

void reload_theme(void) {
    generate_terrain_gfx();
    cmm_settings_terrain_buttons[2].size = cmm_theme_table[cmm_lopt_theme].numFloors + 1;
    if (cmm_lopt_plane > cmm_settings_terrain_buttons[2].size - 1) {
        cmm_lopt_plane = cmm_settings_terrain_buttons[2].size - 1;
    }

    generate_object_preview();
}

void reload_bg(void) {
    load_segment_decompress_skybox(0xA,cmm_skybox_table[cmm_lopt_bg*2],cmm_skybox_table[cmm_lopt_bg*2+1]);
}

u8 cmm_upsidedown_tile = FALSE;
u8 cmm_joystick;
extern s16 cmm_menu_start_timer;
extern s16 cmm_menu_end_timer;

void sb_loop(void) {
    Vec3f cam_pos_offset = {0.0f,cmm_current_camera_zoom[1],0};
    cmm_joystick = joystick_direction();
    u8 cursorMoved = FALSE;

    if (cmm_do_save) {
        cmm_do_save = FALSE;
        save_level();
    }

    cmm_camera_angle = approach_s16_asymptotic(cmm_camera_angle,cmm_camera_rot_offset*0x4000,4);
    cam_pos_offset[0] = sins(cmm_camera_angle+0x8000)*cmm_current_camera_zoom[0];
    cam_pos_offset[2] = coss(cmm_camera_angle+0x8000)*cmm_current_camera_zoom[0];

    cmm_current_camera_zoom[0] = lerp(cmm_current_camera_zoom[0], cmm_camera_zoom_table[cmm_camera_zoom_index][0],0.2f);
    cmm_current_camera_zoom[1] = lerp(cmm_current_camera_zoom[1], cmm_camera_zoom_table[cmm_camera_zoom_index][1],0.2f);

    if (cmm_option_changed_func) {
        cmm_option_changed_func();
        cmm_option_changed_func = NULL;
    }

    switch(cmm_menu_state) {
        case CMM_MAKE_MAIN:
            cursorMoved = main_cursor_logic(cmm_joystick);
            s32 updatePreviewObj = cursorMoved;

            if (gPlayer1Controller->buttonPressed & L_TRIG) {
                cmm_toolbar_index--;
                cmm_param_selection = 0;
                updatePreviewObj = TRUE;
            }
            if (gPlayer1Controller->buttonPressed & R_TRIG) {
                cmm_toolbar_index++;
                cmm_param_selection = 0;
                updatePreviewObj = TRUE;
            }
            cmm_toolbar_index = (cmm_toolbar_index+9)%9;
            cmm_id_selection = cmm_ui_buttons[cmm_toolbar[cmm_toolbar_index]].id;
            cmm_place_mode = cmm_ui_buttons[cmm_toolbar[cmm_toolbar_index]].placeMode;

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
            if (cmm_place_mode != CMM_PM_OBJ || cmm_object_place_types[cmm_id_selection].maxParams != 0) {
                if (gPlayer1Controller->buttonPressed & L_JPAD) {
                    cmm_param_selection --;
                    updatePreviewObj = TRUE;
                }
                if (gPlayer1Controller->buttonPressed & R_JPAD) {
                    cmm_param_selection ++;
                    updatePreviewObj = TRUE;
                }
            }

            //Single A press
            if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                switch(cmm_toolbar_index) {
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
                        cmm_menu_start_timer = 0;
                        cmm_menu_end_timer = -1;
                        cmm_menu_index = 0;
                    break;
                    case 6://test
                        cmm_target_mode = CMM_MODE_PLAY;
                        reset_play_state();
                        level_trigger_warp(gMarioState, WARP_OP_LOOK_UP);
                        sSourceWarpNodeId = 0x0A;
                    break;
                    default://everything else places
                        place_thing_action();
                    break; 
                }
            } else if (gPlayer1Controller->buttonDown & A_BUTTON && cursorMoved) {
                if (cmm_toolbar_index < 6) {
                    place_thing_action();
                }
            }

            if (gPlayer1Controller->buttonPressed & B_BUTTON || ((gPlayer1Controller->buttonDown & B_BUTTON) && cursorMoved)) {
                delete_tile_action(cmm_cursor_pos);
            }

            if (gPlayer1Controller->buttonPressed & START_BUTTON) {
                cmm_menu_start_timer = 0;
                cmm_menu_end_timer = -1;
                cmm_menu_index = 0;
                cmm_menu_state = CMM_MAKE_TOOLBOX;
                if (cmm_toolbar_index > 5) {
                    cmm_toolbar_index = 5;
                }
            }

            if (gPlayer1Controller->buttonPressed & Z_TRIG) {
                if (gPlayer1Controller->buttonDown & B_BUTTON) {
                    cmm_upsidedown_tile ^= 1;
                } else {
                    cmm_rot_selection++;
                    cmm_rot_selection%=4;
                    updatePreviewObj = TRUE;
                }
            }

            if (cmm_place_mode == CMM_PM_OBJ) {
                if (cmm_object_place_types[cmm_id_selection].maxParams != 0) {
                    s16 max = cmm_object_place_types[cmm_id_selection].maxParams;
                    cmm_param_selection = (cmm_param_selection+max)%max;
                }

                if (updatePreviewObj) {
                    delete_preview_object();
                }
            } else {
                delete_preview_object();
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

            struct Object *spawnobjp = get_spawn_preview_object();
            if (spawnobjp) {
                if (!cmm_ui_do_render) {
                    spawnobjp->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
                } else {
                    spawnobjp->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
                }  
            }

            update_boundary_wall();
        break;
        case CMM_MAKE_PLAY://PLAY MODE

        break;
        case CMM_MAKE_TOOLBOX: //MAKE MODE TOOLBOX
            //TOOLBOX CONTROLS
            delete_preview_object();
            if (cmm_joystick != 0) {
                switch((cmm_joystick-1)%4) {
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
                cmm_toolbar_index--;
                cmm_toolbox_transition_btn_render = FALSE;
            }
            if (gPlayer1Controller->buttonPressed & R_TRIG) {
                cmm_toolbar_index++;
                cmm_toolbox_transition_btn_render = FALSE;
            }
            cmm_toolbar_index = (cmm_toolbar_index+6)%6;
            cmm_id_selection = cmm_ui_buttons[cmm_toolbar[cmm_toolbar_index]].id;
            cmm_place_mode = cmm_ui_buttons[cmm_toolbar[cmm_toolbar_index]].placeMode;

            //PRESS A TO MOVE FROM TOOLBOX TO TOOLBAR
            if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                //You can not put a blank button into the toolbox
                if ( cmm_toolbox[cmm_toolbox_index] != CMM_BUTTON_BLANK) {
                    cmm_param_selection = 0;

                    cmm_toolbox_transition_btn_render = TRUE;
                    cmm_toolbox_transition_btn_progress = 0.0f;
                    cmm_toolbox_transition_btn_ox = 34+((cmm_toolbox_index%9)*32);
                    cmm_toolbox_transition_btn_oy = 220-((cmm_toolbox_index/9)*32);
                    cmm_toolbox_transition_btn_x = 34+((cmm_toolbox_index%9)*32);
                    cmm_toolbox_transition_btn_y = 220-((cmm_toolbox_index/9)*32);
                    cmm_toolbox_transition_btn_tx = 34.0f+(cmm_toolbar_index*32.0f);
                    cmm_toolbox_transition_btn_ty = 28.0f;
                    cmm_toolbox_transition_btn_old_gfx = cmm_ui_buttons[cmm_toolbar[cmm_toolbar_index]].material;
                    if (cmm_ui_buttons[cmm_toolbar[cmm_toolbar_index]].multipleBtns) {
                        cmm_toolbox_transition_btn_old_gfx = ((Gfx **)cmm_toolbox_transition_btn_old_gfx)[0];
                    }

                    cmm_toolbox_transition_btn_gfx = cmm_ui_buttons[cmm_toolbox[cmm_toolbox_index]].material;
                    if (cmm_ui_buttons[cmm_toolbox[cmm_toolbox_index]].multipleBtns) {
                        s32 idx = (cmm_toolbox_index == cmm_toolbar_index ? cmm_param_selection : 0);
                        cmm_toolbox_transition_btn_gfx = ((Gfx **)cmm_toolbox_transition_btn_gfx)[0];
                    }

                    cmm_toolbar[cmm_toolbar_index] = cmm_toolbox[cmm_toolbox_index];

                    play_sound(SOUND_ACTION_BRUSH_HAIR, gGlobalSoundSource);
                } else {
                    //error sound
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
            }

            if (cmm_menu_end_timer == 10) {
                cmm_menu_state = CMM_MAKE_MAIN;
                cmm_toolbox_transition_btn_render = FALSE;
            }
        break;
        case CMM_MAKE_SETTINGS: //settings
            if (cmm_menu_end_timer == 10) {
                cmm_menu_state = CMM_MAKE_MAIN;
            }
        break;
        case CMM_MAKE_TRAJECTORY: //trajectory maker
            delete_preview_object();
            cursorMoved = main_cursor_logic(cmm_joystick);

            if (cursorMoved) {
                generate_trajectory_gfx();
            }

            if (cmm_trajectory_edit_index == 0) {
                // Initial placement on top of the object
                cmm_trajectory_list[cmm_trajectory_to_edit][0][0] = 0;
                cmm_trajectory_list[cmm_trajectory_to_edit][0][1] = o->oPosX;
                cmm_trajectory_list[cmm_trajectory_to_edit][0][2] = o->oPosY;
                cmm_trajectory_list[cmm_trajectory_to_edit][0][3] = o->oPosZ;
                cmm_trajectory_list[cmm_trajectory_to_edit][1][0] = -1;
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
                        cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index+1][0] = -1;
                        cmm_trajectory_edit_index++;
                        play_place_sound(SOUND_MENU_CLICK_FILE_SELECT | SOUND_VIBRATO);
                        generate_trajectory_gfx();
                        generate_object_preview();
                    }
                } else if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                    if (cmm_trajectory_edit_index <= 1) {
                        cmm_show_error_message("Nothing to delete!");
                    } else {
                        cmm_trajectory_edit_index--;
                        cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index][0] = -1;
                        play_place_sound(SOUND_GENERAL_DOOR_INSERT_KEY | SOUND_VIBRATO);
                        generate_trajectory_gfx();
                        generate_object_preview();
                    }
                }
            }

            if (gPlayer1Controller->buttonPressed & START_BUTTON) {
                cmm_menu_state = CMM_MAKE_MAIN;
                generate_trajectory_gfx();
                generate_object_preview();
            }

            update_boundary_wall();
        break;
    }

    if (cmm_place_mode == CMM_PM_OBJ) {
        if (cmm_menu_state == CMM_MAKE_MAIN || cmm_menu_state == CMM_MAKE_SETTINGS || cmm_menu_state == CMM_MAKE_TOOLBOX) {
            struct Object *previewObj = cur_obj_nearest_object_with_behavior(bhvCurrPreviewObject);

            if (!previewObj) {
                struct cmm_object_info *info = cmm_object_place_types[cmm_id_selection].info;
                if (cmm_object_place_types[cmm_id_selection].multipleObjs) {
                    info = &info[cmm_param_selection];
                }

                s8 pos[3];
                vec3_set(pos, cmm_cursor_pos[0], cmm_cursor_pos[1], cmm_cursor_pos[2]);
                spawn_preview_object(pos, cmm_rot_selection, 0, cmm_param_selection, info, bhvCurrPreviewObject,FALSE);
            }
        }
    }

    cmm_camera_foc[0] = lerp(cmm_camera_foc[0], GRID_TO_POS(cmm_cursor_pos[0]),  0.2f);
    cmm_camera_foc[1] = lerp(cmm_camera_foc[1], GRIDY_TO_POS(cmm_cursor_pos[1]), 0.2f);
    cmm_camera_foc[2] = lerp(cmm_camera_foc[2], GRID_TO_POS(cmm_cursor_pos[2]),  0.2f);

    vec3_copy(cmm_camera_pos,cmm_camera_foc);
    vec3_add(cmm_camera_pos,cam_pos_offset);
}

#include "src/game/cursed_mirror_maker_menu.inc.c"
