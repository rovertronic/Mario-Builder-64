#include "src/game/envfx_snow.h"

const GeoLayout agcrumble_geo[] = {
	GEO_CULLING_RADIUS(2000),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 229, 300),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, agcrumble_Cube_011_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, agcrumble_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
