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
ALIGNED8 static const Texture mb64_btn_tile_ci8[] = {
#include "textures/mb64_buttons/tile.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_tile_pal_rgba16[] = {
#include "textures/mb64_buttons/tile.ci8.pal"
};
DEFINE_CI8(mb64_btn_tile);

// Slab
ALIGNED8 static const Texture mb64_btn_slabtile_ci8[] = {
#include "textures/mb64_buttons/slabtile.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_slabtile_pal_rgba16[] = {
#include "textures/mb64_buttons/slabtile.ci8.pal"
};
DEFINE_CI8(mb64_btn_slabtile);

// Slope
ALIGNED8 static const Texture mb64_btn_slope_ci8[] = {
#include "textures/mb64_buttons/slope.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_slope_pal_rgba16[] = {
#include "textures/mb64_buttons/slope.ci8.pal"
};
DEFINE_CI8(mb64_btn_slope);

// Outer Corner
ALIGNED8 static const Texture mb64_btn_corner_ci8[] = {
#include "textures/mb64_buttons/corner.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_corner_pal_rgba16[] = {
#include "textures/mb64_buttons/corner.ci8.pal"
};
DEFINE_CI8(mb64_btn_corner);

// Inner Corner
ALIGNED8 static const Texture mb64_btn_icorner_ci8[] = {
#include "textures/mb64_buttons/icorner.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_icorner_pal_rgba16[] = {
#include "textures/mb64_buttons/icorner.ci8.pal"
};
DEFINE_CI8(mb64_btn_icorner);

// Vertical Slab
ALIGNED8 static const Texture mb64_btn_vslab_ci8[] = {
#include "textures/mb64_buttons/vslab.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_vslab_pal_rgba16[] = {
#include "textures/mb64_buttons/vslab.ci8.pal"
};
DEFINE_CI8(mb64_btn_vslab);

// Vertical Slope
ALIGNED8 static const Texture mb64_btn_sideslope_ci8[] = {
#include "textures/mb64_buttons/sideslope.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_sideslope_pal_rgba16[] = {
#include "textures/mb64_buttons/sideslope.ci8.pal"
};
DEFINE_CI8(mb64_btn_sideslope);

// Sloped Corner
ALIGNED8 static const Texture mb64_btn_triangle_ci8[] = {
#include "textures/mb64_buttons/triangle.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_triangle_pal_rgba16[] = {
#include "textures/mb64_buttons/triangle.ci8.pal"
};
DEFINE_CI8(mb64_btn_triangle);

// Inverted Sloped Corner
ALIGNED8 static const Texture mb64_btn_isc_ci8[] = {
#include "textures/mb64_buttons/isc.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_isc_pal_rgba16[] = {
#include "textures/mb64_buttons/isc.ci8.pal"
};
DEFINE_CI8(mb64_btn_isc);

// Lower Gentle Slope
ALIGNED8 static const Texture mb64_btn_lgs_ci8[] = {
#include "textures/mb64_buttons/lgs.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_lgs_pal_rgba16[] = {
#include "textures/mb64_buttons/lgs.ci8.pal"
};
DEFINE_CI8(mb64_btn_lgs);

// Upper Gentle Slope
ALIGNED8 static const Texture mb64_btn_ugs_ci8[] = {
#include "textures/mb64_buttons/ugs.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_ugs_pal_rgba16[] = {
#include "textures/mb64_buttons/ugs.ci8.pal"
};
DEFINE_CI8(mb64_btn_ugs);

// Intangible Tile
ALIGNED8 static const Texture mb64_btn_troll_ci8[] = {
#include "textures/mb64_buttons/troll.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_troll_pal_rgba16[] = {
#include "textures/mb64_buttons/troll.ci8.pal"
};
DEFINE_CI8(mb64_btn_troll);

// Water
ALIGNED8 static const Texture mb64_btn_water_ci8[] = {
#include "textures/mb64_buttons/water.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_water_pal_rgba16[] = {
#include "textures/mb64_buttons/water.ci8.pal"
};
DEFINE_CI8(mb64_btn_water);

// Fence
ALIGNED8 static const Texture mb64_btn_fence_ci8[] = {
#include "textures/mb64_buttons/fence.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_fence_pal_rgba16[] = {
#include "textures/mb64_buttons/fence.ci8.pal"
};
DEFINE_CI8(mb64_btn_fence);

