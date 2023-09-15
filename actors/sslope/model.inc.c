Lights1 sslope_MakerPassthru_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Vtx sslope_sslope_mesh_vtx_0[18] = {
	{{{-150, 150, -150},0, {-16, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-150, 150, 150},0, {-16, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{150, 150, -150},0, {1008, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-150, -150, -150},0, {-16, -16},{0x0, 0x81, 0x0, 0xFF}}},
	{{{150, -150, -150},0, {1008, -16},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-150, -150, 150},0, {-16, 1008},{0x0, 0x81, 0x0, 0xFF}}},
	{{{150, -150, -150},0, {-16, 1008},{0x5A, 0x0, 0x5A, 0xFF}}},
	{{{150, 150, -150},0, {1008, 1008},{0x5A, 0x0, 0x5A, 0xFF}}},
	{{{-150, 150, 150},0, {1008, -16},{0x5A, 0x0, 0x5A, 0xFF}}},
	{{{-150, -150, 150},0, {-16, -16},{0x5A, 0x0, 0x5A, 0xFF}}},
	{{{-150, 150, -150},0, {898, 870},{0x0, 0x0, 0x81, 0xFF}}},
	{{{150, 150, -150},0, {898, 61},{0x0, 0x0, 0x81, 0xFF}}},
	{{{150, -150, -150},0, {89, 61},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-150, -150, -150},0, {89, 870},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-150, 150, -150},0, {898, 870},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-150, -150, -150},0, {89, 870},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-150, -150, 150},0, {882, 110},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-150, 150, 150},0, {110, 110},{0x81, 0x0, 0x0, 0xFF}}},
};

Gfx sslope_sslope_mesh_tri_0[] = {
	gsSPVertex(sslope_sslope_mesh_vtx_0 + 0, 18, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 6, 8, 9, 0),
	gsSP2Triangles(10, 11, 12, 0, 10, 12, 13, 0),
	gsSP2Triangles(14, 15, 16, 0, 14, 16, 17, 0),
	gsSPEndDisplayList(),
};

Gfx mat_sslope_MakerPassthru[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(sslope_MakerPassthru_lights),
	gsSPEndDisplayList(),
};

Gfx sslope_sslope_mesh[] = {
	gsSPDisplayList(mat_sslope_MakerPassthru),
	gsSPDisplayList(sslope_sslope_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

