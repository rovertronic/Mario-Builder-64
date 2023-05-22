#include "src/game/envfx_snow.h"

const GeoLayout movie_9_geo[] = {
	GEO_CULLING_RADIUS(30000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, movie_9_Cube_018_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, movie_9_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
