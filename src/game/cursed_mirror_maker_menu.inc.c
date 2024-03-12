extern u8 gDialogCharWidths[256];

u8 cmm_ascii_lut[] = {
    0,0,0,0,0,0,0,0, // 0 - 7
    0,0,0xFE,0,0,0,0,0, // 8 - 15
    0x54,0x55,0x57,0x58,0,0,0,0, // 16 - 23
    0,0,0,0,0,0,0,0, // 24 - 31
    0x9E, /* */ 0xF2, /*!*/ 0x00, /*"*/ 0x00, /*#*/
    0x00, /*$*/ 0x00, /*%*/ 0xE5, /*&*/ 0x3E, /*'*/
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

// Position, velocity, acceleration
f32 cmm_menu_button_vels[10][3] = {0.f};
f32 cmm_menu_title_vels[3] = {0.f};
s16 cmm_menu_start_timer = -1;
s16 cmm_menu_end_timer = -1;
s8 cmm_menu_going_back = 1;

s8 cmm_mm_selected_level = 0;
u8 cmm_greyed_text = FALSE;

u16 cmm_konami_code[] = {
    U_JPAD, U_JPAD, D_JPAD, D_JPAD, L_JPAD, R_JPAD, L_JPAD, R_JPAD, B_BUTTON, A_BUTTON, START_BUTTON
};
u16 cmm_konami_code_cur_index = 0;

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
    if (cmm_greyed_text) highlight += 2;
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

void print_generic_string_ascii_centered(s32 x, s32 y, char *str) {
    s32 x1 = get_string_width_ascii(str);
    print_generic_string_ascii(x - x1/2, y, str);
}

char fileextsample[] = ".mb64"; //slightly cursed
void print_generic_string_ascii_centered_nofileext(s32 x, s32 y, char *str) {
    s32 x1 = get_string_width_ascii(str) - get_string_width_ascii(fileextsample);
    print_generic_string_ascii_nofileext(x - x1/2, y, str);
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

f32 cmm_menu_toolbar_offsets[9];
f32 cmm_menu_list_offsets[45];

void animate_list_offset_reset(f32 offsets[], s32 length) {
    for (s32 i = 0; i < length; i++) {
        offsets[i] = 0.f;
    }
}
void animate_list_reset() {
    animate_list_offset_reset(cmm_menu_list_offsets, ARRAY_COUNT(cmm_menu_list_offsets));
}
void animate_toolbar_reset() {
    animate_list_offset_reset(cmm_menu_toolbar_offsets, ARRAY_COUNT(cmm_menu_toolbar_offsets));
}

void animate_list_update(f32 offsets[], s32 length, s32 selectedIndex) {
    for (s32 i = 0; i < length; i++) {
        if (i == selectedIndex) {
            offsets[i] = approach_f32_asymptotic(offsets[i], 0.99f, 0.3f);
        } else {
            offsets[i] = approach_f32_asymptotic(offsets[i], 0.f, 0.3f);
        }
    }
}

// First value is timer, second is direction
s8 cmm_menu_scrolling[15][2] = {0};
// Controls saved scissor positions for nested scissoring
u8 cmm_global_scissor = 0;
u8 cmm_global_scissor_top = 0;
u8 cmm_global_scissor_bottom = SCREEN_HEIGHT;
u8 cmm_curr_settings_menu = 0; // Index of current page in the Settings menu
u8 cmm_curr_custom_tab = 0; // Index of current tab in Edit Custom Theme menu
u8 cmm_custom_theme_menu_open = FALSE; // If custom theme menu is currently in use

void full_menu_reset() {
    bzero(cmm_menu_button_vels, sizeof(cmm_menu_button_vels));
    bzero(cmm_menu_title_vels, sizeof(cmm_menu_title_vels));
    bzero(cmm_topleft_vels, sizeof(cmm_topleft_vels));
    bzero(cmm_menu_scrolling, sizeof(cmm_menu_scrolling));
    cmm_menu_start_timer = -1;
    cmm_menu_end_timer = -1;
    cmm_menu_going_back = 1;
    cmm_curr_settings_menu = 0;
    cmm_curr_custom_tab = 0;
    cmm_global_scissor = 0;
    cmm_global_scissor_top = 0;
    cmm_global_scissor_bottom = SCREEN_HEIGHT;
    cmm_menu_index = 0;
    cmm_menu_index_max = 1;
    cmm_tip_timer = 0;
    cmm_topleft_timer = 0;
    cmm_konami_code_cur_index = 0;
    cmm_custom_theme_menu_open = FALSE;
    cmm_greyed_text = FALSE;
    animate_list_reset();
    animate_toolbar_reset();
}

// sets some stuff after exiting play mode into the file selector
void cmm_init_exit_to_files() {
    cmm_menu_start_timer = 0;
    cmm_mode = CMM_MODE_UNINITIALIZED;
    cmm_menu_index = cmm_mm_selected_level;
    cmm_lopt_template = 0;
    cmm_lopt_size = 0;
    cmm_lopt_game = CMM_GAME_VANILLA;
}

// Base generic animation for a menu component using acceleration
void animate_menu_generic(f32 vels[3], f32 beginPos, f32 beginVel, f32 beginAccel, u32 isBegin) {
    if (isBegin) {
        vels[0] = beginPos;
        vels[1] = beginVel;
        vels[2] = beginAccel;
    }
    vels[0] += vels[1];
    vels[1] += vels[2];
}

// This animation goes past its target pos, then comes back
// and immediately halts when it reaches the target pos again
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

// Ease-in animation to a target position
void animate_menu_ease_in(f32 vels[3], f32 beginPos, f32 targetPos, f32 multiplier, u32 isBegin) {
    if (isBegin) {
        vels[0] = beginPos;
        vels[1] = 0.f;
        vels[2] = 0.f;
    }
    f32 remainingDist = targetPos - vels[0];
    vels[0] += remainingDist * multiplier;

    if (remainingDist > 0.f) {
        if (vels[0] > targetPos-1.f) {
            vels[0] = targetPos;
        }
    } else {
        if (vels[0] < targetPos+1.f) {
            vels[0] = targetPos;
        }
    }
}

// Generic function for handling the animation of a list of strings
// that can be cycled through in either direction, using a scissor
// to keep the list centered on the screen.

// X/Y - Position
// Width - How long the scissor is
// Prev/Cur/Next - Text strings for handling side options
// Scroll - Pointer to info array for scrolling
// Highlight - Display as yellow
// Dir - 1 for inputting right, -1 for inputting left

// Returns -1 if option was scrolled right, 1 if scrolled left, 0 if not changed
s32 cmm_menu_option_sidescroll(s32 x, s32 y, s32 width,
                                char *prev, char *cur, char *next,
                                s8 scroll[2], u32 highlight, u32 dir) {
    s32 leftX = x - width * 2;
    s32 rightX = x + width * 2;
    s32 xOffset = 0;

    if (scroll[0] > 0) {
        scroll[0]--;
        xOffset = (scroll[0] * scroll[1] * width * 2) / 5;
        leftX += xOffset;
        rightX += xOffset;
    }

    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE,
        MAX(               cmm_global_scissor, x-width+5), cmm_global_scissor_top,
        MIN(SCREEN_WIDTH - cmm_global_scissor, x+width-7), cmm_global_scissor_bottom);
    
    print_maker_string_ascii_centered(x + xOffset, y, cur, highlight);
    if (leftX > x - width * 2) {
        print_maker_string_ascii_centered(leftX, y, prev, highlight);
    } else if (rightX < x + width * 2) {
        print_maker_string_ascii_centered(rightX, y, next, highlight);
    }

    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, cmm_global_scissor, cmm_global_scissor_top, SCREEN_WIDTH - cmm_global_scissor, cmm_global_scissor_bottom);

    if (scroll[0] == 0) {
        if (dir == -1) {
            scroll[0] = 5;
            scroll[1] = -1;
            return -1;
        } else if (dir == 1) {
            scroll[0] = 5;
            scroll[1] = 1;
            return 1;
        }
    }
    return 0;
}


// More specialised version that handles a list of cmm_settings_buttons
// and is scrolled with the joystick
#define GET_BUTTON_STR(btn, index, buf) ((btn)->nameFunc ? (btn)->nameFunc(index, buf) : (btn)->nametable[index])

void cmm_menu_option_animation(s32 x, s32 y, s32 width, struct cmm_settings_button *btn, s32 i, s32 joystick) {
    s32 dir = 0;
    s32 selected = (i == cmm_menu_index);
    if (selected) {
        if (joystick == 1) dir = -1;
        if (joystick == 3) dir = 1;
    }
    s32 currentVal = *(btn->value);

    s32 prevVal = (currentVal + btn->size - 1) % btn->size;
    s32 nextVal = (currentVal + 1) % btn->size;

    char charbuffers[3][20];
    char *cur = GET_BUTTON_STR(btn, currentVal, charbuffers[0]);
    char *prev = GET_BUTTON_STR(btn, prevVal, charbuffers[1]);
    char *next = GET_BUTTON_STR(btn, nextVal, charbuffers[2]);

    s32 result = cmm_menu_option_sidescroll(x, y, width,
                               prev, cur, next,
                               cmm_menu_scrolling[i], selected, dir);

    print_maker_string_ascii_centered(x - width, y, "<", selected);
    print_maker_string_ascii_centered(x + width, y, ">", selected);

    if (result) {
        *(btn->value) = (result == 1 ? nextVal : prevVal);
        play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
        if (btn->changedFunc) cmm_option_changed_func = btn->changedFunc;
    }
}

