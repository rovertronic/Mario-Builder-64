#include "levels/jrb/header.h"
#include "levels/jrb/texscroll.inc.c"
#include "levels/jrb/bigmine/texscroll.inc.c"
#include "levels/jrb/jrb_sky/texscroll.inc.c"
void scroll_textures_jrb() {
	scroll_jrb();

	scroll_jrb_level_geo_bigmine();
	scroll_jrb_level_dl_jrb_sky();
}
