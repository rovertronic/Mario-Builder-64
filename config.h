#ifndef S2D_CONFIG_H
#define S2D_CONFIG_H

#define const

// include your font header here
#include "fonts/impact.h"

// get your font symbols defined here
#define s2d_font          impact_obj
#define s2d_tex           impact_tex
#define s2d_kerning_table impact_kerning_table
extern char s2d_kerning_table[];

// Debug: bypass custom matrix setup
#define s2d_mat impact_mtx

// Homebrew users: use this to rename your gdl head
#define gdl_head gDisplayListHead
extern Gfx *gdl_head;


// Other games/Homebrew users: change these values

// an allocator function of the format void *alloc(size_t bytes)
#define alloc alloc_display_list

// your init functions for the RDP/RSP
#define my_rdp_init my_rdp_init
#define my_rsp_init my_rsp_init

// The frame timer that is used to time s2d_type_print
#define s2d_timer gGlobalTimer
extern u32 s2d_timer;

// The equivalent vsprintf in your game (defaults to libultra _Printf)
#define vsprintf(dst, str, fmt, args) _Printf(proutSprintf, dst, fmt, args)
extern char *proutSprintf(char *dst, const char *src, size_t count);


// tab glyph width and height
#define TAB_WIDTH_H TEX_WIDTH * 2
#define TAB_WIDTH_V TEX_WIDTH / 2

// Set these to optimize s2d texture "cache"
#define TEX_WIDTH 16
#define TEX_HEIGHT 16
#define TEX_BITDEPTH 8

#define _NUM_CACHE (4096 / (TEX_WIDTH * TEX_HEIGHT * (TEX_BITDEPTH / 8)))

#endif