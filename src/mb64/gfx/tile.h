#pragma once

#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include "types.h"
#include "mb64/editor/grid.h"
#include "mb64/gfx/mb64_buttons.h"

enum mb64_materials {
    MB64_MATLIST_START,

    // Terrain
    MB64_MAT_GRASS = MB64_MATLIST_START,
    MB64_MAT_GRASS_OLD,
    MB64_MAT_CARTOON_GRASS,
    MB64_MAT_DARK_GRASS,
    MB64_MAT_HMC_GRASS,
    MB64_MAT_ORANGE_GRASS,
    MB64_MAT_RED_GRASS,
    MB64_MAT_PURPLE_GRASS,
    MB64_MAT_SAND,
    MB64_MAT_JRB_SAND,
    MB64_MAT_SNOW,
    MB64_MAT_SNOW_OLD,

    MB64_MAT_DIRT,
    MB64_MAT_SANDDIRT,
    MB64_MAT_LIGHTDIRT,
    MB64_MAT_HMC_DIRT,
    MB64_MAT_ROCKY_DIRT,
    MB64_MAT_DIRT_OLD,
    MB64_MAT_WAVY_DIRT,
    MB64_MAT_WAVY_DIRT_BLUE,
    MB64_MAT_SNOWDIRT,
    MB64_MAT_PURPLE_DIRT,
    MB64_MAT_HMC_LAKEGRASS,

    MB64_MATLIST_TERRAIN_END,

    // Stone
    MB64_MAT_STONE = MB64_MATLIST_TERRAIN_END,
    MB64_MAT_HMC_STONE,
    MB64_MAT_HMC_MAZEFLOOR,
    MB64_MAT_CCM_ROCK,
    MB64_MAT_TTM_FLOOR,
    MB64_MAT_TTM_ROCK,
    MB64_MAT_COBBLESTONE,
    MB64_MAT_JRB_WALL,
    MB64_MAT_GABBRO,
    MB64_MAT_RHR_STONE,
    MB64_MAT_LAVA_ROCKS,
    MB64_MAT_VOLCANO_WALL,
    MB64_MAT_RHR_BASALT,
    MB64_MAT_OBSIDIAN,
    MB64_MAT_CASTLE_STONE,
    MB64_MAT_JRB_UNDERWATER,
    MB64_MAT_SNOW_ROCK,
    MB64_MAT_ICY_ROCK,
    MB64_MAT_DESERT_STONE,
    MB64_MAT_RHR_OBSIDIAN,
    MB64_MAT_JRB_STONE,

    MB64_MATLIST_STONE_END,

    // Bricks
    MB64_MAT_BRICKS = MB64_MATLIST_STONE_END,
    MB64_MAT_DESERT_BRICKS,
    MB64_MAT_RHR_BRICK,
    MB64_MAT_HMC_BRICK,
    MB64_MAT_LIGHTBROWN_BRICK,
    MB64_MAT_WDW_BRICK,
    MB64_MAT_TTM_BRICK,
    MB64_MAT_C_BRICK,
    MB64_MAT_BBH_BRICKS,
    MB64_MAT_ROOF_BRICKS,
    MB64_MAT_C_OUTSIDEBRICK,
    MB64_MAT_SNOW_BRICKS,
    MB64_MAT_JRB_BRICKS,
    MB64_MAT_SNOW_TILE_SIDE,
    MB64_MAT_TILESBRICKS,

    MB64_MATLIST_BRICKS_END,

    // Tiling
    MB64_MAT_TILES = MB64_MATLIST_BRICKS_END,
    MB64_MAT_C_TILES,
    MB64_MAT_DESERT_TILES,
    MB64_MAT_VP_BLUETILES,
    MB64_MAT_SNOW_TILES,
    MB64_MAT_JRB_TILETOP,
    MB64_MAT_JRB_TILESIDE,
    MB64_MAT_HMC_TILES,
    MB64_MAT_GRANITE_TILES,
    MB64_MAT_RHR_TILES,
    MB64_MAT_VP_TILES,
    MB64_MAT_DIAMOND_PATTERN,
    MB64_MAT_C_STONETOP,
    MB64_MAT_SNOW_BRICK_TILES,

