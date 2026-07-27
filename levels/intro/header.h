#ifndef INTRO_HEADER_H
#define INTRO_HEADER_H

#include "types.h"

// geo
extern const GeoLayout intro_geo_splash_screen[];
extern const GeoLayout intro_geo_debug_level_select[];
extern const GeoLayout intro_geo_error_screen[];

// leveldata
extern const f32 intro_seg7_table_scale_1[];
extern const f32 intro_seg7_table_scale_2[];

// script
extern const LevelScript level_intro_splash_screen[];
extern const LevelScript level_intro_title_reset[];
extern const LevelScript level_intro_game_over_reset[];
extern const LevelScript level_intro_entry_level_select[];
extern const LevelScript script_intro_file_select[];
extern const LevelScript script_intro_level_select[];
extern const LevelScript script_intro_main_level_entry_stop_music[];
extern const LevelScript script_intro_main_level_entry[];
extern const LevelScript script_intro_splash_screen[];
extern const LevelScript level_intro_entry_error_screen[];

extern Gfx *geo18_display_error_message(u32 run, UNUSED struct GraphNode *sp44, UNUSED u32 sp48);

#include "levels/intro/ts1/header.h"

#include "levels/intro/ts2/header.h"

#include "levels/intro/ts3/header.h"

#include "levels/intro/ts4/header.h"

#endif
