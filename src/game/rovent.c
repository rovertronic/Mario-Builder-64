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
#include "rumble_init.h"
#include "segment2.h"
#include "segment7.h"
#include "dialog_ids.h"
#include "course_table.h"
#include "eu_translation.h"
#include "gfx_dimensions.h"
#include "seq_ids.h"
#include "text_strings.h"
#include "types.h"
#include "spawn_object.h"



#include "ingame_menu.h"

#include "rovent.h"
#include "rovent_data.h"
#include "minigame_menu.h"

#include "actors/group0.h"

//Rovert Simple Cutscene / Event System
//Designed to make cutscene creation simple and fast

u8 revent_active;
u8 revent_halt;
u8 revent_camera_on;
u8 revent_text_engine;
s8 revent_room = 0;
u8 revent_hud = TRUE;
u8 revent_camera_mode;
u8 revent_stop_enemies = FALSE;
u8 revent_queue = 0;
u8 revent_mario_lock = FALSE;
u16 revent_tempo = 0;
Vec3f revent_mario_lock_position;
Vec3f revent_mario_lock_velocity;
u8 revent_head_move;
s16 revent_headangle[3];
u8 revent_handstate;

u16 revent_index;
u16 revent_loop_index;
u16 revent_loop_count;
s32 *revent_pointer;

s32 revent_walk_dist;
s32 revent_timer;
struct Object *revent_target_object;

//Camera Variables
Vec3f revent_camera_pos;
Vec3f revent_camera_foc;

f32 revent_cam_orbit_dist;
f32 revent_cam_orbit_height;
s16 revent_cam_orbit_speed;
s16 orbit_yaw;

s32 revent_cam_spline_index;
s32 revent_cam_spline_max;
s32 revent_cam_spline_pointer;

//QUIZ
u8 quiz_display = FALSE;
s16 quiz_scores[] = {
    0,0,0
};
s8 quiz_points = 0;

//Text Engine
u8 rtext_display[400];
u8 rtext_read[400];
u8 *rtext_insert_pointer[3];

u8 rtext_pressa[] = {0x54,DIALOG_CHAR_TERMINATOR};
u8 rtext_yesno[] = {TEXT_YESNO};
u8 rtext_abcd[] = {TEXT_ABCD};
u8 rtext_abc[] = {TEXT_ABC};
u8 rtext_ab[] = {TEXT_AB};

u8 qbuf[] = {0xF4,0xF4,0xF4,DIALOG_CHAR_TERMINATOR};

u8 rtext_read_index = 0;
u8 rtext_dialog_delay = 0;
u8 rtext_done = FALSE;
u8 rtext_choice = 0;
u8 rtext_choice_amount = 0;
u8 rtext_choice_index = 0;
u8 rtext_offset_buffer[4];

f32 rtext_opacity = 0.0f;

s16 revent_music = 0;

f32 rtext_sintimer;
u8 sinresult;

//Minigame Variables
u8 minigame_real = FALSE;
u8 minigame_transition = FALSE;
u8 minigame_newscore = FALSE;

u8 music_text[] = {MUSIC_TEXT};



u8 mg1[] = {MINIGAME1};
u8 mg2[] = {MINIGAME2};
u8 mg3[] = {MINIGAME3};
u8 mg4[] = {MINIGAME4};
u8 mg5[] = {MINIGAME5};
u8 mg6[] = {MINIGAME6};
u8 mg7[] = {MINIGAME7};
u8 mg8[] = {MINIGAME8};
u8 mge[] = {MINIGAMEE};
u8 *mgt_array[] = {&mg1,&mg2,&mg3,&mg4,&mg5,&mg6,&mg7,&mg8,&mge};
u16 mg_prices[] = {
100,
50,
50,
200,
100,
50,
150,
500,
};

u8 mg_minscores[] = {
10,
50,
45,
50,
70,
150,
10,
8,
};
//level | area | id
// u8 mg_warps[] = {
//     LEVEL_CCM, 3, 0x0A,//enemy arena
//     LEVEL_HMC, 2, 0x01,//hot rope jump 
//     LEVEL_SL, 2, 0x0A,//hexagon heat
//     LEVEL_CASTLE_COURTYARD, 1, 0x0A,//snakio
//     LEVEL_CASTLE_COURTYARD, 2, 0x0A,//edward survival
//     LEVEL_CASTLE_COURTYARD, 3, 0x0A,//bad apple
//     LEVEL_CASTLE_COURTYARD, 4, 0x0A,//flappy bird
//     LEVEL_SA, 1, 0x0A,
// };

s8 minigame_index;

u8 buf1[4];
u8 buf2[4];
u8 coinbuf[] = {0xF9,0,0,0,0};//this is kinda hacky BUT IT IS A ROMHACK AFTER ALL : D
u8 starbuf[] = {0xFA,0,0,0,0};


u8 letgo2 = TRUE;
void stop_event(void) {
    revent_index = 0;
    revent_queue = 0;
    revent_text_engine = FALSE;
    rtext_choice = 0;
    revent_hud = TRUE;
    revent_camera_on = FALSE;
    revent_active = FALSE;
    revent_stop_enemies = FALSE;
    revent_mario_lock = FALSE;
    revent_head_move = FALSE;
    revent_handstate = 0;
}

// void end_minigame(void) {
//     minigame_transition = TRUE;
//     save_file_do_save(gCurrSaveFileNum - 1);
//     initiate_warp(LEVEL_CASTLE, 3, 0x09, 0);
//     fade_into_special_warp(0, 0);
// }

// void minigame_transition_func(void) {
//     minigame_transition = FALSE;
//     minigame_real = FALSE;

//     rtext_insert_pointer[0] = mgt_array[minigame_index];
//     int_to_str(save_file_get_hiscore(minigame_index),&buf1);
//     rtext_insert_pointer[1] = buf1;
//     gMarioState->health = 255 + (255*gMarioState->numMaxHP);
//     gMarioState->numBadgePoints = gMarioState->numMaxFP;

