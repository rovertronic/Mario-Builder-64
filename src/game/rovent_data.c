#include "sm64.h"
#include "area.h"
#include "audio/data.h"
#include "audio/external.h"
#include "behavior_actions.h"
#include "behavior_data.h"
#include "camera.h"
#include "engine/graph_node.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "game_init.h"
#include "interaction.h"
#include "level_table.h"
#include "level_update.h"
#include "main.h"
#include "mario.h"
#include "mario_actions_airborne.h"
#include "mario_actions_automatic.h"
#include "mario_actions_cutscene.h"
#include "mario_actions_moving.h"
#include "mario_actions_object.h"
#include "mario_actions_stationary.h"
#include "mario_actions_submerged.h"
#include "mario_misc.h"
#include "mario_step.h"
#include "memory.h"
#include "object_fields.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "print.h"
#include "save_file.h"
#include "sound_init.h"
#include "rovent.h"
#include "dialog_ids.h"
#include "seq_ids.h"

// s32 event_test[] = {

//     E_HUD_TOGGLE,
//     E_DIALOG, 0,
//     E_WAIT, 140,
//     E_DIALOG, 1,
//     E_WAIT, 150,
//     E_DIALOG, 2,
//     E_ACT, ACT_BACKFLIP,
//     E_WAIT, 200,


//     E_END,
// };

// s32 event_thwomp_towers_gate[] = {
//     E_ACT, ACT_IDLE,
//     E_WAIT, 30,

//     E_CAM_TOGGLE,
//     E_HUD_TOGGLE,

//     E_TARGET_MARIO,
//     E_CAM_CLOSE_UP,
//     E_CAM_FOCUS_TARGET,
//     E_WAIT, 40,

//     E_TARGET_OBJECT, bhvThwompgate,
//     E_DIALOG, 81,
//     E_PUZZLE_JINGLE,
//     E_CAM_MASTER_SHOT, 3000, 0x6000,
//     E_CAM_FOCUS_TARGET,
//     E_WAIT, 100,

//     E_SAVEGAME,

//     E_END,
// };

// s32 event_virtuaplex_gate[] = {
//     E_ACT, ACT_IDLE,
//     E_WAIT, 30,

//     E_CAM_TOGGLE,
//     E_HUD_TOGGLE,

//     E_TARGET_OBJECT, bhvBoneGate,
//     E_DIALOG, 81,
//     E_PUZZLE_JINGLE,
//     E_CAM_MASTER_SHOT, 3000, 0x0000,
//     E_CAM_FOCUS_TARGET,
//     E_ROOM, 5,
//     E_WAIT, 100,

//     E_ROOM, 2,
//     E_HUD_TOGGLE,
//     E_CAM_TOGGLE,
//     E_WAIT, 5,

//     E_END,
// };

// s32 event_pode_intro[] = {
//     E_HUD_TOGGLE,

//     //make mario walk away from center
//     E_TARGET_OBJECT, bhvPodeHead,
//     E_DIALOG, 82,
//     E_WALK_FROM_TARGET, 1700,
//     E_WAIT, 10,

//     //do a shot of the pokey erupting from the ground
//     E_CAM_TOGGLE,
//     E_QUEUE, 1,//queue 1 will free the worm
//     E_DIALOG, 83,
//     E_CAM_FOCUS_TARGET,
//     E_CAM_MANUAL_ECM, ECM_TRACK_TARGET, //make sure the camera is looking at the pokey going up
//     E_CAM_MASTER_SHOT, 5000, 0x0000,
//     E_WAIT, 100,
//     E_CLOSE_DIALOG,//close dialog a bit early
//     E_WAIT, 20,

//     //show the mine as a hint, and also close dialog
//     E_QUEUE, 2,//queue 2 will reveal the mines, and freeze the worm until done
//     E_TARGET_OBJECT, bhvBigmine,
//     E_CAM_FOCUS_TARGET,
//     E_CAM_ORBIT, 1200, 500, 100,
//     E_WAIT, 90,
//     E_END,
// };

// s32 event_wallet[] = {
//     E_MARIO_LOCK,
//     E_ZOUND, SOUND_MARIO_HERE_WE_GO,
//     E_PUZZLE_JINGLE,
//     E_DIALOG, 84,
//     E_DIALOG_WAIT_PRESSA,
//     E_SAVEGAME,
//     E_END,
// };

// s32 event_costume[] = {
//     E_MARIO_LOCK,

//     E_PUZZLE_JINGLE,
//     E_WAIT, 35,
//     //look at mario

//     E_MARIO_VEL, 0,
//     E_MARIO_UNLOCK,
//     E_CAM_TOGGLE,
//     E_TARGET_MARIO,
//     E_CAM_FOCUS_TARGET,
//     E_CAM_CLOSE_UP,
//     //
//     E_WAIT, 30,
//     E_PUT_ON_COSTUME,
//     E_ZOUND, SOUND_MARIO_HERE_WE_GO,
//     E_WAIT, 60,
//     E_CAM_TOGGLE,

//     E_DIALOG, 85,
//     E_DIALOG_YESNO,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG_CHOICE_JUMP,1,5,
//     E_ZOUND, SOUND_MARIO_HAHA,
//     E_SAVEGAME,
//     E_END,
//     //No
//     E_PUT_ON_COSTUME,
//     E_ZOUND, SOUND_MARIO_MAMA_MIA,
//     E_SAVEGAME,
//     E_END,
// };

// s32 event_stardoor[] = {
//     E_ZOUND, SOUND_OBJ_BOWSER_LAUGH,
//     E_DIALOG, 22,
//     E_DIALOG_WAIT_PRESSA,
//     E_ZOUND, SOUND_MARIO_MAMA_MIA,
//     E_END,
// };

// s32 event_metalstardoor[] = {
//     E_ZOUND, SOUND_OBJ_BOWSER_LAUGH,
//     E_DIALOG, 25,
//     E_DIALOG_WAIT_PRESSA,
//     E_ZOUND, SOUND_MARIO_MAMA_MIA,
//     E_END,
// };

// s32 event_virtuaplex_door[] = {
//     E_ZOUND, SOUND_OBJ_BOWSER_LAUGH,
//     E_DIALOG, DIALOG_028,
//     E_DIALOG_WAIT_PRESSA,
//     E_ZOUND, SOUND_MARIO_MAMA_MIA,
//     E_END,
// };

