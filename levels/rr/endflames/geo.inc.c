#include "src/game/envfx_snow.h"

const GeoLayout endflames_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, endflames_Cylinder_011_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, endflames_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
