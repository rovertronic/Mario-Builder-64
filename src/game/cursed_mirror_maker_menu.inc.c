extern u8 gDialogCharWidths[256];

u8 cmm_ascii_lut[] = {
    0,0,0,0,0,0,0,0, // 0 - 7
    0,0,0xFE,0,0,0,0,0, // 8 - 15
    0,0,0,0,0,0,0,0, // 16 - 23
    0,0,0,0,0,0,0,0, // 24 - 31
    0x9E, /* */ 0xF2, /*!*/ 0x00, /*"*/ 0x00, /*#*/
    0x00, /*$*/ 0x00, /*%*/ 0x00, /*&*/ 0x3E, /*'*/
    0xE1, /*(*/ 0xE3, /*)*/ 0x00, /***/ 0x00, /*+*/
    0x6F, /*,*/ 0x9F, /*-*/ 0x3F, /*.*/ 0x00, /*/*/
    0x00, /*0*/ 0x01, /*1*/ 0x02, /*2*/ 0x03, /*3*/
    0x04, /*4*/ 0x05, /*5*/ 0x06, /*6*/ 0x07, /*7*/
    0x08, /*8*/ 0x09, /*9*/ 0xE6, /*:*/ 0x00, /*;*/
    0x52, /*<*/ 0x00, /*=*/ 0x53, /*>*/ 0x00, /*?*/
    0x00, /*@*/ 0x0A, /*A*/ 0x0B, /*B*/ 0x0C, /*C*/
    0x0D, /*D*/ 0x0E, /*E*/ 0x0F, /*F*/ 0x10, /*G*/
    0x11, /*H*/ 0x12, /*I*/ 0x13, /*J*/ 0x14, /*K*/
    0x15, /*L*/ 0x16, /*M*/ 0x17, /*N*/ 0x18, /*O*/
    0x19, /*P*/ 0x1A, /*Q*/ 0x1B, /*R*/ 0x1C, /*S*/
    0x1D, /*T*/ 0x1E, /*U*/ 0x1F, /*V*/ 0x20, /*W*/
    0x21, /*X*/ 0x22, /*Y*/ 0x23, /*Z*/ 0x00, /*[*/
    0x00, /*\*/ 0x00, /*]*/ 0x50, /*^*/ 0x00, /*_*/
    0x00, /*`*/ 0x24, /*a*/ 0x25, /*b*/ 0x26, /*c*/
    0x27, /*d*/ 0x28, /*e*/ 0x29, /*f*/ 0x2A, /*g*/
    0x2B, /*h*/ 0x2C, /*i*/ 0x2D, /*j*/ 0x2E, /*k*/
    0x2F, /*l*/ 0x30, /*m*/ 0x31, /*n*/ 0x32, /*o*/
    0x33, /*p*/ 0x34, /*q*/ 0x35, /*r*/ 0x36, /*s*/
    0x37, /*t*/ 0x38, /*u*/ 0x39, /*v*/ 0x3A, /*w*/
    0x3B, /*x*/ 0x3C, /*y*/ 0x3D, /*z*/ 0x00, /*{*/
    0x51, /*|*/ 0x00, /*}*/ 0x00, /*~*/
};

s32 get_string_width_ascii(char *str) {
    s16 strPos = 0;
    s16 width = 0;

    while (str[strPos] != 0) {
        width += gDialogCharWidths[cmm_ascii_lut[(u8)str[strPos]]];
        strPos++;
    }
    return width;
}

u8 string_runoff(s32 x, char *str) {
    s32 x1 = get_string_width_ascii(str);

    if (x+x1 > 320) {
        return TRUE;
    }
    return FALSE;
}

