#include "levels/ccm/header.h"
#include "levels/ccm/texscroll.inc.c"
#include "levels/ccm/fan/texscroll.inc.c"
#include "levels/ccm/bone_plat/texscroll.inc.c"
#include "levels/ccm/bone_elevator/texscroll.inc.c"
#include "levels/ccm/executive/texscroll.inc.c"
void scroll_textures_ccm() {
	scroll_ccm();

	scroll_ccm_level_geo_fan();

	
	scroll_ccm_level_geo_bone_plat();

	scroll_ccm_level_geo_bone_elevator();

	scroll_ccm_level_geo_executive();
}