//     if (minigame_newscore) {
//         run_event(EVENT_MINIGAME_HI);
//         minigame_newscore = FALSE;
//     }
// }

// void render_minigame_menu(void) {
//     u8 i;

//     if ((gPlayer1Controller->rawStickY > 60)&&(letgo2 == FALSE)) {
//         play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
//         letgo2 = TRUE;
//         minigame_index --;
//         minigame_index = (minigame_index+9)%9;
//     }
//     if ((gPlayer1Controller->rawStickY < -60)&&(letgo2 == FALSE)) {
//         play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
//         letgo2 = TRUE;
//         minigame_index ++;
//         minigame_index = (minigame_index+9)%9;
//     }
//     if ((gPlayer1Controller->rawStickX > -60)&&(gPlayer1Controller->rawStickX < 60)&&(gPlayer1Controller->rawStickY > -60)&&(gPlayer1Controller->rawStickY < 60)) {
//         letgo2 = FALSE;
//     }

//     //render back box
//     create_dl_translation_matrix(MENU_MTX_PUSH, 20, 218, 0);
//     create_dl_scale_matrix(MENU_MTX_NOPUSH, 1.8f, 1.9f, 1.0f);
//     gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
//     gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
//     gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

//     //render selection box
//     create_dl_translation_matrix(MENU_MTX_PUSH, 22, 216-(16*minigame_index), 0);
//     create_dl_scale_matrix(MENU_MTX_NOPUSH, 1.5f, 0.2f, 1.0f);
//     gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, sinresult/2);
//     gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
//     gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

//     //render minigames
//     gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
//     for (i=0;i<9;i++) {
//         if (i==8) {//this is pretty immoral
//             gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
//             print_generic_string(74,199-(i*16), mgt_array[i]);
//             gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
//             print_generic_string(75,200-(i*16), mgt_array[i]);
//         } else {
//             if (save_file_check_minigame(i)) {
//                 //own minigame, display highscore
//                 int_to_str(save_file_get_hiscore(i),&buf1);
//                 int_to_str(mg_minscores[i],&starbuf[1]);

//                 gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
//                 print_generic_string(34,199-(i*16), buf1);
//                 print_generic_string(74,199-(i*16), mgt_array[i]);
//                 print_generic_string(219,199-(i*16), starbuf);
//                 gDPSetEnvColor(gDisplayListHead++, 0, 240, 0, 255);
//                 print_generic_string(35,200-(i*16), buf1);
//                 gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
//                 print_generic_string(75,200-(i*16), mgt_array[i]);
//                 gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
//                 if (((save_file_get_flags()) >> 24+i)&1) {
//                     gDPSetEnvColor(gDisplayListHead++, 50, 50, 255, 255);
//                 }
//                 print_generic_string(220,200-(i*16), starbuf);
//             } else {
//                 int_to_str(mg_prices[i],&coinbuf[1]);

//                 gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
//                 print_generic_string(34,199-(i*16), coinbuf);
//                 print_generic_string(74,199-(i*16), mgt_array[i]);
//                 gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
//                 print_generic_string(35,200-(i*16), coinbuf);
//                 gDPSetEnvColor(gDisplayListHead++, 220, 220, 220, 255);
//                 print_generic_string(75,200-(i*16), mgt_array[i]);
//             }
//         }
//     }
//     gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

//     //control
//     if (gPlayer1Controller->buttonPressed & A_BUTTON) {
//         if (minigame_index == 8) {
//             //exit
//             stop_event();
//         } else {
//             if (save_file_check_minigame(minigame_index)) {
//                 //own minigame so play it
//                 minigame_real = TRUE;
//                 rtext_opacity = 0;
//                 stop_event();
//                 initiate_warp(mg_warps[(minigame_index*3)], mg_warps[(minigame_index*3)+1], mg_warps[(minigame_index*3)+2], 0);
//                 fade_into_special_warp(0, 0);
//             } else {
//                 //if not own minigame, buy it
//                 if ((gMarioState->numGlobalCoins >= mg_prices[minigame_index])&&(gMarioState->gGlobalCoinGain == 0)) {
//                     int_to_str(mg_prices[minigame_index],&buf1);
//                     int_to_str(gMarioState->numGlobalCoins,&buf2);
//                     rtext_insert_pointer[0] = mgt_array[minigame_index];
//                     rtext_insert_pointer[1] = &buf1;
//                     rtext_insert_pointer[2] = &buf2;
//                     revent_index ++;
//                     revent_halt = FALSE; 
//                 } else {
//                     //can not afford
//                     play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
//                 }
//             }
//         }
//     }
// }

u8 txt_thorndust[] = {TEXT_THORNDUST};
u8 txt_jaguar[] = {TEXT_JAGUAR};
u8 txt_spk[] = {TEXT_SPK};
u8 txt_nomico[] = {TEXT_NOMICO};

extern u8 seq_musicmenu_array[];

u8 *musicmenu_authors[] = {
    &txt_spk,     // SEQ_LEVEL_INSIDE_CASTLE
    &txt_thorndust, // SEQ_SHOWRUNNER
    &txt_thorndust, // SEQ_REDHOT
    &txt_thorndust, // SEQ_FARM
    &txt_thorndust, // SEQ_JUNGLE
    &txt_thorndust, // SEQ_EVENT_CUTSCENE_ENDING
    &txt_thorndust, // SEQ_PIRATE
    &txt_thorndust, // SEQ_EVENT_BOSS

    &txt_spk,       //SEQ_LEVEL_KOOPA_ROAD
    &txt_spk,       //SEQ_URBOWSER
    &txt_spk,       //SEQ_BIG_HOUSE
    //10^

    &txt_jaguar,    // SEQ_SMB1_OVERWORLD
    &txt_jaguar,    // SEQ_SMB2_OVERWORLD
    &txt_jaguar,    // SEQ_SMB3_CASTLE
    &txt_jaguar,    // SEQ_NSMB_CASTLE

    &txt_spk,       //SEQ_SHOWRUNNER_BOSS
    &txt_spk,       //SEQ_COSMIC_SEED_LEVEL
    &txt_spk,       //SEQ_FINAL_BOSS

    &txt_nomico,    // SEQ_STREAMED_BAD_APPLE
};

