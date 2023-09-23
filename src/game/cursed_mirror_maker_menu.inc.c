extern u8 gDialogCharWidths[256];
s32 get_string_width_ascii(char *str) {
    s16 strPos = 0;
    s16 width = 0;

    while (str[strPos] != 0) {
        width += gDialogCharWidths[ASCII_TO_DIALOG(str[strPos])];
        strPos++;
    }
    return width;
}

u8 string_runoff(s16 x, char *str) {
    s16 x1 = get_string_width_ascii(str);

    if (x+x1 > 320) {
        return TRUE;
    }
    return FALSE;
}

void print_maker_string_ascii(u16 x, u16 y, char *str, u8 highlight) {
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
    print_generic_string_ascii(x-1, y-1, (u8 *)str);
    switch(highlight) {
        case 0:
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        break;
        case 1:
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
        break;
        case 2:
            gDPSetEnvColor(gDisplayListHead++, 150, 150, 150, 255);
        break;
        case 3:
            gDPSetEnvColor(gDisplayListHead++, 150, 150, 0, 255);
        break;
        case 4:
            gDPSetEnvColor(gDisplayListHead++, 255, 0, 0, 255);
        break;
    }
    print_generic_string_ascii(x, y, (u8 *)str);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

void print_maker_string(u16 x, u16 y, u8 *str, u8 highlight) {
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
    print_generic_string(x-1, y-1, str);
    if (highlight) {
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
    } else {
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    }
    print_generic_string(x, y, str);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

void draw_cmm_menu(void) {
    u8 i;
    u8 op;
    u8 yoff;
    u8 xi;
    u8 yi;

    u16 strx, stry;

    u16 decor_bar_offset = 36;
    if (cmm_menu_state == CMM_MAKE_TOOLBOX || cmm_menu_state == CMM_MAKE_SETTINGS) {
        decor_bar_offset = 235;
    }

    if (!cmm_ui_do_render) {
        cmm_ui_do_render = TRUE;
        return;
    }

    create_dl_translation_matrix(MENU_MTX_PUSH, 19, decor_bar_offset, 0);
    gDPSetEnvColor(gDisplayListHead++, 200, 200, 200, 150);
    gSPDisplayList(gDisplayListHead++, &bg_back_graund_mesh);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    for (i=0; i<9; i++) {
        op = 200;
        yoff = 20;
        if (i == cmm_ui_index) {
            op = 255;
            yoff = 25;
        }
        create_dl_translation_matrix(MENU_MTX_PUSH, 34+(i*32), yoff, 0);
        gDPSetEnvColor(gDisplayListHead++, op, op, op, 255);
        gSPDisplayList(gDisplayListHead++, cmm_ui_buttons[cmm_ui_bar[i]].material);//texture
        gSPDisplayList(gDisplayListHead++, &uibutton_button_mesh);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    }

    //TOOLBOX
    switch (cmm_menu_state) {
        case CMM_MAKE_MAIN:
            print_maker_string_ascii(15,45,cmm_ui_buttons[cmm_ui_bar[cmm_ui_index]].str,FALSE);
            if (cmm_ui_buttons[cmm_ui_bar[cmm_ui_index]].param_strings) {
                print_maker_string_ascii(30+get_string_width_ascii(cmm_ui_buttons[cmm_ui_bar[cmm_ui_index]].str),45,
                cmm_ui_buttons[cmm_ui_bar[cmm_ui_index]].param_strings[cmm_param_selection],TRUE);
            } else if (cmm_place_mode == CMM_PM_TILE && cmm_tile_terrains[cmm_id_selection]) {
                print_maker_string_ascii(30+get_string_width_ascii(cmm_ui_buttons[cmm_ui_bar[cmm_ui_index]].str),45,
                TILE_MATDEF(cmm_mat_selection).name,TRUE);
            }

            if (cmm_error_timer > 0) {
                if (cmm_error_timer == 120) {
                    cmm_error_vels[1] = -15.f;
                    cmm_error_vels[2] = 2.f;
                } else if (cmm_error_timer == 30) {
                    cmm_error_vels[2] = 2.f;
                }
                if (cmm_error_timer > 60 && cmm_error_vels[1] > 0) {
                    cmm_error_vels[1] = 0;
                    cmm_error_vels[2] = 0;
                }
                if (cmm_error_vels[0] > 280) {
                    cmm_error_vels[1] = 0;
                    cmm_error_vels[2] = 0;
                }
                cmm_error_vels[0] += cmm_error_vels[1];
                cmm_error_vels[1] += cmm_error_vels[2];

                print_maker_string_ascii(15,cmm_error_vels[0],cmm_error_message,4);
                cmm_error_timer--;
            }
        break;
        case CMM_MAKE_TOOLBOX:
        for (i=0; i<sizeof(cmm_toolbox); i++) {
            op = 255;
            yoff = 0;
            if (i == cmm_toolbox_index) {
                op = 100;
                yoff = 0;
            }
            xi = i%9;
            yi = i/9;
            create_dl_translation_matrix(MENU_MTX_PUSH, 34+(xi*32), 220-(yi*32), 0);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, op, 255);
            gSPDisplayList(gDisplayListHead++, cmm_ui_buttons[cmm_toolbox[i]].material);//texture
            gSPDisplayList(gDisplayListHead++, &uibutton_button_mesh);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);    
        }

        strx = 54+(cmm_toolbox_index%9)*32;
        stry = 215-(cmm_toolbox_index/9)*32;

        if (cmm_toolbox[cmm_toolbox_index] != CMM_BUTTON_BLANK) {
            //render selection box
            s16 sro = 0;
            if (string_runoff(strx,cmm_ui_buttons[cmm_toolbox[cmm_toolbox_index]].str)) {
                sro = -130;
            }

            create_dl_translation_matrix(MENU_MTX_PUSH, strx-2+sro, stry+16, 0);
            create_dl_scale_matrix(MENU_MTX_NOPUSH, 0.7f, 0.2f, 1.0f);
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
            gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            print_maker_string_ascii(strx+sro, stry ,cmm_ui_buttons[cmm_toolbox[cmm_toolbox_index]].str,TRUE);
            }

        break;

        case CMM_MAKE_SETTINGS:
            //PAINTING
            create_dl_translation_matrix(MENU_MTX_PUSH, 280, 200, 0);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
            gSPDisplayList(gDisplayListHead++, &mat_b_painting);//texture
            gSPDisplayList(gDisplayListHead++, &uibutton_button_mesh);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            //print_maker_string(15,210,txt_btn_2,FALSE);
            print_maker_string_ascii(15,210,cmm_file_info.fname,FALSE);

            for (i=0;i<SETTINGS_SIZE - 1;i++) {
                print_maker_string_ascii(15,180-(i*16),cmm_settings_buttons[i].str,(i==cmm_settings_index));
                print_maker_string_ascii(70,180-(i*16),cmm_settings_buttons[i].nametable[ *cmm_settings_buttons[i].value ],(i==cmm_settings_index));
            }
            // Floor option
            print_maker_string_ascii(15, 180-(i*16), cmm_settings_buttons[i].str, (i==cmm_settings_index));
            if (cmm_lopt_plane == 0) {
                print_maker_string_ascii(70, 180-(i*16), "None", (i==cmm_settings_index));
            } else {
                print_maker_string_ascii(70, 180-(i*16), TILE_MATDEF(cmm_theme_table[cmm_lopt_theme].floors[cmm_lopt_plane - 1]).name, (i==cmm_settings_index));
            }
        break;

        case CMM_MAKE_TRAJECTORY:
            print_maker_string(20,210,cmm_txt_recording,TRUE);
        break;
    }
}

