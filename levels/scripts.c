#include <ultra64.h>
#include "sm64.h"
#include "game/level_update.h"
#include "level_commands.h"
#include "game/area.h"

#include "make_const_nonconst.h"

#include "segment_symbols.h"

#include "actors/common0.h"
#include "actors/common1.h"
#include "actors/group0.h"
#include "actors/group14.h"
#include "actors/group17.h"
#include "game/cursed_mirror_maker.h"

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
static const LevelScript goto_mario_head_regular[6];
static const LevelScript goto_mario_head_dizzy[6];
static const LevelScript goto_debug_level_select[6];

#define STUB_LEVEL(_0, _1, _2, _3, _4, _5, _6, _7, _8)
#define DEFINE_LEVEL(_0, _1, _2, folder, _4, _5, _6, _7, _8, _9, _10) static const LevelScript script_exec_ ## folder [6 + 1];

#include "level_defines.h"

#undef DEFINE_LEVEL
#undef STUB_LEVEL

const LevelScript level_main_scripts_entry[] = {
    LOAD_YAY0(          /*seg*/ SEGMENT_GROUP0_YAY0,   _group0_yay0SegmentRomStart,  _group0_yay0SegmentRomEnd),
    LOAD_YAY0(          /*seg*/ SEGMENT_COMMON1_YAY0, _common1_yay0SegmentRomStart, _common1_yay0SegmentRomEnd),
    LOAD_RAW_WITH_CODE( /*seg*/ SEGMENT_GROUP0_GEO,     _group0_geoSegmentRomStart,   _group0_geoSegmentRomEnd,  _group0_geoSegmentBssStart,  _group0_geoSegmentBssEnd),
    LOAD_RAW_WITH_CODE( /*seg*/ SEGMENT_COMMON1_GEO,   _common1_geoSegmentRomStart,  _common1_geoSegmentRomEnd, _common1_geoSegmentBssStart, _common1_geoSegmentBssEnd),
    LOAD_RAW_WITH_CODE( /*seg*/ SEGMENT_BEHAVIOR_DATA,    _behaviorSegmentRomStart,     _behaviorSegmentRomEnd,   _behaviorSegmentBssStart,     _behaviorSegmentBssEnd),
    ALLOC_LEVEL_POOL(),
    LOAD_MODEL_FROM_GEO(MODEL_SMOKE,                   smoke_geo),

    //LOAD_MODEL_FROM_GEO(0xF0,                   crowbar2_geo),
    
    //LOAD_MODEL_FROM_GEO(MODEL_TV_CORPSE, tvcorpse_geo),

    // LOAD_MODEL_FROM_GEO(MODEL_METAL_STAR,                   metalstar_geo),
    
    //LOAD_MODEL_FROM_GEO(0xEB,                   ring_geo),
    //LOAD_MODEL_FROM_GEO(0xEA,                   metal_crate_geo),
    //LOAD_MODEL_FROM_GEO(MODEL_SHOWRUNNER,       showrunner_geo),
    LOAD_MODEL_FROM_GEO(MODEL_ATM,              moneybag_geo),
    //LOAD_MODEL_FROM_GEO(0xE7,                   chicken_geo),
    // LOAD_MODEL_FROM_GEO(0xE6,                   token_geo),
    //LOAD_MODEL_FROM_GEO(0xE5,                   egg_geo),
    //LOAD_MODEL_FROM_GEO(0xE4,                   snakeblock1_geo),
    //LOAD_MODEL_FROM_GEO(0xE3,                   wallet_geo),
    LOAD_MODEL_FROM_GEO(MODEL_NOTEBLOCK,        noteblock_geo),

    //LOAD_MODEL_FROM_GEO(MODEL_COSMIC_SPIKE, cosmic_spike_geo),

    LOAD_MODEL_FROM_GEO(MODEL_SPARKLES,                sparkles_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BUBBLE,                  bubble_geo),
    LOAD_MODEL_FROM_GEO(MODEL_SMALL_WATER_SPLASH,      small_water_splash_geo),
    LOAD_MODEL_FROM_GEO(MODEL_IDLE_WATER_WAVE,         idle_water_wave_geo),
    LOAD_MODEL_FROM_GEO(MODEL_WATER_SPLASH,            water_splash_geo),
    LOAD_MODEL_FROM_GEO(MODEL_WAVE_TRAIL,              wave_trail_geo),
    LOAD_MODEL_FROM_GEO(MODEL_YELLOW_COIN,             yellow_coin_geo),
    LOAD_MODEL_FROM_GEO(MODEL_STAR,                    star_geo),
    LOAD_MODEL_FROM_GEO(MODEL_TRANSPARENT_STAR,        transparent_star_geo),
    // LOAD_MODEL_FROM_GEO(MODEL_WOODEN_SIGNPOST,         wooden_signpost_geo),
    LOAD_MODEL_FROM_DL( MODEL_WHITE_PARTICLE_SMALL,    white_particle_small_dl,     LAYER_OCCLUDE_SILHOUETTE_ALPHA),
    LOAD_MODEL_FROM_GEO(MODEL_RED_FLAME,               red_flame_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BLUE_FLAME,              blue_flame_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BURN_SMOKE,              burn_smoke_geo),
    LOAD_MODEL_FROM_GEO(MODEL_LEAVES,                  leaves_geo),
    LOAD_MODEL_FROM_GEO(MODEL_PURPLE_MARBLE,           purple_marble_geo),
    LOAD_MODEL_FROM_GEO(MODEL_FISH,                    fish_geo),
    // LOAD_MODEL_FROM_GEO(MODEL_FISH_SHADOW,             fish_shadow_geo),
    LOAD_MODEL_FROM_GEO(MODEL_SPARKLES_ANIMATION,      sparkles_animation_geo),
    LOAD_MODEL_FROM_DL( MODEL_SAND_DUST,               sand_seg3_dl_particle,       LAYER_OCCLUDE_SILHOUETTE_ALPHA),
    LOAD_MODEL_FROM_GEO(MODEL_BUTTERFLY,               butterfly_geo),
    // LOAD_MODEL_FROM_GEO(MODEL_BURN_SMOKE_UNUSED,       burn_smoke_geo),
    LOAD_MODEL_FROM_DL( MODEL_PEBBLE,                  pebble_seg3_dl_0301CB00,     LAYER_OCCLUDE_SILHOUETTE_ALPHA),
    LOAD_MODEL_FROM_GEO(MODEL_MIST,                    mist_geo),
    LOAD_MODEL_FROM_GEO(MODEL_WHITE_PUFF,              white_puff_geo),
    LOAD_MODEL_FROM_DL( MODEL_WHITE_PARTICLE_DL,       white_particle_dl,           LAYER_OCCLUDE_SILHOUETTE_ALPHA),
    LOAD_MODEL_FROM_GEO(MODEL_WHITE_PARTICLE,          white_particle_geo),
    LOAD_MODEL_FROM_GEO(MODEL_YELLOW_COIN_NO_SHADOW,   yellow_coin_no_shadow_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BLUE_COIN,               blue_coin_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BLUE_COIN_NO_SHADOW,     blue_coin_no_shadow_geo),
    // LOAD_MODEL_FROM_GEO(MODEL_BOWSER_KEY_CUTSCENE,     bowser_key_cutscene_geo),
    // LOAD_MODEL_FROM_GEO(MODEL_BOWSER_KEY,              bowser_key_geo),
    LOAD_MODEL_FROM_GEO(MODEL_RED_FLAME_SHADOW,        red_flame_shadow_geo),
    // LOAD_MODEL_FROM_GEO(MODEL_1UP,                     mushroom_1up_geo),
    LOAD_MODEL_FROM_GEO(MODEL_RED_COIN,                red_coin_geo),
    LOAD_MODEL_FROM_GEO(MODEL_RED_COIN_NO_SHADOW,      red_coin_no_shadow_geo),
    LOAD_MODEL_FROM_GEO(MODEL_NUMBER,                  number_geo),
    LOAD_MODEL_FROM_GEO(MODEL_EXPLOSION,               explosion_geo),
    LOAD_MODEL_FROM_GEO(MODEL_DIRT_ANIMATION,          dirt_animation_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CARTOON_STAR,            cartoon_star_geo),
    // LOAD_MODEL_FROM_GEO(MODEL_QUEST ,quest_geo),
    LOAD_MODEL_FROM_GEO(MODEL_SB ,sb_cube_geo),
    LOAD_MODEL_FROM_DL(MODEL_LEV, cmm_terrain_gfx, LAYER_OPAQUE),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_TREE_1,bubbly_tree_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_TREE_2,spiky_tree_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_TREE_3,palm_tree_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_TREE_4,snow_tree_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_BOUNDARY, lev_edge_geo),
    LOAD_MODEL_FROM_GEO(MODEL_SPAWN, spawn_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_PIPE, warp_pipe_geo),
    LOAD_MODEL_FROM_GEO(MODEL_WHOMP_MAKER, whomp_geo),
    LOAD_MODEL_FROM_GEO(MODEL_THWOMP_MAKER, thwomp_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BILL_MAKER, bullet_bill_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BILL_MAKER_2, blaster_geo),
    LOAD_MODEL_FROM_GEO(MODEL_LAKITU_MAKER, enemy_lakitu_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_SNUFIT, snufit_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_BOO, boo_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_MRI, mr_i_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_MRI_2, mr_i_iris_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_PLANT, piranha_plant_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_SPINDRIFT,spindrift_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_BLIZZARD,mr_blizzard_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_HEAVEHO,heave_ho_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_CHILL_BULLY,chilly_chief_geo),
    LOAD_MODEL_FROM_GEO(MODEL_SPINY_BALL,              spiny_ball_geo),
    LOAD_MODEL_FROM_GEO(MODEL_SPINY,                   spiny_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_SCUTTLEBUG,        scuttlebug_geo),
    LOAD_MODEL_FROM_GEO(MODEL_KOOPA_WITH_SHELL,        koopa_with_shell_geo),
    LOAD_MODEL_FROM_GEO(MODEL_KOOPA_WITHOUT_SHELL,     koopa_without_shell_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_FIREBAR, spooner_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_GRINDEL ,ssl_geo_000734),
    LOAD_MODEL_FROM_GEO(MODEL_LOOPINGP, loopingp_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BULLY,                   bully_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BULLY_BOSS,              bully_boss_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CULL_MARKER, new_cull_marker_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_MOTOS, RCP_HmsEnemymotos_basedata_A),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_SKEETER, skeeter_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_FLAMETHROWER, gooner_geo),

