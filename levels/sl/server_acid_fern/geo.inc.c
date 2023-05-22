#include "src/game/envfx_snow.h"

const GeoLayout server_acid_fern_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, server_acid_fern_Server_Acid_Fern_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, server_acid_fern_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
