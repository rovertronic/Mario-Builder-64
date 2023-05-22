#include "src/game/envfx_snow.h"

const GeoLayout target_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, target_Cube_002_mesh),
		GEO_DISPLAY_LIST(LAYER_ALPHA, target_Cube_002_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, target_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, target_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
