void scroll_sts_mat_robot_RoboNPC_Face() {
	static int intervalTex0 = 7;
	static int curInterval0 = 7;
	Gfx *mat = segmented_to_virtual(mat_robot_RoboNPC_Face);

	if (--curInterval0 <= 0) {
		shift_s(mat, 11, PACK_TILESIZE(0, 64));
		curInterval0 = intervalTex0;
	}
};

void scroll_sl_level_geo_robot() {
	scroll_sts_mat_robot_RoboNPC_Face();
}
