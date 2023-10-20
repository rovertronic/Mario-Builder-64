#include "src/game/envfx_snow.h"

const GeoLayout spawn_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, spawn_root_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_BILLBOARD_WITH_PARAMS(LAYER_OPAQUE, 0, 128, 0),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 7, 0, spawn_m_mesh_layer_5),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, spawn_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, spawn_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
