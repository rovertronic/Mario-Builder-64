#include "sm64.h"
#include "game/camera.h"
#include "game/level_update.h"
#include "game/print.h"
#include "engine/math_util.h"
#include "game/segment2.h"
#include "game/save_file.h"
#include "puppycamold.h"
#include "include/text_strings.h"
#include "engine/surface_collision.h"

// /**
// +Quick explanation of the camera modes
// +
// +NC_MODE_NORMAL: Standard mode, allows dualaxial movement and free control of the camera.
// +NC_MODE_FIXED: Disables control of camera, and the actual position of the camera doesn't update.
// +NC_MODE_2D: Disables horizontal control of the camera and locks Mario's direction to the X axis. NYI though.
// +NC_MODE_8D: 8 directional movement. Similar to standard, except the camera direction snaps to 8 directions.
// +NC_MODE_FIXED_NOMOVE: Disables control and movement of the camera.
// +NC_MODE_NOTURN: Disables horizontal and vertical control of the camera.
// +**/

// //!A bunch of developer intended options, to cover every base, really.
// //define NEWCAM_DEBUG //Some print values for puppycam. Not useful anymore, but never hurts to keep em around.
// //#define nosound //If for some reason you hate the concept of audio, you can disable it.
// //#define noaccel //Disables smooth movement of the camera with the C buttons.


// //!Hardcoded camera angle stuff. They're essentially area boxes that when Mario is inside, will trigger some view changes.
// ///Don't touch this btw, unless you know what you're doing, this has to be above for religious reasons.
// struct newcam_hardpos
//  {
//     u8 newcam_hard_levelID;
//     u8 newcam_hard_areaID;
//     u8 newcam_hard_permaswap;
//     u16 newcam_hard_modeset;
//     s16 newcam_hard_X1;
//     s16 newcam_hard_Y1;
//     s16 newcam_hard_Z1;
//     s16 newcam_hard_X2;
//     s16 newcam_hard_Y2;
//     s16 newcam_hard_Z2;
//     s16 newcam_hard_camX;
//     s16 newcam_hard_camY;
//     s16 newcam_hard_camZ;
//     s16 newcam_hard_lookX;
//     s16 newcam_hard_lookY;
//     s16 newcam_hard_lookZ;
// };

// ///This is the bit that defines where the angles happen. They're basically environment boxes that dictate camera behaviour.
// //Permaswap is a boolean that simply determines wether or not when the camera changes at this point it stays changed. 0 means it resets when you leave, and 1 means it stays changed.
// //The camera position fields accept "32767" as an ignore flag.
// struct newcam_hardpos newcam_fixedcam[] =
//  {
//  {/*Level ID*/ 16,/*Area ID*/ 1,/*Permaswap*/ 0,/*Mode*/ NC_MODE_FIXED_NOMOVE, //Standard params.
// /*X begin*/ -540,/*Y begin*/ 800,/*Z begin*/ -3500, //Where the activation box begins
// /*X end*/ 540,/*Y end*/ 2000,/*Z end*/ -1500, //Where the activation box ends.
// /*Cam X*/ 0,/*Cam Y*/ 1500,/*Cam Z*/ -1000, //The position the camera gets placed for NC_MODE_FIXED and NC_MODE_FIXED_NOMOVE
// /*Look X*/ 0,/*Look Y*/ 800,/*Look Z*/ -2500}, //The position the camera looks at for NC_MODE_FIXED_NOMOVE
// };

// #ifdef noaccel
//     u8 accel = 255;
//     #else
//     u8 accel = 10;
// #endif // noaccel

