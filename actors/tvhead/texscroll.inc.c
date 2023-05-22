void scroll_sts_mat_tvhead_Static() {
	Gfx *mat = segmented_to_virtual(mat_tvhead_Static);
	shift_s(mat, 11, PACK_TILESIZE(0, 74));
	shift_t(mat, 11, PACK_TILESIZE(0, 32));
	shift_s(mat, -1, PACK_TILESIZE(0, 74));
	shift_t(mat, -1, PACK_TILESIZE(0, 32));
};

void scroll_actor_geo_tvhead() {
	scroll_sts_mat_tvhead_Static();
}
