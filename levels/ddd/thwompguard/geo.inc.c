#include "src/game/envfx_snow.h"

const GeoLayout thwompguard_geo[] = {
	GEO_CULLING_RADIUS(300),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, thwompguard_Cube_004_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, thwompguard_Cube_004_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, thwompguard_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, thwompguard_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