char cmm_mm_keyboard[] = "1234567890abcdefghijklmnopqrstuvwxyz!'- ";
char cmm_mm_keyboard_caps[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ!'- ";
char cmm_mm_keyboard_input[20];
u8 cmm_mm_keyboard_exit_mode = KXM_NEW_LEVEL;
u8 cmm_mm_keyboard_input_index = 0;
#define KEYBOARD_SIZE (sizeof(cmm_mm_keyboard)-1)
s8 cmm_mm_keyboard_index = 0;

char cmm_mm_comingsoon[] = "Coming soon...";
char cmm_mm_warning[] = \
"WARNING!\n\
SD card emulation not detected.\n\
You will still be able to use\n\
the level editor, but you will\n\
not be able to save levels or\n\
download levels from other people.\n\
\n\
Press START to dismiss this message.";

char *cmm_mm_btns[] = {
    "Build",
    "Play",
    "Help",
    "Credits",
};

char *cmm_mm_btns_lim[] = {
    "Build",
    "Help",
    "Credits",
};

char *cmm_mm_play_btns[] = {
    "Play Levels",
    cmm_mm_comingsoon, //"Play Hacks"
};

char *cmm_mm_make_btns[] = {
    "New Level",
    "Load Level",
    cmm_mm_comingsoon, //"New Hack"
    cmm_mm_comingsoon, //"Load Hack"
};

char *cmm_mm_lmode_btns[] = {
    "Vanilla SM64",
    "SM64 BTCM",
};

char *cmm_mm_help_btns[] = {
    "SD Card Setup",
    "Editor Controls",
    "Version Info",
};

u8 cmm_mm_help_page1[] = {TXT_MM_HELP_PAGE_1};
u8 cmm_mm_help_page2[] = {TXT_MM_HELP_PAGE_2};
u8 cmm_mm_help_page3[] = {TXT_MM_HELP_PAGE_3};
u8 cmm_mm_credits_page[] = {TXT_MM_CREDITS_PAGE};

u8 cmm_mm_txt_pages[] = {TXT_MM_PAGE};
u8 cmm_mm_txt_keyboard[] = {TXT_MM_KEYBOARD};

u8 cmm_mm_state = MM_INIT;
u8 cmm_mm_main_state = MM_MAIN;
s8 cmm_mm_index = 0;
s8 cmm_mm_pages = 0;
s8 cmm_mm_page = 0;
s8 cmm_mm_page_entries = 0;
u8 *cmm_mm_help_ptr = NULL;
#define PAGE_SIZE 5

// Position, velocity, acceleration
f32 cmm_menu_button_vels[5][3] = {0.f};
f32 cmm_menu_title_vels[3] = {0.f};
s16 cmm_menu_start_timer = -1;
s16 cmm_menu_end_timer = -1;
s8 cmm_menu_going_back = 1;

void render_cmm_mm_menu(char * strlist[], char *title, u8 ct) {
    create_dl_scale_matrix(MENU_MTX_PUSH, 2.f, 2.f, 0.f);
    print_maker_string_ascii(78 - (get_string_width_ascii(title)/2),95 + cmm_menu_title_vels[0]/2,title,0);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    if ((cmm_mm_state == MM_MAIN) || (cmm_mm_state == MM_MAIN_LIMITED)) {
        print_maker_string_ascii(185, 177 + cmm_menu_title_vels[0], "By Rovertronic", 0);
    }
    cmm_menu_title_vels[0] += cmm_menu_title_vels[1];
    cmm_menu_title_vels[1] += cmm_menu_title_vels[2];

    for (u8 i=0; i<ct; i++) {
        gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
        create_dl_translation_matrix(MENU_MTX_PUSH, cmm_menu_button_vels[i][0] + 160, 150-(i*30), 0);
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 190);
        if (cmm_mm_index == i) {
            gDPSetEnvColor(gDisplayListHead++, 100, 100, 100, 190);
        }
        gSPDisplayList(gDisplayListHead++, &mm_btn2_mm_btn_mesh);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

        u8 grey_add = 0;
        if (strlist[i] == cmm_mm_comingsoon) {
            grey_add = 2;
        }

        print_maker_string_ascii(cmm_menu_button_vels[i][0] + 120,142-(i*30),strlist[i],(cmm_mm_index == i)+grey_add);
        cmm_menu_button_vels[i][0] += cmm_menu_button_vels[i][1];
        cmm_menu_button_vels[i][1] += cmm_menu_button_vels[i][2];
    }
}

