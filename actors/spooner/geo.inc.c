#include "src/game/envfx_snow.h"

const GeoLayout spooner_geo[] = {
	GEO_CULLING_RADIUS(500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, spooner_FireSpinner_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, spooner_FireSpinner_mesh_layer_4),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
