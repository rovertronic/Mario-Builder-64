Vtx gradibox_Plane_mesh_vtx_0[4] = {
	{{{-160, 30, 0},0, {-16, -16},{0xFF, 0xFF, 0xFF, 0xF1}}},
	{{{-160, -30, 0},0, {-16, 1008},{0xFF, 0xFF, 0xFF, 0x7E}}},
	{{{160, -30, 0},0, {1008, 1008},{0xFF, 0xFF, 0xFF, 0x7E}}},
	{{{160, 30, 0},0, {1008, -16},{0xFF, 0xFF, 0xFF, 0xF1}}},
};

Gfx gradibox_Plane_mesh_tri_0[] = {
	gsSPVertex(gradibox_Plane_mesh_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_gradibox_gradithing[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, 0, ENVIRONMENT, 0, SHADE, 0, 0, 0, 0, 0, ENVIRONMENT, 0, SHADE, 0),
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx mat_revert_gradibox_gradithing[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPEndDisplayList(),
};

Gfx gradibox_Plane_mesh[] = {
	gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
	gsSPDisplayList(mat_gradibox_gradithing),
	gsSPDisplayList(gradibox_Plane_mesh_tri_0),
	gsSPDisplayList(mat_revert_gradibox_gradithing),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

