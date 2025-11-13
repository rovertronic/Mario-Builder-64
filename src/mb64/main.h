#pragma once

#include "types.h"
#include "data.h"

#include "model_ids.h"
#include "seq_ids.h"
#include "sounds.h"
#include "surface_terrains.h"
#include "levels/scripts.h"
#include "game/level_geo.h"

#include "libcart/ff/ff.h"

#define MB64_TILE_POOL_SIZE 20000
#define MB64_GFX_SIZE 20000
#define MB64_VTX_SIZE 50000
#define MB64_MAX_TRAJECTORIES 20
#define MB64_TRAJECTORY_LENGTH 50

#define MB64_MAX_OBJS 512

#define MB64_SPEEDRUN_TIMER_MAX (30 * 60 * 100 - 1)

#define TILE_SIZE 256

#define MB64_VERSION 1
#define MAX_FILE_NAME_SIZE 41
#define MAX_FILE_NAME_INPUT (MAX_FILE_NAME_SIZE - 6)
#define MAX_USERNAME_SIZE 31
#define MAX_USERNAME_INPUT (MAX_USERNAME_SIZE - 1)


extern s8 mb64_cursor_pos[3];

//LEVEL SETTINGS INDEX
extern u8 mb64_lopt_costume;

extern u8 mb64_lopt_seq[5]; // Song index
extern u8 mb64_lopt_seq_seqtype; // Level Music, Race Music, Boss Music 
extern u8 mb64_lopt_seq_album; // Category
extern u8 mb64_lopt_seq_song; // Song index within category

extern u8 mb64_lopt_envfx;
extern u8 mb64_lopt_theme;
extern u8 mb64_lopt_bg;
extern u8 mb64_lopt_boundary_mat;
extern u8 mb64_lopt_boundary;
extern u8 mb64_lopt_boundary_height;
extern u8 mb64_lopt_game;
extern u8 mb64_lopt_size;
extern u8 mb64_lopt_template;
extern u8 mb64_lopt_coinstar;
extern u8 mb64_lopt_coinstar_max;
extern u8 mb64_lopt_waterlevel;
extern u8 mb64_lopt_secret;

extern u8 mb64_prepare_level_screenshot;
extern u8 mb64_do_save;

extern u8 mb64_curr_boundary;
extern u8 mb64_upsidedown_tile;

extern struct mb64_tile mb64_tile_data[MB64_TILE_POOL_SIZE];
extern struct mb64_obj mb64_object_data[MB64_MAX_OBJS];
extern u16 mb64_tile_data_indices[NUM_MATERIALS_PER_THEME + 10];
extern u16 mb64_tile_count;
extern u16 mb64_object_count;
extern u16 mb64_object_limit_count;
extern u16 mb64_total_coin_count;

extern u8 mb64_place_mode;
extern s8 mb64_id_selection;
extern u8 mb64_rot_selection;
extern s16 mb64_param_selection;
extern s16 mb64_mat_selection;

extern s16 mb64_freecam_pitch;
extern s16 mb64_freecam_yaw;
extern u8 mb64_freecam_snap;
extern u8 mb64_freecam_snap_timer;

extern FILINFO mb64_file_info;

#define AT_CEILING(y) ((mb64_curr_boundary & MB64_BOUNDARY_CEILING) && ((y) == mb64_lopt_boundary_height-1))

void reload_bg(void);
void save_level(void);
void sb_loop(void);
void sb_init(void);
void mb64_init();
void reset_play_state(void);
void generate_objects_to_level(void);
s32 mb64_main_menu(void);
extern Gfx mb64_terrain_gfx[MB64_GFX_SIZE];
void play_mb64_extra_music(u8 index);
void stop_mb64_extra_music(u8 index);
void animate_list_reset(void);
void freecam_camera_init(void);
void update_custom_theme(void);
void reload_theme(void);
void reload_boundary_and_gfx(void);

extern u8 mb64_level_action;
extern u8 mb64_mode;
extern u8 mb64_target_mode;
extern Vec3f mb64_camera_pos;
extern Vec3f mb64_camera_foc;
extern f32 mb64_camera_fov;