#define mus_count 5//ARRAY_COUNT(seq_musicmenu_array)
//STATIC_ASSERT(ARRAY_COUNT(musicmenu_authors) == mus_count, "musicmenu_authors has incorrect number of entries!");

void render_music_menu() {
    s8 i;
    s8 i_offset;
    u32 music_flags = 0x3FF;
    
    // //check unlocked music
    // if (save_file_get_course_star_count(gCurrSaveFileNum - 1, COURSE_LLL) > 0) {
    //     music_flags |= (1<<10); //Unlock big house
    // }

    // if (save_file_get_course_star_count(gCurrSaveFileNum - 1, COURSE_SSL) > 0) {
    //     music_flags |= (1<<11); //Unlock smb1
    //     music_flags |= (1<<12); //Unlock smb2
    //     music_flags |= (1<<13); //Unlock smb3
    // }

    // if (save_file_get_course_star_count(gCurrSaveFileNum - 1, COURSE_DDD) > 0) {
    //     music_flags |= (1<<14); //Unlock nsmb castle (c9)
    // }

    // if (save_file_check_progression(PROG_POSTGAME)) {
    //     music_flags |= (1<<15); //Unlock agamemnon songs
    //     music_flags |= (1<<16); //
    //     music_flags |= (1<<17); //
    // }

    // if (save_file_get_hiscore(5) > 0) {
    //     music_flags |= (1<<18); //Unlock bad apple
    // }

    if ((gPlayer1Controller->rawStickY > 60)&&(letgo2 == FALSE)) {
        stop_background_music(seq_musicmenu_array[minigame_index]);
        letgo2 = TRUE;
        minigame_index --;
        minigame_index = (minigame_index+mus_count)%mus_count;
        if (music_flags & (1<<minigame_index)) {
            play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(15, seq_musicmenu_array[minigame_index]), 0);
            //rtext_insert_pointer[0] = musicmenu_titles[minigame_index];
            rtext_insert_pointer[1] = musicmenu_authors[minigame_index];
            read_dialog(DIALOG_MUSICROOM);
        }
    }
    if ((gPlayer1Controller->rawStickY < -60)&&(letgo2 == FALSE)) {
        stop_background_music(seq_musicmenu_array[minigame_index]);
        letgo2 = TRUE;
        minigame_index ++;
        minigame_index = (minigame_index+mus_count)%mus_count;
        if (music_flags & (1<<minigame_index)) {
            play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(15, seq_musicmenu_array[minigame_index]), 0);
            //rtext_insert_pointer[0] = musicmenu_titles[minigame_index];
            rtext_insert_pointer[1] = musicmenu_authors[minigame_index];
            read_dialog(DIALOG_MUSICROOM);
        }
    }
    if ((gPlayer1Controller->rawStickX > -60)&&(gPlayer1Controller->rawStickX < 60)&&(gPlayer1Controller->rawStickY > -60)&&(gPlayer1Controller->rawStickY < 60)) {
        letgo2 = FALSE;
    }

/*
    //render back box
    create_dl_translation_matrix(MENU_MTX_PUSH, 20, 218, 0);
    create_dl_scale_matrix(MENU_MTX_NOPUSH, 1.8f, 1.9f, 1.0f);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    //render selection box
    create_dl_translation_matrix(MENU_MTX_PUSH, 22, 216-(16*minigame_index), 0);
    create_dl_scale_matrix(MENU_MTX_NOPUSH, 1.5f, 0.2f, 1.0f);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, sinresult/2);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    //render music list
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
        print_generic_string(74,199, music_text);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        print_generic_string(75,200, music_text);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
*/

    //render main box
    create_dl_translation_matrix(MENU_MTX_PUSH, 12, 190, 0);
    create_dl_scale_matrix(MENU_MTX_NOPUSH, 0.8f, 1.1f, 1.0f);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    //render selection box
    create_dl_translation_matrix(MENU_MTX_PUSH, 12, 158, 0);
    create_dl_scale_matrix(MENU_MTX_NOPUSH, 0.8f, 0.2f, 1.0f);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, sinresult/2);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    //render unlocked costumes
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    for (i=-2;i<3;i++) {
        i_offset = i+minigame_index;

        if ((i_offset > -1)&&(i_offset <mus_count)) {
            if (music_flags & (1<<i_offset)) {
                    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
                    //print_generic_string(14,140-(i*16), musicmenu_titles[i_offset]);
                    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                    //print_generic_string(15,141-(i*16), musicmenu_titles[i_offset]);
                } else {
                    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
                    print_generic_string(14,140-(i*16), &qbuf);
                    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                    print_generic_string(15,141-(i*16), &qbuf);
                }
            }
    };

    // i really thinkg you should end this dl
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);




    //control
    if (gPlayer1Controller->buttonPressed & A_BUTTON) {
        //exit
        stop_event();
    }
}

u8 ce_n[] = {CTM_EFF_NONE};
u8 ce_2[] = {CTM_EFF_2};
u8 ce_5[] = {CTM_EFF_5};
u8 ce_8[] = {CTM_EFF_8};
u8 ce_12[] = {CTM_EFF_12};








//<<<use the actual line num to figure it out
u8 *costume_effect_text[] = {
&ce_n,
&ce_2,
&ce_n,
&ce_n,
&ce_5,
&ce_n,
&ce_n,
&ce_8,
&ce_n,
&ce_n,
&ce_n,
&ce_12,
};

