//object includes (a lot)
#include "text_strings.h"
#include "types.h"
#include "actors/common0.h"
#include "actors/common1.h"
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
#include "actors/group14.h"
#include "actors/group17.h"
#include "sram.h"
#include "level_geo.h"
#include "src/buffers/framebuffers.h"
#include "memory.h"
#include "geo_misc.h"
#include "mario_actions_automatic.h"
#include "levels/scripts.h"
#include "emutest.h"

#include "libcart/include/cart.h"
#include "libcart/ff/ff.h"

extern void super_cum_working(struct Object *obj, s32 animIndex);

u8 cmm_level_action = CMM_LA_BUILD;
u8 cmm_mode = CMM_MODE_UNINITIALIZED;
u8 cmm_target_mode = CMM_MODE_MAKE;
u8 cmm_joystick_timer = 0;
s8 cmm_cursor_pos[3] = {32,0,32};

Vec3f cmm_camera_pos = {0.0f,0.0f,0.0f};
Vec3f cmm_camera_pos_prev;
Vec3f cmm_camera_foc = {0.0f,0.0f,0.0f};
f32 cmm_camera_fov = 45.0f;
s16 cmm_camera_angle = 0;
u8 cmm_camera_rot_offset = 0;
s8 cmm_camera_zoom_index = 2;
f32 cmm_current_camera_zoom[2] = {1500.0f,800.0f};

u8 cmm_place_mode = CMM_PM_NONE;

s8 cmm_id_selection = 0;
u8 cmm_rot_selection = 0;
s16 cmm_param_selection = 0;
s16 cmm_mat_selection = 0;

struct cmm_grid_obj cmm_grid_data[64][64][64] = {0};

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
u16 cmm_object_limit_count = 0; // Tracks additional objects like in coin formations, flame spinners
u16 cmm_building_collision = FALSE; // 0 = building gfx, 1 = building collision

struct Object *cmm_boundary_object[6]; //one for each side

Trajectory cmm_trajectory_list[CMM_MAX_TRAJECTORIES][CMM_TRAJECTORY_LENGTH][4];
u16 cmm_trajectory_edit_index = 0;
u8 cmm_trajectory_to_edit = 0;
u8 cmm_trajectories_used = 0;
u8 cmm_txt_recording[] = {TXT_RECORDING};
u8 cmm_txt_freecam[] = {TXT_FREECAM};

Vtx *cmm_curr_vtx;
Gfx *cmm_curr_gfx;
u16 cmm_gfx_index;

u8 cmm_use_alt_uvs = FALSE; // Used for decals and special tile shapes
s8 cmm_uv_offset = -16;
u8 cmm_render_flip_normals = FALSE; // Used for drawing water tiles
u8 cmm_render_culling_off = FALSE; // Used for drawing preview blocks in custom theme menu
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
u8 cmm_lopt_boundary_mat = 0;
u8 cmm_lopt_boundary = 0;
u8 cmm_lopt_boundary_height = 0;
u8 cmm_lopt_game = 0;//0 = BTCM, 1 = VANILLA
u8 cmm_lopt_size = 0;
u8 cmm_newsize = 0; // Used for changing level sizes
u8 cmm_lopt_template = 0;
u8 cmm_lopt_coinstar = 0;
u8 cmm_lopt_waterlevel = 0;
u8 cmm_lopt_secret = 0;

//UI
u8 cmm_menu_state = CMM_MAKE_MAIN;
s8 cmm_menu_index = 0;
s8 cmm_menu_index_max = 1;
s8 cmm_toolbar_index = 0;
s8 cmm_toolbox_index = 0;
u8 cmm_prepare_level_screenshot = FALSE;
u8 cmm_do_save = FALSE;

char *cmm_topleft_message = NULL;
u8 cmm_topleft_is_tip = FALSE;
u16 cmm_topleft_max_timer = 120;
u16 cmm_topleft_timer = 0;
f32 cmm_topleft_vels[3];

struct cmm_level_save_header cmm_save;
char cmm_username[31];
u8 cmm_has_username = FALSE;

u8 cmm_num_vertices_cached = 0;
u8 cmm_num_tris_cached = 0;
u8 cmm_cached_tris[16][3];
s16 cmm_tip_timer = 0;

struct ExclamationBoxContents *cmm_exclamation_box_contents;

#include "src/game/cursed_mirror_maker_df.inc.c"
#include "src/game/cursed_mirror_maker_data.inc.c"

void bhv_preview_object_init(void) {
    if (!o->oPreviewObjDisplayFunc) return;
    ((DisplayFunc)o->oPreviewObjDisplayFunc)(CMM_DF_CONTEXT_INIT);
}
void bhv_preview_object_loop(void) {
    if (!o->oPreviewObjDisplayFunc) return;
    ((DisplayFunc)o->oPreviewObjDisplayFunc)(CMM_DF_CONTEXT_MAIN);
}

void play_place_sound(u32 soundBits) {
    play_sound(soundBits, gGlobalSoundSource);
}

