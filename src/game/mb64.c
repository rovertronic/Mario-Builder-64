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
#include "mb64.h"
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

u8 mb64_level_action = MB64_LA_BUILD;
u8 mb64_mode = MB64_MODE_UNINITIALIZED;
u8 mb64_target_mode = MB64_MODE_MAKE;
u8 mb64_joystick_timer = 0;
s8 mb64_cursor_pos[3] = {32,0,32};

Vec3f mb64_camera_pos = {0.0f,0.0f,0.0f};
Vec3f mb64_camera_pos_prev;
Vec3f mb64_camera_foc = {0.0f,0.0f,0.0f};
f32 mb64_camera_fov = 45.0f;
s16 mb64_camera_angle = 0;
u8 mb64_camera_rot_offset = 0;
s8 mb64_camera_zoom_index = 2;
f32 mb64_current_camera_zoom[2] = {1500.0f,800.0f};

u8 mb64_place_mode = MB64_PM_NONE;

s8 mb64_id_selection = 0;
u8 mb64_rot_selection = 0;
s16 mb64_param_selection = 0;
s16 mb64_mat_selection = 0;

struct mb64_grid_obj mb64_grid_data[64][64][64] = {0};

Gfx mb64_terrain_gfx[MB64_GFX_SIZE]; //gfx
Gfx *mb64_terrain_gfx_tp;
Gfx *mb64_trajectory_gfx;
Vtx mb64_terrain_vtx[MB64_VTX_SIZE];
Vtx *mb64_trajectory_vtx;

u32 mb64_gfx_total = 0;
u32 mb64_vtx_total = 0;

struct mb64_tile mb64_tile_data[MB64_TILE_POOL_SIZE];
struct mb64_obj mb64_object_data[MB64_MAX_OBJS];
u16 mb64_tile_data_indices[NUM_MATERIALS_PER_THEME + 10] = {0};
u16 mb64_tile_count = 0;
u16 mb64_object_count = 0;
u16 mb64_object_limit_count = 0; // Tracks additional objects like in coin formations, flame spinners
u16 mb64_building_collision = FALSE; // 0 = building gfx, 1 = building collision

struct Object *mb64_boundary_object[6]; //one for each side

Trajectory mb64_trajectory_list[MB64_MAX_TRAJECTORIES][MB64_TRAJECTORY_LENGTH][4];
u16 mb64_trajectory_edit_index = 0;
u8 mb64_trajectory_to_edit = 0;
u8 mb64_trajectories_used = 0;
u8 mb64_txt_recording[] = {TXT_RECORDING};
u8 mb64_txt_freecam[] = {TXT_FREECAM};

Vtx *mb64_curr_vtx;
Gfx *mb64_curr_gfx;
u16 mb64_gfx_index;

u8 mb64_use_alt_uvs = FALSE; // Used for decals and special tile shapes
s8 mb64_uv_offset = -16;
u8 mb64_render_flip_normals = FALSE; // Used for drawing water tiles
u8 mb64_render_culling_off = FALSE; // Used for drawing preview blocks in custom theme menu
u8 mb64_growth_render_type = 0;
u8 mb64_curr_mat_has_topside = FALSE;
u8 mb64_curr_poly_vert_count = 4; // 3 = tri, 4 = quad
u8 mb64_curr_boundary = 0;

TerrainData mb64_curr_coltype = SURFACE_DEFAULT;

// dialog edit stuff
struct mb64_obj * mb64_dialog_edit_ptr = NULL;
s8 mb64_dialog_subject_index = 0;
s8 mb64_dialog_topic_index = 0;

//play mode stuff
u8 mb64_play_stars = 0;
u8 mb64_play_stars_max = 0;
u64 mb64_play_stars_bitfield = 0;
u32 mb64_play_badge_bitfield = 0;
u8 mb64_play_onoff = FALSE;
s16 mb64_play_s16_water_level = 0;
u32 mb64_play_speedrun_timer = 0;

//LEVEL SETTINGS INDEX
u8 mb64_lopt_costume = 0;

u8 mb64_lopt_seq[5] = {0,0,0,0,0}; // Song index
u8 mb64_lopt_seq_seqtype = 0; // Level Music, Race Music, Boss Music 
u8 mb64_lopt_seq_album = 0; // Category
u8 mb64_lopt_seq_song = 0; // Song index within category

u8 mb64_lopt_envfx = 0;
u8 mb64_lopt_theme = 0;
u8 mb64_lopt_bg = 0;
u8 mb64_lopt_boundary_mat = 0;
u8 mb64_lopt_boundary = 0;
u8 mb64_lopt_boundary_height = 0;
u8 mb64_lopt_game = MB64_GAME_VANILLA;
u8 mb64_lopt_size = 0;
u8 mb64_newsize = 0; // Used for changing level sizes
u8 mb64_lopt_template = 0;
u8 mb64_lopt_coinstar = 0;
u8 mb64_lopt_waterlevel = 0;
u8 mb64_lopt_secret = 0;

//UI
u8 mb64_menu_state = MB64_MAKE_MAIN;
s16 mb64_menu_index = 0;
s16 mb64_menu_index_max = 1;
s8 mb64_toolbar_index = 0;
s8 mb64_toolbox_index = 0;
u8 mb64_prepare_level_screenshot = FALSE;
u8 mb64_do_save = FALSE;

char *mb64_topleft_message = NULL;
u8 mb64_topleft_is_tip = FALSE;
u16 mb64_topleft_max_timer = 120;
u16 mb64_topleft_timer = 0;
f32 mb64_topleft_vels[3];

struct mb64_level_save_header mb64_save;
char mb64_username[MAX_USERNAME_SIZE];
u8 mb64_has_username = FALSE;

u8 mb64_num_vertices_cached = 0;
u8 mb64_num_tris_cached = 0;
u8 mb64_cached_tris[16][3];
s16 mb64_tip_timer = 0;

struct ExclamationBoxContents *mb64_exclamation_box_contents;

#include "src/game/mb64_display_funcs.inc.c"
#include "src/game/mb64_data.inc.c"

s32 mb64_count_stars(void) {
    s32 numStars = 0;
    for (s32 i = 0; i < mb64_object_count; i++) {
        if (mb64_object_type_list[mb64_object_data[i].type].flags & OBJ_TYPE_HAS_STAR) {
            numStars++;
        }
        if (mb64_object_data[i].imbue == IMBUE_STAR) {
            numStars++;
        }
    }
    return numStars;
}

void bhv_preview_object_init(void) {
    if (!o->oPreviewObjDisplayFunc) return;
    ((DisplayFunc)o->oPreviewObjDisplayFunc)(MB64_DF_CONTEXT_INIT);
}
void bhv_preview_object_loop(void) {
    if (!o->oPreviewObjDisplayFunc) return;
    ((DisplayFunc)o->oPreviewObjDisplayFunc)(MB64_DF_CONTEXT_MAIN);
}

void play_place_sound(u32 soundBits) {
    play_sound(soundBits, gGlobalSoundSource);
}

void mb64_show_topleft_message(char *message, s32 isTip) {
    mb64_topleft_is_tip = isTip;
    mb64_topleft_max_timer = (isTip ? 220 : 120);
    if ((message != mb64_topleft_message) || (mb64_topleft_timer < 30)) {
        mb64_topleft_message = message;
        mb64_topleft_timer = mb64_topleft_max_timer;
    } else {
        if (mb64_topleft_timer < mb64_topleft_max_timer - 30) mb64_topleft_timer = mb64_topleft_max_timer - 30;
    }
}
void mb64_show_error_message(char *message) {
    mb64_show_topleft_message(message, FALSE);
    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
}
void mb64_show_tip() {
    s32 count = ARRAY_COUNT(mb64_tips);
    if (mb64_lopt_game != MB64_GAME_BTCM) count -= NUM_BTCM_TIPS;
    mb64_show_topleft_message(mb64_tips[(s32)(random_float() * count)], TRUE);
}

void reset_play_state(void) {
    mb64_play_stars = 0;
    mb64_play_stars_bitfield = 0;
    mb64_play_badge_bitfield = 0;

    // & water level
    mb64_play_s16_water_level = -8220+(mb64_lopt_waterlevel*TILE_SIZE);
    gWDWWaterLevelChanging = FALSE;
    mb64_play_onoff = FALSE;

    mb64_play_speedrun_timer = 0;
}

u8 mb64_grid_min = 0;
u8 mb64_grid_size = 64;

u32 coords_in_range(s8 pos[3]) {
    if (pos[0] < mb64_grid_min || pos[0] > mb64_grid_min + mb64_grid_size - 1) return FALSE;
    if (pos[1] < 0 || pos[1] > 63) return FALSE;
    if (pos[2] < mb64_grid_min || pos[2] > mb64_grid_min + mb64_grid_size - 1) return FALSE;
    return TRUE;
}

s32 tile_sanity_check(void) {
    if (mb64_tile_count >= MB64_TILE_POOL_SIZE) {
        mb64_show_error_message("Tile limit reached! (max 15,000)");
        return FALSE;
    }
    if (mb64_vtx_total >= MB64_VTX_SIZE - 100) {
        if (mb64_id_selection != TILE_TYPE_CULL) {
            mb64_show_error_message("Vertex limit reached! (max 50,000)");
            return FALSE;
        }
    }
    if (mb64_gfx_total >= MB64_GFX_SIZE - 100) {
        mb64_show_error_message("Graphics pool is full!");
        return FALSE;
    }

    return TRUE;
}

// Get number of extra objects used by an object
s32 get_extra_objects(u32 id, s32 param) {
    if (id == OBJECT_TYPE_FIRE_SPINNER) {
        return (param + 2) * 2;
    }
    if (id == OBJECT_TYPE_COIN_FORMATION) {
        return (param <= 1 ? 5 : 8);
    }
    return mb64_object_type_list[id].numExtraObjects;
}

