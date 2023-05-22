#include "src/game/envfx_snow.h"

const GeoLayout snakeblock1_Smaller[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_OPAQUE, 0, 9, 0, 0, 0, 0, snakeblock1_switch_option_Block3_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout snakeblock1_Armature[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_OPAQUE, 0, 9, 0, 0, 0, 0, snakeblock1_switch_option_Block2_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout snakeblock1_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(4, geo_switch_anim_state),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_OPAQUE, 0, 100, 0, 0, 0, 0, snakeblock1_Block_mesh_layer_1),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, snakeblock1_Smaller),
			GEO_BRANCH(1, snakeblock1_Armature),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, snakeblock1_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
