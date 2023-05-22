#include "src/game/envfx_snow.h"
#include "actors/group0.h"

const GeoLayout bob_area_1_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, 0, 1917, 0, bob_dl_a1_lev_geo_col_mesh),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_FORCE, 0, 1917, 0, bob_dl_aSky_mesh_layer_0),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, 0, 1917, 0, bob_dl_non_solid_mesh),
		GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_OPAQUE, -2849, 5323, -3093, 97, 79, 0, bob_dl_Rope_mesh),
		GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_OPAQUE, -5322, 4410, 3139, 78, 9, 180, bob_dl_Rope_001_mesh),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_ALPHA, 5682, 3385, -287, bob_dl_Zgrate_mesh),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout bob_area_1[] = {
	GEO_NODE_SCREEN_AREA(10, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
	GEO_OPEN_NODE(),
		GEO_ZBUFFER(1),
		GEO_OPEN_NODE(),
		GEO_CAMERA_FRUSTUM_WITH_FUNC(45.0000, 100, 30000, geo_camera_fov),
			GEO_OPEN_NODE(),
				GEO_CAMERA(CAMERA_MODE_8_DIRECTIONS, 0, 0, 0, 0, -100, 0, geo_camera_main),
				GEO_OPEN_NODE(),
					GEO_BRANCH(1, bob_area_1_geo),
					GEO_RENDER_OBJ(),
					GEO_ASM(ENVFX_SNOW_NORMAL, geo_envfx_main),
					GEO_ASM(0, geo_moon_move),
					GEO_TRANSLATE_NODE_WITH_DL(LAYER_FORCE, 0, 0, 0, executive__circle_mesh),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_FORCE, bob_dl_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bob_dl_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, bob_dl_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
