#include "src/game/envfx_snow.h"

const GeoLayout Evilship_geo[] = {
	GEO_CULLING_RADIUS(20000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, Evilship_Cube_004_mesh),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, Evilship_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
