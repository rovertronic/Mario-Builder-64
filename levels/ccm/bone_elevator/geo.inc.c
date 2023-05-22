#include "src/game/envfx_snow.h"

const GeoLayout bone_elevator_geo[] = {
	GEO_CULLING_RADIUS(3000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bone_elevator_oonginggang_mesh),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bone_elevator_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
