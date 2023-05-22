#include "src/game/envfx_snow.h"

const GeoLayout movie6_geo[] = {
	GEO_CULLING_RADIUS(10000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, movie6_Cube_010_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, movie6_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