// Iron Mesh
ALIGNED8 static const Texture mb64_btn_bars_ci4[] = {
#include "textures/mb64_buttons/bars.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bars_pal_rgba16[] = {
#include "textures/mb64_buttons/bars.ci4.pal"
};
DEFINE_CI4(mb64_btn_bars);

// Pole
ALIGNED8 static const Texture mb64_btn_pole_ci4[] = {
#include "textures/mb64_buttons/pole.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_pole_pal_rgba16[] = {
#include "textures/mb64_buttons/pole.ci4.pal"
};
DEFINE_CI4(mb64_btn_pole);

// Tree
ALIGNED8 static const Texture mb64_btn_tree_ci8[] = {
#include "textures/mb64_buttons/tree.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_tree_pal_rgba16[] = {
#include "textures/mb64_buttons/tree.ci8.pal"
};
DEFINE_CI8(mb64_btn_tree);

// Cull Marker
ALIGNED8 static const Texture mb64_btn_cull_ci8[] = {
#include "textures/mb64_buttons/cull.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_cull_pal_rgba16[] = {
#include "textures/mb64_buttons/cull.ci8.pal"
};
DEFINE_CI8(mb64_btn_cull);

// Power Star
ALIGNED8 static const Texture mb64_btn_star_ci8[] = {
#include "textures/mb64_buttons/star.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_star_pal_rgba16[] = {
#include "textures/mb64_buttons/star.ci8.pal"
};
DEFINE_CI8(mb64_btn_star);

// Red Coins
ALIGNED8 static const Texture mb64_btn_rcs_ci8[] = {
#include "textures/mb64_buttons/rcs.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_rcs_pal_rgba16[] = {
#include "textures/mb64_buttons/rcs.ci8.pal"
};
DEFINE_CI8(mb64_btn_rcs);

// Star Triggers
ALIGNED8 static const Texture mb64_btn_triggerstar_ci8[] = {
#include "textures/mb64_buttons/triggerstar.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_triggerstar_pal_rgba16[] = {
#include "textures/mb64_buttons/triggerstar.ci8.pal"
};
DEFINE_CI8(mb64_btn_triggerstar);

// Yellow Coin
ALIGNED8 static const Texture mb64_btn_coin_ci8[] = {
#include "textures/mb64_buttons/coin.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_coin_pal_rgba16[] = {
#include "textures/mb64_buttons/coin.ci8.pal"
};
DEFINE_CI8(mb64_btn_coin);

// Coin Formation
ALIGNED8 static const Texture mb64_btn_cformation_ci8[] = {
#include "textures/mb64_buttons/cformation.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_cformation_pal_rgba16[] = {
#include "textures/mb64_buttons/cformation.ci8.pal"
};
DEFINE_CI8(mb64_btn_cformation);

// Green Coin
ALIGNED8 static const Texture mb64_btn_greencoin_ci8[] = {
#include "textures/mb64_buttons/greencoin.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_greencoin_pal_rgba16[] = {
#include "textures/mb64_buttons/greencoin.ci8.pal"
};
DEFINE_CI8(mb64_btn_greencoin);

// Red Coin
ALIGNED8 static const Texture mb64_btn_redcoin_ci8[] = {
#include "textures/mb64_buttons/redcoin.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_redcoin_pal_rgba16[] = {
#include "textures/mb64_buttons/redcoin.ci8.pal"
};
DEFINE_CI8(mb64_btn_redcoin);

// Blue Coin
ALIGNED8 static const Texture mb64_btn_bluecoin_ci8[] = {
#include "textures/mb64_buttons/bluecoin.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bluecoin_pal_rgba16[] = {
#include "textures/mb64_buttons/bluecoin.ci8.pal"
};
DEFINE_CI8(mb64_btn_bluecoin);

// Blue Coin Switch
ALIGNED8 static const Texture mb64_btn_bcs_ci8[] = {
#include "textures/mb64_buttons/bcs.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bcs_pal_rgba16[] = {
#include "textures/mb64_buttons/bcs.ci8.pal"
};
DEFINE_CI8(mb64_btn_bcs);

// Item Box
ALIGNED8 static const Texture mb64_btn_excla_ci4[] = {
#include "textures/mb64_buttons/excla.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_excla_pal_rgba16[] = {
#include "textures/mb64_buttons/excla.ci4.pal"
};
DEFINE_CI4(mb64_btn_excla);

