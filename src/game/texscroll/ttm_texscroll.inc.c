#include "levels/ttm/header.h"
#include "levels/ttm/texscroll.inc.c"
#include "levels/ttm/bean/texscroll.inc.c"
#include "levels/ttm/vflood/texscroll.inc.c"
void scroll_textures_ttm() {
	scroll_ttm();
	scroll_ttm_level_geo_bean();
	scroll_ttm_level_geo_vflood();
}
