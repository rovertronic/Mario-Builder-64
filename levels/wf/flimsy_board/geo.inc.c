#include "src/game/envfx_snow.h"

const GeoLayout flimboard_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, flimsy_board_Cube_001_mesh),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, flimsy_board_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
