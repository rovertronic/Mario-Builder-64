#ifndef SAVE_FILE_H
#define SAVE_FILE_H

#include <PR/ultratypes.h>

#include "types.h"
#include "area.h"
#include "puppycam2.h"

#include "course_table.h"

#if defined(SRAM)
    #define EEPROM_SIZE 0x8000
#elif defined(EEP16K)
    #define EEPROM_SIZE 0x800
#else
    #define EEPROM_SIZE 0x200
#endif

#define NUM_SAVE_FILES 3

struct SaveBlockSignature {
    u16 magic;
    u16 chksum;
};

struct SaveFile {
    u16 UnlockedCostumes;
    u16 WalletCollected;
    u16 GlobalCoins;
    u8 OptionFlags;
    u8 UnlockedMinigames;
    u8 MinigameHighscores[8]; //64 bits
    u32 flags;
    u8 courseStars[COURSE_COUNT];
    u8 courseCoinScores[COURSE_STAGES_COUNT];
    u32 PlayTime;
    u32 UnlockedBadges : 24;
    u8 progression : 4;
    u8 UpgradeLevel : 4;
    u32 EquippedBadges : 24;
    u8 SavedCostume;
    u8 SavedLanguage;

    struct SaveBlockSignature signature; // 32 bits
};

enum SaveFileIndex {
    SAVE_FILE_A,
    SAVE_FILE_B,
    SAVE_FILE_C,
    SAVE_FILE_D
};

enum Options {
    OPT_MUSIC,
    OPT_WIDESCREEN,
    OPT_MINIMAP,
    OPT_HUD,
    OPT_SAVE,
    OPT_CAMCOL,
};

struct MainMenuSaveData {
    // Each save file has a 2 bit "age" for each course. The higher this value,
    // the older the high score is. This is used for tie-breaking when displaying
    // on the high score screen.
    u32 coinScoreAges[NUM_SAVE_FILES];

    struct SaveBlockSignature signature;
};

struct SaveBuffer {
    // Main menu data, storing config options.
    struct MainMenuSaveData menuData;
    // Each of the four save files has two copies. If one is bad, the other is used as a backup.
    struct SaveFile files[NUM_SAVE_FILES][2];
};

STATIC_ASSERT(sizeof(struct SaveBuffer) <= EEPROM_SIZE, "eeprom buffer size higher than intended");

#ifdef PUPPYCAM
extern void puppycam_set_save(void);
extern void puppycam_get_save(void);
extern void puppycam_check_save(void);
#endif

STATIC_ASSERT(sizeof(struct SaveBuffer) <= EEPROM_SIZE, "ERROR: Save struct too big for specified save type");

extern u8 gLastCompletedCourseNum;
extern u8 gLastCompletedStarNum;
extern s8 sUnusedGotGlobalCoinHiScore;
extern u8 gGotFileCoinHiScore;
extern u8 gCurrCourseStarFlags;
extern u8 gSpecialTripleJump;
extern s8 gLevelToCourseNumTable[];

enum Progression {
    PROG_LETTER_INIT,
    PROG_START,
    PROG_MIRROR,//set when the mirror shatters
    PROG_TRUE_START,
    PROG_TALK_2,//set when first intereacting with showrunner
    PROG_10_STARS,//set when collecting 10 stars
    PROG_DEFEAT_BOWSER_1,//set when defeated bowser
    PROG_CORE_DEFEAT,//set when destroy core
    PROG_DEFEAT_BOWSER_2,//set when talk to bowser again
    PROG_40_STARS,//set at 40 stars, only if bowser defeated 2 (actually 30)
    PROG_QUIZ_COMPLETE_ANGRY,//set after showrunner quiz, bad ending
    PROG_QUIZ_COMPLETE_HAPPY,//set after showrunner quiz, good ending
    PROG_DEFEAT_SHOWRUNNER,//set when showrunner is defeated, unlocks projector
    PROG_ON_AGAMEMNON,//set upon entering agamemnon
    PROG_POSTGAME,//set when agamemnon is defeated,
    PROG_POSTPOST_GAME,//set at 100% completion (unlocks cheats (and toolgun?))
};

