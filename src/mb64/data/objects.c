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

/*  Object Type                  Name                       Button GFX              Behavior           Y Offset     Model                      Flags                                  Coins/Objs/Scale  Anims   Display Func    Sound*/
struct mb64_object_info mb64_object_type_list[] = {
/* OBJECT_TYPE_SETTINGS */      {"Level Settings",          &mb64_btn_settings,       NULL,              0,           MODEL_NONE,                0,                       0,                0, 0, 0.0f, NULL,  NULL, 0},
/* OBJECT_TYPE_1 */             {" ",                       &mb64_btn_settings,       NULL,              0,           MODEL_NONE,                0,                       0,                0, 0, 0.0f, NULL,  NULL, 0}, // previously screenshot
/* OBJECT_TYPE_STAR */          {"Normal",                  &mb64_btn_star,           bhvStar,           TILE_SIZE/2, MODEL_STAR,                OBJ_TYPE_STAR,           OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_star, SOUND_MENU_STAR_SOUND | SOUND_VIBRATO},
/* OBJECT_TYPE_RED_COIN_STAR */ {"Red Coins",               &mb64_btn_redcoinstar,    bhvHiddenRedCoinStar, TILE_SIZE/2, MODEL_TRANSPARENT_STAR, OBJ_TYPE_STAR,           OBJ_OCCUPY_INNER, 0, 1, 1.0f, NULL, df_reds_marker, SOUND_MENU_STAR_SOUND | SOUND_VIBRATO},
/* OBJECT_TYPE_GOOMBA */        {"Normal",                  &mb64_btn_goomba,         bhvGoomba,         0,           MODEL_GOOMBA,              OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 1, 0, 1.5f, goomba_seg8_anims_0801DA4C, NULL, SOUND_OBJ_GOOMBA_PREVIEW},
/* OBJECT_TYPE_BIG_GOOMBA */    {"Huge",                    &mb64_btn_biggoomba,      bhvBigGoomba,      0,           MODEL_GOOMBA,              OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 5, 0, 3.5f, goomba_seg8_anims_0801DA4C, NULL, SOUND_OBJ_GOOMBA_PREVIEW},
/* OBJECT_TYPE_TINY_GOOMBA */   {"Tiny",                    &mb64_btn_tinygoomba,     bhvTinyGoomba,     0,           MODEL_GOOMBA,              OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 1, 0, 0.5f, goomba_seg8_anims_0801DA4C, NULL, SOUND_OBJ_GOOMBA_PREVIEW},
/* OBJECT_TYPE_PIRANHA_PLANT */ {"Normal",                  &mb64_btn_piranha,        bhvPiranhaPlant,   0,           MODEL_MAKER_PLANT,         OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 5, 1, 1.0f, piranha_plant_seg6_anims_0601C31C, df_piranha, SOUND_OBJ2_PIRANHA_PLANT_BITE},
/* OBJECT_TYPE_BIG_PIRANHA_PLANT */  {"Huge",               &mb64_btn_bigfirepiranha, bhvFirePiranhaPlantBig, 0,      MODEL_MAKER_PLANT,         OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 2, 0, 2.0f, piranha_plant_seg6_anims_0601C31C, NULL, SOUND_OBJ2_PIRANHA_PLANT_BITE},
/* OBJECT_TYPE_TINY_PIRANHA_PLANT */ {"Tiny",               &mb64_btn_firepiranha,    bhvFirePiranhaPlant, 0,         MODEL_MAKER_PLANT,         OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 1, 0, 0.5f, piranha_plant_seg6_anims_0601C31C, NULL, SOUND_OBJ2_PIRANHA_PLANT_BITE},
/* OBJECT_TYPE_KOOPA */         {"Koopa",                   &mb64_btn_koopa,          bhvScaredKoopa,    0,           MODEL_KOOPA_WITH_SHELL,    OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 5, 0, 1.5f, koopa_seg6_anims_06011364, df_koopa, SOUND_OBJ_KOOPA_TALK},
/* OBJECT_TYPE_COIN */          {"Yellow Coin",             &mb64_btn_coin,           bhvYellowCoin,     0,           MODEL_YELLOW_COIN,         OBJ_TYPE_BILLBOARD | OBJ_TYPE_IMBUABLE_TRIGGER, OBJ_OCCUPY_INNER, 1, 0, 1.0f, NULL, NULL, SOUND_GENERAL_COIN | SOUND_VIBRATO},
/* OBJECT_TYPE_GREEN_COIN */    {"Green Coin",              &mb64_btn_greencoin,      bhvGreenCoin,      0,           MODEL_GREEN_COIN,          OBJ_TYPE_BILLBOARD | OBJ_TYPE_IMBUABLE_TRIGGER, OBJ_OCCUPY_INNER, 3, 0, 1.0f, NULL, NULL, SOUND_GENERAL_COIN_MULTI},
/* OBJECT_TYPE_RED_COIN */      {"Red Coin",                &mb64_btn_redcoin,        bhvRedCoin,        0,           MODEL_RED_COIN,            OBJ_TYPE_BILLBOARD,      OBJ_OCCUPY_INNER, 2, 0, 1.0f, NULL, NULL, SOUND_MENU_COLLECT_RED_COIN},
/* OBJECT_TYPE_BLUE_COIN */     {"Coin",                    &mb64_btn_bluecoin,       bhvHiddenBlueCoin, 0,           MODEL_BLUE_COIN,           OBJ_TYPE_BILLBOARD | OBJ_TYPE_IMBUABLE_TRIGGER, OBJ_OCCUPY_INNER, 5, 0, 1.0f, NULL, NULL, SOUND_GENERAL_COIN_MULTI},
/* OBJECT_TYPE_BLUE_COIN_SWITCH */ {"Switch",               &mb64_btn_bluecoinswitch, bhvBlueCoinSwitch, 0,           MODEL_BLUE_COIN_SWITCH,    OBJ_TYPE_IMBUABLE_TRIGGER, OBJ_OCCUPY_INNER, 0, 0, 3.0f, NULL, NULL, SOUND_GENERAL2_PURPLE_SWITCH},
/* OBJECT_TYPE_NOTEBLOCK */     {"Noteblock",               &mb64_btn_noteblock,      bhvNoteblock,      TILE_SIZE/2, MODEL_NOTEBLOCK,           0,                       OBJ_OCCUPY_INNER, 0, 0, 1.27f,NULL, NULL, SOUND_GENERAL_CRAZY_BOX_BOING_SLOW},
/* OBJECT_TYPE_BOBOMB */        {"Bob-omb",                 &mb64_btn_bobomb,         bhvBobomb,         0,           MODEL_BLACK_BOBOMB,        OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 1, 0, 1.0f, bobomb_anims, NULL, SOUND_GENERAL2_QUIET_EXPLOSION},
/* OBJECT_TYPE_CHUCKYA */       {"Chuckya",                 &mb64_btn_chuckya,        bhvChuckya,        0,           MODEL_CHUCKYA,             OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 5, 0, 2.0f, chuckya_seg8_anims_0800C070, df_chuckya, SOUND_OBJ_CHUCKYA_PREVIEW},
/* OBJECT_TYPE_BULLY */         {"Bully",                   &mb64_btn_bully,          bhvSmallBully,     0,           MODEL_BULLY,               OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 1, 0, 1.0f, bully_seg5_anims_0500470C, NULL, SOUND_OBJ2_SMALL_BULLY_ATTACKED},
/* OBJECT_TYPE_CHILL_BULLY */   {"Chill Bully",             &mb64_btn_chillbully,     bhvSmallBully,     0,           MODEL_CHILL_BULLY,         OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 1, 0, 1.0f, bully_seg5_anims_0500470C, NULL, SOUND_OBJ2_SMALL_BULLY_ATTACKED},
/* OBJECT_TYPE_BULLET_BILL */   {"Bullet Bill",             &mb64_btn_bulletbill,     bhvBulletBillCannon, TILE_SIZE/2, MODEL_BILL_MAKER_2,      0,                       OBJ_OCCUPY_FULL,  0, 1, 1.0f, NULL, NULL, SOUND_OBJ_POUNDING_CANNON},
/* OBJECT_TYPE_HEAVE_HO */      {"Heave-Ho",                &mb64_btn_heaveho,        bhvHeaveHo,        0,           MODEL_MAKER_HEAVEHO,       OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS, OBJ_OCCUPY_INNER, 0, 0, 2.0f, heave_ho_seg5_anims_0501534C, NULL, SOUND_OBJ_HEAVEHO_PREVIEW},
/* OBJECT_TYPE_MOTOS */         {"Motos",                   &mb64_btn_motos,          bhvMotos,          0,           MODEL_MAKER_MOTOS,         OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 5, 0, 2.0f, motos_anime, NULL, SOUND_OBJ_HEAVEHO_PREVIEW},
/* OBJECT_TYPE_TREE */          {"Tree",                    &mb64_btn_bubblytree,     bhvTree,           0,           MODEL_MAKER_TREE_1,        OBJ_TYPE_BILLBOARD,      OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_tree, SOUND_ACTION_CLIMB_UP_TREE | SOUND_VIBRATO},
/* OBJECT_TYPE_EXCL_BOX */      {"Item Box",                &mb64_btn_exclamationbox, bhvExclamationBox, TILE_SIZE/2, MODEL_EXCLAMATION_BOX,     OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 0, 0, 2.0f, NULL, df_exbox, SOUND_GENERAL_BOX_PREVIEW},
/* OBJECT_TYPE_SPAWN */         {"Mario Spawn",             &mb64_btn_spawn,          bhvSpawn,          TILE_SIZE/2, MODEL_SPAWN,               0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_hide_during_screenshot, SOUND_MENU_STAR_SOUND_LETS_A_GO},
/* OBJECT_TYPE_REX */           {"Rex",                     &mb64_btn_rex,            bhvRex,            0,           MODEL_REX,                 OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 2, 0, 1.5f, Rex_anims, NULL, SOUND_OBJ_GOOMBA_PREVIEW},
/* OBJECT_TYPE_PODOBOO */       {"Podoboo",                 &mb64_btn_podoboo,        bhvPodoboo,        TILE_SIZE/2, MODEL_PODOBOO,             0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_podoboo, SOUND_OBJ_FLAME_BLOWN},
/* OBJECT_TYPE_CRABLET */       {"Crablet",                 &mb64_btn_crablet,        bhvCrablet,        0,           MODEL_MAKER_CRABLET,       OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 4, 0, 1.0f, crab_anims_anims, NULL, SOUND_OBJ2_SCUTTLEBUG_ALERT},
/* OBJECT_TYPE_HAMMER_BRO */    {"Normal",                  &mb64_btn_hammerbro,      bhvHammerBro,      0,           MODEL_HAMMER_BRO,          OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 6, 0, 1.0f, Hammerbro_anims, df_hammerbro, SOUND_OBJ_KOOPA_DAMAGE},
/* OBJECT_TYPE_FIRE_BRO */      {"Fire Bro",                &mb64_btn_firebro,        bhvFireBro,        0,           MODEL_HAMMER_BRO,          OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 6, 0, 1.0f, Hammerbro_anims, df_firebro, SOUND_OBJ_KOOPA_DAMAGE},
/* OBJECT_TYPE_CHICKEN */       {"Chicken",                 &mb64_btn_chicken,        bhvChicken,        TILE_SIZE/2, MODEL_MAKER_CHICKEN,       OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 2, 0, 1.0f, chicken_anims, NULL, SOUND_OBJ_BOO_LAUGH_SHORT},
/* OBJECT_TYPE_PHANTASM */      {"Cosmic Phantasm",         &mb64_btn_cosmicphantasm, bhvPhantasm,       0,           MODEL_MARIO,               OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 5, 9, 1.0f, &evil_mario_anims[2], NULL, SOUND_ACTION_METAL_STEP | SOUND_VIBRATO},
/* OBJECT_TYPE_WARP_PIPE */     {"Warp Pipe",               &mb64_btn_pipe,           bhvStaticObject,   0,           MODEL_MAKER_PIPE,          0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_MENU_ENTER_PIPE | SOUND_VIBRATO},
/* OBJECT_TYPE_BADGE */         {"Badge",                   &mb64_btn_badgelava,      bhvBadge,          TILE_SIZE/2, MODEL_BADGE,               OBJ_TYPE_BILLBOARD | OBJ_TYPE_IMBUABLE_TRIGGER, OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_GENERAL2_PURPLE_SWITCH},
/* OBJECT_TYPE_KING_BOBOMB */   {"King Bob-omb",            &mb64_btn_kingbobomb,     bhvKingBobomb,     0,           MODEL_KINGBOMB_MAKER,      OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  0, 0, 1.0f, king_bobomb_seg5_anims_0500FE30, df_kingbomb, SOUND_OBJ_KING_BOBOMB_POUNDING1_HIGHPRIO},
/* OBJECT_TYPE_KING_WHOMP */    {"King Whomp",              &mb64_btn_kingwhomp,      bhvWhompKingBoss,  0,           MODEL_WHOMP_MAKER,         OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  0, 1, 2.0f, whomp_seg6_anims_06020A04, NULL, SOUND_OBJ_WHOMP},
/* OBJECT_TYPE_BIG_BOO */       {"Big Boo",                 &mb64_btn_bigboo,         bhvBalconyBigBoo,  TILE_SIZE,   MODEL_MAKER_BOO,           OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS, OBJ_OCCUPY_FULL,  0, 0, 3.0f, NULL, df_boo, SOUND_OBJ_BOO_LAUGH_LONG},
/* OBJECT_TYPE_BIG_BULLY */     {"Big Bully",               &mb64_btn_bigbully,       bhvBigBully,       0,           MODEL_BULLY,               OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  0, 0, 2.0f, bully_seg5_anims_0500470C, NULL, SOUND_OBJ2_LARGE_BULLY_ATTACKED},
/* OBJECT_TYPE_BIG_CHILL_BULLY */ {"Big Chill Bully",       &mb64_btn_chiefchilly,    bhvBigBully,       0,           MODEL_CHILL_BULLY,         OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  0, 0, 2.0f, bully_seg5_anims_0500470C, NULL, SOUND_OBJ2_LARGE_BULLY_ATTACKED},
/* OBJECT_TYPE_WIGGLER */       {"Wiggler",                 &mb64_btn_wiggler,        bhvWigglerHead,    0,           MODEL_WIGGLER_HEAD,        OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  0, 5, 4.0f, wiggler_seg5_anims_0500EC8C, df_wiggler, SOUND_OBJ_WIGGLER_TALK},
/* OBJECT_TYPE_BOWSER */        {"Bowser",                  &mb64_btn_bowser,         bhvBowser,         0,           MODEL_MAKER_BOWSER,        OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  0, 24, 1.0f, bowser_anims, df_bowser, SOUND_OBJ2_BOWSER_ROAR},
/* OBJECT_TYPE_PLATFORM_TRACK */ {"Activated",              &mb64_btn_movingplatform, bhvPlatformOnTrack, TILE_SIZE/2, MODEL_CHECKERBOARD_PLATFORM, OBJ_TYPE_TRAJECTORY,  OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_ENV_ELEVATOR1 | SOUND_VIBRATO},
/* OBJECT_TYPE_PLATFORM_LOOPING */ {"Looping",              &mb64_btn_movingplatform, bhvLoopingPlatform, TILE_SIZE/2, MODEL_LOOPINGP,           OBJ_TYPE_TRAJECTORY,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_ENV_ELEVATOR1 | SOUND_VIBRATO},
/* OBJECT_TYPE_BOWLING_BALL */  {"Bowling Ball",            &mb64_btn_bowlingball,    bhvBobBowlingBallSpawner, TILE_SIZE/2, MODEL_BOWLING_BALL, OBJ_TYPE_BILLBOARD | OBJ_TYPE_TRAJECTORY, OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_GENERAL_QUIET_POUND1 | SOUND_VIBRATO},
/* OBJECT_TYPE_KOOPA_THE_QUICK */ {"Koopa the Quick",       &mb64_btn_ktq,            bhvKoopa,          0,           MODEL_KOOPA_WITH_SHELL,    OBJ_TYPE_TRAJECTORY | OBJ_TYPE_STAR, OBJ_OCCUPY_FULL, 0, 1, 3.0f, koopa_seg6_anims_06011364, df_ktq, SOUND_OBJ_KOOPA_TALK},
/* OBJECT_TYPE_PURPLE_SWITCH */ {"Purple Switch",           &mb64_btn_purpleswitch,   bhvFloorSwitchHiddenObjects, 0, MODEL_PURPLE_SWITCH,       0,                       OBJ_OCCUPY_INNER, 0, 0, 1.28f,NULL, NULL, SOUND_GENERAL2_PURPLE_SWITCH},
/* OBJECT_TYPE_TIMED_BOX */     {"Breakable",               &mb64_btn_timedbox,       bhvHiddenObject,   0,           MODEL_BREAKABLE_BOX,       0,                       OBJ_OCCUPY_OUTER, 0, 0, 1.0f, NULL, df_timedbox, SOUND_GENERAL2_SWITCH_TICK_FAST},
/* OBJECT_TYPE_RECOVERY_HEART */ {"Recovery Heart",         &mb64_btn_recoveryheart,  bhvRecoveryHeart,  TILE_SIZE/2, MODEL_HEART,               0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_heart, SOUND_GENERAL_HEART_SPIN},
/* OBJECT_TYPE_TEST_MARIO */    {"Save & Test",             &mb64_btn_check,          NULL,              0,           MODEL_MARIO,               0,                       OBJ_OCCUPY_FULL,  0, 0, 1.0f, mario_btcm_anims, NULL, 0},
/* OBJECT_TYPE_THWOMP */        {"Thwomp",                  &mb64_btn_thwomp,         bhvThwomp,         0,           MODEL_THWOMP_MAKER,        0,                       OBJ_OCCUPY_FULL,  0, 2, 1.5f, NULL, NULL, SOUND_OBJ_THWOMP},
/* OBJECT_TYPE_WHOMP */         {"Whomp",                   &mb64_btn_whomp,          bhvSmallWhomp,     0,           MODEL_WHOMP_MAKER,         OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL, 10, 1, 1.0f, whomp_seg6_anims_06020A04, NULL, SOUND_OBJ_WHOMP},
/* OBJECT_TYPE_GRINDEL */       {"Grindel",                 &mb64_btn_grindel,        bhvGrindel,        0,           MODEL_MAKER_GRINDEL,       0,                       OBJ_OCCUPY_FULL,  0, 2, 1.0f, NULL, df_grindel, SOUND_OBJ_KING_BOBOMB_JUMP},
/* OBJECT_TYPE_LAKITU */        {"Lakitu",                  &mb64_btn_lakitu,         bhvEnemyLakitu,    TILE_SIZE/2, MODEL_LAKITU_MAKER,        OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 5, 5, 1.0f, lakitu_enemy_seg5_anims_050144D4, df_lakitu, SOUND_OBJ_EVIL_LAKITU_THROW},
/* OBJECT_TYPE_FLY_GUY */       {"Fly Guy",                 &mb64_btn_flyguy,         bhvFlyGuy,         TILE_SIZE/2, MODEL_FLYGUY,              OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 2, 0, 1.5f, flyguy_seg8_anims_08011A64, df_flyguy, SOUND_OBJ_KOOPA_FLYGUY_DEATH},
/* OBJECT_TYPE_SNUFIT */        {"Snufit",                  &mb64_btn_snufit,         bhvSnufit,         TILE_SIZE/2, MODEL_MAKER_SNUFIT,        OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 2, 0, 1.0f, NULL, df_snufit, SOUND_OBJ_SNUFIT_SHOOT},
/* OBJECT_TYPE_AMP */           {"Amp",                     &mb64_btn_amp,            bhvCirclingAmp,    TILE_SIZE/2, MODEL_AMP,                 0,                       OBJ_OCCUPY_OUTER, 0, 0, 1.0f, amp_anims, df_circling_amp, SOUND_AIR_AMP_PREVIEW},
/* OBJECT_TYPE_BOO */           {"Boo",                     &mb64_btn_boo,            bhvBoo,            TILE_SIZE/2, MODEL_MAKER_BOO,           OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS,  OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_boo, SOUND_OBJ_BOO_LAUGH_LONG},
/* OBJECT_TYPE_MR_I */          {"Mr. I",                   &mb64_btn_mri,            bhvMrI,            0,           MODEL_MAKER_MRI,           OBJ_TYPE_IMBUABLE | OBJ_TYPE_BILLBOARD, OBJ_OCCUPY_INNER, 5, 1, 1.0f, NULL, df_mri, SOUND_OBJ_MRI_SHOOT},
/* OBJECT_TYPE_SCUTTLEBUG */    {"Scuttlebug",              &mb64_btn_scuttlebug,     bhvScuttlebug,     0,           MODEL_MAKER_SCUTTLEBUG,    OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 3, 0, 1.0f, scuttlebug_seg6_anims_06015064, NULL, SOUND_OBJ2_SCUTTLEBUG_ALERT},
/* OBJECT_TYPE_BOWSER_BOMB */   {"Bowser Bomb",             &mb64_btn_bowserbomb,     bhvBowserBomb,     TILE_SIZE/2, MODEL_MAKER_BOWSER_BOMB,   0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_GENERAL2_QUIET_EXPLOSION},
/* OBJECT_TYPE_FIRE_SPINNER */  {"Fire Spinner",            &mb64_btn_firespinner,    bhvLllRotatingBlockWithFireBars, 0, MODEL_MAKER_FIREBAR,   0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_fire_spinner, SOUND_OBJ_FLAME_BLOWN},
/* OBJECT_TYPE_COIN_FORMATION */ {"Coin Formation",         &mb64_btn_coinline,       bhvCoinFormation,  0,           MODEL_NONE,                0,                       OBJ_OCCUPY_FULL,  0, 0, 1.0f, NULL, df_coin_formation, SOUND_GENERAL_COIN_MULTI},
/* OBJECT_TYPE_RED_FLAME */     {"Red",                     &mb64_btn_redflame,       bhvFlame,          90,          MODEL_RED_FLAME,           OBJ_TYPE_BILLBOARD,      OBJ_OCCUPY_INNER, 0, 0, 7.0f, NULL, df_flame, SOUND_OBJ_FLAME_BLOWN},
/* OBJECT_TYPE_BLUE_FLAME */    {"Blue",                    &mb64_btn_blueflame,      bhvFlame,          90,          MODEL_BLUE_FLAME,          OBJ_TYPE_BILLBOARD,      OBJ_OCCUPY_INNER, 0, 0, 7.0f, NULL, df_flame, SOUND_OBJ_FLAME_BLOWN},
/* OBJECT_TYPE_FIRE_SPITTER */  {"Fire Spitter",            &mb64_btn_firespitter,    bhvFireSpitter,    TILE_SIZE/2, MODEL_BOWLING_BALL,        OBJ_TYPE_BILLBOARD,      OBJ_OCCUPY_INNER, 0, 0, 0.2f, NULL, NULL, SOUND_OBJ_FLAME_BLOWN},
/* OBJECT_TYPE_FLAMETHROWER */  {"Flamethrower",            &mb64_btn_flamethrower,   bhvFlamethrower,   TILE_SIZE/2, MODEL_MAKER_FLAMETHROWER,  0,                       OBJ_OCCUPY_FULL,  0, 5, 1.0f, NULL, NULL, SOUND_OBJ_FLAME_BLOWN},
/* OBJECT_TYPE_SPINDRIFT */     {"Spindrift",               &mb64_btn_spindrift,      bhvSpindrift,      0,           MODEL_MAKER_SPINDRIFT,     OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 3, 0, 1.0f, spindrift_seg5_anims_05002D68, NULL, SOUND_ACTION_TWIRL},
/* OBJECT_TYPE_MR_BLIZZARD */   {"Mr. Blizzard",            &mb64_btn_mrblizzard,     bhvMrBlizzard,     0,           MODEL_MAKER_BLIZZARD,      OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 3, 0, 1.0f, snowman_seg5_anims_0500D118, df_blizzard, SOUND_OBJ2_SCUTTLEBUG_ALERT},
/* OBJECT_TYPE_MONEYBAG */      {"Moneybag",                &mb64_btn_moneybag,       bhvMoneybagHidden, 0,           MODEL_MONEYBAG,            OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS, OBJ_OCCUPY_INNER, 0, 1, 1.0f, moneybag_seg6_anims_06005E5C, df_moneybag, SOUND_GENERAL_MONEYBAG_BOING_LOWPRIO},
/* OBJECT_TYPE_SKEETER */       {"Skeeter",                 &mb64_btn_skeeter,        bhvSkeeter,        0,           MODEL_MAKER_SKEETER,       OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_INNER, 3, 0, 1.0f, skeeter_seg6_anims_06007DE0, df_skeeter, SOUND_OBJ_SKEETER_WALK},
/* OBJECT_TYPE_POKEY */         {"Pokey",                   &mb64_btn_pokey,          bhvPokey,          0,           MODEL_MAKER_POKEY_HEAD,    OBJ_TYPE_IMBUABLE | OBJ_TYPE_BILLBOARD, OBJ_OCCUPY_INNER, 5, 5, 3.0f, NULL, df_pokey, SOUND_OBJ_POKEY_DEATH},
/* OBJECT_TYPE_BBOX_SMALL*/     {"Throwable Box",           &mb64_btn_smallbox,       bhvBreakableBoxSmall, 0,        MODEL_BREAKABLE_BOX_SMALL, 0,                       OBJ_OCCUPY_INNER, 3, 0, 0.31f,NULL, df_corkbox, SOUND_GENERAL_BOX_PREVIEW},
/* OBJECT_TYPE_BBOX_NORMAL*/    {"Breakable Box",           &mb64_btn_box,            bhvBreakableBox,   0,           MODEL_BREAKABLE_BOX,       OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS, OBJ_OCCUPY_FULL, 0, 0, 1.0f, NULL, df_corkbox, SOUND_GENERAL_BOX_PREVIEW},
/* OBJECT_TYPE_BBOX_CRAZY*/     {"Crazy Box",               &mb64_btn_crazybox,       bhvJumpingBox,     0,           MODEL_BREAKABLE_BOX_SMALL, 0,                       OBJ_OCCUPY_INNER, 5, 0, 0.38f,NULL, df_crazybox, SOUND_GENERAL_CRAZY_BOX_BOING_SLOW},
/* OBJECT_TYPE_DIAMOND*/        {"Water Diamond",           &mb64_btn_waterdiamond,   bhvWaterLevelDiamond,0,         MODEL_MAKER_DIAMOND,       0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_GENERAL_WATER_LEVEL_TRIG},
/* OBJECT_TYPE_SIGN */          {"Bill Board",              &mb64_btn_signpost,       bhvMessagePanel,   0,           MODEL_WOODEN_SIGNPOST,     OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_ACTION_READ_SIGN},
/* OBJECT_TYPE_BUDDY */         {"Bob-omb Buddy",           &mb64_btn_bobombbuddy,    bhvBobombBuddy,    0,           MODEL_BOBOMB_BUDDY,        OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, bobomb_anims, NULL, SOUND_OBJ_BOBOMB_BUDDY_TALK},
/* OBJECT_TYPE_BUTTON */        {"On-Off Button",           &mb64_btn_redswitch,      bhvOnOffButton,    0,           MODEL_MAKER_BUTTON,        0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_button, SOUND_GENERAL_BUTTON_PRESS},
/* OBJECT_TYPE_ON_OFF_BLOCK */  {"On-Off Block",            &mb64_btn_redblock,       bhvOnOffBlock,     0,           MODEL_MAKER_BLOCK_OFF,     0,                       OBJ_OCCUPY_OUTER, 0, 0, 1.0f, NULL, df_block, SOUND_GENERAL_BUTTON_PRESS},
/* OBJECT_TYPE_WOODPLAT */      {"Wooden Platform",         &mb64_btn_woodplatform,   bhvWoodPlat,       0,           MODEL_MAKER_WOODPLAT,      0,                       OBJ_OCCUPY_FULL,  0, 1, 1.0f, NULL, df_woodplat, SOUND_ACTION_TERRAIN_STEP + (SOUND_TERRAIN_SPOOKY << 16)},
/* OBJECT_TYPE_RFBOX */         {"Reinforced Box",          &mb64_btn_rfbox,          bhvBreakableBoxRF, 0,           MODEL_MAKER_RFBOX,         OBJ_TYPE_IMBUABLE | OBJ_TYPE_IMBUABLE_COINS, OBJ_OCCUPY_FULL, 0, 0, 1.0f, NULL, NULL, SOUND_OBJ_BULLY_METAL},
/* OBJECT_TYPE_CULL_PREVIEW */  {"",                        &mb64_btn_cullmarker,     bhvStaticObject,   TILE_SIZE/2, MODEL_CULL_MARKER,         OBJ_TYPE_BILLBOARD,      OBJ_OCCUPY_INNER, 0, 0, 1.f,  NULL, NULL, 0},
/* OBJECT_TYPE_SHOWRUNNER */    {"Showrunner",              &mb64_btn_showrunner,     bhvShowrunner,     0,           MODEL_MAKER_SHOWRUNNER,    OBJ_TYPE_IMBUABLE,       OBJ_OCCUPY_FULL,  50,39,1.0f, showrunner_anims, NULL, SOUND_OBJ_MRI_SHOOT},
/* OBJECT_TYPE_CROWBAR */       {"Crowbar",                 &mb64_btn_pipebar,        bhvCrowbarPower,   TILE_SIZE/2, MODEL_MAKER_CROWBAR,       0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_crowbar, SOUND_MENU_EXIT_PIPE},
/* OBJECT_TYPE_MASK    */       {"Bullet Bill Mask",        &mb64_btn_bulletmask,     bhvBMask,          TILE_SIZE/2, MODEL_MAKER_MASK,          0,                       OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_mask, SOUND_MENU_EXIT_PIPE},
/* OBJECT_TYPE_TOAD */          {"Toad",                    &mb64_btn_toad,           bhvMakerToad,      0,           MODEL_MAKER_TOAD,          OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, toad_seg6_anims_0600FB58, df_toad, SOUND_ACTION_READ_SIGN},
/* OBJECT_TYPE_TUXIE */         {"Tuxie",                   &mb64_btn_tuxie,          bhvMakerTuxie,     0,           MODEL_MAKER_TUXIE,         OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, penguin_seg5_anims_05008B74, NULL, SOUND_OBJ2_BABY_PENGUIN_YELL},
/* OBJECT_TYPE_UKIKI */         {"Ukiki",                   &mb64_btn_ukiki,          bhvMakerUkiki,     0,           MODEL_MAKER_UKIKI,         OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, ukiki_seg5_anims_05015784, df_ukiki, SOUND_OBJ_UKIKI_CHATTER_SHORT},
/* OBJECT_TYPE_MOLEMAN */       {"Moleman",                 &mb64_btn_moleman,        bhvMoleman,        65,          MODEL_MAKER_MOLEMAN,       OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, moleman3_anims, NULL, SOUND_ACTION_READ_SIGN},
/* OBJECT_TYPE_COBIE */         {"Cobie",                   &mb64_btn_cowboy,         bhvCobie,          0,           MODEL_MAKER_COBIE,         OBJ_TYPE_HAS_DIALOG,     OBJ_OCCUPY_INNER, 0, 0, 1.0f, cobie2_anims, NULL, SOUND_ACTION_READ_SIGN},
/* OBJECT_TYPE_CONVEYOR */      {"Conveyor",                &mb64_btn_conveyor,       bhvConveyor,       0,           MODEL_MAKER_CONVEYOR_HALF, 0,                       OBJ_OCCUPY_FULL,  0, 0, 1.0f, NULL, df_conveyor, SOUND_OBJ_HEAVEHO_PREVIEW},
/* OBJECT_TYPE_TIMED_BLOCK */   {"Inverted",                &mb64_btn_invertedtimedblock, bhvTimedBlock, 0,           MODEL_MAKER_BLOCK_OFF,     0,                       OBJ_OCCUPY_OUTER, 0, 0, 1.0f, NULL, df_timedblock, SOUND_GENERAL2_SWITCH_TICK_FAST},
/* OBJECT_TYPE_TRIGGER */       {"Star Trigger",            &mb64_btn_trigger,        bhvStaticObject,   TILE_SIZE/2, MODEL_MAKER_IMBUE_TRIGGER, OBJ_TYPE_BILLBOARD,      OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, NULL, SOUND_MENU_COLLECT_SECRET},
/* OBJECT_TYPE_TRIGGER_STAR */  {"Star Triggers",           &mb64_btn_triggerstar,    bhvHiddenStar,     TILE_SIZE/2, MODEL_TRANSPARENT_STAR,    OBJ_TYPE_STAR,           OBJ_OCCUPY_INNER, 0, 0, 1.0f, NULL, df_star, SOUND_MENU_STAR_SOUND | SOUND_VIBRATO},
};

