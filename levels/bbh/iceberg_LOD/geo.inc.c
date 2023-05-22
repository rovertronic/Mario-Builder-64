#include "src/game/envfx_snow.h"

const GeoLayout iceberg_LOD_geo[] = {
	GEO_CULLING_RADIUS(3000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, iceberg_LOD_LoPolyIceberg_mesh),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, iceberg_LOD_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
