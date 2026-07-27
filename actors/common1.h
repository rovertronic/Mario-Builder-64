#ifndef COMMON1_H
#define COMMON1_H

#include "types.h"

// coin
extern const Gfx coin_dl_start1[];
extern const Gfx coin_dl_start2[];
extern const Gfx coin_dl_start3[];
extern const Gfx coin_dl_start4[];

extern ALIGNED8 const Texture coin_seg3_texture_tilt_left[];
extern ALIGNED8 const Texture coin_seg3_texture_front[];
extern ALIGNED8 const Texture coin_seg3_texture_tilt_right[];
extern ALIGNED8 const Texture coin_seg3_texture_side[];

extern const GeoLayout yellow_coin_geo[];
extern const GeoLayout yellow_coin_no_shadow_geo[];
extern const GeoLayout blue_coin_geo[];
extern const GeoLayout blue_coin_no_shadow_geo[];
extern const GeoLayout red_coin_geo[];
extern const GeoLayout red_coin_no_shadow_geo[];
extern const GeoLayout green_coin_geo[];
extern const GeoLayout green_coin_no_shadow_geo[];
// extern const GeoLayout pink_coin_geo[];
// extern const GeoLayout pink_coin_no_shadow_geo[];
#ifdef IA8_30FPS_COINS
extern const GeoLayout silver_coin_geo[];
extern const GeoLayout silver_coin_no_shadow_geo[];

extern const Gfx coin_seg3_dl_yellow_0[];
extern const Gfx coin_seg3_dl_yellow_22_5[];
extern const Gfx coin_seg3_dl_yellow_45[];
extern const Gfx coin_seg3_dl_yellow_67_5[];
extern const Gfx coin_seg3_dl_yellow_90[];
extern const Gfx coin_seg3_dl_yellow_67_5_r[];
extern const Gfx coin_seg3_dl_yellow_45_r[];
extern const Gfx coin_seg3_dl_yellow_22_5_r[];

extern const Gfx coin_seg3_dl_blue_0[];
extern const Gfx coin_seg3_dl_blue_22_5[];
extern const Gfx coin_seg3_dl_blue_45[];
extern const Gfx coin_seg3_dl_blue_67_5[];
extern const Gfx coin_seg3_dl_blue_90[];
extern const Gfx coin_seg3_dl_blue_67_5_r[];
extern const Gfx coin_seg3_dl_blue_45_r[];
extern const Gfx coin_seg3_dl_blue_22_5_r[];

extern const Gfx coin_seg3_dl_red_0[];
extern const Gfx coin_seg3_dl_red_22_5[];
extern const Gfx coin_seg3_dl_red_45[];
extern const Gfx coin_seg3_dl_red_67_5[];
extern const Gfx coin_seg3_dl_red_90[];
extern const Gfx coin_seg3_dl_red_67_5_r[];
extern const Gfx coin_seg3_dl_red_45_r[];
extern const Gfx coin_seg3_dl_red_22_5_r[];

extern const Gfx coin_seg3_dl_secret_0[];
extern const Gfx coin_seg3_dl_secret_22_5[];
extern const Gfx coin_seg3_dl_secret_45[];
extern const Gfx coin_seg3_dl_secret_67_5[];
extern const Gfx coin_seg3_dl_secret_90[];
extern const Gfx coin_seg3_dl_secret_67_5_r[];
extern const Gfx coin_seg3_dl_secret_45_r[];
extern const Gfx coin_seg3_dl_secret_22_5_r[];

extern const Gfx coin_seg3_dl_green_0[];
extern const Gfx coin_seg3_dl_green_22_5[];
extern const Gfx coin_seg3_dl_green_45[];
extern const Gfx coin_seg3_dl_green_67_5[];
extern const Gfx coin_seg3_dl_green_90[];
extern const Gfx coin_seg3_dl_green_67_5_r[];
extern const Gfx coin_seg3_dl_green_45_r[];
extern const Gfx coin_seg3_dl_green_22_5_r[];

