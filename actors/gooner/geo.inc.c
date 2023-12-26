#include "src/game/envfx_snow.h"

const GeoLayout gooner_geo[] = {
	GEO_CULLING_RADIUS(500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, gooner_gooner_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, gooner_gooner_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, gooner_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, gooner_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
