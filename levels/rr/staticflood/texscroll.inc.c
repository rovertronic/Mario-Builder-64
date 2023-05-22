void scroll_sts_mat_staticflood_static_quicksand() {
	Gfx *mat = segmented_to_virtual(mat_staticflood_static_quicksand);
	shift_s(mat, 11, PACK_TILESIZE(0, 53));
	shift_t(mat, 11, PACK_TILESIZE(0, 82));
};

void scroll_rr_level_geo_staticflood() {
	scroll_sts_mat_staticflood_static_quicksand();
}
