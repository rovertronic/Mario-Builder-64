#include <ultra64.h>
#include "sm64.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "levels/menu/header.h"
#include "levels/game/header.h"

#include "make_const_nonconst.h"

#include "config.h"

const LevelScript level_script_entry[] = {
    INIT_LEVEL(),
    SLEEP(/*frames*/ 2),
    BLACKOUT(/*active*/ FALSE),
#ifdef TEST_LEVEL
    SET_REG(/*value*/ TEST_LEVEL),
    EXIT_AND_EXECUTE_WITH_CODE(/*seg*/ SEGMENT_LEVEL_SCRIPT, _gameSegmentRomStart, _gameSegmentRomEnd, level_game_entry, _gameSegmentBssStart, _gameSegmentBssEnd),
#else
    SET_REG(/*value*/ 0),
    JUMP(/*target*/ level_intro_splash_screen),
#endif
    JUMP(/*target*/ level_script_entry),
};

const LevelScript level_script_entry_error_screen[] = {
    INIT_LEVEL(),
    SLEEP(/*frames*/ 2),
    BLACKOUT(/*active*/ FALSE),
    SET_REG(/*value*/ 0),
    JUMP(/*target*/ level_intro_entry_error_screen),
};
