#include "src/game/envfx_snow.h"

const GeoLayout streetlight_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, streetlight_Cube_009_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, streetlight_Cube_009_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, streetlight_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, streetlight_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