// Star Trigger
ALIGNED8 static const Texture mb64_btn_trigger_ci8[] = {
#include "textures/mb64_buttons/trigger.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_trigger_pal_rgba16[] = {
#include "textures/mb64_buttons/trigger.ci8.pal"
};
DEFINE_CI8(mb64_btn_trigger);

// Recovery Heart
ALIGNED8 static const Texture mb64_btn_heart_ci8[] = {
#include "textures/mb64_buttons/heart.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_heart_pal_rgba16[] = {
#include "textures/mb64_buttons/heart.ci8.pal"
};
DEFINE_CI8(mb64_btn_heart);

// Moving Platform
ALIGNED8 static const Texture mb64_btn_checker_ci8[] = {
#include "textures/mb64_buttons/checker.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_checker_pal_rgba16[] = {
#include "textures/mb64_buttons/checker.ci8.pal"
};
DEFINE_CI8(mb64_btn_checker);

// Purple Switch
ALIGNED8 static const Texture mb64_btn_purpleswitch_ci8[] = {
#include "textures/mb64_buttons/purpleswitch.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_purpleswitch_pal_rgba16[] = {
#include "textures/mb64_buttons/purpleswitch.ci8.pal"
};
DEFINE_CI8(mb64_btn_purpleswitch);

// Timed Box
ALIGNED8 static const Texture mb64_btn_tbox_ci8[] = {
#include "textures/mb64_buttons/tbox.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_tbox_pal_rgba16[] = {
#include "textures/mb64_buttons/tbox.ci8.pal"
};
DEFINE_CI8(mb64_btn_tbox);

// Inverted Timed Box
ALIGNED8 static const Texture mb64_btn_tblock_ci8[] = {
#include "textures/mb64_buttons/tblock.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_tblock_pal_rgba16[] = {
#include "textures/mb64_buttons/tblock.ci8.pal"
};
DEFINE_CI8(mb64_btn_tblock);

// Breakable Box
ALIGNED8 static const Texture mb64_btn_corkbox_ci8[] = {
#include "textures/mb64_buttons/corkbox.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_corkbox_pal_rgba16[] = {
#include "textures/mb64_buttons/corkbox.ci8.pal"
};
DEFINE_CI8(mb64_btn_corkbox);

// Reinforced Box
ALIGNED8 static const Texture mb64_btn_rfbox_ci8[] = {
#include "textures/mb64_buttons/rfbox.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_rfbox_pal_rgba16[] = {
#include "textures/mb64_buttons/rfbox.ci8.pal"
};
DEFINE_CI8(mb64_btn_rfbox);

// Water Diamond
ALIGNED8 static const Texture mb64_btn_water_diamond_ci8[] = {
#include "textures/mb64_buttons/water_diamond.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_water_diamond_pal_rgba16[] = {
#include "textures/mb64_buttons/water_diamond.ci8.pal"
};
DEFINE_CI8(mb64_btn_water_diamond);

// Wooden Platform
ALIGNED8 static const Texture mb64_btn_woodplat_ci8[] = {
#include "textures/mb64_buttons/woodplat.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_woodplat_pal_rgba16[] = {
#include "textures/mb64_buttons/woodplat.ci8.pal"
};
DEFINE_CI8(mb64_btn_woodplat);

// Bill Board
ALIGNED8 static const Texture mb64_btn_sign_ci8[] = {
#include "textures/mb64_buttons/sign.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_sign_pal_rgba16[] = {
#include "textures/mb64_buttons/sign.ci8.pal"
};
DEFINE_CI8(mb64_btn_sign);

// Bob-omb Buddy
ALIGNED8 static const Texture mb64_btn_buddy_ci8[] = {
#include "textures/mb64_buttons/buddy.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_buddy_pal_rgba16[] = {
#include "textures/mb64_buttons/buddy.ci8.pal"
};
DEFINE_CI8(mb64_btn_buddy);

// Moleman
ALIGNED8 static const Texture mb64_btn_moleman_ci8[] = {
#include "textures/mb64_buttons/moleman.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_moleman_pal_rgba16[] = {
#include "textures/mb64_buttons/moleman.ci8.pal"
};
DEFINE_CI8(mb64_btn_moleman);

// Cobie
ALIGNED8 static const Texture mb64_btn_cobie_ci8[] = {
#include "textures/mb64_buttons/cobie.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_cobie_pal_rgba16[] = {
#include "textures/mb64_buttons/cobie.ci8.pal"
};
DEFINE_CI8(mb64_btn_cobie);

