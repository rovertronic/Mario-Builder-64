#include "mb64/editor/object.h"
#include "mb64/editor/grid.h"
#include "mb64/editor/display_funcs.h"
#include "mb64/menu/toolbox.h"
#include "model_ids.h"
#include "behavior_data.h"
#include "mb64/gfx/mb64_buttons.h"
#include "actors/group_global.h"
#include "actors/group_btcm.h"
#include "actors/group_vanilla.h"

struct ExclamationBoxContents sExclamationBoxContents_btcm[] = {
    { 0, MODEL_MARIOS_ROCKET_BOOTS,  bhvWingCap,           0, TRUE,  0},
    { 0, MODEL_MARIOS_VANETAL_CAP,   bhvVanishCap,         2, TRUE,  0},
    { 0, MODEL_KOOPA_SHELL,          bhvKoopaShell,        3, TRUE,  0},
    { 0, MODEL_GREEN_COIN,           bhvGreenGetsSpawned,  4, FALSE, 3},
    { 0, MODEL_YELLOW_COIN,          bhvSingleCoinGetsSpawned,  4, FALSE, 1},
    { 0, MODEL_NONE,                 bhvThreeCoinsSpawn,   4, FALSE, 3},
    { 0, MODEL_NONE,                 bhvTenCoinsSpawn,     4, FALSE, 10},
};

struct ExclamationBoxContents sExclamationBoxContents_vanilla[] = {
    { 0, MODEL_V_MARIOS_WING_CAP,  bhvWingCap,         0, TRUE,  0},
    { 6, MODEL_V_MARIOS_METAL_CAP, bhvMetalCap,        1, TRUE,  0},
    { 0, MODEL_MARIOS_CAP,         bhvVanishCap,       2, TRUE,  0},
    { 0, MODEL_KOOPA_SHELL,        bhvKoopaShell,      3, TRUE,  0},
    { 0, MODEL_YELLOW_COIN,        bhvSingleCoinGetsSpawned, 3, FALSE, 1},
    { 0, MODEL_NONE,               bhvThreeCoinsSpawn, 3, FALSE, 3},
    { 0, MODEL_NONE,               bhvTenCoinsSpawn,   3, FALSE, 10},
};

