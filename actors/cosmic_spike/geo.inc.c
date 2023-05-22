#include "src/game/envfx_snow.h"

const GeoLayout cosmic_spike_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 255, 100),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, cosmic_spike_Cube_009_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, cosmic_spike_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
