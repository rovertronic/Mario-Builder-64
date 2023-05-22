#include "src/game/envfx_snow.h"

const GeoLayout horse_cart_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, horse_cart_carriage_mesh),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, horse_cart_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
