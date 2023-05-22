#include "src/game/envfx_snow.h"

const GeoLayout woogly_geo[] = {
	GEO_CULLING_RADIUS(2000),
	GEO_OPEN_NODE(),
		GEO_OPEN_NODE(),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 0, 0, -90, 0, -179),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, woogly_root_mesh_layer_1),
				GEO_OPEN_NODE(),
					GEO_DISPLAY_LIST(LAYER_OPAQUE, woogly_a1_skinned_mesh_layer_1),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 300, 0, woogly_a1_mesh_layer_1),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_OPAQUE, woogly_a2_skinned_mesh_layer_1),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 300, 0, woogly_a2_mesh_layer_1),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, woogly_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
