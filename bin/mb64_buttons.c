#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include "macros.h"
#include "types.h"
#include "make_const_nonconst.h"
#include "mb64/gfx/mb64_buttons.h"

static const Vtx mb64_btn_vtx[4] = {
    {{{-16, -16, 0}, 0, { -16, 1008}, {0, 0, 0x7F, 0xFF}}},
    {{{ 16, -16, 0}, 0, {1008, 1008}, {0, 0, 0x7F, 0xFF}}},
    {{{ 16,  16, 0}, 0, {1008,  -16}, {0, 0, 0x7F, 0xFF}}},
    {{{-16,  16, 0}, 0, { -16,  -16}, {0, 0, 0x7F, 0xFF}}},
};

const Gfx mb64_btn_dl_begin[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(ENVIRONMENT, 0, TEXEL0, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, TEXEL0, 0, 0, 0, 0, TEXEL0),
    gsDPSetRenderMode(G_RM_TEX_EDGE, G_RM_TEX_EDGE2),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

const Gfx mb64_btn_dl_end[] = {
    gsDPPipeSync(),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};

const Gfx mb64_btn_dl_ci8[] = {
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_8b_BYTES)),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPVertex(mb64_btn_vtx, 4, 0),
    gsSP2Triangles(0, 1, 2, 0x0, 0, 2, 3, 0x0),
    gsSPEndDisplayList(),
};

const Gfx mb64_btn_dl_ci4[] = {
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, ((32 * 32 + 3) >> 2) - 1, CALC_DXT_4b(32)),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPVertex(mb64_btn_vtx, 4, 0),
    gsSP2Triangles(0, 1, 2, 0x0, 0, 2, 3, 0x0),
    gsSPEndDisplayList(),
};

