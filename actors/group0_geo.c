#include <ultra64.h>
#include "sm64.h"
#include "geo_commands.h"

#include "make_const_nonconst.h"

#include "common1.h"
#include "group0.h"

#include "bubble/geo.inc.c"
#include "walk_smoke/geo.inc.c"
#include "burn_smoke/geo.inc.c"
#include "stomp_smoke/geo.inc.c"
#include "water_wave/geo.inc.c"
#include "sparkle/geo.inc.c"
#include "water_splash/geo.inc.c"
#include "sparkle_animation/geo.inc.c"
#if SILHOUETTE
#define LAYER_OPAQUE_ORIG LAYER_OPAQUE
#define LAYER_ALPHA_ORIG LAYER_ALPHA
#undef LAYER_OPAQUE
#undef LAYER_ALPHA
#define LAYER_OPAQUE LAYER_SILHOUETTE_OPAQUE
#define LAYER_ALPHA  LAYER_SILHOUETTE_ALPHA
#include "mario/geo.inc.c"
#undef LAYER_OPAQUE
#undef LAYER_ALPHA
#define LAYER_OPAQUE LAYER_OPAQUE_ORIG
#define LAYER_ALPHA  LAYER_ALPHA_ORIG
#undef LAYER_OPAQUE_ORIG
#undef LAYER_ALPHA_OGIG
#else
#include "mario/geo.inc.c"
#endif