struct mb64_ui_option mb64_star_options[] = {
    { NULL, &mb64_btn_star,        OBJECT_TYPE_STAR, 0 },
    { NULL, &mb64_btn_redcoinstar, OBJECT_TYPE_RED_COIN_STAR, 0 },
    { NULL, &mb64_btn_triggerstar, OBJECT_TYPE_TRIGGER_STAR, 0 },
};
struct mb64_ui_option mb64_goomba_options[] = {
    { NULL, &mb64_btn_goomba,     OBJECT_TYPE_GOOMBA, 0 },
    { NULL, &mb64_btn_biggoomba,  OBJECT_TYPE_BIG_GOOMBA, 0 },
    { NULL, &mb64_btn_tinygoomba, OBJECT_TYPE_TINY_GOOMBA, 0 },
};
struct mb64_ui_option mb64_piranha_options[] = {
    { NULL, &mb64_btn_piranha,        OBJECT_TYPE_PIRANHA_PLANT, 0 },
    { NULL, &mb64_btn_bigfirepiranha, OBJECT_TYPE_BIG_PIRANHA_PLANT, 0 },
    { NULL, &mb64_btn_firepiranha,    OBJECT_TYPE_TINY_PIRANHA_PLANT, 0 },
};
struct mb64_ui_option mb64_bluecoin_options[] = {
    { NULL, &mb64_btn_bluecoin,       OBJECT_TYPE_BLUE_COIN, 0 },
    { NULL, &mb64_btn_bluecoinswitch, OBJECT_TYPE_BLUE_COIN_SWITCH, 0 },
};
struct mb64_ui_option mb64_hammer_options[] = {
    { NULL, &mb64_btn_hammerbro, OBJECT_TYPE_HAMMER_BRO, 0 },
    { NULL, &mb64_btn_firebro,   OBJECT_TYPE_FIRE_BRO, 0 },
};
struct mb64_ui_option mb64_whomp_options[] = {
    { NULL, &mb64_btn_whomp,     OBJECT_TYPE_WHOMP, 0 },
    { NULL, &mb64_btn_kingwhomp, OBJECT_TYPE_KING_WHOMP, 0 },
};
struct mb64_ui_option mb64_bully_options[] = {
    { NULL, &mb64_btn_bully,       OBJECT_TYPE_BULLY, 0 },
    { NULL, &mb64_btn_chillbully,  OBJECT_TYPE_CHILL_BULLY, 0 },
    { NULL, &mb64_btn_bigbully,    OBJECT_TYPE_BIG_BULLY, 0 },
    { NULL, &mb64_btn_chiefchilly, OBJECT_TYPE_BIG_CHILL_BULLY, 0 },
};
struct mb64_ui_option mb64_boo_options[] = {
    { NULL, &mb64_btn_boo,    OBJECT_TYPE_BOO, 0 },
    { NULL, &mb64_btn_bigboo, OBJECT_TYPE_BIG_BOO, 0 },
};
struct mb64_ui_option mb64_plat_options[] = {
    { NULL, &mb64_btn_movingplatform, OBJECT_TYPE_PLATFORM_TRACK, 0 },
    { NULL, &mb64_btn_loopplatform, OBJECT_TYPE_PLATFORM_LOOPING, 0 },
};
struct mb64_ui_option mb64_thwomp_options[] = {
    { NULL, &mb64_btn_thwomp,  OBJECT_TYPE_THWOMP, 0 },
    { NULL, &mb64_btn_grindel, OBJECT_TYPE_GRINDEL, 0 },
};
struct mb64_ui_option mb64_flame_options[] = {
    { NULL, &mb64_btn_redflame,  OBJECT_TYPE_RED_FLAME, 0 },
    { NULL, &mb64_btn_blueflame, OBJECT_TYPE_BLUE_FLAME, 0 },
};
struct mb64_ui_option mb64_npc_options[] = {
    { NULL, &mb64_btn_signpost,    OBJECT_TYPE_SIGN, 0 },
    { NULL, &mb64_btn_bobombbuddy, OBJECT_TYPE_BUDDY, 0 },
    { NULL, &mb64_btn_toad,        OBJECT_TYPE_TOAD, 0 },
    { NULL, &mb64_btn_tuxie,       OBJECT_TYPE_TUXIE, 0 },
    { NULL, &mb64_btn_ukiki,       OBJECT_TYPE_UKIKI, 0 },
};
struct mb64_ui_option mb64_npccm_options[] = {
    { NULL, &mb64_btn_signpost,    OBJECT_TYPE_SIGN, 0 },
    { NULL, &mb64_btn_bobombbuddy, OBJECT_TYPE_BUDDY, 0 },
    { NULL, &mb64_btn_moleman,     OBJECT_TYPE_MOLEMAN, 0 },
    { NULL, &mb64_btn_cowboy,      OBJECT_TYPE_COBIE, 0 },
};
struct mb64_ui_option mb64_power_options[] = {
    { NULL, &mb64_btn_pipebar,    OBJECT_TYPE_CROWBAR, 0 },
    { NULL, &mb64_btn_bulletmask, OBJECT_TYPE_MASK, 0 },
};
struct mb64_ui_option mb64_timedbox_options[] = {
    { NULL, &mb64_btn_timedbox,           OBJECT_TYPE_TIMED_BOX, 0 },
    { NULL, &mb64_btn_invertedtimedblock, OBJECT_TYPE_TIMEDBLOCK, 0 },
};
struct mb64_ui_option mb64_smallbox_options[] = {
    { NULL, &mb64_btn_smallbox, OBJECT_TYPE_BBOX_SMALL, 0 },
    { NULL, &mb64_btn_crazybox, OBJECT_TYPE_BBOX_CRAZY, 0 },
};

