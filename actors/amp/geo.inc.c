#include "src/game/envfx_snow.h"

const GeoLayout amp_eletricity_geolayout[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, amp_switch_option_eletricity_mesh_layer_4),
		GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, amp_switch_option_eletricity_001_mesh_layer_4),
		GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, amp_switch_option_eletricity_002_mesh_layer_4),
		GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, amp_switch_option_eletricity_003_mesh_layer_4),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};

const GeoLayout dAmpGeo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(0, 200, 100),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, amp_root_mesh_layer_4),
			GEO_BILLBOARD_WITH_PARAMS_AND_DL(LAYER_ALPHA, 0, 0, 0, amp_billboard_mesh_layer_4),
			GEO_SWITCH_CASE(2, geo_switch_anim_state),
			GEO_OPEN_NODE(),
				GEO_NODE_START(),
				GEO_OPEN_NODE(),
					GEO_NOP_1A(),
				GEO_CLOSE_NODE(),
				GEO_BRANCH(1, amp_eletricity_geolayout),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, amp_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
