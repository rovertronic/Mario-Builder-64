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
#include "mb64/menu/main.h"

#include "levels/scripts.h"

#include "make_const_nonconst.h"
#include "levels/menu/header.h"

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
     CALL(     /*arg*/ 0, /*func*/ lvl_mb64_main_menu_init),
    CALL_LOOP(/*arg*/ 0, /*func*/ lvl_mb64_main_menu_update),
    GET_OR_SET(/*op*/ OP_SET, /*var*/ VAR_CURR_SAVE_FILE_NUM),
    STOP_MUSIC(/*fadeOutTime*/ 0x00BE),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    SLEEP(/*frames*/ 30),
    CLEAR_LEVEL(),
    SLEEP_BEFORE_EXIT(/*frames*/ 1),
#endif // SKIP_FILE_SELECT
    FILESELECT_CHECK(/*op*/ OP_SET, /*var*/ VAR_CURR_SAVE_FILE_NUM),
    EXIT_AND_EXECUTE(/*seg*/ SEGMENT_GLOBAL_LEVEL_SCRIPT, _scriptsSegmentRomStart, _scriptsSegmentRomEnd, level_main_scripts_entry),
};

const LevelScript level_main_menu_entry_act_select_exit[] = {
    EXIT(),
};

const LevelScript level_main_menu_entry_act_select[] = {
    CALL(/*arg*/ 0, /*func*/ lvl_set_current_level),
    JUMP_IF(/*op*/ OP_EQ, /*arg*/ FALSE, (level_main_menu_entry_act_select_exit)),
};
