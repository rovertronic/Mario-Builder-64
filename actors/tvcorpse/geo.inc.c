#include "src/game/envfx_snow.h"

const GeoLayout tvcorpse_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, tvcorpse_TV_003_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, tvcorpse_TV_003_mesh_layer_6),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, tvcorpse_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, tvcorpse_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
