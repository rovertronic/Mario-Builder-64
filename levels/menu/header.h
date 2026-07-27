#ifndef MENU_HEADER_H
#define MENU_HEADER_H

#include "types.h"
#include "src/game/game_init.h"
#include "mb64/file.h"

// geo
extern const GeoLayout geo_menu_file_select_strings_and_menu_cursor[];
extern const GeoLayout intro_geo_splash_screen[];
extern const GeoLayout intro_geo_error_screen[];

// leveldata
extern const f32 intro_seg7_table_scale_1[];
extern const f32 intro_seg7_table_scale_2[];

// script
extern const LevelScript level_main_menu_entry_file_select[];
extern const LevelScript level_intro_splash_screen[];
extern const LevelScript level_intro_title_reset[];
extern const LevelScript level_intro_entry_error_screen[];

extern Gfx *geo18_display_error_message(u32 run, UNUSED struct GraphNode *sp44, UNUSED u32 sp48);

#include "levels/menu/mbg/geo_header.h"
#include "levels/menu/bigpainting/header.h"
#include "levels/menu/ts1/header.h"
#include "levels/menu/ts2/header.h"
#include "levels/menu/ts3/header.h"
#include "levels/menu/ts4/header.h"

extern FILINFO mb64_level_entries[MAX_FILES];
extern u16 mb64_level_entry_thumbnail[MAX_FILES][64][64];

#endif
