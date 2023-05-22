#include "src/game/envfx_snow.h"

const GeoLayout movie_2_geo[] = {
	GEO_CULLING_RADIUS(10000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, movie_2_Cube_014_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, movie_2_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
