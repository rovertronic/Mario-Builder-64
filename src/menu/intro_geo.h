#ifndef INTRO_GEO_H
#define INTRO_GEO_H

#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "types.h"

extern Gfx ts1_letter_R_mesh[];
extern Gfx ts2_grid_mesh[];
extern Gfx ts3_eyes_mesh[];
extern Gfx ts4_MARIO_mesh[];

Gfx *geo_intro_super_mario_64_logo(s32 callContext, struct GraphNode *node, UNUSED void *context);
Gfx *geo_title_screen2(s32 sp50, struct GraphNode *sp54, UNUSED void *context);
Gfx *geo_title_screen3(s32 sp50, struct GraphNode *sp54, UNUSED void *context);

#endif // INTRO_GEO_H