// s16 newcam_yaw; //Z axis rotation
// f32 newcam_yaw_acc;
// s16 newcam_tilt = 1500; //Y axis rotation
// f32 newcam_tilt_acc;
// u16 newcam_distance = 750; //The distance the camera stays from the player
// u16 newcam_distance_target = 750; //The distance the player camera tries to reach.
// f32 newcam_pos_target[3]; //The position the camera is basing calculations off. *usually* Mario.
// f32 newcam_pos[3]; //Position the camera is in the world
// f32 newcam_lookat[3]; //Position the camera is looking at
// f32 newcam_framessincec[2];
// f32 newcam_extheight = 125;
// u8 newcam_centering = 0; // The flag that depicts wether the camera's goin gto try centering.
// s16 newcam_yaw_target; // The yaw value the camera tries to set itself to when the centre flag is active. Is set to Mario's face angle.
// f32 newcam_turnwait; // The amount of time to wait after landing before allowing the camera to turn again
// f32 newcam_pan_x;
// f32 newcam_pan_z;
// u8 newcam_cstick_down = 0; //Just a value that triggers true when the player 2 stick is moved in 8 direction move to prevent holding it down.
// u8 newcam_target;
// s32 newcam_sintimer = 0;
// s16 newcam_coldist;
// u8 newcam_xlu = 255;

// s16 newcam_sensitivityX; //How quick the camera works.
// s16 newcam_sensitivityY;
// s16 newcam_invertX; //Reverses movement of the camera axis.
// s16 newcam_invertY;
// s16 newcam_panlevel; //How much the camera sticks out a bit in the direction you're looking.
// s16 newcam_aggression ; //How much the camera tries to centre itself to Mario's facing and movement.
// s16 newcam_degrade ;
// s16 newcam_analogue; //Wether to accept inputs from a player 2 joystick, and then disables C button input.
// s16 newcam_distance_values[] = {750,1250,2000};

// s16 newcam_active = 0; // basically the thing that governs if newcam is on.

// //OTHER OPTIONS
// s16 opt_music = TRUE;
// s16 opt_widescreen = FALSE;
// s16 opt_minimap = TRUE;
// s16 opt_showhud = TRUE;

// u16 newcam_mode;
// u16 newcam_intendedmode = 0; // which camera mode the camera's going to try to be in when not forced into another.
// u16 newcam_modeflags;

// u8 newcam_option_open = 0;
// s8 newcam_option_selection = 0;
// f32 newcam_option_timer = 0;
// u8 newcam_option_index = 0;
// u8 newcam_option_scroll = 0;
// u8 newcam_option_scroll_last = 0;

// #ifndef NC_CODE_NOMENU
// // static u8 newcam_options[][64] = {{NC_ANALOGUE}, {NC_CAMX}, {NC_CAMY}, {NC_INVERTX}, {NC_INVERTY}, {NC_CAMC}, {NC_CAMP}, {NC_CAMD},{TEXT_OPTION_1},{TEXT_OPTION_2},{TEXT_OPTION_3},{TEXT_OPTION_4}}; // unused
// // static u8 newcam_flags[][64] = {{NC_DISABLED}, {NC_ENABLED}}; // unused
// // static u8 newcam_strings[][64] = {{NC_BUTTON}, {NC_BUTTON2}, {NC_OPTION}, {NC_HIGHLIGHT_L}, {NC_HIGHLIGHT_R}}; // unused
// #endif

// #define OPT 32 //Just a temp thing

// // static u8 (*newcam_options_ptr)[OPT][64] = &newcam_options; // unused
// // static u8 (*newcam_flags_ptr)[OPT][64] = &newcam_flags;
// // static u8 (*newcam_strings_ptr)[OPT][64] = &newcam_strings;


// // static struct newcam_optionstruct
// //  {
// //     u8 newcam_op_name; //This is the position in the newcam_options text array. It doesn't have to directly correlate with its position in the struct
// //     s16 *newcam_op_var; //This is the value that the option is going to directly affect.
// //     u8 newcam_op_option_start; //This is where the text array will start. Set it to 255 to have it be ignored.
// //     s32 newcam_op_min; //The minimum value of the option.
// //     s32 newcam_op_max; //The maximum value of the option.
// // };

