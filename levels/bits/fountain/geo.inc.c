#include "src/game/envfx_snow.h"

const GeoLayout fountain_geo[] = {
	GEO_CULLING_RADIUS(1800),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, fountain_Cylinder_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, fountain_Cylinder_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, fountain_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, fountain_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
