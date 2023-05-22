#include "levels/bbh/header.h"
#include "levels/bbh/texscroll.inc.c"
#include "levels/bbh/barell/texscroll.inc.c"
#include "levels/bbh/iceberg/texscroll.inc.c"
#include "levels/bbh/ship_elevator/texscroll.inc.c"
#include "levels/bbh/ship_elevator_rope/texscroll.inc.c"
#include "levels/bbh/ship_elevator_pulley/texscroll.inc.c"
#include "levels/bbh/GhostBoard/texscroll.inc.c"
#include "levels/bbh/iceberg_LOD/texscroll.inc.c"

#include "levels/bbh/lightning/texscroll.inc.c"
void scroll_textures_bbh() {
	scroll_bbh();

	scroll_bbh_level_geo_barell();

	scroll_bbh_level_geo_iceberg();

	scroll_bbh_level_geo_ship_elevator();

	scroll_bbh_level_geo_ship_elevator_rope();

	scroll_bbh_level_geo_ship_elevator_pulley();

	scroll_bbh_level_geo_GhostBoard();

	scroll_bbh_level_geo_iceberg_LOD();


	scroll_bbh_level_geo_lightning();

}
