#include "src/game/envfx_snow.h"

const GeoLayout highcane_geo[] = {
	GEO_CULLING_RADIUS(200),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, highcane_highcane_geo_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, highcane_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
