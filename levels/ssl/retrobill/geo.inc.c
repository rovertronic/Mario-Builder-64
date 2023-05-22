#include "src/game/envfx_snow.h"

const GeoLayout retrobill_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, retrobill_Plane_002_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, retrobill_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
