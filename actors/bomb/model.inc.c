
Gfx bomb_bomb_spike_rgba16_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 bomb_bomb_spike_rgba16_rgba16[] = {
	#include "actors/bomb/bomb_spike.rgba16.inc.c"
};

Gfx bomb_bomb_left_side_rgba16_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 bomb_bomb_left_side_rgba16_rgba16[] = {
	#include "actors/bomb/bomb_left_side.rgba16.inc.c"
};

Gfx bomb_bomb_right_side_rgba16_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 bomb_bomb_right_side_rgba16_rgba16[] = {
	#include "actors/bomb/bomb_right_side.rgba16.inc.c"
};

Vtx bomb_spikes_mesh_layer_1_vtx_0[55] = {
	{{ {0, -177, 0}, 0, {496, -8}, {255, 129, 255, 255} }},
	{{ {-27, -108, 0}, 0, {-20, 988}, {138, 210, 253, 255} }},
	{{ {0, -108, -24}, 0, {1008, 988}, {254, 214, 136, 255} }},
	{{ {0, -108, -24}, 0, {-20, 988}, {254, 214, 136, 255} }},
	{{ {30, -108, 0}, 0, {1008, 988}, {116, 205, 254, 255} }},
	{{ {0, 111, -24}, 0, {-20, 988}, {254, 42, 136, 255} }},
	{{ {-27, 111, 0}, 0, {1008, 988}, {138, 46, 253, 255} }},
	{{ {0, 180, 0}, 0, {496, -8}, {255, 127, 255, 255} }},
	{{ {30, 111, 0}, 0, {-20, 988}, {116, 51, 254, 255} }},
	{{ {0, 111, -24}, 0, {1008, 988}, {254, 42, 136, 255} }},
	{{ {0, 111, 27}, 0, {-20, 988}, {254, 46, 118, 255} }},
	{{ {30, 111, 0}, 0, {1008, 988}, {116, 51, 254, 255} }},
	{{ {-27, 111, 0}, 0, {-20, 988}, {138, 46, 253, 255} }},
	{{ {0, 111, 27}, 0, {1008, 988}, {254, 46, 118, 255} }},
	{{ {0, 30, 111}, 0, {-20, 988}, {254, 116, 51, 255} }},
	{{ {-27, 0, 111}, 0, {1008, 988}, {138, 251, 46, 255} }},
	{{ {0, 0, 180}, 0, {496, -8}, {255, 253, 127, 255} }},
	{{ {-27, 0, 111}, 0, {-20, 988}, {138, 251, 46, 255} }},
	{{ {0, -24, 111}, 0, {1008, 988}, {254, 136, 42, 255} }},
	{{ {30, -108, 0}, 0, {-20, 988}, {116, 205, 254, 255} }},
	{{ {0, -108, 27}, 0, {1008, 988}, {254, 210, 118, 255} }},
	{{ {0, -108, 27}, 0, {-20, 988}, {254, 210, 118, 255} }},
	{{ {-27, -108, 0}, 0, {1008, 988}, {138, 210, 253, 255} }},
	{{ {30, 0, 111}, 0, {-20, 988}, {117, 251, 50, 255} }},
	{{ {0, 30, 111}, 0, {1008, 988}, {254, 116, 51, 255} }},
	{{ {0, -24, 111}, 0, {-20, 988}, {254, 136, 42, 255} }},
	{{ {30, 0, 111}, 0, {1008, 988}, {117, 251, 50, 255} }},
	{{ {111, 0, -27}, 0, {-20, 988}, {46, 251, 138, 255} }},
	{{ {111, 30, 0}, 0, {1008, 988}, {51, 116, 254, 255} }},
	{{ {180, 0, 0}, 0, {496, -8}, {127, 253, 255, 255} }},
	{{ {111, -24, 0}, 0, {-20, 988}, {42, 136, 254, 255} }},
	{{ {111, 0, -27}, 0, {1008, 988}, {46, 251, 138, 255} }},
	{{ {111, 0, 30}, 0, {-20, 988}, {50, 251, 117, 255} }},
	{{ {111, -24, 0}, 0, {1008, 988}, {42, 136, 254, 255} }},
	{{ {180, 0, 0}, 0, {496, -8}, {127, 253, 255, 255} }},
	{{ {111, 30, 0}, 0, {-20, 988}, {51, 116, 254, 255} }},
	{{ {111, 0, 30}, 0, {1008, 988}, {50, 251, 117, 255} }},
	{{ {-177, 0, 0}, 0, {496, -8}, {129, 253, 255, 255} }},
	{{ {-108, 0, 30}, 0, {-20, 988}, {206, 251, 117, 255} }},
	{{ {-108, 30, 0}, 0, {1008, 988}, {205, 116, 254, 255} }},
	{{ {-108, -24, 0}, 0, {-20, 988}, {214, 136, 254, 255} }},
	{{ {-108, 0, 30}, 0, {1008, 988}, {206, 251, 117, 255} }},
	{{ {-108, 0, -27}, 0, {-20, 988}, {210, 251, 138, 255} }},
	{{ {-108, -24, 0}, 0, {1008, 988}, {214, 136, 254, 255} }},
	{{ {-108, 30, 0}, 0, {-20, 988}, {205, 116, 254, 255} }},
	{{ {-108, 0, -27}, 0, {1008, 988}, {210, 251, 138, 255} }},
	{{ {0, 0, -177}, 0, {496, -8}, {255, 253, 129, 255} }},
	{{ {0, 30, -108}, 0, {-20, 988}, {254, 116, 205, 255} }},
	{{ {30, 0, -108}, 0, {1008, 988}, {117, 251, 206, 255} }},
	{{ {30, 0, -108}, 0, {-20, 988}, {117, 251, 206, 255} }},
	{{ {0, -24, -108}, 0, {1008, 988}, {254, 136, 214, 255} }},
	{{ {-27, 0, -108}, 0, {-20, 988}, {138, 251, 210, 255} }},
	{{ {0, 30, -108}, 0, {1008, 988}, {254, 116, 205, 255} }},
	{{ {0, -24, -108}, 0, {-20, 988}, {254, 136, 214, 255} }},
	{{ {-27, 0, -108}, 0, {1008, 988}, {138, 251, 210, 255} }},
};

