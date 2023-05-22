#include "levels/sl/header.h"
#include "levels/sl/texscroll.inc.c"
#include "levels/sl/server_acid_fern/texscroll.inc.c"
#include "levels/sl/robot/texscroll.inc.c"
void scroll_textures_sl() {
	scroll_sl();
	scroll_sl_level_geo_server_acid_fern();
	scroll_sl_level_geo_robot();
}
