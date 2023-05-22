Lights1 arrow_Indicator_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Vtx arrow_Plane_001_mesh_vtx_cull[8] = {
	{{{-2, -3, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0xFF}}},
	{{{-2, -3, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0xFF}}},
	{{{-2, 3, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0xFF}}},
	{{{-2, 3, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0xFF}}},
	{{{2, -3, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0xFF}}},
	{{{2, -3, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0xFF}}},
	{{{2, 3, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0xFF}}},
	{{{2, 3, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0xFF}}},
};

Vtx arrow_Plane_001_mesh_vtx_0[4] = {
	{{{0, 3, 0},0, {-16, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{0, -2, 0},0, {496, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{2, -3, 0},0, {1008, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-2, -3, 0},0, {-16, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx arrow_Plane_001_mesh_tri_0[] = {
	gsSPVertex(arrow_Plane_001_mesh_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 1, 0, 3, 0),
	gsSPEndDisplayList(),
};


Gfx mat_arrow_Indicator[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(arrow_Indicator_lights),
	gsSPEndDisplayList(),
};


Gfx arrow_Plane_001_mesh[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(arrow_Plane_001_mesh_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_arrow_Indicator),
	gsSPDisplayList(arrow_Plane_001_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};



