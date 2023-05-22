void scroll_executive__circle_mesh_vtx_0() {
	int i = 0;
	int count = 71;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(executive__circle_mesh_vtx_0);

	deltaX = (int)(0.25 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_sts_mat_executive__Static_layer1() {
	Gfx *mat = segmented_to_virtual(mat_executive__Static_layer1);
	shift_s(mat, 15, PACK_TILESIZE(0, 60));
	shift_t(mat, 15, PACK_TILESIZE(0, 100));
};

void scroll_actor_dl_executive_() {
	scroll_executive__circle_mesh_vtx_0();
	scroll_sts_mat_executive__Static_layer1();
}
