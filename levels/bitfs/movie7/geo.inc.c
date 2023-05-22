#include "src/game/envfx_snow.h"

const GeoLayout movie7_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, movie7_Plane_007_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, movie7_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
