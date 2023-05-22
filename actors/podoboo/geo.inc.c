#include "src/game/envfx_snow.h"

const GeoLayout podoboo_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(1, podoboo_Sphere_mesh_layer_1),
		GEO_DISPLAY_LIST(4, podoboo_Sphere_mesh_layer_4),
		GEO_DISPLAY_LIST(4, podoboo_material_revert_render_settings),
		GEO_DISPLAY_LIST(1, podoboo_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
