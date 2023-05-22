#include "src/game/envfx_snow.h"

const GeoLayout ship_elevator_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, ship_elevator_Cube_006_mesh),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, ship_elevator_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
