void scroll_sts_mat_ladybug_Ladybug() {
	static int intervalTex0 = 10;
	static int curInterval0 = 10;
	Gfx *mat = segmented_to_virtual(mat_ladybug_Ladybug);

	if (--curInterval0 <= 0) {
		shift_s(mat, 19, PACK_TILESIZE(0, 64));
		curInterval0 = intervalTex0;
	}
};

void scroll_ssl_level_geo_ladybug() {
	scroll_sts_mat_ladybug_Ladybug();
}
