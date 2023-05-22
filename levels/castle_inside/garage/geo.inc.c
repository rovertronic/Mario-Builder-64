#include "src/game/envfx_snow.h"

const GeoLayout garage_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(1, garage_Cube_011_mesh_layer_1),
		GEO_DISPLAY_LIST(4, garage_Cube_011_mesh_layer_4),
		GEO_DISPLAY_LIST(1, garage_material_revert_render_settings),
		GEO_DISPLAY_LIST(4, garage_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
