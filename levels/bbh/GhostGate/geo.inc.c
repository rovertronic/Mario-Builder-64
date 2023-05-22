#include "src/game/envfx_snow.h"

const GeoLayout GhostGate_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, GhostGate_Cube_025_mesh),
		GEO_DISPLAY_LIST(1, GhostGate_Cube_025_mesh_layer_1),
		GEO_DISPLAY_LIST(4, GhostGate_Cube_025_mesh_layer_4),
		GEO_DISPLAY_LIST(5, GhostGate_Cube_025_mesh_layer_5),
		GEO_DISPLAY_LIST(1, GhostGate_material_revert_render_settings),
		GEO_DISPLAY_LIST(5, GhostGate_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, GhostGate_material_revert_render_settings),
		GEO_DISPLAY_LIST(4, GhostGate_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
