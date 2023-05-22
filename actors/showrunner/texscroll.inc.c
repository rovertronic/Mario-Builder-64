void scroll_sts_mat_showrunner_Static() {
	Gfx *mat = segmented_to_virtual(mat_showrunner_Static);
	shift_s(mat, 11, PACK_TILESIZE(0, 32));
	shift_t(mat, 11, PACK_TILESIZE(0, 16));
};

void scroll_actor_geo_showrunner() {
	scroll_sts_mat_showrunner_Static();
}
