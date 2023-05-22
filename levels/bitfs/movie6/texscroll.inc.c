void scroll_sts_mat_movie6_ProjectorBrick_layer5() {
	Gfx *mat = segmented_to_virtual(mat_movie6_ProjectorBrick_layer5);
	shift_s(mat, 20, PACK_TILESIZE(0, 3));
};

void scroll_bitfs_level_geo_movie6() {
	scroll_sts_mat_movie6_ProjectorBrick_layer5();
}
