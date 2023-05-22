#include "src/game/envfx_snow.h"

const GeoLayout ghoad_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 0, 0, 0, 90, 0),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 0, 0, ghoad_root_mesh_layer_5),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 21, 0, ghoad_head_mesh_layer_5),
				GEO_DISPLAY_LIST(LAYER_TRANSPARENT, ghoad_tail_skinned_mesh_layer_5),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 10, -8, 0, 0, 0, -109),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 0, 0, ghoad_tail_mesh_layer_5),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, ghoad_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
