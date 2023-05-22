#ifndef DDD_HEADER_H
#define DDD_HEADER_H

#include "types.h"
#include "game/moving_texture.h"

// geo
extern const GeoLayout ddd_geo_000450[];
extern const GeoLayout ddd_geo_000478[];
extern const GeoLayout ddd_geo_0004A0[];
extern const GeoLayout ddd_geo_0004C0[];
extern const GeoLayout ddd_geo_000570[];

// leveldata
extern const f32 coinpath[][2][3];
extern const Gfx ddd_seg7_dl_07004D48[];
extern const Gfx ddd_seg7_dl_070057E8[];
extern const Gfx ddd_seg7_dl_07005C40[];
extern const Gfx ddd_seg7_dl_07005F78[];
extern const Gfx ddd_seg7_dl_07007408[];
extern const Gfx ddd_seg7_dl_07007CB8[];
extern const Gfx ddd_seg7_dl_07008C48[];
extern const Gfx ddd_seg7_dl_07008F80[];
extern const Gfx ddd_seg7_dl_07009030[];
extern const Gfx ddd_seg7_dl_07009120[];
extern const Gfx ddd_seg7_dl_07009208[];
extern const Gfx ddd_seg7_dl_0700AF10[];
extern const Gfx ddd_seg7_dl_0700B068[];
extern const Gfx ddd_seg7_dl_0700BAE0[];
extern const Gfx ddd_seg7_dl_0700CE48[];
extern const Gfx ddd_seg7_dl_0700D2A0[];
extern const Collision ddd_seg7_area_1_collision[];
extern const Collision ddd_seg7_area_2_collision[];
extern const MacroObject ddd_seg7_area_1_macro_objs[];
extern const MacroObject ddd_seg7_area_2_macro_objs[];
extern const Collision ddd_seg7_collision_submarine[];
extern const Collision ddd_seg7_collision_bowser_sub_door[];
extern const struct MovtexQuadCollection ddd_movtex_area1_water[];
extern const struct MovtexQuadCollection ddd_movtex_area2_water[];

// script
extern const LevelScript level_ddd_entry[];


#include "levels/ddd/header.inc.h"

#include "levels/ddd/thwompform/collision_header.h"

#include "levels/ddd/thwompform/geo_header.h"

#include "levels/ddd/banner/geo_header.h"

#include "levels/ddd/bannera/anim_header.h"

#include "levels/ddd/bewer/geo_header.h"

#include "levels/ddd/whplat/collision_header.h"

#include "levels/ddd/whplat/geo_header.h"

#include "levels/ddd/weakgrate/geo_header.h"

#include "levels/ddd/weakgrate/collision_header.h"

#include "levels/ddd/thwompking/geo_header.h"

#include "levels/ddd/thwompking/collision_header.h"

#include "levels/ddd/thwompqueen/geo_header.h"

#include "levels/ddd/thwompqueen/anim_header.h"

#include "levels/ddd/queenrock/geo_header.h"

#include "levels/ddd/thwompqueen/collision_header.h"

#include "levels/ddd/thwompgate/geo_header.h"

#include "levels/ddd/thwompgate/collision_header.h"

#include "levels/ddd/Map9/header.h"

#include "levels/ddd/thwompguard/geo_header.h"

#include "levels/ddd/thwompguard/collision_header.h"

#endif
