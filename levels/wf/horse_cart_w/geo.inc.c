#include "src/game/envfx_snow.h"

const GeoLayout horse_cart_w_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, horse_cart_w_Cylinder_002_mesh),
		GEO_DISPLAY_LIST(LAYER_ALPHA, horse_cart_w_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
