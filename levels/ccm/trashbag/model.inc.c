Lights1 trashbag_trashbag_lights = gdSPDefLights1(
	0x5, 0x5, 0x5,
	0xA, 0xA, 0xA, 0x28, 0x28, 0x28);

Vtx trashbag_Icosphere_mesh_layer_1_vtx_cull[8] = {
	{{{-53, -10, 51},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-53, 126, 51},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-53, 126, -52},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-53, -10, -52},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{55, -10, 51},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{55, 126, 51},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{55, 126, -52},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{55, -10, -52},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
};

Vtx trashbag_Icosphere_mesh_layer_1_vtx_0[36] = {
	{{{-11, 112, 29},0, {240, 506},{0x77, 0x17, 0x26, 0xFF}}},
	{{{3, 87, -1},0, {240, 752},{0x77, 0x17, 0x26, 0xFF}}},
	{{{-6, 126, 4},0, {453, 875},{0x77, 0x17, 0x26, 0xFF}}},
	{{{-6, 126, 4},0, {453, 875},{0xEC, 0xB, 0x83, 0xFF}}},
	{{{3, 87, -1},0, {240, 752},{0xEC, 0xB, 0x83, 0xFF}}},
	{{{-30, 109, 7},0, {27, 875},{0xEC, 0xB, 0x83, 0xFF}}},
	{{{-30, 109, 7},0, {27, 875},{0xC9, 0x9C, 0x38, 0xFF}}},
	{{{3, 87, -1},0, {240, 752},{0xC9, 0x9C, 0x38, 0xFF}}},
	{{{-11, 112, 29},0, {240, 506},{0xC9, 0x9C, 0x38, 0xFF}}},
	{{{-11, 112, 29},0, {752, 506},{0xBD, 0x63, 0x2C, 0xFF}}},
	{{{-6, 126, 4},0, {965, 875},{0xBD, 0x63, 0x2C, 0xFF}}},
	{{{-30, 109, 7},0, {539, 875},{0xBD, 0x63, 0x2C, 0xFF}}},
	{{{0, -10, 2},0, {822, 1008},{0x2, 0x81, 0x9, 0xFF}}},
	{{{46, 14, 20},0, {729, 847},{0x5D, 0xC0, 0x3A, 0xFF}}},
	{{{-15, 10, 42},0, {915, 847},{0xE0, 0xBE, 0x68, 0xFF}}},
	{{{18, 65, 51},0, {822, 686},{0x1D, 0x31, 0x72, 0xFF}}},
	{{{55, 65, -1},0, {636, 686},{0x72, 0x38, 0x1, 0xFF}}},
	{{{45, 10, -32},0, {543, 847},{0x58, 0xBE, 0xC0, 0xFF}}},
	{{{0, -10, 2},0, {636, 1008},{0x2, 0x81, 0x9, 0xFF}}},
	{{{18, 65, -52},0, {449, 686},{0x23, 0x39, 0x94, 0xFF}}},
	{{{-16, 10, -52},0, {356, 847},{0xDF, 0xBF, 0x98, 0xFF}}},
	{{{0, -10, 2},0, {449, 1008},{0x2, 0x81, 0x9, 0xFF}}},
	{{{-43, 65, -32},0, {263, 686},{0xA0, 0x3B, 0xC4, 0xFF}}},
	{{{-53, 10, -1},0, {170, 847},{0x90, 0xC4, 0x8, 0xFF}}},
	{{{0, -10, 2},0, {263, 1008},{0x2, 0x81, 0x9, 0xFF}}},
	{{{-34, 60, 28},0, {77, 686},{0xA6, 0x34, 0x4A, 0xFF}}},
	{{{-15, 10, 42},0, {-16, 847},{0xE0, 0xBE, 0x68, 0xFF}}},
	{{{0, -10, 2},0, {77, 1008},{0x2, 0x81, 0x9, 0xFF}}},
	{{{1, 98, -1},0, {170, 524},{0xFA, 0x7F, 0x4, 0xFF}}},
	{{{1, 98, -1},0, {729, 524},{0xFA, 0x7F, 0x4, 0xFF}}},
	{{{1, 98, -1},0, {356, 524},{0xFA, 0x7F, 0x4, 0xFF}}},
	{{{1, 98, -1},0, {543, 524},{0xFA, 0x7F, 0x4, 0xFF}}},
	{{{-15, 10, 42},0, {915, 847},{0xE0, 0xBE, 0x68, 0xFF}}},
	{{{18, 65, 51},0, {822, 686},{0x1D, 0x31, 0x72, 0xFF}}},
	{{{-34, 60, 28},0, {1008, 686},{0xA6, 0x34, 0x4A, 0xFF}}},
	{{{1, 98, -1},0, {915, 524},{0xFA, 0x7F, 0x4, 0xFF}}},
};

Gfx trashbag_Icosphere_mesh_layer_1_tri_0[] = {
	gsSPVertex(trashbag_Icosphere_mesh_layer_1_vtx_0 + 0, 32, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 14, 13, 15, 0),
	gsSP2Triangles(13, 16, 15, 0, 13, 17, 16, 0),
	gsSP2Triangles(13, 18, 17, 0, 17, 19, 16, 0),
	gsSP2Triangles(17, 20, 19, 0, 21, 20, 17, 0),
	gsSP2Triangles(20, 22, 19, 0, 20, 23, 22, 0),
	gsSP2Triangles(24, 23, 20, 0, 23, 25, 22, 0),
	gsSP2Triangles(23, 26, 25, 0, 27, 26, 23, 0),
	gsSP2Triangles(22, 25, 28, 0, 15, 16, 29, 0),
	gsSP2Triangles(19, 22, 30, 0, 16, 19, 31, 0),
	gsSPVertex(trashbag_Icosphere_mesh_layer_1_vtx_0 + 32, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 2, 1, 3, 0),
	gsSPEndDisplayList(),
};


Gfx mat_trashbag_trashbag[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(trashbag_trashbag_lights),
	gsSPEndDisplayList(),
};

Gfx trashbag_Icosphere_mesh_layer_1[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(trashbag_Icosphere_mesh_layer_1_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_trashbag_trashbag),
	gsSPDisplayList(trashbag_Icosphere_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx trashbag_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