#ifdef IA8_30FPS_COINS
    LOAD_MODEL_FROM_GEO(MODEL_SILVER_COIN,             silver_coin_geo),
    LOAD_MODEL_FROM_GEO(MODEL_SILVER_COIN_NO_SHADOW,   silver_coin_no_shadow_geo),
#endif
    FREE_LEVEL_POOL(),
    POP_POOL(),
    CALL(/*arg*/ 0, /*func*/ lvl_init_from_save_file),
    LOOP_BEGIN(),
        EXECUTE(/*seg*/ SEGMENT_MENU_INTRO, _menuSegmentRomStart, _menuSegmentRomEnd, level_main_menu_entry_act_select),
        JUMP_LINK(script_exec_level_table),
        SLEEP(/*frames*/ 1),
    LOOP_UNTIL(/*op*/ OP_LT, /*arg*/ WARP_SPECIAL_NONE),
    JUMP_IF(   /*op*/ OP_EQ, /*arg*/ WARP_SPECIAL_ENDING,              goto_ending),
    JUMP_IF(   /*op*/ OP_EQ, /*arg*/ WARP_SPECIAL_MARIO_HEAD_REGULAR,  goto_mario_head_regular),
    JUMP_IF(   /*op*/ OP_EQ, /*arg*/ WARP_SPECIAL_MARIO_HEAD_DIZZY,    goto_mario_head_dizzy),
    JUMP_IF(   /*op*/ OP_EQ, /*arg*/ WARP_SPECIAL_INTRO_SPLASH_SCREEN, goto_intro_splash_screen),
    JUMP_IF(   /*op*/ OP_EQ, /*arg*/ WARP_SPECIAL_LEVEL_SELECT,        goto_debug_level_select),
};

