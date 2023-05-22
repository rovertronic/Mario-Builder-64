void scroll_sts_mat_agmoon_Static_layer1() {
	Gfx *mat = segmented_to_virtual(mat_agmoon_Static_layer1);
	shift_s(mat, 13, PACK_TILESIZE(0, 60));
	shift_t(mat, 13, PACK_TILESIZE(0, 100));
};

void scroll_rr_level_geo_agmoon() {
	scroll_sts_mat_agmoon_Static_layer1();
}
