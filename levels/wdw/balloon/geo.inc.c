#include "src/game/envfx_snow.h"

const GeoLayout balloon_geo[] = {
	GEO_CULLING_RADIUS(400),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, balloon_Plane_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, balloon_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
