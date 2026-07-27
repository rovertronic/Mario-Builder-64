#include <ultra64.h>
#include "sm64.h"
#include "game/level_update.h"
#include "level_commands.h"
#include "game/area.h"

#include "make_const_nonconst.h"

#include "segment_symbols.h"

#include "actors/group_global.h"
#include "actors/group_btcm.h"
#include "actors/group_vanilla.h"
#include "model_ids.h"
#include "mb64/file.h"

#include "levels/menu/header.h"
#include "levels/intro/header.h"

#include "level_headers.h"

#include "level_table.h"

#define STUB_LEVEL(_0, _1, _2, _3, _4, _5, _6, _7, _8)
#define DEFINE_LEVEL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) + 3
static const LevelScript script_exec_level_table[2
  #include "level_defines.h"
];
#undef DEFINE_LEVEL
#undef STUB_LEVEL

static const LevelScript goto_intro_splash_screen[6];
static const LevelScript goto_ending[6];
static const LevelScript goto_title_reset[6];
static const LevelScript goto_game_over_reset[6];
static const LevelScript goto_debug_level_select[6];

#define STUB_LEVEL(_0, _1, _2, _3, _4, _5, _6, _7, _8)
#define DEFINE_LEVEL(_0, _1, _2, folder, _4, _5, _6, _7, _8, _9, _10) static const LevelScript script_exec_ ## folder [6 + 1];

#include "level_defines.h"

#undef DEFINE_LEVEL
#undef STUB_LEVEL

const LevelScript level_main_scripts_entry[] = {
    LOAD_RAW_WITH_CODE( /*seg*/ SEGMENT_BEHAVIOR_DATA,    _behaviorSegmentRomStart,     _behaviorSegmentRomEnd,   _behaviorSegmentBssStart,     _behaviorSegmentBssEnd),
    CALL(/*arg*/ 0, /*func*/ lvl_init_from_save_file),
    LOOP_BEGIN(),
        EXECUTE(/*seg*/ SEGMENT_MENU_INTRO, _menuSegmentRomStart, _menuSegmentRomEnd, level_main_menu_entry_act_select),
        JUMP_LINK(script_exec_level_table),
        SLEEP(/*frames*/ 1),
    LOOP_UNTIL(/*op*/ OP_LT, /*arg*/ WARP_SPECIAL_NONE),
    JUMP_IF(   /*op*/ OP_EQ, /*arg*/ WARP_SPECIAL_ENDING,              goto_ending),
    JUMP_IF(   /*op*/ OP_EQ, /*arg*/ WARP_SPECIAL_TITLE_RESET,  goto_title_reset),
    JUMP_IF(   /*op*/ OP_EQ, /*arg*/ WARP_SPECIAL_GAME_OVER_RESET,    goto_game_over_reset),
    JUMP_IF(   /*op*/ OP_EQ, /*arg*/ WARP_SPECIAL_INTRO_SPLASH_SCREEN, goto_intro_splash_screen),
    JUMP_IF(   /*op*/ OP_EQ, /*arg*/ WARP_SPECIAL_LEVEL_SELECT,        goto_debug_level_select),
};

static const LevelScript goto_intro_splash_screen[] = {
    EXIT_AND_EXECUTE_WITH_CODE(/*seg*/ SEGMENT_MENU_INTRO, _introSegmentRomStart, _introSegmentRomEnd, level_intro_splash_screen, _introSegmentBssStart, _introSegmentBssEnd),
};

static const LevelScript goto_title_reset[] = {
    EXIT_AND_EXECUTE_WITH_CODE(/*seg*/ SEGMENT_MENU_INTRO, _introSegmentRomStart, _introSegmentRomEnd, level_intro_title_reset, _introSegmentBssStart, _introSegmentBssEnd),
};

static const LevelScript goto_game_over_reset[] = {
    EXIT_AND_EXECUTE_WITH_CODE(/*seg*/ SEGMENT_MENU_INTRO, _introSegmentRomStart, _introSegmentRomEnd, level_intro_game_over_reset, _introSegmentBssStart, _introSegmentBssEnd),
};

static const LevelScript goto_debug_level_select[] = {
    EXIT_AND_EXECUTE_WITH_CODE(/*seg*/ SEGMENT_MENU_INTRO, _introSegmentRomStart, _introSegmentRomEnd, level_intro_entry_level_select, _introSegmentBssStart, _introSegmentBssEnd),
};

