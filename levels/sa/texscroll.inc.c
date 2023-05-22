void scroll_sa_dl_Cylinder_009_mesh_vtx_0() {
	int i = 0;
	int count = 14;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(sa_dl_Cylinder_009_mesh_vtx_0);

	deltaX = (int)(3.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_sa() {
	scroll_sa_dl_Cylinder_009_mesh_vtx_0();
}
