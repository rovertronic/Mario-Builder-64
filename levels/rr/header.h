#ifndef RR_HEADER_H
#define RR_HEADER_H

#include "types.h"

//cam spline : )
extern const f32 rr_frames[][2][3];

// geo
extern const GeoLayout rr_geo_000660[];
extern const GeoLayout rr_geo_000678[];
extern const GeoLayout rr_geo_000690[];
extern const GeoLayout rr_geo_0006A8[];
extern const GeoLayout rr_geo_0006C0[];
extern const GeoLayout rr_geo_0006D8[];
extern const GeoLayout rr_geo_0006F0[];
extern const GeoLayout rr_geo_000708[];
extern const GeoLayout rr_geo_000720[];
extern const GeoLayout rr_geo_000738[];
extern const GeoLayout rr_geo_000758[];
extern const GeoLayout rr_geo_000770[];
extern const GeoLayout rr_geo_000788[];
extern const GeoLayout rr_geo_0007A0[];
extern const GeoLayout rr_geo_0007B8[];
extern const GeoLayout rr_geo_0007D0[];
extern const GeoLayout rr_geo_0007E8[];
extern const GeoLayout rr_geo_000800[];
extern const GeoLayout rr_geo_000818[];
extern const GeoLayout rr_geo_000830[];
extern const GeoLayout rr_geo_000848[];
extern const GeoLayout rr_geo_000860[];
extern const GeoLayout rr_geo_000878[];
extern const GeoLayout rr_geo_000890[];
extern const GeoLayout rr_geo_0008A8[];
extern const GeoLayout rr_geo_0008C0[];
extern const GeoLayout rr_geo_0008D8[];
extern const GeoLayout rr_geo_0008F0[];
extern const GeoLayout rr_geo_000908[];
extern const GeoLayout rr_geo_000920[];
extern const GeoLayout rr_geo_000940[];
extern const GeoLayout rr_geo_000958[];
extern const GeoLayout rr_geo_000970[];
extern const GeoLayout rr_geo_000988[];
extern const GeoLayout rr_geo_0009A0[];
extern const GeoLayout rr_geo_0009B8[];
extern const GeoLayout rr_geo_0009D0[];

// leveldata
extern const Gfx dl_cruiser_metal_holes[];
extern const Gfx rr_seg7_dl_07002CC8[];
extern const Gfx rr_seg7_dl_07002E80[];
extern const Gfx rr_seg7_dl_07004A98[];
extern const Gfx rr_seg7_dl_07005C80[];
extern const Gfx rr_seg7_dl_07007E60[];
extern const Gfx rr_seg7_dl_07008258[];
extern const Gfx rr_seg7_dl_07008E20[];
extern const Gfx rr_seg7_dl_0700BB48[];
extern const Gfx rr_seg7_dl_0700CA38[];
extern const Gfx rr_seg7_dl_0700DBD8[];
extern const Gfx rr_seg7_dl_0700DE88[];
extern const Gfx rr_seg7_dl_0700E178[];
extern const Gfx rr_seg7_dl_0700E830[];
extern const Gfx rr_seg7_dl_07012758[];
extern const Gfx rr_seg7_dl_07014508[];
extern const Gfx rr_seg7_dl_07014F30[];
extern const Gfx rr_seg7_dl_070156B8[];
extern const Gfx rr_seg7_dl_07015C68[];
extern const Gfx rr_seg7_dl_07017530[];
extern const Gfx rr_seg7_dl_07018B58[];
extern const Gfx rr_seg7_dl_070191A0[];
extern const s16 flying_carpet_static_vertex_data[];
extern const Gfx dl_flying_carpet_begin[];
extern const Gfx dl_flying_carpet_model_half[];
extern const Gfx dl_flying_carpet_end[];
extern const Gfx rr_seg7_dl_07019AE0[];
extern const Gfx rr_seg7_dl_0701A568[];
extern const Gfx rr_seg7_dl_0701A680[];
extern const Gfx rr_seg7_dl_0701AB78[];
extern const Gfx rr_seg7_dl_0701ADF8[];
extern const Gfx rr_seg7_dl_0701AFA0[];
extern const Gfx rr_seg7_dl_0701B220[];
extern const Gfx rr_seg7_dl_0701B4C0[];
extern const Gfx rr_seg7_dl_0701B848[];
extern const Gfx rr_seg7_dl_0701B980[];
extern const Gfx rr_seg7_dl_0701BD08[];
extern const Gfx rr_seg7_dl_0701E670[];
extern const Gfx rr_seg7_dl_07021100[];
extern const Gfx rr_seg7_dl_07023B90[];
extern const Gfx rr_seg7_dl_07026630[];
extern const Gfx rr_seg7_dl_07028FA8[];
extern const Collision rr_seg7_collision_flying_carpet[];
extern const Collision rr_seg7_collision_pendulum[];
extern const Collision rr_seg7_collision_rotating_platform_with_fire[];
extern const Collision rr_seg7_collision_07029508[];
extern const Collision rr_seg7_collision_070295F8[];
extern const Collision rr_seg7_collision_0702967C[];
extern const Collision rr_seg7_collision_elevator_platform[];
extern const Collision rr_seg7_collision_07029750[];
extern const Collision rr_seg7_collision_donut_platform[];
extern const Collision rr_seg7_collision_07029858[];
extern const Collision rr_seg7_collision_07029924[];
extern const Collision rr_seg7_collision_07029C1C[];
extern const Collision rr_seg7_collision_07029FA4[];
extern const Collision rr_seg7_collision_0702A32C[];
extern const Collision rr_seg7_collision_0702A6B4[];
extern const Collision rr_seg7_collision_level[];
extern const MacroObject rr_seg7_macro_objs[];
extern const Trajectory rr_seg7_trajectory_0702EC3C[];
extern const Trajectory rr_seg7_trajectory_0702ECC0[];
extern const Trajectory rr_seg7_trajectory_0702ED9C[];
extern const Trajectory rr_seg7_trajectory_0702EEE0[];

