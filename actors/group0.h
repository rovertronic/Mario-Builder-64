#ifndef GROUP0_H
#define GROUP0_H

#include "types.h"

// bubble
extern const GeoLayout bubble_geo[];
extern const GeoLayout purple_marble_geo[];
extern const Gfx bubble_seg4_dl_0401DD60[];
extern const Gfx bubble_seg4_dl_0401DDE0[];

// burn_smoke
extern const GeoLayout burn_smoke_geo[];
extern const Gfx burn_smoke_seg4_sub_dl_begin[];
extern const Gfx burn_smoke_seg4_sub_dl_model[];
extern const Gfx burn_smoke_seg4_sub_dl_end[];
extern const Gfx burn_smoke_seg4_dl[];

/*
//Crowbar
extern Vtx Crowbar_Crowbar_Mesh_mesh_vtx_0[496];
extern Gfx Crowbar_Crowbar_Mesh_mesh_tri_0[];
extern Vtx Crowbar_Crowbar_Mesh_mesh_vtx_1[40];
extern Gfx Crowbar_Crowbar_Mesh_mesh_tri_1[];

extern Gfx Crowbar_Crowbar_Mesh_mesh[];

extern GeoLayout crowbar_geo[];
*/

//extern const Lights1 mario_button_v4_lights;
//extern const Lights1 mario_hat_v4_lights;
//extern const Lights1 mario_skin_v4_lights;
//extern const Lights1 mario_shoes_v4_lights;

extern const Lights1 token_token_lights[];

