f32 cmm_camera_zoom_table[][2] = {
    {900.0f,50.0f},
    {900.0f,400.0f},
    {1500.0f,800.0f},
    {2000.0f,900.0f},
    {2100.0f,1500.0f},
};

// lookup table for rotating blocks
u8 cmm_rotated_dirs[4][6] = {
    {CMM_DIRECTION_UP, CMM_DIRECTION_DOWN, CMM_DIRECTION_POS_X, CMM_DIRECTION_NEG_X, CMM_DIRECTION_POS_Z, CMM_DIRECTION_NEG_Z},
    {CMM_DIRECTION_UP, CMM_DIRECTION_DOWN, CMM_DIRECTION_NEG_Z, CMM_DIRECTION_POS_Z, CMM_DIRECTION_POS_X, CMM_DIRECTION_NEG_X},
    {CMM_DIRECTION_UP, CMM_DIRECTION_DOWN, CMM_DIRECTION_NEG_X, CMM_DIRECTION_POS_X, CMM_DIRECTION_NEG_Z, CMM_DIRECTION_POS_Z},
    {CMM_DIRECTION_UP, CMM_DIRECTION_DOWN, CMM_DIRECTION_POS_Z, CMM_DIRECTION_NEG_Z, CMM_DIRECTION_NEG_X, CMM_DIRECTION_POS_X},
};

#define ROTATE_DIRECTION(dir, rot) (cmm_rotated_dirs[rot][dir])

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
    NULL,                    // TILE_TYPE_SSLAB
    NULL,                    //TILE_TYPE_CULL
    &cmm_terrain_fullblock,  //TILE_TYPE_TROLL
    NULL,                    //TILE_TYPE_FENCE
    NULL,                    // TILE_TYPE_WATER
};

//BEHAVIOR  //Y-OFF //MODEL ID //BILLB //SCALE  //ANIMATION PTR //DISP.FUNC //SOUND
struct cmm_object_info cmm_object_type_star = {
    bhvStar, TILE_SIZE/2, MODEL_STAR, FALSE, 1.0f, NULL, &df_star, SOUND_MENU_STAR_SOUND | SOUND_VIBRATO,
};
struct cmm_object_info cmm_object_type_goomba = {
    bhvGoomba, 0, MODEL_GOOMBA, FALSE, 1.5f, goomba_seg8_anims_0801DA4C, NULL, SOUND_OBJ_GOOMBA_ALERT,
};
struct cmm_object_info cmm_object_type_yellowcoin = {
    bhvYellowCoin, 0, MODEL_YELLOW_COIN, TRUE, 1.0f, NULL, NULL, SOUND_GENERAL_COIN | SOUND_VIBRATO,
};
struct cmm_object_info cmm_object_type_greencoin = {
    bhvGreenCoin, 0, 0xEF, TRUE, 1.0f, NULL, NULL, SOUND_GENERAL_COIN | SOUND_VIBRATO,
};
struct cmm_object_info cmm_object_type_redcoin = {
    bhvRedCoin, 0, MODEL_RED_COIN, TRUE, 1.0f, NULL, NULL, SOUND_MENU_COLLECT_RED_COIN,
};
struct cmm_object_info cmm_object_type_bluecoin = {
    bhvHiddenBlueCoin, 0, MODEL_BLUE_COIN, TRUE, 1.0f, NULL, NULL, SOUND_GENERAL_COIN | SOUND_VIBRATO,
};
struct cmm_object_info cmm_object_type_bluecoinswitch = {
    bhvBlueCoinSwitch, 0, MODEL_BLUE_COIN_SWITCH, FALSE, 3.0f, NULL, NULL, SOUND_GENERAL2_PURPLE_SWITCH
};
struct cmm_object_info cmm_object_type_redcoinstar = {
    bhvHiddenRedCoinStar, TILE_SIZE/2, MODEL_TRANSPARENT_STAR, FALSE, 1.0f, NULL, &df_reds_marker, SOUND_MENU_STAR_SOUND | SOUND_VIBRATO,
};
struct cmm_object_info cmm_object_type_noteblock = {
    bhvNoteblock, TILE_SIZE/2, MODEL_NOTEBLOCK, FALSE, 1.0f, NULL, NULL, SOUND_GENERAL_CRAZY_BOX_BOING_SLOW,
};
struct cmm_object_info cmm_object_type_podoboo = {
    bhvPodoboo, TILE_SIZE/2, MODEL_PODOBOO, FALSE, 1.0f, NULL, NULL, SOUND_OBJ_FLAME_BLOWN | SOUND_VIBRATO,
};
struct cmm_object_info cmm_object_type_rex = {
    bhvRex, 0, 0xE1, FALSE, 1.5f, Rex_anims, NULL, SOUND_OBJ_GOOMBA_ALERT,
};
struct cmm_object_info cmm_object_type_smallbully = {
    bhvSmallBully, 0, MODEL_BULLY, FALSE, 1.0f, bully_seg5_anims_0500470C, NULL, SOUND_OBJ2_SMALL_BULLY_ATTACKED,
};
struct cmm_object_info cmm_object_type_bobomb = {
    bhvBobomb, 0, MODEL_BLACK_BOBOMB, FALSE, 1.0f, bobomb_seg8_anims_0802396C, NULL, SOUND_OBJ_BOBOMB_WALK | SOUND_VIBRATO,
};
struct cmm_object_info cmm_object_type_tree = {
    bhvTree, 0, MODEL_MAKER_TREE_1, TRUE, 1.0f, NULL, &df_tree, SOUND_ACTION_CLIMB_UP_TREE | SOUND_VIBRATO,
};
struct cmm_object_info cmm_object_type_exclamationbox = {
    bhvExclamationBox, TILE_SIZE/2, MODEL_EXCLAMATION_BOX, FALSE, 2.0f, NULL, &df_exbox, SOUND_GENERAL_BREAK_BOX,
};
struct cmm_object_info cmm_object_type_chuckya = {
    bhvChuckya, 0, MODEL_CHUCKYA, FALSE, 2.0f, chuckya_seg8_anims_0800C070, &df_chuckya, SOUND_OBJ_CHUCKYA_DEATH,
};
struct cmm_object_info cmm_object_type_spawn = {
    bhvSpawn, TILE_SIZE/2, MODEL_SPAWN, TRUE, 1.0f, NULL, NULL, SOUND_MENU_STAR_SOUND_LETS_A_GO,
};
struct cmm_object_info cmm_object_type_phantasm = {
    bhvPhantasm, 0, MODEL_MARIO, FALSE, 1.0f, &evil_mario_anims[2], NULL, SOUND_ACTION_METAL_STEP | SOUND_VIBRATO
};
struct cmm_object_info cmm_object_type_warppipe = {
    bhvWarpPipe, 0, MODEL_MAKER_PIPE, FALSE, 1.0f, NULL, NULL, SOUND_MENU_ENTER_PIPE | SOUND_VIBRATO,
};
struct cmm_object_info cmm_object_type_badge = {
    bhvBadge, TILE_SIZE/2, MODEL_BADGE, TRUE, 5.0f, NULL, NULL, SOUND_GENERAL2_PURPLE_SWITCH,
};

