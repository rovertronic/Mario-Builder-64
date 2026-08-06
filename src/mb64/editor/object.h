#pragma once

#include "types.h"
#include "mb64/gfx/mb64_buttons.h"

struct Object;

#define MB64_MAX_OBJS 512

struct mb64_obj {
    u8 bparam;
    u8 x;
    u8 y;
    u8 z;
    u8 type;
    u8 rot;
    u8 imbue;
    u8 pad;
};

#define OBJ_TYPE_BILLBOARD (1 << 0)
#define OBJ_TYPE_TRAJECTORY     (1 << 1)
#define OBJ_TYPE_STAR       (1 << 2)
#define OBJ_TYPE_HAS_DIALOG     (1 << 3)
#define OBJ_TYPE_IMBUABLE       (1 << 4)
#define OBJ_TYPE_IMBUABLE_COINS (1 << 5)
#define OBJ_TYPE_IMBUABLE_TRIGGER (1 << 6)

#define OBJ_OCCUPY_OUTER        (1 << 0)
#define OBJ_OCCUPY_INNER        (1 << 1)

#define OBJ_OCCUPY_FULL        (OBJ_OCCUPY_OUTER | OBJ_OCCUPY_INNER)

enum imbue {
    IMBUE_NONE,
    IMBUE_STAR,
    IMBUE_THREE_COINS,
    IMBUE_ONE_COIN,
    IMBUE_GREEN_COIN,
    IMBUE_BLUE_COIN,
    IMBUE_RED_SWITCH,
    IMBUE_BLUE_SWITCH,
    IMBUE_RED_COIN,
    IMBUE_TRIGGER,
    IMBUE_CROWBAR,
    IMBUE_BULLET_MASK,
    IMBUE_BADGE_BASE,
};

enum {
    OBJECT_TYPE_SETTINGS,
    OBJECT_TYPE_1, // empty, used to be for screenshot
    OBJECT_TYPE_STAR,
    OBJECT_TYPE_RED_COIN_STAR,
    OBJECT_TYPE_GOOMBA,
    OBJECT_TYPE_BIG_GOOMBA,
    OBJECT_TYPE_TINY_GOOMBA,
    OBJECT_TYPE_PIRANHA_PLANT,
    OBJECT_TYPE_BIG_PIRANHA_PLANT,
    OBJECT_TYPE_TINY_PIRANHA_PLANT,
    OBJECT_TYPE_KOOPA,
    OBJECT_TYPE_COIN,
    OBJECT_TYPE_GREEN_COIN,
    OBJECT_TYPE_RED_COIN,
    OBJECT_TYPE_BLUE_COIN,
    OBJECT_TYPE_BLUE_COIN_SWITCH,
    OBJECT_TYPE_NOTEBLOCK,
    OBJECT_TYPE_BOBOMB,
    OBJECT_TYPE_CHUCKYA,
    OBJECT_TYPE_BULLY,
    OBJECT_TYPE_CHILL_BULLY,
    OBJECT_TYPE_BULLET_BILL,
    OBJECT_TYPE_HEAVE_HO,
    OBJECT_TYPE_MOTOS,
    OBJECT_TYPE_TREE,
    OBJECT_TYPE_EXCL_BOX,
    OBJECT_TYPE_MARIO_SPAWN,
    OBJECT_TYPE_REX,
    OBJECT_TYPE_PODOBOO,
    OBJECT_TYPE_CRABLET,
    OBJECT_TYPE_HAMMER_BRO,
    OBJECT_TYPE_FIRE_BRO,
    OBJECT_TYPE_CHICKEN,
    OBJECT_TYPE_PHANTASM,
    OBJECT_TYPE_WARP_PIPE,
    OBJECT_TYPE_BADGE,
    OBJECT_TYPE_KING_BOBOMB,
    OBJECT_TYPE_KING_WHOMP,
    OBJECT_TYPE_BIG_BOO,
    OBJECT_TYPE_BIG_BULLY,
    OBJECT_TYPE_BIG_CHILL_BULLY,
    OBJECT_TYPE_WIGGLER,
    OBJECT_TYPE_BOWSER,
    OBJECT_TYPE_PLATFORM_TRACK,
    OBJECT_TYPE_PLATFORM_LOOPING,
    OBJECT_TYPE_BOWLING_BALL,
    OBJECT_TYPE_KOOPA_THE_QUICK,
    OBJECT_TYPE_PURPLE_SWITCH,
    OBJECT_TYPE_TIMED_BOX,
    OBJECT_TYPE_RECOVERY_HEART,
    OBJECT_TYPE_TEST_MARIO,// Fake type, used for the Test mario preview
    OBJECT_TYPE_THWOMP,
    OBJECT_TYPE_WHOMP,
    OBJECT_TYPE_GRINDEL,
    OBJECT_TYPE_LAKITU,
    OBJECT_TYPE_FLY_GUY,
    OBJECT_TYPE_SNUFIT,
    OBJECT_TYPE_AMP,
    OBJECT_TYPE_BOO,
    OBJECT_TYPE_MR_I,
    OBJECT_TYPE_SCUTTLEBUG,
    OBJECT_TYPE_BOWSER_BOMB,
    OBJECT_TYPE_FIRE_SPINNER,
    OBJECT_TYPE_COIN_FORMATION,
    OBJECT_TYPE_RED_FLAME,
    OBJECT_TYPE_BLUE_FLAME,
    OBJECT_TYPE_FIRE_SPITTER,
    OBJECT_TYPE_FLAMETHROWER,
    OBJECT_TYPE_SPINDRIFT,
    OBJECT_TYPE_MR_BLIZZARD,
    OBJECT_TYPE_MONEYBAG,
    OBJECT_TYPE_SKEETER,
    OBJECT_TYPE_POKEY,
    OBJECT_TYPE_BBOX_SMALL,
    OBJECT_TYPE_BBOX_NORMAL,
    OBJECT_TYPE_BBOX_CRAZY,
    OBJECT_TYPE_DIAMOND,
    OBJECT_TYPE_SIGN,
    OBJECT_TYPE_BUDDY,
    OBJECT_TYPE_BUTTON,
    OBJECT_TYPE_ON_OFF_BLOCK,
    OBJECT_TYPE_WOODPLAT,
    OBJECT_TYPE_RFBOX,
    OBJECT_TYPE_CULL_PREVIEW, // also fake type
    OBJECT_TYPE_SHOWRUNNER,
    OBJECT_TYPE_CROWBAR,
    OBJECT_TYPE_MASK,
    OBJECT_TYPE_TOAD,
    OBJECT_TYPE_TUXIE,
    OBJECT_TYPE_UKIKI,
    OBJECT_TYPE_MOLEMAN,
    OBJECT_TYPE_COBIE,
    OBJECT_TYPE_CONVEYOR,
    OBJECT_TYPE_TIMEDBLOCK,
    OBJECT_TYPE_TRIGGER,
    OBJECT_TYPE_TRIGGER_STAR,
};

