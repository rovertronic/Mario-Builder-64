Lights1 makerfence_MakerPassthru2_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Vtx makerfence_mfv_mesh_vtx_0[8] = {
	{{{-128, -128, -128},0, {-1040, 1008},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-128, -43, -128},0, {-1040, -16},{0x0, 0x0, 0x81, 0xFF}}},
	{{{128, -43, -128},0, {2032, -16},{0x0, 0x0, 0x81, 0xFF}}},
	{{{128, -128, -128},0, {2032, 1008},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-128, -128, -128},0, {-1040, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{128, -128, -128},0, {2032, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{128, -43, -128},0, {2032, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-128, -43, -128},0, {-1040, -16},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx makerfence_mfv_mesh_tri_0[] = {
	gsSPVertex(makerfence_mfv_mesh_vtx_0 + 0, 8, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSPEndDisplayList(),
};

Gfx mat_makerfence_MakerPassthru2[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(makerfence_MakerPassthru2_lights),
	gsSPEndDisplayList(),
};

Gfx makerfence_mfv_mesh[] = {
	gsSPDisplayList(mat_makerfence_MakerPassthru2),
	gsSPDisplayList(makerfence_mfv_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

