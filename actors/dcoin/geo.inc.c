#include "src/game/envfx_snow.h"

const GeoLayout dcoin_Bone_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, dcoin_Coin_mesh_layer_4_mat_override_coin2_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout dcoin_Bone_opt2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, dcoin_Coin_mesh_layer_4_mat_override_coin3_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout dcoin_Bone_opt3[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, dcoin_Coin_mesh_layer_4_mat_override_coin4_2),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout dcoin_Bone_opt4[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, dcoin_Coin_mesh_layer_4_mat_override_coin5_3),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout dcoin_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(5, geo_switch_anim_state),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_ALPHA, dcoin_Coin_mesh_layer_4),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, dcoin_Bone_opt1),
			GEO_BRANCH(1, dcoin_Bone_opt2),
			GEO_BRANCH(1, dcoin_Bone_opt3),
			GEO_BRANCH(1, dcoin_Bone_opt4),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, dcoin_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