struct cmm_object_info cmm_object_type_bosses[] = {
    {bhvBoss, 0, MODEL_KINGBOMB_MAKER, FALSE, 1.0f, king_bobomb_seg5_anims_0500FE30, &df_kingbomb, SOUND_OBJ_KING_BOBOMB},
    {bhvWhompKingBoss, 0, MODEL_WHOMP_MAKER, FALSE, 2.f, whomp_seg6_anims_06020A04, NULL, SOUND_OBJ_WHOMP},
};

struct cmm_object_info cmm_object_type_platform = {
    bhvPlatformOnTrack, TILE_SIZE/2, MODEL_CHECKERBOARD_PLATFORM, FALSE, 1.0f, NULL, NULL, SOUND_ENV_ELEVATOR1 | SOUND_VIBRATO,
};
struct cmm_object_info cmm_object_type_bowlingball = {
    bhvBobBowlingBallSpawner, TILE_SIZE/2, MODEL_BOWLING_BALL, TRUE, 1.0f, NULL, NULL, SOUND_GENERAL_QUIET_POUND1 | SOUND_VIBRATO,
};
struct cmm_object_info cmm_object_type_ktq = {
    bhvKoopa, 0, MODEL_KOOPA_WITH_SHELL, FALSE, 3.0f, koopa_seg6_anims_06011364, &df_koopa, SOUND_OBJ_KOOPA_TALK,
};

struct cmm_object_place cmm_object_place_types[] = {
    {&cmm_object_type_star, FALSE, TRUE, FALSE, 0},
    {&cmm_object_type_goomba, FALSE, FALSE, FALSE, 0},
    {&cmm_object_type_yellowcoin, FALSE, FALSE, FALSE, 0},
    {&cmm_object_type_greencoin, FALSE, FALSE, FALSE, 0},
    {&cmm_object_type_redcoin, FALSE, FALSE, FALSE, 0},
    {&cmm_object_type_bluecoin, FALSE, FALSE, FALSE, 0},
    {&cmm_object_type_bluecoinswitch, FALSE, FALSE, FALSE, 0},
    {&cmm_object_type_redcoinstar, FALSE, TRUE, FALSE, 0},
    {&cmm_object_type_noteblock, FALSE, FALSE, FALSE, 0},
    {&cmm_object_type_podoboo, FALSE, FALSE, FALSE, 0},
    {&cmm_object_type_rex, FALSE, FALSE, FALSE, 0},
    {&cmm_object_type_smallbully, FALSE, FALSE, FALSE, 0},
    {&cmm_object_type_bobomb, FALSE, FALSE, FALSE, 0},
    {&cmm_object_type_tree, FALSE, FALSE, FALSE, 4},
    {&cmm_object_type_exclamationbox, FALSE, FALSE, FALSE, 8},
    {&cmm_object_type_chuckya, FALSE, FALSE, FALSE, 0},
    {&cmm_object_type_spawn, FALSE, FALSE, FALSE, 0},
    {&cmm_object_type_phantasm, FALSE, FALSE, FALSE, 0},
    {&cmm_object_type_warppipe, FALSE, FALSE, FALSE, 0},
    {&cmm_object_type_badge, FALSE, FALSE, FALSE, 23},
    {&cmm_object_type_bosses, FALSE, TRUE, TRUE, 2},
    {&cmm_object_type_platform, TRUE, FALSE, FALSE, 0},
    {&cmm_object_type_bowlingball, TRUE, FALSE, FALSE, 0},
    {&cmm_object_type_ktq, TRUE, TRUE, FALSE, 0},
};

enum cmm_materials {
    CMM_MAT_NONE,
    // Generic
    CMM_MAT_DIRT,
    CMM_MAT_GRASS,
    CMM_MAT_BRICKS,
    CMM_MAT_STONE,
    CMM_MAT_COBBLESTONE,
    CMM_MAT_TILES,
    CMM_MAT_TILESBRICKS,
    CMM_MAT_ROOF,
    CMM_MAT_WOOD,
    CMM_MAT_SANDDIRT,
    CMM_MAT_SAND,
    CMM_MAT_SNOWDIRT,
    CMM_MAT_SNOW,
    CMM_MAT_LAVA,
    CMM_MAT_QUICKSAND,
    // Desert
    CMM_MAT_DESERT_BRICKS,
    CMM_MAT_DESERT_STONE,
    CMM_MAT_DESERT_TILES,
    CMM_MAT_DESERT_BLOCK,
    CMM_MAT_DESERT_TILES2,
    CMM_MAT_DESERT_SLOWSAND,
    // Red Hot Reservoir
    CMM_MAT_RHR_OBSIDIAN,
    CMM_MAT_RHR_STONE,
    CMM_MAT_RHR_BRICK,
    CMM_MAT_RHR_BASALT,
    CMM_MAT_RHR_TILES,
    CMM_MAT_RHR_BLOCK,
    CMM_MAT_RHR_WOOD,
    CMM_MAT_RHR_PILLAR,
    CMM_MAT_RHR_MESH,
    CMM_MAT_SERVER_ACID,
    // Hazy Maze Cave
    CMM_MAT_HMC_GRASS,
    CMM_MAT_HMC_DIRT,
    CMM_MAT_HMC_BRICK,
    CMM_MAT_HMC_STONE,
    CMM_MAT_HMC_MAZEWALL,
    CMM_MAT_HMC_MAZEFLOOR,
    CMM_MAT_HMC_LIGHT,
    CMM_MAT_HMC_LAKEGRASS,
    CMM_MAT_HMC_MESH,
    // Castle
    CMM_MAT_C_TILES,
    CMM_MAT_C_WOOD,
    CMM_MAT_C_BRICK,
    CMM_MAT_C_STONETOP,
    CMM_MAT_C_STONESIDE,
    CMM_MAT_C_CARPET,
    CMM_MAT_C_ROOF,
    CMM_MAT_C_WALL,
    CMM_MAT_C_PILLAR,
    CMM_MAT_C_BASEMENTWALL,
    CMM_MAT_C_OUTSIDEBRICK,
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
    CMM_MAT_BBH_BRICKS,
    CMM_MAT_BBH_HAUNTED_PLANKS,
    CMM_MAT_BBH_WOOD_FLOOR,
    CMM_MAT_BBH_WOOD_WALL,
    CMM_MAT_BBH_ROOF,
    CMM_MAT_BBH_STONE,
    CMM_MAT_BBH_STONE_PATTERN,
    CMM_MAT_BBH_PILLAR,
    CMM_MAT_BBH_WINDOW,
    // JRB
    CMM_MAT_JRB_SAND,
    CMM_MAT_JRB_STONE,
    CMM_MAT_JRB_METAL,
    CMM_MAT_JRB_UNDERWATER,
    CMM_MAT_JRB_SHIPSIDE,
    CMM_MAT_JRB_SHIPTOP,
    CMM_MAT_JRB_WOOD,
    CMM_MAT_JRB_METALSIDE,
    CMM_MAT_JRB_WALL,
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
};