// Badge
ALIGNED8 static const Texture mb64_btn_badge_ci8[] = {
#include "textures/mb64_buttons/badge.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_badge_pal_rgba16[] = {
#include "textures/mb64_buttons/badge.ci8.pal"
};
DEFINE_CI8(mb64_btn_badge);

// Noteblock
ALIGNED8 static const Texture mb64_btn_noteblock_ci8[] = {
#include "textures/mb64_buttons/noteblock.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_noteblock_pal_rgba16[] = {
#include "textures/mb64_buttons/noteblock.ci8.pal"
};
DEFINE_CI8(mb64_btn_noteblock);

// On-Off Button
ALIGNED8 static const Texture mb64_btn_switch_ci8[] = {
#include "textures/mb64_buttons/switch.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_switch_pal_rgba16[] = {
#include "textures/mb64_buttons/switch.ci8.pal"
};
DEFINE_CI8(mb64_btn_switch);

// On-Off Block
ALIGNED8 static const Texture mb64_btn_block_ci8[] = {
#include "textures/mb64_buttons/block.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_block_pal_rgba16[] = {
#include "textures/mb64_buttons/block.ci8.pal"
};
DEFINE_CI8(mb64_btn_block);

// Conveyor
ALIGNED8 static const Texture mb64_btn_conveyor_ci8[] = {
#include "textures/mb64_buttons/conveyor.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_conveyor_pal_rgba16[] = {
#include "textures/mb64_buttons/conveyor.ci8.pal"
};
DEFINE_CI8(mb64_btn_conveyor);

// Toad
ALIGNED8 static const Texture mb64_btn_toad_ci8[] = {
#include "textures/mb64_buttons/toad.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_toad_pal_rgba16[] = {
#include "textures/mb64_buttons/toad.ci8.pal"
};
DEFINE_CI8(mb64_btn_toad);

// Tuxie
ALIGNED8 static const Texture mb64_btn_tuxie_ci8[] = {
#include "textures/mb64_buttons/tuxie.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_tuxie_pal_rgba16[] = {
#include "textures/mb64_buttons/tuxie.ci8.pal"
};
DEFINE_CI8(mb64_btn_tuxie);

// Ukiki
ALIGNED8 static const Texture mb64_btn_ukiki_ci8[] = {
#include "textures/mb64_buttons/ukiki.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_ukiki_pal_rgba16[] = {
#include "textures/mb64_buttons/ukiki.ci8.pal"
};
DEFINE_CI8(mb64_btn_ukiki);

// Koopa the Quick
ALIGNED8 static const Texture mb64_btn_kuppaq_ci8[] = {
#include "textures/mb64_buttons/kuppaq.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_kuppaq_pal_rgba16[] = {
#include "textures/mb64_buttons/kuppaq.ci8.pal"
};
DEFINE_CI8(mb64_btn_kuppaq);

// Goomba
ALIGNED8 static const Texture mb64_btn_goomba_ci8[] = {
#include "textures/mb64_buttons/goomba.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_goomba_pal_rgba16[] = {
#include "textures/mb64_buttons/goomba.ci8.pal"
};
DEFINE_CI8(mb64_btn_goomba);

// Huge Goomba
ALIGNED8 static const Texture mb64_btn_goomba_b_ci8[] = {
#include "textures/mb64_buttons/goomba_b.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_goomba_b_pal_rgba16[] = {
#include "textures/mb64_buttons/goomba_b.ci8.pal"
};
DEFINE_CI8(mb64_btn_goomba_b);

// Tiny Goomba
ALIGNED8 static const Texture mb64_btn_goomba_s_ci8[] = {
#include "textures/mb64_buttons/goomba_s.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_goomba_s_pal_rgba16[] = {
#include "textures/mb64_buttons/goomba_s.ci8.pal"
};
DEFINE_CI8(mb64_btn_goomba_s);

// Bob-omb
ALIGNED8 static const Texture mb64_btn_bobomb_ci8[] = {
#include "textures/mb64_buttons/bobomb.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bobomb_pal_rgba16[] = {
#include "textures/mb64_buttons/bobomb.ci8.pal"
};
DEFINE_CI8(mb64_btn_bobomb);

// Chuckya
ALIGNED8 static const Texture mb64_btn_chuckya_ci8[] = {
#include "textures/mb64_buttons/chuckya.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_chuckya_pal_rgba16[] = {
#include "textures/mb64_buttons/chuckya.ci8.pal"
};
DEFINE_CI8(mb64_btn_chuckya);

