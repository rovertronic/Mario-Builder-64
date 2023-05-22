#include "src/game/envfx_snow.h"

const GeoLayout thi_cage_geo[] = {
	GEO_CULLING_RADIUS(200),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, thi_cage_Cylinder_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, thi_cage_Cylinder_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, thi_cage_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, thi_cage_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
