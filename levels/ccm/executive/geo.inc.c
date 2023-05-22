#include "src/game/envfx_snow.h"

const GeoLayout executive_geo[] = {
	GEO_CULLING_RADIUS(30000),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, executive_root_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, executive_root_mesh_layer_4),
			GEO_BILLBOARD_WITH_PARAMS(LAYER_OPAQUE, 0, 5149, 0),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_ALPHA, executive_eye_mesh_layer_4),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, executive_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, executive_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
