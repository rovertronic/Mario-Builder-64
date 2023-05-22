#include "src/game/envfx_snow.h"

const GeoLayout chainpole_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, chainpole_Chain_036_mesh),
		GEO_DISPLAY_LIST(LAYER_ALPHA, chainpole_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
