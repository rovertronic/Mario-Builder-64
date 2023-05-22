#include "src/game/envfx_snow.h"

const GeoLayout rbowser_Material_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, rbowser_Bowser_mesh_layer_4_mat_override_bowser_hop_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout rbowser_Material_opt2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, rbowser_Bowser_mesh_layer_4_mat_override_bowser_blow_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout rbowser_Material_opt3[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, rbowser_Bowser_mesh_layer_4_mat_override_bowser_jump_2),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout rbowser_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(4, geo_switch_anim_state),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_ALPHA, rbowser_Bowser_mesh_layer_4),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, rbowser_Material_opt1),
			GEO_BRANCH(1, rbowser_Material_opt2),
			GEO_BRANCH(1, rbowser_Material_opt3),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, rbowser_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
