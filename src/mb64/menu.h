#pragma once

#include "menu_engine.h"

Gfx *get_button_tex(u32 buttonId, u32 objIndex);

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