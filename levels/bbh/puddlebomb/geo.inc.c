#include "src/game/envfx_snow.h"

const GeoLayout puddlebomb_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xC8, 70),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, puddlebomb_Cone_001_mesh),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, puddlebomb_material_revert_render_settings),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