// // static struct newcam_optionstruct newcam_optionvar[]=
// //  { //If the min and max are 0 and 1, then the value text is used, otherwise it's ignored.
// //     //{/*Option Name*/ 8, /*Option Variable*/ &newcam_active, /*Option Value Text Start*/ 0, /*Option Minimum*/ FALSE, /*Option Maximum*/ TRUE},
// //     {/*Option Name*/ 9, /*Option Variable*/ &opt_music, /*Option Value Text Start*/ 0, /*Option Minimum*/ FALSE, /*Option Maximum*/ TRUE},
// //     {/*Option Name*/ 10, /*Option Variable*/ &opt_widescreen, /*Option Value Text Start*/ 0, /*Option Minimum*/ FALSE, /*Option Maximum*/ TRUE},
// //     {/*Option Name*/ 8, /*Option Variable*/ &opt_minimap, /*Option Value Text Start*/ 0, /*Option Minimum*/ FALSE, /*Option Maximum*/ TRUE},
// //     {/*Option Name*/ 11, /*Option Variable*/ &opt_showhud, /*Option Value Text Start*/ 0, /*Option Minimum*/ FALSE, /*Option Maximum*/ TRUE},
    
// //     //{/*Option Name*/ 0, /*Option Variable*/ &newcam_analogue, /*Option Value Text Start*/ 0, /*Option Minimum*/ FALSE, /*Option Maximum*/ TRUE},
// //     //{/*Option Name*/ 1, /*Option Variable*/ &newcam_sensitivityX, /*Option Value Text Start*/ 255, /*Option Minimum*/ 10, /*Option Maximum*/ 500},
// //     //{/*Option Name*/ 2, /*Option Variable*/ &newcam_sensitivityY, /*Option Value Text Start*/ 255, /*Option Minimum*/ 10, /*Option Maximum*/ 500},
// //     //{/*Option Name*/ 3, /*Option Variable*/ &newcam_invertX, /*Option Value Text Start*/ 0, /*Option Minimum*/ FALSE, /*Option Maximum*/ TRUE},
// //     //{/*Option Name*/ 4, /*Option Variable*/ &newcam_invertY, /*Option Value Text Start*/ 0, /*Option Minimum*/ FALSE, /*Option Maximum*/ TRUE},
// //     //{/*Option Name*/ 7, /*Option Variable*/ &newcam_degrade, /*Option Value Text Start*/ 255, /*Option Minimum*/ 5, /*Option Maximum*/ 100},
// //     //{/*Option Name*/ 5, /*Option Variable*/ &newcam_aggression, /*Option Value Text Start*/ 255, /*Option Minimum*/ 0, /*Option Maximum*/ 100},
// //     //{/*Option Name*/ 6, /*Option Variable*/ &newcam_panlevel, /*Option Value Text Start*/ 255, /*Option Minimum*/ 0, /*Option Maximum*/ 100},
// // };

// //You no longer need to edit this anymore lol
// // u8 newcam_total = sizeof(newcam_optionvar) / sizeof(struct newcam_optionstruct); //How many options there are in newcam_uptions.

// #if defined(VERSION_EU)
// static void newcam_set_language(void)
//  {
//     switch (eu_get_language())
//     {
//     case 0:
//         newcam_options_ptr = &newcam_options;
//         newcam_flags_ptr = &newcam_flags;
//         newcam_strings_ptr = &newcam_strings;
//         break;
//     case 1:
//         newcam_options_ptr = &newcam_options_fr;
//         newcam_flags_ptr = &newcam_flags_fr;
//         newcam_strings_ptr = &newcam_strings_fr;
//         break;
//     case 2:
//         newcam_options_ptr = &newcam_options_de;
//         newcam_flags_ptr = &newcam_flags_de;
//         newcam_strings_ptr = &newcam_strings_de;
//         break;
//     }
// }
// #endif

// ///This is called at every level initialisation.
// void newcam_init(struct Camera *c, u8 dv)
//  {
//     #if defined(VERSION_EU)
//     newcam_set_language();
//     #endif
//     newcam_tilt = 1500;
//     newcam_distance_target = newcam_distance_values[dv];
//     newcam_yaw = -c->yaw+0x4000; //Mario and the camera's yaw have this offset between them.
//     newcam_mode = NC_MODE_NORMAL;
//     ///This here will dictate what modes the camera will start in at the beginning of a level. Below are some examples.
//     switch (gCurrLevelNum)
//     {
//         case LEVEL_WF: newcam_yaw = 0x4000; newcam_tilt = 2000; newcam_distance_target = newcam_distance_values[1]; if (gCurrAreaIndex == 2) newcam_mode = NC_MODE_SLIDE; break;
//     }

