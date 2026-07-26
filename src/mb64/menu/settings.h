#pragma once

#include "engine.h"

extern u8 seq_musicmenu_array[];
extern u8 mb64_envfx_table[];
extern u8 mb64_boundary_table[];

extern MenuComponent *settingsRoot;

void settings_menu_create(void);
void reset_settings_menu_state(void);
