#include "src/game/envfx_snow.h"

const GeoLayout spotlight_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, spotlight_Cylinder_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, spotlight_Cylinder_002_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, spotlight_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, spotlight_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