static const LevelScript goto_intro_splash_screen[] = {
    EXIT_AND_EXECUTE_WITH_CODE(/*seg*/ SEGMENT_MENU_INTRO, _introSegmentRomStart, _introSegmentRomEnd, level_intro_splash_screen, _introSegmentBssStart, _introSegmentBssEnd),
};

// static const LevelScript goto_ending[] = {
//     EXIT_AND_EXECUTE_WITH_CODE(/*seg*/ SEGMENT_LEVEL_SCRIPT, _endingSegmentRomStart, _endingSegmentRomEnd, level_ending_entry, _endingSegmentBssStart, _endingSegmentBssEnd),
// };

static const LevelScript goto_mario_head_regular[] = {
    EXIT_AND_EXECUTE_WITH_CODE(/*seg*/ SEGMENT_MENU_INTRO, _introSegmentRomStart, _introSegmentRomEnd, level_intro_mario_head_regular, _introSegmentBssStart, _introSegmentBssEnd),
};

static const LevelScript goto_mario_head_dizzy[] = {
    EXIT_AND_EXECUTE_WITH_CODE(/*seg*/ SEGMENT_MENU_INTRO, _introSegmentRomStart, _introSegmentRomEnd, level_intro_mario_head_dizzy, _introSegmentBssStart, _introSegmentBssEnd),
};

