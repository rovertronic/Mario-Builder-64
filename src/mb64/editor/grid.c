#include "grid.h"

#include "main.h"
#include "object.h"
#include "mb64/gfx/tile.h"
#include "mb64/menu/misc.h"

#include "surface_terrains.h"
#include "sounds.h"
#include "game/mario.h"

struct mb64_grid_obj mb64_grid_data[64][64][64] = {0};

struct mb64_tile mb64_tile_data[MB64_TILE_POOL_SIZE];
u16 mb64_tile_data_indices[NUM_MATERIALS_PER_THEME + 10] = {0};
u16 mb64_tile_count = 0;

u8 mb64_grid_min = 0;
u8 mb64_grid_size = 64;
s32 mb64_min_coord;
s32 mb64_max_coord;

s8 cullOffsetLUT[6][3] = {
    {0, 1, 0},
    {0, -1, 0},
    {1, 0, 0},
    {-1, 0, 0},
    {0, 0, 1},
    {0, 0, -1},
};

u8 mb64_rotated_dirs[4][6] = {
    {MB64_DIRECTION_UP, MB64_DIRECTION_DOWN, MB64_DIRECTION_POS_X, MB64_DIRECTION_NEG_X, MB64_DIRECTION_POS_Z, MB64_DIRECTION_NEG_Z},
    {MB64_DIRECTION_UP, MB64_DIRECTION_DOWN, MB64_DIRECTION_NEG_Z, MB64_DIRECTION_POS_Z, MB64_DIRECTION_POS_X, MB64_DIRECTION_NEG_X},
    {MB64_DIRECTION_UP, MB64_DIRECTION_DOWN, MB64_DIRECTION_NEG_X, MB64_DIRECTION_POS_X, MB64_DIRECTION_NEG_Z, MB64_DIRECTION_POS_Z},
    {MB64_DIRECTION_UP, MB64_DIRECTION_DOWN, MB64_DIRECTION_POS_Z, MB64_DIRECTION_NEG_Z, MB64_DIRECTION_NEG_X, MB64_DIRECTION_POS_X},
};

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

u32 shift_tile_data_indices(u32 tiletypeIndex) {
    u32 tiledataIndex = mb64_tile_data_indices[tiletypeIndex + 1];
    for (u32 i = tiletypeIndex + 1; i < ARRAY_COUNT(mb64_tile_data_indices); i++) {
        mb64_tile_data_indices[i]++;
    }

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

void place_tile(s8 pos[3]) {
    u8 waterlogged = FALSE;
    if (get_grid_tile(pos)->type == TILE_TYPE_WATER) {
        waterlogged = TRUE;
        for (u32 i = 0; i < mb64_tile_count; i++) {
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
        }
    } else {
        place_terrain_data(pos, TILE_TYPE_WATER, 0, 0);
        tile->waterlogged = TRUE;
        u32 newtileIndex = shift_tile_data_indices(WATER_TILETYPE_INDEX);

        mb64_tile_data[newtileIndex].x = pos[0];
        mb64_tile_data[newtileIndex].y = pos[1];
        mb64_tile_data[newtileIndex].z = pos[2];
        mb64_tile_data[newtileIndex].type = TILE_TYPE_WATER;
        mb64_tile_data[newtileIndex].mat = 0;
        mb64_tile_data[newtileIndex].rot = 0;
        mb64_tile_data[newtileIndex].waterlogged = TRUE;
        mb64_tile_count++;
        play_place_sound(SOUND_ACTION_TERRAIN_STEP + (SOUND_TERRAIN_WATER << 16));
    }
}

void delete_useless_cull_markers(void) {
    for (u32 i = mb64_tile_data_indices[CULL_TILETYPE_INDEX]; i < mb64_tile_data_indices[CULL_TILETYPE_INDEX + 1]; i++) {
        s8 pos[3];
        vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);

        if (!is_cull_marker_useless(pos)) {
            continue;
        }

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