void cmm_show_topleft_message(char *message, s32 isTip) {
    cmm_topleft_is_tip = isTip;
    cmm_topleft_max_timer = (isTip ? 220 : 120);
    if ((message != cmm_topleft_message) || (cmm_topleft_timer < 30)) {
        cmm_topleft_message = message;
        cmm_topleft_timer = cmm_topleft_max_timer;
    } else {
        if (cmm_topleft_timer < cmm_topleft_max_timer - 30) cmm_topleft_timer = cmm_topleft_max_timer - 30;
    }
}
void cmm_show_error_message(char *message) {
    cmm_show_topleft_message(message, FALSE);
    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
}
void cmm_show_tip() {
    s32 count = ARRAY_COUNT(cmm_tips);
    if (cmm_lopt_game != CMM_GAME_BTCM) count -= NUM_BTCM_TIPS;
    cmm_show_topleft_message(cmm_tips[(s32)(random_float() * count)], TRUE);
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
    if (pos[1] < 0 || pos[1] > 63) return FALSE;
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

// Get number of extra objects used by an object
s32 get_extra_objects(struct cmm_object_info *info, s32 param) {
    if (info == &cmm_object_type_fire_spinner) {
        return (param + 2) * 2;
    }
    if (info == &cmm_object_type_coin_formation) {
        return (param <= 1 ? 5 : 8);
    }
    return info->numExtraObjects;
}

s32 object_sanity_check(void) {
    struct cmm_object_info *info = cmm_object_place_types[cmm_id_selection].info;
    if (cmm_object_place_types[cmm_id_selection].multipleObjs) {
        info = &info[cmm_param_selection];
    }
    if (cmm_object_limit_count + get_extra_objects(info, cmm_param_selection) >= CMM_MAX_OBJS) {
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

    if ((cmm_id_selection == OBJECT_TYPE_STAR) && ((cmm_param_selection == 1) || (cmm_param_selection == 2))) {
        for (u32 i = 0; i < cmm_object_count; i++) {
            if ((cmm_object_data[i].type == OBJECT_TYPE_STAR) && (cmm_object_data[i].param2 == cmm_param_selection)) {
                if (cmm_param_selection == 1) {
                    cmm_show_error_message("Red Coin Star already placed!");
                } else {
                    cmm_show_error_message("Piranha Star already placed!");
                }
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

#define place_terrain_data(pos, type_, rot_, mat_) {        \
    cmm_grid_data[pos[0]][pos[1]][pos[2]].rot = rot_;       \
    cmm_grid_data[pos[0]][pos[1]][pos[2]].type = type_ + 1; \
    cmm_grid_data[pos[0]][pos[1]][pos[2]].mat = mat_;       \
    cmm_grid_data[pos[0]][pos[1]][pos[2]].waterlogged = 0;  \
}

#define remove_terrain_data(pos) {                         \
    cmm_grid_data[pos[0]][pos[1]][pos[2]].rot = 0;         \
    cmm_grid_data[pos[0]][pos[1]][pos[2]].type = 0;        \
    cmm_grid_data[pos[0]][pos[1]][pos[2]].mat = 0;         \
    cmm_grid_data[pos[0]][pos[1]][pos[2]].waterlogged = 0; \
}

#define get_grid_tile(pos) (&(cmm_grid_data[(pos)[0]][(pos)[1]][(pos)[2]]))

#define rotate_direction(dir, rot) (cmm_rotated_dirs[rot][dir])

u32 get_faceshape(s8 pos[3], u32 dir) {
    struct cmm_terrain *terrain;
    if (cmm_render_culling_off) return CMM_FACESHAPE_EMPTY;
    s8 tileType = get_grid_tile(pos)->type - 1;
    if (tileType == -1) return CMM_FACESHAPE_EMPTY;

    if (tileType == TILE_TYPE_POLE) terrain = &cmm_terrain_pole;
    else terrain = cmm_tile_terrains[tileType];

    if (!terrain) return CMM_FACESHAPE_EMPTY;

    u8 rot = get_grid_tile(pos)->rot;
    dir = rotate_direction(dir,((4-rot) % 4)) ^ 1;

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

#define place_occupy_data(pos) { \
    cmm_grid_data[pos[0]][pos[1]][pos[2]].occupied = TRUE; \
}

#define remove_occupy_data(pos) { \
    cmm_grid_data[pos[0]][pos[1]][pos[2]].occupied = FALSE; \
}

#define get_occupy_data(pos) (coords_in_range(pos) ? get_grid_tile(pos)->occupied : FALSE)

s8 cullOffsetLUT[6][3] = {
    {0, 1, 0},
    {0, -1, 0},
    {1, 0, 0},
    {-1, 0, 0},
    {0, 0, 1},
    {0, 0, -1},
};

#define fullblock_can_be_waterlogged(mat) ((MATERIAL(mat).type == MAT_CUTOUT) || (TOPMAT(mat).type == MAT_CUTOUT))

// Classifications for culling checks.
// Lower types of faces cull higher types of faces
enum BlockSideClassifications {
    CLASS_OPAQUE, // < CUTOUT
    CLASS_HOLLOW_TRANSPARENT,
    CLASS_HOLLOW_CUTOUT,
    CLASS_TRANSPARENT, // > CUTOUT
    CLASS_CUTOUT, // = CUTOUT
};

u32 get_side_class(u32 mat, u32 dir) {
    u32 mattype = TOPMAT(mat).type;
    if (dir != CMM_DIRECTION_UP) {
        mattype = MATERIAL(mat).type;
        if (mattype < MAT_CUTOUT) {
            if (TOPMAT(mat).type == MAT_CUTOUT) return CLASS_HOLLOW_CUTOUT;
            if (TOPMAT(mat).type > MAT_CUTOUT) return CLASS_HOLLOW_TRANSPARENT;
        }
    }
    if (mattype < MAT_CUTOUT) return CLASS_OPAQUE;
    if (mattype == MAT_CUTOUT) return CLASS_CUTOUT;
    return CLASS_TRANSPARENT;
}

// Used to compare material types and see if any future culling checks can be skipped
// WARNING! using grid tile ->mat directly will result in mat being 0 if the tile is empty/water
s32 cutout_skip_culling_check(s32 curMat, s32 otherMat, s32 direction) {
    s32 curMatClass, otherMatClass;
    if (curMat == otherMat) return FALSE;
    curMatClass = get_side_class(curMat, direction);
    otherMatClass = get_side_class(otherMat, direction^1);
    if (curMatClass == otherMatClass) {
        return (curMatClass == CLASS_TRANSPARENT);
    } else {
        if ((curMatClass == CLASS_HOLLOW_CUTOUT) || (curMatClass == CLASS_HOLLOW_TRANSPARENT)) {
            if (direction == CMM_DIRECTION_DOWN) {
                if (get_side_class(otherMat, CMM_DIRECTION_DOWN) == curMatClass) return FALSE;
            }
        }
        return (curMatClass < otherMatClass);
    }
}

// Used for determining if a water side should be culled.
u32 block_side_is_solid(s32 adjMat, s32 mat, s32 direction) {
    s32 mattype = TOPMAT(adjMat).type;
    if (direction != CMM_DIRECTION_DOWN) {
        mattype = MATERIAL(adjMat).type;
    }
    if (mattype == MAT_CUTOUT) return FALSE;
    if (mat == -1) return TRUE; // adjMat should be confirmed to have a full face
    return cutout_skip_culling_check(mat, adjMat, direction);
}

s32 should_cull(s8 pos[3], s32 direction, s32 faceshape, s32 rot) {
    if (faceshape == CMM_FACESHAPE_EMPTY) return FALSE;
    if (cmm_render_culling_off) return FALSE;
    direction = rotate_direction(direction, rot);

    s8 newpos[3];
    vec3_sum(newpos, pos, cullOffsetLUT[direction]);
    if (!coords_in_range(newpos)) {
        if (direction == CMM_DIRECTION_UP) return FALSE;
        if (direction == CMM_DIRECTION_DOWN) {
            return (cmm_boundary_table[cmm_lopt_boundary] & CMM_BOUNDARY_INNER_FLOOR) != 0;
        }
        return ((cmm_boundary_table[cmm_lopt_boundary] & CMM_BOUNDARY_INNER_WALLS) && (pos[1] < cmm_lopt_boundary_height));
    }
    s32 tileType = get_grid_tile(newpos)->type - 1;
    switch(tileType) {
        case TILE_TYPE_CULL:
            return TRUE;
        case TILE_TYPE_TROLL:
            if (cmm_building_collision) return FALSE;
            break;
    }

    if (cutout_skip_culling_check(get_grid_tile(pos)->mat, get_grid_tile(newpos)->mat, direction)) return FALSE;
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
    direction = rotate_direction(direction, rot);

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
        if (curr_trajectory[0][0] == -1) continue;
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
            vec3_set(pos2, GRID_TO_POS(cmm_cursor_pos[0]), GRID_TO_POS(cmm_cursor_pos[1]), GRID_TO_POS(cmm_cursor_pos[2]));
            draw_dotted_line(pos1, pos2);
        }
        if (isLoop) {
            vec3_set(pos1, curr_trajectory[0][1], curr_trajectory[0][2], curr_trajectory[0][3]);
            draw_dotted_line(pos2, pos1);
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
    direction = rotate_direction(direction, rot);
    switch (direction) {
        case CMM_DIRECTION_NEG_X: *uAxis = 2; *vAxis = 1; return TRUE;
        case CMM_DIRECTION_POS_X: *uAxis = 2; *vAxis = 1; return FALSE;
        case CMM_DIRECTION_DOWN: *uAxis = 2; *vAxis = 0; return FALSE;
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
            GRID_TO_POS(pos[0]) + ((newVtx[i][0] - 8) * 16),
            GRID_TO_POS(pos[1]) + ((newVtx[i][1] - 8) * 16),
            GRID_TO_POS(pos[2]) + ((newVtx[i][2] - 8) * 16),
            (u * 64 + cmm_uv_offset), (v * 64 + cmm_uv_offset),
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
            GRID_TO_POS(pos[1]) + ((newVtx[i][1] - 8) * 16),
            GRID_TO_POS(pos[2]) + ((newVtx[i][2] - 8) * 16),
            (u * 64 + cmm_uv_offset), (v * 64 + cmm_uv_offset),
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
        colVtxs[k][0] = GRID_TO_POS(pos[0]) + ((newVtx[k][0] - 8) * (TILE_SIZE/16)),
        colVtxs[k][1] = GRID_TO_POS(pos[1]) + ((newVtx[k][1] - 8) * (TILE_SIZE/16)),
        colVtxs[k][2] = GRID_TO_POS(pos[2]) + ((newVtx[k][2] - 8) * (TILE_SIZE/16));
    }
    cmm_create_surface(colVtxs[0], colVtxs[1], colVtxs[2]);
    cmm_create_surface(colVtxs[1], colVtxs[3], colVtxs[2]);
}

void cmm_create_tri(struct cmm_terrain_tri *tri, s8 pos[3], u32 rot) {
    s8 newVtx[3][3];
    cmm_transform_vtx_with_rot(newVtx, tri->vtx, 3, rot);
    for (u32 k = 0; k < 3; k++) {
        colVtxs[k][0] = GRID_TO_POS(pos[0]) + ((newVtx[k][0] - 8) * (TILE_SIZE/16)),
        colVtxs[k][1] = GRID_TO_POS(pos[1]) + ((newVtx[k][1] - 8) * (TILE_SIZE/16)),
        colVtxs[k][2] = GRID_TO_POS(pos[2]) + ((newVtx[k][2] - 8) * (TILE_SIZE/16));
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

u32 render_grass_slope_extra_decal(s8 pos[3], u32 direction, u32 grassType) {
    // Check if below block is in range
    s8 newpos[3];
    vec3_set(newpos, pos[0], pos[1]-1, pos[2]);
    if (!coords_in_range(newpos)) return TRUE;

    // Check if below block matches material
    u8 curMat = get_grid_tile(pos)->mat;
    u8 belowMat = get_grid_tile(newpos)->mat;
    if (curMat != belowMat) return TRUE;

    // Check if below block is right shape and culled
    // Shape of face of above block on same side
    s32 otherFaceshape = get_faceshape(newpos, direction^1);
    if (should_cull(newpos, direction, otherFaceshape, 0)) return;
    if (should_cull_topslab_check(newpos, direction, 0)) return;
    
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

    s32 index;
    s32 isQuad;

    switch (otherFaceshape) {
        default:
            return;
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
        case CMM_FACESHAPE_HALFSIDE_1:
            index = 4;
            isQuad = TRUE;
            break;
        case CMM_FACESHAPE_HALFSIDE_2:
            index = 5;
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
    return;
}

u32 should_render_grass_side(s8 pos[3], u32 direction, u32 faceshape, u32 rot, u32 grassType) {
    s8 abovePos[3];
    vec3_set(abovePos, pos[0], pos[1]+1, pos[2]);
    if (should_cull(pos, direction, faceshape, rot)) return FALSE;
    if (!coords_in_range(abovePos)) return TRUE;

    // Render extra decal for slopes if necessary
    // The side of the slope itself is unconditional and will always render
    if (grassType == CMM_GROWTH_SLOPE_SIDE_L || grassType == CMM_GROWTH_SLOPE_SIDE_R) {
        render_grass_slope_extra_decal(pos, rotate_direction(direction, rot), grassType);
        return TRUE;
    }

    // Other sides that don't care about the above block (e.g. bottom slab)
    if (grassType == CMM_GROWTH_UNCONDITIONAL) return TRUE;

    // Render if above tile is empty
    if (get_grid_tile(abovePos)->type == 0) return TRUE;
    // Render if above tile is seethrough (some exceptions)
    if (cutout_skip_culling_check(get_grid_tile(pos)->mat, get_grid_tile(abovePos)->mat, CMM_DIRECTION_UP)) return TRUE;

    s32 otherFaceshape;
    switch (grassType) {
        case CMM_GROWTH_NORMAL_SIDE:
        case CMM_GROWTH_HALF_SIDE:
            // Shape of face of above block on same side
            if (should_cull_topslab_check(pos, direction, rot)) return FALSE;
            otherFaceshape = get_faceshape(abovePos, rotate_direction(direction, rot)^1);
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
            u8 faceshape1 = get_faceshape(abovePos, rotate_direction(CMM_DIRECTION_POS_Z, rot)^1);
            u8 faceshape2 = get_faceshape(abovePos, rotate_direction(CMM_DIRECTION_POS_X, rot)^1);
            // this is basically just checking for if a normal slope corner is on top at the right angle
            if (faceshape1 == CMM_FACESHAPE_TRI_1 && faceshape2 == CMM_FACESHAPE_TRI_2)
                return FALSE;
            // don't display if either face on top of the inside corner is full
            return !((faceshape1 == CMM_FACESHAPE_FULL || faceshape1 == CMM_FACESHAPE_BOTTOMSLAB)
                || (faceshape2 == CMM_FACESHAPE_FULL || faceshape2 == CMM_FACESHAPE_BOTTOMSLAB));

        case CMM_GROWTH_DIAGONAL_SIDE:
        case CMM_GROWTH_VSLAB_SIDE:
            otherFaceshape = get_faceshape(abovePos, CMM_DIRECTION_UP);
            if (otherFaceshape == CMM_FACESHAPE_FULL) return FALSE;
            if (otherFaceshape != (grassType == CMM_GROWTH_DIAGONAL_SIDE ? CMM_FACESHAPE_TOPTRI : CMM_FACESHAPE_TOPHALF)) return TRUE;
            u8 otherrot = get_grid_tile(abovePos)->rot;
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
        s32 dir = rotate_direction(CMM_DIRECTION_POS_Z, rot);
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
            u32 faceshape = get_faceshape(adjacentPos, updown);
            if (faceshape == CMM_FACESHAPE_FULL) {
                for (u32 rot = 0; rot < 4; rot++) {
                    connections[rot] |= (1 << (updown+1)); // Apply top flag to all bars
                }
                connections[4] |= (1 << (updown + 1));
            } else if (faceshape == CMM_FACESHAPE_TOPHALF) {
                connections[(get_grid_tile(adjacentPos)->rot + 2) % 4] |= (1 << (updown + 1));
            } else if (get_grid_tile(adjacentPos)->type - 1 == TILE_TYPE_BARS) {
                check_bar_side_connections(adjacentPos, adjacentConnections);
                for (u32 rot = 0; rot < 4; rot++) {
                    connections[rot] |= adjacentConnections[rot] << (updown+1); // Apply top flag to all bars
                }
                connections[4] |= (1 << (updown + 1));
            }
        } else if ((adjacentPos[1] == -1) && (cmm_boundary_table[cmm_lopt_boundary] & CMM_BOUNDARY_INNER_FLOOR)) { // Culling for bottom
            for (u32 rot = 0; rot < 5; rot++) {
                connections[rot] |= (1 << 2);
            }
        }
    }
}

void render_bars_side(s8 pos[3], u8 connections[5]) {
    for (u32 rot = 0; rot < 4; rot++) {
        u32 leftRot = (rot + 3) % 4;
        u32 rightRot = (rot + 1) % 4;
        if (BAR_CONNECTED_SIDE(connections[rot])) {
            process_quad(pos, &cmm_terrain_bars_connected_quads[0], rot);
            process_quad(pos, &cmm_terrain_bars_connected_quads[1], rot);
        }
        if (!BAR_CONNECTED_SIDE(connections[rot]) ||
            (BAR_CONNECTED_SIDE(connections[leftRot]) && BAR_CONNECTED_SIDE(connections[rightRot]))) {
            process_quad(pos, cmm_terrain_bars_unconnected_quad, rot);
        }
    }
}

void render_bars_top(s8 pos[3], u8 connections[5]) {
    for (u32 rot = 0; rot < 4; rot++) {
        u32 leftRot = (rot + 3) % 4;
        u32 rightRot = (rot + 1) % 4;
        if (BAR_CONNECTED_SIDE(connections[rot])) {
            if (!BAR_CONNECTED_TOP(connections[rot])) {
                process_quad(pos, &cmm_terrain_bars_connected_quads[2], rot);
            }
            if (!BAR_CONNECTED_BOTTOM(connections[rot])) {
                process_quad(pos, &cmm_terrain_bars_connected_quads[3], rot);
            }
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
    s32 type = get_grid_tile(pos)->type - 1;
    if ((type != TILE_TYPE_WATER) && (type != TILE_TYPE_TROLL)) {
        if (get_faceshape(pos, CMM_DIRECTION_DOWN) == CMM_FACESHAPE_FULL) {
            if (TOPMAT(get_grid_tile(pos)->mat).type != MAT_CUTOUT) {
                return TRUE;
            }
        }
    }
    // Full block if above block has solid bottom face
    if ((get_faceshape(abovePos, CMM_DIRECTION_UP) == CMM_FACESHAPE_FULL) && (MATERIAL(get_grid_tile(abovePos)->mat).type != MAT_CUTOUT)) {
        // If above block is troll, but current block is also troll, then not full block
        if ((type == TILE_TYPE_TROLL) && (get_grid_tile(abovePos)->type - 1 == TILE_TYPE_TROLL)) return FALSE;
        // If bottom block is hollow cutout and top block is some kind of cutout then not full block
        if (type != TILE_TYPE_WATER) {
            u8 curMat = get_grid_tile(pos)->mat;
            u8 aboveMat = get_grid_tile(abovePos)->mat;
            if ((TOPMAT(aboveMat).type == MAT_CUTOUT) && (TOPMAT(curMat).type == MAT_CUTOUT) &&
                (MATERIAL(curMat).type != MAT_CUTOUT)) return FALSE;
        }
        return TRUE;
    }
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

    if (!coords_in_range(adjacentPos)) {
        if (dir == CMM_DIRECTION_UP) return 1;
        u32 type = isFullblock ? 2 : 1;
        if (dir == CMM_DIRECTION_DOWN) {
            return (cmm_boundary_table[cmm_lopt_boundary] & CMM_BOUNDARY_INNER_FLOOR) ? 0 : type;
        }
        return ((cmm_boundary_table[cmm_lopt_boundary] & CMM_BOUNDARY_INNER_WALLS) && (pos[1] < cmm_lopt_boundary_height)) ? 0 : type;
    }
    if (get_grid_tile(adjacentPos)->type - 1 == TILE_TYPE_CULL) return 0;

    if (cmm_building_collision) {
        if (get_grid_tile(adjacentPos)->waterlogged) return 0;
        return isFullblock ? 2 : 1;
    }

    s32 mat = get_grid_tile(pos)->mat;
    s32 adjMat = get_grid_tile(adjacentPos)->mat;
    if ((get_grid_tile(pos)->type - 1) == TILE_TYPE_WATER) {
        mat = -1;
    }
    s32 adjTile = get_grid_tile(adjacentPos)->type - 1;
    if ((adjTile == TILE_TYPE_WATER) || (adjTile == -1)){
        adjMat = -1;
    }

    // Apply normal side culling
    // Usually this would fail if next to a mesh, but it will pass if
    // the current tile is the same material, which in this case will happen
    // if an entire mesh is waterlogged.
    if ((get_faceshape(adjacentPos, dir) == CMM_FACESHAPE_FULL) && block_side_is_solid(adjMat, mat, dir)) return 0;

    // Check if the block that's waterlogged has a full face on the same side
    if ((get_faceshape(pos, dir^1) == CMM_FACESHAPE_FULL) && block_side_is_solid(mat, adjMat, dir^1)) {
        return 0;
    }

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

void set_render_mode(Gfx* gfx, u32 tileType, u32 disableZ) {
    u32 rendermode = cmm_render_mode_table[tileType];
    if (disableZ) rendermode &= ~(Z_UPD | Z_CMP);
    if (!gIsConsole && (tileType != MAT_TRANSPARENT)) rendermode |= AA_EN;
    gDPSetRenderMode(gfx, rendermode, 0);
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


Gfx *get_sidetex(s32 matid) {
    for (s32 i = 0; i < ARRAY_COUNT(cmm_topmat_table); i++) {
        if (cmm_topmat_table[i].mat == matid) {
            return cmm_topmat_table[i].decaltex;
        }
    }
    return NULL;
}


#define retroland_filter_on() if ((cmm_lopt_theme == CMM_THEME_RETRO) || (cmm_lopt_theme == CMM_THEME_MC)) { gDPSetTextureFilter(&cmm_curr_gfx[cmm_gfx_index++], G_TF_POINT); if (!gIsGliden) {cmm_uv_offset = 0;} }
#define retroland_filter_off() if ((cmm_lopt_theme == CMM_THEME_RETRO) || (cmm_lopt_theme == CMM_THEME_MC)) { gDPSetTextureFilter(&cmm_curr_gfx[cmm_gfx_index++], G_TF_BILERP); cmm_uv_offset = (cmm_lopt_theme == CMM_THEME_MC ? -32 : -16); }

// For render or collision specific code
#define PROC_COLLISION(statement) if (cmm_building_collision)  { statement; }
#define PROC_RENDER(statement)    if (!cmm_building_collision) { statement; }

enum ProcessTileRenderModes {
    PROCESS_TILE_NORMAL,
    PROCESS_TILE_TRANSPARENT,
    PROCESS_TILE_BOTH,
    PROCESS_TILE_VPLEX,
};

// Returns true if tile should be processed
// If in vplex screen processing mode, can also override target mat type in order
// to render screen
u32 do_process(u8 *targetMatType, u32 processTileRenderMode) {
    switch (processTileRenderMode) {
        case PROCESS_TILE_NORMAL:
            return (*targetMatType != MAT_TRANSPARENT);
        case PROCESS_TILE_TRANSPARENT:
            return (*targetMatType == MAT_TRANSPARENT);
        case PROCESS_TILE_VPLEX:
            if (*targetMatType == MAT_DECAL) {
                *targetMatType = MAT_SCREEN;
                return TRUE;
            }
            return FALSE;
    }
    return TRUE; // PROCESS_TILE_BOTH
}

void process_tiles(u32 processTileRenderMode) {
    u32 startIndex, endIndex;
    u8 tileType, rot;
    s8 pos[3];

    // Poles
    if (!cmm_building_collision) {
        u8 poleMatType = cmm_mat_table[cmm_theme_table[cmm_lopt_theme].pole].type;
        if (do_process(&poleMatType, processTileRenderMode)) {
            cmm_use_alt_uvs = TRUE;
            cmm_growth_render_type = 0;
            startIndex = cmm_tile_data_indices[POLE_TILETYPE_INDEX];
            endIndex = cmm_tile_data_indices[POLE_TILETYPE_INDEX+1];
            set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], poleMatType, FALSE);
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], POLE_TEX());
            for (u32 i = startIndex; i < endIndex; i++) {
                s8 pos[3];
                vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
                process_tile(pos, &cmm_terrain_pole, cmm_tile_data[i].rot);
            }
            display_cached_tris();
        }
        cmm_use_alt_uvs = FALSE;
    }

    for (u32 mat = 0; mat < NUM_MATERIALS_PER_THEME; mat++) {
        u8 matType = MATERIAL(mat).type;
        cmm_growth_render_type = 0;
        cmm_curr_mat_has_topside = HAS_TOPMAT(mat);
        startIndex = cmm_tile_data_indices[mat];
        endIndex = cmm_tile_data_indices[mat+1];

        // RENDER
        if (!cmm_building_collision) {
            if (!do_process(&matType, processTileRenderMode)) {
                goto skip_maintex;
            }

            set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], matType, FALSE);
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], MATERIAL(mat).gfx);

            // 
            if ((matType == MAT_CUTOUT) || ((matType < MAT_CUTOUT) && (TOPMAT(mat).type >= MAT_CUTOUT))) {
                gSPClearGeometryMode(&cmm_curr_gfx[cmm_gfx_index++], G_CULL_BACK);
            }
        // COLLISION
        } else {
            cmm_curr_coltype = MATERIAL(mat).col;
        }

        for (u32 i = startIndex; i < endIndex; i++) {
            tileType = cmm_tile_data[i].type;
            PROC_COLLISION( if (tileType == TILE_TYPE_TROLL) continue; )
            rot = cmm_tile_data[i].rot;
            vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);

            process_tile(pos, cmm_tile_terrains[tileType], rot);
        }

        PROC_RENDER( display_cached_tris(); \
                     skip_maintex: )
        
        if (cmm_curr_mat_has_topside) {
            u8 topmatType = TOPMAT(mat).type;
            PROC_RENDER( if (!do_process(&topmatType, processTileRenderMode)) continue; )
            Gfx *sidetex = get_sidetex(TILE_MATDEF(mat).topmat);
            // Only runs when rendering
            if (!cmm_building_collision && (sidetex)) {
                cmm_use_alt_uvs = TRUE;
                gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], sidetex);
                cmm_growth_render_type = 2;

                // This code is pretty ugly. It renders the side decal in decal mode
                // for opaque parts of the texture, and in cutout mode for transparent parts.
                // Luckily this will only double the number of triangles in the rare case
                // that a custom block with a cutout side texture and a topmat with a side decal
                // is made (in order to cover both the opaque and alpha parts of the side tex.)
                // DECAL MODE
                if (matType != MAT_TRANSPARENT) { // Render in decal mode for cutouts, opaque and screen
                    set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], MAT_DECAL, FALSE);
                    for (u32 i = startIndex; i < endIndex; i++) {
                        tileType = cmm_tile_data[i].type;
                        rot = cmm_tile_data[i].rot;
                        vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);

                        process_tile(pos, cmm_tile_terrains[tileType], rot);
                    }
                    display_cached_tris();
                }
                // OPAQUE MODE
                if (matType >= MAT_CUTOUT) { // Render in cutout mode for cutouts and transparent
                    set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], MAT_CUTOUT, FALSE);
                    for (u32 i = startIndex; i < endIndex; i++) {
                        tileType = cmm_tile_data[i].type;
                        rot = cmm_tile_data[i].rot;
                        vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);

                        process_tile(pos, cmm_tile_terrains[tileType], rot);
                    }
                    display_cached_tris();
                }
                cmm_use_alt_uvs = FALSE;
            }

            PROC_COLLISION( cmm_curr_coltype = TOPMAT(mat).col; )
            PROC_RENDER( set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], topmatType, FALSE); \
                         gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], TOPMAT(mat).gfx); )

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
        PROC_RENDER( gSPSetGeometryMode(&cmm_curr_gfx[cmm_gfx_index++], G_CULL_BACK); )
    }
}

