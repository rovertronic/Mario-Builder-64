#pragma once

#include "types.h"
#include "mb64/editor/main.h"
#include "boundary.h"

#define MB64_TILE_POOL_SIZE 20000
#define TILE_SIZE 256

struct mb64_tile {
    u32 x:6, y:6, z:6, type:5, mat:4, rot:2, waterlogged:1;
};

struct mb64_grid_obj {
    u16 type:5, mat:4, rot:2, waterlogged:1;
};

#define NUM_MATERIALS_PER_THEME 10
enum tiletypeIndices {
    FENCE_TILETYPE_INDEX = NUM_MATERIALS_PER_THEME,
    POLE_TILETYPE_INDEX,
    BARS_TILETYPE_INDEX,
    CULL_TILETYPE_INDEX,
    WATER_TILETYPE_INDEX,
    END_TILE_INDEX
};

enum {
    TILE_TYPE_EMPTY,
    // Flippable tiles
    TILE_TYPE_SLOPE = 2,
    TILE_TYPE_DSLOPE,
    TILE_TYPE_SLAB,
    TILE_TYPE_DSLAB,
    TILE_TYPE_CORNER,
    TILE_TYPE_DCORNER,
    TILE_TYPE_ICORNER, // Inner Corner
    TILE_TYPE_DICORNER, // Down Inner Corner
    TILE_TYPE_SCORNER, // Sloped Corner
    TILE_TYPE_DSCORNER, // Down Sloped Corner
    TILE_TYPE_ISCORNER, // Inverted Sloped Corner
    TILE_TYPE_DISCORNER, // Down Inverted Sloped Corner
    TILE_TYPE_UGENTLE,
    TILE_TYPE_DUGENTLE,
    TILE_TYPE_LGENTLE,
    TILE_TYPE_DLGENTLE,

    TILE_END_OF_FLIPPABLE,
    TILE_TYPE_BLOCK = TILE_END_OF_FLIPPABLE,
    TILE_TYPE_SSLOPE,
    TILE_TYPE_SSLAB,
    TILE_TYPE_CULL,
    TILE_TYPE_TROLL,
    TILE_TYPE_FENCE,
    TILE_TYPE_POLE,
    TILE_TYPE_BARS,

    TILE_TYPE_WATER, // only blocks that are empty otherwise
};

extern struct mb64_grid_obj mb64_grid_data[64][64][64];
extern struct mb64_tile mb64_tile_data[MB64_TILE_POOL_SIZE];
extern u16 mb64_tile_data_indices[NUM_MATERIALS_PER_THEME + 10];
extern u16 mb64_tile_count;
extern u8 mb64_grid_size;
extern u8 mb64_grid_min;
extern s32 mb64_min_coord;
extern s32 mb64_max_coord;
extern s8 cullOffsetLUT[6][3];

extern u8 mb64_rotated_dirs[4][6];
#define rotate_direction(dir, rot) (mb64_rotated_dirs[rot][dir])

#define GRID_TO_POS(gridx) ((gridx) * TILE_SIZE - (32 * TILE_SIZE) + TILE_SIZE/2)
#define POS_TO_GRID(pos) (((pos) + (32 * TILE_SIZE) - TILE_SIZE/2) / TILE_SIZE)

#define get_grid_tile(pos) (&(mb64_grid_data[(pos)[0]][(pos)[1]][(pos)[2]]))

#define AT_CEILING(y) ((mb64_curr_boundary & MB64_BOUNDARY_CEILING) && ((y) == mb64_lopt_boundary_height-1))

#define place_terrain_data(pos, type_, rot_, mat_) {        \
    mb64_grid_data[pos[0]][pos[1]][pos[2]].rot = rot_;       \
    mb64_grid_data[pos[0]][pos[1]][pos[2]].type = type_;     \
    mb64_grid_data[pos[0]][pos[1]][pos[2]].mat = mat_;       \
    mb64_grid_data[pos[0]][pos[1]][pos[2]].waterlogged = 0;  \
}

#define remove_terrain_data(pos) {                         \
    mb64_grid_data[pos[0]][pos[1]][pos[2]].rot = 0;         \
    mb64_grid_data[pos[0]][pos[1]][pos[2]].type = 0; \
    mb64_grid_data[pos[0]][pos[1]][pos[2]].mat = 0;         \
    mb64_grid_data[pos[0]][pos[1]][pos[2]].waterlogged = 0; \
}

s32 tile_sanity_check(void);
u32 shift_tile_data_indices(u32 tiletypeIndex);
u32 is_cull_marker_useless(s8 pos[3]);
u32 get_tiletype_index(u32 type, u32 mat);
u32 get_tile_occupy_flags(u32 type);
void place_tile(s8 pos[3]);
void place_water(s8 pos[3]);
void delete_useless_cull_markers(void);
