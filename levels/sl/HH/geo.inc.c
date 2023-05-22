#include "src/game/envfx_snow.h"

const GeoLayout HH_root_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, HH_boner_mesh_layer_1_mat_override_HH_Circle_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout HH_root_opt2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, HH_boner_mesh_layer_1_mat_override_HH_Square_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout HH_root_opt3[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, HH_boner_mesh_layer_1_mat_override_HH_Triangle_2),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout HH_root_opt4[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, HH_boner_mesh_layer_1_mat_override_HH_Star_3),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout HH_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(5, geo_switch_anim_state),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, HH_boner_mesh_layer_1),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, HH_root_opt1),
			GEO_BRANCH(1, HH_root_opt2),
			GEO_BRANCH(1, HH_root_opt3),
			GEO_BRANCH(1, HH_root_opt4),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, HH_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
