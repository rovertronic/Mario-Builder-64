#ifndef cursed_mirror_maker_h
#define cursed_mirror_maker_h
#include "libcart/ff/ff.h"

#define CMM_TILE_POOL_SIZE 10000
#define CMM_GFX_SIZE 20000
#define CMM_VTX_SIZE 25000

#define CMM_MAX_OBJS 512
#define CMM_MAX_TRAJECTORIES 20
#define CMM_TRAJECTORY_LENGTH 50

#define TILE_SIZE 256

#define CMM_VERSION 0

void save_level(void);
void sb_loop(void);
void sb_init(void);
void cmm_init();
void draw_cmm_menu(void);
void reset_play_state(void);
void generate_objects_to_level(void);
Gfx *cmm_append(s32 callContext, UNUSED struct GraphNode *node, UNUSED Mat4 mtx);
s32 cmm_main_menu(void);
extern Gfx cmm_terrain_gfx[CMM_GFX_SIZE];
extern Trajectory cmm_trajectory_list[CMM_MAX_TRAJECTORIES][CMM_TRAJECTORY_LENGTH][4];
void rotate_obj_toward_trajectory_angle(struct Object * obj, u32 traj_id);

extern u8 cmm_level_action;
extern u8 cmm_mode;
extern u8 cmm_target_mode;
extern Vec3f cmm_camera_pos;
extern Vec3f cmm_camera_foc;
extern f32 cmm_camera_fov;

extern u16 painting_rgba16[32][32];
extern u8 cmm_lopt_envfx;
extern u8 cmm_lopt_costume;
extern u8 cmm_envfx_table[];

//play mode stuff
extern u8 cmm_play_stars;
extern u8 cmm_play_stars_max;
extern u64 cmm_play_stars_bitfield;
extern u32 cmm_play_badge_bitfield;

extern struct cmm_level_save_header cmm_save;
extern TCHAR cmm_file_name[30];
extern char cmm_username[31];
extern u8 cmm_has_username;

extern void* cmm_theme_segments[][4];
extern LevelScript * cmm_theme_model_scripts[];

enum {
    CMM_PM_NONE,
    CMM_PM_TILE,
    CMM_PM_OBJ,
    CMM_PM_WATER,
};

#define GRID_TO_POS(gridx) ((gridx) * TILE_SIZE - (32 * TILE_SIZE) + TILE_SIZE/2)
#define POS_TO_GRID(pos) (((pos) + (32 * TILE_SIZE) - TILE_SIZE/2) / TILE_SIZE)

enum cmm_directions {
    CMM_DIRECTION_UP,
    CMM_DIRECTION_DOWN,
    CMM_DIRECTION_POS_X,
    CMM_DIRECTION_NEG_X,
    CMM_DIRECTION_POS_Z,
    CMM_DIRECTION_NEG_Z,
};

#define CMM_GRID_FLAG_OCCUPIED (1 << 7)
#define CMM_GRID_MASK_ROT   (0x3 << 5)
#define CMM_GRID_SHIFT_ROT  (5)
#define CMM_GRID_MASK_TILETYPE  (0x1F)

enum cmm_culling_shapes {
    CMM_FACESHAPE_FULL,
    CMM_FACESHAPE_POLETOP,

    CMM_FACESHAPE_TRI_1, // make sure irregular shapes can be flipped with ^1
    CMM_FACESHAPE_TRI_2,
    CMM_FACESHAPE_DOWNTRI_1,
    CMM_FACESHAPE_DOWNTRI_2,
    CMM_FACESHAPE_HALFSIDE_1,
    CMM_FACESHAPE_HALFSIDE_2,

    CMM_FACESHAPE_BOTTOMSLAB,
    CMM_FACESHAPE_TOPSLAB,
    CMM_FACESHAPE_TOPTRI,
    CMM_FACESHAPE_TOPHALF,

    CMM_FACESHAPE_EMPTY,
};

