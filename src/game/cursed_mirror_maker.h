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
extern Gfx cmm_terrain_gfx[15000];
extern Gfx cmm_terrain_gfx_tdecal[8000];
extern u16 cmm_trajectory_list[5][160];
extern u8 cmm_mode;
extern u8 cmm_target_mode;
extern Vec3f cmm_camera_pos;
extern Vec3f cmm_camera_foc;

extern u16 painting_rgba16[32][32];
extern u8 cmm_lopt_envfx;
extern u8 cmm_envfx_table[];


struct cmm_tile {
    u8 x:5, y:5, z:5, type:5, rot:2;
};
struct cmm_tile_type_struct {
    Gfx * model;
    Gfx * material;
    u32 * collision_data;
    u8 growth:1;
    u8 transparent:1;
};
enum {
    TILE_TYPE_TERRAIN,
    TILE_TYPE_BRICK,
    TILE_TYPE_STONE,
    TILE_TYPE_WOOD,
    TILE_TYPE_LAVA,
    TILE_TYPE_SLOPE,
    TILE_TYPE_CORNER,
    TILE_TYPE_ICORNER,
    TILE_TYPE_TROLL,
    TILE_TYPE_CULL,
    TILE_TYPE_SNOW,
    TILE_TYPE_DSLOPE,
    TILE_TYPE_WATER,
    TILE_TYPE_FENCE,
};

struct cmm_obj {
    u8 param, x:5, y:5, z:5, type:5, rot:2;
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
    CMM_BUTTON_BRICK,
    CMM_BUTTON_LAVA,
    CMM_BUTTON_SLOPE,
    CMM_BUTTON_TROLL,
    CMM_BUTTON_STAR,
    CMM_BUTTON_GOOMBA,
    CMM_BUTTON_COIN,
    CMM_BUTTON_BLANK,
    CMM_BUTTON_WOOD,
    CMM_BUTTON_STONE,
    CMM_BUTTON_GCOIN,
    CMM_BUTTON_CORNER,
    CMM_BUTTON_ICORNER,
    CMM_BUTTON_RCOIN,
    CMM_BUTTON_BCOIN,
    CMM_BUTTON_BCS,
    CMM_BUTTON_RCS,
    CMM_BUTTON_NOTEBLOCK,
    CMM_BUTTON_CULL,
    CMM_BUTTON_SNOW,
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
};

enum {
    CMM_PM_TILE,
    CMM_PM_OBJ,
};

enum {
    CMM_THEME_GENERIC,
    CMM_THEME_CASTLE,
    CMM_THEME_DESERT,
    CMM_THEME_CAVE,
    CMM_THEME_VIRTUAPLEX,
    CMM_THEME_RED_HOT_RESERVOIR,
    CMM_THEME_RETRO,
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

    struct cmm_tile tiles[2000];//3*1500 = 4500 bytes
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