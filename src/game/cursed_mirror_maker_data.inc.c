f32 cmm_camera_zoom_table[][2] = {
    {900.0f,50.0f},
    {900.0f,400.0f},
    {1500.0f,800.0f},
    {2000.0f,900.0f},
    {2100.0f,1500.0f},
};

void* cmm_theme_segments[][4] = {
    {_group17_yay0SegmentRomStart, _group17_yay0SegmentRomEnd, _group17_geoSegmentRomStart, _group17_geoSegmentRomEnd}, //CMM_GAME_VANILLA
    {_group14_yay0SegmentRomStart, _group14_yay0SegmentRomEnd, _group14_geoSegmentRomStart, _group14_geoSegmentRomEnd}, //CMM_GAME_BTCM
};
LevelScript * cmm_theme_model_scripts[] = {
    script_func_cmm_theme_vanilla,
    script_func_cmm_theme_btcm,
};


// lookup table for rotating blocks
u8 cmm_rotated_dirs[4][6] = {
    {CMM_DIRECTION_UP, CMM_DIRECTION_DOWN, CMM_DIRECTION_POS_X, CMM_DIRECTION_NEG_X, CMM_DIRECTION_POS_Z, CMM_DIRECTION_NEG_Z},
    {CMM_DIRECTION_UP, CMM_DIRECTION_DOWN, CMM_DIRECTION_NEG_Z, CMM_DIRECTION_POS_Z, CMM_DIRECTION_POS_X, CMM_DIRECTION_NEG_X},
    {CMM_DIRECTION_UP, CMM_DIRECTION_DOWN, CMM_DIRECTION_NEG_X, CMM_DIRECTION_POS_X, CMM_DIRECTION_NEG_Z, CMM_DIRECTION_POS_Z},
    {CMM_DIRECTION_UP, CMM_DIRECTION_DOWN, CMM_DIRECTION_POS_Z, CMM_DIRECTION_NEG_Z, CMM_DIRECTION_NEG_X, CMM_DIRECTION_POS_X},
};

