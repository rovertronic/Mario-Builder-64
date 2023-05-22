#include "src/game/envfx_snow.h"

const GeoLayout wallet_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(1, wallet_Sphere_mesh_layer_1),
		GEO_DISPLAY_LIST(1, wallet_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
