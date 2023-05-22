#include "src/game/envfx_snow.h"

const GeoLayout cursedmirror_geo[] = {
	GEO_CULLING_RADIUS(8000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, cursedmirror_mirrorlayers_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, cursedmirror_mirrorlayers_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, cursedmirror_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, cursedmirror_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
