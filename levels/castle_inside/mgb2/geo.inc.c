#include "src/game/envfx_snow.h"

const GeoLayout mgb2_geo[] = {
	GEO_CULLING_RADIUS(500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, mgb2_mgb_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, mgb2_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