s32 object_sanity_check(void) {
    struct mb64_object_info *info = &mb64_object_type_list[mb64_id_selection];

    if (mb64_object_limit_count + get_extra_objects(mb64_id_selection, mb64_param_selection) >= MB64_MAX_OBJS) {
        mb64_show_error_message("Object limit reached! (max 512)");
        return FALSE;
    }

    if (info->flags & OBJ_TYPE_TRAJECTORY) {
        if (mb64_trajectories_used >= MB64_MAX_TRAJECTORIES) {
            mb64_show_error_message("Trajectory limit reached! (max 20)");
            return FALSE;
        }
    }

    if (info->flags & OBJ_TYPE_HAS_STAR) {
        // Count stars
        s32 numStars = mb64_count_stars();
        if (numStars >= 63) {
            mb64_show_error_message("Star limit reached! (max 63)");
            return FALSE;
        }
    }

    if (mb64_id_selection == OBJECT_TYPE_RED_COIN_STAR) {
        for (u32 i = 0; i < mb64_object_count; i++) {
            if (mb64_object_data[i].type == OBJECT_TYPE_RED_COIN_STAR) {
                mb64_show_error_message("Red Coin Star already placed!");
                return FALSE;
            }
        }
    }

    if (mb64_id_selection == OBJECT_TYPE_SHOWRUNNER) {
        s32 numRunners = 0;
        for (u32 i = 0; i < mb64_object_count; i++) {
            if (mb64_object_data[i].type == OBJECT_TYPE_SHOWRUNNER) {
                numRunners++;
            }
            if (numRunners >= 3) {
                mb64_show_error_message("Showrunner limit reached! (max 3)");
                return FALSE;
            }
        }
    }

    if (mb64_id_selection == OBJECT_TYPE_PHANTASM) {
        s32 num = 0;
        for (u32 i = 0; i < mb64_object_count; i++) {
            if (mb64_object_data[i].type == OBJECT_TYPE_PHANTASM) {
                num++;
            }
            if (num >= 12) {
                mb64_show_error_message("Cosmic Phantasm limit reached! (max 12)");
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
    mb64_grid_data[pos[0]][pos[1]][pos[2]].rot = rot_;       \
    mb64_grid_data[pos[0]][pos[1]][pos[2]].type = type_;     \
    mb64_grid_data[pos[0]][pos[1]][pos[2]].mat = mat_;       \
    mb64_grid_data[pos[0]][pos[1]][pos[2]].waterlogged = 0;  \
}

#define remove_terrain_data(pos) {                         \
    mb64_grid_data[pos[0]][pos[1]][pos[2]].rot = 0;         \
    mb64_grid_data[pos[0]][pos[1]][pos[2]].type = TILE_TYPE_EMPTY; \
    mb64_grid_data[pos[0]][pos[1]][pos[2]].mat = 0;         \
    mb64_grid_data[pos[0]][pos[1]][pos[2]].waterlogged = 0; \
}

#define get_grid_tile(pos) (&(mb64_grid_data[(pos)[0]][(pos)[1]][(pos)[2]]))

#define rotate_direction(dir, rot) (mb64_rotated_dirs[rot][dir])

u32 get_faceshape(s8 pos[3], u32 dir) {
    struct mb64_terrain *terrain;
    if (mb64_render_culling_off) return MB64_FACESHAPE_EMPTY;

    struct mb64_grid_obj *tile = get_grid_tile(pos);
    s8 tileType = tile->type;
    if (tileType == TILE_TYPE_EMPTY) return MB64_FACESHAPE_EMPTY;

    if (tileType == TILE_TYPE_POLE) terrain = &mb64_terrain_pole;
    else terrain = mb64_terrain_info_list[tileType].terrain;

    if (!terrain) return MB64_FACESHAPE_EMPTY;

    u8 rot = tile->rot;
    dir = rotate_direction(dir,((4-rot) % 4)) ^ 1;

    for (u32 i = 0; i < terrain->numTris; i++) {
        struct mb64_terrain_poly *tri = &terrain->tris[i];
        if (tri->faceDir == dir) {
            return tri->faceshape;
        }
    }
    for (u32 i = 0; i < terrain->numQuads; i++) {
        struct mb64_terrain_poly *quad = &terrain->quads[i];
        if (quad->faceDir == dir) {
            return quad->faceshape;
        }
    }
    return MB64_FACESHAPE_EMPTY;
}

#define place_occupy_data(pos) { \
    mb64_grid_data[pos[0]][pos[1]][pos[2]].occupied = TRUE; \
}

#define remove_occupy_data(pos) { \
    mb64_grid_data[pos[0]][pos[1]][pos[2]].occupied = FALSE; \
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
    if (dir != MB64_DIRECTION_UP) {
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
// If this returns FALSE then the material can be culled.
s32 cutout_skip_culling_check(s32 curMat, s32 otherMat, s32 direction) {
    s32 curMatClass, otherMatClass;
    if (curMat == otherMat) return FALSE;
    curMatClass = get_side_class(curMat, direction);
    otherMatClass = get_side_class(otherMat, direction^1);
    if (curMatClass == otherMatClass) {
        return (curMatClass == CLASS_TRANSPARENT);
    } else {
        if ((curMatClass == CLASS_HOLLOW_CUTOUT) || (curMatClass == CLASS_HOLLOW_TRANSPARENT)) {
            if (direction == MB64_DIRECTION_DOWN) {
                if (get_side_class(otherMat, MB64_DIRECTION_DOWN) == curMatClass) return FALSE;
            }
        }
        return (curMatClass < otherMatClass);
    }
}

// Used for determining if a water side should be culled.
u32 block_side_is_solid(s32 adjMat, s32 mat, s32 direction) {
    s32 adjMatClass = get_side_class(adjMat, direction^1);
    if (adjMatClass == CLASS_CUTOUT) return FALSE;
    if (adjMatClass != CLASS_HOLLOW_CUTOUT) return TRUE; // cannot be waterlogged
    // Now we know that the side is a hollow cutout
    if (mat == -1) return TRUE; // adjMat should be confirmed to have a full face
    s32 matClass = get_side_class(mat, direction);
    return (matClass != CLASS_HOLLOW_CUTOUT);
    // Will return FALSE if both materials are hollow cutouts but the waterlogged block
    // isn't a full faceshape. Not a big deal
}

s32 should_cull(s8 pos[3], s32 direction, s32 faceshape, s32 rot) {
    if (faceshape == MB64_FACESHAPE_EMPTY) return FALSE;
    if (mb64_render_culling_off) return FALSE;
    direction = rotate_direction(direction, rot);

    s8 adjPos[3];
    vec3_sum(adjPos, pos, cullOffsetLUT[direction]);

    if (AT_CEILING(pos[1]) && (direction == MB64_DIRECTION_UP)) return TRUE;

    if (!coords_in_range(adjPos)) {
        if (direction == MB64_DIRECTION_UP) return FALSE;
        if (direction == MB64_DIRECTION_DOWN) {
            return (mb64_curr_boundary & MB64_BOUNDARY_INNER_FLOOR) != 0;
        }
        return ((mb64_curr_boundary & MB64_BOUNDARY_INNER_WALLS) && (pos[1] < mb64_lopt_boundary_height));
    }
    struct mb64_grid_obj *adjTile = get_grid_tile(adjPos);
    s32 tileType = adjTile->type;
    switch(tileType) {
        case TILE_TYPE_CULL:
            return TRUE;
        case TILE_TYPE_TROLL:
            if (mb64_building_collision) return FALSE;
            break;
    }

    if (cutout_skip_culling_check(get_grid_tile(pos)->mat, adjTile->mat, direction)) return FALSE;
    s32 otherFaceshape = get_faceshape(adjPos, direction);

    if (otherFaceshape == MB64_FACESHAPE_EMPTY) return FALSE;
    if (otherFaceshape == MB64_FACESHAPE_FULL) return TRUE;
    if (faceshape == MB64_FACESHAPE_FULL) return FALSE;
    if ((faceshape == MB64_FACESHAPE_TOPTRI) || (faceshape == MB64_FACESHAPE_TOPHALF)) {
        if (otherFaceshape == faceshape) {
            u8 otherrot = adjTile->rot;
            return (otherrot == rot);
        } else return FALSE;
    }
    if (faceshape == MB64_FACESHAPE_BOTTOMSLAB || faceshape == MB64_FACESHAPE_TOPSLAB || faceshape == MB64_FACESHAPE_POLETOP) {
        if (otherFaceshape == faceshape) return TRUE;
    }
    if (faceshape == (otherFaceshape^1)) return TRUE;
    // Slab priority lists
    if (((faceshape & 0x10) && (otherFaceshape & 0x10)) ||
        ((faceshape & 0x20) && (otherFaceshape & 0x20))) return (faceshape > otherFaceshape);
    return FALSE;
}

// Additional culling check for certain grass overhangs. Assumes should_cull has already failed.
s32 should_cull_topslab_check(s8 pos[3], s32 direction) {
    s8 adjPos[3];
    vec3_sum(adjPos, pos, cullOffsetLUT[direction]);
    if (!coords_in_range(adjPos)) return FALSE;

    s32 otherFaceshape = get_faceshape(adjPos, direction);
    if ((otherFaceshape >= MB64_FACESHAPE_DOWNUPPERGENTLE_1) && (otherFaceshape <= MB64_FACESHAPE_TOPSLAB)) return TRUE;
    return FALSE;
}

void cache_tri(u8 v1, u8 v2, u8 v3) {
    mb64_cached_tris[mb64_num_tris_cached][0] = mb64_num_vertices_cached + v1;
    mb64_cached_tris[mb64_num_tris_cached][1] = mb64_num_vertices_cached + v2;
    mb64_cached_tris[mb64_num_tris_cached][2] = mb64_num_vertices_cached + v3;
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
    if (mb64_num_vertices_cached > 28) {
        display_cached_tris();
    }
}

void rotate_obj_toward_trajectory_angle(struct Object * obj, u32 traj_id) {
    if ((mb64_trajectory_list[traj_id][0][0] == -1)||(mb64_trajectory_list[traj_id][1][0] == -1)) return;

    s16 angle_to_trajectory;
    if (!trajectory_get_target_angle(&angle_to_trajectory, &mb64_trajectory_list[traj_id][0], &mb64_trajectory_list[traj_id][1])) {
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

    make_vertex(mb64_curr_vtx, mb64_num_vertices_cached,     pos1[0] + cy, pos1[1], pos1[2] - sy, 0, 0, 0, 0, 0, 0xFF);
    make_vertex(mb64_curr_vtx, mb64_num_vertices_cached + 1, pos1[0] - cy, pos1[1], pos1[2] + sy, 0, 0, 0, 0, 0, 0xFF);
    make_vertex(mb64_curr_vtx, mb64_num_vertices_cached + 2, pos2[0] + cy, pos2[1], pos2[2] - sy, 0, length, 0, 0, 0, 0xFF);
    make_vertex(mb64_curr_vtx, mb64_num_vertices_cached + 3, pos2[0] - cy, pos2[1], pos2[2] + sy, 0, length, 0, 0, 0, 0xFF);

    cache_tri(0, 1, 2);
    cache_tri(1, 3, 2);
    mb64_num_vertices_cached += 4;
    //check_cached_tris();
    display_cached_tris();

    make_vertex(mb64_curr_vtx, mb64_num_vertices_cached,     pos1[0] + spsy, pos1[1] - cp, pos1[2] + spcy, 0, 0, 0, 0, 0, 0xFF);
    make_vertex(mb64_curr_vtx, mb64_num_vertices_cached + 1, pos1[0] - spsy, pos1[1] + cp, pos1[2] - spcy, 0, 0, 0, 0, 0, 0xFF);
    make_vertex(mb64_curr_vtx, mb64_num_vertices_cached + 2, pos2[0] + spsy, pos2[1] - cp, pos2[2] + spcy, 0, length, 0, 0, 0, 0xFF);
    make_vertex(mb64_curr_vtx, mb64_num_vertices_cached + 3, pos2[0] - spsy, pos2[1] + cp, pos2[2] - spcy, 0, length, 0, 0, 0, 0xFF);

    cache_tri(0, 1, 2);
    cache_tri(1, 3, 2);
    mb64_num_vertices_cached += 4;
    //check_cached_tris();
    display_cached_tris();
}

void generate_trajectory_gfx(void) {
    mb64_curr_gfx = mb64_trajectory_gfx;
    mb64_curr_vtx = mb64_trajectory_vtx;
    mb64_gfx_index = 0;
    gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], mat_maker_MakerLineMat_layer1);

    for (s32 traj = 0; traj < mb64_trajectories_used; traj++) {
        Trajectory (*curr_trajectory)[4] = mb64_trajectory_list[traj];
        if (curr_trajectory[0][0] == -1) continue;
        s16 pos1[3], pos2[3];
        s32 isLoop = FALSE;

        // Find object corresponding to this trajectory
        for (s32 i = 0; i < mb64_object_count; i++) {
            if (mb64_object_type_list[mb64_object_data[i].type].flags & OBJ_TYPE_TRAJECTORY) {
                if (mb64_object_data[i].bparam == traj) {
                    // Check if it loops or not
                    if (mb64_object_data[i].type == OBJECT_TYPE_PLATFORM_LOOPING) {
                        isLoop = TRUE;
                        gDPSetPrimColor(&mb64_curr_gfx[mb64_gfx_index++], 0, 0, 0, 0, 255, 255);
                    } else {
                        gDPSetPrimColor(&mb64_curr_gfx[mb64_gfx_index++], 0, 0, 255, 255, 0, 255);
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
        if (traj == mb64_trajectory_to_edit && mb64_menu_state == MB64_MAKE_TRAJECTORY) {
            vec3_set(pos1, curr_trajectory[i][1], curr_trajectory[i][2], curr_trajectory[i][3]);
            vec3_set(pos2, GRID_TO_POS(mb64_cursor_pos[0]), GRID_TO_POS(mb64_cursor_pos[1]), GRID_TO_POS(mb64_cursor_pos[2]));
            draw_dotted_line(pos1, pos2);
        }
        if (isLoop) {
            vec3_set(pos1, curr_trajectory[0][1], curr_trajectory[0][2], curr_trajectory[0][3]);
            draw_dotted_line(pos2, pos1);
        }
        display_cached_tris();
    }

    gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], mat_revert_maker_MakerLineMat_layer1);
    gSPEndDisplayList(&mb64_curr_gfx[mb64_gfx_index]);
}

void mb64_transform_vtx_with_rot(s8 v[][3], s8 oldv[][3], u32 rot) {
    for (u32 i = 0; i < mb64_curr_poly_vert_count; i++) {
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
        case MB64_DIRECTION_NEG_X: *uAxis = 2; *vAxis = 1; return TRUE;
        case MB64_DIRECTION_POS_X: *uAxis = 2; *vAxis = 1; return FALSE;
        case MB64_DIRECTION_DOWN: *uAxis = 2; *vAxis = 0; return FALSE;
        case MB64_DIRECTION_UP: *uAxis = 2; *vAxis = 0; return FALSE;
        case MB64_DIRECTION_NEG_Z: *uAxis = 0; *vAxis = 1; return FALSE;
        /*case MB64_DIRECTION_POS_Z:*/ default: *uAxis = 0; *vAxis = 1; return TRUE;
    }
}

void render_poly(struct mb64_terrain_poly *poly, s8 pos[3], u32 rot) {
    s8 n[3];
    u8 uAxis, vAxis;

    s8 newVtx[4][3];
    mb64_transform_vtx_with_rot(newVtx, poly->vtx, rot);
    s32 flipU = render_get_normal_and_uvs(newVtx, poly->faceDir, rot, &uAxis, &vAxis, n);

    for (u32 i = 0; i < mb64_curr_poly_vert_count; i++) {
        s16 u, v;
        if (mb64_use_alt_uvs && poly->altuvs) {
            u = 16 - (*poly->altuvs)[i][0];
            v = 16 - (*poly->altuvs)[i][1];
        } else {
            u = newVtx[i][uAxis];
            if (!flipU) u = 16 - u;
            v = 16 - newVtx[i][vAxis];
        }
        make_vertex(mb64_curr_vtx, mb64_num_vertices_cached + i,
            GRID_TO_POS(pos[0]) + ((newVtx[i][0] - 8) * 16),
            GRID_TO_POS(pos[1]) + ((newVtx[i][1] - 8) * 16),
            GRID_TO_POS(pos[2]) + ((newVtx[i][2] - 8) * 16),
            (u * 64 + mb64_uv_offset), (v * 64 + mb64_uv_offset),
            n[0], n[1], n[2], 0xFF);
    }
    
    u32 isQuad = (mb64_curr_poly_vert_count == 4);
    if (mb64_render_flip_normals) {
        cache_tri(0, 2, 1);
        if (isQuad) cache_tri(1, 2, 3);
    } else {
        cache_tri(0, 1, 2);
        if (isQuad) cache_tri(1, 3, 2);
    }
    mb64_num_vertices_cached += mb64_curr_poly_vert_count;
    check_cached_tris();
}

// Create new static surface
extern struct Surface *alloc_surface(u32 dynamic);
extern void add_surface(struct Surface *surface, s32 dynamic);
void mb64_create_surface(TerrainData v1[3], TerrainData v2[3], TerrainData v3[3]) { 
    struct Surface *surface = alloc_surface(FALSE);

    vec3_copy(surface->vertex1, v1);
    vec3_copy(surface->vertex2, v2);
    vec3_copy(surface->vertex3, v3);

    s16 min,max;
    min_max_3s(v1[1], v2[1], v3[1], &min, &max);
    surface->lowerY = (min - SURFACE_VERTICAL_BUFFER);
    surface->upperY = (max + SURFACE_VERTICAL_BUFFER);

    surface->type = mb64_curr_coltype;
    add_surface(surface, FALSE);
};

TerrainData colVtxs[4][3];

void mb64_create_poly(struct mb64_terrain_poly *poly, s8 pos[3], u32 rot) {
    s8 newVtx[4][3];
    mb64_transform_vtx_with_rot(newVtx, poly->vtx, rot);
    for (u32 k = 0; k < mb64_curr_poly_vert_count; k++) {
        colVtxs[k][0] = GRID_TO_POS(pos[0]) + ((newVtx[k][0] - 8) * (TILE_SIZE/16)),
        colVtxs[k][1] = GRID_TO_POS(pos[1]) + ((newVtx[k][1] - 8) * (TILE_SIZE/16)),
        colVtxs[k][2] = GRID_TO_POS(pos[2]) + ((newVtx[k][2] - 8) * (TILE_SIZE/16));
    }
    mb64_create_surface(colVtxs[0], colVtxs[1], colVtxs[2]);
    if (mb64_curr_poly_vert_count == 4) {
        mb64_create_surface(colVtxs[1], colVtxs[3], colVtxs[2]);
    }
}

void process_poly(s8 pos[3], struct mb64_terrain_poly *quad, u32 rot) {
    if (!mb64_building_collision)
        render_poly(quad, pos, rot);
    else
        mb64_create_poly(quad, pos, rot);
}

void grass_slope_extra_decal_uvs(s8 newUVs[][2], s8 vtx[][3], s32 side, s32 scalefactor, s32 count) {
    for (s32 i = 0; i < count; i++) {
        newUVs[i][0] = 16 - vtx[i][0];
        s32 upFactor = (side == 0 ? vtx[i][0] : 16 - vtx[i][0]);
        newUVs[i][1] = vtx[i][1] - ((upFactor*scalefactor) >> 1); // multiply by scalefactor/2
    }
}

void render_grass_slope_extra_decal(s8 pos[3], u32 direction, u32 grassType) {
    // Check if below block is in range
    s8 newpos[3];
    s8 newUVs[4][2];
    vec3_set(newpos, pos[0], pos[1]-1, pos[2]);
    if (!coords_in_range(newpos)) return;

    // Check if below block matches material
    u8 curMat = get_grid_tile(pos)->mat;
    u8 belowMat = get_grid_tile(newpos)->mat;
    if (curMat != belowMat) return;

    // Check if below block is right shape and culled
    // Shape of face of above block on same side
    s32 otherFaceshape = get_faceshape(newpos, direction^1);
    if (should_cull(newpos, direction, otherFaceshape, 0)) return;
    if (should_cull_topslab_check(newpos, direction)) return;
    
    // Calculate effective rotation of face to print. very ugly
    u8 targetRot = 0;
    switch (direction) {
        case MB64_DIRECTION_POS_X:
            targetRot = 1;
            break;
        case MB64_DIRECTION_NEG_X:
            targetRot = 3;
            break;
        //case MB64_DIRECTION_POS_Z:
            //targetRot = 0;
            //break;
        case MB64_DIRECTION_NEG_Z:
            targetRot = 2;
            break;
    }

    s32 index;
    s32 oldVerts = mb64_curr_poly_vert_count;

    switch (otherFaceshape) {
        default:
            return;
        // Face is full quad
        case MB64_FACESHAPE_FULL:
            index = 0; mb64_curr_poly_vert_count = 4;
            break;
        case MB64_FACESHAPE_DOWNTRI_1:
            index = 1; mb64_curr_poly_vert_count = 3;
            break;
        case MB64_FACESHAPE_DOWNTRI_2:
            index = 2; mb64_curr_poly_vert_count = 3;
            break;
        case MB64_FACESHAPE_DOWNUPPERGENTLE_1:
        case MB64_FACESHAPE_DOWNUPPERGENTLE_2:
        case MB64_FACESHAPE_TOPSLAB:
            index = 3; mb64_curr_poly_vert_count = 4;
            break;
        case MB64_FACESHAPE_HALFSIDE_1:
            if (grassType == MB64_GROWTH_SLOPE_SIDE_L) return;
            index = 4; mb64_curr_poly_vert_count = 4;
            break;
        case MB64_FACESHAPE_HALFSIDE_2:
            if (grassType == MB64_GROWTH_SLOPE_SIDE_R) return;
            index = 5; mb64_curr_poly_vert_count = 4;
            break;
        case MB64_FACESHAPE_DOWNLOWERGENTLE_1:
            index = 6; mb64_curr_poly_vert_count = 3;
            break;
        case MB64_FACESHAPE_DOWNLOWERGENTLE_2:
            index = 7; mb64_curr_poly_vert_count = 3;
            break;
    }

    s32 side = grassType & 1;
    s32 scalefactor = (grassType & 2) ? 1 : 2;

    struct mb64_terrain_poly *poly = slope_decal_below_surfs[index];
    grass_slope_extra_decal_uvs(newUVs, poly->vtx, side, scalefactor, mb64_curr_poly_vert_count);
    poly->altuvs = newUVs;
    render_poly(poly, newpos, targetRot);
    mb64_curr_poly_vert_count = oldVerts;

    return;
}

// Determines if the faceshape as a solid bottom edge and two vertical edges on either side
u32 faceshape_has_full_bottom(u32 faceshape) {
    return (faceshape == MB64_FACESHAPE_FULL) ||
        (faceshape >= MB64_FACESHAPE_UPPERGENTLE_1 && faceshape <= MB64_FACESHAPE_BOTTOMSLAB);
}

u32 should_render_grass_side(s8 pos[3], u32 direction, u32 faceshape, u32 rot, u32 grassType) {
    s8 abovePos[3];
    vec3_set(abovePos, pos[0], pos[1]+1, pos[2]);
    struct mb64_grid_obj *tile = get_grid_tile(pos);
    struct mb64_grid_obj *aboveTile = get_grid_tile(abovePos);
    if (should_cull(pos, direction, faceshape, rot)) return FALSE;

    // Other sides that don't care about the above block (e.g. bottom slab)
    if (grassType == MB64_GROWTH_UNCONDITIONAL) return TRUE;

    // Render extra decal for slopes if necessary
    // The side of the slope itself is unconditional and will always render
    if (grassType >= MB64_GROWTH_EXTRADECAL_START) {
        render_grass_slope_extra_decal(pos, rotate_direction(direction, rot), grassType);
        return TRUE;
    }

    if (AT_CEILING(pos[1])) return FALSE;
    if (!coords_in_range(abovePos)) return TRUE;

    if (faceshape != MB64_FACESHAPE_EMPTY) {
        if ((grassType == MB64_GROWTH_HALF_SIDE) || (grassType == MB64_GROWTH_NORMAL_SIDE)) {
            if (should_cull_topslab_check(pos, rotate_direction(direction, rot))) return FALSE;
        }
    }

    // Render if above tile is empty
    if (aboveTile->type == TILE_TYPE_EMPTY) return TRUE;
    // Render if above tile is seethrough (some exceptions)
    if (cutout_skip_culling_check(tile->mat, aboveTile->mat, MB64_DIRECTION_UP)) return TRUE;

    s32 otherFaceshape;
    switch (grassType) {
        case MB64_GROWTH_DLGENTLE_UNDER:
            direction = MB64_DIRECTION_POS_Z;
        case MB64_GROWTH_NORMAL_SIDE:
        case MB64_GROWTH_HALF_SIDE:
            // Shape of face of above block on same side
            otherFaceshape = get_faceshape(abovePos, rotate_direction(direction, rot)^1);
            switch (otherFaceshape) {
                case MB64_FACESHAPE_TRI_1:
                case MB64_FACESHAPE_TRI_2:
                case MB64_FACESHAPE_FULL:
                case MB64_FACESHAPE_UPPERGENTLE_1:
                case MB64_FACESHAPE_UPPERGENTLE_2:
                case MB64_FACESHAPE_LOWERGENTLE_1:
                case MB64_FACESHAPE_LOWERGENTLE_2:
                case MB64_FACESHAPE_BOTTOMSLAB:
                    return FALSE;
            }
            if ((grassType == MB64_GROWTH_HALF_SIDE) && (faceshape == otherFaceshape)) {
                return FALSE;
            }
            return TRUE;
        case MB64_GROWTH_UNDERSLOPE_CORNER:
            ;// some very cursed logic here, this is solely for upside-down inside corners
            u8 faceshape1 = get_faceshape(abovePos, rotate_direction(MB64_DIRECTION_POS_Z, rot)^1);
            u8 faceshape2 = get_faceshape(abovePos, rotate_direction(MB64_DIRECTION_POS_X, rot)^1);
            // this is basically just checking for if a normal slope corner is on top at the right angle
            if (faceshape1 == MB64_FACESHAPE_TRI_1 && faceshape2 == MB64_FACESHAPE_TRI_2)
                return FALSE;
            // don't display if either face on top of the inside corner is full
            return !(faceshape_has_full_bottom(faceshape1) || faceshape_has_full_bottom(faceshape2));

        case MB64_GROWTH_DIAGONAL_SIDE:
        case MB64_GROWTH_VSLAB_SIDE:
            otherFaceshape = get_faceshape(abovePos, MB64_DIRECTION_UP);
            if (otherFaceshape == MB64_FACESHAPE_FULL) return FALSE;
            if (otherFaceshape != (grassType == MB64_GROWTH_DIAGONAL_SIDE ? MB64_FACESHAPE_TOPTRI : MB64_FACESHAPE_TOPHALF)) return TRUE;
            if (aboveTile->type == TILE_TYPE_SCORNER) return TRUE;
            u8 otherrot = aboveTile->rot;
            return (otherrot != rot);
    }
    return FALSE;
}

void process_poly_with_growth(s8 pos[3], struct mb64_terrain_poly *poly, u32 rot) {
    switch (mb64_growth_render_type) {
        case 0: // regular tex
            if (mb64_curr_mat_has_topside && (poly->growthType == MB64_GROWTH_FULL)) return;
            if (should_cull(pos, poly->faceDir, poly->faceshape, rot)) return;
            break;
        case 1: // grass top
            if (poly->growthType != MB64_GROWTH_FULL) return;
            if (should_cull(pos, poly->faceDir, poly->faceshape, rot)) return;
            break;
        case 2: // grass decal
            if (poly->growthType == MB64_GROWTH_FULL || poly->growthType == MB64_GROWTH_NONE) return;
            if (!should_render_grass_side(pos, poly->faceDir, poly->faceshape, rot, poly->growthType)) return;
            break;
    }
    process_poly(pos, poly, rot);
}

void process_tile(s8 pos[3], struct mb64_terrain *terrain, u32 rot) {
    mb64_curr_poly_vert_count = 4;
    for (u32 j = 0; j < terrain->numQuads; j++) {
        struct mb64_terrain_poly *quad = &terrain->quads[j];
        process_poly_with_growth(pos, quad, rot);
    }
    mb64_curr_poly_vert_count = 3;
    for (u32 j = 0; j < terrain->numTris; j++) {
        struct mb64_terrain_poly *tri = &terrain->tris[j];
        process_poly_with_growth(pos, tri, rot);
    }
}

#define BAR_CONNECTED_SIDE(bar) ((bar) & 1)
#define BAR_CONNECTED_TOP(bar) (((bar) >> 1) & 0x1)
#define BAR_CONNECTED_BOTTOM(bar) (((bar) >> 2) & 0x1)

void check_bar_side_connections(s8 pos[3], u8 connections[4]) {
    s8 adjacentPos[3];

    for (u32 rot = 0; rot < 4; rot++) {
        connections[rot] = 0;
        s32 dir = rotate_direction(MB64_DIRECTION_POS_Z, rot);
        vec3_sum(adjacentPos, pos, cullOffsetLUT[dir]);
        struct mb64_grid_obj *adjTile = get_grid_tile(adjacentPos);

        if (!coords_in_range(adjacentPos)) {
            if ((mb64_curr_boundary & MB64_BOUNDARY_INNER_WALLS) && 
                adjacentPos[1] < mb64_lopt_boundary_height) {
                connections[rot] = 1;
            }
            continue;
        }

        // If adjacent block is a bar, return true
        if (adjTile->type == TILE_TYPE_BARS) {
            connections[rot] = 1; continue;
        }

        // Else check its a full block
        if ((get_faceshape(adjacentPos, dir) == MB64_FACESHAPE_FULL) || (adjTile->type == TILE_TYPE_CULL)) {
            connections[rot] = 1;
        }
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
        struct mb64_grid_obj *adjTile = get_grid_tile(adjacentPos);

        if (coords_in_range(adjacentPos)) {
            u32 faceshape = get_faceshape(adjacentPos, updown);
            if ((faceshape == MB64_FACESHAPE_FULL) || (adjTile->type == TILE_TYPE_CULL)) {
                for (u32 rot = 0; rot < 4; rot++) {
                    connections[rot] |= (1 << (updown+1)); // Apply top flag to all bars
                }
                connections[4] |= (1 << (updown + 1));
            } else if (faceshape == MB64_FACESHAPE_TOPHALF) {
                connections[(adjTile->rot + 2) % 4] |= (1 << (updown + 1));
            } else if (adjTile->type == TILE_TYPE_BARS) {
                check_bar_side_connections(adjacentPos, adjacentConnections);
                for (u32 rot = 0; rot < 4; rot++) {
                    connections[rot] |= adjacentConnections[rot] << (updown+1); // Apply top flag to all bars
                }
                connections[4] |= (1 << (updown + 1));
            }
        }
    }
    if ((pos[1] == 0) && (mb64_curr_boundary & MB64_BOUNDARY_INNER_FLOOR)) { // Culling for bottom
        for (u32 rot = 0; rot < 5; rot++) {
            connections[rot] |= (1 << 2);
        }
    }
    if (AT_CEILING(pos[1])) { // Culling for top
        for (u32 rot = 0; rot < 5; rot++) {
            connections[rot] |= (1 << 1);
        }
    }
}

void render_bars_side(s8 pos[3], u8 connections[5]) {
    for (u32 rot = 0; rot < 4; rot++) {
        u32 leftRot = (rot + 3) % 4;
        u32 rightRot = (rot + 1) % 4;
        if (BAR_CONNECTED_SIDE(connections[rot])) {
            process_poly(pos, &mb64_terrain_bars_connected_quads[0], rot);
            process_poly(pos, &mb64_terrain_bars_connected_quads[1], rot);
        }
        if (!BAR_CONNECTED_SIDE(connections[rot]) ||
            (BAR_CONNECTED_SIDE(connections[leftRot]) && BAR_CONNECTED_SIDE(connections[rightRot]))) {
            process_poly(pos, mb64_terrain_bars_unconnected_quad, rot);
        }
    }
}

void render_bars_top(s8 pos[3], u8 connections[5]) {
    for (u32 rot = 0; rot < 4; rot++) {
        u32 leftRot = (rot + 3) % 4;
        u32 rightRot = (rot + 1) % 4;
        if (BAR_CONNECTED_SIDE(connections[rot])) {
            if (!BAR_CONNECTED_TOP(connections[rot])) {
                process_poly(pos, &mb64_terrain_bars_connected_quads[2], rot);
            }
            if (!BAR_CONNECTED_BOTTOM(connections[rot])) {
                process_poly(pos, &mb64_terrain_bars_connected_quads[3], rot);
            }
        }
    }
    if (!BAR_CONNECTED_TOP(connections[4])) process_poly(pos, &mb64_terrain_bars_center_quads[0], 0);
    if (!BAR_CONNECTED_BOTTOM(connections[4])) process_poly(pos, &mb64_terrain_bars_center_quads[1], 0);
}

// Find if specific tile of water is fullblock or shallow
u32 is_water_fullblock(s8 pos[3]) {
    s8 abovePos[3];
    if (AT_CEILING(pos[1])) {
        if (MATERIAL(mb64_lopt_boundary_mat).type != MAT_CUTOUT) return TRUE;
    }
    vec3_set(abovePos, pos[0], pos[1]+1, pos[2]);
    if (!coords_in_range(abovePos)) return FALSE;
    // Full block if above block is water
    struct mb64_grid_obj *aboveTile = get_grid_tile(abovePos);
    struct mb64_grid_obj *tile = get_grid_tile(pos);
    if (aboveTile->waterlogged) return TRUE;

    // Full block if above block has solid bottom face
    if ((get_faceshape(abovePos, MB64_DIRECTION_UP) == MB64_FACESHAPE_FULL) && (MATERIAL(aboveTile->mat).type != MAT_CUTOUT)) {
        // If above block is troll, but current block is also troll, then not full block
        if ((tile->type == TILE_TYPE_TROLL) && (aboveTile->type == TILE_TYPE_TROLL)) return FALSE;
        // If bottom block is hollow cutout and top block is some kind of cutout then not full block
        if (tile->type != TILE_TYPE_WATER) {
            u8 curMat = tile->mat;
            u8 aboveMat = aboveTile->mat;
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
    if (AT_CEILING(pos[1])) {
        if ((dir == MB64_DIRECTION_UP) && (MATERIAL(mb64_lopt_boundary_mat).type != MAT_CUTOUT)) return 0;
    }
    struct mb64_grid_obj *adjTile = get_grid_tile(adjacentPos);

    if (!coords_in_range(adjacentPos)) {
        if (dir == MB64_DIRECTION_UP) return 1;
        u32 type = isFullblock ? 2 : 1;
        if (dir == MB64_DIRECTION_DOWN) {
            return (mb64_curr_boundary & MB64_BOUNDARY_INNER_FLOOR) ? 0 : type;
        }
        return ((mb64_curr_boundary & MB64_BOUNDARY_INNER_WALLS) && (pos[1] < mb64_lopt_boundary_height)) ? 0 : type;
    }
    if (adjTile->type == TILE_TYPE_CULL) return 0;

    if (mb64_building_collision) {
        if (adjTile->waterlogged) return 0;
        return isFullblock ? 2 : 1;
    }

    struct mb64_grid_obj *tile = get_grid_tile(pos);

    s32 mat = tile->mat;
    s32 adjMat = adjTile->mat;
    if (tile->type == TILE_TYPE_WATER) {
        mat = -1;
    }
    if ((adjTile->type == TILE_TYPE_WATER) || (adjTile->type == TILE_TYPE_EMPTY)){
        adjMat = -1;
    }

    // Apply normal side culling
    // Usually this would fail if next to a mesh, but it will pass if
    // the current tile is the same material, which in this case will happen
    // if an entire mesh is waterlogged.
    if ((get_faceshape(adjacentPos, dir) == MB64_FACESHAPE_FULL) && block_side_is_solid(adjMat, mat, dir)) return 0;

    // Check if the block that's waterlogged has a full face on the same side
    if ((get_faceshape(pos, dir^1) == MB64_FACESHAPE_FULL) && block_side_is_solid(mat, adjMat, dir^1)) {
        if (!isFullblock && (dir == MB64_DIRECTION_UP)) {
            return 1;
        }
        return 0;
    }

    if (adjTile->waterlogged) {
        // Check if this is a full block, next to a non-full block.
        // If so, use special thin side
        if (dir != MB64_DIRECTION_UP && dir != MB64_DIRECTION_DOWN) {
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
        u8 sideRender = get_water_side_render(pos, mb64_terrain_fullblock_quads[j].faceDir, isFullblock);
        if (sideRender != 0) {
            struct mb64_terrain_poly *poly = &mb64_terrain_water_quadlists[sideRender - 1][j];
            process_poly(pos, poly, 0);
        }
    }
}

void set_render_mode(u32 tileType, u32 disableZ) {
    u32 rendermode = mb64_render_mode_table[tileType];
    if (disableZ) rendermode &= ~(Z_UPD | Z_CMP);
    if (!gIsConsole && (tileType != MAT_TRANSPARENT)) rendermode |= AA_EN;
    gDPPipeSync(&mb64_curr_gfx[mb64_gfx_index++]);
    gDPSetRenderMode(&mb64_curr_gfx[mb64_gfx_index++], rendermode, 0);
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
            if (mb64_terrain_info_list[type].terrain) {
                return mat;
            }
    }
    return END_TILE_INDEX;
}


Gfx *get_sidetex(s32 matid) {
    for (s32 i = 0; i < ARRAY_COUNT(mb64_topmat_table); i++) {
        if (mb64_topmat_table[i].mat == matid) {
            return mb64_topmat_table[i].decaltex;
        }
    }
    return NULL;
}


#define retroland_filter_on() if ((mb64_lopt_theme == MB64_THEME_RETRO) || (mb64_lopt_theme == MB64_THEME_MC)) { gDPSetTextureFilter(&mb64_curr_gfx[mb64_gfx_index++], G_TF_POINT); if (!gIsGliden) {mb64_uv_offset = 0;} }
#define retroland_filter_off() if ((mb64_lopt_theme == MB64_THEME_RETRO) || (mb64_lopt_theme == MB64_THEME_MC)) { gDPSetTextureFilter(&mb64_curr_gfx[mb64_gfx_index++], G_TF_BILERP); mb64_uv_offset = (mb64_lopt_theme == MB64_THEME_MC ? -32 : -16); }

// For render or collision specific code
#define PROC_COLLISION(statement) if (mb64_building_collision)  { statement; }
#define PROC_RENDER(statement)    if (!mb64_building_collision) { statement; }

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
    if (!mb64_building_collision) {
        u8 poleMatType = mb64_mat_table[mb64_theme_table[mb64_lopt_theme].pole].type;
        if (do_process(&poleMatType, processTileRenderMode)) {
            mb64_use_alt_uvs = TRUE;
            mb64_growth_render_type = 0;
            startIndex = mb64_tile_data_indices[POLE_TILETYPE_INDEX];
            endIndex = mb64_tile_data_indices[POLE_TILETYPE_INDEX+1];
            set_render_mode( poleMatType, FALSE);
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], POLE_TEX());
            for (u32 i = startIndex; i < endIndex; i++) {
                s8 pos[3];
                vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);
                process_tile(pos, &mb64_terrain_pole, mb64_tile_data[i].rot);
            }
            display_cached_tris();
        }
        mb64_use_alt_uvs = FALSE;
    }

    for (u32 mat = 0; mat < NUM_MATERIALS_PER_THEME; mat++) {
        u8 matType = MATERIAL(mat).type;
        mb64_growth_render_type = 0;
        mb64_curr_mat_has_topside = HAS_TOPMAT(mat);
        startIndex = mb64_tile_data_indices[mat];
        endIndex = mb64_tile_data_indices[mat+1];

        // RENDER
        if (!mb64_building_collision) {
            if (!do_process(&matType, processTileRenderMode)) {
                goto skip_maintex;
            }

            set_render_mode( matType, FALSE);
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], MATERIAL(mat).gfx);

            // Important to not use matType here so that it's still opaque for screens
            if ((matType == MAT_CUTOUT) || ((MATERIAL(mat).type < MAT_CUTOUT) && (TOPMAT(mat).type >= MAT_CUTOUT))) {
                gSPClearGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK);
            }
        // COLLISION
        } else {
            mb64_curr_coltype = MATERIAL(mat).col;
        }

        for (u32 i = startIndex; i < endIndex; i++) {
            tileType = mb64_tile_data[i].type;
            PROC_COLLISION( if (tileType == TILE_TYPE_TROLL) continue; )
            rot = mb64_tile_data[i].rot;
            vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);
            
            process_tile(pos, mb64_terrain_info_list[tileType].terrain, rot);
        }

        PROC_RENDER( display_cached_tris(); \
                     skip_maintex: )
        
        if (mb64_curr_mat_has_topside) {
            u8 topmatType = TOPMAT(mat).type;
            PROC_RENDER( if (!do_process(&topmatType, processTileRenderMode)) continue; )
            Gfx *sidetex = get_sidetex(TILE_MATDEF(mat).topmat);
            // Only runs when rendering
            if (!mb64_building_collision && (sidetex)) {
                mb64_use_alt_uvs = TRUE;
                gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], sidetex);
                mb64_growth_render_type = 2;

                // This code is pretty ugly. It renders the side decal in decal mode
                // for opaque parts of the texture, and in cutout mode for transparent parts.
                // Luckily this will only double the number of triangles in the rare case
                // that a custom block with a cutout side texture and a topmat with a side decal
                // is made (in order to cover both the opaque and alpha parts of the side tex.)
                // DECAL MODE
                if (matType != MAT_TRANSPARENT) { // Render in decal mode for cutouts, opaque and screen
                    set_render_mode( MAT_DECAL, FALSE);
                    for (u32 i = startIndex; i < endIndex; i++) {
                        tileType = mb64_tile_data[i].type;
                        rot = mb64_tile_data[i].rot;
                        vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);

                        process_tile(pos, mb64_terrain_info_list[tileType].terrain, rot);
                    }
                    display_cached_tris();
                }
                // OPAQUE MODE
                if (matType >= MAT_CUTOUT) { // Render in cutout mode for cutouts and transparent
                    set_render_mode( MAT_CUTOUT, FALSE);
                    for (u32 i = startIndex; i < endIndex; i++) {
                        tileType = mb64_tile_data[i].type;
                        rot = mb64_tile_data[i].rot;
                        vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);

                        process_tile(pos, mb64_terrain_info_list[tileType].terrain, rot);
                    }
                    display_cached_tris();
                }
                mb64_use_alt_uvs = FALSE;
            }

            PROC_COLLISION( mb64_curr_coltype = TOPMAT(mat).col; )
            PROC_RENDER( set_render_mode( topmatType, FALSE); \
                         gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], TOPMAT(mat).gfx); )

            mb64_growth_render_type = 1;
            for (u32 i = startIndex; i < endIndex; i++) {
                tileType = mb64_tile_data[i].type;
                PROC_COLLISION( if (tileType == TILE_TYPE_TROLL) continue; )
                rot = mb64_tile_data[i].rot;
                vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);

                process_tile(pos, mb64_terrain_info_list[tileType].terrain, rot);
            }
            PROC_RENDER( display_cached_tris(); )
        }
        PROC_RENDER( gSPSetGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK); )
    }
}