// Koopa
ALIGNED8 static const Texture mb64_btn_kuppa_ci8[] = {
#include "textures/mb64_buttons/kuppa.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_kuppa_pal_rgba16[] = {
#include "textures/mb64_buttons/kuppa.ci8.pal"
};
DEFINE_CI8(mb64_btn_kuppa);

// Lakitu
ALIGNED8 static const Texture mb64_btn_lakitu_ci8[] = {
#include "textures/mb64_buttons/lakitu.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_lakitu_pal_rgba16[] = {
#include "textures/mb64_buttons/lakitu.ci8.pal"
};
DEFINE_CI8(mb64_btn_lakitu);

// Fly Guy
ALIGNED8 static const Texture mb64_btn_flyguy_ci8[] = {
#include "textures/mb64_buttons/flyguy.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_flyguy_pal_rgba16[] = {
#include "textures/mb64_buttons/flyguy.ci8.pal"
};
DEFINE_CI8(mb64_btn_flyguy);

// Snufit
ALIGNED8 static const Texture mb64_btn_snufit_ci8[] = {
#include "textures/mb64_buttons/snufit.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_snufit_pal_rgba16[] = {
#include "textures/mb64_buttons/snufit.ci8.pal"
};
DEFINE_CI8(mb64_btn_snufit);

// Thwomp
ALIGNED8 static const Texture mb64_btn_thwomp_ci8[] = {
#include "textures/mb64_buttons/thwomp.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_thwomp_pal_rgba16[] = {
#include "textures/mb64_buttons/thwomp.ci8.pal"
};
DEFINE_CI8(mb64_btn_thwomp);

// Grindel
ALIGNED8 static const Texture mb64_btn_grindel_ci8[] = {
#include "textures/mb64_buttons/grindel.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_grindel_pal_rgba16[] = {
#include "textures/mb64_buttons/grindel.ci8.pal"
};
DEFINE_CI8(mb64_btn_grindel);

// Whomp
ALIGNED8 static const Texture mb64_btn_whomp_ci8[] = {
#include "textures/mb64_buttons/whomp.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_whomp_pal_rgba16[] = {
#include "textures/mb64_buttons/whomp.ci8.pal"
};
DEFINE_CI8(mb64_btn_whomp);

// King Whomp
ALIGNED8 static const Texture mb64_btn_boss_whomp_ci8[] = {
#include "textures/mb64_buttons/boss_whomp.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_boss_whomp_pal_rgba16[] = {
#include "textures/mb64_buttons/boss_whomp.ci8.pal"
};
DEFINE_CI8(mb64_btn_boss_whomp);

// Bully
ALIGNED8 static const Texture mb64_btn_bully_ci8[] = {
#include "textures/mb64_buttons/bully.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bully_pal_rgba16[] = {
#include "textures/mb64_buttons/bully.ci8.pal"
};
DEFINE_CI8(mb64_btn_bully);

// Chill Bully
ALIGNED8 static const Texture mb64_btn_chillbully_ci8[] = {
#include "textures/mb64_buttons/chillbully.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_chillbully_pal_rgba16[] = {
#include "textures/mb64_buttons/chillbully.ci8.pal"
};
DEFINE_CI8(mb64_btn_chillbully);

// Big Bully
ALIGNED8 static const Texture mb64_btn_boss_bully_ci8[] = {
#include "textures/mb64_buttons/boss_bully.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_boss_bully_pal_rgba16[] = {
#include "textures/mb64_buttons/boss_bully.ci8.pal"
};
DEFINE_CI8(mb64_btn_boss_bully);

// Big Chill Bully
ALIGNED8 static const Texture mb64_btn_boss_chillbully_ci8[] = {
#include "textures/mb64_buttons/boss_chillbully.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_boss_chillbully_pal_rgba16[] = {
#include "textures/mb64_buttons/boss_chillbully.ci8.pal"
};
DEFINE_CI8(mb64_btn_boss_chillbully);

// Motos
ALIGNED8 static const Texture mb64_btn_motos_ci8[] = {
#include "textures/mb64_buttons/motos.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_motos_pal_rgba16[] = {
#include "textures/mb64_buttons/motos.ci8.pal"
};
DEFINE_CI8(mb64_btn_motos);

// Heave-Ho
ALIGNED8 static const Texture mb64_btn_heaveho_ci8[] = {
#include "textures/mb64_buttons/heaveho.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_heaveho_pal_rgba16[] = {
#include "textures/mb64_buttons/heaveho.ci8.pal"
};
DEFINE_CI8(mb64_btn_heaveho);

