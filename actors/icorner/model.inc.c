Lights1 icorner_MakerPassthru_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Vtx icorner_icorner_mesh_vtx_0[24] = {
	{{{150, -150, -150},0, {1008, -16},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{150, 150, -150},0, {-16, -16},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{150, -150, 150},0, {-16, 1008},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{-150, -150, 150},0, {-16, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{150, -150, 150},0, {1008, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-150, 150, 150},0, {1008, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{150, -150, 150},0, {1008, -16},{0x5A, 0x5A, 0x0, 0xFF}}},
	{{{-150, 150, -150},0, {1008, 1008},{0x5A, 0x5A, 0x0, 0xFF}}},
	{{{-150, 150, 150},0, {1008, 1008},{0x5A, 0x5A, 0x0, 0xFF}}},
	{{{150, 150, -150},0, {-16, -16},{0x0, 0x5A, 0x5A, 0xFF}}},
	{{{-150, 150, -150},0, {1008, 1008},{0x0, 0x5A, 0x5A, 0xFF}}},
	{{{150, -150, 150},0, {-16, 1008},{0x0, 0x5A, 0x5A, 0xFF}}},
	{{{-150, -150, -150},0, {-16, 1008},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-150, 150, -150},0, {1008, 1008},{0x0, 0x0, 0x81, 0xFF}}},
	{{{150, 150, -150},0, {1008, -16},{0x0, 0x0, 0x81, 0xFF}}},
	{{{150, -150, -150},0, {-16, -16},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-150, 150, -150},0, {1008, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-150, -150, -150},0, {-16, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-150, -150, 150},0, {-16, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-150, 150, 150},0, {1008, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-150, -150, -150},0, {-16, 1008},{0x0, 0x81, 0x0, 0xFF}}},
	{{{150, -150, -150},0, {1008, 1008},{0x0, 0x81, 0x0, 0xFF}}},
	{{{150, -150, 150},0, {1008, -16},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-150, -150, 150},0, {-16, -16},{0x0, 0x81, 0x0, 0xFF}}},
};

Gfx icorner_icorner_mesh_tri_0[] = {
	gsSPVertex(icorner_icorner_mesh_vtx_0 + 0, 24, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
	gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
	gsSPEndDisplayList(),
};

Gfx mat_icorner_MakerPassthru[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(icorner_MakerPassthru_lights),
	gsSPEndDisplayList(),
};

Gfx icorner_icorner_mesh[] = {
	gsSPDisplayList(mat_icorner_MakerPassthru),
	gsSPDisplayList(icorner_icorner_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