// len - number of buttons in menu
// time - how long until actually switching to next menu
// canBack - able to press B to go to previous menu
// returns if menu has switched
u32 cmm_menu_animation_out(s32 len, s32 time, u32 canBack) {
    if (cmm_menu_end_timer == -1) {
        if (cmm_menu_start_timer == -1) {
            if (gPlayer1Controller->buttonPressed & (A_BUTTON|START_BUTTON)) {
                cmm_menu_end_timer = 0;
                cmm_menu_going_back = 1;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
            }
            if (gPlayer1Controller->buttonPressed & (B_BUTTON)) {
                if (canBack) {
                    cmm_menu_end_timer = 0;
                    cmm_menu_going_back = -1;
                    play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                }
            }
        }
        return FALSE;
    }

    if (cmm_menu_end_timer < len*2 && cmm_menu_end_timer % 2 == 0) {
        u8 step = cmm_menu_end_timer/2;
        u8 index;
        if (step == 0) {
            index = cmm_mm_index;
            cmm_menu_title_vels[1] = 0.f;
            cmm_menu_title_vels[2] = 2.f;
        } else {
            index = (step > cmm_mm_index) ? step : step-1;
        }
        cmm_menu_button_vels[index][1] = 20.f * cmm_menu_going_back;
        cmm_menu_button_vels[index][2] = -6.f * cmm_menu_going_back;
    }

    if (++cmm_menu_end_timer == time) {
        cmm_menu_end_timer = -1;
        for (u32 i=0;i<5;i++) {
            cmm_menu_button_vels[i][0] = 250.f * cmm_menu_going_back;
            cmm_menu_button_vels[i][1] = 0.f;
            cmm_menu_button_vels[i][2] = 0.f;
        }
        cmm_menu_title_vels[0] = 50.f;
        cmm_menu_title_vels[1] = 0.f;
        cmm_menu_title_vels[2] = 0.f;
        return TRUE;
    }
    return FALSE;
}