// Bullet Bill
ALIGNED8 static const Texture mb64_btn_bill_ci8[] = {
#include "textures/mb64_buttons/bill.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bill_pal_rgba16[] = {
#include "textures/mb64_buttons/bill.ci8.pal"
};
DEFINE_CI8(mb64_btn_bill);

// Amp
ALIGNED8 static const Texture mb64_btn_amp_ci8[] = {
#include "textures/mb64_buttons/amp.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_amp_pal_rgba16[] = {
#include "textures/mb64_buttons/amp.ci8.pal"
};
DEFINE_CI8(mb64_btn_amp);

// Piranha Plant
ALIGNED8 static const Texture mb64_btn_plant_ci8[] = {
#include "textures/mb64_buttons/plant.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_plant_pal_rgba16[] = {
#include "textures/mb64_buttons/plant.ci8.pal"
};
DEFINE_CI8(mb64_btn_plant);

// Huge Piranha Plant
ALIGNED8 static const Texture mb64_btn_plant_b_ci8[] = {
#include "textures/mb64_buttons/plant_b.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_plant_b_pal_rgba16[] = {
#include "textures/mb64_buttons/plant_b.ci8.pal"
};
DEFINE_CI8(mb64_btn_plant_b);

// Tiny Piranha Plant
ALIGNED8 static const Texture mb64_btn_plant_s_ci8[] = {
#include "textures/mb64_buttons/plant_s.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_plant_s_pal_rgba16[] = {
#include "textures/mb64_buttons/plant_s.ci8.pal"
};
DEFINE_CI8(mb64_btn_plant_s);

// Boo
ALIGNED8 static const Texture mb64_btn_boo_ci8[] = {
#include "textures/mb64_buttons/boo.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_boo_pal_rgba16[] = {
#include "textures/mb64_buttons/boo.ci8.pal"
};
DEFINE_CI8(mb64_btn_boo);

// Big Boo
ALIGNED8 static const Texture mb64_btn_boss_boo_ci8[] = {
#include "textures/mb64_buttons/boss_boo.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_boss_boo_pal_rgba16[] = {
#include "textures/mb64_buttons/boss_boo.ci8.pal"
};
DEFINE_CI8(mb64_btn_boss_boo);

// Mr. I
ALIGNED8 static const Texture mb64_btn_mri_ci8[] = {
#include "textures/mb64_buttons/mri.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_mri_pal_rgba16[] = {
#include "textures/mb64_buttons/mri.ci8.pal"
};
DEFINE_CI8(mb64_btn_mri);

// Scuttlebug
ALIGNED8 static const Texture mb64_btn_scuttlebug_ci8[] = {
#include "textures/mb64_buttons/scuttlebug.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_scuttlebug_pal_rgba16[] = {
#include "textures/mb64_buttons/scuttlebug.ci8.pal"
};
DEFINE_CI8(mb64_btn_scuttlebug);

// Spindrift
ALIGNED8 static const Texture mb64_btn_spindrift_ci8[] = {
#include "textures/mb64_buttons/spindrift.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_spindrift_pal_rgba16[] = {
#include "textures/mb64_buttons/spindrift.ci8.pal"
};
DEFINE_CI8(mb64_btn_spindrift);

// Mr. Blizzard
ALIGNED8 static const Texture mb64_btn_blizzard_ci8[] = {
#include "textures/mb64_buttons/blizzard.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_blizzard_pal_rgba16[] = {
#include "textures/mb64_buttons/blizzard.ci8.pal"
};
DEFINE_CI8(mb64_btn_blizzard);

// Moneybag
ALIGNED8 static const Texture mb64_btn_moneybag_ci8[] = {
#include "textures/mb64_buttons/moneybag.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_moneybag_pal_rgba16[] = {
#include "textures/mb64_buttons/moneybag.ci8.pal"
};
DEFINE_CI8(mb64_btn_moneybag);

// Skeeter
ALIGNED8 static const Texture mb64_btn_skeeter_ci8[] = {
#include "textures/mb64_buttons/skeeter.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_skeeter_pal_rgba16[] = {
#include "textures/mb64_buttons/skeeter.ci8.pal"
};
DEFINE_CI8(mb64_btn_skeeter);

// Pokey
ALIGNED8 static const Texture mb64_btn_pokey_ci8[] = {
#include "textures/mb64_buttons/pokey.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_pokey_pal_rgba16[] = {
#include "textures/mb64_buttons/pokey.ci8.pal"
};
DEFINE_CI8(mb64_btn_pokey);

