#include "src/game/envfx_snow.h"

const GeoLayout trap_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, -17, 0, trap_root_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, trap_root_mesh_layer_4),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 34, 175, -81, 0, 0),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, trap_hammer_mesh_layer_4),
			GEO_CLOSE_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, trap_snap_skinned_mesh_layer_4),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 64, 0, 97, 0, 0),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, trap_snap_mesh_layer_4),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, trap_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, trap_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