    MB64_MATLIST_TILES_END,

    // Cut Stone
    MB64_MAT_DESERT_BLOCK = MB64_MATLIST_TILES_END,
    MB64_MAT_VP_BLOCK,
    MB64_MAT_BBH_STONE,
    MB64_MAT_BBH_STONE_PATTERN,
    MB64_MAT_PATTERNED_BLOCK,
    MB64_MAT_HMC_SLAB,
    MB64_MAT_RHR_BLOCK,
    MB64_MAT_GRANITE_BLOCK,
    MB64_MAT_C_STONESIDE,
    MB64_MAT_C_PILLAR,
    MB64_MAT_BBH_PILLAR,
    MB64_MAT_RHR_PILLAR,

    MB64_MATLIST_CUTSTONE_END,

    // Wood
    MB64_MAT_WOOD = MB64_MATLIST_CUTSTONE_END,
    MB64_MAT_BBH_WOOD_FLOOR,
    MB64_MAT_BBH_WOOD_WALL,
    MB64_MAT_C_WOOD,
    MB64_MAT_JRB_WOOD,
    MB64_MAT_JRB_SHIPSIDE,
    MB64_MAT_JRB_SHIPTOP,
    MB64_MAT_BBH_HAUNTED_PLANKS,
    MB64_MAT_BBH_ROOF,
    MB64_MAT_SOLID_WOOD,
    MB64_MAT_RHR_WOOD,

    MB64_MATLIST_WOOD_END,

    // Metal
    MB64_MAT_BBH_METAL = MB64_MATLIST_WOOD_END,
    MB64_MAT_JRB_METALSIDE,
    MB64_MAT_JRB_METAL,
    MB64_MAT_C_BASEMENTWALL,
    MB64_MAT_DESERT_TILES2,
    MB64_MAT_VP_RUSTYBLOCK,

    MB64_MATLIST_METAL_END,

    // Buildings
    MB64_MAT_C_CARPET = MB64_MATLIST_METAL_END,
    MB64_MAT_C_WALL,
    MB64_MAT_ROOF,
    MB64_MAT_C_ROOF,
    MB64_MAT_SNOW_ROOF,
    MB64_MAT_BBH_WINDOW,
    MB64_MAT_HMC_LIGHT,
    MB64_MAT_VP_CAUTION,
    MB64_MAT_RR_BLOCKS,
    MB64_MAT_STUDDED_TILE,
    MB64_MAT_TTC_BLOCK,
    MB64_MAT_TTC_SIDE,
    MB64_MAT_TTC_WALL,
    MB64_MAT_FLOWERS,

    MB64_MATLIST_BUILDING_END,

    // Hazards
    MB64_MAT_LAVA = MB64_MATLIST_BUILDING_END,
    MB64_MAT_LAVA_OLD,
    MB64_MAT_SERVER_ACID,
    MB64_MAT_BURNING_ICE,
    MB64_MAT_QUICKSAND,
    MB64_MAT_DESERT_SLOWSAND,
    MB64_MAT_VP_VOID,

    MB64_MATLIST_HAZARD_END,

    // Transparent
    MB64_MAT_RHR_MESH = MB64_MATLIST_HAZARD_END,
    MB64_MAT_VP_MESH,
    MB64_MAT_HMC_MESH,
    MB64_MAT_BBH_MESH,
    MB64_MAT_PINK_MESH,
    MB64_MAT_TTC_MESH,
    MB64_MAT_ICE,
    MB64_MAT_CRYSTAL,
    MB64_MAT_VP_SCREEN,

    MB64_MATLIST_END,

