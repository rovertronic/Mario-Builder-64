#include "src/game/envfx_snow.h"

const GeoLayout dementor_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 0, 0, 0, -90, 0),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, dementor_root_mesh_layer_1),
			GEO_OPEN_NODE(),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 93, 0, 0, 0, -23),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, dementor_head_mesh_layer_1),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, dementor_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
