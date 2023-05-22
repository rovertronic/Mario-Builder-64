#include "src/game/envfx_snow.h"

const GeoLayout denormO_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 0, 0, 4, 0, 0),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, denormO_root_mesh_layer_1),
			GEO_OPEN_NODE(),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 107, 1, 113, 0, 0),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, denormO_arm_mesh_layer_1),
				GEO_CLOSE_NODE(),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 122, 0, -4, 0, 0),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, denormO_head_mesh_layer_1),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, denormO_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
