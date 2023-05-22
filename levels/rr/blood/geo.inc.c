#include "src/game/envfx_snow.h"

const GeoLayout blood_geo[] = {
	GEO_CULLING_RADIUS(32000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, blood_vis_col_001_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, blood_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
