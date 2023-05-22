#include "src/game/envfx_snow.h"

const GeoLayout egg_geo[] = {
	GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xB4, 50),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, egg_Egg_mesh),
		GEO_DISPLAY_LIST(LAYER_ALPHA, egg_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
