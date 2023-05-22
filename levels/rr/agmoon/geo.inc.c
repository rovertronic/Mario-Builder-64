#include "src/game/envfx_snow.h"

const GeoLayout agmoon_geo[] = {
	GEO_CULLING_RADIUS(300),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, agmoon_Sphere_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, agmoon_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
