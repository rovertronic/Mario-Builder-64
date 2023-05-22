#include "src/game/envfx_snow.h"

const GeoLayout rr_tube_geo[] = {
	GEO_CULLING_RADIUS(32000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, rr_tube_Tube_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, rr_tube_Tube_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, rr_tube_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, rr_tube_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
