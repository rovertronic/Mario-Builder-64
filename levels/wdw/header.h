#ifndef WDW_HEADER_H
#define WDW_HEADER_H

#include "types.h"
#include "game/moving_texture.h"

// geo
extern const GeoLayout wdw_geo_000580[];
extern const GeoLayout wdw_geo_000598[];
extern const GeoLayout wdw_geo_0005C0[];
extern const GeoLayout wdw_geo_0005E8[];
extern const GeoLayout wdw_geo_000610[];
extern const GeoLayout wdw_geo_000628[];
extern const GeoLayout wdw_geo_000640[];
extern const GeoLayout wdw_geo_000658[];
extern const GeoLayout wdw_geo_000724[];

// leveldata
extern const Gfx wdw_seg7_dl_07009AB0[];
extern const Gfx wdw_seg7_dl_0700A138[];
extern const Gfx wdw_seg7_dl_07011E48[];
extern const Gfx wdw_seg7_dl_07012258[];
extern const Gfx wdw_seg7_dl_07012798[];
extern const Gfx wdw_seg7_dl_07012908[];
extern const Gfx wdw_seg7_dl_07012B90[];
extern const Gfx wdw_seg7_dl_07012E88[];
extern const Gfx wdw_seg7_dl_070131B8[];
extern const Gfx wdw_seg7_dl_07013490[];
extern const Gfx wdw_seg7_dl_07013B70[];
extern const Gfx wdw_seg7_dl_07013E40[];
extern const Gfx wdw_seg7_dl_070140E0[];
extern const Collision wdw_seg7_area_1_collision[];
extern const MacroObject wdw_seg7_area_1_macro_objs[];
extern const Collision wdw_seg7_area_2_collision[];
extern const MacroObject wdw_seg7_area_2_macro_objs[];
extern const Collision wdw_seg7_collision_square_floating_platform[];
extern const Collision wdw_seg7_collision_arrow_lift[];
extern const Collision wdw_seg7_collision_070184C8[];
extern const Collision wdw_seg7_collision_hidden_platform[];
extern const Collision wdw_seg7_collision_express_elevator_platform[];
extern const Collision wdw_seg7_collision_rect_floating_platform[];
extern const Collision wdw_seg7_collision_rotating_platform[];
extern const struct MovtexQuadCollection wdw_movtex_area1_water[];
extern const struct MovtexQuadCollection wdw_movtex_area2_water[];

// script
extern const LevelScript level_wdw_entry[];


#include "levels/wdw/header.inc.h"

#include "levels/wdw/projector/geo_header.h"

#include "levels/wdw/projector/collision_header.h"

#include "levels/wdw/movie_1/collision_header.h"

#include "levels/wdw/movie_1/geo_header.h"

#include "levels/wdw/projector_handle/geo_header.h"

#include "levels/wdw/theater_sky/header.h"

#include "levels/wdw/movie_2/geo_header.h"

#include "levels/wdw/movie_2/collision_header.h"

#include "levels/wdw/cone/geo_header.h"

#include "levels/wdw/balloon/geo_header.h"

#include "levels/wdw/stopsign/geo_header.h"

#include "levels/wdw/streetlight/geo_header.h"

#include "levels/wdw/ferris/geo_header.h"

#include "levels/wdw/ferriscart/geo_header.h"

#include "levels/wdw/ferriscart/collision_header.h"

#include "levels/wdw/press/geo_header.h"

#include "levels/wdw/press/collision_header.h"

#include "levels/wdw/girl/geo_header.h"

#include "levels/wdw/movie8/geo_header.h"

#include "levels/wdw/movie_8/collision_header.h"

#include "levels/wdw/movie_9/collision_header.h"

#include "levels/wdw/movie_9/geo_header.h"

#include "levels/wdw/star_sign/geo_header.h"

#include "levels/wdw/cobie2/anim_header.h"

#include "levels/wdw/cobie2/geo_header.h"

#include "levels/wdw/Map11/header.h"

#include "levels/wdw/moleman2/anim_header.h"

#include "levels/wdw/moleman2/geo_header.h"

#include "levels/wdw/edward2/geo_header.h"

#include "levels/wdw/robozo2/geo_header.h"

#include "levels/wdw/robozo2/anim_header.h"

#endif
