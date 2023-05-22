void scroll_sts_mat_showrunner_tv_Static() {
	Gfx *mat = segmented_to_virtual(mat_showrunner_tv_Static);
	shift_s(mat, 11, PACK_TILESIZE(0, 32));
	shift_t(mat, 11, PACK_TILESIZE(0, 16));
};

void scroll_castle_inside_level_geo_showrunner_tv() {
	scroll_sts_mat_showrunner_tv_Static();
}
