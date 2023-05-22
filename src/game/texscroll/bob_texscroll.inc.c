#include "levels/bob/header.h"
#include "levels/bob/texscroll.inc.c"
#include "levels/bob/Spewer/texscroll.inc.c"

#include "levels/bob/Map1/texscroll.inc.c"
void scroll_textures_bob() {
	scroll_actor_dl_spewer();
	scroll_bob();

	scroll_bob_level_dl_Map1();

}