// Rex
ALIGNED8 static const Texture mb64_btn_rex_ci8[] = {
#include "textures/mb64_buttons/rex.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_rex_pal_rgba16[] = {
#include "textures/mb64_buttons/rex.ci8.pal"
};
DEFINE_CI8(mb64_btn_rex);

// Hammer Bro
ALIGNED8 static const Texture mb64_btn_hammerbro_ci8[] = {
#include "textures/mb64_buttons/hammerbro.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_hammerbro_pal_rgba16[] = {
#include "textures/mb64_buttons/hammerbro.ci8.pal"
};
DEFINE_CI8(mb64_btn_hammerbro);

// Fire Bro
ALIGNED8 static const Texture mb64_btn_firebro_ci8[] = {
#include "textures/mb64_buttons/firebro.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_firebro_pal_rgba16[] = {
#include "textures/mb64_buttons/firebro.ci8.pal"
};
DEFINE_CI8(mb64_btn_firebro);

// Podoboo
ALIGNED8 static const Texture mb64_btn_podoboo_ci8[] = {
#include "textures/mb64_buttons/podoboo.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_podoboo_pal_rgba16[] = {
#include "textures/mb64_buttons/podoboo.ci8.pal"
};
DEFINE_CI8(mb64_btn_podoboo);

// Cosmic Phantasm
ALIGNED8 static const Texture mb64_btn_phantasm_ci8[] = {
#include "textures/mb64_buttons/phantasm.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_phantasm_pal_rgba16[] = {
#include "textures/mb64_buttons/phantasm.ci8.pal"
};
DEFINE_CI8(mb64_btn_phantasm);

// Red Flame
ALIGNED8 static const Texture mb64_btn_fire_red_ci8[] = {
#include "textures/mb64_buttons/fire_red.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_fire_red_pal_rgba16[] = {
#include "textures/mb64_buttons/fire_red.ci8.pal"
};
DEFINE_CI8(mb64_btn_fire_red);

// Blue Flame
ALIGNED8 static const Texture mb64_btn_fire_blue_ci8[] = {
#include "textures/mb64_buttons/fire_blue.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_fire_blue_pal_rgba16[] = {
#include "textures/mb64_buttons/fire_blue.ci8.pal"
};
DEFINE_CI8(mb64_btn_fire_blue);

// Flamethrower
ALIGNED8 static const Texture mb64_btn_flamethrower_ci8[] = {
#include "textures/mb64_buttons/flamethrower.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_flamethrower_pal_rgba16[] = {
#include "textures/mb64_buttons/flamethrower.ci8.pal"
};
DEFINE_CI8(mb64_btn_flamethrower);

// Fire Spitter
ALIGNED8 static const Texture mb64_btn_firespitter_ci8[] = {
#include "textures/mb64_buttons/firespitter.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_firespitter_pal_rgba16[] = {
#include "textures/mb64_buttons/firespitter.ci8.pal"
};
DEFINE_CI8(mb64_btn_firespitter);

// Fire Spinner
ALIGNED8 static const Texture mb64_btn_firebar_ci8[] = {
#include "textures/mb64_buttons/firebar.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_firebar_pal_rgba16[] = {
#include "textures/mb64_buttons/firebar.ci8.pal"
};
DEFINE_CI8(mb64_btn_firebar);

// Bowling Ball
ALIGNED8 static const Texture mb64_btn_bball_ci8[] = {
#include "textures/mb64_buttons/bball.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bball_pal_rgba16[] = {
#include "textures/mb64_buttons/bball.ci8.pal"
};
DEFINE_CI8(mb64_btn_bball);

// Chicken
ALIGNED8 static const Texture mb64_btn_chicken_ci8[] = {
#include "textures/mb64_buttons/chicken.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_chicken_pal_rgba16[] = {
#include "textures/mb64_buttons/chicken.ci8.pal"
};
DEFINE_CI8(mb64_btn_chicken);

// Crablet
ALIGNED8 static const Texture mb64_btn_crablet_ci8[] = {
#include "textures/mb64_buttons/crablet.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_crablet_pal_rgba16[] = {
#include "textures/mb64_buttons/crablet.ci8.pal"
};
DEFINE_CI8(mb64_btn_crablet);