enum cmm_growth_types {
    CMM_GROWTH_NONE,
    CMM_GROWTH_FULL,
    CMM_GROWTH_NORMAL_SIDE,
    CMM_GROWTH_HALF_SIDE, // vertical slabs - either side
    CMM_GROWTH_UNDERSLOPE_CORNER, // special check
    CMM_GROWTH_DIAGONAL_SIDE,
    CMM_GROWTH_VSLAB_SIDE, // vertical slabs - middle face
    CMM_GROWTH_SLOPE_SIDE_L,
    CMM_GROWTH_SLOPE_SIDE_R,
    CMM_GROWTH_UNCONDITIONAL,
};

struct cmm_terrain_quad {
    s8 vtx[4][3];
    u8 faceDir;
    u8 faceshape;
    u8 growthType;
    s8 (*altuvs)[4][2];
};
struct cmm_terrain_tri {
    s8 vtx[3][3];
    u8 faceDir;
    u8 faceshape;
    u8 growthType;
    s8 (*altuvs)[3][2];
};

struct cmm_boundary_quad {
    s8 vtx[4][3];
    s8 u[2];
    s8 v[2];
    u8 uYScale; // Scale U by Y instead of width
    u8 vYScale; // Scale V by Y instead of width
    u8 flipUvs;
};

struct cmm_terrain {
    u8 numQuads;
    u8 numTris;
    struct cmm_terrain_quad * quads;
    struct cmm_terrain_tri * tris;
};

struct cmm_tile {
    u32 x:6, y:6, z:6, type:5, mat:4, rot:2, waterlogged:1;
};

enum {
    TILE_TYPE_BLOCK,
    TILE_TYPE_SLOPE,
    TILE_TYPE_CORNER,
    TILE_TYPE_ICORNER,
    TILE_TYPE_DCORNER,
    TILE_TYPE_DICORNER,
    TILE_TYPE_DSLOPE,
    TILE_TYPE_SSLOPE,
    TILE_TYPE_SLAB,
    TILE_TYPE_DSLAB,
    TILE_TYPE_SSLAB,
    TILE_TYPE_CULL,
    TILE_TYPE_TROLL,
    TILE_TYPE_FENCE,
    TILE_TYPE_POLE,
    TILE_TYPE_BARS,

    TILE_TYPE_WATER, // only blocks that are empty otherwise
};

struct cmm_obj {
    u32 param1:1, param2:7, x:6, y:6, z:6, type:5, rot:2;
};

struct cmm_grid_obj {
    u16 type:5, mat:4, rot:2, occupied:1, waterlogged:1;
};

enum cmm_df_context {
    CMM_DF_CONTEXT_INIT,
    CMM_DF_CONTEXT_MAIN,
};

typedef void (*DisplayFunc)(s32);

struct cmm_object_info {
    const BehaviorScript *behavior;
    f32 y_offset;
    u16 model_id;
    u16 billboarded:1;
    u16 numCoins:4;
    u16 numExtraObjects:3;
    f32 scale;
    const struct Animation *const *anim;
    DisplayFunc disp_func;
    u32 soundBits;
};

struct cmm_object_place {
    struct cmm_object_info *info; // can be an array
    u8 useTrajectory:1;
    u8 hasStar:1;
    u8 multipleObjs:1;
    s8 maxParams;
};

struct ExclamationBoxContents {
    u8 behParams;
    ModelID16 model;
    const BehaviorScript *behavior;
    u8 animState; //not shitcum
    u8 doRespawn;
    u8 numCoins;
};

extern struct ExclamationBoxContents *cmm_exclamation_box_contents;

struct cmm_ui_button_type {
    Gfx *material;
    u8 multipleBtns;
    u8 id;
    u8 placeMode:2;
    char *str;
    char **param_strings;
};

struct cmm_settings_button {
    char *str;
    u8 *value;
    char **nametable;
    u8 size;
    char *(*nameFunc)(s32, char *);
    void (*changedFunc)(void);
};

enum {
    CMM_MODE_PLAY,
    CMM_MODE_MAKE,
    CMM_MODE_UNINITIALIZED,
};

