#include "src/game/envfx_snow.h"

const GeoLayout fountain2_geo[] = {
	GEO_CULLING_RADIUS(1800),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, fountain2_Cylinder_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, fountain2_Cylinder_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, fountain2_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, fountain2_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
