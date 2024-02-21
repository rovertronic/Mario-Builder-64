#include "src/game/envfx_snow.h"

const GeoLayout timedbox_geo[] = {
	GEO_CULLING_RADIUS(300),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, timedbox_hollowbox_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, timedbox_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
