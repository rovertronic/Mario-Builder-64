f32 mb64_camera_zoom_table[][2] = {
    {900.0f,50.0f},
    {900.0f,400.0f},
    {1500.0f,800.0f},
    {2000.0f,900.0f},
    {2100.0f,1500.0f},
};

void* mb64_theme_segments[][4] = {
    {_group17_yay0SegmentRomStart, _group17_yay0SegmentRomEnd, _group17_geoSegmentRomStart, _group17_geoSegmentRomEnd}, //MB64_GAME_VANILLA
    {_group14_yay0SegmentRomStart, _group14_yay0SegmentRomEnd, _group14_geoSegmentRomStart, _group14_geoSegmentRomEnd}, //MB64_GAME_BTCM
};
LevelScript * mb64_theme_model_scripts[] = {
    script_func_mb64_theme_vanilla,
    script_func_mb64_theme_btcm,
};


// lookup table for rotating blocks
u8 mb64_rotated_dirs[4][6] = {
    {MB64_DIRECTION_UP, MB64_DIRECTION_DOWN, MB64_DIRECTION_POS_X, MB64_DIRECTION_NEG_X, MB64_DIRECTION_POS_Z, MB64_DIRECTION_NEG_Z},
    {MB64_DIRECTION_UP, MB64_DIRECTION_DOWN, MB64_DIRECTION_NEG_Z, MB64_DIRECTION_POS_Z, MB64_DIRECTION_POS_X, MB64_DIRECTION_NEG_X},
    {MB64_DIRECTION_UP, MB64_DIRECTION_DOWN, MB64_DIRECTION_NEG_X, MB64_DIRECTION_POS_X, MB64_DIRECTION_NEG_Z, MB64_DIRECTION_POS_Z},
    {MB64_DIRECTION_UP, MB64_DIRECTION_DOWN, MB64_DIRECTION_POS_Z, MB64_DIRECTION_NEG_Z, MB64_DIRECTION_NEG_X, MB64_DIRECTION_POS_X},
};

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

    {{{16, 8, 0},  {0, 8, 0},   {16, 7, 1}, {0, 7, 1}}, MB64_DIRECTION_POS_Z, MB64_FACESHAPE_EMPTY, 0, NULL}, // FRONT (towards tile)
    {{{16, 8, 0},  {16, 7, -1}, {0, 8, 0},  {0, 7, -1}}, MB64_DIRECTION_NEG_Z, MB64_FACESHAPE_BOTTOMSLAB, 0, NULL}, // BACK (away from tile)
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


s8 pole_uvs1[4][2] = {{16, 0}, {16, 32}, {12, 0}, {12, 32}};
s8 pole_uvs2[4][2] = {{12, 0}, {12, 32}, {8, 0}, {8, 32}};
s8 pole_uvs3[4][2] = {{8, 0}, {8, 32}, {4, 0}, {4, 32}};
s8 pole_uvs4[4][2] = {{4, 0}, {4, 32}, {0, 0}, {0, 32}};
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

enum {
    TILE_TYPE_EMPTY,
    // Flippable tiles
    TILE_TYPE_SLOPE = 2,
    TILE_TYPE_DSLOPE,
    TILE_TYPE_SLAB,
    TILE_TYPE_DSLAB,
    TILE_TYPE_CORNER,
    TILE_TYPE_DCORNER,
    TILE_TYPE_ICORNER,
    TILE_TYPE_DICORNER,
    TILE_TYPE_SCORNER,
    TILE_TYPE_DSCORNER,
    TILE_TYPE_UGENTLE,
    TILE_TYPE_DUGENTLE,
    TILE_TYPE_LGENTLE,
    TILE_TYPE_DLGENTLE,

    TILE_END_OF_FLIPPABLE,
    TILE_TYPE_BLOCK = TILE_END_OF_FLIPPABLE,
    TILE_TYPE_SSLOPE,
    TILE_TYPE_SSLAB,
    TILE_TYPE_CULL,
    TILE_TYPE_TROLL,
    TILE_TYPE_FENCE,
    TILE_TYPE_POLE,
    TILE_TYPE_BARS,

    TILE_TYPE_WATER, // only blocks that are empty otherwise
};

struct mb64_terrain_info {
    char *name;
    Gfx *button;
    struct mb64_terrain *terrain;
};

struct mb64_terrain_info mb64_terrain_info_list[] = {
    {NULL, NULL, NULL},
    {NULL, NULL, NULL},
    {"Slope", mat_b_btn_slope, &mb64_terrain_slope},
    {NULL, mat_b_btn_slope, &mb64_terrain_dslope},
    {"Slab", mat_b_btn_slabtile, &mb64_terrain_bottomslab},
    {NULL, mat_b_btn_slabtile, &mb64_terrain_topslab},
    {"Outer Corner", mat_b_btn_corner, &mb64_terrain_corner},
    {NULL, mat_b_btn_corner, &mb64_terrain_dcorner},
    {"Inner Corner", mat_b_btn_icorner, &mb64_terrain_icorner},
    {NULL, mat_b_btn_icorner, &mb64_terrain_dicorner},
    {"Sloped Corner", mat_b_btn_triangle, &mb64_terrain_scorner},
    {NULL, mat_b_btn_corner, &mb64_terrain_dscorner},
    {"Upper Gentle Slope", mat_b_btn_ugs, &mb64_terrain_ugentle},
    {NULL, mat_b_btn_slope, &mb64_terrain_dugentle},
    {"Lower Gentle Slope", mat_b_btn_lgs, &mb64_terrain_lgentle},
    {NULL, mat_b_btn_slope, &mb64_terrain_dlgentle},

    {"Tile", mat_b_btn_tile, &mb64_terrain_fullblock},
    {"Vertical Slope", mat_b_btn_sideslope, &mb64_terrain_sslope},
    {"Vertical Slab", mat_b_btn_vslab, &mb64_terrain_vslab},
    {"Cull Marker", mat_b_btn_cull, NULL},
    {"Intangible Tile", mat_b_btn_troll, &mb64_terrain_fullblock},
    {"Fence", mat_b_btn_fence, NULL},
    {"Pole", mat_b_btn_pole, NULL},
    {"Iron Mesh", mat_b_btn_bars, NULL},
    {"Water", mat_b_btn_water, NULL},
};

struct mb64_boundary_quad floor_boundary[] = {
    {{{32, 0, 32}, {32, 0, 0}, {0, 0, 32}, {0, 0, 0}}, {-16, 16}, {-16, 16}, FALSE, FALSE, FALSE},
    {{{0, 0, 32}, {0, 0, 0}, {-32, 0, 32}, {-32, 0, 0}}, {-16, 16}, {-16, 16}, FALSE, FALSE, FALSE},
    {{{32, 0, 0}, {32, 0, -32}, {0, 0, 0}, {0, 0, -32}}, {-16, 16}, {-16, 16}, FALSE, FALSE, FALSE},
    {{{0, 0, 0}, {0, 0, -32}, {-32, 0, 0}, {-32, 0, -32}}, {-16, 16}, {-16, 16}, FALSE, FALSE, FALSE},
};

struct mb64_boundary_quad floor_edge_boundary[] = {
    {{{48, 0, 32}, {48, 0, 0}, {32, 0, 32}, {32, 0, 0}}, {-16, 16}, {-8, 8}, FALSE, FALSE, FALSE},
    {{{48, 0, 32}, {32, 0, 32}, {48, 0, 48}, {32, 0, 48}}, {-8, 8}, {8, -8}, FALSE, FALSE, TRUE},
    {{{32, 0, 48}, {32, 0, 32}, {0, 0, 48}, {0, 0, 32}}, {-8, 8}, {-16, 16}, FALSE, FALSE, FALSE},

    {{{-32, 0, 32}, {-32, 0, 0}, {-48, 0, 32}, {-48, 0, 0}}, {-16, 16}, {-8, 8}, FALSE, FALSE, FALSE},
    {{{-32, 0, 48}, {-32, 0, 32}, {-48, 0, 48}, {-48, 0, 32}}, {-8, 8}, {-8, 8}, FALSE, FALSE, FALSE},
    {{{0, 0, 48}, {0, 0, 32}, {-32, 0, 48}, {-32, 0, 32}}, {-8, 8}, {-16, 16}, FALSE, FALSE, FALSE},

    {{{48, 0, 0}, {48, 0, -32}, {32, 0, 0}, {32, 0, -32}}, {-16, 16}, {-8, 8}, FALSE, FALSE, FALSE},
    {{{48, 0, -32}, {48, 0, -48}, {32, 0, -32}, {32, 0, -48}}, {-8, 8}, {-8, 8}, FALSE, FALSE, FALSE},
    {{{32, 0, -32}, {32, 0, -48}, {0, 0, -32}, {0, 0, -48}}, {-8, 8}, {-16, 16}, FALSE, FALSE, FALSE},

    {{{-32, 0, 0}, {-32, 0, -32}, {-48, 0, 0}, {-48, 0, -32}}, {-16, 16}, {-8, 8}, FALSE, FALSE, FALSE},
    {{{-32, 0, -48}, {-48, 0, -48}, {-32, 0, -32}, {-48, 0, -32}}, {-8, 8}, {8, -8}, FALSE, FALSE, TRUE},
    {{{0, 0, -32}, {0, 0, -48}, {-32, 0, -32}, {-32, 0, -48}}, {-8, 8}, {-16, 16}, FALSE, FALSE, FALSE},
};

struct mb64_boundary_quad wall_boundary[] = {
    {{{32, 1, 0}, {32, 1, -32}, {32, 0, 0}, {32, 0, -32}}, {16, -16}, {-8, 8}, FALSE, TRUE, FALSE},
    {{{32, 1, 32}, {32, 1, 0}, {32, 0, 32}, {32, 0, 0}}, {16, -16}, {-8, 8}, FALSE, TRUE, FALSE},

    {{{0, 1, 32}, {32, 1, 32}, {0, 0, 32}, {32, 0, 32}}, {16, -16}, {-8, 8}, FALSE, TRUE, FALSE},
    {{{-32, 1, 32}, {0, 1, 32}, {-32, 0, 32}, {0, 0, 32}}, {16, -16}, {-8, 8}, FALSE, TRUE, FALSE},

    {{{-32, 1, 0}, {-32, 1, 32}, {-32, 0, 0}, {-32, 0, 32}}, {16, -16}, {-8, 8}, FALSE, TRUE, FALSE},
    {{{-32, 1, -32}, {-32, 1, 0}, {-32, 0, -32}, {-32, 0, 0}}, {16, -16}, {-8, 8}, FALSE, TRUE, FALSE},

    {{{0, 1, -32}, {-32, 1, -32}, {0, 0, -32}, {-32, 0, -32}}, {16, -16}, {-8, 8}, FALSE, TRUE, FALSE},
    {{{32, 1, -32}, {0, 1, -32}, {32, 0, -32}, {0, 0, -32}}, {16, -16}, {-8, 8}, FALSE, TRUE, FALSE},
};

extern Gfx mat_maker_MakerMCWater[];
extern Gfx mat_maker_MakerMCLava[];
extern Gfx mat_maker_MakerMCFlowingLava[];

enum mb64_materials {
    MB64_MATLIST_START,

    // Terrain
    MB64_MAT_GRASS = MB64_MATLIST_START,
    MB64_MAT_GRASS_OLD,
    MB64_MAT_CARTOON_GRASS,
    MB64_MAT_DARK_GRASS,
    MB64_MAT_HMC_GRASS,
    MB64_MAT_ORANGE_GRASS,
    MB64_MAT_RED_GRASS,
    MB64_MAT_PURPLE_GRASS,
    MB64_MAT_SAND,
    MB64_MAT_JRB_SAND,
    MB64_MAT_SNOW,
    MB64_MAT_SNOW_OLD,

    MB64_MAT_DIRT,
    MB64_MAT_SANDDIRT,
    MB64_MAT_LIGHTDIRT,
    MB64_MAT_HMC_DIRT,
    MB64_MAT_ROCKY_DIRT,
    MB64_MAT_DIRT_OLD,
    MB64_MAT_WAVY_DIRT,
    MB64_MAT_WAVY_DIRT_BLUE,
    MB64_MAT_SNOWDIRT,
    MB64_MAT_PURPLE_DIRT,
    MB64_MAT_HMC_LAKEGRASS,

    MB64_MATLIST_TERRAIN_END,

    // Stone
    MB64_MAT_STONE = MB64_MATLIST_TERRAIN_END,
    MB64_MAT_HMC_STONE,
    MB64_MAT_HMC_MAZEFLOOR,
    MB64_MAT_CCM_ROCK,
    MB64_MAT_TTM_FLOOR,
    MB64_MAT_TTM_ROCK,
    MB64_MAT_COBBLESTONE,
    MB64_MAT_JRB_WALL,
    MB64_MAT_GABBRO,
    MB64_MAT_RHR_STONE,
    MB64_MAT_LAVA_ROCKS,
    MB64_MAT_VOLCANO_WALL,
    MB64_MAT_RHR_BASALT,
    MB64_MAT_OBSIDIAN,
    MB64_MAT_CASTLE_STONE,
    MB64_MAT_JRB_UNDERWATER,
    MB64_MAT_SNOW_ROCK,
    MB64_MAT_ICY_ROCK,
    MB64_MAT_DESERT_STONE,
    MB64_MAT_RHR_OBSIDIAN,
    MB64_MAT_JRB_STONE,

    MB64_MATLIST_STONE_END,

    // Bricks
    MB64_MAT_BRICKS = MB64_MATLIST_STONE_END,
    MB64_MAT_DESERT_BRICKS,
    MB64_MAT_RHR_BRICK,
    MB64_MAT_HMC_BRICK,
    MB64_MAT_LIGHTBROWN_BRICK,
    MB64_MAT_WDW_BRICK,
    MB64_MAT_TTM_BRICK,
    MB64_MAT_C_BRICK,
    MB64_MAT_BBH_BRICKS,
    MB64_MAT_ROOF_BRICKS,
    MB64_MAT_C_OUTSIDEBRICK,
    MB64_MAT_SNOW_BRICKS,
    MB64_MAT_JRB_BRICKS,
    MB64_MAT_SNOW_TILE_SIDE,
    MB64_MAT_TILESBRICKS,

    MB64_MATLIST_BRICKS_END,

    // Tiling
    MB64_MAT_TILES = MB64_MATLIST_BRICKS_END,
    MB64_MAT_C_TILES,
    MB64_MAT_DESERT_TILES,
    MB64_MAT_VP_BLUETILES,
    MB64_MAT_SNOW_TILES,
    MB64_MAT_JRB_TILETOP,
    MB64_MAT_JRB_TILESIDE,
    MB64_MAT_HMC_TILES,
    MB64_MAT_GRANITE_TILES,
    MB64_MAT_RHR_TILES,
    MB64_MAT_VP_TILES,
    MB64_MAT_DIAMOND_PATTERN,
    MB64_MAT_C_STONETOP,
    MB64_MAT_SNOW_BRICK_TILES,

    MB64_MATLIST_TILES_END,

    // Cut Stone
    MB64_MAT_DESERT_BLOCK = MB64_MATLIST_TILES_END,
    MB64_MAT_VP_BLOCK,
    MB64_MAT_BBH_STONE,
    MB64_MAT_BBH_STONE_PATTERN,
    MB64_MAT_PATTERNED_BLOCK,
    MB64_MAT_HMC_SLAB,
    MB64_MAT_RHR_BLOCK,
    MB64_MAT_GRANITE_BLOCK,
    MB64_MAT_C_STONESIDE,
    MB64_MAT_C_PILLAR,
    MB64_MAT_BBH_PILLAR,
    MB64_MAT_RHR_PILLAR,

    MB64_MATLIST_CUTSTONE_END,

    // Wood
    MB64_MAT_WOOD = MB64_MATLIST_CUTSTONE_END,
    MB64_MAT_BBH_WOOD_FLOOR,
    MB64_MAT_BBH_WOOD_WALL,
    MB64_MAT_C_WOOD,
    MB64_MAT_JRB_WOOD,
    MB64_MAT_JRB_SHIPSIDE,
    MB64_MAT_JRB_SHIPTOP,
    MB64_MAT_BBH_HAUNTED_PLANKS,
    MB64_MAT_BBH_ROOF,
    MB64_MAT_SOLID_WOOD,
    MB64_MAT_RHR_WOOD,

    MB64_MATLIST_WOOD_END,

    // Metal
    MB64_MAT_BBH_METAL = MB64_MATLIST_WOOD_END,
    MB64_MAT_JRB_METALSIDE,
    MB64_MAT_JRB_METAL,
    MB64_MAT_C_BASEMENTWALL,
    MB64_MAT_DESERT_TILES2,
    MB64_MAT_VP_RUSTYBLOCK,

    MB64_MATLIST_METAL_END,

    // Buildings
    MB64_MAT_C_CARPET = MB64_MATLIST_METAL_END,
    MB64_MAT_C_WALL,
    MB64_MAT_ROOF,
    MB64_MAT_C_ROOF,
    MB64_MAT_SNOW_ROOF,
    MB64_MAT_BBH_WINDOW,
    MB64_MAT_HMC_LIGHT,
    MB64_MAT_VP_CAUTION,
    MB64_MAT_RR_BLOCKS,
    MB64_MAT_STUDDED_TILE,
    MB64_MAT_TTC_BLOCK,
    MB64_MAT_TTC_SIDE,
    MB64_MAT_TTC_WALL,
    MB64_MAT_FLOWERS,

    MB64_MATLIST_BUILDING_END,

    // Hazards
    MB64_MAT_LAVA = MB64_MATLIST_BUILDING_END,
    MB64_MAT_LAVA_OLD,
    MB64_MAT_SERVER_ACID,
    MB64_MAT_BURNING_ICE,
    MB64_MAT_QUICKSAND,
    MB64_MAT_DESERT_SLOWSAND,
    MB64_MAT_VP_VOID,

    MB64_MATLIST_HAZARD_END,
    
    // Transparent
    MB64_MAT_RHR_MESH = MB64_MATLIST_HAZARD_END,
    MB64_MAT_VP_MESH,
    MB64_MAT_HMC_MESH,
    MB64_MAT_BBH_MESH,
    MB64_MAT_PINK_MESH,
    MB64_MAT_TTC_MESH,
    MB64_MAT_ICE,
    MB64_MAT_CRYSTAL,
    MB64_MAT_VP_SCREEN,

    MB64_MATLIST_END,

    // Retro
    MB64_MAT_RETRO_GROUND = MB64_MATLIST_END,
    MB64_MAT_RETRO_BRICKS,
    MB64_MAT_RETRO_TREETOP,
    MB64_MAT_RETRO_TREEPLAT,
    MB64_MAT_RETRO_BLOCK,
    MB64_MAT_RETRO_BLUEGROUND,
    MB64_MAT_RETRO_BLUEBRICKS,
    MB64_MAT_RETRO_BLUEBLOCK,
    MB64_MAT_RETRO_WHITEBRICK,
    MB64_MAT_RETRO_LAVA,
    MB64_MAT_RETRO_UNDERWATERGROUND,

    // Minecraft
    MB64_MAT_MC_DIRT,
    MB64_MAT_MC_GRASS,
    MB64_MAT_MC_COBBLESTONE,
    MB64_MAT_MC_STONE,
    MB64_MAT_MC_OAK_LOG_TOP,
    MB64_MAT_MC_OAK_LOG_SIDE,
    MB64_MAT_MC_OAK_LEAVES,
    MB64_MAT_MC_WOOD_PLANKS,
    MB64_MAT_MC_SAND,
    MB64_MAT_MC_BRICKS,
    MB64_MAT_MC_LAVA,
    MB64_MAT_MC_FLOWING_LAVA,
    MB64_MAT_MC_GLASS,
};

u8 mb64_matlist[] = {
    MB64_MATLIST_START,
    MB64_MATLIST_TERRAIN_END,
    MB64_MATLIST_STONE_END,
    MB64_MATLIST_BRICKS_END,
    MB64_MATLIST_TILES_END,
    MB64_MATLIST_CUTSTONE_END,
    MB64_MATLIST_WOOD_END,
    MB64_MATLIST_METAL_END,
    MB64_MATLIST_BUILDING_END,
    MB64_MATLIST_HAZARD_END,
    MB64_MATLIST_END,
};
char *mb64_matlist_names[] = {
    "Terrain",
    "Stone",
    "Bricks",
    "Tiling",
    "Cut Stone",
    "Wood",
    "Metal",
    "Other",
    "Hazards",
    "Transparent",
};

