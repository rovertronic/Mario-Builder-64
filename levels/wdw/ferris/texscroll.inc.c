void scroll_sts_mat_ferris_Blinkers() {
	static int intervalTex0 = 4;
	static int curInterval0 = 4;
	Gfx *mat = segmented_to_virtual(mat_ferris_Blinkers);

	if (--curInterval0 <= 0) {
		shift_t(mat, 17, PACK_TILESIZE(0, 128));
		curInterval0 = intervalTex0;
	}
};

void scroll_wdw_level_geo_ferris() {
	scroll_sts_mat_ferris_Blinkers();
}