u8 costume_order[] = {
    CTM_MARIO,
    CTM_LUIGI,
    CTM_FIRE,//c1
    CTM_WARIO,//2
    CTM_MOCAP,//4
    CTM_PIRATE,//5
    CTM_BUTLER,//7
    CTM_RETRO,//8
    CTM_THWOMPIO,//9
    CTM_GLITCHY,//10
    
    CTM_DARIUS,

    CTM_DISCO,
    CTM_BUILDER,
    CTM_RUNNER,
    CTM_PHANTASM
    };

#define CTM_COUNT 15

void render_costume_menu() {
    s8 i;
    s8 i_offset;
    u16 costume_flags = save_file_get_costume_unlock();

    if ((gPlayer1Controller->rawStickY > 60)&&(letgo2 == FALSE)) {
        letgo2 = TRUE;
        minigame_index --;
        minigame_index = (minigame_index+CTM_COUNT)%CTM_COUNT;
    }
    if ((gPlayer1Controller->rawStickY < -60)&&(letgo2 == FALSE)) {
        letgo2 = TRUE;
        minigame_index ++;
        minigame_index = (minigame_index+CTM_COUNT)%CTM_COUNT;
    }
    if ((gPlayer1Controller->rawStickX > -60)&&(gPlayer1Controller->rawStickX < 60)&&(gPlayer1Controller->rawStickY > -60)&&(gPlayer1Controller->rawStickY < 60)) {
        letgo2 = FALSE;
    }

    //render main box
    create_dl_translation_matrix(MENU_MTX_PUSH, 12, 190, 0);
    create_dl_scale_matrix(MENU_MTX_NOPUSH, 0.8f, 1.1f, 1.0f);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    //render selection box
    create_dl_translation_matrix(MENU_MTX_PUSH, 12, 158, 0);
    create_dl_scale_matrix(MENU_MTX_NOPUSH, 0.8f, 0.2f, 1.0f);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, sinresult/2);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    //render unlocked costumes
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    for (i=-2;i<3;i++) {
        i_offset = i+minigame_index;

        if ((i_offset > -1)&&(i_offset <CTM_COUNT)) {
            if (costume_flags & (1<<costume_order[i_offset])) {
                    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
                    print_generic_string(14,140-(i*16), costume_text[costume_order[i_offset]]);
                    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                    print_generic_string(15,141-(i*16), costume_text[costume_order[i_offset]]);
                } else {
                    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
                    print_generic_string(14,140-(i*16), &qbuf);
                    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                    print_generic_string(15,141-(i*16), &qbuf);
                }
            }
    };

    // i really thinkg you should end this dl
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

    if (costume_flags & (1<<costume_order[minigame_index])) {
        //gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
        //print_generic_string(14,60, costume_effect_text[costume_order[minigame_index]]);
        //gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        //print_generic_string(15,61, costume_effect_text[costume_order[minigame_index]]);
        //gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

        gMarioState->CostumeID = costume_order[minigame_index];
    }

        save_file_set_stats();

    //mario go speen
    gMarioState->faceAngle[1] += 0x100;
    vec3f_copy(&gMarioState->pos,&revent_target_object->oPosX);

    //control
    if (gPlayer1Controller->buttonPressed & A_BUTTON) {
        //exit
        stop_event();
    }
}

void read_dialog(s32 dialog_id) {
    u16 i;
    u16 i2;
    u8 pic;
    u16 iwrite;

    u8 **dialogTable = segmented_to_virtual(seg2_dialog_table);
    struct DialogEntry *sdialog = segmented_to_virtual(dialogTable[dialog_id]);
    u8 *sstr = segmented_to_virtual(sdialog->str);

    i = 0;
    iwrite = 0;
    pic = 0;
    while(sstr[i] != DIALOG_CHAR_TERMINATOR) {
        if (sstr[i] == 0xE0) {
            i2 = 0;
            while (rtext_insert_pointer[pic][i2] != DIALOG_CHAR_TERMINATOR) {
                rtext_read[iwrite] = rtext_insert_pointer[pic][i2];
                iwrite++;
                i2++;
            }
            pic++;
        } else {
            rtext_read[iwrite] = sstr[i];
            iwrite++;
            }
        i++;
    }
    

    rtext_read[iwrite] = DIALOG_CHAR_TERMINATOR;
    rtext_read_index = 0;
}

//Event Logic
void run_event(u8 event_tdo) {
    if (!revent_active) {
        revent_tempo = 0;
        revent_stop_enemies = TRUE;
        revent_room = gMarioCurrentRoom;
        revent_camera_on = FALSE;
        revent_camera_mode = ECM_STATIC;
        revent_loop_count = 0;
        revent_loop_index = 0;
        revent_active = TRUE;
        revent_halt = FALSE;
        revent_hud = TRUE;
        revent_text_engine = FALSE;
        revent_mario_lock = FALSE;
        revent_index = 0;
        rtext_opacity = 0.0f;
        revent_queue = 0;
        rtext_choice = 0;
        quiz_display = FALSE;
        quiz_points = 0;
        revent_music = 0;
        revent_pointer = event_list[event_tdo];
    }
}

