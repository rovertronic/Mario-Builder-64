void scroll_sts_mat_makerwater_water() {
	Gfx *mat = segmented_to_virtual(mat_makerwater_water);
	shift_s(mat, 18, PACK_TILESIZE(0, 1));
	shift_t(mat, 18, PACK_TILESIZE(0, 1));
};

void scroll_actor_dl_makerwater() {
	scroll_sts_mat_makerwater_water();
}
