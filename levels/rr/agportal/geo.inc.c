#include "src/game/envfx_snow.h"

const GeoLayout agportal_geo[] = {
	GEO_CULLING_RADIUS(500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, agportal_Plane_002_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, agportal_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