Vtx bomb_bomb_billboard_mesh_layer_4_vtx_0[4] = {
	{{ {0, 120, 0}, 0, {992, 0}, {255, 255, 255, 255} }},
	{{ {-117, -117, 0}, 0, {0, 2016}, {255, 255, 255, 255} }},
	{{ {0, -117, 0}, 0, {992, 2016}, {255, 255, 255, 255} }},
	{{ {-117, 120, 0}, 0, {0, 0}, {255, 255, 255, 255} }},
};

Vtx bomb_bomb_billboard_mesh_layer_4_vtx_1[4] = {
	{{ {120, 120, 0}, 0, {992, 0}, {255, 255, 255, 255} }},
	{{ {0, 120, 0}, 0, {0, 0}, {255, 255, 255, 255} }},
	{{ {0, -117, 0}, 0, {0, 2016}, {255, 255, 255, 255} }},
	{{ {120, -117, 0}, 0, {992, 2016}, {255, 255, 255, 255} }},
};


Gfx bomb_spikes_mesh_layer_1[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE, TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_1PRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 3, G_AC_NONE | G_ZS_PIXEL),
	gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLightColor(LIGHT_1, 0xffffffff),
    gsSPLightColor(LIGHT_2, 0x3f3f3fff),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, bomb_bomb_spike_rgba16_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 1023, 256),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPVertex(bomb_spikes_mesh_layer_1_vtx_0 + 0, 32, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 4, 0),
	gsSP2Triangles(5, 6, 7, 0, 8, 9, 7, 0),
	gsSP2Triangles(10, 11, 7, 0, 12, 13, 7, 0),
	gsSP2Triangles(14, 15, 16, 0, 17, 18, 16, 0),
	gsSP2Triangles(0, 19, 20, 0, 0, 21, 22, 0),
	gsSP2Triangles(23, 24, 16, 0, 25, 26, 16, 0),
	gsSP2Triangles(27, 28, 29, 0, 30, 31, 29, 0),
	gsSPVertex(bomb_spikes_mesh_layer_1_vtx_0 + 32, 23, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 2, 0),
	gsSP2Triangles(5, 6, 7, 0, 5, 8, 9, 0),
	gsSP2Triangles(5, 10, 11, 0, 5, 12, 13, 0),
	gsSP2Triangles(14, 15, 16, 0, 14, 17, 18, 0),
	gsSP2Triangles(14, 19, 20, 0, 14, 21, 22, 0),
	gsDPPipeSync(),
	gsDPSetCycleType(G_CYC_1CYCLE),
	gsSPEndDisplayList(),
};

Gfx bomb_bomb_billboard_mesh_layer_4[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_1PRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 3, G_AC_NONE | G_ZS_PIXEL),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, bomb_bomb_left_side_rgba16_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 2047, 256),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 252),
	gsSPVertex(bomb_bomb_billboard_mesh_layer_4_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsDPPipeSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, bomb_bomb_right_side_rgba16_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 2047, 256),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
	gsSPVertex(bomb_bomb_billboard_mesh_layer_4_vtx_1 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsDPPipeSync(),
	gsDPSetCycleType(G_CYC_1CYCLE),
	gsSPEndDisplayList(),
};

Gfx bomb_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};
