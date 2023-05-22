#include "src/game/envfx_snow.h"

const GeoLayout raft_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, raft_Cube_003_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, raft_Cube_003_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, raft_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, raft_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
