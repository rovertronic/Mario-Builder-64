#include "src/game/envfx_snow.h"

const GeoLayout c5_bridge_geo[] = {
	GEO_CULLING_RADIUS(5000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, c5_bridge_Cube_007_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, c5_bridge_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
