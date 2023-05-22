#include "src/game/envfx_snow.h"

const GeoLayout projector2_switch_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, projector2_projector_mesh_layer_1_mat_override_LowerLight_0),
		GEO_DISPLAY_LIST(LAYER_ALPHA, projector2_projector_mesh_layer_4_mat_override_LowerLight_0),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, projector2_projector_mesh_layer_5_mat_override_LowerLight_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout projector2_switch_opt2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, projector2_projector_mesh_layer_1_mat_override_Light_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, projector2_projector_mesh_layer_4_mat_override_Light_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, projector2_projector_mesh_layer_5_mat_override_Light_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout projector2_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(3, geo_switch_anim_state),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, projector2_projector_mesh_layer_1),
				GEO_DISPLAY_LIST(LAYER_ALPHA, projector2_projector_mesh_layer_4),
				GEO_DISPLAY_LIST(LAYER_TRANSPARENT, projector2_projector_mesh_layer_5),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, projector2_switch_opt1),
			GEO_BRANCH(1, projector2_switch_opt2),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, projector2_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, projector2_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, projector2_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
