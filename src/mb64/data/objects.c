#include "mb64/editor/object.h"
#include "mb64/editor/grid.h"
#include "mb64/editor/display_funcs.h"
#include "mb64/menu/toolbox.h"
#include "model_ids.h"
#include "behavior_data.h"
#include "actors/b/header.h"
#include "actors/group0.h"
#include "actors/common0.h"
#include "actors/group14.h"
#include "actors/group17.h"

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

/*  Object Type                  Name                       Button GFX              Behavior           Y Offset     Model                      Flags                                  Coins/Objs/Scale  Anims   Display Func    Sound*/
struct mb64_object_info mb64_object_type_list[] = {
/* OBJECT_TYPE_SETTINGS */      {"Level Settings",          mat_b_btn_settings,     NULL,              0,           MODEL_NONE,                0,                       0,                0, 0, 0.0f, NULL,  NULL, 0},
/* OBJECT_TYPE_1 */             {" ",                       mat_b_btn_settings,     NULL,              0,           MODEL_NONE,                0,                       0,                0, 0, 0.0f, NULL,  NULL, 0}, // previously screenshot
/* OBJECT_TYPE_STAR */          {"Normal",                  mat_b_btn_star,         bhvStar,           TILE_SIZE/2, MODEL_STAR,                OBJ_TYPE_STAR,           OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_star, SOUND_MENU_STAR_SOUND | SOUND_VIBRATO},
/* OBJECT_TYPE_RED_COIN_STAR */ {"Red Coins",               mat_b_btn_rcs,          bhvHiddenRedCoinStar, TILE_SIZE/2, MODEL_TRANSPARENT_STAR, OBJ_TYPE_STAR,           OBJ_OCCUPY_INNER, 0, 1, 1.0f, NULL, df_reds_marker, SOUND_MENU_STAR_SOUND | SOUND_VIBRATO},
/* OBJECT_TYPE_GOOMBA */        {"Normal",                  mat_b_btn_goomba,       bhvGoomba,         0,           MODEL_GOOMBA,              OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 1, 0, 1.5f, goomba_seg8_anims_0801DA4C, NULL, SOUND_OBJ_GOOMBA_PREVIEW},
/* OBJECT_TYPE_BIG_GOOMBA */    {"Huge",                    mat_b_btn_goomba_b,     bhvBigGoomba,      0,           MODEL_GOOMBA,              OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 5, 0, 3.5f, goomba_seg8_anims_0801DA4C, NULL, SOUND_OBJ_GOOMBA_PREVIEW},
/* OBJECT_TYPE_TINY_GOOMBA */   {"Tiny",                    mat_b_btn_goomba_s,     bhvTinyGoomba,     0,           MODEL_GOOMBA,              OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 1, 0, 0.5f, goomba_seg8_anims_0801DA4C, NULL, SOUND_OBJ_GOOMBA_PREVIEW},
/* OBJECT_TYPE_PIRANHA_PLANT */ {"Normal",                  mat_b_btn_plant,        bhvPiranhaPlant,   0,           MODEL_MAKER_PLANT,         OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 5, 1, 1.0f, piranha_plant_seg6_anims_0601C31C, df_piranha, SOUND_OBJ2_PIRANHA_PLANT_BITE},
/* OBJECT_TYPE_BIG_PIRANHA_PLANT */  {"Huge",               mat_b_btn_plant_b,      bhvFirePiranhaPlantBig, 0,      MODEL_MAKER_PLANT,         OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 2, 0, 2.0f, piranha_plant_seg6_anims_0601C31C, NULL, SOUND_OBJ2_PIRANHA_PLANT_BITE},
/* OBJECT_TYPE_TINY_PIRANHA_PLANT */ {"Tiny",               mat_b_btn_plant_s,      bhvFirePiranhaPlant, 0,         MODEL_MAKER_PLANT,         OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 1, 0, 0.5f, piranha_plant_seg6_anims_0601C31C, NULL, SOUND_OBJ2_PIRANHA_PLANT_BITE},
/* OBJECT_TYPE_KOOPA */         {"Koopa",                   mat_b_btn_kuppa,        bhvScaredKoopa,    0,           MODEL_KOOPA_WITH_SHELL,    OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 5, 0, 1.5f, koopa_seg6_anims_06011364, df_koopa, SOUND_OBJ_KOOPA_TALK},
/* OBJECT_TYPE_COIN */          {"Yellow Coin",             mat_b_btn_coin,         bhvYellowCoin,     0,           MODEL_YELLOW_COIN,         OBJ_TYPE_BILLBOARD | OBJ_TYPE_IMBUABLE_TRIGGER, OBJ_OCCUPY_INNER, 1, 0, 1.0f, NULL, NULL, SOUND_GENERAL_COIN | SOUND_VIBRATO},
/* OBJECT_TYPE_GREEN_COIN */    {"Green Coin",              mat_b_btn_greencoin,    bhvGreenCoin,      0,           MODEL_GREEN_COIN,          OBJ_TYPE_BILLBOARD | OBJ_TYPE_IMBUABLE_TRIGGER, OBJ_OCCUPY_INNER, 3, 0, 1.0f, NULL, NULL, SOUND_GENERAL_COIN_MULTI},
/* OBJECT_TYPE_RED_COIN */      {"Red Coin",                mat_b_btn_redcoin,      bhvRedCoin,        0,           MODEL_RED_COIN,            OBJ_TYPE_BILLBOARD,      OBJ_OCCUPY_INNER, 2, 0, 1.0f, NULL, NULL, SOUND_MENU_COLLECT_RED_COIN},
/* OBJECT_TYPE_BLUE_COIN */     {"Coin",                    mat_b_btn_bluecoin,     bhvHiddenBlueCoin, 0,           MODEL_BLUE_COIN,           OBJ_TYPE_BILLBOARD | OBJ_TYPE_IMBUABLE_TRIGGER, OBJ_OCCUPY_INNER, 5, 0, 1.0f, NULL, NULL, SOUND_GENERAL_COIN_MULTI},
/* OBJECT_TYPE_BLUE_COIN_SWITCH */ {"Switch",               mat_b_btn_bcs,          bhvBlueCoinSwitch, 0,           MODEL_BLUE_COIN_SWITCH,    OBJ_TYPE_IMBUABLE_TRIGGER, OBJ_OCCUPY_INNER, 0, 0, 3.0f, NULL, NULL, SOUND_GENERAL2_PURPLE_SWITCH},
/* OBJECT_TYPE_NOTEBLOCK */     {"Noteblock",               mat_b_btn_noteblock,    bhvNoteblock,      TILE_SIZE/2, MODEL_NOTEBLOCK,           0,                       OBJ_OCCUPY_INNER, 0, 0, 1.27f,NULL, NULL, SOUND_GENERAL_CRAZY_BOX_BOING_SLOW},
/* OBJECT_TYPE_BOBOMB */        {"Bob-omb",                 mat_b_btn_bobomb,       bhvBobomb,         0,           MODEL_BLACK_BOBOMB,        OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 1, 0, 1.0f, bobomb_anims, NULL, SOUND_GENERAL2_QUIET_EXPLOSION},
/* OBJECT_TYPE_CHUCKYA */       {"Chuckya",                 mat_b_btn_chuckya,      bhvChuckya,        0,           MODEL_CHUCKYA,             OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 5, 0, 2.0f, chuckya_seg8_anims_0800C070, df_chuckya, SOUND_OBJ_CHUCKYA_PREVIEW},
/* OBJECT_TYPE_BULLY */         {"Bully",                   mat_b_btn_bully,        bhvSmallBully,     0,           MODEL_BULLY,               OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 1, 0, 1.0f, bully_seg5_anims_0500470C, NULL, SOUND_OBJ2_SMALL_BULLY_ATTACKED},
/* OBJECT_TYPE_CHILL_BULLY */   {"Chill Bully",             mat_b_btn_chillbully,   bhvSmallBully,     0,           MODEL_CHILL_BULLY,         OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 1, 0, 1.0f, bully_seg5_anims_0500470C, NULL, SOUND_OBJ2_SMALL_BULLY_ATTACKED},
/* OBJECT_TYPE_BULLET_BILL */   {"Bullet Bill",             mat_b_btn_bill,         bhvBulletBillCannon, TILE_SIZE/2, MODEL_BILL_MAKER_2,      0,                       OBJ_OCCUPY_FULL,  0, 1, 1.0f, NULL, NULL, SOUND_OBJ_POUNDING_CANNON},
/* OBJECT_TYPE_HEAVE_HO */      {"Heave-Ho",                mat_b_btn_heaveho,      bhvHeaveHo,        0,           MODEL_MAKER_HEAVEHO,       OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS, OBJ_OCCUPY_INNER, 0, 0, 2.0f, heave_ho_seg5_anims_0501534C, NULL, SOUND_OBJ_HEAVEHO_PREVIEW},
/* OBJECT_TYPE_MOTOS */         {"Motos",                   mat_b_btn_motos,        bhvMotos,          0,           MODEL_MAKER_MOTOS,         OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 5, 0, 2.0f, motos_anime, NULL, SOUND_OBJ_HEAVEHO_PREVIEW},
/* OBJECT_TYPE_TREE */          {"Tree",                    mat_b_btn_tree,         bhvTree,           0,           MODEL_MAKER_TREE_1,        OBJ_TYPE_BILLBOARD,      OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_tree, SOUND_ACTION_CLIMB_UP_TREE | SOUND_VIBRATO},
/* OBJECT_TYPE_EXCL_BOX */      {"Item Box",                mat_b_btn_excla,        bhvExclamationBox, TILE_SIZE/2, MODEL_EXCLAMATION_BOX,     OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 0, 0, 2.0f, NULL, df_exbox, SOUND_GENERAL_BOX_PREVIEW},
/* OBJECT_TYPE_SPAWN */         {"Mario Spawn",             mat_b_btn_spawn,        bhvSpawn,          TILE_SIZE/2, MODEL_SPAWN,               0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_hide_during_screenshot, SOUND_MENU_STAR_SOUND_LETS_A_GO},
/* OBJECT_TYPE_REX */           {"Rex",                     mat_b_btn_rex,          bhvRex,            0,           MODEL_REX,                 OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 2, 0, 1.5f, Rex_anims, NULL, SOUND_OBJ_GOOMBA_PREVIEW},
/* OBJECT_TYPE_PODOBOO */       {"Podoboo",                 mat_b_btn_podoboo,      bhvPodoboo,        TILE_SIZE/2, MODEL_PODOBOO,             0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_podoboo, SOUND_OBJ_FLAME_BLOWN},
/* OBJECT_TYPE_CRABLET */       {"Crablet",                 mat_b_btn_crablet,      bhvCrablet,        0,           MODEL_MAKER_CRABLET,       OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 4, 0, 1.0f, crab_anims_anims, NULL, SOUND_OBJ2_SCUTTLEBUG_ALERT},
/* OBJECT_TYPE_HAMMER_BRO */    {"Normal",                  mat_b_btn_hammerbro,    bhvHammerBro,      0,           MODEL_HAMMER_BRO,          OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 6, 0, 1.0f, Hammerbro_anims, df_hammerbro, SOUND_OBJ_KOOPA_DAMAGE},
/* OBJECT_TYPE_FIRE_BRO */      {"Fire Bro",                mat_b_btn_firebro,      bhvFireBro,        0,           MODEL_HAMMER_BRO,          OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 6, 0, 1.0f, Hammerbro_anims, df_firebro, SOUND_OBJ_KOOPA_DAMAGE},
/* OBJECT_TYPE_CHICKEN */       {"Chicken",                 mat_b_btn_chicken,      bhvChicken,        TILE_SIZE/2, MODEL_MAKER_CHICKEN,       OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 2, 0, 1.0f, chicken_anims, NULL, SOUND_OBJ_BOO_LAUGH_SHORT},
/* OBJECT_TYPE_PHANTASM */      {"Cosmic Phantasm",         mat_b_btn_phantasm,     bhvPhantasm,       0,           MODEL_MARIO,               OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 5, 9, 1.0f, &evil_mario_anims[2], NULL, SOUND_ACTION_METAL_STEP | SOUND_VIBRATO},
/* OBJECT_TYPE_WARP_PIPE */     {"Warp Pipe",               mat_b_btn_pipe,         bhvStaticObject,   0,           MODEL_MAKER_PIPE,          0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_MENU_ENTER_PIPE | SOUND_VIBRATO},
/* OBJECT_TYPE_BADGE */         {"Badge",                   mat_b_btn_badge,        bhvBadge,          TILE_SIZE/2, MODEL_BADGE,               OBJ_TYPE_BILLBOARD | OBJ_TYPE_IMBUABLE_TRIGGER, OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_GENERAL2_PURPLE_SWITCH},
/* OBJECT_TYPE_KING_BOBOMB */   {"King Bob-omb",            mat_b_btn_boss_kb,      bhvKingBobomb,     0,           MODEL_KINGBOMB_MAKER,      OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  0, 0, 1.0f, king_bobomb_seg5_anims_0500FE30, df_kingbomb, SOUND_OBJ_KING_BOBOMB_POUNDING1_HIGHPRIO},
/* OBJECT_TYPE_KING_WHOMP */    {"King Whomp",              mat_b_btn_boss_whomp,   bhvWhompKingBoss,  0,           MODEL_WHOMP_MAKER,         OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  0, 1, 2.0f, whomp_seg6_anims_06020A04, NULL, SOUND_OBJ_WHOMP},
/* OBJECT_TYPE_BIG_BOO */       {"Big Boo",                 mat_b_btn_boss_boo,     bhvBalconyBigBoo,  TILE_SIZE,   MODEL_MAKER_BOO,           OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS, OBJ_OCCUPY_FULL,  0, 0, 3.0f, NULL, df_boo, SOUND_OBJ_BOO_LAUGH_LONG},
/* OBJECT_TYPE_BIG_BULLY */     {"Big Bully",               mat_b_btn_boss_bully,   bhvBigBully,       0,           MODEL_BULLY,               OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  0, 0, 2.0f, bully_seg5_anims_0500470C, NULL, SOUND_OBJ2_LARGE_BULLY_ATTACKED},
/* OBJECT_TYPE_BIG_CHILL_BULLY */ {"Big Chill Bully",       mat_b_btn_boss_chillbully,bhvBigBully,     0,           MODEL_CHILL_BULLY,         OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  0, 0, 2.0f, bully_seg5_anims_0500470C, NULL, SOUND_OBJ2_LARGE_BULLY_ATTACKED},
/* OBJECT_TYPE_WIGGLER */       {"Wiggler",                 mat_b_btn_boss_wiggler, bhvWigglerHead,    0,           MODEL_WIGGLER_HEAD,        OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  0, 5, 4.0f, wiggler_seg5_anims_0500EC8C, df_wiggler, SOUND_OBJ_WIGGLER_TALK},
/* OBJECT_TYPE_BOWSER */        {"Bowser",                  mat_b_btn_boss_bowser,  bhvBowser,         0,           MODEL_MAKER_BOWSER,        OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  0, 24, 1.0f, bowser_anims, df_bowser, SOUND_OBJ2_BOWSER_ROAR},
/* OBJECT_TYPE_PLATFORM_TRACK */ {"Activated",              mat_b_btn_checker,      bhvPlatformOnTrack, TILE_SIZE/2, MODEL_CHECKERBOARD_PLATFORM, OBJ_TYPE_TRAJECTORY,  OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_ENV_ELEVATOR1 | SOUND_VIBRATO},
/* OBJECT_TYPE_PLATFORM_LOOPING */ {"Looping",              mat_b_btn_checker,      bhvLoopingPlatform, TILE_SIZE/2, MODEL_LOOPINGP,           OBJ_TYPE_TRAJECTORY,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_ENV_ELEVATOR1 | SOUND_VIBRATO},
/* OBJECT_TYPE_BOWLING_BALL */  {"Bowling Ball",            mat_b_btn_bball,        bhvBobBowlingBallSpawner, TILE_SIZE/2, MODEL_BOWLING_BALL, OBJ_TYPE_BILLBOARD | OBJ_TYPE_TRAJECTORY, OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_GENERAL_QUIET_POUND1 | SOUND_VIBRATO},
/* OBJECT_TYPE_KOOPA_THE_QUICK */ {"Koopa the Quick",       mat_b_btn_kuppaq,       bhvKoopa,          0,           MODEL_KOOPA_WITH_SHELL,    OBJ_TYPE_TRAJECTORY | OBJ_TYPE_STAR, OBJ_OCCUPY_FULL, 0, 1, 3.0f, koopa_seg6_anims_06011364, df_ktq, SOUND_OBJ_KOOPA_TALK},
/* OBJECT_TYPE_PURPLE_SWITCH */ {"Purple Switch",           mat_b_btn_purpleswitch, bhvFloorSwitchHiddenObjects, 0, MODEL_PURPLE_SWITCH,       0,                       OBJ_OCCUPY_INNER, 0, 0, 1.28f,NULL, NULL, SOUND_GENERAL2_PURPLE_SWITCH},
/* OBJECT_TYPE_TIMED_BOX */     {"Breakable",               mat_b_btn_tbox,         bhvHiddenObject,   0,           MODEL_BREAKABLE_BOX,       0,                       OBJ_OCCUPY_OUTER, 0, 0, 1.0f, NULL, df_timedbox, SOUND_GENERAL2_SWITCH_TICK_FAST},
/* OBJECT_TYPE_RECOVERY_HEART */ {"Recovery Heart",         mat_b_btn_heart,        bhvRecoveryHeart,  TILE_SIZE/2, MODEL_HEART,               0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_heart, SOUND_GENERAL_HEART_SPIN},
/* OBJECT_TYPE_TEST_MARIO */    {"Save & Test",             mat_b_btn_check,        NULL,              0,           MODEL_MARIO,               0,                       OBJ_OCCUPY_FULL,  0, 0, 1.0f, mario_btcm_anims, NULL, 0},
/* OBJECT_TYPE_THWOMP */        {"Thwomp",                  mat_b_btn_thwomp,       bhvThwomp,         0,           MODEL_THWOMP_MAKER,        0,                       OBJ_OCCUPY_FULL,  0, 2, 1.5f, NULL, NULL, SOUND_OBJ_THWOMP},
/* OBJECT_TYPE_WHOMP */         {"Whomp",                   mat_b_btn_whomp,        bhvSmallWhomp,     0,           MODEL_WHOMP_MAKER,         OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL, 10, 1, 1.0f, whomp_seg6_anims_06020A04, NULL, SOUND_OBJ_WHOMP},
/* OBJECT_TYPE_GRINDEL */       {"Grindel",                 mat_b_btn_grindel,      bhvGrindel,        0,           MODEL_MAKER_GRINDEL,       0,                       OBJ_OCCUPY_FULL,  0, 2, 1.0f, NULL, df_grindel, SOUND_OBJ_KING_BOBOMB_JUMP},
/* OBJECT_TYPE_LAKITU */        {"Lakitu",                  mat_b_btn_lakitu,       bhvEnemyLakitu,    TILE_SIZE/2, MODEL_LAKITU_MAKER,        OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 5, 5, 1.0f, lakitu_enemy_seg5_anims_050144D4, df_lakitu, SOUND_OBJ_EVIL_LAKITU_THROW},
/* OBJECT_TYPE_FLY_GUY */       {"Fly Guy",                 mat_b_btn_flyguy,       bhvFlyGuy,     TILE_SIZE/2, MODEL_FLYGUY,              OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 2, 0, 1.5f, flyguy_seg8_anims_08011A64, df_flyguy, SOUND_OBJ_KOOPA_FLYGUY_DEATH},
/* OBJECT_TYPE_SNUFIT */        {"Snufit",                  mat_b_btn_snufit,       bhvSnufit,         TILE_SIZE/2, MODEL_MAKER_SNUFIT,        OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 2, 0, 1.0f, NULL, df_snufit, SOUND_OBJ_SNUFIT_SHOOT},
/* OBJECT_TYPE_AMP */           {"Amp",                     mat_b_btn_amp,          bhvCirclingAmp,    TILE_SIZE/2, MODEL_AMP,                 0,                       OBJ_OCCUPY_OUTER, 0, 0, 1.0f, amp_anims, df_circling_amp, SOUND_AIR_AMP_PREVIEW},
/* OBJECT_TYPE_BOO */           {"Boo",                     mat_b_btn_boo,          bhvBoo,            TILE_SIZE/2, MODEL_MAKER_BOO,           OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS,  OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_boo, SOUND_OBJ_BOO_LAUGH_LONG},
/* OBJECT_TYPE_MR_I */          {"Mr. I",                   mat_b_btn_mri,          bhvMrI,            0,           MODEL_MAKER_MRI,           OBJ_TYPE_IMBUABLE | OBJ_TYPE_BILLBOARD, OBJ_OCCUPY_INNER, 5, 1, 1.0f, NULL, df_mri, SOUND_OBJ_MRI_SHOOT},
/* OBJECT_TYPE_SCUTTLEBUG */    {"Scuttlebug",              mat_b_btn_scuttlebug,   bhvScuttlebug,     0,           MODEL_MAKER_SCUTTLEBUG,    OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 3, 0, 1.0f, scuttlebug_seg6_anims_06015064, NULL, SOUND_OBJ2_SCUTTLEBUG_ALERT},
/* OBJECT_TYPE_BOWSER_BOMB */   {"Bowser Bomb",             mat_b_btn_bbomb,        bhvBowserBomb,     TILE_SIZE/2, MODEL_MAKER_BOWSER_BOMB,   0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_GENERAL2_QUIET_EXPLOSION},
/* OBJECT_TYPE_FIRE_SPINNER */  {"Fire Spinner",            mat_b_btn_firebar,      bhvLllRotatingBlockWithFireBars, 0, MODEL_MAKER_FIREBAR,   0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_fire_spinner, SOUND_OBJ_FLAME_BLOWN},
/* OBJECT_TYPE_COIN_FORMATION */ {"Coin Formation",         mat_b_btn_cformation,   bhvCoinFormation,  0,           MODEL_NONE,                0,                       OBJ_OCCUPY_FULL,  0, 0, 1.0f, NULL, df_coin_formation, SOUND_GENERAL_COIN_MULTI},
/* OBJECT_TYPE_RED_FLAME */     {"Red",                     mat_b_btn_fire_red,     bhvFlame,          90,          MODEL_RED_FLAME,           OBJ_TYPE_BILLBOARD,      OBJ_OCCUPY_INNER, 0, 0, 7.0f, NULL, df_flame, SOUND_OBJ_FLAME_BLOWN},
/* OBJECT_TYPE_BLUE_FLAME */    {"Blue",                    mat_b_btn_fire_blue,    bhvFlame,          90,          MODEL_BLUE_FLAME,          OBJ_TYPE_BILLBOARD,      OBJ_OCCUPY_INNER, 0, 0, 7.0f, NULL, df_flame, SOUND_OBJ_FLAME_BLOWN},
/* OBJECT_TYPE_FIRE_SPITTER */  {"Fire Spitter",            mat_b_btn_firespitter,  bhvFireSpitter,    TILE_SIZE/2, MODEL_BOWLING_BALL,        OBJ_TYPE_BILLBOARD,      OBJ_OCCUPY_INNER, 0, 0, 0.2f, NULL, NULL, SOUND_OBJ_FLAME_BLOWN},
/* OBJECT_TYPE_FLAMETHROWER */  {"Flamethrower",            mat_b_btn_flamethrower, bhvFlamethrower,   TILE_SIZE/2, MODEL_MAKER_FLAMETHROWER,  0,                       OBJ_OCCUPY_FULL,  0, 5, 1.0f, NULL, NULL, SOUND_OBJ_FLAME_BLOWN},
/* OBJECT_TYPE_SPINDRIFT */     {"Spindrift",               mat_b_btn_spindrift,    bhvSpindrift,      0,           MODEL_MAKER_SPINDRIFT,     OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 3, 0, 1.0f, spindrift_seg5_anims_05002D68, NULL, SOUND_ACTION_TWIRL},
/* OBJECT_TYPE_MR_BLIZZARD */   {"Mr. Blizzard",            mat_b_btn_blizzard,     bhvMrBlizzard,     0,           MODEL_MAKER_BLIZZARD,      OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 3, 0, 1.0f, snowman_seg5_anims_0500D118, df_blizzard, SOUND_OBJ2_SCUTTLEBUG_ALERT},
/* OBJECT_TYPE_MONEYBAG */      {"Moneybag",                mat_b_btn_moneybag,     bhvMoneybagHidden, 0,           MODEL_MONEYBAG,            OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS, OBJ_OCCUPY_INNER, 0, 1, 1.0f, moneybag_seg6_anims_06005E5C, df_moneybag, SOUND_GENERAL_MONEYBAG_BOING_LOWPRIO},
/* OBJECT_TYPE_SKEETER */       {"Skeeter",                 mat_b_btn_skeeter,      bhvSkeeter,        0,           MODEL_MAKER_SKEETER,       OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 3, 0, 1.0f, skeeter_seg6_anims_06007DE0, df_skeeter, SOUND_OBJ_SKEETER_WALK},
/* OBJECT_TYPE_POKEY */         {"Pokey",                   mat_b_btn_pokey,        bhvPokey,          0,           MODEL_MAKER_POKEY_HEAD,    OBJ_TYPE_IMBUABLE | OBJ_TYPE_BILLBOARD, OBJ_OCCUPY_INNER, 5, 5, 3.0f, NULL, df_pokey, SOUND_OBJ_POKEY_DEATH},
/* OBJECT_TYPE_BBOX_SMALL*/     {"Throwable Box",           mat_b_btn_sbox,         bhvBreakableBoxSmall, 0,        MODEL_BREAKABLE_BOX_SMALL, 0,                       OBJ_OCCUPY_INNER, 3, 0, 0.31f,NULL, df_corkbox, SOUND_GENERAL_BOX_PREVIEW},
/* OBJECT_TYPE_BBOX_NORMAL*/    {"Breakable Box",           mat_b_btn_corkbox,      bhvBreakableBox,   0,           MODEL_BREAKABLE_BOX,       OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS, OBJ_OCCUPY_FULL, 0, 0, 1.0f, NULL, df_corkbox, SOUND_GENERAL_BOX_PREVIEW},
/* OBJECT_TYPE_BBOX_CRAZY*/     {"Crazy Box",               mat_b_btn_cbox,         bhvJumpingBox,     0,           MODEL_BREAKABLE_BOX_SMALL, 0,                       OBJ_OCCUPY_INNER, 5, 0, 0.38f,NULL, df_crazybox, SOUND_GENERAL_CRAZY_BOX_BOING_SLOW},
/* OBJECT_TYPE_DIAMOND*/        {"Water Diamond",           mat_b_btn_water_diamond,bhvWaterLevelDiamond,0,         MODEL_MAKER_DIAMOND,       0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_GENERAL_WATER_LEVEL_TRIG},
/* OBJECT_TYPE_SIGN */          {"Bill Board",              mat_b_btn_sign,         bhvMessagePanel,   0,           MODEL_WOODEN_SIGNPOST,     OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_ACTION_READ_SIGN},
/* OBJECT_TYPE_BUDDY */         {"Bob-omb Buddy",           mat_b_btn_buddy,        bhvBobombBuddy,    0,           MODEL_BOBOMB_BUDDY,        OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, bobomb_anims, NULL, SOUND_OBJ_BOBOMB_BUDDY_TALK},
/* OBJECT_TYPE_BUTTON */        {"On-Off Button",           mat_b_btn_switch,       bhvOnOffButton,    0,           MODEL_MAKER_BUTTON,        0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_button, SOUND_GENERAL_BUTTON_PRESS},
/* OBJECT_TYPE_ON_OFF_BLOCK */  {"On-Off Block",            mat_b_btn_block,        bhvOnOffBlock,     0,           MODEL_MAKER_BLOCK_OFF,     0,                       OBJ_OCCUPY_OUTER, 0, 0, 1.0f, NULL, df_block, SOUND_GENERAL_BUTTON_PRESS},
/* OBJECT_TYPE_WOODPLAT */      {"Wooden Platform",         mat_b_btn_woodplat,     bhvWoodPlat,       0,           MODEL_MAKER_WOODPLAT,      0,                       OBJ_OCCUPY_FULL,  0, 1, 1.0f, NULL, df_woodplat, SOUND_ACTION_TERRAIN_STEP + (SOUND_TERRAIN_SPOOKY << 16)},
/* OBJECT_TYPE_RFBOX */         {"Reinforced Box",          mat_b_btn_rfbox,        bhvBreakableBoxRF, 0,           MODEL_MAKER_RFBOX,         OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS, OBJ_OCCUPY_FULL, 0, 0, 1.0f, NULL, NULL, SOUND_OBJ_BULLY_METAL},
/* OBJECT_TYPE_CULL_PREVIEW */  {"",                        mat_b_btn_cull,         bhvStaticObject,   TILE_SIZE/2, MODEL_CULL_MARKER,         OBJ_TYPE_BILLBOARD,      OBJ_OCCUPY_INNER, 0, 0, 1.f,  NULL, NULL, 0},
/* OBJECT_TYPE_SHOWRUNNER */    {"Showrunner",              mat_b_btn_showrunner,   bhvShowrunner,     0,           MODEL_MAKER_SHOWRUNNER,    OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  50,39,1.0f, showrunner_anims, NULL, SOUND_OBJ_MRI_SHOOT},
/* OBJECT_TYPE_CROWBAR */       {"Crowbar",                 mat_b_btn_pipebar,      bhvCrowbarPower,   TILE_SIZE/2, MODEL_MAKER_CROWBAR,       0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_crowbar, SOUND_MENU_EXIT_PIPE},
/* OBJECT_TYPE_MASK    */       {"Bullet Bill Mask",        mat_b_btn_mask,         bhvBMask,          TILE_SIZE/2, MODEL_MAKER_MASK,          0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_mask, SOUND_MENU_EXIT_PIPE},
/* OBJECT_TYPE_TOAD */          {"Toad",                    mat_b_btn_toad,         bhvMakerToad,      0,           MODEL_MAKER_TOAD,          OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, toad_seg6_anims_0600FB58, df_toad, SOUND_ACTION_READ_SIGN},
/* OBJECT_TYPE_TUXIE */         {"Tuxie",                   mat_b_btn_tuxie,        bhvMakerTuxie,     0,           MODEL_MAKER_TUXIE,         OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, penguin_seg5_anims_05008B74, NULL, SOUND_OBJ2_BABY_PENGUIN_YELL},
/* OBJECT_TYPE_UKIKI */         {"Ukiki",                   mat_b_btn_ukiki,        bhvMakerUkiki,     0,           MODEL_MAKER_UKIKI,         OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, ukiki_seg5_anims_05015784, df_ukiki, SOUND_OBJ_UKIKI_CHATTER_SHORT},
/* OBJECT_TYPE_MOLEMAN */       {"Moleman",                 mat_b_btn_moleman,      bhvMoleman,        65,          MODEL_MAKER_MOLEMAN,       OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, moleman3_anims, NULL, SOUND_ACTION_READ_SIGN},
/* OBJECT_TYPE_COBIE */         {"Cobie",                   mat_b_btn_cobie,        bhvCobie,          0,           MODEL_MAKER_COBIE,         OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, cobie2_anims, NULL, SOUND_ACTION_READ_SIGN},
/* OBJECT_TYPE_CONVEYOR */      {"Conveyor",                mat_b_btn_conveyor,     bhvConveyor,       0,           MODEL_MAKER_CONVEYOR_HALF, 0,                       OBJ_OCCUPY_FULL,  0, 0, 1.0f, NULL, df_conveyor, SOUND_OBJ_HEAVEHO_PREVIEW},
/* OBJECT_TYPE_TIMED_BLOCK */   {"Inverted",                mat_b_btn_tblock,       bhvTimedBlock,     0,           MODEL_MAKER_BLOCK_OFF,     0,                       OBJ_OCCUPY_OUTER, 0, 0, 1.0f, NULL, df_timedblock, SOUND_GENERAL2_SWITCH_TICK_FAST},
/* OBJECT_TYPE_TRIGGER */       {"Star Trigger",            mat_b_btn_trigger,      bhvStaticObject,   TILE_SIZE/2, MODEL_MAKER_IMBUE_TRIGGER, OBJ_TYPE_BILLBOARD,      OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_MENU_COLLECT_SECRET},
/* OBJECT_TYPE_TRIGGER_STAR */  {"Star Triggers",           mat_b_btn_triggerstar,  bhvHiddenStar,     TILE_SIZE/2, MODEL_TRANSPARENT_STAR,    OBJ_TYPE_STAR,           OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_star, SOUND_MENU_STAR_SOUND | SOUND_VIBRATO},
};

