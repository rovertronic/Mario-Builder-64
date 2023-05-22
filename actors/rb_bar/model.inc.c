Vtx rb_bar_Plane_001_mesh_vtx_0[4] = {
	{{{-6, 0, 0},0, {182, 679},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{6, 0, 0},0, {324, 679},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{6, 91, 0},0, {324, 237},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-6, 91, 0},0, {182, 237},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx rb_bar_Plane_001_mesh_tri_0[] = {
	gsSPVertex(rb_bar_Plane_001_mesh_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_rb_bar_bar[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(1, 0, PRIMITIVE, 0, 0, 0, 0, ENVIRONMENT, 1, 0, PRIMITIVE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 254, 145, 82, 255),
	gsSPEndDisplayList(),
};

Gfx rb_bar_Plane_001_mesh[] = {
	gsSPDisplayList(mat_rb_bar_bar),
	gsSPDisplayList(rb_bar_Plane_001_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

