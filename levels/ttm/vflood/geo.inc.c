#include "src/game/envfx_snow.h"

const GeoLayout vflood_geo[] = {
	GEO_CULLING_RADIUS(5000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, vflood_Cylinder_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, vflood_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