// s32 event_minigame[] = {
//     E_MARIO_VEL, 0,
//     E_WAIT, 30,
//     E_HUD_TOGGLE,
//     E_CAM_TOGGLE,
//     E_TARGET_OBJECT, bhvMGB,
//     E_CAM_FOCUS_TARGET,
//     E_CAM_ORBIT, 400, 250, 50,
//     E_DIALOG, 20,
//     E_MINIGAME_MENU,
//     E_DIALOG, 21,
//     E_DIALOG_YESNO,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG_CHOICE_JUMP,1,-9,
//     E_DIALOG, 23,
//     E_PUZZLE_JINGLE,
//     E_DIALOG_WAIT_PRESSA,
//     E_MINIGAME_UNLOCK, 1,
//     E_DIALOG_CHOICE_JUMP,0,-18,
//     E_END,
// };

// s32 event_minigame_hi[] = {
//     E_DIALOG, 24,
//     E_DIALOG_WAIT_PRESSA,
//     E_END,
// };

// s32 event_switch_1[] = {
//     E_WAIT, 30,

//     E_DIALOG, 86,
//     E_CAM_TOGGLE,
//     E_TARGET_MARIO,
//     E_CAM_FOCUS_TARGET,
//     E_CAM_ORBIT, 400, 250, 50,

//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG_AND_PRESSA, DIALOG_SWITCH_1,
//     E_SAVEGAME,
//     E_END,
// };

// s32 event_switch_2[] = {
//     E_WAIT, 30,

//     E_DIALOG, 87,
//     E_CAM_TOGGLE,
//     E_TARGET_MARIO,
//     E_CAM_FOCUS_TARGET,
//     E_CAM_ORBIT, 400, 250, 50,

//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG_AND_PRESSA, DIALOG_SWITCH_2,
//     E_SAVEGAME,
//     E_END,
// };

// s32 event_switch_3[] = {
//     E_WAIT, 30,

//     E_DIALOG, 88,
//     E_CAM_TOGGLE,
//     E_TARGET_MARIO,
//     E_CAM_FOCUS_TARGET,
//     E_CAM_ORBIT, 400, 250, 50,

//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG_AND_PRESSA, DIALOG_SWITCH_3,
//     E_SAVEGAME,
//     E_END,
// };

// s32 event_switch_4[] = {
//     E_WAIT, 30,

//     E_DIALOG, 89,
//     E_CAM_TOGGLE,
//     E_TARGET_MARIO,
//     E_CAM_FOCUS_TARGET,
//     E_CAM_ORBIT, 400, 250, 50,

//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG_AND_PRESSA, DIALOG_SWITCH_4,
//     E_SAVEGAME,
//     E_END,
// };

// s32 event_letter[] = {
//     //E_END,

//     E_HUD_TOGGLE,
//     E_CAM_TOGGLE,

//     E_CAM_SPLINE, SPLINE_CG, 348,
//     E_WAIT, 370,
//     E_DIALOG_AND_PRESSA, DIALOG_POEM_1,
//     E_DIALOG_AND_PRESSA, DIALOG_POEM_2,
//     E_CLOSE_DIALOG,
//     E_WAIT, 45,

//     E_CAM_MANUAL_ECM, ECM_STATIC,

//     E_TARGET_MARIO,
//     E_CAM_FOCUS_TARGET,
//     E_CAM_MASTER_SHOT, 700, 0x8000,
//     E_MARIO_YAW, 0x8000,
//     E_HEAD_TOGGLE,
//     E_HEAD_ANGLE, -0x1000, 0, 0x600,

//     E_WAIT, 30,
//     E_MARIO_HANDSTATE, 6,
//     E_ZOUND, SOUND_ACTION_BRUSH_HAIR,
//     E_WAIT, 15,

//     E_DIALOG, 91,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, 95,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, 92,
//     E_DIALOG_WAIT_PRESSA,
//     E_CLOSE_DIALOG,

//     E_WAIT, 15,
//     E_MARIO_HANDSTATE, 0,
//     E_ZOUND, SOUND_ACTION_BRUSH_HAIR,
//     E_WAIT, 30,

//     E_START_PRECREDITS,

//     E_END,
// };

// s32 event_showrunner_1[] = {
//     E_TARGET_OBJECT, bhvDoor,
//     E_WALK_TO_TARGET, 60,

//     //mario at door
//     //SHOT: Mario enter office and go ontop of trapdoor
//     E_HUD_TOGGLE,
//     E_CAM_TOGGLE,
//     E_CAM_POS_XYZ, 10500, 2270, -7135,
//     E_CAM_MANUAL_ECM, ECM_TRACK_MARIO,

//     E_TARGET_OBJECT, bhvStaticObject,
//     E_WALK_TO_TARGET, 100,
//     E_WAIT, 30,

//     //mario is on top of trapdoor
//     //SHOT: disuccion with showrunner
//     E_HEAD_TOGGLE,
//     E_HEAD_ANGLE, 0, 0, -0x2000,
//     E_CAM_POS_XYZ, 9312, 629, -4575,
//     E_TARGET_OBJECT, bhvShowrunner,
//     E_CAM_FOCUS_TARGET,
//     E_TARGET_OBJECT_SPOTLIGHT, 500,

//     E_MUSIC, SEQ_SHOWRUNNER,

//     E_WAIT, 30,
//     //showrunner begin talking
//     E_DIALOG, 96,
//     E_DIALOG_WAIT_PRESSA,
//     E_CAM_MASTER_SHOT, 2800, 0x2000,
//     E_DIALOG, 97,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, 98,
//     E_DIALOG_WAIT_PRESSA,
//     E_CAM_MASTER_SHOT, 2800, -0x2000,
//     E_DIALOG, 99,
//     E_DIALOG_WAIT_PRESSA,
//     //Show off mario woohoo
//     E_ZOUND, SOUND_CUSTOM_PEACH_SOMETHING_SPECIAL,
//     E_CLOSE_DIALOG,
//     E_CAM_POS_XYZ, 9312, 629, -4575,

//     E_WAIT, 60,

//     //return to showrunner
//     E_CAM_FOCUS_TARGET,
//     E_CAM_MASTER_SHOT, 2800, -0x2000,

//     E_DIALOG, 100,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, 101,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, 102,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, 103,
//     E_DIALOG_WAIT_PRESSA,
//     E_ZOUND, SOUND_CUSTOM_PEACH_SOMETHING_SPECIAL,
//     E_DIALOG, 104,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, 105,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, 106,
//     E_DIALOG_WAIT_PRESSA,

