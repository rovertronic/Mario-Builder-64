#include "src/game/envfx_snow.h"

const GeoLayout secret_books_geo[] = {
   GEO_CULLING_RADIUS(800),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, secret_books_Secret_Book_mesh),
   GEO_CLOSE_NODE(),

   GEO_END(),
};