#define SETTINGS_MENU_SCROLL_WIDTH 140
typedef void (*cmm_page_display_func)(f32 xPos, f32 yPos);

void cmm_menu_page_animation(f32 yoff, void pageFunc(u32, f32, f32), s32 index, s32 pageCount, s8 scroll[2]) {
    s32 prevIndex = index - 1;
    s32 nextIndex = index + 1;
    if (prevIndex < 0) prevIndex = pageCount - 1;
    if (nextIndex >= pageCount) nextIndex = 0;

    s32 leftX = -SETTINGS_MENU_SCROLL_WIDTH * 2;
    s32 rightX = SETTINGS_MENU_SCROLL_WIDTH * 2;
    s32 xOffset = 0;

    if (scroll[0] > 0) {
        xOffset = (scroll[0] * scroll[1] * SETTINGS_MENU_SCROLL_WIDTH * 2) / 5;
        leftX += xOffset;
        rightX += xOffset;
    }

    if (leftX > -SETTINGS_MENU_SCROLL_WIDTH * 2) {
        pageFunc(prevIndex, leftX, yoff);

    } else if (rightX < SETTINGS_MENU_SCROLL_WIDTH * 2) {
        pageFunc(nextIndex, rightX, yoff);
    }

    pageFunc(index, xOffset, yoff);
}

void cmm_render_topleft_text(void) {
    if (cmm_topleft_timer > 0) {

        if (cmm_topleft_timer > 30) {
            animate_menu_ease_in(cmm_topleft_vels, 250.f, 215.f, 0.4f, cmm_topleft_timer == cmm_topleft_max_timer);
        } else {
            animate_menu_generic(cmm_topleft_vels, 215.f, 0.f, 2.f, cmm_topleft_timer == 30);
        }

        print_maker_string_ascii(15,cmm_topleft_vels[0],cmm_topleft_message,cmm_topleft_is_tip ? 0 : 4);
        cmm_topleft_timer--;
    }
}

char *cmm_get_floor_name(s32 index, UNUSED char *buffer) {
    return TILE_MATDEF(index).name;
}
char *cmm_get_coinstar_str(s32 index, char *buffer) {
    if (index == 0) {
        return "Disabled";
    }
    sprintf(buffer, "%d Coins", index*20);
    return buffer;
}
char *cmm_get_waterlevel_name(s32 index, char *buffer) {
    if (index == 0) {
        return "Disabled";
    }
    sprintf(buffer, "Y: %d", index);
    return buffer;
}
char *cmm_get_boundaryheight_name(s32 index, char *buffer) {
    sprintf(buffer, "Y: %d", index);
    return buffer;
}
char *cmm_get_category(s32 index, UNUSED char *buffer) {
    return cmm_matlist_names[index];
}
char *cmm_get_custom_mat(s32 index, char *buffer) {
    s32 category = *cmm_settings_mat_selector[0].value; // very hacky lmfao
    return cmm_mat_table[cmm_matlist[category] + index].name;
}

#define CMM_NUM_CUSTOM_TABS 14
char *cmm_custom_get_menu_name(s32 index) {
    if (index < 10) return cmm_theme_table[CMM_THEME_CUSTOM].mats[index].name;
    switch (index - 10) {
        case 0: return "Poles";
        case 1: return "Fences";
        case 2: return "Iron Meshes";
        case 3: return "Water";
    }
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
    } while (++i < ARRAY_COUNT(cmm_music_album_string_table));
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
    } while (++i < ARRAY_COUNT(cmm_music_album_string_table));
}

// Set category and material index from a material enum
void get_category_and_mat_from_mat(u8 *category, u8 *matIndex, u8 mat) {
    u8 i = 1;
    do {
        if (mat < cmm_matlist[i]) {
            *category = i-1;
            *matIndex = mat - cmm_matlist[i-1];
            return;
        }
    } while (++i < ARRAY_COUNT(cmm_matlist));
}

void music_category_changed(void) {
    cmm_lopt_seq_song = 0;
    song_changed();
    cmm_set_data_overrides();
}
void song_changed(void) {
    set_seq_from_album_and_song();
    stop_background_music(get_current_background_music());
    play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, seq_musicmenu_array[cmm_lopt_seq]), 0);
}

void cmm_set_data_overrides(void) {
    // Music options
    set_album_and_song_from_seq();
    bcopy(&cmm_settings_music_albums[cmm_lopt_seq_album], &cmm_settings_music_buttons[MUSIC_SONG_INDEX], sizeof(struct cmm_settings_button));

    // Secret unlock
    if (cmm_lopt_secret) {
        cmm_settings_env_buttons[ENV_THEME_INDEX].size = ARRAY_COUNT(cmm_theme_string_table);
    } else {
        cmm_settings_env_buttons[ENV_THEME_INDEX].size = ARRAY_COUNT(cmm_theme_string_table) - 1;
    }

    // Custom theme
    if (cmm_lopt_theme == CMM_THEME_CUSTOM) {
        cmm_settings_menu_lengths[SETTINGS_ENV_INDEX] = ARRAY_COUNT(cmm_settings_env_buttons) + 1; // Terrain menu length for selecting
    } else {
        cmm_settings_menu_lengths[SETTINGS_ENV_INDEX] = ARRAY_COUNT(cmm_settings_env_buttons);
    }

    // Theme-specific data
    bzero(&cmm_toolbox_params, sizeof(cmm_toolbox_params));
    switch(cmm_lopt_game) {
        case CMM_GAME_BTCM:
            bcopy(&cmm_toolbox_btcm,&cmm_toolbox,sizeof(cmm_toolbox));
            cmm_exclamation_box_contents = sExclamationBoxContents_btcm;
            cmm_settings_menu_lengths[SETTINGS_MISC_INDEX] = ARRAY_COUNT(cmm_settings_misc_buttons); // includes costume
            cmm_settings_menus[SETTINGS_MISC_INDEX] = draw_cmm_settings_misc;
            break;
        case CMM_GAME_VANILLA:
            bcopy(&cmm_toolbox_vanilla,&cmm_toolbox,sizeof(cmm_toolbox));
            cmm_exclamation_box_contents = sExclamationBoxContents_vanilla;
            cmm_settings_menu_lengths[SETTINGS_MISC_INDEX] = ARRAY_COUNT(cmm_settings_misc_buttons_vanilla); // no costume
            cmm_settings_menus[SETTINGS_MISC_INDEX] = draw_cmm_settings_misc_vanilla;
            break;
    }
}

#define SCROLL_CUSTOM_TABS 12
#define SCROLL_CUSTOM 13
#define SCROLL_SETTINGS 14
#define CMM_SETTINGS_MENU_IS_STILL  ((cmm_menu_scrolling[SCROLL_SETTINGS][0] == 0) && (cmm_menu_start_timer == -1))

void draw_cmm_settings_misc(f32 xoff, f32 yoff) {
    animate_list_update(cmm_menu_list_offsets, ARRAY_COUNT(cmm_settings_misc_buttons), cmm_menu_index);
    for (s32 i=0;i<ARRAY_COUNT(cmm_settings_misc_buttons);i++) {
        print_maker_string_ascii( 55 +xoff+3*cmm_menu_list_offsets[i],154-(i*16)+yoff,cmm_settings_misc_buttons[i].str,(i==cmm_menu_index));
        cmm_menu_option_animation(200+xoff+3*cmm_menu_list_offsets[i],154-(i*16)+yoff,60,&cmm_settings_misc_buttons[i],i,cmm_joystick);
    }
}

void draw_cmm_settings_misc_vanilla(f32 xoff, f32 yoff) {
    animate_list_update(cmm_menu_list_offsets, ARRAY_COUNT(cmm_settings_misc_buttons_vanilla), cmm_menu_index);
    for (s32 i=0;i<ARRAY_COUNT(cmm_settings_misc_buttons_vanilla);i++) {
        print_maker_string_ascii(55+xoff+3*cmm_menu_list_offsets[i],154-(i*16)+yoff,cmm_settings_misc_buttons_vanilla[i].str,(i==cmm_menu_index));
        cmm_menu_option_animation(200+xoff+3*cmm_menu_list_offsets[i],154-(i*16)+yoff,60,&cmm_settings_misc_buttons_vanilla[i],i,cmm_joystick);
    }
}

