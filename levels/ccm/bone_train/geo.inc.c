#include "src/game/envfx_snow.h"

const GeoLayout bone_train_geo[] = {
	GEO_CULLING_RADIUS(3000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bone_train_TrainCol_001_mesh),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bone_train_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