// Showrunner
ALIGNED8 static const Texture mb64_btn_showrunner_ci8[] = {
#include "textures/mb64_buttons/showrunner.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_showrunner_pal_rgba16[] = {
#include "textures/mb64_buttons/showrunner.ci8.pal"
};
DEFINE_CI8(mb64_btn_showrunner);

// Mario Spawn
ALIGNED8 static const Texture mb64_btn_spawn_ci8[] = {
#include "textures/mb64_buttons/spawn.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_spawn_pal_rgba16[] = {
#include "textures/mb64_buttons/spawn.ci8.pal"
};
DEFINE_CI8(mb64_btn_spawn);

// Throwable Box
ALIGNED8 static const Texture mb64_btn_sbox_ci8[] = {
#include "textures/mb64_buttons/sbox.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_sbox_pal_rgba16[] = {
#include "textures/mb64_buttons/sbox.ci8.pal"
};
DEFINE_CI8(mb64_btn_sbox);

// Crazy Box
ALIGNED8 static const Texture mb64_btn_cbox_ci8[] = {
#include "textures/mb64_buttons/cbox.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_cbox_pal_rgba16[] = {
#include "textures/mb64_buttons/cbox.ci8.pal"
};
DEFINE_CI8(mb64_btn_cbox);

// Crowbar
ALIGNED8 static const Texture mb64_btn_pipebar_ci8[] = {
#include "textures/mb64_buttons/pipebar.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_pipebar_pal_rgba16[] = {
#include "textures/mb64_buttons/pipebar.ci8.pal"
};
DEFINE_CI8(mb64_btn_pipebar);

// Bullet Bill Mask
ALIGNED8 static const Texture mb64_btn_mask_ci8[] = {
#include "textures/mb64_buttons/mask.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_mask_pal_rgba16[] = {
#include "textures/mb64_buttons/mask.ci8.pal"
};
DEFINE_CI8(mb64_btn_mask);

// King Bob-omb
ALIGNED8 static const Texture mb64_btn_boss_kb_ci8[] = {
#include "textures/mb64_buttons/boss_kb.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_boss_kb_pal_rgba16[] = {
#include "textures/mb64_buttons/boss_kb.ci8.pal"
};
DEFINE_CI8(mb64_btn_boss_kb);

// Wiggler
ALIGNED8 static const Texture mb64_btn_boss_wiggler_ci8[] = {
#include "textures/mb64_buttons/boss_wiggler.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_boss_wiggler_pal_rgba16[] = {
#include "textures/mb64_buttons/boss_wiggler.ci8.pal"
};
DEFINE_CI8(mb64_btn_boss_wiggler);

// Bowser
ALIGNED8 static const Texture mb64_btn_boss_bowser_ci8[] = {
#include "textures/mb64_buttons/boss_bowser.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_boss_bowser_pal_rgba16[] = {
#include "textures/mb64_buttons/boss_bowser.ci8.pal"
};
DEFINE_CI8(mb64_btn_boss_bowser);

// Bowser Bomb
ALIGNED8 static const Texture mb64_btn_bbomb_ci8[] = {
#include "textures/mb64_buttons/bbomb.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_bbomb_pal_rgba16[] = {
#include "textures/mb64_buttons/bbomb.ci8.pal"
};
DEFINE_CI8(mb64_btn_bbomb);

// Save & Test
ALIGNED8 static const Texture mb64_btn_check_ci8[] = {
#include "textures/mb64_buttons/check.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_check_pal_rgba16[] = {
#include "textures/mb64_buttons/check.ci8.pal"
};
DEFINE_CI8(mb64_btn_check);

// Level Settings
ALIGNED8 static const Texture mb64_btn_settings_ci8[] = {
#include "textures/mb64_buttons/settings.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_settings_pal_rgba16[] = {
#include "textures/mb64_buttons/settings.ci8.pal"
};
DEFINE_CI8(mb64_btn_settings);

// Blank
ALIGNED8 static const Texture mb64_btn_blank_ci4[] = {
#include "textures/mb64_buttons/blank.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_btn_blank_pal_rgba16[] = {
#include "textures/mb64_buttons/blank.ci4.pal"
};
DEFINE_CI4(mb64_btn_blank);

// Warp Pipe
ALIGNED8 static const Texture mb64_btn_pipe_ci8[] = {
#include "textures/mb64_buttons/pipe.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_btn_pipe_pal_rgba16[] = {
#include "textures/mb64_buttons/pipe.ci8.pal"
};
DEFINE_CI8(mb64_btn_pipe);