struct mb64_object_info mb64_object_type_list[OBJECT_TYPE_COUNT] = {
    [OBJECT_TYPE_SETTINGS]           = {"Level Settings",     &mb64_btn_settings,           NULL,                            0,           MODEL_NONE,                  0,                                              0,                0,  0,  0.0f,  NULL,                              NULL,                      0},
    [OBJECT_TYPE_1]                  = {" ",                  &mb64_btn_settings,           NULL,                            0,           MODEL_NONE,                  0,                                              0,                0,  0,  0.0f,  NULL,                              NULL,                      0}, // previously screenshot
    [OBJECT_TYPE_STAR]               = {"Power Star",         &mb64_btn_star,               bhvStar,                         TILE_SIZE/2, MODEL_STAR,                  OBJ_TYPE_STAR,                                  OBJ_OCCUPY_INNER, 0,  0,  1.0f,  NULL,                              df_star,                   SOUND_MENU_STAR_SOUND | SOUND_VIBRATO},
    [OBJECT_TYPE_RED_COIN_STAR]      = {"Red Coin Star",      &mb64_btn_redcoinstar,        bhvHiddenRedCoinStar,            TILE_SIZE/2, MODEL_TRANSPARENT_STAR,      OBJ_TYPE_STAR,                                  OBJ_OCCUPY_INNER, 0,  1,  1.0f,  NULL,                              df_reds_marker,            SOUND_MENU_STAR_SOUND | SOUND_VIBRATO},
    [OBJECT_TYPE_GOOMBA]             = {"Goomba",             &mb64_btn_goomba,             bhvGoomba,                       0,           MODEL_GOOMBA,                OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 1,  0,  1.5f,  goomba_seg8_anims_0801DA4C,        NULL,                      SOUND_OBJ_GOOMBA_PREVIEW},
    [OBJECT_TYPE_BIG_GOOMBA]         = {"Huge Goomba",        &mb64_btn_biggoomba,          bhvBigGoomba,                    0,           MODEL_GOOMBA,                OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 5,  0,  3.5f,  goomba_seg8_anims_0801DA4C,        NULL,                      SOUND_OBJ_GOOMBA_PREVIEW},
    [OBJECT_TYPE_TINY_GOOMBA]        = {"Tiny Goomba",        &mb64_btn_tinygoomba,         bhvTinyGoomba,                   0,           MODEL_GOOMBA,                OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 1,  0,  0.5f,  goomba_seg8_anims_0801DA4C,        NULL,                      SOUND_OBJ_GOOMBA_PREVIEW},
    [OBJECT_TYPE_PIRANHA_PLANT]      = {"Piranha Plant",      &mb64_btn_piranha,            bhvPiranhaPlant,                 0,           MODEL_MAKER_PLANT,           OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 5,  1,  1.0f,  piranha_plant_seg6_anims_0601C31C, df_piranha,                SOUND_OBJ2_PIRANHA_PLANT_BITE},
    [OBJECT_TYPE_BIG_PIRANHA_PLANT]  = {"Huge Piranha Plant", &mb64_btn_bigfirepiranha,     bhvFirePiranhaPlantBig,          0,           MODEL_MAKER_PLANT,           OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 2,  0,  2.0f,  piranha_plant_seg6_anims_0601C31C, NULL,                      SOUND_OBJ2_PIRANHA_PLANT_BITE},
    [OBJECT_TYPE_TINY_PIRANHA_PLANT] = {"Tiny Piranha Plant", &mb64_btn_firepiranha,        bhvFirePiranhaPlant,             0,           MODEL_MAKER_PLANT,           OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 1,  0,  0.5f,  piranha_plant_seg6_anims_0601C31C, NULL,                      SOUND_OBJ2_PIRANHA_PLANT_BITE},
    [OBJECT_TYPE_KOOPA]              = {"Koopa",              &mb64_btn_koopa,              bhvScaredKoopa,                  0,           MODEL_KOOPA_WITH_SHELL,      OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 5,  0,  1.5f,  koopa_seg6_anims_06011364,         df_koopa,                  SOUND_OBJ_KOOPA_TALK},
    [OBJECT_TYPE_COIN]               = {"Yellow Coin",        &mb64_btn_coin,               bhvYellowCoin,                   0,           MODEL_YELLOW_COIN,           OBJ_TYPE_BILLBOARD | OBJ_TYPE_IMBUABLE_TRIGGER, OBJ_OCCUPY_INNER, 1,  0,  1.0f,  NULL,                              NULL,                      SOUND_GENERAL_COIN | SOUND_VIBRATO},
    [OBJECT_TYPE_GREEN_COIN]         = {"Green Coin",         &mb64_btn_greencoin,          bhvGreenCoin,                    0,           MODEL_GREEN_COIN,            OBJ_TYPE_BILLBOARD | OBJ_TYPE_IMBUABLE_TRIGGER, OBJ_OCCUPY_INNER, 3,  0,  1.0f,  NULL,                              NULL,                      SOUND_GENERAL_COIN_MULTI},
    [OBJECT_TYPE_RED_COIN]           = {"Red Coin",           &mb64_btn_redcoin,            bhvRedCoin,                      0,           MODEL_RED_COIN,              OBJ_TYPE_BILLBOARD,                             OBJ_OCCUPY_INNER, 2,  0,  1.0f,  NULL,                              NULL,                      SOUND_MENU_COLLECT_RED_COIN},
    [OBJECT_TYPE_BLUE_COIN]          = {"Blue Coin",          &mb64_btn_bluecoin,           bhvHiddenBlueCoin,               0,           MODEL_BLUE_COIN,             OBJ_TYPE_BILLBOARD | OBJ_TYPE_IMBUABLE_TRIGGER, OBJ_OCCUPY_INNER, 5,  0,  1.0f,  NULL,                              NULL,                      SOUND_GENERAL_COIN_MULTI},
    [OBJECT_TYPE_BLUE_COIN_SWITCH]   = {"Blue Coin Switch",   &mb64_btn_bluecoinswitch,     bhvBlueCoinSwitch,               0,           MODEL_BLUE_COIN_SWITCH,      OBJ_TYPE_IMBUABLE_TRIGGER,                      OBJ_OCCUPY_INNER, 0,  0,  3.0f,  NULL,                              NULL,                      SOUND_GENERAL2_PURPLE_SWITCH},
    [OBJECT_TYPE_NOTEBLOCK]          = {"Noteblock",          &mb64_btn_noteblock,          bhvNoteblock,                    TILE_SIZE/2, MODEL_NOTEBLOCK,             0,                                              OBJ_OCCUPY_INNER, 0,  0,  1.27f, NULL,                              NULL,                      SOUND_GENERAL_CRAZY_BOX_BOING_SLOW},
    [OBJECT_TYPE_BOBOMB]             = {"Bob-omb",            &mb64_btn_bobomb,             bhvBobomb,                       0,           MODEL_BLACK_BOBOMB,          OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 1,  0,  1.0f,  bobomb_anims,                      NULL,                      SOUND_GENERAL2_QUIET_EXPLOSION},
    [OBJECT_TYPE_CHUCKYA]            = {"Chuckya",            &mb64_btn_chuckya,            bhvChuckya,                      0,           MODEL_CHUCKYA,               OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 5,  0,  2.0f,  chuckya_seg8_anims_0800C070,       df_chuckya,                SOUND_OBJ_CHUCKYA_PREVIEW},
    [OBJECT_TYPE_BULLY]              = {"Bully",              &mb64_btn_bully,              bhvSmallBully,                   0,           MODEL_BULLY,                 OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 1,  0,  1.0f,  bully_seg5_anims_0500470C,         NULL,                      SOUND_OBJ2_SMALL_BULLY_ATTACKED},
    [OBJECT_TYPE_CHILL_BULLY]        = {"Chill Bully",        &mb64_btn_chillbully,         bhvSmallBully,                   0,           MODEL_CHILL_BULLY,           OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 1,  0,  1.0f,  bully_seg5_anims_0500470C,         NULL,                      SOUND_OBJ2_SMALL_BULLY_ATTACKED},
    [OBJECT_TYPE_BULLET_BILL]        = {"Bullet Bill",        &mb64_btn_bulletbill,         bhvBulletBillCannon,             TILE_SIZE/2, MODEL_BILL_MAKER_2,          0,                                              OBJ_OCCUPY_FULL,  0,  1,  1.0f,  NULL,                              NULL,                      SOUND_OBJ_POUNDING_CANNON},
    [OBJECT_TYPE_HEAVE_HO]           = {"Heave-Ho",           &mb64_btn_heaveho,            bhvHeaveHo,                      0,           MODEL_MAKER_HEAVEHO,         OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS,    OBJ_OCCUPY_INNER, 0,  0,  2.0f,  heave_ho_seg5_anims_0501534C,      NULL,                      SOUND_OBJ_HEAVEHO_PREVIEW},
    [OBJECT_TYPE_MOTOS]              = {"Motos",              &mb64_btn_motos,              bhvMotos,                        0,           MODEL_MAKER_MOTOS,           OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 5,  0,  2.0f,  motos_anime,                       NULL,                      SOUND_OBJ_HEAVEHO_PREVIEW},
    [OBJECT_TYPE_TREE]               = {"Tree",               &mb64_btn_bubblytree,         bhvTree,                         0,           MODEL_MAKER_TREE_1,          OBJ_TYPE_BILLBOARD,                             OBJ_OCCUPY_INNER, 0,  0,  1.0f,  NULL,                              df_tree,                   SOUND_ACTION_CLIMB_UP_TREE | SOUND_VIBRATO},
    [OBJECT_TYPE_EXCL_BOX]           = {"Item Box",           &mb64_btn_exclamationbox,     bhvExclamationBox,               TILE_SIZE/2, MODEL_EXCLAMATION_BOX,       OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 0,  0,  2.0f,  NULL,                              df_exbox,                  SOUND_GENERAL_BOX_PREVIEW},
    [OBJECT_TYPE_MARIO_SPAWN]        = {"Mario Spawn",        &mb64_btn_spawn,              bhvSpawn,                        TILE_SIZE/2, MODEL_SPAWN,                 0,                                              OBJ_OCCUPY_INNER, 0,  0,  1.0f,  NULL,                              df_hide_during_screenshot, SOUND_MENU_STAR_SOUND_LETS_A_GO},
    [OBJECT_TYPE_REX]                = {"Rex",                &mb64_btn_rex,                bhvRex,                          0,           MODEL_REX,                   OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 2,  0,  1.5f,  Rex_anims,                         NULL,                      SOUND_OBJ_GOOMBA_PREVIEW},
    [OBJECT_TYPE_PODOBOO]            = {"Podoboo",            &mb64_btn_podoboo,            bhvPodoboo,                      TILE_SIZE/2, MODEL_PODOBOO,               0,                                              OBJ_OCCUPY_INNER, 0,  0,  1.0f,  NULL,                              df_podoboo,                SOUND_OBJ_FLAME_BLOWN},
    [OBJECT_TYPE_CRABLET]            = {"Crablet",            &mb64_btn_crablet,            bhvCrablet,                      0,           MODEL_MAKER_CRABLET,         OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 4,  0,  1.0f,  crab_anims_anims,                  NULL,                      SOUND_OBJ2_SCUTTLEBUG_ALERT},
    [OBJECT_TYPE_HAMMER_BRO]         = {"Hammer Bro",         &mb64_btn_hammerbro,          bhvHammerBro,                    0,           MODEL_HAMMER_BRO,            OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 6,  0,  1.0f,  Hammerbro_anims,                   df_hammerbro,              SOUND_OBJ_KOOPA_DAMAGE},
    [OBJECT_TYPE_FIRE_BRO]           = {"Fire Bro",           &mb64_btn_firebro,            bhvFireBro,                      0,           MODEL_HAMMER_BRO,            OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 6,  0,  1.0f,  Hammerbro_anims,                   df_firebro,                SOUND_OBJ_KOOPA_DAMAGE},
    [OBJECT_TYPE_CHICKEN]            = {"Chicken",            &mb64_btn_chicken,            bhvChicken,                      TILE_SIZE/2, MODEL_MAKER_CHICKEN,         OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 2,  0,  1.0f,  chicken_anims,                     NULL,                      SOUND_OBJ_BOO_LAUGH_SHORT},
    [OBJECT_TYPE_PHANTASM]           = {"Cosmic Phantasm",    &mb64_btn_cosmicphantasm,     bhvPhantasm,                     0,           MODEL_MARIO,                 OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 5,  9,  1.0f,  &evil_mario_anims[2],              NULL,                      SOUND_ACTION_METAL_STEP | SOUND_VIBRATO},
    [OBJECT_TYPE_WARP_PIPE]          = {"Warp Pipe",          &mb64_btn_pipe,               bhvStaticObject,                 0,           MODEL_MAKER_PIPE,            0,                                              OBJ_OCCUPY_INNER, 0,  0,  1.0f,  NULL,                              NULL,                      SOUND_MENU_ENTER_PIPE | SOUND_VIBRATO},
    [OBJECT_TYPE_BADGE]              = {"Badge",              &mb64_btn_badgelava,          bhvBadge,                        TILE_SIZE/2, MODEL_BADGE,                 OBJ_TYPE_BILLBOARD | OBJ_TYPE_IMBUABLE_TRIGGER, OBJ_OCCUPY_INNER, 0,  0,  1.0f,  NULL,                              NULL,                      SOUND_GENERAL2_PURPLE_SWITCH},
    [OBJECT_TYPE_KING_BOBOMB]        = {"King Bob-omb",       &mb64_btn_kingbobomb,         bhvKingBobomb,                   0,           MODEL_KINGBOMB_MAKER,        OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_FULL,  0,  0,  1.0f,  king_bobomb_seg5_anims_0500FE30,   df_kingbomb,               SOUND_OBJ_KING_BOBOMB_POUNDING1_HIGHPRIO},
    [OBJECT_TYPE_KING_WHOMP]         = {"King Whomp",         &mb64_btn_kingwhomp,          bhvWhompKingBoss,                0,           MODEL_WHOMP_MAKER,           OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_FULL,  0,  1,  2.0f,  whomp_seg6_anims_06020A04,         NULL,                      SOUND_OBJ_WHOMP},
    [OBJECT_TYPE_BIG_BOO]            = {"Big Boo",            &mb64_btn_bigboo,             bhvBalconyBigBoo,                TILE_SIZE,   MODEL_MAKER_BOO,             OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS,    OBJ_OCCUPY_FULL,  0,  0,  3.0f,  NULL,                              df_boo,                    SOUND_OBJ_BOO_LAUGH_LONG},
    [OBJECT_TYPE_BIG_BULLY]          = {"Big Bully",          &mb64_btn_bigbully,           bhvBigBully,                     0,           MODEL_BULLY,                 OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_FULL,  0,  0,  2.0f,  bully_seg5_anims_0500470C,         NULL,                      SOUND_OBJ2_LARGE_BULLY_ATTACKED},
    [OBJECT_TYPE_BIG_CHILL_BULLY]    = {"Big Chill Bully",    &mb64_btn_chiefchilly,        bhvBigBully,                     0,           MODEL_CHILL_BULLY,           OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_FULL,  0,  0,  2.0f,  bully_seg5_anims_0500470C,         NULL,                      SOUND_OBJ2_LARGE_BULLY_ATTACKED},
    [OBJECT_TYPE_WIGGLER]            = {"Wiggler",            &mb64_btn_wiggler,            bhvWigglerHead,                  0,           MODEL_WIGGLER_HEAD,          OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_FULL,  0,  5,  4.0f,  wiggler_seg5_anims_0500EC8C,       df_wiggler,                SOUND_OBJ_WIGGLER_TALK},
    [OBJECT_TYPE_BOWSER]             = {"Bowser",             &mb64_btn_bowser,             bhvBowser,                       0,           MODEL_MAKER_BOWSER,          OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_FULL,  0,  24, 1.0f,  bowser_anims,                      df_bowser,                 SOUND_OBJ2_BOWSER_ROAR},
    [OBJECT_TYPE_PLATFORM_TRACK]     = {"Activated Platform", &mb64_btn_movingplatform,     bhvPlatformOnTrack,              TILE_SIZE/2, MODEL_CHECKERBOARD_PLATFORM, OBJ_TYPE_TRAJECTORY,                            OBJ_OCCUPY_INNER, 0,  0,  1.0f,  NULL,                              NULL,                      SOUND_ENV_ELEVATOR1 | SOUND_VIBRATO},
    [OBJECT_TYPE_PLATFORM_LOOPING]   = {"Looping Platform",   &mb64_btn_loopplatform,       bhvLoopingPlatform,              TILE_SIZE/2, MODEL_LOOPINGP,              OBJ_TYPE_TRAJECTORY,                            OBJ_OCCUPY_INNER, 0,  0,  1.0f,  NULL,                              NULL,                      SOUND_ENV_ELEVATOR1 | SOUND_VIBRATO},
    [OBJECT_TYPE_BOWLING_BALL]       = {"Bowling Ball",       &mb64_btn_bowlingball,        bhvBobBowlingBallSpawner,        TILE_SIZE/2, MODEL_BOWLING_BALL,          OBJ_TYPE_BILLBOARD | OBJ_TYPE_TRAJECTORY,       OBJ_OCCUPY_INNER, 0,  0,  1.0f,  NULL,                              NULL,                      SOUND_GENERAL_QUIET_POUND1 | SOUND_VIBRATO},
    [OBJECT_TYPE_KOOPA_THE_QUICK]    = {"Koopa the Quick",    &mb64_btn_ktq,                bhvKoopa,                        0,           MODEL_KOOPA_WITH_SHELL,      OBJ_TYPE_TRAJECTORY | OBJ_TYPE_STAR,            OBJ_OCCUPY_FULL,  0,  1,  3.0f,  koopa_seg6_anims_06011364,         df_ktq,                    SOUND_OBJ_KOOPA_TALK},
    [OBJECT_TYPE_PURPLE_SWITCH]      = {"Purple Switch",      &mb64_btn_purpleswitch,       bhvFloorSwitchHiddenObjects,     0,           MODEL_PURPLE_SWITCH,         0,                                              OBJ_OCCUPY_INNER, 0,  0,  1.28f, NULL,                              NULL,                      SOUND_GENERAL2_PURPLE_SWITCH},
    [OBJECT_TYPE_TIMED_BOX]          = {"Timed Box",          &mb64_btn_timedbox,           bhvHiddenObject,                 0,           MODEL_BREAKABLE_BOX,         0,                                              OBJ_OCCUPY_OUTER, 0,  0,  1.0f,  NULL,                              df_timedbox,               SOUND_GENERAL2_SWITCH_TICK_FAST},
    [OBJECT_TYPE_RECOVERY_HEART]     = {"Recovery Heart",     &mb64_btn_recoveryheart,      bhvRecoveryHeart,                TILE_SIZE/2, MODEL_HEART,                 0,                                              OBJ_OCCUPY_INNER, 0,  0,  1.0f,  NULL,                              df_heart,                  SOUND_GENERAL_HEART_SPIN},
    [OBJECT_TYPE_TEST_MARIO]         = {"Save & Test",        &mb64_btn_check,              NULL,                            0,           MODEL_MARIO,                 0,                                              OBJ_OCCUPY_FULL,  0,  0,  1.0f,  mario_btcm_anims,                  NULL,                      0},
    [OBJECT_TYPE_THWOMP]             = {"Thwomp",             &mb64_btn_thwomp,             bhvThwomp,                       0,           MODEL_THWOMP_MAKER,          0,                                              OBJ_OCCUPY_FULL,  0,  2,  1.5f,  NULL,                              NULL,                      SOUND_OBJ_THWOMP},
    [OBJECT_TYPE_WHOMP]              = {"Whomp",              &mb64_btn_whomp,              bhvSmallWhomp,                   0,           MODEL_WHOMP_MAKER,           OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_FULL,  10, 1,  1.0f,  whomp_seg6_anims_06020A04,         NULL,                      SOUND_OBJ_WHOMP},
    [OBJECT_TYPE_GRINDEL]            = {"Grindel",            &mb64_btn_grindel,            bhvGrindel,                      0,           MODEL_MAKER_GRINDEL,         0,                                              OBJ_OCCUPY_FULL,  0,  2,  1.0f,  NULL,                              df_grindel,                SOUND_OBJ_KING_BOBOMB_JUMP},
    [OBJECT_TYPE_LAKITU]             = {"Lakitu",             &mb64_btn_lakitu,             bhvEnemyLakitu,                  TILE_SIZE/2, MODEL_LAKITU_MAKER,          OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 5,  5,  1.0f,  lakitu_enemy_seg5_anims_050144D4,  df_lakitu,                 SOUND_OBJ_EVIL_LAKITU_THROW},
    [OBJECT_TYPE_FLY_GUY]            = {"Fly Guy",            &mb64_btn_flyguy,             bhvFlyGuy,                       TILE_SIZE/2, MODEL_FLYGUY,                OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 2,  0,  1.5f,  flyguy_seg8_anims_08011A64,        df_flyguy,                 SOUND_OBJ_KOOPA_FLYGUY_DEATH},
    [OBJECT_TYPE_SNUFIT]             = {"Snufit",             &mb64_btn_snufit,             bhvSnufit,                       TILE_SIZE/2, MODEL_MAKER_SNUFIT,          OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 2,  0,  1.0f,  NULL,                              df_snufit,                 SOUND_OBJ_SNUFIT_SHOOT},
    [OBJECT_TYPE_AMP]                = {"Amp",                &mb64_btn_amp,                bhvCirclingAmp,                  TILE_SIZE/2, MODEL_AMP,                   0,                                              OBJ_OCCUPY_OUTER, 0,  0,  1.0f,  amp_anims,                         df_circling_amp,           SOUND_AIR_AMP_PREVIEW},
    [OBJECT_TYPE_BOO]                = {"Boo",                &mb64_btn_boo,                bhvBoo,                          TILE_SIZE/2, MODEL_MAKER_BOO,             OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS,    OBJ_OCCUPY_INNER, 0,  0,  1.0f,  NULL,                              df_boo,                    SOUND_OBJ_BOO_LAUGH_LONG},
    [OBJECT_TYPE_MR_I]               = {"Mr. I",              &mb64_btn_mri,                bhvMrI,                          0,           MODEL_MAKER_MRI,             OBJ_TYPE_IMBUABLE | OBJ_TYPE_BILLBOARD,         OBJ_OCCUPY_INNER, 5,  1,  1.0f,  NULL,                              df_mri,                    SOUND_OBJ_MRI_SHOOT},
    [OBJECT_TYPE_SCUTTLEBUG]         = {"Scuttlebug",         &mb64_btn_scuttlebug,         bhvScuttlebug,                   0,           MODEL_MAKER_SCUTTLEBUG,      OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 3,  0,  1.0f,  scuttlebug_seg6_anims_06015064,    NULL,                      SOUND_OBJ2_SCUTTLEBUG_ALERT},
    [OBJECT_TYPE_BOWSER_BOMB]        = {"Bowser Bomb",        &mb64_btn_bowserbomb,         bhvBowserBomb,                   TILE_SIZE/2, MODEL_MAKER_BOWSER_BOMB,     0,                                              OBJ_OCCUPY_INNER, 0,  0,  1.0f,  NULL,                              NULL,                      SOUND_GENERAL2_QUIET_EXPLOSION},
    [OBJECT_TYPE_FIRE_SPINNER]       = {"Fire Spinner",       &mb64_btn_firespinner,        bhvLllRotatingBlockWithFireBars, 0,           MODEL_MAKER_FIREBAR,         0,                                              OBJ_OCCUPY_INNER, 0,  0,  1.0f,  NULL,                              df_fire_spinner,           SOUND_OBJ_FLAME_BLOWN},
    [OBJECT_TYPE_COIN_FORMATION]     = {"Coin Formation",     &mb64_btn_coinline,           bhvCoinFormation,                0,           MODEL_NONE,                  0,                                              OBJ_OCCUPY_FULL,  0,  0,  1.0f,  NULL,                              df_coin_formation,         SOUND_GENERAL_COIN_MULTI},
    [OBJECT_TYPE_RED_FLAME]          = {"Red Flame",          &mb64_btn_redflame,           bhvFlame,                        90,          MODEL_RED_FLAME,             OBJ_TYPE_BILLBOARD,                             OBJ_OCCUPY_INNER, 0,  0,  7.0f,  NULL,                              df_flame,                  SOUND_OBJ_FLAME_BLOWN},
    [OBJECT_TYPE_BLUE_FLAME]         = {"Blue Flame",         &mb64_btn_blueflame,          bhvFlame,                        90,          MODEL_BLUE_FLAME,            OBJ_TYPE_BILLBOARD,                             OBJ_OCCUPY_INNER, 0,  0,  7.0f,  NULL,                              df_flame,                  SOUND_OBJ_FLAME_BLOWN},
    [OBJECT_TYPE_FIRE_SPITTER]       = {"Fire Spitter",       &mb64_btn_firespitter,        bhvFireSpitter,                  TILE_SIZE/2, MODEL_BOWLING_BALL,          OBJ_TYPE_BILLBOARD,                             OBJ_OCCUPY_INNER, 0,  0,  0.2f,  NULL,                              NULL,                      SOUND_OBJ_FLAME_BLOWN},
    [OBJECT_TYPE_FLAMETHROWER]       = {"Flamethrower",       &mb64_btn_flamethrower,       bhvFlamethrower,                 TILE_SIZE/2, MODEL_MAKER_FLAMETHROWER,    0,                                              OBJ_OCCUPY_FULL,  0,  5,  1.0f,  NULL,                              NULL,                      SOUND_OBJ_FLAME_BLOWN},
    [OBJECT_TYPE_SPINDRIFT]          = {"Spindrift",          &mb64_btn_spindrift,          bhvSpindrift,                    0,           MODEL_MAKER_SPINDRIFT,       OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 3,  0,  1.0f,  spindrift_seg5_anims_05002D68,     NULL,                      SOUND_ACTION_TWIRL},
    [OBJECT_TYPE_MR_BLIZZARD]        = {"Mr. Blizzard",       &mb64_btn_mrblizzard,         bhvMrBlizzard,                   0,           MODEL_MAKER_BLIZZARD,        OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 3,  0,  1.0f,  snowman_seg5_anims_0500D118,       df_blizzard,               SOUND_OBJ2_SCUTTLEBUG_ALERT},
    [OBJECT_TYPE_MONEYBAG]           = {"Moneybag",           &mb64_btn_moneybag,           bhvMoneybagHidden,               0,           MODEL_MONEYBAG,              OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS,    OBJ_OCCUPY_INNER, 0,  1,  1.0f,  moneybag_seg6_anims_06005E5C,      df_moneybag,               SOUND_GENERAL_MONEYBAG_BOING_LOWPRIO},
    [OBJECT_TYPE_SKEETER]            = {"Skeeter",            &mb64_btn_skeeter,            bhvSkeeter,                      0,           MODEL_MAKER_SKEETER,         OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_INNER, 3,  0,  1.0f,  skeeter_seg6_anims_06007DE0,       df_skeeter,                SOUND_OBJ_SKEETER_WALK},
    [OBJECT_TYPE_POKEY]              = {"Pokey",              &mb64_btn_pokey,              bhvPokey,                        0,           MODEL_MAKER_POKEY_HEAD,      OBJ_TYPE_IMBUABLE | OBJ_TYPE_BILLBOARD,         OBJ_OCCUPY_INNER, 5,  5,  3.0f,  NULL,                              df_pokey,                  SOUND_OBJ_POKEY_DEATH},
    [OBJECT_TYPE_BBOX_SMALL]         = {"Throwable Box",      &mb64_btn_smallbox,           bhvBreakableBoxSmall,            0,           MODEL_BREAKABLE_BOX_SMALL,   0,                                              OBJ_OCCUPY_INNER, 3,  0,  0.31f, NULL,                              df_corkbox,                SOUND_GENERAL_BOX_PREVIEW},
    [OBJECT_TYPE_BBOX_NORMAL]        = {"Breakable Box",      &mb64_btn_box,                bhvBreakableBox,                 0,           MODEL_BREAKABLE_BOX,         OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS,    OBJ_OCCUPY_FULL,  0,  0,  1.0f,  NULL,                              df_corkbox,                SOUND_GENERAL_BOX_PREVIEW},
    [OBJECT_TYPE_BBOX_CRAZY]         = {"Crazy Box",          &mb64_btn_crazybox,           bhvJumpingBox,                   0,           MODEL_BREAKABLE_BOX_SMALL,   0,                                              OBJ_OCCUPY_INNER, 5,  0,  0.38f, NULL,                              df_crazybox,               SOUND_GENERAL_CRAZY_BOX_BOING_SLOW},
    [OBJECT_TYPE_DIAMOND]            = {"Water Diamond",      &mb64_btn_waterdiamond,       bhvWaterLevelDiamond,            0,           MODEL_MAKER_DIAMOND,         0,                                              OBJ_OCCUPY_INNER, 0,  0,  1.0f,  NULL,                              NULL,                      SOUND_GENERAL_WATER_LEVEL_TRIG},
    [OBJECT_TYPE_SIGN]               = {"Bill Board",         &mb64_btn_signpost,           bhvMessagePanel,                 0,           MODEL_WOODEN_SIGNPOST,       OBJ_TYPE_HAS_DIALOG,                            OBJ_OCCUPY_INNER, 0,  0,  1.0f,  NULL,                              NULL,                      SOUND_ACTION_READ_SIGN},
    [OBJECT_TYPE_BUDDY]              = {"Bob-omb Buddy",      &mb64_btn_bobombbuddy,        bhvBobombBuddy,                  0,           MODEL_BOBOMB_BUDDY,          OBJ_TYPE_HAS_DIALOG,                            OBJ_OCCUPY_INNER, 0,  0,  1.0f,  bobomb_anims,                      NULL,                      SOUND_OBJ_BOBOMB_BUDDY_TALK},
    [OBJECT_TYPE_BUTTON]             = {"On-Off Button",      &mb64_btn_redswitch,          bhvOnOffButton,                  0,           MODEL_MAKER_BUTTON,          0,                                              OBJ_OCCUPY_INNER, 0,  0,  1.0f,  NULL,                              df_button,                 SOUND_GENERAL_BUTTON_PRESS},
    [OBJECT_TYPE_ON_OFF_BLOCK]       = {"On-Off Block",       &mb64_btn_redblock,           bhvOnOffBlock,                   0,           MODEL_MAKER_BLOCK_OFF,       0,                                              OBJ_OCCUPY_OUTER, 0,  0,  1.0f,  NULL,                              df_block,                  SOUND_GENERAL_BUTTON_PRESS},
    [OBJECT_TYPE_WOODPLAT]           = {"Wooden Platform",    &mb64_btn_woodplatform,       bhvWoodPlat,                     0,           MODEL_MAKER_WOODPLAT,        0,                                              OBJ_OCCUPY_FULL,  0,  1,  1.0f,  NULL,                              df_woodplat,               SOUND_ACTION_TERRAIN_STEP + (SOUND_TERRAIN_SPOOKY << 16)},
    [OBJECT_TYPE_RFBOX]              = {"Reinforced Box",     &mb64_btn_rfbox,              bhvBreakableBoxRF,               0,           MODEL_MAKER_RFBOX,           OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS,    OBJ_OCCUPY_FULL,  0,  0,  1.0f,  NULL,                              NULL,                      SOUND_OBJ_BULLY_METAL},
    [OBJECT_TYPE_CULL_PREVIEW]       = {"",                   &mb64_btn_cullmarker,         bhvStaticObject,                 TILE_SIZE/2, MODEL_CULL_MARKER,           OBJ_TYPE_BILLBOARD,                             OBJ_OCCUPY_INNER, 0,  0,  1.f,   NULL,                              NULL,                      0},
    [OBJECT_TYPE_SHOWRUNNER]         = {"Showrunner",         &mb64_btn_showrunner,         bhvShowrunner,                   0,           MODEL_MAKER_SHOWRUNNER,      OBJ_TYPE_IMBUABLE,                              OBJ_OCCUPY_FULL,  50, 39, 1.0f,  showrunner_anims,                  NULL,                      SOUND_OBJ_MRI_SHOOT},
    [OBJECT_TYPE_CROWBAR]            = {"Crowbar",            &mb64_btn_pipebar,            bhvCrowbarPower,                 TILE_SIZE/2, MODEL_MAKER_CROWBAR,         0,                                              OBJ_OCCUPY_INNER, 0,  0,  1.0f,  NULL,                              df_crowbar,                SOUND_MENU_EXIT_PIPE},
    [OBJECT_TYPE_MASK]               = {"Bullet Bill Mask",   &mb64_btn_bulletmask,         bhvBMask,                        TILE_SIZE/2, MODEL_MAKER_MASK,            0,                                              OBJ_OCCUPY_INNER, 0,  0,  1.0f,  NULL,                              df_mask,                   SOUND_MENU_EXIT_PIPE},
    [OBJECT_TYPE_TOAD]               = {"Toad",               &mb64_btn_toad,               bhvMakerToad,                    0,           MODEL_MAKER_TOAD,            OBJ_TYPE_HAS_DIALOG,                            OBJ_OCCUPY_INNER, 0,  0,  1.0f,  toad_seg6_anims_0600FB58,          df_toad,                   SOUND_ACTION_READ_SIGN},
    [OBJECT_TYPE_TUXIE]              = {"Tuxie",              &mb64_btn_tuxie,              bhvMakerTuxie,                   0,           MODEL_MAKER_TUXIE,           OBJ_TYPE_HAS_DIALOG,                            OBJ_OCCUPY_INNER, 0,  0,  1.0f,  penguin_seg5_anims_05008B74,       NULL,                      SOUND_OBJ2_BABY_PENGUIN_YELL},
    [OBJECT_TYPE_UKIKI]              = {"Ukiki",              &mb64_btn_ukiki,              bhvMakerUkiki,                   0,           MODEL_MAKER_UKIKI,           OBJ_TYPE_HAS_DIALOG,                            OBJ_OCCUPY_INNER, 0,  0,  1.0f,  ukiki_seg5_anims_05015784,         df_ukiki,                  SOUND_OBJ_UKIKI_CHATTER_SHORT},
    [OBJECT_TYPE_MOLEMAN]            = {"Moleman",            &mb64_btn_moleman,            bhvMoleman,                      65,          MODEL_MAKER_MOLEMAN,         OBJ_TYPE_HAS_DIALOG,                            OBJ_OCCUPY_INNER, 0,  0,  1.0f,  moleman3_anims,                    NULL,                      SOUND_ACTION_READ_SIGN},
    [OBJECT_TYPE_COBIE]              = {"Cobie",              &mb64_btn_cowboy,             bhvCobie,                        0,           MODEL_MAKER_COBIE,           OBJ_TYPE_HAS_DIALOG,                            OBJ_OCCUPY_INNER, 0,  0,  1.0f,  cobie2_anims,                      NULL,                      SOUND_ACTION_READ_SIGN},
    [OBJECT_TYPE_CONVEYOR]           = {"Conveyor",           &mb64_btn_conveyor,           bhvConveyor,                     0,           MODEL_MAKER_CONVEYOR_HALF,   0,                                              OBJ_OCCUPY_FULL,  0,  0,  1.0f,  NULL,                              df_conveyor,               SOUND_OBJ_HEAVEHO_PREVIEW},
    [OBJECT_TYPE_TIMEDBLOCK]         = {"Inverted Timed Box", &mb64_btn_invertedtimedblock, bhvTimedBlock,                   0,           MODEL_MAKER_BLOCK_OFF,       0,                                              OBJ_OCCUPY_OUTER, 0,  0,  1.0f,  NULL,                              df_timedblock,             SOUND_GENERAL2_SWITCH_TICK_FAST},
    [OBJECT_TYPE_TRIGGER]            = {"Star Trigger",       &mb64_btn_trigger,            bhvStaticObject,                 TILE_SIZE/2, MODEL_MAKER_IMBUE_TRIGGER,   OBJ_TYPE_BILLBOARD,                             OBJ_OCCUPY_INNER, 0,  0,  1.0f,  NULL,                              NULL,                      SOUND_MENU_COLLECT_SECRET},
    [OBJECT_TYPE_TRIGGER_STAR]       = {"Trigger Star Spawn", &mb64_btn_triggerstar,        bhvHiddenStar,                   TILE_SIZE/2, MODEL_TRANSPARENT_STAR,      OBJ_TYPE_STAR,                                  OBJ_OCCUPY_INNER, 0,  0,  1.0f,  NULL,                              df_star,                   SOUND_MENU_STAR_SOUND | SOUND_VIBRATO},
};

