Gfx smb_platform_Platform_ci4_aligner[] = {gsSPEndDisplayList()};
u8 smb_platform_Platform_ci4[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 
	0x22, 0x22, 0x33, 0x33, 0x33, 0x33, 0x22, 0x22, 
	0x22, 0x22, 0x33, 0x33, 0x33, 0x33, 0x22, 0x22, 
	0x22, 0x33, 0x33, 0x33, 0x33, 0x33, 0x11, 0x22, 
	0x22, 0x33, 0x33, 0x33, 0x33, 0x33, 0x11, 0x22, 
	0x22, 0x33, 0x33, 0x33, 0x33, 0x33, 0x11, 0x22, 
	0x22, 0x33, 0x33, 0x33, 0x33, 0x33, 0x11, 0x22, 
	0x22, 0x22, 0x11, 0x11, 0x11, 0x11, 0x22, 0x22, 
	0x22, 0x22, 0x11, 0x11, 0x11, 0x11, 0x22, 0x22, 
	0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 
	0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 
	
};

Gfx smb_platform_Platform_ci4_pal_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 smb_platform_Platform_ci4_pal_rgba16[] = {
	0xff, 0xff, 0xd1, 0x41, 0xfc, 0x8f, 0xfc, 0x8e, 
	
};

Vtx smb_platform_Cube_002_mesh_layer_4_vtx_0[4] = {
	{{{150, -63, 50},0, {2048, 512},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{150, 12, 50},0, {2048, 0},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-150, 12, 50},0, {0, 0},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-150, -63, 50},0, {0, 512},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx smb_platform_Cube_002_mesh_layer_4_tri_0[] = {
	gsSPVertex(smb_platform_Cube_002_mesh_layer_4_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};


Gfx mat_smb_platform_Platform[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
	gsDPSetTextureFilter(G_TF_POINT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureLUT(G_TT_RGBA16),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, smb_platform_Platform_ci4_pal_rgba16),
	gsDPTileSync(),
	gsDPSetTile(0, 0, 0, 256, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTLUTCmd(7, 3),
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, smb_platform_Platform_ci4),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 63, 2048),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 60),
	gsSPEndDisplayList(),
};

Gfx mat_revert_smb_platform_Platform[] = {
	gsDPPipeSync(),
	gsDPSetTextureFilter(G_TF_BILERP),
	gsDPSetTextureLUT(G_TT_NONE),
	gsSPEndDisplayList(),
};

Gfx smb_platform_Cube_002_mesh_layer_4[] = {
	gsSPDisplayList(mat_smb_platform_Platform),
	gsSPDisplayList(smb_platform_Cube_002_mesh_layer_4_tri_0),
	gsSPDisplayList(mat_revert_smb_platform_Platform),
	gsSPEndDisplayList(),
};

Gfx smb_platform_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

