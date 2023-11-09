#ifndef CCM_HEADER_H
#define CCM_HEADER_H

#include "types.h"
#include "game/moving_texture.h"

// geo
extern const GeoLayout ccm_geo_0003D0[];
extern const GeoLayout ccm_geo_0003F0[];
extern const GeoLayout ccm_geo_00040C[];
extern const GeoLayout ccm_geo_00042C[];
extern const GeoLayout ccm_geo_00045C[];
extern const GeoLayout ccm_geo_000494[];
extern const GeoLayout ccm_geo_0004BC[];
extern const GeoLayout ccm_geo_0004E4[];
extern const GeoLayout ccm_geo_00051C[];
extern const GeoLayout ccm_geo_0005E8[];

extern const f32 ccm_frames[][2][3];

// leveldata
extern const Gfx ccm_seg7_dl_0700B090[];
extern const Gfx ccm_seg7_dl_0700B1D8[];
extern const Gfx ccm_seg7_dl_0700C380[];
extern const Gfx ccm_seg7_dl_0700D578[];
extern const Gfx ccm_seg7_dl_0700DDF0[];
extern const Gfx ccm_seg7_dl_0700E708[];
extern const Gfx ccm_seg7_dl_0700E970[];
extern const Gfx ccm_seg7_dl_0700F440[];
extern const Gfx ccm_seg7_dl_0700F650[];
extern const Gfx ccm_seg7_dl_0700F780[];
extern const Gfx ccm_seg7_dl_0700FB00[];
extern const Gfx ccm_seg7_dl_0700FD08[];
extern const Gfx ccm_seg7_dl_07010660[];
extern const Gfx ccm_seg7_dl_070109D0[];
extern const Gfx ccm_seg7_dl_07010B50[];
extern const Gfx ccm_seg7_dl_07010F28[];
extern const Gfx ccm_seg7_dl_070118B0[];
extern const Gfx ccm_seg7_dl_07012BD8[];
extern const Gfx ccm_seg7_dl_070136D0[];
extern const Gfx ccm_seg7_dl_07013870[];
extern const Collision ccm_seg7_area_1_collision[];
extern const MacroObject ccm_seg7_area_1_macro_objs[];
extern const Collision ccm_seg7_collision_ropeway_lift[];
extern const Trajectory ccm_seg7_trajectory_snowman[];
extern const Trajectory ccm_seg7_trajectory_ropeway_lift[];
extern const struct MovtexQuadCollection ccm_movtex_penguin_puddle_water[];
extern const Gfx ccm_seg7_dl_0701CE30[];
extern const Gfx ccm_seg7_dl_0701E558[];
extern const Gfx ccm_seg7_dl_0701E6B0[];
extern const Gfx ccm_seg7_dl_0701FC78[];
extern const Gfx ccm_seg7_dl_0701FD78[];
extern const Gfx ccm_seg7_dl_0701FE60[];
extern const Gfx ccm_seg7_dl_070207F0[];
extern const Collision ccm_seg7_area_2_collision[];
extern const MacroObject ccm_seg7_area_2_macro_objs[];
extern const Trajectory ccm_seg7_trajectory_penguin_race[];

// script
extern const LevelScript level_ccm_entry[];

#include "levels/ccm/header.inc.h"

#include "levels/ccm/fan/geo_header.h"

#include "levels/ccm/bone_plat/geo_header.h"

#include "levels/ccm/bone_plat/collision_header.h"

#include "levels/ccm/bone_elevator/geo_header.h"

#include "levels/ccm/bone_elevator/collision_header.h"

#include "levels/ccm/bone_train/geo_header.h"

#include "levels/ccm/bone_train/collision_header.h"

#include "levels/ccm/bonespin/geo_header.h"

#include "levels/ccm/bonespin/collision_header.h"

#include "levels/ccm/bonespin2/geo_header.h"

#include "levels/ccm/bonespin2/collision_header.h"

#include "levels/ccm/bonegate/geo_header.h"

#include "levels/ccm/bonegate/collision_header.h"

#include "levels/ccm/boneswapgate/collision_header.h"

#include "levels/ccm/boneswapgate/geo_header.h"

#include "levels/ccm/Map4/header.h"

#include "levels/ccm/corenode/geo_header.h"

#include "levels/ccm/nullbody/geo_header.h"

#include "levels/ccm/can/geo_header.h"

#include "levels/ccm/trashbag/geo_header.h"

#include "levels/ccm/puddlepoop/geo_header.h"

#include "levels/ccm/pipe_ccm/collision_header.h"

#include "levels/ccm/pipe1_ccm/geo_header.h"

#include "levels/ccm/pipe2_ccm/geo_header.h"

#include "levels/ccm/conv1_ccm/collision_header.h"

#include "levels/ccm/conv2_ccm/collision_header.h"

#include "levels/ccm/conv1_ccm/geo_header.h"

#include "levels/ccm/conv2_ccm/geo_header.h"

#include "levels/ccm/executive/collision_header.h"

#include "levels/ccm/executive/geo_header.h"

#include "levels/ccm/stencil/header.h"

#include "levels/ccm/ccm_sky/header.h"

#include "levels/ccm/cosmic_missile/geo_header.h"

#include "levels/ccm/conv1ccm/geo_header.h"

#include "levels/ccm/conv2ccm/geo_header.h"

#endif
