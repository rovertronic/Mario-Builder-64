#include "src/game/envfx_snow.h"

const GeoLayout thi_area_2_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, thi_dl_both_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, thi_dl_Cube_012_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, thi_dl_Cube_013_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout thi_area_2[] = {
	GEO_NODE_SCREEN_AREA(10, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
	GEO_OPEN_NODE(),
		GEO_ZBUFFER(1),
		GEO_OPEN_NODE(),
			GEO_CAMERA_FRUSTUM_WITH_FUNC(45.0000, 100, 30000, geo_camera_fov),
			GEO_OPEN_NODE(),
				GEO_CAMERA(CAMERA_MODE_8_DIRECTIONS, 27215, -2525, 4007, 27215, -2625, 4007, geo_camera_main),
				GEO_OPEN_NODE(),
					GEO_BRANCH(1, thi_area_2_geo),
					GEO_RENDER_OBJ(),
					GEO_ASM(ENVFX_MODE_NONE, geo_envfx_main),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, thi_dl_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
