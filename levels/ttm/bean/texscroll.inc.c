void scroll_sts_mat_bean_static() {
	Gfx *mat = segmented_to_virtual(mat_bean_static);
	shift_s(mat, 11, PACK_TILESIZE(0, 64));
	shift_t(mat, 11, PACK_TILESIZE(0, 32));
};

void scroll_ttm_level_geo_bean() {
	scroll_sts_mat_bean_static();
}
