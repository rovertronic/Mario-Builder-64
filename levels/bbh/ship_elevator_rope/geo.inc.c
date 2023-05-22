#include "src/game/envfx_snow.h"

const GeoLayout ship_elevator_rope_geo[] = {
	GEO_CULLING_RADIUS(3000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, ship_elevator_rope_StretchRopes_mesh),
		GEO_DISPLAY_LIST(LAYER_ALPHA, ship_elevator_rope_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
