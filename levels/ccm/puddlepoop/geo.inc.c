#include "src/game/envfx_snow.h"

const GeoLayout puddlepoop_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, puddlepoop_Plane_008_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, puddlepoop_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
