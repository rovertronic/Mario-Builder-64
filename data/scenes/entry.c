#include <ultra64.h>
#include "sm64.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "data/scenes/menu/header.h"
#include "data/scenes/game/header.h"

#include "make_const_nonconst.h"

#include "config.h"

const LevelScript level_script_entry[] = {
    INIT_LEVEL(),
    SLEEP(/*frames*/ 2),
    BLACKOUT(/*active*/ FALSE),
    JUMP(/*target*/ level_intro_splash_screen),
    JUMP(/*target*/ level_script_entry),
};

const LevelScript level_script_entry_error_screen[] = {
    INIT_LEVEL(),
    SLEEP(/*frames*/ 2),
    BLACKOUT(/*active*/ FALSE),
    JUMP(/*target*/ level_intro_entry_error_screen),
};
