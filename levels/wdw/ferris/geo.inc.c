#include "src/game/envfx_snow.h"

const GeoLayout ferris_geo[] = {
	GEO_CULLING_RADIUS(9000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, ferris_Cylinder_002_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, ferris_Cylinder_002_mesh_layer_6),
		GEO_DISPLAY_LIST(LAYER_ALPHA, ferris_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, ferris_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
