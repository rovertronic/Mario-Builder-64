#ifndef MENU_HEADER_H
#define MENU_HEADER_H

#include "types.h"
#include "src/game/game_init.h"
#include "mb64/file.h"

// geo
extern const GeoLayout geo_menu_file_select_strings_and_menu_cursor[];

// script
extern const LevelScript level_main_menu_entry_file_select[];
extern const LevelScript level_main_menu_entry_act_select[];

#include "levels/menu/mbg/geo_header.h"

#include "levels/menu/bigpainting/header.h"

extern FILINFO mb64_level_entries[MAX_FILES];
extern u16 mb64_level_entry_thumbnail[MAX_FILES][64][64];

#endif
