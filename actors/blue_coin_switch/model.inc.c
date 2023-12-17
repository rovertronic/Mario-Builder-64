

Gfx blue_coin_switch_blue_coin_switch_side_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 blue_coin_switch_blue_coin_switch_side_rgba16[] = {
	#include "actors/blue_coin_switch/blue_coin_switch_side.rgba16.inc.c"
};

Gfx blue_coin_switch_blue_coin_switch_top_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 blue_coin_switch_blue_coin_switch_top_rgba16[] = {
	#include "actors/blue_coin_switch/blue_coin_switch_top.rgba16.inc.c"
};

Vtx blue_coin_switch_Blue_coin_switch_model_mesh_layer_1_vtx_0[16] = {
	{{ {26, 0, 26}, 0, {1008, 496}, {0, 0, 127, 255} }},
	{{ {26, 26, 26}, 0, {1008, -16}, {0, 0, 127, 255} }},
	{{ {-25, 26, 26}, 0, {-16, -16}, {0, 0, 127, 255} }},
	{{ {-25, 0, 26}, 0, {-16, 496}, {0, 0, 127, 255} }},
	{{ {-25, 0, -25}, 0, {1008, 496}, {0, 0, 129, 255} }},
	{{ {26, 26, -25}, 0, {-16, -16}, {0, 0, 129, 255} }},
	{{ {26, 0, -25}, 0, {-16, 496}, {0, 0, 129, 255} }},
	{{ {-25, 26, -25}, 0, {1008, -16}, {0, 0, 129, 255} }},
	{{ {-25, 0, 26}, 0, {1008, 496}, {129, 0, 0, 255} }},
	{{ {-25, 26, -25}, 0, {-16, -16}, {129, 0, 0, 255} }},
	{{ {-25, 0, -25}, 0, {-16, 496}, {129, 0, 0, 255} }},
	{{ {-25, 26, 26}, 0, {1008, -16}, {129, 0, 0, 255} }},
	{{ {26, 0, -25}, 0, {1008, 496}, {127, 0, 0, 255} }},
	{{ {26, 26, -25}, 0, {1008, -16}, {127, 0, 0, 255} }},
	{{ {26, 26, 26}, 0, {-16, -16}, {127, 0, 0, 255} }},
	{{ {26, 0, 26}, 0, {-16, 496}, {127, 0, 0, 255} }},
};

Vtx blue_coin_switch_Blue_coin_switch_model_mesh_layer_1_vtx_1[4] = {
	{{ {26, 26, -25}, 0, {1008, -16}, {0, 127, 0, 255} }},
	{{ {-25, 26, 26}, 0, {-16, 1008}, {0, 127, 0, 255} }},
	{{ {26, 26, 26}, 0, {1008, 1008}, {0, 127, 0, 255} }},
	{{ {-25, 26, -25}, 0, {-16, -16}, {0, 127, 0, 255} }},
};


Gfx blue_coin_switch_Blue_coin_switch_model_mesh_layer_1[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_1PRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 3, G_AC_NONE | G_ZS_PIXEL),
	gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLightColor(LIGHT_1, 0xffffffff),
    gsSPLightColor(LIGHT_2, 0x7f7f7fff),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, blue_coin_switch_blue_coin_switch_side_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 511, 256),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 60),
	gsSPVertex(blue_coin_switch_Blue_coin_switch_model_mesh_layer_1_vtx_0 + 0, 16, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 7, 5, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 11, 9, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsDPPipeSync(),
    gsSPLightColor(LIGHT_1, 0xffffffff),
    gsSPLightColor(LIGHT_2, 0x7f7f7fff),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, blue_coin_switch_blue_coin_switch_top_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 1023, 256),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPVertex(blue_coin_switch_Blue_coin_switch_model_mesh_layer_1_vtx_1 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsDPSetCycleType(G_CYC_1CYCLE),
	gsDPPipeSync(),
	gsSPEndDisplayList(),
};

Gfx blue_coin_switch_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