void event_main(void) {
    u8 i = 0;
    u8 swap;
    s32 command;
    s32 arg1;
    s32 arg2;
    s32 arg3;
    struct Object *spawnobj;

    // f32 (*CamPath)[2][3] = segmented_to_virtual(spline_list[revent_cam_spline_pointer]);

    while ((!revent_halt)&&(revent_active)) {
        command = revent_pointer[revent_index];
        arg1 = revent_pointer[revent_index+1];
        arg2 = revent_pointer[revent_index+2];
        arg3 = revent_pointer[revent_index+3];
        
        switch(command) {
            // case E_WAIT:
            //     revent_timer = arg1;
            //     revent_halt = TRUE;
            // break;
            // case E_WALK_TO_TARGET:
            //     revent_walk_dist = (f32)arg1,
            //     revent_halt = TRUE;
            // break;
            // case E_WALK_FROM_TARGET:
            //     revent_walk_dist = (f32)arg1,
            //     revent_halt = TRUE;
            // break;
            // case E_DIALOG_AND_PRESSA:
            //     read_dialog(arg1);
            //     rtext_done = FALSE;
            //     rtext_dialog_delay = 0;
            //     revent_text_engine = TRUE;
            //     rtext_choice = 0;
            //     revent_halt = TRUE;
            // break;
            // case E_DIALOG_WAIT_PRESSA:
            //     revent_halt = TRUE;
            // break;
            // case E_DIALOG_WAIT_END:
            //     revent_halt = TRUE;
            // break;
            // case E_DIALOG_WAIT_UPGRADE:
            //     revent_halt = TRUE;
            // break;
            // case E_MINIGAME_MENU:
            //     minigame_index = 0;
            //     revent_halt = TRUE;
            // break;
            // case E_COSTUME_MENU:
            //     minigame_index = 0;
            //     while (i != gMarioState->CostumeID) {
            //         minigame_index++;
            //         i = costume_order[minigame_index];
            //     }
            //     revent_halt = TRUE;
            // break;
            // case E_MUSIC_MENU:
            //     minigame_index = 0;
            //     revent_halt = TRUE;
            // break;
            // case E_ZOUND:
            //     play_sound(arg1, gGlobalSoundSource);
            //     revent_index += 2;
            // break;
            // case E_MUSIC:
            //     revent_music = SEQ_PLAYER_LEVEL;
            //     play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(15, arg1), 0);
            //     revent_index += 2;
            // break;
            // case E_STOP_MUSIC:
            //     stop_background_music(SEQUENCE_ARGS(4, arg1));
            //     revent_index+=2;
            // break;
            // case E_TEMPO:
            //     revent_tempo = arg1;
            //     revent_index+=2;
            // break;
            // case E_QUEUE:
            //     revent_queue = arg1;
            //     revent_index += 2;
            // break;
            // case E_ACT:
            //     set_mario_action(gMarioState, arg1,0);
            //     revent_index += 2;
            // break;
            // case E_TARGET_OBJECT:
            //     gCurrentObject = gMarioObject;
            //     revent_target_object = cur_obj_nearest_object_with_behavior(arg1);
            //     revent_index += 2;
            // break;
            // case E_TARGET_MARIO:
            //     revent_target_object = gMarioObject;
            //     revent_index++;
            // break;
            // case E_TARGET_OBJECT_DELETE:
            //     mark_obj_for_deletion(revent_target_object);
            //     revent_index += 1;
            // break;
            // case E_TARGET_OBJECT_ACTION:
            //     revent_target_object->oAction = arg1;
            //     revent_index += 2;
            // break;
            // case E_TARGET_OBJECT_SUBACTION:
            //     revent_target_object->oSubAction = arg1;
            //     revent_index += 2;
            // break;
            // case E_START_LOOP:
            //     revent_loop_count = 0;
            //     revent_loop_index = revent_index+1;
            //     revent_index += 1;
            // break;
            // case E_REPEAT:
            //     revent_loop_count ++;
            //     if (revent_loop_count < arg1) {
            //             revent_index = revent_loop_index;
            //         } else {
            //             revent_index += 2;
            //         }
            // break;
            // case E_HUD_TOGGLE:
            //     revent_hud = !revent_hud;
            //     revent_index ++;
            // break;
            // case E_CAM_TOGGLE:
            //     //no custom cutscenes in 2D
            //     if (!gMarioState->_2D) {
            //         revent_camera_on = !revent_camera_on;
            //     }
            //     vec3f_copy(revent_camera_pos,gLakituState.pos);
            //     vec3f_copy(revent_camera_foc,gLakituState.focus);
            //     revent_index ++;
            // break;
            // case E_CAM_FOCUS_TARGET:
            //     revent_camera_mode = ECM_STATIC;
            //     revent_target_object->oPosY += 50.0f;//aim the camera not directly on the origin poitn whic is on floor lol
            //     vec3f_copy(revent_camera_foc,&revent_target_object->oPosX);
            //     revent_target_object->oPosY -= 50.0f;
            //     revent_index++;
            // break;
            // case E_CAM_ORBIT:
            //     revent_camera_mode = ECM_ORBIT;
            //     revent_cam_orbit_dist = (f32)arg1;
            //     revent_cam_orbit_height = (f32)arg2;
            //     revent_cam_orbit_speed = (s16)arg3;
            //     orbit_yaw = revent_target_object->oFaceAngleYaw;

            //     revent_index += 4;
            // break;
            // case E_CAM_POS_XYZ:
            //     revent_camera_pos[0] = (f32)arg1;
            //     revent_camera_pos[1] = (f32)arg2;
            //     revent_camera_pos[2] = (f32)arg3;
            //     revent_index += 4;
            // break;
            // case E_CAM_FOCUS_XYZ:
            //     revent_camera_foc[0] = (f32)arg1;
            //     revent_camera_foc[1] = (f32)arg2;
            //     revent_camera_foc[2] = (f32)arg3;
            //     revent_index += 4;
            // break;
            // case E_CAM_MASTER_SHOT:
            //     vec3f_copy(revent_camera_pos,&revent_target_object->oPosX);
            //     revent_camera_pos[0] += sins(revent_target_object->oFaceAngleYaw+arg2)*(f32)arg1;
            //     revent_camera_pos[1] += (f32)arg1*.5f;
            //     revent_camera_pos[2] += coss(revent_target_object->oFaceAngleYaw+arg2)*(f32)arg1;
            //     revent_index += 3;
            // break;
            // case E_CAM_CLOSE_UP:
            //     vec3f_copy(revent_camera_pos,&revent_target_object->oPosX);
            //     revent_camera_pos[0] += sins(revent_target_object->oFaceAngleYaw)*300.0f;
            //     revent_camera_pos[1] += 150.0f;
            //     revent_camera_foc[2] = revent_camera_pos[2];
            //     revent_camera_pos[2] += coss(revent_target_object->oFaceAngleYaw)*300.0f;
            //     revent_index ++;
            // break;
            // case E_CAM_MANUAL_ECM:
            //     revent_camera_mode = arg1;
            //     revent_index += 2;
            // break;
            // case E_CAM_SPLINE:
            //     revent_cam_spline_pointer = arg1;
            //     revent_cam_spline_max = arg2;
            //     revent_cam_spline_index = 0;
            //     revent_camera_mode = ECM_SPLINE;
            //     CamPath = segmented_to_virtual(spline_list[revent_cam_spline_pointer]);
            //     revent_index += 3;
            // break;
            // case E_TARGET_OBJECT_SPAWN:
            //     spawnobj = spawn_object(revent_target_object,arg1,arg2);
            //     spawnobj->oBehParams2ndByte = arg3;
            //     revent_index+=4;
            // break;
            // case E_PUZZLE_JINGLE:
            //     play_puzzle_jingle();
            //     revent_index ++;
            // break;
            // case E_DIALOG:
            //     read_dialog(arg1);
            //     rtext_done = FALSE;
            //     rtext_dialog_delay = 0;
            //     revent_text_engine = TRUE;
            //     revent_index+=2;
            //     rtext_choice = 0;
            // break;
            // case E_CLOSE_DIALOG:
            //     revent_text_engine = FALSE;
            //     revent_index++;
            // break;
            // case E_DIALOG_YESNO:
            //     rtext_choice = 1;
            //     rtext_choice_amount = 2;
            //     rtext_choice_index = 0;
            //     rtext_offset_buffer[0] = 8;
            //     rtext_offset_buffer[1] = 42;
            //     revent_index++;
            // break;
            // case E_DIALOG_ABCD:
            //     rtext_choice = 2;
            //     rtext_choice_amount = 4;
            //     rtext_choice_index = 0;
            //     rtext_offset_buffer[0] = 8;
            //     rtext_offset_buffer[1] = 32;
            //     rtext_offset_buffer[2] = 52;
            //     rtext_offset_buffer[3] = 72;
            //     revent_index++;
            // break;
            // case E_DIALOG_ABC:
            //     rtext_choice = 3;
            //     rtext_choice_amount = 3;
            //     rtext_choice_index = 0;
            //     rtext_offset_buffer[0] = 8;
            //     rtext_offset_buffer[1] = 32;
            //     rtext_offset_buffer[2] = 52;
            //     rtext_offset_buffer[3] = 72;
            //     revent_index++;
            // break;
            // case E_DIALOG_AB:
            //     rtext_choice = 4;
            //     rtext_choice_amount = 2;
            //     rtext_choice_index = 0;
            //     rtext_offset_buffer[0] = 8;
            //     rtext_offset_buffer[1] = 32;
            //     rtext_offset_buffer[2] = 52;
            //     rtext_offset_buffer[3] = 72;
            //     revent_index++;
            // break;
            // case E_DIALOG_CHOICE_JUMP:
            //     if (rtext_choice_index == arg1) {
            //         revent_index+=2+arg2;
            //     } else {
            //         //failed, continue as normal
            //         revent_index+=3;
            //     }
            // break;
            // case E_QUIZ_POINT_JUMP:
            //     if (quiz_points >= arg1) {
            //         revent_index+=2+arg2;
            //         save_file_set_flags(SAVE_FLAG_HAPPY_SHOWRUNNER);
            //     } else {
            //         //failed, continue as normal
            //         revent_index+=3;
            //     }
            // break;
            // case E_JUMP:
            //     revent_index+=1+arg1;
            // break;
            // case E_ROOM:
            //     revent_room = arg1;
            //     revent_index+=2;
            // break;
            // case E_ENEMIES_TOGGLE:
            //     revent_stop_enemies = !revent_stop_enemies;
            //     revent_index++;
            // break;
            // case E_SAVEGAME:
            //     save_file_do_save(gCurrSaveFileNum - 1);
            //     revent_index++;
            // break;
            // case E_PUT_ON_COSTUME:
            //     swap = gMarioState->LastCostumeID;
            //     gMarioState->LastCostumeID = gMarioState->CostumeID;
            //     gMarioState->CostumeID = swap;
            //     save_file_set_stats();
            //     revent_index ++;
            // break;
            // case E_MINIGAME_UNLOCK:
            //     gMarioState->gGlobalCoinGain = -mg_prices[minigame_index];
            //     save_file_unlock_minigame(minigame_index);
            //     revent_index+=2;
            // break;
            // case E_MARIO_LOCK:
            //     revent_mario_lock = TRUE;
            //     vec3f_copy(&revent_mario_lock_position,&gMarioState->pos);
            //     vec3f_copy(&revent_mario_lock_velocity,&gMarioState->vel);
            //     revent_index ++;
            // break;
            // case E_MARIO_UNLOCK:
            //     revent_mario_lock = FALSE;
            //     revent_index ++;
            // break;
            // case E_MARIO_TELEPORT:
            //     gMarioState->pos[0] = arg1;
            //     gMarioState->pos[1] = arg2;
            //     gMarioState->pos[2] = arg3;
            //     revent_index+=4;
            // break;
            // case E_HEAD_TOGGLE:
            //     revent_head_move = !revent_head_move;
            //     revent_index ++;
            // break;
            // case E_HEAD_ANGLE:
            //     revent_headangle[0] = arg1;
            //     revent_headangle[1] = arg2;
            //     revent_headangle[2] = arg3;
            //     revent_index += 4;
            // break;
            // case E_MARIO_YAW:
            //     gMarioState->faceAngle[1] = arg1;
            //     gMarioObject->oFaceAngleYaw = arg1;
            //     revent_index += 2;
            // break;
            // case E_MARIO_VEL:
            //     gMarioState->forwardVel = (f32)arg1;
            //     revent_index += 2;
            // break;
            // case E_MARIO_HANDSTATE:
            //     revent_handstate = arg1;
            //     revent_index += 2;
            // break;
            // case E_QUIZ_HOST:
            //     revent_camera_pos[0] = 0.0f;
            //     revent_camera_pos[1] = 725.0f;
            //     revent_camera_pos[2] =-1279.0f;
            //     vec3f_copy(&revent_camera_foc,&revent_camera_pos);
            //     revent_camera_foc[2] += 10.0f;
            //     revent_camera_mode = ECM_STATIC;
            //     revent_index ++;
            //     quiz_display = FALSE;
            // break;
            // case E_QUIZ_CONTESTANT: //-800, 462, -1422,
            //     revent_camera_pos[0] = -800.0f+(800.0f*(f32)(arg1));
            //     revent_camera_pos[1] = 462.0f;
            //     revent_camera_pos[2] =-1422.0f;
            //     vec3f_copy(&revent_camera_foc,&revent_camera_pos);
            //     revent_camera_foc[2] -= 10.0f;
            //     revent_camera_mode = ECM_STATIC;
            //     revent_index += 2;
            //     quiz_display = FALSE;
            // break;
            // case E_QUIZ_SCORES: //0, 656, 171,
            //     revent_camera_pos[0] = 0.0f;
            //     revent_camera_pos[1] = 656.0f;
            //     revent_camera_pos[2] = 171.0f;
            //     vec3f_copy(&revent_camera_foc,&revent_camera_pos);
            //     revent_camera_foc[2] -= 10.0f;
            //     revent_camera_mode = ECM_STATIC;
            //     quiz_display = TRUE;
            //     revent_index ++;
            // break;
            // case E_DIALOG_BUZZ_IN:
            //     revent_timer = arg1;
            //     revent_halt = TRUE;
            // break;
            // case E_TARGET_OBJECT_SPOTLIGHT:
            //     gMarioState->SpotlightTarget = revent_target_object;
            //     gMarioState->SpotlightTargetYOffset = arg1;
            //     revent_index += 2;
            // break;
            // case E_QUIZ_POINT:
            //     quiz_points += arg1;
            //     revent_index += 2;
            // break;
            // case E_WARP:
            //     level_trigger_warp(gMarioState, WARP_OP_LOOK_UP);
            //     sSourceWarpNodeId = arg1;
            //     revent_halt = TRUE;
            // break;
            // case E_PROGRESS_SET:
            //     save_file_set_progression(arg1);
            //     revent_index += 2;
            // break;
            // case E_SAVEFLAG_SET:
            //     save_file_set_flags(arg1);
            //     revent_index += 2;
            // break;
            // case E_START_PRECREDITS:
            //     start_precredits = TRUE;
            //     revent_index++;
            // break;
            // case E_END:
            //     stop_event();
            // break;
        }
    }

    if (revent_halt) {
        command = revent_pointer[revent_index];
        arg1 = revent_pointer[revent_index+1];
        arg2 = revent_pointer[revent_index+2];
        arg3 = revent_pointer[revent_index+3];

        switch(command) {
            case E_WAIT:
                revent_timer --;
                if (revent_timer < 1) {
                    revent_halt = FALSE;
                    revent_index += 2;
                }
            break;
            case E_WALK_TO_TARGET:
                if (((gMarioState->action & ACT_FLAG_STATIONARY)&&(gMarioState->action != ACT_PUSHING_DOOR))||(gMarioState->action == ACT_SLIDE_KICK_SLIDE)) {
                    set_mario_action(gMarioState, ACT_WALKING,0);
                }

                if (!(gMarioState->action & ACT_FLAG_AIR)) {
                    gMarioState->faceAngle[1] = obj_angle_to_object(gMarioObject, revent_target_object);
                    gMarioState->forwardVel = 15.0f;
                }


                if (dist_between_objects(gMarioObject,revent_target_object) < revent_walk_dist ) {
                    revent_halt = FALSE;
                    revent_index += 2;
                }
            break;
            case E_WALK_FROM_TARGET:
                if (gMarioState->action & ACT_FLAG_STATIONARY) {
                    set_mario_action(gMarioState, ACT_WALKING,0);
                }

                if (!(gMarioState->action & ACT_FLAG_AIR)) {
                    gMarioState->faceAngle[1] = obj_angle_to_object(gMarioObject, revent_target_object)+0x7FFF;
                    gMarioState->forwardVel = 15.0f;
                }


                if (dist_between_objects(gMarioObject,revent_target_object) > revent_walk_dist ) {
                    revent_halt = FALSE;
                    revent_index += 2;
                }
            break;
            case E_DIALOG_WAIT_PRESSA:
                if ((rtext_done)&&(gPlayer1Controller->buttonPressed & A_BUTTON)) {
                    revent_halt = FALSE;
                    revent_index ++;
                }
            break;
            case E_DIALOG_AND_PRESSA:
                if ((rtext_done)&&(gPlayer1Controller->buttonPressed & A_BUTTON)) {
                    revent_halt = FALSE;
                    revent_index += 2;
                }
            break;
            case E_DIALOG_WAIT_END:
                if (rtext_done) {
                    revent_halt = FALSE;
                    revent_index ++;
                }
            break;
            case E_DIALOG_BUZZ_IN:
                //arg 1 is how long u wait
                //arg 2 is the jump to the alternate buzz in
                revent_timer--;
                if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                    revent_index += 3;
                    revent_halt = FALSE;
                } else if (revent_timer < 1) {
                    revent_index += 3+arg2;
                    revent_halt = FALSE;
                }
            break;
            case E_DIALOG_WAIT_UPGRADE:
                if ((rtext_done)&&(gMarioState->Level > 0)) {
                    revent_halt = FALSE;
                    revent_index ++;
                }
            break;
            case E_WARP:
                //nothing
            break;
        }
    }

    switch(revent_camera_mode) {
        case ECM_ORBIT:
            revent_camera_pos[0] = revent_camera_foc[0] + (sins(orbit_yaw)*revent_cam_orbit_dist);
            revent_camera_pos[2] = revent_camera_foc[2] + (coss(orbit_yaw)*revent_cam_orbit_dist);
            revent_camera_pos[1] = revent_camera_foc[1] + revent_cam_orbit_height;
            orbit_yaw += revent_cam_orbit_speed;
        break;
        case ECM_ORBIT_TRACK:
            vec3f_copy(&revent_camera_foc,&revent_target_object->oPosX);
            revent_camera_pos[0] = revent_camera_foc[0] + (sins(orbit_yaw)*revent_cam_orbit_dist);
            revent_camera_pos[2] = revent_camera_foc[2] + (coss(orbit_yaw)*revent_cam_orbit_dist);
            revent_camera_pos[1] = revent_camera_foc[1] + revent_cam_orbit_height;
            orbit_yaw += revent_cam_orbit_speed;
        break;
        case ECM_TRACK_TARGET:
            vec3f_copy(&revent_camera_foc,&revent_target_object->oPosX);
        break;
        case ECM_TRACK_MARIO:
            vec3f_copy(&revent_camera_foc,&gMarioState->pos);
        break;
        // case ECM_SPLINE:
        //     vec3f_copy(&revent_camera_pos,&CamPath[revent_cam_spline_index][0][0]);
        //     vec3f_copy(&revent_camera_foc,&CamPath[revent_cam_spline_index][1][0]);

        //     if (revent_cam_spline_index < revent_cam_spline_max) {
        //         revent_cam_spline_index++;
        //         }
        // break;
    }

    if (revent_mario_lock) {
        vec3f_copy(&gMarioState->pos,&revent_mario_lock_position);
        vec3f_copy(&gMarioState->vel,&revent_mario_lock_velocity);
    }
}