// mario
extern const GeoLayout mario_geo_face_and_wings[];
extern const GeoLayout mario_geo_left_hand[];
extern const GeoLayout mario_geo_right_hand[];
extern const GeoLayout mario_geo_body[];
extern const GeoLayout mario_geo_medium_poly_left_hand[];
extern const GeoLayout mario_geo_medium_poly_right_hand[];
extern const GeoLayout mario_geo_medium_poly_body[];
extern const GeoLayout mario_geo_low_poly_face_and_wings[];
extern const GeoLayout mario_geo_low_poly_left_hand[];
extern const GeoLayout mario_geo_low_poly_right_hand[];
extern const GeoLayout mario_geo_low_poly_body[];
extern const GeoLayout mario_vanish_geo_face_and_wings[];
extern const GeoLayout mario_vanish_geo_left_hand[];
extern const GeoLayout mario_vanish_geo_right_hand[];
extern const GeoLayout mario_vanish_geo_body[];
extern const GeoLayout mario_vanish_geo_medium_poly_left_hand[];
extern const GeoLayout mario_vanish_geo_medium_poly_right_hand[];
extern const GeoLayout mario_vanish_geo_medium_poly_body[];
extern const GeoLayout mario_vanish_geo_low_poly_face_and_wings[];
extern const GeoLayout mario_vanish_geo_low_poly_left_hand[];
extern const GeoLayout mario_vanish_geo_low_poly_right_hand[];
extern const GeoLayout mario_vanish_geo_low_poly_body[];
extern const GeoLayout mario_metal_geo_face_and_wings[];
extern const GeoLayout mario_metal_geo_left_hand[];
extern const GeoLayout mario_metal_geo_right_hand[];
extern const GeoLayout mario_metal_geo_body[];
extern const GeoLayout mario_metal_geo_medium_poly_left_hand[];
extern const GeoLayout mario_metal_geo_medium_poly_right_hand[];
extern const GeoLayout mario_metal_geo_medium_poly_body[];
extern const GeoLayout mario_metal_geo_low_poly_face_and_wings[];
extern const GeoLayout mario_metal_geo_low_poly_left_hand[];
extern const GeoLayout mario_metal_geo_low_poly_right_hand[];
extern const GeoLayout mario_metal_geo_low_poly_body[];
extern const GeoLayout mario_metal_vanish_geo_face_and_wings[];
extern const GeoLayout mario_metal_vanish_geo_left_hand[];
extern const GeoLayout mario_metal_vanish_geo_right_hand[];
extern const GeoLayout mario_metal_vanish_geo_body[];
extern const GeoLayout mario_metal_vanish_geo_medium_poly_left_hand[];
extern const GeoLayout mario_metal_vanish_geo_medium_poly_right_hand[];
extern const GeoLayout mario_metal_vanish_geo_medium_poly_body[];
extern const GeoLayout mario_metal_vanish_geo_low_poly_face_and_wings[];
extern const GeoLayout mario_metal_vanish_geo_low_poly_left_hand[];
extern const GeoLayout mario_metal_vanish_geo_low_poly_right_hand[];
extern const GeoLayout mario_metal_vanish_geo_low_poly_body[];
extern const GeoLayout mario_geo_load_body[];
extern const GeoLayout mario_geo_load_medium_poly_body[];
extern const GeoLayout mario_geo_load_low_poly_body[];
extern const GeoLayout mario_geo_render_body[];
extern const GeoLayout mario_geo[];
extern const Gfx mario_butt_dl[];
extern const Gfx mario_butt[];
extern const Gfx mario_metal_butt[];
extern const Gfx mario_left_arm_shared_dl[];
extern const Gfx mario_left_arm[];
extern const Gfx mario_left_forearm_shared_dl[];
extern const Gfx mario_left_hand_closed_shared_dl[];
extern const Gfx mario_left_hand_closed[];
extern const Gfx mario_right_arm_shared_dl[];
extern const Gfx mario_right_arm[];
extern const Gfx mario_right_forearm_shared_dl[];
extern const Gfx mario_right_hand_closed_dl[];
extern const Gfx mario_right_hand_closed[];
extern const Gfx mario_metal_right_hand_closed[];
extern const Gfx mario_left_thigh_dl[];
extern const Gfx mario_left_thigh[];
extern const Gfx mario_metal_left_thigh[];
extern const Gfx mario_left_leg_shared_dl[];
extern const Gfx mario_left_foot_shared_dl[];
extern const Gfx mario_left_foot[];
extern const Gfx mario_right_thigh_shared_dl[];
extern const Gfx mario_right_thigh[];
extern const Gfx mario_right_leg_shared_dl[];
extern const Gfx mario_right_foot_dl[];
extern const Gfx mario_right_foot[];
extern const Gfx mario_metal_right_foot[];
extern const Gfx mario_yellow_button_dl[];
extern const Gfx mario_pants_overalls_shared_dl[];
extern const Gfx mario_tshirt_shared_dl[];
extern const Gfx mario_torso_dl[];
extern const Gfx mario_torso[];
extern const Gfx mario_metal_torso_shared_dl[];
extern const Gfx mario_m_logo_dl[];
extern const Gfx mario_eyes_cap_on_dl[];
extern const Gfx mario_hair_sideburn_cap_on_dl[];
extern const Gfx mario_mustache_cap_on_dl[];
extern const Gfx mario_face_part_cap_on_dl[];
extern const Gfx mario_face_cap_dl[];
extern const Gfx mario_face_back_hair_cap_on_dl[];
extern const Gfx mario_face_cap_on_dl[];
extern const Gfx mario_cap_on_eyes_front[];
extern const Gfx mario_cap_on_eyes_half_closed[];
extern const Gfx mario_cap_on_eyes_closed[];
extern const Gfx mario_cap_on_eyes_right[];
extern const Gfx mario_cap_on_eyes_left[];
extern const Gfx mario_cap_on_eyes_up[];
extern const Gfx mario_cap_on_eyes_down[];
extern const Gfx mario_cap_on_eyes_dead[];
extern const Gfx mario_metal_cap_on_shared_dl[];
extern const Gfx mario_eyes_cap_off_dl[];
extern const Gfx mario_mustache_cap_off_dl[];
extern const Gfx mario_hair_sideburn_cap_off_dl[];
extern const Gfx mario_face_part_cap_off_dl[];
extern const Gfx mario_face_hair_cap_off_dl[];
extern const Gfx mario_face_cap_off_dl[];
extern const Gfx mario_cap_off_eyes_front[];
extern const Gfx mario_cap_off_eyes_half_closed[];
extern const Gfx mario_cap_off_eyes_closed[];
extern const Gfx mario_cap_off_eyes_right[];
extern const Gfx mario_cap_off_eyes_left[];
extern const Gfx mario_cap_off_eyes_up[];
extern const Gfx mario_cap_off_eyes_down[];
extern const Gfx mario_cap_off_eyes_dead[];
extern const Gfx mario_metal_cap_off_shared_dl[];
extern const Gfx mario_medium_poly_butt_dl[];
extern const Gfx mario_medium_poly_butt[];
extern const Gfx mario_metal_medium_poly_butt[];
extern const Gfx mario_medium_poly_left_arm_shared_dl[];
extern const Gfx mario_medium_poly_left_arm[];
extern const Gfx mario_medium_poly_left_forearm_shared_dl[];
extern const Gfx mario_medium_poly_left_hand_closed_shared_dl[];
extern const Gfx mario_medium_poly_left_hand_closed[];
extern const Gfx mario_medium_poly_right_arm_shared_dl[];
extern const Gfx mario_medium_poly_right_arm[];
extern const Gfx mario_medium_poly_right_forearm_shared_dl[];
extern const Gfx mario_medium_poly_right_hand_closed_dl[];
extern const Gfx mario_medium_poly_right_hand_closed[];
extern const Gfx mario_metal_medium_poly_right_hand_closed[];
extern const Gfx mario_medium_poly_left_thigh_dl[];
extern const Gfx mario_medium_poly_left_thigh[];
extern const Gfx mario_metal_medium_poly_left_thigh[];
extern const Gfx mario_medium_poly_left_leg_shared_dl[];
extern const Gfx mario_medium_poly_left_foot_shared_dl[];
extern const Gfx mario_medium_poly_left_foot[];
extern const Gfx mario_medium_poly_right_thigh_shared_dl[];
extern const Gfx mario_medium_poly_right_thigh[];
extern const Gfx mario_medium_poly_right_leg_shared_dl[];
extern const Gfx mario_medium_poly_right_foot_dl[];
extern const Gfx mario_medium_poly_right_foot[];
extern const Gfx mario_metal_medium_poly_right_foot[];
extern const Gfx mario_medium_poly_yellow_button_dl[];
extern const Gfx mario_medium_poly_pants_overalls_shared_dl[];
extern const Gfx mario_medium_poly_tshirt_shared_dl[];
extern const Gfx mario_medium_poly_torso_dl[];
extern const Gfx mario_medium_poly_torso[];
extern const Gfx mario_metal_medium_poly_torso[];
extern const Gfx mario_low_poly_butt_dl[];
extern const Gfx mario_low_poly_butt[];
extern const Gfx mario_metal_low_poly_butt[];
extern const Gfx mario_low_poly_left_arm_shared_dl[];
extern const Gfx mario_low_poly_left_arm[];
extern const Gfx mario_low_poly_left_forearm_shared_dl[];
extern const Gfx mario_low_poly_left_hand_closed_shared_dl[];
extern const Gfx mario_low_poly_left_hand_closed[];
extern const Gfx mario_low_poly_right_arm_shared_dl[];
extern const Gfx mario_low_poly_right_arm[];
extern const Gfx mario_low_poly_right_forearm_shared_dl[];
extern const Gfx mario_low_poly_right_hand_closed_dl[];
extern const Gfx mario_low_poly_right_hand_closed[];
extern const Gfx mario_metal_low_poly_right_hand_closed[];
extern const Gfx mario_low_poly_left_thigh_dl[];
extern const Gfx mario_low_poly_left_thigh[];
extern const Gfx mario_metal_low_poly_left_thigh[];
extern const Gfx mario_low_poly_left_leg_shared_dl[];
extern const Gfx mario_low_poly_left_foot_shared_dl[];
extern const Gfx mario_low_poly_left_foot[];
extern const Gfx mario_low_poly_right_thigh_shared_dl[];
extern const Gfx mario_low_poly_right_thigh[];
extern const Gfx mario_low_poly_right_leg_shared_dl[];
extern const Gfx mario_low_poly_right_foot_dl[];
extern const Gfx mario_low_poly_right_foot[];
extern const Gfx mario_metal_low_poly_right_foot[];
extern const Gfx mario_low_poly_yellow_button_dl[];
extern const Gfx mario_low_poly_pants_overalls_shared_dl[];
extern const Gfx mario_low_poly_tshirt_shared_dl[];
extern const Gfx mario_low_poly_torso_dl[];
extern const Gfx mario_low_poly_torso[];
extern const Gfx mario_metal_low_poly_torso[];
extern const Gfx mario_low_poly_mario_m_logo_dl[];
extern const Gfx mario_low_poly_eyes_cap_on_dl[];
extern const Gfx mario_low_poly_mustache_cap_on_dl[];
extern const Gfx mario_low_poly_face_part_cap_on_dl[];
extern const Gfx mario_low_poly_face_cap_dl[];
extern const Gfx mario_low_poly_face_back_hair_cap_on_dl[];
extern const Gfx mario_low_poly_face_cap_on_dl[];
extern const Gfx mario_low_poly_cap_on_eyes_front[];
extern const Gfx mario_low_poly_cap_on_eyes_half_closed[];
extern const Gfx mario_low_poly_cap_on_eyes_closed[];
extern const Gfx mario_low_poly_cap_on_eyes_right[];
extern const Gfx mario_low_poly_cap_on_eyes_left[];
extern const Gfx mario_low_poly_cap_on_eyes_up[];
extern const Gfx mario_low_poly_cap_on_eyes_down[];
extern const Gfx mario_low_poly_cap_on_eyes_dead[];
extern const Gfx mario_metal_low_poly_cap_on[];
extern const Gfx mario_low_poly_mario_eyes_cap_off_dl[];
extern const Gfx mario_low_poly_mustache_cap_off_dl[];
extern const Gfx mario_low_poly_face_part_cap_off_dl[];
extern const Gfx mario_low_poly_face_hair_cap_off_dl[];
extern const Gfx mario_low_poly_face_cap_off_dl[];
extern const Gfx mario_low_poly_cap_off_eyes_front[];
extern const Gfx mario_low_poly_cap_off_eyes_half_closed[];
extern const Gfx mario_low_poly_cap_off_eyes_closed[];
extern const Gfx mario_low_poly_cap_off_eyes_right[];
extern const Gfx mario_low_poly_cap_off_eyes_left[];
extern const Gfx mario_low_poly_cap_off_eyes_up[];
extern const Gfx mario_low_poly_cap_off_eyes_down[];
extern const Gfx mario_low_poly_cap_off_eyes_dead[];
extern const Gfx mario_metal_low_poly_cap_off[];
extern const Gfx mario_left_hand_open_shared_dl[];
extern const Gfx mario_left_hand_open[];
extern const Gfx mario_right_hand_open_dl[];
extern const Gfx mario_right_hand_open[];
extern const Gfx mario_metal_right_hand_open[];
extern const Gfx mario_right_hand_cap_m_logo_dl[];
extern const Gfx mario_right_hand_cap_top_dl[];
extern const Gfx mario_right_hand_cap_hand_position_dl[];
extern const Gfx mario_right_hand_cap_bottom_dl[];
extern const Gfx mario_right_hand_cap_dl[];
extern const Gfx mario_right_hand_cap_wings_half_1_dl[];
extern const Gfx mario_right_hand_cap_wings_half_2_dl[];
extern const Gfx mario_right_hand_cap_wings_initial_dl[];
extern const Gfx mario_right_hand_cap_wings_end_dl[];
extern const Gfx mario_right_hand_cap[];
extern const Gfx mario_right_hand_cap_wings[];
extern const Gfx mario_metal_right_hand_cap_shared_dl[];
extern const Gfx mario_metal_right_hand_cap_shared_dl_wings[];
extern const Gfx mario_right_hand_peace_shared_dl[];
extern const Gfx mario_right_hand_peace[];
extern const Gfx mario_cap_unused_m_logo_dl[];
extern const Gfx mario_cap_unused_base_top_dl[];
extern const Gfx mario_cap_unused_base_bottom_dl[];
extern const Gfx mario_cap_unused_base_dl[];
extern const Gfx mario_wings_half_1_unused_dl[];
extern const Gfx mario_wings_half_2_unused_dl[];
extern const Gfx mario_cap_wings_unused_initial_dl[];
extern const Gfx mario_cap_wings_unused_end_dl[];
extern const Gfx mario_cap_unused_dl[];
extern const Gfx mario_metal_cap_unused_dl[];
extern const Gfx mario_cap_wings_unused[];
extern const Gfx mario_metal_cap_wings_unused[];
extern const Gfx mario_wings_half_1_dl[];
extern const Gfx mario_wings_half_2_dl[];
extern const Gfx mario_cap_wings[];
extern const Gfx mario_cap_wings_transparent[];
extern const Gfx mario_metal_cap_wings[];
extern const Gfx mario_metal_cap_wings_transparent[];

