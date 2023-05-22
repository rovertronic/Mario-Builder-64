#include "src/game/envfx_snow.h"

const GeoLayout curtaincall_geo[] = {
	GEO_CULLING_RADIUS(2000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, curtaincall_Cube_007_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, curtaincall_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
