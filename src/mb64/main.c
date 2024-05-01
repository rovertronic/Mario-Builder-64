//object includes (a lot)
#include "main.h"
#include "menu.h"
#include "gfx.h"
#include "trajectory.h"
#include "boundary.h"
#include "display_funcs.h"

#include "lib/libpl/libpl-rhdc.h"

#include <string.h>
#include "game/object_list_processor.h"
#include "game/level_update.h"
#include "game/main.h"
#include "behavior_data.h"
#include "game/puppyprint.h"
#include "game/spawn_object.h"
#include "game/mario.h"
#include "audio/external.h"

void super_cum_working(struct Object *o, u8 type);

u8 mb64_menu_state = MB64_MAKE_MAIN;
u8 mb64_level_action = MB64_LA_BUILD;
u8 mb64_mode = MB64_MODE_UNINITIALIZED;
u8 mb64_target_mode = MB64_MODE_MAKE;
s8 mb64_cursor_pos[3] = {32,8,32};

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

struct mb64_tile mb64_tile_data[MB64_TILE_POOL_SIZE];
struct mb64_obj mb64_object_data[MB64_MAX_OBJS];
u16 mb64_tile_data_indices[NUM_MATERIALS_PER_THEME + 10] = {0};
u16 mb64_tile_count = 0;
u16 mb64_object_count = 0;
u16 mb64_object_limit_count = 0; // Tracks additional objects like in coin formations, flame spinners
u16 mb64_total_coin_count = 0;

struct Object *mb64_boundary_object[6]; //one for each side

u8 mb64_curr_boundary = 0;
u8 mb64_upsidedown_tile = FALSE;

//play mode stuff
s16 mb64_play_stars = 0;
s16 mb64_play_stars_max = 0;
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
u8 mb64_lopt_coinstar_max = 0;

u8 mb64_lopt_envfx = 0;
u8 mb64_lopt_theme = 0;
u8 mb64_lopt_bg = 0;
u8 mb64_lopt_boundary_mat = 0;
u8 mb64_lopt_boundary = 0;
u8 mb64_lopt_boundary_height = 0;
u8 mb64_lopt_game = MB64_GAME_VANILLA;
u8 mb64_lopt_size = 0;
u8 mb64_lopt_template = 0;
u8 mb64_lopt_coinstar = 0;
u8 mb64_lopt_waterlevel = 0;
u8 mb64_lopt_secret = 0;

u8 mb64_prepare_level_screenshot = FALSE;
u8 mb64_do_save = FALSE;

struct ExclamationBoxContents *mb64_exclamation_box_contents;

s8 cullOffsetLUT[6][3] = {
    {0, 1, 0},
    {0, -1, 0},
    {1, 0, 0},
    {-1, 0, 0},
    {0, 0, 1},
    {0, 0, -1},
};