enum CourseFlags {
    COURSE_FLAG_CANNON_UNLOCKED      = (1 <<  7), /* 0x00000080 */
};

// game progress flags
enum SaveProgressFlags {
    SAVE_FLAG_FILE_EXISTS            = (1 <<  0), /* 0x00000001 */
    SAVE_FLAG_HAVE_WING_CAP          = (1 <<  1), /* 0x00000002 */
    SAVE_FLAG_HAVE_METAL_CAP         = (1 <<  2), /* 0x00000004 */
    SAVE_FLAG_HAVE_VANISH_CAP        = (1 <<  3), /* 0x00000008 */
    SAVE_FLAG_HAVE_YELLOW            = (1 <<  4), /* 0x00000010 */
    SAVE_FLAG_HAVE_KEY_1             = (1 <<  5), /* 0x00000020 */
    SAVE_FLAG_HAVE_KEY_2             = (1 <<  6), /* 0x00000040 */
    SAVE_FLAG_UNLOCKED_BASEMENT_DOOR = (1 <<  7), /* 0x00000080 */
    SAVE_FLAG_UNLOCKED_UPSTAIRS_DOOR = (1 <<  8), /* 0x00000100 */

    SAVE_FLAG_BOOKSHELF_MOVED        = (1 <<  9), /* 0x00000200 */
    SAVE_FLAG_TALKED_TO_TOAD         = (1 << 10), /* 0x00000400 */
    SAVE_FLAG_LENS_INSERTED          = (1 << 11), /* 0x00000800 */
    SAVE_FLAG_THWOMPGATE_OPEN        = (1 << 12), /* 0x00001000 */
    SAVE_FLAG_HAPPY_SHOWRUNNER       = (1 << 13), /* 0x00002000 */
    SAVE_FLAG_DEFEATED_WHOMP         = (1 << 14), /* 0x00004000 */
    SAVE_FLAG_FREE_BADGE             = (1 << 15),

    //23 is limit, anything beyond are secret stars

    SAVE_FLAG_COLLECTED_TOAD_STAR_1  = (1 << 24), /* 0x01000000 */
    SAVE_FLAG_COLLECTED_TOAD_STAR_2  = (1 << 25), /* 0x02000000 */
    SAVE_FLAG_COLLECTED_TOAD_STAR_3  = (1 << 26), /* 0x04000000 */
    SAVE_FLAG_COLLECTED_MIPS_STAR_1  = (1 << 27), /* 0x08000000 */
    SAVE_FLAG_COLLECTED_MIPS_STAR_2  = (1 << 28), /* 0x10000000 */

    // stubbed save flags
    SAVE_FLAG_DDD_MOVED_BACK         = 0,
    SAVE_FLAG_MOAT_DRAINED           = 0,
    SAVE_FLAG_CAP_ON_GROUND          = 0,
    SAVE_FLAG_CAP_ON_KLEPTO          = 0,
    SAVE_FLAG_CAP_ON_UKIKI           = 0,
    SAVE_FLAG_CAP_ON_MR_BLIZZARD     = 0,
};

enum StarFlags {
    STAR_FLAGS_NONE         = (0 << 0), // 0x00
    STAR_FLAG_ACT_1         = (1 << 0), // 0x01
    STAR_FLAG_ACT_2         = (1 << 1), // 0x02
    STAR_FLAG_ACT_3         = (1 << 2), // 0x04
    STAR_FLAG_ACT_4         = (1 << 3), // 0x08
    STAR_FLAG_ACT_5         = (1 << 4), // 0x10
    STAR_FLAG_ACT_6         = (1 << 5), // 0x20
    STAR_FLAG_ACT_100_COINS = (1 << 6), // 0x40
    STAR_FLAG_LAST          = STAR_FLAG_ACT_100_COINS
};

#define SAVE_FLAG_TO_STAR_FLAG(cmd) (((cmd) >> 24) & 0x7F)
#define STAR_FLAG_TO_SAVE_FLAG(cmd) ((cmd) << 24)

