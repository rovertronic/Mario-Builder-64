void scroll_sts_mat_tvshop_Static() {
	Gfx *mat = segmented_to_virtual(mat_tvshop_Static);
	shift_s(mat, 11, PACK_TILESIZE(0, 52));
	shift_t(mat, 11, PACK_TILESIZE(0, 13));
};

void scroll_bits_level_geo_tvshop() {
	scroll_sts_mat_tvshop_Static();
}
