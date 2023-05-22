#include "src/game/envfx_snow.h"

const GeoLayout reflection_change_geo[] = {
	GEO_CULLING_RADIUS(20000),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE_WITH_DL(1, 0, 0, 0, 0, 0, 0, reflection_change_MirrorObject_mesh),
		GEO_DISPLAY_LIST(1, reflection_change_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
