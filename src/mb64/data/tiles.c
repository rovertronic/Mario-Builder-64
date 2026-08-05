#include "mb64/gfx/tile.h"
#include "mb64/gfx/mb64_buttons.h"

struct mb64_terrain_poly mb64_terrain_fullblock_quads[] = {
    {{{16, 16, 16}, {16, 16, 0}, {0, 16, 16},  {0, 16, 0}},  MB64_DIRECTION_UP,    MB64_FACESHAPE_FULL, MB64_GROWTH_FULL, NULL}, // TOP
    {{{16, 0, 16},  {0, 0, 16},  {16, 0, 0},   {0, 0, 0}},   MB64_DIRECTION_DOWN,  MB64_FACESHAPE_FULL, 0, NULL}, // BOTTOM
    {{{16, 16, 16}, {16, 0, 16}, {16, 16, 0},  {16, 0, 0}},  MB64_DIRECTION_POS_X, MB64_FACESHAPE_FULL, MB64_GROWTH_NORMAL_SIDE, NULL}, // LEFT
    {{{0, 16, 0},   {0, 0, 0},   {0, 16, 16},  {0, 0, 16}},  MB64_DIRECTION_NEG_X, MB64_FACESHAPE_FULL, MB64_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
    {{{0, 16, 16},  {0, 0, 16},  {16, 16, 16}, {16, 0, 16}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_FULL, MB64_GROWTH_NORMAL_SIDE, NULL}, // FRONT
    {{{16, 16, 0},  {16, 0, 0},  {0, 16, 0},   {0, 0, 0}},   MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_FULL, MB64_GROWTH_NORMAL_SIDE, NULL}, // BACK
};
struct mb64_terrain mb64_terrain_fullblock = {
    6,
    0,
    mb64_terrain_fullblock_quads,
    NULL
};

s8 slope_decal_uvs1[3][2] = {{0, 0}, {0, 16}, {16, 16}};
s8 slope_decal_uvs2[3][2] = {{16, 16}, {16, 0}, {0, 16}};

struct mb64_terrain_poly mb64_terrain_slope_quads[] = {
    {{{16, 0, 16}, {16, 16, 0}, {0, 0, 16}, {0, 16, 0}}, MB64_DIRECTION_UP,    MB64_FACESHAPE_EMPTY_2, MB64_GROWTH_FULL, NULL}, // TOP
    {{{16, 0, 16}, {0, 0, 16},  {16, 0, 0}, {0, 0, 0}},  MB64_DIRECTION_DOWN,  MB64_FACESHAPE_FULL, 0, NULL}, // BOTTOM
    {{{16, 16, 0}, {16, 0, 0},  {0, 16, 0}, {0, 0, 0}},  MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_FULL, MB64_GROWTH_NORMAL_SIDE, NULL}, // BACK
};

struct mb64_terrain_poly mb64_terrain_slope_tris[] = {
    {{{16, 0, 0}, {16, 16, 0}, {16, 0, 16}}, MB64_DIRECTION_POS_X, MB64_FACESHAPE_TRI_1, MB64_GROWTH_SLOPE_SIDE_L, &slope_decal_uvs1}, // LEFT
    {{{0, 16, 0}, {0, 0, 0},   {0, 0, 16}},  MB64_DIRECTION_NEG_X, MB64_FACESHAPE_TRI_2, MB64_GROWTH_SLOPE_SIDE_R, &slope_decal_uvs2}, // RIGHT
};

struct mb64_terrain mb64_terrain_slope = {
    3,
    2,
    mb64_terrain_slope_quads,
    mb64_terrain_slope_tris,
};

struct mb64_terrain_poly mb64_terrain_dslope_quads[] = {
    {{{16, 16, 16}, {16, 16, 0}, {0, 16, 16}, {0, 16, 0}}, MB64_DIRECTION_UP,    MB64_FACESHAPE_FULL, MB64_GROWTH_FULL, NULL}, // TOP
    {{{16, 16, 0},  {16, 0, 0},  {0, 16, 0},  {0, 0, 0}},  MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_FULL, MB64_GROWTH_NORMAL_SIDE, NULL}, // BACK
    {{{16, 16, 16}, {0, 16, 16}, {16, 0, 0},  {0, 0, 0}},  MB64_DIRECTION_DOWN,  MB64_FACESHAPE_EMPTY_2, MB64_GROWTH_NORMAL_SIDE, NULL}, // BOTTOM
};

struct mb64_terrain_poly mb64_terrain_dslope_tris[] = {
    {{{16, 0, 0}, {16, 16, 0}, {16, 16, 16}},  MB64_DIRECTION_POS_X, MB64_FACESHAPE_DOWNTRI_1, MB64_GROWTH_NORMAL_SIDE, NULL}, // LEFT
    {{{0, 16, 0}, {0, 0, 0},   {0, 16, 16}},   MB64_DIRECTION_NEG_X, MB64_FACESHAPE_DOWNTRI_2, MB64_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
};

struct mb64_terrain mb64_terrain_dslope = {
    3,
    2,
    mb64_terrain_dslope_quads,
    mb64_terrain_dslope_tris,
};

struct mb64_terrain_poly mb64_terrain_corner_quads[] = {
    {{{16, 0, 16}, {0, 0, 16}, {16, 0, 0}, {0, 0, 0}}, MB64_DIRECTION_DOWN, MB64_FACESHAPE_FULL, 0, NULL}, // BOTTOM
};

struct mb64_terrain_poly mb64_terrain_corner_tris[] = {
    {{{0, 0, 16}, {16, 0, 16}, {0, 16, 0}},  MB64_DIRECTION_UP,    MB64_FACESHAPE_EMPTY_2, MB64_GROWTH_FULL, NULL}, // TOP-FRONT
    {{{0, 16, 0}, {16, 0, 16}, {16, 0, 0}},  MB64_DIRECTION_UP,    MB64_FACESHAPE_EMPTY_0, MB64_GROWTH_FULL, NULL}, // TOP-LEFT 
    {{{0, 16, 0}, {0, 0, 0},   {0, 0, 16}},  MB64_DIRECTION_NEG_X, MB64_FACESHAPE_TRI_2, MB64_GROWTH_SLOPE_SIDE_R, &slope_decal_uvs2}, // RIGHT
    {{{0, 0, 0},  {0, 16, 0},  {16, 0, 0}},  MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_TRI_1, MB64_GROWTH_SLOPE_SIDE_L, &slope_decal_uvs1}, // BACK
};

struct mb64_terrain mb64_terrain_corner = {
    1,
    4,
    mb64_terrain_corner_quads,
    mb64_terrain_corner_tris,
};

struct mb64_terrain_poly mb64_terrain_dcorner_quads[] = {
    {{{16, 16, 16}, {16, 16, 0}, {0, 16, 16}, {0, 16, 0}}, MB64_DIRECTION_UP, MB64_FACESHAPE_FULL, MB64_GROWTH_FULL, NULL}, // TOP
};

struct mb64_terrain_poly mb64_terrain_dcorner_tris[] = {
    {{{16, 16, 16}, {0, 16, 16}, {0, 0, 0}},    MB64_DIRECTION_DOWN, MB64_FACESHAPE_EMPTY_2, MB64_GROWTH_NORMAL_SIDE, NULL}, // BOTTOM-FRONT
    {{{0, 0, 0},    {16, 16, 0}, {16, 16, 16}}, MB64_DIRECTION_DOWN, MB64_FACESHAPE_EMPTY_0, MB64_GROWTH_NORMAL_SIDE, NULL}, // BOTTOM-LEFT 
    {{{0, 0, 0},    {0, 16, 16}, {0, 16, 0}},   MB64_DIRECTION_NEG_X, MB64_FACESHAPE_DOWNTRI_2, MB64_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
    {{{0, 0, 0},    {0, 16, 0},  {16, 16, 0}},  MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_DOWNTRI_1, MB64_GROWTH_NORMAL_SIDE, NULL}, // BACK
};

struct mb64_terrain mb64_terrain_dcorner = {
    1,
    4,
    mb64_terrain_dcorner_quads,
    mb64_terrain_dcorner_tris,
};


struct mb64_terrain_poly mb64_terrain_icorner_quads[] = {
    {{{16, 0, 16}, {0, 0, 16}, {16, 0, 0},  {0, 0, 0}},  MB64_DIRECTION_DOWN,  MB64_FACESHAPE_FULL, 0, NULL}, // BOTTOM
    {{{16, 16, 0}, {16, 0, 0}, {0, 16, 0},  {0, 0, 0}},  MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_FULL, MB64_GROWTH_NORMAL_SIDE, NULL}, // BACK
    {{{0, 16, 0},  {0, 0, 0},  {0, 16, 16}, {0, 0, 16}}, MB64_DIRECTION_NEG_X, MB64_FACESHAPE_FULL, MB64_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
};

struct mb64_terrain_poly mb64_terrain_icorner_tris[] = {
    {{{0, 16, 16}, {16, 0, 16}, {0, 16, 0}},  MB64_DIRECTION_UP,    MB64_FACESHAPE_EMPTY_0, MB64_GROWTH_FULL, NULL}, // TOP-FRONT
    {{{0, 16, 0},  {16, 0, 16}, {16, 16, 0}}, MB64_DIRECTION_UP,    MB64_FACESHAPE_EMPTY_2, MB64_GROWTH_FULL, NULL}, // TOP-LEFT
    {{{16, 0, 0},  {16, 16, 0}, {16, 0, 16}}, MB64_DIRECTION_POS_X, MB64_FACESHAPE_TRI_1, MB64_GROWTH_SLOPE_SIDE_L, &slope_decal_uvs1}, // LEFT
    {{{0, 16, 16}, {0, 0, 16},  {16, 0, 16}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_TRI_2, MB64_GROWTH_SLOPE_SIDE_R, &slope_decal_uvs2}, // FRONT
};

struct mb64_terrain mb64_terrain_icorner = {
    3,
    4,
    mb64_terrain_icorner_quads,
    mb64_terrain_icorner_tris,
};

struct mb64_terrain_poly mb64_terrain_dicorner_quads[] = {
    {{{16, 16, 16}, {16, 16, 0}, {0, 16, 16}, {0, 16, 0}}, MB64_DIRECTION_UP,    MB64_FACESHAPE_FULL, MB64_GROWTH_FULL, NULL}, // TOP
    {{{16, 16, 0},  {16, 0, 0},  {0, 16, 0},  {0, 0, 0}},  MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_FULL, MB64_GROWTH_NORMAL_SIDE, NULL}, // BACK
    {{{0, 16, 0},   {0, 0, 0},   {0, 16, 16}, {0, 0, 16}}, MB64_DIRECTION_NEG_X, MB64_FACESHAPE_FULL, MB64_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
};

struct mb64_terrain_poly mb64_terrain_dicorner_tris[] = {
    {{{16, 0, 0},   {16, 16, 0}, {16, 16, 16}}, MB64_DIRECTION_POS_X, MB64_FACESHAPE_DOWNTRI_1, MB64_GROWTH_NORMAL_SIDE, NULL}, // LEFT
    {{{0, 16, 16},  {0, 0, 16},  {16, 16, 16}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_DOWNTRI_2, MB64_GROWTH_NORMAL_SIDE, NULL}, // FRONT
    {{{16, 16, 16}, {0, 0, 16},  {0, 0, 0}},    MB64_DIRECTION_DOWN, MB64_FACESHAPE_EMPTY_0, MB64_GROWTH_UNDERSLOPE_CORNER, NULL}, // BOTTOM-FRONT
    {{{16, 16, 16}, {0, 0, 0},   {16, 0, 0}},   MB64_DIRECTION_DOWN, MB64_FACESHAPE_EMPTY_2, MB64_GROWTH_UNDERSLOPE_CORNER, NULL}, // BOTTOM-LEFT
};

struct mb64_terrain mb64_terrain_dicorner = {
    3,
    4,
    mb64_terrain_dicorner_quads,
    mb64_terrain_dicorner_tris,
};

struct mb64_terrain_poly mb64_terrain_sslope_quads[] = {
    {{{16, 16, 0}, {16, 0, 0},  {0, 16, 0},  {0, 0, 0}},  MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_FULL, MB64_GROWTH_NORMAL_SIDE, NULL}, // BACK
    {{{0, 16, 0},  {0, 0, 0},   {0, 16, 16}, {0, 0, 16}}, MB64_DIRECTION_NEG_X, MB64_FACESHAPE_FULL, MB64_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
    {{{16, 16, 0}, {0, 16, 16}, {16, 0, 0},  {0, 0, 16}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_EMPTY, MB64_GROWTH_DIAGONAL_SIDE, NULL}, // DIAGONAL
};

struct mb64_terrain_poly mb64_terrain_sslope_tris[] = {
    {{{0, 16, 16}, {16, 16, 0}, {0, 16, 0}}, MB64_DIRECTION_UP,   MB64_FACESHAPE_TOPTRI, MB64_GROWTH_FULL, NULL}, // TOP
    {{{16, 0, 0},  {0, 0, 16},  {0, 0, 0}},  MB64_DIRECTION_DOWN, MB64_FACESHAPE_TOPTRI, 0, NULL}, // BOTTOM
};

struct mb64_terrain mb64_terrain_sslope = {
    3,
    2,
    mb64_terrain_sslope_quads,
    mb64_terrain_sslope_tris,
};

s8 scorner_slope_tri_uvs[3][2] = {{16, 0}, {0, 0}, {8, 16}};

struct mb64_terrain_poly mb64_terrain_scorner_tris[] = {
    {{{0, 0, 16}, {16, 0, 0}, {0, 16, 0}},  MB64_DIRECTION_UP,    MB64_FACESHAPE_EMPTY_2, MB64_GROWTH_FULL, &scorner_slope_tri_uvs}, // TOP
    {{{16, 0, 0},  {0, 0, 16},  {0, 0, 0}}, MB64_DIRECTION_DOWN, MB64_FACESHAPE_TOPTRI, 0, NULL}, // BOTTOM
    {{{0, 16, 0}, {0, 0, 0},   {0, 0, 16}}, MB64_DIRECTION_NEG_X, MB64_FACESHAPE_TRI_2, MB64_GROWTH_SLOPE_SIDE_R, &slope_decal_uvs2}, // RIGHT
    {{{0, 0, 0},  {0, 16, 0},  {16, 0, 0}}, MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_TRI_1, MB64_GROWTH_SLOPE_SIDE_L, &slope_decal_uvs1}, // BACK
};

struct mb64_terrain mb64_terrain_scorner = {
    0,
    4,
    NULL,
    mb64_terrain_scorner_tris,
};

s8 dscorner_slope_tri_uvs[3][2] = {{0, 16}, {16, 16}, {8, 0}};

struct mb64_terrain_poly mb64_terrain_dscorner_tris[] = {
    {{{16, 16, 0}, {0, 16, 16}, {0, 0, 0}},    MB64_DIRECTION_DOWN, MB64_FACESHAPE_EMPTY_2, MB64_GROWTH_DIAGONAL_SIDE, &dscorner_slope_tri_uvs}, // BOTTOM
    {{{0, 16, 16}, {16, 16, 0}, {0, 16, 0}},   MB64_DIRECTION_UP,   MB64_FACESHAPE_TOPTRI, MB64_GROWTH_FULL, NULL}, // TOP
    {{{0, 0, 0},    {0, 16, 16}, {0, 16, 0}},  MB64_DIRECTION_NEG_X, MB64_FACESHAPE_DOWNTRI_2, MB64_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
    {{{0, 0, 0},    {0, 16, 0},  {16, 16, 0}}, MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_DOWNTRI_1, MB64_GROWTH_NORMAL_SIDE, NULL}, // BACK
};

struct mb64_terrain mb64_terrain_dscorner = {
    0,
    4,
    NULL,
    mb64_terrain_dscorner_tris,
};

s8 iscorner_slope_tri_uvs[3][2] = {{8, 16}, {0, 0}, {-8, 16}};

struct mb64_terrain_poly mb64_terrain_iscorner_quads[] = {
    {{{16, 0, 16}, {0, 0, 16}, {16, 0, 0},  {0, 0, 0}},  MB64_DIRECTION_DOWN,  MB64_FACESHAPE_FULL, 0, NULL}, // BOTTOM
    {{{16, 16, 0}, {16, 0, 0}, {0, 16, 0},  {0, 0, 0}},  MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_FULL, MB64_GROWTH_NORMAL_SIDE, NULL}, // BACK
    {{{0, 16, 0},  {0, 0, 0},  {0, 16, 16}, {0, 0, 16}}, MB64_DIRECTION_NEG_X, MB64_FACESHAPE_FULL, MB64_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
};

struct mb64_terrain_poly mb64_terrain_iscorner_tris[] = {
    {{{0, 16, 16}, {16, 16, 0}, {0, 16, 0}}, MB64_DIRECTION_UP,   MB64_FACESHAPE_TOPTRI, MB64_GROWTH_FULL, NULL}, // TOP
    {{{0, 16, 16},  {16, 0, 16}, {16, 16, 0}}, MB64_DIRECTION_UP,    MB64_FACESHAPE_EMPTY_2, MB64_GROWTH_FULL, &iscorner_slope_tri_uvs}, // TOP SLOPE
    {{{16, 0, 0},  {16, 16, 0}, {16, 0, 16}}, MB64_DIRECTION_POS_X, MB64_FACESHAPE_TRI_1, MB64_GROWTH_SLOPE_SIDE_L, &slope_decal_uvs1}, // LEFT
    {{{0, 16, 16}, {0, 0, 16},  {16, 0, 16}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_TRI_2, MB64_GROWTH_SLOPE_SIDE_R, &slope_decal_uvs2}, // FRONT
};

struct mb64_terrain mb64_terrain_iscorner = {
    3,
    4,
    mb64_terrain_iscorner_quads,
    mb64_terrain_iscorner_tris,
};

s8 discorner_slope_tri_uvs[3][2] = {{8, 0}, {-8, 0}, {0, 16}};

struct mb64_terrain_poly mb64_terrain_discorner_quads[] = {
    {{{16, 16, 16}, {16, 16, 0}, {0, 16, 16}, {0, 16, 0}}, MB64_DIRECTION_UP,    MB64_FACESHAPE_FULL, MB64_GROWTH_FULL, NULL}, // TOP
    {{{16, 16, 0},  {16, 0, 0},  {0, 16, 0},  {0, 0, 0}},  MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_FULL, MB64_GROWTH_NORMAL_SIDE, NULL}, // BACK
    {{{0, 16, 0},   {0, 0, 0},   {0, 16, 16}, {0, 0, 16}}, MB64_DIRECTION_NEG_X, MB64_FACESHAPE_FULL, MB64_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
};

struct mb64_terrain_poly mb64_terrain_discorner_tris[] = {
    {{{16, 0, 0},   {16, 16, 0}, {16, 16, 16}}, MB64_DIRECTION_POS_X, MB64_FACESHAPE_DOWNTRI_1, MB64_GROWTH_NORMAL_SIDE, NULL}, // LEFT
    {{{0, 16, 16},  {0, 0, 16},  {16, 16, 16}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_DOWNTRI_2, MB64_GROWTH_NORMAL_SIDE, NULL}, // FRONT
    {{{16, 0, 0},  {0, 0, 16},  {0, 0, 0}},  MB64_DIRECTION_DOWN, MB64_FACESHAPE_TOPTRI, 0, NULL}, // BOTTOM
    {{{0, 0, 16},   {16, 0, 0}, {16, 16, 16}},   MB64_DIRECTION_DOWN, MB64_FACESHAPE_EMPTY_2, MB64_GROWTH_UNDERSLOPE_CORNER, &discorner_slope_tri_uvs}, // BOTTOM SLOPE
};

struct mb64_terrain mb64_terrain_discorner = {
    3,
    4,
    mb64_terrain_discorner_quads,
    mb64_terrain_discorner_tris,
};

s8 bottomslab_decal_uvs1[4][2] = {{16, 16}, {16, 8}, {0, 16}, {0, 8}};

struct mb64_terrain_poly mb64_terrain_bottomslab_quads[] = {
    {{{16, 8, 16}, {16, 8, 0},  {0, 8, 16},  {0, 8, 0}},   MB64_DIRECTION_UP,    MB64_FACESHAPE_EMPTY, MB64_GROWTH_FULL, NULL}, // TOP
    {{{16, 0, 16}, {0, 0, 16},  {16, 0, 0},  {0, 0, 0}},   MB64_DIRECTION_DOWN,  MB64_FACESHAPE_FULL, 0, NULL}, // BOTTOM
    {{{16, 8, 16}, {16, 0, 16}, {16, 8, 0},  {16, 0, 0}},  MB64_DIRECTION_POS_X, MB64_FACESHAPE_BOTTOMSLAB, MB64_GROWTH_UNCONDITIONAL, &bottomslab_decal_uvs1}, // LEFT
    {{{0, 8, 0},   {0, 0, 0},   {0, 8, 16},  {0, 0, 16}},  MB64_DIRECTION_NEG_X, MB64_FACESHAPE_BOTTOMSLAB, MB64_GROWTH_UNCONDITIONAL, &bottomslab_decal_uvs1}, // RIGHT
    {{{0, 8, 16},  {0, 0, 16},  {16, 8, 16}, {16, 0, 16}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_BOTTOMSLAB, MB64_GROWTH_UNCONDITIONAL, &bottomslab_decal_uvs1}, // FRONT
    {{{16, 8, 0},  {16, 0, 0},  {0, 8, 0},   {0, 0, 0}},   MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_BOTTOMSLAB, MB64_GROWTH_UNCONDITIONAL, &bottomslab_decal_uvs1}, // BACK
};

struct mb64_terrain mb64_terrain_bottomslab = {
    6,
    0,
    mb64_terrain_bottomslab_quads,
    NULL
};

struct mb64_terrain_poly mb64_terrain_topslab_quads[] = {
    {{{16, 16, 16}, {16, 16, 0}, {0, 16, 16},  {0, 16, 0}},  MB64_DIRECTION_UP,    MB64_FACESHAPE_FULL, MB64_GROWTH_FULL, NULL}, // TOP
    {{{16, 8, 16},  {0, 8, 16},  {16, 8, 0},   {0, 8, 0}},   MB64_DIRECTION_DOWN,  MB64_FACESHAPE_EMPTY, 0, NULL}, // BOTTOM
    {{{16, 16, 16}, {16, 8, 16}, {16, 16, 0},  {16, 8, 0}},  MB64_DIRECTION_POS_X, MB64_FACESHAPE_TOPSLAB, MB64_GROWTH_NORMAL_SIDE, NULL}, // LEFT
    {{{0, 16, 0},   {0, 8, 0},   {0, 16, 16},  {0, 8, 16}},  MB64_DIRECTION_NEG_X, MB64_FACESHAPE_TOPSLAB, MB64_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
    {{{0, 16, 16},  {0, 8, 16},  {16, 16, 16}, {16, 8, 16}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_TOPSLAB, MB64_GROWTH_NORMAL_SIDE, NULL}, // FRONT
    {{{16, 16, 0},  {16, 8, 0},  {0, 16, 0},   {0, 8, 0}},   MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_TOPSLAB, MB64_GROWTH_NORMAL_SIDE, NULL}, // BACK
};

struct mb64_terrain mb64_terrain_topslab = {
    6,
    0,
    mb64_terrain_topslab_quads,
    NULL
};

struct mb64_terrain_poly mb64_terrain_vslab_quads[] = {
    {{{16, 16, 8}, {16, 16, 0}, {0, 16, 8},  {0, 16, 0}}, MB64_DIRECTION_UP,    MB64_FACESHAPE_TOPHALF,    MB64_GROWTH_FULL, NULL}, // TOP
    {{{16, 0, 8},  {0, 0, 8},   {16, 0, 0},  {0, 0, 0}},  MB64_DIRECTION_DOWN,  MB64_FACESHAPE_TOPHALF,    0, NULL}, // BOTTOM
    {{{16, 16, 8}, {16, 0, 8},  {16, 16, 0}, {16, 0, 0}}, MB64_DIRECTION_POS_X, MB64_FACESHAPE_HALFSIDE_1, MB64_GROWTH_HALF_SIDE,   NULL}, // LEFT
    {{{0, 16, 0},  {0, 0, 0},   {0, 16, 8},  {0, 0, 8}},  MB64_DIRECTION_NEG_X, MB64_FACESHAPE_HALFSIDE_2, MB64_GROWTH_HALF_SIDE,   NULL}, // RIGHT
    {{{0, 16, 8},  {0, 0, 8},   {16, 16, 8}, {16, 0, 8}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_EMPTY,      MB64_GROWTH_VSLAB_SIDE, NULL}, // FRONT
    {{{16, 16, 0}, {16, 0, 0},  {0, 16, 0},  {0, 0, 0}},  MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_FULL,       MB64_GROWTH_NORMAL_SIDE,   NULL}, // BACK
};
struct mb64_terrain mb64_terrain_vslab = {
    6,
    0,
    mb64_terrain_vslab_quads,
    NULL
};

s8 gentle_slope_uvs[4][2] = {{0, 0}, {0, 16}, {16, 0}, {16, 16}};

s8 gentle_decal_tri_uvs1[3][2] = {{0, 8}, {0, 16}, {16, 16}};
s8 gentle_decal_tri_uvs2[3][2] = {{16, 16}, {16, 8}, {0, 16}};
s8 ugentle_decal_quad_uvs1[4][2] = {{16, 16}, {16, 8}, {0, 8}, {0, 0}};
s8 ugentle_decal_quad_uvs2[4][2] = {{16, 8}, {16, 0}, {0, 16}, {0, 8}};

struct mb64_terrain_poly mb64_terrain_ugentle_quads[] = {
    {{{16, 8, 16}, {16, 16, 0}, {0, 8, 16}, {0, 16, 0}}, MB64_DIRECTION_UP,    MB64_FACESHAPE_EMPTY_2, MB64_GROWTH_FULL, &gentle_slope_uvs}, // TOP
    {{{16, 0, 16}, {0, 0, 16},  {16, 0, 0}, {0, 0, 0}},  MB64_DIRECTION_DOWN,  MB64_FACESHAPE_FULL, 0, NULL}, // BOTTOM
    {{{16, 16, 0}, {16, 0, 0},  {0, 16, 0}, {0, 0, 0}},  MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_FULL, MB64_GROWTH_NORMAL_SIDE, NULL}, // BACK
    {{{0, 8, 16},  {0, 0, 16},  {16, 8, 16}, {16, 0, 16}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_BOTTOMSLAB, MB64_GROWTH_UNCONDITIONAL, &bottomslab_decal_uvs1}, // FRONT
    {{{16, 8, 16}, {16, 0, 16}, {16, 8, 0},  {16, 0, 0}},  MB64_DIRECTION_POS_X, MB64_FACESHAPE_BOTTOMSLAB, MB64_GROWTH_UNCONDITIONAL, &ugentle_decal_quad_uvs1}, // LEFT
    {{{0, 8, 0},   {0, 0, 0},   {0, 8, 16},  {0, 0, 16}},  MB64_DIRECTION_NEG_X, MB64_FACESHAPE_BOTTOMSLAB, MB64_GROWTH_UNCONDITIONAL, &ugentle_decal_quad_uvs2}, // RIGHT
};

struct mb64_terrain_poly mb64_terrain_ugentle_tris[] = {
    {{{16, 8, 0}, {16, 16, 0}, {16, 8, 16}}, MB64_DIRECTION_POS_X, MB64_FACESHAPE_UPPERGENTLE_1, MB64_GROWTH_UNCONDITIONAL, &gentle_decal_tri_uvs1}, // LEFT
    {{{0, 16, 0}, {0, 8, 0},   {0, 8, 16}},  MB64_DIRECTION_NEG_X, MB64_FACESHAPE_UPPERGENTLE_2, MB64_GROWTH_UNCONDITIONAL, &gentle_decal_tri_uvs2}, // RIGHT
};

struct mb64_terrain mb64_terrain_ugentle = {
    6,
    2,
    mb64_terrain_ugentle_quads,
    mb64_terrain_ugentle_tris,
};

struct mb64_terrain_poly mb64_terrain_dugentle_quads[] = {
    {{{16, 16, 16}, {16, 16, 0}, {0, 16, 16},  {0, 16, 0}}, MB64_DIRECTION_UP,    MB64_FACESHAPE_FULL, MB64_GROWTH_FULL, NULL}, // TOP
    {{{16, 16, 0},  {16, 0, 0},  {0, 16, 0},   {0, 0, 0}},  MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_FULL, MB64_GROWTH_NORMAL_SIDE, NULL}, // BACK
    {{{16, 0, 0},   {16, 8, 16}, {0, 0, 0},    {0, 8, 16}},  MB64_DIRECTION_DOWN, MB64_FACESHAPE_EMPTY_2, MB64_GROWTH_NONE, &gentle_slope_uvs}, // BOTTOM
    {{{0, 16, 16},  {0, 8, 16},  {16, 16, 16}, {16, 8, 16}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_TOPSLAB, MB64_GROWTH_NORMAL_SIDE, NULL}, // FRONT
    {{{16, 16, 16}, {16, 8, 16}, {16, 16, 0},  {16, 8, 0}},  MB64_DIRECTION_POS_X, MB64_FACESHAPE_TOPSLAB, MB64_GROWTH_NORMAL_SIDE, NULL}, // LEFT
    {{{0, 16, 0},   {0, 8, 0},   {0, 16, 16},  {0, 8, 16}},  MB64_DIRECTION_NEG_X, MB64_FACESHAPE_TOPSLAB, MB64_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
};

struct mb64_terrain_poly mb64_terrain_dugentle_tris[] = {
    {{{16, 0, 0}, {16, 8, 0}, {16, 8, 16}},  MB64_DIRECTION_POS_X, MB64_FACESHAPE_DOWNUPPERGENTLE_1, MB64_GROWTH_NONE, NULL}, // LEFT
    {{{0, 8, 0}, {0, 0, 0},   {0, 8, 16}},   MB64_DIRECTION_NEG_X, MB64_FACESHAPE_DOWNUPPERGENTLE_2, MB64_GROWTH_NONE, NULL}, // RIGHT
};

struct mb64_terrain mb64_terrain_dugentle = {
    6,
    2,
    mb64_terrain_dugentle_quads,
    mb64_terrain_dugentle_tris,
};

struct mb64_terrain_poly mb64_terrain_lgentle_quads[] = {
    {{{16, 0, 16}, {16, 8, 0}, {0, 0, 16}, {0, 8, 0}}, MB64_DIRECTION_UP,    MB64_FACESHAPE_EMPTY_2, MB64_GROWTH_FULL, &gentle_slope_uvs}, // TOP
    {{{16, 0, 16}, {0, 0, 16},  {16, 0, 0}, {0, 0, 0}},  MB64_DIRECTION_DOWN,  MB64_FACESHAPE_FULL, 0, NULL}, // BOTTOM
    {{{16, 8, 0},  {16, 0, 0},  {0, 8, 0},   {0, 0, 0}},   MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_BOTTOMSLAB, MB64_GROWTH_UNCONDITIONAL, &bottomslab_decal_uvs1}, // BACK
};

struct mb64_terrain_poly mb64_terrain_lgentle_tris[] = {
    {{{16, 0, 0}, {16, 8, 0}, {16, 0, 16}}, MB64_DIRECTION_POS_X, MB64_FACESHAPE_LOWERGENTLE_1, MB64_GROWTH_GENTLE_SIDE_L, &gentle_decal_tri_uvs1}, // LEFT
    {{{0, 8, 0}, {0, 0, 0},   {0, 0, 16}},  MB64_DIRECTION_NEG_X, MB64_FACESHAPE_LOWERGENTLE_2, MB64_GROWTH_GENTLE_SIDE_R, &gentle_decal_tri_uvs2}, // RIGHT
};

struct mb64_terrain mb64_terrain_lgentle = {
    3,
    2,
    mb64_terrain_lgentle_quads,
    mb64_terrain_lgentle_tris,
};

s8 dlgentle_decal_uvs[4][2] = {{0, 16}, {16, 16}, {0, 8}, {16, 8}};

struct mb64_terrain_poly mb64_terrain_dlgentle_quads[] = {
    {{{16, 16, 16}, {16, 16, 0}, {0, 16, 16}, {0, 16, 0}}, MB64_DIRECTION_UP,    MB64_FACESHAPE_FULL, MB64_GROWTH_FULL, NULL}, // TOP
    {{{16, 16, 0},  {16, 8, 0},  {0, 16, 0},   {0, 8, 0}}, MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_TOPSLAB, MB64_GROWTH_NORMAL_SIDE, NULL}, // BACK
    {{{16, 8, 0},   {16, 16, 16}, {0, 8, 0},    {0, 16, 16}},  MB64_DIRECTION_DOWN, MB64_FACESHAPE_EMPTY_2, MB64_GROWTH_NORMAL_SIDE, &gentle_slope_uvs}, // BOTTOM
};

struct mb64_terrain_poly mb64_terrain_dlgentle_tris[] = {
    {{{16, 8, 0}, {16, 16, 0}, {16, 16, 16}},  MB64_DIRECTION_POS_X, MB64_FACESHAPE_DOWNLOWERGENTLE_1, MB64_GROWTH_NORMAL_SIDE, NULL}, // LEFT
    {{{0, 16, 0}, {0, 8, 0},   {0, 16, 16}},   MB64_DIRECTION_NEG_X, MB64_FACESHAPE_DOWNLOWERGENTLE_2, MB64_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
};

struct mb64_terrain mb64_terrain_dlgentle = {
    3,
    2,
    mb64_terrain_dlgentle_quads,
    mb64_terrain_dlgentle_tris,
};


struct mb64_terrain_poly mb64_terrain_slopebelowdecal_quad = {
    {{0, 16, 16}, {0, 0, 16}, {16, 16, 16}, {16, 0, 16}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_FULL, 0, NULL
};
struct mb64_terrain_poly mb64_terrain_slopebelowdecal_downtri1 = {
    {{16, 16, 16}, {0, 16, 16}, {16, 0, 16}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_DOWNTRI_1, 0, NULL
};
struct mb64_terrain_poly mb64_terrain_slopebelowdecal_downtri2 = {
    {{0, 16, 16}, {0, 0, 16}, {16, 16, 16}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_DOWNTRI_2, 0, NULL
};
struct mb64_terrain_poly mb64_terrain_slopebelowdecal_topslab = {
    {{0, 16, 16}, {0, 8, 16}, {16, 16, 16}, {16, 8, 16}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_TOPSLAB, 0, NULL
};
struct mb64_terrain_poly mb64_terrain_slopebelowdecal_vslab_1 = {
    {{8, 16, 16}, {8, 0, 16}, {16, 16, 16}, {16, 0, 16}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_HALFSIDE_1, 0, NULL
};
struct mb64_terrain_poly mb64_terrain_slopebelowdecal_vslab_2 = {
    {{0, 16, 16}, {0, 0, 16}, {8, 16, 16}, {8, 0, 16}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_HALFSIDE_2, 0, NULL
};
struct mb64_terrain_poly mb64_terrain_slopebelowdecal_downlowergentle1 = {
    {{16, 16, 16}, {0, 16, 16}, {16, 8, 16}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_DOWNLOWERGENTLE_1, 0, NULL
};
struct mb64_terrain_poly mb64_terrain_slopebelowdecal_downlowergentle2 = {
    {{0, 16, 16}, {0, 8, 16}, {16, 16, 16}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_DOWNLOWERGENTLE_2, 0, NULL
};

void *slope_decal_below_surfs[] = {
    &mb64_terrain_slopebelowdecal_quad,
    &mb64_terrain_slopebelowdecal_downtri1,
    &mb64_terrain_slopebelowdecal_downtri2,
    &mb64_terrain_slopebelowdecal_topslab,
    &mb64_terrain_slopebelowdecal_vslab_1,
    &mb64_terrain_slopebelowdecal_vslab_2,
    &mb64_terrain_slopebelowdecal_downlowergentle1,
    &mb64_terrain_slopebelowdecal_downlowergentle2,
};

// Shape of fence

s8 fence_uvs[4][2] = {{32, 16},  {32, 0},  {0, 16},  {0, 0}};
struct mb64_terrain_poly mb64_terrain_fence_quad[] = {
    {{{0, 8, 0}, {0, 0, 0}, {16, 8, 0}, {16, 0, 0}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_EMPTY, 0, &fence_uvs}, // FRONT (towards tile)
    {{{16, 8, 0}, {16, 0, 0}, {0, 8, 0}, {0, 0, 0}}, MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_BOTTOMSLAB, 0, &fence_uvs}, // BACK (away from tile)
};

struct mb64_terrain_poly mb64_terrain_fence_col_quads[] = {
    {{{16, 7, 1},  {0, 7, 1},   {16, 0, 1}, {0, 0, 1}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_EMPTY, 0, NULL}, // FRONT (towards tile)
    {{{16, 7, -1}, {16, 0, -1}, {0, 7, -1}, {0, 0, -1}}, MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_BOTTOMSLAB, 0, NULL}, // BACK (away from tile)

    {{{16, 8, 0},  {0, 8, 0},   {16, 7, 1}, {0, 7, 1}}, MB64_DIRECTION_UP, MB64_FACESHAPE_EMPTY, 0, NULL}, // FRONT (towards tile)
    {{{16, 8, 0},  {16, 7, -1}, {0, 8, 0},  {0, 7, -1}}, MB64_DIRECTION_UP, MB64_FACESHAPE_EMPTY, 0, NULL}, // BACK (away from tile)
};

struct mb64_terrain mb64_terrain_fence = {
    2,
    0,
    mb64_terrain_fence_quad,
    NULL,
};

struct mb64_terrain mb64_terrain_fence_col = {
    4,
    0,
    mb64_terrain_fence_col_quads,
    NULL,
};


s8 pole_uvs1[4][2] = {{16, 32}, {16, 0}, {12, 32}, {12, 0}};
s8 pole_uvs2[4][2] = {{12, 32}, {12, 0}, {8, 32}, {8, 0}};
s8 pole_uvs3[4][2] = {{8, 32}, {8, 0}, {4, 32}, {4, 0}};
s8 pole_uvs4[4][2] = {{4, 32}, {4, 0}, {0, 32}, {0, 0}};
struct mb64_terrain_poly mb64_terrain_pole_quads[] = {
    {{{8, 16, 9}, {8, 0, 9}, {9, 16, 8}, {9, 0, 8}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_EMPTY, 0, &pole_uvs1}, // Diagonal 1
    {{{9, 16, 8}, {9, 0, 8}, {8, 16, 7}, {8, 0, 7}}, MB64_DIRECTION_POS_X, MB64_FACESHAPE_EMPTY, 0, &pole_uvs2}, // Diagonal 2
    {{{8, 16, 7}, {8, 0, 7}, {7, 16, 8}, {7, 0, 8}}, MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_EMPTY, 0, &pole_uvs3}, // Diagonal 3
    {{{7, 16, 8}, {7, 0, 8}, {8, 16, 9}, {8, 0, 9}}, MB64_DIRECTION_NEG_X, MB64_FACESHAPE_EMPTY, 0, &pole_uvs4}, // Diagonal 4

    {{{8, 16, 9}, {9, 16, 8}, {7, 16, 8}, {8, 16, 7}}, MB64_DIRECTION_UP,   MB64_FACESHAPE_POLETOP, 0, NULL}, // Top
    {{{8, 0, 9},  {7, 0, 8},  {9, 0, 8},  {8, 0, 7}},  MB64_DIRECTION_DOWN, MB64_FACESHAPE_POLETOP, 0, NULL}, // Bottom
};

struct mb64_terrain mb64_terrain_pole = {
    6,
    0,
    mb64_terrain_pole_quads,
    NULL,
};

struct mb64_terrain_poly mb64_terrain_bars_connected_quads[] = {
    {{{7, 16, 16}, {7, 16, 9}, {7, 0, 16}, {7, 0, 9}}, MB64_DIRECTION_NEG_X, MB64_FACESHAPE_EMPTY, 0, NULL}, // Left
    {{{9, 16, 9}, {9, 16, 16}, {9, 0, 9}, {9, 0, 16}}, MB64_DIRECTION_POS_X, MB64_FACESHAPE_EMPTY, 0, NULL}, // Right

    {{{7, 16, 16}, {9, 16, 16}, {7, 16, 9}, {9, 16, 9}}, MB64_DIRECTION_UP, MB64_FACESHAPE_EMPTY, 0, NULL}, // Top
    {{{9, 0, 16}, {7, 0, 16}, {9, 0, 9}, {7, 0, 9}}, MB64_DIRECTION_DOWN, MB64_FACESHAPE_EMPTY, 0, NULL}, // Bottom
};

struct mb64_terrain_poly mb64_terrain_bars_unconnected_quad[] = {
    {{{9, 16, 9}, {7, 16, 9}, {9, 0, 9}, {7, 0, 9}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_EMPTY, 0, NULL}, // Back
};

struct mb64_terrain_poly mb64_terrain_bars_center_quads[] = {
    {{{7, 16, 9}, {9, 16, 9}, {7, 16, 7}, {9, 16, 7}}, MB64_DIRECTION_UP, MB64_FACESHAPE_EMPTY, 0, NULL},
    {{{9, 0, 9}, {7, 0, 9}, {9, 0, 7}, {7, 0, 7}}, MB64_DIRECTION_DOWN, MB64_FACESHAPE_EMPTY, 0, NULL},
};

// Shapes of water tiles
struct mb64_terrain_poly mb64_terrain_shallowwater_quads[] = {
    {{{16, 14, 16}, {16, 14, 0}, {0, 14, 16}, {0, 14, 0}}, MB64_DIRECTION_UP, MB64_FACESHAPE_EMPTY, 0, NULL}, // TOP
    {{{16, 0, 16},  {0, 0, 16},  {16, 0, 0},  {0, 0, 0}},  MB64_DIRECTION_DOWN, MB64_FACESHAPE_FULL, 0, NULL}, // BOTTOM
    {{{16, 14, 16}, {16, 0, 16}, {16, 14, 0}, {16, 0, 0}}, MB64_DIRECTION_POS_X, MB64_FACESHAPE_FULL, 0, NULL}, // LEFT
    {{{0, 14, 16},  {0, 14, 0},  {0, 0, 16},  {0, 0, 0}},  MB64_DIRECTION_NEG_X, MB64_FACESHAPE_FULL, 0, NULL}, // RIGHT
    {{{16, 14, 16}, {0, 14, 16}, {16, 0, 16}, {0, 0, 16}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_FULL, 0, NULL}, // FRONT
    {{{16, 14, 0},  {16, 0, 0},  {0, 14, 0},  {0, 0, 0}},  MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_FULL, 0, NULL}, // BACK
};

struct mb64_terrain_poly mb64_terrain_topwater_quads[] = {
    {{{16, 16, 16}, {16, 16, 0}, {0, 16, 16}, {0, 16, 0}}, MB64_DIRECTION_UP, MB64_FACESHAPE_FULL, 0, NULL}, // TOP
    {{{16, 0, 16},  {0, 0, 16},  {16, 0, 0},  {0, 0, 0}},  MB64_DIRECTION_DOWN, MB64_FACESHAPE_FULL, 0, NULL}, // BOTTOM
    {{{16, 16, 16}, {16, 14, 16}, {16, 16, 0}, {16, 14, 0}}, MB64_DIRECTION_POS_X, MB64_FACESHAPE_FULL, 0, NULL}, // LEFT
    {{{0, 16, 16},  {0, 16, 0},  {0, 14, 16},  {0, 14, 0}},  MB64_DIRECTION_NEG_X, MB64_FACESHAPE_FULL, 0, NULL}, // RIGHT
    {{{16, 16, 16}, {0, 16, 16}, {16, 14, 16}, {0, 14, 16}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_FULL, 0, NULL}, // FRONT
    {{{16, 16, 0},  {16, 14, 0},  {0, 16, 0},  {0, 14, 0}}, MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_FULL, 0, NULL}, // BACK
};

struct mb64_terrain_poly *mb64_terrain_water_quadlists[] = {
    mb64_terrain_shallowwater_quads,
    mb64_terrain_fullblock_quads,
    mb64_terrain_topwater_quads,
};

struct mb64_terrain_info mb64_terrain_info_list[] = {
    {NULL, NULL, NULL},
    {NULL, NULL, NULL},
    {"Slope", &mb64_btn_slope, &mb64_terrain_slope},
    {NULL, NULL, &mb64_terrain_dslope},
    {"Slab", &mb64_btn_slab, &mb64_terrain_bottomslab},
    {NULL, NULL, &mb64_terrain_topslab},
    {"Outer Corner", &mb64_btn_outercorner, &mb64_terrain_corner},
    {NULL, NULL, &mb64_terrain_dcorner},
    {"Inner Corner", &mb64_btn_innercorner, &mb64_terrain_icorner},
    {NULL, NULL, &mb64_terrain_dicorner},
    {"Sloped Corner", &mb64_btn_cornerslope, &mb64_terrain_scorner},
    {NULL, NULL, &mb64_terrain_dscorner},
    {"Inverted Sloped Corner", &mb64_btn_invertedcorner, &mb64_terrain_iscorner},
    {NULL, NULL, &mb64_terrain_discorner},
    {"Upper Gentle Slope", &mb64_btn_uppergentle, &mb64_terrain_ugentle},
    {NULL, NULL, &mb64_terrain_dugentle},
    {"Lower Gentle Slope", &mb64_btn_lowergentle, &mb64_terrain_lgentle},
    {NULL, NULL, &mb64_terrain_dlgentle},

    {"Tile", &mb64_btn_block, &mb64_terrain_fullblock},
    {"Vertical Slope", &mb64_btn_verticalslope, &mb64_terrain_sslope},
    {"Vertical Slab", &mb64_btn_verticalslab, &mb64_terrain_vslab},
    {"Cull Marker", &mb64_btn_cullmarker, NULL},
    {"Intangible Tile", &mb64_btn_intangible, &mb64_terrain_fullblock},
    {"Fence", &mb64_btn_fence, NULL},
    {"Pole", &mb64_btn_pole, NULL},
    {"Iron Mesh", &mb64_btn_ironmesh, NULL},
    {"Water", &mb64_btn_water, NULL},
};

