Gfx retrobill_Bill_ci4_aligner[] = {gsSPEndDisplayList()};
u8 retrobill_Bill_ci4[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x11, 0x11, 0x11, 0x10, 0x11, 
	0x00, 0x00, 0x11, 0x12, 0x22, 0x22, 0x10, 0x22, 
	0x00, 0x01, 0x11, 0x21, 0x11, 0x11, 0x13, 0x11, 
	0x00, 0x12, 0x11, 0x11, 0x11, 0x11, 0x12, 0x11, 
	0x01, 0x22, 0x11, 0x11, 0x11, 0x11, 0x13, 0x11, 
	0x12, 0x12, 0x11, 0x11, 0x13, 0x31, 0x13, 0x11, 
	0x11, 0x21, 0x11, 0x12, 0x12, 0x23, 0x13, 0x11, 
	0x11, 0x11, 0x12, 0x22, 0x22, 0x23, 0x13, 0x11, 
	0x11, 0x11, 0x12, 0x22, 0x22, 0x11, 0x13, 0x11, 
	0x01, 0x11, 0x11, 0x22, 0x21, 0x11, 0x13, 0x11, 
	0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x13, 0x11, 
	0x00, 0x01, 0x11, 0x11, 0x11, 0x11, 0x13, 0x11, 
	0x00, 0x00, 0x11, 0x11, 0x11, 0x11, 0x10, 0x11, 
	0x00, 0x00, 0x00, 0x11, 0x11, 0x11, 0x10, 0x11, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	
};

Gfx retrobill_Bill_ci4_pal_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 retrobill_Bill_ci4_pal_rgba16[] = {
	0x00, 0x00, 0x00, 0x01, 0xfe, 0x71, 0x9a, 0x41, 
	
};

Vtx retrobill_Plane_002_mesh_layer_4_vtx_0[4] = {
	{{{-75, 0, 0},0, {0, 512},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{75, 0, 0},0, {512, 512},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{75, 150, 0},0, {512, 0},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-75, 150, 0},0, {0, 0},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx retrobill_Plane_002_mesh_layer_4_tri_0[] = {
	gsSPVertex(retrobill_Plane_002_mesh_layer_4_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};


Gfx mat_retrobill_Bill[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsDPSetTextureFilter(G_TF_POINT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureLUT(G_TT_RGBA16),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, retrobill_Bill_ci4_pal_rgba16),
	gsDPTileSync(),
	gsDPSetTile(0, 0, 0, 256, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTLUTCmd(7, 3),
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, retrobill_Bill_ci4),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 63, 2048),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 60),
	gsSPEndDisplayList(),
};

Gfx mat_revert_retrobill_Bill[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsDPSetTextureFilter(G_TF_BILERP),
	gsDPSetTextureLUT(G_TT_NONE),
	gsSPEndDisplayList(),
};

Gfx retrobill_Plane_002_mesh_layer_4[] = {
	gsSPDisplayList(mat_retrobill_Bill),
	gsSPDisplayList(retrobill_Plane_002_mesh_layer_4_tri_0),
	gsSPDisplayList(mat_revert_retrobill_Bill),
	gsSPEndDisplayList(),
};

Gfx retrobill_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