// Fade: 0 = no fade, 1 = fade at bottom, 2 = fade at top
void render_boundary_quad(struct mb64_boundary_quad *quad, s16 y, s16 yHeight, u32 fade) {
    // Get normal
    Vec3f normal;
    find_vector_perpendicular_to_plane(normal, quad->vtx[0], quad->vtx[1], quad->vtx[2]);
    vec3_normalize(normal);
    s8 n[3];
    s32 normalMult = (mb64_render_flip_normals ? -0x7F : 0x7F);
    n[0] = normal[0]*normalMult;
    n[1] = normal[1]*normalMult;
    n[2] = normal[2]*normalMult;

    s32 uScale = quad->uYScale ? (yHeight * 64) : mb64_grid_size*16;
    s32 vScale = quad->vYScale ? (yHeight * 64) : mb64_grid_size*16;
    for (u32 i = 0; i < 4; i++) {
        s16 u = (quad->u[i & 1])*uScale + mb64_uv_offset;
        s16 v = (quad->v[i >> 1])*vScale + mb64_uv_offset;
        if (quad->flipUvs) { s16 tmp = u; u = v; v = tmp;}
        if (yHeight % 2) v += 512; // offset for odd number of blocks
        u8 alpha = 255;
        if ((ABS(quad->vtx[i][0]) > 32) || (ABS(quad->vtx[i][2]) > 32)) {
            alpha = 0;
        } else if (((fade == 1) && (quad->vtx[i][1] == 0)) || ((fade == 2) && (quad->vtx[i][1] == 1))) {
            alpha = 0;
        }
        make_vertex(mb64_curr_vtx, i+mb64_num_vertices_cached, quad->vtx[i][0]*mb64_grid_size*4, (quad->vtx[i][1]*yHeight*TILE_SIZE + y), quad->vtx[i][2]*mb64_grid_size*4,
            u, v, n[0], n[1], n[2], alpha);
    }
    if (mb64_render_flip_normals) {
        cache_tri(0, 2, 1);
        cache_tri(1, 2, 3);
    } else {
        cache_tri(0, 1, 2);
        cache_tri(1, 3, 2);
    }
    mb64_num_vertices_cached += 4;
    check_cached_tris();
}

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

