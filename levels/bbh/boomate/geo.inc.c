#include "src/game/envfx_snow.h"

const GeoLayout geo_boomate[] = {
	GEO_CULLING_RADIUS(200),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, boomate_boo_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, boomate_boo_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, boomate_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, boomate_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