// sparkle
extern const GeoLayout sparkles_geo[];
extern const Gfx sparkles_seg4_dl_0402A490[];
extern const Gfx sparkles_seg4_dl_0402A4F8[];
extern const Gfx sparkles_seg4_dl_0402A510[];
extern const Gfx sparkles_seg4_dl_0402A528[];
extern const Gfx sparkles_seg4_dl_0402A540[];
extern const Gfx sparkles_seg4_dl_0402A558[];
extern const Gfx sparkles_seg4_dl_0402A570[];

// sparkle_animation
extern const GeoLayout sparkles_animation_geo[];
extern const Gfx sparkles_animation_seg4_dl_04035288[];
extern const Gfx sparkles_animation_seg4_dl_04035300[];
extern const Gfx sparkles_animation_seg4_dl_04035318[];
extern const Gfx sparkles_animation_seg4_dl_04035330[];
extern const Gfx sparkles_animation_seg4_dl_04035348[];
extern const Gfx sparkles_animation_seg4_dl_04035360[];

// small water splash
extern const GeoLayout small_water_splash_geo[];
extern const Gfx small_water_splash_seg4_dl_0[];
extern const Gfx small_water_splash_seg4_dl_1[];
extern const Gfx small_water_splash_seg4_dl_2[];
extern const Gfx small_water_splash_seg4_dl_3[];
extern const Gfx small_water_splash_seg4_dl_4[];
extern const Gfx small_water_splash_seg4_dl_5[];

