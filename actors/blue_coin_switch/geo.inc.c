#include "src/game/envfx_snow.h"

const GeoLayout blue_coin_switch_geo[] = {
   GEO_CULLING_RADIUS(30),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, blue_coin_switch_Blue_coin_switch_model_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, blue_coin_switch_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