// same-object parameter tables (leaf variants share one object/tile id)
static struct mb64_ui_param mb64_tree_params[] = {
    { "Bubbly", &mb64_btn_bubblytree, 0 },
    { "Palm",   &mb64_btn_palmtree,   1 },
    { "Spiky",  &mb64_btn_spikytree,  2 },
    { "Snowy",  &mb64_btn_snowytree,  3 },
    { "Farm",   &mb64_btn_farmtree,   4 },
    { "Dead",   &mb64_btn_deadtree,   5 },
};
static struct mb64_ui_param mb64_excla_params[] = {
    { "One Coin",     &mb64_btn_questionbox, 4 },
    { "Three Coins",  &mb64_btn_questionbox, 5 },
    { "Ten Coins",    &mb64_btn_questionbox, 6 },
    { "Green Coin",   &mb64_btn_questionbox, 3 },
    { "Rocket Boots", &mb64_btn_rocketbox, 0 },
    { "Vanetal Cap",  &mb64_btn_vanetalbox, 1 },
    { "Koopa Shell",  &mb64_btn_exclamationbox, 2 },
};
static struct mb64_ui_param mb64_vexcla_params[] = {
    { "One Coin",    &mb64_btn_exclamationbox, 4 },
    { "Three Coins", &mb64_btn_exclamationbox, 5 },
    { "Ten Coins",   &mb64_btn_exclamationbox, 6 },
    { "Wing Cap",    &mb64_btn_wingbox, 0 },
    { "Metal Cap",   &mb64_btn_metalbox, 1 },
    { "Vanish Cap",  &mb64_btn_vanishbox, 2 },
    { "Koopa Shell", &mb64_btn_exclamationbox, 3 },
};
static struct mb64_ui_param mb64_badge_params[] = {
    { "Lava Boost",       &mb64_btn_badgelava,       0 },
    { "Fall Damage",      &mb64_btn_badgefall,       1 },
    { "Defense",          &mb64_btn_badgedefense,    2 },
    { "One Hit",          &mb64_btn_badgedamage,     3 },
    { "Gills",            &mb64_btn_badgegills,      4 },
    { "Fins",             &mb64_btn_badgefins,       5 },
    { "HP Regen",         &mb64_btn_badgehp,         6 },
    { "Mana Regen",       &mb64_btn_badgemana,       7 },
    { "Greed",            &mb64_btn_badgegreed,      8 },
    { "Double Time",      &mb64_btn_badgetime,       9 },
    { "Magnet",           &mb64_btn_badgemagnet,     10 },
    { "Burn",             &mb64_btn_badgeburn,       11 },
    { "Squish",           &mb64_btn_badgesquish,     12 },
    { "Feather",          &mb64_btn_badgefeather,    13 },
    { "Weight",           &mb64_btn_badgeweight,     14 },
    { "Sticky",           &mb64_btn_badgesticky,     15 },
    { "Fast Foot",        &mb64_btn_badgefeet,       16 },
    { "Heal Plus",        &mb64_btn_badgeheal,       17 },
    { "Bottomless",       &mb64_btn_badgebottomless, 18 },
    { "Slow Fall",        &mb64_btn_badgeslowfall,   19 },
    { "Brittle Burden",   &mb64_btn_badgebrittle,    20 },
    { "Withering Burden", &mb64_btn_badgewither,     21 },
};
static struct mb64_ui_param mb64_formation_params[] = {
    { "Line",          &mb64_btn_coinline,         0 },
    { "Vertical Line", &mb64_btn_verticalcoinline, 1 },
    { "Ring",          &mb64_btn_coinring,         2 },
    { "Vertical Ring", &mb64_btn_verticalcoinring, 3 },
    { "Arrow",         &mb64_btn_coinarrow,        4 },
};
static struct mb64_ui_param mb64_fire_spinner_params[] = {
    { "Length: 2", NULL, 0 },
    { "Length: 3", NULL, 1 },
    { "Length: 4", NULL, 2 },
    { "Length: 5", NULL, 3 },
    { "Length: 6", NULL, 4 },
};
static struct mb64_ui_param mb64_button_params[] = {
    { "Red",  &mb64_btn_redswitch,  0 },
    { "Blue", &mb64_btn_blueswitch, 1 },
};
static struct mb64_ui_param mb64_block_params[] = {
    { "Red",  &mb64_btn_redblock,  0 },
    { "Blue", &mb64_btn_blueblock, 1 },
};
static struct mb64_ui_param mb64_woodplat_params[] = {
    { "Thin", &mb64_btn_woodplatform,     0 },
    { "Full", &mb64_btn_fullwoodplatform, 1 },
};
static struct mb64_ui_param mb64_conveyor_params[] = {
    { "Thin",               &mb64_btn_conveyor,        0 },
    { "Full",               &mb64_btn_fullconveyor,    1 },
    { "Upwards",            &mb64_btn_upconveyor,      2 },
    { "Downwards",          &mb64_btn_downconveyor,    3 },
    { "Thin (On-Off)",      &mb64_btn_redconveyor,     4 },
    { "Full (On-Off)",      &mb64_btn_redfullconveyor, 5 },
    { "Upwards (On-Off)",   &mb64_btn_redupconveyor,   6 },
    { "Downwards (On-Off)", &mb64_btn_reddownconveyor, 7 },
};