// walk_smoke
extern const GeoLayout smoke_geo[];
extern const Gfx smoke_seg4_dl_040216A0[];
extern const Gfx smoke_seg4_dl_04021718[];
extern const Gfx smoke_seg4_dl_04021730[];
extern const Gfx smoke_seg4_dl_04021748[];
extern const Gfx smoke_seg4_dl_04021760[];
extern const Gfx smoke_seg4_dl_04021778[];
extern const Gfx smoke_seg4_dl_04021790[];
extern const Gfx smoke_seg4_dl_040217A8[];

// water_splash
extern const GeoLayout water_splash_geo[];
extern const Gfx water_splash_seg4_dl_040325C8[];
extern const Gfx water_splash_seg4_dl_04032640[];
extern const Gfx water_splash_seg4_dl_04032658[];
extern const Gfx water_splash_seg4_dl_04032670[];
extern const Gfx water_splash_seg4_dl_04032688[];
extern const Gfx water_splash_seg4_dl_040326A0[];
extern const Gfx water_splash_seg4_dl_040326B8[];
extern const Gfx water_splash_seg4_dl_040326D0[];
extern const Gfx water_splash_seg4_dl_040326E8[];

// water_waves
extern const GeoLayout idle_water_wave_geo[];
extern const GeoLayout wave_trail_geo[];
extern const Gfx water_wave_seg4_dl_04027358[];
extern const Gfx water_wave_seg4_dl_040273A0[];
extern const Gfx water_wave_seg4_dl_040273D8[];
extern const Gfx water_wave_seg4_dl_040273F0[];
extern const Gfx water_wave_seg4_dl_04027408[];
extern const Gfx water_wave_seg4_dl_04027420[];
extern const Gfx water_wave_seg4_dl_04027438[];

