#pragma once

#include "types.h"

#define MB64_SPEEDRUN_TIMER_MAX (30 * 60 * 100 - 1)

enum {
    MB64_PM_NONE,
    MB64_PM_ACTION,
    MB64_PM_TILE,
    MB64_PM_OBJ,
};

enum {
    MB64_MAKE_MAIN,
    MB64_MAKE_PLAY,
    MB64_MAKE_TOOLBOX,
    MB64_MAKE_SETTINGS,
    MB64_MAKE_TRAJECTORY,
    MB64_MAKE_SCREENSHOT,
};

enum {
    MB64_LA_PLAY_LEVELS,
    MB64_LA_BUILD,
    MB64_LA_TEST_LEVEL,
};

extern s8 mb64_cursor_pos[3];

extern u8 mb64_prepare_level_screenshot;
extern u8 mb64_do_save;
extern u8 mb64_upsidedown_tile;

extern u8 mb64_place_mode;
extern s8 mb64_id_selection;
extern u8 mb64_rot_selection;
extern s16 mb64_param_selection;
extern s16 mb64_mat_selection;

extern u8 mb64_level_action;
extern u8 mb64_menu_state;

extern s16 mb64_play_stars;
extern s16 mb64_play_stars_max;
extern u64 mb64_play_stars_bitfield;
extern u32 mb64_play_badge_bitfield;
extern u8 mb64_play_onoff;
extern s16 mb64_play_s16_water_level;
extern u32 mb64_play_speedrun_timer;

extern void *mb64_theme_segments[][4];
extern const LevelScript *mb64_theme_model_scripts[];
extern u8 *mb64_skybox_table[];

void reload_bg(void);
void sb_loop(void);
void sb_init(void);
void mb64_init(void);
void update_custom_theme(void);
void reload_theme(void);
void reload_boundary_and_gfx(void);
void play_mb64_extra_music(u8 index);
void stop_mb64_extra_music(u8 index);
void delete_tile_action(s8 pos[3]);
void reset_play_state(void);
