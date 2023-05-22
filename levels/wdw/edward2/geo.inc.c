#include "src/game/envfx_snow.h"

const GeoLayout edward2_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 229, 200),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_TRANSPARENT, edward2_root_mesh_layer_5),
			GEO_BILLBOARD_WITH_PARAMS_AND_DL(LAYER_ALPHA, 0, 0, 0, edward2_bill_mesh_layer_4),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, edward2_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, edward2_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