struct Object;

typedef void (*DisplayFunc)(s32);

struct mb64_object_info {
    char *name;
    const struct ci_texture_define *btn;
    const BehaviorScript *behavior;
    f32 y_offset;
    u16 model_id;
    u8 flags;
    u8 occupy;
    u8 numCoins;
    u8 numExtraObjects;
    f32 scale;
    const struct Animation *const *anim;
    DisplayFunc disp_func;
    u32 soundBits;
};

struct imbue_model {
    s16 model;
    u8 billboarded:1;
    u8 doShrink:1;
    u8 doMove:1;
    f32 scale;
    s16 spin;
};

struct ImbueData {
    u32 coins;
    u32 model;
    u32 color;
};

struct ExclamationBoxContents {
    u8 behParams;
    ModelID16 model;
    const BehaviorScript *behavior;
    u8 animState;
    u8 doRespawn;
    u8 numCoins;
};

extern struct ExclamationBoxContents sExclamationBoxContents_btcm[];
extern struct ExclamationBoxContents sExclamationBoxContents_vanilla[];
extern struct mb64_object_info mb64_object_type_list[];
extern struct ImbueData imbue_table[];

extern struct mb64_obj mb64_object_data[MB64_MAX_OBJS];
extern u16 mb64_object_count;
extern u16 mb64_object_limit_count;
extern u16 mb64_total_coin_count;
extern struct ExclamationBoxContents *mb64_exclamation_box_contents;

s32 mb64_count_stars(void);
void bhv_preview_object_init(void);
void bhv_preview_object_loop(void);
void play_place_sound(u32 soundBits);
s32 get_extra_objects(u32 id, s32 param);
s32 object_sanity_check(void);
struct Object *get_spawn_preview_object(void);
u32 can_place(s8 pos[3], u32 occupyFlags);
u32 can_place_tile(s8 pos[3]);
u32 can_place_object(s8 pos[3]);
struct Object *spawn_preview_object(s8 pos[3], s32 rot, s32 param, struct mb64_object_info *info, const BehaviorScript *script);
void unload_all_preview_objs(void);
void generate_object_preview(void);
void generate_objects_to_level(void);
void delete_object(s32 index);
void place_number_spawner_check(s8 pos[3], s32 spawnerType, s32 objType, s32 objImbue);
void should_spawn_place_number(s8 pos[3]);
void place_object(s8 pos[3]);
void imbue_action(void);
void place_thing_action(void);
void delete_preview_object(void);