//behparam2 strings
char *txt_bp_box[] = {
    "Rocket Boots",
    "Vanetal Cap",
    "Koopa Shell",
    "Green Coin",
    "One Coin",
    "Three Coins",
    "Ten Coins",
};

char *txt_bp_vbox[] = {
    "Wing Cap",
    "Metal Cap",
    "Vanish Cap",
    "Koopa Shell",
    "One Coin",
    "Three Coins",
    "Ten Coins",
};

char *txt_bp_tree[] = {
    "Bubbly",
    "Palm",
    "Spiky",
    "Snowy",
    "Farm",
    "Dead",
};

char *txt_badges[] = {
    "Lava Boost",
    "Fall Damage",
    "Defense",
    "One Hit",
    "Gills",
    "Fins",
    "HP Regen",
    "Mana Regen",
    "Greed",
    "Double Time",
    "Magnet",
    "Burn",
    "Squish",
    "Feather",
    "Weight",
    "Sticky",
    "Fast Foot",
    "Heal Plus",
    "Bottomless",
    "Slow Fall",
    "Brittle Burden",
    "Withering Burden",
};

char *txt_coin_formation[] = {
    "Line",
    "Vertical Line",
    "Ring",
    "Vertical Ring",
    "Arrow",
};

char *txt_onoff[] = {
    "Red",
    "Blue"
};