static const LevelScript goto_debug_level_select[] = {
    EXIT_AND_EXECUTE_WITH_CODE(/*seg*/ SEGMENT_MENU_INTRO, _introSegmentRomStart, _introSegmentRomEnd, level_intro_entry_level_select, _introSegmentBssStart, _introSegmentBssEnd),
};

// Include the level jumptable.

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

const LevelScript script_func_global_1[] = {
    LOAD_MODEL_FROM_GEO(MODEL_BLUE_COIN_SWITCH,        blue_coin_switch_geo),
    LOAD_MODEL_FROM_GEO(MODEL_AMP,                     dAmpGeo),
    LOAD_MODEL_FROM_GEO(MODEL_PURPLE_SWITCH,           purple_switch_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CHECKERBOARD_PLATFORM,   checkerboard_platform_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BREAKABLE_BOX,           breakable_box_no_shadow_geo),
    //LOAD_MODEL_FROM_GEO(MODEL_BREAKABLE_BOX_NO_SHADOW, breakable_box_no_shadow_geo),
    // LOAD_MODEL_FROM_GEO(MODEL_EXCLAMATION_BOX_OUTLINE, exclamation_box_outline_geo),
    LOAD_MODEL_FROM_GEO(MODEL_GOOMBA,                  goomba_geo),
    // LOAD_MODEL_FROM_DL( MODEL_EXCLAMATION_POINT,       exclamation_box_outline_seg8_dl_exclamation_point, LAYER_OCCLUDE_SILHOUETTE_ALPHA),
    LOAD_MODEL_FROM_GEO(MODEL_KOOPA_SHELL,             koopa_shell_geo),
    // LOAD_MODEL_FROM_GEO(MODEL_METAL_BOX,               metal_box_geo),
    // LOAD_MODEL_FROM_DL( MODEL_METAL_BOX_DL,            metal_box_dl,                             LAYER_OPAQUE),
    LOAD_MODEL_FROM_GEO(MODEL_BLACK_BOBOMB,            black_bobomb_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BOBOMB_BUDDY,            bobomb_buddy_geo),
    // LOAD_MODEL_FROM_DL( MODEL_DL_CANNON_LID,           cannon_lid_seg8_dl_080048E0,              LAYER_OPAQUE),
    LOAD_MODEL_FROM_GEO(MODEL_BOWLING_BALL,            bowling_ball_geo),
    // LOAD_MODEL_FROM_GEO(MODEL_CANNON_BARREL,           cannon_barrel_geo),
    // LOAD_MODEL_FROM_GEO(MODEL_CANNON_BASE,             cannon_base_geo),
    LOAD_MODEL_FROM_GEO(MODEL_HEART,                   heart_geo),
    LOAD_MODEL_FROM_GEO(MODEL_FLYGUY,                  flyguy_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CHUCKYA,                 chuckya_geo),
    LOAD_MODEL_FROM_GEO(MODEL_TRAJECTORY_MARKER_BALL,      bowling_ball_track_geo),

    RETURN(),
};

