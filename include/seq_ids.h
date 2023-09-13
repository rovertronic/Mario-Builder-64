#ifndef SEQ_IDS_H
#define SEQ_IDS_H

// Sometimes a sequence id is represented as one of the below ids (the base id),
// optionally OR'd with SEQ_VARIATION.
#define SEQ_BASE_ID 0x7f
#define SEQ_VARIATION 0x80
#define SEQUENCE_NONE 0xFF

#define SEQ_MENU_GAME_OVER (SEQ_MENU_TITLE_SCREEN | SEQ_VARIATION)

enum SeqId {
    SEQ_SOUND_PLAYER,                 // 0x00
    SEQ_EVENT_CUTSCENE_COLLECT_STAR,  // 0x01
    SEQ_MENU_TITLE_SCREEN,            // 0x02
    SEQ_LEVEL_GRASS,                  // 0x03
    SEQ_LEVEL_INSIDE_CASTLE,          // 0x04
    SEQ_LEVEL_WATER,                  // 0x05
    SEQ_LEVEL_HOT,                    // 0x06
    SEQ_LEVEL_BOSS_KOOPA,             // 0x07
    SEQ_LEVEL_SNOW,                   // 0x08
    SEQ_LEVEL_SLIDE,                  // 0x09
    SEQ_LEVEL_SPOOKY,                 // 0x0A
    SEQ_EVENT_PIRANHA_PLANT,          // 0x0B
    SEQ_LEVEL_UNDERGROUND,            // 0x0C
    SEQ_MENU_STAR_SELECT,             // 0x0D
    SEQ_EVENT_POWERUP,                // 0x0E
    SEQ_EVENT_METAL_CAP,              // 0x0F
    SEQ_EVENT_KOOPA_MESSAGE,          // 0x10
    SEQ_LEVEL_KOOPA_ROAD,             // 0x11
    SEQ_EVENT_HIGH_SCORE,             // 0x12
    SEQ_EVENT_MERRY_GO_ROUND,         // 0x13
    SEQ_EVENT_RACE,                   // 0x14
    SEQ_EVENT_CUTSCENE_STAR_SPAWN,    // 0x15
    SEQ_EVENT_BOSS,                   // 0x16
    SEQ_EVENT_CUTSCENE_COLLECT_KEY,   // 0x17
    SEQ_EVENT_ENDLESS_STAIRS,         // 0x18
    SEQ_LEVEL_BOSS_KOOPA_FINAL,       // 0x19
    SEQ_EVENT_CUTSCENE_CREDITS,       // 0x1A
    SEQ_EVENT_SOLVE_PUZZLE,           // 0x1B
    SEQ_EVENT_TOAD_MESSAGE,           // 0x1C
    SEQ_EVENT_PEACH_MESSAGE,          // 0x1D
    SEQ_EVENT_CUTSCENE_INTRO,         // 0x1E
    SEQ_EVENT_CUTSCENE_VICTORY,       // 0x1F
    SEQ_EVENT_CUTSCENE_ENDING,        // 0x20
    SEQ_MENU_FILE_SELECT,             // 0x21
    SEQ_EVENT_CUTSCENE_LAKITU,        // 0x22 (not in JP)
    SEQ_STREAMED_BAD_APPLE,           // 0x23
    SEQ_STREAMED_BONEARENA,           // 0x24
    SEQ_FARM,                         // 0x25
    SEQ_PIRATE,                       // 0x26
    SEQ_JUNGLE,                       // 0x27
    SEQ_REDHOT,                       // 0x28
    SEQ_STREAMED_RAIN_OUTSIDE,        // 0x29
    SEQ_STREAMED_RAIN_INSIDE,         // 0x2A
    SEQ_SHOWRUNNER,                   // 0x2B

    SEQ_COSMIC_SEED_COLLECT,          // 0x2C
    SEQ_COSMIC_SEED_LEVEL,            // 0x2D
    SEQ_COSMIC_SEED_BOSS,             // 0x2E

    SEQ_SMB1_OVERWORLD,               // 0x2F
    SEQ_SMB2_OVERWORLD,               // 0x30
    SEQ_SMB3_CASTLE,                  // 0x31
    SEQ_NSMB_CASTLE,                  // 0x32

    SEQ_FINAL_BOSS,                   // 0x33
    SEQ_SHOWRUNNER_BOSS,              // 0x34
    SEQ_BIG_HOUSE,                    // 0x35
    SEQ_LEVEL_KOOPA_ROAD_2,           // 0x36

    SEQ_COUNT
};

#endif // SEQ_IDS_H
