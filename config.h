#ifndef S2D_CONFIG_H
#define S2D_CONFIG_H

// include your font header here
#include "fonts/impact.h"

// get your symbols defined here
#define s2d_font impact_obj
#define s2d_tex  impact_tex

// Debug: bypass custom matrix setup
#define s2d_mat impact_mtx

// homebrew users: use this to rename your gdl head
#define gdl_head gDisplayListHead
extern Gfx *gdl_head;

#endif