void scroll_gfx_mat_maker_MakerServerAcid() {
	Gfx *mat = segmented_to_virtual(mat_maker_MakerServerAcid);

	shift_s(mat, 15, PACK_TILESIZE(0, 1));
	shift_t(mat, 15, PACK_TILESIZE(0, 1));

};

void scroll_gfx_mat_maker_MakerGreenWater() {
	Gfx *mat = segmented_to_virtual(mat_maker_MakerGreenWater);

	shift_s(mat, 16, PACK_TILESIZE(0, 1));
	shift_t(mat, 16, PACK_TILESIZE(0, 1));

};

void scroll_gfx_mat_maker_MakerRetroLava() {
	Gfx *mat = segmented_to_virtual(mat_maker_MakerRetroLava);
	static int interval_tex_maker_MakerRetroLava = 10;
	static int cur_interval_tex_maker_MakerRetroLava = 10;

	if (--cur_interval_tex_maker_MakerRetroLava <= 0) {
		shift_s(mat, 15, PACK_TILESIZE(0, 5));
		shift_t(mat, 15, PACK_TILESIZE(0, 5));
		cur_interval_tex_maker_MakerRetroLava = interval_tex_maker_MakerRetroLava;
	}

};

void scroll_gfx_mat_maker_MakerVoid() {
	Gfx *mat = segmented_to_virtual(mat_maker_MakerVoid);

	shift_s(mat, 15, PACK_TILESIZE(0, 1));
	shift_t(mat, 15, PACK_TILESIZE(0, 1));

};

void scroll_gfx_mat_maker_MakerQuicksand() {
	Gfx *mat = segmented_to_virtual(mat_maker_MakerQuicksand);

	shift_s(mat, 15, PACK_TILESIZE(0, 1));
	shift_t(mat, 15, PACK_TILESIZE(0, 1));

};

void scroll_gfx_mat_maker_MakerRetroWater() {
	Gfx *mat = segmented_to_virtual(mat_maker_MakerRetroWater);
	static int interval_tex_maker_MakerRetroWater = 10;
	static int cur_interval_tex_maker_MakerRetroWater = 10;

	if (--cur_interval_tex_maker_MakerRetroWater <= 0) {
		shift_s(mat, 16, PACK_TILESIZE(0, 5));
		shift_t(mat, 16, PACK_TILESIZE(0, 5));
		cur_interval_tex_maker_MakerRetroWater = interval_tex_maker_MakerRetroWater;
	}

};

void scroll_gfx_mat_maker_MakerBurningIce() {
	Gfx *mat = segmented_to_virtual(mat_maker_MakerBurningIce);

	shift_s(mat, 15, PACK_TILESIZE(0, 1));
	shift_t(mat, 15, PACK_TILESIZE(0, 1));

};

void scroll_gfx_mat_maker_MakerWater() {
	Gfx *mat = segmented_to_virtual(mat_maker_MakerWater);

	shift_s(mat, 16, PACK_TILESIZE(0, 1));
	shift_t(mat, 16, PACK_TILESIZE(0, 1));

};

void scroll_gfx_mat_maker_MakerLava() {
	Gfx *mat = segmented_to_virtual(mat_maker_MakerLava);

	shift_s(mat, 15, PACK_TILESIZE(0, 1));
	shift_t(mat, 15, PACK_TILESIZE(0, 1));

};

void scroll_gfx_mat_maker_MakerVanillaLava() {
	Gfx *mat = segmented_to_virtual(mat_maker_MakerVanillaLava);

	shift_s(mat, 15, PACK_TILESIZE(0, 1));
	shift_t(mat, 15, PACK_TILESIZE(0, 1));

};

void scroll_actor_dl_maker() {
	scroll_gfx_mat_maker_MakerServerAcid();
	scroll_gfx_mat_maker_MakerGreenWater();
	scroll_gfx_mat_maker_MakerRetroLava();
	scroll_gfx_mat_maker_MakerVoid();
	scroll_gfx_mat_maker_MakerQuicksand();
	scroll_gfx_mat_maker_MakerRetroWater();
	scroll_gfx_mat_maker_MakerBurningIce();
	scroll_gfx_mat_maker_MakerWater();
	scroll_gfx_mat_maker_MakerLava();
	scroll_gfx_mat_maker_MakerVanillaLava();
};
