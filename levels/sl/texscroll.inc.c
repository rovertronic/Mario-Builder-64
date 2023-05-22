void scroll_sts_mat_sl_dl_Blava_layer1() {
	Gfx *mat = segmented_to_virtual(mat_sl_dl_Blava_layer1);
	shift_s(mat, 12, PACK_TILESIZE(0, 1));
	shift_t(mat, 20, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_sl_dl_Machine() {
	static int intervalTex0 = 6;
	static int curInterval0 = 6;
	Gfx *mat = segmented_to_virtual(mat_sl_dl_Machine);

	if (--curInterval0 <= 0) {
		shift_s(mat, 11, PACK_TILESIZE(0, 256));
		curInterval0 = intervalTex0;
	}
};

void scroll_sts_mat_sl_dl_lights() {
	static int intervalTex0 = 2;
	static int curInterval0 = 2;
	Gfx *mat = segmented_to_virtual(mat_sl_dl_lights);

	if (--curInterval0 <= 0) {
		shift_s(mat, 18, PACK_TILESIZE(0, 128));
		curInterval0 = intervalTex0;
	}
};

void scroll_sl() {
	scroll_sts_mat_sl_dl_Blava_layer1();
	scroll_sts_mat_sl_dl_Machine();
	scroll_sts_mat_sl_dl_lights();
}