// Fade: 0 = no fade, 1 = fade at bottom, 2 = fade at top
void render_boundary_quad(struct cmm_boundary_quad *quad, s16 y, s16 yHeight, u32 fade) {
    // Get normal
    Vec3f normal;
    find_vector_perpendicular_to_plane(normal, quad->vtx[0], quad->vtx[1], quad->vtx[2]);
    vec3_normalize(normal);
    s8 n[3];
    n[0] = normal[0]*0x7F; n[1] = normal[1]*0x7F; n[2] = normal[2]*0x7F;

    s32 uScale = quad->uYScale ? (yHeight * 64) : cmm_grid_size*16;
    s32 vScale = quad->vYScale ? (yHeight * 64) : cmm_grid_size*16;
    for (u32 i = 0; i < 4; i++) {
        s16 u = (quad->u[i & 1])*uScale + cmm_uv_offset;
        s16 v = (quad->v[i >> 1])*vScale + cmm_uv_offset;
        if (quad->flipUvs) { s16 tmp = u; u = v; v = tmp;}
        if (yHeight % 2) v += 512; // offset for odd number of blocks
        u8 alpha = 255;
        if ((ABS(quad->vtx[i][0]) > 32) || (ABS(quad->vtx[i][2]) > 32)) {
            alpha = 0;
        } else if (((fade == 1) && (quad->vtx[i][1] == 0)) || ((fade == 2) && (quad->vtx[i][1] == 1))) {
            alpha = 0;
        }
        make_vertex(cmm_curr_vtx, i+cmm_num_vertices_cached, quad->vtx[i][0]*cmm_grid_size*4, (quad->vtx[i][1]*yHeight + y)*TILE_SIZE, quad->vtx[i][2]*cmm_grid_size*4,
            u, v, n[0], n[1], n[2], alpha);
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

void render_boundary(struct cmm_boundary_quad *quadList, u32 count, s16 yBottom, s16 yTop, u32 fade) {
    for (u32 i = 0; i < count; i++) {
        render_boundary_quad(&quadList[i], yBottom, yTop - yBottom, fade);
    }
    display_cached_tris();
}

void render_boundary_decal_edge(Gfx *sidetex, s32 yBottom, u32 sideMatType) {
    if (sideMatType != MAT_TRANSPARENT) {
        set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], MAT_DECAL, FALSE);
        gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], sidetex);
        render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), yBottom, yBottom+1, 0);
    }
    if (sideMatType >= MAT_CUTOUT) {
        set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], MAT_CUTOUT, FALSE);
        gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], sidetex);
        render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), yBottom, yBottom+1, 0);
    }
}

