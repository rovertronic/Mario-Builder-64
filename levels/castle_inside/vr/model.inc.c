Lights1 vr_Red_lights = gdSPDefLights1(
	0x7F, 0x0, 0x5,
	0xFE, 0x0, 0xB, 0x28, 0x28, 0x28);

Lights1 vr_Darkness_lights = gdSPDefLights1(
	0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x28, 0x28, 0x28);

Lights1 vr_gray_lights = gdSPDefLights1(
	0x3A, 0x3A, 0x3A,
	0x75, 0x75, 0x75, 0x28, 0x28, 0x28);

Vtx vr_4droom_mesh_vtx_cull[8] = {
	{{{-64, -27, 3},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-64, -27, 62},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-64, 811, 62},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-64, 811, 3},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{64, -27, 3},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{64, -27, 62},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{64, 811, 62},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{64, 811, 3},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
};

Vtx vr_4droom_mesh_vtx_0[27] = {
	{{{-59, 31, 3},0, {880, 496},{0xD6, 0x52, 0xA9, 0xFF}}},
	{{{-40, 31, 61},0, {880, 240},{0xCB, 0x51, 0x52, 0xFF}}},
	{{{40, 31, 61},0, {624, 240},{0x35, 0x51, 0x52, 0xFF}}},
	{{{59, 31, 3},0, {624, 496},{0x2A, 0x52, 0xA9, 0xFF}}},
	{{{59, -18, 61},0, {411, 240},{0x57, 0xE, 0x5B, 0xFF}}},
	{{{-40, 31, 61},0, {624, -16},{0xCB, 0x51, 0x52, 0xFF}}},
	{{{0, 3, 61},0, {411, 112},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-29, -18, 61},0, {411, 48},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-59, -18, 61},0, {411, -16},{0xA9, 0xE, 0x5B, 0xFF}}},
	{{{29, -18, 61},0, {411, 176},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-40, 31, 61},0, {624, 1008},{0xCB, 0x51, 0x52, 0xFF}}},
	{{{-59, 31, 3},0, {624, 752},{0xD6, 0x52, 0xA9, 0xFF}}},
	{{{-59, 11, 3},0, {411, 752},{0xE9, 0x15, 0x85, 0xFF}}},
	{{{-59, -18, 42},0, {411, 880},{0x84, 0x14, 0x12, 0xFF}}},
	{{{-59, -18, 61},0, {411, 1008},{0xA9, 0xE, 0x5B, 0xFF}}},
	{{{4, -10, 38},0, {-16, 1008},{0x0, 0x0, 0x81, 0xFF}}},
	{{{4, 6, 38},0, {-16, -16},{0x0, 0x0, 0x81, 0xFF}}},
	{{{36, 6, 38},0, {1008, -16},{0x0, 0x0, 0x81, 0xFF}}},
	{{{36, -10, 38},0, {1008, 1008},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-36, -10, 38},0, {-16, 1008},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-36, 6, 38},0, {-16, -16},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-4, 6, 38},0, {1008, -16},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-4, -10, 38},0, {1008, 1008},{0x0, 0x0, 0x81, 0xFF}}},
	{{{59, -18, 42},0, {411, 368},{0x7C, 0x14, 0x12, 0xFF}}},
	{{{59, 11, 3},0, {411, 496},{0x15, 0x17, 0x85, 0xFF}}},
	{{{40, 23, 42},0, {368, 368},{0xCE, 0xB7, 0xA5, 0xFF}}},
	{{{-40, 23, 42},0, {304, 368},{0x31, 0xB6, 0xA5, 0xFF}}},
};

