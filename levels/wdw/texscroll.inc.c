void scroll_wdw_dl_vis_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 25;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(wdw_dl_vis_mesh_layer_5_vtx_0);

	deltaX = (int)(0.10000000149011612 * 0x20) % width;
	deltaY = (int)(0.10000000149011612 * 0x20) % height;

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

void scroll_sts_mat_wdw_dl_Blinkers() {
	static int intervalTex0 = 4;
	static int curInterval0 = 4;
	Gfx *mat = segmented_to_virtual(mat_wdw_dl_Blinkers);

	if (--curInterval0 <= 0) {
		shift_t(mat, 17, PACK_TILESIZE(0, 128));
		curInterval0 = intervalTex0;
	}
};

void scroll_wdw_dl_vis_mesh_layer_1_vtx_0() {
	int i = 0;
	int count = 12;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(wdw_dl_vis_mesh_layer_1_vtx_0);

	deltaX = (int)(0.10000000149011612 * 0x20) % width;
	deltaY = (int)(0.10000000149011612 * 0x20) % height;

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

void scroll_sts_mat_wdw_dl_Sign11() {
	static int intervalTex0 = 3;
	static int curInterval0 = 3;
	Gfx *mat = segmented_to_virtual(mat_wdw_dl_Sign11);

	if (--curInterval0 <= 0) {
		shift_s(mat, 18, PACK_TILESIZE(0, 128));
		curInterval0 = intervalTex0;
	}
};

void scroll_sts_mat_wdw_dl_Lights() {
	static int intervalTex0 = 3;
	static int curInterval0 = 3;
	Gfx *mat = segmented_to_virtual(mat_wdw_dl_Lights);

	if (--curInterval0 <= 0) {
		shift_s(mat, 11, PACK_TILESIZE(0, 128));
		curInterval0 = intervalTex0;
	}
};

void scroll_sts_mat_wdw_dl_Sign9() {
	static int intervalTex0 = 3;
	static int curInterval0 = 3;
	Gfx *mat = segmented_to_virtual(mat_wdw_dl_Sign9);

	if (--curInterval0 <= 0) {
		shift_s(mat, 18, PACK_TILESIZE(0, 256));
		curInterval0 = intervalTex0;
	}
};

void scroll_sts_mat_wdw_dl_Sign10() {
	static int intervalTex0 = 5;
	static int curInterval0 = 5;
	Gfx *mat = segmented_to_virtual(mat_wdw_dl_Sign10);

	if (--curInterval0 <= 0) {
		shift_s(mat, 18, PACK_TILESIZE(0, 128));
		curInterval0 = intervalTex0;
	}
};

void scroll_wdw_dl_Cube_010_mesh_layer_1_vtx_7() {
	int i = 0;
	int count = 12;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(wdw_dl_Cube_010_mesh_layer_1_vtx_7);

	deltaX = (int)(1.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_wdw_dl_Cube_010_mesh_layer_1_vtx_8() {
	int i = 0;
	int count = 32;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(wdw_dl_Cube_010_mesh_layer_1_vtx_8);

	deltaX = (int)(1.5 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_wdw_dl_Cube_010_mesh_layer_1_vtx_9() {
	int i = 0;
	int count = 10;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(wdw_dl_Cube_010_mesh_layer_1_vtx_9);

	deltaX = (int)(1.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_wdw() {
	scroll_wdw_dl_vis_mesh_layer_5_vtx_0();
	scroll_sts_mat_wdw_dl_Blinkers();
	scroll_wdw_dl_vis_mesh_layer_1_vtx_0();
	scroll_sts_mat_wdw_dl_Sign11();
	scroll_sts_mat_wdw_dl_Lights();
	scroll_sts_mat_wdw_dl_Sign9();
	scroll_sts_mat_wdw_dl_Sign10();
	scroll_wdw_dl_Cube_010_mesh_layer_1_vtx_7();
	scroll_wdw_dl_Cube_010_mesh_layer_1_vtx_8();
	scroll_wdw_dl_Cube_010_mesh_layer_1_vtx_9();
}
