#include "src/game/envfx_snow.h"

const GeoLayout movie8_geo[] = {
	GEO_CULLING_RADIUS(20000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, movie8_Cube_007_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, movie8_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
