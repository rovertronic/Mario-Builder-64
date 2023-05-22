#include "src/game/envfx_snow.h"

const GeoLayout geo_GhostBoard[] = {
	GEO_CULLING_RADIUS(800),
	GEO_OPEN_NODE(),
		GEO_ASM(10, geo_update_layer_transparency),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, GhostBoard_GhostBoard_mesh),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, GhostBoard_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
