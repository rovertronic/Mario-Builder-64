#include "src/game/envfx_snow.h"

const GeoLayout agring_geo[] = {
	GEO_CULLING_RADIUS(32000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, agring_audience_ring_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, agring_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
