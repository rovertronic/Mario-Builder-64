void scroll_castle_inside_dl_Cube_004Water_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 16;
	int width = 32 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int timeX;
	float amplitudeX = 1.0;
	float frequencyX = 0.5;
	float offsetX = 0.0;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(castle_inside_dl_Cube_004Water_mesh_layer_5_vtx_0);

	deltaX = (int)(amplitudeX * frequencyX * coss((frequencyX * timeX + offsetX) * (1024 * 16 - 1) / 6.28318530718) * 0x20);
	deltaY = (int)(0.5 * 0x20) % height;

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
	currentX += deltaX;	timeX += 1;	currentY += deltaY;
}

void scroll_castle_inside_dl_Cube_004Water_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 8;
	int width = 32 * 0x20;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(castle_inside_dl_Cube_004Water_mesh_layer_5_vtx_1);

	deltaY = (int)(0.25 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_castle_inside_dl_Cube_004Water_mesh_layer_5_vtx_2() {
	int i = 0;
	int count = 8;
	int width = 64 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(castle_inside_dl_Cube_004Water_mesh_layer_5_vtx_2);

	deltaX = (int)(0.10000000149011612 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_castle_inside_dl_Cube_006_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 4;
	int width = 32 * 0x20;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(castle_inside_dl_Cube_006_mesh_layer_5_vtx_0);

	deltaY = (int)(0.25 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_castle_inside_dl_Cube_006_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 4;
	int width = 64 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(castle_inside_dl_Cube_006_mesh_layer_5_vtx_1);

	deltaX = (int)(0.10000000149011612 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_castle_inside_dl_Cube_014_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 28;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(castle_inside_dl_Cube_014_mesh_layer_5_vtx_1);

	deltaY = (int)(0.20000000298023224 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_sts_mat_castle_inside_dl_CloudXsky_layer1() {
	static int intervalTex0 = 2;
	static int curInterval0 = 2;
	Gfx *mat = segmented_to_virtual(mat_castle_inside_dl_CloudXsky_layer1);

	if (--curInterval0 <= 0) {
		shift_s(mat, 13, PACK_TILESIZE(0, 1));
		curInterval0 = intervalTex0;
	}
};

void scroll_sts_mat_castle_inside_dl_vCloud_layer1() {
	static int intervalTex1 = 2;
	static int curInterval1 = 2;
	Gfx *mat = segmented_to_virtual(mat_castle_inside_dl_vCloud_layer1);

	if (--curInterval1 <= 0) {
		shift_s(mat, 21, PACK_TILESIZE(0, 1));
		curInterval1 = intervalTex1;
	}
};

void scroll_sts_mat_castle_inside_dl_BillboardWHAT_layer5() {
	Gfx *mat = segmented_to_virtual(mat_castle_inside_dl_BillboardWHAT_layer5);
	shift_s(mat, 22, PACK_TILESIZE(0, 8));
};

void scroll_castle_inside() {
	scroll_castle_inside_dl_Cube_004Water_mesh_layer_5_vtx_0();
	scroll_castle_inside_dl_Cube_004Water_mesh_layer_5_vtx_1();
	scroll_castle_inside_dl_Cube_004Water_mesh_layer_5_vtx_2();
	scroll_castle_inside_dl_Cube_006_mesh_layer_5_vtx_0();
	scroll_castle_inside_dl_Cube_006_mesh_layer_5_vtx_1();
	scroll_castle_inside_dl_Cube_014_mesh_layer_5_vtx_1();
	scroll_sts_mat_castle_inside_dl_CloudXsky_layer1();
	scroll_sts_mat_castle_inside_dl_vCloud_layer1();
	scroll_sts_mat_castle_inside_dl_BillboardWHAT_layer5();
}