enum {
    CMM_MAKE_MAIN,
    CMM_MAKE_PLAY,
    CMM_MAKE_TOOLBOX,
    CMM_MAKE_SETTINGS,
    CMM_MAKE_TRAJECTORY,
    CMM_MAKE_SCREENSHOT,
};

#define NUM_MATERIALS_PER_THEME 10

enum cmm_mat_types {
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

// Represents a material texture and collision
struct cmm_material {
    Gfx *gfx;
    u8 type;
    TerrainData col;
    char *name; // Only used for Custom Theme menu
};

// Represents a material as a top texture with optional side decal
struct cmm_topmaterial {
    u8 mat;
    Gfx *decaltex;
};

// Defines materials of a full block
struct cmm_tilemat_def {
    u8 mat;
    u8 topmat;
    char *name;
};
struct cmm_theme {
    struct cmm_tilemat_def mats[NUM_MATERIALS_PER_THEME];
    u8 fence;
    u8 pole;
    u8 bars;
    u8 water;
};

struct cmm_custom_theme {
    u8 mats[NUM_MATERIALS_PER_THEME];
    u8 topmats[NUM_MATERIALS_PER_THEME];
    u8 topmatsEnabled[NUM_MATERIALS_PER_THEME];
    u8 fence;
    u8 pole;
    u8 bars;
    u8 water;
};

//compressed trajectories
struct cmm_comptraj {
    s8 t;
    u8 x;
    u8 y;
    u8 z;
};

/*
IMPORTANT!

char file_header[10];
u8 version;
char author[31];
u16 piktcher[64][64];

Should always be the first 2 members of the cmm_level_uncompressed_save struct
no matter what version.
*/

struct cmm_level_save_header {
    char file_header[10];
    u8 version;
    char author[31];

    // Level options
    u8 costume;
    u8 seq;
    u8 envfx;
    u8 theme;
    u8 bg;
    u8 boundary_mat;
    u8 boundary;
    u8 boundary_height;
    u8 coinstar;
    u8 size;
    u8 waterlevel;
    u8 secret;
    u8 game;

    u8 padding[20];
    u16 tile_count;
    u16 object_count;

    struct cmm_custom_theme custom_theme;

    struct cmm_comptraj trajectories[CMM_MAX_TRAJECTORIES][CMM_TRAJECTORY_LENGTH];

    u16 piktcher[64][64];

    u64 pad;
};

struct cmm_level_uncompressed_save {
    struct cmm_level_save_header header;
    struct cmm_tile tiles[CMM_TILE_POOL_SIZE];
    struct cmm_obj objects[CMM_MAX_OBJS];
};

#define SRAM_MAGIC 0x0203DD10 // Rovert's favorite binary ROM Address!

struct cmm_sram_config {
    char author[31];
    u32 magic;
};

enum {
    MM_INIT,
    MM_NO_SD_CARD,
    MM_MAIN,
    MM_MAIN_LIMITED,
    MM_HELP,
    MM_HELP_MODE,
    MM_CREDITS,
    MM_PLAY,
    MM_MAKE,
    MM_KEYBOARD,
    MM_FILES,
    MM_MAKE_MODE,
};

enum {
    KXM_NEW_LEVEL,
    KXM_NEW_LEVEL_LIMITED,
    KXM_AUTHOR,
    KXM_CHANGE_AUTHOR,
};

extern u8 cmm_lopt_game;
enum {
    CMM_GAME_VANILLA,
    CMM_GAME_BTCM,
};

enum {
    CMM_LA_PLAY_LEVELS,
    CMM_LA_BUILD,
};

enum cmm_themes {
    CMM_THEME_GENERIC,
    CMM_THEME_SSL,
    CMM_THEME_RHR,
    CMM_THEME_HMC,
    CMM_THEME_CASTLE,
    CMM_THEME_VIRTUAPLEX,
    CMM_THEME_SNOW,
    CMM_THEME_BBH,
    CMM_THEME_JRB,
    CMM_THEME_RETRO,
    CMM_THEME_CUSTOM,
    CMM_THEME_MC,
};

#endif