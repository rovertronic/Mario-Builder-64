#include "src/game/envfx_snow.h"

const GeoLayout ag_killer_laser_geo[] = {
	GEO_CULLING_RADIUS(30000),
	GEO_OPEN_NODE(),
		GEO_ASM(0, geo_update_layer_transparency),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, ag_killer_laser_laser_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, ag_killer_laser_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
