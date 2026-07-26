#pragma once

#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include "types.h"
#include "mb64/mb64.h"
#include "mb64/editor/grid.h"
#include "mb64/gfx/batch.h"
#include "mb64/gfx/cull.h"

struct mb64_material {
    Gfx *gfx;
    u8 type;
    u8 vertical;
    TerrainData col;
    char *name;
};

struct mb64_topmaterial {
    u8 mat;
    Gfx *decaltex;
};

struct mb64_tilemat_def {
    u8 mat;
    u8 topmat;
    char *name;
};

struct mb64_theme {
    struct mb64_tilemat_def mats[NUM_MATERIALS_PER_THEME];
    u8 fence;
    u8 pole;
    u8 bars;
    u8 water;
};

struct mb64_custom_theme {
    u8 mats[NUM_MATERIALS_PER_THEME];
    u8 topmats[NUM_MATERIALS_PER_THEME];
    u8 topmatsEnabled[NUM_MATERIALS_PER_THEME];
    u8 fence;
    u8 pole;
    u8 bars;
    u8 water;
};

enum mb64_directions {
    MB64_DIRECTION_UP,
    MB64_DIRECTION_DOWN,
    MB64_DIRECTION_POS_X,
    MB64_DIRECTION_NEG_X,
    MB64_DIRECTION_POS_Z,
    MB64_DIRECTION_NEG_Z,
};

enum mb64_themes {
    MB64_THEME_GENERIC,
    MB64_THEME_SSL,
    MB64_THEME_RHR,
    MB64_THEME_HMC,
    MB64_THEME_CASTLE,
    MB64_THEME_VIRTUAPLEX,
    MB64_THEME_SNOW,
    MB64_THEME_BBH,
    MB64_THEME_JRB,
    MB64_THEME_RETRO,
    MB64_THEME_CUSTOM,
    MB64_THEME_MC,
};

extern Bool32 gIsGliden;

struct mb64_boundary_quad;

struct mb64_terrain_poly {
    s8 vtx[4][3];
    u8 faceDir;
    u8 faceshape;
    u8 growthType;
    s8 (*altuvs)[][2];
};

struct mb64_terrain {
    u8 numQuads;
    u8 numTris;
    struct mb64_terrain_poly * quads;
    struct mb64_terrain_poly * tris;
};

struct mb64_terrain_info {
    char *name;
    Gfx *button;
    struct mb64_terrain *terrain;
};

enum mb64_growth_types {
    MB64_GROWTH_NONE,
    MB64_GROWTH_FULL,
    MB64_GROWTH_NORMAL_SIDE,
    MB64_GROWTH_HALF_SIDE, // vertical slabs - either side
    MB64_GROWTH_UNDERSLOPE_CORNER, // special check
    MB64_GROWTH_DIAGONAL_SIDE,
    MB64_GROWTH_VSLAB_SIDE, // vertical slabs - middle face
    MB64_GROWTH_UNCONDITIONAL,

    // Anything beyond this is a slope decal type
    // & 1 - left or right side
    // & 2 - gentle or steep
    MB64_GROWTH_EXTRADECAL_START = 0x10,
    MB64_GROWTH_SLOPE_SIDE_L = MB64_GROWTH_EXTRADECAL_START,
    MB64_GROWTH_SLOPE_SIDE_R,
    MB64_GROWTH_GENTLE_SIDE_L,
    MB64_GROWTH_GENTLE_SIDE_R,
};

enum ProcessTileRenderModes {
    PROCESS_TILE_NORMAL,
    PROCESS_TILE_TRANSPARENT,
    PROCESS_TILE_BOTH,
    PROCESS_TILE_VPLEX,
};

enum mb64_mat_types {
    // Opaque types (for culling)
    MAT_OPAQUE,
    MAT_DECAL, // only used for VP screen when used as a block type
    // Transparent types
    MAT_CUTOUT,
    MAT_CUTOUT_NOCULL,
    MAT_TRANSPARENT,
    // Used for override when processing vplex screens
    MAT_SCREEN,
};

