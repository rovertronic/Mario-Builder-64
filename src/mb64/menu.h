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
extern MenuComponent *gCurDialog;

 struct BadgeInfo {
    const char *name;
    const char *desc;
    u8 color[3];
};
extern struct BadgeInfo badge_info[];

void show_error(char *msg);
void show_tip(void);

void create_coord_display(void);
void show_coord_display(void);
void hide_coord_display(void);
