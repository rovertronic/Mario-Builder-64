#include "src/game/envfx_snow.h"

const GeoLayout spiketube_geo[] = {
	GEO_CULLING_RADIUS(2000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, spiketube_Torus_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, spiketube_Torus_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, spiketube_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, spiketube_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
