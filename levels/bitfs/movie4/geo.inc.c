#include "src/game/envfx_snow.h"

const GeoLayout movie4_geo[] = {
	GEO_CULLING_RADIUS(10000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, movie4_Cube_007_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, movie4_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
