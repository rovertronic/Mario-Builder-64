void scroll_sts_mat_jrb_dl_Water_v4_layer5() {
	Gfx *mat = segmented_to_virtual(mat_jrb_dl_Water_v4_layer5);
	shift_s_down(mat, 14, PACK_TILESIZE(0, 1));
	shift_t_down(mat, 14, PACK_TILESIZE(0, 2));
	shift_s(mat, 22, PACK_TILESIZE(0, 1));
	shift_t_down(mat, 22, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_jrb_dl_Water_v4_001_layer5() {
	Gfx *mat = segmented_to_virtual(mat_jrb_dl_Water_v4_001_layer5);
	shift_s_down(mat, 15, PACK_TILESIZE(0, 1));
	shift_t_down(mat, 15, PACK_TILESIZE(0, 2));
	shift_s(mat, 23, PACK_TILESIZE(0, 1));
	shift_t_down(mat, 23, PACK_TILESIZE(0, 1));
};

void scroll_jrb() {
	scroll_sts_mat_jrb_dl_Water_v4_layer5();
	scroll_sts_mat_jrb_dl_Water_v4_001_layer5();
}
