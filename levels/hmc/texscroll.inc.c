void scroll_sts_mat_hmc_dl_Mesa_Scroll_layer1() {
	Gfx *mat = segmented_to_virtual(mat_hmc_dl_Mesa_Scroll_layer1);
	shift_s(mat, 13, PACK_TILESIZE(0, 1));
	shift_s(mat, 21, PACK_TILESIZE(0, 4));
};

void scroll_sts_mat_hmc_dl_Sand_Scroll() {
	Gfx *mat = segmented_to_virtual(mat_hmc_dl_Sand_Scroll);
	shift_s(mat, 18, PACK_TILESIZE(0, 4));
};

void scroll_sts_mat_hmc_dl_Rail_Scroll() {
	Gfx *mat = segmented_to_virtual(mat_hmc_dl_Rail_Scroll);
	shift_t_down(mat, 18, PACK_TILESIZE(0, 4));
};

void scroll_hmc() {
	scroll_sts_mat_hmc_dl_Mesa_Scroll_layer1();
	scroll_sts_mat_hmc_dl_Sand_Scroll();
	scroll_sts_mat_hmc_dl_Rail_Scroll();
}