struct mb64_material mb64_mat_table[] = {
    // Terrain
    {mat_maker_MakerGrass,        MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Grass"},       // MB64_MAT_GRASS
    {mat_maker_MakerVanillaGrass, MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Grass (Old)"}, // MB64_MAT_GRASS_OLD
    {mat_maker_MakerCartoonGrass, MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Smooth Grass"},// MB64_MAT_CARTOON_GRASS
    {mat_maker_MakerDarkGrass,    MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Dark Grass"},  // MB64_MAT_DARK_GRASS
    {mat_maker_MakerHGrass,       MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Cave Grass"},  // MB64_MAT_HMC_GRASS
    {mat_maker_MakerOrangeGrass,  MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Orange Grass"},// MB64_MAT_ORANGE_GRASS
    {mat_maker_MakerRedGrass,     MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Red Grass"},   // MB64_MAT_RED_GRASS
    {mat_maker_MakerPurpleGrass,  MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Purple Grass"},// MB64_MAT_PURPLE_GRASS
    {mat_maker_MakerSand,         MAT_OPAQUE, FALSE, SURFACE_SAND,         "Sand"},        // MB64_MAT_SAND
    {mat_maker_MakerJRBSand,      MAT_OPAQUE, FALSE, SURFACE_SAND,         "Ocean Sand"},  // MB64_MAT_JRB_SAND
    {mat_maker_MakerSnow,         MAT_OPAQUE, FALSE, SURFACE_SNOW,         "Snow"},        // MB64_MAT_SNOW
    {mat_maker_MakerVanillaSnow,  MAT_OPAQUE, FALSE, SURFACE_SNOW,         "Snow (Old)"},  // MB64_MAT_SNOW_OLD
    {mat_maker_MakerDirt,         MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Dirt"},        // MB64_MAT_DIRT
    {mat_maker_MakerSandDirt,     MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Sandy Dirt"},  // MB64_MAT_SANDDIRT
    {mat_maker_MakerLightDirt,    MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Light Dirt"},  // MB64_MAT_LIGHTDIRT
    {mat_maker_MakerHDirt,        MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Cave Dirt"},   // MB64_MAT_HMC_DIRT
    {mat_maker_MakerRockyDirt,    MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Rocky Dirt"},  // MB64_MAT_ROCKY_DIRT
    {mat_maker_MakerVanillaDirt,  MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY,  "Dirt (Old)"}, // MB64_MAT_DIRT_OLD
    {mat_maker_MakerWavyDirt,     MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Wavy Dirt"},   // MB64_MAT_WAVY_DIRT
    {mat_maker_MakerWavyDirtBlue, MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Wavy Dirt (Blue)"}, // MB64_MAT_WAVY_DIRT_BLUE
    {mat_maker_MakerSnowDirt,     MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Snowy Dirt"},  // MB64_MAT_SNOWDIRT
    {mat_maker_MakerPurpleDirt,   MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Purple Dirt"}, // MB64_MAT_PURPLE_DIRT
    {mat_maker_MakerHLakewall,    MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Clay"},        // MB64_MAT_HMC_LAKEGRASS

    // Stone
    {mat_maker_MakerStoneSide,     MAT_OPAQUE, FALSE, SURFACE_DEFAULT,      "White Stone"},     // MB64_MAT_STONE
    {mat_maker_MakerHStone,        MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Cave Stone"},      // MB64_MAT_HMC_STONE
    {mat_maker_MakerHMazefloor,    MAT_OPAQUE, FALSE, SURFACE_DEFAULT,      "Beige Stone"},     // MB64_MAT_HMC_MAZEFLOOR
    {mat_maker_MakerCCMWall,       MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Green Stone"},     // MB64_MAT_CCM_ROCK
    {mat_maker_MakerMountainFloor, MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Mountain Stone"},  // MB64_MAT_TTM_FLOOR
    {mat_maker_MakerMountainRock,  MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Mountain Rock"},   // MB64_MAT_TTM_ROCK
    {mat_maker_MakerStone,         MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "White Rock"},      // MB64_MAT_COBBLESTONE
    {mat_maker_MakerJRBWall,       MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Green Rock"},      // MB64_MAT_JRB_WALL
    {mat_maker_MakerBlackStone,    MAT_OPAQUE, FALSE, SURFACE_DEFAULT,      "Black Rock"},      // MB64_MAT_GABBRO
    {mat_maker_MakerRHRStone,      MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Scorched Rock"},   // MB64_MAT_RHR_STONE
    {mat_maker_MakerLavaRock,      MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Volcanic Rocks"},  // MB64_MAT_LAVA_ROCKS
    {mat_maker_MakerVolcanicRock,  MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Volcanic Wall"},   // MB64_MAT_VOLCANO_WALL
    {mat_maker_MakerRHRBasalt,     MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Basalt"},          // MB64_MAT_RHR_BASALT
    {mat_maker_MakerObsidian,      MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Obsidian"},        // MB64_MAT_OBSIDIAN
    {mat_maker_MakerCastleCobble,  MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Plum Concrete"},   // MB64_MAT_CASTLE_STONE
    {mat_maker_MakerJRBUnderwater, MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Ocean Floor"},     // MB64_MAT_JRB_UNDERWATER
    {mat_maker_MakerSnowRock,      MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Snowy Rock"},      // MB64_MAT_SNOW_ROCK
    {mat_maker_MakerIcyRock,       MAT_OPAQUE, TRUE,  SURFACE_VERY_SLIPPERY, "Icy Rock"},       // MB64_MAT_ICY_ROCK
    {mat_maker_MakerDStone,        MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Cobblestone (1)"}, // MB64_MAT_DESERT_STONE
    {mat_maker_MakerRHRObsidian,   MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Cobblestone (2)"}, // MB64_MAT_RHR_OBSIDIAN
    {mat_maker_MakerJRBStone,      MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Cobblestone (3)"}, // MB64_MAT_JRB_STONE

    // Bricks
    {mat_maker_MakerBricks,           MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Stone Bricks"},     // MB64_MAT_BRICKS
    {mat_maker_MakerDBrick,           MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Desert Bricks"},    // MB64_MAT_DESERT_BRICKS
    {mat_maker_MakerRHRBrick,         MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Scorched Bricks"},  // MB64_MAT_RHR_BRICK
    {mat_maker_MakerHBrick,           MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Cave Bricks"},      // MB64_MAT_HMC_BRICK
    {mat_maker_MakerLightBrownBricks, MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,    "Fortress Bricks"},  // MB64_MAT_LIGHTBROWN_BRICK
    {mat_maker_MakerBrownBricks,      MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Brown Bricks (1)"}, // MB64_MAT_WDW_BRICK
    {mat_maker_MakerTTMBricks,        MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Brown Bricks (2)"}, // MB64_MAT_TTM_BRICK
    {mat_maker_MakerCBrick,           MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Castle Bricks"},    // MB64_MAT_C_BRICK
    {mat_maker_MakerBBHBricks,        MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Red Bricks (1)"},   // MB64_MAT_BBH_BRICKS
    {mat_maker_MakerRoofBricks,       MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Red Bricks (2)"},   // MB64_MAT_ROOF_BRICKS
    {mat_maker_MakerCOutsideBricks,   MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "White Bricks (1)"}, // MB64_MAT_C_OUTSIDE_BRICK
    {mat_maker_MakerSnowBricks,       MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "White Bricks (2)"}, // MB64_MAT_SNOW_BRICKS
    {mat_maker_MakerJRBBricks,        MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Ocean Bricks"},     // MB64_MAT_JRB_BRICKS 
    {mat_maker_MakerSnowTileSide,     MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Blue Bricks"},      // MB64_MAT_SNOW_TILE_SIDE
    {mat_maker_MakerTileBricks,       MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Mixed Bricks"},     // MB64_MAT_TILESBRICKS

    // Tiling
    {mat_maker_MakerTiles,          MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Checkered Tiling"}, // MB64_MAT_TILES
    {mat_maker_MakerCTiles,         MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Castle Tiling"},    // MB64_MAT_C_TILES
    {mat_maker_MakerDTiles,         MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Desert Tiling"},    // MB64_MAT_DESERT_TILES
    {mat_maker_MakerVBlueTiles,     MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Blue Tiling (1)"},  // MB64_MAT_VP_BLUETILES
    {mat_maker_MakerSnowTiles,      MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Blue Tiling (2)"},  // MB64_MAT_SNOW_TILES
    {mat_maker_MakerJRBTileTop,     MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Ocean Tiling (1)"}, // MB64_MAT_JRB_TILETOP
    {mat_maker_MakerJRBTileSide,    MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Ocean Tiling (2)"}, // MB64_MAT_JRB_TILESIDE
    {mat_maker_MakerHTileTop,       MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Dark Tiling"},     // MB64_MAT_HMC_TILES
    {mat_maker_MakerGraniteTiles,   MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Granite Tiling"},   // MB64_MAT_GRANITE_TILES
    {mat_maker_MakerRHRTiles,       MAT_OPAQUE, FALSE, SURFACE_DEFAULT,      "Black Tiling"},    // MB64_MAT_RHR_TILES
    {mat_maker_MakerVTiles,         MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Grey Tiling"},     // MB64_MAT_VP_TILES
    {mat_maker_MakerDiamondPattern, MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Diamond Pattern"},  // MB64_MAT_DIAMOND_PATTERN
    {mat_maker_MakerCStone,         MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Hex Tiling"},       // MB64_MAT_C_STONETOP
    {mat_maker_MakerSnowBrickTiles, MAT_OPAQUE, FALSE, SURFACE_DEFAULT,      "Diamond Tiling"},   // MB64_MAT_SNOW_BRICK_TILES

    // Cut Stone
    {mat_maker_MakerDStoneBlock,     MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, "Block"},           // MB64_MAT_DESERT_BLOCK
    {mat_maker_MakerVBlock,          MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Smooth Block"},    // MB64_MAT_VP_BLOCK
    {mat_maker_MakerBBHWall,         MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Mansion Wall"},    // MB64_MAT_BBH_STONE
    {mat_maker_MakerBBHStonePattern, MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Chiseled Wall"},   // MB64_MAT_BBH_STONE_PATTERN
    {mat_maker_MakerLauncherTex,     MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Patterned Block"}, // MB64_MAT_PATTERNED_BLOCK
    {mat_maker_MakerHTileSide,       MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Black Slabs"},     // MB64_MAT_HMC_SLAB
    {mat_maker_MakerRHRPattern,      MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, "Chiseled Block"},  // MB64_MAT_RHR_BLOCK
    {mat_maker_MakerGraniteBlock,    MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, "Granite Block"},   // MB64_MAT_GRANITE_BLOCK
    {mat_maker_MakerCStoneSide,      MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Stone Slab"},      // MB64_MAT_C_STONESIDE
    {mat_maker_MakerCPillar,         MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Castle Pillar"},   // MB64_MAT_C_PILLAR
    {mat_maker_MakerBBHPillar,       MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Mansion Pillar"},  // MB64_MAT_BBH_PILLAR
    {mat_maker_MakerRHRPillar,       MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Scorched Pillar"}, // MB64_MAT_RHR_PILLAR

    // Wood
    {mat_maker_MakerWood,             MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Planks (1)"},    // MB64_MAT_WOOD
    {mat_maker_MakerBBHWoodWall,      MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Planks (2)"},    // MB64_MAT_BBH_WOOD_WALL
    {mat_maker_MakerBBHWoodFloor,     MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Dark Planks"},   // MB64_MAT_BBH_WOOD_FLOOR
    {mat_maker_MakerCWood,            MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Castle Planks"}, // MB64_MAT_C_WOOD
    {mat_maker_MakerJRBWood,          MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Docks"},         // MB64_MAT_JRB_WOOD
    {mat_maker_MakerJRBShipSide,      MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Ship Planks"},   // MB64_MAT_JRB_SHIPSIDE
    {mat_maker_MakerJRBShipTop,       MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Ship Decking"},  // MB64_MAT_JRB_SHIPTOP
    {mat_maker_MakerBBHHauntedPlanks, MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Spooky Planks"}, // MB64_MAT_BBH_HAUNTED_PLANKS
    {mat_maker_MakerBBHRoof,          MAT_OPAQUE, FALSE, SURFACE_CREAKWOOD,    "Mansion Roof"},  // MB64_MAT_BBH_ROOF
    {mat_maker_MakerSolidWood,        MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Wood (Old)"},    // MB64_MAT_SOLID_WOOD
    {mat_maker_MakerRHRWood,          MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Scorched Wood"}, // MB64_MAT_RHR_WOOD

    // Metal
    {mat_maker_MakerBBHMetal,        MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Metal Flooring"},   // MB64_MAT_BBH_METAL
    {mat_maker_MakerJRBMetalSide,    MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Metal Sheet"},      // MB64_MAT_JRB_METALSIDE
    {mat_maker_MakerJRBMetal,        MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Metal Plating"},    // MB64_MAT_JRB_METAL
    {mat_maker_MakerCBasementWall,   MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Basement Plating"}, // MB64_MAT_C_BASEMENTWALL
    {mat_maker_MakerDTiles2,         MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Desert Plating"},   // MB64_MAT_DESERT_TILES2
    {mat_maker_MakerVRustyBlock,     MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Rusted Block"},     // MB64_MAT_VP_RUSTYBLOCK

    // Other
    {mat_maker_MakerCCarpet,      MAT_OPAQUE, FALSE, SURFACE_GRASS,         "Carpet"},         // MB64_MAT_C_CARPET
    {mat_maker_MakerCWall,        MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,       "Castle Wall"},    // MB64_MAT_C_WALL
    {mat_maker_MakerRoof,         MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY,  "Roof"},           // MB64_MAT_ROOF
    {mat_maker_MakerCRoof,        MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY,  "Castle Roof"},    // MB64_MAT_C_ROOF
    {mat_maker_MakerSnowRoof,     MAT_OPAQUE, TRUE,  SURFACE_VERY_SLIPPERY, "Blue Roof"},      // MB64_MAT_SNOW_ROOF
    {mat_maker_MakerBBHWindow,    MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,       "Window"},         // MB64_MAT_BBH_WINDOW
    {mat_maker_MakerHLight,       MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,       "Lantern"},        // MB64_MAT_HMC_LIGHT
    {mat_maker_MakerCaution,      MAT_OPAQUE, FALSE, SURFACE_DEFAULT,       "Hazard Stripes"}, // MB64_MAT_VP_CAUTION
    {mat_maker_MakerRRBlocks,     MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,       "Rainbow Blocks"},  // MB64_MAT_RR_BLOCKS
    {mat_maker_MakerStuddedFloor, MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Studded Tile"},  // MB64_MAT_STUDDED_TILE
    {mat_maker_MakerYellowBlock,  MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,     "Yellow Block"},   // MB64_MAT_TTC_BLOCK
    {mat_maker_MakerTTCSide,      MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,       "Clock Platform"}, // MB64_MAT_TTC_SIDE
    {mat_maker_MakerTTCWall,      MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,       "Clock Exterior"}, // MB64_MAT_TTC_WALL
    {mat_maker_MakerFlowerTop,    MAT_OPAQUE, FALSE, SURFACE_GRASS,         "Flowers"},        // MB64_MAT_FLOWERS

    // Hazards
    {mat_maker_MakerLava,        MAT_OPAQUE, TRUE,  SURFACE_BURNING_BUBBLES,   "Lava"},           // MB64_MAT_LAVA
    {mat_maker_MakerVanillaLava, MAT_OPAQUE, TRUE,  SURFACE_BURNING_BUBBLES,  "Lava (Old)"},     // MB64_MAT_LAVA_OLD
    {mat_maker_MakerServerAcid,  MAT_OPAQUE, TRUE,  SURFACE_BURNING_ICE,       "Server Acid"},    // MB64_MAT_SERVER_ACID
    {mat_maker_MakerBurningIce,  MAT_OPAQUE, TRUE,  SURFACE_BURNING_ICE,       "Hazard Ice"},     // MB64_MAT_BURNING_ICE
    {mat_maker_MakerQuicksand,   MAT_OPAQUE, TRUE,  SURFACE_INSTANT_QUICKSAND, "Quicksand"},      // MB64_MAT_QUICKSAND
    {mat_maker_MakerSlowsand,    MAT_OPAQUE, FALSE, SURFACE_DEEP_QUICKSAND,    "Slow Quicksand"}, // MB64_MAT_DESERT_SLOWSAND
    {mat_maker_MakerVoid,        MAT_OPAQUE, TRUE,  SURFACE_INSTANT_QUICKSAND, "Cosmic Void"},           // MB64_MAT_VP_VOID

    // Seethrough
    {mat_maker_MakerRHRMesh, MAT_CUTOUT,      TRUE,  SURFACE_HANGABLE_MESH, "Mesh"},         // MB64_MAT_RHR_MESH
    {mat_maker_MakerVPMesh,  MAT_CUTOUT,      TRUE,  SURFACE_HANGABLE_MESH, "Fine Mesh"},    // MB64_MAT_VP_MESH
    {mat_maker_MakerHMesh,   MAT_CUTOUT,      TRUE,  SURFACE_HANGABLE_MESH, "Red Grille"},   // MB64_MAT_HMC_MESH
    {mat_maker_MakerBBHMesh, MAT_CUTOUT,      TRUE,  SURFACE_HANGABLE_MESH, "Red Mesh"},     // MB64_MAT_BBH_MESH
    {mat_maker_MakerGratePink, MAT_CUTOUT,    TRUE,  SURFACE_HANGABLE_MESH, "Pink Mesh"},    // MB64_MAT_PINK_MESH
    {mat_maker_MakerTTCGrate, MAT_CUTOUT,     TRUE,  SURFACE_HANGABLE_MESH, "Clock Grille"}, // MB64_MAT_TTC_MESH
    {mat_maker_MakerIce,     MAT_TRANSPARENT, FALSE, SURFACE_ICE,           "Ice"},          // MB64_MAT_ICE
    {mat_maker_MakerCrystal, MAT_TRANSPARENT, FALSE, SURFACE_CRYSTAL,       "Crystal"},      // MB64_MAT_CRYSTAL
    {mat_maker_MakerScreen,  MAT_DECAL,       TRUE,  SURFACE_DEFAULT,       "Screen"},       // MB64_MAT_VP_SCREEN

    // Retro
    {mat_maker_MakerRetroGround,     MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_RETRO_GROUND
    {mat_maker_MakerRetroBrick,      MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      NULL}, // MB64_MAT_RETRO_BRICKS
    {mat_maker_MakerRetroTreeTop,    MAT_OPAQUE, TRUE, SURFACE_GRASS,        NULL}, // MB64_MAT_RETRO_TREETOP
    {mat_maker_MakerRetroTree,       MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      NULL}, // MB64_MAT_RETRO_TREEPLAT
    {mat_maker_MakerRetroBlock,      MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_RETRO_BLOCK
    {mat_maker_MakerRetroBGround,    MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_RETRO_BLUEGROUND
    {mat_maker_MakerRetroBBrick,     MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      NULL}, // MB64_MAT_RETRO_BLUEBRICKS
    {mat_maker_MakerRetroBBlock,     MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_RETRO_BLUEBLOCK
    {mat_maker_MakerRetroWBrick,     MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      NULL}, // MB64_MAT_RETRO_WHITEBRICK
    {mat_maker_MakerRetroLava,       MAT_OPAQUE, TRUE, SURFACE_BURNING,      NULL}, // MB64_MAT_RETRO_LAVA
    {mat_maker_MakerRetroUnderwater, MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_RETRO_UNDERWATERGROUND

    // Minecraft
    {mat_maker_MakerMCDirt,        MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_MC_DIRT
    {mat_maker_MakerMCGrassTop,    MAT_OPAQUE, TRUE, SURFACE_GRASS,        NULL}, // MB64_MAT_MC_GRASS
    {mat_maker_MakerMCCobblestone, MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_MC_COBBLESTONE
    {mat_maker_MakerMCStone,       MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      NULL}, // MB64_MAT_MC_STONE
    {mat_maker_MakerMCOakLogTop,   MAT_OPAQUE, TRUE, SURFACE_CREAKWOOD,    NULL}, // MB64_MAT_MC_OAK_LOG_TOP
    {mat_maker_MakerMCOakLogSide,  MAT_OPAQUE, TRUE, SURFACE_CREAKWOOD,    NULL}, // MB64_MAT_MC_OAK_LOG_SIDE
    {mat_maker_MakerMCOakLeaves,   MAT_CUTOUT, TRUE, SURFACE_GRASS,        NULL}, // MB64_MAT_MC_OAK_LEAVES
    {mat_maker_MakerMCWoodPlanks,  MAT_OPAQUE, TRUE, SURFACE_CREAKWOOD,    NULL}, // MB64_MAT_MC_WOOD_PLANKS
    {mat_maker_MakerMCSand,        MAT_OPAQUE, TRUE, SURFACE_SAND,         NULL}, // MB64_MAT_MC_SAND
    {mat_maker_MakerMCBricks,      MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      NULL}, // MB64_MAT_MC_BRICKS
    {mat_maker_MakerMCLava,        MAT_OPAQUE, TRUE, SURFACE_BURNING,      NULL}, // MB64_MAT_MC_LAVA
    {mat_maker_MakerMCFlowingLava, MAT_OPAQUE, TRUE, SURFACE_BURNING,      NULL}, // MB64_MAT_MC_FLOWING_LAVA
    {mat_maker_MakerMCGlass,       MAT_CUTOUT_NOCULL, TRUE, SURFACE_VANISH_CAP_WALLS, NULL}, // MB64_MAT_MC_GLASS
};

u32 mb64_render_mode_table[] = {
    /* MAT_OPAQUE */        G_RM_ZB_OPA_SURF    | G_RM_ZB_OPA_SURF2,
    /* MAT_DECAL */         G_RM_TEX_EDGE_DECAL | G_RM_TEX_EDGE_DECAL2,
    /* MAT_CUTOUT */        G_RM_AA_ZB_TEX_EDGE | G_RM_AA_ZB_TEX_EDGE2,
    /* MAT_CUTOUT_NOCULL */ G_RM_AA_ZB_TEX_EDGE | G_RM_AA_ZB_TEX_EDGE2,
    /* MAT_TRANSPARENT */   G_RM_AA_ZB_XLU_SURF | G_RM_AA_ZB_XLU_SURF2,
    /* MAT_SCREEN */        G_RM_VPLEX_SCREEN   | G_RM_VPLEX_SCREEN2,
};

struct mb64_topmaterial mb64_topmat_table[] = {
    {MB64_MAT_GRASS,         mat_maker_MakerGrassSide},
    {MB64_MAT_SAND,          mat_maker_MakerSandSide},
    {MB64_MAT_SNOW,          mat_maker_MakerSnowSide},
    {MB64_MAT_TILES,         mat_maker_MakerTileEdge},
    {MB64_MAT_C_STONETOP,    mat_maker_MakerCastleHexRim},
    {MB64_MAT_HMC_GRASS,     mat_maker_MakerHGrassSide},
    {MB64_MAT_BBH_METAL,     mat_maker_MakerBBHMetalSide},
    {MB64_MAT_BBH_STONE,     mat_maker_MakerBBHMetalSide},
    {MB64_MAT_JRB_TILETOP,   mat_maker_MakerJRBTileRim},
    {MB64_MAT_SNOW_TILES,    mat_maker_MakerSnowTileRim},
    {MB64_MAT_FLOWERS,       mat_maker_MakerFlowerEdge},
    {MB64_MAT_RETRO_TREETOP, mat_maker_MakerRetroTreeSide},
    {MB64_MAT_MC_GRASS,      mat_maker_MakerMCGrassEdge},
    {MB64_MAT_LAVA_ROCKS,    mat_maker_MakerLavaRockEdge},
    {MB64_MAT_DARK_GRASS,    mat_maker_MakerDarkGrassSide},
    {MB64_MAT_CARTOON_GRASS, mat_maker_MakerCartoonGrassSide},
    {MB64_MAT_ORANGE_GRASS,  mat_maker_MakerOrangeGrassSide},
    {MB64_MAT_RED_GRASS,     mat_maker_MakerRedGrassSide},
    {MB64_MAT_PURPLE_GRASS,  mat_maker_MakerPurpleGrassSide},
};

enum mb64_fences {
    MB64_FENCE_NORMAL,
    MB64_FENCE_WOOD2,
    MB64_FENCE_DESERT,
    MB64_FENCE_BARBED,
    MB64_FENCE_RHR,
    MB64_FENCE_HMC,
    MB64_FENCE_CASTLE,
    MB64_FENCE_VIRTUAPLEX,
    MB64_FENCE_BBH,
    MB64_FENCE_JRB,
    MB64_FENCE_SNOW2,
    MB64_FENCE_SNOW,
    MB64_FENCE_RETRO,
    MB64_FENCE_MC,
};

Gfx *mb64_fence_texs[] = {
    mat_maker_MakerFence,
    mat_maker_MakerWoodenFence,
    mat_maker_MakerDFence,
    mat_maker_MakerBarbedWire,
    mat_maker_MakerRHRFence,
    mat_maker_MakerHFence,
    mat_maker_MakerCFence,
    mat_maker_MakerVPFence,
    mat_maker_MakerBBHFence,
    mat_maker_MakerJRBFence,
    mat_maker_MakerSnowFence2,
    mat_maker_MakerSnowFence,
    mat_maker_MakerRetroFence,
    mat_maker_MakerMCFence,
};

enum mb64_bars {
    MB64_BAR_GENERIC,
    MB64_BAR_RHR,
    MB64_BAR_VP,
    MB64_BAR_HMC,
    MB64_BAR_BBH,
    MB64_BAR_LLL,
    MB64_BAR_TTC,
    MB64_BAR_DESERT,
    MB64_BAR_BOB,
    MB64_BAR_RETRO,
    MB64_BAR_MC,
};
Gfx *mb64_bar_texs[][2] = {
    {mat_maker_MakerIronBars,   mat_maker_MakerIronBarsTop},
    {mat_maker_MakerRHRMesh,    mat_maker_MakerChainTop},
    {mat_maker_MakerVPMesh,     mat_maker_MakerChainTop},
    {mat_maker_MakerHMesh,      mat_maker_MakerHMCTop},
    {mat_maker_MakerBBHMesh,    mat_maker_MakerHMCTop},
    {mat_maker_MakerGratePink,  mat_maker_MakerChainTopPink},
    {mat_maker_MakerTTCGrate,   mat_maker_MakerTTCGrateTop},
    {mat_maker_MakerDMesh,      mat_maker_MakerDesertMeshTop},
    {mat_maker_MakerBOBBars,    mat_maker_MakerBOBBarsTop},
    {mat_maker_MakerRetroMesh,  mat_maker_MakerRetroMeshTop},
    {mat_maker_MakerMCIronBars, mat_maker_MakerMCIronBarsTop},
};

enum mb64_water {
    MB64_WATER_DEFAULT,
    MB64_WATER_GREEN,
    MB64_WATER_RETRO,
    MB64_WATER_MC,
};

Gfx *mb64_water_texs[] = {
    mat_maker_MakerWater,
    mat_maker_MakerGreenWater,
    mat_maker_MakerRetroWater,
    mat_maker_MakerMCWater,
};

struct mb64_theme mb64_theme_table[] = {
    // GENERIC
    {
        {
            {MB64_MAT_DIRT,        MB64_MAT_GRASS,     "Grass"},
            {MB64_MAT_BRICKS,      MB64_MAT_BRICKS,    "Bricks"},
            {MB64_MAT_COBBLESTONE, MB64_MAT_STONE,     "Rock"},
            {MB64_MAT_TILESBRICKS, MB64_MAT_TILES,     "Tiling"},
            {MB64_MAT_ROOF,        MB64_MAT_ROOF,      "Roof"},
            {MB64_MAT_WOOD,        MB64_MAT_WOOD,      "Wood"},
            {MB64_MAT_SANDDIRT,    MB64_MAT_SAND,      "Sand"},
            {MB64_MAT_SNOWDIRT,    MB64_MAT_SNOW,      "Snow"},
            {MB64_MAT_LAVA,        MB64_MAT_LAVA,      "Lava"},
            {MB64_MAT_QUICKSAND,   MB64_MAT_QUICKSAND, "Quicksand"},
        },
        MB64_FENCE_NORMAL, MB64_MAT_STONE, MB64_BAR_GENERIC, MB64_WATER_DEFAULT
    },
    // DESERT
    {
        {
            {MB64_MAT_SANDDIRT,        MB64_MAT_SAND,            "Sand"},
            {MB64_MAT_DESERT_BRICKS,   MB64_MAT_DESERT_BRICKS,   "Bricks"},
            {MB64_MAT_DESERT_STONE,    MB64_MAT_DESERT_STONE,    "Cobblestone"},
            {MB64_MAT_DESERT_TILES,    MB64_MAT_DESERT_TILES,    "Tiling"},
            {MB64_MAT_DESERT_BLOCK,    MB64_MAT_DESERT_BLOCK,    "Stone Block"},
            {MB64_MAT_DESERT_SLOWSAND, MB64_MAT_DESERT_SLOWSAND, "Slow Quicksand"},
            {MB64_MAT_DESERT_BRICKS,   MB64_MAT_DESERT_TILES2,   "Plating"},
            {MB64_MAT_DIRT,            MB64_MAT_GRASS,           "Grass"},
            {MB64_MAT_LAVA,            MB64_MAT_LAVA,            "Lava"},
            {MB64_MAT_QUICKSAND,       MB64_MAT_QUICKSAND,       "Quicksand"},
        },
        MB64_FENCE_DESERT, MB64_MAT_DESERT_TILES2, MB64_BAR_DESERT, MB64_WATER_GREEN
    },
    // LAVA
    {
        {
            {MB64_MAT_RHR_STONE,   MB64_MAT_RHR_OBSIDIAN, "Rock"},
            {MB64_MAT_RHR_BRICK,   MB64_MAT_RHR_OBSIDIAN, "Bricks"},
            {MB64_MAT_RHR_BASALT,  MB64_MAT_RHR_BASALT,   "Basalt"},
            {MB64_MAT_RHR_TILES,   MB64_MAT_RHR_TILES,    "Tiling"},
            {MB64_MAT_RHR_BLOCK,   MB64_MAT_RHR_BLOCK,    "Stone Block"},
            {MB64_MAT_RHR_WOOD,    MB64_MAT_RHR_WOOD,     "Wood"},
            {MB64_MAT_RHR_PILLAR,  MB64_MAT_RHR_TILES,    "Pillar"},
            {MB64_MAT_RHR_MESH,    MB64_MAT_RHR_MESH,     "Mesh"},
            {MB64_MAT_LAVA,        MB64_MAT_LAVA,         "Lava"},
            {MB64_MAT_SERVER_ACID, MB64_MAT_SERVER_ACID,  "Server Acid"},
        },
        MB64_FENCE_RHR, MB64_MAT_RHR_PILLAR, MB64_BAR_RHR, MB64_WATER_DEFAULT
    },
    // CAVE
    {
        {
            {MB64_MAT_HMC_DIRT,      MB64_MAT_HMC_GRASS,     "Grass"},
            {MB64_MAT_HMC_BRICK,     MB64_MAT_HMC_MAZEFLOOR, "Bricks"},
            {MB64_MAT_HMC_STONE,     MB64_MAT_HMC_STONE,     "Rock"},
            {MB64_MAT_HMC_SLAB,      MB64_MAT_HMC_TILES,     "Tiling"},
            {MB64_MAT_HMC_BRICK,     MB64_MAT_HMC_GRASS,     "Grassy Bricks"},
            {MB64_MAT_HMC_LAKEGRASS, MB64_MAT_HMC_GRASS,     "Lake Wall"},
            {MB64_MAT_HMC_LIGHT,     MB64_MAT_HMC_LIGHT,     "Light"},
            {MB64_MAT_HMC_MESH,      MB64_MAT_HMC_MESH,      "Grille"},
            {MB64_MAT_LAVA,          MB64_MAT_LAVA,          "Lava"},
            {MB64_MAT_QUICKSAND,     MB64_MAT_QUICKSAND,     "Quicksand"},
        },
        MB64_FENCE_HMC, MB64_MAT_HMC_LAKEGRASS, MB64_BAR_HMC, MB64_WATER_GREEN
    },
    // CASTLE
    {
        {
            {MB64_MAT_C_WOOD,         MB64_MAT_C_TILES,        "Tiling"},
            {MB64_MAT_C_BRICK,        MB64_MAT_C_TILES,        "Tiling (Bricks)"},
            {MB64_MAT_C_STONESIDE,    MB64_MAT_C_STONETOP,     "Tiling (Stone)"},
            {MB64_MAT_C_WOOD,         MB64_MAT_C_CARPET,       "Carpet"},
            {MB64_MAT_C_ROOF,         MB64_MAT_C_ROOF,         "Roof"},
            {MB64_MAT_C_WALL,         MB64_MAT_C_WALL,         "Castle Wall"},
            {MB64_MAT_C_PILLAR,       MB64_MAT_C_STONETOP,     "Pillar"},
            {MB64_MAT_C_BASEMENTWALL, MB64_MAT_C_BASEMENTWALL, "Basement Wall"},
            {MB64_MAT_LAVA,           MB64_MAT_LAVA,           "Lava"},
            {MB64_MAT_C_OUTSIDEBRICK, MB64_MAT_C_OUTSIDEBRICK, "Castle Bricks"},
        },
        MB64_FENCE_CASTLE, MB64_MAT_C_STONESIDE, MB64_BAR_VP, MB64_WATER_DEFAULT
    },
    // VIRTUAPLEX
    {
        {
            {MB64_MAT_VP_BLOCK,      MB64_MAT_VP_BLOCK,      "Block"},
            {MB64_MAT_VP_TILES,      MB64_MAT_VP_TILES,      "Tiling"},
            {MB64_MAT_DIRT,          MB64_MAT_GRASS,         "Grass"},
            {MB64_MAT_VP_TILES,      MB64_MAT_VP_BLUETILES,  "Blue Tiling"},
            {MB64_MAT_VP_RUSTYBLOCK, MB64_MAT_VP_RUSTYBLOCK, "Rusted Block"},
            {MB64_MAT_VP_SCREEN,     MB64_MAT_VP_SCREEN,     "Screen"},
            {MB64_MAT_VP_CAUTION,    MB64_MAT_VP_CAUTION,    "Hazard Stripes"},
            {MB64_MAT_VP_BLOCK,      MB64_MAT_SNOW,          "Snowy Block"},
            {MB64_MAT_LAVA,          MB64_MAT_LAVA,          "Lava"},
            {MB64_MAT_VP_VOID,       MB64_MAT_VP_VOID,       "Cosmic Void"},
        },
        MB64_FENCE_VIRTUAPLEX, MB64_MAT_VP_CAUTION, MB64_BAR_VP, MB64_WATER_DEFAULT
    },
    // SNOW
    {
        {
            {MB64_MAT_SNOWDIRT,       MB64_MAT_SNOW,             "Snow"},
            {MB64_MAT_SNOW_BRICKS,    MB64_MAT_SNOW_BRICK_TILES, "Bricks"},
            {MB64_MAT_SNOW_ROCK,      MB64_MAT_SNOW_ROCK,        "Rock"},
            {MB64_MAT_SNOW_TILE_SIDE, MB64_MAT_SNOW_TILES,       "Tiling"},
            {MB64_MAT_SNOW_ROOF,      MB64_MAT_SNOW_ROOF,        "Roof"},
            {MB64_MAT_WOOD,           MB64_MAT_WOOD,             "Wood"},
            {MB64_MAT_CRYSTAL,        MB64_MAT_CRYSTAL,          "Crystal"},
            {MB64_MAT_ICE,            MB64_MAT_ICE,              "Ice"},
            {MB64_MAT_BURNING_ICE,    MB64_MAT_BURNING_ICE,      "Hazard Ice"},
            {MB64_MAT_LAVA,           MB64_MAT_LAVA,             "Lava"},
        },
        MB64_FENCE_SNOW, MB64_MAT_SNOW_TILE_SIDE, MB64_BAR_GENERIC, MB64_WATER_DEFAULT
    },
    // BBH
    {
        {
            {MB64_MAT_BBH_BRICKS,         MB64_MAT_BBH_STONE,          "Stone Floor"},
            {MB64_MAT_BBH_HAUNTED_PLANKS, MB64_MAT_BBH_HAUNTED_PLANKS, "Haunted Planks"},
            {MB64_MAT_BBH_STONE_PATTERN,  MB64_MAT_BBH_WOOD_FLOOR,     "Wood Floor"},
            {MB64_MAT_BBH_BRICKS,         MB64_MAT_BBH_METAL,          "Metal Floor"},
            {MB64_MAT_BBH_ROOF,           MB64_MAT_BBH_ROOF,           "Roof"},
            {MB64_MAT_BBH_WOOD_WALL,      MB64_MAT_BBH_WOOD_WALL,      "Wood"},
            {MB64_MAT_BBH_STONE,          MB64_MAT_BBH_STONE,          "Wall"},
            {MB64_MAT_BBH_PILLAR,         MB64_MAT_BBH_STONE,          "Pillar"},
            {MB64_MAT_LAVA,               MB64_MAT_LAVA,               "Lava"},
            {MB64_MAT_BBH_WINDOW,         MB64_MAT_BBH_WINDOW,         "Window"},
        },
        MB64_FENCE_BBH, MB64_MAT_BBH_BRICKS, MB64_BAR_BBH, MB64_WATER_DEFAULT
    },
    // JRB
    {
        {
            {MB64_MAT_JRB_STONE,      MB64_MAT_JRB_SAND,       "Sand"},
            {MB64_MAT_JRB_BRICKS,     MB64_MAT_JRB_BRICKS,     "Bricks"},
            {MB64_MAT_JRB_UNDERWATER, MB64_MAT_JRB_UNDERWATER, "Ocean Floor"},
            {MB64_MAT_JRB_TILESIDE,   MB64_MAT_JRB_TILETOP,    "Tiles"},
            {MB64_MAT_JRB_SHIPSIDE,   MB64_MAT_JRB_SHIPTOP,    "Wood (Ship)"},
            {MB64_MAT_JRB_METAL,      MB64_MAT_JRB_WOOD,       "Wood (Docks)"},
            {MB64_MAT_JRB_METALSIDE,  MB64_MAT_JRB_METAL,      "Metal"},
            {MB64_MAT_HMC_MESH,       MB64_MAT_HMC_MESH,       "Grille"},
            {MB64_MAT_JRB_WALL,       MB64_MAT_JRB_WALL,       "Wall"},
            {MB64_MAT_QUICKSAND,      MB64_MAT_QUICKSAND,      "Quicksand"},
        },
        MB64_FENCE_JRB, MB64_MAT_VP_CAUTION, MB64_BAR_HMC, MB64_WATER_DEFAULT
    },
    // RETRO
    {
        {
            {MB64_MAT_RETRO_GROUND,           MB64_MAT_RETRO_GROUND,           "Ground"},
            {MB64_MAT_RETRO_BRICKS,           MB64_MAT_RETRO_BRICKS,           "Bricks"},
            {MB64_MAT_RETRO_TREEPLAT,         MB64_MAT_RETRO_TREETOP,          "Treetop"},
            {MB64_MAT_RETRO_BLOCK,            MB64_MAT_RETRO_BLOCK,            "Block"},
            {MB64_MAT_RETRO_BLUEGROUND,       MB64_MAT_RETRO_BLUEGROUND,       "Blue Ground"},
            {MB64_MAT_RETRO_BLUEBRICKS,       MB64_MAT_RETRO_BLUEBRICKS,       "Blue Bricks"},
            {MB64_MAT_RETRO_BLUEBLOCK,        MB64_MAT_RETRO_BLUEBLOCK,        "Blue Block"},
            {MB64_MAT_RETRO_WHITEBRICK,       MB64_MAT_RETRO_WHITEBRICK,       "White Bricks"},
            {MB64_MAT_RETRO_LAVA,             MB64_MAT_RETRO_LAVA,             "Lava"},
            {MB64_MAT_RETRO_UNDERWATERGROUND, MB64_MAT_RETRO_UNDERWATERGROUND, "Underwater Tile"},
        },
        MB64_FENCE_RETRO, MB64_MAT_RETRO_BRICKS, MB64_BAR_RETRO, MB64_WATER_RETRO
    },
    // CUSTOM
    {
        {
            {0, 0, "Tile 1"},
            {0, 0, "Tile 2"},
            {0, 0, "Tile 3"},
            {0, 0, "Tile 4"},
            {0, 0, "Tile 5"},
            {0, 0, "Tile 6"},
            {0, 0, "Tile 7"},
            {0, 0, "Tile 8"},
            {0, 0, "Tile 9"},
            {0, 0, "Tile 10"},
        },
        0, 0, 0, 0
    },
    // MINECRAFT
    {
        {
            {MB64_MAT_MC_DIRT,         MB64_MAT_MC_GRASS,       "Grass"},
            {MB64_MAT_MC_COBBLESTONE,  MB64_MAT_MC_COBBLESTONE, "Cobblestone"},
            {MB64_MAT_MC_STONE,        MB64_MAT_MC_STONE,       "Stone"},
            {MB64_MAT_MC_OAK_LOG_SIDE, MB64_MAT_MC_OAK_LOG_TOP, "Oak Log"},
            {MB64_MAT_MC_OAK_LEAVES,   MB64_MAT_MC_OAK_LEAVES,  "Oak Leaves"},
            {MB64_MAT_MC_WOOD_PLANKS,  MB64_MAT_MC_WOOD_PLANKS, "Oak Planks"},
            {MB64_MAT_MC_SAND,         MB64_MAT_MC_SAND,        "Sand"},
            {MB64_MAT_MC_BRICKS,       MB64_MAT_MC_BRICKS,      "Bricks"},
            {MB64_MAT_MC_FLOWING_LAVA, MB64_MAT_MC_LAVA,        "Lava"},
            {MB64_MAT_MC_GLASS,        MB64_MAT_MC_GLASS,       "Glass"},
        },
        MB64_FENCE_MC, MB64_MAT_MC_OAK_LOG_SIDE, MB64_BAR_MC, MB64_WATER_MC
    },
};

struct mb64_custom_theme mb64_default_custom = {
    {
        MB64_MAT_DIRT,
        MB64_MAT_BRICKS,
        MB64_MAT_COBBLESTONE,
        MB64_MAT_TILESBRICKS,
        MB64_MAT_ROOF,
        MB64_MAT_WOOD,
        MB64_MAT_SANDDIRT,
        MB64_MAT_SNOWDIRT,
        MB64_MAT_LAVA,
        MB64_MAT_QUICKSAND,
    },
    {
        MB64_MAT_GRASS,
        MB64_MAT_TILES,
        MB64_MAT_STONE,
        MB64_MAT_TILES,
        MB64_MAT_ROOF,
        MB64_MAT_WOOD,
        MB64_MAT_SAND,
        MB64_MAT_SNOW,
        MB64_MAT_LAVA,
        MB64_MAT_QUICKSAND,
    },
    {1, 0, 1, 1, 0, 0, 1, 1, 0, 0},
    MB64_FENCE_NORMAL, MB64_MAT_STONE, MB64_BAR_GENERIC, MB64_WATER_DEFAULT,
};
struct mb64_custom_theme mb64_curr_custom_theme;

// Returns full tile definition (struct mb64_tilemat_def)
#define TILE_MATDEF(matid) (mb64_theme_table[mb64_lopt_theme].mats[matid])
// Returns main material (struct mb64_material)
#define MATERIAL(matid) (mb64_mat_table[TILE_MATDEF(matid).mat])

// Returns TRUE if given material has a unique top texture
#define HAS_TOPMAT(matid) (TILE_MATDEF(matid).topmat != TILE_MATDEF(matid).mat)
// Returns top material's topmat struct (struct mb64_material)
#define TOPMAT(matid) (mb64_mat_table[TILE_MATDEF(matid).topmat])

// Returns current fence texture
#define FENCE_TEX() (mb64_fence_texs[mb64_theme_table[mb64_lopt_theme].fence])
#define POLE_TEX()  (mb64_mat_table[mb64_theme_table[mb64_lopt_theme].pole].gfx)
#define BARS_TEX() (mb64_bar_texs[mb64_theme_table[mb64_lopt_theme].bars][0])
#define BARS_TOPTEX() (mb64_bar_texs[mb64_theme_table[mb64_lopt_theme].bars][1])
#define WATER_TEX() (mb64_water_texs[mb64_theme_table[mb64_lopt_theme].water])

struct ExclamationBoxContents sExclamationBoxContents_btcm[] = {
    { 0, MODEL_MARIOS_WING_CAP,  bhvWingCap,           0, TRUE,  0},
    { 0, MODEL_MARIOS_METAL_CAP, bhvVanishCap,         2, TRUE,  0},
    { 0, MODEL_KOOPA_SHELL,      bhvKoopaShell,        3, TRUE,  0},
    { 0, 0xEF,                   bhvGreenGetsSpawned,  4, FALSE, 3},
    { 0, MODEL_YELLOW_COIN,      bhvSingleCoinGetsSpawned,  4, FALSE, 1},
    { 0, MODEL_NONE,             bhvThreeCoinsSpawn,   4, FALSE, 3},
    { 0, MODEL_NONE,             bhvTenCoinsSpawn,     4, FALSE, 10},
};

struct ExclamationBoxContents sExclamationBoxContents_vanilla[] = {
    { 0, MODEL_V_MARIOS_WING_CAP,  bhvWingCap,         0, TRUE,  0},
    { 6, MODEL_V_MARIOS_METAL_CAP, bhvMetalCap,        1, TRUE,  0},
    { 0, MODEL_MARIOS_CAP,         bhvVanishCap,       2, TRUE,  0},
    { 0, MODEL_KOOPA_SHELL,        bhvKoopaShell,      3, TRUE,  0},
    { 0, MODEL_YELLOW_COIN,        bhvSingleCoinGetsSpawned, 3, FALSE, 1},
    { 0, MODEL_NONE,               bhvThreeCoinsSpawn, 3, FALSE, 3},
    { 0, MODEL_NONE,               bhvTenCoinsSpawn,   3, FALSE, 10},
};

enum {
    OBJECT_TYPE_SETTINGS,
    OBJECT_TYPE_SCREENSHOT,
    OBJECT_TYPE_STAR,
    OBJECT_TYPE_RED_COIN_STAR,
    OBJECT_TYPE_GOOMBA,
    OBJECT_TYPE_BIG_GOOMBA,
    OBJECT_TYPE_TINY_GOOMBA,
    OBJECT_TYPE_PIRANHA_PLANT,
    OBJECT_TYPE_BIG_PIRANHA_PLANT,
    OBJECT_TYPE_TINY_PIRANHA_PLANT,
    OBJECT_TYPE_KOOPA,
    OBJECT_TYPE_COIN,
    OBJECT_TYPE_GREEN_COIN,
    OBJECT_TYPE_RED_COIN,
    OBJECT_TYPE_BLUE_COIN,
    OBJECT_TYPE_BLUE_COIN_SWITCH,
    OBJECT_TYPE_NOTEBLOCK,
    OBJECT_TYPE_BOBOMB,
    OBJECT_TYPE_CHUCKYA,
    OBJECT_TYPE_BULLY,
    OBJECT_TYPE_CHILL_BULLY,
    OBJECT_TYPE_BULLET_BILL,
    OBJECT_TYPE_HEAVE_HO,
    OBJECT_TYPE_MOTOS,
    OBJECT_TYPE_TREE,
    OBJECT_TYPE_EXCL_BOX,
    OBJECT_TYPE_MARIO_SPAWN,
    OBJECT_TYPE_REX,
    OBJECT_TYPE_PODOBOO,
    OBJECT_TYPE_CRABLET,
    OBJECT_TYPE_HAMMER_BRO,
    OBJECT_TYPE_FIRE_BRO,
    OBJECT_TYPE_CHICKEN,
    OBJECT_TYPE_PHANTASM,
    OBJECT_TYPE_WARP_PIPE,
    OBJECT_TYPE_BADGE,
    OBJECT_TYPE_KING_BOBOMB,
    OBJECT_TYPE_KING_WHOMP,
    OBJECT_TYPE_BIG_BOO,
    OBJECT_TYPE_BIG_BULLY,
    OBJECT_TYPE_BIG_CHILL_BULLY,
    OBJECT_TYPE_WIGGLER,
    OBJECT_TYPE_BOWSER,
    OBJECT_TYPE_PLATFORM_TRACK,
    OBJECT_TYPE_PLATFORM_LOOPING,
    OBJECT_TYPE_BOWLING_BALL,
    OBJECT_TYPE_KOOPA_THE_QUICK,
    OBJECT_TYPE_PURPLE_SWITCH,
    OBJECT_TYPE_TIMED_BOX,
    OBJECT_TYPE_RECOVERY_HEART,
    OBJECT_TYPE_TEST_MARIO,// Fake type, used for the Test mario preview
    OBJECT_TYPE_THWOMP,
    OBJECT_TYPE_WHOMP,
    OBJECT_TYPE_GRINDEL,
    OBJECT_TYPE_LAKITU,
    OBJECT_TYPE_FLY_GUY,
    OBJECT_TYPE_SNUFIT,
    OBJECT_TYPE_AMP,
    OBJECT_TYPE_BOO,
    OBJECT_TYPE_MR_I,
    OBJECT_TYPE_SCUTTLEBUG,
    OBJECT_TYPE_BOWSER_BOMB,
    OBJECT_TYPE_FIRE_SPINNER,
    OBJECT_TYPE_COIN_FORMATION,
    OBJECT_TYPE_RED_FLAME,
    OBJECT_TYPE_BLUE_FLAME,
    OBJECT_TYPE_FIRE_SPITTER,
    OBJECT_TYPE_FLAMETHROWER,
    OBJECT_TYPE_SPINDRIFT,
    OBJECT_TYPE_MR_BLIZZARD,
    OBJECT_TYPE_MONEYBAG,
    OBJECT_TYPE_SKEETER,
    OBJECT_TYPE_POKEY,
    OBJECT_TYPE_BBOX_SMALL,
    OBJECT_TYPE_BBOX_NORMAL,
    OBJECT_TYPE_BBOX_CRAZY,
    OBJECT_TYPE_DIAMOND,
    OBJECT_TYPE_SIGN,
    OBJECT_TYPE_BUDDY,
    OBJECT_TYPE_BUTTON,
    OBJECT_TYPE_ON_OFF_BLOCK,
    OBJECT_TYPE_WOODPLAT,
    OBJECT_TYPE_RFBOX,
    OBJECT_TYPE_CULL_PREVIEW, // also fake type
    OBJECT_TYPE_SHOWRUNNER,
    OBJECT_TYPE_CROWBAR,
    OBJECT_TYPE_MASK,
    OBJECT_TYPE_TOAD,
    OBJECT_TYPE_TUXIE,
    OBJECT_TYPE_UKIKI,
    OBJECT_TYPE_MOLEMAN,
    OBJECT_TYPE_COBIE,
    OBJECT_TYPE_CONVEYOR,
};

/*  Object Type                  Name                       Button GFX              Behavior           Y Offset     Model                      Flags                 Coins/Objs/Scale/Params  Anims   Display Func    Sound*/
struct mb64_object_info mb64_object_type_list[] = {
/* OBJECT_TYPE_SETTINGS */      {"Level Settings",          mat_b_btn_settings},
/* OBJECT_TYPE_SCREENSHOT */    {"Take Screenshot",         mat_b_btn_camera},
/* OBJECT_TYPE_STAR */          {"Normal",                  mat_b_btn_star,         bhvStar,           TILE_SIZE/2, MODEL_STAR,                OBJ_TYPE_HAS_STAR,       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_star, SOUND_MENU_STAR_SOUND | SOUND_VIBRATO},
/* OBJECT_TYPE_RED_COIN_STAR */ {"Red Coins",               mat_b_btn_rcs,          bhvHiddenRedCoinStar, TILE_SIZE/2, MODEL_TRANSPARENT_STAR, OBJ_TYPE_HAS_STAR,       OBJ_OCCUPY_INNER, 0, 1, 1.0f, NULL, df_reds_marker, SOUND_MENU_STAR_SOUND | SOUND_VIBRATO},
/* OBJECT_TYPE_GOOMBA */        {"Normal",                  mat_b_btn_goomba,       bhvGoomba,         0,           MODEL_GOOMBA,              OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 1, 0, 1.5f, goomba_seg8_anims_0801DA4C, NULL, SOUND_OBJ_GOOMBA_PREVIEW},
/* OBJECT_TYPE_BIG_GOOMBA */    {"Huge",                    mat_b_btn_goomba_b,     bhvBigGoomba,      0,           MODEL_GOOMBA,              OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 5, 0, 3.5f, goomba_seg8_anims_0801DA4C, NULL, SOUND_OBJ_GOOMBA_PREVIEW},
/* OBJECT_TYPE_TINY_GOOMBA */   {"Tiny",                    mat_b_btn_goomba_s,     bhvTinyGoomba,     0,           MODEL_GOOMBA,              OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 1, 0, 0.5f, goomba_seg8_anims_0801DA4C, NULL, SOUND_OBJ_GOOMBA_PREVIEW},
/* OBJECT_TYPE_PIRANHA_PLANT */ {"Normal",                  mat_b_btn_plant,        bhvPiranhaPlant,   0,           MODEL_MAKER_PLANT,         0,                       OBJ_OCCUPY_INNER, 5, 0, 1.0f, piranha_plant_seg6_anims_0601C31C, NULL, SOUND_OBJ2_PIRANHA_PLANT_BITE},
/* OBJECT_TYPE_BIG_PIRANHA_PLANT */  {"Huge",               mat_b_btn_plant_b,      bhvFirePiranhaPlantBig, 0,      MODEL_MAKER_PLANT,         0,                       OBJ_OCCUPY_INNER, 2, 0, 2.0f, piranha_plant_seg6_anims_0601C31C, NULL, SOUND_OBJ2_PIRANHA_PLANT_BITE},
/* OBJECT_TYPE_TINY_PIRANHA_PLANT */ {"Tiny",               mat_b_btn_plant_s,      bhvFirePiranhaPlant, 0,         MODEL_MAKER_PLANT,         0,                       OBJ_OCCUPY_INNER, 1, 0, 0.5f, piranha_plant_seg6_anims_0601C31C, NULL, SOUND_OBJ2_PIRANHA_PLANT_BITE},
/* OBJECT_TYPE_KOOPA */         {"Koopa",                   mat_b_btn_kuppa,        bhvScaredKoopa,    0,           MODEL_KOOPA_WITH_SHELL,    0,                       OBJ_OCCUPY_INNER, 5, 0, 1.5f, koopa_seg6_anims_06011364, df_koopa, SOUND_OBJ_KOOPA_TALK},
/* OBJECT_TYPE_COIN */          {"Yellow Coin",             mat_b_btn_coin,         bhvYellowCoin,     0,           MODEL_YELLOW_COIN,         OBJ_TYPE_IS_BILLBOARDED, OBJ_OCCUPY_INNER, 1, 0, 1.0f, NULL, NULL, SOUND_GENERAL_COIN | SOUND_VIBRATO},
/* OBJECT_TYPE_GREEN_COIN */    {"Green Coin",              mat_b_btn_greencoin,    bhvGreenCoin,      0,           MODEL_GREEN_COIN,          OBJ_TYPE_IS_BILLBOARDED, OBJ_OCCUPY_INNER, 3, 0, 1.0f, NULL, NULL, SOUND_GENERAL_COIN_MULTI},
/* OBJECT_TYPE_RED_COIN */      {"Red Coin",                mat_b_btn_redcoin,      bhvRedCoin,        0,           MODEL_RED_COIN,            OBJ_TYPE_IS_BILLBOARDED, OBJ_OCCUPY_INNER, 2, 0, 1.0f, NULL, NULL, SOUND_MENU_COLLECT_RED_COIN},
/* OBJECT_TYPE_BLUE_COIN */     {"Coin",                    mat_b_btn_bluecoin,     bhvHiddenBlueCoin, 0,           MODEL_BLUE_COIN,           OBJ_TYPE_IS_BILLBOARDED, OBJ_OCCUPY_INNER, 5, 0, 1.0f, NULL, NULL, SOUND_GENERAL_COIN_MULTI},
/* OBJECT_TYPE_BLUE_COIN_SWITCH */ {"Switch",               mat_b_btn_bcs,          bhvBlueCoinSwitch, 0,           MODEL_BLUE_COIN_SWITCH,    0,                       OBJ_OCCUPY_INNER, 0, 0, 3.0f, NULL, NULL, SOUND_GENERAL2_PURPLE_SWITCH},
/* OBJECT_TYPE_NOTEBLOCK */     {"Noteblock",               mat_b_btn_noteblock,    bhvNoteblock,      TILE_SIZE/2, MODEL_NOTEBLOCK,           0,                       OBJ_OCCUPY_INNER, 0, 0, 1.27f,NULL, NULL, SOUND_GENERAL_CRAZY_BOX_BOING_SLOW},
/* OBJECT_TYPE_BOBOMB */        {"Bob-omb",                 mat_b_btn_bobomb,       bhvBobomb,         0,           MODEL_BLACK_BOBOMB,        OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 1, 0, 1.0f, bobomb_anims, NULL, SOUND_GENERAL2_QUIET_EXPLOSION},
/* OBJECT_TYPE_CHUCKYA */       {"Chuckya",                 mat_b_btn_chuckya,      bhvChuckya,        0,           MODEL_CHUCKYA,             OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 5, 0, 2.0f, chuckya_seg8_anims_0800C070, df_chuckya, SOUND_OBJ_CHUCKYA_PREVIEW},
/* OBJECT_TYPE_BULLY */         {"Bully",                   mat_b_btn_bully,        bhvSmallBully,     0,           MODEL_BULLY,               OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 1, 0, 1.0f, bully_seg5_anims_0500470C, NULL, SOUND_OBJ2_SMALL_BULLY_ATTACKED},
/* OBJECT_TYPE_CHILL_BULLY */   {"Chill Bully",             mat_b_btn_chillbully,   bhvSmallBully,     0,           MODEL_CHILL_BULLY,         OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 1, 0, 1.0f, bully_seg5_anims_0500470C, NULL, SOUND_OBJ2_SMALL_BULLY_ATTACKED},
/* OBJECT_TYPE_BULLET_BILL */   {"Bullet Bill",             mat_b_btn_bill,         bhvBulletBillCannon, TILE_SIZE/2, MODEL_BILL_MAKER_2,      0,                       OBJ_OCCUPY_INNER, 0, 1, 1.0f, NULL, NULL, SOUND_OBJ_POUNDING_CANNON},
/* OBJECT_TYPE_HEAVE_HO */      {"Heave-Ho",                mat_b_btn_heaveho,      bhvHeaveHo,        0,           MODEL_MAKER_HEAVEHO,       0,                       OBJ_OCCUPY_INNER, 0, 0, 2.0f, heave_ho_seg5_anims_0501534C, NULL, SOUND_OBJ_HEAVEHO_PREVIEW},
/* OBJECT_TYPE_MOTOS */         {"Motos",                   mat_b_btn_motos,        bhvMotos,          0,           MODEL_MAKER_MOTOS,         OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 5, 0, 2.0f, motos_anime, NULL, SOUND_OBJ_HEAVEHO_PREVIEW},
/* OBJECT_TYPE_TREE */          {"Tree",                    mat_b_btn_tree,         bhvTree,           0,           MODEL_MAKER_TREE_1,        OBJ_TYPE_IS_BILLBOARDED, OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_tree, SOUND_ACTION_CLIMB_UP_TREE | SOUND_VIBRATO},
/* OBJECT_TYPE_EXCL_BOX */      {"Item Box",                mat_b_btn_excla,        bhvExclamationBox, TILE_SIZE/2, MODEL_EXCLAMATION_BOX,     0,                       OBJ_OCCUPY_INNER, 0, 0, 2.0f, NULL, df_exbox, SOUND_GENERAL_BOX_PREVIEW},
/* OBJECT_TYPE_SPAWN */         {"Mario Spawn",             mat_b_btn_spawn,        bhvSpawn,          TILE_SIZE/2, MODEL_SPAWN,               0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_MENU_STAR_SOUND_LETS_A_GO},
/* OBJECT_TYPE_REX */           {"Rex",                     mat_b_btn_rex,          bhvRex,            0,           MODEL_REX,                 0,                       OBJ_OCCUPY_INNER, 2, 0, 1.5f, Rex_anims, NULL, SOUND_OBJ_GOOMBA_PREVIEW},
/* OBJECT_TYPE_PODOBOO */       {"Podoboo",                 mat_b_btn_podoboo,      bhvPodoboo,        TILE_SIZE/2, MODEL_PODOBOO,             0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_podoboo, SOUND_OBJ_FLAME_BLOWN},
/* OBJECT_TYPE_CRABLET */       {"Crablet",                 mat_b_btn_crablet,      bhvCrablet,        0,           MODEL_MAKER_CRABLET,       0,                       OBJ_OCCUPY_INNER, 4, 0, 1.0f, crab_anims_anims, NULL, SOUND_OBJ2_SCUTTLEBUG_ALERT},
/* OBJECT_TYPE_HAMMER_BRO */    {"Normal",                  mat_b_btn_hammerbro,    bhvHammerBro,      60.0f,       MODEL_HAMMER_BRO,          0,                       OBJ_OCCUPY_INNER, 6, 0, 1.0f, Hammerbro_anims, df_hammerbro, SOUND_OBJ_KOOPA_DAMAGE},
/* OBJECT_TYPE_FIRE_BRO */      {"Fire Bro",                mat_b_btn_firebro,      bhvFireBro,        60.0f,       MODEL_HAMMER_BRO,          0,                       OBJ_OCCUPY_INNER, 6, 0, 1.0f, Hammerbro_anims, df_firebro, SOUND_OBJ_KOOPA_DAMAGE},
/* OBJECT_TYPE_CHICKEN */       {"Chicken",                 mat_b_btn_chicken,      bhvChicken,        0,           MODEL_MAKER_CHICKEN,       0,                       OBJ_OCCUPY_INNER, 2, 0, 1.0f, chicken_anims, NULL, SOUND_OBJ_BOO_LAUGH_SHORT},
/* OBJECT_TYPE_PHANTASM */      {"Cosmic Phantasm",         mat_b_btn_phantasm,     bhvPhantasm,       0,           MODEL_MARIO,               0,                       OBJ_OCCUPY_INNER, 5, 9, 1.0f, &evil_mario_anims[2], NULL, SOUND_ACTION_METAL_STEP | SOUND_VIBRATO},
/* OBJECT_TYPE_WARP_PIPE */     {"Warp Pipe",               mat_b_btn_pipe,         bhvStaticObject,   0,           MODEL_MAKER_PIPE,          0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_MENU_ENTER_PIPE | SOUND_VIBRATO},
/* OBJECT_TYPE_BADGE */         {"Badge",                   mat_b_btn_badge,        bhvBadge,          TILE_SIZE/2, MODEL_BADGE,               OBJ_TYPE_IS_BILLBOARDED, OBJ_OCCUPY_INNER, 0, 0, 5.0f, NULL, NULL, SOUND_GENERAL2_PURPLE_SWITCH},
/* OBJECT_TYPE_KING_BOBOMB */   {"King Bob-omb",            mat_b_btn_boss_kb,      bhvKingBobomb,     0,           MODEL_KINGBOMB_MAKER,      OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  0, 0, 1.0f, king_bobomb_seg5_anims_0500FE30, df_kingbomb, SOUND_OBJ_KING_BOBOMB_POUNDING1_HIGHPRIO},
/* OBJECT_TYPE_KING_WHOMP */    {"King Whomp",              mat_b_btn_boss_whomp,   bhvWhompKingBoss,  0,           MODEL_WHOMP_MAKER,         OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  0, 0, 2.0f, whomp_seg6_anims_06020A04, NULL, SOUND_OBJ_WHOMP},
/* OBJECT_TYPE_BIG_BOO */       {"Big Boo",                 mat_b_btn_boss_boo,     bhvBalconyBigBoo,  TILE_SIZE,   MODEL_MAKER_BOO,           OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS,       OBJ_OCCUPY_FULL,  0, 0, 3.0f, NULL, df_boo, SOUND_OBJ_BOO_LAUGH_LONG},
/* OBJECT_TYPE_BIG_BULLY */     {"Big Bully",               mat_b_btn_boss_bully,   bhvBigBully,       0,           MODEL_BULLY,               OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  0, 0, 2.0f, bully_seg5_anims_0500470C, NULL, SOUND_OBJ2_LARGE_BULLY_ATTACKED},
/* OBJECT_TYPE_BIG_CHILL_BULLY */ {"Big Chill Bully",       mat_b_btn_boss_chillbully,bhvBigBully,     0,           MODEL_CHILL_BULLY,         OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  0, 0, 2.0f, bully_seg5_anims_0500470C, NULL, SOUND_OBJ2_LARGE_BULLY_ATTACKED},
/* OBJECT_TYPE_WIGGLER */       {"Wiggler",                 mat_b_btn_boss_wiggler, bhvWigglerHead,    0,           MODEL_WIGGLER_HEAD,        OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  0, 0, 4.0f, wiggler_seg5_anims_0500EC8C, df_wiggler, SOUND_OBJ_WIGGLER_TALK},
/* OBJECT_TYPE_BOWSER */        {"Bowser",                  mat_b_btn_boss_bowser,  bhvBowser,         0,           MODEL_MAKER_BOWSER,        OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  0, 24, 1.0f, bowser_anims, df_booser, SOUND_OBJ2_BOWSER_ROAR},
/* OBJECT_TYPE_PLATFORM_TRACK */ {"Activated",              mat_b_btn_checker,      bhvPlatformOnTrack, TILE_SIZE/2, MODEL_CHECKERBOARD_PLATFORM, OBJ_TYPE_TRAJECTORY,  OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_ENV_ELEVATOR1 | SOUND_VIBRATO},
/* OBJECT_TYPE_PLATFORM_LOOPING */ {"Looping",              mat_b_btn_checker,      bhvLoopingPlatform, TILE_SIZE/2, MODEL_LOOPINGP,           OBJ_TYPE_TRAJECTORY,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_ENV_ELEVATOR1 | SOUND_VIBRATO},
/* OBJECT_TYPE_BOWLING_BALL */  {"Bowling Ball",            mat_b_btn_bball,        bhvBobBowlingBallSpawner, TILE_SIZE/2, MODEL_BOWLING_BALL, OBJ_TYPE_IS_BILLBOARDED | OBJ_TYPE_TRAJECTORY, OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_GENERAL_QUIET_POUND1 | SOUND_VIBRATO},
/* OBJECT_TYPE_KOOPA_THE_QUICK */ {"Koopa the Quick",       mat_b_btn_kuppaq,       bhvKoopa,          0,           MODEL_KOOPA_WITH_SHELL,    OBJ_TYPE_TRAJECTORY | OBJ_TYPE_HAS_STAR, OBJ_OCCUPY_FULL, 0, 1, 3.0f, koopa_seg6_anims_06011364, df_ktq, SOUND_OBJ_KOOPA_TALK},
/* OBJECT_TYPE_PURPLE_SWITCH */ {"Purple Switch",           mat_b_btn_purpleswitch, bhvFloorSwitchHiddenObjects, 0, MODEL_PURPLE_SWITCH,       0,                       OBJ_OCCUPY_INNER, 0, 0, 1.28f,NULL, NULL, SOUND_GENERAL2_PURPLE_SWITCH},
/* OBJECT_TYPE_TIMED_BOX */     {"Timed Box",               mat_b_btn_tbox,         bhvHiddenObject,   0,           MODEL_BREAKABLE_BOX,       0,                       OBJ_OCCUPY_OUTER, 0, 0, 1.0f, NULL, df_timedbox, SOUND_GENERAL2_SWITCH_TICK_FAST},
/* OBJECT_TYPE_RECOVERY_HEART */ {"Recovery Heart",         mat_b_btn_heart,        bhvRecoveryHeart,  TILE_SIZE/2, MODEL_HEART,               0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_heart, SOUND_GENERAL_HEART_SPIN},
/* OBJECT_TYPE_TEST_MARIO */    {"Save & Test",             mat_b_btn_check,        NULL,              0,           MODEL_MARIO,               0,                       OBJ_OCCUPY_FULL,  0, 0, 1.0f, &evil_mario_anims[11], NULL, 0},
/* OBJECT_TYPE_THWOMP */        {"Thwomp",                  mat_b_btn_thwomp,       bhvThwomp,         0,           MODEL_THWOMP_MAKER,        0,                       OBJ_OCCUPY_FULL,  0, 0, 1.5f, NULL, NULL, SOUND_OBJ_THWOMP},
/* OBJECT_TYPE_WHOMP */         {"Whomp",                   mat_b_btn_whomp,        bhvSmallWhomp,     0,           MODEL_WHOMP_MAKER,         0,                       OBJ_OCCUPY_FULL, 10, 0, 1.0f, whomp_seg6_anims_06020A04, NULL, SOUND_OBJ_WHOMP},
/* OBJECT_TYPE_GRINDEL */       {"Grindel",                 mat_b_btn_grindel,      bhvGrindel,        0,           MODEL_MAKER_GRINDEL,       0,                       OBJ_OCCUPY_FULL,  0, 0, 1.0f, NULL, df_grindel, SOUND_OBJ_KING_BOBOMB_JUMP},
/* OBJECT_TYPE_LAKITU */        {"Lakitu",                  mat_b_btn_lakitu,       bhvEnemyLakitu,    TILE_SIZE/2, MODEL_LAKITU_MAKER,        0,                       OBJ_OCCUPY_INNER, 5, 5, 1.0f, lakitu_enemy_seg5_anims_050144D4, df_lakitu, SOUND_OBJ_EVIL_LAKITU_THROW},
/* OBJECT_TYPE_FLY_GUY */       {"Fly Guy",                 mat_b_btn_flyguy,       bhvRealFlyGuy,     TILE_SIZE/2, MODEL_FLYGUY,              0,                       OBJ_OCCUPY_INNER, 2, 0, 1.5f, flyguy_seg8_anims_08011A64, df_flyguy, SOUND_OBJ_KOOPA_FLYGUY_DEATH},
/* OBJECT_TYPE_SNUFIT */        {"Snufit",                  mat_b_btn_snufit,       bhvSnufit,         TILE_SIZE/2, MODEL_MAKER_SNUFIT,        0,                       OBJ_OCCUPY_INNER, 2, 0, 1.0f, NULL, df_snufit, SOUND_OBJ_SNUFIT_SHOOT},
/* OBJECT_TYPE_AMP */           {"Amp",                     mat_b_btn_amp,          bhvCirclingAmp,    TILE_SIZE/2, MODEL_AMP,                 0,                       OBJ_OCCUPY_OUTER, 0, 0, 1.0f, amp_anims, df_circling_amp, SOUND_AIR_AMP_PREVIEW},
/* OBJECT_TYPE_BOO */           {"Boo",                     mat_b_btn_boo,          bhvBoo,            TILE_SIZE/2, MODEL_MAKER_BOO,           OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS,  OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_boo, SOUND_OBJ_BOO_LAUGH_LONG},
/* OBJECT_TYPE_MR_I */          {"Mr. I",                   mat_b_btn_mri,          bhvMrI,            0,           MODEL_MAKER_MRI,           OBJ_TYPE_IS_BILLBOARDED, OBJ_OCCUPY_INNER, 5, 1, 1.0f, NULL, df_mri, SOUND_OBJ_MRI_SHOOT},
/* OBJECT_TYPE_SCUTTLEBUG */    {"Scuttlebug",              mat_b_btn_scuttlebug,   bhvScuttlebug,     0,           MODEL_MAKER_SCUTTLEBUG,    0,                       OBJ_OCCUPY_INNER, 3, 0, 1.0f, scuttlebug_seg6_anims_06015064, NULL, SOUND_OBJ2_SCUTTLEBUG_ALERT},
/* OBJECT_TYPE_BOWSER_BOMB */   {"Bowser Bomb",             mat_b_btn_bbomb,        bhvBowserBomb,     TILE_SIZE/2, MODEL_MAKER_BOWSER_BOMB,   0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_GENERAL2_QUIET_EXPLOSION},
/* OBJECT_TYPE_FIRE_SPINNER */  {"Fire Spinner",            mat_b_btn_firebar,      bhvLllRotatingBlockWithFireBars, 0, MODEL_MAKER_FIREBAR,   0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_fire_spinner, SOUND_OBJ_FLAME_BLOWN},
/* OBJECT_TYPE_COIN_FORMATION */ {"Coin Formation",         mat_b_btn_cformation,   bhvCoinFormation,  0,           MODEL_NONE,                0,                       OBJ_OCCUPY_FULL,  0, 0, 1.0f, NULL, df_coin_formation, SOUND_GENERAL_COIN_MULTI},
/* OBJECT_TYPE_RED_FLAME */     {"Red",                     mat_b_btn_fire_red,     bhvFlame,          60,          MODEL_RED_FLAME,           OBJ_TYPE_IS_BILLBOARDED, OBJ_OCCUPY_INNER, 0, 0, 7.0f, NULL, df_flame, SOUND_OBJ_FLAME_BLOWN},
/* OBJECT_TYPE_BLUE_FLAME */    {"Blue",                    mat_b_btn_fire_blue,    bhvFlame,          60,          MODEL_BLUE_FLAME,          OBJ_TYPE_IS_BILLBOARDED, OBJ_OCCUPY_INNER, 0, 0, 7.0f, NULL, df_flame, SOUND_OBJ_FLAME_BLOWN},
/* OBJECT_TYPE_FIRE_SPITTER */  {"Fire Spitter",            mat_b_btn_firespitter,  bhvFireSpitter,    TILE_SIZE/2, MODEL_BOWLING_BALL,        OBJ_TYPE_IS_BILLBOARDED, OBJ_OCCUPY_INNER, 0, 0, 0.2f, NULL, NULL, SOUND_OBJ_FLAME_BLOWN},
/* OBJECT_TYPE_FLAMETHROWER */  {"Flamethrower",            mat_b_btn_flamethrower, bhvFlamethrower,   TILE_SIZE/2, MODEL_MAKER_FLAMETHROWER,  0,                       OBJ_OCCUPY_FULL,  0, 0, 1.0f, NULL, NULL, SOUND_OBJ_FLAME_BLOWN},
/* OBJECT_TYPE_SPINDRIFT */     {"Spindrift",               mat_b_btn_spindrift,    bhvSpindrift,      0,           MODEL_MAKER_SPINDRIFT,     0,                       OBJ_OCCUPY_INNER, 3, 0, 1.0f, spindrift_seg5_anims_05002D68, NULL, SOUND_ACTION_TWIRL},
/* OBJECT_TYPE_MR_BLIZZARD */   {"Mr. Blizzard",            mat_b_btn_blizzard,     bhvMrBlizzard,     0,           MODEL_MAKER_BLIZZARD,      0,                       OBJ_OCCUPY_INNER, 3, 0, 1.0f, snowman_seg5_anims_0500D118, df_blizzard, SOUND_OBJ2_SCUTTLEBUG_ALERT},
/* OBJECT_TYPE_MONEYBAG */      {"Moneybag",                mat_b_btn_moneybag,     bhvMoneybagHidden, 0,           MODEL_MONEYBAG,            0,                       OBJ_OCCUPY_INNER, 5, 0, 1.0f, moneybag_seg6_anims_06005E5C, df_moneybag, SOUND_GENERAL_MONEYBAG_BOING_LOWPRIO},
/* OBJECT_TYPE_SKEETER */       {"Skeeter",                 mat_b_btn_skeeter,      bhvSkeeter,        0,           MODEL_MAKER_SKEETER,       0,                       OBJ_OCCUPY_INNER, 3, 0, 1.0f, skeeter_seg6_anims_06007DE0, NULL, SOUND_OBJ_SKEETER_WALK},
/* OBJECT_TYPE_POKEY */         {"Pokey",                   mat_b_btn_pokey,        bhvPokey,          0,           MODEL_MAKER_POKEY_HEAD,    OBJ_TYPE_IS_BILLBOARDED, OBJ_OCCUPY_INNER, 5, 0, 3.0f, NULL, df_pokey, SOUND_OBJ_POKEY_DEATH},
/* OBJECT_TYPE_BBOX_SMALL*/     {"Throwable Box",           mat_b_btn_sbox,         bhvBreakableBoxSmall, 0,        MODEL_BREAKABLE_BOX,       0,                       OBJ_OCCUPY_INNER, 3, 0, 0.31f,NULL, df_corkbox, SOUND_GENERAL_BOX_PREVIEW},
/* OBJECT_TYPE_BBOX_NORMAL*/    {"Breakable Box",           mat_b_btn_corkbox,      bhvBreakableBox,   0,           MODEL_BREAKABLE_BOX,       OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS, OBJ_OCCUPY_FULL, 0, 0, 1.0f, NULL, df_corkbox, SOUND_GENERAL_BOX_PREVIEW},
/* OBJECT_TYPE_BBOX_CRAZY*/     {"Crazy Box",               mat_b_btn_cbox,         bhvJumpingBox,     0,           MODEL_BREAKABLE_BOX,       0,                       OBJ_OCCUPY_INNER, 5, 0, 0.38f,NULL, NULL, SOUND_GENERAL_CRAZY_BOX_BOING_SLOW},
/* OBJECT_TYPE_DIAMOND*/        {"Water Diamond",           mat_b_btn_water_diamond,bhvWaterLevelDiamond,0,         MODEL_MAKER_DIAMOND,       0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_GENERAL_WATER_LEVEL_TRIG},
/* OBJECT_TYPE_SIGN */          {"Bill Board",              mat_b_btn_sign,         bhvMessagePanel,   0,           MODEL_WOODEN_SIGNPOST,     OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_ACTION_READ_SIGN},
/* OBJECT_TYPE_BUDDY */         {"Bob-omb Buddy",           mat_b_btn_buddy,        bhvBobombBuddy,    0,           MODEL_BOBOMB_BUDDY,        OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, bobomb_anims, NULL, SOUND_OBJ_BOBOMB_BUDDY_TALK},
/* OBJECT_TYPE_BUTTON */        {"On-Off Button",           mat_b_btn_switch,       bhvOnOffButton,    0,           MODEL_MAKER_BUTTON,        0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_button, SOUND_GENERAL_BUTTON_PRESS},
/* OBJECT_TYPE_ON_OFF_BLOCK */  {"On-Off Block",            mat_b_btn_block,        bhvOnOffBlock,     0,           MODEL_MAKER_BLOCK_OFF,     0,                       OBJ_OCCUPY_OUTER, 0, 0, 1.0f, NULL, df_block, SOUND_GENERAL_BUTTON_PRESS},
/* OBJECT_TYPE_WOODPLAT */      {"Wooden Platform",         mat_b_btn_woodplat,     bhvWoodPlat,       0,           MODEL_MAKER_WOODPLAT,      0,                       OBJ_OCCUPY_FULL,  0, 1, 1.0f, NULL, df_woodplat, SOUND_ACTION_TERRAIN_STEP + (SOUND_TERRAIN_SPOOKY << 16)},
/* OBJECT_TYPE_RFBOX */         {"Reinforced Box",          mat_b_btn_rfbox,        bhvBreakableBoxRF, 0,           MODEL_MAKER_RFBOX,         OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS, OBJ_OCCUPY_FULL, 0, 0, 1.0f, NULL, NULL, SOUND_OBJ_BULLY_METAL},
/* OBJECT_TYPE_CULL_PREVIEW */  {"",                        mat_b_btn_cull,         bhvStaticObject,   TILE_SIZE/2, MODEL_CULL_MARKER,         OBJ_TYPE_IS_BILLBOARDED, OBJ_OCCUPY_INNER, 0, 0, 1.f,  NULL, NULL, 0},
/* OBJECT_TYPE_SHOWRUNNER */    {"Showrunner",              mat_b_btn_showrunner,   bhvShowrunner,     0,           MODEL_MAKER_SHOWRUNNER,    OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  50,39,1.0f, showrunner_anims, NULL, SOUND_OBJ_MRI_SHOOT},
/* OBJECT_TYPE_CROWBAR */       {"Crowbar",                 mat_b_btn_pipebar,      bhvCrowbarPower,   0,           MODEL_MAKER_CROWBAR,       0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_power, SOUND_MENU_EXIT_PIPE},
/* OBJECT_TYPE_MASK    */       {"Bullet Bill Mask",        mat_b_btn_mask,         bhvBMask,          0,           MODEL_MAKER_MASK,          0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_power, SOUND_MENU_EXIT_PIPE},
/* OBJECT_TYPE_TOAD */          {"Toad",                    mat_b_btn_toad,         bhvMakerToad,      0,           MODEL_MAKER_TOAD,          OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, toad_seg6_anims_0600FB58, df_toad, SOUND_ACTION_READ_SIGN},
/* OBJECT_TYPE_TUXIE */         {"Tuxie",                   mat_b_btn_tuxie,        bhvMakerTuxie,     0,           MODEL_MAKER_TUXIE,         OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, penguin_seg5_anims_05008B74, NULL, SOUND_OBJ2_BABY_PENGUIN_YELL},
/* OBJECT_TYPE_UKIKI */         {"Ukiki",                   mat_b_btn_ukiki,        bhvMakerUkiki,     0,           MODEL_MAKER_UKIKI,         OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, ukiki_seg5_anims_05015784, df_ukiki, SOUND_OBJ_UKIKI_CHATTER_SHORT},
/* OBJECT_TYPE_MOLEMAN */       {"Moleman",                 mat_b_btn_moleman,      bhvMoleman,        65,          MODEL_MAKER_MOLEMAN,       OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, moleman3_anims, NULL, SOUND_ACTION_READ_SIGN},
/* OBJECT_TYPE_COBIE */         {"Cobie",                   mat_b_btn_cobie,        bhvCobie,          0,           MODEL_MAKER_COBIE,         OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, cobie2_anims, NULL, SOUND_ACTION_READ_SIGN},
/* OBJECT_TYPE_CONVEYOR */      {"Conveyor",                mat_b_btn_conveyor,     bhvConveyor,       0,           MODEL_MAKER_CONVEYOR_HALF, 0,                       OBJ_OCCUPY_FULL,  0, 0, 1.0f, NULL, df_conveyor, SOUND_OBJ_HEAVEHO_PREVIEW},
};

//behparam2 strings
char *txt_bp_box[] = {
    "Rocket Boots",
    "Vanetal Cap",
    "Koopa Shell",
    "Green Coin",
    "One Coin",
    "Three Coins",
    "Ten Coins",
};

char *txt_bp_vbox[] = {
    "Wing Cap",
    "Metal Cap",
    "Vanish Cap",
    "Koopa Shell",
    "One Coin",
    "Three Coins",
    "Ten Coins",
};

char *txt_bp_tree[] = {
    "Bubbly",
    "Palm",
    "Spiky",
    "Snowy",
    "Farm",
    "Dead",
};

char *txt_badges[] = {
    "Lava Boost",
    "Fall Damage",
    "Defense",
    "Double Damage",
    "Gills",
    "Fins",
    "HP Regen",
    "Mana Regen",
    "Greed",
    "Double Time",
    "Magnet",
    "Star Radar",
    "Burn",
    "Squish",
    "Feather",
    "Weight",
    "Sticky",
    "Fast Foot",
    "Heal Plus",
    "Bottomless",
    "Slow Fall",
    "Brittle Burden",
    "Withering Burden",
};

char *txt_coin_formation[] = {
    "Line",
    "Vertical Line",
    "Ring",
    "Vertical Ring",
    "Arrow",
};

char *txt_onoff[] = {
    "Red",
    "Blue"
};

char *txt_woodplat[] = {
    "Thin",
    "Full"
};

char *txt_fire_spinner[] = {
    "Length: 2",
    "Length: 3",
    "Length: 4",
    "Length: 5",
    "Length: 6",
};

char *txt_conveyor[] = {
    "Thin",
    "Full",
    "Upwards",
    "Downwards",
    "Thin (Toggle)",
    "Full (Toggle)",
    "Upwards (Toggle)",
    "Downwards (Toggle)",
};

enum {
    MB64_BUTTON_SETTINGS,
    MB64_BUTTON_TEST,
    MB64_BUTTON_TERRAIN,
    MB64_BUTTON_SLOPE,
    MB64_BUTTON_TROLL,
    MB64_BUTTON_STAR,
    MB64_BUTTON_GOOMBA,
    MB64_BUTTON_PIRANHA,
    MB64_BUTTON_KOOPA,
    MB64_BUTTON_COIN,
    MB64_BUTTON_BLANK,
    MB64_BUTTON_GCOIN,
    MB64_BUTTON_CORNER,
    MB64_BUTTON_ICORNER,
    MB64_BUTTON_RCOIN,
    MB64_BUTTON_BCOIN,
    MB64_BUTTON_NOTEBLOCK,
    MB64_BUTTON_CULL,
    MB64_BUTTON_BOBOMB,
    MB64_BUTTON_CHUCKYA,
    MB64_BUTTON_BULLY,
    MB64_BUTTON_BULLET,
    MB64_BUTTON_HEAVEHO,
    MB64_BUTTON_MOTOS,
    MB64_BUTTON_TREE,
    MB64_BUTTON_EXCLA,
    MB64_BUTTON_SPAWN,
    MB64_BUTTON_REX,
    MB64_BUTTON_PODOBOO,
    MB64_BUTTON_CRABLET,
    MB64_BUTTON_HAMMER_BRO,
    MB64_BUTTON_CHICKEN,
    MB64_BUTTON_PHANTASM,
    MB64_BUTTON_PIPE,
    MB64_BUTTON_BADGE,
    MB64_BUTTON_WATER,
    MB64_BUTTON_FENCE,
    MB64_BUTTON_KING_BOBOMB,
    MB64_BUTTON_WIGGLER,
    MB64_BUTTON_BOWSER,
    MB64_BUTTON_MPLAT,
    MB64_BUTTON_BBALL,
    MB64_BUTTON_KTQ,
    MB64_BUTTON_SSLOPE,
    MB64_BUTTON_SLAB,
    MB64_BUTTON_PURPLE_SWITCH,
    MB64_BUTTON_TIMED_BOX,
    MB64_BUTTON_HEART,
    MB64_BUTTON_FORMATION,
    MB64_BUTTON_VSLAB,
    MB64_BUTTON_SCORNER,
    MB64_BUTTON_UGENTLE,
    MB64_BUTTON_LGENTLE,
    MB64_BUTTON_BARS,
    MB64_BUTTON_THWOMP,
    MB64_BUTTON_WHOMP,
    MB64_BUTTON_POLE,
    MB64_BUTTON_VEXCLA,
    MB64_BUTTON_LAKITU,
    MB64_BUTTON_FLYGUY,
    MB64_BUTTON_SNUFIT,
    MB64_BUTTON_AMP,
    MB64_BUTTON_BOO,
    MB64_BUTTON_MR_I,
    MB64_BUTTON_SCUTTLEBUG,
    MB64_BUTTON_SPINDRIFT,
    MB64_BUTTON_BLIZZARD,
    MB64_BUTTON_MONEYBAG,
    MB64_BUTTON_SKEETER,
    MB64_BUTTON_POKEY,
    MB64_BUTTON_MINE,
    MB64_BUTTON_FIRE,
    MB64_BUTTON_FLAMETHROWER,
    MB64_BUTTON_FIRE_SPITTER,
    MB64_BUTTON_FIRE_SPINNER,
    MB64_BUTTON_BREAKABLE,
    MB64_BUTTON_THROWABLE,
    MB64_BUTTON_CRAZY,
    MB64_BUTTON_DIAMOND,
    MB64_BUTTON_NPC,
    MB64_BUTTON_NPCCM,
    MB64_BUTTON_BUTTON,
    MB64_BUTTON_BLOCK,
    MB64_BUTTON_WOODPLAT,
    MB64_BUTTON_RFBOX,
    MB64_BUTTON_SHOWRUN,
    MB64_BUTTON_POWER,
    MB64_BUTTON_CONVEYOR,
};

u8 mb64_settings_idlist[] = {OBJECT_TYPE_SETTINGS, OBJECT_TYPE_SCREENSHOT};
u8 mb64_star_idlist[] = {OBJECT_TYPE_STAR, OBJECT_TYPE_RED_COIN_STAR};
u8 mb64_goomba_idlist[] = {OBJECT_TYPE_GOOMBA, OBJECT_TYPE_BIG_GOOMBA, OBJECT_TYPE_TINY_GOOMBA};
u8 mb64_piranha_idlist[] = {OBJECT_TYPE_PIRANHA_PLANT, OBJECT_TYPE_BIG_PIRANHA_PLANT, OBJECT_TYPE_TINY_PIRANHA_PLANT};
u8 mb64_bluecoin_idlist[] = {OBJECT_TYPE_BLUE_COIN, OBJECT_TYPE_BLUE_COIN_SWITCH};
u8 mb64_hammer_idlist[] = {OBJECT_TYPE_HAMMER_BRO, OBJECT_TYPE_FIRE_BRO};
u8 mb64_whomp_idlist[] = {OBJECT_TYPE_WHOMP, OBJECT_TYPE_KING_WHOMP};
u8 mb64_bully_idlist[] = {OBJECT_TYPE_BULLY, OBJECT_TYPE_CHILL_BULLY, OBJECT_TYPE_BIG_BULLY, OBJECT_TYPE_BIG_CHILL_BULLY};
u8 mb64_boo_idlist[] = {OBJECT_TYPE_BOO, OBJECT_TYPE_BIG_BOO};
u8 mb64_plat_idlist[] = {OBJECT_TYPE_PLATFORM_TRACK, OBJECT_TYPE_PLATFORM_LOOPING};
u8 mb64_thwomp_idlist[] = {OBJECT_TYPE_THWOMP, OBJECT_TYPE_GRINDEL};
u8 mb64_flame_idlist[] = {OBJECT_TYPE_RED_FLAME, OBJECT_TYPE_BLUE_FLAME};
u8 mb64_npc_idlist[] = {OBJECT_TYPE_SIGN, OBJECT_TYPE_BUDDY, OBJECT_TYPE_TOAD, OBJECT_TYPE_TUXIE, OBJECT_TYPE_UKIKI};
u8 mb64_npccm_idlist[] = {OBJECT_TYPE_SIGN, OBJECT_TYPE_BUDDY, OBJECT_TYPE_MOLEMAN, OBJECT_TYPE_COBIE};
u8 mb64_power_idlist[] = {OBJECT_TYPE_CROWBAR, OBJECT_TYPE_MASK};

struct mb64_ui_button_type mb64_ui_buttons[] = {
/* MB64_BUTTON_SETTINGS */ {MB64_PM_OBJ,  TRUE,  2, &mb64_settings_idlist,    "Options"},
/* MB64_BUTTON_TEST */     {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_TEST_MARIO,  NULL},
/* MB64_BUTTON_TERRAIN */  {MB64_PM_TILE, FALSE, 0, TILE_TYPE_BLOCK,         NULL},
/* MB64_BUTTON_SLOPE */    {MB64_PM_TILE, FALSE, 0, TILE_TYPE_SLOPE,         NULL},
/* MB64_BUTTON_TROLL */    {MB64_PM_TILE, FALSE, 0, TILE_TYPE_TROLL,         NULL},
/* MB64_BUTTON_STAR */     {MB64_PM_OBJ,  TRUE,  2, &mb64_star_idlist,        "Power Star"},
/* MB64_BUTTON_GOOMBA */   {MB64_PM_OBJ,  TRUE,  3, &mb64_goomba_idlist,      "Goomba"},
/* MB64_BUTTON_PIRANHA */  {MB64_PM_OBJ,  TRUE,  3, &mb64_piranha_idlist,     "Piranha Plant"},
/* MB64_BUTTON_KOOPA */    {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_KOOPA,       NULL},
/* MB64_BUTTON_COIN */     {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_COIN,        NULL},
/* MB64_BUTTON_BLANK */    {MB64_PM_TILE, FALSE, 0, TILE_TYPE_BLOCK,         NULL},
/* MB64_BUTTON_GCOIN */    {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_GREEN_COIN,  NULL},
/* MB64_BUTTON_CORNER */   {MB64_PM_TILE, FALSE, 0, TILE_TYPE_CORNER,        NULL},
/* MB64_BUTTON_ICORNER */  {MB64_PM_TILE, FALSE, 0, TILE_TYPE_ICORNER,       NULL},
/* MB64_BUTTON_RCOIN */    {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_RED_COIN,    NULL},
/* MB64_BUTTON_BCOIN */    {MB64_PM_OBJ,  TRUE,  2, &mb64_bluecoin_idlist,    "Blue Coins"},
/* MB64_BUTTON_NOTEBLOCK */{MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_NOTEBLOCK,   NULL},
/* MB64_BUTTON_CULL */     {MB64_PM_TILE, FALSE, 0, TILE_TYPE_CULL,          NULL},
/* MB64_BUTTON_BOBOMB */   {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_BOBOMB,      NULL},
/* MB64_BUTTON_CHUCKYA */  {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_CHUCKYA,     NULL},
/* MB64_BUTTON_BULLY */    {MB64_PM_OBJ,  TRUE,  4, &mb64_bully_idlist,       "Bully"},
/* MB64_BUTTON_BULLET */   {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_BULLET_BILL, NULL},
/* MB64_BUTTON_HEAVEHO */  {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_HEAVE_HO,    NULL},
/* MB64_BUTTON_MOTOS */    {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_MOTOS,       NULL},
/* MB64_BUTTON_TREE */     {MB64_PM_OBJ,  FALSE, 6, OBJECT_TYPE_TREE,        &txt_bp_tree},
/* MB64_BUTTON_EXCLA */    {MB64_PM_OBJ,  FALSE, 7, OBJECT_TYPE_EXCL_BOX,    &txt_bp_box},
/* MB64_BUTTON_SPAWN */    {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_MARIO_SPAWN, NULL},
/* MB64_BUTTON_REX */      {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_REX,         NULL},
/* MB64_BUTTON_PODOBOO */  {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_PODOBOO,     NULL},
/* MB64_BUTTON_CRABLET */  {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_CRABLET,     NULL},
/* MB64_BUTTON_HAMMER_BRO */{MB64_PM_OBJ, TRUE,  2, &mb64_hammer_idlist,      "Hammer Bro"},
/* MB64_BUTTON_CHICKEN */  {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_CHICKEN,     NULL},
/* MB64_BUTTON_PHANTASM */ {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_PHANTASM,    NULL},
/* MB64_BUTTON_PIPE */     {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_WARP_PIPE,   NULL},
/* MB64_BUTTON_BADGE */    {MB64_PM_OBJ,  FALSE, 23, OBJECT_TYPE_BADGE,      &txt_badges},
/* MB64_BUTTON_WATER */    {MB64_PM_WATER,FALSE, 0, TILE_TYPE_WATER,         NULL},
/* MB64_BUTTON_FENCE */    {MB64_PM_TILE, FALSE, 0, TILE_TYPE_FENCE,         NULL},
/* MB64_BUTTON_KING_BOBOMB */ {MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_KING_BOBOMB, NULL},
/* MB64_BUTTON_WIGGLER */  {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_WIGGLER,     NULL},
/* MB64_BUTTON_BOWSER */   {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_BOWSER,      NULL},
/* MB64_BUTTON_MPLAT */    {MB64_PM_OBJ,  TRUE,  2, &mb64_plat_idlist,        "Moving Platform"},
/* MB64_BUTTON_BBALL */    {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_BOWLING_BALL, NULL},
/* MB64_BUTTON_KTQ */      {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_KOOPA_THE_QUICK, NULL},
/* MB64_BUTTON_SSLOPE */   {MB64_PM_TILE, FALSE, 0, TILE_TYPE_SSLOPE,        NULL},
/* MB64_BUTTON_SLAB */     {MB64_PM_TILE, FALSE, 0, TILE_TYPE_SLAB,          NULL},
/* MB64_BUTTON_PURPLE_SWITCH */{MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_PURPLE_SWITCH, NULL},
/* MB64_BUTTON_TIMED_BOX */ {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_TIMED_BOX,   NULL},
/* MB64_BUTTON_HEART */    {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_RECOVERY_HEART, NULL},
/* MB64_BUTTON_FORMATION */{MB64_PM_OBJ,  FALSE, 5, OBJECT_TYPE_COIN_FORMATION, &txt_coin_formation},
/* MB64_BUTTON_VSLAB */    {MB64_PM_TILE, FALSE, 0, TILE_TYPE_SSLAB,         NULL},
/* MB64_BUTTON_SCORNER */  {MB64_PM_TILE, FALSE, 0, TILE_TYPE_SCORNER,       NULL},
/* MB64_BUTTON_UGENTLE */  {MB64_PM_TILE, FALSE, 0, TILE_TYPE_UGENTLE,       NULL},
/* MB64_BUTTON_LGENTLE */  {MB64_PM_TILE, FALSE, 0, TILE_TYPE_LGENTLE,       NULL},
/* MB64_BUTTON_BARS */     {MB64_PM_TILE, FALSE, 0, TILE_TYPE_BARS,          NULL},
/* MB64_BUTTON_THWOMP */   {MB64_PM_OBJ,  TRUE,  2, &mb64_thwomp_idlist,      "Thwomp"},
/* MB64_BUTTON_WHOMP */    {MB64_PM_OBJ,  TRUE,  2, &mb64_whomp_idlist,       "Whomp"},
/* MB64_BUTTON_POLE */     {MB64_PM_TILE, FALSE, 0, TILE_TYPE_POLE,          NULL},
/* MB64_BUTTON_VEXCLA */   {MB64_PM_OBJ,  FALSE, 7, OBJECT_TYPE_EXCL_BOX,    &txt_bp_vbox},
/* MB64_BUTTON_LAKITU */   {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_LAKITU,      NULL},
/* MB64_BUTTON_FLYGUY */   {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_FLY_GUY,     NULL},
/* MB64_BUTTON_SNUFIT */   {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_SNUFIT,      NULL},
/* MB64_BUTTON_AMP */      {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_AMP,         NULL},
/* MB64_BUTTON_BOO */      {MB64_PM_OBJ,  TRUE,  2, &mb64_boo_idlist,         "Boo"},
/* MB64_BUTTON_MR_I */     {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_MR_I,        NULL},
/* MB64_BUTTON_SCUTTLEBUG */{MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_SCUTTLEBUG,  NULL},
/* MB64_BUTTON_SPINDRIFT */{MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_SPINDRIFT,   NULL},
/* MB64_BUTTON_BLIZZARD */ {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_MR_BLIZZARD, NULL},
/* MB64_BUTTON_MONEYBAG */ {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_MONEYBAG,    NULL},
/* MB64_BUTTON_SKEETER */  {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_SKEETER,     NULL},
/* MB64_BUTTON_POKEY */    {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_POKEY,       NULL},
/* MB64_BUTTON_MINE */     {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_BOWSER_BOMB, NULL},
/* MB64_BUTTON_FIRE */     {MB64_PM_OBJ,  TRUE,  2, &mb64_flame_idlist,       "Flame"},
/* MB64_BUTTON_FLAMETHROWER */{MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_FLAMETHROWER, NULL},
/* MB64_BUTTON_FIRE_SPITTER */{MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_FIRE_SPITTER, NULL},
/* MB64_BUTTON_FIRE_SPINNER */{MB64_PM_OBJ, FALSE, 5, OBJECT_TYPE_FIRE_SPINNER, &txt_fire_spinner},
/* MB64_BUTTON_BREAKABLE */{MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_BBOX_NORMAL, NULL},
/* MB64_BUTTON_THROWABLE */{MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_BBOX_SMALL, NULL},
/* MB64_BUTTON_CRAZY */    {MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_BBOX_CRAZY, NULL},
/* MB64_BUTTON_DIAMOND */  {MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_DIAMOND, NULL},
/* MB64_BUTTON_NPC */      {MB64_PM_OBJ, TRUE, 5, mb64_npc_idlist, "NPC"},
/* MB64_BUTTON_NPCCM */    {MB64_PM_OBJ, TRUE, 4, mb64_npccm_idlist, "NPC"},
/* MB64_BUTTON_BUTTON */   {MB64_PM_OBJ, FALSE, 2, OBJECT_TYPE_BUTTON, &txt_onoff},
/* MB64_BUTTON_BLOCK */    {MB64_PM_OBJ, FALSE, 2, OBJECT_TYPE_ON_OFF_BLOCK, &txt_onoff},
/* MB64_BUTTON_WOODPLAT */ {MB64_PM_OBJ, FALSE, 2, OBJECT_TYPE_WOODPLAT, &txt_woodplat},
/* MB64_BUTTON_RFBOX */    {MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_RFBOX, NULL},
/* MB64_BUTTON_SHOWRUN */  {MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_SHOWRUNNER, NULL},
/* MB64_BUTTON_POWER */    {MB64_PM_OBJ, TRUE, 2, mb64_power_idlist, "Powerup"},
/* MB64_BUTTON_CONVEYOR */ {MB64_PM_OBJ, FALSE, 8, OBJECT_TYPE_CONVEYOR, &txt_conveyor},
};

u8 mb64_toolbar_defaults[9] = {
    MB64_BUTTON_TERRAIN,
    MB64_BUTTON_SLOPE,
    MB64_BUTTON_BARS,
    MB64_BUTTON_TREE,
    MB64_BUTTON_COIN,
    MB64_BUTTON_STAR,
    MB64_BUTTON_GOOMBA,
    MB64_BUTTON_TEST,
    MB64_BUTTON_SETTINGS,
};

u8 mb64_toolbar[9];
u8 mb64_toolbar_params[9];
f32 mb64_toolbar_y_anim[9] = {
    0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
};
u8 mb64_toolbox_transition_btn_render = FALSE;
f32 mb64_toolbox_transition_btn_x;
f32 mb64_toolbox_transition_btn_y;
f32 mb64_toolbox_transition_btn_tx;
f32 mb64_toolbox_transition_btn_ty;
Gfx * mb64_toolbox_transition_btn_gfx;
Gfx * mb64_toolbox_transition_btn_old_gfx;
f32 mb64_toolbox_transition_progress;

// went a bit Define Crazy over here, im just quirky like that
#define TOOLBOX_PAGE_WIDTH 9
#define TOOLBOX_NUM_PAGES 2

#define TOOLBOX_WIDTH (TOOLBOX_PAGE_WIDTH * TOOLBOX_NUM_PAGES)
#define TOOLBOX_HEIGHT 5

// gap between the pages
#define TOOLBOX_PAGE_OFFSET 30
#define TOOLBOX_SIZE (TOOLBOX_WIDTH * TOOLBOX_HEIGHT)

// X offset based on scroll
#define TOOLBOX_OFFSET_MIN 34
#define TOOLBOX_OFFSET_MAX ((TOOLBOX_OFFSET_MIN - (32*TOOLBOX_PAGE_WIDTH)) - TOOLBOX_PAGE_OFFSET)

s32 mb64_toolbox_x_offset = TOOLBOX_OFFSET_MIN;

// macros to get position of a certain toolbox position
#define GET_TOOLBOX_X(i) (mb64_toolbox_x_offset + (((i) % TOOLBOX_WIDTH)*32) + ((i) % TOOLBOX_WIDTH >= TOOLBOX_PAGE_WIDTH ? TOOLBOX_PAGE_OFFSET : 0))
#define GET_TOOLBOX_Y(i) (220 - (((i) / TOOLBOX_WIDTH)*32))

u8 mb64_toolbox[TOOLBOX_SIZE];
u8 mb64_toolbox_params[TOOLBOX_SIZE];
//Different toolboxes for different game styles
#define _ MB64_BUTTON_BLANK
u8 mb64_toolbox_btcm[TOOLBOX_SIZE] = {
    MB64_BUTTON_TERRAIN, MB64_BUTTON_SLAB, MB64_BUTTON_SLOPE, MB64_BUTTON_CORNER, MB64_BUTTON_ICORNER, MB64_BUTTON_VSLAB, MB64_BUTTON_SSLOPE, MB64_BUTTON_SCORNER, _,
    MB64_BUTTON_GOOMBA, MB64_BUTTON_BOBOMB, MB64_BUTTON_CHUCKYA, MB64_BUTTON_KOOPA, MB64_BUTTON_LAKITU, MB64_BUTTON_FLYGUY, MB64_BUTTON_SNUFIT, MB64_BUTTON_THWOMP, MB64_BUTTON_WHOMP,

    MB64_BUTTON_LGENTLE, MB64_BUTTON_UGENTLE, MB64_BUTTON_TROLL, MB64_BUTTON_WATER, MB64_BUTTON_FENCE, MB64_BUTTON_BARS, MB64_BUTTON_POLE, MB64_BUTTON_TREE, MB64_BUTTON_CULL,
    MB64_BUTTON_BULLY, MB64_BUTTON_MOTOS, MB64_BUTTON_HEAVEHO, MB64_BUTTON_BULLET, MB64_BUTTON_AMP, MB64_BUTTON_PIRANHA, MB64_BUTTON_BOO,MB64_BUTTON_MR_I,MB64_BUTTON_SCUTTLEBUG,

    MB64_BUTTON_STAR, MB64_BUTTON_COIN, MB64_BUTTON_FORMATION, MB64_BUTTON_GCOIN, MB64_BUTTON_RCOIN, MB64_BUTTON_BCOIN, MB64_BUTTON_EXCLA, MB64_BUTTON_HEART, MB64_BUTTON_BADGE,
    MB64_BUTTON_SPINDRIFT,MB64_BUTTON_BLIZZARD,MB64_BUTTON_MONEYBAG,MB64_BUTTON_SKEETER, MB64_BUTTON_POKEY, MB64_BUTTON_REX, MB64_BUTTON_HAMMER_BRO, MB64_BUTTON_PODOBOO, MB64_BUTTON_PHANTASM,

    MB64_BUTTON_MPLAT, MB64_BUTTON_PURPLE_SWITCH, MB64_BUTTON_TIMED_BOX, MB64_BUTTON_BREAKABLE, MB64_BUTTON_RFBOX, MB64_BUTTON_DIAMOND, MB64_BUTTON_WOODPLAT, MB64_BUTTON_NPCCM, _,
    MB64_BUTTON_FIRE, MB64_BUTTON_FLAMETHROWER, MB64_BUTTON_FIRE_SPITTER, MB64_BUTTON_FIRE_SPINNER, MB64_BUTTON_BBALL, _, MB64_BUTTON_CHICKEN, MB64_BUTTON_CRABLET, MB64_BUTTON_SHOWRUN,

    MB64_BUTTON_NOTEBLOCK, MB64_BUTTON_BUTTON, MB64_BUTTON_BLOCK, MB64_BUTTON_CONVEYOR, _, _, _, _, _,
    MB64_BUTTON_SPAWN, MB64_BUTTON_THROWABLE, MB64_BUTTON_CRAZY, MB64_BUTTON_POWER, _, _, _, _, _,
};

u8 mb64_toolbox_vanilla[TOOLBOX_SIZE] = {
    MB64_BUTTON_TERRAIN, MB64_BUTTON_SLAB, MB64_BUTTON_SLOPE, MB64_BUTTON_CORNER, MB64_BUTTON_ICORNER, MB64_BUTTON_VSLAB, MB64_BUTTON_SSLOPE, MB64_BUTTON_SCORNER, _,
    MB64_BUTTON_GOOMBA, MB64_BUTTON_BOBOMB, MB64_BUTTON_CHUCKYA, MB64_BUTTON_KOOPA, MB64_BUTTON_LAKITU, MB64_BUTTON_FLYGUY, MB64_BUTTON_SNUFIT, MB64_BUTTON_THWOMP, MB64_BUTTON_WHOMP,

    MB64_BUTTON_LGENTLE, MB64_BUTTON_UGENTLE, MB64_BUTTON_TROLL, MB64_BUTTON_WATER, MB64_BUTTON_FENCE, MB64_BUTTON_BARS, MB64_BUTTON_POLE, MB64_BUTTON_TREE, MB64_BUTTON_CULL,
    MB64_BUTTON_BULLY, MB64_BUTTON_MOTOS, MB64_BUTTON_HEAVEHO, MB64_BUTTON_BULLET, MB64_BUTTON_AMP, MB64_BUTTON_PIRANHA, MB64_BUTTON_BOO,MB64_BUTTON_MR_I,MB64_BUTTON_SCUTTLEBUG,

    MB64_BUTTON_STAR, MB64_BUTTON_COIN, MB64_BUTTON_FORMATION, MB64_BUTTON_RCOIN, MB64_BUTTON_BCOIN, MB64_BUTTON_VEXCLA, MB64_BUTTON_HEART, MB64_BUTTON_KTQ, _,
    MB64_BUTTON_SPINDRIFT,MB64_BUTTON_BLIZZARD,MB64_BUTTON_MONEYBAG,MB64_BUTTON_SKEETER, MB64_BUTTON_POKEY, MB64_BUTTON_KING_BOBOMB, MB64_BUTTON_WIGGLER, MB64_BUTTON_BOWSER, _,

    MB64_BUTTON_MPLAT, MB64_BUTTON_PURPLE_SWITCH, MB64_BUTTON_TIMED_BOX, MB64_BUTTON_BREAKABLE, MB64_BUTTON_RFBOX, MB64_BUTTON_DIAMOND, MB64_BUTTON_WOODPLAT, MB64_BUTTON_NPC, _,
    MB64_BUTTON_FIRE, MB64_BUTTON_FLAMETHROWER, MB64_BUTTON_FIRE_SPITTER, MB64_BUTTON_FIRE_SPINNER, MB64_BUTTON_BBALL, _, _, _, _,

    MB64_BUTTON_NOTEBLOCK, MB64_BUTTON_BUTTON, MB64_BUTTON_BLOCK, MB64_BUTTON_CONVEYOR, _, _, _, _, _,
    MB64_BUTTON_SPAWN, MB64_BUTTON_THROWABLE, MB64_BUTTON_CRAZY, MB64_BUTTON_MINE, _, _, _, _, _,
};

char *mb64_costume_string_table[] = {
    "Mario",
    "Fire Mario",
    "Glitchy",
    "Luigi",
    "Wario",
    "Disco Mario",
    "Undead Pirate",
    "Mocap Mario",
    "Darius",
    "Butler Mario",
    "Retro Mario",
    "Thwompio",
    "Builder Mario",
    "Showrunner",
    "Cosmic Phantasm",
};

char *mb64_music_type_string_table[] = {
    "Level",
    "Koopa Race",
    "Bossfight",
};

char *mb64_music_album_string_table[] = {
    "Super Mario 64 OST",
    "Beyond the Cursed Mirror OST",
    "ROM Hack Music Ports",
    "Retro 2D Mario Music"
};

char *mb64_music_vanilla_string_table[] = {
    "Bob-omb Battlefield",
    "Slider",
    "Dire, Dire Docks",
    "Dire, Dire Docks (Underwater)",
    "Lethal Lava Land",
    "Cool, Cool Mountain",
    "Big Boo's Haunt",
    "Hazy Maze Cave",
    "Hazy Maze Cave (Haze)",
    "Koopa's Road",
    "Stage Boss",
    "Koopa's Theme",
    "Ultimate Koopa",
    "Inside the Castle Walls",
};

char *mb64_music_btcm_string_table[] = {
    "Cosmic Castle",
    "Red-Hot Reservoir",
    "Lonely Floating Farm",
    "Jurassic Savanna",
    "The Phantom Strider",
    "Virtuaplex",
    "Immense Residence",
    "Thwomp Towers",
    "Cursed Boss",
    "Road To The Boss",
    "Urbowser",
    "The Show's Finale",
    "Parasite Moon",
    "AGAMEMNON",
};

char *mb64_music_romhack_string_table[] = {
    "Bianco Hills (Super Mario Sunshine)",
    "Sky and Sea (Super Mario Sunshine)",
    "Secret Course (Super Mario Sunshine)",
    "Comet Observatory (Mario Galaxy)",
    "Buoy Base Galaxy (Mario Galaxy)",
    "Battlerock Galaxy (Mario Galaxy)",
    "Ghostly Galaxy (Mario Galaxy)",
    "Purple Comet (Mario Galaxy)",
    "Honeybloom Galaxy (Mario Galaxy 2)",
    "Piranha Creeper Creek (3D World)",
    "Desert (New Super Mario Bros.)",

    "Koopa Troopa Beach (Mario Kart 64)",
    "Frappe Snowland (Mario Kart 64)",
    "Bowser's Castle (Mario Kart 64)",
    "Rainbow Road (Mario Kart 64)",
    "Waluigi Pinball (Mario Kart DS)",
    "Rainbow Road (Mario Kart 8)",

    "Mario's Pad (Super Mario RPG)",
    "Nimbus Land (Super Mario RPG)",
    "Forest Maze (Super Mario RPG)",
    "Sunken Ship (Super Mario RPG)",

    "Dry Dry Desert (Paper Mario 64)",
    "Forever Forest (Paper Mario 64)",
    "Petal Meadows (Paper Mario: TTYD)",
    "Riddle Tower (Paper Mario: TTYD)",
    "Rogueport Sewers (Paper Mario: TTYD)",
    "X-Naut Fortress (Paper Mario: TTYD)",
    "Flipside (Super Paper Mario)",
    "Lineland Road (Super Paper Mario)",
    "Sammer Kingdom (Super Paper Mario)",
    "Floro Caverns (Super Paper Mario)",
    "Overthere Stair (Super Paper Mario)",

    "Yoshi's Tropical Island (Mario Party)",
    "Rainbow Castle (Mario Party)",
    "Behind Yoshi Village (Partners in Time)",
    "Gritzy Desert (Partners in Time)",
    "Bumpsy Plains (Bowser's Inside Story)",
    "Deep Castle (Bowser's Inside Story)",

    "Overworld (Yoshi's Island)",
    "Underground (Yoshi's Island)",
    "Title (Yoshi's Story)",

    "Kokiri Forest (Ocarina of Time)",
    "Lost Woods (Ocarina of Time)",
    "Gerudo Valley (Ocarina of Time)",
    "Stone Tower Temple (Majora's Mask)",
    "Outset Island (Wind Waker)",
    "Lake Hylia (Twilight Princess)",
    "Gerudo Desert (Twilight Princess)",
    "Skyloft (Skyward Sword)",

    "Frantic Factory (Donkey Kong 64)",
    "Hideout Helm (Donkey Kong 64)",
    "Creepy Castle (Donkey Kong 64)",
    "Gloomy Galleon (Donkey Kong 64)",
    "Fungi Forest (Donkey Kong 64)",
    "Crystal Caves (Donkey Kong 64)",
    "Angry Aztec (Donkey Kong 64)",
    "In a Snow-Bound Land (DKC 2)",

    "Bubblegloop Swamp (Banjo-Kazooie)",
    "Freezeezy Peak (Banjo-Kazooie)",
    "Gobi's Valley (Banjo-Kazooie)",

    "Factory Inspection (Kirby 64)",
    "Green Garden (Bomberman 64)",
    "Black Fortress (Bomberman 64)",
    "Windy Hill (Sonic Adventure)",
    "Sky Tower (Pokemon Mystery Dungeon)",
    "Youkai Mountain (Touhou 10)",
    "Forest Temple (Final Fantasy VII)",
    "Band Land (Rayman)",
};

char *mb64_music_retro_string_table[] = {
    "Overworld (Super Mario Bros.)",
    "Castle Mix (Super Mario Bros.)",
    "Overworld (Super Mario Bros. 2)",
    "Overworld Mix (Super Mario Bros. 3)",
    "Fortress (Super Mario Bros. 3)",
    "Athletic (Super Mario World)",
    "Castle (Super Mario World)",
};

u8 seq_musicmenu_array[] = {
    SEQ_LEVEL_GRASS,
    SEQ_LEVEL_SLIDE,
    SEQ_LEVEL_WATER,
    SEQ_LEVEL_WATER,
    SEQ_LEVEL_HOT,
    SEQ_LEVEL_SNOW,
    SEQ_LEVEL_SPOOKY,
    SEQ_LEVEL_UNDERGROUND,
    SEQ_LEVEL_UNDERGROUND,
    SEQ_LEVEL_KOOPA_ROAD_2,
    SEQ_VANILLA_BOSS,
    SEQ_LEVEL_BOSS_KOOPA,
    SEQ_LEVEL_BOSS_KOOPA_FINAL,
    SEQ_LEVEL_INSIDE_CASTLE2,

    SEQ_LEVEL_INSIDE_CASTLE,
    SEQ_REDHOT,
    SEQ_FARM,
    SEQ_JUNGLE,
    SEQ_PIRATE,
    SEQ_EVENT_CUTSCENE_ENDING,
    SEQ_BIG_HOUSE,
    SEQ_NSMB_CASTLE,
    SEQ_EVENT_BOSS,
    SEQ_LEVEL_KOOPA_ROAD,
    SEQ_COSMIC_SEED_BOSS,
    SEQ_SHOWRUNNER_BOSS,
    SEQ_COSMIC_SEED_LEVEL,
    SEQ_FINAL_BOSS,

    SEQ_SMS_BIANCO_HILLS,
    SEQ_SMS_SKY_AND_SEA,
    SEQ_SMS_SECRET_COURSE,
    SEQ_SMG_COMET_OBSERVATORY,
    SEQ_SMG_BUOY_BASE,
    SEQ_SMG_BATTLEROCK,
    SEQ_SMG_GHOSTLY_GALAXY,
    SEQ_SMG_PURPLE_COMET,
    SEQ_SMG2_HONEYBLOOM,
    SEQ_PIRANHA_CREEK,
    SEQ_NSMB_DESERT,

    SEQ_KOOPA_BEACH, // mk64 koopa troopa beach
    SEQ_FRAPPE_SNOWLAND,
    SEQ_MK64_BOWSERS_CASTLE,
    SEQ_MK64_RAINBOW_ROAD,
    SEQ_MKDS_WALUIGI_PINBALL,
    SEQ_MK8_RAINBOW_ROAD,

    SEQ_SMRPG_MARIOS_PAD,             // 0x46
    SEQ_SMRPG_NIMBUS_LAND,
    SEQ_FOREST_MAZE,
    SEQ_SMRPG_SUNKEN_SHIP,            // 0x47

    SEQ_PM_DRY_DESERT,
    SEQ_PM_FOREVER_FOREST,
    SEQ_TTYD_PETAL_MEADOWS,
    SEQ_TTYD_EIGHT_KEY_DOMAIN, // riddle tower
    SEQ_TTYD_ROGUEPORT_SEWERS,
    SEQ_TTYD_XNAUT_FORTRESS,
    SEQ_SPM_FLIPSIDE,
    SEQ_SPM_LINELAND_ROAD,
    SEQ_SAMMER_KINGDOM,
    SEQ_SPM_FLORO_CAVERNS,
    SEQ_SPM_OVERTHERE_STAIR,

    SEQ_MP_YOSHIS_TROPICAL_ISLAND,
    SEQ_MP_RAINBOW_CASTLE,
    SEQ_MLPIT_BEHIND_YOSHI_VILLAGE,
    SEQ_PIT_GRITZY_DESERT,
    SEQ_BIS_BUMPSY_PLAINS,
    SEQ_BIS_DEEP_CASTLE,
    SEQ_YI_OVERWORLD,
    SEQ_YI_CRYSTAL_CAVES,
    SEQ_YS_TITLE,                     // 0x51

    SEQ_OOT_KOKIRI_FOREST,
    SEQ_OOT_LOST_WOODS,
    SEQ_OOT_GERUDO_VALLEY,            // 0x52
    SEQ_STONE_TOWER_TEMPLE,
    SEQ_WW_OUTSET_ISLAND,
    SEQ_TP_LAKE_HYLIA,                // 0x53
    SEQ_TP_GERUDO_DESERT,
    SEQ_SS_SKYLOFT,

    SEQ_DK64_FRANTIC_FACTORY,
    SEQ_DK64_HIDEOUT_HELM,
    SEQ_DK_CREEPY_CASTLE,
    SEQ_DK64_GLOOMY_GALLEON,
    SEQ_DK64_FUNGI_FOREST,
    SEQ_DK64_CRYSTAL_CAVES,
    SEQ_DK64_ANGRY_AZTEC,
    SEQ_DKC2_SNOWBOUND_LAND,

    SEQ_BK_BUBBLEGLOOP_SWAMP,
    SEQ_BK_FREEZEEZY_PEAKS,
    SEQ_BK_GOBI_VALLEY,

    SEQ_K64_FACTORY_INSPECTION,
    SEQ_BM_GREEN_GARDEN,
    SEQ_BM_BLACK_FORTRESS,
    SEQ_SA_WINDY_HILL,
    SEQ_PKMN_SKY_TOWER,
    SEQ_TOUHOU_YOUKAI_MOUNTAIN,
    SEQ_FOREST_TEMPLE,
    SEQ_RAYMAN_BAND_LAND,

    SEQ_SMB1_OVERWORLD,
    SEQ_SMB_BOWSER_REMIX,             // 0x4B
    SEQ_SMB2_OVERWORLD,
    SEQ_SMB3_OVERWORLD,
    SEQ_SMB3_CASTLE,
    SEQ_SMW_ATHLETIC,                 // 0x4E
    SEQ_SMW_CASTLE,
};

char *mb64_envfx_string_table[] = {
    "None",
    "Ashes",
    "Snow",
    "Rain",
    "Sandstorm",
};

//envfx table
u8 mb64_envfx_table[] = {
    ENVFX_NONE,         // no effects
    ENVFX_ASHES,       // CCM, SL
    ENVFX_SNOW,     // unused
    ENVFX_RAIN,
    ENVFX_SANDSTORM,
};

char *mb64_theme_string_table[] = {
    "Generic",
    "Shifting Sand Land",
    "Red Hot Reservoir",
    "Hazy Maze Cave",
    "Peach's Castle",
    "Virtuaplex",
    "Snowy Palace",
    "Big Boo's Haunt",
    "Jolly Roger Bay",
    "Retroland",
    "Custom",
    "Minecraft",
};

//themes moved to mb64.h to work with object df
//example: ice bully appears in snow theme
//impossible to extern enum : (

char *mb64_bg_string_table[] = {
    "Ocean Hills",
    "Cloudy Sky",
    "Fiery Sky",
    "Green Cave",
    "Haunted Forest", // 4 - doesn't generate black chasm
    "Ice Mountains",
    "Desert Pyramids",
    "Underwater City",
    "Pink Sky",
    "None", // 9 - doesn't generate black chasm
};

u8 mb64_boundary_table[] = {
    0, // Void
    MB64_BOUNDARY_INNER_FLOOR | MB64_BOUNDARY_OUTER_FLOOR, // Plain
    MB64_BOUNDARY_INNER_FLOOR | MB64_BOUNDARY_OUTER_FLOOR | MB64_BOUNDARY_INNER_WALLS, // Valley
    MB64_BOUNDARY_OUTER_FLOOR | MB64_BOUNDARY_INNER_WALLS, // Chasm
    MB64_BOUNDARY_INNER_FLOOR | MB64_BOUNDARY_OUTER_WALLS, // Plateau
    MB64_BOUNDARY_INNER_FLOOR | MB64_BOUNDARY_INNER_WALLS | MB64_BOUNDARY_CEILING, // Interior
};

#define AT_CEILING(y) ((mb64_curr_boundary & MB64_BOUNDARY_CEILING) && ((y) == mb64_lopt_boundary_height-1))

char *mb64_bound_string_table[] = {
    "Void",
    "Plain",
    "Valley",
    "Chasm",
    "Plateau",
    "Interior",
};

//skybox table
u8 *mb64_skybox_table[] = {
    _water_skybox_yay0SegmentRomStart,
    _water_skybox_yay0SegmentRomEnd,
    _cloud_floor_skybox_yay0SegmentRomStart,
    _cloud_floor_skybox_yay0SegmentRomEnd,
    _bitfs_skybox_yay0SegmentRomStart,
    _bitfs_skybox_yay0SegmentRomEnd,
    _bidw_skybox_yay0SegmentRomStart,
    _bidw_skybox_yay0SegmentRomEnd,
    _bbh_skybox_yay0SegmentRomStart,
    _bbh_skybox_yay0SegmentRomEnd,
    _ccm_skybox_yay0SegmentRomStart,
    _ccm_skybox_yay0SegmentRomEnd,
    _ssl_skybox_yay0SegmentRomStart,
    _ssl_skybox_yay0SegmentRomEnd,
    _wdw_skybox_yay0SegmentRomStart,
    _wdw_skybox_yay0SegmentRomEnd,
    _bits_skybox_yay0SegmentRomStart,
    _bits_skybox_yay0SegmentRomEnd,
    NULL,
    NULL,
};

extern char *mb64_get_floor_name(s32, char *);
extern char *mb64_get_coinstar_str(s32, char *);
extern char *mb64_get_waterlevel_name(s32, char *);
extern char *mb64_get_boundaryheight_name(s32, char *);
extern char *mb64_get_category(s32, char *);
extern char *mb64_get_custom_mat(s32, char *);
extern void reload_bg(void);
extern void reload_theme(void);
extern void generate_terrain_gfx(void);

extern void music_type_changed(void);
extern void music_category_changed(void);
extern void song_changed(void);

struct mb64_settings_button mb64_settings_misc_buttons[] = {
    {"Coin Star:", &mb64_lopt_coinstar, NULL, 1, mb64_get_coinstar_str, NULL},
    {"Water Level:", &mb64_lopt_waterlevel, NULL,               65,               mb64_get_waterlevel_name, generate_terrain_gfx},
    {"Costume:", &mb64_lopt_costume, mb64_costume_string_table, ARRAY_COUNT(mb64_costume_string_table), NULL, NULL},
};

#define MISC_COINSTAR_INDEX 0
#define MISC_WATER_INDEX 1
#define MISC_COSTUME_INDEX 2

struct mb64_settings_button mb64_settings_misc_buttons_vanilla[] = {
    {"Coin Star:", &mb64_lopt_coinstar, NULL, 1, mb64_get_coinstar_str, NULL},
    {"Water Level:", &mb64_lopt_waterlevel, NULL,               65,               mb64_get_waterlevel_name, generate_terrain_gfx},
};
#define MISCV_COINSTAR_INDEX 0
#define MISCV_WATER_INDEX 1

struct mb64_settings_button mb64_settings_env_buttons[] = {
    {"Theme:",   &mb64_lopt_theme,   mb64_theme_string_table,   ARRAY_COUNT(mb64_theme_string_table) - 1, NULL, reload_theme},
    {"Skybox:",  &mb64_lopt_bg,      mb64_bg_string_table,      ARRAY_COUNT(mb64_bg_string_table),    NULL, reload_bg},
    {"Effect:",  &mb64_lopt_envfx,   mb64_envfx_string_table,   ARRAY_COUNT(mb64_envfx_string_table), NULL, NULL},
};
#define ENV_THEME_INDEX 0
#define ENV_SKYBOX_INDEX 1
#define ENV_EFFECT_INDEX 2

struct mb64_settings_button mb64_settings_boundary_buttons[] = {
    {"Boundary:", &mb64_lopt_boundary, mb64_bound_string_table, ARRAY_COUNT(mb64_bound_string_table), NULL, generate_terrain_gfx},
    {"Material:",   &mb64_lopt_boundary_mat, NULL, NUM_MATERIALS_PER_THEME, mb64_get_floor_name, generate_terrain_gfx}, // Filled in by code
    {"Height:", &mb64_lopt_boundary_height,   NULL, 65, mb64_get_boundaryheight_name, generate_terrain_gfx},
};

#define BOUNDARY_BOUNDARY_INDEX 0
#define BOUNDARY_TILE_INDEX 1
#define BOUNDARY_HEIGHT_INDEX 2

struct mb64_settings_button mb64_settings_music_buttons[] = {
    {"Type:", &mb64_lopt_seq_seqtype, mb64_music_type_string_table, ARRAY_COUNT(mb64_music_type_string_table), NULL, music_type_changed},
    {"Album:",   &mb64_lopt_seq_album,  mb64_music_album_string_table,  ARRAY_COUNT(mb64_music_album_string_table), NULL, music_category_changed},
    {"Song:", NULL, NULL, 0, NULL, NULL}, // Filled in by code
};
#define MUSIC_ALBUM_INDEX 1
#define MUSIC_SONG_INDEX 2

struct mb64_settings_button mb64_settings_mat_selector[] = {
    {"Category:", NULL, NULL, ARRAY_COUNT(mb64_matlist) - 1, mb64_get_category,   NULL},
    {"Material:", NULL, NULL, 0, mb64_get_custom_mat, NULL},
};

char *mb64_fence_names[] = {
    "Wooden (1)",
    "Wooden (2)",
    "Wooden (3)",
    "Barbed Wire",
    "Metal",
    "Netting",
    "Castle",
    "Stanchion",
    "Mansion",
    "Rope",
    "Snowy (1)",
    "Snowy (2)",
};

char *mb64_bar_names[] = {
    "Grille",
    "Mesh",
    "Fine Mesh",
    "Red Grille",
    "Red Mesh",
    "Pink Mesh",
    "Clock Grille",
    "Desert Grille",
    "Cage Bars",
};

char *mb64_water_names[] = {
    "Default",
    "Swampy",
};

struct mb64_settings_button mb64_settings_other_selectors[] = {
    {"Fence:", &mb64_curr_custom_theme.fence, mb64_fence_names, ARRAY_COUNT(mb64_fence_names), NULL, NULL},
    {"Iron Mesh:", &mb64_curr_custom_theme.bars, mb64_bar_names, ARRAY_COUNT(mb64_bar_names), NULL, NULL},
    {"Water:", &mb64_curr_custom_theme.water, mb64_water_names, ARRAY_COUNT(mb64_water_names), NULL, NULL},
};

char *mb64_settings_menu_names[] = {
    "Environment",
    "Level Boundary",
    "Music",
    "Miscellaneous",
    "System",
};

char *mb64_settings_system_buttons[] = {
    "Save & Quit",
    "Play Level",
    //"Level Size:",
    //"Apply Size Change (Dangerous!)",
};


void draw_mb64_settings_misc(f32,f32);
void draw_mb64_settings_misc_vanilla(f32,f32);
void draw_mb64_settings_env(f32,f32);
void draw_mb64_settings_boundary(f32,f32);
void draw_mb64_settings_music(f32,f32);
void draw_mb64_settings_system(f32,f32);

void (*mb64_settings_menus[])(f32, f32) = {
    draw_mb64_settings_env,
    draw_mb64_settings_boundary,
    draw_mb64_settings_music,
    draw_mb64_settings_misc,
    draw_mb64_settings_system,
};

u8 mb64_settings_menu_lengths[] = {
    ARRAY_COUNT(mb64_settings_env_buttons),
    ARRAY_COUNT(mb64_settings_boundary_buttons),
    ARRAY_COUNT(mb64_settings_music_buttons),
    ARRAY_COUNT(mb64_settings_misc_buttons),
    ARRAY_COUNT(mb64_settings_system_buttons),
};

#define SETTINGS_ENV_INDEX 0
#define SETTINGS_BOUNDARY_INDEX 1
#define SETTINGS_MUSIC_INDEX 2
#define SETTINGS_MISC_INDEX 3
#define SETTINGS_SYSTEM_INDEX 4

// These get copied over to the above array
struct mb64_settings_button mb64_settings_music_albums[] = {
    {"Song:",  &mb64_lopt_seq_song, mb64_music_vanilla_string_table, ARRAY_COUNT(mb64_music_vanilla_string_table), NULL, song_changed},
    {"Song:",  &mb64_lopt_seq_song, mb64_music_btcm_string_table, ARRAY_COUNT(mb64_music_btcm_string_table), NULL, song_changed},
    {"Song:",  &mb64_lopt_seq_song, mb64_music_romhack_string_table, ARRAY_COUNT(mb64_music_romhack_string_table), NULL, song_changed},
    {"Song:",  &mb64_lopt_seq_song, mb64_music_retro_string_table, ARRAY_COUNT(mb64_music_retro_string_table), NULL, song_changed},
};

struct mb64_settings_button mb64_settings_backtomainmenu[] = {
};

char *mb64_gamemode_string_table[] = {
    "Vanilla SM64",
    "Cursed Mirror",
};

char *mb64_levelsize_string_table[] = {
    "Small (32)",
    "Medium (48)",
    "Large (64)",
};

char *mb64_template_string_table[] = {
    "Grassy",
    "Desert",
    "Lava",
    "Underwater",
    "Snowy",
};

struct mb64_template {
    u8 music[2]; // vanilla, btcm
    u8 envfx;
    u8 bg;
    u8 theme;
    u8 plane;

    u8 spawnHeight;
    u8 platform;
};

struct mb64_template mb64_templates[] = {
    {{0, 16}, 0, 0, 0, 0,     2, FALSE},   // Grassy - BoB, Floating Farm
    {{4, 49}, 0, 6, 1, 0,     2, FALSE},   // Desert - LLL, Dry Dry Desert
    {{4, 15}, 1, 2, 2, 8,     2, TRUE},    // Lava -   LLL, Red-Hot Reservoir
    {{2, 29}, 0, 0, 8, 0,     2, FALSE},   // Water -  DDD, Sky and Sea
    {{5, 39}, 2, 5, 6, 0,     2, FALSE},   // Snowy -  CCM, Frappe Snowland
};

struct mb64_settings_button mb64_mode_settings_buttons[] = {
    {"Mode:", &mb64_lopt_game, mb64_gamemode_string_table, ARRAY_COUNT(mb64_gamemode_string_table), NULL, NULL},
    {"Size:", &mb64_lopt_size, mb64_levelsize_string_table, ARRAY_COUNT(mb64_levelsize_string_table), NULL, NULL},
    {"Template:", &mb64_lopt_template, mb64_template_string_table, ARRAY_COUNT(mb64_template_string_table), NULL, NULL},
};

char *mb64_tips[] = {
    "Tip: Use D-Pad ^ to flip certain tiles like slopes or slabs!",
    "Tip: Use D-Pad | to change the camera's\n   zoom level while building!",
    "Tip: You can place objects or tiles inside\n   water blocks to submerge them!",
    "Tip: The thin Iron Meshes can be used to create walls\n   that require a Vanish Cap to pass through.",
    "Tip: Mesh materials can be used as both\n   hangable ceilings and Vanish Cap walls.",
    "Tip: The maximum number of stars you can place is 63,\n   or 64 if the coin star is enabled.",
    "Tip: Objects such as coin formations or fire spinners\n   can use up the object limit rather quickly.",
    "Tip: The available items inside an Item Box will change\n   depending on the chosen gamemode.",
    "Tip: Thwomps and Grindels will use the height they are\n   placed at as the peak of their movement.",
    "Tip: The Vertical Slope tile is very useful for making\n   smooth, natural terrain!",
    "Tip: Cull Markers are very useful for lowering your\n   level's complexity!",
    "Tip: If you want to rename your level, simply rename the\n   .mb64 file itself.",
    "Tip: Entering and exiting water from the side with a shell\n   will let you transition between riding and swimming!",
    "Tip: Entering a famous code while on a certain menu\n   might reward you with a little surprise...",
    "Tip: Transparent materials such as water, flames or ice\n   can look strange when layered together, so watch out.",
    "Tip: Using the Cursed Mirror gamemode will let you use a\n   bunch of new enemies and collectible badges!",
    "Tip: Remember to use the Take Screenshot button to capture\n   a thumbnail before publishing your level!",
    "Tip: You can place stars and switches inside of\n   bosses or other objects as loot.",
    "Tip: Placing Wooden Platforms on top of each other\n   will cause them to combine into one object.",
// BTCM
    "Tip: The Double Time badge extends the timer of\n   hidden corkboxes and blue coin switches!",
    "Tip: The Star Radar badge will let the player know\n   what direction the nearest star is in.",
    "Tip: Badges that the player collects will be kept\n   as permanent collectibles even after death.",
    "Tip: You can use the Burden badges as a punishment\n   when touched, or an optional challenge!",
    "Tip: Green Coins heal the player for 4 HP when collected,\n   or fully with the Heal Plus badge.",
};
#define NUM_BTCM_TIPS 5

u8 mb64_text_colors[][3] = {
    {255, 255, 255},
    {255, 255, 0},
    {150, 150, 150},
    {150, 150, 0},
    {255, 0, 0},
    {0, 150, 255},
};

enum TextColors {
    MB64_TEXT_WHITE,
    MB64_TEXT_YELLOW,
    MB64_TEXT_GRAY,
    MB64_TEXT_DARK_YELLOW,
    MB64_TEXT_RED,
    MB64_TEXT_LIGHTBLUE,
};

struct mb64_dialog_topic mb64_dialog_topics_greetings[] = {
    {"Hello",DIALOG_004},
    {"Going",DIALOG_006},
    {"Sup",DIALOG_007},
    {"Howdy",DIALOG_008},
};

struct mb64_dialog_topic mb64_dialog_topics_trouble[] = {
    {"King Bob-omb",DIALOG_000},
    {"King Whomp",DIALOG_001},
    {"Big Boo",DIALOG_016},
    {"Big Bully",DIALOG_019},
    {"Chief Chilly",DIALOG_020},
    {"Wiggler",DIALOG_021},
    {"Bowser",DIALOG_022},
};

struct mb64_dialog_topic mb64_dialog_topics_tricks[] = {
    {"Triple Jump Kick",DIALOG_002},
    {"BLJ",DIALOG_003},
    {"QSLG",DIALOG_018},
    {"Bomb Clip",DIALOG_051},
};

struct mb64_dialog_topic mb64_dialog_topics_keys[] = {
    {"Vanish Cap",DIALOG_030},
    {"Wing Cap",DIALOG_031},
    {"Metal Cap",DIALOG_032},
    {"Koopa Shell",DIALOG_033},
    {"Corkbox",DIALOG_034},
    {"Rocket Boots",DIALOG_035},
    {"Vanetal",DIALOG_036},
    {"Pipebar",DIALOG_038},
    {"B.Bill Mask",DIALOG_037},
};

struct mb64_dialog_topic mb64_dialog_topics_mystery[] = {
    {"Hmm",DIALOG_039},
    {"This",DIALOG_040},
    {"What",DIALOG_041},
    {"Peculiar",DIALOG_042},
    {"Box",DIALOG_043},
    {"Way",DIALOG_044},
};

struct mb64_dialog_topic mb64_dialog_topics_warning[] = {
    {"Pit",DIALOG_045},
    {"Lava",DIALOG_046},
    {"Quicksand",DIALOG_047},
    {"Enemies",DIALOG_048},
    {"Trolling",DIALOG_049},
    {"Void",DIALOG_050},
};

struct mb64_dialog_subject mb64_dialog_subjects[] = {
    {"Greetings",&mb64_dialog_topics_greetings, 4},
    {"Trouble",&mb64_dialog_topics_trouble, 7},
    {"Warning",&mb64_dialog_topics_warning,6},
    {"Keys",&mb64_dialog_topics_keys, 9},
    {"Mystery",&mb64_dialog_topics_mystery, 6},
    {"Tricks",&mb64_dialog_topics_tricks, 4},
};

#define NUM_DIALOG_SUBJECT_COUNT 6

u8 imbue_coin_amounts[] = {
    /* IMBUE_NONE */ 0,
    /* IMBUE_STAR */ 0,
    /* IMBUE_THREE_COINS */ 3,
    /* IMBUE_FIVE_COINS */ 5,
    /* IMBUE_EIGHT_COINS */ 8,
    /* IMBUE_BLUE_COIN */ 5,
    /* IMBUE_RED_SWITCH */ 0,
    /* IMBUE_BLUE_SWITCH */ 0,
    /* IMBUE_RED_COIN */ 2,
};