//     //SHOT: Mario presses a and fucking dies
//     E_TARGET_MARIO,
//     E_TARGET_OBJECT_SPOTLIGHT, 100,
//     E_CAM_POS_XYZ, 10500, 2270, -7135,
//     E_CAM_MANUAL_ECM, ECM_TRACK_MARIO,
//     E_HEAD_TOGGLE,

//     E_DIALOG, 108,
//     E_DIALOG_WAIT_PRESSA,
//     E_CLOSE_DIALOG,
//     E_ACT, ACT_TRIPLE_JUMP,
//     E_WAIT, 5,
//     E_TARGET_OBJECT, bhvTTrap,
//     E_TARGET_OBJECT_ACTION, 2,

//     E_WAIT, 200,

//     E_END,
// };

// s32 event_toadmeet[] = {
//     E_CAM_TOGGLE,
//     E_TARGET_OBJECT, bhvGhoad,
//     E_CAM_MASTER_SHOT, 800 ,0x2000,
//     E_CAM_MANUAL_ECM, ECM_TRACK_MARIO,
//     E_WAIT, 60,
//     E_WALK_TO_TARGET, 300,
//     E_HEAD_TOGGLE,
//     E_HEAD_ANGLE,0,0,0,
//     E_CAM_FOCUS_TARGET,
//     E_DIALOG, 168,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, 167,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, 166,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, 165,
//     E_DIALOG_WAIT_PRESSA,
//     //E_DIALOG, 164,
//     //E_DIALOG_WAIT_PRESSA,
//     //E_DIALOG, 163,
//     //E_DIALOG_WAIT_UPGRADE,
//     //E_DIALOG, 162,
//     //E_DIALOG_WAIT_PRESSA,
//     E_END,
// };

// s32 event_costume_select[] = {
//     E_MARIO_VEL, 0,
//     E_WAIT, 30,
//     E_HUD_TOGGLE,
//     E_CAM_TOGGLE,
//     E_TARGET_OBJECT, bhvMGB,
//     E_CAM_FOCUS_TARGET,
//     E_CAM_MASTER_SHOT, 600, 0x4000,
//     E_DIALOG, 26,
//     E_COSTUME_MENU,
//     E_SAVEGAME,
//     E_END,
// };

// s32 event_costume_select_ag[] = {
//     E_MARIO_VEL, 0,
//     E_WAIT, 30,
//     E_HUD_TOGGLE,
//     E_CAM_TOGGLE,
//     E_TARGET_OBJECT, bhvMGBA,
//     E_CAM_FOCUS_TARGET,
//     E_CAM_MASTER_SHOT, 600, 0x4000,
//     E_DIALOG, 26,
//     E_COSTUME_MENU,
//     E_SAVEGAME,
//     E_END,
// };

// s32 event_music_select[] = {
//     E_MARIO_VEL, 0,
//     E_WAIT, 30,
//     E_HUD_TOGGLE,
//     E_CAM_TOGGLE,
//     E_TARGET_OBJECT, bhvMGB,
//     E_CAM_MASTER_SHOT, 400, -0x2000,
//     E_TARGET_OBJECT, bhvPhonograph,
//     E_CAM_FOCUS_TARGET,
//     E_DIALOG, 27,
//     E_MUSIC_MENU,
//     E_END,
// };

// s32 event_bowser_defeat[] = {
//     E_WAIT, 10,
//     E_MARIO_LOCK,
//     E_WAIT, 40,
//     E_CAM_TOGGLE,
//     E_HUD_TOGGLE,
//     E_TARGET_OBJECT, bhvBowser,
//     E_CAM_FOCUS_TARGET,
//     E_CAM_ORBIT, 6000, 6000, 0x80,
//     E_CAM_MANUAL_ECM, ECM_ORBIT_TRACK,
//     E_ZOUND, SOUND_OBJ2_BOWSER_ROAR,
//     E_DIALOG, DIALOG_BOWSER1,
//     E_DIALOG_WAIT_PRESSA,
//     E_ZOUND, SOUND_OBJ2_BOWSER_ROAR,
//     E_DIALOG, DIALOG_BOWSER2,
//     E_DIALOG_WAIT_PRESSA,
//     E_ZOUND, SOUND_OBJ2_BOWSER_ROAR,
//     E_DIALOG, DIALOG_BOWSER3,
//     E_DIALOG_WAIT_PRESSA,
//     E_ZOUND, SOUND_OBJ2_BOWSER_ROAR,
//     E_DIALOG, DIALOG_BOWSER4,
//     E_DIALOG_WAIT_PRESSA,
//     E_ZOUND, SOUND_OBJ2_BOWSER_ROAR,
//     E_DIALOG, DIALOG_BOWSER5,
//     E_DIALOG_WAIT_PRESSA,
//     E_ZOUND, SOUND_OBJ2_BOWSER_ROAR,
//     E_DIALOG, DIALOG_BOWSER6,
//     E_DIALOG_WAIT_PRESSA,
//     E_ZOUND, SOUND_OBJ2_BOWSER_ROAR,
//     E_DIALOG, DIALOG_BOWSER7,
//     E_DIALOG_WAIT_PRESSA,
//     E_ZOUND, SOUND_OBJ2_BOWSER_ROAR,
//     E_DIALOG, DIALOG_BOWSER8,
//     E_DIALOG_WAIT_PRESSA,
//     E_ZOUND, SOUND_OBJ2_BOWSER_ROAR,
//     E_DIALOG, DIALOG_BOWSER9,
//     E_DIALOG_WAIT_PRESSA,
//     E_ZOUND, SOUND_OBJ2_BOWSER_ROAR,
//     E_DIALOG, DIALOG_BOWSER10,
//     E_DIALOG_WAIT_PRESSA,
//     E_ZOUND, SOUND_OBJ2_BOWSER_ROAR,
//     E_DIALOG, DIALOG_BOWSER11,
//     E_DIALOG_WAIT_PRESSA,
//     E_CLOSE_DIALOG,
//     E_STOP_MUSIC, SEQ_COSMIC_SEED_BOSS,
//     E_ZOUND, SOUND_OBJ_BOWSER_DEFEATED,
//     E_TARGET_OBJECT_ACTION, 3,
//     E_WAIT, 60,
//     E_TARGET_MARIO,
//     E_MUSIC, SEQ_SHOWRUNNER,
//     E_TARGET_OBJECT_SPAWN, MODEL_SHOWRUNNER, bhvShowrunner, 1,
//     E_WAIT, 1,
//     E_MARIO_YAW, 0,
//     E_CAM_MASTER_SHOT, 2000, 0xB000,
//     E_TARGET_OBJECT, bhvShowrunner,
//     E_CAM_MANUAL_ECM, ECM_TRACK_TARGET,
//     E_WAIT, 80,
//     E_DIALOG, DIALOG_BOWSER12,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_BOWSER13,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_BOWSER14,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_BOWSER15,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_BOWSER16,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_BOWSER17,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_BOWSER18,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_BOWSER19,
//     E_DIALOG_WAIT_PRESSA,
//     E_TARGET_OBJECT_ACTION, 2,
//     E_END,
// };