u32 cmm_menu_animation_in(s32 len) {
    if (cmm_menu_start_timer == -1) return FALSE;

    if (cmm_menu_start_timer == 0) {
        cmm_menu_title_vels[1] = -14.f;
        cmm_menu_title_vels[2] = 2.f;
    }
    if (cmm_menu_start_timer < len*2 && cmm_menu_start_timer % 2 == 0) {
        u8 step = cmm_menu_start_timer/2;
        cmm_menu_button_vels[step][1] = -55.f * cmm_menu_going_back;
        cmm_menu_button_vels[step][2] = 6.f * cmm_menu_going_back;
    }
    cmm_menu_start_timer++;
    for (s32 i=0;i<len;i++) {
        if (cmm_menu_button_vels[i][1]*cmm_menu_going_back > 1.f && cmm_menu_button_vels[i][0]*cmm_menu_going_back > 0.f) {
            cmm_menu_button_vels[i][0] = 0.f;
            cmm_menu_button_vels[i][1] = 0.f;
            cmm_menu_button_vels[i][2] = 0.f;
            if (i == len-1) {
                cmm_menu_start_timer = -1;
                return TRUE;
            }
        }
    }
    if (cmm_menu_title_vels[1] > 1.f && cmm_menu_title_vels[0] > 0.f) {
        cmm_menu_title_vels[0] = 0.f;
        cmm_menu_title_vels[1] = 0.f;
        cmm_menu_title_vels[2] = 0.f;
    }
    return FALSE;
}