void process_boundary(u32 processRenderMode) {
    u8 planeMat = cmm_lopt_boundary_mat;
    struct cmm_material *mat, *sidemat;
    mat = &TOPMAT(planeMat);
    sidemat = &MATERIAL(planeMat);

    // Outer walls
    if (cmm_boundary_table[cmm_lopt_boundary] & CMM_BOUNDARY_OUTER_WALLS) {
        u8 sidematType = sidemat->type;
        u8 showBackface = ((mat->type >= MAT_CUTOUT) && (sidemat->type <= MAT_CUTOUT)) || (sidemat->type == MAT_CUTOUT);
        cmm_render_flip_normals = TRUE;
        if (showBackface) {
            gSPClearGeometryMode(&cmm_curr_gfx[cmm_gfx_index++], G_CULL_BACK);
        }
        if (do_process(&sidematType, processRenderMode)) {
            set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], sidematType, FALSE);
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], sidemat->gfx);
            render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), -33, -32, 0);

            Gfx *sidetex = get_sidetex(TILE_MATDEF(planeMat).topmat);
            if (sidetex) {
                render_boundary_decal_edge(sidetex, -33, sidematType);
            }
        }
        // Fade at bottom
        gSPSetGeometryMode(&cmm_curr_gfx[cmm_gfx_index++], G_CULL_BACK);
        if (processRenderMode == PROCESS_TILE_TRANSPARENT) {
            gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], sidemat->gfx);
            if (showBackface) {
                cmm_render_flip_normals = FALSE;
                render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), -42, -33, 1);
                cmm_render_flip_normals = TRUE;
            }
            render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), -42, -33, 1);
        }
        cmm_render_flip_normals = FALSE;
    }

    // Main floor
    if (cmm_boundary_table[cmm_lopt_boundary] & CMM_BOUNDARY_INNER_FLOOR) {
        u8 matType = mat->type;
        if (do_process(&matType, processRenderMode)) {
            set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], matType, FALSE);
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], mat->gfx);
            render_boundary(floor_boundary, ARRAY_COUNT(floor_boundary), -32, -32, 0);
        }
    }

    // Inner walls
    if ((cmm_boundary_table[cmm_lopt_boundary] & CMM_BOUNDARY_INNER_WALLS)) {
        u8 sidematType = sidemat->type;
        u8 showBackface = ((mat->type >= MAT_CUTOUT) && (sidemat->type <= MAT_CUTOUT)) || (sidemat->type == MAT_CUTOUT);
        u32 renderWalls = TRUE; // Whether to render main solid walls
        u32 renderFade = FALSE; // Whether to render fade at bottom
        s32 bottomY = -32;
        s32 topY = cmm_lopt_boundary_height-32;
        if (showBackface) {
            gSPClearGeometryMode(&cmm_curr_gfx[cmm_gfx_index++], G_CULL_BACK);
        }
        
        if (!(cmm_boundary_table[cmm_lopt_boundary] & CMM_BOUNDARY_INNER_FLOOR)) {
            renderFade = TRUE;
            bottomY -= 1; // Make sure decal has a solid face to print on
        } else {
            renderWalls = (cmm_lopt_boundary_height > 0);
        }

        Gfx *sidetex = get_sidetex(TILE_MATDEF(planeMat).topmat);
        if (sidetex) topY -= 1;

        if (renderWalls && do_process(&sidematType, processRenderMode)) {
            set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], sidematType, FALSE);
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], sidemat->gfx);
            if (topY > bottomY + 32) {
                render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), bottomY, bottomY + 32, 0);
                render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), bottomY + 32, topY, 0);
            } else {
                render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), bottomY, topY, 0);
            }

            if (sidetex) {
                // Render rim of regular material before decal
                render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), topY, topY + 1, 0);
                render_boundary_decal_edge(sidetex, topY, sidematType);
            }
        }
        gSPSetGeometryMode(&cmm_curr_gfx[cmm_gfx_index++], G_CULL_BACK);
        // Fade if no floor
        if (renderFade) {
            if (processRenderMode == PROCESS_TILE_NORMAL) {
                gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
                gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], &mat_maker_MakerBlack);
                render_boundary(floor_boundary, ARRAY_COUNT(floor_boundary), -40, -40, 0);
            }
            if (processRenderMode == PROCESS_TILE_TRANSPARENT) {
                gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
repeatBackface:
                gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], sidemat->gfx);
                render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), -40, bottomY, 0);
                gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], &mat_maker_MakerBlack);
                render_boundary(wall_boundary, ARRAY_COUNT(wall_boundary), -40, bottomY, 2);
                if (showBackface) {
                    cmm_render_flip_normals = TRUE;
                    showBackface = FALSE;
                    goto repeatBackface; // im such an awesome coder
                }
                cmm_render_flip_normals = FALSE;
            }
        }
    }

    // Outer floor
    if (cmm_boundary_table[cmm_lopt_boundary] & CMM_BOUNDARY_OUTER_FLOOR) {
        s32 y = -32;
        if (cmm_boundary_table[cmm_lopt_boundary] & CMM_BOUNDARY_INNER_WALLS) {
            y = cmm_lopt_boundary_height-32;
        }
        u32 topMatOpaque = (mat->type < MAT_CUTOUT);
        if (topMatOpaque && (processRenderMode == PROCESS_TILE_VPLEX)) {
            gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_VPLEX_SCREEN, G_RM_VPLEX_SCREEN2);
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], mat->gfx);
            render_boundary(floor_edge_boundary, ARRAY_COUNT(floor_edge_boundary), y, y, 0);
        }

        if (processRenderMode == PROCESS_TILE_TRANSPARENT) {
            if (topMatOpaque) {
                gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_XLU_DECAL, G_RM_AA_ZB_XLU_DECAL2);
            } else {
                gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
            }
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], mat->gfx);
            render_boundary(floor_edge_boundary, ARRAY_COUNT(floor_edge_boundary), y, y, 0);
        }
    }
}

void generate_terrain_gfx(void) {
    u8 tileType, rot;
    s8 pos[3];

    cmm_curr_gfx = cmm_terrain_gfx;
    cmm_curr_vtx = cmm_terrain_vtx;
    cmm_gfx_index = 0;
    cmm_building_collision = FALSE;

    cmm_use_alt_uvs = FALSE;
    cmm_render_flip_normals = FALSE;
    cmm_curr_mat_has_topside = FALSE;
    cmm_growth_render_type = 0;
    cmm_uv_offset = (cmm_lopt_theme == CMM_THEME_MC ? -32 : -16);

    retroland_filter_on();

    process_tiles(PROCESS_TILE_VPLEX);
    process_boundary(PROCESS_TILE_VPLEX);

    //BOTTOM PLANE
    process_boundary(PROCESS_TILE_NORMAL);

    // Special Tiles
    cmm_growth_render_type = 0;
    cmm_use_alt_uvs = TRUE;
    u32 startIndex;
    u32 endIndex;

    // Bars
    u8 connections[5];
    startIndex = cmm_tile_data_indices[BARS_TILETYPE_INDEX];
    endIndex = cmm_tile_data_indices[BARS_TILETYPE_INDEX+1];
    set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], MAT_CUTOUT, FALSE);
    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], BARS_TEX());
    for (u32 i = startIndex; i < endIndex; i++) {
        s8 pos[3];
        vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
        check_bar_connections(pos, connections);
        render_bars_side(pos, connections);
    }
    display_cached_tris();
    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], BARS_TOPTEX());
    gSPClearGeometryMode(&cmm_curr_gfx[cmm_gfx_index++], G_CULL_BACK);
    for (u32 i = startIndex; i < endIndex; i++) {
        s8 pos[3];
        vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
        check_bar_connections(pos, connections);
        render_bars_top(pos, connections);
    }
    display_cached_tris();
    gSPSetGeometryMode(&cmm_curr_gfx[cmm_gfx_index++], G_CULL_BACK);

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

    process_tiles(PROCESS_TILE_NORMAL);

    retroland_filter_off();
    gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE);
    gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gSPEndDisplayList(&cmm_curr_gfx[cmm_gfx_index++]);

    cmm_terrain_gfx_tp = &cmm_curr_gfx[cmm_gfx_index];
    retroland_filter_on();

    process_boundary(PROCESS_TILE_TRANSPARENT);

    set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], MAT_TRANSPARENT, FALSE);
    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], WATER_TEX());

    // Render main water plane, top side
    // if (cmm_lopt_waterlevel != 0) {
    //     render_floor((cmm_lopt_waterlevel - 32) * TILE_SIZE - 32);
    // }
    // Render water blocks, interiors
    cmm_render_flip_normals = TRUE;
    for (u32 i = 0; i < cmm_tile_count; i++) {
        if (cmm_tile_data[i].waterlogged) {
            if (((cmm_tile_data[i].type == TILE_TYPE_BLOCK) || (cmm_tile_data[i].type == TILE_TYPE_TROLL)) &&
                !fullblock_can_be_waterlogged(cmm_tile_data[i].mat)) continue;
            vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
            render_water(pos);
        }
    }
    // Render water blocks, exteriors
    cmm_render_flip_normals = FALSE;
    for (u32 i = 0; i < cmm_tile_count; i++) {
        if (cmm_tile_data[i].waterlogged) {
            if (((cmm_tile_data[i].type == TILE_TYPE_BLOCK) || (cmm_tile_data[i].type == TILE_TYPE_TROLL)) &&
                !fullblock_can_be_waterlogged(cmm_tile_data[i].mat)) continue;
            vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
            render_water(pos);
        }
    }
    display_cached_tris();

    cmm_render_flip_normals = TRUE;
    // Render main water plane, bottom side
    // if (cmm_lopt_waterlevel != 0) {
    //     render_floor((cmm_lopt_waterlevel - 32) * TILE_SIZE - 32);
    // }
    cmm_render_flip_normals = FALSE;

    process_tiles(PROCESS_TILE_TRANSPARENT);
    gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
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
Vtx preview_vtx[100];

