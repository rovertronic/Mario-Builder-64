

Vtx hammer_Cylinder_mesh_vtx_cull[8] = {
	{{{-34, -41, -54},0, {-16, -16},{0x0, 0x0, 0x0, 0xFF}}},
	{{{-34, -41, 47},0, {-16, -16},{0x0, 0x0, 0x0, 0xFF}}},
	{{{-34, 91, 47},0, {-16, -16},{0x0, 0x0, 0x0, 0xFF}}},
	{{{-34, 91, -54},0, {-16, -16},{0x0, 0x0, 0x0, 0xFF}}},
	{{{34, -41, -54},0, {-16, -16},{0x0, 0x0, 0x0, 0xFF}}},
	{{{34, -41, 47},0, {-16, -16},{0x0, 0x0, 0x0, 0xFF}}},
	{{{34, 91, 47},0, {-16, -16},{0x0, 0x0, 0x0, 0xFF}}},
	{{{34, 91, -54},0, {-16, -16},{0x0, 0x0, 0x0, 0xFF}}},
};

Vtx hammer_Cylinder_mesh_vtx_0[11] = {
	{{{0, -41, -14},0, {752, 506},{0x0, 0xB9, 0x96, 0xFF}}},
	{{{12, -41, 7},0, {965, 875},{0x5B, 0xB9, 0x35, 0xFF}}},
	{{{-12, -41, 7},0, {539, 875},{0xA5, 0xB9, 0x35, 0xFF}}},
	{{{0, -41, -14},0, {1008, 496},{0x0, 0xB9, 0x96, 0xFF}}},
	{{{0, 41, -14},0, {1008, -16},{0x0, 0x0, 0x81, 0xFF}}},
	{{{12, 41, 7},0, {667, -16},{0x6E, 0x0, 0x3F, 0xFF}}},
	{{{12, -41, 7},0, {667, 496},{0x5B, 0xB9, 0x35, 0xFF}}},
	{{{-12, 41, 7},0, {325, -16},{0x92, 0x0, 0x3F, 0xFF}}},
	{{{-12, -41, 7},0, {325, 496},{0xA5, 0xB9, 0x35, 0xFF}}},
	{{{0, 41, -14},0, {-16, -16},{0x0, 0x0, 0x81, 0xFF}}},
	{{{0, -41, -14},0, {-16, 496},{0x0, 0xB9, 0x96, 0xFF}}},
};

Gfx hammer_Cylinder_mesh_tri_0[] = {
	gsSPVertex(hammer_Cylinder_mesh_vtx_0 + 0, 11, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(3, 5, 6, 0, 6, 5, 7, 0),
	gsSP2Triangles(6, 7, 8, 0, 8, 7, 9, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSPEndDisplayList(),
};Vtx hammer_Cylinder_mesh_vtx_1[26] = {
	{{{0, 85, -54},0, {1008, 496},{0x0, 0x5A, 0xA7, 0xFF}}},
	{{{0, 91, 47},0, {1008, -16},{0x0, 0x67, 0x4A, 0xFF}}},
	{{{34, 71, 47},0, {837, -16},{0x5A, 0x34, 0x4A, 0xFF}}},
	{{{29, 68, -33},0, {837, 496},{0x62, 0x39, 0xC7, 0xFF}}},
	{{{34, 32, 47},0, {667, -16},{0x59, 0xCC, 0x4A, 0xFF}}},
	{{{29, 35, -54},0, {667, 496},{0x4E, 0xD3, 0xA7, 0xFF}}},
	{{{0, 12, 47},0, {496, -16},{0x0, 0x99, 0x4A, 0xFF}}},
	{{{0, 19, -33},0, {496, 496},{0x0, 0x8F, 0xC6, 0xFF}}},
	{{{-34, 32, 47},0, {325, -16},{0xA7, 0xCC, 0x4A, 0xFF}}},
	{{{-29, 35, -54},0, {325, 496},{0xB2, 0xD3, 0xA7, 0xFF}}},
	{{{-34, 71, 47},0, {155, -16},{0xA6, 0x34, 0x4A, 0xFF}}},
	{{{-29, 68, -33},0, {155, 496},{0x9E, 0x39, 0xC7, 0xFF}}},
	{{{0, 91, 47},0, {-16, -16},{0x0, 0x67, 0x4A, 0xFF}}},
	{{{0, 85, -54},0, {-16, 496},{0x0, 0x5A, 0xA7, 0xFF}}},
	{{{34, 32, 47},0, {453, 875},{0x59, 0xCC, 0x4A, 0xFF}}},
	{{{34, 71, 47},0, {453, 629},{0x5A, 0x34, 0x4A, 0xFF}}},
	{{{0, 91, 47},0, {240, 506},{0x0, 0x67, 0x4A, 0xFF}}},
	{{{-34, 32, 47},0, {27, 875},{0xA7, 0xCC, 0x4A, 0xFF}}},
	{{{-34, 71, 47},0, {27, 629},{0xA6, 0x34, 0x4A, 0xFF}}},
	{{{0, 12, 47},0, {240, 998},{0x0, 0x99, 0x4A, 0xFF}}},
	{{{-29, 68, -33},0, {539, 629},{0x9E, 0x39, 0xC7, 0xFF}}},
	{{{0, 85, -54},0, {752, 506},{0x0, 0x5A, 0xA7, 0xFF}}},
	{{{29, 68, -33},0, {965, 629},{0x62, 0x39, 0xC7, 0xFF}}},
	{{{0, 19, -33},0, {752, 998},{0x0, 0x8F, 0xC6, 0xFF}}},
	{{{29, 35, -54},0, {965, 875},{0x4E, 0xD3, 0xA7, 0xFF}}},
	{{{-29, 35, -54},0, {539, 875},{0xB2, 0xD3, 0xA7, 0xFF}}},
};

Gfx hammer_Cylinder_mesh_tri_1[] = {
	gsSPVertex(hammer_Cylinder_mesh_vtx_1 + 0, 26, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(3, 2, 4, 0, 3, 4, 5, 0),
	gsSP2Triangles(5, 4, 6, 0, 5, 6, 7, 0),
	gsSP2Triangles(7, 6, 8, 0, 7, 8, 9, 0),
	gsSP2Triangles(9, 8, 10, 0, 9, 10, 11, 0),
	gsSP2Triangles(11, 10, 12, 0, 11, 12, 13, 0),
	gsSP2Triangles(14, 15, 16, 0, 16, 17, 14, 0),
	gsSP2Triangles(16, 18, 17, 0, 17, 19, 14, 0),
	gsSP2Triangles(20, 21, 22, 0, 22, 23, 20, 0),
	gsSP2Triangles(22, 24, 23, 0, 23, 25, 20, 0),
	gsSPEndDisplayList(),
};


Gfx mat_hammer_Handle[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLightColor(LIGHT_1, 0xfeb935ff),
    gsSPLightColor(LIGHT_2, 0x7f5c1aff),
	gsSPEndDisplayList(),
};


Gfx mat_hammer_Hard[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLightColor(LIGHT_1, 0x191919ff),
    gsSPLightColor(LIGHT_2, 0xc0c0cff),
	gsSPEndDisplayList(),
};


Gfx hammer_Cylinder_mesh[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(hammer_Cylinder_mesh_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_hammer_Handle),
	gsSPDisplayList(hammer_Cylinder_mesh_tri_0),
	gsSPDisplayList(mat_hammer_Hard),
	gsSPDisplayList(hammer_Cylinder_mesh_tri_1),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};



Gfx hammer_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};
