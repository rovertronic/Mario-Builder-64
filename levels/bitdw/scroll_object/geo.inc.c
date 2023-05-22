#include "src/game/envfx_snow.h"

const GeoLayout scroll_object_geo[] = {
	GEO_CULLING_RADIUS(30000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, scroll_object_Plane_003_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, scroll_object_Plane_003_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, scroll_object_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, scroll_object_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