// Variable for setting a warp checkpoint.

// possibly a WarpDest struct where arg is a union. TODO: Check?
struct WarpCheckpoint {
    /*0x00*/ u8 actNum;
    /*0x01*/ u8 courseNum;
    /*0x02*/ u8 levelID;
    /*0x03*/ u8 areaNum;
    /*0x04*/ u8 warpNode;
};

extern struct WarpCheckpoint gWarpCheckpoint;

extern s8 gMainMenuDataModified;
extern s8 gSaveFileModified;

void save_file_do_save(s32 fileIndex);
void save_file_erase(s32 fileIndex);
void save_file_copy(s32 srcFileIndex, s32 destFileIndex);
void save_file_load_all(void);
void save_file_reload(void);
void save_file_collect_star_or_key(s16 coinScore, s16 starIndex);
s32 save_file_exists(s32 fileIndex);
u32 save_file_get_max_coin_score(s32 courseIndex);
s32 save_file_get_course_star_count(s32 fileIndex, s32 courseIndex);
s32 save_file_get_total_star_count(s32 fileIndex, s32 minCourse, s32 maxCourse);
s32 save_file_get_total_golden_star_count(s32 fileIndex, s32 minCourse, s32 maxCourse);
s32 save_file_get_total_metal_star_count(s32 fileIndex, s32 minCourse, s32 maxCourse);
void save_file_set_flags(u32 flags);
void save_file_clear_flags(u32 flags);
u32 save_file_get_flags(void);
u32 save_file_get_star_flags(s32 fileIndex, s32 courseIndex);
void save_file_set_star_flags(s32 fileIndex, s32 courseIndex, u32 starFlags);
s32 save_file_get_course_coin_score(s32 fileIndex, s32 courseIndex);
s32 save_file_is_cannon_unlocked(void);
void save_file_set_cannon_unlocked(void);
void save_file_set_cap_pos(s16 x, s16 y, s16 z);
s32 save_file_get_cap_pos(Vec3s capPos);
#ifdef WIDE
u32 save_file_get_widescreen_mode(void);
void save_file_set_widescreen_mode(u8 mode);
#endif
void save_file_move_cap_to_default_location(void);

void save_file_set_stats(void);
void save_file_get_stats(void);


void disable_warp_checkpoint(void);
void check_if_should_set_warp_checkpoint(struct WarpNode *warpNode);
s32 check_warp_checkpoint(struct WarpNode *warpNode);

void save_file_set_costume_unlock(u32 flags);
void save_file_set_wallet_unlock(u32 flags);
u32 save_file_get_costume_unlock(void);
u32 save_file_get_wallet_unlock(void);
u32 save_file_get_badge_equip(void);
u32 save_file_get_badge_unlock(void);
void save_file_set_badge_unlock(u32 flags);
void save_file_set_badge_equip(u32 flags);
void save_file_set_badge_unequip(u32 flags);
void save_file_set_badge_unequip_all(void);
void save_file_unlock_minigame(u8 minigame);
s32 save_file_check_minigame(u8 minigame);

s32 save_file_get_hiscore(u8 minigame);
s32 save_file_set_hiscore(u8 minigame, u8 newscore);

u32 save_file_check_progression(u32 prog_enum);

u32 save_file_set_progression(u32 prog_enum);
u32 save_file_get_progression(void);

void save_file_one_second();
u16 save_file_get_time();
u16 save_file_index_get_time(s8 index);
u16 save_file_index_get_prog(s8 index);
u8 get_evil_badge_bonus(void);

void save_file_do_save_force(s32 fileIndex);

#if MULTILANG
enum EuLanguages {
    LANGUAGE_ENGLISH,
    LANGUAGE_FRENCH,
    LANGUAGE_GERMAN
};

void eu_set_language(u16 language);
u32 eu_get_language(void);
#else
#define LANGUAGE_ENGLISH 0
#endif

#endif // SAVE_FILE_H
