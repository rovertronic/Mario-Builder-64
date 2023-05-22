void scroll_sts_mat_bits_stairs_ProjectorBrick_layer5() {
	Gfx *mat = segmented_to_virtual(mat_bits_stairs_ProjectorBrick_layer5);
	shift_s(mat, 20, PACK_TILESIZE(0, 3));
};

void scroll_bits_level_geo_bits_stairs() {
	scroll_sts_mat_bits_stairs_ProjectorBrick_layer5();
}
