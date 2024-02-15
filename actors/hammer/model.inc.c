

Vtx hammer_Cylinder_mesh_layer_1_vtx_0[11] = {
	{{ {0, -41, -14}, 0, {752, 506}, {0, 185, 150, 255} }},
	{{ {12, -41, 7}, 0, {965, 875}, {91, 185, 53, 255} }},
	{{ {-12, -41, 7}, 0, {539, 875}, {165, 185, 53, 255} }},
	{{ {0, -41, -14}, 0, {1008, 496}, {0, 185, 150, 255} }},
	{{ {0, 41, -14}, 0, {1008, -16}, {0, 0, 129, 255} }},
	{{ {12, 41, 7}, 0, {667, -16}, {110, 0, 64, 255} }},
	{{ {12, -41, 7}, 0, {667, 496}, {91, 185, 53, 255} }},
	{{ {-12, 41, 7}, 0, {325, -16}, {146, 0, 63, 255} }},
	{{ {-12, -41, 7}, 0, {325, 496}, {165, 185, 53, 255} }},
	{{ {0, 41, -14}, 0, {-16, -16}, {0, 0, 129, 255} }},
	{{ {0, -41, -14}, 0, {-16, 496}, {0, 185, 150, 255} }},
};

Gfx hammer_Cylinder_mesh_layer_1_tri_0[] = {
	gsSPVertex(hammer_Cylinder_mesh_layer_1_vtx_0 + 0, 11, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(3, 5, 6, 0, 6, 5, 7, 0),
	gsSP2Triangles(6, 7, 8, 0, 8, 7, 9, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSPEndDisplayList(),
};

Vtx hammer_Cylinder_mesh_layer_1_vtx_1[26] = {
	{{ {0, 85, -54}, 0, {1008, 496}, {0, 90, 166, 255} }},
	{{ {0, 91, 47}, 0, {1008, -16}, {0, 103, 74, 255} }},
	{{ {34, 71, 47}, 0, {837, -16}, {90, 52, 74, 255} }},
	{{ {29, 68, -33}, 0, {837, 496}, {98, 57, 199, 255} }},
	{{ {34, 32, 47}, 0, {667, -16}, {89, 205, 74, 255} }},
	{{ {29, 35, -54}, 0, {667, 496}, {78, 211, 166, 255} }},
	{{ {0, 12, 47}, 0, {496, -16}, {0, 153, 74, 255} }},
	{{ {0, 19, -33}, 0, {496, 496}, {0, 142, 199, 255} }},
	{{ {-34, 32, 47}, 0, {325, -16}, {167, 205, 74, 255} }},
	{{ {-29, 35, -54}, 0, {325, 496}, {178, 211, 166, 255} }},
	{{ {-34, 71, 47}, 0, {155, -16}, {166, 52, 74, 255} }},
	{{ {-29, 68, -33}, 0, {155, 496}, {158, 57, 199, 255} }},
	{{ {0, 91, 47}, 0, {-16, -16}, {0, 103, 74, 255} }},
	{{ {0, 85, -54}, 0, {-16, 496}, {0, 90, 166, 255} }},
	{{ {34, 32, 47}, 0, {453, 875}, {89, 205, 74, 255} }},
	{{ {34, 71, 47}, 0, {453, 629}, {90, 52, 74, 255} }},
	{{ {0, 91, 47}, 0, {240, 506}, {0, 103, 74, 255} }},
	{{ {-34, 32, 47}, 0, {27, 875}, {167, 205, 74, 255} }},
	{{ {-34, 71, 47}, 0, {27, 629}, {166, 52, 74, 255} }},
	{{ {0, 12, 47}, 0, {240, 998}, {0, 153, 74, 255} }},
	{{ {-29, 68, -33}, 0, {539, 629}, {158, 57, 199, 255} }},
	{{ {0, 85, -54}, 0, {752, 506}, {0, 90, 166, 255} }},
	{{ {29, 68, -33}, 0, {965, 629}, {98, 57, 199, 255} }},
	{{ {0, 19, -33}, 0, {752, 998}, {0, 142, 199, 255} }},
	{{ {29, 35, -54}, 0, {965, 875}, {78, 211, 166, 255} }},
	{{ {-29, 35, -54}, 0, {539, 875}, {178, 211, 166, 255} }},
};

Gfx hammer_Cylinder_mesh_layer_1_tri_1[] = {
	gsSPVertex(hammer_Cylinder_mesh_layer_1_vtx_1 + 0, 26, 0),
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


Gfx mat_hammer_Handle_001[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLightColor(LIGHT_1, 0xffb935ff),
    gsSPLightColor(LIGHT_2, 0x7f5b15ff),
	gsSPEndDisplayList(),
};

Gfx mat_hammer_Hard_001[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLightColor(LIGHT_1, 0x191919ff),
    gsSPLightColor(LIGHT_2, 0x70707ff),
	gsSPEndDisplayList(),
};

Gfx hammer_Cylinder_mesh_layer_1[] = {
	gsSPDisplayList(mat_hammer_Handle_001),
	gsSPDisplayList(hammer_Cylinder_mesh_layer_1_tri_0),
	gsSPDisplayList(mat_hammer_Hard_001),
	gsSPDisplayList(hammer_Cylinder_mesh_layer_1_tri_1),
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

