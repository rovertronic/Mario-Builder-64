#include "src/game/envfx_snow.h"

const GeoLayout movie_1_geo[] = {
	GEO_CULLING_RADIUS(10000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, movie_1_Cube_004_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, movie_1_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
