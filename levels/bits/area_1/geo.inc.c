#include "src/game/envfx_snow.h"

const GeoLayout bits_area_1_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bits_dl_Plane_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bits_dl_rgb_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout bits_area_1[] = {
	GEO_NODE_SCREEN_AREA(10, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
	GEO_OPEN_NODE(),
		GEO_ZBUFFER(1),
		GEO_OPEN_NODE(),
			GEO_CAMERA_FRUSTUM_WITH_FUNC(45.0000, 100, 30000, geo_camera_fov),
			GEO_OPEN_NODE(),
				GEO_CAMERA(CAMERA_MODE_8_DIRECTIONS, 0, 0, 0, 0, -100, 0, geo_camera_main),
				GEO_OPEN_NODE(),
					GEO_BRANCH(1, bits_area_1_geo),
					GEO_RENDER_OBJ(),
					GEO_ASM(0, geo_backdrop_move),
					GEO_TRANSLATE_NODE_WITH_DL(LAYER_FORCE, 0, 0, 0, spacebox_Skybox_mesh),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bits_dl_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bits_dl_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
