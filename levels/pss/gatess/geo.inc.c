#include "src/game/envfx_snow.h"

const GeoLayout gatess_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(4, gatess_SketchUp_001_mesh_layer_4),
		GEO_DISPLAY_LIST(4, gatess_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