#define STUB_LEVEL(_0, _1, _2, _3, _4, _5, _6, _7, _8)

#define DEFINE_LEVEL(_0, levelenum, _2, folder, _4, _5, _6, _7, _8, _9, _10) JUMP_IF(OP_EQ, levelenum, script_exec_ ## folder),

static const LevelScript script_exec_level_table[] = {
    GET_OR_SET(/*op*/ OP_GET, /*var*/ VAR_CURR_LEVEL_NUM),
    #include "levels/level_defines.h"
    EXIT(),
};
#undef DEFINE_LEVEL

#define DEFINE_LEVEL(_0, _1, _2, folder, _4, _5, _6, _7, _8, _9, _10) \
static const LevelScript script_exec_ ## folder [] = { \
    EXECUTE_WITH_CODE(SEGMENT_LEVEL_SCRIPT, _ ## folder ## SegmentRomStart, _ ## folder ## SegmentRomEnd, level_ ## folder ## _entry, _ ## folder ## SegmentBssStart, _ ## folder ## SegmentBssEnd), \
    RETURN(), \
};

#include "levels/level_defines.h"
#undef STUB_LEVEL
#undef DEFINE_LEVEL

const LevelScript script_func_mb64_global[] = {
    LOAD_MODEL_FROM_GEO(MODEL_SMOKE,                   smoke_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MONEYBAG,                moneybag_geo),
    LOAD_MODEL_FROM_GEO(MODEL_NOTEBLOCK,               noteblock_geo),
    LOAD_MODEL_FROM_GEO(MODEL_SPARKLES,                sparkles_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BUBBLE,                  bubble_geo),
    LOAD_MODEL_FROM_GEO(MODEL_SMALL_WATER_SPLASH,      small_water_splash_geo),
    LOAD_MODEL_FROM_GEO(MODEL_IDLE_WATER_WAVE,         idle_water_wave_geo),
    LOAD_MODEL_FROM_GEO(MODEL_WATER_SPLASH,            water_splash_geo),
    LOAD_MODEL_FROM_GEO(MODEL_WAVE_TRAIL,              wave_trail_geo),
    LOAD_MODEL_FROM_GEO(MODEL_YELLOW_COIN,             yellow_coin_geo),
    LOAD_MODEL_FROM_GEO(MODEL_STAR,                    star_geo),
    LOAD_MODEL_FROM_GEO(MODEL_TRANSPARENT_STAR,        transparent_star_geo),
    LOAD_MODEL_FROM_GEO(MODEL_WOODEN_SIGNPOST,         wooden_signpost_geo),
    LOAD_MODEL_FROM_DL( MODEL_WHITE_PARTICLE_SMALL,    white_particle_small_dl, LAYER_OCCLUDE_SILHOUETTE_ALPHA),
    LOAD_MODEL_FROM_GEO(MODEL_RED_FLAME,               red_flame_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BLUE_FLAME,              blue_flame_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BURN_SMOKE,              burn_smoke_geo),
    LOAD_MODEL_FROM_GEO(MODEL_LEAVES,                  leaves_geo),
    LOAD_MODEL_FROM_GEO(MODEL_PURPLE_MARBLE,           purple_marble_geo),
    LOAD_MODEL_FROM_GEO(MODEL_SPARKLES_ANIMATION,      sparkles_animation_geo),
    LOAD_MODEL_FROM_DL( MODEL_SAND_DUST,               sand_seg3_dl_particle,   LAYER_OCCLUDE_SILHOUETTE_ALPHA),
    LOAD_MODEL_FROM_DL( MODEL_PEBBLE,                  pebble_seg3_dl_0301CB00, LAYER_OCCLUDE_SILHOUETTE_ALPHA),
    LOAD_MODEL_FROM_GEO(MODEL_MIST,                    mist_geo),
    LOAD_MODEL_FROM_GEO(MODEL_WHITE_PUFF,              white_puff_geo),
    LOAD_MODEL_FROM_DL( MODEL_WHITE_PARTICLE_DL,       white_particle_dl,       LAYER_OCCLUDE_SILHOUETTE_ALPHA),
    LOAD_MODEL_FROM_GEO(MODEL_WHITE_PARTICLE,          white_particle_geo),
    LOAD_MODEL_FROM_GEO(MODEL_YELLOW_COIN_NO_SHADOW,   yellow_coin_no_shadow_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BLUE_COIN,               blue_coin_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BLUE_COIN_NO_SHADOW,     blue_coin_no_shadow_geo),
    LOAD_MODEL_FROM_GEO(MODEL_RED_FLAME_SHADOW,        red_flame_shadow_geo),
    LOAD_MODEL_FROM_GEO(MODEL_RED_COIN,                red_coin_geo),
    LOAD_MODEL_FROM_GEO(MODEL_RED_COIN_NO_SHADOW,      red_coin_no_shadow_geo),
    LOAD_MODEL_FROM_GEO(MODEL_NUMBER,                  number_geo),
    LOAD_MODEL_FROM_GEO(MODEL_EXPLOSION,               explosion_geo),
    LOAD_MODEL_FROM_GEO(MODEL_DIRT_ANIMATION,          dirt_animation_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CARTOON_STAR,            cartoon_star_geo),
    LOAD_MODEL_FROM_GEO(MODEL_SB,                      sb_cube_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_TREE_1,            bubbly_tree_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_TREE_2,            palm_tree_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_TREE_3,            spiky_tree_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_TREE_4,            snow_tree_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_TREE_5,            farm_tree_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_TREE_6,            dead_tree_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_BOUNDARY,          lev_edge_geo),
    LOAD_MODEL_FROM_GEO(MODEL_SPAWN,                   spawn_geo),
    LOAD_MODEL_FROM_GEO(MODEL_WHOMP_MAKER,             whomp_geo),
    LOAD_MODEL_FROM_GEO(MODEL_THWOMP_MAKER,            thwomp_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BILL_MAKER,              bullet_bill_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BILL_MAKER_2,            blaster_geo),
    LOAD_MODEL_FROM_GEO(MODEL_LAKITU_MAKER,            enemy_lakitu_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_SNUFIT,            snufit_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_BOO,               boo_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_MRI,               mr_i_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_MRI_2,             mr_i_iris_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_PLANT,             piranha_plant_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_SPINDRIFT,         spindrift_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_BLIZZARD,          mr_blizzard_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_HEAVEHO,           heave_ho_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CHILL_BULLY,             chilly_chief_geo),
    LOAD_MODEL_FROM_GEO(MODEL_SPINY_BALL,              spiny_ball_geo),
    LOAD_MODEL_FROM_GEO(MODEL_SPINY,                   spiny_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_SCUTTLEBUG,        scuttlebug_geo),
    LOAD_MODEL_FROM_GEO(MODEL_KOOPA_WITH_SHELL,        koopa_with_shell_geo),
    LOAD_MODEL_FROM_GEO(MODEL_KOOPA_WITHOUT_SHELL,     koopa_without_shell_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_FIREBAR,           spooner_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_GRINDEL,           ssl_geo_000734),
    LOAD_MODEL_FROM_GEO(MODEL_LOOPINGP,                loopingp_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BULLY,                   bully_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BULLY_BOSS,              bully_boss_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CULL_MARKER,             new_cull_marker_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_MOTOS,             RCP_HmsEnemymotos_basedata_A),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_SKEETER,           skeeter_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_FLAMETHROWER,      gooner_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_POKEY_HEAD,        pokey_head_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_POKEY_BODY,        pokey_body_part_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_TIMEDBOX,          timedbox_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_BUTTON,            onoffswitch_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_BLOCK_OFF,         onoffblock1_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_BLOCK_ON,          onoffblock2_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_DIAMOND,           wdw_geo_0005C0),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_WOODPLAT,          woodplat_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_RFBOX,             rfbox_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_FATPLAT,           fatplat_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_CONVEYOR,          conveyor_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_CONVEYOR_HALF,     conveyor_half_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_CONVEYOR_SLOPE,    conveyor_slope_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_CONVEYOR_DSLOPE,   conveyor_dslope_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_IMBUE,             imbue_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_IMBUE_STAR,        imbues_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_IMBUE_COIN,        imbuec_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_IMBUE_TRIGGER,     imbuet_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BLUE_COIN_SWITCH,        blue_coin_switch_geo),
    LOAD_MODEL_FROM_GEO(MODEL_AMP,                     dAmpGeo),
    LOAD_MODEL_FROM_GEO(MODEL_PURPLE_SWITCH,           purple_switch_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CHECKERBOARD_PLATFORM,   checkerboard_platform_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BREAKABLE_BOX,           breakable_box_no_shadow_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BREAKABLE_BOX_SMALL,     breakable_box_geo),
    LOAD_MODEL_FROM_GEO(MODEL_GOOMBA,                  goomba_geo),
    LOAD_MODEL_FROM_GEO(MODEL_KOOPA_SHELL,             koopa_shell_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BLACK_BOBOMB,            black_bobomb_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BOBOMB_BUDDY,            bobomb_buddy_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BOWLING_BALL,            bowling_ball_geo),
    LOAD_MODEL_FROM_GEO(MODEL_HEART,                   heart_geo),
    LOAD_MODEL_FROM_GEO(MODEL_FLYGUY,                  flyguy_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CHUCKYA,                 chuckya_geo),
    LOAD_MODEL_FROM_GEO(MODEL_TRAJECTORY_MARKER_BALL,  bowling_ball_track_geo),