// white_particle_small
extern const Gfx white_particle_small_dl_begin[];
extern const Gfx white_particle_small_dl_end[];
extern const Gfx white_particle_small_dl[];
extern const Gfx white_particle_small_unused_dl[];

// moneybag
extern const GeoLayout moneybag_geo_000000[];
extern const GeoLayout moneybag_geo_000078[];
extern const GeoLayout moneybag_geo[];
extern const Gfx moneybag_seg6_dl_06005300[];
extern const Gfx moneybag_seg6_dl_06005358[];
extern const Gfx moneybag_seg6_dl_060053B8[];
extern const Gfx moneybag_seg6_dl_06005590[];
extern const Gfx moneybag_seg6_dl_06005618[];
extern const Gfx moneybag_seg6_dl_06005688[];
extern const Gfx moneybag_seg6_dl_06005708[];
extern const Gfx moneybag_seg6_dl_06005750[];
extern const Gfx moneybag_seg6_dl_06005980[];
extern const Gfx moneybag_seg6_dl_060059F0[];
extern const struct Animation *const moneybag_seg6_anims_06005E5C[];

// monty_mole
extern const GeoLayout monty_mole_geo[];
extern const Gfx monty_mole_seg5_dl_05003208[];
extern const Gfx monty_mole_seg5_dl_050032A0[];
extern const Gfx monty_mole_seg5_dl_05003438[];
extern const Gfx monty_mole_seg5_dl_050034A0[];
extern const Gfx monty_mole_seg5_dl_05003518[];
extern const Gfx monty_mole_seg5_dl_05003730[];
extern const Gfx monty_mole_seg5_dl_050037A8[];
extern const Gfx monty_mole_seg5_dl_05003820[];
extern const Gfx monty_mole_seg5_dl_05003938[];
extern const Gfx monty_mole_seg5_dl_050039D0[];
extern const Gfx monty_mole_seg5_dl_05003B68[];
extern const Gfx monty_mole_seg5_dl_05003BD0[];
extern const Gfx monty_mole_seg5_dl_05003C48[];
extern const Gfx monty_mole_seg5_dl_05003E60[];
extern const Gfx monty_mole_seg5_dl_05003ED8[];
extern const Gfx monty_mole_seg5_dl_05003F50[];
extern const Gfx monty_mole_seg5_dl_050042B8[];
extern const Gfx monty_mole_seg5_dl_05004368[];
extern const Gfx monty_mole_seg5_dl_050044B0[];
extern const Gfx monty_mole_seg5_dl_050049B0[];
extern const Gfx monty_mole_seg5_dl_05004A10[];
extern const Gfx monty_mole_seg5_dl_05004B50[];
extern const Gfx monty_mole_seg5_dl_05004BE0[];
extern const Gfx monty_mole_seg5_dl_05004C00[];
extern const Gfx monty_mole_seg5_dl_05004CE8[];
extern const Gfx monty_mole_seg5_dl_05004D30[];
extern const struct Animation *const monty_mole_seg5_anims_05007248[];

