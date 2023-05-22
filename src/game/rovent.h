extern u8 revent_active;
extern u8 revent_camera_on;
extern u8 revent_hud;
extern s8 revent_room;
extern u16 revent_index;
extern Vec3f revent_camera_pos;
extern Vec3f revent_camera_foc;
extern u8 revent_stop_enemies;
extern u8 revent_queue;
extern u8 *rtext_insert_pointer[3];
extern u8 minigame_real;
extern u8 minigame_transition;
extern u8 minigame_newscore;
extern u8 revent_head_move;
extern u8 revent_handstate;
extern u16 revent_tempo;
extern s16 revent_headangle[3];

extern u8 mg_minscores[];

extern u8 *costume_effect_text[];

enum revent_command_h {
    E_WAIT,//Time in Frames

    E_TARGET_OBJECT,//Target Behavior
    E_TARGET_MARIO,
    E_TARGET_OBJECT_DELETE,
    E_TARGET_OBJECT_SPAWN,//Model ID, Behavior, BehParam2,
    E_TARGET_OBJECT_ACTION,//o->oAction
    E_TARGET_OBJECT_SUBACTION,//o->oSubAction

    E_START_LOOP,
    E_REPEAT,//Repetitions

    E_HUD_TOGGLE,
    E_ENEMIES_TOGGLE,
    E_QUEUE,//queue id

    E_HEAD_TOGGLE,
    E_HEAD_ANGLE,//yaw,pitch,roll

    E_CAM_TOGGLE,
    E_CAM_FOCUS_TARGET,
    E_CAM_FOCUS_XYZ,//X,Y,Z
    E_CAM_POS_XYZ,//X,Y,Z
    E_CAM_ORBIT,//Distance, Height, Speed
    E_CAM_MASTER_SHOT,//distance, angle offset
    E_CAM_CLOSE_UP,
    E_CAM_DUTCH_TILT,
    E_CAM_180DEGREE_RULE, //actor
    E_CAM_MANUAL_ECM, //cam mode
    E_CAM_SPLINE, //spline data pointer, frames

    E_ZOUND,//sound id
    E_MUSIC,//seq id
    E_STOP_MUSIC,
    E_TEMPO,//amount
    E_ACT,//mario action
    E_PUZZLE_JINGLE,
    E_ROOM,//room
    E_SAVEGAME,
    E_PROGRESS_SET,//prog
    E_SAVEFLAG_SET,//flag

    E_WALK_TO_TARGET,//dist before stopping
    E_WALK_FROM_TARGET,//dist to go away

    E_DIALOG, // dialog id
    E_DIALOG_AND_PRESSA,// dialog id
    E_DIALOG_WAIT_PRESSA,
    E_DIALOG_WAIT_END,
    E_DIALOG_WAIT_UPGRADE,
    E_CLOSE_DIALOG,
    E_DIALOG_YESNO,
    E_DIALOG_ABCD,
    E_DIALOG_ABC,
    E_DIALOG_AB,
    E_DIALOG_CHOICE_JUMP,//choice index,how much to jump
    E_JUMP,//how much to jump

    E_PUT_ON_COSTUME,

    E_MARIO_LOCK,
    E_MARIO_UNLOCK,
    E_MARIO_YAW,//yaw
    E_MARIO_HANDSTATE,//handstate
    E_MARIO_VEL,//fwdvel
    E_MARIO_TELEPORT,//x,y,z

    E_MINIGAME_MENU,
    E_MINIGAME_UNLOCK,//NULL

    E_COSTUME_MENU,
    E_MUSIC_MENU,

    E_QUIZ_HOST,
    E_QUIZ_CONTESTANT,//0 hambro|1 mario|2 robot
    E_QUIZ_SCORES,
    E_DIALOG_BUZZ_IN,
    E_QUIZ_POINT,//how many
    E_QUIZ_POINT_JUMP,//minimum, jump

    E_TARGET_OBJECT_SPOTLIGHT,

    E_WARP,//warp id

    E_START_PRECREDITS,
    E_END,
};

enum revent_camera_modes {
    ECM_STATIC,
    ECM_ORBIT,
    ECM_ORBIT_TRACK,
    ECM_TRACK_TARGET,
    ECM_TRACK_MARIO,
    ECM_SPLINE,
};

enum revent_events {
    EVENT_TEST,
    EVENT_THWOMP_TOWERS_GATE,
    EVENT_VIRTUAPLEX_GATE,
    EVENT_PODE_INTRO,
    EVENT_WALLET,
    EVENT_COSTUME,
    EVENT_STARDOOR,
    EVENT_METALSTARDOOR,
    EVENT_MINIGAME,
    EVENT_MINIGAME_HI,
    EVENT_SWITCH_1,
    EVENT_SWITCH_2,
    EVENT_SWITCH_3,
    EVENT_SWITCH_4,
    EVENT_LETTER,
    EVENT_SHOWRUNNER_1,
    EVENT_TOAD_MEET,
    EVENT_COSTUME_SELECT,
    EVENT_MUSIC_SELECT,
    EVENT_BOWSER_DEFEAT,
    EVENT_BOWSER_INTRO,
    EVENT_BOWSER_POST,
    EVENT_VIRTUAPLEX_DOOR,
    EVENT_QUIZ,
    EVENT_QUIZ_2,
    EVENT_STATUE_ROTATE,
    EVENT_SHOWRUNNER_BATTLE_1,
    EVENT_SHOWRUNNER_BATTLE_2,
    EVENT_SHOWRUNNER_BATTLE_3,
    EVENT_SHOWRUNNER_BATTLE_4,
    EVENT_ELEVATOR,
    EVENT_CREDITS,
    EVENT_AGHEART_STRUCK,
    EVENT_AG_INTRO,
    EVENT_KEYDOOR,
    EVENT_EXECUTIVE_DEFEAT,
    EVENT_EXECUTIVE_INTRO,
    EVENT_EXECUTIVE_MIDDLE,
    EVENT_QUEEN_INTRO,
    EVENT_SHIP_INTRO,
    EVENT_COSTUME_SELECT_AG,
    EVENT_LVUP,
};

enum revent_spline_list {
    SPLINE_RR,
    SPLINE_CG,
    SPLINE_CCM,
};

extern void event_main(void);
extern void run_event(u8 event_tdo);
extern void end_minigame(void);
extern void minigame_transition_func(void);