#define MB64_GAME_MASK_VANILLA (1 << MB64_GAME_VANILLA)
#define MB64_GAME_MASK_BTCM    (1 << MB64_GAME_BTCM)
#define MB64_GAME_MASK_BOTH    (MB64_GAME_MASK_VANILLA | MB64_GAME_MASK_BTCM)

#define FCHILD(id)   { id, MB64_GAME_MASK_BOTH }
#define FCHILD_V(id) { id, MB64_GAME_MASK_VANILLA }
#define FCHILD_B(id) { id, MB64_GAME_MASK_BTCM }

static struct mb64_folder_child mb64_folder_slabs[] = {
    FCHILD(MB64_BUTTON_SLAB),
    FCHILD(MB64_BUTTON_VSLAB),
};
static struct mb64_folder_child mb64_folder_slopes[] = {
    FCHILD(MB64_BUTTON_SLOPE),
    FCHILD(MB64_BUTTON_CORNER),
    FCHILD(MB64_BUTTON_ICORNER),
    FCHILD(MB64_BUTTON_SSLOPE),
};
static struct mb64_folder_child mb64_folder_gentle_slopes[] = {
    FCHILD(MB64_BUTTON_LGENTLE),
    FCHILD(MB64_BUTTON_UGENTLE),
};
static struct mb64_folder_child mb64_folder_diagonal_slopes[] = {
    FCHILD(MB64_BUTTON_SCORNER),
    FCHILD(MB64_BUTTON_ISCORNER),
};
static struct mb64_folder_child mb64_folder_special_tiles[] = {
    FCHILD(MB64_BUTTON_WATER),
    FCHILD(MB64_BUTTON_FENCE),
    FCHILD(MB64_BUTTON_BARS),
    FCHILD(MB64_BUTTON_POLE),
    FCHILD(MB64_BUTTON_CULL),
    FCHILD(MB64_BUTTON_TROLL),
};
static struct mb64_folder_child mb64_folder_platforms[] = {
    FCHILD(MB64_BUTTON_MPLAT),
    FCHILD(MB64_BUTTON_MPLAT_LOOP),
    FCHILD(MB64_BUTTON_WOODPLAT),
    FCHILD(MB64_BUTTON_CONVEYOR),
    FCHILD(MB64_BUTTON_NOTEBLOCK),
};
static struct mb64_folder_child mb64_folder_switches[] = {
    FCHILD(MB64_BUTTON_PURPLE_SWITCH),
    FCHILD(MB64_BUTTON_TIMED_BOX),
    FCHILD(MB64_BUTTON_TIMED_BLOCK),
    FCHILD(MB64_BUTTON_BUTTON),
    FCHILD(MB64_BUTTON_BLOCK),
    FCHILD(MB64_BUTTON_DIAMOND),
};
static struct mb64_folder_child mb64_folder_boxes[] = {
    FCHILD(MB64_BUTTON_BREAKABLE),
    FCHILD(MB64_BUTTON_RFBOX),
    FCHILD(MB64_BUTTON_SMALL_BOX),
    FCHILD(MB64_BUTTON_CRAZY_BOX),
};
static struct mb64_folder_child mb64_folder_fire[] = {
    FCHILD(MB64_BUTTON_FIRE),
    FCHILD(MB64_BUTTON_BLUE_FLAME),
    FCHILD(MB64_BUTTON_FIRE_SPINNER),
    FCHILD(MB64_BUTTON_FIRE_SPITTER),
    FCHILD(MB64_BUTTON_FLAMETHROWER),
};
static struct mb64_folder_child mb64_folder_power_stars[] = {
    FCHILD(MB64_BUTTON_STAR),
    FCHILD(MB64_BUTTON_RED_COIN_STAR),
    FCHILD(MB64_BUTTON_TRIGGER_STAR),
    FCHILD(MB64_BUTTON_TRIGGER),
};
static struct mb64_folder_child mb64_folder_coins[] = {
    FCHILD(MB64_BUTTON_COIN),
    FCHILD_B(MB64_BUTTON_GCOIN),
    FCHILD(MB64_BUTTON_RCOIN),
    FCHILD(MB64_BUTTON_BCOIN),
    FCHILD(MB64_BUTTON_BLUE_COIN_SWITCH),
    FCHILD(MB64_BUTTON_FORMATION),
};
static struct mb64_folder_child mb64_folder_npcs[] = {
    FCHILD(MB64_BUTTON_SIGN),
    FCHILD(MB64_BUTTON_BUDDY),
    FCHILD_V(MB64_BUTTON_TOAD),
    FCHILD_V(MB64_BUTTON_TUXIE),
    FCHILD_V(MB64_BUTTON_UKIKI),
    FCHILD_B(MB64_BUTTON_MOLEMAN),
    FCHILD_B(MB64_BUTTON_COBIE),
};
static struct mb64_folder_child mb64_folder_generic_enemies[] = {
    FCHILD(MB64_BUTTON_GOOMBA),
    FCHILD(MB64_BUTTON_BIG_GOOMBA),
    FCHILD(MB64_BUTTON_TINY_GOOMBA),
    FCHILD(MB64_BUTTON_PIRANHA),
    FCHILD(MB64_BUTTON_BIG_PIRANHA),
    FCHILD(MB64_BUTTON_TINY_PIRANHA),
    FCHILD(MB64_BUTTON_KOOPA),
};
static struct mb64_folder_child mb64_folder_mechanical_enemies[] = {
    FCHILD(MB64_BUTTON_BOBOMB),
    FCHILD(MB64_BUTTON_CHUCKYA),
    FCHILD(MB64_BUTTON_MOTOS),
    FCHILD(MB64_BUTTON_HEAVEHO),
    FCHILD(MB64_BUTTON_BULLET),
    FCHILD(MB64_BUTTON_BBALL),
};
static struct mb64_folder_child mb64_folder_flying_enemies[] = {
    FCHILD(MB64_BUTTON_LAKITU),
    FCHILD(MB64_BUTTON_FLYGUY),
    FCHILD(MB64_BUTTON_SNUFIT),
    FCHILD(MB64_BUTTON_AMP),
};
static struct mb64_folder_child mb64_folder_bullies[] = {
    FCHILD(MB64_BUTTON_BULLY),
    FCHILD(MB64_BUTTON_CHILL_BULLY),
    FCHILD(MB64_BUTTON_BIG_BULLY),
    FCHILD(MB64_BUTTON_CHIEF_CHILLY),
};
static struct mb64_folder_child mb64_folder_stone_enemies[] = {
    FCHILD(MB64_BUTTON_THWOMP),
    FCHILD(MB64_BUTTON_GRINDEL),
    FCHILD(MB64_BUTTON_WHOMP),
};
static struct mb64_folder_child mb64_folder_misc_enemies[] = {
    FCHILD(MB64_BUTTON_SCUTTLEBUG),
    FCHILD(MB64_BUTTON_BOO),
    FCHILD(MB64_BUTTON_MR_I),
    FCHILD(MB64_BUTTON_SPINDRIFT),
    FCHILD(MB64_BUTTON_BLIZZARD),
    FCHILD(MB64_BUTTON_MONEYBAG),
    FCHILD(MB64_BUTTON_SKEETER),
    FCHILD(MB64_BUTTON_POKEY),
};
static struct mb64_folder_child mb64_folder_btcm_enemies[] = {
    FCHILD(MB64_BUTTON_REX),
    FCHILD(MB64_BUTTON_HAMMER_BRO),
    FCHILD(MB64_BUTTON_FIRE_BRO),
    FCHILD(MB64_BUTTON_PODOBOO),
    FCHILD(MB64_BUTTON_PHANTASM),
    FCHILD(MB64_BUTTON_CHICKEN),
    FCHILD(MB64_BUTTON_CRABLET),
};
static struct mb64_folder_child mb64_folder_vanilla_bosses[] = {
    FCHILD(MB64_BUTTON_BOWSER),
    FCHILD(MB64_BUTTON_MINE),
    FCHILD(MB64_BUTTON_KING_BOBOMB),
    FCHILD(MB64_BUTTON_KING_WHOMP),
    FCHILD(MB64_BUTTON_BIG_BOO),
    FCHILD(MB64_BUTTON_WIGGLER),
};
static struct mb64_folder_child mb64_folder_btcm_bosses[] = {
    FCHILD(MB64_BUTTON_SHOWRUN),
    FCHILD(MB64_BUTTON_KING_WHOMP),
    FCHILD(MB64_BUTTON_BIG_BOO),
};
static struct mb64_folder_child mb64_folder_powerups[] = {
    FCHILD(MB64_BUTTON_POWER),
    FCHILD(MB64_BUTTON_MASK),
    FCHILD(MB64_BUTTON_BADGE),
};