//bowsers animations??
extern const struct Animation *const bowser_seg6_anims_06057690[];

// monty_mole_hole
extern const Gfx monty_mole_hole_seg5_dl_05000840[];

extern const struct Animation *const Hammerbro_anims[];

#include "mario/geo_header.h"

#include "Hammerbro/geo_header.h"


#include "Hammerbro/anim_header.h"
#include "hammer/geo_header.h"

#include "ring/geo_header.h"

#include "metal_crate/geo_header.h"

#include "metal_crate/collision_header.h"


#include "evil_mario/anim_header.h"
#include "chicken/geo_header.h"


#include "chicken/anim_header.h"
#include "token/geo_header.h"


#include "crab_anims/anim_header.h"
#include "egg/geo_header.h"

#include "arrow/header.h"

#include "BadgeSelect/header.h"

#include "MysteryBadge/header.h"

#include "snakeblock/collision_header.h"

#include "snakeblock1/geo_header.h"

#include "snakeblock2/geo_header.h"

#include "snakeblock3/geo_header.h"

#include "b0/header.h"

#include "b1/header.h"

#include "b2/header.h"

#include "b3/header.h"

#include "b4/header.h"

#include "b5/header.h"

#include "b6/header.h"

#include "b7/header.h"

#include "b8/header.h"

