#include "src/game/envfx_snow.h"

const GeoLayout tvshop_geo[] = {
	GEO_CULLING_RADIUS(300),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, tvshop_Cube_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, tvshop_Cube_002_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, tvshop_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, tvshop_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
