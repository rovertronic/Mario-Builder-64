#include "src/game/envfx_snow.h"

const GeoLayout bonespin2_geo[] = {
	GEO_CULLING_RADIUS(1200),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bonespin2_Cone_mesh),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bonespin2_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
