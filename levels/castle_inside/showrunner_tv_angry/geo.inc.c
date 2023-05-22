#include "src/game/envfx_snow.h"

const GeoLayout showrunner_tv_angry_geo[] = {
	GEO_CULLING_RADIUS(500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, showrunner_tv_angry_visual_003_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, showrunner_tv_angry_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
