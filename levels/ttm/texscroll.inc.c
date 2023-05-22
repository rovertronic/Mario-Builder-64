void scroll_sts_mat_ttm_dl_Cosmicum_layer1() {
	Gfx *mat = segmented_to_virtual(mat_ttm_dl_Cosmicum_layer1);
	shift_t(mat, 12, PACK_TILESIZE(0, 1));
	shift_s(mat, 20, PACK_TILESIZE(0, 1));
};

void scroll_ttm() {
	scroll_sts_mat_ttm_dl_Cosmicum_layer1();
}