char *txt_woodplat[] = {
    "Thin",
    "Full"
};

char *txt_fire_spinner[] = {
    "Length: 2",
    "Length: 3",
    "Length: 4",
    "Length: 5",
    "Length: 6",
};

char *txt_conveyor[] = {
    "Thin",
    "Full",
    "Upwards",
    "Downwards",
    "Thin (On-Off)",
    "Full (On-Off)",
    "Upwards (On-Off)",
    "Downwards (On-Off)",
};

u8 mb64_star_idlist[] = {OBJECT_TYPE_STAR, OBJECT_TYPE_RED_COIN_STAR, OBJECT_TYPE_TRIGGER_STAR};
u8 mb64_goomba_idlist[] = {OBJECT_TYPE_GOOMBA, OBJECT_TYPE_BIG_GOOMBA, OBJECT_TYPE_TINY_GOOMBA};
u8 mb64_piranha_idlist[] = {OBJECT_TYPE_PIRANHA_PLANT, OBJECT_TYPE_BIG_PIRANHA_PLANT, OBJECT_TYPE_TINY_PIRANHA_PLANT};
u8 mb64_bluecoin_idlist[] = {OBJECT_TYPE_BLUE_COIN, OBJECT_TYPE_BLUE_COIN_SWITCH};
u8 mb64_hammer_idlist[] = {OBJECT_TYPE_HAMMER_BRO, OBJECT_TYPE_FIRE_BRO};
u8 mb64_whomp_idlist[] = {OBJECT_TYPE_WHOMP, OBJECT_TYPE_KING_WHOMP};
u8 mb64_bully_idlist[] = {OBJECT_TYPE_BULLY, OBJECT_TYPE_CHILL_BULLY, OBJECT_TYPE_BIG_BULLY, OBJECT_TYPE_BIG_CHILL_BULLY};
u8 mb64_boo_idlist[] = {OBJECT_TYPE_BOO, OBJECT_TYPE_BIG_BOO};
u8 mb64_plat_idlist[] = {OBJECT_TYPE_PLATFORM_TRACK, OBJECT_TYPE_PLATFORM_LOOPING};
u8 mb64_thwomp_idlist[] = {OBJECT_TYPE_THWOMP, OBJECT_TYPE_GRINDEL};
u8 mb64_flame_idlist[] = {OBJECT_TYPE_RED_FLAME, OBJECT_TYPE_BLUE_FLAME};
u8 mb64_npc_idlist[] = {OBJECT_TYPE_SIGN, OBJECT_TYPE_BUDDY, OBJECT_TYPE_TOAD, OBJECT_TYPE_TUXIE, OBJECT_TYPE_UKIKI};
u8 mb64_npccm_idlist[] = {OBJECT_TYPE_SIGN, OBJECT_TYPE_BUDDY, OBJECT_TYPE_MOLEMAN, OBJECT_TYPE_COBIE};
u8 mb64_power_idlist[] = {OBJECT_TYPE_CROWBAR, OBJECT_TYPE_MASK};
u8 mb64_timedbox_idlist[] = {OBJECT_TYPE_TIMED_BOX, OBJECT_TYPE_TIMEDBLOCK};
u8 mb64_smallbox_idlist[] = {OBJECT_TYPE_BBOX_SMALL, OBJECT_TYPE_BBOX_CRAZY};

