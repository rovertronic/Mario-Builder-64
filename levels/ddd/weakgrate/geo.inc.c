#include "src/game/envfx_snow.h"

const GeoLayout weakgrate_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, weakgrate_Cube_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, weakgrate_Cube_001_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, weakgrate_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, weakgrate_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
