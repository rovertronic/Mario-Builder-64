Vtx bigpainting_bigpainting_mesh_vtx_0[14] = {
	{{ {-16, 0, 0}, 0, {0, 1024}, {0, 0, 127, 255} }},
	{{ {0, 16, 0}, 0, {1024, 0}, {0, 0, 127, 255} }},
	{{ {-16, 16, 0}, 0, {0, 0}, {0, 0, 127, 255} }},
	{{ {0, 0, 0}, 0, {1024, 1024}, {0, 0, 127, 255} }},
	{{ {-16, -16, 0}, 0, {0, 2048}, {0, 0, 127, 255} }},
	{{ {0, 0, 0}, 0, {1024, 1024}, {0, 0, 127, 255} }},
	{{ {-16, 0, 0}, 0, {0, 1024}, {0, 0, 127, 255} }},
	{{ {0, -16, 0}, 0, {1024, 2048}, {0, 0, 127, 255} }},
	{{ {16, 0, 0}, 0, {2048, 1024}, {0, 0, 127, 255} }},
	{{ {16, -16, 0}, 0, {2048, 2048}, {0, 0, 127, 255} }},
	{{ {0, 0, 0}, 0, {1024, 1024}, {0, 0, 127, 255} }},
	{{ {16, 0, 0}, 0, {2048, 1024}, {0, 0, 127, 255} }},
	{{ {16, 16, 0}, 0, {2048, 0}, {0, 0, 127, 255} }},
	{{ {0, 16, 0}, 0, {1024, 0}, {0, 0, 127, 255} }},
};

Gfx bigpainting_bigpainting_mesh_tri_0[] = {
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 9, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTile(7, 0, 0, 128, 128),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 9, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 0, 0, 128, 128),
	gsSPVertex(bigpainting_bigpainting_mesh_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsDPLoadSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTile(7, 0, 128, 252, 252),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 0, 128, 252, 252),
	gsSPVertex(bigpainting_bigpainting_mesh_vtx_0 + 4, 6, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(3, 4, 1, 0, 3, 5, 4, 0),
	gsDPLoadSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTile(7, 128, 0, 252, 128),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 128, 0, 252, 128),
	gsSPVertex(bigpainting_bigpainting_mesh_vtx_0 + 10, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_bigpainting_bigpainting[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0),
	gsSPGeometryMode(G_ZBUFFER | G_CULL_BACK, 0),
	gsDPSetTextureFilter(G_TF_AVERAGE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx mat_revert_bigpainting_bigpainting[] = {
	gsDPPipeSync(),
	gsSPGeometryMode(0, G_ZBUFFER | G_CULL_BACK),
	gsDPSetTextureFilter(G_TF_BILERP),
	gsSPEndDisplayList(),
};

Gfx bigpainting_bigpainting_mesh_part1[] = {
	gsSPDisplayList(mat_bigpainting_bigpainting),
	gsSPEndDisplayList(),
};

Gfx bigpainting_bigpainting_mesh_part2[] = {
	gsSPDisplayList(bigpainting_bigpainting_mesh_tri_0),
	gsSPDisplayList(mat_revert_bigpainting_bigpainting),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

