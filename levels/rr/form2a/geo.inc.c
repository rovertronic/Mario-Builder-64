#include "src/game/envfx_snow.h"

const GeoLayout form2a_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 255, 300),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, form2a_Cylinder_025_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, form2a_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
