#include "levels/wf/header.h"
#include "levels/wf/texscroll.inc.c"
#include "levels/wf/spingrass/texscroll.inc.c"
#include "levels/wf/flimsy_board/texscroll.inc.c"
#include "levels/wf/chainpole/texscroll.inc.c"
#include "levels/wf/horse_cart/texscroll.inc.c"
#include "levels/wf/horse_cart_w/texscroll.inc.c"
#include "levels/wf/Map2/texscroll.inc.c"
void scroll_textures_wf() {
	scroll_wf();

	scroll_wf_level_geo_spingrass();

	scroll_wf_level_geo_flimsy_board();

	scroll_wf_level_geo_chainpole();

	scroll_wf_level_geo_horse_cart();

	scroll_wf_level_geo_horse_cart_w();

	scroll_wf_level_dl_Map2();

}
