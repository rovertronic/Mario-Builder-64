#include "src/game/envfx_snow.h"

const GeoLayout flip_geo[] = {
	GEO_CULLING_RADIUS(400),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, flip_Cube_003_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, flip_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