s32 mb64_count_stars(void) {
    s32 numStars = 0;
    for (s32 i = 0; i < mb64_object_count; i++) {
        if (mb64_object_type_list[mb64_object_data[i].type].flags & OBJ_TYPE_STAR) {
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

void reset_play_state(void) {
    mb64_play_stars = 0;
    mb64_play_stars_bitfield = 0;
    mb64_play_badge_bitfield = 0;

    // & water level
    mb64_play_s16_water_level = -8224+(mb64_lopt_waterlevel*TILE_SIZE);
    gWDWWaterLevelChanging = FALSE;
    mb64_play_onoff = FALSE;

    mb64_play_speedrun_timer = 0;
}

u8 mb64_grid_min = 0;
u8 mb64_grid_size = 64;
s32 mb64_min_coord;
s32 mb64_max_coord;

s32 tile_sanity_check(void) {
    if (mb64_tile_count >= MB64_TILE_POOL_SIZE) {
        show_error("Tile limit reached! (max 20,000)");
        return FALSE;
    }
    if (mb64_vtx_total >= MB64_VTX_SIZE - 100) {
        if (mb64_id_selection != TILE_TYPE_CULL) {
            show_error("Vertex limit reached! (max 50,000)");
            return FALSE;
        }
    }
    if (mb64_gfx_total >= MB64_GFX_SIZE - 100) {
        if (mb64_id_selection != TILE_TYPE_CULL) {
            show_error("Warning: Mesh data pool full!");
            return FALSE;
        }
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
        show_error("Object limit reached! (max 512)");
        return FALSE;
    }

    if (info->flags & OBJ_TYPE_TRAJECTORY) {
        if (mb64_trajectories_used >= MB64_MAX_TRAJECTORIES) {
            show_error("Trajectory limit reached! (max 20)");
            return FALSE;
        }
    }

    if (info->flags & OBJ_TYPE_STAR) {
        // Count stars
        s32 numStars = mb64_count_stars();
        if (numStars >= 63) {
            show_error("Star limit reached! (max 63)");
            return FALSE;
        }
    }

    if (mb64_id_selection == OBJECT_TYPE_RED_COIN_STAR) {
        for (u32 i = 0; i < mb64_object_count; i++) {
            if (mb64_object_data[i].type == OBJECT_TYPE_RED_COIN_STAR) {
                show_error("Red Coin Star already placed!");
                return FALSE;
            }
        }
    }
    if (mb64_id_selection == OBJECT_TYPE_TRIGGER_STAR) {
        for (u32 i = 0; i < mb64_object_count; i++) {
            if (mb64_object_data[i].type == OBJECT_TYPE_TRIGGER_STAR) {
                show_error("Star Trigger star already placed!");
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

u32 get_tile_occupy_flags(u32 type) {
    switch (type) {
        case TILE_TYPE_POLE:
            return OBJ_OCCUPY_INNER;
        case TILE_TYPE_FENCE:
        case TILE_TYPE_TROLL:
            return OBJ_OCCUPY_OUTER;
        case TILE_TYPE_CULL:
            return 0;
        default:
            return OBJ_OCCUPY_FULL;
    }
}

u32 can_place(s8 pos[3], u32 occupyFlags) {
    // Tile Check
    u32 type = get_grid_tile(pos)->type;
    if (type != TILE_TYPE_EMPTY && type != TILE_TYPE_WATER) {
        u32 tileFlags = get_tile_occupy_flags(type);
        if (tileFlags & occupyFlags) return FALSE;
    }
    // Object Check
    for (u32 i = 0; i < mb64_object_count; i++) {
        struct mb64_obj *obj = &mb64_object_data[i];
        if (obj->x == pos[0] && obj->y == pos[1] && obj->z == pos[2]) {
            u32 objFlags = mb64_object_type_list[obj->type].occupy;
            if (obj->type == OBJECT_TYPE_COIN_FORMATION) { // ring override
                if (obj->bparam == 2) objFlags = OBJ_OCCUPY_OUTER;
            }
            
            if (objFlags & occupyFlags) return FALSE;
        }
    }
    return TRUE;
}

u32 can_place_tile(s8 pos[3]) {
    // Tiles can never stack, even if one is outer and one is inner
    u32 type = get_grid_tile(pos)->type;
    if (type != TILE_TYPE_EMPTY && type != TILE_TYPE_WATER) return FALSE;

    u32 flags = get_tile_occupy_flags(mb64_id_selection);
    return can_place(pos, flags);
}

u32 can_place_object(s8 pos[3]) {
    u32 flags = mb64_object_type_list[mb64_id_selection].occupy;
    if (mb64_id_selection == OBJECT_TYPE_COIN_FORMATION) {
        if (mb64_param_selection == 2) flags = OBJ_OCCUPY_OUTER;
    } else if (mb64_id_selection == OBJECT_TYPE_TRIGGER) {
        return FALSE;
    }
    return can_place(pos, flags);
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
    if (info->flags & OBJ_TYPE_BILLBOARD) {
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

void unload_all_preview_objs(void) {
    uintptr_t *behaviorAddr = segmented_to_virtual(bhvPreviewObject);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *obj = (struct Object *) listHead->next;

    while (obj != (struct Object *) listHead) {
        struct Object *nextobj = (struct Object *) obj->header.next;
        if (obj->behavior == behaviorAddr) {
            unload_object(obj);
        }
        obj = nextobj;
    }
}

void generate_object_preview(void) {
    s32 totalCoins = 0;
    s32 curExtraCoins = 0;
    s32 doubleCoins = FALSE;
    mb64_object_limit_count = 0;
    
    unload_all_preview_objs();

    for(u32 i = 0; i < mb64_object_count; i++){
        if (gFreeObjectList.next == NULL) break;
        s32 curType = mb64_object_data[i].type;
        struct mb64_object_info *info = &mb64_object_type_list[curType];
        s32 param = mb64_object_data[i].bparam;

        s8 pos[3];
        vec3_set(pos, mb64_object_data[i].x, mb64_object_data[i].y, mb64_object_data[i].z);
        curExtraCoins = 0;

        spawn_preview_object(pos, mb64_object_data[i].rot, param, info, bhvPreviewObject);
        curExtraCoins += info->numCoins;
        if (curType == OBJECT_TYPE_EXCL_BOX) {
            curExtraCoins += mb64_exclamation_box_contents[param].numCoins;
        }
        if (curType == OBJECT_TYPE_BADGE && param == 8) { // Greed badge
            doubleCoins = TRUE;
        }

        s32 extraObjs = get_extra_objects(curType, param);
        if (curType == OBJECT_TYPE_COIN_FORMATION) {
            curExtraCoins += extraObjs;
        }

        s32 curImbue = mb64_object_data[i].imbue;
        if (curImbue != IMBUE_NONE) {
            int badgeid = 0;
            if (curImbue >= IMBUE_BADGE_BASE) {
                badgeid = curImbue - IMBUE_BADGE_BASE;
                curImbue = IMBUE_BADGE_BASE;
            }
            
            struct Object * imbue_marker = spawn_object(gMarioObject,imbue_table[curImbue].model,bhvPreviewObject);
            imbue_marker->oBehParams2ndByte = badgeid;
            imbue_marker->oExtraVariable1 = imbue_table[curImbue].color;
            imbue_marker->oPreviewObjDisplayFunc = df_hide_during_screenshot;
            imbue_marker->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
            imbue_marker->oPosX = GRID_TO_POS(pos[0]);
            imbue_marker->oPosY = GRID_TO_POS(pos[1]);
            imbue_marker->oPosZ = GRID_TO_POS(pos[2]);
            mb64_object_limit_count ++;
            curExtraCoins = imbue_table[curImbue].coins; // replaces coin count
            if (curType == OBJECT_TYPE_SHOWRUNNER) {
                curExtraCoins += info->numCoins; // showrunner always drops coins
            }
        }

        mb64_object_limit_count += extraObjs + 1;
        totalCoins += curExtraCoins;
    }
    if (doubleCoins) totalCoins *= 2;

    u32 length = MIN(totalCoins / 20, 50);
    mb64_lopt_coinstar_max = length;

    if (mb64_lopt_coinstar > length) {
        mb64_lopt_coinstar = length;
    }
    mb64_total_coin_count = totalCoins;

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
        if ((info->flags & OBJ_TYPE_STAR)||(mb64_object_data[i].imbue == IMBUE_STAR)) {
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

void delete_object(s32 index) {
    if (mb64_object_type_list[mb64_object_data[index].type].flags & OBJ_TYPE_TRAJECTORY) { 
        remove_trajectory(mb64_object_data[index].bparam);
    }

    mb64_object_count--;
    for (u32 i = index; i < mb64_object_count; i++) {
        mb64_object_data[i] = mb64_object_data[i+1];
    }
    generate_object_preview();
}

void place_number_spawner_check(s8 pos[3], s32 spawnerType, s32 objType, s32 objImbue) {
    s32 objectCount = 0;
    s32 hasSpawner = FALSE;
    for (s32 i = 0; i < mb64_object_count; i++) {
        if (mb64_object_data[i].type == spawnerType) {
            hasSpawner = TRUE;
        } else if ((mb64_object_data[i].type == objType) ||
                    (mb64_object_data[i].imbue == objImbue)) {
            objectCount++;
        }
    }
    if (hasSpawner) df_spawn_number(pos, objectCount);
}

void should_spawn_place_number(s8 pos[3]) {
    if (mb64_id_selection == OBJECT_TYPE_RED_COIN) {
        place_number_spawner_check(pos, OBJECT_TYPE_RED_COIN_STAR, OBJECT_TYPE_RED_COIN, IMBUE_RED_COIN);
    } else if (mb64_id_selection == OBJECT_TYPE_TRIGGER) {
        place_number_spawner_check(pos, OBJECT_TYPE_TRIGGER_STAR, OBJECT_TYPE_TRIGGER, IMBUE_TRIGGER);
    } else if ((mb64_object_type_list[mb64_id_selection].flags & OBJ_TYPE_STAR)) {
        s32 starCount = 0;
        for (s32 i = 0; i < mb64_object_count; i++) {
            if ((mb64_object_type_list[mb64_object_data[i].type].flags & OBJ_TYPE_STAR) ||
                (mb64_object_data[i].imbue == IMBUE_STAR)){
                starCount++;
            }
        }
        df_spawn_number(pos, starCount);
    }
}

void place_object(s8 pos[3]) {
    // If spawn, delete old spawn
    if (mb64_id_selection == OBJECT_TYPE_MARIO_SPAWN) {
        for (int i = 0; i < mb64_object_count; i++) {
            if (mb64_object_data[i].type == OBJECT_TYPE_MARIO_SPAWN) {
                delete_object(i);
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
        begin_editing_trajectory();
    } else if (mb64_object_type_list[mb64_id_selection].flags & OBJ_TYPE_HAS_DIALOG) {
        mb64_object_data[mb64_object_count].bparam = 0;
        // todo for dialogs
    } else {
        mb64_object_data[mb64_object_count].bparam = mb64_param_selection;
    }

    if (mb64_id_selection == OBJECT_TYPE_MONEYBAG) {
        mb64_object_data[mb64_object_count].imbue = IMBUE_THREE_COINS;
    } else if (mb64_id_selection == OBJECT_TYPE_BOO) {
        mb64_object_data[mb64_object_count].imbue = IMBUE_ONE_COIN;
    }

    mb64_object_count++;

    play_place_sound(mb64_object_type_list[mb64_id_selection].soundBits);
    should_spawn_place_number(pos);
}

void imbue_action(void) {
    for (u32 i=0;i<mb64_object_count;i++) {
        s32 objType = mb64_object_data[i].type;
        s32 canbeImbued = (mb64_object_type_list[objType].flags & OBJ_TYPE_IMBUABLE);
        if (mb64_id_selection == OBJECT_TYPE_TRIGGER) {
            canbeImbued |= (mb64_object_type_list[objType].flags & OBJ_TYPE_IMBUABLE_TRIGGER);
        }
        if (canbeImbued && (mb64_object_data[i].x == mb64_cursor_pos[0])&&(mb64_object_data[i].y == mb64_cursor_pos[1])&&(mb64_object_data[i].z == mb64_cursor_pos[2])) {
            u8 imbue_success = FALSE;
            if (!object_sanity_check()) break;
            u8 oldImbue = mb64_object_data[i].imbue;

            switch(mb64_id_selection) {
                case OBJECT_TYPE_STAR:
                    ;s32 numStars = mb64_count_stars();
                    if (numStars >= 63) {
                        show_error("Star limit reached! (max 63)");
                        imbue_success = FALSE;
                        break;
                    }
                    mb64_object_data[i].imbue = IMBUE_STAR;
                    imbue_success = TRUE;
                    break;
                case OBJECT_TYPE_BLUE_COIN:
                    if (mb64_object_type_list[objType].flags & OBJ_TYPE_IMBUABLE_COINS) {
                        mb64_object_data[i].imbue = IMBUE_BLUE_COIN;
                        imbue_success = TRUE;
                    }
                    break;
                case OBJECT_TYPE_COIN:
                case OBJECT_TYPE_COIN_FORMATION:
                    if (mb64_object_type_list[objType].flags & OBJ_TYPE_IMBUABLE_COINS) {
                        if ((objType == OBJECT_TYPE_BBOX_NORMAL) ||
                            (objType == OBJECT_TYPE_RFBOX) ||
                            (objType == OBJECT_TYPE_MONEYBAG)) {
                            mb64_object_data[i].imbue = IMBUE_THREE_COINS;
                        } else {
                            mb64_object_data[i].imbue = IMBUE_ONE_COIN;
                        }
                        imbue_success = TRUE;
                    }
                    break;

                case OBJECT_TYPE_BUTTON:
                    mb64_object_data[i].imbue = IMBUE_RED_SWITCH;
                    if (mb64_param_selection == 1) {
                        mb64_object_data[i].imbue = IMBUE_BLUE_SWITCH;
                    }
                    imbue_success = TRUE;
                    break;

#define generic_imbue(obj, imbueType) \
                case obj: \
                    mb64_object_data[i].imbue = imbueType; \
                    imbue_success = TRUE; \
                    break;

                generic_imbue(OBJECT_TYPE_RED_COIN, IMBUE_RED_COIN);
                generic_imbue(OBJECT_TYPE_TRIGGER, IMBUE_TRIGGER);
                generic_imbue(OBJECT_TYPE_CROWBAR, IMBUE_CROWBAR);
                generic_imbue(OBJECT_TYPE_MASK, IMBUE_BULLET_MASK);
                generic_imbue(OBJECT_TYPE_GREEN_COIN, IMBUE_GREEN_COIN);
                generic_imbue(OBJECT_TYPE_BADGE, IMBUE_BADGE_BASE + mb64_param_selection);
            }

            if (imbue_success && (oldImbue != mb64_object_data[i].imbue)) {
                if (objType == OBJECT_TYPE_EXCL_BOX && mb64_object_data[i].bparam <= 3) {
                    mb64_object_data[i].bparam = 4;
                }

                play_place_sound(mb64_object_type_list[mb64_id_selection].soundBits);
                generate_object_preview();
                should_spawn_place_number(mb64_cursor_pos);
                return;
            }
            break;
        }
    }
    if (mb64_id_selection == OBJECT_TYPE_TRIGGER) {
        show_error("Star Triggers must be placed in other objects!");
    }
}

void place_thing_action(void) {
    if (mb64_place_mode == MB64_PM_TILE) {
        if (tile_sanity_check()) {
            if (mb64_id_selection == TILE_TYPE_WATER) {
                place_water(mb64_cursor_pos);
            } else if (can_place_tile(mb64_cursor_pos)) {
                place_tile(mb64_cursor_pos);
            } else {
                return;
            }
            generate_terrain_gfx();
        }
    } else if (mb64_place_mode == MB64_PM_OBJ) {
        if (can_place_object(mb64_cursor_pos)) {
            if (object_sanity_check()) {
                place_object(mb64_cursor_pos);
                generate_object_preview();
            }
        } else {
            imbue_action();
        }
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
                show_error("Cannot delete spawn point!");
                break;
            }
            delete_object(i);
            i--;
            play_place_sound(SOUND_GENERAL_DOOR_INSERT_KEY | SOUND_VIBRATO);
        }
    }
}

void mb64_init() {
    load_level();
    if (mb64_level_action != MB64_LA_PLAY_LEVELS) {
        vec3_set(mb64_cursor_pos, 32, 8, 32);
        mb64_camera_foc[0] = GRID_TO_POS(32);
        mb64_camera_foc[1] = 0.0f;
        mb64_camera_foc[2] = GRID_TO_POS(32);
    }
}

#include "boot/slidec.h"
void reload_bg(void) {
    void *srcStart = mb64_skybox_table[mb64_lopt_bg*2];
    void *srcEnd = mb64_skybox_table[mb64_lopt_bg*2+1];

    if (srcStart == NULL) {
        return;
    }

    u32 compSize = ALIGN16(srcEnd - srcStart);
    u8 *compressed = main_pool_alloc(compSize, MEMORY_POOL_RIGHT);

    if (compressed != NULL) {
        dma_read(compressed, srcStart, srcEnd);
        slidstart(compressed, get_segment_base_addr(SEGMENT_SKYBOX));
        sSegmentROMTable[SEGMENT_SKYBOX] = (uintptr_t) srcStart;
        main_pool_free(compressed);
    }

    generate_terrain_gfx(); // since some backgrounds affect the boundary
}

// Called whenever boundary is changed
void reload_boundary_and_gfx(void) {
    generate_terrain_gfx();
    generate_boundary_collision();
}

void sb_init(void) {
    struct Object *spawn_obj;

    reload_bg();
    reload_boundary_and_gfx();

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

            play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, seq_musicmenu_array[mb64_lopt_seq[0]]), 0);
            create_toolbar();
            create_coord_display();
            break;
        case MB64_MODE_PLAY:
            mb64_menu_state = MB64_MAKE_PLAY;
            reset_rng();
            gGlobalTimer = 0;
            generate_objects_to_level();

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


            play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, seq_musicmenu_array[mb64_lopt_seq[0]]), 0);

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
void wrap_cursor(void) {
    s32 gridmax = mb64_grid_min + mb64_grid_size - 1;
    s32 gridymax = (mb64_curr_boundary & MB64_BOUNDARY_CEILING) ? mb64_lopt_boundary_height-1 : 63;
    if (mb64_cursor_pos[0] < mb64_grid_min) {mb64_cursor_pos[0] = gridmax; return;}
    if (mb64_cursor_pos[0] > gridmax) {mb64_cursor_pos[0] = mb64_grid_min; return;}
    if (mb64_cursor_pos[2] < mb64_grid_min) {mb64_cursor_pos[2] = gridmax; return;}
    if (mb64_cursor_pos[2] > gridmax) {mb64_cursor_pos[2] = mb64_grid_min; return;}
    if (mb64_cursor_pos[1] < 0) {mb64_cursor_pos[1] = gridymax; return;}
    if (mb64_cursor_pos[1] > gridymax) {mb64_cursor_pos[1] = 0; return;}
}

extern void play_sound_cbutton_side(void);

u8 c_button_timer = 0;
u8 cursor_wrap = FALSE;
u8 mb64_joystick_timer = 0;
u32 main_cursor_logic() {
    u8 cursorMoved = FALSE;
    int joystick = 0;

    if (mb64_joystick_timer > 0) {
        mb64_joystick_timer--;
    }

    if ((gPlayer1Controller->rawStickX < 10)&&(gPlayer1Controller->rawStickX > -10)&&(gPlayer1Controller->rawStickY < 10)&&(gPlayer1Controller->rawStickY > -10)) {
        mb64_joystick_timer = 0;
    }

    if (mb64_joystick_timer == 0) {
        if (gPlayer1Controller->rawStickX > 60) {
            mb64_joystick_timer = 5;
            joystick = 3;
        } else if (gPlayer1Controller->rawStickX < -60) {
            mb64_joystick_timer = 5;
            joystick = 1;
        } else if (gPlayer1Controller->rawStickY > 60) {
            mb64_joystick_timer = 5;
            joystick = 4;
        } else if (gPlayer1Controller->rawStickY < -60) {
            mb64_joystick_timer = 5;
            joystick = 2;
        }
    }

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
    }
    if (gPlayer1Controller->buttonPressed & L_CBUTTONS) {
        mb64_camera_rot_offset--;
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
    reload_boundary_and_gfx();
    generate_object_preview();
}

s16 mb64_freecam_pitch;
s16 mb64_freecam_yaw;
u8 mb64_freecam_snap = FALSE;
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

void freecam_return(void) {
    mb64_menu_state = MB64_MAKE_MAIN;
    mb64_camera_fov = 45.0f;
    mb64_prepare_level_screenshot = FALSE;
    mb64_freecam_snap = FALSE;
    vec3f_copy(mb64_camera_pos,mb64_camera_pos_prev);
    generate_object_preview();
    show_coord_display();
    destroy_yellow_text();

    show_toolbar();
    toolbar_set_active(TRUE);
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
            freecam_return();
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
        play_sound(SOUND_AIR_AMP_BUZZ, gGlobalSoundSource);

        if (mb64_camera_fov < 1.0f) {
            mb64_camera_fov = 1.0f;
        }
    }

    if (gPlayer1Controller->buttonDown & R_TRIG) {
        mb64_camera_fov += 1.0f;
        play_sound(SOUND_AIR_AMP_BUZZ, gGlobalSoundSource);

        if (mb64_camera_fov > 100.0f) {
            mb64_camera_fov = 100.0f;
        }
    }

    if (gPlayer1Controller->buttonPressed & START_BUTTON) {
        mb64_freecam_snap = TRUE;
    }

    if (gPlayer1Controller->buttonPressed & B_BUTTON) {
        freecam_return();
    }

    // transform camera
    mb64_camera_foc[0] = mb64_camera_pos[0] + ( sins(mb64_freecam_yaw) * -sins(mb64_freecam_pitch) * 100.0f );
    mb64_camera_foc[1] = mb64_camera_pos[1] + ( coss(mb64_freecam_pitch) * 100.0f );
    mb64_camera_foc[2] = mb64_camera_pos[2] + ( coss(mb64_freecam_yaw) * -sins(mb64_freecam_pitch) * 100.0f );
}

u8 sPrevPreviewID; // used for resetting preview obj
u8 sPrevPreviewParam;

void sb_loop(void) {
    Vec3f cam_pos_offset = {0.0f,mb64_current_camera_zoom[1],0};
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

    switch(mb64_menu_state) {
        case MB64_MAKE_MAIN:
            ListComponent *toolbarlist = get_child(gToolbar);
            if (toolbarlist->base.inactive) {
                break;
            }
            cursorMoved = main_cursor_logic();

            // Update preview object
            if (cursorMoved || (sPrevPreviewID != mb64_id_selection) || (sPrevPreviewParam != mb64_param_selection)) {
                delete_preview_object();
            }
            sPrevPreviewID = mb64_id_selection;
            sPrevPreviewParam = mb64_param_selection;

            if (gPlayer1Controller->buttonPressed & Z_TRIG) {
                mb64_rot_selection = (mb64_rot_selection + 1) % 4;
                delete_preview_object();
            }


            //Single A press
            if (mb64_place_mode == MB64_PM_ACTION) {
                if (gPlayer1Controller->buttonPressed & (A_BUTTON | START_BUTTON)) {
                    switch (mb64_id_selection) {
                        // Begin Test
                        case OBJECT_TYPE_TEST_MARIO:
                            if ((!can_place(mb64_cursor_pos, OBJ_OCCUPY_INNER)) && !can_place(mb64_cursor_pos, OBJ_OCCUPY_OUTER)) {
                                show_error("Cannot start test here!");
                                break;
                            }
                            if (!gWarpTransition.isActive && sDelayedWarpOp == WARP_OP_NONE) {
                                if (gSDCard) {
                                    save_level();
                                }
                                toolbar_set_active(FALSE);
                                mb64_target_mode = MB64_MODE_PLAY;
                                reset_play_state();
                                level_trigger_warp(gMarioState, WARP_OP_LOOK_UP);
                                sSourceWarpNodeId = 0x0A;
                                play_sound(SOUND_MENU_STAR_SOUND_LETS_A_GO, gGlobalSoundSource);
                            }
                            break;
                        // Open settings menu
                        case OBJECT_TYPE_SETTINGS:
                            mb64_menu_state = MB64_MAKE_SETTINGS;
                            hide_toolbar();
                            hide_coord_display();
                            settings_menu_create();
                            play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                            break;
                    }
                }
            } else {
                if (gPlayer1Controller->buttonPressed & A_BUTTON || ((gPlayer1Controller->buttonDown & A_BUTTON) && cursorMoved)) {
                    place_thing_action();
                }
            }

            if (gPlayer1Controller->buttonPressed & B_BUTTON || ((gPlayer1Controller->buttonDown & B_BUTTON) && cursorMoved)) {
                delete_tile_action(mb64_cursor_pos);
            }

            if (gPlayer1Controller->buttonPressed & START_BUTTON && (mb64_place_mode != MB64_PM_ACTION)) {
                mb64_menu_state = MB64_MAKE_TOOLBOX;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                create_toolbox();
                hide_coord_display();
                delete_preview_object();
            }

            struct Object *spawnobjp = get_spawn_preview_object();
            if (mb64_prepare_level_screenshot) {
                o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
                if (spawnobjp) spawnobjp->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            } else {
                o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
                if (spawnobjp) spawnobjp->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            }

            update_boundary_wall();
            break;
        case MB64_MAKE_TOOLBOX: //MAKE MODE TOOLBOX
            delete_preview_object();
            break;
        case MB64_MAKE_TRAJECTORY: //trajectory maker
            delete_preview_object();
            cursorMoved = main_cursor_logic();

            if (cursorMoved) {
                generate_trajectory_gfx();
            }

            update_boundary_wall();
            break;
        case MB64_MAKE_SCREENSHOT:
            o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            freecam_camera_main();
            update_boundary_wall();
            break;
    }

    if (mb64_menu_state == MB64_MAKE_MAIN || mb64_menu_state == MB64_MAKE_SETTINGS || mb64_menu_state == MB64_MAKE_TOOLBOX) {
        struct Object *previewObj = cur_obj_nearest_object_with_behavior(bhvCurrPreviewObject);
        if (!previewObj) {
            s8 pos[3];
            vec3_set(pos, mb64_cursor_pos[0], mb64_cursor_pos[1], mb64_cursor_pos[2]);

            if (mb64_place_mode != MB64_PM_TILE) {
                struct mb64_object_info *info = &mb64_object_type_list[mb64_id_selection];
                spawn_preview_object(pos, mb64_rot_selection, mb64_param_selection, info, bhvCurrPreviewObject);
            } else if (mb64_id_selection == TILE_TYPE_CULL) {
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
    if (seq_musicmenu_array[mb64_lopt_seq[index]] != seq_musicmenu_array[mb64_lopt_seq[0]]) {
        play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, seq_musicmenu_array[mb64_lopt_seq[index]]), 0);
    }
}

void stop_mb64_extra_music(u8 index) {
    if (seq_musicmenu_array[mb64_lopt_seq[index]] != seq_musicmenu_array[mb64_lopt_seq[0]]) {
        stop_background_music(SEQUENCE_ARGS(4, seq_musicmenu_array[mb64_lopt_seq[index]]));
    }
}
