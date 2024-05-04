#include "src/game/envfx_snow.h"

const GeoLayout conveyor_geo[] = {
	GEO_CULLING_RADIUS(500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, conveyor_blaster_007_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, conveyor_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