extern const Gfx coin_seg3_dl_pink_0[];
extern const Gfx coin_seg3_dl_pink_22_5[];
extern const Gfx coin_seg3_dl_pink_45[];
extern const Gfx coin_seg3_dl_pink_67_5[];
extern const Gfx coin_seg3_dl_pink_90[];
extern const Gfx coin_seg3_dl_pink_67_5_r[];
extern const Gfx coin_seg3_dl_pink_45_r[];
extern const Gfx coin_seg3_dl_pink_22_5_r[];

#else
extern const Gfx coin_seg3_sub_dl_begin[];
extern const Gfx coin_seg3_sub_dl_end[];
extern const Gfx coin_seg3_dl_yellow_front[];
extern const Gfx coin_seg3_dl_yellow_tilt_right[];
extern const Gfx coin_seg3_dl_yellow_side[];
extern const Gfx coin_seg3_dl_yellow_tilt_left[];
extern const Gfx coin_seg3_dl_blue_front[];
extern const Gfx coin_seg3_dl_blue_tilt_right[];
extern const Gfx coin_seg3_dl_blue_side[];
extern const Gfx coin_seg3_dl_blue_tilt_left[];
extern const Gfx coin_seg3_dl_red_front[];
extern const Gfx coin_seg3_dl_red_tilt_right[];
extern const Gfx coin_seg3_dl_red_side[];
extern const Gfx coin_seg3_dl_red_tilt_left[];
extern const Gfx coin_seg3_dl_green_front[];
extern const Gfx coin_seg3_dl_green_tilt_right[];
extern const Gfx coin_seg3_dl_green_side[];
extern const Gfx coin_seg3_dl_green_tilt_left[];
// extern const Gfx coin_seg3_dl_pink_front[];
// extern const Gfx coin_seg3_dl_pink_tilt_right[];
// extern const Gfx coin_seg3_dl_pink_side[];
// extern const Gfx coin_seg3_dl_pink_tilt_left[];
#endif

// dirt
extern const GeoLayout dirt_animation_geo[];
extern const GeoLayout cartoon_star_geo[];
extern const Gfx dirt_seg3_sub_dl_dirt_particle[];
extern const Gfx dirt_seg3_dl_dirt_particle[];
extern const Gfx dirt_seg3_sub_dl_cartoon_star[];
extern const Gfx dirt_seg3_dl_cartoon_star_red[];
extern const Gfx dirt_seg3_dl_cartoon_star_green[];
extern const Gfx dirt_seg3_dl_cartoon_star_blue[];
extern const Gfx dirt_seg3_dl_cartoon_star_yellow[];
extern const Gfx dirt_seg3_dl_cartoon_star_billboard[];
extern const Gfx dirt_seg3_dl_tiny_particle_red[];
extern const Gfx dirt_seg3_dl_tiny_particle_green[];
extern const Gfx dirt_seg3_dl_tiny_particle_blue[];
extern const Gfx dirt_seg3_dl_tiny_particle_yellow[];
extern const Gfx dirt_seg3_dl_tiny_particle_billboard[];

// explosion
extern const GeoLayout explosion_geo[];
extern const Gfx explosion_seg3_dl_03004208[];
extern const Gfx explosion_seg3_dl_03004298[];
extern const Gfx explosion_seg3_dl_030042B0[];
extern const Gfx explosion_seg3_dl_030042C8[];
extern const Gfx explosion_seg3_dl_030042E0[];
extern const Gfx explosion_seg3_dl_030042F8[];
extern const Gfx explosion_seg3_dl_03004310[];
extern const Gfx explosion_seg3_dl_03004328[];

// flame
extern const GeoLayout red_flame_shadow_geo[];
extern const GeoLayout red_flame_geo[];
extern const GeoLayout blue_flame_geo[];
extern const Gfx flame_seg3_dl_0301B320[];
extern const Gfx flame_seg3_dl_0301B3B0[];
extern const Gfx flame_seg3_dl_0301B3C8[];
extern const Gfx flame_seg3_dl_0301B3E0[];
extern const Gfx flame_seg3_dl_0301B3F8[];
extern const Gfx flame_seg3_dl_0301B410[];
extern const Gfx flame_seg3_dl_0301B428[];
extern const Gfx flame_seg3_dl_0301B440[];
extern const Gfx flame_seg3_dl_0301B458[];
extern const Gfx flame_seg3_dl_0301B470[];
extern const Gfx flame_seg3_dl_0301B500[];
extern const Gfx flame_seg3_dl_0301B518[];
extern const Gfx flame_seg3_dl_0301B530[];
extern const Gfx flame_seg3_dl_0301B548[];
extern const Gfx flame_seg3_dl_0301B560[];
extern const Gfx flame_seg3_dl_0301B578[];
extern const Gfx flame_seg3_dl_0301B590[];
extern const Gfx flame_seg3_dl_0301B5A8[];