void generate_terrain_gfx(void) {
    u8 tileType, rot;
    s8 pos[3];

    mb64_curr_gfx = mb64_terrain_gfx;
    mb64_curr_vtx = mb64_terrain_vtx;
    mb64_gfx_index = 0;
    mb64_building_collision = FALSE;

    mb64_use_alt_uvs = FALSE;
    mb64_render_flip_normals = FALSE;
    mb64_curr_mat_has_topside = FALSE;
    mb64_growth_render_type = 0;
    mb64_uv_offset = (mb64_lopt_theme == MB64_THEME_MC ? -32 : -16);

    retroland_filter_on();

    mb64_curr_boundary = mb64_boundary_table[mb64_lopt_boundary];
    if (mb64_lopt_boundary_height == 0) {
        mb64_curr_boundary &= ~MB64_BOUNDARY_CEILING;
        mb64_curr_boundary &= ~MB64_BOUNDARY_INNER_WALLS;
    }
    if ((mb64_curr_boundary & MB64_BOUNDARY_INNER_FLOOR) && !(mb64_curr_boundary & (MB64_BOUNDARY_INNER_WALLS | MB64_BOUNDARY_OUTER_WALLS))) {
        mb64_curr_boundary |= MB64_BOUNDARY_OUTER_FLOOR;
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
        s8 pos[3];
        vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);
        check_bar_connections(pos, connections);
        render_bars_side(pos, connections);
    }
    display_cached_tris();
    gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], BARS_TOPTEX());
    gSPClearGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK);
    for (u32 i = startIndex; i < endIndex; i++) {
        s8 pos[3];
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
    for (u32 i = startIndex; i < endIndex; i++) {
        s8 pos[3];
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

    mb64_play_s16_water_level = -8220+(mb64_lopt_waterlevel*TILE_SIZE); // Update water plane height

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

    //mb64_render_flip_normals = TRUE;
    // Render main water plane, bottom side
    // if (mb64_lopt_waterlevel != 0) {
    //     render_floor((mb64_lopt_waterlevel - 32) * TILE_SIZE - 32);
    // }
    //mb64_render_flip_normals = FALSE;

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

    // A little bit of free performance for N64
    if ((gIsConsole)&&(mb64_vtx_total > 5000)) {
        osViSetSpecialFeatures(OS_VI_DITHER_FILTER_OFF);
        osViSetSpecialFeatures(OS_VI_DIVOT_OFF);
    } else {
        osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON);
        osViSetSpecialFeatures(OS_VI_DIVOT_ON);
    }

    if (mb64_vtx_total >= MB64_VTX_SIZE) {
        mb64_show_error_message("CRITICAL WARNING: Vertex limit exceeded.");
    } else if (mb64_vtx_total >= MB64_VTX_SIZE - 30) {
        mb64_show_error_message("WARNING: Vertex limit is about to overflow.\nCreate any more vertices and you're cooked.");
    }
};

Gfx preview_gfx[50];
Vtx preview_vtx[100];
Gfx water_gfx[50];
Vtx water_vtx[100];

extern void geo_append_display_list(void *displayList, s32 layer);

void render_preview_block(u32 matid, u32 topmatid, s8 pos[3], struct mb64_terrain *terrain, u32 rot, u32 processType, u32 disableZ) {
    mb64_curr_mat_has_topside = (topmatid != matid);

    u8 matType = mb64_mat_table[matid].type;

    if (do_process(&matType, processType)) {
        set_render_mode( matType, disableZ);
        gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], mb64_mat_table[matid].gfx);
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
        process_tile(pos, terrain, rot);
        display_cached_tris();
    }
    gSPSetGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK);
}

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
            if (mb64_place_mode == MB64_PM_OBJ || mb64_place_mode == MB64_PM_NONE) {render_water_plane(); return NULL;}
            mb64_curr_gfx = preview_gfx;
            mb64_curr_vtx = preview_vtx;
            mb64_gfx_index = 0;
            mb64_growth_render_type = 0;

            mb64_building_collision = FALSE;

            retroland_filter_on();

            if (mb64_place_mode == MB64_PM_WATER) {
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
            }
            
            if (terrain) {
                // Handle Virtuaplex screen effect
                if (mat == MB64_MAT_VP_SCREEN || topmat == MB64_MAT_VP_SCREEN) {
                    render_preview_block(mat, topmat, mb64_cursor_pos, terrain, mb64_rot_selection, PROCESS_TILE_VPLEX, FALSE);

                    gSPEndDisplayList(&mb64_curr_gfx[mb64_gfx_index]);
                    geo_append_display_list(mb64_curr_gfx, LAYER_FORCE);

                    mb64_curr_gfx += mb64_gfx_index;
                    mb64_gfx_index = 0;
                    mb64_growth_render_type = 0;
                }

                render_preview_block(mat, topmat, mb64_cursor_pos, terrain, mb64_rot_selection, PROCESS_TILE_BOTH, FALSE);

            } else if (mb64_id_selection != TILE_TYPE_CULL) {
                mb64_use_alt_uvs = TRUE;
                mb64_curr_poly_vert_count = 4;
                if (mb64_id_selection == TILE_TYPE_FENCE) {
                    gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], FENCE_TEX());
                    set_render_mode( MAT_CUTOUT, FALSE);
                    process_tile(mb64_cursor_pos, &mb64_terrain_fence, mb64_rot_selection);
                } else if (mb64_id_selection == TILE_TYPE_POLE) {
                    gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], POLE_TEX());
                    set_render_mode( mb64_mat_table[mb64_theme_table[mb64_lopt_theme].pole].type, FALSE);
                    process_tile(mb64_cursor_pos, &mb64_terrain_pole, mb64_rot_selection);
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


