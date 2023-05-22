#include "src/game/envfx_snow.h"

const GeoLayout saw_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, saw_Plane_001_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, saw_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
