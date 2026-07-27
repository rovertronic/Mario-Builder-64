#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "config/config_cutscenes.h"

#include "game/area.h"
#include "game/level_update.h"
#include "menu/title_screen.h"
#include "mb64/menu/main.h"

#include "make_const_nonconst.h"
#include "levels/menu/header.h"
#include "levels/game/header.h"

#include "config.h"

const LevelScript level_intro_entry_error_screen[] = {
    INIT_LEVEL(),
    FIXED_LOAD(/*loadAddr*/ _menu_segSegmentStart, /*romStart*/ _menu_segSegmentRomStart, /*romEnd*/ _menu_segSegmentRomEnd),
    LOAD_LEVEL_DATA(menu),
    ALLOC_LEVEL_POOL(),

    AREA(/*index*/ 1, intro_geo_error_screen),
    END_AREA(),

    FREE_LEVEL_POOL(),
    LOAD_AREA(/*area*/ 1),
    SLEEP(/*frames*/ 32767),

    UNLOAD_AREA(/*area*/ 1),
    CLEAR_LEVEL(),
    SLEEP(/*frames*/ 1),
    EXIT_AND_EXECUTE_WITH_CODE(/*seg*/ SEGMENT_LEVEL_SCRIPT, _menuSegmentRomStart, _menuSegmentRomEnd, level_intro_entry_error_screen, _menuSegmentBssStart, _menuSegmentBssEnd),
};

const LevelScript level_intro_splash_screen[] = {
#ifdef SKIP_TITLE_SCREEN
    JUMP(level_intro_title_reset),
#endif
    INIT_LEVEL(),
    LOAD_MENU_SEG(),
    LOAD_BEHAVIOR_DATA(),
    LOAD_LEVEL_DATA(menu),

    SLEEP(/*frames*/ 16),
    ALLOC_LEVEL_POOL(),
    AREA(/*index*/ 1, intro_geo_splash_screen),
    END_AREA(),
    FREE_LEVEL_POOL(),

    LOAD_AREA(/*area*/ 1),

    SET_MENU_MUSIC(/*seq*/ SEQ_SOUND_PLAYER),
    CALL(/*arg*/ LVL_INTRO_PLAY_ITS_A_ME_MARIO, /*func*/ lvl_intro_update),
    SLEEP(/*frames*/ 75),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0x00, 0x00, 0x00),
    SLEEP(/*frames*/ 16),

    UNLOAD_AREA(/*area*/ 1),
    CLEAR_LEVEL(),
    SLEEP(/*frames*/ 2),
    JUMP(level_intro_title_reset),
};

const LevelScript level_intro_title_reset[] = {
    STOP_MUSIC(/*fadeOutTime*/ 0x00BE),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    SLEEP(/*frames*/ 16),
    SET_REG(/*value*/ START_LEVEL),
    JUMP(level_main_menu_entry_file_select),
};

const LevelScript level_main_menu_entry_file_select[] = {
#ifndef SKIP_FILE_SELECT
    INIT_LEVEL(),
    LOAD_MENU_SEG(),
    LOAD_LEVEL_DATA(menu),
    LOAD_BEHAVIOR_DATA(),
    ALLOC_LEVEL_POOL(),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_MAIN_MENU, mbg_geo),

    AREA(/*index*/ 1, geo_menu_file_select_strings_and_menu_cursor),
        OBJECT(/*model*/ MODEL_MAKER_MAIN_MENU, /*pos*/ 0, 0, 0, /*angle*/ 0, 0, 0, /*behParam*/ BP(0x04, 0x00, 0x00, 0x00), /*beh*/ bhvYellowBackgroundInMenu),
    END_AREA(),

    FREE_LEVEL_POOL(),
    LOAD_AREA(/*area*/ 1),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_FROM_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    CALL(/*arg*/ 0, /*func*/ lvl_mb64_main_menu_init),
    CALL_LOOP(/*arg*/ 0, /*func*/ lvl_mb64_main_menu_update),
    GET_OR_SET(/*op*/ OP_SET, /*var*/ VAR_CURR_SAVE_FILE_NUM),
    STOP_MUSIC(/*fadeOutTime*/ 0x00BE),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    SLEEP(/*frames*/ 30),
    CLEAR_LEVEL(),
    SLEEP_BEFORE_EXIT(/*frames*/ 1),
#endif // SKIP_FILE_SELECT
    FILESELECT_CHECK(/*op*/ OP_SET, /*var*/ VAR_CURR_SAVE_FILE_NUM),
    EXIT_AND_EXECUTE_WITH_CODE(/*seg*/ SEGMENT_LEVEL_SCRIPT, _gameSegmentRomStart, _gameSegmentRomEnd, level_game_entry, _gameSegmentBssStart, _gameSegmentBssEnd),
};
