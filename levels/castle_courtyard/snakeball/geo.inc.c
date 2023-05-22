#include "src/game/envfx_snow.h"

const GeoLayout snakeball_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 229, 100),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, snakeball_Plane_001_mesh_layer_4),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, snakeball_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
