#include "src/game/envfx_snow.h"

const GeoLayout bits_stairs_geo[] = {
	GEO_CULLING_RADIUS(3000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bits_stairs_Cube_018_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bits_stairs_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
