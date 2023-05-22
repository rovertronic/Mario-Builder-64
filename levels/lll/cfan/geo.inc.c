#include "src/game/envfx_snow.h"

const GeoLayout cfan_geo[] = {
	GEO_CULLING_RADIUS(3000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, cfan_Cylinder_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, cfan_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
