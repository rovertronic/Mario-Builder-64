#ifndef cursed_mirror_maker_h
#define cursed_mirror_maker_h

#define CMM_VERSION 1

void sb_loop(void);
void sb_init(void);
void cmm_init();
void draw_cmm_menu(void);
void generate_objects_to_level(void);
Gfx *ccm_append(s32 callContext, UNUSED struct GraphNode *node, UNUSED Mat4 mtx);
s32 cmm_main_menu(void);
extern Gfx cmm_terrain_gfx[23000];
extern Trajectory cmm_trajectory_list[5][160];
extern u8 cmm_mode;
extern u8 cmm_target_mode;
extern Vec3f cmm_camera_pos;
extern Vec3f cmm_camera_foc;

extern u16 painting_rgba16[32][32];
extern u8 cmm_lopt_envfx;
extern u8 cmm_envfx_table[];

//play mode stuff
extern u8 cmm_play_stars;
extern u8 cmm_play_stars_max;
extern u32 cmm_play_stars_bitfield;
extern u32 cmm_play_badge_bitfield;


#define CMM_TILE_POOL_SIZE 5000
#define CMM_GFX_SIZE 23000
#define CMM_GFX_TP_SIZE 8000
#define CMM_VTX_SIZE 100000

#define TILE_SIZE 256


enum cmm_directions {
    CMM_DIRECTION_UP,
    CMM_DIRECTION_DOWN,
    CMM_DIRECTION_POS_X,
    CMM_DIRECTION_NEG_X,
    CMM_DIRECTION_POS_Z,
    CMM_DIRECTION_NEG_Z,

    CMM_NO_CULLING,
};

#define CMM_GRID_FLAG_OCCUPIED (1 << 7)
#define CMM_GRID_MASK_ROT   (0x3 << 5)
#define CMM_GRID_SHIFT_ROT  (5)
#define CMM_GRID_MASK_TILETYPE  (0x1F)

enum cmm_culling_shapes {
    CMM_FACESHAPE_FULL,
    CMM_FACESHAPE_TOPTRI,

    CMM_FACESHAPE_TRI_1, // make sure irregular shapes can be flipped with ^1
    CMM_FACESHAPE_TRI_2,
    CMM_FACESHAPE_DOWNTRI_1,
    CMM_FACESHAPE_DOWNTRI_2,

    CMM_FACESHAPE_EMPTY,
};

enum cmm_growth_types {
    CMM_GROWTH_NONE,
    CMM_GROWTH_FULL,
    CMM_GROWTH_NORMAL_SIDE,
    CMM_GROWTH_UNDERSLOPE, // act as if it was positive Z
    CMM_GROWTH_DIAGONAL_SIDE,
    CMM_GROWTH_SLOPE_SIDE_L,
    CMM_GROWTH_SLOPE_SIDE_R,
};

struct cmm_terrain_quad {
    s8 vtx[4][3];
    u8 uvProjDir;
    u8 cullDir;
    u8 faceshape;
    u8 growthType;
    s8 (*decaluvs)[3][2];
};
struct cmm_terrain_tri {
    s8 vtx[3][3];
    u8 uvProjDir;
    u8 cullDir;
    u8 faceshape;
    u8 growthType;
    s8 (*decaluvs)[3][2];
};
struct cmm_terrain_block {
    u8 numQuads;
    u8 numTris;
    struct cmm_terrain_quad * quads;
    struct cmm_terrain_tri * tris;
};

struct cmm_tile {
    u8 x:5, y:5, z:5, type:5, mat:4, rot:2;
};
struct cmm_tile_type_struct {
    Gfx * model;
    struct cmm_terrain_block *terrain;
    u32 * collision_data;
    u8 transparent:1;
};
enum {
    TILE_TYPE_BLOCK,
    TILE_TYPE_SLOPE,
    TILE_TYPE_CORNER,
    TILE_TYPE_ICORNER,
    TILE_TYPE_TROLL,
    TILE_TYPE_CULL,
    TILE_TYPE_DSLOPE,
    TILE_TYPE_WATER,
    TILE_TYPE_FENCE,
    TILE_TYPE_SSLOPE,
};

struct cmm_obj {
    u8 param, x:5, y:5, z:5, type:5, rot:2;
};