void print_maker_string_ascii(s32 x, s32 y, char *str, s32 highlight) {
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

void print_maker_string_ascii_centered(s32 x, s32 y, char *str, s32 highlight) {
    s32 x1 = get_string_width_ascii(str);
    print_maker_string_ascii(x - x1/2, y, str, highlight);
}

void print_maker_string(s32 x, s32 y, u8 *str, s32 highlight) {
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

void animate_menu_generic(f32 vels[3], f32 beginPos, f32 beginVel, f32 beginAccel, u32 isBegin) {
    if (isBegin) {
        vels[0] = beginPos;
        vels[1] = beginVel;
        vels[2] = beginAccel;
    }
    vels[0] += vels[1];
    vels[1] += vels[2];
}

void animate_menu_overshoot_target(f32 vels[3], f32 targetPos,
                                   f32 beginPos, f32 beginVel, f32 beginAccel, u32 isBegin) {
    animate_menu_generic(vels, beginPos, beginVel, beginAccel, isBegin);
    // Take note of what sign the beginning velocity was.
    // If it's the opposite sign of current velocity,
    // stop animation once it overshoots the target.
    if (beginVel > 0.f && vels[1] < 0.f) {
        if (vels[0] < targetPos) {
            vels[0] = targetPos;
            vels[1] = 0.f;
            vels[2] = 0.f;
        }
    } else if (beginVel < 0.f && vels[1] > 0.f) {
        if (vels[0] > targetPos) {
            vels[0] = targetPos;
            vels[1] = 0.f;
            vels[2] = 0.f;
        }
    }
}

void animate_menu_ease_in(f32 vels[3], f32 beginPos, f32 beginVel, f32 beginAccel, u32 isBegin) {
    animate_menu_generic(vels, beginPos, beginVel, beginAccel, isBegin);
    
    if ((beginVel > 0.f && vels[1] < 0.f) || (beginVel < 0.f && vels[1] > 0.f)) {
        vels[1] = 0.f;
        vels[2] = 0.f;
    }
}

// First value is timer, second is direction
s8 cmm_menu_scrolling[6][2] = {0};

#define GET_BUTTON_STR(btn, index) ((btn).nameFunc ? (btn).nameFunc(index) : (btn).nametable[index])

void cmm_menu_option_animation(s32 x, s32 y, s32 width, struct cmm_settings_button *btn, s32 i, s32 joystick) {
    s32 leftX = x - width * 2;
    s32 rightX = x + width * 2;
    s32 xOffset = 0;
    if (cmm_menu_scrolling[i][0] == 0 && cmm_menu_index == i) {
        if (joystick == 1) {
            cmm_menu_scrolling[i][0] = 5;
            cmm_menu_scrolling[i][1] = -1;
            play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
            *(btn[i].value) = (*(btn[i].value) + btn[i].size - 1) % btn[i].size;
            if (btn[i].changedFunc) cmm_option_changed_func = btn[i].changedFunc;
        } else if (joystick == 3) {
            cmm_menu_scrolling[i][0] = 5;
            cmm_menu_scrolling[i][1] = 1;
            play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
            *(btn[i].value) = (*(btn[i].value) + 1) % btn[i].size;
            if (btn[i].changedFunc) cmm_option_changed_func = btn[i].changedFunc;
        }
    }
    if (cmm_menu_scrolling[i][0] > 0) {
        cmm_menu_scrolling[i][0]--;
        xOffset = (cmm_menu_scrolling[i][0] * cmm_menu_scrolling[i][1] * width * 2) / 5;
        leftX += xOffset;
        rightX += xOffset;
    }

    char *str = GET_BUTTON_STR(btn[i], *(btn[i].value));
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, x-width+5, 0, x+width-7, SCREEN_HEIGHT);
    print_maker_string_ascii_centered(x + xOffset, y, str, cmm_menu_index == i);
    if (leftX > x - width * 2) {
        u8 prevIndex = (*(btn[i].value) - 1 + btn[i].size) % btn[i].size;
        char *prevStr = GET_BUTTON_STR(btn[i], prevIndex);;
        print_maker_string_ascii_centered(leftX, y, prevStr, cmm_menu_index == i);
    } else if (rightX < x + width * 2) {
        u8 nextIndex = (*(btn[i].value) + 1) % btn[i].size;
        char *nextStr = GET_BUTTON_STR(btn[i], nextIndex);
        print_maker_string_ascii_centered(rightX, y, nextStr, cmm_menu_index == i);
    }

    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    print_maker_string_ascii_centered(x - width, y, "<", cmm_menu_index == i);
    print_maker_string_ascii_centered(x + width, y, ">", cmm_menu_index == i);
}

void cmm_render_error_message(void) {
    if (cmm_error_timer > 0) {

        if (cmm_error_timer > 60) {
            animate_menu_ease_in(cmm_error_vels, 280.f, -15.f, 2.f, cmm_error_timer == 120);
        } else if (cmm_error_timer <= 30) {
            animate_menu_generic(cmm_error_vels, cmm_error_vels[0], 0.f, 2.f, cmm_error_timer == 30);
        }

        print_maker_string_ascii(15,cmm_error_vels[0],cmm_error_message,4);
        cmm_error_timer--;
    }
}

char *cmm_get_floor_name(s32 index) {
    if (index == 0) {
        return "None";
    }
    return TILE_MATDEF(cmm_theme_table[cmm_lopt_theme].floors[cmm_lopt_plane - 1]).name;
}
char cmm_temp_name_buffer[12];
char *cmm_get_coinstar_str(s32 index) {
    if (index == 0) {
        return "Disabled";
    }
    sprintf(cmm_temp_name_buffer, "%d Coins", index*20);
    return cmm_temp_name_buffer;
}
char *cmm_get_waterlevel_name(s32 index) {
    if (index == 0) {
        return "Disabled";
    }
    sprintf(cmm_temp_name_buffer, "Y: %d", index);
    return cmm_temp_name_buffer;
}

// Set cmm_lopt_seq_album and cmm_lopt_seq_song based on cmm_lopt_seq
void set_album_and_song_from_seq(void) {
    u32 song = cmm_lopt_seq;
    u32 i = 0;
    do {
        if (song < cmm_settings_music_albums[i].size) {
            cmm_lopt_seq_album = i;
            cmm_lopt_seq_song = song;
            return;
        }
        song -= cmm_settings_music_albums[i].size;
    } while (++i < sizeof(cmm_music_album_string_table));
}
// Set cmm_lopt_seq from cmm_lopt_seq_album and cmm_lopt_seq_song
void set_seq_from_album_and_song(void) {
    cmm_lopt_seq = 0;
    u32 i = 0;
    do {
        if (i == cmm_lopt_seq_album) {
            cmm_lopt_seq += cmm_lopt_seq_song;
            return;
        }
        cmm_lopt_seq += cmm_settings_music_albums[i].size;
    } while (++i < sizeof(cmm_music_album_string_table));
}

void music_category_changed(void) {
    cmm_lopt_seq_song = 0;
    bcopy(&cmm_settings_music_albums[cmm_lopt_seq_album], &cmm_settings_music_buttons[2], sizeof(struct cmm_settings_button));
    song_changed();
}
void song_changed(void) {
    set_seq_from_album_and_song();
    stop_background_music(get_current_background_music());
    play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, seq_musicmenu_array[cmm_lopt_seq]), 0);
}