const LevelScript script_func_cmm_theme_vanilla[] = {
    LOAD_MODEL_FROM_GEO(MODEL_MARIO, mario2_geo),
    LOAD_MODEL_FROM_GEO(MODEL_KINGBOMB_MAKER,   king_bobomb_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_BOWSER_BOMB,bowser_bomb_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_BOWSER,bowser_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_BSHOCKWAVE, invisible_bowser_accessory_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_BFLAMES, bowser_flames_geo),
    LOAD_MODEL_FROM_GEO(MODEL_WIGGLER_HEAD,            wiggler_head_geo),
    LOAD_MODEL_FROM_GEO(MODEL_WIGGLER_BODY,            wiggler_body_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MARIOS_WINGED_METAL_CAP, marios_winged_metal_cap_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MARIOS_CAP,              marios_cap_geo),
    LOAD_MODEL_FROM_GEO(MODEL_V_MARIOS_METAL_CAP,        marios_metal_cap_geo),
    LOAD_MODEL_FROM_GEO(MODEL_V_MARIOS_WING_CAP,         marios_wing_cap_geo),
    LOAD_MODEL_FROM_GEO(MODEL_VEXCLAMATION_BOX,        vexclamation_box_geo),
    LOAD_MODEL_FROM_GEO(MODEL_KOOPA_FLAG,              koopa_flag_geo),
    RETURN(),
};
const LevelScript script_func_cmm_theme_btcm[] = {
    LOAD_MODEL_FROM_GEO(MODEL_MARIO, mario_geo),
    LOAD_MODEL_FROM_GEO(0xEE,                   HammerBroGeo),
    LOAD_MODEL_FROM_GEO(0xEC,                   hammer_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_CRABLET,    crab_geo),
    LOAD_MODEL_FROM_GEO(0xE1,                   rex_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BADGE, badge_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MARIOS_METAL_CAP,        vanetalc_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MARIOS_WING_CAP,         rocket_boot_geo),
    LOAD_MODEL_FROM_GEO(MODEL_EXCLAMATION_BOX,         exclamation_box_geo),
    LOAD_MODEL_FROM_GEO(MODEL_PODOBOO ,podoboo_geo),
    LOAD_MODEL_FROM_GEO(0xEF,                   green_coin_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_CHICKEN, chicken_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAKER_EGG, egg_geo),
    RETURN(),
};

