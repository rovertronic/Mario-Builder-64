#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/area.h"
#include "game/level_update.h"
#include "menu/title_screen.h"

#include "levels/scripts.h"
#include "levels/menu/header.h"

#include "actors/common0.h"
#include "actors/common1.h"

#include "make_const_nonconst.h"
#include "levels/intro/header.h"
#include "farcall.h"

#include "config.h"
#include "game/print.h"

#include "game/object_list_processor.h"

const LevelScript level_intro_entry_error_screen[] = {
    INIT_LEVEL(),
    FIXED_LOAD(/*loadAddr*/ _menu_segSegmentStart, /*romStart*/ _menu_segSegmentRomStart, /*romEnd*/ _menu_segSegmentRomEnd),
    LOAD_YAY0(/*seg*/ 0x07, _intro_segment_7SegmentRomStart, _intro_segment_7SegmentRomEnd),
    ALLOC_LEVEL_POOL(),

    AREA(/*index*/ 1, intro_geo_error_screen),
	END_AREA(),

    FREE_LEVEL_POOL(),
    LOAD_AREA(/*area*/ 1),
    SLEEP(/*frames*/ 32767),

    UNLOAD_AREA(/*area*/ 1),
    CLEAR_LEVEL(),
    SLEEP(/*frames*/ 1),
    EXIT_AND_EXECUTE(/*seg*/ 0x14, _introSegmentRomStart, _introSegmentRomEnd, level_intro_entry_error_screen),
};

const LevelScript level_intro_splash_screen[] = {
#ifdef SKIP_TITLE_SCREEN
    EXIT_AND_EXECUTE_WITH_CODE(/*seg*/ SEGMENT_MENU_INTRO, _introSegmentRomStart, _introSegmentRomEnd, level_intro_title_reset, _introSegmentBssStart, _introSegmentBssEnd),
#endif
    INIT_LEVEL(),
    LOAD_MENU_SEG(),
    LOAD_BEHAVIOR_DATA(),
    LOAD_LEVEL_DATA(intro),

    // Load "Super Mario 64" logo
    SLEEP(/*frames*/ 16),
    ALLOC_LEVEL_POOL(),
    AREA(/*index*/ 1, intro_geo_splash_screen),
    END_AREA(),
    FREE_LEVEL_POOL(),

    // Start animation
    LOAD_AREA(/*area*/ 1),

    // SLEEP(/*frames*/ 65),
    SET_MENU_MUSIC(/*seq*/ SEQ_SOUND_PLAYER),
    CALL(/*arg*/ LVL_INTRO_PLAY_ITS_A_ME_MARIO, /*func*/ lvl_intro_update),
    SLEEP(/*frames*/ 75),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0x00, 0x00, 0x00),
    SLEEP(/*frames*/ 16),

    UNLOAD_AREA(/*area*/ 1),
    CLEAR_LEVEL(),
    SLEEP(/*frames*/ 2),
    EXIT_AND_EXECUTE_WITH_CODE(/*seg*/ SEGMENT_MENU_INTRO, _introSegmentRomStart, _introSegmentRomEnd, level_intro_title_reset, _introSegmentBssStart, _introSegmentBssEnd),
};

const LevelScript level_intro_title_reset_bypass[] = {
    PUSH_POOL(),
    PUSH_POOL(),
    JUMP(script_intro_file_select), // go to ingame
};

const LevelScript level_intro_title_reset[] = {
    JUMP(level_intro_title_reset_bypass),
};

const LevelScript level_intro_game_over_reset[] = {
    JUMP(level_intro_title_reset),
};

const LevelScript level_intro_entry_level_select[] = {
    INIT_LEVEL(),
    LOAD_BEHAVIOR_DATA(),
    LOAD_TITLE_SCREEN_BG(),
    LOAD_YAY0(/*seg*/ SEGMENT_LEVEL_DATA, _debug_level_select_yay0SegmentRomStart, _debug_level_select_yay0SegmentRomEnd),
    FIXED_LOAD(/*loadAddr*/ _menu_segSegmentStart, /*romStart*/ _menu_segSegmentRomStart, /*romEnd*/ _menu_segSegmentRomEnd),
    ALLOC_LEVEL_POOL(),

    AREA(/*index*/ 1, intro_geo_debug_level_select),
    END_AREA(),

    FREE_LEVEL_POOL(),
    LOAD_AREA(/*area*/ 1),
    SET_MENU_MUSIC(/*seq*/ SEQ_MENU_TITLE_SCREEN),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_FROM_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    SLEEP(/*frames*/ 16),
    CALL_LOOP(/*arg*/ LVL_INTRO_LEVEL_SELECT, /*func*/ lvl_intro_update),
    JUMP_IF(/*op*/ OP_EQ, /*arg*/ LEVEL_RESTART_GAME, script_intro_splash_screen),
    JUMP(script_intro_main_level_entry_stop_music),
};

// These should be static, but C doesn't allow non-sized forward declarations of static arrays

const LevelScript script_intro_file_select[] = {
    STOP_MUSIC(/*fadeOutTime*/ 0x00BE),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    SLEEP(/*frames*/ 16),
    CLEAR_LEVEL(),
    SLEEP(/*frames*/ 2),
    SET_REG(/*value*/ START_LEVEL),
    EXIT_AND_EXECUTE(/*seg*/ SEGMENT_MENU_INTRO, _menuSegmentRomStart, _menuSegmentRomEnd, level_main_menu_entry_file_select),
};

const LevelScript script_intro_level_select[] = {
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    SLEEP(/*frames*/ 16),
    CLEAR_LEVEL(),
    SLEEP(/*frames*/ 2),
    EXIT_AND_EXECUTE_WITH_CODE(/*seg*/ SEGMENT_MENU_INTRO, _introSegmentRomStart, _introSegmentRomEnd, level_intro_entry_level_select, _introSegmentBssStart, _introSegmentBssEnd),
};

const LevelScript script_intro_main_level_entry_stop_music[] = {
    STOP_MUSIC(/*fadeOutTime*/ 0x00BE),
    JUMP(script_intro_main_level_entry),
};

const LevelScript script_intro_main_level_entry[] = {
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    SLEEP(/*frames*/ 16),
    CLEAR_LEVEL(),
    SLEEP(/*frames*/ 2),
    EXIT_AND_EXECUTE(/*seg*/ SEGMENT_GLOBAL_LEVEL_SCRIPT, _scriptsSegmentRomStart, _scriptsSegmentRomEnd, level_main_scripts_entry),
};

const LevelScript script_intro_splash_screen[] = {
    STOP_MUSIC(/*fadeOutTime*/ 0x00BE),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0x00, 0x00, 0x00),
    SLEEP(/*frames*/ 16),
    CLEAR_LEVEL(),
    SLEEP(/*frames*/ 2),
    EXIT_AND_EXECUTE_WITH_CODE(/*seg*/ SEGMENT_MENU_INTRO, _introSegmentRomStart, _introSegmentRomEnd, level_intro_splash_screen, _introSegmentBssStart, _introSegmentBssEnd),
};
