#include "src/game/envfx_snow.h"

const GeoLayout onoffblock1_000_switch_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, onoffblock1_000_displaylist_mesh_layer_1_mat_override_blueblock_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout onoffblock1_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(2, geo_switch_anim_state),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, onoffblock1_000_displaylist_mesh_layer_1),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, onoffblock1_000_switch_opt1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, onoffblock1_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