#define BTN_LEAF(mode, objId) { mode, 0, { .leaf = { objId, NULL } } }
#define BTN_PARAMS(mode, objId, params) { mode, ARRAY_COUNT(params), { .leaf = { objId, params } } }
#define BTN_FOLDER(name, icon, children) { MB64_PM_NONE, ARRAY_COUNT(children), { .folder = { name, children, icon } } }

struct mb64_ui_button_type mb64_ui_buttons[MB64_BUTTON_COUNT] = {
    [MB64_BUTTON_SETTINGS]           = BTN_LEAF(MB64_PM_ACTION, OBJECT_TYPE_SETTINGS),
    [MB64_BUTTON_TEST]               = BTN_LEAF(MB64_PM_ACTION, OBJECT_TYPE_TEST_MARIO),

    [MB64_BUTTON_TERRAIN]            = BTN_LEAF(MB64_PM_TILE,   TILE_TYPE_BLOCK),
    [MB64_BUTTON_SLAB]               = BTN_LEAF(MB64_PM_TILE,   TILE_TYPE_SLAB),
    [MB64_BUTTON_VSLAB]              = BTN_LEAF(MB64_PM_TILE,   TILE_TYPE_SSLAB),
    [MB64_BUTTON_SLOPE]              = BTN_LEAF(MB64_PM_TILE,   TILE_TYPE_SLOPE),
    [MB64_BUTTON_CORNER]             = BTN_LEAF(MB64_PM_TILE,   TILE_TYPE_CORNER),
    [MB64_BUTTON_ICORNER]            = BTN_LEAF(MB64_PM_TILE,   TILE_TYPE_ICORNER),
    [MB64_BUTTON_SSLOPE]             = BTN_LEAF(MB64_PM_TILE,   TILE_TYPE_SSLOPE),
    [MB64_BUTTON_LGENTLE]            = BTN_LEAF(MB64_PM_TILE,   TILE_TYPE_LGENTLE),
    [MB64_BUTTON_UGENTLE]            = BTN_LEAF(MB64_PM_TILE,   TILE_TYPE_UGENTLE),
    [MB64_BUTTON_SCORNER]            = BTN_LEAF(MB64_PM_TILE,   TILE_TYPE_SCORNER),
    [MB64_BUTTON_ISCORNER]           = BTN_LEAF(MB64_PM_TILE,   TILE_TYPE_ISCORNER),
    [MB64_BUTTON_WATER]              = BTN_LEAF(MB64_PM_TILE,   TILE_TYPE_WATER),
    [MB64_BUTTON_FENCE]              = BTN_LEAF(MB64_PM_TILE,   TILE_TYPE_FENCE),
    [MB64_BUTTON_BARS]               = BTN_LEAF(MB64_PM_TILE,   TILE_TYPE_BARS),
    [MB64_BUTTON_POLE]               = BTN_LEAF(MB64_PM_TILE,   TILE_TYPE_POLE),
    [MB64_BUTTON_CULL]               = BTN_LEAF(MB64_PM_TILE,   TILE_TYPE_CULL),
    [MB64_BUTTON_TROLL]              = BTN_LEAF(MB64_PM_TILE,   TILE_TYPE_TROLL),
    [MB64_BUTTON_TREE]               = BTN_PARAMS(MB64_PM_OBJ,  OBJECT_TYPE_TREE,           mb64_tree_params),

