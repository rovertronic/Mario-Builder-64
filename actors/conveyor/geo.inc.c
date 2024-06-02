#include "src/game/envfx_snow.h"

const GeoLayout conveyor_000_switch_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, conveyor_000_displaylist_mesh_layer_1_mat_override_conveyor_top_red_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout conveyor_000_switch_opt2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, conveyor_000_displaylist_mesh_layer_1_mat_override_conveyor_top_blue_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout conveyor_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(3, geo_switch_anim_state),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, conveyor_000_displaylist_mesh_layer_1),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, conveyor_000_switch_opt1),
			GEO_BRANCH(1, conveyor_000_switch_opt2),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, conveyor_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
