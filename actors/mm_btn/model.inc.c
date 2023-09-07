Lights1 mm_btn_f3dlite_material_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFF, 0xFF, 0xFF, 0x28, 0x28, 0x28);

Vtx mm_btn_mm_btn_mesh_vtx_0[23] = {
	{{ {44, 0, 0}, 0, {1008, 1008}, {0, 0, 127, 255} }},
	{{ {55, 0, 0}, 0, {1008, -16}, {0, 0, 127, 255} }},
	{{ {55, 11, 0}, 0, {-16, -16}, {0, 0, 127, 255} }},
	{{ {44, 11, 0}, 0, {-16, 1008}, {0, 0, 127, 255} }},
	{{ {-55, 0, 0}, 0, {-16, 1008}, {0, 0, 127, 255} }},
	{{ {-44, 0, 0}, 0, {1008, 1008}, {0, 0, 127, 255} }},
	{{ {-44, 11, 0}, 0, {1008, -16}, {0, 0, 127, 255} }},
	{{ {-55, 11, 0}, 0, {-16, -16}, {0, 0, 127, 255} }},
	{{ {-44, 0, 0}, 0, {538, 587}, {0, 0, 127, 255} }},
	{{ {44, 0, 0}, 0, {710, 587}, {0, 0, 127, 255} }},
	{{ {44, 11, 0}, 0, {710, 581}, {0, 0, 127, 255} }},
	{{ {-44, 11, 0}, 0, {538, 581}, {0, 0, 127, 255} }},
	{{ {44, -11, 0}, 0, {1008, -16}, {0, 0, 127, 255} }},
	{{ {55, -11, 0}, 0, {-16, -16}, {0, 0, 127, 255} }},
	{{ {55, 0, 0}, 0, {-16, 1008}, {0, 0, 127, 255} }},
	{{ {44, 0, 0}, 0, {1008, 1008}, {0, 0, 127, 255} }},
	{{ {-55, -11, 0}, 0, {-16, -16}, {0, 0, 127, 255} }},
	{{ {-44, -11, 0}, 0, {-16, 1008}, {0, 0, 127, 255} }},
	{{ {-55, 0, 0}, 0, {1008, -16}, {0, 0, 127, 255} }},
	{{ {-44, -11, 0}, 0, {538, 667}, {0, 0, 127, 255} }},
	{{ {44, -11, 0}, 0, {710, 667}, {0, 0, 127, 255} }},
	{{ {44, 0, 0}, 0, {710, 661}, {0, 0, 127, 255} }},
	{{ {-44, 0, 0}, 0, {538, 661}, {0, 0, 127, 255} }},
};

Gfx mm_btn_mm_btn_mesh_tri_0[] = {
	gsSPVertex(mm_btn_mm_btn_mesh_vtx_0 + 0, 23, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 5, 0, 16, 5, 18, 0),
	gsSP2Triangles(19, 20, 21, 0, 19, 21, 22, 0),
	gsSPEndDisplayList(),
};

Gfx mat_mm_btn_f3dlite_material[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(mm_btn_f3dlite_material_lights),
	gsSPEndDisplayList(),
};

Gfx mm_btn_mm_btn_mesh[] = {
	gsSPDisplayList(mat_mm_btn_f3dlite_material),
	gsSPDisplayList(mm_btn_mm_btn_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

