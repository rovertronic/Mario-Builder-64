#include "src/game/envfx_snow.h"

const GeoLayout bowling_ball_track_geo[] = {
	GEO_CULLING_RADIUS(130),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, bowling_ball_Bowling_ball_geolayout_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, bowling_ball_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

const GeoLayout bowling_ball_geo[] = {
	GEO_CULLING_RADIUS(130),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 200, 280),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, bowling_ball_Bowling_ball_geolayout_mesh_layer_4),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, bowling_ball_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
