#include "src/game/envfx_snow.h"

const GeoLayout ring_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE_WITH_DL(1, 0, 0, 0, 0, 0, 0, ring_Ring_mesh),
		GEO_DISPLAY_LIST(0, ring_material_revert_render_settings),
		GEO_DISPLAY_LIST(1, ring_material_revert_render_settings),
		GEO_DISPLAY_LIST(2, ring_material_revert_render_settings),
		GEO_DISPLAY_LIST(3, ring_material_revert_render_settings),
		GEO_DISPLAY_LIST(4, ring_material_revert_render_settings),
		GEO_DISPLAY_LIST(5, ring_material_revert_render_settings),
		GEO_DISPLAY_LIST(6, ring_material_revert_render_settings),
		GEO_DISPLAY_LIST(7, ring_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
