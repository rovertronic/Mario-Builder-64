#include "src/game/envfx_snow.h"

const GeoLayout sr_spike_geo[] = {
	GEO_CULLING_RADIUS(200),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, sr_spike_Cone_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, sr_spike_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