struct mb64_ui_button_type mb64_ui_buttons[] = {
/* MB64_BUTTON_SETTINGS */ {MB64_PM_ACTION,  FALSE, 0, OBJECT_TYPE_SETTINGS,    NULL},
/* MB64_BUTTON_TEST */     {MB64_PM_ACTION,  FALSE, 0, OBJECT_TYPE_TEST_MARIO,  NULL},
/* MB64_BUTTON_TERRAIN */  {MB64_PM_TILE, FALSE, 0, TILE_TYPE_BLOCK,         NULL},
/* MB64_BUTTON_SLOPE */    {MB64_PM_TILE, FALSE, 0, TILE_TYPE_SLOPE,         NULL},
/* MB64_BUTTON_TROLL */    {MB64_PM_TILE, FALSE, 0, TILE_TYPE_TROLL,         NULL},
/* MB64_BUTTON_STAR */     {MB64_PM_OBJ,  TRUE,  3, (u32)mb64_star_idlist,        "Power Star"},
/* MB64_BUTTON_GOOMBA */   {MB64_PM_OBJ,  TRUE,  3, (u32)mb64_goomba_idlist,      "Goomba"},
/* MB64_BUTTON_PIRANHA */  {MB64_PM_OBJ,  TRUE,  3, (u32)mb64_piranha_idlist,     "Piranha Plant"},
/* MB64_BUTTON_KOOPA */    {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_KOOPA,       NULL},
/* MB64_BUTTON_COIN */     {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_COIN,        NULL},
/* MB64_BUTTON_BLANK */    {MB64_PM_TILE, FALSE, 0, TILE_TYPE_BLOCK,         NULL},
/* MB64_BUTTON_GCOIN */    {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_GREEN_COIN,  NULL},
/* MB64_BUTTON_CORNER */   {MB64_PM_TILE, FALSE, 0, TILE_TYPE_CORNER,        NULL},
/* MB64_BUTTON_ICORNER */  {MB64_PM_TILE, FALSE, 0, TILE_TYPE_ICORNER,       NULL},
/* MB64_BUTTON_RCOIN */    {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_RED_COIN,    NULL},
/* MB64_BUTTON_BCOIN */    {MB64_PM_OBJ,  TRUE,  2, (u32)mb64_bluecoin_idlist,    "Blue Coins"},
/* MB64_BUTTON_NOTEBLOCK */{MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_NOTEBLOCK,   NULL},
/* MB64_BUTTON_CULL */     {MB64_PM_TILE, FALSE, 0, TILE_TYPE_CULL,          NULL},
/* MB64_BUTTON_BOBOMB */   {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_BOBOMB,      NULL},
/* MB64_BUTTON_CHUCKYA */  {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_CHUCKYA,     NULL},
/* MB64_BUTTON_BULLY */    {MB64_PM_OBJ,  TRUE,  4, (u32)mb64_bully_idlist,       "Bully"},
/* MB64_BUTTON_BULLET */   {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_BULLET_BILL, NULL},
/* MB64_BUTTON_HEAVEHO */  {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_HEAVE_HO,    NULL},
/* MB64_BUTTON_MOTOS */    {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_MOTOS,       NULL},
/* MB64_BUTTON_TREE */     {MB64_PM_OBJ,  FALSE, 6, OBJECT_TYPE_TREE,        (char *)txt_bp_tree},
/* MB64_BUTTON_EXCLA */    {MB64_PM_OBJ,  FALSE, 7, OBJECT_TYPE_EXCL_BOX,    (char *)txt_bp_box},
/* MB64_BUTTON_SPAWN */    {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_MARIO_SPAWN, NULL},
/* MB64_BUTTON_REX */      {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_REX,         NULL},
/* MB64_BUTTON_PODOBOO */  {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_PODOBOO,     NULL},
/* MB64_BUTTON_CRABLET */  {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_CRABLET,     NULL},
/* MB64_BUTTON_HAMMER_BRO */{MB64_PM_OBJ, TRUE,  2, (u32)mb64_hammer_idlist,      "Hammer Bro"},
/* MB64_BUTTON_CHICKEN */  {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_CHICKEN,     NULL},
/* MB64_BUTTON_PHANTASM */ {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_PHANTASM,    NULL},
/* MB64_BUTTON_PIPE */     {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_WARP_PIPE,   NULL},
/* MB64_BUTTON_BADGE */    {MB64_PM_OBJ,  FALSE, 22, OBJECT_TYPE_BADGE,      (char *)txt_badges},
/* MB64_BUTTON_WATER */    {MB64_PM_TILE,FALSE, 0, TILE_TYPE_WATER,         NULL},
/* MB64_BUTTON_FENCE */    {MB64_PM_TILE, FALSE, 0, TILE_TYPE_FENCE,         NULL},
/* MB64_BUTTON_KING_BOBOMB */ {MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_KING_BOBOMB, NULL},
/* MB64_BUTTON_WIGGLER */  {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_WIGGLER,     NULL},
/* MB64_BUTTON_BOWSER */   {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_BOWSER,      NULL},
/* MB64_BUTTON_MPLAT */    {MB64_PM_OBJ,  TRUE,  2, (u32)mb64_plat_idlist,        "Moving Platform"},
/* MB64_BUTTON_BBALL */    {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_BOWLING_BALL, NULL},
/* MB64_BUTTON_KTQ */      {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_KOOPA_THE_QUICK, NULL},
/* MB64_BUTTON_SSLOPE */   {MB64_PM_TILE, FALSE, 0, TILE_TYPE_SSLOPE,        NULL},
/* MB64_BUTTON_SLAB */     {MB64_PM_TILE, FALSE, 0, TILE_TYPE_SLAB,          NULL},
/* MB64_BUTTON_PURPLE_SWITCH */{MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_PURPLE_SWITCH, NULL},
/* MB64_BUTTON_TIMED_BOX */ {MB64_PM_OBJ,  TRUE, 2, (u32)mb64_timedbox_idlist,   "Timed Box"},
/* MB64_BUTTON_HEART */    {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_RECOVERY_HEART, NULL},
/* MB64_BUTTON_FORMATION */{MB64_PM_OBJ,  FALSE, 5, OBJECT_TYPE_COIN_FORMATION, (char *)txt_coin_formation},
/* MB64_BUTTON_VSLAB */    {MB64_PM_TILE, FALSE, 0, TILE_TYPE_SSLAB,         NULL},
/* MB64_BUTTON_SCORNER */  {MB64_PM_TILE, FALSE, 0, TILE_TYPE_SCORNER,       NULL},
/* MB64_BUTTON_UGENTLE */  {MB64_PM_TILE, FALSE, 0, TILE_TYPE_UGENTLE,       NULL},
/* MB64_BUTTON_LGENTLE */  {MB64_PM_TILE, FALSE, 0, TILE_TYPE_LGENTLE,       NULL},
/* MB64_BUTTON_BARS */     {MB64_PM_TILE, FALSE, 0, TILE_TYPE_BARS,          NULL},
/* MB64_BUTTON_THWOMP */   {MB64_PM_OBJ,  TRUE,  2, (u32)mb64_thwomp_idlist,      "Thwomp"},
/* MB64_BUTTON_WHOMP */    {MB64_PM_OBJ,  TRUE,  2, (u32)mb64_whomp_idlist,       "Whomp"},
/* MB64_BUTTON_POLE */     {MB64_PM_TILE, FALSE, 0, TILE_TYPE_POLE,          NULL},
/* MB64_BUTTON_VEXCLA */   {MB64_PM_OBJ,  FALSE, 7, OBJECT_TYPE_EXCL_BOX,    (char *)txt_bp_vbox},
/* MB64_BUTTON_LAKITU */   {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_LAKITU,      NULL},
/* MB64_BUTTON_FLYGUY */   {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_FLY_GUY,     NULL},
/* MB64_BUTTON_SNUFIT */   {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_SNUFIT,      NULL},
/* MB64_BUTTON_AMP */      {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_AMP,         NULL},
/* MB64_BUTTON_BOO */      {MB64_PM_OBJ,  TRUE,  2, (u32)mb64_boo_idlist,         "Boo"},
/* MB64_BUTTON_MR_I */     {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_MR_I,        NULL},
/* MB64_BUTTON_SCUTTLEBUG */{MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_SCUTTLEBUG,  NULL},
/* MB64_BUTTON_SPINDRIFT */{MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_SPINDRIFT,   NULL},
/* MB64_BUTTON_BLIZZARD */ {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_MR_BLIZZARD, NULL},
/* MB64_BUTTON_MONEYBAG */ {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_MONEYBAG,    NULL},
/* MB64_BUTTON_SKEETER */  {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_SKEETER,     NULL},
/* MB64_BUTTON_POKEY */    {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_POKEY,       NULL},
/* MB64_BUTTON_MINE */     {MB64_PM_OBJ,  FALSE, 0, OBJECT_TYPE_BOWSER_BOMB, NULL},
/* MB64_BUTTON_FIRE */     {MB64_PM_OBJ,  TRUE,  2, (u32)mb64_flame_idlist,       "Flame"},
/* MB64_BUTTON_FLAMETHROWER */{MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_FLAMETHROWER, NULL},
/* MB64_BUTTON_FIRE_SPITTER */{MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_FIRE_SPITTER, NULL},
/* MB64_BUTTON_FIRE_SPINNER */{MB64_PM_OBJ, FALSE, 5, OBJECT_TYPE_FIRE_SPINNER, (char *)txt_fire_spinner},
/* MB64_BUTTON_BREAKABLE */{MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_BBOX_NORMAL, NULL},
/* MB64_BUTTON_SMALL_BOX */{MB64_PM_OBJ, TRUE, 2, (u32)mb64_smallbox_idlist, "Boxes"},
/* MB64_BUTTON_DIAMOND */  {MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_DIAMOND, NULL},
/* MB64_BUTTON_NPC */      {MB64_PM_OBJ, TRUE, 5, (u32)mb64_npc_idlist, "NPC"},
/* MB64_BUTTON_NPCCM */    {MB64_PM_OBJ, TRUE, 4, (u32)mb64_npccm_idlist, "NPC"},
/* MB64_BUTTON_BUTTON */   {MB64_PM_OBJ, FALSE, 2, OBJECT_TYPE_BUTTON, (char *)txt_onoff},
/* MB64_BUTTON_BLOCK */    {MB64_PM_OBJ, FALSE, 2, OBJECT_TYPE_ON_OFF_BLOCK, (char *)txt_onoff},
/* MB64_BUTTON_WOODPLAT */ {MB64_PM_OBJ, FALSE, 2, OBJECT_TYPE_WOODPLAT, (char *)txt_woodplat},
/* MB64_BUTTON_RFBOX */    {MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_RFBOX, NULL},
/* MB64_BUTTON_SHOWRUN */  {MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_SHOWRUNNER, NULL},
/* MB64_BUTTON_POWER */    {MB64_PM_OBJ, TRUE, 2, (u32)mb64_power_idlist, "Powerup"},
/* MB64_BUTTON_CONVEYOR */ {MB64_PM_OBJ, FALSE, 8, OBJECT_TYPE_CONVEYOR, (char *)txt_conveyor},
/* MB64_BUTTON_ISCORNER */ {MB64_PM_TILE, FALSE, 0, TILE_TYPE_ISCORNER, NULL},
/* MB64_BUTTON_TRIGGER */  {MB64_PM_OBJ, FALSE, 0, OBJECT_TYPE_TRIGGER, NULL},
};

