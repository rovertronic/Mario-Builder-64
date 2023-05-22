#include "src/game/envfx_snow.h"

const GeoLayout shock_geo[] = {
	GEO_CULLING_RADIUS(5000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(5, shock_Plane_mesh_layer_5),
		GEO_DISPLAY_LIST(5, shock_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
