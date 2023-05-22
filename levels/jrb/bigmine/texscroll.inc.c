void scroll_bigmine_Cylinder_010_mesh_layer_1_vtx_1() {
	int i = 0;
	int count = 16;
	int width = 1 * 0x20;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(bigmine_Cylinder_010_mesh_layer_1_vtx_1);

	deltaY = (int)(1.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_jrb_level_geo_bigmine() {
	scroll_bigmine_Cylinder_010_mesh_layer_1_vtx_1();
}
