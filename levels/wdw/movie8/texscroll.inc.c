void scroll_sts_mat_movie8_ProjectorBrick_layer5() {
	Gfx *mat = segmented_to_virtual(mat_movie8_ProjectorBrick_layer5);
	shift_s(mat, 20, PACK_TILESIZE(0, 3));
};

void scroll_wdw_level_geo_movie8() {
	scroll_sts_mat_movie8_ProjectorBrick_layer5();
}