// s32 event_bowser_intro[] = {
//     E_CAM_TOGGLE,
//     E_HUD_TOGGLE,
//     //shot: kinda front of truck
//     E_TARGET_OBJECT, bhvTruck,
//     E_CAM_MASTER_SHOT, 9000, 0x800,
//     E_CAM_MANUAL_ECM, ECM_TRACK_MARIO,
//     E_WAIT, 120,
//     //shot: truck careens off a cliff
//     E_CAM_POS_XYZ, 2306, 1399, -2507,
//     E_CAM_MANUAL_ECM, ECM_TRACK_MARIO,
//     E_WAIT, 150,
//     //shot: bowser turns EEVVIOOLLL
//     E_TARGET_OBJECT, bhvBowser,
//     E_CAM_FOCUS_TARGET,
//     E_CAM_MASTER_SHOT, 5000, 0x0,
//     E_TARGET_OBJECT_ACTION, 5,
//     E_WAIT, 70,
//     E_DIALOG, DIALOG_BOWSER_INTRO_1,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_BOWSER_INTRO_2,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_BOWSER_INTRO_3,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_BOWSER_INTRO_4,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_BOWSER_INTRO_5,
//     E_DIALOG_WAIT_PRESSA,
//     E_WAIT, 20,
//     E_MUSIC, SEQ_COSMIC_SEED_BOSS,
//     E_END,
// };

// s32 event_bowser_post[] = {
//     E_HUD_TOGGLE,
//     E_CAM_TOGGLE,
//     E_TARGET_OBJECT, bhvBowser,
//     E_CAM_MASTER_SHOT, 2000, 0x0,
//     E_CAM_MANUAL_ECM, ECM_TRACK_TARGET,
//     E_WAIT, 70,
//     E_CAM_POS_XYZ, -622, 532, 11803,
//     E_WAIT, 20,
//     E_TARGET_OBJECT_ACTION, 3,
//     E_WAIT, 40,

//     E_DIALOG, DIALOG_BOWSER_POST_1,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_BOWSER_POST_2,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_BOWSER_POST_3,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_BOWSER_POST_4,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_BOWSER_POST_5,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_BOWSER_POST_6,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_BOWSER_POST_7,
//     E_DIALOG_WAIT_PRESSA,

//     //GIVE LENS!
//     E_CLOSE_DIALOG,

//     E_WAIT, 20,

//     E_TARGET_MARIO,
//     E_TARGET_OBJECT_SPAWN, MODEL_LENS, bhvCelebrationStar, 0,

//     E_TARGET_OBJECT, bhvBowser,
    
//     E_PUZZLE_JINGLE,
//     E_WAIT, 70,

//     E_DIALOG, DIALOG_BOWSER_POST_8,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_BOWSER_POST_9,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_BOWSER_POST_10,
//     E_DIALOG_WAIT_PRESSA,
//     E_TARGET_OBJECT_ACTION, 4,
//     E_END,
// };

// s32 event_quiz[] = {
//     E_TARGET_OBJECT, bhvCurtain,
//     E_TARGET_OBJECT_ACTION, 1,
//     E_WAIT, 60,
//     E_HUD_TOGGLE,
//     E_CAM_TOGGLE,
//     E_HEAD_TOGGLE,

//     E_MUSIC, SEQ_SHOWRUNNER,
//     E_QUIZ_HOST,
//     //camera at mario
//     E_CAM_MANUAL_ECM, ECM_TRACK_MARIO,

//     E_DIALOG, DIALOG_QUIZ_1,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_QUIZ_2,
//     E_DIALOG_WAIT_PRESSA,
//     //camera at showrunner

//     E_TARGET_OBJECT, bhvShowrunner,
//     E_TARGET_OBJECT_SPOTLIGHT, 500,

//     E_CAM_MANUAL_ECM, ECM_STATIC,
//     E_QUIZ_HOST,

//     E_MARIO_TELEPORT, 0, 347, -1987,
//     E_MARIO_YAW, 0x0,

//     E_DIALOG, DIALOG_QUIZ_3,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_QUIZ_4,
//     E_DIALOG_WAIT_PRESSA,
//     //introductions
//     E_QUIZ_SCORES,
//     E_DIALOG, DIALOG_QUIZ_5,
//     E_DIALOG_WAIT_PRESSA,
//     //whomp
//     E_ZOUND, SOUND_CUSTOM_PEACH_SOMETHING_SPECIAL,
//     E_QUIZ_CONTESTANT, 2,
//     E_DIALOG, DIALOG_QUIZ_6,
//     E_DIALOG_WAIT_END,

//     //host again
//     E_QUIZ_HOST,
//     E_DIALOG, DIALOG_QUIZ_7,
//     E_DIALOG_WAIT_PRESSA,

//     E_ZOUND, SOUND_CUSTOM_PEACH_SOMETHING_SPECIAL,
//     E_QUIZ_CONTESTANT, 1,
//     E_CLOSE_DIALOG,
//     E_WAIT,30,
//     E_ACT, ACT_JUMP,
//     E_WAIT,30,

//     E_QUIZ_HOST,
//     E_DIALOG, DIALOG_QUIZ_8,
//     E_DIALOG_WAIT_PRESSA,

//     //reggie not a clue
//     E_QUIZ_CONTESTANT, 0,
//     E_DIALOG, DIALOG_QUIZ_9,
//     E_DIALOG_WAIT_PRESSA,

//     E_QUIZ_HOST,
//     E_DIALOG, DIALOG_QUIZ_10,
//     E_DIALOG_WAIT_PRESSA,

//     //reggie go crazy
//     E_QUIZ_CONTESTANT, 0,
//     E_DIALOG, DIALOG_QUIZ_11,
//     E_DIALOG_WAIT_END,

//     E_DIALOG, DIALOG_QUIZ_12,
//     E_DIALOG_WAIT_PRESSA,

//     //showrunner
//     E_QUIZ_HOST,
//     E_DIALOG, DIALOG_QUIZ_13,
//     E_DIALOG_WAIT_PRESSA,

