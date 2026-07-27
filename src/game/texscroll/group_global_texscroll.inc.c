#include "actors/group_global.h"
#include "actors/group_btcm.h"
//#include "actors/chicken/texscroll.inc.c"
//#include "actors/egg/texscroll.inc.c"
//#include "actors/showrunner/texscroll.inc.c"
#include "actors/mario_btcm/texscroll.inc.c"
#include "actors/maker/texscroll.inc.c"
#include "actors/badge/texscroll.inc.c"
#include "actors/showrunner/texscroll.inc.c"
void scroll_textures_group_btcm() {
	scroll_actor_geo_showrunner();
	scroll_actor_geo_badge();
}

#include "actors/conveyor_slope/texscroll.inc.c"
#include "actors/conveyor_half/texscroll.inc.c"
#include "actors/conveyor/texscroll.inc.c"
#include "actors/conveyor_dslope/texscroll.inc.c"
void scroll_textures_group_global() {
	
	
	//

	
	//scroll_actor_geo_chicken();


	//scroll_actor_geo_egg();



		


	//scroll_actor_geo_showrunner();
	scroll_actor_geo_mario();
	scroll_actor_dl_maker();
	scroll_actor_geo_conveyor_slope();
	scroll_actor_geo_conveyor_half();
	scroll_actor_geo_conveyor();
	scroll_actor_geo_conveyor_dslope();
}
