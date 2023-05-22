#include "levels/bits/header.h"
#include "levels/bits/bits_stairs/texscroll.inc.c"
#include "levels/bits/texscroll.inc.c"
#include "levels/bits/tvshop/texscroll.inc.c"
void scroll_textures_bits() {
	scroll_bits_level_geo_bits_stairs();
	scroll_bits();
	scroll_bits_level_geo_tvshop();
}
