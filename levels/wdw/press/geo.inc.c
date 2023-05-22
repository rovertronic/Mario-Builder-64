#include "src/game/envfx_snow.h"

const GeoLayout press_geo[] = {
	GEO_CULLING_RADIUS(400),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, press_Cube_012_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, press_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
