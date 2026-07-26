#pragma once

#include "engine.h"

struct BadgeInfo {
    const char *name;
    const char *desc;
    u8 color[3];
};
extern struct BadgeInfo badge_info[];

void create_pause_menu(void);
