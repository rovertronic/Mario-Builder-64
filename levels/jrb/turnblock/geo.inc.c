#include "src/game/envfx_snow.h"

const GeoLayout turnblock_geo[] = {
	GEO_CULLING_RADIUS(400),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(1, turnblock_Cube_002_mesh_layer_1),
		GEO_DISPLAY_LIST(1, turnblock_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
