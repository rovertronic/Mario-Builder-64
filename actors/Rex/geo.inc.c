#include "src/game/envfx_snow.h"

const GeoLayout Rex_eye_control_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 14, -1, Rex_head_mesh_layer_1_mat_override_eyes_open_v4_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout rex_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 20, 4, Rex_body_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 12, 10, -3, NULL),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, -8, 0, Rex_foot_L_mesh_layer_1),
			GEO_CLOSE_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, -12, 10, -3, NULL),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, -8, 0, Rex_foot_R_mesh_layer_1),
			GEO_CLOSE_NODE(),
			GEO_SHADOW(1, 150, 100),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, Rex_tail_skinned_mesh_layer_1),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, -10, Rex_tail_mesh_layer_1),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, Rex_upper_body_skinned_mesh_layer_1),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 24, -2, Rex_upper_body_mesh_layer_1),
			GEO_OPEN_NODE(),
				GEO_SWITCH_CASE(2, geo_switch_anim_state),
				GEO_OPEN_NODE(),
					GEO_NODE_START(),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 14, -1, Rex_head_mesh_layer_1),
					GEO_CLOSE_NODE(),
					GEO_BRANCH(1, Rex_eye_control_opt1),
				GEO_CLOSE_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 10, 4, 2, Rex_shoulder_L_mesh_layer_1),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 7, 0, 0, Rex_arm_L_mesh_layer_1),
				GEO_CLOSE_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, -10, 4, 2, Rex_shoulder_R_mesh_layer_1),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, -7, 0, 0, Rex_arm_R_mesh_layer_1),
				GEO_CLOSE_NODE(),
				GEO_ANIMATED_PART(LAYER_ALPHA, 5, 5, -7, Rex_wing_L_mesh_layer_4),
				GEO_ANIMATED_PART(LAYER_ALPHA, -5, 5, -7, Rex_wing_R_mesh_layer_4),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, Rex_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, Rex_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
