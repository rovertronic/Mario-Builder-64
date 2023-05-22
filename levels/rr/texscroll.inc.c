void scroll_rr_dl_Cylinder_mesh_layer_1_vtx_6() {
	int i = 0;
	int count = 55;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(rr_dl_Cylinder_mesh_layer_1_vtx_6);

	deltaX = (int)(1.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_sts_mat_rr_dl_static_quicksand() {
	Gfx *mat = segmented_to_virtual(mat_rr_dl_static_quicksand);
	shift_s(mat, 11, PACK_TILESIZE(0, 53));
	shift_t(mat, 11, PACK_TILESIZE(0, 82));
};

void scroll_rr_dl_solid_mesh_layer_1_vtx_4() {
	int i = 0;
	int count = 24;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(rr_dl_solid_mesh_layer_1_vtx_4);

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

void scroll_sts_mat_rr_dl_f3d_material_layer1() {
	Gfx *mat = segmented_to_virtual(mat_rr_dl_f3d_material_layer1);
	shift_s(mat, 12, PACK_TILESIZE(0, 1));
	shift_t(mat, 20, PACK_TILESIZE(0, 1));
};

void scroll_rr_dl_Water_Box_Mesh_001_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 4;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(rr_dl_Water_Box_Mesh_001_mesh_layer_5_vtx_0);

	deltaX = (int)(0.5 * 0x20) % width;
	deltaY = (int)(0.20000000298023224 * 0x20) % height;

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

void scroll_sts_mat_rr_dl_static_quicksand_darker() {
	static int intervalTex0 = 5;
	static int curInterval0 = 5;
	Gfx *mat = segmented_to_virtual(mat_rr_dl_static_quicksand_darker);

	if (--curInterval0 <= 0) {
		shift_s(mat, 11, PACK_TILESIZE(0, 53));
		shift_t(mat, 11, PACK_TILESIZE(0, 82));
		curInterval0 = intervalTex0;
	}
};

void scroll_rr() {
	scroll_rr_dl_Cylinder_mesh_layer_1_vtx_6();
	scroll_sts_mat_rr_dl_static_quicksand();
	scroll_rr_dl_solid_mesh_layer_1_vtx_4();
	scroll_sts_mat_rr_dl_f3d_material_layer1();
	scroll_rr_dl_Water_Box_Mesh_001_mesh_layer_5_vtx_0();
	scroll_sts_mat_rr_dl_static_quicksand_darker();
}
