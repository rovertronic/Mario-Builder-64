
Vtx BadgeSelect_Plane_mesh_vtx_0[8] = {
	{{{-12, 12, 0},0, {78, 78},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{12, 12, 0},0, {914, 78},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{16, 16, 0},0, {1008, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{16, -16, 0},0, {1008, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{12, -12, 0},0, {914, 914},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-16, -16, 0},0, {-16, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-12, -12, 0},0, {78, 914},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-16, 16, 0},0, {-16, -16},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx BadgeSelect_Plane_mesh_tri_0[] = {
	gsSPVertex(BadgeSelect_Plane_mesh_vtx_0 + 0, 8, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(1, 3, 2, 0),
	gsSP1Triangle(1, 4, 3, 0),
	gsSP1Triangle(4, 5, 3, 0),
	gsSP1Triangle(4, 6, 5, 0),
	gsSP1Triangle(6, 7, 5, 0),
	gsSP1Triangle(6, 0, 7, 0),
	gsSP1Triangle(0, 2, 7, 0),
	gsSPEndDisplayList(),
};


Gfx mat_BadgeSelect_Indicator[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLightColor(LIGHT_1, 0xfefefeff),
    gsSPLightColor(LIGHT_2, 0x7f7f7fff),
	gsSPEndDisplayList(),
};


Gfx BadgeSelect_Plane_mesh[] = {
	gsSPDisplayList(mat_BadgeSelect_Indicator),
	gsSPDisplayList(BadgeSelect_Plane_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};



