#include "src/game/envfx_snow.h"

const GeoLayout agboom_geo[] = {
	GEO_CULLING_RADIUS(30000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, agboom_agboom_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, agboom_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
