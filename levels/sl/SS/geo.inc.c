#include "src/game/envfx_snow.h"

const GeoLayout SS_root1_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, SS_boner1_mesh_layer_1_mat_override_SS_Circle_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout SS_root1_opt2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, SS_boner1_mesh_layer_1_mat_override_SS_Square_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout SS_root1_opt3[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, SS_boner1_mesh_layer_1_mat_override_SS_Triangle_2),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout SS_root1_opt4[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, SS_boner1_mesh_layer_1_mat_override_SS_Star_3),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout SS_geo[] = {
	GEO_CULLING_RADIUS(20000),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(5, geo_switch_anim_state),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, SS_boner1_mesh_layer_1),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, SS_root1_opt1),
			GEO_BRANCH(1, SS_root1_opt2),
			GEO_BRANCH(1, SS_root1_opt3),
			GEO_BRANCH(1, SS_root1_opt4),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, SS_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
