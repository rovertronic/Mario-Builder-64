void scroll_sts_mat_wmotr_dl_PoolTileRef_layer1() {
	Gfx *mat = segmented_to_virtual(mat_wmotr_dl_PoolTileRef_layer1);
	shift_s(mat, 21, PACK_TILESIZE(0, 1));
	shift_t(mat, 21, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_wmotr_dl_sm64_water_mat() {
	Gfx *mat = segmented_to_virtual(mat_wmotr_dl_sm64_water_mat);
	shift_s(mat, 17, PACK_TILESIZE(0, 1));
	shift_t(mat, 17, PACK_TILESIZE(0, 1));
};

void scroll_wmotr() {
	scroll_sts_mat_wmotr_dl_PoolTileRef_layer1();
	scroll_sts_mat_wmotr_dl_sm64_water_mat();
}
