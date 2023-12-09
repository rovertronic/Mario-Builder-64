#include "src/game/envfx_snow.h"

const GeoLayout boo_geo[] = {
   GEO_CULLING_RADIUS(80),
	GEO_OPEN_NODE(),
		GEO_SHADOW(0, 150, 70),
		GEO_OPEN_NODE(),
			GEO_ASM(0, geo_update_layer_transparency),
			GEO_SWITCH_CASE(2, geo_switch_anim_state),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, boo_body_mesh_layer_1),
				GEO_DISPLAY_LIST(LAYER_TRANSPARENT, boo_body_mesh_layer_1),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
