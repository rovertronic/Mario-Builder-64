#include "src/game/envfx_snow.h"

const GeoLayout slob_geo[] = {
	GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xC8, 100),
	GEO_OPEN_NODE(),
	GEO_ASM(1, geo_set_color_env),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, slob_root_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 89, 64, 0, 0, 0, -57),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, slob_larm_mesh_layer_1),
			GEO_CLOSE_NODE(),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, -87, 64, 0, 0, 0, 61),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, slob_rarm_mesh_layer_1),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, slob_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
