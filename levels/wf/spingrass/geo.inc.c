#include "src/game/envfx_snow.h"

const GeoLayout spingrass_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(1, 0, 0, 0, spingrass_spingrass_mesh),
		GEO_DISPLAY_LIST(0, spingrass_material_revert_render_settings),
		GEO_DISPLAY_LIST(1, spingrass_material_revert_render_settings),
		GEO_DISPLAY_LIST(2, spingrass_material_revert_render_settings),
		GEO_DISPLAY_LIST(3, spingrass_material_revert_render_settings),
		GEO_DISPLAY_LIST(4, spingrass_material_revert_render_settings),
		GEO_DISPLAY_LIST(5, spingrass_material_revert_render_settings),
		GEO_DISPLAY_LIST(6, spingrass_material_revert_render_settings),
		GEO_DISPLAY_LIST(7, spingrass_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
