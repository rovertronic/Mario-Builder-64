void scroll_bob_dl_a1_lev_geo_col_mesh_vtx_0() {
	int i = 0;
	int count = 70;
	int width = 32 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(bob_dl_a1_lev_geo_col_mesh_vtx_0);

	deltaX = (int)(0.0 * 0x20) % width;
	deltaY = (int)(-0.5 * 0x20) % height;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}
	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
		vertices[i].n.tc[1] += deltaY;
	}
	currentX += deltaX;	currentY += deltaY;
}

void scroll_bob() {
	scroll_bob_dl_a1_lev_geo_col_mesh_vtx_0();
}