void draw_cmm_settings_boundary(f32 xoff, f32 yoff) {
    animate_list_update(cmm_menu_list_offsets, ARRAY_COUNT(cmm_settings_boundary_buttons), cmm_menu_index);
    u32 numOptions = ARRAY_COUNT(cmm_settings_boundary_buttons);

    if (!(cmm_boundary_table[cmm_lopt_boundary] & CMM_BOUNDARY_INNER_WALLS)) {
        numOptions -= 1;
    }
    cmm_settings_menu_lengths[SETTINGS_BOUNDARY_INDEX] = numOptions;

    for (s32 i=0;i<ARRAY_COUNT(cmm_settings_boundary_buttons);i++) {
        if ((i == BOUNDARY_HEIGHT_INDEX) && (numOptions == ARRAY_COUNT(cmm_settings_boundary_buttons) - 1)) {
            cmm_greyed_text = TRUE;
        }
        print_maker_string_ascii(55 +xoff+3*cmm_menu_list_offsets[i],154-(i*16)+yoff,cmm_settings_boundary_buttons[i].str,(i==cmm_menu_index));
        cmm_menu_option_animation(200+xoff+3*cmm_menu_list_offsets[i],154-(i*16)+yoff,60,&cmm_settings_boundary_buttons[i],i,cmm_joystick);
    }
    cmm_greyed_text = FALSE;
}

#define CUSTOM_MENU_SCROLL_HEIGHT 105

s32 env_menu_handle_scroll() {
    s32 yOffset = (cmm_custom_theme_menu_open ? CUSTOM_MENU_SCROLL_HEIGHT : 0);
    if (cmm_menu_scrolling[SCROLL_CUSTOM][0] > 0) {
        cmm_menu_scrolling[SCROLL_CUSTOM][0]--;
        yOffset += (cmm_menu_scrolling[SCROLL_CUSTOM][0] * cmm_menu_scrolling[SCROLL_CUSTOM][1] * CUSTOM_MENU_SCROLL_HEIGHT) / 8;
    }
    return yOffset;
}

void prepare_block_draw(f32 xpos, f32 ypos) {
    u16 perspNorm;
    Mat4 mtx1, mtx2;
    Vec3f pos;
    Vec3s rot;

    Mtx *perspMtx = alloc_display_list(sizeof(*perspMtx));
    guFrustum(perspMtx, -SCREEN_WIDTH/2 + xpos, SCREEN_WIDTH/2 + xpos, -SCREEN_HEIGHT/2 - ypos, SCREEN_HEIGHT/2 - ypos, 128, 4000, 0.005f);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(perspMtx), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);

    Lights1* curLight = (Lights1*)alloc_display_list(sizeof(Lights1));
    extern Lights1 *defaultLight;
    bcopy(&defaultLight, curLight, sizeof(Lights1));

    curLight->l->l.dir[0] = (s8)(globalLightDirection[0]);
    curLight->l->l.dir[1] = (s8)(globalLightDirection[1]);
    curLight->l->l.dir[2] = (s8)(globalLightDirection[2]);

    gSPSetLights1(gDisplayListHead++, (*curLight));

    Mtx *mtx = alloc_display_list(sizeof(*mtx));
    vec3_set(pos, 0, 0, -1500);
    vec3_set(rot, 0, (s16)(0x200*gGlobalTimer), 0);
    mtxf_rotate_zxy_and_translate(mtx1, gVec3fZero, rot);
    vec3_set(rot, 0x1800, 0, 0);
    mtxf_rotate_zxy_and_translate(mtx2, pos, rot);
    mtxf_mul(mtx1, mtx1, mtx2);
    mtxf_to_mtx(mtx, mtx1);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_PUSH);

    cmm_building_collision = FALSE;
    cmm_growth_render_type = 0;
    cmm_render_culling_off = TRUE;
    cmm_curr_mat_has_topside = FALSE;
    cmm_use_alt_uvs = FALSE;
    cmm_render_flip_normals = FALSE;
}

void finish_block_draw() {
    cmm_render_culling_off = FALSE;

    gSPDisplayList(gDisplayListHead++, cmm_curr_gfx);
    cmm_curr_gfx += cmm_gfx_index;
    cmm_gfx_index = 0;

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    create_dl_ortho_matrix();
}

void custom_theme_draw_block(f32 xpos, f32 ypos, s32 index) {
    prepare_block_draw(xpos, ypos);

    s8 pos[3];
    vec3_set(pos,32,32,32);

    if (index < NUM_MATERIALS_PER_THEME) {
        u8 renderedMat = cmm_curr_custom_theme.mats[index];
        u8 renderedTopmat = cmm_curr_custom_theme.topmats[index];
        if (!cmm_curr_custom_theme.topmatsEnabled[index]) renderedTopmat = renderedMat;

        render_preview_block(renderedMat, renderedTopmat, pos, &cmm_terrain_fullblock, 0, PROCESS_TILE_BOTH, TRUE);
    } else {
        cmm_use_alt_uvs = TRUE;
        cmm_curr_poly_vert_count = 4;
        if (index == 10) { // Poles
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], cmm_mat_table[cmm_curr_custom_theme.pole].gfx);
            set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], cmm_mat_table[cmm_curr_custom_theme.pole].type, TRUE);
            process_tile(pos, &cmm_terrain_pole, cmm_rot_selection);
        } else if (index == 11) { // Fence
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], cmm_fence_texs[cmm_curr_custom_theme.fence]);
            set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], MAT_CUTOUT, TRUE);
            process_tile(pos, &cmm_terrain_fence, cmm_rot_selection);
        } else if (index == 12) { // Iron Mesh
            set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], MAT_CUTOUT, TRUE);
            u8 connections[5] = {1,0,1,0,1};
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], cmm_bar_texs[cmm_curr_custom_theme.bars][1]);
            gSPClearGeometryMode(&cmm_curr_gfx[cmm_gfx_index++], G_CULL_BACK);
            render_bars_top(pos, connections);
            display_cached_tris();
            gSPSetGeometryMode(&cmm_curr_gfx[cmm_gfx_index++], G_CULL_BACK);
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], cmm_bar_texs[cmm_curr_custom_theme.bars][0]);
            render_bars_side(pos, connections);
        } else if (index == 13) { // Water
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], cmm_water_texs[cmm_curr_custom_theme.water]);
            set_render_mode(&cmm_curr_gfx[cmm_gfx_index++], MAT_TRANSPARENT, TRUE);
            render_water(pos);
        }
        display_cached_tris();
        cmm_use_alt_uvs = FALSE;
    }

    gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gDPSetTextureLUT(&cmm_curr_gfx[cmm_gfx_index++], G_TT_NONE);
    gSPEndDisplayList(&cmm_curr_gfx[cmm_gfx_index++]);

    finish_block_draw();
}

void custom_theme_draw_mat_selector(f32 xPos, f32 yPos, s32 startIndex, u8 *outputVar) {
    u8 tmpCategory;
    u8 tmpMaterial;
    get_category_and_mat_from_mat(&tmpCategory, &tmpMaterial, *outputVar);
    u8 oldCategory = tmpCategory;

    cmm_settings_mat_selector[0].value = &tmpCategory;
    cmm_settings_mat_selector[1].value = &tmpMaterial;
    cmm_settings_mat_selector[1].size = cmm_matlist[tmpCategory+1] - cmm_matlist[tmpCategory];

    print_maker_string_ascii(xPos+20+3*cmm_menu_list_offsets[startIndex], yPos, "Category:", (startIndex == cmm_menu_index));
    cmm_menu_option_animation(xPos+150+3*cmm_menu_list_offsets[startIndex], yPos, 50, &cmm_settings_mat_selector[0], startIndex, cmm_joystick);

    if (tmpCategory != oldCategory) {
        tmpMaterial = 0;
    }

    print_maker_string_ascii(xPos+20+3*cmm_menu_list_offsets[startIndex+1], yPos - 16, "Material:", (startIndex+1 == cmm_menu_index));
    cmm_menu_option_animation(xPos+150+3*cmm_menu_list_offsets[startIndex+1], yPos - 16, 50, &cmm_settings_mat_selector[1], startIndex + 1, cmm_joystick);

    *outputVar = cmm_matlist[tmpCategory] + tmpMaterial;
}

// The amount to offset cmm_menu_index by when in the custom theme menu
#define CUSTOM_INDEX_OFFSET (ARRAY_COUNT(cmm_settings_env_buttons) + 1)

void cmm_custom_theme_block_page(u32 index, f32 xPos, f32 yPos) {
    u32 topmatDisabled = !cmm_curr_custom_theme.topmatsEnabled[index];
    char *topmatText = "";

    if (cmm_custom_theme_menu_open) {
        if (topmatDisabled) {
            topmatText = "Enable Top Material...";
            cmm_menu_index_max = 3;
        } else {
            topmatText = "Disable Top Material...";
            cmm_menu_index_max = 5;
        }
    }

    // Selector for main material
    custom_theme_draw_mat_selector(xPos, 160 + yPos, CUSTOM_INDEX_OFFSET, &cmm_curr_custom_theme.mats[index]);

    // Selector for top material
    print_maker_string_ascii(xPos+55+3*cmm_menu_list_offsets[CUSTOM_INDEX_OFFSET+2], 128 + yPos, topmatText, (CUSTOM_INDEX_OFFSET+2 == cmm_menu_index));
    cmm_greyed_text = topmatDisabled;
    custom_theme_draw_mat_selector(xPos, 112 + yPos, CUSTOM_INDEX_OFFSET+3, &cmm_curr_custom_theme.topmats[index]);
    cmm_greyed_text = FALSE;

    if (cmm_menu_index == CUSTOM_INDEX_OFFSET + 2) { // Enable/disable button
        if (gPlayer1Controller->buttonPressed & A_BUTTON) {
            play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
            cmm_curr_custom_theme.topmatsEnabled[index] ^= 1;
        }
    }
}