s32 cmm_main_menu(void) {
    u8 joystick = joystick_direction();
    switch(joystick) {
        case 2:
            cmm_mm_index++;
            play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
        break;
        case 4:
            cmm_mm_index--;
            play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
        break;
    }

    create_dl_ortho_matrix();

    switch(cmm_mm_state) {
        case MM_INIT:
            for (u8 i=0;i<sizeof(cmm_mm_keyboard_input);i++){
                cmm_mm_keyboard_input[i] = '\0';
            }
            if (mount_success == FR_OK) {
                cmm_mm_state = MM_MAIN;
            } else {
                cmm_mm_state = MM_NO_SD_CARD;
                cmm_mm_main_state = MM_MAIN_LIMITED;
            }
            break;
        case MM_NO_SD_CARD:
            shade_screen();
            print_maker_string_ascii(20,210,cmm_mm_warning,FALSE);
            if (gPlayer1Controller->buttonPressed & START_BUTTON) {
                cmm_mm_state = MM_MAIN_LIMITED;
            }
            break;
        case MM_MAIN:
            cmm_mm_index = (cmm_mm_index+4)%4;
            render_cmm_mm_menu(cmm_mm_btns,"Mario Builder 64",4);
            cmm_menu_animation_in(4);
            if (cmm_menu_animation_out(4, 22, FALSE)) {
                switch(cmm_mm_index) {
                    case 0:
                        cmm_mm_state = MM_MAKE;
                        break;
                    case 1:
                        cmm_mm_state = MM_PLAY;
                        break;
                    case 2:
                        cmm_mm_state = MM_HELP_MODE;
                        break;
                    case 3:
                        cmm_mm_state = MM_CREDITS;
                        break;
                }
                cmm_mm_index = 0;
                cmm_menu_start_timer = 0;
            }
            break;
        case MM_MAIN_LIMITED:
            cmm_mm_index = (cmm_mm_index+3)%3;
            render_cmm_mm_menu(cmm_mm_btns_lim,"Mario Builder 64",3);
            if (gPlayer1Controller->buttonPressed & (A_BUTTON|START_BUTTON)) {
                switch(cmm_mm_index) {
                    case 0:
                        return 1;
                    break;
                    case 1:
                        cmm_mm_state = MM_HELP_MODE;
                        cmm_mm_index = 0;
                    break;
                    case 2:
                        cmm_mm_state = MM_CREDITS;
                    break;
                }
            }
            break;
        case MM_PLAY:
            cmm_mm_index = (cmm_mm_index+2)%2;
            render_cmm_mm_menu(cmm_mm_play_btns,"Play Levels",2);
            cmm_menu_animation_in(2);
            if (cmm_menu_animation_out(2, 18, TRUE)) {
                if (cmm_menu_going_back == -1) {
                    cmm_mm_state = cmm_mm_main_state;
                    cmm_mm_index = 1;
                    cmm_menu_start_timer = 0;
                } else {
                    switch(cmm_mm_index) {
                        case 0: //play levels
                            cmm_mm_state = MM_FILES;
                            cmm_mm_index = 0;
                            cmm_menu_start_timer = 0;
                        break;
                        case 1: //play hacks
                            play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                        break;
                    }
                }
            }
            break;
        case MM_MAKE:
            cmm_mm_index = (cmm_mm_index+4)%4;
            render_cmm_mm_menu(cmm_mm_make_btns,"Make Levels",4);
            cmm_menu_animation_in(4);
            if (cmm_menu_animation_out(4, 22, TRUE)) {
                cmm_menu_start_timer = 0;
                if (cmm_menu_going_back == -1) {
                    cmm_mm_state = cmm_mm_main_state;
                    cmm_mm_index = 0;
                } else {
                    switch(cmm_mm_index) {
                        case 0:
                            //make new level
                            cmm_mm_state = MM_MAKE_MODE;
                            break;
                        case 1:
                            //load levels
                            cmm_mm_state = MM_FILES;
                            break;
                        case 2://make new hack
                        case 3://load hack
                            break;
                    }
                    cmm_mm_index = 0;
                }
            }
            break;
        case MM_MAKE_MODE:
            cmm_mm_index = (cmm_mm_index+2)%2;
            render_cmm_mm_menu(cmm_mm_lmode_btns,"Choose Mode",2);
            cmm_menu_animation_in(2);
            if (cmm_menu_animation_out(2, 18, TRUE)) {
                cmm_menu_start_timer = 0;
                if (cmm_menu_going_back == -1) {
                    cmm_mm_state = MM_MAKE;
                    cmm_mm_index = 0;
                } else {
                    cmm_mm_keyboard_exit_mode = KXM_NEW_LEVEL;
                    cmm_mm_state = MM_KEYBOARD;

                    switch(cmm_mm_index) {
                        case 0: //vanilla
                            cmm_lopt_game = 1;
                        break;
                        case 1: //btcm
                            cmm_lopt_game = 0;
                        break;
                    }
                    cmm_mm_index = 0;
                }
            }
            break;
        case MM_HELP_MODE:
            cmm_mm_index = (cmm_mm_index+3)%3;
            render_cmm_mm_menu(cmm_mm_help_btns,"Help",3);
            cmm_menu_animation_in(3);
            if (cmm_menu_animation_out(3, 20, TRUE)) {
                cmm_menu_start_timer = 0;
                if (cmm_menu_going_back == -1) {
                    cmm_mm_state = cmm_mm_main_state;
                    cmm_mm_index = 2;
                } else {
                    cmm_mm_state = MM_HELP;
                    switch(cmm_mm_index) {
                        case 0:
                            cmm_mm_help_ptr = cmm_mm_help_page1;
                        break;
                        case 1:
                            cmm_mm_help_ptr = cmm_mm_help_page2;
                        break;
                        case 2:
                            cmm_mm_help_ptr = cmm_mm_help_page3;
                        break;
                    }
                }
            }
            break;
        case MM_HELP:
            shade_screen();
            print_maker_string(20,210,cmm_mm_help_ptr,FALSE);

            if (cmm_mm_help_ptr == cmm_mm_help_page1) {
                gSPDisplayList(gDisplayListHead++, &pl_scard_pl_scard_mesh);
            }

            if (gPlayer1Controller->buttonPressed & (A_BUTTON|B_BUTTON|START_BUTTON)) {
                cmm_mm_state = MM_HELP_MODE;
                cmm_mm_index = 0;
            }
            break;
        case MM_CREDITS:
            shade_screen();
            print_maker_string(20,210,cmm_mm_credits_page,FALSE);
            if (gPlayer1Controller->buttonPressed & (A_BUTTON|B_BUTTON|START_BUTTON)) {
                cmm_mm_state = cmm_mm_main_state;
                cmm_mm_index = 0;
            }
            break;
        case MM_KEYBOARD:
            switch(joystick) {
                case 1:
                    cmm_mm_keyboard_index--;
                break;
                case 2:
                    cmm_mm_keyboard_index+=10;
                break;
                case 3:
                    cmm_mm_keyboard_index++;
                break;
                case 4:
                    cmm_mm_keyboard_index-=10;
                break;
            }
            cmm_mm_keyboard_index = (cmm_mm_keyboard_index+KEYBOARD_SIZE)%KEYBOARD_SIZE;

            if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                if (gPlayer1Controller->buttonDown & Z_TRIG) {
                    //shift
                    cmm_mm_keyboard_input[cmm_mm_keyboard_input_index] = cmm_mm_keyboard_caps[cmm_mm_keyboard_index];
                } else {
                    cmm_mm_keyboard_input[cmm_mm_keyboard_input_index] = cmm_mm_keyboard[cmm_mm_keyboard_index];
                }
                cmm_mm_keyboard_input_index++;
            }

            if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                if (cmm_mm_keyboard_input_index > 0) {
                    cmm_mm_keyboard_input_index--;
                    cmm_mm_keyboard_input[cmm_mm_keyboard_input_index] = '\0';
                } else {
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
            }

            if (gPlayer1Controller->buttonPressed & START_BUTTON) {
                switch(cmm_mm_keyboard_exit_mode) {
                    case KXM_NEW_LEVEL:
                        bcopy(&cmm_mm_keyboard_input,&cmm_file_name,cmm_mm_keyboard_input_index);
                        //manually add file extension
                        cmm_file_name[cmm_mm_keyboard_input_index+0] = '.';
                        cmm_file_name[cmm_mm_keyboard_input_index+1] = 'm';
                        cmm_file_name[cmm_mm_keyboard_input_index+2] = 'b';
                        cmm_file_name[cmm_mm_keyboard_input_index+3] = '6';
                        cmm_file_name[cmm_mm_keyboard_input_index+4] = '4';
                        cmm_file_name[cmm_mm_keyboard_input_index+5] = '\0';
                        return 1;
                    break;
                }
            }

            if (gPlayer1Controller->buttonPressed & R_TRIG) {
                cmm_mm_state = cmm_mm_main_state;
                cmm_mm_index = 0;
            }

            shade_screen();
            print_maker_string_ascii(35,210,cmm_mm_keyboard_input,FALSE);
            print_maker_string(35,80,cmm_mm_txt_keyboard,FALSE);

            for (u8 i=0; i<(sizeof(cmm_mm_keyboard)-1); i++) {
                u16 x = i%10;
                u16 y = i/10;
                gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
                create_dl_translation_matrix(MENU_MTX_PUSH, 40+(x*25), 190-(y*25), 0);
                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
                if (cmm_mm_keyboard_index == i) {
                    gDPSetEnvColor(gDisplayListHead++, 100, 100, 100, 150);
                }
                gSPDisplayList(gDisplayListHead++, &mm_btn_sm_mm_btn_sm_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
                char single_char[2];
                if (gPlayer1Controller->buttonDown & Z_TRIG) {
                    //shift
                    single_char[0] = cmm_mm_keyboard_caps[i];
                } else {
                    single_char[0] = cmm_mm_keyboard[i];
                }
                single_char[1] = '\0';
                print_maker_string_ascii(37+(x*25),182-(y*25),single_char,(cmm_mm_keyboard_index == i));
            }
            break;
        case MM_FILES:
            if (cmm_level_entry_count == 0) {
                //no levels, do not render anything
                gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
                create_dl_translation_matrix(MENU_MTX_PUSH, 160, 210, 0);
                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
                gSPDisplayList(gDisplayListHead++, &mm_btn_lg_mm_btn_lg_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

                print_maker_string_ascii(55,200,"No levels currently loaded yet.",TRUE);

                if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                    cmm_mm_state = cmm_mm_main_state;
                    cmm_mm_index = 0;
                }
                return 0;
            }

            cmm_mm_index = (cmm_mm_index+cmm_level_entry_count)%cmm_level_entry_count;

            cmm_mm_pages = (cmm_level_entry_count/PAGE_SIZE)+1;
            cmm_mm_page = cmm_mm_index/PAGE_SIZE;
            cmm_mm_page_entries = PAGE_SIZE;
            if (cmm_mm_page == cmm_mm_pages-1) {
                cmm_mm_page_entries = cmm_level_entry_count-(cmm_mm_page*PAGE_SIZE);
            }

            if (gPlayer1Controller->buttonPressed & (A_BUTTON|START_BUTTON)) {
                for (u8 i=0; cmm_level_entries[cmm_mm_index].fname[i] != 0;i++) {
                    cmm_file_name[i] = cmm_level_entries[cmm_mm_index].fname[i];
                }
                return 1;
            }
            if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                cmm_mm_state = cmm_mm_main_state;
                cmm_mm_index = 0;
            }

            for (u8 i=0; i<cmm_mm_page_entries; i++) {
                gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
                create_dl_translation_matrix(MENU_MTX_PUSH, 160, 210-(i*36), 0);
                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
                if (cmm_mm_index-(cmm_mm_page*PAGE_SIZE) == i) {
                    gDPSetEnvColor(gDisplayListHead++, 100, 100, 100, 190);
                }
                gSPDisplayList(gDisplayListHead++, &mm_btn_lg_mm_btn_lg_mesh);

                //render painting
                create_dl_translation_matrix(MENU_MTX_PUSH, -108, -2, 0);
                    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                    gDPPipeSync(gDisplayListHead++);
                    gDPSetCombineLERP(gDisplayListHead++,ENVIRONMENT, 0, TEXEL0, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, TEXEL0, 0, 0, 0, 0, TEXEL0);
                    gSPGeometryMode(gDisplayListHead++,G_ZBUFFER | G_CULL_BACK, 0);
                    gSPTexture(gDisplayListHead++,65535, 65535, 0, 0, 1);
                    gDPSetTextureImage(gDisplayListHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, &cmm_level_entry_piktcher[i+(cmm_mm_page*PAGE_SIZE)]);
                    gSPDisplayList(gDisplayListHead++, &mptng_mptng_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                //


                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
                print_maker_string_ascii(75,200-(i*36),cmm_level_entries[i+(cmm_mm_page*PAGE_SIZE)].fname,(cmm_mm_index == i));
            }

            //render pages
            create_dl_translation_matrix(MENU_MTX_PUSH, 90, 20, 0);
            gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
            gSPDisplayList(gDisplayListHead++, mm_btn2_mm_btn_mesh);
            gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
            int_to_str_slash(cmm_mm_page+1, cmm_mm_pages, (u8 *)&cmm_mm_txt_pages[6]);
            print_maker_string(42,12,cmm_mm_txt_pages,FALSE);
            break;
    }

    return 0;
}