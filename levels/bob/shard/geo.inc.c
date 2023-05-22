#include "src/game/envfx_snow.h"

const GeoLayout shard_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xC8, 70),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(1, shard_Cone_mesh_layer_1),
			GEO_DISPLAY_LIST(1, shard_material_revert_render_settings),
		GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_END(),
};