struct cmm_terrain_quad cmm_terrain_fullblock_quads[] = {
    {{{16, 16, 16}, {16, 16, 0}, {0, 16, 16}, {0, 16, 0}}, CMM_DIRECTION_UP,    CMM_FACESHAPE_FULL, CMM_GROWTH_FULL, NULL}, // TOP
    {{{16, 0, 16},  {0, 0, 16},  {16, 0, 0},  {0, 0, 0}},  CMM_DIRECTION_DOWN,  CMM_FACESHAPE_FULL, 0, NULL}, // BOTTOM
    {{{16, 16, 16}, {16, 0, 16}, {16, 16, 0}, {16, 0, 0}}, CMM_DIRECTION_POS_X, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // LEFT
    {{{0, 16, 16},  {0, 16, 0},  {0, 0, 16},  {0, 0, 0}},  CMM_DIRECTION_NEG_X, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
    {{{16, 16, 16}, {0, 16, 16}, {16, 0, 16}, {0, 0, 16}}, CMM_DIRECTION_POS_Z, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // FRONT
    {{{16, 16, 0},  {16, 0, 0},  {0, 16, 0},  {0, 0, 0}},  CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // BACK
};
struct cmm_terrain cmm_terrain_fullblock = {
    6,
    0,
    cmm_terrain_fullblock_quads,
    NULL
};

s8 slope_decal_uvs1[3][2] = {{0, 0}, {0, 16}, {16, 16}};
s8 slope_decal_uvs2[3][2] = {{16, 16}, {16, 0}, {0, 16}};

struct cmm_terrain_quad cmm_terrain_slope_quads[] = {
    {{{16, 0, 16}, {16, 16, 0}, {0, 0, 16}, {0, 16, 0}}, CMM_DIRECTION_UP,    CMM_FACESHAPE_EMPTY, CMM_GROWTH_FULL, NULL}, // TOP
    {{{16, 0, 16}, {0, 0, 16},  {16, 0, 0}, {0, 0, 0}},  CMM_DIRECTION_DOWN,  CMM_FACESHAPE_FULL, 0, NULL}, // BOTTOM
    {{{16, 16, 0}, {16, 0, 0},  {0, 16, 0}, {0, 0, 0}},  CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // BACK
};

struct cmm_terrain_tri cmm_terrain_slope_tris[] = {
    {{{16, 0, 0}, {16, 16, 0}, {16, 0, 16}}, CMM_DIRECTION_POS_X, CMM_FACESHAPE_TRI_1, CMM_GROWTH_SLOPE_SIDE_L, &slope_decal_uvs1}, // LEFT
    {{{0, 16, 0}, {0, 0, 0},   {0, 0, 16}},  CMM_DIRECTION_NEG_X, CMM_FACESHAPE_TRI_2, CMM_GROWTH_SLOPE_SIDE_R, &slope_decal_uvs2}, // RIGHT
};

struct cmm_terrain cmm_terrain_slope = {
    3,
    2,
    cmm_terrain_slope_quads,
    cmm_terrain_slope_tris,
};

struct cmm_terrain_quad cmm_terrain_corner_quads[] = {
    {{{16, 0, 16}, {0, 0, 16}, {16, 0, 0}, {0, 0, 0}}, CMM_DIRECTION_DOWN, CMM_FACESHAPE_FULL, 0, NULL}, // BOTTOM
};

struct cmm_terrain_tri cmm_terrain_corner_tris[] = {
    {{{0, 0, 16}, {16, 0, 16}, {0, 16, 0}},  CMM_DIRECTION_UP,    CMM_FACESHAPE_EMPTY, CMM_GROWTH_FULL, NULL}, // TOP-FRONT
    {{{0, 16, 0}, {16, 0, 16}, {16, 0, 0}},  CMM_DIRECTION_UP,    CMM_FACESHAPE_EMPTY, CMM_GROWTH_FULL, NULL}, // TOP-LEFT 
    {{{0, 16, 0}, {0, 0, 0},   {0, 0, 16}},  CMM_DIRECTION_NEG_X, CMM_FACESHAPE_TRI_2, CMM_GROWTH_SLOPE_SIDE_R, &slope_decal_uvs2}, // RIGHT
    {{{0, 0, 0},  {0, 16, 0},  {16, 0, 0}},  CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_TRI_1, CMM_GROWTH_SLOPE_SIDE_L, &slope_decal_uvs1}, // BACK
};

struct cmm_terrain cmm_terrain_corner = {
    1,
    4,
    cmm_terrain_corner_quads,
    cmm_terrain_corner_tris,
};

struct cmm_terrain_quad cmm_terrain_dcorner_quads[] = {
    {{{16, 16, 16}, {16, 16, 0}, {0, 16, 16}, {0, 16, 0}}, CMM_DIRECTION_UP, CMM_FACESHAPE_FULL, CMM_GROWTH_FULL, NULL}, // TOP
};

struct cmm_terrain_tri cmm_terrain_dcorner_tris[] = {
    {{{16, 16, 16}, {0, 16, 16}, {0, 0, 0}},    CMM_DIRECTION_POS_Z, CMM_FACESHAPE_EMPTY, CMM_GROWTH_UNDERSLOPE, NULL}, // BOTTOM-FRONT
    {{{0, 0, 0},    {16, 16, 0}, {16, 16, 16}}, CMM_DIRECTION_POS_X, CMM_FACESHAPE_EMPTY, CMM_GROWTH_UNDERSLOPE_L, NULL}, // BOTTOM-LEFT 
    {{{0, 0, 0},    {0, 16, 16}, {0, 16, 0}},   CMM_DIRECTION_NEG_X, CMM_FACESHAPE_DOWNTRI_2, CMM_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
    {{{0, 0, 0},    {0, 16, 0},  {16, 16, 0}},  CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_DOWNTRI_1, CMM_GROWTH_NORMAL_SIDE, NULL}, // BACK
};

struct cmm_terrain cmm_terrain_dcorner = {
    1,
    4,
    cmm_terrain_dcorner_quads,
    cmm_terrain_dcorner_tris,
};


struct cmm_terrain_quad cmm_terrain_icorner_quads[] = {
    {{{16, 0, 16}, {0, 0, 16}, {16, 0, 0}, {0, 0, 0}}, CMM_DIRECTION_DOWN,  CMM_FACESHAPE_FULL, 0, NULL}, // BOTTOM
    {{{16, 16, 0}, {16, 0, 0}, {0, 16, 0}, {0, 0, 0}}, CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // BACK
    {{{0, 16, 16}, {0, 16, 0}, {0, 0, 16}, {0, 0, 0}}, CMM_DIRECTION_NEG_X, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
};

struct cmm_terrain_tri cmm_terrain_icorner_tris[] = {
    {{{0, 16, 16}, {16, 0, 16}, {0, 16, 0}},  CMM_DIRECTION_UP,    CMM_FACESHAPE_EMPTY, CMM_GROWTH_FULL, NULL}, // TOP-FRONT
    {{{0, 16, 0},  {16, 0, 16}, {16, 16, 0}}, CMM_DIRECTION_UP,    CMM_FACESHAPE_EMPTY, CMM_GROWTH_FULL, NULL}, // TOP-LEFT
    {{{16, 0, 0},  {16, 16, 0}, {16, 0, 16}}, CMM_DIRECTION_POS_X, CMM_FACESHAPE_TRI_1, CMM_GROWTH_SLOPE_SIDE_L, &slope_decal_uvs1}, // LEFT
    {{{0, 16, 16}, {0, 0, 16},  {16, 0, 16}}, CMM_DIRECTION_POS_Z, CMM_FACESHAPE_TRI_2, CMM_GROWTH_SLOPE_SIDE_R, &slope_decal_uvs2}, // FRONT
};

struct cmm_terrain cmm_terrain_icorner = {
    3,
    4,
    cmm_terrain_icorner_quads,
    cmm_terrain_icorner_tris,
};

struct cmm_terrain_quad cmm_terrain_dicorner_quads[] = {
    {{{16, 16, 16}, {16, 16, 0}, {0, 16, 16}, {0, 16, 0}}, CMM_DIRECTION_UP,    CMM_FACESHAPE_FULL, CMM_GROWTH_FULL, NULL}, // TOP
    {{{16, 16, 0},  {16, 0, 0},  {0, 16, 0},  {0, 0, 0}},  CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // BACK
    {{{0, 16, 16},  {0, 16, 0},  {0, 0, 16},  {0, 0, 0}},  CMM_DIRECTION_NEG_X, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
};

struct cmm_terrain_tri cmm_terrain_dicorner_tris[] = {
    {{{16, 0, 0},   {16, 16, 0}, {16, 16, 16}}, CMM_DIRECTION_POS_X, CMM_FACESHAPE_DOWNTRI_1, CMM_GROWTH_NORMAL_SIDE, NULL}, // LEFT
    {{{0, 16, 16},  {0, 0, 16},  {16, 16, 16}}, CMM_DIRECTION_POS_Z, CMM_FACESHAPE_DOWNTRI_2, CMM_GROWTH_NORMAL_SIDE, NULL}, // FRONT
    {{{16, 16, 16}, {0, 0, 16},  {0, 0, 0}},    CMM_DIRECTION_POS_X, CMM_FACESHAPE_EMPTY, CMM_GROWTH_UNDERSLOPE_CORNER, NULL}, // BOTTOM-FRONT
    {{{16, 16, 16}, {0, 0, 0},   {16, 0, 0}},   CMM_DIRECTION_POS_Z, CMM_FACESHAPE_EMPTY, CMM_GROWTH_UNDERSLOPE_CORNER, NULL}, // BOTTOM-LEFT
};

struct cmm_terrain cmm_terrain_dicorner = {
    3,
    4,
    cmm_terrain_dicorner_quads,
    cmm_terrain_dicorner_tris,
};

struct cmm_terrain_quad cmm_terrain_dslope_quads[] = {
    {{{16, 16, 16}, {16, 16, 0}, {0, 16, 16}, {0, 16, 0}}, CMM_DIRECTION_UP,    CMM_FACESHAPE_FULL, CMM_GROWTH_FULL, NULL}, // TOP
    {{{16, 16, 0},  {16, 0, 0},  {0, 16, 0},  {0, 0, 0}},  CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // BACK
    {{{16, 16, 16}, {0, 16, 16}, {16, 0, 0},  {0, 0, 0}},  CMM_DIRECTION_POS_Z, CMM_FACESHAPE_EMPTY, CMM_GROWTH_UNDERSLOPE, NULL}, // BOTTOM
};

struct cmm_terrain_tri cmm_terrain_dslope_tris[] = {
    {{{16, 0, 0}, {16, 16, 0}, {16, 16, 16}},  CMM_DIRECTION_POS_X, CMM_FACESHAPE_DOWNTRI_1, CMM_GROWTH_NORMAL_SIDE, NULL}, // LEFT
    {{{0, 16, 0}, {0, 0, 0},   {0, 16, 16}},   CMM_DIRECTION_NEG_X, CMM_FACESHAPE_DOWNTRI_2, CMM_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
};

struct cmm_terrain cmm_terrain_dslope = {
    3,
    2,
    cmm_terrain_dslope_quads,
    cmm_terrain_dslope_tris,
};

struct cmm_terrain_quad cmm_terrain_sslope_quads[] = {
    {{{16, 16, 0}, {16, 0, 0},  {0, 16, 0}, {0, 0, 0}},  CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // BACK
    {{{0, 16, 16}, {0, 16, 0},  {0, 0, 16}, {0, 0, 0}},  CMM_DIRECTION_NEG_X, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
    {{{16, 16, 0}, {0, 16, 16}, {16, 0, 0}, {0, 0, 16}}, CMM_DIRECTION_POS_Z, CMM_FACESHAPE_EMPTY, CMM_GROWTH_DIAGONAL_SIDE, NULL}, // DIAGONAL
};

struct cmm_terrain_tri cmm_terrain_sslope_tris[] = {
    {{{0, 16, 16}, {16, 16, 0}, {0, 16, 0}}, CMM_DIRECTION_UP,   CMM_FACESHAPE_TOPTRI, CMM_GROWTH_FULL, NULL}, // TOP
    {{{16, 0, 0},  {0, 0, 16},  {0, 0, 0}},  CMM_DIRECTION_DOWN, CMM_FACESHAPE_TOPTRI, 0, NULL}, // BOTTOM
};

struct cmm_terrain cmm_terrain_sslope = {
    3,
    2,
    cmm_terrain_sslope_quads,
    cmm_terrain_sslope_tris,
};

s8 bottomslab_decal_uvs1[4][2] = {{16, 16}, {16, 8}, {0, 16}, {0, 8}};

struct cmm_terrain_quad cmm_terrain_bottomslab_quads[] = {
    {{{16, 8, 16}, {16, 8, 0},  {0, 8, 16},  {0, 8, 0}},   CMM_DIRECTION_UP,    CMM_FACESHAPE_EMPTY, CMM_GROWTH_FULL, NULL}, // TOP
    {{{16, 0, 16}, {0, 0, 16},  {16, 0, 0},  {0, 0, 0}},   CMM_DIRECTION_DOWN,  CMM_FACESHAPE_FULL, 0, NULL}, // BOTTOM
    {{{16, 8, 16}, {16, 0, 16}, {16, 8, 0},  {16, 0, 0}},  CMM_DIRECTION_POS_X, CMM_FACESHAPE_BOTTOMSLAB, CMM_GROWTH_UNCONDITIONAL, &bottomslab_decal_uvs1}, // LEFT
    {{{0, 8, 0},   {0, 0, 0},   {0, 8, 16},  {0, 0, 16}},  CMM_DIRECTION_NEG_X, CMM_FACESHAPE_BOTTOMSLAB, CMM_GROWTH_UNCONDITIONAL, &bottomslab_decal_uvs1}, // RIGHT
    {{{0, 8, 16},  {0, 0, 16},  {16, 8, 16}, {16, 0, 16}}, CMM_DIRECTION_POS_Z, CMM_FACESHAPE_BOTTOMSLAB, CMM_GROWTH_UNCONDITIONAL, &bottomslab_decal_uvs1}, // FRONT
    {{{16, 8, 0},  {16, 0, 0},  {0, 8, 0},   {0, 0, 0}},   CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_BOTTOMSLAB, CMM_GROWTH_UNCONDITIONAL, &bottomslab_decal_uvs1}, // BACK
};

struct cmm_terrain cmm_terrain_bottomslab = {
    6,
    0,
    cmm_terrain_bottomslab_quads,
    NULL
};

struct cmm_terrain_quad cmm_terrain_topslab_quads[] = {
    {{{16, 16, 16}, {16, 16, 0}, {0, 16, 16},  {0, 16, 0}},  CMM_DIRECTION_UP,    CMM_FACESHAPE_FULL, CMM_GROWTH_FULL, NULL}, // TOP
    {{{16, 8, 16},  {0, 8, 16},  {16, 8, 0},   {0, 8, 0}},   CMM_DIRECTION_DOWN,  CMM_FACESHAPE_EMPTY, 0, NULL}, // BOTTOM
    {{{16, 16, 16}, {16, 8, 16}, {16, 16, 0},  {16, 8, 0}},  CMM_DIRECTION_POS_X, CMM_FACESHAPE_TOPSLAB, CMM_GROWTH_NORMAL_SIDE, NULL}, // LEFT
    {{{0, 16, 0},   {0, 8, 0},   {0, 16, 16},  {0, 8, 16}},  CMM_DIRECTION_NEG_X, CMM_FACESHAPE_TOPSLAB, CMM_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
    {{{0, 16, 16},  {0, 8, 16},  {16, 16, 16}, {16, 8, 16}}, CMM_DIRECTION_POS_Z, CMM_FACESHAPE_TOPSLAB, CMM_GROWTH_NORMAL_SIDE, NULL}, // FRONT
    {{{16, 16, 0},  {16, 8, 0},  {0, 16, 0},   {0, 8, 0}},   CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_TOPSLAB, CMM_GROWTH_NORMAL_SIDE, NULL}, // BACK
};

struct cmm_terrain cmm_terrain_topslab = {
    6,
    0,
    cmm_terrain_topslab_quads,
    NULL
};

struct cmm_terrain_quad cmm_terrain_vslab_quads[] = {
    {{{16, 16, 8}, {16, 16, 0}, {0, 16, 8},  {0, 16, 0}}, CMM_DIRECTION_UP,    CMM_FACESHAPE_TOPHALF,    CMM_GROWTH_FULL, NULL}, // TOP
    {{{16, 0, 8},  {0, 0, 8},   {16, 0, 0},  {0, 0, 0}},  CMM_DIRECTION_DOWN,  CMM_FACESHAPE_TOPHALF,    0, NULL}, // BOTTOM
    {{{16, 16, 8}, {16, 0, 8},  {16, 16, 0}, {16, 0, 0}}, CMM_DIRECTION_POS_X, CMM_FACESHAPE_HALFSIDE_1, CMM_GROWTH_HALF_SIDE,   NULL}, // LEFT
    {{{0, 16, 8},  {0, 16, 0},  {0, 0, 8},   {0, 0, 0}},  CMM_DIRECTION_NEG_X, CMM_FACESHAPE_HALFSIDE_2, CMM_GROWTH_HALF_SIDE,   NULL}, // RIGHT
    {{{16, 16, 8}, {0, 16, 8},  {16, 0, 8},  {0, 0, 8}},  CMM_DIRECTION_POS_Z, CMM_FACESHAPE_EMPTY,      CMM_GROWTH_VSLAB_SIDE, NULL}, // FRONT
    {{{16, 16, 0}, {16, 0, 0},  {0, 16, 0},  {0, 0, 0}},  CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_FULL,       CMM_GROWTH_NORMAL_SIDE,   NULL}, // BACK
};
struct cmm_terrain cmm_terrain_vslab = {
    6,
    0,
    cmm_terrain_vslab_quads,
    NULL
};

s8 slope_decal_below_uvsquad_l[4][2] =  {{0, 0},   {16, 16},  {0, -16}, {16, 0}  };
s8 slope_decal_below_uvsquad_r[4][2] =  {{0, 16},  {16, 0},   {0, 0},   {16, -16}};
s8 slope_decal_below_uvstri_1_l[3][2] = {{0, 0},   {16, 16},  {0, -16}           };
s8 slope_decal_below_uvstri_1_r[3][2] = {{0, 16},  {16, 0},   {0, 0}             };
s8 slope_decal_below_uvstri_2_l[3][2] = {{16, 16}, {16, 0},   {0, 0}             };
s8 slope_decal_below_uvstri_2_r[3][2] = {{16, 0},  {16, -16}, {0, 16}            };
s8 slope_decal_below_uvsslab_l[4][2] =  {{0, 0},   {16, 16},  {0, -8},  {16, 8}  };
s8 slope_decal_below_uvsslab_r[4][2] =  {{0, 16},  {16, 0},   {0, 8},   {16, -8} };

// All of this is for the system where slopes can place a decal on the face below them.
// Very hardcoded, so best not to touch any of these numbers
void *slope_decal_below_uvs[][2] = {
    { // Full block
        &slope_decal_below_uvsquad_l,
        &slope_decal_below_uvsquad_r,
    },
    { // Downtri 1
        &slope_decal_below_uvstri_1_l,
        &slope_decal_below_uvstri_1_r,
    },
    { // Downtri 2
        &slope_decal_below_uvstri_2_l,
        &slope_decal_below_uvstri_2_r,
    },
    { // Top slab
        &slope_decal_below_uvsslab_l,
        &slope_decal_below_uvsslab_r,
    }
};

struct cmm_terrain_quad cmm_terrain_slopebelowdecal_quad = {
    {{16, 16, 16}, {0, 16, 16}, {16, 0, 16}, {0, 0, 16}}, CMM_DIRECTION_POS_Z, CMM_FACESHAPE_FULL, 0, NULL
};
struct cmm_terrain_tri cmm_terrain_slopebelowdecal_downtri1 = {
    {{16, 16, 16}, {0, 16, 16}, {16, 0, 16}}, CMM_DIRECTION_POS_Z, CMM_FACESHAPE_DOWNTRI_1, 0, NULL
};
struct cmm_terrain_tri cmm_terrain_slopebelowdecal_downtri2 = {
    {{0, 16, 16}, {0, 0, 16}, {16, 16, 16}}, CMM_DIRECTION_POS_Z, CMM_FACESHAPE_DOWNTRI_2, 0, NULL
};
struct cmm_terrain_quad cmm_terrain_slopebelowdecal_topslab = {
    {{16, 16, 16}, {0, 16, 16}, {16, 8, 16}, {0, 8, 16}}, CMM_DIRECTION_POS_Z, CMM_FACESHAPE_TOPSLAB, 0, NULL
};

void *slope_decal_below_surfs[] = {
    &cmm_terrain_slopebelowdecal_quad,
    &cmm_terrain_slopebelowdecal_downtri1,
    &cmm_terrain_slopebelowdecal_downtri2,
    &cmm_terrain_slopebelowdecal_topslab,
};

// Shape of fence

s8 fence_uvs[4][2] = {{32, 16},  {32, 0},  {0, 16},  {0, 0}};
struct cmm_terrain_quad cmm_terrain_fence_quad[] = {
    {{{0, 8, 0}, {0, 0, 0}, {16, 8, 0}, {16, 0, 0}}, CMM_DIRECTION_POS_Z, CMM_FACESHAPE_EMPTY, 0, &fence_uvs}, // FRONT (towards tile)
    {{{16, 8, 0}, {16, 0, 0}, {0, 8, 0}, {0, 0, 0}}, CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_BOTTOMSLAB, 0, &fence_uvs}, // BACK (away from tile)
};

struct cmm_terrain_quad cmm_terrain_fence_col_quads[] = {
    {{{16, 7, 1},  {0, 7, 1},   {16, 0, 1}, {0, 0, 1}}, CMM_DIRECTION_POS_Z, CMM_FACESHAPE_EMPTY, 0, NULL}, // FRONT (towards tile)
    {{{16, 7, -1}, {16, 0, -1}, {0, 7, -1}, {0, 0, -1}}, CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_BOTTOMSLAB, 0, NULL}, // BACK (away from tile)

    {{{16, 8, 0},  {0, 8, 0},   {16, 7, 1}, {0, 7, 1}}, CMM_DIRECTION_POS_Z, CMM_FACESHAPE_EMPTY, 0, NULL}, // FRONT (towards tile)
    {{{16, 8, 0},  {16, 7, -1}, {0, 8, 0},  {0, 7, -1}}, CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_BOTTOMSLAB, 0, NULL}, // BACK (away from tile)
};

struct cmm_terrain cmm_terrain_fence = {
    2,
    0,
    cmm_terrain_fence_quad,
    NULL,
};

struct cmm_terrain cmm_terrain_fence_col = {
    4,
    0,
    cmm_terrain_fence_col_quads,
    NULL,
};


s8 pole_uvs1[4][2] = {{16, 0}, {16, 32}, {12, 0}, {12, 32}};
s8 pole_uvs2[4][2] = {{12, 0}, {12, 32}, {8, 0}, {8, 32}};
s8 pole_uvs3[4][2] = {{8, 0}, {8, 32}, {4, 0}, {4, 32}};
s8 pole_uvs4[4][2] = {{4, 0}, {4, 32}, {0, 0}, {0, 32}};
struct cmm_terrain_quad cmm_terrain_pole_quads[] = {
    {{{8, 16, 9}, {8, 0, 9}, {9, 16, 8}, {9, 0, 8}}, CMM_DIRECTION_POS_Z, CMM_FACESHAPE_EMPTY, 0, &pole_uvs1}, // Diagonal 1
    {{{9, 16, 8}, {9, 0, 8}, {8, 16, 7}, {8, 0, 7}}, CMM_DIRECTION_POS_X, CMM_FACESHAPE_EMPTY, 0, &pole_uvs2}, // Diagonal 2
    {{{8, 16, 7}, {8, 0, 7}, {7, 16, 8}, {7, 0, 8}}, CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_EMPTY, 0, &pole_uvs3}, // Diagonal 3
    {{{7, 16, 8}, {7, 0, 8}, {8, 16, 9}, {8, 0, 9}}, CMM_DIRECTION_NEG_X, CMM_FACESHAPE_EMPTY, 0, &pole_uvs4}, // Diagonal 4

    {{{8, 16, 9}, {9, 16, 8}, {7, 16, 8}, {8, 16, 7}}, CMM_DIRECTION_UP,   CMM_FACESHAPE_POLETOP, 0, NULL}, // Top
    {{{8, 0, 9},  {7, 0, 8},  {9, 0, 8},  {8, 0, 7}},  CMM_DIRECTION_DOWN, CMM_FACESHAPE_POLETOP, 0, NULL}, // Bottom
};

struct cmm_terrain cmm_terrain_pole = {
    6,
    0,
    cmm_terrain_pole_quads,
    NULL,
};

struct cmm_terrain_quad cmm_terrain_bars_connected_quads[] = {
    {{{7, 16, 16}, {7, 16, 9}, {7, 0, 16}, {7, 0, 9}}, CMM_DIRECTION_NEG_X, CMM_FACESHAPE_EMPTY, 0, NULL}, // Left
    {{{9, 16, 9}, {9, 16, 16}, {9, 0, 9}, {9, 0, 16}}, CMM_DIRECTION_POS_X, CMM_FACESHAPE_EMPTY, 0, NULL}, // Right

    {{{7, 16, 16}, {9, 16, 16}, {7, 16, 9}, {9, 16, 9}}, CMM_DIRECTION_UP, CMM_FACESHAPE_EMPTY, 0, NULL}, // Top
    {{{9, 0, 16}, {7, 0, 16}, {9, 0, 9}, {7, 0, 9}}, CMM_DIRECTION_DOWN, CMM_FACESHAPE_EMPTY, 0, NULL}, // Bottom
};

struct cmm_terrain_quad cmm_terrain_bars_unconnected_quad[] = {
    {{{9, 16, 9}, {7, 16, 9}, {9, 0, 9}, {7, 0, 9}}, CMM_DIRECTION_POS_Z, CMM_FACESHAPE_EMPTY, 0, NULL}, // Back
};

struct cmm_terrain_quad cmm_terrain_bars_center_quads[] = {
    {{{7, 16, 9}, {9, 16, 9}, {7, 16, 7}, {9, 16, 7}}, CMM_DIRECTION_UP, CMM_FACESHAPE_EMPTY, 0, NULL},
    {{{9, 0, 9}, {7, 0, 9}, {9, 0, 7}, {7, 0, 7}}, CMM_DIRECTION_DOWN, CMM_FACESHAPE_EMPTY, 0, NULL},
};

// Shapes of water tiles
struct cmm_terrain_quad cmm_terrain_shallowwater_quads[] = {
    {{{16, 14, 16}, {16, 14, 0}, {0, 14, 16}, {0, 14, 0}}, CMM_DIRECTION_UP, CMM_FACESHAPE_EMPTY, 0, NULL}, // TOP
    {{{16, 0, 16},  {0, 0, 16},  {16, 0, 0},  {0, 0, 0}},  CMM_DIRECTION_DOWN, CMM_FACESHAPE_FULL, 0, NULL}, // BOTTOM
    {{{16, 14, 16}, {16, 0, 16}, {16, 14, 0}, {16, 0, 0}}, CMM_DIRECTION_POS_X, CMM_FACESHAPE_FULL, 0, NULL}, // LEFT
    {{{0, 14, 16},  {0, 14, 0},  {0, 0, 16},  {0, 0, 0}},  CMM_DIRECTION_NEG_X, CMM_FACESHAPE_FULL, 0, NULL}, // RIGHT
    {{{16, 14, 16}, {0, 14, 16}, {16, 0, 16}, {0, 0, 16}}, CMM_DIRECTION_POS_Z, CMM_FACESHAPE_FULL, 0, NULL}, // FRONT
    {{{16, 14, 0},  {16, 0, 0},  {0, 14, 0},  {0, 0, 0}},  CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_FULL, 0, NULL}, // BACK
};

struct cmm_terrain_quad cmm_terrain_topwater_quads[] = {
    {{{16, 16, 16}, {16, 16, 0}, {0, 16, 16}, {0, 16, 0}}, CMM_DIRECTION_UP, CMM_FACESHAPE_FULL, 0, NULL}, // TOP
    {{{16, 0, 16},  {0, 0, 16},  {16, 0, 0},  {0, 0, 0}},  CMM_DIRECTION_DOWN, CMM_FACESHAPE_FULL, 0, NULL}, // BOTTOM
    {{{16, 16, 16}, {16, 14, 16}, {16, 16, 0}, {16, 14, 0}}, CMM_DIRECTION_POS_X, CMM_FACESHAPE_FULL, 0, NULL}, // LEFT
    {{{0, 16, 16},  {0, 16, 0},  {0, 14, 16},  {0, 14, 0}},  CMM_DIRECTION_NEG_X, CMM_FACESHAPE_FULL, 0, NULL}, // RIGHT
    {{{16, 16, 16}, {0, 16, 16}, {16, 14, 16}, {0, 14, 16}}, CMM_DIRECTION_POS_Z, CMM_FACESHAPE_FULL, 0, NULL}, // FRONT
    {{{16, 16, 0},  {16, 14, 0},  {0, 16, 0},  {0, 14, 0}}, CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_FULL, 0, NULL}, // BACK
};

struct cmm_terrain_quad *cmm_terrain_water_quadlists[] = {
    cmm_terrain_shallowwater_quads,
    cmm_terrain_fullblock_quads,
    cmm_terrain_topwater_quads,
};

struct cmm_terrain *cmm_tile_terrains[] = {
    &cmm_terrain_fullblock,  // TILE_TYPE_BLOCK
    &cmm_terrain_slope,      // TILE_TYPE_SLOPE
    &cmm_terrain_corner,     // TILE_TYPE_CORNER
    &cmm_terrain_icorner,    // TILE_TYPE_ICORNER
    &cmm_terrain_dcorner,    // TILE_TYPE_DCORNER
    &cmm_terrain_dicorner,   // TILE_TYPE_DICORNER
    &cmm_terrain_dslope,     // TILE_TYPE_DSLOPE
    &cmm_terrain_sslope,     // TILE_TYPE_SSLOPE
    &cmm_terrain_bottomslab, // TILE_TYPE_SLAB
    &cmm_terrain_topslab,    // TILE_TYPE_DSLAB
    &cmm_terrain_vslab,      // TILE_TYPE_SSLAB
    NULL,                    //TILE_TYPE_CULL
    &cmm_terrain_fullblock,  //TILE_TYPE_TROLL
    NULL,                    //TILE_TYPE_FENCE
    NULL,                    //TILE_TYPE_BARS
    NULL,                    //TILE_TYPE_POLE
    NULL,                    // TILE_TYPE_WATER
};

enum cmm_materials {
    CMM_MAT_NONE,
    // Generic
    CMM_MAT_DIRT,
    CMM_MAT_SANDDIRT,

    CMM_MAT_GRASS,
    CMM_MAT_HMC_GRASS,

    CMM_MAT_SAND,
    CMM_MAT_JRB_SAND,
    CMM_MAT_SNOW,

    CMM_MAT_BRICKS,
    CMM_MAT_TILESBRICKS,
    CMM_MAT_DESERT_BRICKS,
    CMM_MAT_RHR_BRICK,
    CMM_MAT_HMC_BRICK,
    CMM_MAT_C_BRICK,
    CMM_MAT_C_OUTSIDEBRICK,
    CMM_MAT_BBH_BRICKS,
    CMM_MAT_JRB_BRICKS,

    CMM_MAT_STONE,
    CMM_MAT_COBBLESTONE,
    CMM_MAT_TILES,
    CMM_MAT_ROOF,
    CMM_MAT_WOOD,
    CMM_MAT_SNOWDIRT,
    CMM_MAT_LAVA,
    CMM_MAT_QUICKSAND,
    // Desert
    CMM_MAT_DESERT_STONE,
    CMM_MAT_DESERT_TILES,
    CMM_MAT_DESERT_BLOCK,
    CMM_MAT_DESERT_TILES2,
    CMM_MAT_DESERT_SLOWSAND,
    // Red Hot Reservoir
    CMM_MAT_RHR_OBSIDIAN,
    CMM_MAT_RHR_STONE,
    CMM_MAT_RHR_BASALT,
    CMM_MAT_RHR_TILES,
    CMM_MAT_RHR_BLOCK,
    CMM_MAT_RHR_WOOD,
    CMM_MAT_RHR_PILLAR,
    CMM_MAT_RHR_MESH,
    CMM_MAT_SERVER_ACID,
    // Hazy Maze Cave
    CMM_MAT_HMC_DIRT,
    CMM_MAT_HMC_STONE,
    CMM_MAT_HMC_MAZEWALL,
    CMM_MAT_HMC_MAZEFLOOR,
    CMM_MAT_HMC_LIGHT,
    CMM_MAT_HMC_LAKEGRASS,
    CMM_MAT_HMC_MESH,
    // Castle
    CMM_MAT_C_WOOD,
    CMM_MAT_C_TILES,
    CMM_MAT_C_STONETOP,
    CMM_MAT_C_STONESIDE,
    CMM_MAT_C_CARPET,
    CMM_MAT_C_ROOF,
    CMM_MAT_C_WALL,
    CMM_MAT_C_PILLAR,
    CMM_MAT_C_BASEMENTWALL,
    // Virtuaplex
    CMM_MAT_VP_BLOCK,
    CMM_MAT_VP_TILES,
    CMM_MAT_VP_BLUETILES,
    CMM_MAT_VP_RUSTYBLOCK,
    CMM_MAT_VP_SCREEN,
    CMM_MAT_VP_CAUTION,
    CMM_MAT_VP_VOID,
    // Snow
    // BBH
    CMM_MAT_BBH_METAL,
    CMM_MAT_BBH_HAUNTED_PLANKS,
    CMM_MAT_BBH_WOOD_FLOOR,
    CMM_MAT_BBH_WOOD_WALL,
    CMM_MAT_BBH_ROOF,
    CMM_MAT_BBH_STONE,
    CMM_MAT_BBH_STONE_PATTERN,
    CMM_MAT_BBH_PILLAR,
    CMM_MAT_BBH_WINDOW,
    // JRB
    CMM_MAT_JRB_STONE,
    CMM_MAT_JRB_METAL,
    CMM_MAT_JRB_UNDERWATER,
    CMM_MAT_JRB_SHIPSIDE,
    CMM_MAT_JRB_SHIPTOP,
    CMM_MAT_JRB_WOOD,
    CMM_MAT_JRB_METALSIDE,
    CMM_MAT_JRB_WALL,
    CMM_MAT_JRB_TILETOP,
    CMM_MAT_JRB_TILESIDE,

    CMM_MAT_SNOW_ROCK,
    CMM_MAT_ICE,
    CMM_MAT_SNOW_ROOF,
    CMM_MAT_SNOW_BRICKS,
    CMM_MAT_BURNING_ICE,
    CMM_MAT_CRYSTAL,
    CMM_MAT_SNOW_BRICK_TILES,
    CMM_MAT_SNOW_TILES,
    CMM_MAT_SNOW_TILE_SIDE,
    // Retro
    CMM_MAT_RETRO_GROUND,
    CMM_MAT_RETRO_BRICKS,
    CMM_MAT_RETRO_TREETOP,
    CMM_MAT_RETRO_TREEPLAT,
    CMM_MAT_RETRO_BLOCK,
    CMM_MAT_RETRO_BLUEGROUND,
    CMM_MAT_RETRO_BLUEBRICKS,
    CMM_MAT_RETRO_BLUEBLOCK,
    CMM_MAT_RETRO_WHITEBRICK,
    CMM_MAT_RETRO_LAVA,
    CMM_MAT_RETRO_UNDERWATERGROUND,

    // Minecraft
    CMM_MAT_MC_DIRT,
    CMM_MAT_MC_GRASS,
    CMM_MAT_MC_COBBLESTONE,
    CMM_MAT_MC_STONE,
    CMM_MAT_MC_OAK_LOG_TOP,
    CMM_MAT_MC_OAK_LOG_SIDE,
    CMM_MAT_MC_OAK_LEAVES,
    CMM_MAT_MC_WOOD_PLANKS,
    CMM_MAT_MC_SAND,
    CMM_MAT_MC_BRICKS,
    CMM_MAT_MC_LAVA,
    CMM_MAT_MC_FLOWING_LAVA,
    CMM_MAT_MC_GLASS,
};

struct cmm_material cmm_mat_table[] = {
    {0,0,0}, // CMM_MAT_NONE
    // Dirt
    {mat_maker_MakerDirt,     0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_DIRT
    {mat_maker_MakerSandDirt, 0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_SANDDIRT
    // Grass
    {mat_maker_MakerGrass,    0, SURFACE_GRASS},        // CMM_MAT_GRASS
    {mat_maker_MakerHGrass,   0, SURFACE_GRASS},        // CMM_MAT_HMC_GRASS
    // Other Terrain
    {mat_maker_MakerSand,     0, SURFACE_SAND},         // CMM_MAT_SAND
    {mat_maker_MakerJRBSand,  0, SURFACE_SAND},         // CMM_MAT_JRB_SAND
    {mat_maker_MakerSnow,     0, SURFACE_SNOW},         // CMM_MAT_SNOW
    // Bricks
    {mat_maker_MakerBricks,         0, SURFACE_DEFAULT},      // CMM_MAT_BRICKS
    {mat_maker_MakerTileBricks,     0, SURFACE_DEFAULT},      // CMM_MAT_TILESBRICKS
    {mat_maker_MakerDBrick,         0, SURFACE_DEFAULT},      // CMM_MAT_DESERT_BRICKS
    {mat_maker_MakerRHRBrick,       0, SURFACE_DEFAULT},      // CMM_MAT_RHR_BRICK
    {mat_maker_MakerHBrick,         0, SURFACE_DEFAULT},      // CMM_MAT_HMC_BRICK
    {mat_maker_MakerCBrick,         0, SURFACE_DEFAULT},      // CMM_MAT_C_BRICK
    {mat_maker_MakerCOutsideBricks, 0, SURFACE_DEFAULT},      // CMM_MAT_C_OUTSIDE_BRICK
    {mat_maker_MakerBBHBricks,      0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_BBH_BRICKS
    {mat_maker_MakerJRBBricks,      0, SURFACE_DEFAULT},      // CMM_MAT_JRB_BRICKS 

    {mat_maker_MakerStoneSide,  0, SURFACE_NOT_SLIPPERY},      // CMM_MAT_STONE
    {mat_maker_MakerStone,      0, SURFACE_NOT_SLIPPERY},      // CMM_MAT_COBBLESTONE
    {mat_maker_MakerTiles,      0, SURFACE_NOT_SLIPPERY},      // CMM_MAT_TILES
    {mat_maker_MakerRoof,       0, SURFACE_NOT_SLIPPERY},      // CMM_MAT_ROOF
    {mat_maker_MakerWood,       0, SURFACE_CREAKWOOD},         // CMM_MAT_WOOD
    {mat_maker_MakerSnowDirt,   0, SURFACE_NOT_SLIPPERY},      // CMM_MAT_SNOWDIRT
    {mat_maker_MakerLava,       0, SURFACE_BURNING},           // CMM_MAT_LAVA
    {mat_maker_MakerQuicksand,  0, SURFACE_INSTANT_QUICKSAND}, // CMM_MAT_QUICKSAND
    // Desert
    {mat_maker_MakerDStone,      0, SURFACE_NOT_SLIPPERY},   // CMM_MAT_DESERT_STONE
    {mat_maker_MakerDTiles,      0, SURFACE_NOT_SLIPPERY},   // CMM_MAT_DESERT_TILES
    {mat_maker_MakerDStoneBlock, 0, SURFACE_NOT_SLIPPERY},   // CMM_MAT_DESERT_BLOCK
    {mat_maker_MakerDTiles2,     0, SURFACE_NOT_SLIPPERY},   // CMM_MAT_DESERT_TILES2
    {mat_maker_MakerSlowsand,    0, SURFACE_DEEP_QUICKSAND}, // CMM_MAT_DESERT_SLOWSAND
    // Red Hot Reservoir
    {mat_maker_MakerRHRObsidian,     0,          SURFACE_NOT_SLIPPERY},     // CMM_MAT_RHR_OBSIDIAN
    {mat_maker_MakerRHRStone,        0,          SURFACE_NOT_SLIPPERY},     // CMM_MAT_RHR_STONE
    {mat_maker_MakerRHRBasalt,       0,          SURFACE_NOT_SLIPPERY},     // CMM_MAT_RHR_BASALT
    {mat_maker_MakerRHRTiles,        0,          SURFACE_NOT_SLIPPERY},     // CMM_MAT_RHR_TILES
    {mat_maker_MakerRHRPattern,      0,          SURFACE_DEFAULT},          // CMM_MAT_RHR_BLOCK
    {mat_maker_MakerRHRWood,         0,          SURFACE_CREAKWOOD},        // CMM_MAT_RHR_WOOD
    {mat_maker_MakerRHRPillar,       0,          SURFACE_DEFAULT},          // CMM_MAT_RHR_PILLAR
    {mat_maker_MakerRHRMesh_layer1,  MAT_CUTOUT, SURFACE_HANGABLE_MESH}, // CMM_MAT_RHR_MESH
    {mat_maker_MakerServerAcid,      0,          SURFACE_BURNING},          // CMM_MAT_SERVER_ACID
    // Hazy Maze Cave
    {mat_maker_MakerHDirt,           0,          SURFACE_NOT_SLIPPERY},     // CMM_MAT_HMC_DIRT
    {mat_maker_MakerHStone,          0,          SURFACE_NOT_SLIPPERY},     // CMM_MAT_HMC_STONE
    {mat_maker_MakerHMazewall,       0,          SURFACE_DEFAULT},          // CMM_MAT_HMC_MAZEWALL
    {mat_maker_MakerHMazefloor,      0,          SURFACE_NOT_SLIPPERY},     // CMM_MAT_HMC_MAZEFLOOR
    {mat_maker_MakerHLight,          0,          SURFACE_DEFAULT},          // CMM_MAT_HMC_LIGHT
    {mat_maker_MakerHLakewall,       0,          SURFACE_NOT_SLIPPERY},     // CMM_MAT_HMC_LAKEGRASS
    {mat_maker_MakerHMesh_layer1,    MAT_CUTOUT, SURFACE_HANGABLE_MESH}, // CMM_MAT_HMC_MESH
    // Castle
    {mat_maker_MakerCWood,           0, SURFACE_DEFAULT},      // CMM_MAT_C_WOOD
    {mat_maker_MakerCTiles,          0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_C_TILES
    {mat_maker_MakerCStone,          0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_C_STONETOP
    {mat_maker_MakerCStoneSide,      0, SURFACE_DEFAULT},      // CMM_MAT_C_STONESIDE
    {mat_maker_MakerCCarpet,         0, SURFACE_GRASS},        // CMM_MAT_C_CARPET
    {mat_maker_MakerCRoof,           0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_C_ROOF
    {mat_maker_MakerCWall,           0, SURFACE_DEFAULT},      // CMM_MAT_C_WALL
    {mat_maker_MakerCPillar,         0, SURFACE_DEFAULT},      // CMM_MAT_C_PILLAR
    {mat_maker_MakerCBasementWall,   0, SURFACE_DEFAULT},      // CMM_MAT_C_BASEMENTWALL
    // Virtuaplex
    {mat_maker_MakerVBlock,          0,            SURFACE_NOT_SLIPPERY},      // CMM_MAT_VP_BLOCK
    {mat_maker_MakerVTiles,          0,            SURFACE_NOT_SLIPPERY},      // CMM_MAT_VP_TILES
    {mat_maker_MakerVBlueTiles,      0,            SURFACE_NOT_SLIPPERY},      // CMM_MAT_VP_BLUETILES
    {mat_maker_MakerVRustyBlock,     0,            SURFACE_NOT_SLIPPERY},      // CMM_MAT_VP_RUSTYBLOCK
    {mat_maker_MakerScreen_layer1,   MAT_VPSCREEN, SURFACE_DEFAULT},           // CMM_MAT_VP_SCREEN
    {mat_maker_MakerCaution,         0,            SURFACE_DEFAULT},           // CMM_MAT_VP_CAUTION
    {mat_maker_MakerVoid,            0,            SURFACE_INSTANT_QUICKSAND}, // CMM_MAT_VP_VOID
    // Snow
    // BBH
    {mat_maker_MakerBBHMetal,        0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_BBH_METAL
    {mat_maker_MakerBBHHauntedPlanks,0, SURFACE_CREAKWOOD},    // CMM_MAT_BBH_HAUNTED_PLANKS
    {mat_maker_MakerBBHWoodFloor,    0, SURFACE_CREAKWOOD},    // CMM_MAT_BBH_WOOD_FLOOR
    {mat_maker_MakerBBHWoodWall,     0, SURFACE_CREAKWOOD},    // CMM_MAT_BBH_WOOD_WALL
    {mat_maker_MakerBBHRoof,         0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_BBH_ROOF
    {mat_maker_MakerBBHWall,         0, SURFACE_DEFAULT},      // CMM_MAT_BBH_STONE
    {mat_maker_MakerBBHStonePattern, 0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_BBH_STONE_PATTERN
    {mat_maker_MakerBBHPillar,       0, SURFACE_DEFAULT},      // CMM_MAT_BBH_PILLAR
    {mat_maker_MakerBBHWindow,       0, SURFACE_DEFAULT},      // CMM_MAT_BBH_WINDOW
    // JRB
    {mat_maker_MakerJRBStone,        0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_JRB_STONE
    {mat_maker_MakerJRBMetal,        0, SURFACE_DEFAULT},      // CMM_MAT_JRB_METAL
    {mat_maker_MakerJRBUnderwater,   0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_JRB_UNDERWATER
    {mat_maker_MakerJRBShipSide,     0, SURFACE_CREAKWOOD},    // CMM_MAT_JRB_SHIPSIDE
    {mat_maker_MakerJRBShipTop,      0, SURFACE_CREAKWOOD},    // CMM_MAT_JRB_SHIPTOP
    {mat_maker_MakerJRBWood,         0, SURFACE_CREAKWOOD},    // CMM_MAT_JRB_WOOD
    {mat_maker_MakerJRBMetalSide,    0, SURFACE_DEFAULT},      // CMM_MAT_JRB_METALSIDE
    {mat_maker_MakerJRBWall,         0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_JRB_WALL
    {mat_maker_MakerJRBTileTop,      0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_JRB_TILETOP
    {mat_maker_MakerJRBTileSide,     0, SURFACE_DEFAULT},      // CMM_MAT_JRB_TILESIDE

    {mat_maker_MakerSnowRock,        0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_SNOW_ROCK
    {mat_maker_MakerIce_layer1,      MAT_TRANSPARENT, SURFACE_ICE}, // CMM_MAT_ICE
    {mat_maker_MakerSnowRoof,        0, SURFACE_VERY_SLIPPERY}, // CMM_MAT_SNOW_ROOF
    {mat_maker_MakerSnowBricks,      0, SURFACE_DEFAULT}, // CMM_MAT_SNOW_BRICKS
    {mat_maker_MakerBurningIce,      0, SURFACE_BURNING_ICE}, // CMM_MAT_BURNING_ICE
    {mat_maker_MakerCrystal_layer1,  MAT_TRANSPARENT, SURFACE_CRYSTAL}, // CMM_MAT_CRYSTAL
    {mat_maker_MakerSnowBrickTiles,  0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_SNOW_BRICK_TILES
    {mat_maker_MakerSnowTiles,       0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_SNOW_TILES
    {mat_maker_MakerSnowTileSide,    0, SURFACE_DEFAULT}, // CMM_MAT_SNOW_TILE_SIDE
    // Retro
    {mat_maker_MakerRetroGround,     0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_RETRO_GROUND
    {mat_maker_MakerRetroBrick,      0, SURFACE_DEFAULT},      // CMM_MAT_RETRO_BRICKS
    {mat_maker_MakerRetroTreeTop,    0, SURFACE_GRASS},        // CMM_MAT_RETRO_TREETOP
    {mat_maker_MakerRetroTree,       0, SURFACE_DEFAULT},      // CMM_MAT_RETRO_TREEPLAT
    {mat_maker_MakerRetroBlock,      0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_RETRO_BLOCK
    {mat_maker_MakerRetroBGround,    0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_RETRO_BLUEGROUND
    {mat_maker_MakerRetroBBrick,     0, SURFACE_DEFAULT},      // CMM_MAT_RETRO_BLUEBRICKS
    {mat_maker_MakerRetroBBlock,     0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_RETRO_BLUEBLOCK
    {mat_maker_MakerRetroWBrick,     0, SURFACE_DEFAULT},      // CMM_MAT_RETRO_WHITEBRICK
    {mat_maker_MakerRetroLava,       0, SURFACE_BURNING},      // CMM_MAT_RETRO_LAVA
    {mat_maker_MakerRetroUnderwater, 0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_RETRO_UNDERWATERGROUND

    // Minecraft
    {mat_maker_MakerMCDirt,        0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_MC_DIRT
    {mat_maker_MakerMCGrassTop,    0, SURFACE_GRASS},        // CMM_MAT_MC_GRASS
    {mat_maker_MakerMCCobblestone, 0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_MC_COBBLESTONE
    {mat_maker_MakerMCStone,       0, SURFACE_DEFAULT},      // CMM_MAT_MC_STONE
    {mat_maker_MakerMCOakLogTop,   0, SURFACE_CREAKWOOD},    // CMM_MAT_MC_OAK_LOG_TOP
    {mat_maker_MakerMCOakLogSide,  0, SURFACE_CREAKWOOD},    // CMM_MAT_MC_OAK_LOG_SIDE
    {mat_maker_MakerMCOakLeaves_layer1,  MAT_CUTOUT, SURFACE_GRASS}, // CMM_MAT_MC_OAK_LEAVES
    {mat_maker_MakerMCWoodPlanks,  0, SURFACE_CREAKWOOD},    // CMM_MAT_MC_WOOD_PLANKS
    {mat_maker_MakerMCSand,        0, SURFACE_SAND},         // CMM_MAT_MC_SAND
    {mat_maker_MakerMCBricks,      0, SURFACE_DEFAULT},      // CMM_MAT_MC_BRICKS
    {mat_maker_MakerMCLava,        0, SURFACE_BURNING},      // CMM_MAT_MC_LAVA
    {mat_maker_MakerMCFlowingLava, 0, SURFACE_BURNING},      // CMM_MAT_MC_FLOWING_LAVA
    {mat_maker_MakerMCGlass_layer1,  MAT_CUTOUT_NOCULL, SURFACE_VANISH_CAP_WALLS}, // CMM_MAT_MC_GLASS
};

struct cmm_topmaterial cmm_topmat_table[] = {
    {CMM_MAT_GRASS,         mat_maker_MakerGrassSide_layer1},
    {CMM_MAT_SAND,          mat_maker_MakerSandSide_layer1},
    {CMM_MAT_SNOW,          mat_maker_MakerSnowSide_layer1},
    {CMM_MAT_C_STONETOP,    mat_maker_MakerCastleHexRim_layer1},
    {CMM_MAT_HMC_GRASS,     mat_maker_MakerHGrassSide_layer1},
    {CMM_MAT_BBH_METAL,     mat_maker_MakerBBHMetalSide_layer1},
    {CMM_MAT_BBH_STONE,     mat_maker_MakerBBHMetalSide_layer1},
    {CMM_MAT_JRB_TILETOP,   mat_maker_MakerJRBTileRim_layer1},
    {CMM_MAT_SNOW_TILES,    mat_maker_MakerSnowTileRim_layer1},
    {CMM_MAT_RETRO_TREETOP, mat_maker_MakerRetroTreeSide_layer1},
    {CMM_MAT_MC_GRASS,      mat_maker_MakerMCGrassEdge_layer1},
};

s8 cmm_terrain_floors_generic[] =    {0, 8, 9, 2, 3, 5, 6, 7}; // grass, lava, quicksand, stone, tiles, wood, sand, snow
s8 cmm_terrain_floors_desert[] =     {0, 8, 9, 2, 3, 6, 7}; // sand, lava, quicksand, stone, tiles, desert tiles, grass
s8 cmm_terrain_floors_lava[] =       {0, 8, 9, 2, 3}; // stone, lava, quicksand, basalt, tiles
s8 cmm_terrain_floors_cave[] =       {0, 8, 9, 2, 4}; // grass, lava, quicksand, stone, maze floor
s8 cmm_terrain_floors_castle[] =     {0, 8, 9, 3}; // tiling, lava, quicksand, carpet
s8 cmm_terrain_floors_virtuaplex[] = {0, 8, 9, 1, 2, 3, 7}; // block, lava, void, tiling, grass, blue tiling, snowy block
s8 cmm_terrain_floors_bbh[] =        {3, 8, 0, 6}; // metal, lava, stone, wood
s8 cmm_terrain_floors_jrb[] =        {0, 2, 9, 3, 5}; // sand, stone, quicksand, tiles, wood
s8 cmm_terrain_floors_snow[] =       {0, 8, 9, 1, 3}; // snow, hazard ice, lava, bricks, tiles
s8 cmm_terrain_floors_retro[] =      {0, 8, 4, 7, 9}; // ground, lava, blue ground, white bricks, underwater tile
s8 cmm_terrain_floors_mc[] =         {0, 8, 2, 5, 6, 7}; // grass, lava, stone, planks, sand, bricks

enum cmm_fences {
    CMM_FENCE_NORMAL,
    CMM_FENCE_DESERT,
    CMM_FENCE_RHR,
    CMM_FENCE_HMC,
    CMM_FENCE_CASTLE,
    CMM_FENCE_VIRTUAPLEX,
    CMM_FENCE_BBH,
    CMM_FENCE_JRB,
    CMM_FENCE_SNOW,
    CMM_FENCE_RETRO,
    CMM_FENCE_MC,
};

Gfx *cmm_fence_texs[] = {
    mat_maker_MakerFence_layer1,
    mat_maker_MakerDFence_layer1,
    mat_maker_MakerRHRFence_layer1,
    mat_maker_MakerHFence_layer1,
    mat_maker_MakerCFence_layer1,
    mat_maker_MakerVPFence_layer1,
    mat_maker_MakerBBHFence_layer1,
    mat_maker_MakerJRBFence_layer1,
    mat_maker_MakerSnowFence_layer1,
    mat_maker_MakerRetroFence_layer1,
    mat_maker_MakerMCFence_layer1,
};

enum cmm_bars {
    CMM_BAR_GENERIC,
    CMM_BAR_DESERT,
    CMM_BAR_RHR,
    CMM_BAR_HMC,
    CMM_BAR_BBH,
    CMM_BAR_VP,
    CMM_BAR_RETRO,
    CMM_BAR_MC,
};
Gfx *cmm_bar_texs[][2] = {
    {mat_maker_MakerIronBars_layer1,   mat_maker_MakerIronBarsTop_layer1},
    {mat_maker_MakerDMesh_layer1,      mat_maker_MakerDesertMeshTop_layer1},
    {mat_maker_MakerRHRMesh_layer1,    mat_maker_MakerChainTop_layer1},
    {mat_maker_MakerHMesh_layer1,      mat_maker_MakerHMCTop_layer1},
    {mat_maker_MakerBBHMesh_layer1,    mat_maker_MakerHMCTop_layer1},
    {mat_maker_MakerVPMesh_layer1,     mat_maker_MakerChainTop_layer1},
    {mat_maker_MakerRetroMesh_layer1,  mat_maker_MakerRetroMeshTop_layer1},
    {mat_maker_MakerMCIronBars_layer1, mat_maker_MakerMCIronBarsTop_layer1},
};

enum cmm_water {
    CMM_WATER_DEFAULT,
    CMM_WATER_GREEN,
    CMM_WATER_RETRO,
    CMM_WATER_MC,
};

Gfx *cmm_water_texs[] = {
    mat_maker_MakerWater,
    mat_maker_MakerGreenWater,
    mat_maker_MakerRetroWater,
    mat_maker_MakerMCWater,
};

struct cmm_theme cmm_theme_table[] = {
    // GENERIC
    {
        {
            {CMM_MAT_DIRT,        CMM_MAT_GRASS, "Grass"},
            {CMM_MAT_BRICKS,      0,             "Bricks"},
            {CMM_MAT_COBBLESTONE, CMM_MAT_STONE, "Stone"},
            {CMM_MAT_TILESBRICKS, CMM_MAT_TILES, "Tiling"},
            {CMM_MAT_ROOF,        0,             "Roof"},
            {CMM_MAT_WOOD,        0,             "Wood"},
            {CMM_MAT_SANDDIRT,    CMM_MAT_SAND,  "Sand"},
            {CMM_MAT_SNOWDIRT,    CMM_MAT_SNOW,  "Snow"},
            {CMM_MAT_LAVA,        0,             "Lava"},
            {CMM_MAT_QUICKSAND,   0,             "Quicksand"},
        },
        ARRAY_COUNT(cmm_terrain_floors_generic), cmm_terrain_floors_generic,
        CMM_FENCE_NORMAL, CMM_MAT_STONE, CMM_BAR_GENERIC, CMM_WATER_DEFAULT
    },
    // DESERT
    {
        {
            {CMM_MAT_SANDDIRT,        CMM_MAT_SAND,          "Sand"},
            {CMM_MAT_DESERT_BRICKS,   0,                     "Bricks"},
            {CMM_MAT_DESERT_STONE,    0,                     "Stone"},
            {CMM_MAT_DESERT_TILES,    0,                     "Tiling"},
            {CMM_MAT_DESERT_BLOCK,    0,                     "Stone Block"},
            {CMM_MAT_DESERT_SLOWSAND, 0,                     "Slow Quicksand"},
            {CMM_MAT_DESERT_BRICKS,   CMM_MAT_DESERT_TILES2, "Plating"},
            {CMM_MAT_DIRT,            CMM_MAT_GRASS,         "Grass"},
            {CMM_MAT_LAVA,            0,                     "Lava"},
            {CMM_MAT_QUICKSAND,       0,                     "Quicksand"},
        },
        ARRAY_COUNT(cmm_terrain_floors_desert), cmm_terrain_floors_desert,
        CMM_FENCE_DESERT, CMM_MAT_DESERT_TILES2, CMM_BAR_DESERT, CMM_WATER_GREEN
    },
    // LAVA
    {
        {
            {CMM_MAT_RHR_STONE,   CMM_MAT_RHR_OBSIDIAN, "Stone"},
            {CMM_MAT_RHR_BRICK,   CMM_MAT_RHR_OBSIDIAN, "Bricks"},
            {CMM_MAT_RHR_BASALT,  0,                    "Basalt"},
            {CMM_MAT_RHR_TILES,   0,                    "Tiling"},
            {CMM_MAT_RHR_BLOCK,   0,                    "Stone Block"},
            {CMM_MAT_RHR_WOOD,    0,                    "Wood"},
            {CMM_MAT_RHR_PILLAR,  CMM_MAT_RHR_TILES,    "Pillar"},
            {CMM_MAT_RHR_MESH,    0,                    "Mesh"},
            {CMM_MAT_LAVA,        0,                    "Lava"},
            {CMM_MAT_SERVER_ACID, 0,                    "Server Acid"},
        },
        ARRAY_COUNT(cmm_terrain_floors_lava), cmm_terrain_floors_lava,
        CMM_FENCE_RHR, CMM_MAT_RHR_PILLAR, CMM_BAR_RHR, CMM_WATER_DEFAULT
    },
    // CAVE
    {
        {
            {CMM_MAT_HMC_DIRT,      CMM_MAT_HMC_GRASS, "Grass"},
            {CMM_MAT_HMC_BRICK,     0,                 "Bricks"},
            {CMM_MAT_HMC_STONE,     0,                 "Stone"},
            {CMM_MAT_HMC_MAZEWALL,  0,                 "Maze Wall"},
            {CMM_MAT_HMC_MAZEFLOOR, 0,                 "Maze Floor"},
            {CMM_MAT_HMC_LIGHT,     0,                 "Light"},
            {CMM_MAT_HMC_LAKEGRASS, CMM_MAT_HMC_GRASS, "Cave Wall"},
            {CMM_MAT_HMC_MESH,      0,                 "Mesh"},
            {CMM_MAT_LAVA,          0,                 "Lava"},
            {CMM_MAT_QUICKSAND,     0,                 "Quicksand"},
        },
        ARRAY_COUNT(cmm_terrain_floors_cave), cmm_terrain_floors_cave,
        CMM_FENCE_HMC, CMM_MAT_HMC_LAKEGRASS, CMM_BAR_HMC, CMM_WATER_GREEN
    },
    // CASTLE
    {
        {
            {CMM_MAT_C_WOOD,         CMM_MAT_C_TILES,      "Tiling"},
            {CMM_MAT_C_BRICK,        CMM_MAT_C_TILES,      "Tiling (Bricks)"},
            {CMM_MAT_C_STONESIDE,    CMM_MAT_C_STONETOP, "Tiling (Stone)"},
            {CMM_MAT_C_WOOD,         CMM_MAT_C_CARPET,   "Carpet"},
            {CMM_MAT_C_ROOF,         0,                  "Roof"},
            {CMM_MAT_C_WALL,         0,                  "Castle Wall"},
            {CMM_MAT_C_PILLAR,       CMM_MAT_C_STONETOP, "Pillar"},
            {CMM_MAT_C_BASEMENTWALL, 0,                  "Basement Wall"},
            {CMM_MAT_LAVA,           0,                  "Lava"},
            {CMM_MAT_C_OUTSIDEBRICK, 0,                  "Castle Bricks"},
        },
        ARRAY_COUNT(cmm_terrain_floors_castle), cmm_terrain_floors_castle,
        CMM_FENCE_CASTLE, CMM_MAT_C_STONESIDE, CMM_BAR_VP, CMM_WATER_DEFAULT
    },
    // VIRTUAPLEX
    {
        {
            {CMM_MAT_VP_BLOCK,      0,                    "Block"},
            {CMM_MAT_VP_TILES,      0,                    "Tiling"},
            {CMM_MAT_DIRT,          CMM_MAT_GRASS,        "Grass"},
            {CMM_MAT_VP_TILES,      CMM_MAT_VP_BLUETILES, "Blue Tiling"},
            {CMM_MAT_VP_RUSTYBLOCK, 0,                    "Rusty Block"},
            {CMM_MAT_VP_SCREEN,     0,                    "Screen"},
            {CMM_MAT_VP_CAUTION,    0,                    "Hazard Stripes"},
            {CMM_MAT_VP_BLOCK,      CMM_MAT_SNOW,         "Snowy Block"},
            {CMM_MAT_LAVA,          0,                    "Lava"},
            {CMM_MAT_VP_VOID,       0,                    "Void"},
        },
        ARRAY_COUNT(cmm_terrain_floors_virtuaplex), cmm_terrain_floors_virtuaplex,
        CMM_FENCE_VIRTUAPLEX, CMM_MAT_VP_CAUTION, CMM_BAR_VP, CMM_WATER_DEFAULT
    },
    // SNOW
    {
        {
            {CMM_MAT_SNOWDIRT,       CMM_MAT_SNOW,             "Snow"},
            {CMM_MAT_SNOW_BRICKS,    CMM_MAT_SNOW_BRICK_TILES, "Bricks"},
            {CMM_MAT_SNOW_ROCK,      0,                        "Rock"},
            {CMM_MAT_SNOW_TILE_SIDE, CMM_MAT_SNOW_TILES,       "Tiling"},
            {CMM_MAT_SNOW_ROOF,      0,                        "Roof"},
            {CMM_MAT_WOOD,           0,                        "Wood"},
            {CMM_MAT_CRYSTAL,        0,                        "Crystal"},
            {CMM_MAT_ICE,            0,                        "Ice"},
            {CMM_MAT_BURNING_ICE,    0,                        "Hazard Ice"},
            {CMM_MAT_LAVA,           0,                        "Lava"},
        },
        ARRAY_COUNT(cmm_terrain_floors_snow), cmm_terrain_floors_snow,
        CMM_FENCE_SNOW, CMM_MAT_SNOW_TILE_SIDE, CMM_BAR_GENERIC, CMM_WATER_DEFAULT
    },
    // BBH
    {
        {
            {CMM_MAT_BBH_BRICKS,         CMM_MAT_BBH_STONE,      "Stone Floor"},
            {CMM_MAT_BBH_HAUNTED_PLANKS, 0,                      "Haunted Planks"},
            {CMM_MAT_BBH_STONE_PATTERN,  CMM_MAT_BBH_WOOD_FLOOR, "Wood Floor"},
            {CMM_MAT_BBH_BRICKS,         CMM_MAT_BBH_METAL,      "Metal Floor"},
            {CMM_MAT_BBH_ROOF,           0,                      "Roof"},
            {CMM_MAT_BBH_WOOD_WALL,      0,                      "Wood"},
            {CMM_MAT_BBH_STONE,          0,                      "Wall"},
            {CMM_MAT_BBH_PILLAR,         CMM_MAT_BBH_STONE,      "Pillar"},
            {CMM_MAT_LAVA,               0,                      "Lava"},
            {CMM_MAT_BBH_WINDOW,         0,                      "Window"},
        },
        ARRAY_COUNT(cmm_terrain_floors_bbh), cmm_terrain_floors_bbh,
        CMM_FENCE_BBH, CMM_MAT_BBH_BRICKS, CMM_BAR_BBH, CMM_WATER_DEFAULT
    },
    // JRB
    {
        {
            {CMM_MAT_JRB_STONE,      CMM_MAT_JRB_SAND,    "Sand"},
            {CMM_MAT_JRB_BRICKS,     0,                   "Bricks"},
            {CMM_MAT_JRB_UNDERWATER, 0,                   "Stone"},
            {CMM_MAT_JRB_TILESIDE,   CMM_MAT_JRB_TILETOP, "Tiles"},
            {CMM_MAT_JRB_SHIPSIDE,   CMM_MAT_JRB_SHIPTOP, "Wood (Ship)"},
            {CMM_MAT_JRB_METAL,      CMM_MAT_JRB_WOOD,    "Wood (Docks)"},
            {CMM_MAT_JRB_METALSIDE,  CMM_MAT_JRB_METAL,   "Metal"},
            {CMM_MAT_HMC_MESH,       0,                   "Mesh"},
            {CMM_MAT_JRB_WALL,       0,                   "Wall"},
            {CMM_MAT_QUICKSAND,      0,                   "Quicksand"},
        },
        ARRAY_COUNT(cmm_terrain_floors_jrb), cmm_terrain_floors_jrb,
        CMM_FENCE_JRB, CMM_MAT_VP_CAUTION, CMM_BAR_HMC, CMM_WATER_DEFAULT
    },
    // RETRO
    {
        {
            {CMM_MAT_RETRO_GROUND,           0,                     "Ground"},
            {CMM_MAT_RETRO_BRICKS,           0,                     "Bricks"},
            {CMM_MAT_RETRO_TREEPLAT,         CMM_MAT_RETRO_TREETOP, "Treetop"},
            {CMM_MAT_RETRO_BLOCK,            0,                     "Block"},
            {CMM_MAT_RETRO_BLUEGROUND,       0,                     "Blue Ground"},
            {CMM_MAT_RETRO_BLUEBRICKS,       0,                     "Blue Bricks"},
            {CMM_MAT_RETRO_BLUEBLOCK,        0,                     "Blue Block"},
            {CMM_MAT_RETRO_WHITEBRICK,       0,                     "White Bricks"},
            {CMM_MAT_RETRO_LAVA,             0,                     "Lava"},
            {CMM_MAT_RETRO_UNDERWATERGROUND, 0,                     "Underwater Tile"},
        },
        ARRAY_COUNT(cmm_terrain_floors_retro), cmm_terrain_floors_retro,
        CMM_FENCE_RETRO, CMM_MAT_RETRO_BRICKS, CMM_BAR_RETRO, CMM_WATER_RETRO
    },
    // MINECRAFT
    {
        {
            {CMM_MAT_MC_DIRT,          CMM_MAT_MC_GRASS,       "Grass"},
            {CMM_MAT_MC_COBBLESTONE,   0,                      "Cobblestone"},
            {CMM_MAT_MC_STONE,         0,                      "Stone"},
            {CMM_MAT_MC_OAK_LOG_SIDE,  CMM_MAT_MC_OAK_LOG_TOP, "Oak Log"},
            {CMM_MAT_MC_OAK_LEAVES,    0,                      "Oak Leaves"},
            {CMM_MAT_MC_WOOD_PLANKS,   0,                      "Oak Planks"},
            {CMM_MAT_MC_SAND,          0,                      "Sand"},
            {CMM_MAT_MC_BRICKS,        0,                      "Bricks"},
            {CMM_MAT_MC_FLOWING_LAVA,  CMM_MAT_MC_LAVA,        "Lava"},
            {CMM_MAT_MC_GLASS,         0,                      "Glass"},
        },
        ARRAY_COUNT(cmm_terrain_floors_mc), cmm_terrain_floors_mc,
        CMM_FENCE_MC, CMM_MAT_MC_OAK_LOG_SIDE, CMM_BAR_MC, CMM_WATER_MC
    },
};

// Returns full tile definition (struct cmm_tilemat_def)
#define TILE_MATDEF(matid) (cmm_theme_table[cmm_lopt_theme].mats[matid])
// Returns main material (struct cmm_material)
#define MATERIAL(matid) (cmm_mat_table[TILE_MATDEF(matid).mat])

// Returns TRUE if given material has a unique top texture
#define HAS_TOPMAT(matid) (TILE_MATDEF(matid).topmat != 0)
// Returns top material's topmat struct (struct cmm_topmaterial)
#define TOPMAT(matid) (cmm_mat_table[TILE_MATDEF(matid).topmat])

// Returns current fence texture
#define FENCE_TEX() (cmm_fence_texs[cmm_theme_table[cmm_lopt_theme].fence])
#define POLE_TEX()  (cmm_mat_table[cmm_theme_table[cmm_lopt_theme].pole].gfx)
#define BARS_TEX() (cmm_bar_texs[cmm_theme_table[cmm_lopt_theme].bars][0])
#define BARS_TOPTEX() (cmm_bar_texs[cmm_theme_table[cmm_lopt_theme].bars][1])
#define WATER_TEX() (cmm_water_texs[cmm_theme_table[cmm_lopt_theme].water])

enum {
    CMM_BUTTON_SETTINGS,
    CMM_BUTTON_TEST,
    CMM_BUTTON_TERRAIN,
    CMM_BUTTON_SLOPE,
    CMM_BUTTON_TROLL,
    CMM_BUTTON_STAR,
    CMM_BUTTON_GROUND,
    CMM_BUTTON_COIN,
    CMM_BUTTON_BLANK,
    CMM_BUTTON_GCOIN,
    CMM_BUTTON_CORNER,
    CMM_BUTTON_ICORNER,
    CMM_BUTTON_RCOIN,
    CMM_BUTTON_BCOIN,
    CMM_BUTTON_NOTEBLOCK,
    CMM_BUTTON_CULL,
    CMM_BUTTON_MECH,
    CMM_BUTTON_TREE,
    CMM_BUTTON_EXCLA,
    CMM_BUTTON_SPAWN,
    CMM_BUTTON_BTCME,
    CMM_BUTTON_PIPE,
    CMM_BUTTON_BADGE,
    CMM_BUTTON_WATER,
    CMM_BUTTON_FENCE,
    CMM_BUTTON_BOSS,
    CMM_BUTTON_MPLAT,
    CMM_BUTTON_BBALL,
    CMM_BUTTON_KTQ,
    CMM_BUTTON_SSLOPE,
    CMM_BUTTON_SLAB,
    CMM_BUTTON_TC,

    CMM_BUTTON_HEART,
    CMM_BUTTON_FORMATION,
    CMM_BUTTON_VSLAB,
    CMM_BUTTON_BARS,
    CMM_BUTTON_ROCKENEMY,
    CMM_BUTTON_POLE,
    CMM_BUTTON_VEXCLA,
    CMM_BUTTON_FLYING,
    CMM_BUTTON_HAUNTED,
    CMM_BUTTON_SNOWEN,
    CMM_BUTTON_MINE,
    CMM_BUTTON_FIRE_SPINNER,
};

u8 cmm_toolbar_defaults[9] = {
    CMM_BUTTON_TERRAIN,
    CMM_BUTTON_SLOPE,
    CMM_BUTTON_BARS,
    CMM_BUTTON_TREE,
    CMM_BUTTON_COIN,
    CMM_BUTTON_STAR,
    CMM_BUTTON_GROUND,
    CMM_BUTTON_TEST,
    CMM_BUTTON_SETTINGS,
};

u8 cmm_toolbar[9];
f32 cmm_toolbar_y_anim[9] = {
    0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
};
u8 cmm_toolbox_transition_btn_render = FALSE;
f32 cmm_toolbox_transition_btn_x;
f32 cmm_toolbox_transition_btn_y;
f32 cmm_toolbox_transition_btn_tx;
f32 cmm_toolbox_transition_btn_ty;
Gfx * cmm_toolbox_transition_btn_gfx;
Gfx * cmm_toolbox_transition_btn_old_gfx;

u8 cmm_toolbox[45];
//Different toolboxes for different game styles
u8 cmm_toolbox_btcm[45] = {
    /*Tiles    */ CMM_BUTTON_TERRAIN, CMM_BUTTON_SLAB, CMM_BUTTON_SLOPE, CMM_BUTTON_CORNER, CMM_BUTTON_ICORNER, CMM_BUTTON_VSLAB, CMM_BUTTON_SSLOPE, CMM_BUTTON_TROLL, CMM_BUTTON_CULL,
    /*Tiles 2  */ CMM_BUTTON_WATER, CMM_BUTTON_FENCE, CMM_BUTTON_BARS, CMM_BUTTON_POLE, CMM_BUTTON_TREE, CMM_BUTTON_NOTEBLOCK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK,
    /*Items    */ CMM_BUTTON_STAR, CMM_BUTTON_COIN,CMM_BUTTON_FORMATION,CMM_BUTTON_GCOIN,CMM_BUTTON_RCOIN,CMM_BUTTON_BCOIN,CMM_BUTTON_EXCLA, CMM_BUTTON_HEART, CMM_BUTTON_BLANK,
    /*Enemies  */ CMM_BUTTON_GROUND,CMM_BUTTON_MECH,CMM_BUTTON_FLYING,CMM_BUTTON_HAUNTED,CMM_BUTTON_ROCKENEMY,CMM_BUTTON_SNOWEN,CMM_BUTTON_BTCME,CMM_BUTTON_BLANK,CMM_BUTTON_BLANK,
    /*Obstacles*/ CMM_BUTTON_SPAWN,CMM_BUTTON_MPLAT, CMM_BUTTON_TC, CMM_BUTTON_MINE,CMM_BUTTON_FIRE_SPINNER, CMM_BUTTON_BADGE, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK,
};
u8 cmm_toolbox_vanilla[45] = {
    /*Tiles    */ CMM_BUTTON_TERRAIN, CMM_BUTTON_SLAB, CMM_BUTTON_SLOPE, CMM_BUTTON_CORNER, CMM_BUTTON_ICORNER, CMM_BUTTON_VSLAB, CMM_BUTTON_SSLOPE, CMM_BUTTON_TROLL, CMM_BUTTON_CULL,
    /*Tiles 2  */ CMM_BUTTON_WATER, CMM_BUTTON_FENCE, CMM_BUTTON_BARS, CMM_BUTTON_POLE, CMM_BUTTON_TREE, CMM_BUTTON_NOTEBLOCK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK,
    /*Items    */ CMM_BUTTON_STAR, CMM_BUTTON_COIN,CMM_BUTTON_FORMATION, CMM_BUTTON_RCOIN,CMM_BUTTON_BCOIN,CMM_BUTTON_VEXCLA,CMM_BUTTON_HEART,CMM_BUTTON_BLANK, CMM_BUTTON_BLANK,
    /*Enemies  */ CMM_BUTTON_GROUND,CMM_BUTTON_MECH,CMM_BUTTON_FLYING,CMM_BUTTON_HAUNTED,CMM_BUTTON_ROCKENEMY,CMM_BUTTON_SNOWEN,CMM_BUTTON_BOSS,CMM_BUTTON_KTQ, CMM_BUTTON_BLANK,
    /*Obstacles*/ CMM_BUTTON_SPAWN,CMM_BUTTON_MPLAT,CMM_BUTTON_TC, CMM_BUTTON_MINE, CMM_BUTTON_FIRE_SPINNER, CMM_BUTTON_BBALL, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK,
};



//BEHAVIOR  //Y-OFF //MODEL ID //BILLB //COINS //SCALE  //ANIMATION PTR //DISP.FUNC //SOUND
struct cmm_object_info cmm_object_type_star[] = {
    {bhvStar, TILE_SIZE/2, MODEL_STAR, FALSE, 0, 0, 1.0f, NULL, df_star, SOUND_MENU_STAR_SOUND | SOUND_VIBRATO},
    {bhvHiddenRedCoinStar, TILE_SIZE/2, MODEL_TRANSPARENT_STAR, FALSE, 0, 1, 1.0f, NULL, df_reds_marker, SOUND_MENU_STAR_SOUND | SOUND_VIBRATO},
    {bhvPlantStar, TILE_SIZE/2, MODEL_TRANSPARENT_STAR, FALSE, 0, 1, 1.0f, NULL, df_star, SOUND_MENU_STAR_SOUND | SOUND_VIBRATO},
};
struct cmm_object_info cmm_object_type_goomba[] = {
    {bhvGoomba, 0, MODEL_GOOMBA, FALSE, 1, 0, 1.5f, goomba_seg8_anims_0801DA4C, NULL, SOUND_OBJ_GOOMBA_PREVIEW},
    {bhvBigGoomba, 0, MODEL_GOOMBA, FALSE, 5, 0, 3.5f, goomba_seg8_anims_0801DA4C, NULL, SOUND_OBJ_GOOMBA_PREVIEW},
    {bhvTinyGoomba, 0, MODEL_GOOMBA, FALSE, 1, 0, 0.5f, goomba_seg8_anims_0801DA4C, NULL, SOUND_OBJ_GOOMBA_PREVIEW},
    {bhvPiranhaPlant, 0, MODEL_MAKER_PLANT, FALSE, 5, 0, 1.0f, piranha_plant_seg6_anims_0601C31C, NULL, SOUND_OBJ2_PIRANHA_PLANT_BITE},
    {bhvFirePiranhaPlantBig, 0, MODEL_MAKER_PLANT, FALSE, 2, 0, 2.0f, piranha_plant_seg6_anims_0601C31C, NULL, SOUND_OBJ2_PIRANHA_PLANT_BITE},
    {bhvFirePiranhaPlant, 0, MODEL_MAKER_PLANT, FALSE, 1, 0, 0.5f, piranha_plant_seg6_anims_0601C31C, NULL, SOUND_OBJ2_PIRANHA_PLANT_BITE},
    {bhvScaredKoopa, 0, MODEL_KOOPA_WITH_SHELL, FALSE, 5, 0, 1.5f, koopa_seg6_anims_06011364, df_koopa, SOUND_OBJ_KOOPA_TALK},
};
struct cmm_object_info cmm_object_type_yellowcoin = {
    bhvYellowCoin, 0, MODEL_YELLOW_COIN, TRUE, 1, 0, 1.0f, NULL, NULL, SOUND_GENERAL_COIN | SOUND_VIBRATO,
};
struct cmm_object_info cmm_object_type_greencoin = {
    bhvGreenCoin, 0, 0xEF, TRUE, 3, 0, 1.0f, NULL, NULL, SOUND_GENERAL_COIN_MULTI,
};
struct cmm_object_info cmm_object_type_redcoin = {
    bhvRedCoin, 0, MODEL_RED_COIN, TRUE, 2, 0, 1.0f, NULL, NULL, SOUND_MENU_COLLECT_RED_COIN,
};
struct cmm_object_info cmm_object_type_bluecoin[] = {
    {bhvHiddenBlueCoin, 0, MODEL_BLUE_COIN, TRUE, 5, 0, 1.0f, NULL, NULL, SOUND_GENERAL_COIN_MULTI},
    {bhvBlueCoinSwitch, 0, MODEL_BLUE_COIN_SWITCH, FALSE, 0, 0, 3.0f, NULL, NULL, SOUND_GENERAL2_PURPLE_SWITCH},
};
struct cmm_object_info cmm_object_type_noteblock = {
    bhvNoteblock, TILE_SIZE/2, MODEL_NOTEBLOCK, FALSE, 0, 0, 1.0f, NULL, NULL, SOUND_GENERAL_CRAZY_BOX_BOING_SLOW,
};

struct cmm_object_info cmm_object_type_mech_enemy[] = {
    {bhvBobomb, 0, MODEL_BLACK_BOBOMB, FALSE, 1, 0, 1.0f, bobomb_seg8_anims_0802396C, NULL, SOUND_GENERAL2_QUIET_EXPLOSION},
    {bhvChuckya, 0, MODEL_CHUCKYA, FALSE, 5, 0, 2.0f, chuckya_seg8_anims_0800C070, df_chuckya, SOUND_OBJ_CHUCKYA_PREVIEW},
    {bhvSmallBully, 0, MODEL_BULLY, FALSE, 1, 0, 1.0f, bully_seg5_anims_0500470C, df_bully, SOUND_OBJ2_SMALL_BULLY_ATTACKED},
    {bhvBulletBillCannon, TILE_SIZE/2, MODEL_BILL_MAKER_2, FALSE, 0, 1, 1.0f, NULL, NULL, SOUND_OBJ_POUNDING_CANNON},
    {bhvHeaveHo, 0, MODEL_MAKER_HEAVEHO, FALSE, 0, 0, 2.0f, heave_ho_seg5_anims_0501534C, NULL, SOUND_OBJ_HEAVEHO_PREVIEW},
};

struct cmm_object_info cmm_object_type_tree = {
    bhvTree, 0, MODEL_MAKER_TREE_1, TRUE, 0, 0, 1.0f, NULL, df_tree, SOUND_ACTION_CLIMB_UP_TREE | SOUND_VIBRATO,
};
struct cmm_object_info cmm_object_type_exclamationbox = {
    bhvExclamationBox, TILE_SIZE/2, MODEL_EXCLAMATION_BOX, FALSE, 0, 0, 2.0f, NULL, df_exbox, SOUND_GENERAL_BOX_PREVIEW,
};
struct cmm_object_info cmm_object_type_spawn = {
    bhvSpawn, TILE_SIZE/2, MODEL_SPAWN, FALSE, 0, 0, 1.0f, NULL, NULL, SOUND_MENU_STAR_SOUND_LETS_A_GO,
};
struct cmm_object_info cmm_object_type_btcme[] = {
    {bhvRex, 0, 0xE1, FALSE, 2, 0, 1.5f, Rex_anims, NULL, SOUND_OBJ_GOOMBA_PREVIEW},
    {bhvPodoboo, TILE_SIZE/2, MODEL_PODOBOO, FALSE, 0, 0, 1.0f, NULL, df_podoboo, SOUND_OBJ_FLAME_BLOWN},
    {bhvCrablet, 0, MODEL_MAKER_CRABLET, FALSE, 4, 0, 1.0f, crab_anims_anims, NULL, SOUND_OBJ2_SCUTTLEBUG_ALERT},
    {bhvHammerBro, 60.0f, 0xEE, FALSE, 6, 0, 1.0f, Hammerbro_anims, NULL, SOUND_OBJ_KOOPA_DAMAGE},
    {bhvFireBro, 60.0f, 0xEE, FALSE, 6, 0, 1.0f, Hammerbro_anims, df_firebro, SOUND_OBJ_KOOPA_DAMAGE},
    {bhvPhantasm, 0, MODEL_MARIO, FALSE, 5, 0, 1.0f, &evil_mario_anims[2], NULL, SOUND_ACTION_METAL_STEP | SOUND_VIBRATO},
};
struct cmm_object_info cmm_object_type_warppipe = {
    bhvWarpPipe, 0, MODEL_MAKER_PIPE, FALSE, 0, 0, 1.0f, NULL, NULL, SOUND_MENU_ENTER_PIPE | SOUND_VIBRATO,
};
struct cmm_object_info cmm_object_type_badge = {
    bhvBadge, TILE_SIZE/2, MODEL_BADGE, TRUE, 0, 0, 5.0f, NULL, NULL, SOUND_GENERAL2_PURPLE_SWITCH,
};

struct cmm_object_info cmm_object_type_bosses[] = {
    {bhvBoss, 0, MODEL_KINGBOMB_MAKER, FALSE, 0, 0, 1.0f, king_bobomb_seg5_anims_0500FE30, df_kingbomb, SOUND_OBJ_KING_BOBOMB_POUNDING1_HIGHPRIO},
    {bhvWhompKingBoss, 0, MODEL_WHOMP_MAKER, FALSE, 0, 0, 2.f, whomp_seg6_anims_06020A04, NULL, SOUND_OBJ_WHOMP},
    {bhvBalconyBigBoo, TILE_SIZE, MODEL_MAKER_BOO, FALSE, 0, 0, 3.0f, NULL, df_boo, SOUND_OBJ_BOO_LAUGH_LONG},
    {bhvBigBully, 0, MODEL_BULLY, FALSE, 0, 0, 2.0f, bully_seg5_anims_0500470C, df_bully, SOUND_OBJ2_LARGE_BULLY_ATTACKED},
    {bhvBowser, 0, MODEL_MAKER_BOWSER, FALSE, 0, 3, 1.0f, bowser_seg6_anims_06057690, df_booser, SOUND_OBJ2_BOWSER_ROAR},
};

struct cmm_object_info cmm_object_type_platform = {
    bhvPlatformOnTrack, TILE_SIZE/2, MODEL_CHECKERBOARD_PLATFORM, FALSE, 0, 0, 1.0f, NULL, df_checkerboard_elevator, SOUND_ENV_ELEVATOR1 | SOUND_VIBRATO,
};
struct cmm_object_info cmm_object_type_bowlingball = {
    bhvBobBowlingBallSpawner, TILE_SIZE/2, MODEL_BOWLING_BALL, TRUE, 0, 0, 1.0f, NULL, NULL, SOUND_GENERAL_QUIET_POUND1 | SOUND_VIBRATO,
};
struct cmm_object_info cmm_object_type_ktq = {
    bhvKoopa, 0, MODEL_KOOPA_WITH_SHELL, FALSE, 0, 1, 3.0f, koopa_seg6_anims_06011364, df_ktq, SOUND_OBJ_KOOPA_TALK,
};
struct cmm_object_info cmm_object_type_timed_challenge[] = {
    {bhvFloorSwitchHiddenObjects, 0, MODEL_PURPLE_SWITCH, FALSE, 0, 0, 1.5f, NULL, NULL, SOUND_GENERAL2_PURPLE_SWITCH},
    {bhvHiddenObject, 0, MODEL_BREAKABLE_BOX, FALSE, 0, 0, 1.0f, NULL, df_corkbox, SOUND_GENERAL2_SWITCH_TICK_FAST},
};

struct cmm_object_info cmm_object_type_heart = {
    bhvRecoveryHeart, TILE_SIZE/2, MODEL_HEART, FALSE, 0, 0, 1.0f, NULL, df_heart, SOUND_GENERAL_HEART_SPIN,
};
struct cmm_object_info cmm_object_type_test_mario = {
    NULL, 0, MODEL_MARIO, FALSE, 0, 0, 1.f, &evil_mario_anims[11], NULL, 0,
};

struct cmm_object_info cmm_object_type_settings[2] = {0};

struct cmm_object_info cmm_object_type_stone[] = {
    {bhvThwomp, 0, MODEL_THWOMP_MAKER, FALSE, 0, 0, 1.5f, NULL, NULL, SOUND_OBJ_THWOMP},
    {bhvSmallWhomp, 0, MODEL_WHOMP_MAKER, FALSE, 10, 0, 1.f, whomp_seg6_anims_06020A04, NULL, SOUND_OBJ_WHOMP},
    {bhvGrindel, 0, MODEL_MAKER_GRINDEL, FALSE, 0, 0, 1.f, NULL, df_grindel, SOUND_OBJ_KING_BOBOMB_JUMP},
};

struct cmm_object_info cmm_object_type_flying[] = {
    {bhvEnemyLakitu, TILE_SIZE/2, MODEL_LAKITU_MAKER, FALSE, 5, 5, 1.0f, lakitu_enemy_seg5_anims_050144D4, df_lakitu, SOUND_OBJ_EVIL_LAKITU_THROW},
    {bhvRealFlyGuy, TILE_SIZE/2, MODEL_FLYGUY, FALSE, 2, 0, 1.5f, flyguy_seg8_anims_08011A64, df_flyguy, SOUND_OBJ_KOOPA_FLYGUY_DEATH},
    {bhvSnufit, TILE_SIZE/2, MODEL_MAKER_SNUFIT, FALSE, 2, 0, 1.0f, NULL, df_snufit, SOUND_OBJ_SNUFIT_SHOOT},
    {bhvCirclingAmp, TILE_SIZE/2, MODEL_AMP, FALSE, 0, 0, 1.0f, dAmpAnimsList, df_circling_amp, SOUND_AIR_AMP_PREVIEW},
};

struct cmm_object_info cmm_object_type_haunted[] = {
    {bhvBoo, TILE_SIZE/2, MODEL_MAKER_BOO, FALSE, 1, 0, 1.0f, NULL, df_boo, SOUND_OBJ_BOO_LAUGH_LONG},
    {bhvMrI, 0, MODEL_MAKER_MRI, TRUE, 5, 1, 1.0f, NULL, df_mri, SOUND_OBJ_MRI_SHOOT},
    {bhvScuttlebug, 0, MODEL_MAKER_SCUTTLEBUG, FALSE, 3, 0, 1.0f, scuttlebug_seg6_anims_06015064, NULL, SOUND_OBJ2_SCUTTLEBUG_ALERT},
};

struct cmm_object_info cmm_object_type_snow_enemy[] = {
    {bhvSpindrift, 0, MODEL_MAKER_SPINDRIFT, FALSE, 3, 0, 1.0f, spindrift_seg5_anims_05002D68, NULL, SOUND_ACTION_TWIRL},
    {bhvMrBlizzard, 0, MODEL_MAKER_BLIZZARD, FALSE, 3, 0, 1.0f, snowman_seg5_anims_0500D118, df_blizzard, SOUND_OBJ2_SCUTTLEBUG_ALERT},
    {bhvMoneybagHidden, 0, MODEL_ATM, FALSE, 5, 0, 1.0f, moneybag_seg6_anims_06005E5C, df_moneybag, SOUND_GENERAL_MONEYBAG_BOING_LOWPRIO},
};

struct cmm_object_info cmm_object_type_mine[] = {
    bhvBowserBomb, TILE_SIZE/2, MODEL_MAKER_BOWSER_BOMB, FALSE, 0, 0, 1.0f, NULL, NULL, SOUND_GENERAL2_QUIET_EXPLOSION,
};

struct cmm_object_info cmm_object_type_fire_spinner[] = {
    bhvLllRotatingBlockWithFireBars, 0, MODEL_MAKER_FIREBAR, FALSE, 0, 0, 1.0f, NULL, df_fire_spinner, SOUND_OBJ_FLAME_BLOWN,
};

struct cmm_object_info cmm_object_type_coin_formation = {
    bhvCoinFormation, 0, MODEL_NONE, FALSE, 0, 0, 1.0f, NULL, df_coin_formation, SOUND_GENERAL_COIN_MULTI,
};

enum {
    OBJECT_TYPE_STAR,
    OBJECT_TYPE_GOOMBA,
    OBJECT_TYPE_COIN,
    OBJECT_TYPE_GCOIN,
    OBJECT_TYPE_RCOIN,
    OBJECT_TYPE_BCOIN,
    OBJECT_TYPE_NOTE,
    OBJECT_TYPE_MECH,
    OBJECT_TYPE_TREE,
    OBJECT_TYPE_EXCLA,
    OBJECT_TYPE_SPAWN,
    OBJECT_TYPE_BTCME,
    OBJECT_TYPE_PIPE,
    OBJECT_TYPE_BADGE,
    OBJECT_TYPE_BOSS,
    OBJECT_TYPE_MPLAT,
    OBJECT_TYPE_BBALL,
    OBJECT_TYPE_KTQ,
    OBJECT_TYPE_TC,
    OBJECT_TYPE_HEART,
    OBJECT_TYPE_STONE,
    OBJECT_TYPE_TEST,// Fake type, used for the Test mario preview
    OBJECT_TYPE_FLYING,
    OBJECT_TYPE_HAUNTED,
    OBJECT_TYPE_SNOWEN,
    OBJECT_TYPE_MINE,
    OBJECT_TYPE_FIRE_SPINNER,
    OBJECT_TYPE_COINFORM,
    OBJECT_TYPE_SETTINGS, // Also fake type
};

struct cmm_object_place cmm_object_place_types[] = {
    { cmm_object_type_star, FALSE, TRUE, TRUE, 3},
    {&cmm_object_type_goomba, FALSE, FALSE, TRUE, 7},
    {&cmm_object_type_yellowcoin, FALSE, FALSE, FALSE, 0},
    {&cmm_object_type_greencoin, FALSE, FALSE, FALSE, 0},
    {&cmm_object_type_redcoin, FALSE, FALSE, FALSE, 0},
    { cmm_object_type_bluecoin, FALSE, FALSE, TRUE, 2},
    {&cmm_object_type_noteblock, FALSE, FALSE, FALSE, 0},
    { cmm_object_type_mech_enemy, FALSE, FALSE, TRUE, 5},
    {&cmm_object_type_tree, FALSE, FALSE, FALSE, 4},
    {&cmm_object_type_exclamationbox, FALSE, FALSE, FALSE, 7}, // only supports same size i think
    {&cmm_object_type_spawn, FALSE, FALSE, FALSE, 0},
    { cmm_object_type_btcme, FALSE, FALSE, TRUE, 6},
    {&cmm_object_type_warppipe, FALSE, FALSE, FALSE, 0},
    {&cmm_object_type_badge, FALSE, FALSE, FALSE, 23},
    { cmm_object_type_bosses, FALSE, TRUE, TRUE, 5},
    {&cmm_object_type_platform, TRUE, FALSE, FALSE, 2},
    {&cmm_object_type_bowlingball, TRUE, FALSE, FALSE, 0},
    {&cmm_object_type_ktq, TRUE, TRUE, FALSE, 0},
    { cmm_object_type_timed_challenge, FALSE, FALSE, TRUE, 2},
    {&cmm_object_type_heart, FALSE, FALSE, FALSE, 0},
    { cmm_object_type_stone, FALSE, FALSE, TRUE, 3},
    {&cmm_object_type_test_mario, FALSE, FALSE, FALSE, 0},
    { cmm_object_type_flying, FALSE, FALSE, TRUE, 4},
    { cmm_object_type_haunted, FALSE, FALSE, TRUE, 3},
    { cmm_object_type_snow_enemy, FALSE, FALSE, TRUE, 3},
    {&cmm_object_type_mine, FALSE, FALSE, FALSE, 0},
    {&cmm_object_type_fire_spinner, FALSE, FALSE, FALSE, 9},
    {&cmm_object_type_coin_formation, FALSE, FALSE, FALSE, 5},
    { cmm_object_type_settings, FALSE, FALSE, TRUE, 2}, // Used only for the length field
};

struct ExclamationBoxContents sExclamationBoxContents_btcm[] = {
    { 0, 0, 0, MODEL_MARIOS_WING_CAP,  bhvWingCap,           0, TRUE,  0},
    { 1, 0, 0, MODEL_MARIOS_METAL_CAP, bhvVanishCap,         2, TRUE,  0},
    { 2, 0, 0, MODEL_KOOPA_SHELL,      bhvKoopaShell,        3, TRUE,  0},
    { 3, 0, 0, 0xEF,                   bhvGreenGetsSpawned,  4, FALSE, 3},
    { 4, 0, 0, MODEL_YELLOW_COIN,      bhvSingleCoinGetsSpawned,  4, FALSE, 1},
    { 5, 0, 0, MODEL_NONE,             bhvThreeCoinsSpawn,   4, FALSE, 3},
    { 6, 0, 0, MODEL_NONE,             bhvTenCoinsSpawn,     4, FALSE, 10},
    //END
    { EXCLAMATION_BOX_BP_NULL, 0, 0,         MODEL_NONE,NULL,4, FALSE, 0},
};

struct ExclamationBoxContents sExclamationBoxContents_vanilla[] = {
    { 0, 0, 0, MODEL_V_MARIOS_WING_CAP,  bhvWingCap,         0, TRUE,  0},
    { 1, 0, 6, MODEL_V_MARIOS_METAL_CAP, bhvMetalCap,        1, TRUE,  0},
    { 2, 0, 0, MODEL_MARIOS_CAP,         bhvVanishCap,       2, TRUE,  0},
    { 3, 0, 0, MODEL_KOOPA_SHELL,        bhvKoopaShell,      3, TRUE,  0},
    { 4, 0, 0, MODEL_YELLOW_COIN,        bhvSingleCoinGetsSpawned, 3, FALSE, 1},
    { 5, 0, 0, MODEL_NONE,               bhvThreeCoinsSpawn, 3, FALSE, 3},
    { 6, 0, 0, MODEL_NONE,               bhvTenCoinsSpawn,   3, FALSE, 10},
    //END
    { EXCLAMATION_BOX_BP_NULL, 0, 0,         MODEL_NONE,NULL,3, FALSE, 0},
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
    "Farm",
    "Palm",
    "Snowy"
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
    "Boss Slayer",
    "Brittle Burden",
    "Withering Burden",
};

Gfx *btn_mech_enemies[] = {
    mat_b_btn_bobomb,
    mat_b_btn_chuckya,
    mat_b_btn_bully,
    mat_b_btn_bill,
    mat_b_btn_heaveho,
};

char *txt_mech_enemies[] = {
    "Bob-omb",
    "Chuckya",
    "Bully",
    "Bullet Bill",
    "Heave-Ho",
};

Gfx *btn_mech_bosses[] = {
    mat_b_btn_boss,
    mat_b_btn_boss,
    mat_b_btn_boss,
    mat_b_btn_boss,
    mat_b_btn_boss,
};

char *txt_bp_boss[] = {
    "King Bob-Omb",
    "King Whomp",
    "Big Boo",
    "Big Bully",
    "Bowser",
    "Eyerok",
    "Wiggler",
};

char *txt_star_objects[] = {
    "Normal",
    "Red Coins",
    "Huge Piranhas",
};

Gfx *btn_star_objects[] = {
    mat_b_btn_star,
    mat_b_btn_rcs,
    mat_b_btn_plant,
};

char *txt_timed_objects[] = {
    "Purple Switch",
    "Hidden Corkbox",
};

Gfx *btn_timed_objects[] = {
    mat_b_btn_purpleswitch,
    mat_b_btn_corkbox,
};

char *txt_blue_coins[] = {
    "Hidden Blue Coin",
    "Blue Coin Switch",
};

Gfx *btn_blue_coins[] = {
    mat_b_btn_bluecoin,
    mat_b_btn_bcs,
};

char *txt_btcm_objects[] = {
    "Rex",
    "Podoboo",
    "Crablet",
    "Hammer Bro",
    "Fire Bro",
    "Cosmic Phantasm",
};

Gfx *btn_btcm_objects[] = {
    mat_b_btn_rex,
    mat_b_btn_podoboo,
    mat_b_btn_crablet,
    mat_b_btn_hammerbro,
    mat_b_btn_hammerbro,
    mat_b_btn_phantasm,
};

char *txt_stone_enemies[] = {
    "Thwomp",
    "Whomp",
    "Grindel",
};

Gfx *btn_stone_enemies[] = {
    mat_b_btn_thwomp,
    mat_b_btn_whomp,
    mat_b_btn_grindel,
};

char *txt_flying_enemies[] = {
    "Lakitu",
    "Fly Guy",
    "Snufit",
    "Amp",
};

Gfx *btn_flying_enemies[] = {
    mat_b_btn_lakitu,
    mat_b_btn_flyguy,
    mat_b_btn_snufit,
    mat_b_btn_amp,
};

char *txt_haunted_enemies[] = {
    "Boo",
    "Mr. I",
    "Scuttlebug",
};

Gfx *btn_haunted_enemies[] = {
    mat_b_btn_boo,
    mat_b_btn_mri,
    mat_b_btn_scuttlebug,
};

char *txt_ground_enemies[] = {
    "Goomba",
    "Huge Goomba",
    "Tiny Goomba",
    "Piranha Plant",
    "Huge Piranha Plant",
    "Tiny Piranha Plant",
    "Koopa",
};
Gfx *btn_ground_enemies[] = {
    mat_b_btn_goomba,
    mat_b_btn_goomba,
    mat_b_btn_goomba,
    mat_b_btn_plant,
    mat_b_btn_plant,
    mat_b_btn_plant,
    mat_b_btn_kuppa,
};

char *txt_snow_enemies[] = {
    "Spindrift",
    "Mr.Blizzard",
    "Moneybag",
};

Gfx *btn_snow_enemies[] = {
    mat_b_btn_spindrift,
    mat_b_btn_blizzard,
    mat_b_btn_moneybag,
};

char *txt_obstacles[] = {
    "Bowser Bomb",
    "Fire Spinner",
};

Gfx *btn_obstacles[] = {
    mat_b_btn_bbomb,
    mat_b_btn_firebar,
};

char *txt_coin_formation[] = {
    "Line",
    "Vertical Line",
    "Ring",
    "Vertical Ring",
    "Arrow",
};

char *txt_platforms[] = {
    "Activated",
    "Looping",
};

char *txt_fire_spinner[] = {
    "Length: 2",
    "Length: 3",
    "Length: 4",
    "Length: 5",
    "Length: 6",
    "Length: 7",
    "Length: 8",
    "Length: 9",
    "Length: 10",
};

Gfx *btn_settings[] = {
    mat_b_btn_settings,
    mat_b_btn_camera,
};

char *txt_settings[] = {
    "Level Settings",
    "Take Screenshot",
};

struct cmm_ui_button_type cmm_ui_buttons[] = {
    //button texture            //TILE/OBJ ID        //PLACE MODE  //TXT POINTER         //PARAM STR
    {btn_settings,           1, OBJECT_TYPE_SETTINGS, CMM_PM_OBJ,  "Options",            txt_settings},        //CMM_BUTTON_SETTINGS
    {mat_b_btn_check,        0, OBJECT_TYPE_TEST,    CMM_PM_OBJ,   "Save & Test",        NULL},                //CMM_BUTTON_TEST
    {mat_b_btn_tile,         0, TILE_TYPE_BLOCK,     CMM_PM_TILE,  "Terrain",            NULL},                //CMM_BUTTON_GRASS
    {mat_b_btn_slope,        0, TILE_TYPE_SLOPE,     CMM_PM_TILE,  "Slope",              NULL},                //CMM_BUTTON_SLOPE
    {mat_b_btn_troll,        0, TILE_TYPE_TROLL,     CMM_PM_TILE,  "Intangible Tile",    NULL},                //CMM_BUTTON_TROLL
    {btn_star_objects,       1, OBJECT_TYPE_STAR,    CMM_PM_OBJ,   "Power Star",         txt_star_objects},    //CMM_BUTTON_STAR
    {btn_ground_enemies,     1, OBJECT_TYPE_GOOMBA,  CMM_PM_OBJ,   "Ground Enemies",     txt_ground_enemies},  //CMM_BUTTON_GROUND
    {mat_b_btn_coin,         0, OBJECT_TYPE_COIN,    CMM_PM_OBJ,   "Yellow Coin",        NULL},                //CMM_BUTTON_COIN
    {mat_b_btn_blank,        0, TILE_TYPE_BLOCK,     CMM_PM_TILE,  "",                   NULL},                //CMM_BUTTON_BLANK
    {mat_b_btn_greencoin,    0, OBJECT_TYPE_GCOIN,   CMM_PM_OBJ,   "Green Coin",         NULL},                //CMM_BUTTON_GCOIN
    {mat_b_btn_corner,       0, TILE_TYPE_CORNER,    CMM_PM_TILE,  "Slope Corner",       NULL},                //CMM_BUTTON_CORNER
    {mat_b_btn_icorner,      0, TILE_TYPE_ICORNER,   CMM_PM_TILE,  "Slope Inner Corner", NULL},                //CMM_BUTTON_ICORNER
    {mat_b_btn_redcoin,      0, OBJECT_TYPE_RCOIN,   CMM_PM_OBJ,   "Red Coin",           NULL},                //CMM_BUTTON_RCOIN
    {btn_blue_coins,         1, OBJECT_TYPE_BCOIN,   CMM_PM_OBJ,   "Blue Coin",          txt_blue_coins},      //CMM_BUTTON_BCOIN
    {mat_b_btn_noteblock,    0, OBJECT_TYPE_NOTE,    CMM_PM_OBJ,   "Note Block",         NULL},                //CMM_BUTTON_NOTEBLOCK
    {mat_b_btn_cull,         0, TILE_TYPE_CULL,      CMM_PM_TILE,  "Cull Marker",        NULL},                //CMM_BUTTON_CULL
    {btn_mech_enemies,       1, OBJECT_TYPE_MECH,    CMM_PM_OBJ,   "Mechanical Enemies", txt_mech_enemies},    //CMM_BUTTON_MECH
    {mat_b_btn_tree,         0, OBJECT_TYPE_TREE,    CMM_PM_OBJ,   "Tree",               txt_bp_tree},         //CMM_BUTTON_TREE
    {mat_b_btn_excla,        0, OBJECT_TYPE_EXCLA,   CMM_PM_OBJ,   "Item Box",           txt_bp_box},          //CMM_BUTTON_EXCLA
    {mat_b_btn_spawn,        0, OBJECT_TYPE_SPAWN,   CMM_PM_OBJ,   "Mario Spawn",        NULL},                //CMM_BUTTON_SPAWN
    {btn_btcm_objects,       1, OBJECT_TYPE_BTCME,   CMM_PM_OBJ,   "BTCM Enemies",       txt_btcm_objects},    //CMM_BUTTON_BTCME
    {mat_b_btn_pipe,         0, OBJECT_TYPE_PIPE,    CMM_PM_OBJ,   "Warp Pipe",          NULL},                //CMM_BUTTON_PIPE
    {mat_b_btn_badge,        0, OBJECT_TYPE_BADGE,   CMM_PM_OBJ,   "Badge",              txt_badges},          //CMM_BUTTON_BADGE
    {mat_b_btn_water,        0, 0,                   CMM_PM_WATER, "Water",              NULL},                //CMM_BUTTON_WATER
    {mat_b_btn_fence,        0, TILE_TYPE_FENCE,     CMM_PM_TILE,  "Fence",              NULL},                //CMM_BUTTON_FENCE
    {btn_mech_bosses,        1, OBJECT_TYPE_BOSS,    CMM_PM_OBJ,   "Bosses",             txt_bp_boss},         //CMM_BUTTON_BOSS
    {mat_b_btn_checker,      0, OBJECT_TYPE_MPLAT,   CMM_PM_OBJ,   "Moving Platform",    txt_platforms},       //CMM_BUTTON_MPLAT
    {mat_b_btn_bball,        0, OBJECT_TYPE_BBALL,   CMM_PM_OBJ,   "Bowling Ball",       NULL},                //CMM_BUTTON_BBALL
    {mat_b_btn_kuppa,        0, OBJECT_TYPE_KTQ,     CMM_PM_OBJ,   "Koopa the Quick",    NULL},                //CMM_BUTTON_KTQ
    {mat_b_btn_sideslope,    0, TILE_TYPE_SSLOPE,    CMM_PM_TILE,  "Vertical Slope",     NULL},                //CMM_BUTTON_SSLOPE
    {mat_b_btn_slabtile,     0, TILE_TYPE_SLAB,      CMM_PM_TILE,  "Slab",               NULL},                //CMM_BUTTON_SLAB
    {btn_timed_objects,      1, OBJECT_TYPE_TC,      CMM_PM_OBJ,   "Timed Boxes",        txt_timed_objects},   //CMM_BUTTON_TC
    {mat_b_btn_heart,        0, OBJECT_TYPE_HEART,   CMM_PM_OBJ,   "Recovery Heart",     NULL},                //CMM_BUTTON_HEART
    {mat_b_btn_cformation,   0, OBJECT_TYPE_COINFORM,CMM_PM_OBJ,   "Coin Formation",     txt_coin_formation},  //CMM_BUTTON_FORMATION
    {mat_b_btn_vslab,        0, TILE_TYPE_SSLAB,     CMM_PM_TILE,  "Vertical Slab",      NULL},                //CMM_BUTTON_VSLAB
    {mat_b_btn_bars,         0, TILE_TYPE_BARS,      CMM_PM_TILE,  "Iron Mesh",          NULL},                //CMM_BUTTON_BARS
    {btn_stone_enemies,      1, OBJECT_TYPE_STONE,   CMM_PM_OBJ,   "Stone Enemies",      txt_stone_enemies},   //CMM_BUTTON_ROCKENEMY
    {mat_b_btn_pole,         0, TILE_TYPE_POLE,      CMM_PM_TILE,  "Pole",               NULL},                //CMM_BUTTON_POLE
    {mat_b_btn_excla,        0, OBJECT_TYPE_EXCLA,   CMM_PM_OBJ,   "Item Box",           txt_bp_vbox},         //CMM_BUTTON_VEXCLA
    {btn_flying_enemies,     1, OBJECT_TYPE_FLYING,  CMM_PM_OBJ,   "Flying Enemies",     txt_flying_enemies},  //CMM_BUTTON_FLYING
    {btn_haunted_enemies,    1, OBJECT_TYPE_HAUNTED, CMM_PM_OBJ,   "Spooky Enemies",     txt_haunted_enemies}, //CMM_BUTTON_HAUNTED
    {btn_snow_enemies,       1, OBJECT_TYPE_SNOWEN,  CMM_PM_OBJ,   "Snowy Enemies",      txt_snow_enemies},    //CMM_BUTTON_SNOWEN
    {mat_b_btn_bbomb,        0, OBJECT_TYPE_MINE,    CMM_PM_OBJ,   "Bowser Mine",        NULL},                //CMM_BUTTON_MINE
    {mat_b_btn_firebar,      0, OBJECT_TYPE_FIRE_SPINNER, CMM_PM_OBJ, "Fire Spinner",    txt_fire_spinner},    //CMM_BUTTON_FIRE_SPINNER

};

char *cmm_costume_string_table[] = {
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

char *cmm_music_album_string_table[] = {
    "Super Mario 64 OST",
    "Beyond the Cursed Mirror OST",
    "ROM Hack Music Ports",
    "Retro 2D Mario Music"
};

char *cmm_music_vanilla_string_table[] = {
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
    "Koopa's Theme",
    "Ultimate Koopa",
    "Inside the Castle Walls",
};

char *cmm_music_btcm_string_table[] = {
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

char *cmm_music_romhack_string_table[] = {
    "Bianco Hills (Super Mario Sunshine)",
    "Sky and Sea (Super Mario Sunshine)",
    "Secret Course (Super Mario Sunshine)",
    "Comet Observatory (Mario Galaxy)",
    "Buoy Base Galaxy (Mario Galaxy)",
    "Battlerock Galaxy (Mario Galaxy)",
    "Ghostly Galaxy (Mario Galaxy)",
    "Purple Comet (Mario Galaxy)",
    "Honeybloom Galaxy (Mario Galaxy 2)",
    "Overworld (New Super Mario Bros.)",

    "Koopa Troopa Beach (Mario Kart 64)",
    "Frappe Snowland (Mario Kart 64)",
    "Rainbow Road (Mario Kart 64)",
    "Bowser's Castle (Mario Kart 64)",
    "Waluigi Pinball (Mario Kart DS)",

    "Mario's Pad (Super Mario RPG)",
    "Nimbus Land (Super Mario RPG)",
    "Forest Maze (Super Mario RPG)",
    "Sunken Ship (Super Mario RPG)",

    "Dry Dry Desert (Paper Mario 64)",
    "Forever Forest (Paper Mario 64)",
    "Riddle Tower (Paper Mario: TTYD)",
    "Rogueport Sewers (Paper Mario: TTYD)",
    "X-Naut Fortress (Paper Mario: TTYD)",
    "Flipside (Super Paper Mario)",
    "Lineland Road (Super Paper Mario)",
    "Sammer Kingdom (Super Paper Mario)",
    "Floro Caverns (Super Paper Mario)",
    "Overthere Stair (Super Paper Mario)",

    "Rainbow Castle (Mario Party)",
    "Behind Yoshi Village (Partners in Time)",
    "Thwomp Caverns (Partners in Time)",
    "Bumpsy Plains (Bowser's Inside Story)",

    "Overworld (Yoshi's Island)",
    "Crystal Caves (Yoshi's Island)",
    "Title (Yoshi's Story)",

    "Lost Woods (Ocarina of Time)",
    "Gerudo Valley (Ocarina of Time)",
    "Stone Tower Temple (Majora's Mask)",
    "Mountain Village (Majora's Mask)",
    "Outset Island (Wind Waker)",
    "Lake Hylia (Twilight Princess)",
    "Twilight Realm (Twilight Princess)",
    "Skyloft (Skyward Sword)",

    "Frantic Factory (Donkey Kong 64)",
    "Hideout Helm (Donkey Kong 64)",
    "Creepy Castle (Donkey Kong 64)",
    "Gloomy Galleon (Donkey Kong 64)",
    "In a Snow-Bound Land (DKC 2)",

    "Bubblegloop Swamp (Banjo-Kazooie)",
    "Freezeezy Peak (Banjo-Kazooie)",
    "Gobi's Valley (Banjo-Kazooie)",

    "Factory Inspection (Kirby 64)",
    "Green Garden (Bomberman 64)",
    "Black Fortress (Bomberman 64)",
    "Windy Hill (Sonic Adventure)",
    "Tropical Resort (Sonic Colors)",
    "Sky Tower (Pokemon Mystery Dungeon)",
    "Band Land (Rayman)",
};

char *cmm_music_retro_string_table[] = {
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

    SEQ_NSMB_OVERWORLD,

    SEQ_KOOPA_BEACH, // mk64 koopa troopa beach
    SEQ_FRAPPE_SNOWLAND,
    SEQ_MK64_RAINBOW_ROAD,
    SEQ_MK64_BOWSERS_CASTLE,
    SEQ_MKDS_WALUIGI_PINBALL,

    SEQ_SMRPG_MARIOS_PAD,             // 0x46
    SEQ_SMRPG_NIMBUS_LAND,
    SEQ_FOREST_MAZE,
    SEQ_SMRPG_SUNKEN_SHIP,            // 0x47

    SEQ_PM_DRY_DESERT,
    SEQ_PM_FOREVER_FOREST,
    SEQ_TTYD_EIGHT_KEY_DOMAIN, // riddle tower
    SEQ_TTYD_ROGUEPORT_SEWERS,
    SEQ_TTYD_XNAUT_FORTRESS,
    SEQ_SPM_FLIPSIDE,
    SEQ_SPM_LINELAND_ROAD,
    SEQ_SAMMER_KINGDOM,
    SEQ_SPM_FLORO_CAVERNS,
    SEQ_SPM_OVERTHERE_STAIR,

    SEQ_MP_RAINBOW_CASTLE,
    SEQ_MLPIT_BEHIND_YOSHI_VILLAGE,
    SEQ_PIT_THWOMP_CAVERNS,
    SEQ_BIS_BUMPSY_PLAINS,
    SEQ_YI_OVERWORLD,
    SEQ_YI_CRYSTAL_CAVES,
    SEQ_YS_TITLE,                     // 0x51

    SEQ_OOT_LOST_WOODS,
    SEQ_OOT_GERUDO_VALLEY,            // 0x52
    SEQ_STONE_TOWER_TEMPLE,
    SEQ_MM_SNOWHEAD,
    SEQ_WW_OUTSET_ISLAND,
    SEQ_TP_LAKE_HYLIA,                // 0x53
    SEQ_TP_TWILIGHT_REALM,
    SEQ_SS_SKYLOFT,

    SEQ_DK64_FRANTIC_FACTORY,
    SEQ_DK64_HIDEOUT_HELM,
    SEQ_DK_CREEPY_CASTLE,
    SEQ_DK64_GLOOMY_GALLEON,
    SEQ_DKC2_SNOWBOUND_LAND,

    SEQ_BK_BUBBLEGLOOP_SWAMP,
    SEQ_BK_FREEZEEZY_PEAKS,
    SEQ_BK_GOBI_VALLEY,

    SEQ_K64_FACTORY_INSPECTION,
    SEQ_BM_GREEN_GARDEN,
    SEQ_BM_BLACK_FORTRESS,
    SEQ_SA_WINDY_HILL,
    SEQ_SC_TROPICAL_RESORT,           // 0x49
    SEQ_PKMN_SKY_TOWER,
    SEQ_RAYMAN_BAND_LAND,

    SEQ_SMB1_OVERWORLD,
    SEQ_SMB_BOWSER_REMIX,             // 0x4B
    SEQ_SMB2_OVERWORLD,
    SEQ_SMB3_OVERWORLD,
    SEQ_SMB3_CASTLE,
    SEQ_SMW_ATHLETIC,                 // 0x4E
    SEQ_SMW_CASTLE,
};

char *cmm_envfx_string_table[] = {
    "None",
    "Ashes",
    "Snow",
    "Rain",
};

//envfx table
u8 cmm_envfx_table[] = {
    ENVFX_MODE_NONE,         // no effects
    ENVFX_SNOW_NORMAL,       // CCM, SL
    ENVFX_SNOW_BLIZZARD,     // unused
    ENVFX_RAIN
};

char *cmm_theme_string_table[] = {
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
    "Minecraft",
};

//cmm themes moved to cursed_mirror_maker.h to work with object df
//example: ice bully appears in snow theme
//impossible to extern enum : (

char *cmm_bg_string_table[] = {
    "Ocean Hills",
    "Cloudy Sky",
    "Firey Sky",
    "Green Cave",
    "Haunted Forest",
    "Ice Mountains",
    "Desert Pyramids",
    "Pink Sky",
};

//skybox table
u8 *cmm_skybox_table[] = {
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
    _bits_skybox_yay0SegmentRomStart,
    _bits_skybox_yay0SegmentRomEnd,
};

extern char *cmm_get_floor_name(s32, char *);
extern char *cmm_get_coinstar_str(s32, char *);
extern char *cmm_get_waterlevel_name(s32, char *);
extern void reload_bg(void);
extern void reload_theme(void);
extern void generate_terrain_gfx(void);

extern void music_category_changed(void);
extern void song_changed(void);

struct cmm_settings_button cmm_settings_general_buttons[] = {
    {"Costume:", &cmm_lopt_costume, cmm_costume_string_table, ARRAY_COUNT(cmm_costume_string_table), NULL, NULL},
    {"Effect:",  &cmm_lopt_envfx,   cmm_envfx_string_table,   ARRAY_COUNT(cmm_envfx_string_table), NULL, NULL},
    {"Skybox:",  &cmm_lopt_bg,      cmm_bg_string_table,      ARRAY_COUNT(cmm_bg_string_table),    NULL, reload_bg},
    {"Coin Star:", &cmm_lopt_coinstar, NULL, 1, cmm_get_coinstar_str, NULL},
};
#define GENERAL_COSTUME_INDEX 0
#define GENERAL_EFFECT_INDEX 1
#define GENERAL_SKYBOX_INDEX 2
#define GENERAL_COINSTAR_INDEX 3

struct cmm_settings_button cmm_settings_general_buttons_vanilla[] = {
    {"Effect:",  &cmm_lopt_envfx,   cmm_envfx_string_table,   ARRAY_COUNT(cmm_envfx_string_table), NULL, NULL},
    {"Skybox:",  &cmm_lopt_bg,      cmm_bg_string_table,      ARRAY_COUNT(cmm_bg_string_table),    NULL, reload_bg},
    {"Coin Star:", &cmm_lopt_coinstar, NULL, 1, cmm_get_coinstar_str, NULL},
};
#define GENERALV_EFFECT_INDEX 0
#define GENERALV_SKYBOX_INDEX 1
#define GENERALV_COINSTAR_INDEX 2

struct cmm_settings_button cmm_settings_terrain_buttons[] = {
    {"Theme:",   &cmm_lopt_theme,   cmm_theme_string_table,   ARRAY_COUNT(cmm_theme_string_table) - 1, NULL, reload_theme},
    {"Floor:",   &cmm_lopt_plane,   NULL,                     0,                     cmm_get_floor_name, generate_terrain_gfx}, // Filled in by code
    {"Water Level:", &cmm_lopt_waterlevel, NULL,               33,               cmm_get_waterlevel_name, generate_terrain_gfx},
};
#define TERRAIN_THEME_INDEX 0
#define TERRAIN_FLOOR_INDEX 1
#define TERRAIN_WATER_INDEX 2

struct cmm_settings_button cmm_settings_music_buttons[] = {
    {"Album:",   &cmm_lopt_seq_album,  cmm_music_album_string_table,  ARRAY_COUNT(cmm_music_album_string_table), NULL, music_category_changed},
    {"Song:", NULL, NULL, 0, NULL, NULL}, // Filled in by code
};
#define MUSIC_ALBUM_INDEX 0
#define MUSIC_SONG_INDEX 1

char *cmm_settings_menu_names[] = {
    "General",
    "Terrain",
    "Music",
    "System",
};

char *cmm_settings_system_buttons[] = {
    "Save & Quit",
    "Play Level",
    "Level Size:",
    "Apply Size Change (Dangerous!)",
};

u8 cmm_settings_menu_lengths[] = {
    ARRAY_COUNT(cmm_settings_general_buttons),
    ARRAY_COUNT(cmm_settings_terrain_buttons),
    ARRAY_COUNT(cmm_settings_music_buttons),
    ARRAY_COUNT(cmm_settings_system_buttons),
};

void draw_cmm_settings_general(f32,f32);
void draw_cmm_settings_general_vanilla(f32,f32);
void draw_cmm_settings_terrain(f32,f32);
void draw_cmm_settings_music(f32,f32);
void draw_cmm_settings_system(f32,f32);

void (*cmm_settings_menus[])(f32, f32) = {
    draw_cmm_settings_general,
    draw_cmm_settings_terrain,
    draw_cmm_settings_music,
    draw_cmm_settings_system,
};

// These get copied over to the above array
struct cmm_settings_button cmm_settings_music_albums[] = {
    {"Song:",  &cmm_lopt_seq_song, cmm_music_vanilla_string_table, ARRAY_COUNT(cmm_music_vanilla_string_table), NULL, song_changed},
    {"Song:",  &cmm_lopt_seq_song, cmm_music_btcm_string_table, ARRAY_COUNT(cmm_music_btcm_string_table), NULL, song_changed},
    {"Song:",  &cmm_lopt_seq_song, cmm_music_romhack_string_table, ARRAY_COUNT(cmm_music_romhack_string_table), NULL, song_changed},
    {"Song:",  &cmm_lopt_seq_song, cmm_music_retro_string_table, ARRAY_COUNT(cmm_music_retro_string_table), NULL, song_changed},
};

struct cmm_settings_button cmm_settings_backtomainmenu[] = {
};

char *cmm_gamemode_string_table[] = {
    "Vanilla SM64",
    "Cursed Mirror",
};

char *cmm_levelsize_string_table[] = {
    "Small (32)",
    "Medium (48)",
    "Large (64)",
};

char *cmm_template_string_table[] = {
    "Grassy",
    "Desert",
    "Lava",
    "Underwater",
    "Snowy",
};

struct cmm_template {
    u8 music[2]; // vanilla, btcm
    u8 envfx;
    u8 bg;
    u8 theme;
    u8 plane;

    u8 spawnHeight;
    u8 platform;
};

struct cmm_template cmm_templates[] = {
    {{0, 15}, 0, 0, 0, 1,     2, FALSE},   // Grassy - BoB, Floating Farm
    {{4, 46}, 0, 6, 1, 1,     2, FALSE},   // Desert - LLL, Dry Dry Desert
    {{4, 14}, 1, 2, 2, 2,     2, TRUE},    // Lava -   LLL, Red-Hot Reservoir
    {{2, 28}, 0, 0, 8, 1,     2, FALSE},   // Water -  DDD, Sky and Sea
    {{5, 38}, 2, 5, 6, 1,     2, FALSE},   // Snowy -  CCM, Frappe Snowland
};

struct cmm_settings_button cmm_mode_settings_buttons[] = {
    {"Mode:", &cmm_lopt_game, cmm_gamemode_string_table, ARRAY_COUNT(cmm_gamemode_string_table), NULL, NULL},
    {"Size:", &cmm_lopt_size, cmm_levelsize_string_table, ARRAY_COUNT(cmm_levelsize_string_table), NULL, NULL},
    {"Template:", &cmm_lopt_template, cmm_template_string_table, ARRAY_COUNT(cmm_template_string_table), NULL, NULL},
};

#define SETTINGS_SIZE ARRAY_COUNT(cmm_settings_general_buttons)

char *cmm_tips[] = {
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
    "Tip: Pressing every C-button while on a certain menu\n   might reward you with a little surprise...",
    "Tip: Transparent materials such as water, flames or ice\n   can look strange when layered together, so watch out.",
    "Tip: Using the Cursed Mirror gamemode will let you use a\n   bunch of new enemies and collectible badges!",
// BTCM
    "Tip: The Double Time badge extends the timer of\n   hidden corkboxes and blue coin switches!",
    "Tip: The Star Radar badge will let the player know\n   what direction the nearest star is in.",
    "Tip: Badges that the player collects will be kept\n   as permanent collectibles even after death.",
    "Tip: You can use the Burden badges as a punishment\n   when touched, or an optional challenge!",
    "Tip: Green Coins heal the player for 4 HP when collected,\n   or fully with the Heal Plus badge.",
};
#define NUM_BTCM_TIPS 5

