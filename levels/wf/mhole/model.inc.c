Vtx mhole_Cylinder_003_mesh_layer_5_vtx_cull[8] = {
	{{{-57, 8, 57},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-57, 8, 57},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-57, 8, -57},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-57, 8, -57},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{57, 8, 57},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{57, 8, 57},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{57, 8, -57},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{57, 8, -57},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
};

Vtx mhole_Cylinder_003_mesh_layer_5_vtx_0[16] = {
	{{{0, 8, -40},0, {240, 579},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{40, 8, -40},0, {414, 578},{0xFF, 0xFF, 0xFF, 0x0}}},
	{{{0, 8, -57},0, {240, 506},{0xFF, 0xFF, 0xFF, 0x0}}},
	{{{28, 8, -28},0, {362, 630},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{40, 8, 0},0, {413, 752},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-40, 8, 0},0, {67, 752},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-28, 8, -28},0, {118, 630},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-40, 8, -40},0, {66, 578},{0xFF, 0xFF, 0xFF, 0x0}}},
	{{{-57, 8, 0},0, {-6, 752},{0xFF, 0xFF, 0xFF, 0x40}}},
	{{{-28, 8, 28},0, {118, 874},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-40, 8, 40},0, {66, 926},{0xFF, 0xFF, 0xFF, 0xF}}},
	{{{0, 8, 40},0, {240, 925},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, 8, 57},0, {240, 998},{0xFF, 0xFF, 0xFF, 0x1}}},
	{{{28, 8, 28},0, {362, 874},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{40, 8, 40},0, {414, 926},{0xFF, 0xFF, 0xFF, 0x4}}},
	{{{57, 8, 0},0, {486, 752},{0xFF, 0xFF, 0xFF, 0x0}}},
};

Gfx mhole_Cylinder_003_mesh_layer_5_tri_0[] = {
	gsSPVertex(mhole_Cylinder_003_mesh_layer_5_vtx_0 + 0, 16, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(4, 3, 0, 0, 4, 0, 5, 0),
	gsSP2Triangles(0, 6, 5, 0, 6, 0, 2, 0),
	gsSP2Triangles(6, 2, 7, 0, 5, 6, 7, 0),
	gsSP2Triangles(5, 7, 8, 0, 9, 5, 8, 0),
	gsSP2Triangles(9, 8, 10, 0, 11, 9, 10, 0),
	gsSP2Triangles(11, 10, 12, 0, 13, 11, 12, 0),
	gsSP2Triangles(13, 12, 14, 0, 4, 13, 14, 0),
	gsSP2Triangles(4, 14, 15, 0, 3, 4, 15, 0),
	gsSP2Triangles(3, 15, 1, 0, 11, 13, 4, 0),
	gsSP2Triangles(5, 11, 4, 0, 5, 9, 11, 0),
	gsSPEndDisplayList(),
};


Gfx mat_mhole_shadowball_geo[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, 0, 0, 0, 0, SHADE, 0, 0, 0, 0, 0, 0, 0, SHADE),
	gsSPGeometryMode(G_LIGHTING, 0),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx mat_revert_mhole_shadowball_geo[] = {
	gsDPPipeSync(),
	gsSPGeometryMode(0, G_LIGHTING),
	gsSPEndDisplayList(),
};

Gfx mhole_Cylinder_003_mesh_layer_5[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(mhole_Cylinder_003_mesh_layer_5_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_mhole_shadowball_geo),
	gsSPDisplayList(mhole_Cylinder_003_mesh_layer_5_tri_0),
	gsSPDisplayList(mat_revert_mhole_shadowball_geo),
	gsSPEndDisplayList(),
};

Gfx mhole_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