u8 letgo1 = TRUE;
void render_revent_textbox(void) {
    u8 i;
    u8 textsteps = 1;
    u8 *txtptr = rtext_yesno;

    if (gPlayer1Controller->buttonDown & B_BUTTON) {
        textsteps = 8;
    }
    rtext_sintimer += 800;
    sinresult = 150.0f+ABS(sins(rtext_sintimer)*100.0f);

    if (rtext_opacity > 1.0f) {
        for (i=0;i<textsteps;i++) {
            if (rtext_read[rtext_read_index] != DIALOG_CHAR_TERMINATOR) {
                if (rtext_dialog_delay == 0) {
                    rtext_display[rtext_read_index] = rtext_read[rtext_read_index];
                    rtext_display[rtext_read_index+1] = DIALOG_CHAR_TERMINATOR;

                    if (rtext_read[rtext_read_index] != DIALOG_CHAR_SPACE) {
                        play_sound(SOUND_OBJ_KOOPA_WALK,gGlobalSoundSource);
                        rtext_dialog_delay = 0;
                    }
                    if (rtext_read[rtext_read_index] == DIALOG_CHAR_COMMA) {
                        rtext_dialog_delay = 4;
                    }
                    if (rtext_read[rtext_read_index] == 0x3F) {
                        rtext_dialog_delay = 6;
                    }
                    if (rtext_read[rtext_read_index] == 0xF2) {
                        rtext_dialog_delay = 6;
                    }

                    rtext_read_index ++;
                } else {
                    rtext_dialog_delay --;
                }
            } else {
                //done reading
                rtext_done = TRUE;
            }
        }
        //render box
        create_dl_translation_matrix(MENU_MTX_PUSH, 160, 30, 0);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, rtext_opacity);
        gSPDisplayList(gDisplayListHead++, &gradibox_Plane_mesh);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
        //render text
        gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, rtext_opacity);
        print_generic_string(9, 40, rtext_display);//rtext_pressa
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, rtext_opacity);
        print_generic_string(10, 41, rtext_display);
        //render press a
        if (((revent_pointer[revent_index] == E_DIALOG_WAIT_PRESSA)||(revent_pointer[revent_index] == E_DIALOG_AND_PRESSA))&&(rtext_done)) {
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, rtext_opacity);
            print_generic_string(299, 7, rtext_pressa);//rtext_pressa
            gDPSetEnvColor(gDisplayListHead++, sinresult, sinresult, sinresult, rtext_opacity);
            print_generic_string(300, 8, rtext_pressa);
        }
        //render decision
        if ((rtext_choice >= 1)&&(rtext_done)) {
            //decision controls
            if ((gPlayer1Controller->rawStickX > 60)&&(letgo1 == FALSE)) {
                rtext_choice_index++;
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
                letgo1 = TRUE;
                }
            if ((gPlayer1Controller->rawStickX < -60)&&(letgo1 == FALSE)) {
                rtext_choice_index--;
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
                letgo1 = TRUE;
                }
            if ((gPlayer1Controller->rawStickX > -60)&&(gPlayer1Controller->rawStickX < 60)) {
                letgo1 = FALSE;
                }
            rtext_choice_index=(rtext_choice_amount+rtext_choice_index)%rtext_choice_amount;

            switch(rtext_choice) {
                case 2:
                    txtptr = rtext_abcd;
                break;
                case 3:
                    txtptr = rtext_abc;
                break;
                case 4:
                    txtptr = rtext_ab;
                break;
            }

            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, rtext_opacity);
            print_generic_string(19, 7, txtptr);
            gDPSetEnvColor(gDisplayListHead++, 255,255,255, rtext_opacity);
            print_generic_string(20, 8, txtptr);

            create_dl_translation_matrix(MENU_MTX_PUSH, rtext_offset_buffer[rtext_choice_index], 8, 0);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, rtext_opacity);
            gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
        }
        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

        //render textbox menus if needed
        // switch(revent_pointer[revent_index]) {
        //     case E_MINIGAME_MENU:
        //         render_minigame_menu();
        //     break;
        //     case E_COSTUME_MENU:
        //         render_costume_menu();
        //     break;
        //     case E_MUSIC_MENU:
        //         render_music_menu();
        //     break;
        // }
    }

    if (revent_text_engine) {
        rtext_opacity = lerp(rtext_opacity,255.0f,0.1f);
    } else {
        rtext_opacity = lerp(rtext_opacity,0.0f,0.1f);
    }

}