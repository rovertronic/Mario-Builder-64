#include "src/game/envfx_snow.h"

const GeoLayout alientree_geo[] = {
	GEO_CULLING_RADIUS(200),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, alientree_root_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, alientree_root2_skinned_mesh_layer_1),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 130, 0, alientree_root2_mesh_layer_1),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, alientree_root3_skinned_mesh_layer_1),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 114, 0, alientree_root3_mesh_layer_1),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, alientree_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