//     newcam_distance = newcam_distance_target;
//     newcam_intendedmode = newcam_mode;
//     newcam_modeflags = newcam_mode;
// }

// // static s16 newcam_clamp(s16 value, s16 max, s16 min) // unused
// //  {
// //     if (value > max)
// //         return max;
// //     if (value < min)
// //         return min;
// //     else
// //         return value;
// // }

// ///These are the default settings for Puppycam. You may change them to change how they'll be set for first timers.
// void newcam_init_settings()
//  {

// }

// /** Mathematic calculations. This stuffs so basic even *I* understand it lol
// +Basically, it just returns a position based on angle */
// // static s16 lengthdir_x(f32 length, s16 dir) // unused
// //  {
// //     return (s16) (length * coss(dir));
// // }
// // static s16 lengthdir_y(f32 length, s16 dir) // unused
// //  {
// //     return (s16) (length * sins(dir));
// // }

// void newcam_diagnostics(void)
//  {

// }

// // static s16 newcam_adjust_value(s16 var, s16 val, s8 max) // unused
// //  {
// //     if (val > 0)
// //     {
// //         var += val;
// //         if (var > max)
// //             var = max;
// //     }
// //     else
// //     if (val < 0)
// //     {
// //         var += val;
// //         if (var < max)
// //             var = max;
// //     }

// //     return var;
// // }

// // static f32 newcam_approach_float(f32 var, f32 val, f32 inc) // unused
// //  {
// //     if (var < val)
// //         return min(var + inc, val);
// //         else
// //         return max(var - inc, val);
// // }

// // static s16 newcam_approach_s16(s16 var, s16 val, s16 inc) // unused
// //  {
// //     if (var < val)
// //         return max(var + inc, val);
// //         else
// //         return min(var - inc, val);
// // }

// // static f32 ivrt(u8 axis) // unused
// //  {
// //     if (axis == 0)
// //         return 1;
// //     else
// //         return -1;
// // }

// // static void newcam_rotate_button(void) // unused
// //  {

// // }

// // static void newcam_zoom_button(void) // unused
// //  {

// // }

// // static void newcam_update_values(void) // unused
// //  {//For tilt, this just limits it so it doesn't go further than 90 degrees either way. 90 degrees is actually 16384, but can sometimes lead to issues, so I just leave it shy of 90.

// // }
// //
// // static void newcam_collision(void) // unused
// //  {

// // }

// // static void newcam_set_pan(void) // unused
// //  {

// // }

// // static void newcam_position_cam(void) // unused
// //  {


// // }

// //Nested if's baybeeeee
// // static void newcam_find_fixed(void) // unused
// //  {

// // }

// // static void newcam_apply_values(struct Camera *c) // unused
// //  {

// // }

// //If puppycam gets too close to its target, start fading it out so you don't see the inside of it.
// void newcam_fade_target_closeup(void)
// {

// }

// //The ingame cutscene system is such a spaghetti mess I actually have to resort to something as stupid as this to cover every base.
// void newcam_apply_outside_values(UNUSED struct Camera *c, UNUSED u8 bit)
//  {

// }

// //Main loop.
// void newcam_loop(UNUSED struct Camera *c)
//  {

// }


// #ifndef NC_CODE_NOMENU
// //Displays a box.
// void newcam_display_box(UNUSED s16 x1, UNUSED s16 y1, UNUSED s16 x2, UNUSED s16 y2, UNUSED u8 r, UNUSED u8 g, UNUSED u8 b)
//  {

// }

// //I actually took the time to redo this, properly. Lmao. Please don't bully me over this anymore :(
// void newcam_change_setting(UNUSED s8 toggle)
//  {

// }

// void newcam_text(UNUSED s16 x, UNUSED s16 y, UNUSED u8 str[], UNUSED u8 col)
//  {

// }

// //Options menu
// void newcam_display_options()
//  {

// }

// //This has been separated for interesting reasons. Don't question it.
// void newcam_render_option_text(void)
//  {

// }

// void newcam_check_pause_buttons()
//  {

// }
// #endif