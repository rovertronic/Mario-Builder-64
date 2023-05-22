#include "levels/wdw/header.h"
#include "levels/wdw/texscroll.inc.c"
#include "levels/wdw/movie_1/texscroll.inc.c"
#include "levels/wdw/theater_sky/texscroll.inc.c"
#include "levels/wdw/movie_2/texscroll.inc.c"
#include "levels/wdw/ferris/texscroll.inc.c"
#include "levels/wdw/movie8/texscroll.inc.c"
#include "levels/wdw/movie_9/texscroll.inc.c"
#include "levels/wdw/robozo2/texscroll.inc.c"
void scroll_textures_wdw() {
	scroll_wdw();
	scroll_wdw_level_geo_movie_1();
	scroll_wdw_level_dl_theater_sky();
	scroll_wdw_level_geo_movie_2();
	scroll_wdw_level_geo_ferris();
	scroll_wdw_level_geo_movie8();
	scroll_wdw_level_geo_movie_9();
	scroll_wdw_level_geo_robozo2();
}