    [MB64_BUTTON_STAR]               = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_STAR),
    [MB64_BUTTON_RED_COIN_STAR]      = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_RED_COIN_STAR),
    [MB64_BUTTON_TRIGGER_STAR]       = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_TRIGGER_STAR),
    [MB64_BUTTON_TRIGGER]            = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_TRIGGER),
    [MB64_BUTTON_COIN]               = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_COIN),
    [MB64_BUTTON_GCOIN]              = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_GREEN_COIN),
    [MB64_BUTTON_RCOIN]              = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_RED_COIN),
    [MB64_BUTTON_BCOIN]              = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_BLUE_COIN),
    [MB64_BUTTON_BLUE_COIN_SWITCH]   = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_BLUE_COIN_SWITCH),
    [MB64_BUTTON_FORMATION]          = BTN_PARAMS(MB64_PM_OBJ,  OBJECT_TYPE_COIN_FORMATION, mb64_formation_params),
    [MB64_BUTTON_VEXCLA]             = BTN_PARAMS(MB64_PM_OBJ,  OBJECT_TYPE_EXCL_BOX,       mb64_vexcla_params),
    [MB64_BUTTON_EXCLA]              = BTN_PARAMS(MB64_PM_OBJ,  OBJECT_TYPE_EXCL_BOX,       mb64_excla_params),
    [MB64_BUTTON_POWER]              = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_CROWBAR),
    [MB64_BUTTON_MASK]               = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_MASK),
    [MB64_BUTTON_BADGE]              = BTN_PARAMS(MB64_PM_OBJ,  OBJECT_TYPE_BADGE,          mb64_badge_params),
    [MB64_BUTTON_HEART]              = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_RECOVERY_HEART),
    [MB64_BUTTON_SPAWN]              = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_MARIO_SPAWN),

    [MB64_BUTTON_MPLAT]              = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_PLATFORM_TRACK),
    [MB64_BUTTON_MPLAT_LOOP]         = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_PLATFORM_LOOPING),
    [MB64_BUTTON_WOODPLAT]           = BTN_PARAMS(MB64_PM_OBJ,  OBJECT_TYPE_WOODPLAT,       mb64_woodplat_params),
    [MB64_BUTTON_CONVEYOR]           = BTN_PARAMS(MB64_PM_OBJ,  OBJECT_TYPE_CONVEYOR,       mb64_conveyor_params),
    [MB64_BUTTON_NOTEBLOCK]          = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_NOTEBLOCK),
    [MB64_BUTTON_PURPLE_SWITCH]      = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_PURPLE_SWITCH),
    [MB64_BUTTON_TIMED_BOX]          = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_TIMED_BOX),
    [MB64_BUTTON_TIMED_BLOCK]        = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_TIMEDBLOCK),
    [MB64_BUTTON_BUTTON]             = BTN_PARAMS(MB64_PM_OBJ,  OBJECT_TYPE_BUTTON,         mb64_button_params),
    [MB64_BUTTON_BLOCK]              = BTN_PARAMS(MB64_PM_OBJ,  OBJECT_TYPE_ON_OFF_BLOCK,   mb64_block_params),
    [MB64_BUTTON_DIAMOND]            = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_DIAMOND),
    [MB64_BUTTON_BREAKABLE]          = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_BBOX_NORMAL),
    [MB64_BUTTON_RFBOX]              = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_RFBOX),
    [MB64_BUTTON_SMALL_BOX]          = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_BBOX_SMALL),
    [MB64_BUTTON_CRAZY_BOX]          = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_BBOX_CRAZY),
    [MB64_BUTTON_FIRE]               = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_RED_FLAME),
    [MB64_BUTTON_BLUE_FLAME]         = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_BLUE_FLAME),
    [MB64_BUTTON_FIRE_SPINNER]       = BTN_PARAMS(MB64_PM_OBJ,  OBJECT_TYPE_FIRE_SPINNER,   mb64_fire_spinner_params),
    [MB64_BUTTON_FIRE_SPITTER]       = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_FIRE_SPITTER),
    [MB64_BUTTON_FLAMETHROWER]       = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_FLAMETHROWER),
    [MB64_BUTTON_SIGN]               = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_SIGN),
    [MB64_BUTTON_BUDDY]              = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_BUDDY),
    [MB64_BUTTON_TOAD]               = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_TOAD),
    [MB64_BUTTON_TUXIE]              = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_TUXIE),
    [MB64_BUTTON_UKIKI]              = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_UKIKI),
    [MB64_BUTTON_MOLEMAN]            = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_MOLEMAN),
    [MB64_BUTTON_COBIE]              = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_COBIE),
    [MB64_BUTTON_KTQ]                = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_KOOPA_THE_QUICK),

    [MB64_BUTTON_GOOMBA]             = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_GOOMBA),
    [MB64_BUTTON_BIG_GOOMBA]         = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_BIG_GOOMBA),
    [MB64_BUTTON_TINY_GOOMBA]        = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_TINY_GOOMBA),
    [MB64_BUTTON_PIRANHA]            = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_PIRANHA_PLANT),
    [MB64_BUTTON_BIG_PIRANHA]        = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_BIG_PIRANHA_PLANT),
    [MB64_BUTTON_TINY_PIRANHA]       = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_TINY_PIRANHA_PLANT),
    [MB64_BUTTON_KOOPA]              = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_KOOPA),
    [MB64_BUTTON_BOBOMB]             = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_BOBOMB),
    [MB64_BUTTON_CHUCKYA]            = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_CHUCKYA),
    [MB64_BUTTON_MOTOS]              = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_MOTOS),
    [MB64_BUTTON_HEAVEHO]            = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_HEAVE_HO),
    [MB64_BUTTON_BULLET]             = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_BULLET_BILL),
    [MB64_BUTTON_BBALL]              = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_BOWLING_BALL),
    [MB64_BUTTON_LAKITU]             = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_LAKITU),
    [MB64_BUTTON_FLYGUY]             = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_FLY_GUY),
    [MB64_BUTTON_SNUFIT]             = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_SNUFIT),
    [MB64_BUTTON_AMP]                = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_AMP),
    [MB64_BUTTON_BULLY]              = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_BULLY),
    [MB64_BUTTON_CHILL_BULLY]        = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_CHILL_BULLY),
    [MB64_BUTTON_BIG_BULLY]          = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_BIG_BULLY),
    [MB64_BUTTON_CHIEF_CHILLY]       = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_BIG_CHILL_BULLY),
    [MB64_BUTTON_THWOMP]             = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_THWOMP),
    [MB64_BUTTON_GRINDEL]            = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_GRINDEL),
    [MB64_BUTTON_WHOMP]              = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_WHOMP),
    [MB64_BUTTON_SCUTTLEBUG]         = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_SCUTTLEBUG),
    [MB64_BUTTON_BOO]                = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_BOO),
    [MB64_BUTTON_MR_I]               = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_MR_I),
    [MB64_BUTTON_SPINDRIFT]          = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_SPINDRIFT),
    [MB64_BUTTON_BLIZZARD]           = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_MR_BLIZZARD),
    [MB64_BUTTON_MONEYBAG]           = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_MONEYBAG),
    [MB64_BUTTON_SKEETER]            = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_SKEETER),
    [MB64_BUTTON_POKEY]              = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_POKEY),
    [MB64_BUTTON_BOWSER]             = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_BOWSER),
    [MB64_BUTTON_MINE]               = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_BOWSER_BOMB),
    [MB64_BUTTON_KING_BOBOMB]        = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_KING_BOBOMB),
    [MB64_BUTTON_KING_WHOMP]         = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_KING_WHOMP),
    [MB64_BUTTON_BIG_BOO]            = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_BIG_BOO),
    [MB64_BUTTON_WIGGLER]            = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_WIGGLER),
    [MB64_BUTTON_REX]                = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_REX),
    [MB64_BUTTON_HAMMER_BRO]         = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_HAMMER_BRO),
    [MB64_BUTTON_FIRE_BRO]           = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_FIRE_BRO),
    [MB64_BUTTON_PODOBOO]            = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_PODOBOO),
    [MB64_BUTTON_PHANTASM]           = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_PHANTASM),
    [MB64_BUTTON_CHICKEN]            = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_CHICKEN),
    [MB64_BUTTON_CRABLET]            = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_CRABLET),
    [MB64_BUTTON_SHOWRUN]            = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_SHOWRUNNER),

    [MB64_BUTTON_PIPE]               = BTN_LEAF(MB64_PM_OBJ,    OBJECT_TYPE_WARP_PIPE),
    [MB64_BUTTON_BLANK]              = BTN_LEAF(MB64_PM_TILE,   TILE_TYPE_BLOCK),

    [MB64_FOLDER_GENTLE_SLOPES]      = BTN_FOLDER("Gentle Slopes",      &mb64_btn_folder_gentle_slopes,      mb64_folder_gentle_slopes),
    [MB64_FOLDER_SLOPES]             = BTN_FOLDER("Slopes",             &mb64_btn_folder_slopes,             mb64_folder_slopes),
    [MB64_FOLDER_PLATFORMS]          = BTN_FOLDER("Platforms",          &mb64_btn_folder_platforms,          mb64_folder_platforms),
    [MB64_FOLDER_SWITCHES]           = BTN_FOLDER("Switches",           &mb64_btn_folder_switches,           mb64_folder_switches),
    [MB64_FOLDER_BOXES]              = BTN_FOLDER("Boxes",              &mb64_btn_folder_boxes,              mb64_folder_boxes),
    [MB64_FOLDER_FIRE]               = BTN_FOLDER("Fire",               &mb64_btn_folder_fire,               mb64_folder_fire),
    [MB64_FOLDER_POWER_STARS]        = BTN_FOLDER("Power Stars",        &mb64_btn_folder_power_stars,        mb64_folder_power_stars),
    [MB64_FOLDER_COINS]              = BTN_FOLDER("Coins",              &mb64_btn_folder_coins,              mb64_folder_coins),
    [MB64_FOLDER_POWERUPS]           = BTN_FOLDER("Powerups",           &mb64_btn_folder_powerups,           mb64_folder_powerups),
    [MB64_FOLDER_NPCS]               = BTN_FOLDER("NPCs",               &mb64_btn_folder_npcs,               mb64_folder_npcs),
    [MB64_FOLDER_GENERIC_ENEMIES]    = BTN_FOLDER("Generic Enemies",    &mb64_btn_folder_generic_enemies,    mb64_folder_generic_enemies),
    [MB64_FOLDER_BULLIES]            = BTN_FOLDER("Bullies",            &mb64_btn_folder_bullies,            mb64_folder_bullies),
    [MB64_FOLDER_MECHANICAL_ENEMIES] = BTN_FOLDER("Mechanical Enemies", &mb64_btn_folder_mechanical_enemies, mb64_folder_mechanical_enemies),
    [MB64_FOLDER_MISC_ENEMIES]       = BTN_FOLDER("Misc. Enemies",      &mb64_btn_folder_misc_enemies,       mb64_folder_misc_enemies),
    [MB64_FOLDER_SLABS]              = BTN_FOLDER("Slabs",              &mb64_btn_folder_slabs,              mb64_folder_slabs),
    [MB64_FOLDER_STONE_ENEMIES]      = BTN_FOLDER("Stone Enemies",      &mb64_btn_folder_stone_enemies,      mb64_folder_stone_enemies),
    [MB64_FOLDER_FLYING_ENEMIES]     = BTN_FOLDER("Flying Enemies",     &mb64_btn_folder_flying_enemies,     mb64_folder_flying_enemies),
    [MB64_FOLDER_VANILLA_BOSSES]     = BTN_FOLDER("Bosses",             &mb64_btn_folder_vanilla_bosses,     mb64_folder_vanilla_bosses),
    [MB64_FOLDER_DIAGONAL_SLOPES]    = BTN_FOLDER("Diagonal Slopes",    &mb64_btn_folder_diagonal_slopes,    mb64_folder_diagonal_slopes),
    [MB64_FOLDER_SPECIAL_TILES]      = BTN_FOLDER("Special Tiles",      &mb64_btn_folder_special_tiles,      mb64_folder_special_tiles),
    [MB64_FOLDER_BTCM_ENEMIES]       = BTN_FOLDER("BTCM Enemies",       &mb64_btn_folder_btcm_enemies,       mb64_folder_btcm_enemies),
    [MB64_FOLDER_BTCM_BOSSES]        = BTN_FOLDER("Bosses",             &mb64_btn_folder_btcm_bosses,        mb64_folder_btcm_bosses),
};