#ifdef IA8_30FPS_COINS
    LOAD_MODEL_FROM_GEO(MODEL_SILVER_COIN,             silver_coin_geo),
    LOAD_MODEL_FROM_GEO(MODEL_SILVER_COIN_NO_SHADOW,   silver_coin_no_shadow_geo),
#endif
    RETURN(),
};

const LevelScript script_func_mb64_theme_vanilla[] = {
    LOAD_MODEL_FROM_GEO(MODEL_MARIO,                   mario2_geo),
    LOAD_MODEL_FROM_GEO(MODEL_KINGBOMB_MAKER,          king_bobomb_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_BOWSER_BOMB,       bowser_bomb_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_BOWSER,            bowser_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_BSHOCKWAVE,        invisible_bowser_accessory_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_BFLAMES,           bowser_flames_geo),
    LOAD_MODEL_FROM_GEO(MODEL_WIGGLER_HEAD,            wiggler_head_geo),
    LOAD_MODEL_FROM_GEO(MODEL_WIGGLER_BODY,            wiggler_body_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MARIOS_WINGED_METAL_CAP, marios_winged_metal_cap_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MARIOS_CAP,              marios_cap_geo),
    LOAD_MODEL_FROM_GEO(MODEL_V_MARIOS_METAL_CAP,      marios_metal_cap_geo),
    LOAD_MODEL_FROM_GEO(MODEL_V_MARIOS_WING_CAP,       marios_wing_cap_geo),
    LOAD_MODEL_FROM_GEO(MODEL_VEXCLAMATION_BOX,        vexclamation_box_geo),
    LOAD_MODEL_FROM_GEO(MODEL_KOOPA_FLAG,              koopa_flag_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_TOAD,              toad_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_TUXIE,             penguin_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_UKIKI,             ukiki_geo),
    RETURN(),
};

