#ifndef S2D_CONFIG_H
#define S2D_CONFIG_H

// include your font header here
#include "fonts/impact.h"

// get your font symbols defined here
#define s2d_font impact_obj
#define s2d_tex  impact_tex

// Debug: bypass custom matrix setup
#define s2d_mat impact_mtx

// Homebrew users: use this to rename your gdl head
#define gdl_head gDisplayListHead
extern Gfx *gdl_head;


// Other games/Homebrew users: change these values

// an allocator function of the format void *alloc(size_t bytes)
#define alloc alloc_display_list

// The frame timer that is used to time s2d_type_print
#define s2d_timer gGlobalTimer

// The equivalent vsprintf in your game (defaults to libultra _Printf)
#define vsprintf _Printf


// texture glyph width and height
#define TEX_WIDTH 16
#define TEX_HEIGHT 16


#endif