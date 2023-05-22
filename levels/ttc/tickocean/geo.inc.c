#include "src/game/envfx_snow.h"

const GeoLayout tickocean_geo[] = {
	GEO_CULLING_RADIUS(32000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, tickocean_mesh_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, tickocean_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