//     E_DIALOG, DIALOG_QUIZ_14,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_14_2,

//     E_DIALOG, DIALOG_QUIZ_15,
//     E_DIALOG_WAIT_PRESSA,

//     //whomp
//     E_QUIZ_CONTESTANT, 2,
//     E_ZOUND, SOUND_OBJ2_WHOMP_SOUND_SHORT,
//     E_DIALOG, DIALOG_QUIZ_16,
//     E_DIALOG_WAIT_PRESSA,

//     E_ZOUND, SOUND_GENERAL_CRAZY_BOX_BOING_SLOW,
//     //red dot
//     E_QUIZ_HOST,
//     E_DIALOG, DIALOG_QUIZ_17,
//     E_DIALOG_WAIT_PRESSA,
//     E_DIALOG, DIALOG_QUIZ_18,
//     E_DIALOG_WAIT_PRESSA,

//     E_QUIZ_CONTESTANT, 1,
//     E_DIALOG, DIALOG_QUIZ_19_Q1,
//     E_DIALOG_ABCD,
//     E_DIALOG_WAIT_PRESSA,

//     E_DIALOG_CHOICE_JUMP, 1, 14,

//     E_ZOUND, SOUND_GENERAL_CRAZY_BOX_BOING_SLOW,
//     E_QUIZ_HOST,
//     E_DIALOG, DIALOG_QUIZ_20_B,
//     E_DIALOG_WAIT_PRESSA,
//     E_QUIZ_CONTESTANT, 2,
//     E_DIALOG, DIALOG_QUIZ_21_B,
//     E_DIALOG_WAIT_PRESSA,
//     E_JUMP, 11,

//     //jump location
//     E_PUZZLE_JINGLE,
//     E_QUIZ_HOST,
//     E_DIALOG, DIALOG_QUIZ_20_A,
//     E_DIALOG_WAIT_PRESSA,
//     E_QUIZ_CONTESTANT, 2,
//     E_DIALOG, DIALOG_QUIZ_21_A,
//     E_DIALOG_WAIT_PRESSA,

//     //jump location
//     E_QUIZ_HOST,
//     E_DIALOG, DIALOG_QUIZ_22,
//     E_DIALOG_WAIT_PRESSA,
//     //rant
//     E_QUIZ_CONTESTANT, 0,
//     E_DIALOG, DIALOG_QUIZ_23,
//     E_DIALOG_WAIT_END,
//     E_DIALOG, DIALOG_QUIZ_24,
//     E_DIALOG_WAIT_PRESSA,

//     E_QUIZ_HOST,
//     E_DIALOG, DIALOG_QUIZ_25,
//     E_DIALOG_WAIT_PRESSA,

//     //goodbye reggie
//     E_TARGET_OBJECT, bhvContestant1,
//     E_TARGET_OBJECT_ACTION, 1,
//     E_QUIZ_CONTESTANT, 0,
//     E_DIALOG, DIALOG_QUIZ_26,
//     E_DIALOG_WAIT_END,

//     E_QUIZ_HOST,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_27,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_28,

//     E_QUIZ_CONTESTANT, 2,
//     E_ZOUND, SOUND_OBJ2_WHOMP_SOUND_SHORT,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_29,

//     E_QUIZ_HOST,
//     E_PUZZLE_JINGLE,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_30,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_31,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_32,

//     E_QUIZ_CONTESTANT, 1,
//     E_DIALOG, DIALOG_QUIZ_33,
//     E_DIALOG_ABCD,
//     E_DIALOG_WAIT_PRESSA,

//     E_STOP_MUSIC, SEQ_SHOWRUNNER,

//     E_QUIZ_CONTESTANT, 2,
//     E_ZOUND, SOUND_OBJ2_WHOMP_SOUND_SHORT,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_34,
//     E_ZOUND, SOUND_OBJ2_WHOMP_SOUND_SHORT,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_35,
//     E_ZOUND, SOUND_OBJ2_WHOMP_SOUND_SHORT,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_36,

//     E_QUIZ_HOST,
//     E_MUSIC, SEQ_EVENT_BOSS,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_37,

//     E_QUIZ_CONTESTANT, 2,
//     E_ZOUND, SOUND_OBJ2_WHOMP_SOUND_SHORT,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_38,

//     E_QUIZ_HOST,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_39,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_40,

//     E_TARGET_OBJECT, bhvContestant2,
//     E_TARGET_OBJECT_ACTION, 2,

//     E_END,
// };

// s32 event_quiz_2[] = {
//     E_WAIT, 30,
//     E_CAM_TOGGLE,
//     E_HUD_TOGGLE,
//     E_HEAD_TOGGLE,

//     E_QUIZ_HOST,
//     E_MARIO_TELEPORT, 0, 347, -1987,
//     E_MARIO_YAW, 0x0,
//     E_MARIO_VEL, 0,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_41,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_42,

//     //whomp ramble
//     E_QUIZ_CONTESTANT, 2,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_43,
//     E_ZOUND, SOUND_OBJ2_WHOMP_SOUND_SHORT,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_44,
//     E_ZOUND, SOUND_OBJ2_WHOMP_SOUND_SHORT,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_45,
//     E_ZOUND, SOUND_OBJ2_WHOMP_SOUND_SHORT,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_46,
//     E_ZOUND, SOUND_OBJ2_WHOMP_SOUND_SHORT,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_47,
//     E_ZOUND, SOUND_OBJ2_WHOMP_SOUND_SHORT,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_48,
//     E_ZOUND, SOUND_OBJ2_WHOMP_SOUND_SHORT,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_49,
//     E_ZOUND, SOUND_OBJ2_WHOMP_SOUND_SHORT,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_50,

//     E_TARGET_OBJECT, bhvSmallWhomp,
//     E_TARGET_OBJECT_ACTION, 10,
//     E_CLOSE_DIALOG,
//     E_WAIT, 90,

//     E_QUIZ_HOST,
//     E_MUSIC, SEQ_SHOWRUNNER,
//     E_TARGET_OBJECT, bhvShowrunner,
//     E_TARGET_OBJECT_SPOTLIGHT, 500,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_51,
//     E_STOP_MUSIC, SEQ_SHOWRUNNER,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_52,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_53,

//     E_QUIZ_CONTESTANT, 1,
//     E_DIALOG, DIALOG_QUIZ_54,
//     E_DIALOG_AB,
//     E_DIALOG_WAIT_PRESSA,
//     E_QUIZ_HOST,

