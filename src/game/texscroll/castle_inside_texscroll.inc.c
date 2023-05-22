#include "levels/castle_inside/header.h"
#include "levels/castle_inside/secret_books/texscroll.inc.c"
#include "levels/castle_inside/reflection_change/texscroll.inc.c"
#include "levels/castle_inside/fucking_mirror/texscroll.inc.c"
#include "levels/castle_inside/texscroll.inc.c"
#include "levels/castle_inside/showrunner_tv/texscroll.inc.c"
void scroll_textures_castle_inside() {
		scroll_castle_inside_level_geo_secret_books();

	scroll_castle_inside_level_geo_reflection_change();

	scroll_castle_inside_level_geo_fucking_mirror();

	scroll_castle_inside();

	scroll_castle_inside_level_geo_showrunner_tv();
}
