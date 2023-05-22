#include "src/game/envfx_snow.h"

const GeoLayout cosmic_missile_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 255, 300),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, cosmic_missile_Cylinder_023_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, cosmic_missile_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
