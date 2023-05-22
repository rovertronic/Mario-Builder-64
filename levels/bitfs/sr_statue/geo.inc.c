#include "src/game/envfx_snow.h"

const GeoLayout sr_statue_geo[] = {
	GEO_CULLING_RADIUS(10000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, sr_statue_ShowrunnerStatue_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, sr_statue_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
