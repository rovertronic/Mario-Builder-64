#include "src/game/envfx_snow.h"

const GeoLayout fucking_mirror_geo[] = {
	GEO_CULLING_RADIUS(20000),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE_WITH_DL(5, 0, 0, 0, 0, 0, 0, fucking_mirror_ActualMirror_mesh),
		GEO_DISPLAY_LIST(5, fucking_mirror_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
