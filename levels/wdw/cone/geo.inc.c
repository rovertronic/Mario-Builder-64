#include "src/game/envfx_snow.h"

const GeoLayout cone_geo[] = {
	GEO_CULLING_RADIUS(500),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 229, 100),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, cone_Cylinder_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, cone_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
