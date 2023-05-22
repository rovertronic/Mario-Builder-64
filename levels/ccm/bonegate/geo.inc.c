#include "src/game/envfx_snow.h"

const GeoLayout bonegate_geo[] = {
	GEO_CULLING_RADIUS(5000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, bonegate_Cube_006_mesh),
		GEO_DISPLAY_LIST(LAYER_ALPHA, bonegate_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
