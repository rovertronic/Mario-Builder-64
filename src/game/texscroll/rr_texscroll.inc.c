#include "levels/rr/header.h"
#include "levels/rr/texscroll.inc.c"
#include "levels/rr/rr_tube/texscroll.inc.c"
#include "levels/rr/staticflood/texscroll.inc.c"
#include "levels/rr/blood/texscroll.inc.c"
#include "levels/rr/palamedes/texscroll.inc.c"
#include "levels/rr/blood_particle/texscroll.inc.c"
#include "levels/rr/agcrack/texscroll.inc.c"
#include "levels/rr/agwall/texscroll.inc.c"
#include "levels/rr/agring/texscroll.inc.c"
#include "levels/rr/agmoon/texscroll.inc.c"
#include "levels/rr/endflames/texscroll.inc.c"
void scroll_textures_rr() {
	scroll_rr();
	scroll_rr_level_geo_rr_tube();
	scroll_rr_level_geo_staticflood();
	scroll_rr_level_geo_blood();
	scroll_rr_level_geo_palamedes();
	scroll_rr_level_geo_blood_particle();
	scroll_rr_level_geo_agcrack();
	scroll_rr_level_geo_agwall();
	scroll_rr_level_geo_agring();
	scroll_rr_level_geo_agmoon();
	scroll_rr_level_geo_endflames();
}