void cmm_custom_theme_pole_page(f32 xPos, f32 yPos) {
    if (cmm_custom_theme_menu_open) cmm_menu_index_max = 2;
    custom_theme_draw_mat_selector(xPos, 150 + yPos, CUSTOM_INDEX_OFFSET, &cmm_curr_custom_theme.pole);
}

void cmm_custom_theme_other_page(f32 xPos, f32 yPos, u32 otherIndex) {
    if (cmm_custom_theme_menu_open) cmm_menu_index_max = 1;

    print_maker_string_ascii(xPos+20+3*cmm_menu_list_offsets[CUSTOM_INDEX_OFFSET], yPos + 135, cmm_settings_other_selectors[otherIndex].str, (CUSTOM_INDEX_OFFSET == cmm_menu_index));
    cmm_menu_option_animation(xPos+150+3*cmm_menu_list_offsets[CUSTOM_INDEX_OFFSET], yPos + 135, 50, &cmm_settings_other_selectors[otherIndex], CUSTOM_INDEX_OFFSET, cmm_joystick);
}

void cmm_custom_theme_render_page(u32 index, f32 xPos, f32 yPos) {
    if (index < NUM_MATERIALS_PER_THEME) {
        cmm_custom_theme_block_page(index, xPos, yPos);
    } else if (index == 10) {
        cmm_custom_theme_pole_page(xPos, yPos);
    } else {
        cmm_custom_theme_other_page(xPos, yPos, index - 11);
    }


    custom_theme_draw_block(-xPos - 100, yPos + 10, index);
}

void draw_cmm_settings_custom_theme(f32 yoff) {
    s32 dir = 0;

    if (cmm_custom_theme_menu_open) {
        if (gPlayer1Controller->buttonPressed & L_TRIG) dir = -1;
        if (gPlayer1Controller->buttonPressed & R_TRIG) dir = 1;
    }

    s32 prevMenu = (cmm_curr_custom_tab - 1 + CMM_NUM_CUSTOM_TABS) % CMM_NUM_CUSTOM_TABS;
    s32 nextMenu = (cmm_curr_custom_tab + 1) % CMM_NUM_CUSTOM_TABS;
    char *cur = cmm_custom_get_menu_name(cmm_curr_custom_tab);
    char *prev = cmm_custom_get_menu_name(prevMenu);
    char *next = cmm_custom_get_menu_name(nextMenu);
    print_maker_string_ascii_centered(80, yoff + 185, "< L", FALSE);
    print_maker_string_ascii_centered(240, yoff + 185, "R >", FALSE);
    s32 result = cmm_menu_option_sidescroll(160, 185+yoff, 70,
                                prev, cur, next,
                                cmm_menu_scrolling[SCROLL_CUSTOM_TABS], FALSE, dir); 

    // Change selected menu if it was switched
    if (result) {
        cmm_curr_custom_tab = (result == 1 ? nextMenu : prevMenu);
        play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
    }
    // Reset index halfway through animation
    if (cmm_menu_scrolling[SCROLL_CUSTOM_TABS][0] == 2) {
        cmm_menu_index = CUSTOM_INDEX_OFFSET;
    }

    cmm_curr_gfx = preview_gfx;
    cmm_curr_vtx = preview_vtx;
    cmm_gfx_index = 0;

    cmm_menu_page_animation(yoff, cmm_custom_theme_render_page, cmm_curr_custom_tab, CMM_NUM_CUSTOM_TABS, cmm_menu_scrolling[SCROLL_CUSTOM_TABS]);

    // This code is so fucking disgusting.
    // Edit all the vertices for the drawn preview blocks here.
    // Done outside the main block draw to be able to affect multiple blocks at once
    for (s32 i = 0; i < ARRAY_COUNT(preview_vtx); i++) {
        // Offset all vertices
        preview_vtx[i].v.ob[0] -= TILE_SIZE/2;
        preview_vtx[i].v.ob[2] -= TILE_SIZE/2;
    }
}

void draw_cmm_settings_env(f32 xoff, f32 yoff) {
    s32 oldtheme = cmm_lopt_theme;
    u8 beginScrollAnim = FALSE;

    if (cmm_custom_theme_menu_open) {
        cmm_menu_index += CUSTOM_INDEX_OFFSET;
    }

    animate_list_update(cmm_menu_list_offsets, 10, cmm_menu_index);
    for (s32 i=0;i<ARRAY_COUNT(cmm_settings_env_buttons);i++) {
        print_maker_string_ascii(55+xoff+3*cmm_menu_list_offsets[i],154-(i*16)+yoff,cmm_settings_env_buttons[i].str,(i==cmm_menu_index));
        cmm_menu_option_animation(200+xoff+3*cmm_menu_list_offsets[i],154-(i*16)+yoff,60,&cmm_settings_env_buttons[i],i,cmm_joystick);
    }

    if (cmm_lopt_theme == CMM_THEME_CUSTOM) {
        animate_menu_ease_in(cmm_menu_button_vels[0], 0.f, 30.f, 0.4f, oldtheme != CMM_THEME_CUSTOM);
    } else {
        animate_menu_generic(cmm_menu_button_vels[0], 30.f, 0.f, -2.f, oldtheme == CMM_THEME_CUSTOM);
    }
    cmm_set_data_overrides();

    s32 index = ARRAY_COUNT(cmm_settings_env_buttons);
    s32 customThemeY = 120-(index*16) + cmm_menu_button_vels[0][0];
    print_maker_string_ascii_centered(160+xoff+3*cmm_menu_list_offsets[index],customThemeY + yoff,"Edit Custom Theme...",(index == cmm_menu_index));
    draw_cmm_settings_custom_theme(yoff - CUSTOM_MENU_SCROLL_HEIGHT);

    if ((cmm_menu_scrolling[SCROLL_CUSTOM][0] == 0) && CMM_SETTINGS_MENU_IS_STILL) {
        if (!cmm_custom_theme_menu_open) {
            if (cmm_menu_index == index) {
                if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                    // Open custom theme menu
                    cmm_custom_theme_menu_open = TRUE;
                    cmm_menu_scrolling[SCROLL_CUSTOM][0] = 8;
                    cmm_menu_scrolling[SCROLL_CUSTOM][1] = -1;
                    cmm_menu_index = CUSTOM_INDEX_OFFSET;
                    play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                }
            }
        } else {
            if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                cmm_custom_theme_menu_open = FALSE;
                cmm_menu_scrolling[SCROLL_CUSTOM][0] = 8;
                cmm_menu_scrolling[SCROLL_CUSTOM][1] = 1;
                cmm_menu_index = index;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                update_custom_theme();
                generate_terrain_gfx();
            }
        }
    }

    if (!cmm_lopt_secret && !cmm_custom_theme_menu_open) {
        u16 nextButton = cmm_konami_code[cmm_konami_code_cur_index];
        if (gPlayer1Controller->buttonPressed & nextButton) {
            cmm_konami_code_cur_index++;
            if (cmm_konami_code_cur_index == 11) {
                cmm_konami_code_cur_index = 0;
                cmm_lopt_secret = TRUE;
                cmm_set_data_overrides();
                play_puzzle_jingle();
            }
        } else if (gPlayer1Controller->buttonPressed) {
            cmm_konami_code_cur_index = 0;
        }
    }

    if (cmm_custom_theme_menu_open) {
        cmm_menu_index -= CUSTOM_INDEX_OFFSET;
    }
}

void draw_cmm_settings_music(f32 xoff, f32 yoff) {
    animate_list_update(cmm_menu_list_offsets, ARRAY_COUNT(cmm_settings_music_buttons), cmm_menu_index);
    for (s32 i=0;i<ARRAY_COUNT(cmm_settings_music_buttons);i++) {
        print_maker_string_ascii(35+xoff+3*cmm_menu_list_offsets[i],154-(i*25)+yoff,cmm_settings_music_buttons[i].str,(i==cmm_menu_index));
        cmm_menu_option_animation(190+xoff+3*cmm_menu_list_offsets[i],154-(i*25)+yoff,100,&cmm_settings_music_buttons[i],i,cmm_joystick);
    }
}

struct cmm_settings_button cmm_change_size_button = {NULL,  &cmm_newsize, cmm_levelsize_string_table, ARRAY_COUNT(cmm_levelsize_string_table), NULL, NULL};

