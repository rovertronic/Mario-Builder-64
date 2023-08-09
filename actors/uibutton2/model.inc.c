Vtx uibutton2_button_001_mesh_vtx_cull[8] = {
	{{{-16, -16, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-16, -16, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-16, 16, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-16, 16, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{16, -16, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{16, -16, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{16, 16, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{16, 16, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
};

Vtx uibutton2_button_001_mesh_vtx_0[4] = {
	{{{-16, -16, 0},0, {-16, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{16, -16, 0},0, {1008, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{16, 16, 0},0, {1008, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-16, 16, 0},0, {-16, -16},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx uibutton2_button_001_mesh_tri_0[] = {
	gsSPVertex(uibutton2_button_001_mesh_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_uibutton2_buttont[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(ENVIRONMENT, 0, TEXEL0, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, TEXEL0, 0, 0, 0, 0, TEXEL0),
	gsSPGeometryMode(G_ZBUFFER | G_CULL_BACK, 0),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx mat_revert_uibutton2_buttont[] = {
	gsDPPipeSync(),
	gsSPGeometryMode(0, G_ZBUFFER | G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx uibutton2_button_001_mesh[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(uibutton2_button_001_mesh_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_uibutton2_buttont),
	gsSPDisplayList(uibutton2_button_001_mesh_tri_0),
	gsSPDisplayList(mat_revert_uibutton2_buttont),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

