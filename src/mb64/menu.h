#pragma once

#include "menu_engine.h"

extern u8 mb64_toolbar[9];
extern u8 mb64_toolbar_params[9];
extern u8 mb64_toolbox[18 * 5];
extern u8 mb64_toolbox_params[18 * 5];

extern u8 mb64_toolbar_defaults[9];
extern u8 mb64_toolbox_btcm[18 * 5];
extern u8 mb64_toolbox_vanilla[18 * 5];

extern AnimatedComponent *gToolbar;
extern MatrixComponent *gCurDialog;
extern int gDialogResponse;

 struct BadgeInfo {
    const char *name;
    const char *desc;
    u8 color[3];
};
extern struct BadgeInfo badge_info[];

void create_toolbar(void);
void show_toolbar(void);
void hide_toolbar(void);
void toolbar_set_active(int active);

void create_toolbox(void);
void init_toolbox(void);
void settings_menu_create(void);

void set_page_to_level_list(void);
void set_initial_menu_page(void);

void show_error(char *msg);
void show_tip(void);

void create_coord_display(void);
void show_coord_display(void);
void hide_coord_display(void);

void create_yellow_text(char *msg);
void destroy_yellow_text(void);

void reset_settings_menu_state(void);
void reset_main_menu_state(void);
void reset_toolbox_state(void);
void reset_misc_menu_state(void);