    // Retro
    MB64_MAT_RETRO_GROUND = MB64_MATLIST_END,
    MB64_MAT_RETRO_BRICKS,
    MB64_MAT_RETRO_TREETOP,
    MB64_MAT_RETRO_TREEPLAT,
    MB64_MAT_RETRO_BLOCK,
    MB64_MAT_RETRO_BLUEGROUND,
    MB64_MAT_RETRO_BLUEBRICKS,
    MB64_MAT_RETRO_BLUEBLOCK,
    MB64_MAT_RETRO_WHITEBRICK,
    MB64_MAT_RETRO_LAVA,
    MB64_MAT_RETRO_UNDERWATERGROUND,

    // Minecraft
    MB64_MAT_MC_DIRT,
    MB64_MAT_MC_GRASS,
    MB64_MAT_MC_COBBLESTONE,
    MB64_MAT_MC_STONE,
    MB64_MAT_MC_OAK_LOG_TOP,
    MB64_MAT_MC_OAK_LOG_SIDE,
    MB64_MAT_MC_OAK_LEAVES,
    MB64_MAT_MC_WOOD_PLANKS,
    MB64_MAT_MC_SAND,
    MB64_MAT_MC_BRICKS,
    MB64_MAT_MC_LAVA,
    MB64_MAT_MC_FLOWING_LAVA,
    MB64_MAT_MC_GLASS,
};

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

enum mb64_culling_shapes {
    MB64_FACESHAPE_FULL,
    MB64_FACESHAPE_POLETOP,

    MB64_FACESHAPE_TRI_1, // make sure irregular shapes can be flipped with ^1
    MB64_FACESHAPE_TRI_2,
    MB64_FACESHAPE_DOWNTRI_1,
    MB64_FACESHAPE_DOWNTRI_2,
    MB64_FACESHAPE_HALFSIDE_1, // vertical slab sides
    MB64_FACESHAPE_HALFSIDE_2,

    MB64_FACESHAPE_TOPTRI,
    MB64_FACESHAPE_TOPHALF,

    // & 0x10: Bottom slab priority list
    MB64_FACESHAPE_BOTTOMSLAB_PRI = 0x10,
    MB64_FACESHAPE_UPPERGENTLE_1 = MB64_FACESHAPE_BOTTOMSLAB_PRI,
    MB64_FACESHAPE_UPPERGENTLE_2,
    MB64_FACESHAPE_BOTTOMSLAB,
    // 0x13 empty
    MB64_FACESHAPE_LOWERGENTLE_1 = MB64_FACESHAPE_BOTTOMSLAB_PRI + 4,
    MB64_FACESHAPE_LOWERGENTLE_2,

    // & 0x20: Top slab priority list
    MB64_FACESHAPE_TOPSLAB_PRI = 0x20,
    MB64_FACESHAPE_DOWNUPPERGENTLE_1 = MB64_FACESHAPE_TOPSLAB_PRI,
    MB64_FACESHAPE_DOWNUPPERGENTLE_2,
    MB64_FACESHAPE_TOPSLAB,
    // 0x23 empty
    MB64_FACESHAPE_DOWNLOWERGENTLE_1 = MB64_FACESHAPE_TOPSLAB_PRI + 4,
    MB64_FACESHAPE_DOWNLOWERGENTLE_2,

    // & 0x40: Empty faces
    MB64_FACESHAPE_EMPTY = 0x40,
    // Rotate UVs for certain textures
    MB64_FACESHAPE_EMPTY_0,
    MB64_FACESHAPE_EMPTY_1,
    MB64_FACESHAPE_EMPTY_2,
    MB64_FACESHAPE_EMPTY_3,
};

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
    const struct texture_define *button;
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
extern u8 mb64_render_culling_off;

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

u32 get_faceshape(s8 pos[3], u32 dir);
s32 get_mat(s8 pos[3]);
s32 cutout_skip_culling_check(s32 curMat, s32 otherMat, s32 direction);
u32 block_side_is_solid(s32 adjMat, s32 mat, s32 direction);
s32 should_cull(s8 pos[3], s32 direction, s32 faceshape, s32 rot);
s32 should_cull_topslab_check(s8 pos[3], s32 direction);