// script
extern const LevelScript level_rr_entry[];

#include "levels/rr/fountain2/geo_header.h"


#include "levels/rr/header.inc.h"

#include "levels/rr/blocker/geo_header.h"

#include "levels/rr/rr_door/geo_header.h"

#include "levels/rr/rr_door/collision_header.h"

#include "levels/rr/rr_tube/geo_header.h"

#include "levels/rr/rr_tube/collision_header.h"

#include "levels/rr/rr_eye/geo_header.h"

#include "levels/rr/rr_pyramid/geo_header.h"

#include "levels/rr/rr_pyramid/collision_header.h"

#include "levels/rr/spinseed/collision_header.h"

#include "levels/rr/spinseed/geo_header.h"

#include "levels/rr/staticflood/geo_header.h"

#include "levels/rr/staticflood/collision_header.h"

#include "levels/rr/blood/geo_header.h"

#include "levels/rr/blood/collision_header.h"

#include "levels/rr/palamedes/geo_header.h"

#include "levels/rr/palamedes/anim_header.h"

#include "levels/rr/agheart/geo_header.h"

#include "levels/rr/agportal/geo_header.h"

#include "levels/rr/blood_particle/geo_header.h"

#include "levels/rr/agcrack/geo_header.h"

#include "levels/rr/agcrack/collision_header.h"

#include "levels/rr/agpillar1/collision_header.h"

#include "levels/rr/agpillar1/geo_header.h"

#include "levels/rr/agwall/geo_header.h"

#include "levels/rr/agwall/collision_header.h"

#include "levels/rr/agcrumble/geo_header.h"

#include "levels/rr/agring/geo_header.h"

#include "levels/rr/ag_killer_laser/geo_header.h"

#include "levels/rr/agboom/geo_header.h"

#include "levels/rr/agmoon/geo_header.h"

#include "levels/rr/agpillar2/collision_header.h"

#include "levels/rr/agpillar2/geo_header.h"

#include "levels/rr/agpillar3/geo_header.h"

#include "levels/rr/agpillar3/collision_header.h"

#include "levels/rr/endflames/geo_header.h"

#include "levels/rr/agtri/geo_header.h"

#include "levels/rr/agtri/collision_header.h"

#include "levels/rr/form1/geo_header.h"

#include "levels/rr/form2a/geo_header.h"

#include "levels/rr/form2/geo_header.h"

#include "levels/rr/form3/geo_header.h"

#include "levels/rr/lopalam/geo_header.h"

#endif
