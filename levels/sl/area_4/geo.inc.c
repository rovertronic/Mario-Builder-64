#include "src/game/envfx_snow.h"

const GeoLayout sl_area_4_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, sl_dl_Cube_003_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, sl_dl_Cube_005_mesh_layer_4),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout sl_area_4[] = {
	GEO_NODE_SCREEN_AREA(10, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
	GEO_OPEN_NODE(),
		GEO_ZBUFFER(1),
		GEO_OPEN_NODE(),
			GEO_CAMERA_FRUSTUM_WITH_FUNC(45.0000, 100, 30000, geo_camera_fov),
			GEO_OPEN_NODE(),
				GEO_CAMERA(CAMERA_MODE_8_DIRECTIONS, 18659, 213, 11016, 18659, 113, 11016, geo_camera_main),
				GEO_OPEN_NODE(),
					GEO_BRANCH(1, sl_area_4_geo),
					GEO_RENDER_OBJ(),
					GEO_ASM(ENVFX_MODE_NONE, geo_envfx_main),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, sl_dl_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, sl_dl_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
