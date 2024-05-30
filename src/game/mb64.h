#ifndef mb64_h
#define mb64_h
#include "libcart/ff/ff.h"

#define MB64_TILE_POOL_SIZE 15000
#define MB64_GFX_SIZE 15000
#define MB64_VTX_SIZE 50000

#define MB64_MAX_OBJS 512
#define MB64_MAX_TRAJECTORIES 20
#define MB64_TRAJECTORY_LENGTH 50

#define TILE_SIZE 256

#define MB64_VERSION 1
#define MAX_FILE_NAME_SIZE 41
#define MAX_USERNAME_SIZE 31

void save_level(void);
void sb_loop(void);
void sb_init(void);
void mb64_init();
void draw_mb64_menu(void);
void reset_play_state(void);
void generate_objects_to_level(void);
Gfx *mb64_append(s32 callContext, UNUSED struct GraphNode *node, UNUSED Mat4 mtx);
s32 mb64_main_menu(void);
extern Gfx mb64_terrain_gfx[MB64_GFX_SIZE];
extern Trajectory mb64_trajectory_list[MB64_MAX_TRAJECTORIES][MB64_TRAJECTORY_LENGTH][4];
void rotate_obj_toward_trajectory_angle(struct Object * obj, u32 traj_id);
s32 draw_mb64_pause_menu(void);
void mb64_init_pause_menu(void);
void play_mb64_extra_music(u8 index);
void stop_mb64_extra_music(u8 index);

extern u8 mb64_level_action;
extern u8 mb64_mode;
extern u8 mb64_target_mode;
extern Vec3f mb64_camera_pos;
extern Vec3f mb64_camera_foc;
extern f32 mb64_camera_fov;

extern u16 painting_rgba16[32][32];
extern u8 mb64_lopt_envfx;
extern u8 mb64_lopt_costume;
extern u8 mb64_envfx_table[];

//play mode stuff
extern u8 mb64_play_stars;
extern u8 mb64_play_stars_max;
extern u64 mb64_play_stars_bitfield;
extern u32 mb64_play_badge_bitfield;
extern u8 mb64_play_onoff;
extern s16 mb64_play_s16_water_level;
extern u32 mb64_play_speedrun_timer;

extern struct mb64_level_save_header mb64_save;
extern TCHAR mb64_file_name[MAX_FILE_NAME_SIZE];
extern char mb64_username[MAX_USERNAME_SIZE];
extern u8 mb64_has_username;

extern void* mb64_theme_segments[][4];
extern LevelScript * mb64_theme_model_scripts[];

enum {
    MB64_PM_NONE,
    MB64_PM_TILE,
    MB64_PM_OBJ,
    MB64_PM_WATER,
};

#define GRID_TO_POS(gridx) ((gridx) * TILE_SIZE - (32 * TILE_SIZE) + TILE_SIZE/2)
#define POS_TO_GRID(pos) (((pos) + (32 * TILE_SIZE) - TILE_SIZE/2) / TILE_SIZE)

enum mb64_directions {
    MB64_DIRECTION_UP,
    MB64_DIRECTION_DOWN,
    MB64_DIRECTION_POS_X,
    MB64_DIRECTION_NEG_X,
    MB64_DIRECTION_POS_Z,
    MB64_DIRECTION_NEG_Z,
};

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
    MB64_FACESHAPE_EMPTY,

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
};

