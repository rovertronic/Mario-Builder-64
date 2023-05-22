#include "src/game/envfx_snow.h"

const GeoLayout conv2ccm_geo[] = {
	GEO_CULLING_RADIUS(20000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, conv2ccm_Circle_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, conv2ccm_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
