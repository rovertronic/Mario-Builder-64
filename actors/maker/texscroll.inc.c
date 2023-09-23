void scroll_sts_mat_maker_MakerLava() {
	Gfx *mat = segmented_to_virtual(mat_maker_MakerLava);
	shift_s(mat, 7, PACK_TILESIZE(0, 1));
	shift_t(mat, 7, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_maker_MakerWater() {
	Gfx *mat = segmented_to_virtual(mat_maker_MakerWater);
	shift_s(mat, 7, PACK_TILESIZE(0, 1));
	shift_t(mat, 7, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_maker_MakerRetroLava() {
	static int intervalTex0 = 10;
	static int curInterval0 = 10;
	Gfx *mat = segmented_to_virtual(mat_maker_MakerRetroLava);

	if (--curInterval0 <= 0) {
		shift_s(mat, 8, PACK_TILESIZE(0, 5));
		shift_t(mat, 8, PACK_TILESIZE(0, 5));
		curInterval0 = intervalTex0;
	}
};

void scroll_sts_mat_maker_MakerVoid() {
	Gfx *mat = segmented_to_virtual(mat_maker_MakerVoid);
	shift_s(mat, 7, PACK_TILESIZE(0, 1));
	shift_t(mat, 7, PACK_TILESIZE(0, 1));
	shift_t(mat, -1, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_maker_MakerQuicksand() {
	Gfx *mat = segmented_to_virtual(mat_maker_MakerQuicksand);
	shift_s(mat, 7, PACK_TILESIZE(0, 1));
	shift_t(mat, 7, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_maker_MakerRetroWater() {
	static int intervalTex0 = 10;
	static int curInterval0 = 10;
	Gfx *mat = segmented_to_virtual(mat_maker_MakerRetroWater);

	if (--curInterval0 <= 0) {
		shift_s(mat, 8, PACK_TILESIZE(0, 5));
		shift_t(mat, 8, PACK_TILESIZE(0, 5));
		curInterval0 = intervalTex0;
	}
};

void scroll_actor_dl_maker() {
	scroll_sts_mat_maker_MakerLava();
	scroll_sts_mat_maker_MakerWater();
	scroll_sts_mat_maker_MakerRetroLava();
	scroll_sts_mat_maker_MakerVoid();
	scroll_sts_mat_maker_MakerQuicksand();
	scroll_sts_mat_maker_MakerRetroWater();
}