//     E_DIALOG_CHOICE_JUMP, 1, 9,

//     //A
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_55_A,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_56_A,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_57_A,
//     E_JUMP, 7,

//     //B
//     E_QUIZ_POINT, 1,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_55_B,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_56_B,
//     //jump

//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_57,
//     E_QUIZ_CONTESTANT, 1,
//     E_DIALOG, DIALOG_QUIZ_57_Q,
//     E_DIALOG_AB,
//     E_DIALOG_WAIT_PRESSA,
//     E_QUIZ_HOST,

//     //a
//     E_DIALOG_CHOICE_JUMP, 1, 7,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_58_A,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_59_A,
//     E_JUMP, 9,

//     //b
//     E_QUIZ_POINT, 1,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_58_B,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_59_B,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_60_B,
//     //jump
//     E_QUIZ_HOST,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_61,
//     E_QUIZ_CONTESTANT, 1,
//     E_DIALOG, DIALOG_QUIZ_61_Q,
//     E_DIALOG_ABC,
//     E_DIALOG_WAIT_PRESSA,
//     E_QUIZ_HOST,

//     E_DIALOG_CHOICE_JUMP, 1, 12,
//     E_DIALOG_CHOICE_JUMP, 2, 17,

//     E_QUIZ_POINT, -1,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_62_A,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_63_A,
//     E_JUMP, 13,

//     E_QUIZ_POINT, 1,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_62_B,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_63_B,
//     E_JUMP, 5,

//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_62_C,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_63_C,
//     //end final question

//     E_STOP_MUSIC, SEQ_SHOWRUNNER,
//     E_QUIZ_POINT_JUMP, 2, 13,

//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_64_A,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_65_A,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_66_A,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_67_A,
//     E_PROGRESS_SET, PROG_QUIZ_COMPLETE_ANGRY,
//     E_JUMP, 17,

//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_64_B,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_65_B,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_66_B,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_67_B,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_68_B,
//     E_DIALOG_AND_PRESSA, DIALOG_QUIZ_69_B,
//     E_PROGRESS_SET, PROG_QUIZ_COMPLETE_HAPPY,
//     E_SAVEFLAG_SET, SAVE_FLAG_HAPPY_SHOWRUNNER,

//     //ENDING
//     E_CLOSE_DIALOG,
//     E_QUIZ_SCORES,
//     E_TARGET_OBJECT, bhvShowrunner,
//     E_TARGET_OBJECT_DELETE,
//     E_TARGET_OBJECT, bhvCurtain2,
//     E_TARGET_OBJECT_ACTION, 1,
//     E_WAIT, 90,
//     E_SAVEGAME,

//     E_END,
// };

// s32 event_statue_rotate[] = {
//     E_MARIO_VEL, 0,
//     E_WAIT, 30,
//     E_PUZZLE_JINGLE,
//     E_CAM_TOGGLE,
//     E_HUD_TOGGLE,
//     E_CAM_POS_XYZ, -9253, 4248, -4964,
//     E_TARGET_OBJECT, bhvSrstatue,
//     E_CAM_FOCUS_TARGET,

//     E_WAIT, 20,
//     E_TARGET_OBJECT_ACTION, 1,

//     E_WAIT, 50,

//     E_END,
// };

// s32 event_showrunner_battle_1[] = {//begin, happy
//     E_HUD_TOGGLE,
//     E_WAIT, 30,
//     E_CAM_TOGGLE,
//     E_CAM_POS_XYZ, -605, 740, 2559,
//     E_CAM_FOCUS_XYZ, 0, 1608, 0,
//     E_WAIT, 30,
//     E_DIALOG_AND_PRESSA, DIALOG_SB_1,
//     E_DIALOG_AND_PRESSA, DIALOG_SB_2,
//     E_DIALOG_AND_PRESSA, DIALOG_SB_3,
//     E_DIALOG_AND_PRESSA, DIALOG_SB_4,
//     E_DIALOG_AND_PRESSA, DIALOG_SB_5,
//     E_DIALOG_AND_PRESSA, DIALOG_SB_6,
//     E_DIALOG_AND_PRESSA, DIALOG_SB_7,
//     E_DIALOG_AND_PRESSA, DIALOG_SB_8,
//     E_DIALOG_AND_PRESSA, DIALOG_SB_9,
//     E_TARGET_OBJECT, bhvShowrunner,
//     E_TARGET_OBJECT_ACTION, 1,

//     E_MUSIC, SEQ_SHOWRUNNER_BOSS,
//     E_END,
// };

// s32 event_showrunner_battle_2[] = {//begin, angry
//     E_HUD_TOGGLE,
//     E_WAIT, 30,
//     E_CAM_TOGGLE,
//     E_CAM_POS_XYZ, -605, 740, 2559,
//     E_CAM_FOCUS_XYZ, 0, 1608, 0,
//     E_WAIT, 30,

//     E_DIALOG_AND_PRESSA, DIALOG_SHOWRUNNER_BAD_1,

//     E_TARGET_OBJECT, bhvShowrunner,
//     E_TARGET_OBJECT_ACTION, 1,

//     E_MUSIC, SEQ_SHOWRUNNER_BOSS,
//     E_END,
// };

// s32 event_showrunner_battle_3[] = {//end, happy
//     E_WAIT, 30,
//     E_HUD_TOGGLE,
//     E_CAM_TOGGLE,
//     E_CAM_POS_XYZ, 2038, 2651, 1362,
//     E_CAM_FOCUS_XYZ, 0, 100, 0,

//     E_STOP_MUSIC, SEQ_SHOWRUNNER_BOSS,

//     E_DIALOG_AND_PRESSA, DIALOG_SB_1B,
//     E_DIALOG_AND_PRESSA, DIALOG_SB_2B,
//     E_DIALOG_AND_PRESSA, DIALOG_SB_3B,
//     E_DIALOG_AND_PRESSA, DIALOG_SB_4B,
//     E_DIALOG_AND_PRESSA, DIALOG_SB_5B,
//     E_DIALOG_AND_PRESSA, DIALOG_SB_6B,
//     E_DIALOG_AND_PRESSA, DIALOG_SB_7B,
//     E_DIALOG_AND_PRESSA, DIALOG_SB_8B,

//     E_TARGET_OBJECT, bhvShowrunner,
//     E_TARGET_OBJECT_ACTION, 14,

//     E_END,
// };