struct cmm_material cmm_mat_table[] = {
    {0,0,0}, // CMM_MAT_NONE
    // Generic
    {mat_maker_MakerDirt,       0, SURFACE_NOT_SLIPPERY},      // CMM_MAT_DIRT
    {mat_maker_MakerGrass,      0, SURFACE_GRASS},             // CMM_MAT_GRASS
    {mat_maker_MakerBricks,     0, SURFACE_DEFAULT},           // CMM_MAT_BRICKS
    {mat_maker_MakerStoneSide,  0, SURFACE_NOT_SLIPPERY},      // CMM_MAT_STONE
    {mat_maker_MakerStone,      0, SURFACE_NOT_SLIPPERY},      // CMM_MAT_COBBLESTONE
    {mat_maker_MakerTiles,      0, SURFACE_NOT_SLIPPERY},      // CMM_MAT_TILES
    {mat_maker_MakerTileBricks, 0, SURFACE_DEFAULT},           // CMM_MAT_TILESBRICKS
    {mat_maker_MakerRoof,       0, SURFACE_NOT_SLIPPERY},      // CMM_MAT_ROOF
    {mat_maker_MakerWood,       0, SURFACE_CREAKWOOD},         // CMM_MAT_WOOD
    {mat_maker_MakerSandDirt,   0, SURFACE_NOT_SLIPPERY},      // CMM_MAT_SANDDIRT
    {mat_maker_MakerSand,       0, SURFACE_SAND},              // CMM_MAT_SAND
    {mat_maker_MakerSnowDirt,   0, SURFACE_NOT_SLIPPERY},      // CMM_MAT_SNOWDIRT
    {mat_maker_MakerSnow,       0, SURFACE_SNOW},              // CMM_MAT_SNOW
    {mat_maker_MakerLava,       0, SURFACE_BURNING},           // CMM_MAT_LAVA
    {mat_maker_MakerQuicksand,  0, SURFACE_INSTANT_QUICKSAND}, // CMM_MAT_QUICKSAND
    // Desert
    {mat_maker_MakerDBrick,      0, SURFACE_DEFAULT},        // CMM_MAT_DESERT_BRICKS
    {mat_maker_MakerDStone,      0, SURFACE_NOT_SLIPPERY},   // CMM_MAT_DESERT_STONE
    {mat_maker_MakerDTiles,      0, SURFACE_NOT_SLIPPERY},   // CMM_MAT_DESERT_TILES
    {mat_maker_MakerDStoneBlock, 0, SURFACE_NOT_SLIPPERY},   // CMM_MAT_DESERT_BLOCK
    {mat_maker_MakerDTiles2,     0, SURFACE_NOT_SLIPPERY},   // CMM_MAT_DESERT_TILES2
    {mat_maker_MakerSlowsand,    0, SURFACE_DEEP_QUICKSAND}, // CMM_MAT_DESERT_SLOWSAND
    // Red Hot Reservoir
    {mat_maker_MakerRHRObsidian,     0,          SURFACE_NOT_SLIPPERY},     // CMM_MAT_RHR_OBSIDIAN
    {mat_maker_MakerRHRStone,        0,          SURFACE_NOT_SLIPPERY},     // CMM_MAT_RHR_STONE
    {mat_maker_MakerRHRBrick,        0,          SURFACE_DEFAULT},          // CMM_MAT_RHR_BRICK
    {mat_maker_MakerRHRBasalt,       0,          SURFACE_NOT_SLIPPERY},     // CMM_MAT_RHR_BASALT
    {mat_maker_MakerRHRTiles,        0,          SURFACE_NOT_SLIPPERY},     // CMM_MAT_RHR_TILES
    {mat_maker_MakerRHRPattern,      0,          SURFACE_DEFAULT},          // CMM_MAT_RHR_BLOCK
    {mat_maker_MakerRHRWood,         0,          SURFACE_CREAKWOOD},        // CMM_MAT_RHR_WOOD
    {mat_maker_MakerRHRPillar,       0,          SURFACE_DEFAULT},          // CMM_MAT_RHR_PILLAR
    {mat_maker_MakerRHRGrate_layer1, MAT_CUTOUT, SURFACE_VANISH_CAP_WALLS}, // CMM_MAT_RHR_MESH
    {mat_maker_MakerServerAcid,      0,          SURFACE_BURNING},          // CMM_MAT_SERVER_ACID
    // Hazy Maze Cave
    {mat_maker_MakerHGrass,          0,          SURFACE_GRASS},            // CMM_MAT_HMC_GRASS
    {mat_maker_MakerHDirt,           0,          SURFACE_NOT_SLIPPERY},     // CMM_MAT_HMC_DIRT
    {mat_maker_MakerHBrick,          0,          SURFACE_DEFAULT},          // CMM_MAT_HMC_BRICK
    {mat_maker_MakerHStone,          0,          SURFACE_NOT_SLIPPERY},     // CMM_MAT_HMC_STONE
    {mat_maker_MakerHMazewall,       0,          SURFACE_DEFAULT},          // CMM_MAT_HMC_MAZEWALL
    {mat_maker_MakerHMazefloor,      0,          SURFACE_NOT_SLIPPERY},     // CMM_MAT_HMC_MAZEFLOOR
    {mat_maker_MakerHLight,          0,          SURFACE_DEFAULT},          // CMM_MAT_HMC_LIGHT
    {mat_maker_MakerHLakewall,       0,          SURFACE_NOT_SLIPPERY},     // CMM_MAT_HMC_LAKEGRASS
    {mat_maker_MakerHMesh_layer1,    MAT_CUTOUT, SURFACE_VANISH_CAP_WALLS}, // CMM_MAT_HMC_MESH
    // Castle
    {mat_maker_MakerCTile,           0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_C_TILES
    {mat_maker_MakerCWood,           0, SURFACE_DEFAULT},      // CMM_MAT_C_WOOD
    {mat_maker_MakerCBrick,          0, SURFACE_DEFAULT},      // CMM_MAT_C_BRICK
    {mat_maker_MakerCStone,          0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_C_STONETOP
    {mat_maker_MakerCStoneSide,      0, SURFACE_DEFAULT},      // CMM_MAT_C_STONESIDE
    {mat_maker_MakerCCarpet,         0, SURFACE_GRASS},        // CMM_MAT_C_CARPET
    {mat_maker_MakerCRoof,           0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_C_ROOF
    {mat_maker_MakerCWall,           0, SURFACE_DEFAULT},      // CMM_MAT_C_WALL
    {mat_maker_MakerCPillar,         0, SURFACE_DEFAULT},      // CMM_MAT_C_PILLAR
    {mat_maker_MakerCBasementWall,   0, SURFACE_DEFAULT},      // CMM_MAT_C_BASEMENTWALL
    {mat_maker_MakerCOutsideBricks,  0, SURFACE_DEFAULT},      // CMM_MAT_C_OUTSIDE_BRICK
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
    {mat_maker_MakerBBHBricks,       0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_BBH_BRICKS
    {mat_maker_MakerBBHHauntedPlanks,0, SURFACE_CREAKWOOD},    // CMM_MAT_BBH_HAUNTED_PLANKS
    {mat_maker_MakerBBHWoodFloor,    0, SURFACE_CREAKWOOD},    // CMM_MAT_BBH_WOOD_FLOOR
    {mat_maker_MakerBBHWoodWall,     0, SURFACE_CREAKWOOD},    // CMM_MAT_BBH_WOOD_WALL
    {mat_maker_MakerBBHRoof,         0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_BBH_ROOF
    {mat_maker_MakerBBHWall,         0, SURFACE_DEFAULT},      // CMM_MAT_BBH_STONE
    {mat_maker_MakerBBHStonePattern, 0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_BBH_STONE_PATTERN
    {mat_maker_MakerBBHPillar,       0, SURFACE_DEFAULT},      // CMM_MAT_BBH_PILLAR
    {mat_maker_MakerBBHWindow,       0, SURFACE_DEFAULT},      // CMM_MAT_BBH_WINDOW
    // JRB
    {mat_maker_MakerJRBSand,         0, SURFACE_SAND},         // CMM_MAT_JRB_SAND
    {mat_maker_MakerJRBStone,        0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_JRB_STONE
    {mat_maker_MakerJRBMetal,        0, SURFACE_DEFAULT},      // CMM_MAT_JRB_METAL
    {mat_maker_MakerJRBUnderwater,   0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_JRB_UNDERWATER
    {mat_maker_MakerJRBShipSide,     0, SURFACE_CREAKWOOD},    // CMM_MAT_JRB_SHIPSIDE
    {mat_maker_MakerJRBShipTop,      0, SURFACE_CREAKWOOD},    // CMM_MAT_JRB_SHIPTOP
    {mat_maker_MakerJRBWood,         0, SURFACE_CREAKWOOD},    // CMM_MAT_JRB_WOOD
    {mat_maker_MakerJRBMetalSide,    0, SURFACE_DEFAULT},      // CMM_MAT_JRB_METALSIDE
    {mat_maker_MakerJRBWall,         0, SURFACE_NOT_SLIPPERY}, // CMM_MAT_JRB_WALL
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
};

struct cmm_topmaterial cmm_topmat_table[] = {
    {CMM_MAT_GRASS,         mat_maker_MakerGrassSide_layer1},     // CMM_MAT_GRASS
    {CMM_MAT_SAND,          mat_maker_MakerSandSide_layer1},      // CMM_MAT_SAND
    {CMM_MAT_SNOW,          mat_maker_MakerSnowSide_layer1},      // CMM_MAT_SNOW
    {CMM_MAT_HMC_GRASS,     mat_maker_MakerHGrassSide_layer1},    // CMM_MAT_HMC_GRASS
    {CMM_MAT_BBH_METAL,     mat_maker_MakerBBHMetalSide_layer1},  // CMM_MAT_BBH_METAL
    {CMM_MAT_BBH_STONE,     mat_maker_MakerBBHMetalSide_layer1},  // CMM_MAT_BBH_STONE
    {CMM_MAT_RETRO_TREETOP, mat_maker_MakerRetroTreeSide_layer1}, // CMM_MAT_RETRO_TREETOP
};

s8 cmm_terrain_floors_generic[] = {0, 8, 9, 2, 3, 5, 6, 7}; // grass, lava, quicksand, stone, tiles, wood, sand, snow
s8 cmm_terrain_floors_desert[] = {0, 8, 9, 2, 3, 6, 7}; // sand, lava, quicksand, stone, tiles, desert tiles, grass
s8 cmm_terrain_floors_lava[] = {0, 8, 9, 2, 3}; // stone, lava, quicksand, basalt, tiles
s8 cmm_terrain_floors_cave[] = {0, 8, 9, 2, 4}; // grass, lava, quicksand, stone, maze floor
s8 cmm_terrain_floors_castle[] = {0, 8, 9, 3}; // tiling, lava, quicksand, carpet
s8 cmm_terrain_floors_virtuaplex[] = {0, 8, 9, 1, 2, 3, 7}; // block, lava, void, tiling, grass, blue tiling, snowy block
s8 cmm_terrain_floors_bbh[] = {3, 8, 0, 6}; // metal, lava, stone, wood
s8 cmm_terrain_floors_jrb[] = {0, 2, 9, 6, 5}; // sand, stone, quicksand, metal, wood
s8 cmm_terrain_floors_retro[] = {0, 8, 4, 9}; // ground, lava, blue ground, underwater tile

enum cmm_fences {
    CMM_FENCE_NORMAL,
    CMM_FENCE_DESERT,
    CMM_FENCE_RHR,
    CMM_FENCE_HMC,
    CMM_FENCE_CASTLE,
    CMM_FENCE_VIRTUAPLEX,
    CMM_FENCE_BBH,
    CMM_FENCE_JRB,
    CMM_FENCE_RETRO,
};

Gfx *cmm_fence_texs[] = {
    mat_maker_MakerFence_layer1,
    mat_maker_MakerDMesh_layer1,
    mat_maker_MakerRHRFence_layer1,
    mat_maker_MakerHFence_layer1,
    mat_maker_MakerCFence_layer1,
    mat_maker_MakerVPFence_layer1,
    mat_maker_MakerBBHFence_layer1,
    mat_maker_MakerJRBFence_layer1,
    mat_maker_MakerRetroFence_layer1,
};

enum cmm_water {
    CMM_WATER_DEFAULT,
    CMM_WATER_GREEN,
    CMM_WATER_RETRO,
};

Gfx *cmm_water_texs[] = {
    mat_maker_MakerWater,
    mat_maker_MakerGreenWater,
    mat_maker_MakerRetroWater,
};

struct cmm_theme cmm_theme_table[] = {
    // GENERIC
    {
        {
            {CMM_MAT_DIRT,        CMM_MAT_GRASS, "Grass"},
            {CMM_MAT_BRICKS,      0,                "Bricks"},
            {CMM_MAT_COBBLESTONE, CMM_MAT_STONE, "Stone"},
            {CMM_MAT_TILESBRICKS, CMM_MAT_TILES, "Tiling"},
            {CMM_MAT_ROOF,        0,                "Roof"},
            {CMM_MAT_WOOD,        0,                "Wood"},
            {CMM_MAT_SANDDIRT,    CMM_MAT_SAND,  "Sand"},
            {CMM_MAT_SNOWDIRT,    CMM_MAT_SNOW,  "Snow"},
            {CMM_MAT_LAVA,        0,                "Lava"},
            {CMM_MAT_QUICKSAND,   0,                "Quicksand"},
        },
        ARRAY_COUNT(cmm_terrain_floors_generic), cmm_terrain_floors_generic,
        CMM_FENCE_NORMAL, CMM_WATER_DEFAULT
    },
    // DESERT
    {
        {
            {CMM_MAT_SANDDIRT,        CMM_MAT_SAND,          "Sand"},
            {CMM_MAT_DESERT_BRICKS,   0,                        "Bricks"},
            {CMM_MAT_DESERT_STONE,    0,                        "Stone"},
            {CMM_MAT_DESERT_TILES,    0,                        "Desert Tiling"},
            {CMM_MAT_DESERT_BLOCK,    0,                        "Stone Block"},
            {CMM_MAT_DESERT_SLOWSAND, 0,                        "Slow Quicksand"},
            {CMM_MAT_DESERT_BRICKS,   CMM_MAT_DESERT_TILES2, "Desert Plating"},
            {CMM_MAT_DIRT,            CMM_MAT_GRASS,         "Grass"},
            {CMM_MAT_LAVA,            0,                        "Lava"},
            {CMM_MAT_QUICKSAND,       0,                        "Quicksand"},
        },
        ARRAY_COUNT(cmm_terrain_floors_desert), cmm_terrain_floors_desert,
        CMM_FENCE_DESERT, CMM_WATER_GREEN
    },
    // LAVA
    {
        {
            {CMM_MAT_RHR_STONE,   CMM_MAT_RHR_OBSIDIAN, "Stone"},
            {CMM_MAT_RHR_BRICK,   CMM_MAT_RHR_OBSIDIAN, "Bricks"},
            {CMM_MAT_RHR_BASALT,  0,                       "Basalt"},
            {CMM_MAT_RHR_TILES,   0,                       "Tiling"},
            {CMM_MAT_RHR_BLOCK,   0,                       "Stone Block"},
            {CMM_MAT_RHR_WOOD,    0,                       "Wood"},
            {CMM_MAT_RHR_PILLAR,  CMM_MAT_RHR_TILES,    "Pillar"},
            {CMM_MAT_RHR_MESH,    0,                       "Mesh"},
            {CMM_MAT_LAVA,        0,                       "Lava"},
            {CMM_MAT_SERVER_ACID, 0,                       "Server Acid"},
        },
        ARRAY_COUNT(cmm_terrain_floors_lava), cmm_terrain_floors_lava,
        CMM_FENCE_RHR, CMM_WATER_DEFAULT
    },
    // CAVE
    {
        {
            {CMM_MAT_HMC_DIRT,      CMM_MAT_HMC_GRASS, "Grass"},
            {CMM_MAT_HMC_BRICK,     0,                    "Bricks"},
            {CMM_MAT_HMC_STONE,     0,                    "Stone"},
            {CMM_MAT_HMC_MAZEWALL,  0,                    "Maze Wall"},
            {CMM_MAT_HMC_MAZEFLOOR, 0,                    "Maze Floor"},
            {CMM_MAT_HMC_LIGHT,     0,                    "Light"},
            {CMM_MAT_HMC_LAKEGRASS, CMM_MAT_HMC_GRASS, "Cave Wall"},
            {CMM_MAT_HMC_MESH,      0,                    "Mesh"},
            {CMM_MAT_LAVA,          0,                    "Lava"},
            {CMM_MAT_QUICKSAND,     0,                    "Quicksand"},
        },
        ARRAY_COUNT(cmm_terrain_floors_cave), cmm_terrain_floors_cave,
        CMM_FENCE_HMC, CMM_WATER_GREEN
    },
    // CASTLE
    {
        {
            {CMM_MAT_C_WOOD,         CMM_MAT_C_TILES,  "Tiling"},
            {CMM_MAT_C_BRICK,        CMM_MAT_C_TILES,  "Tiling (Bricks)"},
            {CMM_MAT_C_STONESIDE,    CMM_MAT_C_STONETOP,  "Tiling (Stone)"},
            {CMM_MAT_C_WOOD,         CMM_MAT_C_CARPET, "Carpet"},
            {CMM_MAT_C_ROOF,         0,                   "Roof"},
            {CMM_MAT_C_WALL,         0,                   "Castle Wall"},
            {CMM_MAT_C_PILLAR,       CMM_MAT_C_STONETOP,  "Pillar"},
            {CMM_MAT_C_BASEMENTWALL, 0,                   "Basement Wall"},
            {CMM_MAT_LAVA,           0,                   "Lava"},
            {CMM_MAT_C_OUTSIDEBRICK, 0,                   "Castle Bricks"},
        },
        ARRAY_COUNT(cmm_terrain_floors_castle), cmm_terrain_floors_castle,
        CMM_FENCE_CASTLE, CMM_WATER_DEFAULT
    },
    // VIRTUAPLEX
    {
        {
            {CMM_MAT_VP_BLOCK,      0,                       "Block"},
            {CMM_MAT_VP_TILES,      0,                       "Tiling"},
            {CMM_MAT_DIRT,          CMM_MAT_GRASS,        "Grass"},
            {CMM_MAT_VP_TILES,      CMM_MAT_VP_BLUETILES, "Blue Tiling"},
            {CMM_MAT_VP_RUSTYBLOCK, 0,                       "Rusty Block"},
            {CMM_MAT_VP_SCREEN,     0,                       "Screen"},
            {CMM_MAT_VP_CAUTION,    0,                       "Hazard Stripes"},
            {CMM_MAT_VP_BLOCK,      CMM_MAT_SNOW,         "Snowy Block"},
            {CMM_MAT_LAVA,          0,                       "Lava"},
            {CMM_MAT_VP_VOID,       0,                       "Void"},
        },
        ARRAY_COUNT(cmm_terrain_floors_virtuaplex), cmm_terrain_floors_virtuaplex,
        CMM_FENCE_VIRTUAPLEX, CMM_WATER_DEFAULT
    },
    // SNOW
    {
        {
            {CMM_MAT_VP_BLOCK,      0,                       ""},
            {CMM_MAT_VP_TILES,      0,                       ""},
            {CMM_MAT_DIRT,          CMM_MAT_GRASS,        ""},
            {CMM_MAT_VP_TILES,      CMM_MAT_VP_BLUETILES, ""},
            {CMM_MAT_VP_RUSTYBLOCK, 0,                       ""},
            {CMM_MAT_VP_SCREEN,     0,                       ""},
            {CMM_MAT_VP_CAUTION,    0,                       ""},
            {CMM_MAT_VP_BLOCK,      CMM_MAT_SNOW,         ""},
            {CMM_MAT_LAVA,          0,                       ""},
            {CMM_MAT_VP_VOID,       0,                       ""},
        },
        ARRAY_COUNT(cmm_terrain_floors_virtuaplex), cmm_terrain_floors_virtuaplex,
        CMM_FENCE_VIRTUAPLEX, CMM_WATER_DEFAULT
    },
    // BBH
    {
        {
            {CMM_MAT_BBH_BRICKS,         CMM_MAT_BBH_STONE,      "Stone Floor"},
            {CMM_MAT_BBH_HAUNTED_PLANKS, 0,                         "Haunted Planks"},
            {CMM_MAT_BBH_STONE_PATTERN,  CMM_MAT_BBH_WOOD_FLOOR, "Wood Floor"},
            {CMM_MAT_BBH_BRICKS,         CMM_MAT_BBH_METAL,      "Metal Floor"},
            {CMM_MAT_BBH_ROOF,           0,                         "Roof"},
            {CMM_MAT_BBH_WOOD_WALL,      0,                         "Wood"},
            {CMM_MAT_BBH_STONE,          0,                         "Wall"},
            {CMM_MAT_BBH_PILLAR,         CMM_MAT_BBH_STONE,      "Pillar"},
            {CMM_MAT_LAVA,               0,                         "Lava"},
            {CMM_MAT_BBH_WINDOW,         0,                         "Window"},
        },
        ARRAY_COUNT(cmm_terrain_floors_bbh), cmm_terrain_floors_bbh,
        CMM_FENCE_BBH, CMM_WATER_DEFAULT
    },
    // JRB
    {
        {
            {CMM_MAT_JRB_STONE,     CMM_MAT_JRB_SAND,     "Sand"},
            {CMM_MAT_JRB_METAL,     0,                       "Metal Plating"},
            {CMM_MAT_JRB_UNDERWATER, 0,                      "Stone"},
            {CMM_MAT_JRB_STONE,     0,                       "Rocks"},
            {CMM_MAT_JRB_SHIPSIDE,  CMM_MAT_JRB_SHIPTOP,  "Wood (Ship)"},
            {CMM_MAT_JRB_METAL,     CMM_MAT_JRB_WOOD,     "Wood (Docks)"},
            {CMM_MAT_JRB_METALSIDE, CMM_MAT_JRB_METAL,       "Metal"},
            {CMM_MAT_HMC_MESH,      0,                       "Mesh"},
            {CMM_MAT_JRB_WALL,      0,                       "Wall"},
            {CMM_MAT_QUICKSAND,       0,                       "Quicksand"},
        },
        ARRAY_COUNT(cmm_terrain_floors_jrb), cmm_terrain_floors_jrb,
        CMM_FENCE_JRB, CMM_WATER_DEFAULT
    },
    // RETRO
    {
        {
            {CMM_MAT_RETRO_GROUND,           0,                        "Ground"},
            {CMM_MAT_RETRO_BRICKS,           0,                        "Bricks"},
            {CMM_MAT_RETRO_TREEPLAT,         CMM_MAT_RETRO_TREETOP,    "Treetop"},
            {CMM_MAT_RETRO_BLOCK,            0,                        "Block"},
            {CMM_MAT_RETRO_BLUEGROUND,       0,                        "Blue Ground"},
            {CMM_MAT_RETRO_BLUEBRICKS,       0,                        "Blue Bricks"},
            {CMM_MAT_RETRO_BLUEBLOCK,        0,                        "Blue Block"},
            {CMM_MAT_RETRO_WHITEBRICK,       0,                        "White Bricks"},
            {CMM_MAT_RETRO_LAVA,             0,                        "Lava"},
            {CMM_MAT_RETRO_UNDERWATERGROUND, 0,                        "Underwater Tile"},
        },
        ARRAY_COUNT(cmm_terrain_floors_retro), cmm_terrain_floors_retro,
        CMM_FENCE_RETRO, CMM_WATER_RETRO
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
#define WATER_TEX() (cmm_water_texs[cmm_theme_table[cmm_lopt_theme].water])


enum {
    CMM_BUTTON_SAVE,
    CMM_BUTTON_SETTINGS,
    CMM_BUTTON_PLAY,
    CMM_BUTTON_TERRAIN,
    CMM_BUTTON_SLOPE,
    CMM_BUTTON_TROLL,
    CMM_BUTTON_STAR,
    CMM_BUTTON_GOOMBA,
    CMM_BUTTON_COIN,
    CMM_BUTTON_BLANK,
    CMM_BUTTON_GCOIN,
    CMM_BUTTON_CORNER,
    CMM_BUTTON_ICORNER,
    CMM_BUTTON_RCOIN,
    CMM_BUTTON_BCOIN,
    CMM_BUTTON_BCS,
    CMM_BUTTON_RCS,
    CMM_BUTTON_NOTEBLOCK,
    CMM_BUTTON_CULL,
    CMM_BUTTON_PODOBOO,
    CMM_BUTTON_REX,
    CMM_BUTTON_BULLY,
    CMM_BUTTON_BOMB,
    CMM_BUTTON_TREE,
    CMM_BUTTON_EXCLA,
    CMM_BUTTON_CHUCKYA,
    CMM_BUTTON_SPAWN,
    CMM_BUTTON_PHANTASM,
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
};

u8 cmm_ui_bar[9] = {
    CMM_BUTTON_TERRAIN,
    CMM_BUTTON_FENCE,
    CMM_BUTTON_SLOPE,
    CMM_BUTTON_COIN,
    CMM_BUTTON_GOOMBA,
    CMM_BUTTON_STAR,
    CMM_BUTTON_PLAY,
    CMM_BUTTON_SETTINGS,
    CMM_BUTTON_SAVE,
};

u8 cmm_toolbox[45];
//Different toolboxes for different game styles
u8 cmm_toolbox_btcm[45] = {
    /*Tiles    */ CMM_BUTTON_TERRAIN, CMM_BUTTON_SLAB, CMM_BUTTON_SLOPE, CMM_BUTTON_CORNER, CMM_BUTTON_ICORNER, CMM_BUTTON_BLANK, CMM_BUTTON_SSLOPE, CMM_BUTTON_CULL, CMM_BUTTON_BLANK,
    /*Tiles 2  */ CMM_BUTTON_TROLL, CMM_BUTTON_WATER, CMM_BUTTON_FENCE, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK,
    /*Items    */ CMM_BUTTON_STAR, CMM_BUTTON_RCS, CMM_BUTTON_COIN,CMM_BUTTON_GCOIN,CMM_BUTTON_RCOIN,CMM_BUTTON_BCOIN,CMM_BUTTON_BCS,CMM_BUTTON_BADGE,CMM_BUTTON_BLANK,
    /*Enemies  */ CMM_BUTTON_GOOMBA,CMM_BUTTON_REX,CMM_BUTTON_PODOBOO,CMM_BUTTON_BULLY,CMM_BUTTON_BOMB,CMM_BUTTON_CHUCKYA,CMM_BUTTON_PHANTASM,CMM_BUTTON_BLANK,CMM_BUTTON_BLANK,
    /*Obstacles*/ CMM_BUTTON_NOTEBLOCK,CMM_BUTTON_TREE,CMM_BUTTON_EXCLA,CMM_BUTTON_PIPE,CMM_BUTTON_MPLAT,CMM_BUTTON_SPAWN, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK,
};
u8 cmm_toolbox_vanilla[45] = {
    /*Tiles    */ CMM_BUTTON_TERRAIN, CMM_BUTTON_SLAB, CMM_BUTTON_SLOPE, CMM_BUTTON_CORNER, CMM_BUTTON_ICORNER, CMM_BUTTON_BLANK, CMM_BUTTON_SSLOPE, CMM_BUTTON_CULL, CMM_BUTTON_BLANK,
    /*Tiles 2  */ CMM_BUTTON_TROLL, CMM_BUTTON_WATER, CMM_BUTTON_FENCE, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK,
    /*Items    */ CMM_BUTTON_STAR, CMM_BUTTON_RCS, CMM_BUTTON_COIN,CMM_BUTTON_RCOIN,CMM_BUTTON_BCOIN,CMM_BUTTON_BCS,CMM_BUTTON_KTQ,CMM_BUTTON_BLANK,CMM_BUTTON_BLANK,
    /*Enemies  */ CMM_BUTTON_GOOMBA,CMM_BUTTON_BULLY,CMM_BUTTON_BOMB,CMM_BUTTON_CHUCKYA,CMM_BUTTON_BBALL,CMM_BUTTON_BOSS,CMM_BUTTON_BLANK,CMM_BUTTON_BLANK,CMM_BUTTON_BLANK,
    /*Obstacles*/ CMM_BUTTON_TREE,CMM_BUTTON_PIPE,CMM_BUTTON_MPLAT,CMM_BUTTON_SPAWN,CMM_BUTTON_BLANK,CMM_BUTTON_BLANK,CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK,
};


//behparam2 strings
char *txt_bp_box[] = {
    "Rocket Boots",
    "Cosmic Seed",
    "Vanetal Cap",
    "Koopa Shell",
    "Green Coin",
    "3 Coins",
    "10 Coins",
    "Invisible"
};

char *txt_bp_tree[] = {
    "Bubbly",
    "Farm",
    "Palm",
    "Snowy"
};

char *txt_bp_boss[] = {
    "King Bob-Omb",
    "King Whomp",
    "Eyerok",
    "Wiggler",
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

struct cmm_ui_button_type cmm_ui_buttons[] = {
    //button texture      //TILE/OBJ ID        //PLACE MODE  //TXT POINTER         //PARAM STR
    {mat_b_btn_save,      0,                   CMM_PM_NONE,  "Save",               NULL       }, //CMM_BUTTON_SAVE
    {mat_b_btn_settings,  0,                   CMM_PM_NONE,  "Settings",           NULL       }, //CMM_BUTTON_SETTINGS
    {mat_b_btn_check,     0,                   CMM_PM_NONE,  "Test",               NULL       }, //CMM_BUTTON_PLAY
    {mat_b_btn_tile,      TILE_TYPE_BLOCK,     CMM_PM_TILE,  "Terrain",            NULL       }, //CMM_BUTTON_GRASS
    {mat_b_btn_slope,     TILE_TYPE_SLOPE,     CMM_PM_TILE,  "Slope",              NULL       }, //CMM_BUTTON_SLOPE
    {mat_b_btn_troll,     TILE_TYPE_TROLL,     CMM_PM_TILE,  "Troll Tile",         NULL       }, //CMM_BUTTON_TROLL
    {mat_b_btn_star,      OBJECT_TYPE_STAR,    CMM_PM_OBJ,   "Power Star",         NULL       }, //CMM_BUTTON_STAR
    {mat_b_btn_goomba,    OBJECT_TYPE_GOOMBA,  CMM_PM_OBJ,   "Goomba",             NULL       }, //CMM_BUTTON_GOOMBA
    {mat_b_btn_coin,      OBJECT_TYPE_COIN,    CMM_PM_OBJ,   "Yellow Coin",        NULL       }, //CMM_BUTTON_COIN
    {mat_b_btn_blank,     TILE_TYPE_BLOCK,     CMM_PM_TILE,  "",                   NULL       }, //CMM_BUTTON_BLANK
    {mat_b_btn_greencoin, OBJECT_TYPE_GCOIN,   CMM_PM_OBJ,   "Green Coin",         NULL       }, //CMM_BUTTON_GCOIN
    {mat_b_btn_corner,    TILE_TYPE_CORNER,    CMM_PM_TILE,  "Slope Corner",       NULL       }, //CMM_BUTTON_CORNER
    {mat_b_btn_icorner,   TILE_TYPE_ICORNER,   CMM_PM_TILE,  "Slope Inner Corner", NULL       }, //CMM_BUTTON_ICORNER
    {mat_b_btn_redcoin,   OBJECT_TYPE_RCOIN,   CMM_PM_OBJ,   "Red Coin",           NULL       }, //CMM_BUTTON_RCOIN
    {mat_b_btn_bluecoin,  OBJECT_TYPE_BCOIN,   CMM_PM_OBJ,   "Blue Coin",          NULL       }, //CMM_BUTTON_BCOIN
    {mat_b_btn_bcs,       OBJECT_TYPE_BCS,     CMM_PM_OBJ,   "Blue Coin Switch",   NULL       }, //CMM_BUTTON_BCS
    {mat_b_btn_rcs,       OBJECT_TYPE_RCS,     CMM_PM_OBJ,   "Red Coin Star",      NULL       }, //CMM_BUTTON_RCS
    {mat_b_btn_noteblock, OBJECT_TYPE_NOTE,    CMM_PM_OBJ,   "Note Block",         NULL       }, //CMM_BUTTON_NOTEBLOCK
    {mat_b_btn_cull,      TILE_TYPE_CULL,      CMM_PM_TILE,  "Cull Marker",        NULL       }, //CMM_BUTTON_CULL
    {mat_b_btn_podoboo,   OBJECT_TYPE_PODOB,   CMM_PM_OBJ,   "Podoboo",            NULL       }, //CMM_BUTTON_PODOBOO
    {mat_b_btn_rex,       OBJECT_TYPE_REX,     CMM_PM_OBJ,   "Rex",                NULL       }, //CMM_BUTTON_REX
    {mat_b_btn_bully,     OBJECT_TYPE_BULLY,   CMM_PM_OBJ,   "Bully",              NULL       }, //CMM_BUTTON_BULLY
    {mat_b_btn_bobomb,    OBJECT_TYPE_BOMB,    CMM_PM_OBJ,   "Bob-omb",            NULL       }, //CMM_BUTTON_BOMB
    {mat_b_btn_tree,      OBJECT_TYPE_TREE,    CMM_PM_OBJ,   "Tree",               txt_bp_tree}, //CMM_BUTTON_TREE
    {mat_b_btn_excla,     OBJECT_TYPE_EXCLA,   CMM_PM_OBJ,   "Item Box",           txt_bp_box }, //CMM_BUTTON_EXCLA
    {mat_b_btn_chuckya,   OBJECT_TYPE_CHUCKYA, CMM_PM_OBJ,   "Chuckya",            NULL       }, //CMM_BUTTON_CHUCKYA
    {mat_b_btn_spawn,     OBJECT_TYPE_SPAWN,   CMM_PM_OBJ,   "Mario Spawn",        NULL       }, //CMM_BUTTON_SPAWN
    {mat_b_btn_phantasm,  OBJECT_TYPE_PHNTSM,  CMM_PM_OBJ,   "Cosmic Phantasm",    NULL       }, //CMM_BUTTON_PHANTASM
    {mat_b_btn_pipe,      OBJECT_TYPE_PIPE,    CMM_PM_OBJ,   "Warp Pipe",          NULL       }, //CMM_BUTTON_PIPE
    {mat_b_btn_badge,     OBJECT_TYPE_BADGE,   CMM_PM_OBJ,   "Badge",              txt_badges }, //CMM_BUTTON_BADGE
    {mat_b_btn_water,     0,                   CMM_PM_WATER, "Water",              NULL       }, //CMM_BUTTON_WATER
    {mat_b_btn_fence,     TILE_TYPE_FENCE,     CMM_PM_TILE,  "Fence",              NULL       }, //CMM_BUTTON_FENCE
    {mat_b_btn_boss,      OBJECT_TYPE_BOSS,    CMM_PM_OBJ,   "Boss",               txt_bp_boss}, //CMM_BUTTON_BOSS
    {mat_b_btn_checker,   OBJECT_TYPE_MPLAT,   CMM_PM_OBJ,   "Moving Platform",    NULL       }, //CMM_BUTTON_MPLAT
    {mat_b_btn_bball,     OBJECT_TYPE_BBALL,   CMM_PM_OBJ,   "Bowling Ball",       NULL       }, //CMM_BUTTON_BBALL
    {mat_b_btn_kuppa,     OBJECT_TYPE_KTQ,     CMM_PM_OBJ,   "Koopa the Quick",    NULL       }, //CMM_BUTTON_KTQ
    {mat_b_btn_sideslope, TILE_TYPE_SSLOPE,    CMM_PM_TILE,  "Sideways Slope",     NULL       }, //CMM_BUTTON_SSLOPE
    {mat_b_btn_slabtile,  TILE_TYPE_SLAB,      CMM_PM_TILE,  "Slab",               NULL       }, //CMM_BUTTON_SLAB
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

char *cmm_music_string_table[] = {
    "Cosmic Castle",
    "The Showrunner",
    "Red Hot",
    "Floating Farm",
    "Jungle Temple",
    "VR World",
    "Spooky Pirate",
    "Cursed Boss",
    "Road To The Boss",
    "Urbowser",
    "Big House",
    "SMB1 Overworld",
    "SMB2 Overworld",
    "SMB3 Fortress",
    "NSMB Castle",
    "The Show's Finale",
    "Parasite Moon",
    "AGAMEMNON",
    "Bad Apple!!",

    "SM64 Main Theme",
    "Slider",
    "Dire Dire Docks",
    "Lethal Lava Land",
    "Snow Mountain",
    "Haunted House",
    "Cave Dungeon",
    "Koopa's Road",
    "Koopa's Theme",
    "Ultimate Koopa",
};

char *cmm_envfx_string_table[] = {
    "None",
    "Ashes",
    "Snow",
    "Lava Bubbles",
    "Rain",
};

//envfx table
u8 cmm_envfx_table[] = {
    ENVFX_MODE_NONE,         // no effects
    ENVFX_SNOW_NORMAL,       // CCM, SL
    ENVFX_SNOW_BLIZZARD,     // unused
    ENVFX_LAVA_BUBBLES,      // LLL, BitFS, Bowser 2
    ENVFX_RAIN
};

char *cmm_theme_string_table[] = {
    "Generic",
    "Shifting Sand Land",
    "Red Hot Reservoir",
    "Hazy Maze Cave",
    "Castle Inside",
    "Virtuaplex",
    "Snow",
    "Big Boo's Haunt",
    "Jolly Roger Bay",
    "Retroland",
};

enum cmm_themes {
    CMM_THEME_GENERIC,
    CMM_THEME_SSL,
    CMM_THEME_RHR,
    CMM_THEME_HMC,
    CMM_THEME_CASTLE,
    CMM_THEME_VIRTUAPLEX,
    CMM_THEME_SNOW,
    CMM_THEME_BBH,
    CMM_THEME_JRB,
    CMM_THEME_RETRO,
};

char *cmm_bg_string_table[] = {
    "Ocean Hills",
    "Cloudy Sky",
    "Firey Sky",
    "Green Cave",
    "Haunted Forest",
    "Ice Mountains",
    "Desert Pyramids",
    "Hushed Haven",
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

struct cmm_settings_button cmm_settings_buttons[] = {
    {"Costume:", &cmm_lopt_costume, cmm_costume_string_table, ARRAY_COUNT(cmm_costume_string_table)},
    {"Music:",   &cmm_lopt_seq,     cmm_music_string_table,   ARRAY_COUNT(cmm_music_string_table)},
    {"Effect:",  &cmm_lopt_envfx,   cmm_envfx_string_table,   ARRAY_COUNT(cmm_envfx_string_table)},
    {"Skybox:",  &cmm_lopt_bg,      cmm_bg_string_table,      ARRAY_COUNT(cmm_bg_string_table)},
    {"Theme:",   &cmm_lopt_theme,   cmm_theme_string_table,   ARRAY_COUNT(cmm_theme_string_table)},
    {"Floor:",   &cmm_lopt_plane,   NULL, 0}, // Filled in by code
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
    u8 music;
    u8 envfx;
    u8 bg;
    u8 theme;
    u8 plane;

    u8 spawnHeight;
    u8 platform;
};

struct cmm_template cmm_templates[] = {
    {19, 0, 0, 0, 1,     2, FALSE},   // bob song
    {22, 0, 6, 1, 1,     2, FALSE},   // SSL song
    {2,  1, 2, 2, 2,     3, TRUE}, // red hot
    {21, 0, 0, 8, 1,     2, FALSE}, // DDD
    {23, 2, 5, 0, 6,     2, FALSE}, // CCM
};

struct cmm_settings_button cmm_mode_settings_buttons[] = {
    {"Mode:", &cmm_lopt_game, cmm_gamemode_string_table, ARRAY_COUNT(cmm_gamemode_string_table)},
    {"Size:", &cmm_lopt_size, cmm_levelsize_string_table, ARRAY_COUNT(cmm_levelsize_string_table)},
    {"Template:", &cmm_lopt_template, cmm_template_string_table, ARRAY_COUNT(cmm_template_string_table)},
};

#define SETTINGS_SIZE ARRAY_COUNT(cmm_settings_buttons)
