#include "src/game/envfx_snow.h"

const GeoLayout blaster_geo[] = {
	GEO_CULLING_RADIUS(300),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, blaster_blaster_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, blaster_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