// s32 event_showrunner_battle_4[] = {//end, angry
//     E_WAIT, 30,
//     E_HUD_TOGGLE,
//     E_CAM_TOGGLE,
//     E_CAM_POS_XYZ, 2038, 2651, 1362,
//     E_CAM_FOCUS_XYZ, 0, 100, 0,

//     E_STOP_MUSIC, SEQ_SHOWRUNNER_BOSS,

//     E_DIALOG_AND_PRESSA, DIALOG_SHOWRUNNER_BAD_2,

//     E_TARGET_OBJECT, bhvShowrunner,
//     E_TARGET_OBJECT_ACTION, 14,

//     E_END,
// };

// s32 event_elevator[] = {
//     E_CAM_TOGGLE,
//     E_HUD_TOGGLE,
//     E_MARIO_TELEPORT, 0, -237, 12427,
//     E_MARIO_YAW, 0x8000,
//     E_MARIO_VEL, 0,

//     E_CAM_POS_XYZ, 0, 200, 9000,
//     E_CAM_FOCUS_XYZ, 0, 200, 10000,
//     E_WAIT, 30,
//     E_TARGET_OBJECT, bhvRR_Door,
//     E_TARGET_OBJECT_ACTION, 4,
//     E_ZOUND, SOUND_GENERAL_STAR_DOOR_CLOSE,
//     E_WAIT, 60,
//     E_WARP, 0x07,
// };

// s32 event_credits[] = {
//     //AGHEART BLOWS UP
//     E_ROOM, 1,
//     E_CAM_TOGGLE,
//     E_HUD_TOGGLE,
//     E_TARGET_OBJECT, bhvAgheart,
//     E_TARGET_OBJECT_ACTION, 8,
//     E_CAM_FOCUS_TARGET,
//     E_CAM_ORBIT, 4000, 2000, 100,
//     E_WAIT, 300,
//     E_ZOUND, SOUND_OBJ_EYEROK_EXPLODE,
//     E_TARGET_OBJECT_ACTION, 9,

//     E_TARGET_OBJECT_SPAWN, MODEL_AGBOOM, bhvAgboom, 0,

//     E_WAIT, 290,

//     E_TARGET_OBJECT_ACTION, 10,

//     //AGAMEMNON CRASHES INTO EARTH
//     E_ROOM, 3,
//     E_TARGET_OBJECT, bhvAgmoon,
//     E_TARGET_OBJECT_ACTION, 1,
//     E_CAM_MANUAL_ECM, ECM_STATIC,
//     E_CAM_POS_XYZ, -2481, 14618, 2496,
//     E_CAM_FOCUS_XYZ, 2266, 13311, -2251,
//     E_MUSIC, SEQ_LEVEL_INSIDE_CASTLE,

//     //CREDITS BEGIN
//     E_DIALOG, DIALOG_CREDITS_1,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_2,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_3,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_4,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_5,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_6,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_7,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_8,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_9,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_10,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_11,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_12,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_13,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_14,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_15,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_16,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_17,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_18,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_19,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_20,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_21,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_22,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_22_A,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_23,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_24,
//     E_WAIT, 150,
//     E_DIALOG, DIALOG_CREDITS_25,
//     E_WAIT, 200,
//     E_WARP, 0x01,
// };

// s32 event_agheart_struck[] = {
//     E_ZOUND, SOUND_ACTION_BOUNCE_OFF_OBJECT,
//     E_CAM_TOGGLE,
//     E_TARGET_OBJECT, bhvAgheart,
//     E_CAM_FOCUS_TARGET,
//     E_CAM_ORBIT, 5000, 2000, 100,
//     E_WAIT, 90,

//     E_CAM_MANUAL_ECM, ECM_STATIC,
//     E_CAM_POS_XYZ, 0,1000,6000,
//     E_CAM_FOCUS_XYZ, 0,700,0,
//     E_TARGET_OBJECT_ACTION, 3,
//     E_WAIT, 90,

//     E_TARGET_OBJECT_ACTION, 5, //send portal
//     E_END,
// };

// s32 event_ag_intro[] = {
//     E_HUD_TOGGLE,
//     E_WAIT, 60,
    
//     E_CAM_TOGGLE,
//     E_MUSIC, SEQ_FINAL_BOSS,
//     E_CAM_SPLINE, SPLINE_RR, 238,
//     E_WAIT, 260,
    

//     E_CAM_MANUAL_ECM, ECM_TRACK_MARIO,
//     E_CAM_POS_XYZ, 1465, 729, 9664,

//     E_TARGET_OBJECT, bhvPalamedes,
//     E_WALK_TO_TARGET, 1000,
//     E_WAIT, 20,

//     E_TARGET_OBJECT, bhvRR_Door,
//     E_CAM_FOCUS_TARGET,
//     E_CAM_MASTER_SHOT, 2000, -0x7000,

//     E_WAIT, 10,

//     E_TARGET_OBJECT_ACTION, 4,
//     E_ZOUND, SOUND_GENERAL_STAR_DOOR_CLOSE,

//     E_WAIT, 40,

//     E_CAM_MANUAL_ECM, ECM_STATIC,
//     E_CAM_POS_XYZ, 586, 101, 10159,
//     E_CAM_FOCUS_XYZ, 91, 500, 7941,
//     E_DIALOG_AND_PRESSA, DIALOG_PALAMEDES_1,
    
//     E_TARGET_OBJECT, bhvPalamedes,
//     E_TARGET_OBJECT_ACTION, 2,

//     E_END,
// };

// s32 event_keydoor[] = {
//     E_ZOUND, SOUND_OBJ_BOWSER_LAUGH,
//     E_DIALOG_AND_PRESSA, DIALOG_129,
//     E_ZOUND, SOUND_MARIO_MAMA_MIA,
//     E_END,
// };

// s32 event_executive_defeat[] = {
//     E_TARGET_OBJECT, bhvShowrunner,
//     E_TARGET_OBJECT_ACTION, 2,

//     E_WAIT, 60,

//     E_TARGET_OBJECT, bhvExecutive,
//     E_CAM_TOGGLE,
//     E_HUD_TOGGLE,

//     E_STOP_MUSIC, SEQ_EVENT_BOSS,

//     E_TARGET_OBJECT_ACTION, 2,
//     //E_CAM_FOCUS_TARGET,
//     E_CAM_FOCUS_XYZ,0,3000, 0,
//     E_CAM_ORBIT, 7000, 6000, 150,

//     E_WAIT, 400,

//     E_CAM_MANUAL_ECM, ECM_TRACK_TARGET,
//     E_TARGET_MARIO,
//     E_CAM_MASTER_SHOT, 2000, 0xA000,
//     E_TARGET_OBJECT, bhvShowrunner,
//     E_TARGET_OBJECT_ACTION, 3,

