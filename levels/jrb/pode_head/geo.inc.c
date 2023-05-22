#include "src/game/envfx_snow.h"

const GeoLayout pode_head_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 153, 1000),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, pode_head_dl2_mesh_layer_1),
			GEO_DISPLAY_LIST(LAYER_ALPHA, pode_head_dl2_mesh_layer_4),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, pode_head_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, pode_head_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