// leaves
extern const GeoLayout leaves_geo[];
extern const Gfx leaves_seg3_dl_0301CDE0[];

// mist
extern const GeoLayout mist_geo[];
extern const GeoLayout white_puff_geo[];
extern const Gfx mist_seg3_dl_03000880[];
extern const Gfx mist_seg3_dl_03000920[];

// number
extern const GeoLayout number_geo[];

// pebble
extern const Gfx pebble_seg3_dl_0301CB00[];

// power_meter
extern const Texture *const power_meter_health_segments_lut[];
extern const Gfx dl_power_meter_base[];
extern const Gfx dl_power_meter_health_segments_begin[];
extern const Gfx dl_power_meter_health_segments_end[];

#ifdef BREATH_METER
// breath_meter
extern const Texture *const breath_meter_segments_lut[];
extern const Gfx dl_breath_meter_base[];
extern const Gfx dl_breath_meter_health_segments_begin[];
extern const Gfx dl_breath_meter_health_segments_end[];
#endif

// sand
extern const Gfx sand_seg3_dl_particle[];

// star
extern const GeoLayout star_geo[];
extern const Gfx star_seg3_sub_dl_body[];
extern const Gfx star_seg3_dl_body[];
extern const Gfx star_seg3_sub_dl_eyes[];
extern const Gfx star_seg3_dl_eyes[];

// metalstar
extern const GeoLayout metalstar_geo[];
extern const Gfx metalstar_seg3_sub_dl_body[];
extern const Gfx metalstar_seg3_dl_body[];
extern const Gfx metalstar_seg3_sub_dl_eyes[];
extern const Gfx metalstar_seg3_dl_eyes[];

// transparent_star
extern const GeoLayout transparent_star_geo[];
extern const Gfx transparent_star_seg3_sub_dl_body[];
extern const Gfx transparent_star_seg3_dl_body[];
extern const Gfx transparent_star_black[];

// tree
extern const GeoLayout bubbly_tree_geo[];
extern const GeoLayout dead_tree_geo[];
extern const GeoLayout spiky_tree_geo[];
extern const GeoLayout farm_tree_geo[];
extern const GeoLayout snow_tree_geo[];
extern const GeoLayout palm_tree_geo[];
extern const Gfx tree_seg3_dl_bubbly[];
extern const Gfx tree_seg3_dl_bubbly_transparent[];
extern const Gfx tree_seg3_dl_spiky[];
extern const Gfx tree_seg3_dl_spiky_transparent[];
extern const Gfx tree_seg3_dl_snowy_pine[];
extern const Gfx tree_seg3_dl_snowy_pine_transparent[];
extern const Gfx tree_seg3_dl_palm[];
extern const Gfx tree_seg3_dl_palm_transparent[];
extern const Gfx tree_seg3_dl_dead[];
extern const Gfx tree_seg3_dl_spiky_real[];

// white_particle
extern const GeoLayout white_particle_geo[];
extern const Gfx white_particle_dl[];

// // wooden_signpost
extern const GeoLayout wooden_signpost_geo[];
extern const Gfx wooden_signpost_seg3_dl_0302D9C8[];
extern const Gfx wooden_signpost_seg3_dl_0302DA48[];
extern const Gfx wooden_signpost_seg3_dl_0302DC40[];
extern const Gfx wooden_signpost_seg3_dl_0302DCD0[];
extern const Gfx wooden_signpost_seg3_dl_0302DD08[];
extern const Collision wooden_signpost_seg3_collision_0302DD80[];

#endif
