#include "src/game/envfx_snow.h"

const GeoLayout thwompking_switch_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, thwompking_dl_mesh_layer_1_mat_override_ThwompFace2_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout thwompking_switch_opt2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, thwompking_dl_mesh_layer_1_mat_override_ThwompFace3_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout thwompking_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_CULLING_RADIUS(1000),
		GEO_OPEN_NODE(),
			GEO_SHADOW(11, 204, 300),
			GEO_OPEN_NODE(),
				GEO_SWITCH_CASE(3, geo_switch_anim_state),
				GEO_OPEN_NODE(),
					GEO_NODE_START(),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_OPAQUE, thwompking_dl_mesh_layer_1),
					GEO_CLOSE_NODE(),
					GEO_BRANCH(1, thwompking_switch_opt1),
					GEO_BRANCH(1, thwompking_switch_opt2),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, thwompking_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
