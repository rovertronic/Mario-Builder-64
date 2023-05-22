void scroll_sts_mat_ssl_dl_Lava() {
	static int intervalTex0 = 5;
	static int curInterval0 = 5;
	Gfx *mat = segmented_to_virtual(mat_ssl_dl_Lava);

	if (--curInterval0 <= 0) {
		shift_s(mat, 19, PACK_TILESIZE(0, 64));
		curInterval0 = intervalTex0;
	}
};

void scroll_sts_mat_ssl_dl_SMB2_Waterfall() {
	static int intervalTex0 = 3;
	static int curInterval0 = 3;
	Gfx *mat = segmented_to_virtual(mat_ssl_dl_SMB2_Waterfall);

	if (--curInterval0 <= 0) {
		shift_s_down(mat, 19, PACK_TILESIZE(0, 64));
		curInterval0 = intervalTex0;
	}
};

void scroll_sts_mat_ssl_dl_SMB2_Vine() {
	static int intervalTex0 = 7;
	static int curInterval0 = 7;
	Gfx *mat = segmented_to_virtual(mat_ssl_dl_SMB2_Vine);

	if (--curInterval0 <= 0) {
		shift_s(mat, 19, PACK_TILESIZE(0, 64));
		curInterval0 = intervalTex0;
	}
};

void scroll_ssl() {
	scroll_sts_mat_ssl_dl_Lava();
	scroll_sts_mat_ssl_dl_SMB2_Waterfall();
	scroll_sts_mat_ssl_dl_SMB2_Vine();
}