extern u8 cmm_mm_state; //externing a variable in the same file that it's defined in? more likely than you think. how heinous.
void draw_cmm_settings_system(f32 xoff, f32 yoff) {
    animate_list_update(cmm_menu_list_offsets, ARRAY_COUNT(cmm_settings_system_buttons), cmm_menu_index);
    for (s32 i=0;i<2;i++) {
        print_maker_string_ascii_centered(160+xoff+3*cmm_menu_list_offsets[i],160-(i*16)+yoff,cmm_settings_system_buttons[i],(i==cmm_menu_index));
    }
    
    // Apply size
    print_maker_string_ascii(70+xoff+3*cmm_menu_list_offsets[2],150-(2*16)+yoff,cmm_settings_system_buttons[2],(2==cmm_menu_index));
    cmm_menu_option_animation(210+xoff+3*cmm_menu_list_offsets[2],150-(2*16)+yoff,40,&cmm_change_size_button,2,cmm_joystick);
    print_maker_string_ascii_centered(160+xoff+3*cmm_menu_list_offsets[3],150-(3*16)+yoff,cmm_settings_system_buttons[3],(3==cmm_menu_index ? 1 : 4));

    if ((gPlayer1Controller->buttonPressed & A_BUTTON) && CMM_SETTINGS_MENU_IS_STILL) {
        switch (cmm_menu_index) {
            case 0: // save and quit
                if (mount_success == FR_OK) {
                    save_level();
                    play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
                    load_level_files_from_sd_card();
                    cmm_mm_state = MM_FILES;
                } else {
                    cmm_mm_state = MM_MAIN_LIMITED;
                }
                fade_into_special_warp(WARP_SPECIAL_MARIO_HEAD_REGULAR, 0); // reset game
                break;
            case 1: // play level
                if (mount_success == FR_OK) {
                    save_level();
                }
                cmm_target_mode = CMM_MODE_PLAY;
                cmm_level_action = CMM_LA_PLAY_LEVELS;
                reset_play_state();
                level_trigger_warp(gMarioState, WARP_OP_LOOK_UP);
                sSourceWarpNodeId = 0x0A;
                play_sound(SOUND_MENU_STAR_SOUND_LETS_A_GO, gGlobalSoundSource);
                break;
        }
    }
}

#define SETTINGS_MENU_COUNT ARRAY_COUNT(cmm_settings_menus)

void cmm_settings_menu_page(u32 index, f32 xPos, f32 yPos) {
    cmm_settings_menus[index](xPos, yPos);
}

void draw_cmm_settings_menu(f32 yoff) {
    cmm_menu_page_animation(yoff, cmm_settings_menu_page, cmm_curr_settings_menu, SETTINGS_MENU_COUNT, cmm_menu_scrolling[SCROLL_SETTINGS]);
}

void draw_cmm_menu(void) {
    if (cmm_menu_state != CMM_MAKE_SCREENSHOT) {
        create_dl_translation_matrix(MENU_MTX_PUSH, 19, 36, 0);
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
        gSPDisplayList(gDisplayListHead++, &bg_back_graund_mesh);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

        animate_list_update(cmm_menu_toolbar_offsets, ARRAY_COUNT(cmm_menu_toolbar_offsets), cmm_toolbar_index);
        for (s32 i = 0; i < 9; i++) {
            s32 op = (cmm_toolbar_index == i ? 255 : 200);
            create_dl_translation_matrix(MENU_MTX_PUSH, 34+(i*32), 20 + (5 * cmm_menu_toolbar_offsets[i]), 0);
            gDPSetEnvColor(gDisplayListHead++, op, op, op, 255);

            Gfx *mat = get_button_tex(cmm_toolbar[i], cmm_toolbar_params[i]);

            gSPDisplayList(gDisplayListHead++, mat);//texture
            gSPDisplayList(gDisplayListHead++, &uibutton_button_mesh);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
        }
        gSPDisplayList(gDisplayListHead++, &mat_revert_b_btn_check);
    }

    //TOOLBOX
    switch (cmm_menu_state) {
        case CMM_MAKE_MAIN:
            cmm_render_topleft_text();
            break;

        case CMM_MAKE_TOOLBOX:
            // In/out animation
            if (cmm_menu_start_timer != -1) {
                animate_menu_ease_in(cmm_menu_title_vels, 150.f, -10.f, 0.35f, cmm_menu_start_timer == 0);
                if (cmm_menu_start_timer++ > 10) {
                    cmm_menu_start_timer = -1;
                }
            } else if (cmm_menu_end_timer != -1) {
                animate_menu_generic(cmm_menu_title_vels, -10.f, 0.f, 4.f, cmm_menu_end_timer == 0);
                cmm_menu_end_timer++;
                cmm_joystick = 0;
            } else {
                if (gPlayer1Controller->buttonPressed & (B_BUTTON | START_BUTTON)) {
                    cmm_menu_end_timer = 0;
                    play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                }
            }
            f32 yOff = cmm_menu_title_vels[0];

            create_dl_translation_matrix(MENU_MTX_PUSH, 19, 235+yOff, 0);
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
            gSPDisplayList(gDisplayListHead++, &bg_back_graund_mesh);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
            animate_list_update(cmm_menu_list_offsets, ARRAY_COUNT(cmm_menu_list_offsets), cmm_toolbox_index);

            for (s32 i = 0; i < (s32)sizeof(cmm_toolbox); i++) {
                s32 op = 255;
                if (i == cmm_toolbox_index) {
                    op = 100;
                }
                s32 xi = i%9;
                s32 yi = i/9;
                create_dl_translation_matrix(MENU_MTX_PUSH, 34+(xi*32), 220-(yi*32) + 4*cmm_menu_list_offsets[i] + yOff, 0);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, op, 255);

                Gfx *mat = get_button_tex(cmm_toolbox[i], cmm_toolbox_params[i]);

                gSPDisplayList(gDisplayListHead++, mat);//texture
                gSPDisplayList(gDisplayListHead++, &uibutton_button_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);    
            }

            if (cmm_toolbox_transition_btn_render) {
                create_dl_translation_matrix(MENU_MTX_PUSH, cmm_toolbox_transition_btn_x, cmm_toolbox_transition_btn_y, 0);
                gSPDisplayList(gDisplayListHead++, cmm_toolbox_transition_btn_gfx);//texture
                gSPDisplayList(gDisplayListHead++, &uibutton_button_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

                f32 dist = sqrtf(sqr(cmm_toolbox_transition_btn_tx - cmm_toolbox_transition_btn_x) + sqr(cmm_toolbox_transition_btn_ty - cmm_toolbox_transition_btn_y));
                f32 multiplier = MAX(0.5f - (dist * 0.01f), 0.2f);
                cmm_toolbox_transition_btn_x = approach_f32_asymptotic(cmm_toolbox_transition_btn_x, cmm_toolbox_transition_btn_tx, multiplier);
                cmm_toolbox_transition_btn_y = approach_f32_asymptotic(cmm_toolbox_transition_btn_y, cmm_toolbox_transition_btn_ty, multiplier);
            }
            gSPDisplayList(gDisplayListHead++, &mat_revert_b_btn_check);

            s32 strx = 54+(cmm_toolbox_index%9)*32;
            s32 stry = 215-(cmm_toolbox_index/9)*32+yOff+4*cmm_menu_list_offsets[cmm_toolbox_index];

            if (cmm_toolbox[cmm_toolbox_index] != CMM_BUTTON_BLANK) {
                u32 isMulti = cmm_ui_buttons[cmm_toolbox[cmm_toolbox_index]].multiObj;
                char *buttonName = get_button_str(cmm_toolbox[cmm_toolbox_index]);
                //render selection box
                if ((cmm_toolbox_index%9) > 5) {
                    strx -= 130;
                }
                if (isMulti) stry += 8;

                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
                gDPSetCombineMode(gDisplayListHead++, G_CC_ENVIRONMENT, G_CC_ENVIRONMENT);
                gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
                gDPFillRectangle(gDisplayListHead++, strx-5, 240-stry-14, strx + get_string_width_ascii(buttonName) + 5, 240-stry+1);

                if (isMulti) {
                    char stringBuf[50];
                    u32 objId = cmm_ui_buttons[cmm_toolbox[cmm_toolbox_index]].idList[cmm_toolbox_params[cmm_toolbox_index]];
                    sprintf(stringBuf, "< %s >", cmm_object_type_list[objId].name);
                    gDPFillRectangle(gDisplayListHead++, strx-5, 240-stry+1, strx + get_string_width_ascii(stringBuf) + 5, 240-stry+16);
                    print_maker_string_ascii(strx, stry-15, stringBuf, TRUE);
                }

                print_maker_string_ascii(strx, stry, buttonName, TRUE);
            }

            break;

        case CMM_MAKE_SETTINGS:
            // In/out animation
            if (cmm_menu_start_timer != -1) {
                animate_menu_generic(cmm_menu_button_vels[0], 30.f, 0, 0, cmm_lopt_theme == CMM_THEME_CUSTOM); // mega hacky
                animate_menu_ease_in(cmm_menu_title_vels, 150.f, -10.f, 0.35f, cmm_menu_start_timer == 0);
                if (cmm_menu_start_timer++ > 10) {
                    cmm_menu_start_timer = -1;
                }
            } else if (cmm_menu_end_timer != -1) {
                animate_menu_generic(cmm_menu_title_vels, -10.f, 0.f, 4.f, cmm_menu_end_timer == 0);
                cmm_menu_end_timer++;
                cmm_joystick = 0;
            } else {
                if ((gPlayer1Controller->buttonPressed & START_BUTTON) ||
                    ((gPlayer1Controller->buttonPressed & B_BUTTON) && !cmm_custom_theme_menu_open)) {
                    if (!(gPlayer1Controller->buttonPressed & cmm_konami_code[cmm_konami_code_cur_index])) {
                        cmm_menu_end_timer = 0;
                        play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                        if (cmm_custom_theme_menu_open) {
                            update_custom_theme();
                            generate_terrain_gfx();
                        }
                    }
                }
            }
            yOff = cmm_menu_title_vels[0];

            // Background
            create_dl_translation_matrix(MENU_MTX_PUSH, 19, 240+yOff, 0);
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
            gSPDisplayList(gDisplayListHead++, &bg_back_graund_mesh);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            // Level portrait
            create_dl_translation_matrix(MENU_MTX_PUSH, 290, 210+yOff, 0);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
            gSPDisplayList(gDisplayListHead++, &bigpainting2_bigpainting2_mesh);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            cmm_global_scissor = 15;
            cmm_global_scissor_top = MAX(0, 15 - yOff);
            cmm_global_scissor_bottom = MAX(0, 145 - yOff);
            gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, cmm_global_scissor, cmm_global_scissor_top, SCREEN_WIDTH - cmm_global_scissor, cmm_global_scissor_bottom);
            yOff += env_menu_handle_scroll();

            // Level name
            print_maker_string_ascii_centered(SCREEN_WIDTH/2,210+yOff,cmm_file_info.fname,FALSE);

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

            // Begin rendering top header
            s32 prevMenu = (cmm_curr_settings_menu - 1 + SETTINGS_MENU_COUNT) % SETTINGS_MENU_COUNT;
            s32 nextMenu = (cmm_curr_settings_menu + 1) % SETTINGS_MENU_COUNT;
            char *cur = cmm_settings_menu_names[cmm_curr_settings_menu];
            char *prev = cmm_settings_menu_names[prevMenu];
            char *next = cmm_settings_menu_names[nextMenu];

            // Scroll input
            s32 dir = 0;
            if (!cmm_custom_theme_menu_open) {
                if (cmm_menu_scrolling[SCROLL_CUSTOM][0] == 0) {
                    if (gPlayer1Controller->buttonPressed & L_TRIG) dir = -1;
                    if (gPlayer1Controller->buttonPressed & R_TRIG) dir = 1;
                }
                cmm_menu_index_max = cmm_settings_menu_lengths[cmm_curr_settings_menu];;
            }
            cmm_menu_index = (cmm_menu_index + cmm_menu_index_max) % cmm_menu_index_max;

            print_maker_string_ascii_centered(80, yOff + 185, "< L", FALSE);
            print_maker_string_ascii_centered(240, yOff + 185, "R >", FALSE);
            s32 result = cmm_menu_option_sidescroll(160, 185+yOff, 70,
                                       prev, cur, next,
                                       cmm_menu_scrolling[SCROLL_SETTINGS], FALSE, dir); 

            // Change selected menu if it was switched
            if (result) {
                cmm_curr_settings_menu = (result == 1 ? nextMenu : prevMenu);
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
            }
            // Reset index halfway through animation
            if (cmm_menu_scrolling[SCROLL_SETTINGS][0] == 2) {
                cmm_menu_index = 0;
            }

            // Draw menu + scroll
            draw_cmm_settings_menu(yOff);
            cmm_global_scissor = 0;
            cmm_global_scissor_top = 0;
            cmm_global_scissor_bottom = SCREEN_HEIGHT;
            gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            break;

        case CMM_MAKE_TRAJECTORY:
            print_maker_string(20,210,cmm_txt_recording,TRUE);
            cmm_render_topleft_text();
            break;

        case CMM_MAKE_SCREENSHOT:
            if (cmm_freecam_snap) {
                return;
            }
            print_maker_string(20,210,cmm_txt_freecam,TRUE);
            //cmm_render_topleft_text();
            break;
    }

    if ((cmm_menu_state != CMM_MAKE_TRAJECTORY)&&(cmm_menu_state != CMM_MAKE_SCREENSHOT)) {
        s32 currentX = 15;
        char *buttonName = get_button_str(cmm_toolbar[cmm_toolbar_index]);
        print_maker_string_ascii(currentX,45,buttonName,FALSE);
        currentX += get_string_width_ascii(buttonName) + 10;

        char *yellowStr = NULL;
        if (cmm_place_mode == CMM_PM_OBJ) {
            if (cmm_ui_buttons[cmm_toolbar[cmm_toolbar_index]].multiObj) {
                yellowStr = cmm_object_type_list[cmm_ui_buttons[cmm_toolbar[cmm_toolbar_index]].idList[cmm_toolbar_params[cmm_toolbar_index]]].name;
            } else {
                if (cmm_ui_buttons[cmm_toolbar[cmm_toolbar_index]].names) {
                    yellowStr = cmm_ui_buttons[cmm_toolbar[cmm_toolbar_index]].names[cmm_toolbar_params[cmm_toolbar_index]];
                }
            }
        } else if (cmm_terrain_info_list[cmm_id_selection].terrain) {
            yellowStr = TILE_MATDEF(cmm_mat_selection).name;

            if (cmm_id_selection < TILE_END_OF_FLIPPABLE) {
                if (cmm_upsidedown_tile) {
                    print_maker_string_ascii(currentX,45,"(|)",FALSE);
                } else {
                    print_maker_string_ascii(currentX,45,"(^)",FALSE);
                }
                currentX += 25;
            }
        }
        if (yellowStr) {
            currentX += 15;
            print_maker_string_ascii(currentX,45,"<",TRUE);
            print_maker_string_ascii(currentX + 20,45,yellowStr,TRUE);
            currentX += get_string_width_ascii(yellowStr) + 30;
            print_maker_string_ascii(currentX,45,">",TRUE);
        }
    }
}

