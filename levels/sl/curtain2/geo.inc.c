#include "src/game/envfx_snow.h"

const GeoLayout curtain2_geo[] = {
	GEO_CULLING_RADIUS(10000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, curtain2_Cube_008_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, curtain2_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
