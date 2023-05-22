#include "src/game/envfx_snow.h"

const GeoLayout stopsign_geo[] = {
	GEO_CULLING_RADIUS(200),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, stopsign_Cube_008_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, stopsign_Cube_008_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, stopsign_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, stopsign_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