struct mb64_ui_option mb64_tree_options[] = {
    { "Bubbly", &mb64_btn_bubblytree, OBJECT_TYPE_TREE, 0 },
    { "Palm",   &mb64_btn_palmtree,   OBJECT_TYPE_TREE, 1 },
    { "Spiky",  &mb64_btn_spikytree,  OBJECT_TYPE_TREE, 2 },
    { "Snowy",  &mb64_btn_snowytree,  OBJECT_TYPE_TREE, 3 },
    { "Farm",   &mb64_btn_farmtree,   OBJECT_TYPE_TREE, 4 },
    { "Dead",   &mb64_btn_deadtree,   OBJECT_TYPE_TREE, 5 },
};
struct mb64_ui_option mb64_excla_options[] = {
    { "One Coin",     &mb64_btn_questionbox, OBJECT_TYPE_EXCL_BOX, 4 },
    { "Three Coins",  &mb64_btn_questionbox, OBJECT_TYPE_EXCL_BOX, 5 },
    { "Ten Coins",    &mb64_btn_questionbox, OBJECT_TYPE_EXCL_BOX, 6 },
    { "Green Coin",   &mb64_btn_questionbox, OBJECT_TYPE_EXCL_BOX, 3 },
    { "Rocket Boots", &mb64_btn_rocketbox, OBJECT_TYPE_EXCL_BOX, 0 },
    { "Vanetal Cap",  &mb64_btn_vanetalbox, OBJECT_TYPE_EXCL_BOX, 1 },
    { "Koopa Shell",  &mb64_btn_exclamationbox, OBJECT_TYPE_EXCL_BOX, 2 },
};
struct mb64_ui_option mb64_vexcla_options[] = {
    { "One Coin",    &mb64_btn_exclamationbox, OBJECT_TYPE_EXCL_BOX, 4 },
    { "Three Coins", &mb64_btn_exclamationbox, OBJECT_TYPE_EXCL_BOX, 5 },
    { "Ten Coins",   &mb64_btn_exclamationbox, OBJECT_TYPE_EXCL_BOX, 6 },
    { "Wing Cap",    &mb64_btn_wingbox, OBJECT_TYPE_EXCL_BOX, 0 },
    { "Metal Cap",   &mb64_btn_metalbox, OBJECT_TYPE_EXCL_BOX, 1 },
    { "Vanish Cap",  &mb64_btn_vanishbox, OBJECT_TYPE_EXCL_BOX, 2 },
    { "Koopa Shell", &mb64_btn_exclamationbox, OBJECT_TYPE_EXCL_BOX, 3 },
};
struct mb64_ui_option mb64_badge_options[] = {
    { "Lava Boost",       &mb64_btn_badgelava,       OBJECT_TYPE_BADGE, 0 },
    { "Fall Damage",      &mb64_btn_badgefall,       OBJECT_TYPE_BADGE, 1 },
    { "Defense",          &mb64_btn_badgedefense,    OBJECT_TYPE_BADGE, 2 },
    { "One Hit",          &mb64_btn_badgedamage,     OBJECT_TYPE_BADGE, 3 },
    { "Gills",            &mb64_btn_badgegills,      OBJECT_TYPE_BADGE, 4 },
    { "Fins",             &mb64_btn_badgefins,       OBJECT_TYPE_BADGE, 5 },
    { "HP Regen",         &mb64_btn_badgehp,         OBJECT_TYPE_BADGE, 6 },
    { "Mana Regen",       &mb64_btn_badgemana,       OBJECT_TYPE_BADGE, 7 },
    { "Greed",            &mb64_btn_badgegreed,      OBJECT_TYPE_BADGE, 8 },
    { "Double Time",      &mb64_btn_badgetime,       OBJECT_TYPE_BADGE, 9 },
    { "Magnet",           &mb64_btn_badgemagnet,     OBJECT_TYPE_BADGE, 10 },
    { "Burn",             &mb64_btn_badgeburn,       OBJECT_TYPE_BADGE, 11 },
    { "Squish",           &mb64_btn_badgesquish,     OBJECT_TYPE_BADGE, 12 },
    { "Feather",          &mb64_btn_badgefeather,    OBJECT_TYPE_BADGE, 13 },
    { "Weight",           &mb64_btn_badgeweight,     OBJECT_TYPE_BADGE, 14 },
    { "Sticky",           &mb64_btn_badgesticky,     OBJECT_TYPE_BADGE, 15 },
    { "Fast Foot",        &mb64_btn_badgefeet,       OBJECT_TYPE_BADGE, 16 },
    { "Heal Plus",        &mb64_btn_badgeheal,       OBJECT_TYPE_BADGE, 17 },
    { "Bottomless",       &mb64_btn_badgebottomless, OBJECT_TYPE_BADGE, 18 },
    { "Slow Fall",        &mb64_btn_badgeslowfall,   OBJECT_TYPE_BADGE, 19 },
    { "Brittle Burden",   &mb64_btn_badgebrittle,    OBJECT_TYPE_BADGE, 20 },
    { "Withering Burden", &mb64_btn_badgewither,     OBJECT_TYPE_BADGE, 21 },
};
struct mb64_ui_option mb64_formation_options[] = {
    { "Line",          &mb64_btn_coinline,         OBJECT_TYPE_COIN_FORMATION, 0 },
    { "Vertical Line", &mb64_btn_verticalcoinline, OBJECT_TYPE_COIN_FORMATION, 1 },
    { "Ring",          &mb64_btn_coinring,         OBJECT_TYPE_COIN_FORMATION, 2 },
    { "Vertical Ring", &mb64_btn_verticalcoinring, OBJECT_TYPE_COIN_FORMATION, 3 },
    { "Arrow",         &mb64_btn_coinarrow,        OBJECT_TYPE_COIN_FORMATION, 4 },
};
struct mb64_ui_option mb64_fire_spinner_options[] = {
    { "Length: 2", &mb64_btn_firespinner, OBJECT_TYPE_FIRE_SPINNER, 0 },
    { "Length: 3", &mb64_btn_firespinner, OBJECT_TYPE_FIRE_SPINNER, 1 },
    { "Length: 4", &mb64_btn_firespinner, OBJECT_TYPE_FIRE_SPINNER, 2 },
    { "Length: 5", &mb64_btn_firespinner, OBJECT_TYPE_FIRE_SPINNER, 3 },
    { "Length: 6", &mb64_btn_firespinner, OBJECT_TYPE_FIRE_SPINNER, 4 },
};
struct mb64_ui_option mb64_button_options[] = {
    { "Red",  &mb64_btn_redswitch,  OBJECT_TYPE_BUTTON, 0 },
    { "Blue", &mb64_btn_blueswitch, OBJECT_TYPE_BUTTON, 1 },
};
struct mb64_ui_option mb64_block_options[] = {
    { "Red",  &mb64_btn_redblock,  OBJECT_TYPE_ON_OFF_BLOCK, 0 },
    { "Blue", &mb64_btn_blueblock, OBJECT_TYPE_ON_OFF_BLOCK, 1 },
};
struct mb64_ui_option mb64_woodplat_options[] = {
    { "Thin", &mb64_btn_woodplatform,     OBJECT_TYPE_WOODPLAT, 0 },
    { "Full", &mb64_btn_fullwoodplatform, OBJECT_TYPE_WOODPLAT, 1 },
};
struct mb64_ui_option mb64_conveyor_options[] = {
    { "Thin",               &mb64_btn_conveyor,        OBJECT_TYPE_CONVEYOR, 0 },
    { "Full",               &mb64_btn_fullconveyor,    OBJECT_TYPE_CONVEYOR, 1 },
    { "Upwards",            &mb64_btn_upconveyor,      OBJECT_TYPE_CONVEYOR, 2 },
    { "Downwards",          &mb64_btn_downconveyor,    OBJECT_TYPE_CONVEYOR, 3 },
    { "Thin (On-Off)",      &mb64_btn_redconveyor,     OBJECT_TYPE_CONVEYOR, 4 },
    { "Full (On-Off)",      &mb64_btn_redfullconveyor, OBJECT_TYPE_CONVEYOR, 5 },
    { "Upwards (On-Off)",   &mb64_btn_redupconveyor,   OBJECT_TYPE_CONVEYOR, 6 },
    { "Downwards (On-Off)", &mb64_btn_reddownconveyor, OBJECT_TYPE_CONVEYOR, 7 },
};

