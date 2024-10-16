#include "src/game/envfx_snow.h"

const GeoLayout imbue_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(0, geo_imbue_marker_color),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_INTER, imbue_imbue_excla_mesh_layer_7),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