char *cmm_mm_keyboard_prompt[] = {
    "Enter level name:",//KXM_NEW_LEVEL
    "Enter placeholder level name:", //KXM_NEW_LEVEL_LIMITED
    "Enter your author name:",//KXM_AUTHOR
    "Change author name:",
};
char cmm_mm_keyboard[] = "1234567890abcdefghijklmnopqrstuvwxyz!'- ";
char cmm_mm_keyboard_caps[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ!'- ";
char cmm_mm_keyboard_input[31];
u8 cmm_mm_keyboard_exit_mode = KXM_NEW_LEVEL;
u8 cmm_mm_keyboard_input_index = 0;
#define KEYBOARD_SIZE (sizeof(cmm_mm_keyboard)-1)
s8 cmm_mm_keyboard_index = 0;

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

/**
char *cmm_mm_play_btns[] = {
    "Play Levels",
    cmm_mm_comingsoon, //"Play Hacks"
};
**/

char *cmm_mm_make_btns[] = {
    "New Level",
    "Load Level",
    "Change Name",
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

char *cmm_mm_txt_keyboard[]= {
    "\x10: Press Key         \x11: Backspace\n\x12: Shift              \x13: Exit\nSTART: Confirm",
    "\x10: Press Key         \x11: Backspace\n\x12: Shift              \x13: Exit\nSTART: Confirm",
    "\x10: Press Key         \x11: Backspace\n\x12: Shift              START: Confirm",
    "\x10: Press Key         \x11: Backspace\n\x12: Shift              \x13: Exit\nSTART: Confirm",
};

u8 cmm_mm_state = MM_INIT;
u8 cmm_mm_main_state = MM_MAIN;
u8 cmm_mm_files_prev_menu;
s8 cmm_mm_pages = 0;
s8 cmm_mm_page = 0;
u8 *cmm_mm_help_ptr = NULL;
#define PAGE_SIZE 5

void cmm_mm_shade_screen(void) {
    u8 alpha = 110;
    if (cmm_menu_start_timer != -1) {
        u8 time = MIN(cmm_menu_start_timer, 8);
        alpha = (time * 110) / 8;
    } else if (cmm_menu_end_timer != -1 && !(cmm_mm_state == MM_KEYBOARD && cmm_mm_keyboard_exit_mode == KXM_NEW_LEVEL && cmm_menu_going_back == 1)) {
        u8 time = MIN(cmm_menu_end_timer, 8);
        alpha = 110 - ((time * 110) / 8);
    }
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, alpha);
    gDPSetCombineMode(gDisplayListHead++, G_CC_ENVIRONMENT, G_CC_ENVIRONMENT);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPFillRectangle(gDisplayListHead++, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
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
        print_maker_string_ascii(115, 177 + cmm_menu_title_vels[0], "By Rovertronic & Arthurtilly", 0);
    }

    for (s32 i=0; i<ct; i++) {
        render_cmm_mm_button(cmm_menu_button_vels[i][0] + 160, 150-(i*30), cmm_menu_index == i);
        print_maker_string_ascii_centered(cmm_menu_button_vels[i][0] + 160,143-(i*30),strlist[i],cmm_menu_index == i);
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
            u8 file_does_not_exist_already = (!level_file_exists(cmm_mm_keyboard_input));
            u8 something_is_entered = (cmm_mm_keyboard_input_index > 0);

            if ((something_is_entered)&&(file_does_not_exist_already)) { //ensure that people write _something_
                cmm_menu_end_timer = 0;
                cmm_menu_going_back = 1;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
            } else {
                play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                if (!something_is_entered) {
                    cmm_show_error_message("Please enter a name first.");
                }
                if (!file_does_not_exist_already) {
                    cmm_show_error_message("Name is already used!");
                }
            }
        }
        if (gPlayer1Controller->buttonPressed & (R_TRIG)) {
            if (cmm_mm_keyboard_exit_mode != KXM_AUTHOR) {
                cmm_menu_end_timer = 0;
                cmm_menu_going_back = -1;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
            } else {
                play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
            }
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
    return cmm_mm_anim_out(6, TRUE, cmm_mm_keyboard_anim_check, 0.f);
}

s32 cmm_mm_make_anim_out(void) {
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
        animate_menu_overshoot_target(cmm_menu_title_vels, 20.f, -300.f, 55.f, -5.f, cmm_menu_start_timer == 0);
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
        animate_menu_generic(cmm_menu_title_vels, 20.f, 0.f, -10.f, cmm_menu_end_timer == 0);
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
    for (s32 i = 0; i < (cmm_joystick+1); i++) {
        random_u16(); // randomize for the initial tip
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
    cmm_menu_index = (cmm_menu_index + cmm_menu_index_max) % cmm_menu_index_max;

    create_dl_ortho_matrix();
    
    switch(cmm_mm_state) {
        case MM_INIT:
            full_menu_reset();
            for (u8 i=0;i<sizeof(cmm_mm_keyboard_input);i++){
                cmm_mm_keyboard_input[i] = '\0';
            }
            if (mount_success == FR_OK) {
                //SD Card success

                if (cmm_sram_configuration.author[0] != '\0') {
                    //already have an author, go straight to the main menu
                    cmm_mm_state = MM_MAIN;

                    //set cmm_username to author in sram config
                    bcopy(&cmm_sram_configuration.author,&cmm_username,sizeof(cmm_username));
                    cmm_has_username = TRUE;
                } else {
                    //no author file detected, prompt user to enter an author name
                    cmm_mm_keyboard_exit_mode = KXM_AUTHOR;
                    cmm_mm_state = MM_KEYBOARD;
                    cmm_mm_keyboard_input_index = 0;

                    //check for rhdc username
                    if (gSupportsLibpl) {
                        char * rhdc_username = libpl_get_my_rhdc_username();
                        if (rhdc_username) {
                            while ((rhdc_username[cmm_mm_keyboard_input_index] != 0)&&(cmm_mm_keyboard_input_index <= 29)) {
                                cmm_mm_keyboard_input[cmm_mm_keyboard_input_index] = rhdc_username[cmm_mm_keyboard_input_index];
                                cmm_mm_keyboard_input_index++;
                            }
                            cmm_mm_keyboard_input[cmm_mm_keyboard_input_index] = '\0';
                        }
                    }
                }
            } else {
                //SD Card failure, give player warning and limited play
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
            cmm_menu_index_max = 4;
            cmm_mm_anim_in(4);
            render_cmm_mm_menu(cmm_mm_btns,"Mario Builder 64",4);
            if (cmm_mm_generic_anim_out(4, FALSE)) {
                switch(cmm_menu_index) {
                    case 0:
                        cmm_mm_state = MM_MAKE;
                        break;
                    case 1:
                        cmm_mm_state = MM_FILES;
                        cmm_mm_files_prev_menu = MM_MAIN;
                        cmm_tip_timer = 0;
                        cmm_mm_page = 0;
                        cmm_level_action = CMM_LA_PLAY_LEVELS;
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
            cmm_menu_index_max = 3;
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
            /**
        case MM_PLAY:
            cmm_menu_index_max = 2;
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
                            cmm_level_action = CMM_LA_PLAY_LEVELS;
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
            **/
        case MM_MAKE:
            cmm_menu_index_max = 3;
            cmm_mm_anim_in(3);
            render_cmm_mm_menu(cmm_mm_make_btns,"Make Levels",3);
            if (cmm_mm_generic_anim_out(3, TRUE)) {
                cmm_menu_start_timer = 0;
                if (cmm_menu_going_back == -1) {
                    cmm_mm_state = cmm_mm_main_state;
                    cmm_menu_index = 0;
                } else {
                    switch(cmm_menu_index) {
                        case 0:
                            //make new level
                            cmm_mm_state = MM_MAKE_MODE;
                            cmm_level_action = CMM_LA_BUILD;
                            cmm_target_mode = CMM_MODE_MAKE;
                            break;
                        case 1:
                            //load levels
                            cmm_mm_files_prev_menu = MM_MAKE;
                            cmm_level_action = CMM_LA_BUILD;
                            cmm_target_mode = CMM_MODE_MAKE;
                            cmm_mm_state = MM_FILES;
                            cmm_mm_page = 0;
                            break;
                        case 2:
                            //change name
                            cmm_mm_keyboard_exit_mode = KXM_CHANGE_AUTHOR;
                            cmm_mm_state = MM_KEYBOARD;
                            cmm_mm_keyboard_input_index = 0;
                            cmm_mm_keyboard_input[0] = '\0';
                            break;
                    }
                    cmm_menu_index = 0;
                }
            }
            break;
        case MM_MAKE_MODE:
            cmm_menu_index_max = 4;
            cmm_mm_anim_in(4);
            f32 x,y;

            create_dl_scale_matrix(MENU_MTX_PUSH, 2.f, 2.f, 0.f);

            char *title = "Level Settings";
            print_maker_string_ascii(78 - (get_string_width_ascii(title)/2),95 + cmm_menu_title_vels[0]/2,title,0);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            for (s32 i=0; i<3; i++) {
                x = cmm_menu_button_vels[i][0] + 160;
                y = 150-(i*27);
                print_maker_string_ascii_centered(x - 60, y, cmm_mode_settings_buttons[i].str,0);
                render_cmm_mm_button(x + 20, y + 8, cmm_menu_index == i);
                cmm_menu_option_animation(x + 20, y, 43, &cmm_mode_settings_buttons[i], i, cmm_joystick);
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
                    } else {
                        cmm_mm_keyboard_exit_mode = KXM_NEW_LEVEL_LIMITED;
                        cmm_mm_state = MM_KEYBOARD;
                        cmm_mm_keyboard_input_index = 0;
                        cmm_mm_keyboard_input[0] = '\0';
                        cmm_menu_index = 0;
                    }
                } else {
                    if (cmm_menu_going_back == -1) {
                        cmm_mm_state = MM_MAKE;
                        cmm_menu_index = 0;
                    } else {
                        cmm_mm_keyboard_exit_mode = KXM_NEW_LEVEL;
                        cmm_mm_state = MM_KEYBOARD;
                        cmm_mm_keyboard_input_index = 0;
                        cmm_mm_keyboard_input[0] = '\0';
                        cmm_menu_index = 0;
                    }
                }
            }
            //if (cmm_mm_main_state == MM_MAIN_LIMITED && cmm_menu_end_timer == 0 && cmm_menu_going_back == 1) {
            //    cmm_tip_timer = 60;
            //    return 1;
            //}
            break;
        case MM_HELP_MODE:
            cmm_menu_index_max = 3;
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
            cmm_mm_anim_in(6);
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
                cmm_mm_keyboard_input[cmm_mm_keyboard_input_index] = '\0';
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
                if ((cmm_menu_going_back == 1)&&(cmm_mm_keyboard_exit_mode == KXM_AUTHOR)) {
                    cmm_mm_state = MM_MAIN;
                    cmm_menu_index = 0;
                }
                if (cmm_mm_keyboard_exit_mode == KXM_CHANGE_AUTHOR) {
                    cmm_mm_state = MM_MAKE;
                    cmm_menu_index = 0;
                }
            }

            cmm_mm_shade_screen();

            f32 inputX = CLAMP(30 + cmm_menu_button_vels[1][0], -160, 320);
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 100);
            gDPSetCombineMode(gDisplayListHead++, G_CC_ENVIRONMENT, G_CC_ENVIRONMENT);
            gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPFillRectangle(gDisplayListHead++, inputX, (240-185)-16, inputX + 150, (240-185)+3);


            print_maker_string_ascii(35 + cmm_menu_button_vels[0][0],208,cmm_mm_keyboard_prompt[cmm_mm_keyboard_exit_mode],FALSE);
            print_maker_string_ascii(35 + cmm_menu_button_vels[1][0],185,cmm_mm_keyboard_input,FALSE);
            print_maker_string_ascii(35,45 - cmm_menu_title_vels[0],cmm_mm_txt_keyboard[cmm_mm_keyboard_exit_mode],FALSE);

            cmm_render_topleft_text();

            for (u8 i=0; i<(sizeof(cmm_mm_keyboard)-1); i++) {
                u16 x = i%10;
                u16 y = i/10;
                gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
                create_dl_translation_matrix(MENU_MTX_PUSH, 40+(x*25)+cmm_menu_button_vels[y+2][0], 160-(y*25), 0);
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
                print_maker_string_ascii(37+(x*25)+cmm_menu_button_vels[y+2][0],152-(y*25),single_char,(cmm_mm_keyboard_index == i));
            }

            if (cmm_menu_end_timer == 0 && cmm_menu_going_back == 1) {
                switch(cmm_mm_keyboard_exit_mode) {
                    case KXM_NEW_LEVEL:
                    case KXM_NEW_LEVEL_LIMITED:
                        bcopy(&cmm_mm_keyboard_input,&cmm_file_name,cmm_mm_keyboard_input_index);
                        //manually add file extension
                        cmm_file_name[cmm_mm_keyboard_input_index+0] = '.';
                        cmm_file_name[cmm_mm_keyboard_input_index+1] = 'm';
                        cmm_file_name[cmm_mm_keyboard_input_index+2] = 'b';
                        cmm_file_name[cmm_mm_keyboard_input_index+3] = '6';
                        cmm_file_name[cmm_mm_keyboard_input_index+4] = '4';
                        cmm_file_name[cmm_mm_keyboard_input_index+5] = '\0';

                        cmm_mode = CMM_MODE_UNINITIALIZED;
                        return 1;
                    break;
                    case KXM_AUTHOR:
                    case KXM_CHANGE_AUTHOR:
                        bcopy(&cmm_mm_keyboard_input,&cmm_username,cmm_mm_keyboard_input_index);
                        cmm_username[cmm_mm_keyboard_input_index+1] = '\0';

                        bcopy(&cmm_username,&cmm_sram_configuration.author,sizeof(cmm_sram_configuration.author));
                        if (gSramProbe != 0) {
                            nuPiWriteSram(0, &cmm_sram_configuration, ALIGN4(sizeof(cmm_sram_configuration)));
                        }

                        cmm_has_username = TRUE;
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
                        cmm_menu_index = 1;
                        break;
                    }
                }
                return 0;
            }

            cmm_menu_index_max = cmm_level_entry_count;

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
                    cmm_menu_index = 1;
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
                cmm_file_name[i] = '\0'; // add null terminator

                f_chdir(cmm_level_dir_name);
                struct cmm_level_save_header * level_info = get_level_info_from_filename(&cmm_file_name);
                f_chdir("..");
                cmm_lopt_game = level_info->game;
                cmm_mm_selected_level = cmm_menu_index;
                if (cmm_level_action == CMM_LA_BUILD) cmm_tip_timer = 60;
                else cmm_tip_timer = 0;

                return 1;
            }

            break;
    }

    return 0;
}


