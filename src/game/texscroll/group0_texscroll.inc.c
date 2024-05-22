#include "actors/group0.h"
#include "actors/group14.h"
////#include "actors/ring/texscroll.inc.c"
//#include "actors/chicken/texscroll.inc.c"
// #include "actors/token/texscroll.inc.c"
//#include "actors/egg/texscroll.inc.c"
// #include "actors/arrow/texscroll.inc.c"
// #include "actors/BadgeSelect/texscroll.inc.c"
//#include "actors/snakeblock2/texscroll.inc.c"
//#include "actors/snakeblock3/texscroll.inc.c"
//#include "actors/shopselect/texscroll.inc.c"
//#include "actors/shopgui/texscroll.inc.c"
//#include "actors/showrunner/texscroll.inc.c"
//#include "actors/executive_/texscroll.inc.c"
//#include "actors/executive_loom_/texscroll.inc.c"
//#include "actors/tvhead/texscroll.inc.c"
//#include "actors/ocean_ttc/texscroll.inc.c"
#include "actors/mario/texscroll.inc.c"
#include "actors/maker/texscroll.inc.c"
#include "actors/badge/texscroll.inc.c"
#include "actors/showrunner/texscroll.inc.c"
void scroll_textures_group14() {
	scroll_actor_geo_showrunner();
}

#include "actors/conveyor_slope/texscroll.inc.c"
#include "actors/conveyor_half/texscroll.inc.c"
#include "actors/conveyor/texscroll.inc.c"
void scroll_textures_group0() {
	
	
	//
	//scroll_actor_geo_ring();

	
	//scroll_actor_geo_chicken();

	// scroll_actor_geo_token();

	//scroll_actor_geo_egg();

	// scroll_actor_dl_arrow();

	// scroll_actor_dl_BadgeSelect();

		
	//scroll_actor_geo_snakeblock2();

	//scroll_actor_geo_snakeblock3();

	//scroll_actor_dl_shopselect();
	//scroll_actor_dl_shopgui();
	//scroll_actor_geo_showrunner();
	//scroll_actor_dl_executive_();
	//scroll_actor_dl_executive_loom_();
	//scroll_actor_geo_tvhead();
	scroll_actor_geo_mario();
	scroll_actor_dl_maker();
	scroll_actor_geo_badge();
		scroll_actor_geo_conveyor_slope();
	scroll_actor_geo_conveyor_half();
	scroll_actor_geo_conveyor();
}
