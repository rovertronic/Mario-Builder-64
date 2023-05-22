void scroll_sts_mat_agcrack_static_quicksand_001() {
	Gfx *mat = segmented_to_virtual(mat_agcrack_static_quicksand_001);
	shift_s(mat, 11, PACK_TILESIZE(0, 53));
	shift_t(mat, 11, PACK_TILESIZE(0, 82));
};

void scroll_rr_level_geo_agcrack() {
	scroll_sts_mat_agcrack_static_quicksand_001();
}