extern void *slope_decal_below_surfs[];
extern struct mb64_terrain_poly mb64_terrain_fullblock_quads[];
extern struct mb64_terrain mb64_terrain_fullblock;
extern struct mb64_terrain_poly mb64_terrain_bars_connected_quads[];
extern struct mb64_terrain_poly mb64_terrain_bars_unconnected_quad[];
extern struct mb64_terrain_poly mb64_terrain_bars_center_quads[];
extern struct mb64_terrain mb64_terrain_pole;
extern struct mb64_terrain mb64_terrain_fence;
extern struct mb64_terrain mb64_terrain_fence_col;
extern struct mb64_terrain_poly *mb64_terrain_water_quadlists[];
extern struct mb64_terrain_info mb64_terrain_info_list[];

extern u8 mb64_matlist[];
extern struct mb64_material mb64_mat_table[];
extern u32 mb64_render_mode_table[];
extern struct mb64_theme mb64_theme_table[];
extern struct mb64_custom_theme mb64_default_custom;
extern struct mb64_custom_theme mb64_curr_custom_theme;

extern Gfx *mb64_fence_texs[];
extern Gfx *mb64_bar_texs[][2];
extern Gfx *mb64_water_texs[];
extern struct mb64_topmaterial mb64_topmat_table[19];

// Returns full tile definition (struct mb64_tilemat_def)
#define TILE_MATDEF(matid) (mb64_theme_table[mb64_lopt_theme].mats[matid])
// Returns main material (struct mb64_material)
#define MATERIAL(matid) (mb64_mat_table[TILE_MATDEF(matid).mat])

// Returns TRUE if given material has a unique top texture
#define HAS_TOPMAT(matid) (TILE_MATDEF(matid).topmat != TILE_MATDEF(matid).mat)
// Returns top material's topmat struct (struct mb64_material)
#define TOPMAT(matid) (mb64_mat_table[TILE_MATDEF(matid).topmat])

#define fullblock_can_be_waterlogged(mat) ((MATERIAL(mat).type == MAT_CUTOUT) || (TOPMAT(mat).type == MAT_CUTOUT))

#define FENCE_TEX() (mb64_fence_texs[mb64_theme_table[mb64_lopt_theme].fence])
#define POLE_TEX()  (mb64_mat_table[mb64_theme_table[mb64_lopt_theme].pole].gfx)
#define BARS_TEX() (mb64_bar_texs[mb64_theme_table[mb64_lopt_theme].bars][0])
#define BARS_TOPTEX() (mb64_bar_texs[mb64_theme_table[mb64_lopt_theme].bars][1])
#define WATER_TEX() (mb64_water_texs[mb64_theme_table[mb64_lopt_theme].water])

#define retroland_filter_on() if ((mb64_lopt_theme == MB64_THEME_RETRO) || (mb64_lopt_theme == MB64_THEME_MC)) { gDPSetTextureFilter(&mb64_curr_gfx[mb64_gfx_index++], G_TF_POINT); if (!gIsGliden) {mb64_uv_offset = 0;} }
#define retroland_filter_off() if ((mb64_lopt_theme == MB64_THEME_RETRO) || (mb64_lopt_theme == MB64_THEME_MC)) { gDPSetTextureFilter(&mb64_curr_gfx[mb64_gfx_index++], G_TF_BILERP); mb64_uv_offset = (mb64_lopt_theme == MB64_THEME_MC ? -32 : -16); }

extern u8 mb64_use_alt_uvs;
extern s8 mb64_uv_offset;
extern u8 mb64_render_flip_normals;
extern u8 mb64_render_vertical;
extern u8 mb64_growth_render_type;
extern u8 mb64_curr_mat_has_topside;
extern u8 mb64_curr_poly_vert_count;

void mb64_transform_vtx_with_rot(s8 v[][3], s8 oldv[][3], u32 rot);
void check_bar_connections(s8 pos[3], u8 connections[5]);
void render_bars_side(s8 pos[3], u8 connections[5]);
void render_bars_top(s8 pos[3], u8 connections[5]);
u32 is_water_fullblock(s8 pos[3]);
void process_tile(s8 pos[3], struct mb64_terrain *terrain, u32 rot);
void render_boundary_quad(struct mb64_boundary_quad *quad, s16 y, s16 yHeight, u32 fade);
void set_render_mode(u32 tileType, u32 disableZ);
u32 do_process(u8 *targetMatType, u32 processTileRenderMode);
Gfx *get_sidetex(s32 matid);
void render_water(s8 pos[3]);
void process_tiles(u32 processTileRenderMode);