Gfx vr_4droom_mesh_tri_0[] = {
	gsSPVertex(vr_4droom_mesh_vtx_0 + 0, 27, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(3, 2, 4, 0, 4, 2, 5, 0),
	gsSP2Triangles(5, 6, 4, 0, 5, 7, 6, 0),
	gsSP2Triangles(5, 8, 7, 0, 6, 9, 4, 0),
	gsSP2Triangles(10, 11, 12, 0, 10, 12, 13, 0),
	gsSP2Triangles(13, 14, 10, 0, 15, 16, 17, 0),
	gsSP2Triangles(15, 17, 18, 0, 19, 20, 21, 0),
	gsSP2Triangles(19, 21, 22, 0, 3, 4, 23, 0),
	gsSP2Triangles(23, 24, 3, 0, 25, 3, 24, 0),
	gsSP2Triangles(25, 0, 3, 0, 25, 26, 0, 0),
	gsSP1Triangle(12, 0, 26, 0),
	gsSPEndDisplayList(),
};Vtx vr_4droom_mesh_vtx_1[35] = {
	{{{-59, -27, 61},0, {368, -16},{0xB8, 0xBE, 0x50, 0xFF}}},
	{{{-59, -27, 42},0, {368, 880},{0x8C, 0xCD, 0xB, 0xFF}}},
	{{{-29, -27, 42},0, {176, 368},{0x24, 0x86, 0x5, 0xFF}}},
	{{{-29, -27, 61},0, {368, 48},{0x1F, 0xA5, 0x53, 0xFF}}},
	{{{-29, -18, 61},0, {411, 48},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{0, -3, 61},0, {368, 112},{0x0, 0xA3, 0x56, 0xFF}}},
	{{{0, 3, 61},0, {411, 112},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{29, -18, 61},0, {411, 176},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{29, -27, 61},0, {368, 176},{0xE1, 0xA5, 0x53, 0xFF}}},
	{{{59, -18, 61},0, {411, 240},{0x57, 0xE, 0x5B, 0xFF}}},
	{{{59, -27, 61},0, {368, 240},{0x48, 0xBE, 0x50, 0xFF}}},
	{{{59, -18, 42},0, {411, 368},{0x7C, 0x14, 0x12, 0xFF}}},
	{{{59, -27, 42},0, {368, 368},{0x74, 0xCD, 0xB, 0xFF}}},
	{{{29, -27, 42},0, {304, 368},{0xDC, 0x86, 0x5, 0xFF}}},
	{{{29, -27, 61},0, {304, 240},{0xE1, 0xA5, 0x53, 0xFF}}},
	{{{59, 11, 3},0, {411, 496},{0x15, 0x17, 0x85, 0xFF}}},
	{{{64, -27, 3},0, {368, 496},{0x1F, 0xA7, 0xAA, 0xFF}}},
	{{{-59, -18, 61},0, {411, -16},{0xA9, 0xE, 0x5B, 0xFF}}},
	{{{-59, -27, 61},0, {368, 1008},{0xB8, 0xBE, 0x50, 0xFF}}},
	{{{-59, -18, 61},0, {411, 1008},{0xA9, 0xE, 0x5B, 0xFF}}},
	{{{-59, -18, 42},0, {411, 880},{0x84, 0x14, 0x12, 0xFF}}},
	{{{-64, -27, 3},0, {368, 752},{0xE1, 0xA7, 0xAA, 0xFF}}},
	{{{-59, 11, 3},0, {411, 752},{0xE9, 0x15, 0x85, 0xFF}}},
	{{{0, 811, 25},0, {1008, 496},{0x0, 0x0, 0x81, 0xFF}}},
	{{{6, 31, 36},0, {667, -16},{0x6E, 0x0, 0x3F, 0xFF}}},
	{{{0, 31, 25},0, {1008, -16},{0x0, 0x0, 0x81, 0xFF}}},
	{{{6, 811, 36},0, {667, 496},{0x6E, 0x0, 0x3F, 0xFF}}},
	{{{-6, 31, 36},0, {325, -16},{0x92, 0x0, 0x3F, 0xFF}}},
	{{{-6, 811, 36},0, {325, 496},{0x92, 0x0, 0x3F, 0xFF}}},
	{{{0, 31, 25},0, {-16, -16},{0x0, 0x0, 0x81, 0xFF}}},
	{{{0, 811, 25},0, {-16, 496},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-38, 12, 62},0, {-16, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{1, 12, 62},0, {1008, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{1, 23, 62},0, {1008, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-38, 23, 62},0, {-16, -16},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx vr_4droom_mesh_tri_1[] = {
	gsSPVertex(vr_4droom_mesh_vtx_1 + 0, 31, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 0, 3, 0, 4, 3, 5, 0),
	gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
	gsSP2Triangles(5, 8, 7, 0, 8, 9, 7, 0),
	gsSP2Triangles(8, 10, 9, 0, 11, 9, 10, 0),
	gsSP2Triangles(11, 10, 12, 0, 10, 13, 12, 0),
	gsSP2Triangles(10, 14, 13, 0, 11, 12, 15, 0),
	gsSP2Triangles(12, 16, 15, 0, 4, 17, 0, 0),
	gsSP2Triangles(1, 18, 19, 0, 20, 1, 19, 0),
	gsSP2Triangles(20, 21, 1, 0, 20, 22, 21, 0),
	gsSP2Triangles(23, 24, 25, 0, 23, 26, 24, 0),
	gsSP2Triangles(26, 27, 24, 0, 26, 28, 27, 0),
	gsSP2Triangles(28, 29, 27, 0, 28, 30, 29, 0),
	gsSPVertex(vr_4droom_mesh_vtx_1 + 31, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};Vtx vr_4droom_mesh_vtx_2[14] = {
	{{{-29, -27, 42},0, {176, 368},{0x24, 0x86, 0x5, 0xFF}}},
	{{{0, -3, 61},0, {240, 240},{0x0, 0xA3, 0x56, 0xFF}}},
	{{{-29, -27, 61},0, {176, 240},{0x1F, 0xA5, 0x53, 0xFF}}},
	{{{0, -6, 54},0, {240, 368},{0x0, 0x82, 0xD, 0xFF}}},
	{{{29, -27, 61},0, {304, 240},{0xE1, 0xA5, 0x53, 0xFF}}},
	{{{29, -27, 42},0, {304, 368},{0xDC, 0x86, 0x5, 0xFF}}},
	{{{64, -27, 3},0, {368, 496},{0x1F, 0xA7, 0xAA, 0xFF}}},
	{{{40, 23, 42},0, {368, 368},{0xCE, 0xB7, 0xA5, 0xFF}}},
	{{{59, 11, 3},0, {411, 496},{0x15, 0x17, 0x85, 0xFF}}},
	{{{59, -27, 42},0, {368, 368},{0xAB, 0xE9, 0xA5, 0xFF}}},
	{{{-40, 23, 42},0, {304, 368},{0x31, 0xB6, 0xA5, 0xFF}}},
	{{{-59, -27, 42},0, {304, 368},{0x55, 0xE8, 0xA5, 0xFF}}},
	{{{-59, 11, 3},0, {411, 752},{0xE9, 0x15, 0x85, 0xFF}}},
	{{{-64, -27, 3},0, {368, 752},{0xE1, 0xA7, 0xAA, 0xFF}}},
};

Gfx vr_4droom_mesh_tri_2[] = {
	gsSPVertex(vr_4droom_mesh_vtx_2 + 0, 14, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(3, 4, 1, 0, 3, 5, 4, 0),
	gsSP2Triangles(6, 7, 8, 0, 6, 9, 7, 0),
	gsSP2Triangles(9, 10, 7, 0, 9, 11, 10, 0),
	gsSP2Triangles(12, 10, 11, 0, 12, 11, 13, 0),
	gsSPEndDisplayList(),
};


Gfx mat_vr_Red[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(vr_Red_lights),
	gsSPEndDisplayList(),
};


Gfx mat_vr_Darkness[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(vr_Darkness_lights),
	gsSPEndDisplayList(),
};


Gfx mat_vr_gray[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(vr_gray_lights),
	gsSPEndDisplayList(),
};


Gfx vr_4droom_mesh[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(vr_4droom_mesh_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_vr_Red),
	gsSPDisplayList(vr_4droom_mesh_tri_0),
	gsSPDisplayList(mat_vr_Darkness),
	gsSPDisplayList(vr_4droom_mesh_tri_1),
	gsSPDisplayList(mat_vr_gray),
	gsSPDisplayList(vr_4droom_mesh_tri_2),
	gsSPEndDisplayList(),
};



Gfx vr_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};