u8 cmm_curr_settings_menu = 0;

void draw_cmm_settings_general(void) {
    for (s32 i=1;i<ARRAY_COUNT(cmm_settings_general_buttons);i++) {
        print_maker_string_ascii(45,170-(i*16),cmm_settings_general_buttons[i].str,(i==cmm_menu_index));
        cmm_menu_option_animation(190,170-(i*16),60,cmm_settings_general_buttons,i,cmm_joystick);
    }
}

void draw_cmm_settings_terrain(void) {
    for (s32 i=1;i<ARRAY_COUNT(cmm_settings_terrain_buttons);i++) {
        print_maker_string_ascii(45,170-(i*16),cmm_settings_terrain_buttons[i].str,(i==cmm_menu_index));
        cmm_menu_option_animation(190,170-(i*16),60,cmm_settings_terrain_buttons,i,cmm_joystick);
    }
}

void draw_cmm_settings_music(void) {
    for (s32 i=1;i<ARRAY_COUNT(cmm_settings_music_buttons);i++) {
        print_maker_string_ascii(35,170-(i*25),cmm_settings_music_buttons[i].str,(i==cmm_menu_index));
        cmm_menu_option_animation(190,170-(i*25),100,cmm_settings_music_buttons,i,cmm_joystick);
    }
}

extern u8 cmm_mm_state; //externing a variable in the same file that it's defined in? more likely than you think. how heinous.
void draw_cmm_settings_backtomainmenu(void) {
    if (gPlayer1Controller->buttonPressed & (A_BUTTON|START_BUTTON)) {
        load_level_files_from_sd_card();
        cmm_menu_state = CMM_MAKE_MAIN;
        cmm_curr_settings_menu = 0;
        cmm_mm_state = MM_FILES;
        fade_into_special_warp(WARP_SPECIAL_MARIO_HEAD_REGULAR, 0); // reset game
    }
}

void (*cmm_settings_menus[])(void) = {
    draw_cmm_settings_general,
    draw_cmm_settings_terrain,
    draw_cmm_settings_music,
    draw_cmm_settings_backtomainmenu,
};
u8 cmm_settings_menu_lengths[] = {
    ARRAY_COUNT(cmm_settings_general_buttons),
    ARRAY_COUNT(cmm_settings_terrain_buttons),
    ARRAY_COUNT(cmm_settings_music_buttons),
    1,
};

