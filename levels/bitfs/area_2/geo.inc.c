#include "src/game/envfx_snow.h"
#include "actors/group0.h"

const GeoLayout bitfs_area_2_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, 0, 740, 0, bitfs_dl_Cube_015_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bitfs_dl_Cylinder_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, bitfs_dl_Cylinder_mesh_layer_4),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout bitfs_area_2[] = {
	GEO_NODE_SCREEN_AREA(10, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
	GEO_OPEN_NODE(),
		GEO_ZBUFFER(1),
		GEO_OPEN_NODE(),
			GEO_CAMERA_FRUSTUM_WITH_FUNC(45.0000, 100, 30000, geo_camera_fov),
			GEO_OPEN_NODE(),
				GEO_CAMERA(CAMERA_MODE_8_DIRECTIONS, -30001, 0, 0, -30001, -100, 0, geo_camera_main),
				GEO_OPEN_NODE(),
					GEO_BRANCH(1, bitfs_area_2_geo),
					GEO_RENDER_OBJ(),
					GEO_ASM(ENVFX_MODE_NONE, geo_envfx_main),

					GEO_ASM(0, geo_moon_move),
					GEO_TRANSLATE_NODE_WITH_DL(LAYER_FORCE, 0, 0, 0, sr_fight_sky_sky_mesh),
					GEO_ASM(0, geo_moon_move),
					GEO_TRANSLATE_NODE_WITH_DL(LAYER_FORCE, 0, 0, 0, executive_loom__circle_mesh),

				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bitfs_dl_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, bitfs_dl_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
