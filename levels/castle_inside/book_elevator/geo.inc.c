#include "src/game/envfx_snow.h"

const GeoLayout book_elevator_geo[] = {
	GEO_CULLING_RADIUS(5000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, book_elevator_Cube_016_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, book_elevator_Cube_016_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, book_elevator_Cube_016_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, book_elevator_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, book_elevator_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, book_elevator_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
