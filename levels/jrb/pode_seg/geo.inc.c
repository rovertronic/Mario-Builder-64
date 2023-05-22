#include "src/game/envfx_snow.h"

const GeoLayout pode_seg_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 153, 800),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, pode_seg_dl_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, pode_seg_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