#include "b9/header.h"

#include "b10/header.h"

#include "b11/header.h"

#include "bE/header.h"

//#include "title/header.h"

#include "Rex/geo_header.h"


#include "Rex/anim_header.h"
#include "dcoin/geo_header.h"

#include "shopgui/header.h"

#include "shopselect/header.h"

#include "wallet/geo_header.h"

#include "noteblock/geo_header.h"
#include "noteblock/collision_header.h"


#include "null_anims/anim_header.h"
#include "ico_heart/header.h"

#include "ico_mana/header.h"

#include "ico_badge/header.h"


#include "rb_hud/header.h"

#include "rb_bar/header.h"

#include "bs_hud/header.h"

#include "bs_bar/header.h"

#include "billmask/geo_header.h"

#include "gradibox/header.h"

#include "showrunner/geo_header.h"


#include "showrunner/anim_header.h"
#include "b12/header.h"

#include "b13/header.h"

#include "b14/header.h"

#include "b15/header.h"

#include "b16/header.h"

#include "b21/header.h"

#include "b22/header.h"

#include "b17/header.h"

#include "executive_/header.h"

#include "spotlight/geo_header.h"

#include "executive_loom_/header.h"


#include "girl/anim_header.h"
#include "b23/header.h"

#include "b20/header.h"

#include "b18/header.h"

#include "tvhead/collision_header.h"

#include "tvhead/geo_header.h"


#include "tvhead/anim_header.h"
#include "b19/header.h"

#include "quest/geo_header.h"

#include "rocket_boot/geo_header.h"

#include "vanetalc/geo_header.h"

#include "ocean_ttc/geo_header.h"

#include "tvcorpse/geo_header.h"

#include "cosmic_spike/geo_header.h"

#include "crowbar2/geo_header.h"

#include "cube_collision/collision_header.h"

#include "sb/header.h"

#include "top/header.h"

#include "maker/header.h"

#include "grasstop/header.h"

#include "lava_collision/collision_header.h"

#include "slope_collision/collision_header.h"

#include "slope/header.h"

#include "corner_collision/collision_header.h"

#include "corner/header.h"

#include "icorner/header.h"

#include "icorner_collision/collision_header.h"

#include "uibutton/header.h"

#include "uibutton2/header.h"

#include "b/header.h"

#include "cull/header.h"

#include "bg/header.h"

#include "sb_cube/geo_header.h"

#endif
