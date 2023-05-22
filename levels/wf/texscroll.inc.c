void scroll_wf_dl_slide_001_mesh_vtx_0() {
	int i = 0;
	int count = 174;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(wf_dl_slide_001_mesh_vtx_0);

	deltaY = (int)(2.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_wf_dl_slide_002_mesh_vtx_0() {
	int i = 0;
	int count = 16;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(wf_dl_slide_002_mesh_vtx_0);

	deltaY = (int)(2.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_wf_dl_Arena_mesh_layer_1_vtx_1() {
	int i = 0;
	int count = 26;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(wf_dl_Arena_mesh_layer_1_vtx_1);

	deltaX = (int)(1.0 * 0x20) % width;
	deltaY = (int)(1.0 * 0x20) % height;

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

void scroll_wf() {
	scroll_wf_dl_slide_001_mesh_vtx_0();
	scroll_wf_dl_slide_002_mesh_vtx_0();
	scroll_wf_dl_Arena_mesh_layer_1_vtx_1();
}
