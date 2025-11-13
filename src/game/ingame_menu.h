#ifndef INGAME_MENU_H
#define INGAME_MENU_H

#include <PR/ultratypes.h>

enum MenuMtxPushOp {
    MENU_MTX_NONE,
    MENU_MTX_PUSH,
    MENU_MTX_NOPUSH,
};

struct DialogEntry {
    /*0x00*/ u32 unused;
    /*0x04*/ s8 linesPerBox;
    /*0x06*/ s16 leftOffset;
    /*0x08*/ s16 width;
    /*0x0C*/ const u8 *str;
};

// definitions for some of the special characters defined in charmap.txt
enum DialogSpecialChars {
    DIALOG_CHAR_SLASH                = 0xD0,
    DIALOG_CHAR_PERIOD               = 0x6E,
    DIALOG_CHAR_COMMA                = 0x6F,
    DIALOG_CHAR_COLOR                = 0xDF,
    DIALOG_CHAR_SPACE                = 0x9E,
    DIALOG_CHAR_STAR_COUNT           = 0xE0, // number of stars
    DIALOG_CHAR_UMLAUT               = 0xE9,
    DIALOG_CHAR_MARK_START           = 0xEF,
    DIALOG_CHAR_STAR_FILLED          = 0xFA,
    DIALOG_CHAR_STAR_OPEN            = 0xFD,
    DIALOG_CHAR_NEWLINE              = 0xFE,
    DIALOG_CHAR_TERMINATOR           = 0xFF
};

extern s16 gRedCoinsCollected;
extern s16 gRedCoinsTotal;
extern s16 gStarTriggersCollected;
extern s16 gStarTriggersTotal;
extern u8 *costume_text[];
extern u8 start_precredits;
extern u8 *badgenames[];
extern u8 *badgedescs[];

void create_dl_translation_matrix(s8 pushOp, f32 x, f32 y, f32 z);
void create_dl_ortho_matrix(void);
void create_dl_scale_matrix(s8 pushOp, f32 x, f32 y, f32 z);
void print_generic_string_ascii(s16 x, s16 y, const char *str);
s32 get_string_width_ascii(const char *str);
void print_hud_string_ascii(s16 x, s16 y, char *str);
s32 get_hud_string_width_ascii(char *str);

enum costume_enum {
    CTM_MARIO,
    CTM_FIRE,
    CTM_GLITCHY,
    CTM_LUIGI,
    CTM_WARIO,
    CTM_DISCO,
    CTM_PIRATE,
    CTM_MOCAP,
    CTM_DARIUS,
    CTM_BUTLER,
    CTM_RETRO,
    CTM_THWOMPIO,
    CTM_BUILDER,
    CTM_RUNNER,
    CTM_PHANTASM
};

enum badge_enum {
    BADGE_LAVA,//SOLD!
    BADGE_FALL,//SOLD!
    BADGE_DEFENSE,//SOLD!
    BADGE_DAMAGE,//SOLD!
    BADGE_GILLS,//SOLD!
    BADGE_FINS,//SOLD!
    BADGE_HP,//SOLD!
    BADGE_MANA,//SOLD!
    BADGE_GREED,//SOLD!
    BADGE_TIME,//SOLD!
    BADGE_MAGNET,//SOLD!
    BADGE_BURN,//SOLD!
    BADGE_SQUISH,//SOLD!
    BADGE_FEATHER,//SOLD!
    BADGE_WEIGHT,//SOLD!
    BADGE_STICKY,//SOLD!
    BADGE_FEET,//SOLD!
    BADGE_HEAL,//SOLD!
    BADGE_BOTTOMLESS,//SOLD!
    BADGE_SLOWFALL,//SOLD!
    BADGE_BRITTLE,//SOLD!
    BADGE_WITHER,//SOLD!
    BADGE_HARDCORE,//SOLD!
};

#endif // INGAME_MENU_H
