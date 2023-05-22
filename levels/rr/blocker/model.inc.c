Lights1 blocker_Color_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Vtx blocker_Cylinder_001_mesh_layer_1_vtx_0[8] = {
	{{{49, -49, 11},0, {321, 1768},{0x0, 0x0, 0x0, 0xFF}}},
	{{{-49, -49, 11},0, {321, 1417},{0x0, 0x0, 0x0, 0xFF}}},
	{{{-49, 49, 11},0, {671, 1417},{0x0, 0x0, 0x0, 0xFF}}},
	{{{49, 49, 11},0, {671, 1768},{0x0, 0x0, 0x0, 0xFF}}},
	{{{40, -40, -7},0, {321, 1768},{0x0, 0x0, 0x0, 0xFF}}},
	{{{-40, -40, -7},0, {321, 1417},{0x0, 0x0, 0x0, 0xFF}}},
	{{{-40, 40, -7},0, {671, 1417},{0x0, 0x0, 0x0, 0xFF}}},
	{{{40, 40, -7},0, {671, 1768},{0x0, 0x0, 0x0, 0xFF}}},
};

Gfx blocker_Cylinder_001_mesh_layer_1_tri_0[] = {
	gsSPVertex(blocker_Cylinder_001_mesh_layer_1_vtx_0 + 0, 8, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSPEndDisplayList(),
};


Gfx mat_blocker_Color[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(1, 0, SHADE, 0, ENVIRONMENT, 0, SHADE, 0, 1, 0, SHADE, 0, ENVIRONMENT, 0, SHADE, 0),
	gsSPGeometryMode(G_LIGHTING, 0),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(blocker_Color_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_blocker_Color[] = {
	gsDPPipeSync(),
	gsSPGeometryMode(0, G_LIGHTING),
	gsSPEndDisplayList(),
};

Gfx blocker_Cylinder_001_mesh_layer_1[] = {
	gsSPDisplayList(mat_blocker_Color),
	gsSPDisplayList(blocker_Cylinder_001_mesh_layer_1_tri_0),
	gsSPDisplayList(mat_revert_blocker_Color),
	gsSPEndDisplayList(),
};

Gfx blocker_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