extern void geo_append_display_list(void *displayList, s32 layer);

void render_preview_block(u32 matid, u32 topmatid, s8 pos[3], struct cmm_terrain *terrain, u32 rot, u32 processType, u32 disableZ) {
    cmm_curr_mat_has_topside = (topmatid != matid);

    u8 matType = cmm_mat_table[matid].type;

    if (do_process(&matType, processType)) {
        set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], matType, disableZ);
        gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], cmm_mat_table[matid].gfx);
        if (((matType == MAT_CUTOUT) ||
            ((matType < MAT_CUTOUT) && (cmm_mat_table[topmatid].type >= MAT_CUTOUT)))
            && !disableZ) {
            gSPClearGeometryMode(&cmm_curr_gfx[cmm_gfx_index++], G_CULL_BACK);
        }
        process_tile(pos, terrain, rot);
        display_cached_tris();
    }

    if (cmm_curr_mat_has_topside) {
        u8 topMatType = cmm_mat_table[topmatid].type;
        if (!do_process(&topMatType, processType)) return;
        Gfx *sidetex = get_sidetex(topmatid);
        if (sidetex != NULL) {
            cmm_use_alt_uvs = TRUE;
            cmm_growth_render_type = 2;
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], sidetex);

            // DECAL MODE
            if (matType != MAT_TRANSPARENT) { // Render in decal mode for cutouts, opaque and screen
                set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], MAT_DECAL, disableZ);
                process_tile(pos, terrain, rot);
                display_cached_tris();
            }
            // OPAQUE MODE
            if (matType >= MAT_CUTOUT) { // Render in cutout mode for cutouts and transparent
                set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], MAT_CUTOUT, disableZ);
                process_tile(pos, terrain, rot);
                display_cached_tris();
            }

            cmm_use_alt_uvs = FALSE;
        }
        cmm_growth_render_type = 1;

        set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], topMatType, disableZ);
        gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], cmm_mat_table[topmatid].gfx);
        process_tile(pos, terrain, rot);
        display_cached_tris();
    }
    gSPSetGeometryMode(&cmm_curr_gfx[cmm_gfx_index++], G_CULL_BACK);
}

Gfx *ccm_append(s32 callContext, UNUSED struct GraphNode *node, UNUSED Mat4 mtx) {
    if (callContext == GEO_CONTEXT_RENDER) {
        geo_append_display_list(cmm_terrain_gfx, LAYER_OPAQUE);
        geo_append_display_list(cmm_terrain_gfx_tp, LAYER_TRANSPARENT_INTER);

        //this extra append is for the editor tile preview
        if (cmm_mode == CMM_MODE_MAKE) {
            if (!cmm_prepare_level_screenshot) {
                geo_append_display_list(cmm_trajectory_gfx, LAYER_OPAQUE);
            }
            //generate dl
            if (cmm_place_mode == CMM_PM_OBJ || cmm_place_mode == CMM_PM_NONE) return NULL;
            cmm_curr_gfx = preview_gfx;
            cmm_curr_vtx = preview_vtx;
            cmm_gfx_index = 0;
            cmm_growth_render_type = 0;

            cmm_building_collision = FALSE;

            retroland_filter_on();

            if (cmm_place_mode == CMM_PM_WATER) {
                gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], WATER_TEX());
                gSPGeometryMode(&cmm_curr_gfx[cmm_gfx_index++], 0, G_CULL_BACK);
                render_water(cmm_cursor_pos);
                display_cached_tris();
                retroland_filter_off();
                gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE);
                gSPEndDisplayList(&cmm_curr_gfx[cmm_gfx_index]);

                geo_append_display_list(cmm_curr_gfx, LAYER_TRANSPARENT_INTER);
                return NULL;
            }

            struct cmm_terrain *terrain = cmm_tile_terrains[cmm_id_selection];
            u8 mat = TILE_MATDEF(cmm_mat_selection).mat;
            u8 topmat = TILE_MATDEF(cmm_mat_selection).topmat;
            if (cmm_id_selection == TILE_TYPE_POLE) {
                terrain = &cmm_terrain_pole;
                mat = cmm_theme_table[cmm_lopt_theme].pole;
                topmat = mat;
                cmm_use_alt_uvs = TRUE;
            }
            
            if (terrain) {
                // Handle Virtuaplex screen effect
                if (mat == CMM_MAT_VP_SCREEN || topmat == CMM_MAT_VP_SCREEN) {
                    render_preview_block(mat, topmat, cmm_cursor_pos, terrain, cmm_rot_selection, PROCESS_TILE_VPLEX, FALSE);

                    gSPEndDisplayList(&cmm_curr_gfx[cmm_gfx_index]);
                    geo_append_display_list(cmm_curr_gfx, LAYER_FORCE);

                    cmm_curr_gfx += cmm_gfx_index;
                    cmm_gfx_index = 0;
                    cmm_growth_render_type = 0;
                }

                render_preview_block(mat, topmat, cmm_cursor_pos, terrain, cmm_rot_selection, PROCESS_TILE_BOTH, FALSE);

            } else if (cmm_id_selection != TILE_TYPE_CULL) {
                cmm_use_alt_uvs = TRUE;
                if (cmm_id_selection == TILE_TYPE_FENCE) {
                    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], FENCE_TEX());
                    set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], MAT_CUTOUT, FALSE);
                    process_tile(cmm_cursor_pos, &cmm_terrain_fence, cmm_rot_selection);
                } else if (cmm_id_selection == TILE_TYPE_POLE) {
                    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], POLE_TEX());
                    set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], cmm_mat_table[cmm_theme_table[cmm_lopt_theme].pole].type, FALSE);
                    process_tile(cmm_cursor_pos, &cmm_terrain_pole, cmm_rot_selection);
                } else if (cmm_id_selection == TILE_TYPE_BARS) {
                    set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], MAT_CUTOUT, FALSE);
                    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], BARS_TEX());
                    u8 connections[5];
                    check_bar_connections(cmm_cursor_pos, connections);
                    render_bars_side(cmm_cursor_pos, connections);
                    display_cached_tris();
                    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], BARS_TOPTEX());
                    gSPClearGeometryMode(&cmm_curr_gfx[cmm_gfx_index++], G_CULL_BACK);
                    render_bars_top(cmm_cursor_pos, connections);
                }
                display_cached_tris();
                gSPSetGeometryMode(&cmm_curr_gfx[cmm_gfx_index++], G_CULL_BACK);
                cmm_use_alt_uvs = FALSE;
            }

            gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
            gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE);
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
        while (pos[1] < 64 && (get_grid_tile(pos)->type - 1 == TILE_TYPE_POLE)) {
            poleLength++;
            pos[1]++;
        }

        gPoleArray[gNumPoles].pos[0] = GRID_TO_POS(cmm_tile_data[i].x);
        gPoleArray[gNumPoles].pos[1] = GRID_TO_POS(cmm_tile_data[i].y) - TILE_SIZE/2;
        gPoleArray[gNumPoles].pos[2] = GRID_TO_POS(cmm_tile_data[i].z);
        gPoleArray[gNumPoles].height = poleLength * TILE_SIZE;
        gPoleArray[gNumPoles].poleType = 0;
        gNumPoles++;
    }

    // Trees
    for (u32 i = 0; i < cmm_object_count; i++) {
        if (cmm_object_data[i].type == OBJECT_TYPE_TREE) {
            gPoleArray[gNumPoles].pos[0] = GRID_TO_POS(cmm_object_data[i].x);
            gPoleArray[gNumPoles].pos[1] = GRID_TO_POS(cmm_object_data[i].y) - TILE_SIZE/2;
            gPoleArray[gNumPoles].pos[2] = GRID_TO_POS(cmm_object_data[i].z);
            gPoleArray[gNumPoles].height = 500;
            gPoleArray[gNumPoles].poleType = (cmm_object_data[i].param2 == 2 ? 2 : 1);
            gNumPoles++;
        } else if (cmm_object_data[i].type == OBJECT_TYPE_KTQ) {
            s32 traj_id = cmm_object_data[i].param2;
            // Scan for end of trajectory and place flag
            for (u32 j = 0; j < CMM_TRAJECTORY_LENGTH; j++) {
                if (cmm_trajectory_list[traj_id][j][0] == -1) {
                    gPoleArray[gNumPoles].pos[0] = cmm_trajectory_list[traj_id][j-1][1];
                    gPoleArray[gNumPoles].pos[1] = cmm_trajectory_list[traj_id][j-1][2] - TILE_SIZE/2;
                    gPoleArray[gNumPoles].pos[2] = cmm_trajectory_list[traj_id][j-1][3];
                    gPoleArray[gNumPoles].height = 700;
                    gPoleArray[gNumPoles].poleType = 0;
                    gNumPoles++;
                    break;
                }
            }
        }
    }

    main_pool_realloc(gPoleArray, gNumPoles * sizeof(struct Pole));
}

void generate_boundary_collision(struct cmm_boundary_quad *quadList, u32 count, s16 yBottom, s16 yTop, s16 size, u32 reverse) {
    TerrainData newVtxs[4][3];
    s16 yHeight = yTop - yBottom;
    for (u32 i = 0; i < count; i++) {
        for (u32 j = 0; j < 4; j++) {
            newVtxs[j][0] = quadList[i].vtx[j][0]*size*4;
            newVtxs[j][1] = (quadList[i].vtx[j][1]*yHeight + yBottom)*TILE_SIZE;
            newVtxs[j][2] = quadList[i].vtx[j][2]*size*4;
        }
        if (reverse) {
            cmm_create_surface(newVtxs[0], newVtxs[2], newVtxs[1]);
            cmm_create_surface(newVtxs[1], newVtxs[2], newVtxs[3]);
        } else {
            cmm_create_surface(newVtxs[0], newVtxs[1], newVtxs[2]);
            cmm_create_surface(newVtxs[1], newVtxs[3], newVtxs[2]);
        }
    }
}

