#include "src/game/envfx_snow.h"

const GeoLayout tutorialgate_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_ASM(0, geo_update_layer_transparency),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, tutorialgate_tgate_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, tutorialgate_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
