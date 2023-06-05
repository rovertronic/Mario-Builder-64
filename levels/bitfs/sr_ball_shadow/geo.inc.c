#include "src/game/envfx_snow.h"

const GeoLayout sr_ball_shadow_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 255, 100),
		GEO_OPEN_NODE(),
			GEO_ASM(0, geo_update_layer_transparency),
			GEO_DISPLAY_LIST(LAYER_TRANSPARENT, sr_ball_shadow_Plane_009_mesh_layer_5),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, sr_ball_shadow_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
