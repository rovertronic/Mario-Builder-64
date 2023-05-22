#include "src/game/envfx_snow.h"

const GeoLayout agwall_geo[] = {
	GEO_CULLING_RADIUS(10000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, agwall_Cylinder_007_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, agwall_Cylinder_007_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, agwall_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, agwall_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
