#pragma once

#include <PR/ultratypes.h>
#include "types.h"

enum mb64_culling_shapes {
    MB64_FACESHAPE_FULL,
    MB64_FACESHAPE_POLETOP,

    MB64_FACESHAPE_TRI_1, // make sure irregular shapes can be flipped with ^1
    MB64_FACESHAPE_TRI_2,
    MB64_FACESHAPE_DOWNTRI_1,
    MB64_FACESHAPE_DOWNTRI_2,
    MB64_FACESHAPE_HALFSIDE_1, // vertical slab sides
    MB64_FACESHAPE_HALFSIDE_2,

    MB64_FACESHAPE_TOPTRI,
    MB64_FACESHAPE_TOPHALF,

    // & 0x10: Bottom slab priority list
    MB64_FACESHAPE_BOTTOMSLAB_PRI = 0x10,
    MB64_FACESHAPE_UPPERGENTLE_1 = MB64_FACESHAPE_BOTTOMSLAB_PRI,
    MB64_FACESHAPE_UPPERGENTLE_2,
    MB64_FACESHAPE_BOTTOMSLAB,
    // 0x13 empty
    MB64_FACESHAPE_LOWERGENTLE_1 = MB64_FACESHAPE_BOTTOMSLAB_PRI + 4,
    MB64_FACESHAPE_LOWERGENTLE_2,
    
    // & 0x20: Top slab priority list
    MB64_FACESHAPE_TOPSLAB_PRI = 0x20,
    MB64_FACESHAPE_DOWNUPPERGENTLE_1 = MB64_FACESHAPE_TOPSLAB_PRI,
    MB64_FACESHAPE_DOWNUPPERGENTLE_2,
    MB64_FACESHAPE_TOPSLAB,
    // 0x23 empty
    MB64_FACESHAPE_DOWNLOWERGENTLE_1 = MB64_FACESHAPE_TOPSLAB_PRI + 4,
    MB64_FACESHAPE_DOWNLOWERGENTLE_2,

    // & 0x40: Empty faces
    MB64_FACESHAPE_EMPTY = 0x40,
    // Rotate UVs for certain textures
    MB64_FACESHAPE_EMPTY_0,
    MB64_FACESHAPE_EMPTY_1,
    MB64_FACESHAPE_EMPTY_2,
    MB64_FACESHAPE_EMPTY_3,
};

extern u8 mb64_render_culling_off;

u32 get_faceshape(s8 pos[3], u32 dir);
s32 get_mat(s8 pos[3]);
s32 cutout_skip_culling_check(s32 curMat, s32 otherMat, s32 direction);
u32 block_side_is_solid(s32 adjMat, s32 mat, s32 direction);
s32 should_cull(s8 pos[3], s32 direction, s32 faceshape, s32 rot);
s32 should_cull_topslab_check(s8 pos[3], s32 direction);