void generate_poles(void) {
    gPoleArray = main_pool_alloc(main_pool_available() - 0x10, MEMORY_POOL_LEFT);
    gNumPoles = 0;

    // Iterate over all poles
    u32 startIndex = mb64_tile_data_indices[POLE_TILETYPE_INDEX];
    u32 endIndex = mb64_tile_data_indices[POLE_TILETYPE_INDEX+1];

    for (u32 i = startIndex; i < endIndex; i++) {
        s8 pos[3];
        vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);
        
        // If there is a pole below, skip
        pos[1] -= 1;
        if (pos[1] >= 0 && (get_grid_tile(pos)->type == TILE_TYPE_POLE)) {
            continue;
        }

        s32 poleLength = 1;
        // Scan upwards until no more poles or top of grid reached
        pos[1] += 2;
        while (pos[1] < 64 && (get_grid_tile(pos)->type == TILE_TYPE_POLE)) {
            poleLength++;
            pos[1]++;
        }

        gPoleArray[gNumPoles].pos[0] = GRID_TO_POS(mb64_tile_data[i].x);
        gPoleArray[gNumPoles].pos[1] = GRID_TO_POS(mb64_tile_data[i].y) - TILE_SIZE/2;
        gPoleArray[gNumPoles].pos[2] = GRID_TO_POS(mb64_tile_data[i].z);
        gPoleArray[gNumPoles].height = poleLength * TILE_SIZE;
        gPoleArray[gNumPoles].poleType = 0;
        gNumPoles++;
    }

    // Trees
    for (u32 i = 0; i < mb64_object_count; i++) {
        if (mb64_object_data[i].type == OBJECT_TYPE_TREE) {
            gPoleArray[gNumPoles].pos[0] = GRID_TO_POS(mb64_object_data[i].x);
            gPoleArray[gNumPoles].pos[1] = GRID_TO_POS(mb64_object_data[i].y) - TILE_SIZE/2;
            gPoleArray[gNumPoles].pos[2] = GRID_TO_POS(mb64_object_data[i].z);
            gPoleArray[gNumPoles].height = 500;
            gPoleArray[gNumPoles].poleType = (mb64_object_data[i].bparam == 2 ? 2 : 1);
            gNumPoles++;
        } else if (mb64_object_data[i].type == OBJECT_TYPE_KOOPA_THE_QUICK) {
            s32 traj_id = mb64_object_data[i].bparam;
            // Scan for end of trajectory and place flag
            for (u32 j = 0; j < MB64_TRAJECTORY_LENGTH; j++) {
                if (mb64_trajectory_list[traj_id][j][0] == -1) {
                    gPoleArray[gNumPoles].pos[0] = mb64_trajectory_list[traj_id][j-1][1];
                    gPoleArray[gNumPoles].pos[1] = mb64_trajectory_list[traj_id][j-1][2] - TILE_SIZE/2;
                    gPoleArray[gNumPoles].pos[2] = mb64_trajectory_list[traj_id][j-1][3];
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

void generate_boundary_collision(struct mb64_boundary_quad *quadList, u32 count, s16 yBottom, s16 yTop, s16 size, u32 reverse) {
    TerrainData newVtxs[4][3];
    s16 yHeight = yTop - yBottom;
    for (u32 i = 0; i < count; i++) {
        for (u32 j = 0; j < 4; j++) {
            newVtxs[j][0] = quadList[i].vtx[j][0]*size*4;
            newVtxs[j][1] = (quadList[i].vtx[j][1]*yHeight + yBottom)*TILE_SIZE;
            newVtxs[j][2] = quadList[i].vtx[j][2]*size*4;
        }
        if (reverse) {
            mb64_create_surface(newVtxs[0], newVtxs[2], newVtxs[1]);
            mb64_create_surface(newVtxs[1], newVtxs[2], newVtxs[3]);
        } else {
            mb64_create_surface(newVtxs[0], newVtxs[1], newVtxs[2]);
            mb64_create_surface(newVtxs[1], newVtxs[3], newVtxs[2]);
        }
    }
}

void generate_terrain_collision(void) {
    gCurrStaticSurfacePool = main_pool_alloc(main_pool_available() - 0x10, MEMORY_POOL_LEFT);
    gCurrStaticSurfacePoolEnd = gCurrStaticSurfacePool;
    gSurfaceNodesAllocated = gNumStaticSurfaceNodes;
    gSurfacesAllocated = gNumStaticSurfaces;
    mb64_building_collision = TRUE;
    mb64_curr_poly_vert_count = 4;

    u32 deathsize = (mb64_curr_boundary & MB64_BOUNDARY_OUTER_FLOOR) ? mb64_grid_size : (mb64_grid_size + 16);
    mb64_curr_coltype = SURFACE_DEATH_PLANE;
    generate_boundary_collision(floor_boundary, ARRAY_COUNT(floor_boundary), -40, -40, deathsize, FALSE);

    if (mb64_curr_boundary & MB64_BOUNDARY_INNER_FLOOR) {
        mb64_curr_coltype = TOPMAT(mb64_lopt_boundary_mat).col;
        generate_boundary_collision(floor_boundary, ARRAY_COUNT(floor_boundary), -32, -32, mb64_grid_size, FALSE);
    }
    mb64_curr_coltype = MATERIAL(mb64_lopt_boundary_mat).col;
    if (MATERIAL(mb64_lopt_boundary_mat).type == MAT_TRANSPARENT) {
        mb64_curr_coltype = SURFACE_DEFAULT;
    }
    if (mb64_curr_boundary & MB64_BOUNDARY_INNER_WALLS) {
        s32 bottomY = (mb64_curr_boundary & MB64_BOUNDARY_INNER_FLOOR) ? -32 : -40;
        s32 topY = mb64_lopt_boundary_height-32;
        generate_boundary_collision(wall_boundary, ARRAY_COUNT(wall_boundary), bottomY, topY, mb64_grid_size, FALSE);
    } else if (mb64_curr_boundary & MB64_BOUNDARY_OUTER_WALLS) {
        generate_boundary_collision(wall_boundary, ARRAY_COUNT(wall_boundary), -42, -32, mb64_grid_size, TRUE);
    }
    if (mb64_curr_boundary & MB64_BOUNDARY_CEILING) {
        generate_boundary_collision(floor_boundary, ARRAY_COUNT(floor_boundary), mb64_lopt_boundary_height-32, mb64_lopt_boundary_height-32, mb64_grid_size, TRUE);
    }

    process_tiles(0);
    mb64_growth_render_type = 0;
    mb64_curr_poly_vert_count = 4;

    mb64_curr_coltype = SURFACE_NO_CAM_COLLISION;
    for (u32 i = mb64_tile_data_indices[FENCE_TILETYPE_INDEX]; i < mb64_tile_data_indices[FENCE_TILETYPE_INDEX+1]; i++) {
        s8 pos[3];
        vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);
        process_tile(pos, &mb64_terrain_fence_col, mb64_tile_data[i].rot);
    }
    mb64_curr_poly_vert_count = 4;
    mb64_curr_coltype = SURFACE_VANISH_CAP_WALLS;
    for (u32 i = mb64_tile_data_indices[BARS_TILETYPE_INDEX]; i < mb64_tile_data_indices[BARS_TILETYPE_INDEX+1]; i++) {
        s8 pos[3];
        u8 connections[5];
        vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);
        check_bar_connections(pos, connections);
        render_bars_side(pos, connections);
        render_bars_top(pos, connections);
    }

    mb64_building_collision = FALSE;
    u32 surfacePoolData = (uintptr_t)gCurrStaticSurfacePoolEnd - (uintptr_t)gCurrStaticSurfacePool;
    gTotalStaticSurfaceData += surfacePoolData;
    main_pool_realloc(gCurrStaticSurfacePool, surfacePoolData);

    gNumStaticSurfaceNodes = gSurfaceNodesAllocated;
    gNumStaticSurfaces = gSurfacesAllocated;

    generate_poles();
}


s32 mb64_get_water_level(s32 x, s32 y, s32 z) {
    //(mb64_lopt_waterlevel - 32) * TILE_SIZE - (TILE_SIZE / 8)
    s32 waterPlaneHeight = (mb64_lopt_waterlevel == 0 ? FLOOR_LOWER_LIMIT : mb64_play_s16_water_level);
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

struct Object *spawn_preview_object(s8 pos[3], s32 rot, s32 param, struct mb64_object_info *info, const BehaviorScript *script) {
    struct Object *preview_object = spawn_object(gMarioObject, info->model_id, script);
    preview_object->oPosX = GRID_TO_POS(pos[0]);
    preview_object->oPosY = GRID_TO_POS(pos[1]) - TILE_SIZE/2 + info->y_offset;
    preview_object->oPosZ = GRID_TO_POS(pos[2]);
    preview_object->oFaceAngleYaw = rot*0x4000;
    preview_object->oBehParams2ndByte = param;
    preview_object->oBehParams = (param << 16);
    preview_object->oPreviewObjDisplayFunc = info->disp_func;
    preview_object->oOpacity = 255;
    obj_scale(preview_object, info->scale);
    if (info->flags & OBJ_TYPE_IS_BILLBOARDED) {
        preview_object->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
    }
    if (info->anim) {
        preview_object->oAnimations = (struct Animation **)info->anim;
        super_cum_working(preview_object,0);
        preview_object->header.gfx.animInfo.animAccel = 0.0f;
    }
    if ((info->flags & OBJ_TYPE_TRAJECTORY)
        && (script != bhvCurrPreviewObject)
        && (info->behavior != bhvLoopingPlatform)) {
        rotate_obj_toward_trajectory_angle(preview_object,param);
    }
    return preview_object;
}

void generate_object_preview(void) {
    s32 totalCoins = 0;
    s32 doubleCoins = FALSE;
    mb64_object_limit_count = 0;
    struct Object *preview_object = cur_obj_nearest_object_with_behavior(bhvPreviewObject);
    while (preview_object) {
        unload_object(preview_object);
        preview_object = cur_obj_nearest_object_with_behavior(bhvPreviewObject);
    }

    for(u32 i = 0; i < mb64_object_count; i++){
        if (gFreeObjectList.next == NULL) break;
        struct mb64_object_info *info = &mb64_object_type_list[mb64_object_data[i].type];
        s32 param = mb64_object_data[i].bparam;

        s8 pos[3];
        vec3_set(pos, mb64_object_data[i].x, mb64_object_data[i].y, mb64_object_data[i].z);

        spawn_preview_object(pos, mb64_object_data[i].rot, param, info, bhvPreviewObject);
        totalCoins += info->numCoins;
        if (mb64_object_data[i].type == OBJECT_TYPE_EXCL_BOX) {
            totalCoins += mb64_exclamation_box_contents[param].numCoins;
        }
        if (mb64_object_data[i].type == OBJECT_TYPE_BADGE && param == 8) { // Greed badge
            doubleCoins = TRUE;
        }

        s32 extraObjs = get_extra_objects(mb64_object_data[i].type, param);
        if (mb64_object_data[i].type == OBJECT_TYPE_COIN_FORMATION) {
            totalCoins += extraObjs;
        }

        if ((mb64_object_data[i].imbue != IMBUE_NONE)&&(!mb64_prepare_level_screenshot)) {
            u16 imbue_marker_model = MODEL_MAKER_IMBUE;
            if (mb64_object_data[i].imbue == IMBUE_STAR) {
                imbue_marker_model = MODEL_MAKER_IMBUE_STAR;
            }
            struct Object * imbue_marker = spawn_object(o,imbue_marker_model,bhvPreviewObject);
            imbue_marker->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
            imbue_marker->oPosX = GRID_TO_POS(pos[0]);
            imbue_marker->oPosY = GRID_TO_POS(pos[1]);
            imbue_marker->oPosZ = GRID_TO_POS(pos[2]);
            mb64_object_limit_count ++;
            totalCoins += imbue_coin_amounts[mb64_object_data[i].imbue];
        }

        mb64_object_limit_count += extraObjs + 1;
    }
    if (doubleCoins) totalCoins *= 2;

    u32 length = MIN(totalCoins / 20, 50);
    if (mb64_lopt_game == MB64_GAME_BTCM) {
        mb64_settings_misc_buttons[MISC_COINSTAR_INDEX].size = length + 1;
    } else {
        mb64_settings_misc_buttons_vanilla[MISCV_COINSTAR_INDEX].size = length + 1;
    }

    if (mb64_lopt_coinstar > length) {
        mb64_lopt_coinstar = length;
    }

    generate_trajectory_gfx();
}

void generate_objects_to_level(void) {
    struct Object *obj;
    u32 i;
    mb64_play_stars_max = 0;
    for(i=0;i<mb64_object_count;i++){
        struct mb64_object_info *info = &mb64_object_type_list[mb64_object_data[i].type];
        s32 param = mb64_object_data[i].bparam;

        obj = spawn_object(gMarioObject, info->model_id, info->behavior);
        obj->oPosX = GRID_TO_POS(mb64_object_data[i].x);
        obj->oPosY = GRID_TO_POS(mb64_object_data[i].y) - TILE_SIZE/2 + info->y_offset;
        obj->oPosZ = GRID_TO_POS(mb64_object_data[i].z);
        obj->oFaceAngleYaw = mb64_object_data[i].rot*0x4000;
        obj->oMoveAngleYaw = mb64_object_data[i].rot*0x4000;
        obj->oBehParams2ndByte = param;
        obj->oBehParams = (param << 16);
        obj->oImbue = mb64_object_data[i].imbue;

        //assign star ids
        if ((info->flags & OBJ_TYPE_HAS_STAR)||(mb64_object_data[i].imbue == IMBUE_STAR)) {
            if (mb64_play_stars_max < 63) {
                obj->oBehParams = ((mb64_play_stars_max << 24)|(o->oBehParams2ndByte << 16));
                mb64_play_stars_max++;
            }
        }
    }
    if (mb64_lopt_coinstar > 0) mb64_play_stars_max++; // 100 coin star
}

// shift all indices past the given one by 1
// return index to insert a new block at
u32 shift_tile_data_indices(u32 tiletypeIndex) {
    u32 tiledataIndex = mb64_tile_data_indices[tiletypeIndex + 1];
    // Shift all indices forward one
    for (u32 i = tiletypeIndex + 1; i < ARRAY_COUNT(mb64_tile_data_indices); i++) {
        mb64_tile_data_indices[i]++;
    }

    // Shift all data forward one
    for (u32 i = mb64_tile_count; i > tiledataIndex; i--) {
        mb64_tile_data[i] = mb64_tile_data[i - 1];
    }
    return tiledataIndex;
}

u32 is_cull_marker_useless(s8 pos[3]) {
    s8 adjacentPos[3];

    for (u8 dir = 0; dir < 6; dir++) {
        vec3_sum(adjacentPos, pos, cullOffsetLUT[dir]);
        u8 tileType = get_grid_tile(adjacentPos)->type;
        if ((tileType != TILE_TYPE_EMPTY) && (tileType != TILE_TYPE_CULL)) {
            return FALSE;
        }
    }

    return TRUE;
}


void place_tile(s8 pos[3]) {
    u8 waterlogged = FALSE;
    // Placing tile upon water automatically waterlogs new tile
    // But delete the old tile first
    if (get_grid_tile(pos)->type == TILE_TYPE_WATER) {
        waterlogged = TRUE;
        for (u32 i = 0; i < mb64_tile_count; i++) {
        //search for tile to delete
            if ((mb64_tile_data[i].x == pos[0])&&(mb64_tile_data[i].y == pos[1])&&(mb64_tile_data[i].z == pos[2])) {
                mb64_tile_count--;
                for (u32 j = WATER_TILETYPE_INDEX + 1; j < ARRAY_COUNT(mb64_tile_data_indices); j++) {
                    mb64_tile_data_indices[j]--;
                }
                for (u32 j = i; j < mb64_tile_count; j++) {
                    mb64_tile_data[j] = mb64_tile_data[j+1];
                }
                break;
            }
        }
    }

    if (mb64_id_selection == TILE_TYPE_BLOCK) {
        if (!fullblock_can_be_waterlogged(mb64_mat_selection)) {
            waterlogged = FALSE;
        }
    }
    // If placing a cull marker, check that its actually next to a tile
    if (mb64_id_selection == TILE_TYPE_CULL && is_cull_marker_useless(pos)) {
        remove_occupy_data(pos);
        return;
    }

    if (mb64_terrain_info_list[mb64_id_selection].terrain != NULL) {
        TerrainData coltype = TOPMAT(mb64_mat_selection).col;
        if (SURFACE_IS_BURNING(coltype)) {
            play_place_sound(SOUND_GENERAL_LOUD_BUBBLE | SOUND_VIBRATO);
        } else {
            play_place_sound(SOUND_ACTION_TERRAIN_STEP + get_terrain_sound_addend(coltype));
        }
    } else {
        switch (mb64_id_selection ) {
            case TILE_TYPE_FENCE:
                if (mb64_lopt_theme == MB64_THEME_RHR) {
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

    place_terrain_data(pos, mb64_id_selection, mb64_rot_selection, mb64_mat_selection);
    get_grid_tile(pos)->waterlogged = waterlogged;
    u32 index = get_tiletype_index(mb64_id_selection, mb64_mat_selection);
    u32 newtileIndex = shift_tile_data_indices(index);

    mb64_tile_data[newtileIndex].x = pos[0];
    mb64_tile_data[newtileIndex].y = pos[1];
    mb64_tile_data[newtileIndex].z = pos[2];
    mb64_tile_data[newtileIndex].type = mb64_id_selection;
    mb64_tile_data[newtileIndex].mat = mb64_mat_selection;
    mb64_tile_data[newtileIndex].rot = mb64_rot_selection;
    mb64_tile_data[newtileIndex].waterlogged = waterlogged;
    mb64_tile_count++;
}


void place_water(s8 pos[3]) {
    struct mb64_grid_obj *tile = get_grid_tile(pos);
    if (tile->waterlogged) return;

    if (tile->type != TILE_TYPE_EMPTY) {
        // cant waterlog a full block
        if ((tile->type == TILE_TYPE_BLOCK) && !fullblock_can_be_waterlogged(tile->mat)) {
            return;
        }
        play_place_sound(SOUND_ACTION_TERRAIN_STEP + (SOUND_TERRAIN_WATER << 16));
        tile->waterlogged = TRUE;
        u32 tileIndex = get_tiletype_index(tile->type, tile->mat);
        for (u32 i = mb64_tile_data_indices[tileIndex]; i < mb64_tile_data_indices[tileIndex + 1]; i++) {
            if (mb64_tile_data[i].x == pos[0] && mb64_tile_data[i].y == pos[1] && mb64_tile_data[i].z == pos[2]) {
                mb64_tile_data[i].waterlogged = TRUE;
                break;
            }
            // should not be possible to reach here
        }
    } else {
        // empty currently, so add water
        place_terrain_data(pos, TILE_TYPE_WATER, 0, 0);
        tile->waterlogged = TRUE;
        u32 newtileIndex = shift_tile_data_indices(WATER_TILETYPE_INDEX);

        mb64_tile_data[newtileIndex].x = pos[0];
        mb64_tile_data[newtileIndex].y = pos[1];
        mb64_tile_data[newtileIndex].z = pos[2];
        mb64_tile_data[newtileIndex].type = TILE_TYPE_WATER; // should be unused
        mb64_tile_data[newtileIndex].mat = 0; // should be unused
        mb64_tile_data[newtileIndex].rot = 0;
        mb64_tile_data[newtileIndex].waterlogged = TRUE;
        mb64_tile_count++;
        play_place_sound(SOUND_ACTION_TERRAIN_STEP + (SOUND_TERRAIN_WATER << 16));
    }
}


void remove_trajectory(u32 index) {
    // Scan all objects
    // If their trajectory index is past the one being deleted, lower it by 1
    for (u32 i = 0; i < mb64_object_count; i++) {
        if (mb64_object_type_list[mb64_object_data[i].type].flags & OBJ_TYPE_TRAJECTORY) {
            if (mb64_object_data[i].bparam > index) {
                mb64_object_data[i].bparam--;
            }
        }
    }
    // Move trajectories back by one
    for (s32 i = index; i < mb64_trajectories_used - 1; i++) {
        bcopy(mb64_trajectory_list[i + 1], mb64_trajectory_list[i], sizeof(mb64_trajectory_list[0]));
    }
    // Zero out the last one
    bzero(mb64_trajectory_list[mb64_trajectories_used - 1], sizeof(mb64_trajectory_list[0]));
    mb64_trajectories_used--;
}


void delete_object(s8 pos[3], s32 index) {
    remove_occupy_data(pos);

    if (mb64_object_type_list[mb64_object_data[index].type].flags & OBJ_TYPE_TRAJECTORY) { 
        remove_trajectory(mb64_object_data[index].bparam);
    }

    mb64_object_count--;
    for (u32 i = index; i < mb64_object_count; i++) {
        mb64_object_data[i] = mb64_object_data[i+1];
    }
    generate_object_preview();
}

extern s8 gDialogBoxType;
void place_object(s8 pos[3]) {
    // If spawn, delete old spawn
    if (mb64_id_selection == OBJECT_TYPE_MARIO_SPAWN) {
        for (s32 i = 0; i < mb64_object_count; i++) {
            if (mb64_object_data[i].type == OBJECT_TYPE_MARIO_SPAWN) {
                s8 pos[3];
                vec3_set(pos, mb64_object_data[i].x, mb64_object_data[i].y, mb64_object_data[i].z);
                delete_object(pos, i);
                break;
            }
        }
    }

    mb64_object_data[mb64_object_count].x = pos[0];
    mb64_object_data[mb64_object_count].y = pos[1];
    mb64_object_data[mb64_object_count].z = pos[2];
    mb64_object_data[mb64_object_count].type = mb64_id_selection;
    mb64_object_data[mb64_object_count].rot = mb64_rot_selection;
    mb64_object_data[mb64_object_count].imbue = IMBUE_NONE;

    if (mb64_object_type_list[mb64_id_selection].flags & OBJ_TYPE_TRAJECTORY) {
        mb64_trajectory_to_edit = mb64_trajectories_used;
        mb64_object_data[mb64_object_count].bparam = mb64_trajectories_used;
        mb64_trajectories_used++;

        mb64_menu_state = MB64_MAKE_TRAJECTORY;
        mb64_trajectory_list[mb64_trajectory_to_edit][0][0] = -1;
        mb64_trajectory_edit_index = 0;
    } else if (mb64_object_type_list[mb64_id_selection].flags & OBJ_TYPE_HAS_DIALOG) {
        gDialogBoxType = 0;
        mb64_menu_state = MB64_MAKE_SELECT_DIALOG;
        mb64_object_data[mb64_object_count].bparam = 0;
        mb64_dialog_edit_ptr = &mb64_object_data[mb64_object_count];
    } else if (!mb64_ui_buttons[mb64_toolbar[mb64_toolbar_index]].multiObj) {
        // BehParam2 Object
        mb64_object_data[mb64_object_count].bparam = mb64_param_selection;
    } else {
        // Multi Object
        mb64_object_data[mb64_object_count].bparam = 0;
    }

    mb64_object_count++;

    play_place_sound(mb64_object_type_list[mb64_id_selection].soundBits);
}

u8 joystick_direction(void) {
    if (mb64_joystick_timer > 0) {
        mb64_joystick_timer--;
    }

    if ((gPlayer1Controller->rawStickX < 10)&&(gPlayer1Controller->rawStickX > -10)&&(gPlayer1Controller->rawStickY < 10)&&(gPlayer1Controller->rawStickY > -10)) {
        mb64_joystick_timer = 0;
    }

    if (mb64_joystick_timer == 0) {
        if (gPlayer1Controller->rawStickX > 60) {
            mb64_joystick_timer = 5;
            return 3;
        }
        if (gPlayer1Controller->rawStickX < -60) {
            mb64_joystick_timer = 5;
            return 1;
        }
        if (gPlayer1Controller->rawStickY > 60) {
            mb64_joystick_timer = 5;
            return 4;
        }
        if (gPlayer1Controller->rawStickY < -60) {
            mb64_joystick_timer = 5;
            return 2;
        }
    }

    return 0;
}

void imbue_action(void) {
    if (mb64_place_mode == MB64_PM_OBJ) {
        for (u32 i=0;i<mb64_object_count;i++) {
            if ((mb64_object_type_list[mb64_object_data[i].type].flags & OBJ_TYPE_IMBUABLE)&&(mb64_object_data[i].x == mb64_cursor_pos[0])&&(mb64_object_data[i].y == mb64_cursor_pos[1])&&(mb64_object_data[i].z == mb64_cursor_pos[2])&&(mb64_object_data[i].imbue == IMBUE_NONE)) {
                u8 imbue_success = FALSE;

                switch(mb64_id_selection) {
                    case OBJECT_TYPE_STAR:
                        mb64_object_data[i].imbue = IMBUE_STAR;
                        imbue_success = TRUE;
                        break;
                    case OBJECT_TYPE_BLUE_COIN:
                        if (mb64_object_type_list[mb64_object_data[i].type].flags & OBJ_TYPE_IMBUABLE_COINS) {
                            mb64_object_data[i].imbue = IMBUE_BLUE_COIN;
                            imbue_success = TRUE;
                        }
                        break;
                    case OBJECT_TYPE_COIN:
                        if (mb64_object_type_list[mb64_object_data[i].type].flags & OBJ_TYPE_IMBUABLE_COINS) {
                            mb64_object_data[i].imbue = IMBUE_THREE_COINS;
                            imbue_success = TRUE;
                        }
                        break;
                    case OBJECT_TYPE_RED_COIN:
                        mb64_object_data[i].imbue = IMBUE_RED_COIN;
                        imbue_success = TRUE;
                        break;
                    case OBJECT_TYPE_BUTTON:
                        mb64_object_data[i].imbue = IMBUE_RED_SWITCH;
                        if (mb64_param_selection == 1) {
                            mb64_object_data[i].imbue = IMBUE_BLUE_SWITCH;
                        }
                        imbue_success = TRUE;
                        break;
                }

                if (imbue_success) {
                    play_place_sound(SOUND_GENERAL_DOOR_INSERT_KEY | SOUND_VIBRATO);
                    generate_object_preview();
                }
                break;
            }
        }
    }
}

void place_thing_action(void) {
     if (mb64_place_mode == MB64_PM_WATER) {
        if (tile_sanity_check()) {
            place_water(mb64_cursor_pos);
            generate_terrain_gfx();
        }
        return;
    }
    //tiles and objects share occupancy data
    if (!get_occupy_data(mb64_cursor_pos)) {
        if (mb64_place_mode == MB64_PM_TILE) {
            //MB64_PM_TILE
            if (tile_sanity_check()) {
                place_occupy_data(mb64_cursor_pos);
                place_tile(mb64_cursor_pos);
                generate_terrain_gfx();
            }
        } else if (mb64_place_mode == MB64_PM_OBJ){
            //MB64_PM_OBJECT
            if (object_sanity_check()) {
                place_occupy_data(mb64_cursor_pos);
                place_object(mb64_cursor_pos);
                generate_object_preview();
            }
        }
    } else {
        imbue_action();
    }
}


void delete_useless_cull_markers() {
    for (u32 i = mb64_tile_data_indices[CULL_TILETYPE_INDEX]; i < mb64_tile_data_indices[CULL_TILETYPE_INDEX + 1]; i++) {
        s8 pos[3];
        vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);

        if (!is_cull_marker_useless(pos)) {
            continue;
        }

        // Useless, delete
        remove_occupy_data(pos);
        remove_terrain_data(pos);
        mb64_tile_count--;

        for (u32 j = CULL_TILETYPE_INDEX + 1; j < ARRAY_COUNT(mb64_tile_data_indices); j++) {
            mb64_tile_data_indices[j]--;
        }
        for (u32 j = i; j < mb64_tile_count; j++) {
            mb64_tile_data[j] = mb64_tile_data[j+1];
        }

        i--;
    }
}


//function name is delete tile, it deletes objects too
void delete_tile_action(s8 pos[3]) {
    s16 index = -1;

    for (u32 i = 0; i < mb64_tile_count; i++) {
        //search for tile to delete
        if ((mb64_tile_data[i].x == pos[0])&&(mb64_tile_data[i].y == pos[1])&&(mb64_tile_data[i].z == pos[2])) {
            index = i;
            remove_occupy_data(pos);
            remove_terrain_data(pos);
            play_place_sound(SOUND_GENERAL_DOOR_INSERT_KEY | SOUND_VIBRATO);
            mb64_tile_count--;
        }
    }

    if (index != -1) {
        u32 tiletypeIndex = get_tiletype_index(mb64_tile_data[index].type, mb64_tile_data[index].mat);

        for (u32 i = tiletypeIndex + 1; i < ARRAY_COUNT(mb64_tile_data_indices); i++) {
            mb64_tile_data_indices[i]--;
        }
        for (u32 i = index; i < mb64_tile_count; i++) {
            mb64_tile_data[i] = mb64_tile_data[i+1];
        }
        delete_useless_cull_markers();
        generate_terrain_gfx();
    }

    for (u32 i=0;i<mb64_object_count;i++) {
        if ((mb64_object_data[i].x == pos[0])&&(mb64_object_data[i].y == pos[1])&&(mb64_object_data[i].z == pos[2])) {
            if (mb64_object_data[i].type == OBJECT_TYPE_MARIO_SPAWN) {
                mb64_show_error_message("Cannot delete spawn point!");
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
            u16_array[(y*64)+x] = mb64_save.piktcher[y][x];
        } 
    }
}

//if (gSramProbe != 0) {
#include "src/game/mb64_painting_frames.inc.c"

TCHAR mb64_file_name[MAX_FILE_NAME_SIZE];
FIL mb64_file;
FILINFO mb64_file_info;

char file_header_string[] = "MB64-v1.0";

extern u16 sRenderedFramebuffer;
#define INSTANT_INPUT_BLACKLIST (EMU_CONSOLE | EMU_WIIVC | EMU_ARES | EMU_SIMPLE64 | EMU_CEN64)
void save_level(void) {
    //bzero(&mb64_save, sizeof(mb64_save)); // should be safe to not need this right?
    if (mb64_vtx_total >= MB64_VTX_SIZE) {
        mb64_show_error_message("Save Failed - Vertex limit exceeded.");
        return;
    }

    //file header
    strncpy(mb64_save.file_header, file_header_string, 10);

    //author
    if ((mb64_has_username) && (mb64_save.author[0] == '\0')) {
        strncpy(mb64_save.author, mb64_username, MAX_USERNAME_SIZE);
    }

    mb64_save.tile_count = mb64_tile_count;
    mb64_save.object_count = mb64_object_count;

    mb64_save.costume = mb64_lopt_costume;
    mb64_save.seq[0] = mb64_lopt_seq[0];
    mb64_save.seq[1] = mb64_lopt_seq[1];
    mb64_save.seq[2] = mb64_lopt_seq[2];
    mb64_save.envfx = mb64_lopt_envfx;
    mb64_save.theme = mb64_lopt_theme;
    mb64_save.bg = mb64_lopt_bg;
    mb64_save.boundary_mat = mb64_lopt_boundary_mat;
    mb64_save.boundary = mb64_lopt_boundary;
    mb64_save.boundary_height = mb64_lopt_boundary_height;
    mb64_save.coinstar = mb64_lopt_coinstar;
    mb64_save.size = mb64_lopt_size;
    mb64_save.waterlevel = mb64_lopt_waterlevel;
    mb64_save.secret = mb64_lopt_secret;
    mb64_save.game = mb64_lopt_game;

    for (s32 i = 0; i < MB64_MAX_TRAJECTORIES; i++) {
        for (s32 j = 0; j < MB64_TRAJECTORY_LENGTH; j++) {
            mb64_save.trajectories[i][j].t = mb64_trajectory_list[i][j][0];
            mb64_save.trajectories[i][j].x = POS_TO_GRID(mb64_trajectory_list[i][j][1]);
            mb64_save.trajectories[i][j].y = POS_TO_GRID(mb64_trajectory_list[i][j][2]);
            mb64_save.trajectories[i][j].z = POS_TO_GRID(mb64_trajectory_list[i][j][3]);
        }
    }

    // If in screenshot mode
    if (mb64_prepare_level_screenshot) {
        u8 screenshot_failure = TRUE;

        for (s32 i=0;i<4096;i++) {
            //take a "screenshot" of the level & burn in a painting frame
            if (mb64_painting_frame_1_rgba16[(i*2)+1]==0x00) {
                //painting
                if (gEmulator & INSTANT_INPUT_BLACKLIST) {
                    mb64_save.piktcher[i/64][i%64] = (gFramebuffers[(sRenderedFramebuffer+2)%3][ ((s32)((i/64)*3.75f))*320 + (s32)((i%64)*3.75f+40) ] | 1);
                } else {
                    mb64_save.piktcher[i/64][i%64] = (gFramebuffers[0][ ((s32)((i/64)*3.75f))*320 + (s32)((i%64)*3.75f+40) ] | 1);
                }

                if (mb64_save.piktcher[i/64][i%64] > 1) { //assumes all fb rgba16 values is initialized to 1 or 0
                    screenshot_failure = FALSE;
                }
            } else {
                //painting frame
                mb64_save.piktcher[i/64][i%64] = ((mb64_painting_frame_1_rgba16[(i*2)]<<8) | mb64_painting_frame_1_rgba16[(i*2)+1]);
            }
        }

        if (screenshot_failure) {
            //framebuffer emulation not enabled, use ?
            bcopy(&mystery_painting_rgba16,&mb64_save.piktcher,sizeof(mb64_save.piktcher));
        }

        update_painting();
    }

    if (mb64_save.piktcher[0][0] == 0) { //0 is a transparent pixel in rgba16
        //use mystery painting if no screenshot has been taken yet
        bcopy(&mystery_painting_rgba16,&mb64_save.piktcher,sizeof(mb64_save.piktcher));
    }
    bcopy(&mb64_curr_custom_theme,&mb64_save.custom_theme,sizeof(struct mb64_custom_theme));
    bcopy(&mb64_toolbar, &mb64_save.toolbar, sizeof(mb64_save.toolbar));
    bcopy(&mb64_toolbar_params, &mb64_save.toolbar_params, sizeof(mb64_save.toolbar_params));

    TCHAR path[256];
    create_level_file_path(path, mb64_file_name, NULL);
    UINT bytes_written;
    f_open(&mb64_file,path, FA_READ | FA_WRITE | FA_CREATE_ALWAYS);
    //write header
    f_write(&mb64_file,&mb64_save,sizeof(mb64_save),&bytes_written);
    //write tiles
    f_write(&mb64_file,&mb64_tile_data,(sizeof(mb64_tile_data[0])*mb64_tile_count),&bytes_written);
    //write objects
    f_write(&mb64_file,&mb64_object_data,(sizeof(mb64_object_data[0])*mb64_object_count),&bytes_written);

    f_close(&mb64_file);
}

#include "mb64_compatibility.inc.c"

void load_level(void) {
    s32 i;
    s32 j;
    u8 fresh = FALSE;

    bzero(&mb64_save, sizeof(mb64_save));
    bzero(&mb64_grid_data, sizeof(mb64_grid_data));

    TCHAR path[256];
    create_level_file_path(path, mb64_file_name, NULL);
    FRESULT code = f_stat(path,&mb64_file_info);
    if (code == FR_OK) {
        UINT bytes_read;
        //file exists, load it
        f_open(&mb64_file,path, FA_READ | FA_WRITE);
        //read header
        f_read(&mb64_file,&mb64_save,sizeof(mb64_save),&bytes_read);
        //read tiles
        f_read(&mb64_file,&mb64_tile_data,sizeof(mb64_tile_data[0])*mb64_save.tile_count,&bytes_read);
        //read objects
        f_read(&mb64_file,&mb64_object_data,sizeof(mb64_object_data[0])*mb64_save.object_count,&bytes_read);

        f_close(&mb64_file);
    } else {
        //Load into a fresh level
        fresh = TRUE;
        strncpy(mb64_file_info.fname,mb64_file_name,MAX_FILE_NAME_SIZE);

        //Set version
        mb64_save.version = MB64_VERSION;

        //Place spawn location
        mb64_save.object_count = 1;
        mb64_object_data[0].x = 32;
        mb64_object_data[0].z = 32;
        mb64_object_data[0].y = mb64_templates[mb64_lopt_template].spawnHeight;
        mb64_object_data[0].type = OBJECT_TYPE_MARIO_SPAWN;

        mb64_save.game = mb64_lopt_game;
        mb64_save.size = mb64_lopt_size;

        mb64_save.seq[0] = mb64_templates[mb64_lopt_template].music[mb64_lopt_game];
        mb64_save.seq[1] = 1;
        mb64_save.seq[2] = 10;
        if (mb64_lopt_game == MB64_GAME_BTCM) {
            mb64_save.seq[2] = 22;
        }
        mb64_save.envfx = mb64_templates[mb64_lopt_template].envfx;
        mb64_save.theme = mb64_templates[mb64_lopt_template].theme;
        mb64_save.bg = mb64_templates[mb64_lopt_template].bg;
        mb64_save.boundary_mat = mb64_templates[mb64_lopt_template].plane;
        mb64_save.boundary = 1;
        mb64_save.boundary_height = 5;

        bcopy(&mb64_toolbar_defaults,&mb64_save.toolbar,sizeof(mb64_save.toolbar));
        bzero(&mb64_save.toolbar_params,sizeof(mb64_save.toolbar_params));

        if (mb64_templates[mb64_lopt_template].platform) {
            u8 i = 0;
            for (s32 x = -1; x <= 1; x++) {
                for (s32 z = -1; z <= 1; z++) {
                    mb64_tile_data[i].x = 32+x;
                    mb64_tile_data[i].y = 0;
                    mb64_tile_data[i].z = 32+z;
                    mb64_tile_data[i].type = TILE_TYPE_BLOCK;
                    mb64_tile_data[i].mat = 0;
                    i++;
                }
            }
            mb64_save.tile_count = i;
        }

        bcopy(&mb64_default_custom,&mb64_save.custom_theme,sizeof(struct mb64_custom_theme));
    }

    if (mb64_save.version < MB64_VERSION) {
        append_puppyprint_log("Performing upgrade from version %d", mb64_save.version);
        mb64_perform_file_upgrade(&mb64_save, &mb64_tile_data, &mb64_object_data);
    }

    mb64_save.author[MAX_USERNAME_SIZE - 1] = '\0'; // memory leak prevention
    mb64_tile_count = mb64_save.tile_count;
    mb64_object_count = mb64_save.object_count;

    mb64_lopt_costume = mb64_save.costume;

    mb64_lopt_seq[0] = mb64_save.seq[0];
    mb64_lopt_seq[1] = mb64_save.seq[1];
    mb64_lopt_seq[2] = mb64_save.seq[2];
    mb64_lopt_envfx = mb64_save.envfx;
    mb64_lopt_theme = mb64_save.theme;
    mb64_lopt_bg = mb64_save.bg;

    mb64_lopt_boundary_mat = mb64_save.boundary_mat;
    mb64_lopt_boundary = mb64_save.boundary;
    mb64_lopt_boundary_height = mb64_save.boundary_height;
    mb64_lopt_coinstar = mb64_save.coinstar;
    mb64_lopt_size = mb64_save.size;
    mb64_lopt_waterlevel = mb64_save.waterlevel;
    mb64_lopt_secret = mb64_save.secret;

    mb64_newsize = mb64_lopt_size;
    switch (mb64_lopt_size) {
        case 0:
            mb64_grid_min = 16;
            mb64_grid_size = 32;
            break;
        case 1:
            mb64_grid_min = 8;
            mb64_grid_size = 48;
            break;
        case 2:
            mb64_grid_min = 0;
            mb64_grid_size = 64;
            break;
    }

    mb64_lopt_game = mb64_save.game;

    //copy toolbar
    bcopy(&mb64_save.toolbar,&mb64_toolbar,sizeof(mb64_toolbar));
    bcopy(&mb64_save.toolbar_params,&mb64_toolbar_params,sizeof(mb64_toolbar_params));

    // copy custom theme
    bcopy(&mb64_save.custom_theme,&mb64_curr_custom_theme,sizeof(struct mb64_custom_theme));

    // for (u32 i = 0; i < NUM_MATERIALS_PER_THEME; i++) {
    //     mb64_curr_custom_theme.mats[i] = random_float() * MB64_MATLIST_END;
    //     mb64_curr_custom_theme.topmats[i] = random_float() * MB64_MATLIST_END;
    //     mb64_curr_custom_theme.topmatsEnabled[i] = 1;
    // }
    update_custom_theme();

    u32 oldIndex = 0;
    bzero(&mb64_tile_data_indices,sizeof(mb64_tile_data_indices));
    // Load tiles and build index list. Assume all tiles are in order
    for (i = 0; i < mb64_tile_count; i++) {
        //bcopy(&mb64_save.tiles[i],&mb64_tile_data[i],sizeof(mb64_tile_data[i]));
        u32 curIndex = get_tiletype_index(mb64_tile_data[i].type, mb64_tile_data[i].mat);

        if (curIndex != oldIndex) {
            // These tiles do not exist in the level so fill in the indices
            mb64_tile_data_indices[oldIndex + 1] = i;
            for (u32 j = oldIndex + 1; j < curIndex; j++) {
                mb64_tile_data_indices[j + 1] = mb64_tile_data_indices[j];
            }
            oldIndex = curIndex;
        }

        s8 pos[3];
        vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z)

        place_terrain_data(pos, mb64_tile_data[i].type, mb64_tile_data[i].rot, mb64_tile_data[i].mat);
        get_grid_tile(pos)->waterlogged = mb64_tile_data[i].waterlogged;
        if (mb64_tile_data[i].type != TILE_TYPE_WATER) place_occupy_data(pos);
    }
    // Fill in remaining indices that were unused
    for (u32 i = oldIndex + 1; i < ARRAY_COUNT(mb64_tile_data_indices); i++) {
        mb64_tile_data_indices[i] = mb64_tile_count;
    }

    mb64_trajectories_used = 0;
    for (i = 0; i < mb64_object_count; i++) {
        //bcopy(&mb64_save.objects[i],&mb64_object_data[i],sizeof(mb64_object_data[i]));
        s8 pos[3];
        vec3_set(pos, mb64_object_data[i].x, mb64_object_data[i].y, mb64_object_data[i].z)
        place_occupy_data(pos);
        if (mb64_object_type_list[mb64_object_data[i].type].flags & OBJ_TYPE_TRAJECTORY) {
            mb64_trajectories_used++;
        }
    }

    for (i = 0; i < MB64_MAX_TRAJECTORIES; i++) {
        for (j = 0; j < MB64_TRAJECTORY_LENGTH; j++) {
            mb64_trajectory_list[i][j][0] = mb64_save.trajectories[i][j].t;
            mb64_trajectory_list[i][j][1] = GRID_TO_POS(mb64_save.trajectories[i][j].x);
            mb64_trajectory_list[i][j][2] = GRID_TO_POS(mb64_save.trajectories[i][j].y);
            mb64_trajectory_list[i][j][3] = GRID_TO_POS(mb64_save.trajectories[i][j].z);
        }
    }
    

    mb64_set_data_overrides();

    if (!fresh) {
        update_painting();
    }
}

void mb64_init() {
    load_level();
    if (mb64_level_action != MB64_LA_PLAY_LEVELS) {
        vec3_set(mb64_cursor_pos, 32, 0, 32);
        mb64_camera_foc[0] = GRID_TO_POS(32);
        mb64_camera_foc[1] = 0.0f;
        mb64_camera_foc[2] = GRID_TO_POS(32);
    }
}

void sb_init(void) {
    struct Object *spawn_obj;

    mb64_toolbar_index = 0;
    reload_bg();
    generate_terrain_gfx();

    switch(mb64_mode) {
        case MB64_MODE_MAKE:
            mb64_menu_state = MB64_MAKE_MAIN;
            o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            generate_object_preview();

            //init visual tile bounds
            for (u8 i=0; i<6; i++) {
                mb64_boundary_object[i] = spawn_object(o,MODEL_MAKER_BOUNDARY,bhvStaticObject);
            }
            mb64_boundary_object[2]->oFaceAngleRoll = -0x4000;
            mb64_boundary_object[3]->oFaceAngleRoll = -0x4000;
            mb64_boundary_object[4]->oFaceAnglePitch = 0x4000;
            mb64_boundary_object[5]->oFaceAnglePitch = 0x4000;

            if (mb64_sram_configuration.option_flags & (1<<OPT_MUSIC)) {
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, seq_musicmenu_array[mb64_lopt_seq[0]]), 0);
            }
        break;
        case MB64_MODE_PLAY:
            mb64_menu_state = MB64_MAKE_PLAY;
            generate_terrain_collision();
            reset_rng();
            gGlobalTimer = 0;
            generate_objects_to_level();
            load_obj_warp_nodes();

            spawn_obj = cur_obj_nearest_object_with_behavior(bhvSpawn);
            if (spawn_obj) {
                if (mb64_level_action == MB64_LA_BUILD) {
                    gMarioState->pos[0] = (f32)(GRID_TO_POS(mb64_cursor_pos[0]));
                    gMarioState->pos[1] = (f32)(GRID_TO_POS(mb64_cursor_pos[1]));
                    gMarioState->pos[2] = (f32)(GRID_TO_POS(mb64_cursor_pos[2]));
                    set_mario_action(gMarioState,ACT_IDLE,0);
                    gMarioState->faceAngle[1] = mb64_rot_selection*0x4000;
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

            if (mb64_sram_configuration.option_flags & (1<<OPT_MUSIC)) {
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, seq_musicmenu_array[mb64_lopt_seq[0]]), 0);
            }
        break;
    }
}

// Keep cursor in bounds
s32 snap_cursor(void) {
    s32 gridmax = mb64_grid_min + mb64_grid_size - 1;
    s32 gridymax = (mb64_curr_boundary & MB64_BOUNDARY_CEILING) ? mb64_lopt_boundary_height-1 : 63;
    if (mb64_cursor_pos[0] < mb64_grid_min) {mb64_cursor_pos[0] = mb64_grid_min; return TRUE;}
    if (mb64_cursor_pos[0] > gridmax) {mb64_cursor_pos[0] = gridmax; return TRUE;}
    if (mb64_cursor_pos[2] < mb64_grid_min) {mb64_cursor_pos[2] = mb64_grid_min; return TRUE;}
    if (mb64_cursor_pos[2] > gridmax) {mb64_cursor_pos[2] = gridmax; return TRUE;}
    if (mb64_cursor_pos[1] < 0) {mb64_cursor_pos[1] = 0; return TRUE;}
    if (mb64_cursor_pos[1] > gridymax) {mb64_cursor_pos[1] = gridymax; return TRUE;}
    return FALSE;
}

// Wrap cursor to other side of level if out of bounds
s32 wrap_cursor(void) {
    s32 gridmax = mb64_grid_min + mb64_grid_size - 1;
    s32 gridymax = (mb64_curr_boundary & MB64_BOUNDARY_CEILING) ? mb64_lopt_boundary_height-1 : 63;
    if (mb64_cursor_pos[0] < mb64_grid_min) {mb64_cursor_pos[0] = gridmax; return TRUE;}
    if (mb64_cursor_pos[0] > gridmax) {mb64_cursor_pos[0] = mb64_grid_min; return TRUE;}
    if (mb64_cursor_pos[2] < mb64_grid_min) {mb64_cursor_pos[2] = gridmax; return TRUE;}
    if (mb64_cursor_pos[2] > gridmax) {mb64_cursor_pos[2] = mb64_grid_min; return TRUE;}
    if (mb64_cursor_pos[1] < 0) {mb64_cursor_pos[1] = gridymax; return TRUE;}
    if (mb64_cursor_pos[1] > gridymax) {mb64_cursor_pos[1] = 0; return TRUE;}
}

extern void play_sound_cbutton_side(void);

u8 c_button_timer = 0;
u8 cursor_wrap = FALSE;
u32 main_cursor_logic(u32 joystick) {
    u8 cursorMoved = FALSE;

    if (sDelayedWarpOp == WARP_OP_NONE) {
        if (joystick != 0) {
            switch(((joystick-1)+mb64_camera_rot_offset)%4) {
                case 0:
                    mb64_cursor_pos[0]++;
                    cursorMoved = TRUE;
                break;
                case 1:
                    mb64_cursor_pos[2]--;
                    cursorMoved = TRUE;
                break;
                case 2:
                    mb64_cursor_pos[0]--;
                    cursorMoved = TRUE;
                break;
                case 3:
                    mb64_cursor_pos[2]++;
                    cursorMoved = TRUE;
                break;
            }
        }

        c_button_timer ++;
        if (!(gPlayer1Controller->buttonDown & (U_CBUTTONS|D_CBUTTONS))) {
            c_button_timer = 0;
        }

        if ((gPlayer1Controller->buttonDown & U_CBUTTONS)&&(c_button_timer%5 == 1)) {
            mb64_cursor_pos[1]++;
            cursorMoved = TRUE;
        }
        if ((gPlayer1Controller->buttonDown & D_CBUTTONS)&&(c_button_timer%5 == 1)) {
            mb64_cursor_pos[1]--;
            cursorMoved = TRUE;
        }
    }
    if (gPlayer1Controller->buttonPressed & R_CBUTTONS) {
        mb64_camera_rot_offset++;
        if (mb64_sram_configuration.option_flags & (1<<OPT_CAMSOUND)) {
            play_sound(SOUND_MENU_CAMERA_TURN, gGlobalSoundSource);
        }
    }
    if (gPlayer1Controller->buttonPressed & L_CBUTTONS) {
        mb64_camera_rot_offset--;
        if (mb64_sram_configuration.option_flags & (1<<OPT_CAMSOUND)) {
            play_sound(SOUND_MENU_CAMERA_TURN, gGlobalSoundSource);
        }
    }
    mb64_camera_rot_offset = (mb64_camera_rot_offset % 4)+4;

    if (cursorMoved) {
        if (!cursor_wrap) {
           if (snap_cursor()) cursor_wrap = TRUE;
        } else {
            wrap_cursor();
            cursor_wrap = FALSE;
        }
    }

    //camera zooming
    if (gPlayer1Controller->buttonPressed & D_JPAD) {
        mb64_camera_zoom_index++;
        if (mb64_sram_configuration.option_flags & (1<<OPT_CAMSOUND)) {
            play_sound(SOUND_MENU_CLICK_CHANGE_VIEW, gGlobalSoundSource);
        }
    }
    mb64_camera_zoom_index = (mb64_camera_zoom_index+5)%5;

    o->oPosX = GRID_TO_POS(mb64_cursor_pos[0]); 
    o->oPosY = GRID_TO_POS(mb64_cursor_pos[1]); 
    o->oPosZ = GRID_TO_POS(mb64_cursor_pos[2]); 

    return cursorMoved;
}

void update_boundary_wall() {
    for (u8 i=0; i<6; i++) {
        vec3_copy(&mb64_boundary_object[i]->oPosVec,&o->oPosVec);
    }
    mb64_boundary_object[0]->oPosY = GRID_TO_POS(0);
    mb64_boundary_object[1]->oPosY = GRID_TO_POS(64);
    mb64_boundary_object[2]->oPosX = GRID_TO_POS(mb64_grid_min);
    mb64_boundary_object[3]->oPosX = GRID_TO_POS(mb64_grid_min + mb64_grid_size);
    mb64_boundary_object[4]->oPosZ = GRID_TO_POS(mb64_grid_min);
    mb64_boundary_object[5]->oPosZ = GRID_TO_POS(mb64_grid_min + mb64_grid_size);

    if (mb64_menu_state == MB64_MAKE_SCREENSHOT) {
        for (int i=0; i<6; i++) {
            mb64_boundary_object[i]->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
        }
    } else {
        for (int i=0; i<6; i++) {
            mb64_boundary_object[i]->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
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

void (*mb64_option_changed_func)(void) = NULL;

void update_custom_theme(void) {
    for (u32 i = 0; i < NUM_MATERIALS_PER_THEME; i++) {
        mb64_theme_table[MB64_THEME_CUSTOM].mats[i].mat = mb64_curr_custom_theme.mats[i];
        if (mb64_curr_custom_theme.topmatsEnabled[i]) {
            mb64_theme_table[MB64_THEME_CUSTOM].mats[i].topmat = mb64_curr_custom_theme.topmats[i];
        } else {
            mb64_theme_table[MB64_THEME_CUSTOM].mats[i].topmat = mb64_curr_custom_theme.mats[i];
        }
    }
    mb64_theme_table[MB64_THEME_CUSTOM].fence = mb64_curr_custom_theme.fence;
    mb64_theme_table[MB64_THEME_CUSTOM].pole = mb64_curr_custom_theme.pole;
    mb64_theme_table[MB64_THEME_CUSTOM].bars = mb64_curr_custom_theme.bars;
    mb64_theme_table[MB64_THEME_CUSTOM].water = mb64_curr_custom_theme.water;
}

void reload_theme(void) {
    generate_terrain_gfx();
    mb64_set_data_overrides();
    generate_object_preview();
}

void reload_bg(void) {
    void *dest = NULL;
    void *srcStart = mb64_skybox_table[mb64_lopt_bg*2];
    void *srcEnd = mb64_skybox_table[mb64_lopt_bg*2+1];

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

    generate_terrain_gfx(); // since some backgrounds affect the boundary
}

u8 mb64_upsidedown_tile = FALSE;
u8 mb64_joystick;
extern s16 mb64_menu_start_timer;
extern s16 mb64_menu_end_timer;

s16 mb64_freecam_pitch;
s16 mb64_freecam_yaw;
u8 mb64_freecam_snap = FALSE;
u8 mb64_freecam_help = TRUE;
u8 mb64_freecam_snap_timer = 0;

void freecam_camera_init(void) {
    vec3f_copy(mb64_camera_pos_prev,mb64_camera_pos);

    Vec3f d;
    vec3_diff(d, mb64_camera_pos, mb64_camera_foc);
    f32 xz = (sqr(d[0]) + sqr(d[2]));
    mb64_freecam_pitch = atan2s(sqrtf(xz), d[1]) + 0x4000;
    mb64_freecam_yaw = atan2s(d[2], d[0]);

    mb64_freecam_snap = FALSE;
    mb64_freecam_snap_timer = 0;
    mb64_prepare_level_screenshot = TRUE;
}

void freecam_camera_main(void) {
    if (mb64_freecam_snap) {
        mb64_freecam_snap_timer++;
        if (mb64_freecam_snap_timer == 3) {
            play_sound(SOUND_MENU_CLICK_CHANGE_VIEW, gGlobalSoundSource);
            for (u8 i=0; i<16; i++) {
                osRecvMesg(&gGameVblankQueue, &gMainReceivedMesg, OS_MESG_BLOCK);
            }
            save_level();
        }
        if (mb64_freecam_snap_timer > 30) {
            mb64_menu_state = MB64_MAKE_MAIN;
            mb64_camera_fov = 45.0f;
            mb64_prepare_level_screenshot = FALSE;
            vec3f_copy(mb64_camera_pos,mb64_camera_pos_prev);
            generate_object_preview();
            mb64_freecam_help = TRUE;
        }
        return;
    }

    // camera controls
    mb64_freecam_yaw += gPlayer1Controller->rawStickX*-4;
    mb64_freecam_pitch += gPlayer1Controller->rawStickY*-4;

    if (mb64_freecam_pitch < 0x100) {
        mb64_freecam_pitch = 0x100;
    }
    if (mb64_freecam_pitch > 0x7000) {
        mb64_freecam_pitch = 0x7000;
    }

    if (gPlayer1Controller->buttonDown & U_CBUTTONS) {
        mb64_camera_pos[0] += ( sins(mb64_freecam_yaw) * -sins(mb64_freecam_pitch) * 45.0f );
        mb64_camera_pos[1] += ( coss(mb64_freecam_pitch) * 45.0f );
        mb64_camera_pos[2] += ( coss(mb64_freecam_yaw) * -sins(mb64_freecam_pitch) * 45.0f );
    }

    if (gPlayer1Controller->buttonDown & D_CBUTTONS) {
        mb64_camera_pos[0] += ( sins(mb64_freecam_yaw) * -sins(mb64_freecam_pitch) * -45.0f );
        mb64_camera_pos[1] += ( coss(mb64_freecam_pitch) * -45.0f );
        mb64_camera_pos[2] += ( coss(mb64_freecam_yaw) * -sins(mb64_freecam_pitch) * -45.0f );
    }

    if (gPlayer1Controller->buttonDown & R_CBUTTONS) {
        mb64_camera_pos[0] += ( sins(mb64_freecam_yaw + 0x4000) * 30.0f );
        mb64_camera_pos[2] += ( coss(mb64_freecam_yaw + 0x4000) * 30.0f );
    }

    if (gPlayer1Controller->buttonDown & L_CBUTTONS) {
        mb64_camera_pos[0] += ( sins(mb64_freecam_yaw - 0x4000) * 30.0f );
        mb64_camera_pos[2] += ( coss(mb64_freecam_yaw - 0x4000) * 30.0f );
    }

    if (gPlayer1Controller->buttonDown & L_TRIG) {
        mb64_camera_fov -= 1.0f;
        cur_obj_play_sound_1(SOUND_AIR_AMP_BUZZ);

        if (mb64_camera_fov < 1.0f) {
            mb64_camera_fov = 1.0f;
        }
    }

    if (gPlayer1Controller->buttonDown & R_TRIG) {
        mb64_camera_fov += 1.0f;
        cur_obj_play_sound_1(SOUND_AIR_AMP_BUZZ);

        if (mb64_camera_fov > 100.0f) {
            mb64_camera_fov = 100.0f;
        }
    }

    if (gPlayer1Controller->buttonPressed & Z_TRIG) {
        mb64_freecam_help = !mb64_freecam_help;
    }

    if (gPlayer1Controller->buttonPressed & START_BUTTON) {
        mb64_freecam_snap = TRUE;
    }

    if (gPlayer1Controller->buttonPressed & B_BUTTON) {
        mb64_menu_state = MB64_MAKE_MAIN;
        mb64_camera_fov = 45.0f;
        mb64_prepare_level_screenshot = FALSE;
        vec3f_copy(mb64_camera_pos,mb64_camera_pos_prev);
        generate_object_preview();
    }

    // transform camera
    mb64_camera_foc[0] = mb64_camera_pos[0] + ( sins(mb64_freecam_yaw) * -sins(mb64_freecam_pitch) * 100.0f );
    mb64_camera_foc[1] = mb64_camera_pos[1] + ( coss(mb64_freecam_pitch) * 100.0f );
    mb64_camera_foc[2] = mb64_camera_pos[2] + ( coss(mb64_freecam_yaw) * -sins(mb64_freecam_pitch) * 100.0f );
}

Gfx *get_button_tex(u32 buttonId, u32 objIndex) {
    if (mb64_ui_buttons[buttonId].placeMode == MB64_PM_OBJ) {
        u32 id;
        if (mb64_ui_buttons[buttonId].multiObj) {
            id = mb64_ui_buttons[buttonId].idList[objIndex];
        } else {
            id = mb64_ui_buttons[buttonId].id;
        }
        return mb64_object_type_list[id].btn;
    }
    if (buttonId == MB64_BUTTON_BLANK) return mat_b_btn_blank;
    return mb64_terrain_info_list[mb64_ui_buttons[buttonId].id].button;
}

Gfx *get_button_str(u32 buttonId) {
    if (mb64_ui_buttons[buttonId].placeMode == MB64_PM_OBJ) {
        if (mb64_ui_buttons[buttonId].multiObj) {
            return mb64_ui_buttons[buttonId].name;
        } else {
            u32 id = mb64_ui_buttons[buttonId].id;
            return mb64_object_type_list[id].name;
        }
    }
    return mb64_terrain_info_list[mb64_ui_buttons[buttonId].id].name;
}

void sb_loop(void) {
    Vec3f cam_pos_offset = {0.0f,mb64_current_camera_zoom[1],0};
    mb64_joystick = joystick_direction();
    u8 cursorMoved = FALSE;

    if (mb64_do_save) {
        mb64_do_save = FALSE;
        save_level();
    }

    mb64_camera_angle = approach_s16_asymptotic(mb64_camera_angle,mb64_camera_rot_offset*0x4000,4);
    cam_pos_offset[0] = sins(mb64_camera_angle+0x8000)*mb64_current_camera_zoom[0];
    cam_pos_offset[2] = coss(mb64_camera_angle+0x8000)*mb64_current_camera_zoom[0];

    mb64_current_camera_zoom[0] = lerp(mb64_current_camera_zoom[0], mb64_camera_zoom_table[mb64_camera_zoom_index][0],0.2f);
    mb64_current_camera_zoom[1] = lerp(mb64_current_camera_zoom[1], mb64_camera_zoom_table[mb64_camera_zoom_index][1],0.2f);

    if (mb64_option_changed_func) {
        mb64_option_changed_func();
        mb64_option_changed_func = NULL;
    }
    if ((mb64_menu_state != MB64_MAKE_PLAY) && mb64_tip_timer) {
        if (!(--mb64_tip_timer)) mb64_show_tip();
    }
    struct mb64_ui_button_type *curBtn;

    switch(mb64_menu_state) {
        case MB64_MAKE_MAIN:
            cursorMoved = main_cursor_logic(mb64_joystick);
            s32 updatePreviewObj = cursorMoved;

            if (sDelayedWarpOp == WARP_OP_NONE) {
                if (gPlayer1Controller->buttonPressed & L_TRIG) {
                    mb64_toolbar_index--;
                    updatePreviewObj = TRUE;
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                } else if (gPlayer1Controller->buttonPressed & R_TRIG) {
                    mb64_toolbar_index++;
                    updatePreviewObj = TRUE;
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                }
            }

            mb64_toolbar_index = (mb64_toolbar_index+9)%9;
            mb64_param_selection = mb64_toolbar_params[mb64_toolbar_index];

            if (mb64_place_mode != MB64_PM_OBJ) updatePreviewObj = TRUE;

            //parameter changing
            if ((mb64_place_mode != MB64_PM_OBJ) || (mb64_ui_buttons[mb64_toolbar[mb64_toolbar_index]].paramCount != 0)) {
                if (gPlayer1Controller->buttonPressed & L_JPAD) {
                    mb64_param_selection--;
                    updatePreviewObj = TRUE;
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                } else if (gPlayer1Controller->buttonPressed & R_JPAD) {
                    mb64_param_selection++;
                    updatePreviewObj = TRUE;
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                }
                if (mb64_place_mode == MB64_PM_OBJ) {
                    u32 max = mb64_ui_buttons[mb64_toolbar[mb64_toolbar_index]].paramCount;
                    mb64_param_selection = (mb64_param_selection+max)%max;
                    mb64_toolbar_params[mb64_toolbar_index] = mb64_param_selection;
                }
            }

            curBtn = &mb64_ui_buttons[mb64_toolbar[mb64_toolbar_index]];
            if (curBtn->multiObj) {
                mb64_id_selection = curBtn->idList[mb64_param_selection];
            } else {
                mb64_id_selection = curBtn->id;
            }
            mb64_place_mode = curBtn->placeMode;

            if (mb64_upsidedown_tile) {
                if ((mb64_id_selection < TILE_END_OF_FLIPPABLE)&&(mb64_place_mode == MB64_PM_TILE)) {
                    mb64_id_selection = (mb64_id_selection & ~1) | 1;
                } else {
                    mb64_upsidedown_tile = FALSE;
                }
            }

            u8 at_spawn_point = FALSE;

            //Single A press
            if (gPlayer1Controller->buttonPressed & A_BUTTON || 
                ((gPlayer1Controller->buttonPressed & START_BUTTON) && (mb64_toolbar_index >= 7))) {
                switch(mb64_toolbar_index) {
                    case 7: // save and test

                        for (u32 i=0;i<mb64_object_count;i++) {
                            if ((mb64_object_data[i].x == mb64_cursor_pos[0])&&(mb64_object_data[i].y == mb64_cursor_pos[1])&&(mb64_object_data[i].z == mb64_cursor_pos[2])) {
                                if (mb64_object_data[i].type == OBJECT_TYPE_MARIO_SPAWN) {
                                    at_spawn_point = TRUE;
                                    break;
                                }
                                break;
                            }
                        }

                        if (get_occupy_data(mb64_cursor_pos) && !at_spawn_point) {
                            mb64_show_error_message("Cannot start test inside another tile or object!");
                            break;
                        }
                        if (!gWarpTransition.isActive && sDelayedWarpOp == WARP_OP_NONE) {
                            if (mount_success == FR_OK) {
                                save_level();
                            }
                            mb64_target_mode = MB64_MODE_PLAY;
                            reset_play_state();
                            level_trigger_warp(gMarioState, WARP_OP_LOOK_UP);
                            sSourceWarpNodeId = 0x0A;
                            play_sound(SOUND_MENU_STAR_SOUND_LETS_A_GO, gGlobalSoundSource);
                        }
                        break;
                    case 8: // options
                        switch (mb64_param_selection) {
                            case 0: // settings menu
                                mb64_newsize = mb64_lopt_size;
                                mb64_menu_state = MB64_MAKE_SETTINGS;
                                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                                mb64_menu_start_timer = 0;
                                mb64_menu_end_timer = -1;
                                mb64_menu_index = 0;
                                animate_list_reset();
                                break;
                            case 1: // screenshot
                                if (mount_success == FR_OK) {
                                    freecam_camera_init();
                                    generate_object_preview();
                                    mb64_menu_state = MB64_MAKE_SCREENSHOT;
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
                if (mb64_toolbar_index < 7) {
                    place_thing_action();
                }
            }

            if (gPlayer1Controller->buttonPressed & B_BUTTON || ((gPlayer1Controller->buttonDown & B_BUTTON) && cursorMoved)) {
                delete_tile_action(mb64_cursor_pos);
            }

            if (gPlayer1Controller->buttonPressed & START_BUTTON && (mb64_toolbar_index < 7)) {
                mb64_menu_start_timer = 0;
                mb64_menu_end_timer = -1;
                mb64_menu_index = 0;
                mb64_menu_state = MB64_MAKE_TOOLBOX;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                animate_list_reset();
            }

            if ((gPlayer1Controller->buttonPressed & U_JPAD)&&(mb64_place_mode == MB64_PM_TILE)) {
                if (mb64_id_selection < TILE_END_OF_FLIPPABLE) {
                    play_sound(SOUND_ACTION_SIDE_FLIP_UNK, gGlobalSoundSource);
                }
                mb64_upsidedown_tile ^= 1;
            }

            if (gPlayer1Controller->buttonPressed & Z_TRIG) {
                mb64_rot_selection++;
                mb64_rot_selection%=4;
                updatePreviewObj = TRUE;
            }

            if (updatePreviewObj) {
                delete_preview_object();
            }

            if (mb64_place_mode == MB64_PM_TILE) {
                if (mb64_terrain_info_list[mb64_id_selection].terrain) {
                    if (gPlayer1Controller->buttonPressed & L_JPAD) {
                        mb64_mat_selection --;
                    }
                    if (gPlayer1Controller->buttonPressed & R_JPAD) {
                        mb64_mat_selection ++;
                    }
                }
                mb64_mat_selection = (mb64_mat_selection+NUM_MATERIALS_PER_THEME)%NUM_MATERIALS_PER_THEME;
            }

            if (mb64_prepare_level_screenshot) {
                o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            } else {
                o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            }

            struct Object *spawnobjp = get_spawn_preview_object();
            if (spawnobjp) {
                if (mb64_prepare_level_screenshot) {
                    spawnobjp->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
                } else {
                    spawnobjp->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
                }  
            }

            update_boundary_wall();
            break;
        case MB64_MAKE_PLAY://PLAY MODE

            break;
        case MB64_MAKE_TOOLBOX: //MAKE MODE TOOLBOX
            //TOOLBOX CONTROLS
            delete_preview_object();
            if (mb64_joystick != 0) {
                switch((mb64_joystick-1)%4) {
                    case 0:
                        mb64_toolbox_index--;
                    break;
                    case 1:
                        mb64_toolbox_index+=TOOLBOX_WIDTH;
                    break;
                    case 2:
                        mb64_toolbox_index++;
                    break;
                    case 3:
                        mb64_toolbox_index-=TOOLBOX_WIDTH;
                    break;
                }
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
            }
            mb64_toolbox_index = (mb64_toolbox_index+sizeof(mb64_toolbox))%sizeof(mb64_toolbox);

            if (mb64_toolbox_index % TOOLBOX_WIDTH >= TOOLBOX_PAGE_WIDTH) {
                if (mb64_toolbox_x_offset > TOOLBOX_OFFSET_MAX) {
                    mb64_toolbox_x_offset = MAX(TOOLBOX_OFFSET_MAX,mb64_toolbox_x_offset-60);
                }
            } else {
                if (mb64_toolbox_x_offset < TOOLBOX_OFFSET_MIN) {
                    mb64_toolbox_x_offset = MIN(TOOLBOX_OFFSET_MIN,mb64_toolbox_x_offset+60);
                }
            }

            //TOOLBAR CONTROLS
            if (gPlayer1Controller->buttonPressed & L_TRIG) {
                mb64_toolbar_index--;
                mb64_toolbox_transition_btn_render = FALSE;
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
            }
            if (gPlayer1Controller->buttonPressed & R_TRIG) {
                mb64_toolbar_index++;
                mb64_toolbox_transition_btn_render = FALSE;
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
            }
            mb64_toolbar_index = (mb64_toolbar_index+7)%7;
            curBtn = &mb64_ui_buttons[mb64_toolbar[mb64_toolbar_index]];
            if (curBtn->multiObj) {
                mb64_id_selection = curBtn->idList[mb64_param_selection];
            } else {
                mb64_id_selection = curBtn->id;
            }
            mb64_place_mode = curBtn->placeMode;

            if (mb64_ui_buttons[mb64_toolbox[mb64_toolbox_index]].multiObj) {
                u32 selectedParam = mb64_toolbox_params[mb64_toolbox_index];
                u32 maxParam = mb64_ui_buttons[mb64_toolbox[mb64_toolbox_index]].paramCount;
                if (gPlayer1Controller->buttonPressed & L_JPAD) {
                    selectedParam += maxParam - 1;
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                } else if (gPlayer1Controller->buttonPressed & R_JPAD) {
                    selectedParam++;
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                }
                mb64_toolbox_params[mb64_toolbox_index] = (selectedParam % maxParam);
            }
            //PRESS A TO MOVE FROM TOOLBOX TO TOOLBAR
            if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                //You can not put a blank button into the toolbox
                if ( mb64_toolbox[mb64_toolbox_index] != MB64_BUTTON_BLANK) {

                    mb64_toolbox_transition_btn_render = TRUE;
                    mb64_toolbox_transition_progress = 0.0f;
                    // current pos
                    mb64_toolbox_transition_btn_x = GET_TOOLBOX_X(mb64_toolbox_index);
                    mb64_toolbox_transition_btn_y = GET_TOOLBOX_Y(mb64_toolbox_index)-5;
                    // target pos
                    mb64_toolbox_transition_btn_tx = 34.0f+(mb64_toolbar_index*32.0f);
                    mb64_toolbox_transition_btn_ty = 25.0f;
                    mb64_toolbox_transition_btn_old_gfx = get_button_tex(mb64_toolbar[mb64_toolbar_index], mb64_toolbar_params[mb64_toolbar_index]);
                    mb64_toolbox_transition_btn_gfx = get_button_tex(mb64_toolbox[mb64_toolbox_index], mb64_toolbox_params[mb64_toolbox_index]);

                    mb64_toolbar[mb64_toolbar_index] = mb64_toolbox[mb64_toolbox_index];
                    mb64_toolbar_params[mb64_toolbar_index] = mb64_param_selection = mb64_toolbox_params[mb64_toolbox_index];

                    play_sound(SOUND_ACTION_BRUSH_HAIR, gGlobalSoundSource);
                } else {
                    //error sound
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
            }

            if (mb64_menu_end_timer == 10) {
                mb64_menu_state = MB64_MAKE_MAIN;
                mb64_toolbox_transition_btn_render = FALSE;
            }
            break;
        case MB64_MAKE_SETTINGS: //settings
            if (mb64_menu_end_timer == 10) {
                mb64_menu_state = MB64_MAKE_MAIN;
            }
            break;
        case MB64_MAKE_TRAJECTORY: //trajectory maker
            delete_preview_object();
            cursorMoved = main_cursor_logic(mb64_joystick);

            if (cursorMoved) {
                generate_trajectory_gfx();
            }

            if (mb64_trajectory_edit_index == 0) {
                // Initial placement on top of the object
                mb64_trajectory_list[mb64_trajectory_to_edit][0][0] = 0;
                mb64_trajectory_list[mb64_trajectory_to_edit][0][1] = o->oPosX;
                mb64_trajectory_list[mb64_trajectory_to_edit][0][2] = o->oPosY;
                mb64_trajectory_list[mb64_trajectory_to_edit][0][3] = o->oPosZ;
                mb64_trajectory_list[mb64_trajectory_to_edit][1][0] = -1;
                mb64_trajectory_edit_index++; 
            } else {
                if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                    if (mb64_trajectory_edit_index == MB64_TRAJECTORY_LENGTH - 1) {
                        mb64_show_error_message("Maximum trajectory length reached! (max 50)");
                    // i fucking hate this, worst code ever. this hopefully won't have floating point inaccuracies
                    } else if (mb64_trajectory_list[mb64_trajectory_to_edit][mb64_trajectory_edit_index - 1][1] == o->oPosX
                            && mb64_trajectory_list[mb64_trajectory_to_edit][mb64_trajectory_edit_index - 1][2] == o->oPosY
                            && mb64_trajectory_list[mb64_trajectory_to_edit][mb64_trajectory_edit_index - 1][3] == o->oPosZ) {
                        mb64_show_error_message("");
                    } else {
                        mb64_trajectory_list[mb64_trajectory_to_edit][mb64_trajectory_edit_index][0] = mb64_trajectory_edit_index;
                        mb64_trajectory_list[mb64_trajectory_to_edit][mb64_trajectory_edit_index][1] = o->oPosX;
                        mb64_trajectory_list[mb64_trajectory_to_edit][mb64_trajectory_edit_index][2] = o->oPosY;
                        mb64_trajectory_list[mb64_trajectory_to_edit][mb64_trajectory_edit_index][3] = o->oPosZ;
                        mb64_trajectory_list[mb64_trajectory_to_edit][mb64_trajectory_edit_index+1][0] = -1;
                        mb64_trajectory_edit_index++;
                        play_place_sound(SOUND_MENU_CLICK_FILE_SELECT | SOUND_VIBRATO);
                        generate_object_preview();
                    }
                } else if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                    if (mb64_trajectory_edit_index <= 1) {
                        mb64_show_error_message("Nothing to delete!");
                    } else {
                        mb64_trajectory_edit_index--;
                        mb64_trajectory_list[mb64_trajectory_to_edit][mb64_trajectory_edit_index][0] = -1;
                        play_place_sound(SOUND_GENERAL_DOOR_INSERT_KEY | SOUND_VIBRATO);
                        generate_object_preview();
                    }
                }
            }

            if (gPlayer1Controller->buttonPressed & START_BUTTON) {
                if (mb64_trajectory_edit_index == 1) {
                    mb64_show_error_message("Trajectory is too short!");
                } else {
                    mb64_menu_state = MB64_MAKE_MAIN;
                    generate_object_preview();
                }
            }

            update_boundary_wall();
            break;
        case MB64_MAKE_SCREENSHOT:
            o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            freecam_camera_main();
            update_boundary_wall();
            break;
        case MB64_MAKE_SELECT_DIALOG:
            if (mb64_joystick != 0) {
                switch((mb64_joystick-1)%4) {
                    case 0:
                        mb64_dialog_topic_index --;
                    break;
                    case 1:
                        mb64_dialog_subject_index++;
                        mb64_dialog_topic_index = 0;
                    break;
                    case 2:
                        mb64_dialog_topic_index ++;
                    break;
                    case 3:
                        mb64_dialog_topic_index = 0;
                        mb64_dialog_subject_index--;
                    break;
                }

                mb64_dialog_subject_index = (NUM_DIALOG_SUBJECT_COUNT + mb64_dialog_subject_index) % NUM_DIALOG_SUBJECT_COUNT;
                mb64_dialog_topic_index = (mb64_dialog_subjects[mb64_dialog_subject_index].topic_list_size + mb64_dialog_topic_index) % mb64_dialog_subjects[mb64_dialog_subject_index].topic_list_size;
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
            }

            if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                mb64_dialog_edit_ptr->bparam = mb64_dialog_subjects[mb64_dialog_subject_index].topic_list[mb64_dialog_topic_index].dialog_id;
                mb64_menu_state = MB64_MAKE_MAIN;
            }
            break;
    }

    if (mb64_menu_state == MB64_MAKE_MAIN || mb64_menu_state == MB64_MAKE_SETTINGS || mb64_menu_state == MB64_MAKE_TOOLBOX) {
        struct Object *previewObj = cur_obj_nearest_object_with_behavior(bhvCurrPreviewObject);
        if (!previewObj) {
            s8 pos[3];
            vec3_set(pos, mb64_cursor_pos[0], mb64_cursor_pos[1], mb64_cursor_pos[2]);

            if (mb64_place_mode == MB64_PM_OBJ) {
                struct mb64_object_info *info = &mb64_object_type_list[mb64_id_selection];

                spawn_preview_object(pos, mb64_rot_selection, mb64_param_selection, info, bhvCurrPreviewObject);
            } else if (mb64_place_mode == MB64_PM_TILE && mb64_id_selection == TILE_TYPE_CULL) {
                spawn_preview_object(pos, mb64_rot_selection, 0, &mb64_object_type_list[OBJECT_TYPE_CULL_PREVIEW], bhvCurrPreviewObject);
            }
        }
    }

    if (mb64_menu_state != MB64_MAKE_SCREENSHOT) {
        mb64_camera_foc[0] = lerp(mb64_camera_foc[0], GRID_TO_POS(mb64_cursor_pos[0]),  0.2f);
        mb64_camera_foc[1] = lerp(mb64_camera_foc[1], GRID_TO_POS(mb64_cursor_pos[1]), 0.2f);
        mb64_camera_foc[2] = lerp(mb64_camera_foc[2], GRID_TO_POS(mb64_cursor_pos[2]),  0.2f);

        vec3_copy(mb64_camera_pos,mb64_camera_foc);
        vec3_add(mb64_camera_pos,cam_pos_offset);
    }
}

void play_mb64_extra_music(u8 index) {
    if ((seq_musicmenu_array[mb64_lopt_seq[index]] != seq_musicmenu_array[mb64_lopt_seq[0]]) && (mb64_sram_configuration.option_flags & (1<<OPT_MUSIC))) {
        play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, seq_musicmenu_array[mb64_lopt_seq[index]]), 0);
    }
}

void stop_mb64_extra_music(u8 index) {
    if ((seq_musicmenu_array[mb64_lopt_seq[index]] != seq_musicmenu_array[mb64_lopt_seq[0]]) && (mb64_sram_configuration.option_flags & (1<<OPT_MUSIC))) {
        stop_background_music(SEQUENCE_ARGS(4, seq_musicmenu_array[mb64_lopt_seq[index]]));
    }
}

#include "src/game/mb64_menu.inc.c"