u8 mb64_toolbar_defaults[MB64_TOOLBAR_SIZE] = {
    MB64_BUTTON_TERRAIN,
    MB64_BUTTON_SLOPE,
    MB64_BUTTON_BARS,
    MB64_BUTTON_TREE,
    MB64_BUTTON_COIN,
    MB64_BUTTON_STAR,
    MB64_BUTTON_GOOMBA,
    MB64_BUTTON_TEST,
    MB64_BUTTON_SETTINGS,
};

// per-game top-level layouts
#define _ MB64_BUTTON_BLANK
u8 mb64_toolbox_layout_vanilla[MB64_TOOLBOX_SIZE] = {
    // terrain
    MB64_BUTTON_TERRAIN, MB64_FOLDER_SLABS, MB64_FOLDER_SLOPES, MB64_FOLDER_GENTLE_SLOPES,
    MB64_FOLDER_DIAGONAL_SLOPES, MB64_FOLDER_SPECIAL_TILES, MB64_BUTTON_TREE, _, _,

    // scenery and collectibles
    MB64_FOLDER_POWER_STARS, MB64_FOLDER_COINS, MB64_BUTTON_VEXCLA,
    MB64_BUTTON_HEART, MB64_BUTTON_SPAWN, _, _, _, _,

    // objects
    MB64_FOLDER_PLATFORMS, MB64_FOLDER_SWITCHES, MB64_FOLDER_BOXES, MB64_FOLDER_FIRE,
    MB64_FOLDER_NPCS, MB64_BUTTON_KTQ, _, _, _,

    // enemies
    MB64_FOLDER_GENERIC_ENEMIES, MB64_FOLDER_MECHANICAL_ENEMIES, MB64_FOLDER_FLYING_ENEMIES,
    MB64_FOLDER_BULLIES, MB64_FOLDER_STONE_ENEMIES, MB64_FOLDER_MISC_ENEMIES,
    MB64_FOLDER_VANILLA_BOSSES, _, _,
};

