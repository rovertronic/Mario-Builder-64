#include "src/game/envfx_snow.h"

const GeoLayout mirror_shard_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, mirror_shard_Plane_001_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, mirror_shard_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