void generate_terrain_collision(void) {
    gCurrStaticSurfacePool = main_pool_alloc(main_pool_available() - 0x10, MEMORY_POOL_LEFT);
    gCurrStaticSurfacePoolEnd = gCurrStaticSurfacePool;
    gSurfaceNodesAllocated = gNumStaticSurfaceNodes;
    gSurfacesAllocated = gNumStaticSurfaces;
    cmm_building_collision = TRUE;

    if (cmm_boundary_table[cmm_lopt_boundary] & CMM_BOUNDARY_DEATH_PLANE) {
        u32 deathsize = (cmm_boundary_table[cmm_lopt_boundary] & CMM_BOUNDARY_INNER_WALLS) ? cmm_grid_size : 128;
        cmm_curr_coltype = SURFACE_DEATH_PLANE;
        generate_boundary_collision(floor_boundary, ARRAY_COUNT(floor_boundary), -40, -40, deathsize, FALSE);
    }
    if (cmm_boundary_table[cmm_lopt_boundary] & CMM_BOUNDARY_INNER_FLOOR) {
        cmm_curr_coltype = TOPMAT(cmm_lopt_boundary_mat).col;
        generate_boundary_collision(floor_boundary, ARRAY_COUNT(floor_boundary), -32, -32, cmm_grid_size, FALSE);
    }
    if (cmm_boundary_table[cmm_lopt_boundary] & CMM_BOUNDARY_INNER_WALLS) {
        cmm_curr_coltype = MATERIAL(cmm_lopt_boundary_mat).col;
        s32 bottomY = (cmm_boundary_table[cmm_lopt_boundary] & CMM_BOUNDARY_INNER_FLOOR) ? -32 : -40;
        s32 topY = cmm_lopt_boundary_height-32;
        generate_boundary_collision(wall_boundary, ARRAY_COUNT(wall_boundary), bottomY, topY, cmm_grid_size, FALSE);
    } else if (cmm_boundary_table[cmm_lopt_boundary] & CMM_BOUNDARY_OUTER_WALLS) {
        cmm_curr_coltype = MATERIAL(cmm_lopt_boundary_mat).col;
        generate_boundary_collision(wall_boundary, ARRAY_COUNT(wall_boundary), -42, -32, cmm_grid_size, TRUE);
    }

    process_tiles(0);
    cmm_growth_render_type = 0;

    cmm_curr_coltype = SURFACE_NO_CAM_COLLISION;
    for (u32 i = cmm_tile_data_indices[FENCE_TILETYPE_INDEX]; i < cmm_tile_data_indices[FENCE_TILETYPE_INDEX+1]; i++) {
        s8 pos[3];
        vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
        process_tile(pos, &cmm_terrain_fence_col, cmm_tile_data[i].rot);
    }
    cmm_curr_coltype = SURFACE_VANISH_CAP_WALLS;
    for (u32 i = cmm_tile_data_indices[BARS_TILETYPE_INDEX]; i < cmm_tile_data_indices[BARS_TILETYPE_INDEX+1]; i++) {
        s8 pos[3];
        u8 connections[5];
        vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
        check_bar_connections(pos, connections);
        render_bars_side(pos, connections);
        render_bars_top(pos, connections);
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
    s32 waterPlaneHeight = (cmm_lopt_waterlevel == 0 ? FLOOR_LOWER_LIMIT : (cmm_lopt_waterlevel - 32) * TILE_SIZE - (TILE_SIZE / 8));
    if (y < waterPlaneHeight) {
        return waterPlaneHeight;
    }
    // Convert world coordinates into grid coordinates
    s8 pos[3];
    vec3_set(pos, (x + 32*TILE_SIZE) / TILE_SIZE, (y + 32*TILE_SIZE) / TILE_SIZE, (z + 32*TILE_SIZE) / TILE_SIZE);

    // Check if out of range
    if (pos[1] > 63) {
        pos[1] = 63;
    }
    if (!coords_in_range(pos)) return waterPlaneHeight;
    // If block contains water, scan upwards, otherwise scan downwards
    if (get_grid_tile(pos)->waterlogged) {
        // Find grid Y coordinate of highest water block.
        // Stop scanning once we hit a non-water block or the top is reached
        pos[1]++;
        while (pos[1] < 64 && get_grid_tile(pos)->waterlogged) {
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
        return (pos[1] - 31) * TILE_SIZE;
    }
    return (pos[1] - 31) * TILE_SIZE - (TILE_SIZE / 8);
}

struct Object *spawn_preview_object(s8 pos[3], s32 rot, s32 param1, s32 param2, struct cmm_object_info *info, const BehaviorScript *script, u8 useTrajectory) {
    struct Object *preview_object = spawn_object(gMarioObject, info->model_id, script);
    preview_object->oPosX = GRID_TO_POS(pos[0]);
    preview_object->oPosY = GRID_TO_POS(pos[1]) - TILE_SIZE/2 + info->y_offset;
    preview_object->oPosZ = GRID_TO_POS(pos[2]);
    preview_object->oFaceAngleYaw = rot*0x4000;
    preview_object->oBehParams2ndByte = param2;
    preview_object->oBehParams = (param1 << 24) | (param2 << 16);
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
    cmm_object_limit_count = 0;
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

        s32 extraObjs = get_extra_objects(info, param);
        if (info == &cmm_object_type_coin_formation) {
            totalCoins += extraObjs;
        }
        cmm_object_limit_count += extraObjs + 1;
    }
    if (doubleCoins) totalCoins *= 2;

    u32 length = MIN(totalCoins / 20, 50);
    if (cmm_lopt_theme == CMM_GAME_BTCM) {
        cmm_settings_misc_buttons[MISC_COINSTAR_INDEX].size = length + 1;
    } else {
        cmm_settings_misc_buttons_vanilla[MISCV_COINSTAR_INDEX].size = length + 1;
    }

    if (cmm_lopt_coinstar > length) {
        cmm_lopt_coinstar = length;
    }

    generate_trajectory_gfx();
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
        obj->oPosY = GRID_TO_POS(cmm_object_data[i].y) - TILE_SIZE/2 + info->y_offset;
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
        if (!fullblock_can_be_waterlogged(cmm_mat_selection)) {
            waterlogged = FALSE;
        }
    }
    // If placing a cull marker, check that its actually next to a tile
    if (cmm_id_selection == TILE_TYPE_CULL && is_cull_marker_useless(pos)) {
        return;
    }

    if (cmm_tile_terrains[cmm_id_selection] != NULL) {
        TerrainData coltype = TOPMAT(cmm_mat_selection).col;
        if (SURFACE_IS_BURNING(coltype)) {
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
        if ((tileType == TILE_TYPE_BLOCK) && !fullblock_can_be_waterlogged(tile->mat)) {
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
    s32 refreshTrajectories = FALSE;

    if (cmm_object_place_types[cmm_object_data[index].type].useTrajectory) { 
        remove_trajectory(cmm_object_data[index].param2);
        refreshTrajectories = TRUE;
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

    //bzero(&cmm_save, sizeof(cmm_save)); // should be safe to not need this right?

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

    cmm_save.costume = cmm_lopt_costume;
    cmm_save.seq = cmm_lopt_seq;
    cmm_save.envfx = cmm_lopt_envfx;
    cmm_save.theme = cmm_lopt_theme;
    cmm_save.bg = cmm_lopt_bg;
    cmm_save.boundary_mat = cmm_lopt_boundary_mat;
    cmm_save.boundary = cmm_lopt_boundary;
    cmm_save.boundary_height = cmm_lopt_boundary_height;
    cmm_save.coinstar = cmm_lopt_coinstar;
    cmm_save.size = cmm_lopt_size;
    cmm_save.waterlevel = cmm_lopt_waterlevel;
    cmm_save.secret = cmm_lopt_secret;
    cmm_save.game = cmm_lopt_game;

    for (i = 0; i < CMM_MAX_TRAJECTORIES; i++) {
        for (j = 0; j < CMM_TRAJECTORY_LENGTH; j++) {
            cmm_save.trajectories[i][j].t = cmm_trajectory_list[i][j][0];
            cmm_save.trajectories[i][j].x = POS_TO_GRID(cmm_trajectory_list[i][j][1]);
            cmm_save.trajectories[i][j].y = POS_TO_GRID(cmm_trajectory_list[i][j][2]);
            cmm_save.trajectories[i][j].z = POS_TO_GRID(cmm_trajectory_list[i][j][3]);
        }
    }

    // If in screenshot mode
    if (cmm_prepare_level_screenshot) {
        u8 screenshot_failure = TRUE;

        for (i=0;i<4096;i++) {
            //take a "screenshot" of the level & burn in a painting frame
            if (cmm_painting_frame_1_rgba16[(i*2)+1]==0x00) {
                //painting
                if (gEmulator & INSTANT_INPUT_BLACKLIST) {
                    cmm_save.piktcher[i/64][i%64] = (gFramebuffers[(sRenderedFramebuffer+2)%3][ ((s32)((i/64)*3.75f))*320 + (s32)((i%64)*3.75f+40) ] | 1);
                } else {
                    cmm_save.piktcher[i/64][i%64] = (gFramebuffers[0][ ((s32)((i/64)*3.75f))*320 + (s32)((i%64)*3.75f+40) ] | 1);
                }

                if (cmm_save.piktcher[i/64][i%64] > 1) { //assumes all fb rgba16 values is initialized to 1 or 0
                    screenshot_failure = FALSE;
                }
            } else {
                //painting frame
                cmm_save.piktcher[i/64][i%64] = ((cmm_painting_frame_1_rgba16[(i*2)]<<8) | cmm_painting_frame_1_rgba16[(i*2)+1]);
            }
        }

        if (screenshot_failure) {
            //framebuffer emulation not enabled, use ?
            bcopy(&mystery_painting_rgba16,&cmm_save.piktcher,sizeof(cmm_save.piktcher));
        }

        update_painting();
    }

    if (cmm_save.piktcher[0][0] == 0) { //0 is a transparent pixel in rgba16
        //use mystery painting if no screenshot has been taken yet
        bcopy(&mystery_painting_rgba16,&cmm_save.piktcher,sizeof(cmm_save.piktcher));
    }
    bcopy(&cmm_curr_custom_theme,&cmm_save.custom_theme,sizeof(struct cmm_custom_theme));

    f_chdir(cmm_level_dir_name);
    UINT bytes_written;
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
    s32 i;
    s32 j;
    u8 fresh = FALSE;

    bzero(&cmm_save, sizeof(cmm_save));
    bzero(&cmm_grid_data, sizeof(cmm_grid_data));

    f_chdir(cmm_level_dir_name); //chdir exits after the ifelse statement
    FRESULT code = f_stat(cmm_file_name,&cmm_file_info);
    if (code == FR_OK) {
        UINT bytes_read;
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
        strcpy(cmm_file_info.fname,cmm_file_name);

        //Set version
        cmm_save.version = CMM_VERSION;

        //Place spawn location
        cmm_save.object_count = 1;
        cmm_object_data[0].x = 32;
        cmm_object_data[0].z = 32;
        cmm_object_data[0].y = cmm_templates[cmm_lopt_template].spawnHeight;
        cmm_object_data[0].type = OBJECT_TYPE_SPAWN;

        cmm_save.game = cmm_lopt_game;
        cmm_save.size = cmm_lopt_size;

        cmm_save.seq = cmm_templates[cmm_lopt_template].music[cmm_lopt_game];
        cmm_save.envfx = cmm_templates[cmm_lopt_template].envfx;
        cmm_save.theme = cmm_templates[cmm_lopt_template].theme;
        cmm_save.bg = cmm_templates[cmm_lopt_template].bg;
        cmm_save.boundary_mat = cmm_templates[cmm_lopt_template].plane;
        cmm_save.boundary = 1;
        cmm_save.boundary_height = 5;

        if (cmm_templates[cmm_lopt_template].platform) {
            u8 i = 0;
            for (s32 x = -1; x <= 1; x++) {
                for (s32 z = -1; z <= 1; z++) {
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

        bcopy(&cmm_default_custom,&cmm_save.custom_theme,sizeof(struct cmm_custom_theme));
    }
    f_chdir("..");

    cmm_tile_count = cmm_save.tile_count;
    cmm_object_count = cmm_save.object_count;

    cmm_lopt_costume = cmm_save.costume;

    cmm_lopt_seq = cmm_save.seq;
    cmm_lopt_envfx = cmm_save.envfx;
    cmm_lopt_theme = cmm_save.theme;
    cmm_lopt_bg = cmm_save.bg;

    cmm_lopt_boundary_mat = cmm_save.boundary_mat;
    cmm_lopt_boundary = cmm_save.boundary;
    cmm_lopt_boundary_height = cmm_save.boundary_height;
    cmm_lopt_coinstar = cmm_save.coinstar;
    cmm_lopt_size = cmm_save.size;
    cmm_lopt_waterlevel = cmm_save.waterlevel;
    cmm_lopt_secret = cmm_save.secret;

    cmm_newsize = cmm_lopt_size;
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

    cmm_lopt_game = cmm_save.game;

    //reset toolbar
    bcopy(&cmm_toolbar_defaults,&cmm_toolbar,sizeof(cmm_toolbar_defaults));

    // copy custom theme
    bcopy(&cmm_save.custom_theme,&cmm_curr_custom_theme,sizeof(struct cmm_custom_theme));
    update_custom_theme();

    reload_bg();

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
            cmm_trajectory_list[i][j][2] = GRID_TO_POS(cmm_save.trajectories[i][j].y);
            cmm_trajectory_list[i][j][3] = GRID_TO_POS(cmm_save.trajectories[i][j].z);
        }
    }


    cmm_set_data_overrides();

    if (!fresh) {
        update_painting();
    }
}

void cmm_init() {
    load_level();
    if (cmm_level_action != CMM_LA_PLAY_LEVELS) {
        vec3_set(cmm_cursor_pos, 32, 0, 32);
        cmm_camera_foc[0] = GRID_TO_POS(32);
        cmm_camera_foc[1] = 0.0f;
        cmm_camera_foc[2] = GRID_TO_POS(32);
    }
}

void sb_init(void) {
    struct Object *spawn_obj;

    cmm_toolbar_index = 0;
    reload_bg();
    generate_terrain_gfx();

    switch(cmm_mode) {
        case CMM_MODE_MAKE:
            cmm_menu_state = CMM_MAKE_MAIN;
            o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            generate_object_preview();

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
            reset_rng();
            gGlobalTimer = 0;
            generate_objects_to_level();
            load_obj_warp_nodes();

            spawn_obj = cur_obj_nearest_object_with_behavior(bhvSpawn);
            if (spawn_obj) {
                if (cmm_level_action == CMM_LA_BUILD) {
                    gMarioState->pos[0] = (f32)(GRID_TO_POS(cmm_cursor_pos[0]));
                    gMarioState->pos[1] = (f32)(GRID_TO_POS(cmm_cursor_pos[1]));
                    gMarioState->pos[2] = (f32)(GRID_TO_POS(cmm_cursor_pos[2]));
                    set_mario_action(gMarioState,ACT_IDLE,0);
                    gMarioState->faceAngle[1] = cmm_rot_selection*0x4000;
                } else {
                    gMarioState->faceAngle[1] = spawn_obj->oFaceAngleYaw;
                    vec3_copy(gMarioState->pos,&spawn_obj->oPosVec);
                    set_mario_action(gMarioState,ACT_SPAWN_SPIN_AIRBORNE,0);
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
        cmm_cursor_pos[1]=(cmm_cursor_pos[1]+64)%64;
    }

    //camera zooming
    if (gPlayer1Controller->buttonPressed & D_JPAD) {
        cmm_camera_zoom_index++;
        play_sound(SOUND_MENU_CAMERA_TURN, gGlobalSoundSource);
    }
    cmm_camera_zoom_index = (cmm_camera_zoom_index+5)%5;

    o->oPosX = GRID_TO_POS(cmm_cursor_pos[0]); 
    o->oPosY = GRID_TO_POS(cmm_cursor_pos[1]); 
    o->oPosZ = GRID_TO_POS(cmm_cursor_pos[2]); 

    return cursorMoved;
}

void update_boundary_wall() {
    for (u8 i=0; i<6; i++) {
        vec3_copy(&cmm_boundary_object[i]->oPosVec,&o->oPosVec);
    }
    cmm_boundary_object[0]->oPosY = GRID_TO_POS(0);
    cmm_boundary_object[1]->oPosY = GRID_TO_POS(64);
    cmm_boundary_object[2]->oPosX = GRID_TO_POS(cmm_grid_min);
    cmm_boundary_object[3]->oPosX = GRID_TO_POS(cmm_grid_min + cmm_grid_size);
    cmm_boundary_object[4]->oPosZ = GRID_TO_POS(cmm_grid_min);
    cmm_boundary_object[5]->oPosZ = GRID_TO_POS(cmm_grid_min + cmm_grid_size);

    if (cmm_menu_state == CMM_MAKE_SCREENSHOT) {
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

void update_custom_theme(void) {
    for (u32 i = 0; i < NUM_MATERIALS_PER_THEME; i++) {
        cmm_theme_table[CMM_THEME_CUSTOM].mats[i].mat = cmm_curr_custom_theme.mats[i];
        if (cmm_curr_custom_theme.topmatsEnabled[i]) {
            cmm_theme_table[CMM_THEME_CUSTOM].mats[i].topmat = cmm_curr_custom_theme.topmats[i];
        } else {
            cmm_theme_table[CMM_THEME_CUSTOM].mats[i].topmat = cmm_curr_custom_theme.mats[i];
        }
    }
    cmm_theme_table[CMM_THEME_CUSTOM].fence = cmm_curr_custom_theme.fence;
    cmm_theme_table[CMM_THEME_CUSTOM].pole = cmm_curr_custom_theme.pole;
    cmm_theme_table[CMM_THEME_CUSTOM].bars = cmm_curr_custom_theme.bars;
    cmm_theme_table[CMM_THEME_CUSTOM].water = cmm_curr_custom_theme.water;
}

void reload_theme(void) {
    generate_terrain_gfx();
    cmm_set_data_overrides();
    generate_object_preview();
}

void reload_bg(void) {
    void *dest = NULL;
    void *srcStart = cmm_skybox_table[cmm_lopt_bg*2];
    void *srcEnd = cmm_skybox_table[cmm_lopt_bg*2+1];

    if (srcStart == NULL) {
        return;
    }

    u32 compSize = ALIGN16(srcEnd - srcStart);
    u8 *compressed = main_pool_alloc(compSize, MEMORY_POOL_RIGHT);

    // Decompressed size from header (This works for non-mio0 because they also have the size in same place)
    u32 *size = (u32 *) (compressed + 4);

    if (compressed != NULL) {
        dma_read(compressed, srcStart, srcEnd);
        Propack_UnpackM1(compressed, get_segment_base_addr(SEGMENT_SKYBOX));
        sSegmentROMTable[SEGMENT_SKYBOX] = (uintptr_t) srcStart;
        main_pool_free(compressed);
    }
}

u8 cmm_upsidedown_tile = FALSE;
u8 cmm_joystick;
extern s16 cmm_menu_start_timer;
extern s16 cmm_menu_end_timer;


s32 get_flipped_tile(s32 tileID) {
    switch (tileID) {
        case TILE_TYPE_SLOPE:
        case TILE_TYPE_DSLOPE:
            return TILE_TYPE_DSLOPE;
        case TILE_TYPE_CORNER:
        case TILE_TYPE_DCORNER:
            return TILE_TYPE_DCORNER;
        case TILE_TYPE_ICORNER:
        case TILE_TYPE_DICORNER:
            return TILE_TYPE_DICORNER;
        case TILE_TYPE_SLAB:
        case TILE_TYPE_DSLAB:
            return TILE_TYPE_DSLAB;
    }
    return -1;
}

s16 cmm_freecam_pitch;
s16 cmm_freecam_yaw;
u8 cmm_freecam_snap = FALSE;
u8 cmm_freecam_snap_timer = 0;

void freecam_camera_init(void) {
    vec3f_copy(cmm_camera_pos_prev,cmm_camera_pos);

    Vec3f d;
    vec3_diff(d, cmm_camera_pos, cmm_camera_foc);
    f32 xz = (sqr(d[0]) + sqr(d[2]));
    cmm_freecam_pitch = atan2s(sqrtf(xz), d[1]) + 0x4000;
    cmm_freecam_yaw = atan2s(d[2], d[0]);

    cmm_freecam_snap = FALSE;
    cmm_freecam_snap_timer = 0;
    cmm_prepare_level_screenshot = TRUE;
}

void freecam_camera_main(void) {
    if (cmm_freecam_snap) {
        cmm_freecam_snap_timer++;
        if (cmm_freecam_snap_timer == 3) {
            play_sound(SOUND_MENU_CLICK_CHANGE_VIEW, gGlobalSoundSource);
            for (u8 i=0; i<16; i++) {
                osRecvMesg(&gGameVblankQueue, &gMainReceivedMesg, OS_MESG_BLOCK);
            }
            save_level();
        }
        if (cmm_freecam_snap_timer > 30) {
            cmm_menu_state = CMM_MAKE_MAIN;
            cmm_camera_fov = 45.0f;
            cmm_prepare_level_screenshot = FALSE;
            vec3f_copy(cmm_camera_pos,cmm_camera_pos_prev);
        }
        return;
    }

    // camera controls
    cmm_freecam_yaw += gPlayer1Controller->rawStickX*-4;
    cmm_freecam_pitch += gPlayer1Controller->rawStickY*-4;

    if (gPlayer1Controller->buttonDown & U_CBUTTONS) {
        cmm_camera_pos[0] += ( sins(cmm_freecam_yaw) * -sins(cmm_freecam_pitch) * 45.0f );
        cmm_camera_pos[1] += ( coss(cmm_freecam_pitch) * 45.0f );
        cmm_camera_pos[2] += ( coss(cmm_freecam_yaw) * -sins(cmm_freecam_pitch) * 45.0f );
    }

    if (gPlayer1Controller->buttonDown & D_CBUTTONS) {
        cmm_camera_pos[0] += ( sins(cmm_freecam_yaw) * -sins(cmm_freecam_pitch) * -45.0f );
        cmm_camera_pos[1] += ( coss(cmm_freecam_pitch) * -45.0f );
        cmm_camera_pos[2] += ( coss(cmm_freecam_yaw) * -sins(cmm_freecam_pitch) * -45.0f );
    }

    if (gPlayer1Controller->buttonDown & R_CBUTTONS) {
        cmm_camera_pos[0] += ( sins(cmm_freecam_yaw + 0x4000) * 30.0f );
        cmm_camera_pos[2] += ( coss(cmm_freecam_yaw + 0x4000) * 30.0f );
    }

    if (gPlayer1Controller->buttonDown & L_CBUTTONS) {
        cmm_camera_pos[0] += ( sins(cmm_freecam_yaw - 0x4000) * 30.0f );
        cmm_camera_pos[2] += ( coss(cmm_freecam_yaw - 0x4000) * 30.0f );
    }

    if (gPlayer1Controller->buttonDown & L_TRIG) {
        cmm_camera_fov -= 1.0f;
        cur_obj_play_sound_1(SOUND_AIR_AMP_BUZZ);

        if (cmm_camera_fov < 1.0f) {
            cmm_camera_fov = 1.0f;
        }
    }

    if (gPlayer1Controller->buttonDown & R_TRIG) {
        cmm_camera_fov += 1.0f;
        cur_obj_play_sound_1(SOUND_AIR_AMP_BUZZ);

        if (cmm_camera_fov > 100.0f) {
            cmm_camera_fov = 100.0f;
        }
    }

    if (gPlayer1Controller->buttonPressed & START_BUTTON) {
        cmm_freecam_snap = TRUE;
    }

    if (gPlayer1Controller->buttonPressed & B_BUTTON) {
        cmm_menu_state = CMM_MAKE_MAIN;
        cmm_camera_fov = 45.0f;
        cmm_prepare_level_screenshot = FALSE;
        vec3f_copy(cmm_camera_pos,cmm_camera_pos_prev);
    }

    // transform camera
    cmm_camera_foc[0] = cmm_camera_pos[0] + ( sins(cmm_freecam_yaw) * -sins(cmm_freecam_pitch) * 100.0f );
    cmm_camera_foc[1] = cmm_camera_pos[1] + ( coss(cmm_freecam_pitch) * 100.0f );
    cmm_camera_foc[2] = cmm_camera_pos[2] + ( coss(cmm_freecam_yaw) * -sins(cmm_freecam_pitch) * 100.0f );
}

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
    if ((cmm_menu_state != CMM_MAKE_PLAY) && cmm_tip_timer) {
        if (!(--cmm_tip_timer)) cmm_show_tip();
    }

    switch(cmm_menu_state) {
        case CMM_MAKE_MAIN:
            cursorMoved = main_cursor_logic(cmm_joystick);
            s32 updatePreviewObj = cursorMoved;

            if (gPlayer1Controller->buttonPressed & L_TRIG) {
                cmm_toolbar_index--;
                cmm_param_selection = 0;
                updatePreviewObj = TRUE;
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
            }
            if (gPlayer1Controller->buttonPressed & R_TRIG) {
                cmm_toolbar_index++;
                cmm_param_selection = 0;
                updatePreviewObj = TRUE;
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
            }
            cmm_toolbar_index = (cmm_toolbar_index+9)%9;
            cmm_id_selection = cmm_ui_buttons[cmm_toolbar[cmm_toolbar_index]].id;
            cmm_place_mode = cmm_ui_buttons[cmm_toolbar[cmm_toolbar_index]].placeMode;

            if (cmm_upsidedown_tile) {
                s32 flippedTile = get_flipped_tile(cmm_id_selection);
                if (flippedTile != -1) {
                    cmm_id_selection = flippedTile;
                } else {
                    cmm_upsidedown_tile = FALSE;
                }
            }

            //parameter changing
            if (cmm_place_mode != CMM_PM_OBJ || cmm_object_place_types[cmm_id_selection].maxParams != 0) {
                if (gPlayer1Controller->buttonPressed & L_JPAD) {
                    cmm_param_selection --;
                    updatePreviewObj = TRUE;
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                }
                if (gPlayer1Controller->buttonPressed & R_JPAD) {
                    cmm_param_selection ++;
                    updatePreviewObj = TRUE;
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                }
            }

            //Single A press
            if (gPlayer1Controller->buttonPressed & A_BUTTON || 
                ((gPlayer1Controller->buttonPressed & START_BUTTON) && (cmm_toolbar_index >= 7))) {
                switch(cmm_toolbar_index) {
                    case 7: // save and test
                        if (mount_success == FR_OK) {
                            save_level();
                        }
                        cmm_target_mode = CMM_MODE_PLAY;
                        reset_play_state();
                        level_trigger_warp(gMarioState, WARP_OP_LOOK_UP);
                        sSourceWarpNodeId = 0x0A;
                        play_sound(SOUND_MENU_STAR_SOUND_LETS_A_GO, gGlobalSoundSource);
                        break;
                    case 8: // options
                        switch (cmm_param_selection) {
                            case 0: // settings menu
                                cmm_newsize = cmm_lopt_size;
                                cmm_menu_state = CMM_MAKE_SETTINGS;
                                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                                cmm_menu_start_timer = 0;
                                cmm_menu_end_timer = -1;
                                cmm_menu_index = 0;
                                animate_list_reset();
                                break;
                            case 1: // screenshot
                                if (mount_success == FR_OK) {
                                    freecam_camera_init();
                                    cmm_menu_state = CMM_MAKE_SCREENSHOT;
                                    play_sound(SOUND_MENU_CLICK_CHANGE_VIEW, gGlobalSoundSource);
                                } else {
                                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                                }
                                break;
                        }
                        break;
                    default: //everything else places
                        place_thing_action();
                }
            } else if (gPlayer1Controller->buttonDown & A_BUTTON && cursorMoved) {
                if (cmm_toolbar_index < 7) {
                    place_thing_action();
                }
            }

            if (gPlayer1Controller->buttonPressed & B_BUTTON || ((gPlayer1Controller->buttonDown & B_BUTTON) && cursorMoved)) {
                delete_tile_action(cmm_cursor_pos);
            }

            if (gPlayer1Controller->buttonPressed & START_BUTTON && (cmm_toolbar_index < 7)) {
                cmm_menu_start_timer = 0;
                cmm_menu_end_timer = -1;
                cmm_menu_index = 0;
                cmm_menu_state = CMM_MAKE_TOOLBOX;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                animate_list_reset();
            }

            if (gPlayer1Controller->buttonPressed & U_JPAD) {
                if (get_flipped_tile(cmm_id_selection) != -1) play_sound(SOUND_ACTION_SIDE_FLIP_UNK, gGlobalSoundSource);
                cmm_upsidedown_tile ^= 1;
            }

            if (gPlayer1Controller->buttonPressed & Z_TRIG) {
                cmm_rot_selection++;
                cmm_rot_selection%=4;
                updatePreviewObj = TRUE;
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

            if (cmm_prepare_level_screenshot) {
                o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            } else {
                o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            }

            struct Object *spawnobjp = get_spawn_preview_object();
            if (spawnobjp) {
                if (cmm_prepare_level_screenshot) {
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
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
            }
            cmm_toolbox_index = (cmm_toolbox_index+sizeof(cmm_toolbox))%sizeof(cmm_toolbox);

            //TOOLBAR CONTROLS
            if (gPlayer1Controller->buttonPressed & L_TRIG) {
                cmm_toolbar_index--;
                cmm_toolbox_transition_btn_render = FALSE;
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
            }
            if (gPlayer1Controller->buttonPressed & R_TRIG) {
                cmm_toolbar_index++;
                cmm_toolbox_transition_btn_render = FALSE;
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
            }
            cmm_toolbar_index = (cmm_toolbar_index+7)%7;
            cmm_id_selection = cmm_ui_buttons[cmm_toolbar[cmm_toolbar_index]].id;
            cmm_place_mode = cmm_ui_buttons[cmm_toolbar[cmm_toolbar_index]].placeMode;

            //PRESS A TO MOVE FROM TOOLBOX TO TOOLBAR
            if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                //You can not put a blank button into the toolbox
                if ( cmm_toolbox[cmm_toolbox_index] != CMM_BUTTON_BLANK) {
                    cmm_param_selection = 0;

                    cmm_toolbox_transition_btn_render = TRUE;
                    // current pos
                    cmm_toolbox_transition_btn_x = 34+((cmm_toolbox_index%9)*32);
                    cmm_toolbox_transition_btn_y = 220-((cmm_toolbox_index/9)*32);
                    // target pos
                    cmm_toolbox_transition_btn_tx = 34.0f+(cmm_toolbar_index*32.0f);
                    cmm_toolbox_transition_btn_ty = 25.0f;
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
                        generate_object_preview();
                    }
                } else if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                    if (cmm_trajectory_edit_index <= 1) {
                        cmm_show_error_message("Nothing to delete!");
                    } else {
                        cmm_trajectory_edit_index--;
                        cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index][0] = -1;
                        play_place_sound(SOUND_GENERAL_DOOR_INSERT_KEY | SOUND_VIBRATO);
                        generate_object_preview();
                    }
                }
            }

            if (gPlayer1Controller->buttonPressed & START_BUTTON) {
                if (cmm_trajectory_edit_index == 1) {
                    cmm_show_error_message("Trajectory is too short!");
                } else {
                    cmm_menu_state = CMM_MAKE_MAIN;
                    generate_object_preview();
                }
            }

            update_boundary_wall();
        break;
        case CMM_MAKE_SCREENSHOT:
            o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            freecam_camera_main();
            update_boundary_wall();
        break;
    }

    if (cmm_menu_state == CMM_MAKE_MAIN || cmm_menu_state == CMM_MAKE_SETTINGS || cmm_menu_state == CMM_MAKE_TOOLBOX) {
        struct Object *previewObj = cur_obj_nearest_object_with_behavior(bhvCurrPreviewObject);
        if (!previewObj) {
            s8 pos[3];
            vec3_set(pos, cmm_cursor_pos[0], cmm_cursor_pos[1], cmm_cursor_pos[2]);

            if (cmm_place_mode == CMM_PM_OBJ) {
                struct cmm_object_info *info = cmm_object_place_types[cmm_id_selection].info;
                if (cmm_object_place_types[cmm_id_selection].multipleObjs) {
                    info = &info[cmm_param_selection];
                }

                spawn_preview_object(pos, cmm_rot_selection, cmm_param_selection, cmm_param_selection, info, bhvCurrPreviewObject,FALSE);
            } else if (cmm_place_mode == CMM_PM_TILE && cmm_id_selection == TILE_TYPE_CULL) {
                spawn_preview_object(pos, cmm_rot_selection, 0, 0, &cmm_cullmarker_preview, bhvCurrPreviewObject, FALSE);
            }
        }
    }

    if (cmm_menu_state != CMM_MAKE_SCREENSHOT) {
        cmm_camera_foc[0] = lerp(cmm_camera_foc[0], GRID_TO_POS(cmm_cursor_pos[0]),  0.2f);
        cmm_camera_foc[1] = lerp(cmm_camera_foc[1], GRID_TO_POS(cmm_cursor_pos[1]), 0.2f);
        cmm_camera_foc[2] = lerp(cmm_camera_foc[2], GRID_TO_POS(cmm_cursor_pos[2]),  0.2f);

        vec3_copy(cmm_camera_pos,cmm_camera_foc);
        vec3_add(cmm_camera_pos,cam_pos_offset);
    }
}

#include "src/game/cursed_mirror_maker_menu.inc.c"
