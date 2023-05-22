#include "levels/bitfs/header.h"
#include "levels/bitfs/flip/texscroll.inc.c"
#include "levels/bitfs/movie3/texscroll.inc.c"
#include "levels/bitfs/movie4/texscroll.inc.c"
#include "levels/bitfs/movie5/texscroll.inc.c"
#include "levels/bitfs/texscroll.inc.c"
#include "levels/bitfs/movie6/texscroll.inc.c"
void scroll_textures_bitfs() {
	scroll_bitfs_level_geo_flip();
	scroll_bitfs_level_geo_movie3();
	scroll_bitfs_level_geo_movie4();
	scroll_bitfs_level_geo_movie5();
	scroll_bitfs();
	scroll_bitfs_level_geo_movie6();
}
