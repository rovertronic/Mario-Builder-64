Lights1 grasstop_cutout_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Vtx grasstop_grasstop_mesh_vtx_0[4] = {
	{{{150, 150, 150},0, {-16, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-150, 150, 150},0, {1008, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-150, 50, 150},0, {1008, 496},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{150, 50, 150},0, {-16, 496},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx grasstop_grasstop_mesh_tri_0[] = {
	gsSPVertex(grasstop_grasstop_mesh_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_grasstop_cutout[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(grasstop_cutout_lights),
	gsSPEndDisplayList(),
};

Gfx grasstop_grasstop_mesh[] = {
	gsSPDisplayList(mat_grasstop_cutout),
	gsSPDisplayList(grasstop_grasstop_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

