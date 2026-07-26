#pragma once

#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include "sm64.h"
#include "game/geo_misc.h"

void generate_terrain_gfx(void);
Gfx *mb64_append(s32 callContext, UNUSED struct GraphNode *node, UNUSED Mat4 mtx);
void custom_theme_draw_block(f32 xpos, f32 ypos, s32 index);

extern u8 mb64_append_frameone_bandaid_fix;
