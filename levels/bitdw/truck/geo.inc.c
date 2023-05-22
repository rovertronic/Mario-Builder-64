#include "src/game/envfx_snow.h"

const GeoLayout truck_geo[] = {
	GEO_CULLING_RADIUS(4000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(1, truck_Cube_033_mesh_layer_1),
		GEO_DISPLAY_LIST(4, truck_Cube_033_mesh_layer_4),
		GEO_DISPLAY_LIST(4, truck_material_revert_render_settings),
		GEO_DISPLAY_LIST(1, truck_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
