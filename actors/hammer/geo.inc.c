#include "src/game/envfx_snow.h"

const GeoLayout hammer_geo[] = {
	GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xB4, 70),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(1, 0, 0, 0, hammer_Cylinder_mesh),
		GEO_DISPLAY_LIST(0, hammer_material_revert_render_settings),
		GEO_DISPLAY_LIST(1, hammer_material_revert_render_settings),
		GEO_DISPLAY_LIST(2, hammer_material_revert_render_settings),
		GEO_DISPLAY_LIST(3, hammer_material_revert_render_settings),
		GEO_DISPLAY_LIST(4, hammer_material_revert_render_settings),
		GEO_DISPLAY_LIST(5, hammer_material_revert_render_settings),
		GEO_DISPLAY_LIST(6, hammer_material_revert_render_settings),
		GEO_DISPLAY_LIST(7, hammer_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