const LevelScript script_func_mb64_theme_btcm[] = {
    LOAD_MODEL_FROM_GEO(MODEL_MARIO,                   mario_btcm_geo),
    LOAD_MODEL_FROM_GEO(MODEL_HAMMER_BRO,              HammerBroGeo),
    LOAD_MODEL_FROM_GEO(MODEL_HAMMER,                  hammer_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_CRABLET,           crab_geo),
    LOAD_MODEL_FROM_GEO(MODEL_REX,                     rex_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BADGE,                   badge_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MARIOS_VANETAL_CAP,      vanetalc_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MARIOS_ROCKET_BOOTS,     rocket_boot_geo),
    LOAD_MODEL_FROM_GEO(MODEL_EXCLAMATION_BOX,         exclamation_box_geo),
    LOAD_MODEL_FROM_GEO(MODEL_PODOBOO,                 podoboo_geo),
    LOAD_MODEL_FROM_GEO(MODEL_GREEN_COIN,              green_coin_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_CHICKEN,           chicken_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_EGG,               egg_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_SHOWRUNNER,        showrunner_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_SHOWRUNNER_BALL,   srball_1_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_SHOWRUNNER_BALL_2, srball_2_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_SHOWRUNNER_SPIKE,  srspike_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_SHOWRUNNER_STAR,   metalstar_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_CROWBAR,           crowbar_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_MASK,              billmask_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_MOLEMAN,           moleman3_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_COBIE,             cobie2_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_IMBUE_BADGE,       imbue_badge_geo),
    RETURN(),
};
