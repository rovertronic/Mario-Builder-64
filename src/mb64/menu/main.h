#pragma once

#include "engine.h"

void init_main_menu(int page);
void set_page_to_level_list(void);
void set_initial_menu_page(void);
void reset_main_menu_state(void);

s32 lvl_mb64_main_menu_init(s32 arg, s32 unused);
s32 lvl_mb64_main_menu_update(s32 arg, s32 unused);

void bhv_mb64_menu_bg_init(void);
void bhv_mb64_menu_bg_loop(void);
