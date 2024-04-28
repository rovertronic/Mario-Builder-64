#include "src/game/envfx_snow.h"

const GeoLayout rfbox_geo[] = {
	GEO_CULLING_RADIUS(300),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, rfbox_blaster_004_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, rfbox_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