u8 mb64_toolbar_defaults[9] = {
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

//Different toolboxes for different game styles
#define _ MB64_BUTTON_BLANK
u8 mb64_toolbox_btcm[18 * 5] = {
    MB64_BUTTON_TERRAIN, MB64_BUTTON_SLAB, MB64_BUTTON_SLOPE, MB64_BUTTON_CORNER, MB64_BUTTON_ICORNER, MB64_BUTTON_VSLAB, MB64_BUTTON_SSLOPE, MB64_BUTTON_SCORNER, MB64_BUTTON_ISCORNER,
    MB64_BUTTON_GOOMBA, MB64_BUTTON_BOBOMB, MB64_BUTTON_CHUCKYA, MB64_BUTTON_KOOPA, MB64_BUTTON_LAKITU, MB64_BUTTON_FLYGUY, MB64_BUTTON_SNUFIT, MB64_BUTTON_THWOMP, MB64_BUTTON_WHOMP,

    MB64_BUTTON_LGENTLE, MB64_BUTTON_UGENTLE, MB64_BUTTON_TROLL, MB64_BUTTON_WATER, MB64_BUTTON_FENCE, MB64_BUTTON_BARS, MB64_BUTTON_POLE, MB64_BUTTON_TREE, MB64_BUTTON_CULL,
    MB64_BUTTON_BULLY, MB64_BUTTON_MOTOS, MB64_BUTTON_HEAVEHO, MB64_BUTTON_BULLET, MB64_BUTTON_AMP, MB64_BUTTON_PIRANHA, MB64_BUTTON_BOO,MB64_BUTTON_MR_I,MB64_BUTTON_SCUTTLEBUG,

    MB64_BUTTON_STAR, MB64_BUTTON_COIN, MB64_BUTTON_FORMATION, MB64_BUTTON_GCOIN, MB64_BUTTON_RCOIN, MB64_BUTTON_BCOIN, MB64_BUTTON_EXCLA, MB64_BUTTON_TRIGGER, MB64_BUTTON_HEART,
    MB64_BUTTON_SPINDRIFT,MB64_BUTTON_BLIZZARD,MB64_BUTTON_MONEYBAG,MB64_BUTTON_SKEETER, MB64_BUTTON_POKEY, MB64_BUTTON_REX, MB64_BUTTON_HAMMER_BRO, MB64_BUTTON_PODOBOO, MB64_BUTTON_PHANTASM,

    MB64_BUTTON_MPLAT, MB64_BUTTON_PURPLE_SWITCH, MB64_BUTTON_TIMED_BOX, MB64_BUTTON_BREAKABLE, MB64_BUTTON_RFBOX, MB64_BUTTON_DIAMOND, MB64_BUTTON_WOODPLAT, MB64_BUTTON_NPCCM, MB64_BUTTON_BADGE,
    MB64_BUTTON_FIRE, MB64_BUTTON_FLAMETHROWER, MB64_BUTTON_FIRE_SPITTER, MB64_BUTTON_FIRE_SPINNER, MB64_BUTTON_BBALL, _, MB64_BUTTON_CHICKEN, MB64_BUTTON_CRABLET, MB64_BUTTON_SHOWRUN,

    MB64_BUTTON_NOTEBLOCK, MB64_BUTTON_BUTTON, MB64_BUTTON_BLOCK, MB64_BUTTON_CONVEYOR, _, _, _, _, _,
    MB64_BUTTON_SPAWN, MB64_BUTTON_SMALL_BOX, MB64_BUTTON_POWER, _, _, _, _, _, _,
};

u8 mb64_toolbox_vanilla[18 * 5] = {
    MB64_BUTTON_TERRAIN, MB64_BUTTON_SLAB, MB64_BUTTON_SLOPE, MB64_BUTTON_CORNER, MB64_BUTTON_ICORNER, MB64_BUTTON_VSLAB, MB64_BUTTON_SSLOPE, MB64_BUTTON_SCORNER, MB64_BUTTON_ISCORNER,
    MB64_BUTTON_GOOMBA, MB64_BUTTON_BOBOMB, MB64_BUTTON_CHUCKYA, MB64_BUTTON_KOOPA, MB64_BUTTON_LAKITU, MB64_BUTTON_FLYGUY, MB64_BUTTON_SNUFIT, MB64_BUTTON_THWOMP, MB64_BUTTON_WHOMP,

    MB64_BUTTON_LGENTLE, MB64_BUTTON_UGENTLE, MB64_BUTTON_TROLL, MB64_BUTTON_WATER, MB64_BUTTON_FENCE, MB64_BUTTON_BARS, MB64_BUTTON_POLE, MB64_BUTTON_TREE, MB64_BUTTON_CULL,
    MB64_BUTTON_BULLY, MB64_BUTTON_MOTOS, MB64_BUTTON_HEAVEHO, MB64_BUTTON_BULLET, MB64_BUTTON_AMP, MB64_BUTTON_PIRANHA, MB64_BUTTON_BOO,MB64_BUTTON_MR_I,MB64_BUTTON_SCUTTLEBUG,

    MB64_BUTTON_STAR, MB64_BUTTON_COIN, MB64_BUTTON_FORMATION, MB64_BUTTON_RCOIN, MB64_BUTTON_BCOIN, MB64_BUTTON_VEXCLA, MB64_BUTTON_TRIGGER, MB64_BUTTON_HEART, _,
    MB64_BUTTON_SPINDRIFT,MB64_BUTTON_BLIZZARD,MB64_BUTTON_MONEYBAG,MB64_BUTTON_SKEETER, MB64_BUTTON_POKEY, MB64_BUTTON_KING_BOBOMB, MB64_BUTTON_WIGGLER, MB64_BUTTON_BOWSER, _,

    MB64_BUTTON_MPLAT, MB64_BUTTON_PURPLE_SWITCH, MB64_BUTTON_TIMED_BOX, MB64_BUTTON_BREAKABLE, MB64_BUTTON_RFBOX, MB64_BUTTON_DIAMOND, MB64_BUTTON_WOODPLAT, MB64_BUTTON_NPC, MB64_BUTTON_KTQ,
    MB64_BUTTON_FIRE, MB64_BUTTON_FLAMETHROWER, MB64_BUTTON_FIRE_SPITTER, MB64_BUTTON_FIRE_SPINNER, MB64_BUTTON_BBALL, _, _, _, _,

    MB64_BUTTON_NOTEBLOCK, MB64_BUTTON_BUTTON, MB64_BUTTON_BLOCK, MB64_BUTTON_CONVEYOR, _, _, _, _, _,
    MB64_BUTTON_SPAWN, MB64_BUTTON_SMALL_BOX, MB64_BUTTON_MINE, _, _, _, _, _, _,
};

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
