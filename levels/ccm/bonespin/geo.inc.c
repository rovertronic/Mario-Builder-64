#include "src/game/envfx_snow.h"

const GeoLayout bonespin_geo[] = {
	GEO_CULLING_RADIUS(2000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bonespin_Cube_003_mesh),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bonespin_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
