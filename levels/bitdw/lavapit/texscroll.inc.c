void scroll_lavapit_pool_mesh_layer_1_vtx_0() {
	int i = 0;
	int count = 28;
	int width = 32 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(lavapit_pool_mesh_layer_1_vtx_0);

	deltaX = (int)(0.20000000298023224 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_bitdw_level_geo_lavapit() {
	scroll_lavapit_pool_mesh_layer_1_vtx_0();
}