// Pause menu during play
u8 cmm_pause_menu_state = 0;
char cmm_pause_menu_rte_text[] = "Return to Editor";
char cmm_pause_menu_ec_text[] = "Exit Course";

char * cmm_pause_menu_buttons_main[] = {
    "Continue",
    "Options",
    "Badges",
    NULL,
};

//#define OPTIONTEXT _("Play Music\nWidescreen Mode\nShow HUD\nCamera Collision")
char * cmm_pause_menu_buttons_options[] = {
    "Play Music",
    "Widescreen Mode",
    "Show HUD",
    "Camera Collision",
    "Return",
};

void cmm_init_pause_menu(void) {
    cmm_menu_index = 0;
    cmm_pause_menu_state = 0;
}

s32 draw_cmm_pause_menu(void) {
    u8 returnval = 0;
    s16 badge_count = count_u32_bits(save_file_get_badge_equip());
    s32 xoff;
    s32 yoff;
    char stringBuf[50];

    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);

    switch(cmm_pause_menu_state) {
        case 0: // main pause menu
            //print title and author
            if (cmm_save.author[0] != 0) {

                create_dl_translation_matrix(MENU_MTX_PUSH, 160, 0, 0);
                create_dl_scale_matrix(MENU_MTX_PUSH, 1.5f, 1.5f, 0.f);
                print_generic_string_ascii_centered_nofileext(0,134,cmm_file_name);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

                sprintf(stringBuf,"%s%s","By: ",cmm_save.author);
                print_generic_string_ascii_centered(160,184,stringBuf);
            } else {
                print_generic_string_ascii_centered(160,192,cmm_file_name);
            }

            cmm_pause_menu_buttons_main[3] = &cmm_pause_menu_rte_text;
            if (cmm_level_action == CMM_LA_PLAY_LEVELS) {
                cmm_pause_menu_buttons_main[3] = &cmm_pause_menu_ec_text;
            }
            xoff = (get_string_width_ascii(cmm_pause_menu_buttons_main[3])/2);
            yoff = 0;
            for (s32 i=0;i<4;i++) {
                if (i==2&&badge_count==0) {
                    continue;
                }
                print_generic_string_ascii(160-xoff  ,120+yoff,cmm_pause_menu_buttons_main[i]);
                yoff-=16;
            }

            gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

            // Print selector triangle
            if ((badge_count==0)&&(cmm_menu_index == 3)) {
                create_dl_translation_matrix(MENU_MTX_PUSH, 144-xoff, 120-(2*16), 0);
            } else {
                create_dl_translation_matrix(MENU_MTX_PUSH, 144-xoff, 120-(cmm_menu_index*16), 0);
            }
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
            gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            // print level collectibles
            // generate string
            sprintf(stringBuf,"^%dQ%d",cmm_play_stars, cmm_play_stars_max);
            print_text_centered(160,160, stringBuf);

            if (gRedCoinsTotal > 0) {
                //sprintf(stringBuf,"%s @%dQ%d", stringBuf, gRedCoinsCollected, gRedCoinsTotal);
                sprintf(stringBuf,"@%dQ%d", gRedCoinsCollected, gRedCoinsTotal);
            }
            if (cmm_lopt_coinstar > 0) {
                sprintf(stringBuf,"%s $%dQ%d", stringBuf, gMarioState->numCoins, (cmm_lopt_coinstar*20));
            }
            if ((gRedCoinsTotal > 0)||(cmm_lopt_coinstar > 0)) {
                print_text_centered(160,10, stringBuf);
            }

            cmm_joystick = joystick_direction();
            switch(cmm_joystick) {
                case 2:
                    cmm_menu_index++;
                    if (cmm_menu_index==2&&badge_count==0) {
                        cmm_menu_index++;
                    }
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                    break;
                case 4:
                    cmm_menu_index--;
                    if (cmm_menu_index==2&&badge_count==0) {
                        cmm_menu_index--;
                    }
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                    break;
            }
            cmm_menu_index = (cmm_menu_index + 4) % 4;

            if (gPlayer1Controller->buttonPressed & (A_BUTTON|B_BUTTON|START_BUTTON)) {
                switch(cmm_menu_index) {
                    case 0: // continue
                        returnval = 1;
                        break;
                    case 1: // options
                        cmm_pause_menu_state = 1;
                        cmm_menu_index = 0;
                        play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                        break;
                    case 2: // badges (btcm only)
                        play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                        cmm_pause_menu_state = 2;
                        //make sure the first unlocked badge is selected
                        gMarioState->numBadgeSelect = 0;
                        while (!(save_file_get_badge_equip() & (1<<gMarioState->numBadgeSelect))) {
                            gMarioState->numBadgeSelect++;
                        }
                        break;
                    case 3: // leave
                        returnval = 2;
                        break;
                }
            }
            break;

        case 1: //options
            xoff = (get_string_width_ascii(cmm_pause_menu_buttons_options[3])/2);
            for (s32 i=0;i<5;i++) {
                if (i!=4) {
                    char * onoroff_string = ": OFF";
                    if (cmm_sram_configuration.option_flags & (1<<i)) {
                        onoroff_string = ": ON";
                    }
                    sprintf(stringBuf,"%s%s",cmm_pause_menu_buttons_options[i],onoroff_string);
                    print_generic_string_ascii(160-xoff ,160-(i*16),stringBuf);
                } else {
                    print_generic_string_ascii(160-xoff ,160-(i*16),cmm_pause_menu_buttons_options[i]);
                }
            }

            create_dl_translation_matrix(MENU_MTX_PUSH, 144-xoff, 160-(cmm_menu_index*16), 0);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
            gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            cmm_joystick = joystick_direction();
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
            cmm_menu_index = (cmm_menu_index + 5) % 5;

            if (gPlayer1Controller->buttonPressed & (B_BUTTON)) {
                cmm_pause_menu_state = 0;
                cmm_menu_index = 0;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                if (gSramProbe != 0) {
                    nuPiWriteSram(0, &cmm_sram_configuration, ALIGN4(sizeof(cmm_sram_configuration)));
                }
            } else if (gPlayer1Controller->buttonPressed & (A_BUTTON|START_BUTTON)) {
                switch(cmm_menu_index) {
                    case 4:
                        cmm_pause_menu_state = 0;
                        cmm_menu_index = 0;
                        if (gSramProbe != 0) {
                            nuPiWriteSram(0, &cmm_sram_configuration, ALIGN4(sizeof(cmm_sram_configuration)));
                        }
                        play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                        break;
                    default:
                        play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                        cmm_sram_configuration.option_flags ^= (1<<cmm_menu_index);
                        break;
                }
            }
            break;

        case 2: //badge view
            if (gPlayer1Controller->buttonPressed & (A_BUTTON|B_BUTTON|START_BUTTON)) {
                cmm_pause_menu_state = 0;
            }
            draw_cmm_pause_badges();
            break;
    }

    return returnval;
}