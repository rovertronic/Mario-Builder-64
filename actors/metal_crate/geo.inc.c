#include "src/game/envfx_snow.h"

const GeoLayout metal_crate_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, metal_crate_Cube_mesh),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, metal_crate_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
