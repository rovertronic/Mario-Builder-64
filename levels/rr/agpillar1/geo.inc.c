#include "src/game/envfx_snow.h"

const GeoLayout agpillar1_geo[] = {
	GEO_CULLING_RADIUS(32000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, agpillar1_Cylinder_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, agpillar1_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
