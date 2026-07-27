#ifndef INTRO_GEO_H
#define INTRO_GEO_H

#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "types.h"
#include "engine/graph_node.h"

extern Gfx ts1_letter_R_mesh[];
extern Gfx ts2_grid_mesh[];
extern Gfx ts3_eyes_mesh[];
extern Gfx ts4_MARIO_mesh[];

enum IntroContexts {
    INTRO_CONTEXT_NORMAL,
    INTRO_CONTEXT_GAME_OVER,
};

Gfx *geo_intro_super_mario_64_logo(s32 callContext, struct GraphNode *node, UNUSED void *context);
Gfx *geo_title_screen2(s32 sp50, struct GraphNode *sp54, UNUSED void *context);
Gfx *geo_title_screen3(s32 sp50, struct GraphNode *sp54, UNUSED void *context);
Gfx *geo_intro_regular_backdrop(s32 callContext, struct GraphNode *node, UNUSED void *context);
Gfx *geo_intro_gameover_backdrop(s32 callContext, struct GraphNode *node, UNUSED void *context);

#ifdef GODDARD_EASTER_EGG
Gfx *geo_intro_face_easter_egg(s32 callContext, struct GraphNode *node, UNUSED void *context);
#endif
#if (defined(COMPLETE_EN_US_SEGMENT2) && ENABLE_RUMBLE)
Gfx *geo_intro_rumble_pak_graphic(s32 callContext, struct GraphNode *node, UNUSED void *context);
#endif

#endif // INTRO_GEO_H
