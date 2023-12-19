Gfx amp_amp_mouth_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 amp_amp_mouth_rgba16[] = {
	#include "actors/amp/amp_mouth.rgba16.inc.c"
};

Gfx amp_amp_eyes_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 amp_amp_eyes_rgba16[] = {
	#include "actors/amp/amp_eyes.rgba16.inc.c"
};

Gfx amp_amp_body_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 amp_amp_body_rgba16[] = {
	#include "actors/amp/amp_body.rgba16.inc.c"
};

Gfx amp_amp_electricity_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 amp_amp_electricity_rgba16[] = {
	#include "actors/amp/amp_electricity.rgba16.inc.c"
};

Vtx amp_root_mesh_layer_4_vtx_0[4] = {
	{{ {-18, -7, 41}, 0, {-16, -16}, {255, 255, 255, 255} }},
	{{ {18, -31, 30}, 0, {974, 974}, {255, 255, 255, 255} }},
	{{ {18, -7, 41}, 0, {974, -16}, {255, 255, 255, 255} }},
	{{ {-18, -31, 30}, 0, {-16, 974}, {255, 255, 255, 255} }},
};

Vtx amp_root_mesh_layer_4_vtx_1[4] = {
	{{ {-18, 17, 40}, 0, {-16, -16}, {255, 255, 255, 255} }},
	{{ {18, -7, 41}, 0, {974, 974}, {255, 255, 255, 255} }},
	{{ {18, 17, 40}, 0, {974, -16}, {255, 255, 255, 255} }},
	{{ {-18, -7, 41}, 0, {-16, 974}, {255, 255, 255, 255} }},
};

Vtx amp_billboard_mesh_layer_4_vtx_0[4] = {
	{{ {-39, -39, 0}, 0, {-16, 974}, {255, 255, 255, 255} }},
	{{ {40, 40, 0}, 0, {974, -16}, {255, 255, 255, 255} }},
	{{ {-39, 40, 0}, 0, {-16, -16}, {255, 255, 255, 255} }},
	{{ {40, -39, 0}, 0, {974, 974}, {255, 255, 255, 255} }},
};

Vtx amp_switch_option_eletricity_mesh_layer_4_vtx_0[5] = {
	{{ {56, 0, 22}, 0, {556, 512}, {255, 255, 255, 255} }},
	{{ {47, -37, 0}, 0, {240, -144}, {255, 255, 255, 255} }},
	{{ {56, 0, -22}, 0, {-78, 512}, {255, 255, 255, 255} }},
	{{ {56, 0, -22}, 0, {-78, 516}, {255, 255, 255, 255} }},
	{{ {47, 37, 0}, 0, {240, 1180}, {255, 255, 255, 255} }},
};

Vtx amp_switch_option_eletricity_001_mesh_layer_4_vtx_0[5] = {
	{{ {56, 0, -22}, 0, {-78, 516}, {255, 255, 255, 255} }},
	{{ {47, 37, 0}, 0, {240, 1180}, {255, 255, 255, 255} }},
	{{ {56, 0, 22}, 0, {556, 512}, {255, 255, 255, 255} }},
	{{ {47, -37, 0}, 0, {240, -144}, {255, 255, 255, 255} }},
	{{ {56, 0, -22}, 0, {-78, 512}, {255, 255, 255, 255} }},
};

Vtx amp_switch_option_eletricity_002_mesh_layer_4_vtx_0[5] = {
	{{ {56, 0, -22}, 0, {-78, 516}, {255, 255, 255, 255} }},
	{{ {47, 37, 0}, 0, {240, 1180}, {255, 255, 255, 255} }},
	{{ {56, 0, 22}, 0, {556, 512}, {255, 255, 255, 255} }},
	{{ {47, -37, 0}, 0, {240, -144}, {255, 255, 255, 255} }},
	{{ {56, 0, -22}, 0, {-78, 512}, {255, 255, 255, 255} }},
};

Vtx amp_switch_option_eletricity_003_mesh_layer_4_vtx_0[5] = {
	{{ {56, 0, -22}, 0, {-78, 516}, {255, 255, 255, 255} }},
	{{ {47, 37, 0}, 0, {240, 1180}, {255, 255, 255, 255} }},
	{{ {56, 0, 22}, 0, {556, 512}, {255, 255, 255, 255} }},
	{{ {47, -37, 0}, 0, {240, -144}, {255, 255, 255, 255} }},
	{{ {56, 0, -22}, 0, {-78, 512}, {255, 255, 255, 255} }},
};


Gfx amp_root_mesh_layer_4[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_1PRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 3, G_AC_NONE | G_ZS_PIXEL),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, amp_amp_mouth_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 1023, 256),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPVertex(amp_root_mesh_layer_4_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsDPPipeSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, amp_amp_eyes_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 1023, 256),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
	gsSPVertex(amp_root_mesh_layer_4_vtx_1 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsDPSetCycleType(G_CYC_1CYCLE),
	gsDPPipeSync(),
	gsSPEndDisplayList(),
};

Gfx amp_billboard_mesh_layer_4[] = {
	gsDPPipeSync(),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_1PRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 3, G_AC_NONE | G_ZS_PIXEL),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, amp_amp_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 1023, 256),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
	gsSPVertex(amp_billboard_mesh_layer_4_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsDPSetCycleType(G_CYC_1CYCLE),
	gsDPPipeSync(),
	gsSPEndDisplayList(),
};

Gfx amp_switch_option_eletricity_mesh_layer_4[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_1PRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 3, G_AC_NONE | G_ZS_PIXEL),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, amp_amp_electricity_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 511, 512),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 124),
	gsSPVertex(amp_switch_option_eletricity_mesh_layer_4_vtx_0 + 0, 5, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 0, 0),
	gsDPSetCycleType(G_CYC_1CYCLE),
	gsDPPipeSync(),
	gsSPEndDisplayList(),
};

Gfx amp_switch_option_eletricity_001_mesh_layer_4[] = {
	gsDPPipeSync(),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_1PRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 3, G_AC_NONE | G_ZS_PIXEL),
	gsSPVertex(amp_switch_option_eletricity_001_mesh_layer_4_vtx_0 + 0, 5, 0),
	gsSP2Triangles(0, 1, 2, 0, 2, 3, 4, 0),
	gsDPSetCycleType(G_CYC_1CYCLE),
	gsDPPipeSync(),
	gsSPEndDisplayList(),
};

Gfx amp_switch_option_eletricity_002_mesh_layer_4[] = {
	gsDPPipeSync(),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_1PRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 3, G_AC_NONE | G_ZS_PIXEL),
	gsSPVertex(amp_switch_option_eletricity_002_mesh_layer_4_vtx_0 + 0, 5, 0),
	gsSP2Triangles(0, 1, 2, 0, 2, 3, 4, 0),
	gsDPSetCycleType(G_CYC_1CYCLE),
	gsDPPipeSync(),
	gsSPEndDisplayList(),
};

Gfx amp_switch_option_eletricity_003_mesh_layer_4[] = {
	gsDPPipeSync(),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_1PRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 3, G_AC_NONE | G_ZS_PIXEL),
	gsSPVertex(amp_switch_option_eletricity_003_mesh_layer_4_vtx_0 + 0, 5, 0),
	gsSP2Triangles(0, 1, 2, 0, 2, 3, 4, 0),
	gsDPSetCycleType(G_CYC_1CYCLE),
	gsDPPipeSync(),
	gsSPEndDisplayList(),
};

Gfx amp_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};
