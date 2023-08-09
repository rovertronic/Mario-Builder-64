Lights1 corner_MakerPassthru_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Vtx corner_corner_mesh_vtx_0[16] = {
	{{{-150, 150, -150},0, {1008, 1008},{0x0, 0x0, 0x81, 0xFF}}},
	{{{150, -150, -150},0, {-16, -16},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-150, -150, -150},0, {-16, 1008},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-150, -150, -150},0, {1008, -16},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-150, -150, 150},0, {-16, -16},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-150, 150, -150},0, {-16, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{150, -150, 150},0, {1008, -16},{0x0, 0x5A, 0x5A, 0xFF}}},
	{{{-150, 150, -150},0, {-16, 1008},{0x0, 0x5A, 0x5A, 0xFF}}},
	{{{-150, -150, 150},0, {-16, -16},{0x0, 0x5A, 0x5A, 0xFF}}},
	{{{150, -150, -150},0, {-16, -16},{0x5A, 0x5A, 0x0, 0xFF}}},
	{{{-150, 150, -150},0, {1008, 1008},{0x5A, 0x5A, 0x0, 0xFF}}},
	{{{150, -150, 150},0, {1008, -16},{0x5A, 0x5A, 0x0, 0xFF}}},
	{{{-150, -150, -150},0, {-16, 1008},{0x0, 0x81, 0x0, 0xFF}}},
	{{{150, -150, -150},0, {1008, 1008},{0x0, 0x81, 0x0, 0xFF}}},
	{{{150, -150, 150},0, {1008, -16},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-150, -150, 150},0, {-16, -16},{0x0, 0x81, 0x0, 0xFF}}},
};

Gfx corner_corner_mesh_tri_0[] = {
	gsSPVertex(corner_corner_mesh_vtx_0 + 0, 16, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSPEndDisplayList(),
};

Gfx mat_corner_MakerPassthru[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(corner_MakerPassthru_lights),
	gsSPEndDisplayList(),
};

Gfx corner_corner_mesh[] = {
	gsSPDisplayList(mat_corner_MakerPassthru),
	gsSPDisplayList(corner_corner_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