// Tile
ALIGNED8 static const Texture mb64_btn_block_ci4[] = {
#include "textures/mb64_buttons/block.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_block_pal_rgba16[] = {
#include "textures/mb64_buttons/block.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_block);

// Slab
ALIGNED8 static const Texture mb64_btn_slab_ci4[] = {
#include "textures/mb64_buttons/slab.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_slab_pal_rgba16[] = {
#include "textures/mb64_buttons/slab.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_slab);

// Slope
ALIGNED8 static const Texture mb64_btn_slope_ci4[] = {
#include "textures/mb64_buttons/slope.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_slope_pal_rgba16[] = {
#include "textures/mb64_buttons/slope.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_slope);

// Outer Corner
ALIGNED8 static const Texture mb64_btn_outercorner_ci4[] = {
#include "textures/mb64_buttons/outercorner.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_outercorner_pal_rgba16[] = {
#include "textures/mb64_buttons/outercorner.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_outercorner);

// Inner Corner
ALIGNED8 static const Texture mb64_btn_innercorner_ci4[] = {
#include "textures/mb64_buttons/innercorner.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_innercorner_pal_rgba16[] = {
#include "textures/mb64_buttons/innercorner.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_innercorner);

// Vertical Slab
ALIGNED8 static const Texture mb64_btn_verticalslab_ci4[] = {
#include "textures/mb64_buttons/verticalslab.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_verticalslab_pal_rgba16[] = {
#include "textures/mb64_buttons/verticalslab.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_verticalslab);

// Vertical Slope
ALIGNED8 static const Texture mb64_btn_verticalslope_ci4[] = {
#include "textures/mb64_buttons/verticalslope.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_verticalslope_pal_rgba16[] = {
#include "textures/mb64_buttons/verticalslope.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_verticalslope);

// Sloped Corner
ALIGNED8 static const Texture mb64_btn_cornerslope_ci4[] = {
#include "textures/mb64_buttons/cornerslope.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_cornerslope_pal_rgba16[] = {
#include "textures/mb64_buttons/cornerslope.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_cornerslope);

// Inverted Sloped Corner
ALIGNED8 static const Texture mb64_btn_invertedcorner_ci4[] = {
#include "textures/mb64_buttons/invertedcorner.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_invertedcorner_pal_rgba16[] = {
#include "textures/mb64_buttons/invertedcorner.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_invertedcorner);

// Lower Gentle Slope
ALIGNED8 static const Texture mb64_btn_lowergentle_ci4[] = {
#include "textures/mb64_buttons/lowergentle.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_lowergentle_pal_rgba16[] = {
#include "textures/mb64_buttons/lowergentle.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_lowergentle);

// Upper Gentle Slope
ALIGNED8 static const Texture mb64_btn_uppergentle_ci4[] = {
#include "textures/mb64_buttons/uppergentle.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_uppergentle_pal_rgba16[] = {
#include "textures/mb64_buttons/uppergentle.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_uppergentle);

// Intangible Tile
ALIGNED8 static const Texture mb64_btn_intangible_ci4[] = {
#include "textures/mb64_buttons/intangible.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_intangible_pal_rgba16[] = {
#include "textures/mb64_buttons/intangible.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_intangible);

// Water
ALIGNED8 static const Texture mb64_btn_water_ci4[] = {
#include "textures/mb64_buttons/water.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_water_pal_rgba16[] = {
#include "textures/mb64_buttons/water.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_water);

// Fence
ALIGNED8 static const Texture mb64_btn_fence_ci4[] = {
#include "textures/mb64_buttons/fence.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_fence_pal_rgba16[] = {
#include "textures/mb64_buttons/fence.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_fence);

// Iron Mesh
ALIGNED8 static const Texture mb64_btn_ironmesh_ci4[] = {
#include "textures/mb64_buttons/ironmesh.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_ironmesh_pal_rgba16[] = {
#include "textures/mb64_buttons/ironmesh.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_ironmesh);

// Pole
ALIGNED8 static const Texture mb64_btn_pole_ci4[] = {
#include "textures/mb64_buttons/pole.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_pole_pal_rgba16[] = {
#include "textures/mb64_buttons/pole.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_pole);

// Bubbly Tree
ALIGNED8 static const Texture mb64_btn_bubblytree_ci4[] = {
#include "textures/mb64_buttons/bubblytree.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bubblytree_pal_rgba16[] = {
#include "textures/mb64_buttons/bubblytree.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_bubblytree);

// Palm Tree
ALIGNED8 static const Texture mb64_btn_palmtree_ci4[] = {
#include "textures/mb64_buttons/palmtree.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_palmtree_pal_rgba16[] = {
#include "textures/mb64_buttons/palmtree.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_palmtree);

// Spiky Tree
ALIGNED8 static const Texture mb64_btn_spikytree_ci4[] = {
#include "textures/mb64_buttons/spikytree.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_spikytree_pal_rgba16[] = {
#include "textures/mb64_buttons/spikytree.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_spikytree);

// Snowy Tree
ALIGNED8 static const Texture mb64_btn_snowytree_ci4[] = {
#include "textures/mb64_buttons/snowytree.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_snowytree_pal_rgba16[] = {
#include "textures/mb64_buttons/snowytree.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_snowytree);

// Farm Tree
ALIGNED8 static const Texture mb64_btn_farmtree_ci4[] = {
#include "textures/mb64_buttons/farmtree.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_farmtree_pal_rgba16[] = {
#include "textures/mb64_buttons/farmtree.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_farmtree);

// Dead Tree
ALIGNED8 static const Texture mb64_btn_deadtree_ci4[] = {
#include "textures/mb64_buttons/deadtree.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_deadtree_pal_rgba16[] = {
#include "textures/mb64_buttons/deadtree.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_deadtree);

// Cull Marker
ALIGNED8 static const Texture mb64_btn_cullmarker_ci4[] = {
#include "textures/mb64_buttons/cullmarker.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_cullmarker_pal_rgba16[] = {
#include "textures/mb64_buttons/cullmarker.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_cullmarker);

// Power Star
ALIGNED8 static const Texture mb64_btn_star_ci4[] = {
#include "textures/mb64_buttons/star.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_star_pal_rgba16[] = {
#include "textures/mb64_buttons/star.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_star);

// Red Coins
ALIGNED8 static const Texture mb64_btn_redcoinstar_ci4[] = {
#include "textures/mb64_buttons/redcoinstar.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_redcoinstar_pal_rgba16[] = {
#include "textures/mb64_buttons/redcoinstar.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_redcoinstar);

// Star Triggers
ALIGNED8 static const Texture mb64_btn_triggerstar_ci4[] = {
#include "textures/mb64_buttons/triggerstar.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_triggerstar_pal_rgba16[] = {
#include "textures/mb64_buttons/triggerstar.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_triggerstar);

// Yellow Coin
ALIGNED8 static const Texture mb64_btn_coin_ci4[] = {
#include "textures/mb64_buttons/coin.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_coin_pal_rgba16[] = {
#include "textures/mb64_buttons/coin.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_coin);

// Coin Line
ALIGNED8 static const Texture mb64_btn_coinline_ci4[] = {
#include "textures/mb64_buttons/coinline.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_coinline_pal_rgba16[] = {
#include "textures/mb64_buttons/coinline.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_coinline);

// Vertical Coin Line
ALIGNED8 static const Texture mb64_btn_verticalcoinline_ci4[] = {
#include "textures/mb64_buttons/verticalcoinline.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_verticalcoinline_pal_rgba16[] = {
#include "textures/mb64_buttons/verticalcoinline.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_verticalcoinline);

// Coin Ring
ALIGNED8 static const Texture mb64_btn_coinring_ci4[] = {
#include "textures/mb64_buttons/coinring.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_coinring_pal_rgba16[] = {
#include "textures/mb64_buttons/coinring.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_coinring);

// Vertical Coin Ring
ALIGNED8 static const Texture mb64_btn_verticalcoinring_ci4[] = {
#include "textures/mb64_buttons/verticalcoinring.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_verticalcoinring_pal_rgba16[] = {
#include "textures/mb64_buttons/verticalcoinring.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_verticalcoinring);

// Coin Arrow
ALIGNED8 static const Texture mb64_btn_coinarrow_ci4[] = {
#include "textures/mb64_buttons/coinarrow.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_coinarrow_pal_rgba16[] = {
#include "textures/mb64_buttons/coinarrow.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_coinarrow);

// Green Coin
ALIGNED8 static const Texture mb64_btn_greencoin_ci4[] = {
#include "textures/mb64_buttons/greencoin.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_greencoin_pal_rgba16[] = {
#include "textures/mb64_buttons/greencoin.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_greencoin);

// Red Coin
ALIGNED8 static const Texture mb64_btn_redcoin_ci4[] = {
#include "textures/mb64_buttons/redcoin.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_redcoin_pal_rgba16[] = {
#include "textures/mb64_buttons/redcoin.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_redcoin);

// Blue Coin
ALIGNED8 static const Texture mb64_btn_bluecoin_ci4[] = {
#include "textures/mb64_buttons/bluecoin.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bluecoin_pal_rgba16[] = {
#include "textures/mb64_buttons/bluecoin.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_bluecoin);

// Blue Coin Switch
ALIGNED8 static const Texture mb64_btn_bluecoinswitch_ci4[] = {
#include "textures/mb64_buttons/bluecoinswitch.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bluecoinswitch_pal_rgba16[] = {
#include "textures/mb64_buttons/bluecoinswitch.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_bluecoinswitch);

// ! Box
ALIGNED8 static const Texture mb64_btn_exclamationbox_ci4[] = {
#include "textures/mb64_buttons/exclamationbox.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_exclamationbox_pal_rgba16[] = {
#include "textures/mb64_buttons/exclamationbox.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_exclamationbox);

// Rocket Boots Box
ALIGNED8 static const Texture mb64_btn_rocketbox_ci4[] = {
#include "textures/mb64_buttons/rocketbox.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_rocketbox_pal_rgba16[] = {
#include "textures/mb64_buttons/rocketbox.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_rocketbox);

// Vanetal Cap Box
ALIGNED8 static const Texture mb64_btn_vanetalbox_ci4[] = {
#include "textures/mb64_buttons/vanetalbox.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_vanetalbox_pal_rgba16[] = {
#include "textures/mb64_buttons/vanetalbox.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_vanetalbox);

// Wing Cap Box
ALIGNED8 static const Texture mb64_btn_wingbox_ci4[] = {
#include "textures/mb64_buttons/wingbox.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_wingbox_pal_rgba16[] = {
#include "textures/mb64_buttons/wingbox.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_wingbox);

// Metal Cap Box
ALIGNED8 static const Texture mb64_btn_metalbox_ci4[] = {
#include "textures/mb64_buttons/metalbox.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_metalbox_pal_rgba16[] = {
#include "textures/mb64_buttons/metalbox.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_metalbox);

// Vanish Cap Box
ALIGNED8 static const Texture mb64_btn_vanishbox_ci4[] = {
#include "textures/mb64_buttons/vanishbox.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_vanishbox_pal_rgba16[] = {
#include "textures/mb64_buttons/vanishbox.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_vanishbox);

// ? Box
ALIGNED8 static const Texture mb64_btn_questionbox_ci4[] = {
#include "textures/mb64_buttons/questionbox.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_questionbox_pal_rgba16[] = {
#include "textures/mb64_buttons/questionbox.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_questionbox);

// Star Trigger
ALIGNED8 static const Texture mb64_btn_trigger_ci4[] = {
#include "textures/mb64_buttons/trigger.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_trigger_pal_rgba16[] = {
#include "textures/mb64_buttons/trigger.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_trigger);

// Recovery Heart
ALIGNED8 static const Texture mb64_btn_recoveryheart_ci4[] = {
#include "textures/mb64_buttons/recoveryheart.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_recoveryheart_pal_rgba16[] = {
#include "textures/mb64_buttons/recoveryheart.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_recoveryheart);

// Moving Platform
ALIGNED8 static const Texture mb64_btn_movingplatform_ci4[] = {
#include "textures/mb64_buttons/movingplatform.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_movingplatform_pal_rgba16[] = {
#include "textures/mb64_buttons/movingplatform.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_movingplatform);

// Looping Platform
ALIGNED8 static const Texture mb64_btn_loopplatform_ci4[] = {
#include "textures/mb64_buttons/loopplatform.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_loopplatform_pal_rgba16[] = {
#include "textures/mb64_buttons/loopplatform.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_loopplatform);

// Purple Switch
ALIGNED8 static const Texture mb64_btn_purpleswitch_ci4[] = {
#include "textures/mb64_buttons/purpleswitch.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_purpleswitch_pal_rgba16[] = {
#include "textures/mb64_buttons/purpleswitch.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_purpleswitch);

// Timed Box
ALIGNED8 static const Texture mb64_btn_timedbox_ci4[] = {
#include "textures/mb64_buttons/timedbox.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_timedbox_pal_rgba16[] = {
#include "textures/mb64_buttons/timedbox.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_timedbox);

// Inverted Timed Box
ALIGNED8 static const Texture mb64_btn_invertedtimedblock_ci4[] = {
#include "textures/mb64_buttons/invertedtimedblock.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_invertedtimedblock_pal_rgba16[] = {
#include "textures/mb64_buttons/invertedtimedblock.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_invertedtimedblock);

// Breakable Box
ALIGNED8 static const Texture mb64_btn_box_ci4[] = {
#include "textures/mb64_buttons/box.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_box_pal_rgba16[] = {
#include "textures/mb64_buttons/box.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_box);

// Reinforced Box
ALIGNED8 static const Texture mb64_btn_rfbox_ci4[] = {
#include "textures/mb64_buttons/rfbox.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_rfbox_pal_rgba16[] = {
#include "textures/mb64_buttons/rfbox.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_rfbox);

// Water Diamond
ALIGNED8 static const Texture mb64_btn_waterdiamond_ci4[] = {
#include "textures/mb64_buttons/waterdiamond.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_waterdiamond_pal_rgba16[] = {
#include "textures/mb64_buttons/waterdiamond.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_waterdiamond);

// Wooden Platform
ALIGNED8 static const Texture mb64_btn_woodplatform_ci4[] = {
#include "textures/mb64_buttons/woodplatform.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_woodplatform_pal_rgba16[] = {
#include "textures/mb64_buttons/woodplatform.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_woodplatform);

// Full Wooden Platform
ALIGNED8 static const Texture mb64_btn_fullwoodplatform_ci4[] = {
#include "textures/mb64_buttons/fullwoodplatform.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_fullwoodplatform_pal_rgba16[] = {
#include "textures/mb64_buttons/fullwoodplatform.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_fullwoodplatform);

// Bill Board
ALIGNED8 static const Texture mb64_btn_signpost_ci4[] = {
#include "textures/mb64_buttons/signpost.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_signpost_pal_rgba16[] = {
#include "textures/mb64_buttons/signpost.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_signpost);

// Bob-omb Buddy
ALIGNED8 static const Texture mb64_btn_bobombbuddy_ci8[] = {
#include "textures/mb64_buttons/bobombbuddy.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bobombbuddy_pal_rgba16[] = {
#include "textures/mb64_buttons/bobombbuddy.ci8.pal"
};
DEFINE_CI8_BUTTON(mb64_btn_bobombbuddy);

// Moleman
ALIGNED8 static const Texture mb64_btn_moleman_ci4[] = {
#include "textures/mb64_buttons/moleman.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_moleman_pal_rgba16[] = {
#include "textures/mb64_buttons/moleman.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_moleman);

// Cobie
ALIGNED8 static const Texture mb64_btn_cowboy_ci4[] = {
#include "textures/mb64_buttons/cowboy.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_cowboy_pal_rgba16[] = {
#include "textures/mb64_buttons/cowboy.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_cowboy);

// Badges
ALIGNED8 static const Texture mb64_btn_badgelava_ci4[] = {
#include "textures/mb64_buttons/badgelava.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgelava_pal_rgba16[] = {
#include "textures/mb64_buttons/badgelava.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgelava);

ALIGNED8 static const Texture mb64_btn_badgefall_ci4[] = {
#include "textures/mb64_buttons/badgefall.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgefall_pal_rgba16[] = {
#include "textures/mb64_buttons/badgefall.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgefall);

ALIGNED8 static const Texture mb64_btn_badgedefense_ci4[] = {
#include "textures/mb64_buttons/badgedefense.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgedefense_pal_rgba16[] = {
#include "textures/mb64_buttons/badgedefense.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgedefense);

ALIGNED8 static const Texture mb64_btn_badgedamage_ci4[] = {
#include "textures/mb64_buttons/badgedamage.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgedamage_pal_rgba16[] = {
#include "textures/mb64_buttons/badgedamage.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgedamage);

ALIGNED8 static const Texture mb64_btn_badgegills_ci4[] = {
#include "textures/mb64_buttons/badgegills.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgegills_pal_rgba16[] = {
#include "textures/mb64_buttons/badgegills.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgegills);

ALIGNED8 static const Texture mb64_btn_badgefins_ci4[] = {
#include "textures/mb64_buttons/badgefins.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgefins_pal_rgba16[] = {
#include "textures/mb64_buttons/badgefins.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgefins);

ALIGNED8 static const Texture mb64_btn_badgehp_ci4[] = {
#include "textures/mb64_buttons/badgehp.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgehp_pal_rgba16[] = {
#include "textures/mb64_buttons/badgehp.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgehp);

ALIGNED8 static const Texture mb64_btn_badgemana_ci4[] = {
#include "textures/mb64_buttons/badgemana.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgemana_pal_rgba16[] = {
#include "textures/mb64_buttons/badgemana.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgemana);

ALIGNED8 static const Texture mb64_btn_badgegreed_ci4[] = {
#include "textures/mb64_buttons/badgegreed.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgegreed_pal_rgba16[] = {
#include "textures/mb64_buttons/badgegreed.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgegreed);

ALIGNED8 static const Texture mb64_btn_badgetime_ci4[] = {
#include "textures/mb64_buttons/badgetime.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgetime_pal_rgba16[] = {
#include "textures/mb64_buttons/badgetime.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgetime);

ALIGNED8 static const Texture mb64_btn_badgemagnet_ci4[] = {
#include "textures/mb64_buttons/badgemagnet.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgemagnet_pal_rgba16[] = {
#include "textures/mb64_buttons/badgemagnet.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgemagnet);

ALIGNED8 static const Texture mb64_btn_badgeburn_ci4[] = {
#include "textures/mb64_buttons/badgeburn.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgeburn_pal_rgba16[] = {
#include "textures/mb64_buttons/badgeburn.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgeburn);

ALIGNED8 static const Texture mb64_btn_badgesquish_ci4[] = {
#include "textures/mb64_buttons/badgesquish.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgesquish_pal_rgba16[] = {
#include "textures/mb64_buttons/badgesquish.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgesquish);

ALIGNED8 static const Texture mb64_btn_badgefeather_ci4[] = {
#include "textures/mb64_buttons/badgefeather.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgefeather_pal_rgba16[] = {
#include "textures/mb64_buttons/badgefeather.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgefeather);

ALIGNED8 static const Texture mb64_btn_badgeweight_ci4[] = {
#include "textures/mb64_buttons/badgeweight.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgeweight_pal_rgba16[] = {
#include "textures/mb64_buttons/badgeweight.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgeweight);

ALIGNED8 static const Texture mb64_btn_badgesticky_ci4[] = {
#include "textures/mb64_buttons/badgesticky.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgesticky_pal_rgba16[] = {
#include "textures/mb64_buttons/badgesticky.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgesticky);

ALIGNED8 static const Texture mb64_btn_badgefeet_ci4[] = {
#include "textures/mb64_buttons/badgefeet.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgefeet_pal_rgba16[] = {
#include "textures/mb64_buttons/badgefeet.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgefeet);

ALIGNED8 static const Texture mb64_btn_badgeheal_ci4[] = {
#include "textures/mb64_buttons/badgeheal.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgeheal_pal_rgba16[] = {
#include "textures/mb64_buttons/badgeheal.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgeheal);

ALIGNED8 static const Texture mb64_btn_badgebottomless_ci4[] = {
#include "textures/mb64_buttons/badgebottomless.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgebottomless_pal_rgba16[] = {
#include "textures/mb64_buttons/badgebottomless.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgebottomless);

ALIGNED8 static const Texture mb64_btn_badgeslowfall_ci4[] = {
#include "textures/mb64_buttons/badgeslowfall.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgeslowfall_pal_rgba16[] = {
#include "textures/mb64_buttons/badgeslowfall.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgeslowfall);

ALIGNED8 static const Texture mb64_btn_badgebrittle_ci4[] = {
#include "textures/mb64_buttons/badgebrittle.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgebrittle_pal_rgba16[] = {
#include "textures/mb64_buttons/badgebrittle.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgebrittle);

ALIGNED8 static const Texture mb64_btn_badgewither_ci4[] = {
#include "textures/mb64_buttons/badgewither.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badgewither_pal_rgba16[] = {
#include "textures/mb64_buttons/badgewither.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_badgewither);

// Noteblock
ALIGNED8 static const Texture mb64_btn_noteblock_ci4[] = {
#include "textures/mb64_buttons/noteblock.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_noteblock_pal_rgba16[] = {
#include "textures/mb64_buttons/noteblock.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_noteblock);

// Red On-Off Button
ALIGNED8 static const Texture mb64_btn_redswitch_ci4[] = {
#include "textures/mb64_buttons/redswitch.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_redswitch_pal_rgba16[] = {
#include "textures/mb64_buttons/redswitch.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_redswitch);

// Blue On-Off Button
ALIGNED8 static const Texture mb64_btn_blueswitch_ci4[] = {
#include "textures/mb64_buttons/blueswitch.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_blueswitch_pal_rgba16[] = {
#include "textures/mb64_buttons/blueswitch.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_blueswitch);

// Red On-Off Block
ALIGNED8 static const Texture mb64_btn_redblock_ci4[] = {
#include "textures/mb64_buttons/redblock.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_redblock_pal_rgba16[] = {
#include "textures/mb64_buttons/redblock.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_redblock);

// Blue On-Off Block
ALIGNED8 static const Texture mb64_btn_blueblock_ci4[] = {
#include "textures/mb64_buttons/blueblock.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_blueblock_pal_rgba16[] = {
#include "textures/mb64_buttons/blueblock.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_blueblock);

// Conveyor
ALIGNED8 static const Texture mb64_btn_conveyor_ci4[] = {
#include "textures/mb64_buttons/conveyor.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_conveyor_pal_rgba16[] = {
#include "textures/mb64_buttons/conveyor.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_conveyor);

// Full Conveyor
ALIGNED8 static const Texture mb64_btn_fullconveyor_ci4[] = {
#include "textures/mb64_buttons/fullconveyor.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_fullconveyor_pal_rgba16[] = {
#include "textures/mb64_buttons/fullconveyor.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_fullconveyor);

// Up Conveyor
ALIGNED8 static const Texture mb64_btn_upconveyor_ci4[] = {
#include "textures/mb64_buttons/upconveyor.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_upconveyor_pal_rgba16[] = {
#include "textures/mb64_buttons/upconveyor.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_upconveyor);

// Down Conveyor
ALIGNED8 static const Texture mb64_btn_downconveyor_ci4[] = {
#include "textures/mb64_buttons/downconveyor.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_downconveyor_pal_rgba16[] = {
#include "textures/mb64_buttons/downconveyor.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_downconveyor);

// Red Conveyor
ALIGNED8 static const Texture mb64_btn_redconveyor_ci4[] = {
#include "textures/mb64_buttons/redconveyor.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_redconveyor_pal_rgba16[] = {
#include "textures/mb64_buttons/redconveyor.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_redconveyor);

// Red Full Conveyor
ALIGNED8 static const Texture mb64_btn_redfullconveyor_ci4[] = {
#include "textures/mb64_buttons/redfullconveyor.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_redfullconveyor_pal_rgba16[] = {
#include "textures/mb64_buttons/redfullconveyor.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_redfullconveyor);

// Red Up Conveyor
ALIGNED8 static const Texture mb64_btn_redupconveyor_ci4[] = {
#include "textures/mb64_buttons/redupconveyor.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_redupconveyor_pal_rgba16[] = {
#include "textures/mb64_buttons/redupconveyor.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_redupconveyor);

// Red Down Conveyor
ALIGNED8 static const Texture mb64_btn_reddownconveyor_ci4[] = {
#include "textures/mb64_buttons/reddownconveyor.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_reddownconveyor_pal_rgba16[] = {
#include "textures/mb64_buttons/reddownconveyor.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_reddownconveyor);

// Toad
ALIGNED8 static const Texture mb64_btn_toad_ci8[] = {
#include "textures/mb64_buttons/toad.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_toad_pal_rgba16[] = {
#include "textures/mb64_buttons/toad.ci8.pal"
};
DEFINE_CI8_BUTTON(mb64_btn_toad);

// Tuxie
ALIGNED8 static const Texture mb64_btn_tuxie_ci4[] = {
#include "textures/mb64_buttons/tuxie.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_tuxie_pal_rgba16[] = {
#include "textures/mb64_buttons/tuxie.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_tuxie);

// Ukiki
ALIGNED8 static const Texture mb64_btn_ukiki_ci4[] = {
#include "textures/mb64_buttons/ukiki.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_ukiki_pal_rgba16[] = {
#include "textures/mb64_buttons/ukiki.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_ukiki);

// Koopa the Quick
ALIGNED8 static const Texture mb64_btn_ktq_ci8[] = {
#include "textures/mb64_buttons/ktq.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_ktq_pal_rgba16[] = {
#include "textures/mb64_buttons/ktq.ci8.pal"
};
DEFINE_CI8_BUTTON(mb64_btn_ktq);

// Goomba
ALIGNED8 static const Texture mb64_btn_goomba_ci4[] = {
#include "textures/mb64_buttons/goomba.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_goomba_pal_rgba16[] = {
#include "textures/mb64_buttons/goomba.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_goomba);

// Huge Goomba
ALIGNED8 static const Texture mb64_btn_biggoomba_ci4[] = {
#include "textures/mb64_buttons/biggoomba.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_biggoomba_pal_rgba16[] = {
#include "textures/mb64_buttons/biggoomba.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_biggoomba);

// Tiny Goomba
ALIGNED8 static const Texture mb64_btn_tinygoomba_ci4[] = {
#include "textures/mb64_buttons/tinygoomba.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_tinygoomba_pal_rgba16[] = {
#include "textures/mb64_buttons/tinygoomba.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_tinygoomba);

// Bob-omb
ALIGNED8 static const Texture mb64_btn_bobomb_ci4[] = {
#include "textures/mb64_buttons/bobomb.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bobomb_pal_rgba16[] = {
#include "textures/mb64_buttons/bobomb.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_bobomb);

// Chuckya
ALIGNED8 static const Texture mb64_btn_chuckya_ci8[] = {
#include "textures/mb64_buttons/chuckya.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_chuckya_pal_rgba16[] = {
#include "textures/mb64_buttons/chuckya.ci8.pal"
};
DEFINE_CI8_BUTTON(mb64_btn_chuckya);

// Koopa
ALIGNED8 static const Texture mb64_btn_koopa_ci4[] = {
#include "textures/mb64_buttons/koopa.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_koopa_pal_rgba16[] = {
#include "textures/mb64_buttons/koopa.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_koopa);

// Lakitu
ALIGNED8 static const Texture mb64_btn_lakitu_ci4[] = {
#include "textures/mb64_buttons/lakitu.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_lakitu_pal_rgba16[] = {
#include "textures/mb64_buttons/lakitu.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_lakitu);

// Fly Guy
ALIGNED8 static const Texture mb64_btn_flyguy_ci4[] = {
#include "textures/mb64_buttons/flyguy.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_flyguy_pal_rgba16[] = {
#include "textures/mb64_buttons/flyguy.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_flyguy);

// Snufit
ALIGNED8 static const Texture mb64_btn_snufit_ci4[] = {
#include "textures/mb64_buttons/snufit.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_snufit_pal_rgba16[] = {
#include "textures/mb64_buttons/snufit.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_snufit);

// Thwomp
ALIGNED8 static const Texture mb64_btn_thwomp_ci4[] = {
#include "textures/mb64_buttons/thwomp.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_thwomp_pal_rgba16[] = {
#include "textures/mb64_buttons/thwomp.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_thwomp);

// Grindel
ALIGNED8 static const Texture mb64_btn_grindel_ci8[] = {
#include "textures/mb64_buttons/grindel.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_grindel_pal_rgba16[] = {
#include "textures/mb64_buttons/grindel.ci8.pal"
};
DEFINE_CI8_BUTTON(mb64_btn_grindel);

// Whomp
ALIGNED8 static const Texture mb64_btn_whomp_ci4[] = {
#include "textures/mb64_buttons/whomp.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_whomp_pal_rgba16[] = {
#include "textures/mb64_buttons/whomp.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_whomp);

// King Whomp
ALIGNED8 static const Texture mb64_btn_kingwhomp_ci4[] = {
#include "textures/mb64_buttons/kingwhomp.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_kingwhomp_pal_rgba16[] = {
#include "textures/mb64_buttons/kingwhomp.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_kingwhomp);

// Bully
ALIGNED8 static const Texture mb64_btn_bully_ci4[] = {
#include "textures/mb64_buttons/bully.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bully_pal_rgba16[] = {
#include "textures/mb64_buttons/bully.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_bully);

// Chill Bully
ALIGNED8 static const Texture mb64_btn_chillbully_ci8[] = {
#include "textures/mb64_buttons/chillbully.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_chillbully_pal_rgba16[] = {
#include "textures/mb64_buttons/chillbully.ci8.pal"
};
DEFINE_CI8_BUTTON(mb64_btn_chillbully);

// Big Bully
ALIGNED8 static const Texture mb64_btn_bigbully_ci4[] = {
#include "textures/mb64_buttons/bigbully.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bigbully_pal_rgba16[] = {
#include "textures/mb64_buttons/bigbully.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_bigbully);

// Big Chill Bully
ALIGNED8 static const Texture mb64_btn_chiefchilly_ci8[] = {
#include "textures/mb64_buttons/chiefchilly.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_chiefchilly_pal_rgba16[] = {
#include "textures/mb64_buttons/chiefchilly.ci8.pal"
};
DEFINE_CI8_BUTTON(mb64_btn_chiefchilly);

// Motos
ALIGNED8 static const Texture mb64_btn_motos_ci8[] = {
#include "textures/mb64_buttons/motos.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_motos_pal_rgba16[] = {
#include "textures/mb64_buttons/motos.ci8.pal"
};
DEFINE_CI8_BUTTON(mb64_btn_motos);

// Heave-Ho
ALIGNED8 static const Texture mb64_btn_heaveho_ci8[] = {
#include "textures/mb64_buttons/heaveho.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_heaveho_pal_rgba16[] = {
#include "textures/mb64_buttons/heaveho.ci8.pal"
};
DEFINE_CI8_BUTTON(mb64_btn_heaveho);

// Bullet Bill
ALIGNED8 static const Texture mb64_btn_bulletbill_ci4[] = {
#include "textures/mb64_buttons/bulletbill.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bulletbill_pal_rgba16[] = {
#include "textures/mb64_buttons/bulletbill.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_bulletbill);

// Amp
ALIGNED8 static const Texture mb64_btn_amp_ci4[] = {
#include "textures/mb64_buttons/amp.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_amp_pal_rgba16[] = {
#include "textures/mb64_buttons/amp.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_amp);

// Piranha Plant
ALIGNED8 static const Texture mb64_btn_piranha_ci4[] = {
#include "textures/mb64_buttons/piranha.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_piranha_pal_rgba16[] = {
#include "textures/mb64_buttons/piranha.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_piranha);

// Huge Piranha Plant
ALIGNED8 static const Texture mb64_btn_bigfirepiranha_ci8[] = {
#include "textures/mb64_buttons/bigfirepiranha.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bigfirepiranha_pal_rgba16[] = {
#include "textures/mb64_buttons/bigfirepiranha.ci8.pal"
};
DEFINE_CI8_BUTTON(mb64_btn_bigfirepiranha);

// Tiny Piranha Plant
ALIGNED8 static const Texture mb64_btn_firepiranha_ci4[] = {
#include "textures/mb64_buttons/firepiranha.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_firepiranha_pal_rgba16[] = {
#include "textures/mb64_buttons/firepiranha.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_firepiranha);

// Boo
ALIGNED8 static const Texture mb64_btn_boo_ci4[] = {
#include "textures/mb64_buttons/boo.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_boo_pal_rgba16[] = {
#include "textures/mb64_buttons/boo.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_boo);

// Big Boo
ALIGNED8 static const Texture mb64_btn_bigboo_ci8[] = {
#include "textures/mb64_buttons/bigboo.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bigboo_pal_rgba16[] = {
#include "textures/mb64_buttons/bigboo.ci8.pal"
};
DEFINE_CI8_BUTTON(mb64_btn_bigboo);

// Mr. I
ALIGNED8 static const Texture mb64_btn_mri_ci4[] = {
#include "textures/mb64_buttons/mri.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_mri_pal_rgba16[] = {
#include "textures/mb64_buttons/mri.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_mri);

// Scuttlebug
ALIGNED8 static const Texture mb64_btn_scuttlebug_ci4[] = {
#include "textures/mb64_buttons/scuttlebug.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_scuttlebug_pal_rgba16[] = {
#include "textures/mb64_buttons/scuttlebug.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_scuttlebug);

// Spindrift
ALIGNED8 static const Texture mb64_btn_spindrift_ci8[] = {
#include "textures/mb64_buttons/spindrift.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_spindrift_pal_rgba16[] = {
#include "textures/mb64_buttons/spindrift.ci8.pal"
};
DEFINE_CI8_BUTTON(mb64_btn_spindrift);

// Mr. Blizzard
ALIGNED8 static const Texture mb64_btn_mrblizzard_ci4[] = {
#include "textures/mb64_buttons/mrblizzard.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_mrblizzard_pal_rgba16[] = {
#include "textures/mb64_buttons/mrblizzard.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_mrblizzard);

// Moneybag
ALIGNED8 static const Texture mb64_btn_moneybag_ci4[] = {
#include "textures/mb64_buttons/moneybag.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_moneybag_pal_rgba16[] = {
#include "textures/mb64_buttons/moneybag.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_moneybag);

// Skeeter
ALIGNED8 static const Texture mb64_btn_skeeter_ci8[] = {
#include "textures/mb64_buttons/skeeter.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_skeeter_pal_rgba16[] = {
#include "textures/mb64_buttons/skeeter.ci8.pal"
};
DEFINE_CI8_BUTTON(mb64_btn_skeeter);

// Pokey
ALIGNED8 static const Texture mb64_btn_pokey_ci4[] = {
#include "textures/mb64_buttons/pokey.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_pokey_pal_rgba16[] = {
#include "textures/mb64_buttons/pokey.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_pokey);

// Rex
ALIGNED8 static const Texture mb64_btn_rex_ci4[] = {
#include "textures/mb64_buttons/rex.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_rex_pal_rgba16[] = {
#include "textures/mb64_buttons/rex.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_rex);

// Hammer Bro
ALIGNED8 static const Texture mb64_btn_hammerbro_ci8[] = {
#include "textures/mb64_buttons/hammerbro.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_hammerbro_pal_rgba16[] = {
#include "textures/mb64_buttons/hammerbro.ci8.pal"
};
DEFINE_CI8_BUTTON(mb64_btn_hammerbro);

// Fire Bro
ALIGNED8 static const Texture mb64_btn_firebro_ci8[] = {
#include "textures/mb64_buttons/firebro.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_firebro_pal_rgba16[] = {
#include "textures/mb64_buttons/firebro.ci8.pal"
};
DEFINE_CI8_BUTTON(mb64_btn_firebro);

// Podoboo
ALIGNED8 static const Texture mb64_btn_podoboo_ci4[] = {
#include "textures/mb64_buttons/podoboo.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_podoboo_pal_rgba16[] = {
#include "textures/mb64_buttons/podoboo.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_podoboo);

// Cosmic Phantasm
ALIGNED8 static const Texture mb64_btn_cosmicphantasm_ci8[] = {
#include "textures/mb64_buttons/cosmicphantasm.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_cosmicphantasm_pal_rgba16[] = {
#include "textures/mb64_buttons/cosmicphantasm.ci8.pal"
};
DEFINE_CI8_BUTTON(mb64_btn_cosmicphantasm);

// Red Flame
ALIGNED8 static const Texture mb64_btn_redflame_ci4[] = {
#include "textures/mb64_buttons/redflame.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_redflame_pal_rgba16[] = {
#include "textures/mb64_buttons/redflame.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_redflame);

// Blue Flame
ALIGNED8 static const Texture mb64_btn_blueflame_ci4[] = {
#include "textures/mb64_buttons/blueflame.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_blueflame_pal_rgba16[] = {
#include "textures/mb64_buttons/blueflame.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_blueflame);

// Flamethrower
ALIGNED8 static const Texture mb64_btn_flamethrower_ci4[] = {
#include "textures/mb64_buttons/flamethrower.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_flamethrower_pal_rgba16[] = {
#include "textures/mb64_buttons/flamethrower.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_flamethrower);

// Fire Spitter
ALIGNED8 static const Texture mb64_btn_firespitter_ci4[] = {
#include "textures/mb64_buttons/firespitter.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_firespitter_pal_rgba16[] = {
#include "textures/mb64_buttons/firespitter.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_firespitter);

// Fire Spinner
ALIGNED8 static const Texture mb64_btn_firespinner_ci4[] = {
#include "textures/mb64_buttons/firespinner.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_firespinner_pal_rgba16[] = {
#include "textures/mb64_buttons/firespinner.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_firespinner);

// Bowling Ball
ALIGNED8 static const Texture mb64_btn_bowlingball_ci4[] = {
#include "textures/mb64_buttons/bowlingball.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bowlingball_pal_rgba16[] = {
#include "textures/mb64_buttons/bowlingball.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_bowlingball);

// Chicken
ALIGNED8 static const Texture mb64_btn_chicken_ci4[] = {
#include "textures/mb64_buttons/chicken.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_chicken_pal_rgba16[] = {
#include "textures/mb64_buttons/chicken.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_chicken);

// Crablet
ALIGNED8 static const Texture mb64_btn_crablet_ci4[] = {
#include "textures/mb64_buttons/crablet.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_crablet_pal_rgba16[] = {
#include "textures/mb64_buttons/crablet.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_crablet);

// Showrunner
ALIGNED8 static const Texture mb64_btn_showrunner_ci8[] = {
#include "textures/mb64_buttons/showrunner.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_showrunner_pal_rgba16[] = {
#include "textures/mb64_buttons/showrunner.ci8.pal"
};
DEFINE_CI8_BUTTON(mb64_btn_showrunner);

// Mario Spawn
ALIGNED8 static const Texture mb64_btn_spawn_ci4[] = {
#include "textures/mb64_buttons/spawn.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_spawn_pal_rgba16[] = {
#include "textures/mb64_buttons/spawn.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_spawn);

// Throwable Box
ALIGNED8 static const Texture mb64_btn_smallbox_ci4[] = {
#include "textures/mb64_buttons/smallbox.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_smallbox_pal_rgba16[] = {
#include "textures/mb64_buttons/smallbox.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_smallbox);

// Crazy Box
ALIGNED8 static const Texture mb64_btn_crazybox_ci4[] = {
#include "textures/mb64_buttons/crazybox.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_crazybox_pal_rgba16[] = {
#include "textures/mb64_buttons/crazybox.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_crazybox);

// Crowbar
ALIGNED8 static const Texture mb64_btn_pipebar_ci4[] = {
#include "textures/mb64_buttons/pipebar.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_pipebar_pal_rgba16[] = {
#include "textures/mb64_buttons/pipebar.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_pipebar);

// Bullet Bill Mask
ALIGNED8 static const Texture mb64_btn_bulletmask_ci4[] = {
#include "textures/mb64_buttons/bulletmask.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bulletmask_pal_rgba16[] = {
#include "textures/mb64_buttons/bulletmask.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_bulletmask);

// King Bob-omb
ALIGNED8 static const Texture mb64_btn_kingbobomb_ci4[] = {
#include "textures/mb64_buttons/kingbobomb.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_kingbobomb_pal_rgba16[] = {
#include "textures/mb64_buttons/kingbobomb.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_kingbobomb);

// Wiggler
ALIGNED8 static const Texture mb64_btn_wiggler_ci8[] = {
#include "textures/mb64_buttons/wiggler.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_wiggler_pal_rgba16[] = {
#include "textures/mb64_buttons/wiggler.ci8.pal"
};
DEFINE_CI8_BUTTON(mb64_btn_wiggler);

// Bowser
ALIGNED8 static const Texture mb64_btn_bowser_ci8[] = {
#include "textures/mb64_buttons/bowser.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bowser_pal_rgba16[] = {
#include "textures/mb64_buttons/bowser.ci8.pal"
};
DEFINE_CI8_BUTTON(mb64_btn_bowser);

// Bowser Bomb
ALIGNED8 static const Texture mb64_btn_bowserbomb_ci4[] = {
#include "textures/mb64_buttons/bowserbomb.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bowserbomb_pal_rgba16[] = {
#include "textures/mb64_buttons/bowserbomb.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_bowserbomb);

// Save & Test
ALIGNED8 static const Texture mb64_btn_check_ci4[] = {
#include "textures/mb64_buttons/check.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_check_pal_rgba16[] = {
#include "textures/mb64_buttons/check.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_check);

// Level Settings
ALIGNED8 static const Texture mb64_btn_settings_ci4[] = {
#include "textures/mb64_buttons/settings.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_settings_pal_rgba16[] = {
#include "textures/mb64_buttons/settings.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_settings);

// Blank
ALIGNED8 static const Texture mb64_btn_blank_ci4[] = {
#include "textures/mb64_buttons/blank.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_blank_pal_rgba16[] = {
#include "textures/mb64_buttons/blank.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_blank);

ALIGNED8 static const Texture mb64_btn_blankterrain_ci4[] = {
#include "textures/mb64_buttons/blankterrain.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_blankterrain_pal_rgba16[] = {
#include "textures/mb64_buttons/blankterrain.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_blankterrain);

ALIGNED8 static const Texture mb64_btn_blanksettings_ci4[] = {
#include "textures/mb64_buttons/blanksettings.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_blanksettings_pal_rgba16[] = {
#include "textures/mb64_buttons/blanksettings.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_blanksettings);

// Warp Pipe
ALIGNED8 static const Texture mb64_btn_pipe_ci4[] = {
#include "textures/mb64_buttons/pipe.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_pipe_pal_rgba16[] = {
#include "textures/mb64_buttons/pipe.ci4.pal"
};
DEFINE_CI4_BUTTON(mb64_btn_pipe);