enum mb64_growth_types {
    MB64_GROWTH_NONE,
    MB64_GROWTH_FULL,
    MB64_GROWTH_NORMAL_SIDE,
    MB64_GROWTH_HALF_SIDE, // vertical slabs - either side
    MB64_GROWTH_UNDERSLOPE_CORNER, // special check
    MB64_GROWTH_DIAGONAL_SIDE,
    MB64_GROWTH_VSLAB_SIDE, // vertical slabs - middle face
    MB64_GROWTH_DLGENTLE_UNDER, // special check
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

struct mb64_terrain_poly {
    s8 vtx[4][3];
    u8 faceDir;
    u8 faceshape;
    u8 growthType;
    s8 (*altuvs)[4][2];
};

struct mb64_boundary_quad {
    s8 vtx[4][3];
    s8 u[2];
    s8 v[2];
    u8 uYScale; // Scale U by Y instead of width
    u8 vYScale; // Scale V by Y instead of width
    u8 flipUvs;
};

struct mb64_terrain {
    u8 numQuads;
    u8 numTris;
    struct mb64_terrain_poly * quads;
    struct mb64_terrain_poly * tris;
};

struct mb64_tile {
    u32 x:6, y:6, z:6, type:5, mat:4, rot:2, waterlogged:1;
};

struct mb64_obj {
    u8 bparam;
    u8 x;
    u8 y;
    u8 z;
    u8 type;
    u8 rot;
    u8 imbue;
    u8 pad;
};

struct mb64_grid_obj {
    u16 type:5, mat:4, rot:2, waterlogged:1;
};

enum mb64_df_context {
    MB64_DF_CONTEXT_INIT,
    MB64_DF_CONTEXT_MAIN,
};

typedef void (*DisplayFunc)(s32);

#define OBJ_TYPE_IS_BILLBOARDED (1 << 0)
#define OBJ_TYPE_TRAJECTORY     (1 << 1)
#define OBJ_TYPE_HAS_STAR       (1 << 2)
#define OBJ_TYPE_HAS_DIALOG     (1 << 3)
#define OBJ_TYPE_IMBUABLE       (1 << 4)
#define OBJ_TYPE_IMBUABLE_COINS (1 << 5)
struct mb64_object_info {
    char *name;
    Gfx *btn;
    const BehaviorScript *behavior;
    f32 y_offset;
    u16 model_id;
    u16 flags:6;
    u16 numCoins:4;
    u16 numExtraObjects:3;
    f32 scale;
    const struct Animation *const *anim;
    DisplayFunc disp_func;
    u32 soundBits;
};

struct ExclamationBoxContents {
    u8 behParams;
    ModelID16 model;
    const BehaviorScript *behavior;
    u8 animState; //not shitcum
    u8 doRespawn;
    u8 numCoins;
};

extern struct ExclamationBoxContents *mb64_exclamation_box_contents;

struct mb64_ui_button_type {
    u32 placeMode:2;
    u32 multiObj:1;
    u32 paramCount:8;

    union {
        u32 id;
        u8 *idList;
    };
    union {
        char *name;
        char **names;
    };
};

struct mb64_settings_button {
    char *str;
    u8 *value;
    char **nametable;
    u8 size;
    char *(*nameFunc)(s32, char *);
    void (*changedFunc)(void);
};

enum {
    MB64_MODE_PLAY,
    MB64_MODE_MAKE,
    MB64_MODE_UNINITIALIZED,
};

enum {
    MB64_MAKE_MAIN,
    MB64_MAKE_PLAY,
    MB64_MAKE_TOOLBOX,
    MB64_MAKE_SETTINGS,
    MB64_MAKE_TRAJECTORY,
    MB64_MAKE_SCREENSHOT,
    MB64_MAKE_SELECT_DIALOG,
};

#define NUM_MATERIALS_PER_THEME 10

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

// Represents a material texture and collision
struct mb64_material {
    Gfx *gfx;
    u8 type;
    TerrainData col;
    char *name; // Only used for Custom Theme menu
};

// Represents a material as a top texture with optional side decal
struct mb64_topmaterial {
    u8 mat;
    Gfx *decaltex;
};

// Defines materials of a full block
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

//compressed trajectories
struct mb64_comptraj {
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

Should always be the first 2 members of the mb64_level_save_header struct
no matter what version.
*/

struct mb64_level_save_header {
    char file_header[10];
    u8 version;
    char author[MAX_USERNAME_SIZE];
    u16 piktcher[64][64];

    // Level options
    u8 costume;
    u8 seq[5];
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

    u8 toolbar[9];
    u8 toolbar_params[9];
    u16 tile_count;
    u16 object_count;

    struct mb64_custom_theme custom_theme;

    struct mb64_comptraj trajectories[MB64_MAX_TRAJECTORIES][MB64_TRAJECTORY_LENGTH];

    u64 pad;
};

#define SRAM_MAGIC 0x0203DD10 // Rovert's favorite binary ROM Address!

struct mb64_sram_config {
    char author[MAX_USERNAME_SIZE];
    u8 option_flags;
    u32 magic;
    u64 pad;
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

extern u8 mb64_lopt_game;
enum {
    MB64_GAME_VANILLA,
    MB64_GAME_BTCM,
};

enum {
    MB64_LA_PLAY_LEVELS,
    MB64_LA_BUILD,
    MB64_LA_TEST_LEVEL,
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

struct mb64_dialog_topic {
    char * name;
    u8 dialog_id;
};

struct mb64_dialog_subject {
    char * name;
    struct mb64_dialog_topic * topic_list;
    u8 topic_list_size;
};

enum imbue {
    IMBUE_NONE,
    IMBUE_STAR,
    IMBUE_THREE_COINS,
    IMBUE_FIVE_COINS,
    IMBUE_EIGHT_COINS,
    IMBUE_BLUE_COIN,
    IMBUE_RED_SWITCH,
    IMBUE_BLUE_SWITCH,
    IMBUE_RED_COIN,
};

#endif