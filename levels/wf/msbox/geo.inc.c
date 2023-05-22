#include "src/game/envfx_snow.h"

const GeoLayout msbox_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, msbox_Cube_003_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, msbox_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