void draw_cmm_menu(void) {
    u16 decor_bar_offset = 36;
    if (cmm_menu_state == CMM_MAKE_SETTINGS) {
        decor_bar_offset = 235;
    }

    if (!cmm_ui_do_render) {
        cmm_ui_do_render = TRUE;
        return;
    }

    create_dl_translation_matrix(MENU_MTX_PUSH, 19, decor_bar_offset, 0);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
    gSPDisplayList(gDisplayListHead++, &bg_back_graund_mesh);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    for (s32 i = 0; i < 9; i++) {
        s32 op = 200;
        s32 yoff = 20;
        if (i == cmm_toolbar_index) {
            op = 255;
            yoff = 25;
        }
        create_dl_translation_matrix(MENU_MTX_PUSH, 34+(i*32), yoff, 0);
        gDPSetEnvColor(gDisplayListHead++, op, op, op, 255);

        Gfx *mat = cmm_ui_buttons[cmm_toolbar[i]].material;
        if (cmm_ui_buttons[cmm_toolbar[i]].multipleBtns) {
            s32 idx = (i == cmm_toolbar_index ? cmm_param_selection : 0);
            mat = ((Gfx **)mat)[idx];
        }

        gSPDisplayList(gDisplayListHead++, mat);//texture
        gSPDisplayList(gDisplayListHead++, &uibutton_button_mesh);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    }
    gSPDisplayList(gDisplayListHead++, &mat_revert_b_btn_check);

    //TOOLBOX
    switch (cmm_menu_state) {
        case CMM_MAKE_MAIN:
            print_maker_string_ascii(15,45,cmm_ui_buttons[cmm_toolbar[cmm_toolbar_index]].str,FALSE);
            if (cmm_ui_buttons[cmm_toolbar[cmm_toolbar_index]].param_strings) {
                print_maker_string_ascii(30+get_string_width_ascii(cmm_ui_buttons[cmm_toolbar[cmm_toolbar_index]].str),45,
                cmm_ui_buttons[cmm_toolbar[cmm_toolbar_index]].param_strings[cmm_param_selection],TRUE);
            } else if (cmm_place_mode == CMM_PM_TILE && cmm_tile_terrains[cmm_id_selection]) {
                print_maker_string_ascii(30+get_string_width_ascii(cmm_ui_buttons[cmm_toolbar[cmm_toolbar_index]].str),45,
                TILE_MATDEF(cmm_mat_selection).name,TRUE);
            }

            cmm_render_error_message();
            break;

        case CMM_MAKE_TOOLBOX:
            for (s32 i = 0; i < (s32)sizeof(cmm_toolbox); i++) {
                s32 op = 255;
                if (i == cmm_toolbox_index) {
                    op = 100;
                }
                s32 xi = i%9;
                s32 yi = i/9;
                create_dl_translation_matrix(MENU_MTX_PUSH, 34+(xi*32), 220-(yi*32), 0);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, op, 255);

                Gfx *mat = cmm_ui_buttons[cmm_toolbox[i]].material;
                if (cmm_ui_buttons[cmm_toolbox[i]].multipleBtns) {
                    mat = ((Gfx **)mat)[0];
                }

                gSPDisplayList(gDisplayListHead++, mat);//texture
                gSPDisplayList(gDisplayListHead++, &uibutton_button_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);    
            }
            gSPDisplayList(gDisplayListHead++, &mat_revert_b_btn_check);

            s32 strx = 54+(cmm_toolbox_index%9)*32;
            s32 stry = 215-(cmm_toolbox_index/9)*32;

            if (cmm_toolbox[cmm_toolbox_index] != CMM_BUTTON_BLANK) {
                //render selection box
                s32 sro = 0;
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
            //gSPDisplayList(gDisplayListHead++, &mat_b_painting);//texture
            gSPDisplayList(gDisplayListHead++, &bigpainting2_bigpainting2_mesh);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            //print_maker_string(15,210,txt_btn_2,FALSE);
            print_maker_string_ascii(15,210,cmm_file_info.fname,FALSE);

            switch(cmm_joystick) {
                case 2:
                    cmm_menu_index++;
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                break;
                case 4:
                    cmm_menu_index--;
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                break;
            }
            cmm_menu_index = (cmm_menu_index + cmm_settings_menu_lengths[cmm_curr_settings_menu]) % cmm_settings_menu_lengths[cmm_curr_settings_menu];

            cmm_menu_option_animation(150,190,40,&cmm_settings_header,0,cmm_joystick);
            cmm_settings_menus[cmm_curr_settings_menu]();
            break;

        case CMM_MAKE_TRAJECTORY:
            print_maker_string(20,210,cmm_txt_recording,TRUE);
            cmm_render_error_message();
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
download levels from other people.";

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
u8 cmm_mm_files_prev_menu;
s8 cmm_mm_pages = 0;
s8 cmm_mm_page = 0;
u8 *cmm_mm_help_ptr = NULL;
#define PAGE_SIZE 5

// Position, velocity, acceleration
f32 cmm_menu_button_vels[10][3] = {0.f};
f32 cmm_menu_title_vels[3] = {0.f};
s16 cmm_menu_start_timer = -1;
s16 cmm_menu_end_timer = -1;
s8 cmm_menu_going_back = 1;

void cmm_mm_shade_screen(void) {

    // This is a bit weird. It reuses the dialog text box (width 130, height -80),
    // so scale to at least fit the screen.
    u8 alpha = 110;
    if (cmm_menu_start_timer != -1) {
        u8 time = MIN(cmm_menu_start_timer, 8);
        alpha = (time * 110) / 8;
    } else if (cmm_menu_end_timer != -1 && !(cmm_mm_state == MM_KEYBOARD && cmm_menu_going_back == 1)) {
        u8 time = MIN(cmm_menu_end_timer, 8);
        alpha = 110 - ((time * 110) / 8);
    }
    create_dl_translation_matrix(MENU_MTX_PUSH, -100.0f, SCREEN_HEIGHT, 0);
    create_dl_scale_matrix(MENU_MTX_NOPUSH, 3.6f, 3.4f, 1.0f);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, alpha);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void render_cmm_mm_button(f32 x, f32 y, u32 highlighted) {
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    create_dl_translation_matrix(MENU_MTX_PUSH, x, y, 0);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 190);
    if (highlighted) {
        gDPSetEnvColor(gDisplayListHead++, 100, 100, 100, 190);
    }
    gSPDisplayList(gDisplayListHead++, &mm_btn2_mm_btn_mesh);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

void render_cmm_mm_menu(char * strlist[], char *title, u8 ct) {
    create_dl_scale_matrix(MENU_MTX_PUSH, 2.f, 2.f, 0.f);
    print_maker_string_ascii(80 - (get_string_width_ascii(title)/2),95 + cmm_menu_title_vels[0]/2,title,0);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    if ((cmm_mm_state == MM_MAIN) || (cmm_mm_state == MM_MAIN_LIMITED)) {
        print_maker_string_ascii(185, 177 + cmm_menu_title_vels[0], "By Rovertronic", 0);
    }

    for (s32 i=0; i<ct; i++) {
        render_cmm_mm_button(cmm_menu_button_vels[i][0] + 160, 150-(i*30), cmm_menu_index == i);

        s32 grey_add = 0;
        if (strlist[i] == cmm_mm_comingsoon) {
            grey_add = 2;
        }

        print_maker_string_ascii_centered(cmm_menu_button_vels[i][0] + 160,142-(i*30),strlist[i],(cmm_menu_index == i)+grey_add);
    }
}

void cmm_mm_reset_all_buttons(f32 pos) {
    for (s32 i=0;i<ARRAY_COUNT(cmm_menu_button_vels);i++) {
        cmm_menu_button_vels[i][0] = pos;
        cmm_menu_button_vels[i][1] = 0.f;
        cmm_menu_button_vels[i][2] = 0.f;
    }
}

void cmm_mm_anim_out_main(s32 len, f32 startvel) {
    animate_menu_generic(cmm_menu_title_vels, 0.f, 0.f, 3.f, cmm_menu_end_timer == 0);

    s32 index = -1;
    if (cmm_menu_end_timer < len*2 && cmm_menu_end_timer % 2 == 0) {
        s32 step = cmm_menu_end_timer/2;
        if (step == 0) {
            index = cmm_menu_index;
        } else {
            index = (step > cmm_menu_index) ? step : step-1;
        }
    }

    for (s32 i = 0; i < len; i++) {
        animate_menu_generic(cmm_menu_button_vels[i], 0.f,
                            startvel*cmm_menu_going_back, -8.f*cmm_menu_going_back,
                            i == index);
    }
}

void cmm_mm_generic_anim_check(s32 canBack) {
    if (cmm_menu_start_timer == -1 || cmm_menu_start_timer > 10) {
        if (gPlayer1Controller->buttonPressed & (A_BUTTON|START_BUTTON)) {
            cmm_menu_end_timer = 0;
            cmm_menu_going_back = 1;
            cmm_menu_start_timer = -1;
            cmm_mm_reset_all_buttons(0.f);
            play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
        }
        if (gPlayer1Controller->buttonPressed & (B_BUTTON)) {
            if (canBack) {
                cmm_menu_end_timer = 0;
                cmm_menu_going_back = -1;
                cmm_menu_start_timer = -1;
                cmm_mm_reset_all_buttons(0.f);
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
            }
        }
    }
}

void cmm_mm_no_files_anim_check(UNUSED s32 canBack) {
    if (cmm_menu_start_timer == -1 || cmm_menu_start_timer > 10) {
        if (gPlayer1Controller->buttonPressed & (B_BUTTON)) {
            cmm_menu_end_timer = 0;
            cmm_menu_going_back = -1;
            cmm_menu_start_timer = -1;
            cmm_mm_reset_all_buttons(0.f);
            play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
        }
    }
}

void cmm_mm_make_anim_check(UNUSED s32 canBack) {
    if (gPlayer1Controller->buttonPressed & (A_BUTTON|START_BUTTON) && (cmm_menu_index != 3)) return;
    cmm_mm_generic_anim_check(TRUE);
}

void cmm_mm_keyboard_anim_check(UNUSED s32 canBack) {
    if (cmm_menu_start_timer == -1) {
        if (gPlayer1Controller->buttonPressed & (START_BUTTON)) {
            cmm_menu_end_timer = 0;
            cmm_menu_going_back = 1;
            play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
        }
        if (gPlayer1Controller->buttonPressed & (R_TRIG)) {
            cmm_menu_end_timer = 0;
            cmm_menu_going_back = -1;
            play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
        }
    }
}

s32 cmm_mm_anim_out(s32 len, s32 canBack, void checkFunc(s32 canBack), f32 startVel) {
    if (cmm_menu_end_timer == -1) {
        checkFunc(canBack);
    } else {
        cmm_mm_anim_out_main(len, startVel);
        if (++cmm_menu_end_timer == 10 + len*2) {
            cmm_menu_end_timer = -1;
            return TRUE;
        }
    }
    return FALSE;
}

s32 cmm_mm_generic_anim_out(s32 len, s32 canBack) {
    return cmm_mm_anim_out(len, canBack, cmm_mm_generic_anim_check, 23.f);
}

s32 cmm_mm_no_files_anim_out(void) {
    return cmm_mm_anim_out(1, TRUE, cmm_mm_no_files_anim_check, 23.f);
}

s32 cmm_mm_keyboard_anim_out(void) {
    return cmm_mm_anim_out(4, TRUE, cmm_mm_keyboard_anim_check, 0.f);
}

u32 cmm_mm_make_anim_out(void) {
    return cmm_mm_anim_out(4, TRUE, cmm_mm_make_anim_check, 23.f);
}

/**
 *     print_maker_string(cmm_menu_title_vels[0],210,cmm_mm_help_ptr,FALSE);

    if (cmm_mm_help_ptr == cmm_mm_help_page1) {
        gSPDisplayList(gDisplayListHead++, &pl_scard_pl_scard_mesh);
    }
*/

s32 cmm_mm_anim_info(void) {
    if (cmm_menu_start_timer != -1) {
        animate_menu_overshoot_target(cmm_menu_title_vels, 20.f, -300.f, 45.f, -3.f, cmm_menu_start_timer == 0);
        cmm_menu_start_timer++;

        if (cmm_menu_start_timer > 10) {
            cmm_menu_start_timer = -1;
        }
    } else if (cmm_menu_end_timer == -1) {
        if (gPlayer1Controller->buttonPressed & (A_BUTTON|B_BUTTON|START_BUTTON)) {
            cmm_menu_end_timer = 0;
            cmm_menu_going_back = -1;
            play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
        }
    } else {
        animate_menu_generic(cmm_menu_title_vels, 20.f, 0.f, -3.f, cmm_menu_end_timer == 0);
        if (cmm_menu_end_timer++ == 10) {
            cmm_menu_end_timer = -1;
            return TRUE;
        }
    }
    return FALSE;
}

#define MENU_ANIM_IN_STARTVEL (cmm_mm_state == MM_KEYBOARD ? -60.f : -63.f)

u32 cmm_mm_anim_in(s32 len) {
    if (cmm_menu_start_timer == -1) return FALSE;

    animate_menu_overshoot_target(cmm_menu_title_vels, 0.f, 50.f, -16.f, 2.5f, cmm_menu_start_timer == 0);

    s8 step = -1;
    if (cmm_menu_start_timer < len*2 && cmm_menu_start_timer % 2 == 0) {
        step = cmm_menu_start_timer/2;
    }

    if (cmm_menu_start_timer == 0) cmm_mm_reset_all_buttons(1000.f);
    for (s32 i=0;i<len;i++) {
        animate_menu_overshoot_target(cmm_menu_button_vels[i], 0.f, 250.f*cmm_menu_going_back, MENU_ANIM_IN_STARTVEL * cmm_menu_going_back, 8.f * cmm_menu_going_back,
        i == step);
    }

    cmm_menu_start_timer++;

    if (cmm_menu_start_timer > len*2 && cmm_menu_button_vels[len-1][2] == 0.f) {
        cmm_menu_start_timer = -1;
        return TRUE;
    }
    return FALSE;
}

s32 cmm_main_menu(void) {
    cmm_joystick = joystick_direction();

    if (cmm_menu_end_timer != -1) {
        cmm_joystick = 0;
    }
    switch(cmm_joystick) {
        case 2:
            cmm_menu_index++;
            play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
        break;
        case 4:
            cmm_menu_index--;
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
                cmm_menu_title_vels[0] = 25.f;
            }
            break;
        case MM_NO_SD_CARD:
            cmm_mm_shade_screen();
            print_maker_string_ascii(cmm_menu_title_vels[0],210,cmm_mm_warning,FALSE);
            if (cmm_mm_anim_info()) {
                cmm_menu_start_timer = 0;
                cmm_mm_state = MM_MAIN_LIMITED;
                cmm_menu_index = 0;
            }
            break;
        case MM_MAIN:
            cmm_menu_index = (cmm_menu_index+4)%4;
            cmm_mm_anim_in(4);
            render_cmm_mm_menu(cmm_mm_btns,"Mario Builder 64",4);
            if (cmm_mm_generic_anim_out(4, FALSE)) {
                switch(cmm_menu_index) {
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
                cmm_menu_index = 0;
                cmm_menu_start_timer = 0;
            }
            break;
        case MM_MAIN_LIMITED:
            cmm_menu_index = (cmm_menu_index+3)%3;
            cmm_mm_anim_in(3);
            render_cmm_mm_menu(cmm_mm_btns_lim,"Mario Builder 64",3);
            if (cmm_mm_generic_anim_out(3, FALSE)) {
                switch(cmm_menu_index) {
                    case 0:
                        cmm_mm_state = MM_MAKE_MODE;
                        break;
                    case 1:
                        cmm_mm_state = MM_HELP_MODE;
                        break;
                    case 2:
                        cmm_mm_state = MM_CREDITS;
                        break;
                }
                cmm_menu_index = 0;
                cmm_menu_start_timer = 0;
            }
            break;
        case MM_PLAY:
            cmm_menu_index = (cmm_menu_index+2)%2;
            cmm_mm_anim_in(2);
            render_cmm_mm_menu(cmm_mm_play_btns,"Play Levels",2);
            if (cmm_mm_generic_anim_out(2, TRUE)) {
                if (cmm_menu_going_back == -1) {
                    cmm_mm_state = cmm_mm_main_state;
                    cmm_menu_index = 1;
                    cmm_menu_start_timer = 0;
                } else {
                    switch(cmm_menu_index) {
                        case 0: //play levels
                            cmm_mm_files_prev_menu = MM_PLAY;
                            cmm_level_action = CMM_LA_PLAYING;
                            cmm_mm_state = MM_FILES;
                            cmm_menu_index = 0;
                            cmm_mm_page = 0;
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
            cmm_menu_index = (cmm_menu_index+4)%4;
            cmm_mm_anim_in(4);
            render_cmm_mm_menu(cmm_mm_make_btns,"Make Levels",4);
            if (cmm_mm_generic_anim_out(4, TRUE)) {
                cmm_menu_start_timer = 0;
                if (cmm_menu_going_back == -1) {
                    cmm_mm_state = cmm_mm_main_state;
                    cmm_menu_index = 0;
                } else {
                    switch(cmm_menu_index) {
                        case 0:
                            //make new level
                            cmm_mm_state = MM_MAKE_MODE;
                            break;
                        case 1:
                            //load levels
                            cmm_mm_files_prev_menu = MM_MAKE;
                            cmm_level_action = CMM_LA_MAKING;
                            cmm_target_mode = CMM_MODE_MAKE;
                            cmm_mm_state = MM_FILES;
                            cmm_mm_page = 0;
                            break;
                        case 2://make new hack
                        case 3://load hack
                            break;
                    }
                    cmm_menu_index = 0;
                }
            }
            break;
        case MM_MAKE_MODE:
            cmm_menu_index = (cmm_menu_index+4)%4;
            cmm_mm_anim_in(4);
            u16 x,y;

            create_dl_scale_matrix(MENU_MTX_PUSH, 2.f, 2.f, 0.f);

            char *title = "Level Settings";
            print_maker_string_ascii(78 - (get_string_width_ascii(title)/2),95 + cmm_menu_title_vels[0]/2,title,0);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            for (s32 i=0; i<3; i++) {
                x = cmm_menu_button_vels[i][0] + 160;
                y = 150-(i*27);
                print_maker_string_ascii_centered(x - 60, y, cmm_mode_settings_buttons[i].str,0);
                render_cmm_mm_button(x + 20, y + 8, cmm_menu_index == i);
                cmm_menu_option_animation(x + 20, y, 43, cmm_mode_settings_buttons, i, cmm_joystick);
            }
            x = cmm_menu_button_vels[3][0] + 160;
            y = 150-(4*27);
            render_cmm_mm_button(x, y + 8, cmm_menu_index == 3);
            print_maker_string_ascii_centered(x, y, "Create!",(cmm_menu_index == 3));


            if (cmm_mm_make_anim_out()) {
                cmm_menu_start_timer = 0;

                if (cmm_mm_main_state == MM_MAIN_LIMITED) {
                    if (cmm_menu_going_back == -1) {
                        cmm_mm_state = MM_MAIN_LIMITED;
                        cmm_menu_index = 0;
                    }
                } else {
                    if (cmm_menu_going_back == -1) {
                        cmm_mm_state = MM_MAKE;
                        cmm_menu_index = 0;
                    } else {
                        cmm_mm_keyboard_exit_mode = KXM_NEW_LEVEL;
                        cmm_mm_state = MM_KEYBOARD;
                        cmm_menu_index = 0;
                    }
                }
            }
            if (cmm_mm_main_state == MM_MAIN_LIMITED && cmm_menu_end_timer == 0 && cmm_menu_going_back == 1) return 1;
            break;
        case MM_HELP_MODE:
            cmm_menu_index = (cmm_menu_index+3)%3;
            cmm_mm_anim_in(3);
            render_cmm_mm_menu(cmm_mm_help_btns,"Help",3);
            if (cmm_mm_generic_anim_out(3, TRUE)) {
                cmm_menu_start_timer = 0;
                if (cmm_menu_going_back == -1) {
                    cmm_mm_state = cmm_mm_main_state;
                    cmm_menu_index = 2;
                } else {
                    cmm_mm_state = MM_HELP;
                    switch(cmm_menu_index) {
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
            cmm_mm_shade_screen();
            if (cmm_mm_anim_info()) {
                cmm_menu_start_timer = 0;
                cmm_mm_state = MM_HELP_MODE;
                cmm_menu_index = 0;
            }
            print_maker_string(cmm_menu_title_vels[0],210,cmm_mm_help_ptr,FALSE);

            if (cmm_mm_help_ptr == cmm_mm_help_page1) {
                gSPDisplayList(gDisplayListHead++, &pl_scard_pl_scard_mesh);
            }
            break;
        case MM_CREDITS:
            cmm_mm_shade_screen();
            if (cmm_mm_anim_info()) {
                cmm_menu_start_timer = 0;
                cmm_mm_state = cmm_mm_main_state;
                cmm_menu_index = 3;
            }
            print_maker_string(cmm_menu_title_vels[0],210,cmm_mm_credits_page,FALSE);
            break;
        case MM_KEYBOARD:
            cmm_mm_anim_in(4);
            switch(cmm_joystick) {
                case 1:
                    cmm_mm_keyboard_index--;
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                break;
                case 2:
                    cmm_mm_keyboard_index+=10;
                break;
                case 3:
                    cmm_mm_keyboard_index++;
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                break;
                case 4:
                    cmm_mm_keyboard_index-=10;
                break;
            }
            cmm_mm_keyboard_index = (cmm_mm_keyboard_index+KEYBOARD_SIZE)%KEYBOARD_SIZE;

            if ((gPlayer1Controller->buttonPressed & A_BUTTON)&&(cmm_mm_keyboard_input_index < 20)) {
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

            if (cmm_mm_keyboard_anim_out()) {
                cmm_menu_start_timer = 0;
                if (cmm_menu_going_back == -1) {
                    cmm_mm_state = MM_MAKE_MODE;
                    cmm_menu_index = 0;
                }
            }

            cmm_mm_shade_screen();
            print_maker_string_ascii(35,210,cmm_mm_keyboard_input,FALSE);
            print_maker_string(35 - cmm_menu_title_vels[0],80,cmm_mm_txt_keyboard,FALSE);

            for (u8 i=0; i<(sizeof(cmm_mm_keyboard)-1); i++) {
                u16 x = i%10;
                u16 y = i/10;
                gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
                create_dl_translation_matrix(MENU_MTX_PUSH, 40+(x*25)+cmm_menu_button_vels[y][0], 190-(y*25), 0);
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
                print_maker_string_ascii(37+(x*25)+cmm_menu_button_vels[y][0],182-(y*25),single_char,(cmm_mm_keyboard_index == i));
            }

            if (cmm_menu_end_timer == 0 && cmm_menu_going_back == 1) {
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
            break;
        case MM_FILES:
            cmm_mm_anim_in(5);
            if (cmm_level_entry_count == 0) {
                //no levels, do not render anything
                gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
                create_dl_translation_matrix(MENU_MTX_PUSH, 160 + cmm_menu_button_vels[0][0], 210, 0);
                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
                gSPDisplayList(gDisplayListHead++, &mm_btn_lg_mm_btn_lg_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

                print_maker_string_ascii(55 + cmm_menu_button_vels[0][0],200,"No levels currently loaded yet.",TRUE);
                if (cmm_mm_no_files_anim_out()) {
                    cmm_menu_start_timer = 0;
                    if (cmm_menu_going_back == -1) {
                        cmm_mm_state = cmm_mm_files_prev_menu;
                        cmm_menu_index = (cmm_mm_state == MM_PLAY ? 0 : 1);
                        break;
                    }
                }
                return 0;
            }

            cmm_menu_index = (cmm_menu_index+cmm_level_entry_count)%cmm_level_entry_count;

            cmm_mm_pages = ((cmm_level_entry_count - 1)/PAGE_SIZE)+1;

            s32 oldPage = cmm_mm_page;
            cmm_mm_page = cmm_menu_index/PAGE_SIZE;

            if (oldPage == cmm_mm_page + 1) {
                cmm_menu_scrolling[0][0] = 9;
                cmm_menu_scrolling[0][1] = -1;
            } else if (oldPage == cmm_mm_page - 1) {
                cmm_menu_scrolling[0][0] = 9;
                cmm_menu_scrolling[0][1] = 1;
            }

            s32 tempindex = cmm_menu_index;
            cmm_menu_index -= cmm_mm_page*PAGE_SIZE; // horrible code to fix animation
            if (cmm_mm_generic_anim_out(5, TRUE)) {
                cmm_menu_start_timer = 0;
                if (cmm_menu_going_back == -1) {
                    cmm_mm_state = cmm_mm_files_prev_menu;
                    cmm_menu_index = (cmm_mm_state == MM_PLAY ? 0 : 1);
                    break;
                }
            }
            cmm_menu_index = tempindex;

            s32 startRenderY = 210;
            s32 startRenderIndex = cmm_mm_page * PAGE_SIZE;
            s32 numPagesRender = PAGE_SIZE;
            s32 indexOffset = 0;

            if (cmm_menu_scrolling[0][0] > 0) {
                if (cmm_menu_scrolling[0][1] == 1) {
                    startRenderY = 210 + ((9-cmm_menu_scrolling[0][0]) * 20);
                    numPagesRender += PAGE_SIZE;
                    startRenderIndex -= PAGE_SIZE;
                    indexOffset = PAGE_SIZE;
                } else {
                    startRenderY = 210 + (cmm_menu_scrolling[0][0] * 20);
                    numPagesRender += PAGE_SIZE;
                }
                cmm_menu_scrolling[0][0]--;
            }
            numPagesRender = MIN(numPagesRender, cmm_level_entry_count - startRenderIndex);

            gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 15, SCREEN_WIDTH, SCREEN_HEIGHT - 45);

            for (s32 i=0; i<numPagesRender; i++) {
                s32 xPosAnim = 0;
                s32 renderIndex = i - indexOffset;
                s32 selectedIndex = cmm_menu_index -(cmm_mm_page*PAGE_SIZE);
                if (renderIndex >= 0 && renderIndex < PAGE_SIZE) {
                    xPosAnim = cmm_menu_button_vels[renderIndex][0];
                }
                gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
                create_dl_translation_matrix(MENU_MTX_PUSH, 160 + xPosAnim, startRenderY-(i*36), 0);
                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
                if (selectedIndex == renderIndex) {
                    gDPSetEnvColor(gDisplayListHead++, 100, 100, 100, 190);
                }
                gSPDisplayList(gDisplayListHead++, &mm_btn_lg_mm_btn_lg_mesh);

                //render painting
                create_dl_translation_matrix(MENU_MTX_PUSH, -108, -2, 0);
                    //gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                    //gDPPipeSync(gDisplayListHead++);
                    //gDPSetCombineLERP(gDisplayListHead++,ENVIRONMENT, 0, TEXEL0, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, TEXEL0, 0, 0, 0, 0, TEXEL0);
                    //gSPGeometryMode(gDisplayListHead++,G_ZBUFFER | G_CULL_BACK, 0);
                    //gSPTexture(gDisplayListHead++,65535, 65535, 0, 0, 1);
                    gSPDisplayList(gDisplayListHead++, &bigpainting_bigpainting_mesh_part1);
                    gDPLoadSync(gDisplayListHead++);
                    gDPSetTextureImage(gDisplayListHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, &cmm_level_entry_piktcher[startRenderIndex + i]);
                    gSPDisplayList(gDisplayListHead++, &bigpainting_bigpainting_mesh_part2);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                //


                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
                print_maker_string_ascii(75 + xPosAnim,startRenderY - 10 -(i*36),cmm_level_entries[startRenderIndex + i].fname,(selectedIndex == renderIndex));
            }

            gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

            //render pages
            create_dl_translation_matrix(MENU_MTX_PUSH, 90, 20 - cmm_menu_title_vels[0], 0);
            gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
            gSPDisplayList(gDisplayListHead++, mm_btn2_mm_btn_mesh);
            gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
            int_to_str_slash(cmm_mm_page+1, cmm_mm_pages, (u8 *)&cmm_mm_txt_pages[6]);
            print_maker_string(42,12 - cmm_menu_title_vels[0],cmm_mm_txt_pages,FALSE);

            if (cmm_menu_end_timer == 1 && cmm_menu_going_back == 1) {
                cmm_mode = CMM_MODE_UNINITIALIZED;
                reset_play_state();
                int i = 0;
                while(cmm_level_entries[cmm_menu_index].fname[i]) {
                    cmm_file_name[i] = cmm_level_entries[cmm_menu_index].fname[i];
                    i++;
                }
                cmm_file_name[i] = 0; // add null terminator
                return 1;
            }

            break;
    }

    return 0;
}