//     E_HEAD_ANGLE, 0, 0, -0x2000,
//     E_HEAD_TOGGLE,

//     E_TEMPO, 2000,
//     E_MUSIC, SEQ_SHOWRUNNER,
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_1_C,
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_2_C,
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_3_C,
//     E_TARGET_OBJECT_ACTION, 4,
    
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_4_C,
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_5_C,
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_6_C,
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_7_C,
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_8_C,
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_9_C,
//     E_STOP_MUSIC, SEQ_SHOWRUNNER,

//     E_TARGET_OBJECT, bhvTVhead,
//     E_TARGET_OBJECT_ACTION, 3,

//     E_END,
// };

// s32 event_executive_intro[] = {
//     E_CAM_TOGGLE,
//     E_HUD_TOGGLE,
    
//     E_CAM_SPLINE, SPLINE_CCM, 148,
//     E_WAIT, 148,

//     E_CAM_TOGGLE,

//     E_WAIT, 160,

//     E_CAM_TOGGLE,
//     E_CAM_MANUAL_ECM, ECM_STATIC,
//     E_CAM_POS_XYZ, 0, -200, 7000,
//     E_CAM_FOCUS_XYZ, 0,4000,0,
//     E_HEAD_TOGGLE,
//     E_HEAD_ANGLE, 0, 0, -0x2100,

//     E_TARGET_OBJECT, bhvExecutive,
//     E_TARGET_OBJECT_ACTION, 6,

//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_1_A,
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_2_A,
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_3_A,
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_4_A,
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_5_A,
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_6_A,
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_7_A,

//     E_CLOSE_DIALOG,
//     E_TARGET_OBJECT_ACTION, 1,

//     E_WAIT, 30,

//     E_MUSIC, SEQ_EVENT_BOSS,

//     E_END,
// };

// s32 event_executive_middle[] = {
//     E_STOP_MUSIC, SEQ_EVENT_BOSS,
//     E_WAIT, 120,
//     E_TEMPO, 4000,
//     E_MUSIC, SEQ_SHOWRUNNER,

//     E_CAM_TOGGLE,
//     E_HUD_TOGGLE,

//     E_TARGET_MARIO,
//     E_CAM_MASTER_SHOT, 2000, 0xA000,
//     E_TARGET_OBJECT, bhvShowrunner,
//     E_CAM_MANUAL_ECM, ECM_TRACK_TARGET,

//     E_WAIT, 30,

//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_1_B,
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_2_B,
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_3_B,
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_4_B,
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_5_B,
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_6_B,
//     E_DIALOG_AND_PRESSA, DIALOG_EXEC_7_B,

//     E_DIALOG, DIALOG_EXEC_8_B,
//     E_STOP_MUSIC, SEQ_SHOWRUNNER,
//     E_WAIT, 30,
//     E_MUSIC, SEQ_EVENT_BOSS,
//     E_TEMPO, 12000,
//     E_DIALOG_WAIT_PRESSA,

//     E_CLOSE_DIALOG,

//     E_WAIT, 40,
//     E_TARGET_OBJECT_ACTION, 2, //Fighting state

//     E_END,
// };

// s32 event_queen_intro[] = {
//     E_CAM_TOGGLE,
//     E_HUD_TOGGLE,
//     E_CAM_MANUAL_ECM, ECM_STATIC,
//     E_CAM_POS_XYZ, 200, 3000, 2500,
//     E_CAM_FOCUS_XYZ, 0, 1500, 0,
//     E_WAIT, 150,
//     E_END,
// };

// s32 event_ship_intro[] = {
//     E_CAM_TOGGLE,
//     E_HUD_TOGGLE,

//     E_TARGET_OBJECT, bhvVoidShip,
//     E_CAM_FOCUS_TARGET,
//     E_CAM_ORBIT, 16000, 10000, 200,
//     E_CAM_MANUAL_ECM, ECM_ORBIT_TRACK,

//     E_WAIT, 100,

//     E_END,
// };

// //ha ha ha. kill them all. undertale genocide.
// //bob omb battlefield with big boo's haunt instruments.
// //bill board is cumming.
// //MORE INFO: https://vxtwitter.com/i/status/1640936903129063426
// s32 event_lvup[] = {
//     E_ACT, ACT_LVUP_DANCE,
//     E_PUZZLE_JINGLE,
//     E_DIALOG_AND_PRESSA, DIALOG_LVUP,
//     E_ZOUND, SOUND_MARIO_HERE_WE_GO,
//     E_ACT, ACT_IDLE,
//     E_END,
// };

s32 event_get_badge[] = {
    E_ACT, ACT_LVUP_DANCE,
    E_PUZZLE_JINGLE,
    E_DIALOG_AND_PRESSA, DIALOG_GET_BADGE,
    E_ZOUND, SOUND_MARIO_HERE_WE_GO,
    E_ACT, ACT_IDLE,
    E_END,
};

//LIST DO NOT RENAME
s32 *event_list[] = {
//     &event_test,
//     &event_thwomp_towers_gate,
//     &event_virtuaplex_gate,
//     &event_pode_intro,
//     &event_wallet,
//     &event_costume,
//     &event_stardoor,
//     &event_metalstardoor,
//     &event_minigame,
//     &event_minigame_hi,
//     &event_switch_1,
//     &event_switch_2,
//     &event_switch_3,
//     &event_switch_4,
//     &event_letter,
//     &event_showrunner_1,
//     &event_toadmeet,
//     &event_costume_select,
//     &event_music_select,
//     &event_bowser_defeat,
//     &event_bowser_intro,
//     &event_bowser_post,
//     &event_virtuaplex_door,
//     &event_quiz,
//     &event_quiz_2,
//     &event_statue_rotate,
//     &event_showrunner_battle_1,
//     &event_showrunner_battle_2,
//     &event_showrunner_battle_3,
//     &event_showrunner_battle_4,
//     &event_elevator,
//     &event_credits,
//     &event_agheart_struck,
//     &event_ag_intro,
//     &event_keydoor,
//     &event_executive_defeat,
//     &event_executive_intro,
//     &event_executive_middle,
//     &event_queen_intro,
//     &event_ship_intro,
//     &event_costume_select_ag,
//     &event_lvup,
       &event_get_badge,
};

// f32 *spline_list[] = {
//     &rr_frames,
//     &cg_frames,
//     &ccm_frames,
// };