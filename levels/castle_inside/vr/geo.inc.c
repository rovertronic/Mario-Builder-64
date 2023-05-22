#include "src/game/envfx_snow.h"

const GeoLayout vr_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, vr_4droom_mesh),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, vr_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
