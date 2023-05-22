#include "src/game/envfx_snow.h"

const GeoLayout agcrack_switch_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, agcrack_dl_mesh_layer_5_mat_override_Crack2_0),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, agcrack_dl_mesh_layer_1_mat_override_Crack2_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout agcrack_switch_opt2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, agcrack_dl_mesh_layer_5_mat_override_Crack3_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, agcrack_dl_mesh_layer_1_mat_override_Crack3_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout agcrack_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(3, geo_switch_anim_state),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_TRANSPARENT, agcrack_dl_mesh_layer_5),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, agcrack_dl_mesh_layer_1),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, agcrack_switch_opt1),
			GEO_BRANCH(1, agcrack_switch_opt2),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, agcrack_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, agcrack_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
