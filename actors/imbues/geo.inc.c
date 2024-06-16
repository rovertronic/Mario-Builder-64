#include "src/game/envfx_snow.h"

const GeoLayout imbues_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_INTER, imbues_imbue_star_mesh_layer_7),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_INTER, imbues_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
