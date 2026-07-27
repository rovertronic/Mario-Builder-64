#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "macros.h"
#include "types.h"
#include "src/game/game_init.h"
#include "mb64/file.h"

#include "make_const_nonconst.h"

#include "levels/menu/mbg/model.inc.c"

#include "levels/menu/bigpainting/model.inc.c"

FILINFO mb64_level_entries[MAX_FILES] = {0};
u16 mb64_level_entry_thumbnail[MAX_FILES][64][64] = {0};