#define BTN_ID(mode, objId)             { mode, 0, NULL, { .id = objId } }
#define BTN_OPTS(mode, label, opts)     { mode, ARRAY_COUNT(opts), label, { .options = opts } }

struct mb64_ui_button_type mb64_ui_buttons[] = {
/* MB64_BUTTON_SETTINGS */ BTN_ID(MB64_PM_ACTION, OBJECT_TYPE_SETTINGS),
/* MB64_BUTTON_TEST */     BTN_ID(MB64_PM_ACTION, OBJECT_TYPE_TEST_MARIO),
/* MB64_BUTTON_TERRAIN */  BTN_ID(MB64_PM_TILE, TILE_TYPE_BLOCK),
/* MB64_BUTTON_SLOPE */    BTN_ID(MB64_PM_TILE, TILE_TYPE_SLOPE),
/* MB64_BUTTON_TROLL */    BTN_ID(MB64_PM_TILE, TILE_TYPE_TROLL),
/* MB64_BUTTON_STAR */     BTN_OPTS(MB64_PM_OBJ, "Power Stars", mb64_star_options),
/* MB64_BUTTON_GOOMBA */   BTN_OPTS(MB64_PM_OBJ, "Goombas", mb64_goomba_options),
/* MB64_BUTTON_PIRANHA */  BTN_OPTS(MB64_PM_OBJ, "Piranha Plants", mb64_piranha_options),
/* MB64_BUTTON_KOOPA */    BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_KOOPA),
/* MB64_BUTTON_COIN */     BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_COIN),
/* MB64_BUTTON_BLANK */    BTN_ID(MB64_PM_TILE, TILE_TYPE_BLOCK),
/* MB64_BUTTON_GCOIN */    BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_GREEN_COIN),
/* MB64_BUTTON_CORNER */   BTN_ID(MB64_PM_TILE, TILE_TYPE_CORNER),
/* MB64_BUTTON_ICORNER */  BTN_ID(MB64_PM_TILE, TILE_TYPE_ICORNER),
/* MB64_BUTTON_RCOIN */    BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_RED_COIN),
/* MB64_BUTTON_BCOIN */    BTN_OPTS(MB64_PM_OBJ, "Blue Coins", mb64_bluecoin_options),
/* MB64_BUTTON_NOTEBLOCK */BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_NOTEBLOCK),
/* MB64_BUTTON_CULL */     BTN_ID(MB64_PM_TILE, TILE_TYPE_CULL),
/* MB64_BUTTON_BOBOMB */   BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_BOBOMB),
/* MB64_BUTTON_CHUCKYA */  BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_CHUCKYA),
/* MB64_BUTTON_BULLY */    BTN_OPTS(MB64_PM_OBJ, "Bullies", mb64_bully_options),
/* MB64_BUTTON_BULLET */   BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_BULLET_BILL),
/* MB64_BUTTON_HEAVEHO */  BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_HEAVE_HO),
/* MB64_BUTTON_MOTOS */    BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_MOTOS),
/* MB64_BUTTON_TREE */     BTN_OPTS(MB64_PM_OBJ, NULL, mb64_tree_options),
/* MB64_BUTTON_EXCLA */    BTN_OPTS(MB64_PM_OBJ, NULL, mb64_excla_options),
/* MB64_BUTTON_SPAWN */    BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_MARIO_SPAWN),
/* MB64_BUTTON_REX */      BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_REX),
/* MB64_BUTTON_PODOBOO */  BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_PODOBOO),
/* MB64_BUTTON_CRABLET */  BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_CRABLET),
/* MB64_BUTTON_HAMMER_BRO */BTN_OPTS(MB64_PM_OBJ, "Hammer Bros", mb64_hammer_options),
/* MB64_BUTTON_CHICKEN */  BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_CHICKEN),
/* MB64_BUTTON_PHANTASM */ BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_PHANTASM),
/* MB64_BUTTON_PIPE */     BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_WARP_PIPE),
/* MB64_BUTTON_BADGE */    BTN_OPTS(MB64_PM_OBJ, NULL, mb64_badge_options),
/* MB64_BUTTON_WATER */    BTN_ID(MB64_PM_TILE, TILE_TYPE_WATER),
/* MB64_BUTTON_FENCE */    BTN_ID(MB64_PM_TILE, TILE_TYPE_FENCE),
/* MB64_BUTTON_KING_BOBOMB */ BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_KING_BOBOMB),
/* MB64_BUTTON_WIGGLER */  BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_WIGGLER),
/* MB64_BUTTON_BOWSER */   BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_BOWSER),
/* MB64_BUTTON_MPLAT */    BTN_OPTS(MB64_PM_OBJ, "Moving Platforms", mb64_plat_options),
/* MB64_BUTTON_BBALL */    BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_BOWLING_BALL),
/* MB64_BUTTON_KTQ */      BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_KOOPA_THE_QUICK),
/* MB64_BUTTON_SSLOPE */   BTN_ID(MB64_PM_TILE, TILE_TYPE_SSLOPE),
/* MB64_BUTTON_SLAB */     BTN_ID(MB64_PM_TILE, TILE_TYPE_SLAB),
/* MB64_BUTTON_PURPLE_SWITCH */BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_PURPLE_SWITCH),
/* MB64_BUTTON_TIMED_BOX */ BTN_OPTS(MB64_PM_OBJ, "Timed Boxes", mb64_timedbox_options),
/* MB64_BUTTON_HEART */    BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_RECOVERY_HEART),
/* MB64_BUTTON_FORMATION */BTN_OPTS(MB64_PM_OBJ, NULL, mb64_formation_options),
/* MB64_BUTTON_VSLAB */    BTN_ID(MB64_PM_TILE, TILE_TYPE_SSLAB),
/* MB64_BUTTON_SCORNER */  BTN_ID(MB64_PM_TILE, TILE_TYPE_SCORNER),
/* MB64_BUTTON_UGENTLE */  BTN_ID(MB64_PM_TILE, TILE_TYPE_UGENTLE),
/* MB64_BUTTON_LGENTLE */  BTN_ID(MB64_PM_TILE, TILE_TYPE_LGENTLE),
/* MB64_BUTTON_BARS */     BTN_ID(MB64_PM_TILE, TILE_TYPE_BARS),
/* MB64_BUTTON_THWOMP */   BTN_OPTS(MB64_PM_OBJ, "Thwomps", mb64_thwomp_options),
/* MB64_BUTTON_WHOMP */    BTN_OPTS(MB64_PM_OBJ, "Whomps", mb64_whomp_options),
/* MB64_BUTTON_POLE */     BTN_ID(MB64_PM_TILE, TILE_TYPE_POLE),
/* MB64_BUTTON_VEXCLA */   BTN_OPTS(MB64_PM_OBJ, NULL, mb64_vexcla_options),
/* MB64_BUTTON_LAKITU */   BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_LAKITU),
/* MB64_BUTTON_FLYGUY */   BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_FLY_GUY),
/* MB64_BUTTON_SNUFIT */   BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_SNUFIT),
/* MB64_BUTTON_AMP */      BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_AMP),
/* MB64_BUTTON_BOO */      BTN_OPTS(MB64_PM_OBJ, "Boos", mb64_boo_options),
/* MB64_BUTTON_MR_I */     BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_MR_I),
/* MB64_BUTTON_SCUTTLEBUG */BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_SCUTTLEBUG),
/* MB64_BUTTON_SPINDRIFT */BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_SPINDRIFT),
/* MB64_BUTTON_BLIZZARD */ BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_MR_BLIZZARD),
/* MB64_BUTTON_MONEYBAG */ BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_MONEYBAG),
/* MB64_BUTTON_SKEETER */  BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_SKEETER),
/* MB64_BUTTON_POKEY */    BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_POKEY),
/* MB64_BUTTON_MINE */     BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_BOWSER_BOMB),
/* MB64_BUTTON_FIRE */     BTN_OPTS(MB64_PM_OBJ, "Flames", mb64_flame_options),
/* MB64_BUTTON_FLAMETHROWER */BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_FLAMETHROWER),
/* MB64_BUTTON_FIRE_SPITTER */BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_FIRE_SPITTER),
/* MB64_BUTTON_FIRE_SPINNER */BTN_OPTS(MB64_PM_OBJ, NULL, mb64_fire_spinner_options),
/* MB64_BUTTON_BREAKABLE */BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_BBOX_NORMAL),
/* MB64_BUTTON_SMALL_BOX */BTN_OPTS(MB64_PM_OBJ, "Boxes", mb64_smallbox_options),
/* MB64_BUTTON_DIAMOND */  BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_DIAMOND),
/* MB64_BUTTON_NPC */      BTN_OPTS(MB64_PM_OBJ, "NPCs", mb64_npc_options),
/* MB64_BUTTON_NPCCM */    BTN_OPTS(MB64_PM_OBJ, "NPCs", mb64_npccm_options),
/* MB64_BUTTON_BUTTON */   BTN_OPTS(MB64_PM_OBJ, NULL, mb64_button_options),
/* MB64_BUTTON_BLOCK */    BTN_OPTS(MB64_PM_OBJ, NULL, mb64_block_options),
/* MB64_BUTTON_WOODPLAT */ BTN_OPTS(MB64_PM_OBJ, NULL, mb64_woodplat_options),
/* MB64_BUTTON_RFBOX */    BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_RFBOX),
/* MB64_BUTTON_SHOWRUN */  BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_SHOWRUNNER),
/* MB64_BUTTON_POWER */    BTN_OPTS(MB64_PM_OBJ, "Powerups", mb64_power_options),
/* MB64_BUTTON_CONVEYOR */ BTN_OPTS(MB64_PM_OBJ, NULL, mb64_conveyor_options),
/* MB64_BUTTON_ISCORNER */ BTN_ID(MB64_PM_TILE, TILE_TYPE_ISCORNER),
/* MB64_BUTTON_TRIGGER */  BTN_ID(MB64_PM_OBJ, OBJECT_TYPE_TRIGGER),
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