struct cmm_grid_obj {
    u8 type:5, mat:4, rot:2, occupied:1;
};
struct cmm_object_type_struct {
    u32 behavior;
    f32 y_offset;
    u16 model_id;
    u8 billboarded:1;
    u8 use_trajectory:1;
    f32 scale;
    struct Animation **anim;
    s16 param_max;
    void (* disp_func)(struct Object *,int);
};
enum {
    OBJECT_TYPE_STAR,
    OBJECT_TYPE_GOOMBA,
    OBJECT_TYPE_COIN,
    OBJECT_TYPE_GCOIN,
    OBJECT_TYPE_RCOIN,
    OBJECT_TYPE_BCOIN,
    OBJECT_TYPE_BCS,//BLUE COIN SWITCH (not better call saul)
    OBJECT_TYPE_RCS,//RED COIN STAR
    OBJECT_TYPE_NOTE,
    OBJECT_TYPE_PODOB,
    OBJECT_TYPE_REX,
    OBJECT_TYPE_BULLY,
    OBJECT_TYPE_BOMB,
    OBJECT_TYPE_TREE,
    OBJECT_TYPE_EXCLA,
    OBJECT_TYPE_CHUCKYA,
    OBJECT_TYPE_SPAWN,
    OBJECT_TYPE_PHNTSM,
    OBJECT_TYPE_PIPE,
    OBJECT_TYPE_BADGE,
    OBJECT_TYPE_BOSS,
    OBJECT_TYPE_MPLAT,
    OBJECT_TYPE_BBALL,
    OBJECT_TYPE_KTQ,
};

struct cmm_ui_button_type {
    Gfx * material;
    u8 id;
    u8 isTile:1;
    u8 * str;
    u8 ** param_strings;
};

struct cmm_settings_button {
    u8 * str;
    u8 * value;
    u8 ** nametable;
    u8 size;
};

//static_assert(sizeof(cmm_tile_type_struct) == 4,"tile is not u32 sized, FIX NOW!")

enum {
    CMM_MODE_PLAY,
    CMM_MODE_MAKE,
    CMM_MODE_UNINITIALIZED,
};

enum {
    CMM_MAKE_MAIN,
    CMM_MAKE_TOOLBOX,
    CMM_MAKE_SETTINGS,
    CMM_MAKE_TRAJECTORY,
};

enum {
    CMM_BUTTON_SAVE,
    CMM_BUTTON_SETTINGS,
    CMM_BUTTON_PLAY,
    CMM_BUTTON_TERRAIN,
    CMM_BUTTON_SLOPE,
    CMM_BUTTON_TROLL,
    CMM_BUTTON_STAR,
    CMM_BUTTON_GOOMBA,
    CMM_BUTTON_COIN,
    CMM_BUTTON_BLANK,
    CMM_BUTTON_GCOIN,
    CMM_BUTTON_CORNER,
    CMM_BUTTON_ICORNER,
    CMM_BUTTON_RCOIN,
    CMM_BUTTON_BCOIN,
    CMM_BUTTON_BCS,
    CMM_BUTTON_RCS,
    CMM_BUTTON_NOTEBLOCK,
    CMM_BUTTON_CULL,
    CMM_BUTTON_PODOBOO,
    CMM_BUTTON_REX,
    CMM_BUTTON_BULLY,
    CMM_BUTTON_BOMB,
    CMM_BUTTON_TREE,
    CMM_BUTTON_EXCLA,
    CMM_BUTTON_DSLOPE,
    CMM_BUTTON_CHUCKYA,
    CMM_BUTTON_SPAWN,
    CMM_BUTTON_PHANTASM,
    CMM_BUTTON_PIPE,
    CMM_BUTTON_BADGE,
    CMM_BUTTON_WATER,
    CMM_BUTTON_FENCE,
    CMM_BUTTON_BOSS,
    CMM_BUTTON_MPLAT,
    CMM_BUTTON_BBALL,
    CMM_BUTTON_KTQ,
    CMM_BUTTON_SSLOPE,
};

enum {
    CMM_PM_TILE,
    CMM_PM_OBJ,
};

#define NUM_THEMES 7
#define NUM_MATERIALS_PER_THEME 10

enum cmm_mat_types {
    MAT_OPAQUE,
    MAT_CUTOUT,
    MAT_TRANSPARENT,
};

// Represents a material texture and collision
struct cmm_material {
    Gfx *gfx;
    u8 type:2;
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
    u8 *name;
};
struct cmm_theme {
    struct cmm_tilemat_def mats[NUM_MATERIALS_PER_THEME];
};

//compressed trajectories
struct cmm_comptraj {
    u8 x:5, y:5, z:5;
    s8 t:7;
};


/*
IMPORTANT!

u8 version;
u16 piktcher[28][28];

Should always be the first 2 members of the cmm_level_save struct
no matter what version.
*/

struct cmm_level_save {
    u8 version;
    u16 piktcher[28][28]; //28*28 = 784*2 = 1568 bytes

    struct cmm_tile tiles[CMM_TILE_POOL_SIZE];//3*1500 = 4500 bytes
    struct cmm_obj objects[200];//4*200 = 800 bytes
    struct cmm_comptraj trajectories[5][40];
    u8 option[20];//20 bytes
    //6906 bytes per level, ~7000 bytes
    u16 tile_count;
    u16 object_count;
};

ALIGNED8 struct cmm_hack_save {
    struct cmm_level_save lvl[1];
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
};

extern u8 cmm_lopt_game;
enum {
    CMM_GAME_BTCM,
    CMM_GAME_VANILLA,
};

#endif