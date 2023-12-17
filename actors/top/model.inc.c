
Vtx top_topplane_mesh_vtx_0[4] = {
	{{{-150, 150, 150},0, {-16, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{150, 150, 150},0, {1008, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{150, 150, -150},0, {1008, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-150, 150, -150},0, {-16, -16},{0x0, 0x7F, 0x0, 0xFF}}},
};

Gfx top_topplane_mesh_tri_0[] = {
	gsSPVertex(top_topplane_mesh_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_top_TextureTemplate[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLightColor(LIGHT_1, 0xfefefeff),
    gsSPLightColor(LIGHT_2, 0x7f7f7fff),
	gsSPEndDisplayList(),
};

Gfx top_topplane_mesh[] = {
	gsSPDisplayList(mat_top_TextureTemplate),
	gsSPDisplayList(top_topplane_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