/**

const LevelScript script_func_global_2[] = {
    //LOAD_MODEL_FROM_GEO(MODEL_BULLET_BILL,             bullet_bill_geo),
    //LOAD_MODEL_FROM_GEO(MODEL_YELLOW_SPHERE,           yellow_sphere_geo),
    //LOAD_MODEL_FROM_GEO(MODEL_HOOT,                    hoot_geo),
    //LOAD_MODEL_FROM_GEO(MODEL_YOSHI_EGG,               yoshi_egg_geo),
    //LOAD_MODEL_FROM_GEO(MODEL_THWOMP,                  thwomp_geo),
    //LOAD_MODEL_FROM_GEO(MODEL_HEAVE_HO,                heave_ho_geo),
    RETURN(),
};

const LevelScript script_func_global_3[] = {
    LOAD_MODEL_FROM_GEO(MODEL_BLARGG,                  blargg_geo),
    RETURN(),
};

const LevelScript script_func_global_4[] = {
    LOAD_MODEL_FROM_GEO(MODEL_WATER_BOMB,              water_bomb_geo),
    LOAD_MODEL_FROM_GEO(MODEL_WATER_BOMB_SHADOW,       water_bomb_shadow_geo),
    LOAD_MODEL_FROM_GEO(MODEL_KING_BOBOMB,             king_bobomb_geo),
    RETURN(),
};

const LevelScript script_func_global_5[] = {
    LOAD_MODEL_FROM_GEO(MODEL_MANTA_RAY,               manta_seg5_geo_05008D14),
    LOAD_MODEL_FROM_GEO(MODEL_UNAGI,                   unagi_geo),
    LOAD_MODEL_FROM_GEO(MODEL_SUSHI,                   sushi_geo),
    LOAD_MODEL_FROM_DL( MODEL_DL_WHIRLPOOL,            whirlpool_seg5_dl_05013CB8, LAYER_TRANSPARENT),
    LOAD_MODEL_FROM_GEO(MODEL_CLAM_SHELL,              clam_shell_geo),
    RETURN(),
};

const LevelScript script_func_global_6[] = {
    LOAD_MODEL_FROM_GEO(MODEL_POKEY_HEAD,              pokey_head_geo),
    LOAD_MODEL_FROM_GEO(MODEL_POKEY_BODY_PART,         pokey_body_part_geo),
    LOAD_MODEL_FROM_GEO(MODEL_TWEESTER,                tweester_geo),
    LOAD_MODEL_FROM_GEO(MODEL_KLEPTO,                  klepto_geo),
    LOAD_MODEL_FROM_GEO(MODEL_EYEROK_LEFT_HAND,        eyerok_left_hand_geo),
    LOAD_MODEL_FROM_GEO(MODEL_EYEROK_RIGHT_HAND,       eyerok_right_hand_geo),
    RETURN(),
};

const LevelScript script_func_global_7[] = {
    // LOAD_MODEL_FROM_DL( MODEL_DL_MONTY_MOLE_HOLE,      monty_mole_hole_seg5_dl_05000840, LAYER_TRANSPARENT_DECAL),
    //LOAD_MODEL_FROM_GEO(MODEL_MONTY_MOLE,              monty_mole_geo),
    LOAD_MODEL_FROM_GEO(MODEL_UKIKI,                   ukiki_geo),
    LOAD_MODEL_FROM_GEO(MODEL_FWOOSH,                  fwoosh_geo),
    RETURN(),
};

const LevelScript script_func_global_8[] = {
    LOAD_MODEL_FROM_GEO(MODEL_SPINDRIFT,               spindrift_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MR_BLIZZARD_HIDDEN,      mr_blizzard_hidden_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MR_BLIZZARD,             mr_blizzard_geo),
    LOAD_MODEL_FROM_GEO(MODEL_PENGUIN,                 penguin_geo),
    RETURN(),
};

const LevelScript script_func_global_9[] = {
    LOAD_MODEL_FROM_DL( MODEL_CAP_SWITCH_EXCLAMATION,  cap_switch_exclamation_seg5_dl_05002E00, LAYER_ALPHA),
    LOAD_MODEL_FROM_GEO(MODEL_CAP_SWITCH,              cap_switch_geo),
    LOAD_MODEL_FROM_DL( MODEL_CAP_SWITCH_BASE,         cap_switch_base_seg5_dl_05003120,        LAYER_OPAQUE),
    RETURN(),
};

const LevelScript script_func_global_10[] = {
    LOAD_MODEL_FROM_GEO(MODEL_BOO,                     boo_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BETA_BOO_KEY,               small_key_geo),
    LOAD_MODEL_FROM_GEO(MODEL_HAUNTED_CHAIR,           haunted_chair_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MAD_PIANO,               mad_piano_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BOOKEND_PART,            bookend_part_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BOOKEND,                 bookend_geo),
    LOAD_MODEL_FROM_GEO(MODEL_HAUNTED_CAGE,            haunted_cage_geo),
    LOAD_MODEL_FROM_GEO(0xF7,                          bowser_bomb_geo),
    RETURN(),
};

const LevelScript script_func_global_11[] = {
    LOAD_MODEL_FROM_GEO(MODEL_BIRDS,                   birds_geo),
    LOAD_MODEL_FROM_GEO(MODEL_PEACH,                   peach_geo),

    RETURN(),
};

const LevelScript script_func_global_12[] = {
    RETURN(),
};

const LevelScript script_func_global_13[] = {
    LOAD_MODEL_FROM_GEO(MODEL_BOWSER,                  bowser_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BOWSER_BOMB_CHILD_OBJ,   bowser_bomb_geo),

    LOAD_MODEL_FROM_GEO(MODEL_BOWSER_SMOKE,            bowser_impact_smoke_geo),
    //LOAD_MODEL_FROM_GEO(MODEL_BOWSER_FLAMES,           bowser_flames_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BOWSER_WAVE,             invisible_bowser_accessory_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BOWSER_NO_SHADOW,        bowser_geo_no_shadow),
    RETURN(),
};

const LevelScript script_func_global_14[] = {
    LOAD_MODEL_FROM_GEO(MODEL_BUB,                     bub_geo),
    LOAD_MODEL_FROM_GEO(MODEL_TREASURE_CHEST_BASE,     treasure_chest_base_geo),
    LOAD_MODEL_FROM_GEO(MODEL_TREASURE_CHEST_LID,      treasure_chest_lid_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CYAN_FISH,               cyan_fish_geo),
    LOAD_MODEL_FROM_GEO(MODEL_WATER_RING,              water_ring_geo),
    LOAD_MODEL_FROM_GEO(MODEL_WATER_MINE,              water_mine_geo),
    LOAD_MODEL_FROM_GEO(MODEL_SEAWEED,                 seaweed_geo),
    LOAD_MODEL_FROM_GEO(MODEL_SKEETER,                 skeeter_geo),
    RETURN(),
};

const LevelScript script_func_global_15[] = {

    RETURN(),
};

const LevelScript script_func_global_16[] = {
    LOAD_MODEL_FROM_GEO(MODEL_MIPS,                    mips_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BOO_CASTLE,              boo_castle_geo),
    LOAD_MODEL_FROM_GEO(MODEL_LAKITU,                  lakitu_geo),
    LOAD_MODEL_FROM_GEO(MODEL_TOAD,                    toad_geo),
    RETURN(),
};

const LevelScript script_func_global_17[] = {

    LOAD_MODEL_FROM_GEO(MODEL_BIG_CHILL_BULLY,         chilly_chief_big_geo),
    // LOAD_MODEL_FROM_GEO(MODEL_MONEYBAG,                moneybag_geo),
    RETURN(),
};

const LevelScript script_func_global_18[] = {
    LOAD_MODEL_FROM_GEO(MODEL_SWOOP,                   swoop_geo),
    LOAD_MODEL_FROM_GEO(MODEL_SCUTTLEBUG,              scuttlebug_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MR_I_IRIS,               mr_i_iris_geo),
    LOAD_MODEL_FROM_GEO(MODEL_MR_I_BODY,               mr_i_geo),
    LOAD_MODEL_FROM_GEO(MODEL_DORRIE,                  dorrie_geo),
    LOAD_MODEL_FROM_GEO(MODEL_SNUFIT,                  snufit_geo),
    RETURN(),
};
**/