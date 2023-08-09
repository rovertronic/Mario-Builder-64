Vtx cull_cull_mesh_vtx_cull[8] = {
	{{{-85, -85, -85},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-85, -85, 85},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-85, 85, 85},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-85, 85, -85},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{85, -85, -85},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{85, -85, 85},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{85, 85, 85},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{85, 85, -85},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
};

Vtx cull_cull_mesh_vtx_0[16] = {
	{{{85, -57, 0},0, {-16, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-57, 85, 0},0, {1008, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-85, 57, 0},0, {1008, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{57, -85, 0},0, {-16, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-57, -85, 0},0, {-16, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{85, 57, 0},0, {1008, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{57, 85, 0},0, {1008, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-85, -57, 0},0, {-16, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{0, -57, -85},0, {-16, 1008},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{0, 85, 57},0, {1008, 1008},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{0, 57, 85},0, {1008, -16},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{0, -85, -57},0, {-16, -16},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{0, -85, 57},0, {-16, 1008},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{0, 57, -85},0, {1008, 1008},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{0, 85, -57},0, {1008, -16},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{0, -57, 85},0, {-16, -16},{0x7F, 0x0, 0x0, 0xFF}}},
};

Gfx cull_cull_mesh_tri_0[] = {
	gsSPVertex(cull_cull_mesh_vtx_0 + 0, 16, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSPEndDisplayList(),
};

Gfx mat_cull_RedX[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, PRIMITIVE, 0, 0, 0, ENVIRONMENT),
	gsSPGeometryMode(G_CULL_BACK, 0),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 254, 0, 23, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_cull_RedX[] = {
	gsDPPipeSync(),
	gsSPGeometryMode(0, G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx cull_cull_mesh[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(cull_cull_mesh_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_cull_RedX),
	gsSPDisplayList(cull_cull_mesh_tri_0),
	gsSPDisplayList(mat_revert_cull_RedX),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

