#include "src/game/envfx_snow.h"

const GeoLayout pipe2_ccm_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, pipe2_ccm_Pipe_004_mesh),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, pipe2_ccm_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