extern u16 painting_rgba16[32][32];
extern u8 mb64_envfx_table[];

//play mode stuff
extern s16 mb64_play_stars;
extern s16 mb64_play_stars_max;
extern u64 mb64_play_stars_bitfield;
extern u32 mb64_play_badge_bitfield;
extern u8 mb64_play_onoff;
extern s16 mb64_play_s16_water_level;
extern u32 mb64_play_speedrun_timer;

extern u8 mb64_grid_size;
extern u8 mb64_grid_min;

extern struct mb64_level_save_header mb64_save;
extern TCHAR mb64_file_name[MAX_FILE_NAME_SIZE];

extern void* mb64_theme_segments[][4];
extern LevelScript * mb64_theme_model_scripts[];

extern s8 cullOffsetLUT[6][3];

extern u8 mb64_rotated_dirs[4][6];
#define rotate_direction(dir, rot) (mb64_rotated_dirs[rot][dir])

enum {
    MB64_PM_NONE,
    MB64_PM_ACTION,
    MB64_PM_TILE,
    MB64_PM_OBJ,
};

#define GRID_TO_POS(gridx) ((gridx) * TILE_SIZE - (32 * TILE_SIZE) + TILE_SIZE/2)
#define POS_TO_GRID(pos) (((pos) + (32 * TILE_SIZE) - TILE_SIZE/2) / TILE_SIZE)

extern struct mb64_grid_obj mb64_grid_data[64][64][64];
#define get_grid_tile(pos) (&(mb64_grid_data[(pos)[0]][(pos)[1]][(pos)[2]]))

enum mb64_directions {
    MB64_DIRECTION_UP,
    MB64_DIRECTION_DOWN,
    MB64_DIRECTION_POS_X,
    MB64_DIRECTION_NEG_X,
    MB64_DIRECTION_POS_Z,
    MB64_DIRECTION_NEG_Z,
};

enum mb64_df_context {
    MB64_DF_CONTEXT_INIT,
    MB64_DF_CONTEXT_MAIN,
};

#define OBJ_TYPE_BILLBOARD (1 << 0)
#define OBJ_TYPE_TRAJECTORY     (1 << 1)
#define OBJ_TYPE_STAR       (1 << 2)
#define OBJ_TYPE_HAS_DIALOG     (1 << 3)
#define OBJ_TYPE_IMBUABLE       (1 << 4)
#define OBJ_TYPE_IMBUABLE_COINS (1 << 5)
#define OBJ_TYPE_IMBUABLE_TRIGGER (1 << 6)

#define OBJ_OCCUPY_OUTER        (1 << 0)
#define OBJ_OCCUPY_INNER        (1 << 1)

#define OBJ_OCCUPY_FULL        (OBJ_OCCUPY_OUTER | OBJ_OCCUPY_INNER)

extern struct ExclamationBoxContents *mb64_exclamation_box_contents;

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
};
extern u8 mb64_menu_state;

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

enum imbue {
    IMBUE_NONE,
    IMBUE_STAR,
    IMBUE_THREE_COINS,
    IMBUE_ONE_COIN,
    IMBUE_GREEN_COIN,
    IMBUE_BLUE_COIN,
    IMBUE_RED_SWITCH,
    IMBUE_BLUE_SWITCH,
    IMBUE_RED_COIN,
    IMBUE_TRIGGER,
    IMBUE_CROWBAR,
    IMBUE_BULLET_MASK,
    IMBUE_BADGE_BASE,
};

#define MB64_BOUNDARY_INNER_FLOOR   (1 << 0) // Has the main floor
#define MB64_BOUNDARY_OUTER_FLOOR   (1 << 1) // Has the fading outer floor
#define MB64_BOUNDARY_INNER_WALLS   (1 << 2) // Has the inner walls going up to boundary height - has fading part if death plane
#define MB64_BOUNDARY_OUTER_WALLS   (1 << 3) // Has fading outer walls extending downwards
#define MB64_BOUNDARY_CEILING       (1 << 4) // Ceiling above the level

extern u8 mb64_painting_frame_1_rgba16[];
extern u8 mystery_painting_rgba16[];