u8 mb64_toolbox_layout_btcm[MB64_TOOLBOX_SIZE] = {
    // terrain
    MB64_BUTTON_TERRAIN, MB64_FOLDER_SLABS, MB64_FOLDER_SLOPES, MB64_FOLDER_GENTLE_SLOPES,
    MB64_FOLDER_DIAGONAL_SLOPES, MB64_FOLDER_SPECIAL_TILES, MB64_BUTTON_TREE, _, _,

    // scenery and collectibles
    MB64_FOLDER_POWER_STARS, MB64_FOLDER_COINS, MB64_BUTTON_EXCLA,
    MB64_FOLDER_POWERUPS, MB64_BUTTON_HEART, MB64_BUTTON_SPAWN, _, _, _,

    // objects
    MB64_FOLDER_PLATFORMS, MB64_FOLDER_SWITCHES, MB64_FOLDER_BOXES, MB64_FOLDER_FIRE,
    MB64_FOLDER_NPCS, _, _, _, _,

    // enemies
    MB64_FOLDER_GENERIC_ENEMIES, MB64_FOLDER_MECHANICAL_ENEMIES, MB64_FOLDER_FLYING_ENEMIES,
    MB64_FOLDER_BULLIES, MB64_FOLDER_STONE_ENEMIES, MB64_FOLDER_MISC_ENEMIES,
    MB64_FOLDER_BTCM_ENEMIES, MB64_FOLDER_BTCM_BOSSES, _,
};
#undef _

#define IMBUE_YELLOW 0xFFFF00FF
#define IMBUE_GREEN 0x00DD00FF
#define IMBUE_BLUE 0x0000FFFF
#define IMBUE_RED 0xFF0000FF
#define IMBUE_ORANGE 0xFFA500FF
#define IMBUE_PINK 0xe23a44FF

struct ImbueData imbue_table[] = {
    /* IMBUE_NONE */        {0, 0, 0},
    /* IMBUE_STAR */        {0, MODEL_MAKER_IMBUE_STAR, IMBUE_YELLOW},
    /* IMBUE_THREE_COINS */ {3, MODEL_MAKER_IMBUE_COIN, IMBUE_YELLOW},
    /* IMBUE_ONE_COIN */    {1, MODEL_MAKER_IMBUE_COIN, IMBUE_YELLOW},
    /* IMBUE_GREEN_COIN */  {3, MODEL_MAKER_IMBUE_COIN, IMBUE_GREEN},
    /* IMBUE_BLUE_COIN */   {5, MODEL_MAKER_IMBUE_COIN, IMBUE_BLUE},
    /* IMBUE_RED_SWITCH */  {0, MODEL_MAKER_IMBUE, IMBUE_RED},
    /* IMBUE_BLUE_SWITCH */ {0, MODEL_MAKER_IMBUE, IMBUE_BLUE},
    /* IMBUE_RED_COIN */    {2, MODEL_MAKER_IMBUE_COIN, IMBUE_RED},
    /* IMBUE_TRIGGER */     {0, MODEL_MAKER_IMBUE_TRIGGER, IMBUE_ORANGE},
    /* IMBUE_CROWBAR */     {0, MODEL_MAKER_IMBUE, IMBUE_GREEN},
    /* IMBUE_BULLET_MASK*/  {0, MODEL_MAKER_IMBUE, IMBUE_PINK},
    /* IMBUE_BADGE_BASE */  {0, MODEL_MAKER_IMBUE_BADGE, 0},
};
