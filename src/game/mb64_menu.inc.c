extern u8 gDialogCharWidths[256];

u8 mb64_ascii_lut[] = {
    0,0,0,0,0,0,0,0, // 0 - 7
    0,0,0xFE,0,0,0,0,0, // 8 - 15
    0x54,0x55,0x57,0x58,0,0,0,0, // 16 - 23
    0,0,0,0,0,0,0,0, // 24 - 31
    0x9E, /* */ 0xF2, /*!*/ 0x00, /*"*/ 0x00, /*#*/
    0x00, /*$*/ 0x71, /*%*/ 0xE5, /*&*/ 0x3E, /*'*/
    0xE1, /*(*/ 0xE3, /*)*/ 0x00, /***/ 0x00, /*+*/
    0x6F, /*,*/ 0x9F, /*-*/ 0x3F, /*.*/ 0x70, /*/*/
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
f32 mb64_menu_button_vels[10][3] = {0.f};
f32 mb64_menu_title_vels[3] = {0.f};
s16 mb64_menu_start_timer = -1;
s16 mb64_menu_end_timer = -1;
s8 mb64_menu_going_back = 1;

s8 mb64_mm_selected_level = 0;
u8 mb64_greyed_text = FALSE;

u16 mb64_konami_code[] = {
    U_JPAD, U_JPAD, D_JPAD, D_JPAD, L_JPAD, R_JPAD, L_JPAD, R_JPAD, B_BUTTON, A_BUTTON, START_BUTTON
};
u16 mb64_konami_code_cur_index = 0;

f32 clamp2(f32 x) {
  f32 lowerlimit = 0.0f;
  f32 upperlimit = 1.0f;
  if (x < lowerlimit) return lowerlimit;
  if (x > upperlimit) return upperlimit;
  return x;
}

f32 smoothstep2(f32 edge0, f32 edge1, f32 x) {
   // Scale, and clamp x to 0..1 range
   x = clamp2((x - edge0) / (edge1 - edge0));

   return x * x * (3.0f - 2.0f * x);
}

s32 get_string_width_ascii(char *str) {
    s16 strPos = 0;
    s16 width = 0;

    while (str[strPos] != 0) {
        width += gDialogCharWidths[mb64_ascii_lut[(u8)str[strPos]]];
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

void print_maker_string_ascii_alpha(s32 x, s32 y, char *str, s32 color, s32 alpha) {
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, alpha);
    print_generic_string_ascii(x-1, y-1, (u8 *)str);
    if (mb64_greyed_text) color += 2;
    gDPSetEnvColor(gDisplayListHead++, mb64_text_colors[color][0], mb64_text_colors[color][1], mb64_text_colors[color][2], alpha);
    print_generic_string_ascii(x, y, (u8 *)str);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

void print_maker_string_ascii(s32 x, s32 y, char *str, s32 color) {
    print_maker_string_ascii_alpha(x, y, str, color, 255);
}

void print_maker_string_ascii_centered_alpha(s32 x, s32 y, char *str, s32 color, s32 alpha) {
    s32 x1 = get_string_width_ascii(str);
    print_maker_string_ascii_alpha(x - x1/2, y, str, color, alpha);
}

void print_maker_string_ascii_centered(s32 x, s32 y, char *str, s32 color) {
    s32 x1 = get_string_width_ascii(str);
    print_maker_string_ascii_alpha(x - x1/2, y, str, color, 255);
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

f32 mb64_menu_toolbar_offsets[9];
f32 mb64_menu_list_offsets[90];

void animate_list_offset_reset(f32 offsets[], s32 length) {
    for (s32 i = 0; i < length; i++) {
        offsets[i] = 0.f;
    }
}
void animate_list_reset() {
    animate_list_offset_reset(mb64_menu_list_offsets, ARRAY_COUNT(mb64_menu_list_offsets));
}
void animate_toolbar_reset() {
    animate_list_offset_reset(mb64_menu_toolbar_offsets, ARRAY_COUNT(mb64_menu_toolbar_offsets));
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
s8 mb64_menu_scrolling[15][2] = {0};
// Controls saved scissor positions for nested scissoring
u8 mb64_global_scissor = 0;
u8 mb64_global_scissor_top = 0;
u8 mb64_global_scissor_bottom = SCREEN_HEIGHT;
u8 mb64_curr_settings_menu = 0; // Index of current page in the Settings menu
u8 mb64_curr_custom_tab = 0; // Index of current tab in Edit Custom Theme menu
u8 mb64_custom_theme_menu_open = FALSE; // If custom theme menu is currently in use

void full_menu_reset() {
    bzero(mb64_menu_button_vels, sizeof(mb64_menu_button_vels));
    bzero(mb64_menu_title_vels, sizeof(mb64_menu_title_vels));
    bzero(mb64_topleft_vels, sizeof(mb64_topleft_vels));
    bzero(mb64_menu_scrolling, sizeof(mb64_menu_scrolling));
    mb64_menu_start_timer = -1;
    mb64_menu_end_timer = -1;
    mb64_menu_going_back = 1;
    mb64_curr_settings_menu = 0;
    mb64_curr_custom_tab = 0;
    mb64_global_scissor = 0;
    mb64_global_scissor_top = 0;
    mb64_global_scissor_bottom = SCREEN_HEIGHT;
    mb64_menu_index = 0;
    mb64_menu_index_max = 256;
    mb64_tip_timer = 0;
    mb64_topleft_timer = 0;
    mb64_konami_code_cur_index = 0;
    mb64_custom_theme_menu_open = FALSE;
    mb64_greyed_text = FALSE;
    animate_list_reset();
    animate_toolbar_reset();
}

// sets some stuff after exiting play mode into the file selector
void mb64_init_exit_to_files() {
    mb64_menu_start_timer = 0;
    mb64_mode = MB64_MODE_UNINITIALIZED;
    mb64_menu_index = mb64_mm_selected_level;
    mb64_lopt_template = 0;
    mb64_lopt_size = 0;
    mb64_lopt_game = MB64_GAME_VANILLA;
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
s32 mb64_menu_option_sidescroll(s32 x, s32 y, s32 width,
                                char *prev, char *cur, char *next,
                                s8 scroll[2], u32 color, u32 dir) {
    s32 leftX = x - width * 2;
    s32 rightX = x + width * 2;
    s32 xOffset = 0;

    if (scroll[0] > 0) {
        scroll[0]--;
        xOffset = (scroll[0] * scroll[1] * width * 2) / 5;
        leftX += xOffset;
        rightX += xOffset;
    }

    f32 scissorLeft = x-width+5;
    f32 scissorRight = x+width-7;
    if (gIsWidescreen) {
        scissorLeft = scissorLeft * 0.75f + 40.f;
        scissorRight = scissorRight * 0.75f + 40.f;
    }
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE,
        MAX(               mb64_global_scissor, scissorLeft), mb64_global_scissor_top,
        MIN(SCREEN_WIDTH - mb64_global_scissor, scissorRight), mb64_global_scissor_bottom);
    
    print_maker_string_ascii_centered(x + xOffset, y, cur, color);
    if (leftX > x - width * 2) {
        print_maker_string_ascii_centered(leftX, y, prev, color);
    } else if (rightX < x + width * 2) {
        print_maker_string_ascii_centered(rightX, y, next, color);
    }

    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, mb64_global_scissor, mb64_global_scissor_top, SCREEN_WIDTH - mb64_global_scissor, mb64_global_scissor_bottom);

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


// More specialised version that handles a list of mb64_settings_buttons
// and is scrolled with the joystick
#define GET_BUTTON_STR(btn, index, buf) ((btn)->nameFunc ? (btn)->nameFunc(index, buf) : (btn)->nametable[index])

void mb64_menu_option_animation(s32 x, s32 y, s32 width, struct mb64_settings_button *btn, s32 i, s32 joystick) {
    s32 dir = 0;
    s32 selected = (i == mb64_menu_index);
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

    s32 result = mb64_menu_option_sidescroll(x, y, width,
                               prev, cur, next,
                               mb64_menu_scrolling[i], selected, dir);

    print_maker_string_ascii_centered(x - width, y, "<", selected);
    print_maker_string_ascii_centered(x + width, y, ">", selected);

    if (result) {
        *(btn->value) = (result == 1 ? nextVal : prevVal);
        play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
        if (btn->changedFunc) mb64_option_changed_func = btn->changedFunc;
    }
}

#define SETTINGS_MENU_SCROLL_WIDTH 140
typedef void (*mb64_page_display_func)(f32 xPos, f32 yPos);

void mb64_menu_page_animation(f32 yoff, void pageFunc(u32, f32, f32), s32 index, s32 pageCount, s8 scroll[2]) {
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

void mb64_render_topleft_text(void) {
    if (mb64_topleft_timer > 0) {

        if (mb64_topleft_timer > 30) {
            animate_menu_ease_in(mb64_topleft_vels, 250.f, 215.f, 0.4f, mb64_topleft_timer == mb64_topleft_max_timer);
        } else {
            animate_menu_generic(mb64_topleft_vels, 215.f, 0.f, 2.f, mb64_topleft_timer == 30);
        }

        print_maker_string_ascii(15,mb64_topleft_vels[0],mb64_topleft_message,mb64_topleft_is_tip ? MB64_TEXT_WHITE : MB64_TEXT_RED);
        mb64_topleft_timer--;
    }
}

f32 mb64_coord_vels[3] = {0.f};
void mb64_render_coord_display(void) {
    if (mb64_tip_timer != 0) {
        mb64_coord_vels[0] = 250.f;
        mb64_coord_vels[1] = 0.f;
        mb64_coord_vels[2] = 0.f;
        return;
    }
    animate_menu_ease_in(mb64_coord_vels, 255.f, 215.f, 0.4f, (mb64_topleft_is_tip && mb64_topleft_timer != 0));

    char buf[20];
    sprintf(buf, "%d, %d, %d", mb64_cursor_pos[0], mb64_cursor_pos[1], mb64_cursor_pos[2]);
    print_maker_string_ascii(255, mb64_coord_vels[0], buf, MB64_TEXT_WHITE);
}

char *mb64_get_floor_name(s32 index, UNUSED char *buffer) {
    return TILE_MATDEF(index).name;
}
char *mb64_get_coinstar_str(s32 index, char *buffer) {
    if (index == 0) {
        return "Disabled";
    }
    sprintf(buffer, "%d Coins", index*20);
    return buffer;
}
char *mb64_get_waterlevel_name(s32 index, char *buffer) {
    if (index == 0) {
        return "Disabled";
    }
    sprintf(buffer, "Y: %d", index);
    return buffer;
}
char *mb64_get_boundaryheight_name(s32 index, char *buffer) {
    sprintf(buffer, "Y: %d", index);
    return buffer;
}
char *mb64_get_category(s32 index, UNUSED char *buffer) {
    return mb64_matlist_names[index];
}
char *mb64_get_custom_mat(s32 index, char *buffer) {
    s32 category = *mb64_settings_mat_selector[0].value; // very hacky lmfao
    return mb64_mat_table[mb64_matlist[category] + index].name;
}

#define MB64_NUM_CUSTOM_TABS 14
char *mb64_custom_get_menu_name(s32 index) {
    if (index < 10) return mb64_theme_table[MB64_THEME_CUSTOM].mats[index].name;
    switch (index - 10) {
        case 0: return "Poles";
        case 1: return "Fences";
        case 2: return "Iron Meshes";
        case 3: return "Water";
    }
}

// Set mb64_lopt_seq_album and mb64_lopt_seq_song based on mb64_lopt_seq
void set_album_and_song_from_seq(u8 index) {
    u32 song = mb64_lopt_seq[index];
    u32 i = 0;
    do {
        if (song < mb64_settings_music_albums[i].size) {
            mb64_lopt_seq_album = i;
            mb64_lopt_seq_song = song;
            return;
        }
        song -= mb64_settings_music_albums[i].size;
    } while (++i < ARRAY_COUNT(mb64_music_album_string_table));
}
// Set mb64_lopt_seq from mb64_lopt_seq_album and mb64_lopt_seq_song
void set_seq_from_album_and_song(u8 index) {
    mb64_lopt_seq[index] = 0;
    u32 i = 0;
    do {
        if (i == mb64_lopt_seq_album) {
            mb64_lopt_seq[index] += mb64_lopt_seq_song;
            return;
        }
        mb64_lopt_seq[index] += mb64_settings_music_albums[i].size;
    } while (++i < ARRAY_COUNT(mb64_music_album_string_table));
}

// Set category and material index from a material enum
void get_category_and_mat_from_mat(u8 *category, u8 *matIndex, u8 mat) {
    u8 i = 1;
    do {
        if (mat < mb64_matlist[i]) {
            *category = i-1;
            *matIndex = mat - mb64_matlist[i-1];
            return;
        }
    } while (++i < ARRAY_COUNT(mb64_matlist));
}

void music_type_changed(void) {
    mb64_set_data_overrides();
    stop_background_music(get_current_background_music());
    play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, seq_musicmenu_array[mb64_lopt_seq[mb64_lopt_seq_seqtype]]), 0);
}
void music_category_changed(void) {
    mb64_lopt_seq_song = 0;
    song_changed();
    mb64_set_data_overrides();
}
void song_changed(void) {
    set_seq_from_album_and_song(mb64_lopt_seq_seqtype);
    stop_background_music(get_current_background_music());
    play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, seq_musicmenu_array[mb64_lopt_seq[mb64_lopt_seq_seqtype]]), 0);
}

void mb64_set_data_overrides(void) {
    // Music options
    set_album_and_song_from_seq(mb64_lopt_seq_seqtype);
    bcopy(&mb64_settings_music_albums[mb64_lopt_seq_album], &mb64_settings_music_buttons[MUSIC_SONG_INDEX], sizeof(struct mb64_settings_button));

    // Secret unlock
    if (mb64_lopt_secret) {
        mb64_settings_env_buttons[ENV_THEME_INDEX].size = ARRAY_COUNT(mb64_theme_string_table);
    } else {
        mb64_settings_env_buttons[ENV_THEME_INDEX].size = ARRAY_COUNT(mb64_theme_string_table) - 1;
    }

    // Custom theme
    if (mb64_lopt_theme == MB64_THEME_CUSTOM) {
        mb64_settings_menu_lengths[SETTINGS_ENV_INDEX] = ARRAY_COUNT(mb64_settings_env_buttons) + 1; // Terrain menu length for selecting
    } else {
        mb64_settings_menu_lengths[SETTINGS_ENV_INDEX] = ARRAY_COUNT(mb64_settings_env_buttons);
    }

    // Theme-specific data
    bzero(&mb64_toolbox_params, sizeof(mb64_toolbox_params));
    switch(mb64_lopt_game) {
        case MB64_GAME_BTCM:
            bcopy(&mb64_toolbox_btcm,&mb64_toolbox,sizeof(mb64_toolbox));
            mb64_exclamation_box_contents = sExclamationBoxContents_btcm;
            mb64_settings_menu_lengths[SETTINGS_MISC_INDEX] = ARRAY_COUNT(mb64_settings_misc_buttons); // includes costume
            mb64_settings_menus[SETTINGS_MISC_INDEX] = draw_mb64_settings_misc;
            break;
        case MB64_GAME_VANILLA:
            bcopy(&mb64_toolbox_vanilla,&mb64_toolbox,sizeof(mb64_toolbox));
            mb64_exclamation_box_contents = sExclamationBoxContents_vanilla;
            mb64_settings_menu_lengths[SETTINGS_MISC_INDEX] = ARRAY_COUNT(mb64_settings_misc_buttons_vanilla); // no costume
            mb64_settings_menus[SETTINGS_MISC_INDEX] = draw_mb64_settings_misc_vanilla;
            break;
    }
}

#define SCROLL_CUSTOM_TABS 12
#define SCROLL_CUSTOM 13
#define SCROLL_SETTINGS 14
#define MB64_SETTINGS_MENU_IS_STILL  ((mb64_menu_scrolling[SCROLL_SETTINGS][0] == 0) && (mb64_menu_start_timer == -1))

void draw_num_coins(f32 x, f32 y) {
    char buf[50];
    sprintf(buf, "Total Coins: %d", mb64_total_coin_count);
    print_maker_string_ascii_centered(x, y, buf, 0);
}

void draw_mb64_settings_misc(f32 xoff, f32 yoff) {
    animate_list_update(mb64_menu_list_offsets, ARRAY_COUNT(mb64_settings_misc_buttons), mb64_menu_index);
    for (s32 i=0;i<ARRAY_COUNT(mb64_settings_misc_buttons);i++) {
        print_maker_string_ascii( 55 +xoff+3*mb64_menu_list_offsets[i],154-(i*16)+yoff,mb64_settings_misc_buttons[i].str,(i==mb64_menu_index));
        mb64_menu_option_animation(200+xoff+3*mb64_menu_list_offsets[i],154-(i*16)+yoff,60,&mb64_settings_misc_buttons[i],i,mb64_joystick);
    }

    draw_num_coins(160+xoff, 95+yoff);
}

void draw_mb64_settings_misc_vanilla(f32 xoff, f32 yoff) {
    animate_list_update(mb64_menu_list_offsets, ARRAY_COUNT(mb64_settings_misc_buttons_vanilla), mb64_menu_index);
    for (s32 i=0;i<ARRAY_COUNT(mb64_settings_misc_buttons_vanilla);i++) {
        print_maker_string_ascii(55+xoff+3*mb64_menu_list_offsets[i],154-(i*16)+yoff,mb64_settings_misc_buttons_vanilla[i].str,(i==mb64_menu_index));
        mb64_menu_option_animation(200+xoff+3*mb64_menu_list_offsets[i],154-(i*16)+yoff,60,&mb64_settings_misc_buttons_vanilla[i],i,mb64_joystick);
    }

    draw_num_coins(160+xoff, 95+yoff);
}

void draw_mb64_settings_boundary(f32 xoff, f32 yoff) {
    animate_list_update(mb64_menu_list_offsets, ARRAY_COUNT(mb64_settings_boundary_buttons), mb64_menu_index);
    u32 numOptions = ARRAY_COUNT(mb64_settings_boundary_buttons);

    if (!(mb64_boundary_table[mb64_lopt_boundary] & MB64_BOUNDARY_INNER_WALLS)) {
        numOptions -= 1;
    }
    mb64_settings_menu_lengths[SETTINGS_BOUNDARY_INDEX] = numOptions;

    for (s32 i=0;i<ARRAY_COUNT(mb64_settings_boundary_buttons);i++) {
        if ((i == BOUNDARY_HEIGHT_INDEX) && (numOptions == ARRAY_COUNT(mb64_settings_boundary_buttons) - 1)) {
            mb64_greyed_text = TRUE;
        }
        print_maker_string_ascii(55 +xoff+3*mb64_menu_list_offsets[i],154-(i*16)+yoff,mb64_settings_boundary_buttons[i].str,(i==mb64_menu_index));
        mb64_menu_option_animation(200+xoff+3*mb64_menu_list_offsets[i],154-(i*16)+yoff,60,&mb64_settings_boundary_buttons[i],i,mb64_joystick);
    }
    mb64_greyed_text = FALSE;
}

#define CUSTOM_MENU_SCROLL_HEIGHT 105

s32 env_menu_handle_scroll() {
    s32 yOffset = (mb64_custom_theme_menu_open ? CUSTOM_MENU_SCROLL_HEIGHT : 0);
    if (mb64_menu_scrolling[SCROLL_CUSTOM][0] > 0) {
        mb64_menu_scrolling[SCROLL_CUSTOM][0]--;
        yOffset += (mb64_menu_scrolling[SCROLL_CUSTOM][0] * mb64_menu_scrolling[SCROLL_CUSTOM][1] * CUSTOM_MENU_SCROLL_HEIGHT) / 8;
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

    mb64_building_collision = FALSE;
    mb64_growth_render_type = 0;
    mb64_render_culling_off = TRUE;
    mb64_curr_mat_has_topside = FALSE;
    mb64_use_alt_uvs = FALSE;
    mb64_render_flip_normals = FALSE;
}

Gfx * custom_preview_gfx;
Vtx * custom_preview_vtx;

void finish_block_draw() {
    mb64_render_culling_off = FALSE;

    gSPDisplayList(gDisplayListHead++, mb64_curr_gfx);
    
    mb64_curr_gfx += mb64_gfx_index;
    mb64_gfx_index = 0;

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    create_dl_ortho_matrix();
}

void custom_theme_draw_block(f32 xpos, f32 ypos, s32 index) {
    prepare_block_draw(xpos, ypos);

    s8 pos[3];
    vec3_set(pos,32,32,32);

    if (index < NUM_MATERIALS_PER_THEME) {
        u8 renderedMat = mb64_curr_custom_theme.mats[index];
        u8 renderedTopmat = mb64_curr_custom_theme.topmats[index];
        if (!mb64_curr_custom_theme.topmatsEnabled[index]) renderedTopmat = renderedMat;

        render_preview_block(renderedMat, renderedTopmat, pos, &mb64_terrain_fullblock, 0, PROCESS_TILE_BOTH, TRUE);
    } else {
        mb64_use_alt_uvs = TRUE;
        mb64_curr_poly_vert_count = 4;
        if (index == 10) { // Poles
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], mb64_mat_table[mb64_curr_custom_theme.pole].gfx);
            set_render_mode( mb64_mat_table[mb64_curr_custom_theme.pole].type, TRUE);
            process_tile(pos, &mb64_terrain_pole, mb64_rot_selection);
        } else if (index == 11) { // Fence
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], mb64_fence_texs[mb64_curr_custom_theme.fence]);
            set_render_mode( MAT_CUTOUT, TRUE);
            process_tile(pos, &mb64_terrain_fence, mb64_rot_selection);
        } else if (index == 12) { // Iron Mesh
            set_render_mode( MAT_CUTOUT, TRUE);
            u8 connections[5] = {1,0,1,0,1};
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], mb64_bar_texs[mb64_curr_custom_theme.bars][1]);
            gSPClearGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK);
            render_bars_top(pos, connections);
            display_cached_tris();
            gSPSetGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK);
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], mb64_bar_texs[mb64_curr_custom_theme.bars][0]);
            render_bars_side(pos, connections);
        } else if (index == 13) { // Water
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], mb64_water_texs[mb64_curr_custom_theme.water]);
            set_render_mode( MAT_TRANSPARENT, TRUE);
            render_water(pos);
        }
        display_cached_tris();
        mb64_use_alt_uvs = FALSE;
    }

    gDPPipeSync(&mb64_curr_gfx[mb64_gfx_index++]);
    gDPSetRenderMode(&mb64_curr_gfx[mb64_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gDPSetTextureLUT(&mb64_curr_gfx[mb64_gfx_index++], G_TT_NONE);
    gSPEndDisplayList(&mb64_curr_gfx[mb64_gfx_index++]);

    finish_block_draw();
}

void custom_theme_draw_mat_selector(f32 xPos, f32 yPos, s32 startIndex, u8 *outputVar) {
    u8 tmpCategory;
    u8 tmpMaterial;
    get_category_and_mat_from_mat(&tmpCategory, &tmpMaterial, *outputVar);
    u8 oldCategory = tmpCategory;

    mb64_settings_mat_selector[0].value = &tmpCategory;
    mb64_settings_mat_selector[1].value = &tmpMaterial;
    mb64_settings_mat_selector[1].size = mb64_matlist[tmpCategory+1] - mb64_matlist[tmpCategory];

    print_maker_string_ascii(xPos+20+3*mb64_menu_list_offsets[startIndex], yPos, "Category:", (startIndex == mb64_menu_index));
    mb64_menu_option_animation(xPos+150+3*mb64_menu_list_offsets[startIndex], yPos, 50, &mb64_settings_mat_selector[0], startIndex, mb64_joystick);

    if (tmpCategory != oldCategory) {
        tmpMaterial = 0;
    }

    print_maker_string_ascii(xPos+20+3*mb64_menu_list_offsets[startIndex+1], yPos - 16, "Material:", (startIndex+1 == mb64_menu_index));
    mb64_menu_option_animation(xPos+150+3*mb64_menu_list_offsets[startIndex+1], yPos - 16, 50, &mb64_settings_mat_selector[1], startIndex + 1, mb64_joystick);

    *outputVar = mb64_matlist[tmpCategory] + tmpMaterial;
}

// The amount to offset mb64_menu_index by when in the custom theme menu
#define CUSTOM_INDEX_OFFSET (ARRAY_COUNT(mb64_settings_env_buttons) + 1)

char *mb64_slipperiness_strs[] = {
    /* SURFACE_CLASS_DEFAULT */        "(Smooth)",
    /* SURFACE_CLASS_VERY_SLIPPERY */  "(Slippery)",
    /* SURFACE_CLASS_SLIPPERY */       "(Slippery)",
    /* SURFACE_CLASS_NOT_SLIPPERY */   "(Walkable)",
    /* Hazard */                       "(Hazardous)",
};
u8 mb64_slipperiness_clrs[] = {
    MB64_TEXT_YELLOW,
    MB64_TEXT_LIGHTBLUE,
    MB64_TEXT_LIGHTBLUE,
    MB64_TEXT_WHITE,
    MB64_TEXT_RED,
};

void mb64_custom_theme_block_page(u32 index, f32 xPos, f32 yPos) {
    u32 topmatDisabled = !mb64_curr_custom_theme.topmatsEnabled[index];
    char *topmatText = "";

    if (mb64_custom_theme_menu_open) {
        if (topmatDisabled) {
            topmatText = "Enable Top Material...";
            mb64_menu_index_max = 3;
        } else {
            topmatText = "Disable Top Material...";
            mb64_menu_index_max = 5;
        }
    }

    // Selector for main material
    custom_theme_draw_mat_selector(xPos, 160 + yPos, CUSTOM_INDEX_OFFSET, &mb64_curr_custom_theme.mats[index]);

    // Selector for top material
    print_maker_string_ascii(xPos+55+3*mb64_menu_list_offsets[CUSTOM_INDEX_OFFSET+2], 128 + yPos, topmatText, (CUSTOM_INDEX_OFFSET+2 == mb64_menu_index));
    mb64_greyed_text = topmatDisabled;
    custom_theme_draw_mat_selector(xPos, 112 + yPos, CUSTOM_INDEX_OFFSET+3, &mb64_curr_custom_theme.topmats[index]);
    mb64_greyed_text = FALSE;

    if (mb64_menu_index == CUSTOM_INDEX_OFFSET + 2) { // Enable/disable button
        if (gPlayer1Controller->buttonPressed & A_BUTTON) {
            play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
            mb64_curr_custom_theme.topmatsEnabled[index] ^= 1;
        }
    }

    // Print material info
    s32 col;
    if (mb64_curr_custom_theme.topmatsEnabled[index]) {
        col = mb64_mat_table[mb64_curr_custom_theme.topmats[index]].col;
    } else {
        col = mb64_mat_table[mb64_curr_custom_theme.mats[index]].col;
    }
    s32 class;
    if (SURFACE_IS_BURNING(col) || SURFACE_IS_QUICKSAND(col)) class = 4;
    else class = get_floor_class(col);

    print_maker_string_ascii_centered_alpha(xPos + 260, yPos + 100, mb64_slipperiness_strs[class], mb64_slipperiness_clrs[class], 150);
}

void mb64_custom_theme_pole_page(f32 xPos, f32 yPos) {
    if (mb64_custom_theme_menu_open) mb64_menu_index_max = 2;
    custom_theme_draw_mat_selector(xPos, 150 + yPos, CUSTOM_INDEX_OFFSET, &mb64_curr_custom_theme.pole);
}

void mb64_custom_theme_other_page(f32 xPos, f32 yPos, u32 otherIndex) {
    if (mb64_custom_theme_menu_open) mb64_menu_index_max = 1;

    print_maker_string_ascii(xPos+20+3*mb64_menu_list_offsets[CUSTOM_INDEX_OFFSET], yPos + 135, mb64_settings_other_selectors[otherIndex].str, (CUSTOM_INDEX_OFFSET == mb64_menu_index));
    mb64_menu_option_animation(xPos+150+3*mb64_menu_list_offsets[CUSTOM_INDEX_OFFSET], yPos + 135, 50, &mb64_settings_other_selectors[otherIndex], CUSTOM_INDEX_OFFSET, mb64_joystick);
}

void mb64_custom_theme_render_page(u32 index, f32 xPos, f32 yPos) {
    if (index < NUM_MATERIALS_PER_THEME) {
        mb64_custom_theme_block_page(index, xPos, yPos);
    } else if (index == 10) {
        mb64_custom_theme_pole_page(xPos, yPos);
    } else {
        mb64_custom_theme_other_page(xPos, yPos, index - 11);
    }


    custom_theme_draw_block(-xPos - 100, yPos + 10, index);
}

void draw_mb64_settings_custom_theme(f32 yoff) {
    s32 dir = 0;

    if (mb64_custom_theme_menu_open) {
        if (gPlayer1Controller->buttonPressed & L_TRIG) dir = -1;
        if (gPlayer1Controller->buttonPressed & R_TRIG) dir = 1;
    }

    s32 prevMenu = (mb64_curr_custom_tab - 1 + MB64_NUM_CUSTOM_TABS) % MB64_NUM_CUSTOM_TABS;
    s32 nextMenu = (mb64_curr_custom_tab + 1) % MB64_NUM_CUSTOM_TABS;
    char *cur = mb64_custom_get_menu_name(mb64_curr_custom_tab);
    char *prev = mb64_custom_get_menu_name(prevMenu);
    char *next = mb64_custom_get_menu_name(nextMenu);
    print_maker_string_ascii_centered(80, yoff + 185, "< L", MB64_TEXT_WHITE);
    print_maker_string_ascii_centered(240, yoff + 185, "R >", MB64_TEXT_WHITE);
    s32 result = mb64_menu_option_sidescroll(160, 185+yoff, 70,
                                prev, cur, next,
                                mb64_menu_scrolling[SCROLL_CUSTOM_TABS], FALSE, dir); 

    // Change selected menu if it was switched
    if (result) {
        mb64_curr_custom_tab = (result == 1 ? nextMenu : prevMenu);
        play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
    }
    // Reset index halfway through animation
    if (mb64_menu_scrolling[SCROLL_CUSTOM_TABS][0] == 2) {
        mb64_menu_index = CUSTOM_INDEX_OFFSET;
    }

    custom_preview_gfx = (Gfx*)alloc_display_list(50*sizeof(Gfx));
    custom_preview_vtx = (Vtx*)alloc_display_list(100*sizeof(Vtx));

    mb64_curr_gfx = custom_preview_gfx;
    mb64_curr_vtx = custom_preview_vtx;
    mb64_gfx_index = 0;

    mb64_menu_page_animation(yoff, mb64_custom_theme_render_page, mb64_curr_custom_tab, MB64_NUM_CUSTOM_TABS, mb64_menu_scrolling[SCROLL_CUSTOM_TABS]);

    // This code is so fucking disgusting.
    // Edit all the vertices for the drawn preview blocks here.
    // Done outside the main block draw to be able to affect multiple blocks at once
    for (s32 i = 0; i < ARRAY_COUNT(preview_vtx); i++) {
        // Offset all vertices
        custom_preview_vtx[i].v.ob[0] -= TILE_SIZE/2;
        custom_preview_vtx[i].v.ob[2] -= TILE_SIZE/2;
    }
}

void draw_mb64_settings_env(f32 xoff, f32 yoff) {
    s32 oldtheme = mb64_lopt_theme;
    u8 beginScrollAnim = FALSE;

    if (mb64_custom_theme_menu_open) {
        mb64_menu_index += CUSTOM_INDEX_OFFSET;
    }

    animate_list_update(mb64_menu_list_offsets, 10, mb64_menu_index);
    for (s32 i=0;i<ARRAY_COUNT(mb64_settings_env_buttons);i++) {
        print_maker_string_ascii(55+xoff+3*mb64_menu_list_offsets[i],154-(i*16)+yoff,mb64_settings_env_buttons[i].str,(i==mb64_menu_index));
        mb64_menu_option_animation(200+xoff+3*mb64_menu_list_offsets[i],154-(i*16)+yoff,60,&mb64_settings_env_buttons[i],i,mb64_joystick);
    }

    if (mb64_lopt_theme == MB64_THEME_CUSTOM) {
        animate_menu_ease_in(mb64_menu_button_vels[0], 0.f, 30.f, 0.4f, oldtheme != MB64_THEME_CUSTOM);
    } else {
        animate_menu_generic(mb64_menu_button_vels[0], 30.f, 0.f, -2.f, oldtheme == MB64_THEME_CUSTOM);
    }
    mb64_set_data_overrides();

    s32 index = ARRAY_COUNT(mb64_settings_env_buttons);
    s32 customThemeY = 120-(index*16) + mb64_menu_button_vels[0][0];
    print_maker_string_ascii_centered(160+xoff+3*mb64_menu_list_offsets[index],customThemeY + yoff,"Edit Custom Theme...",(index == mb64_menu_index));
    draw_mb64_settings_custom_theme(yoff - CUSTOM_MENU_SCROLL_HEIGHT);

    if ((mb64_menu_scrolling[SCROLL_CUSTOM][0] == 0) && MB64_SETTINGS_MENU_IS_STILL) {
        if (!mb64_custom_theme_menu_open) {
            if (mb64_menu_index == index) {
                if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                    // Open custom theme menu
                    mb64_custom_theme_menu_open = TRUE;
                    mb64_menu_scrolling[SCROLL_CUSTOM][0] = 8;
                    mb64_menu_scrolling[SCROLL_CUSTOM][1] = -1;
                    mb64_menu_index = CUSTOM_INDEX_OFFSET;
                    play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                }
            }
        } else {
            if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                mb64_custom_theme_menu_open = FALSE;
                mb64_menu_scrolling[SCROLL_CUSTOM][0] = 8;
                mb64_menu_scrolling[SCROLL_CUSTOM][1] = 1;
                mb64_menu_index = index;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                update_custom_theme();
                generate_terrain_gfx();
            }
        }
    }

    if (!mb64_lopt_secret && !mb64_custom_theme_menu_open) {
        u16 nextButton = mb64_konami_code[mb64_konami_code_cur_index];
        if (gPlayer1Controller->buttonPressed & nextButton) {
            mb64_konami_code_cur_index++;
            if (mb64_konami_code_cur_index == 11) {
                mb64_konami_code_cur_index = 0;
                mb64_lopt_secret = TRUE;
                mb64_set_data_overrides();
                play_puzzle_jingle();
            }
        } else if (gPlayer1Controller->buttonPressed) {
            mb64_konami_code_cur_index = 0;
        }
    }

    if (mb64_custom_theme_menu_open) {
        mb64_menu_index -= CUSTOM_INDEX_OFFSET;
    }
}

void draw_mb64_settings_music(f32 xoff, f32 yoff) {
    animate_list_update(mb64_menu_list_offsets, ARRAY_COUNT(mb64_settings_music_buttons), mb64_menu_index);
    for (s32 i=0;i<ARRAY_COUNT(mb64_settings_music_buttons);i++) {
        print_maker_string_ascii(35+xoff+3*mb64_menu_list_offsets[i],154-(i*20)+yoff,mb64_settings_music_buttons[i].str,(i==mb64_menu_index));
        mb64_menu_option_animation(190+xoff+3*mb64_menu_list_offsets[i],154-(i*20)+yoff,100,&mb64_settings_music_buttons[i],i,mb64_joystick);
    }
}

extern u8 mb64_mm_state; //externing a variable in the same file that it's defined in? more likely than you think. how heinous.
void draw_mb64_settings_system(f32 xoff, f32 yoff) {
    char strbuf[50];
    animate_list_update(mb64_menu_list_offsets, 3, mb64_menu_index);
    for (s32 i=0;i<2;i++) {
        print_maker_string_ascii_centered(160+xoff+3*mb64_menu_list_offsets[i],160-(i*16)+yoff,mb64_settings_system_buttons[i],(i==mb64_menu_index));
    }
    
    int vtx_perc = ((f32)mb64_vtx_total/(f32)MB64_VTX_SIZE)*100.0f;
    int tile_perc = ((f32)mb64_tile_count/(f32)MB64_TILE_POOL_SIZE)*100.0f;
    int obj_perc = ((f32)mb64_object_limit_count/(f32)MB64_MAX_OBJS)*100.0f;
    sprintf(strbuf,"Vertices: %d/50k (%d%%)",mb64_vtx_total, vtx_perc);
    print_maker_string_ascii(20+xoff+3*mb64_menu_list_offsets[2], 110+yoff,strbuf,MB64_TEXT_WHITE);
    sprintf(strbuf,"Tiles:    %d/15k (%d%%)",mb64_tile_count, tile_perc);
    print_maker_string_ascii(20+xoff+3*mb64_menu_list_offsets[2], 95+yoff,strbuf,MB64_TEXT_WHITE);

    sprintf(strbuf,"Objs:  %d/512 (%d%%)",mb64_object_limit_count, obj_perc);
    print_maker_string_ascii(305+xoff+3*mb64_menu_list_offsets[2]-get_string_width_ascii(strbuf), 95+yoff,strbuf,MB64_TEXT_WHITE);

    if ((gPlayer1Controller->buttonPressed & A_BUTTON) && MB64_SETTINGS_MENU_IS_STILL) {
        switch (mb64_menu_index) {
            case 0: // save and quit
                if (mount_success == FR_OK) {
                    save_level();
                    play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
                    mb64_mm_state = MM_FILES;
                } else {
                    mb64_mm_state = MM_MAIN_LIMITED;
                }
                fade_into_special_warp(WARP_SPECIAL_MARIO_HEAD_REGULAR, 0); // reset game
                break;
            case 1: // play level
                if (mount_success == FR_OK) {
                    save_level();
                }
                mb64_target_mode = MB64_MODE_PLAY;
                mb64_level_action = MB64_LA_TEST_LEVEL;
                reset_play_state();
                level_trigger_warp(gMarioState, WARP_OP_LOOK_UP);
                sSourceWarpNodeId = 0x0A;
                play_sound(SOUND_MENU_STAR_SOUND_LETS_A_GO, gGlobalSoundSource);
                break;
        }
    }
}

#define SETTINGS_MENU_COUNT ARRAY_COUNT(mb64_settings_menus)

void mb64_settings_menu_page(u32 index, f32 xPos, f32 yPos) {
    mb64_settings_menus[index](xPos, yPos);
}

void draw_mb64_settings_menu(f32 yoff) {
    mb64_menu_page_animation(yoff, mb64_settings_menu_page, mb64_curr_settings_menu, SETTINGS_MENU_COUNT, mb64_menu_scrolling[SCROLL_SETTINGS]);
}

void draw_mb64_menu(void) {
    if (mb64_menu_state != MB64_MAKE_SCREENSHOT) {
        create_dl_translation_matrix(MENU_MTX_PUSH, 19, 36, 0);
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
        gSPDisplayList(gDisplayListHead++, &bg_back_graund_mesh);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

        animate_list_update(mb64_menu_toolbar_offsets, ARRAY_COUNT(mb64_menu_toolbar_offsets), mb64_toolbar_index);
        for (s32 i = 0; i < 9; i++) {
            s32 op = (mb64_toolbar_index == i ? 255 : 200);
            create_dl_translation_matrix(MENU_MTX_PUSH, 34+(i*32), 20 + (5 * mb64_menu_toolbar_offsets[i]), 0);
            gDPSetEnvColor(gDisplayListHead++, op, op, op, 255);

            Gfx *mat = get_button_tex(mb64_toolbar[i], mb64_toolbar_params[i]);

            gSPDisplayList(gDisplayListHead++, mat);//texture
            gSPDisplayList(gDisplayListHead++, &uibutton_button_mesh);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
        }
        gSPDisplayList(gDisplayListHead++, &mat_revert_b_btn_check);
    }

    //TOOLBOX
    switch (mb64_menu_state) {
        case MB64_MAKE_MAIN:
            mb64_render_topleft_text();
            mb64_render_coord_display();
            break;

        case MB64_MAKE_TOOLBOX:
            // In/out animation
            if (mb64_menu_start_timer != -1) {
                animate_menu_ease_in(mb64_menu_title_vels, 150.f, -10.f, 0.35f, mb64_menu_start_timer == 0);
                if (mb64_menu_start_timer++ > 10) {
                    mb64_menu_start_timer = -1;
                }
            } else if (mb64_menu_end_timer != -1) {
                animate_menu_generic(mb64_menu_title_vels, -10.f, 0.f, 4.f, mb64_menu_end_timer == 0);
                mb64_menu_end_timer++;
                mb64_joystick = 0;
            } else {
                if (gPlayer1Controller->buttonPressed & (B_BUTTON | START_BUTTON)) {
                    mb64_menu_end_timer = 0;
                    play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                }
            }
            f32 yOff = mb64_menu_title_vels[0];

            create_dl_translation_matrix(MENU_MTX_PUSH, 19, 235+yOff, 0);
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
            gSPDisplayList(gDisplayListHead++, &bg_back_graund_mesh);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            animate_list_update(mb64_menu_list_offsets, ARRAY_COUNT(mb64_menu_list_offsets), mb64_toolbox_index);

            for (s32 i = 0; i < (s32)sizeof(mb64_toolbox); i++) {
                s32 op = 255;
                if (i == mb64_toolbox_index) {
                    op = 100;
                }
                create_dl_translation_matrix(MENU_MTX_PUSH, GET_TOOLBOX_X(i), GET_TOOLBOX_Y(i) + 4*mb64_menu_list_offsets[i] + yOff, 0);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, op, 255);

                Gfx *mat = get_button_tex(mb64_toolbox[i], mb64_toolbox_params[i]);

                gSPDisplayList(gDisplayListHead++, mat);//texture
                gSPDisplayList(gDisplayListHead++, &uibutton_button_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);    
            }

            if (mb64_toolbox_transition_btn_render) {
                //f32 dist = sqrtf(sqr(mb64_toolbox_transition_btn_tx - mb64_toolbox_transition_btn_x) + sqr(mb64_toolbox_transition_btn_ty - mb64_toolbox_transition_btn_y));
                //f32 multiplier = MAX(0.5f - (dist * 0.01f), 0.2f);
                //mb64_toolbox_transition_btn_x = approach_f32_asymptotic(mb64_toolbox_transition_btn_x, mb64_toolbox_transition_btn_tx, multiplier);
                //mb64_toolbox_transition_btn_y = approach_f32_asymptotic(mb64_toolbox_transition_btn_y, mb64_toolbox_transition_btn_ty, multiplier);

                create_dl_translation_matrix(MENU_MTX_PUSH, mb64_toolbox_transition_btn_tx, mb64_toolbox_transition_btn_ty, 0);
                gSPDisplayList(gDisplayListHead++, mb64_toolbox_transition_btn_old_gfx);//old texture
                gSPDisplayList(gDisplayListHead++, &uibutton_button_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

                f32 x = smoothstep(mb64_toolbox_transition_btn_x,mb64_toolbox_transition_btn_tx,mb64_toolbox_transition_progress);
                f32 y = smoothstep(mb64_toolbox_transition_btn_y,mb64_toolbox_transition_btn_ty,mb64_toolbox_transition_progress);

                create_dl_translation_matrix(MENU_MTX_PUSH, x, y, 0);
                gSPDisplayList(gDisplayListHead++, mb64_toolbox_transition_btn_gfx);//texture
                gSPDisplayList(gDisplayListHead++, &uibutton_button_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

                mb64_toolbox_transition_progress += 0.08f;
                if (mb64_toolbox_transition_progress > 1.0f) {
                    mb64_toolbox_transition_progress = 1.0f;
                }
            }
            gSPDisplayList(gDisplayListHead++, &mat_revert_b_btn_check);

            if (mb64_toolbox_x_offset == TOOLBOX_OFFSET_MIN) {
                print_maker_string_ascii(310 + sins(gGlobalTimer*0x300)*2.5f, 147+yOff, ">", MB64_TEXT_WHITE);
            }
            if (mb64_toolbox_x_offset == TOOLBOX_OFFSET_MAX) {
                print_maker_string_ascii(7 - sins(gGlobalTimer*0x300)*2.5f, 147+yOff, "<", MB64_TEXT_WHITE);
            }

            s32 strx = GET_TOOLBOX_X(mb64_toolbox_index) + 20;
            s32 lowerstrx = strx;
            s32 stry = GET_TOOLBOX_Y(mb64_toolbox_index) - 5 + yOff + 4*mb64_menu_list_offsets[mb64_toolbox_index];

            if (mb64_toolbox[mb64_toolbox_index] != MB64_BUTTON_BLANK) {
                u32 isMulti = mb64_ui_buttons[mb64_toolbox[mb64_toolbox_index]].multiObj;
                char *buttonName = get_button_str(mb64_toolbox[mb64_toolbox_index]);
                char stringBuf[50];
                if (isMulti) stry += 8;

                s32 strLen = get_string_width_ascii(buttonName);
                s32 lowerStrLen = 0;

                if (isMulti) {
                    u32 objId = mb64_ui_buttons[mb64_toolbox[mb64_toolbox_index]].idList[mb64_toolbox_params[mb64_toolbox_index]];
                    sprintf(stringBuf, "< %s >", mb64_object_type_list[objId].name);
                    lowerStrLen = get_string_width_ascii(stringBuf);
                }

                if ((lowerstrx + lowerStrLen > SCREEN_WIDTH - 5) || (strx + strLen > SCREEN_WIDTH - 5)) {
                    lowerstrx -= lowerStrLen+45;
                    strx -= strLen+45;
                }

                gDPPipeSync(gDisplayListHead++);
                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
                gDPSetCombineMode(gDisplayListHead++, G_CC_ENVIRONMENT, G_CC_ENVIRONMENT);
                gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
                gDPFillRectangle(gDisplayListHead++, strx-5, 240-stry-14, strx + strLen + 5, 240-stry+1);
                if (isMulti) {
                    gDPFillRectangle(gDisplayListHead++, lowerstrx-5, 240-stry+1, lowerstrx + lowerStrLen + 5, 240-stry+16);
                    print_maker_string_ascii(lowerstrx, stry-15, stringBuf, MB64_TEXT_YELLOW);
                }
                print_maker_string_ascii(strx, stry, buttonName, MB64_TEXT_YELLOW);
            }

            break;

        case MB64_MAKE_SETTINGS:
            // In/out animation
            if (mb64_menu_start_timer != -1) {
                animate_menu_generic(mb64_menu_button_vels[0], 30.f, 0, 0, mb64_lopt_theme == MB64_THEME_CUSTOM); // mega hacky
                animate_menu_ease_in(mb64_menu_title_vels, 150.f, -10.f, 0.35f, mb64_menu_start_timer == 0);
                if (mb64_menu_start_timer++ > 10) {
                    mb64_menu_start_timer = -1;
                }
            } else if (mb64_menu_end_timer != -1) {
                animate_menu_generic(mb64_menu_title_vels, -10.f, 0.f, 4.f, mb64_menu_end_timer == 0);
                mb64_menu_end_timer++;
                mb64_joystick = 0;
            } else {
                if ((gPlayer1Controller->buttonPressed & START_BUTTON) ||
                    ((gPlayer1Controller->buttonPressed & B_BUTTON) && !mb64_custom_theme_menu_open)) {
                    if (!(gPlayer1Controller->buttonPressed & mb64_konami_code[mb64_konami_code_cur_index])) {
                        mb64_menu_end_timer = 0;
                        play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                        if (mb64_custom_theme_menu_open) {
                            update_custom_theme();
                            generate_terrain_gfx();
                        }
                    }
                }
            }
            yOff = mb64_menu_title_vels[0];

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

            mb64_global_scissor = (gIsWidescreen ? 51 : 15); // widescreen adjust: (x*3/4 + 40)
            mb64_global_scissor_top = MAX(0, 15 - yOff);
            mb64_global_scissor_bottom = MAX(0, 145 - yOff);
            gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, mb64_global_scissor, mb64_global_scissor_top, SCREEN_WIDTH - mb64_global_scissor, mb64_global_scissor_bottom);
            yOff += env_menu_handle_scroll();

            // Level name
            print_maker_string_ascii_centered(SCREEN_WIDTH/2,210+yOff,mb64_file_info.fname,MB64_TEXT_WHITE);

            switch(mb64_joystick) {
                case 2:
                    mb64_menu_index++;
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                break;
                case 4:
                    mb64_menu_index--;
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                break;
            }

            // Begin rendering top header
            s32 prevMenu = (mb64_curr_settings_menu - 1 + SETTINGS_MENU_COUNT) % SETTINGS_MENU_COUNT;
            s32 nextMenu = (mb64_curr_settings_menu + 1) % SETTINGS_MENU_COUNT;
            char *cur = mb64_settings_menu_names[mb64_curr_settings_menu];
            char *prev = mb64_settings_menu_names[prevMenu];
            char *next = mb64_settings_menu_names[nextMenu];

            // Scroll input
            s32 dir = 0;
            if (!mb64_custom_theme_menu_open) {
                if (mb64_menu_scrolling[SCROLL_CUSTOM][0] == 0) {
                    if (gPlayer1Controller->buttonPressed & L_TRIG) dir = -1;
                    if (gPlayer1Controller->buttonPressed & R_TRIG) dir = 1;
                }
                mb64_menu_index_max = mb64_settings_menu_lengths[mb64_curr_settings_menu];;
            }
            mb64_menu_index = (mb64_menu_index + mb64_menu_index_max) % mb64_menu_index_max;

            print_maker_string_ascii_centered(80, yOff + 185, "< L", MB64_TEXT_WHITE);
            print_maker_string_ascii_centered(240, yOff + 185, "R >", MB64_TEXT_WHITE);
            s32 result = mb64_menu_option_sidescroll(160, 185+yOff, 70,
                                       prev, cur, next,
                                       mb64_menu_scrolling[SCROLL_SETTINGS], FALSE, dir); 

            // Change selected menu if it was switched
            if (result) {
                mb64_curr_settings_menu = (result == 1 ? nextMenu : prevMenu);
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
            }
            // Reset index halfway through animation
            if (mb64_menu_scrolling[SCROLL_SETTINGS][0] == 2) {
                mb64_menu_index = 0;
            }

            // Draw menu + scroll
            draw_mb64_settings_menu(yOff);
            mb64_global_scissor = 0;
            mb64_global_scissor_top = 0;
            mb64_global_scissor_bottom = SCREEN_HEIGHT;
            gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            break;

        case MB64_MAKE_TRAJECTORY:
            print_maker_string(20,210,mb64_txt_recording,TRUE);
            mb64_render_topleft_text();
            mb64_render_coord_display();
            break;

        case MB64_MAKE_SCREENSHOT:
            if (mb64_freecam_snap || !mb64_freecam_help) {
                return;
            }
            print_maker_string(20,210,mb64_txt_freecam,TRUE);
            //mb64_render_topleft_text();
            break;

        case MB64_MAKE_SELECT_DIALOG:
            if (TRUE) { //4 my compiler
                char stringBuf[50];
                sprintf(stringBuf,"^ Subject: %s |", mb64_dialog_subjects[mb64_dialog_subject_index].name);
                print_maker_string_ascii_centered(160,210,stringBuf,MB64_TEXT_WHITE);
                sprintf(stringBuf,"< Topic: %s >",mb64_dialog_subjects[mb64_dialog_subject_index].topic_list[mb64_dialog_topic_index].name);
                print_maker_string_ascii_centered(160,190,stringBuf,MB64_TEXT_WHITE);

                render_dialog_entry_preview(mb64_dialog_subjects[mb64_dialog_subject_index].topic_list[mb64_dialog_topic_index].dialog_id);
            }
            break;

    }

    if ((mb64_menu_state != MB64_MAKE_TRAJECTORY)&&(mb64_menu_state != MB64_MAKE_SCREENSHOT)) {
        s32 currentX = 15;
        char *buttonName = get_button_str(mb64_toolbar[mb64_toolbar_index]);
        print_maker_string_ascii(currentX,45,buttonName,MB64_TEXT_WHITE);
        currentX += get_string_width_ascii(buttonName) + 10;

        char *yellowStr = NULL;
        if (mb64_place_mode == MB64_PM_OBJ) {
            if (mb64_ui_buttons[mb64_toolbar[mb64_toolbar_index]].multiObj) {
                yellowStr = mb64_object_type_list[mb64_ui_buttons[mb64_toolbar[mb64_toolbar_index]].idList[mb64_toolbar_params[mb64_toolbar_index]]].name;
            } else {
                if (mb64_ui_buttons[mb64_toolbar[mb64_toolbar_index]].names) {
                    yellowStr = mb64_ui_buttons[mb64_toolbar[mb64_toolbar_index]].names[mb64_toolbar_params[mb64_toolbar_index]];
                }
            }
        } else if (mb64_terrain_info_list[mb64_id_selection].terrain) {
            yellowStr = TILE_MATDEF(mb64_mat_selection).name;

            if (mb64_id_selection < TILE_END_OF_FLIPPABLE) {
                if (mb64_upsidedown_tile) {
                    print_maker_string_ascii(currentX,45,"(|)",MB64_TEXT_WHITE);
                } else {
                    print_maker_string_ascii(currentX,45,"(^)",MB64_TEXT_WHITE);
                }
                currentX += 25;
            }
        }
        if (yellowStr) {
            currentX += 15;
            print_maker_string_ascii(currentX,45,"<",MB64_TEXT_YELLOW);
            print_maker_string_ascii(currentX + 20,45,yellowStr,MB64_TEXT_YELLOW);
            currentX += get_string_width_ascii(yellowStr) + 30;
            print_maker_string_ascii(currentX,45,">",MB64_TEXT_YELLOW);
        }
    }
}

struct mb64_credits_entry {
    char * text;
    u32 color;
};

struct mb64_credits_entry mb64_credits[] = {
    {"Mario Builder 64",1},
    {"By Rovertronic & Arthurtilly",0},
    {"2024",0},
    {"",0},
    {"HackerSM64",1},
    {"HackerN64 Team",0},
    {"",0},
    {"SD Card Support",1},
    {"Devwizard",0},
    {"Falcobuster",0},
    {"",0},
    {"Title Screen Model",1},
    {"Biobak",0},
    {"",0},
    {"Object Models and Textures",1},
    {"BroDute",0},
    {"Thodds",0},
    {"Yoshi Milkman",0},
    {"Dan GPTV",0},
    {"Lilaa3",0},
    {"",0},
    {"GitHub Contributors",1},
    {"aglab2",0},
    {"ArcticJaguar725",0},
    {"jefftastic",0},
    {"Polprzewodnikowy",0},
    {"",0},
    {"Beyond the Cursed Mirror OST",1},
    {"SpK",0},
    {"Thorndust",0},
    {"",0},
    {"Beyond the Cursed Mirror Badge Art",1},
    {"HeroTechne",0},
    {"Pyro Jay",0},
    {"",0},
    {"Music Ports",1},
    {"SMWCentral",0},
    {"SM64 Editor",0},
    {"",0},
    {"Beta Testers",1},
    {"Arceveti",0},
    {"CaptainTheo86",0},
    {"CowQuack",0},
    {"Dao-Kha",0},
    {"DisturbingNose",0},
    {"FrostyZako",0},
    {"Gmd",0},
    {"hacker2077",0},
    {"Haffey",0},
    {"Kaze Emanuar",0},
    {"KeyBlader",0},
    {"KirbySuper",0},
    {"RationaLess",0},
    {"SpK",0},
    {"Vortoxium",0},
    {NULL, 0},
};

struct mb64_credits_entry mb64_v1_1_changelog[] = {
    {"Mario Builder 64 - v1.1 Changelog",1},
    {"",0},
    {"", 0},
    {"Major Changes", 1},
    {"", 0},
    {"- Increased vertex limit from 40,000 to 50,000", 0},
    {"- Increased tile limit from 10,000 to 15,000", 0},
    {"- New boundary type: Interior"},
    {"- New object: Inverted Timed Box"},
    {"- Ability to place multiple objects/tiles in the same spot", 0},
    {"- Wooden Platforms form a stack when placed vertically", 0},
    {"- Objects can now trigger Activated Moving Platforms", 0},
    {"- Bowling Balls can now destroy boxes and kill enemies", 0},
    {"- Custom Theme menu now shows slipperiness of current tile", 0},
    {"- Display the current number of placed objects in the", 0},
    {"    editor when placing Stars or Red Coins", 0},
    {"- Koopa the Quick respawns after losing the race", 0},
    {"- Dialog to exit a level after collecting every star",0},
    {"", 0},
    {"Conveyors", 1},
    {"", 0},
    {"- Added thin and sloped conveyors"},
    {"- Added red/blue on-off conveyors"},
    {"- The underside of conveyors are now hangable"},
    {"- Improved conveyor physics"},
    {"", 0},
    {"Imbuing System", 1},
    {"", 0},
    {"- All enemies can now be given objects to drop on death", 0},
    {"- Objects can be placed inside ! Boxes", 0},
    {"- Red Coins can now be placed inside enemies/bosses/boxes", 0},
    {"- Dropped objects appear at the object's last safe location", 0},
    {"- Boxes with yellow coins now drop 3 coins instead of 1", 0},
    {"- Boos and Moneybags now show the item they will drop", 0},
    {"", 0},
    {"Minor Tweaks", 1},
    {"", 0},
    {"- Heavily improved Thwomp physics and interactions", 0},
    {"- Physics given to Mr. Blizzard and Piranha Plants", 0},
    {"- AI and physics improvements for all enemies", 0},
    {"- Added the Bowling Ball to the BTCM gamemode", 0},
    {"- Throwable Boxes respawn after being broken", 0},
    {"- Throwable Boxes can no longer break Reinforced Boxes", 0},
    {"- Using a Noteblock no longer forces you to drop objects", 0},
    {"    or stop riding a shell", 0},
    {"- Nerfed the Showrunner", 0},
    {"- Bowser no longer instantly dies to lava", 0},
    {"- Buffed Heal Plus badge to apply to all coins", 0},
    {"- Buffed/renamed Double Damage badge to One Hit badge", 0},
    {"- Ability to hide help text in screenshot mode", 0},
    {"- Added a speedrun timer option", 0},
    {"- Improved vertex/tile/object limit display", 0},
    {"- Better warnings for vertex limit and having FBE disabled", 0},
    {"- Improved cursor wrapping around the sides of the level", 0},
    {"", 0},
    {"Improved Visuals", 1},
    {"", 0},
    {"- Better texture mapping for slopes", 0},
    {"- Better object models for Wooden Platform, On-Off Block,", 0},
    {"    On-Off Switch, Reinforced Box", 0},
    {"- Improved textures: Quicksand, Cosmic Void, Rocky Dirt,", 0},
    {"    Green Rock, Ocean Floor, Scorched Pillar, Hazard Stripes",0},
    {"", 0},
    {"Bug Fixes", 1},
    {"", 0},
    {"- Fixed BTCM void respawn mechanic not working", 0},
    {"- As a result, fixed Bottomless badge having no effect", 0},
    {"- Fixed incorrect star IDs with 8 or more stars", 0},
    {"- Fixed infinite coin exploit from Blue Coin previews", 0},
    {"- Fixed trajectory data not resetting between levels", 0},
    {"- Fixed crash when climbing poles with Mario cam", 0},
    {"- Fixed wooden platforms not squishing Mario", 0},
    {"- Fixed softlock on top of fences at the level boundary", 0},
    {"- Fixed lava bubbles appearing far below the level", 0},
    {"- Fixed glitchy bully physics in midair and on snow/ice", 0},
    {"- Countless minor physics and AI fixes", 0},
    {"- Fixed bug allowing unlimited stars to be placed", 0},
    {"- Fixed failure to load levels on some flashcarts", 0},
    {"- Fixed string overflow glitches in file and author names", 0},
    {"- Fixed bad handling of invalid level files", 0},
    {"- Levels will not corrupt if vertex limit exceeded", 0},
    {"- Fixed broken menus with widescreen viewport hack enabled",0},
    {"- Fixed BTCM templates selecting the wrong music tracks", 0},
    {NULL, 0},
};

void *mb64_mm_page_data = NULL;
s32 credits_y_offset = 0;
void print_maker_credits(void) {
    struct mb64_credits_entry *credits = mb64_mm_page_data;
    u32 leftalign = (mb64_mm_page_data != mb64_credits);
    
    s32 credits_entries = 0;
    while (credits[credits_entries].text != NULL) {
        credits_entries++;
    }

    s32 lower_limit = (credits_entries*16) - 160;

    u8 base_alpha = 255;
    if (mb64_menu_start_timer != -1) {
        u8 time = MIN(mb64_menu_start_timer, 8);
        base_alpha = (time * 255) / 8;
    } else if (mb64_menu_end_timer != -1 && !(mb64_mm_state == MM_KEYBOARD && mb64_menu_going_back == 1)) {
        u8 time = MIN(mb64_menu_end_timer, 8);
        base_alpha = 255 - ((time * 255) / 8);
    }

    credits_y_offset -= (gPlayer1Controller->rawStickY/10.0f);
    if (credits_y_offset <= 0) {
        credits_y_offset = 0;
    }
    if (credits_y_offset >= lower_limit) {
        credits_y_offset = lower_limit;
    }
    if (credits_y_offset != lower_limit) {
        print_maker_string_ascii_centered_alpha(300,20 + sins(gGlobalTimer*0x300)*2.5f ,"|",MB64_TEXT_WHITE,base_alpha);
    }
    if (credits_y_offset != 0) {
        print_maker_string_ascii_centered_alpha(300,40 - sins(gGlobalTimer*0x300)*2.5f,"^",MB64_TEXT_WHITE,base_alpha);
    }

    for (int i=0; i<credits_entries; i++) {
        u8 alpha = base_alpha;
        s32 ypos = credits_y_offset+200-(16*i);
        if ((ypos < 220)&&(ypos >10)) {
            if (ypos > 200) {
                alpha = ((base_alpha/255.0f)*smoothstep2(220.0f,200.0f,ypos))*255.0f;
            }
            if (ypos < 30) {
                alpha = ((base_alpha/255.0f)*smoothstep2(10.0f,30.0f,ypos))*255.0f;
            }
            if (leftalign && credits[i].color == 0) {
                print_maker_string_ascii_alpha(15,ypos, credits[i].text, credits[i].color, alpha);
            } else {
                print_maker_string_ascii_centered_alpha(160,ypos, credits[i].text, credits[i].color, alpha);
            }
        }
    }
}

char *mb64_mm_keyboard_prompt[] = {
    "Enter level name:",//KXM_NEW_LEVEL
    "Enter placeholder level name:", //KXM_NEW_LEVEL_LIMITED
    "Enter your author name:",//KXM_AUTHOR
    "Change author name:",
};
char mb64_mm_keyboard[] = "1234567890abcdefghijklmnopqrstuvwxyz!'- ";
char mb64_mm_keyboard_caps[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ!'- ";
char mb64_mm_keyboard_input[MAX_FILE_NAME_SIZE];
u8 mb64_mm_keyboard_exit_mode = KXM_NEW_LEVEL;
u8 mb64_mm_keyboard_input_index = 0;
#define KEYBOARD_SIZE (sizeof(mb64_mm_keyboard)-1)
s8 mb64_mm_keyboard_index = 0;
s8 mb64_mm_keyboard_max_input_length = 0;

char mb64_mm_warning[] = \
"WARNING!\n\
SD card emulation not detected.\n\
You will still be able to use\n\
the level editor, but you will\n\
not be able to save levels or\n\
download levels from other people.";

char *mb64_mm_btns[] = {
    "Build",
    "Play",
    "Help",
    "Credits",
};

char *mb64_mm_btns_lim[] = {
    "Build",
    "Help",
    "Credits",
};

/**
char *mb64_mm_play_btns[] = {
    "Play Levels",
    mb64_mm_comingsoon, //"Play Hacks"
};
**/

char *mb64_mm_make_btns[] = {
    "New Level",
    "Load Level",
    "Change Name",
};

char *mb64_mm_help_btns[] = {
    "SD Card Setup",
    "Editor Controls",
    "Share Levels",
    "Changelog",
};

u8 mb64_mm_help_page1[] = {TXT_MM_HELP_PAGE_1};
u8 mb64_mm_help_page2[] = {TXT_MM_HELP_PAGE_2};
u8 mb64_mm_help_page3[] = {TXT_MM_HELP_PAGE_3};

u8 mb64_mm_txt_pages[] = {TXT_MM_PAGE};

char *mb64_mm_txt_keyboard[]= {
    "\x10: Press Key         \x11: Backspace\n\x12: Shift              \x13: Exit\nSTART: Confirm",
    "\x10: Press Key         \x11: Backspace\n\x12: Shift              \x13: Exit\nSTART: Confirm",
    "\x10: Press Key         \x11: Backspace\n\x12: Shift              START: Confirm",
    "\x10: Press Key         \x11: Backspace\n\x12: Shift              \x13: Exit\nSTART: Confirm",
};

u8 mb64_mm_state = MM_INIT;
u8 mb64_mm_main_state = MM_MAIN;
u8 mb64_mm_files_prev_menu;
s8 mb64_mm_pages = 0;
s8 mb64_mm_page = 0;
#define PAGE_SIZE 5

void mb64_mm_shade_screen(void) {
    u8 alpha = 110;
    if (mb64_menu_start_timer != -1) {
        u8 time = MIN(mb64_menu_start_timer, 8);
        alpha = (time * 110) / 8;
    } else if (mb64_menu_end_timer != -1 && !(mb64_mm_state == MM_KEYBOARD && mb64_mm_keyboard_exit_mode == KXM_NEW_LEVEL && mb64_menu_going_back == 1)) {
        u8 time = MIN(mb64_menu_end_timer, 8);
        alpha = 110 - ((time * 110) / 8);
    }
    gDPPipeSync(gDisplayListHead++);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, alpha);
    gDPSetCombineMode(gDisplayListHead++, G_CC_ENVIRONMENT, G_CC_ENVIRONMENT);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPFillRectangle(gDisplayListHead++, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void render_mb64_mm_button(f32 x, f32 y, u32 highlighted) {
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

void render_mb64_mm_menu(char * strlist[], char *title, u8 ct) {
    create_dl_scale_matrix(MENU_MTX_PUSH, 2.f, 2.f, 0.f);
    print_maker_string_ascii(80 - (get_string_width_ascii(title)/2),95 + mb64_menu_title_vels[0]/2,title,MB64_TEXT_WHITE);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    if ((mb64_mm_state == MM_MAIN) || (mb64_mm_state == MM_MAIN_LIMITED)) {
       print_maker_string_ascii(115, 177 + mb64_menu_title_vels[0], "By: Rovertronic & Arthurtilly", MB64_TEXT_WHITE);
    }

    for (s32 i=0; i<ct; i++) {
        render_mb64_mm_button(mb64_menu_button_vels[i][0] + 160, 150-(i*30), mb64_menu_index == i);
        print_maker_string_ascii_centered(mb64_menu_button_vels[i][0] + 160,143-(i*30),strlist[i],mb64_menu_index == i);
    }
}

void mb64_mm_reset_all_buttons(f32 pos) {
    for (s32 i=0;i<ARRAY_COUNT(mb64_menu_button_vels);i++) {
        mb64_menu_button_vels[i][0] = pos;
        mb64_menu_button_vels[i][1] = 0.f;
        mb64_menu_button_vels[i][2] = 0.f;
    }
}

void mb64_mm_anim_out_main(s32 len, f32 startvel) {
    animate_menu_generic(mb64_menu_title_vels, 0.f, 0.f, 3.f, mb64_menu_end_timer == 0);

    s32 index = -1;
    if (mb64_menu_end_timer < len*2 && mb64_menu_end_timer % 2 == 0) {
        s32 step = mb64_menu_end_timer/2;
        if (step == 0) {
            index = mb64_menu_index;
        } else {
            index = (step > mb64_menu_index) ? step : step-1;
        }
    }

    for (s32 i = 0; i < len; i++) {
        animate_menu_generic(mb64_menu_button_vels[i], 0.f,
                            startvel*mb64_menu_going_back, -8.f*mb64_menu_going_back,
                            i == index);
    }
}

void mb64_mm_generic_anim_check(s32 canBack) {
    if (mb64_menu_start_timer == -1 || mb64_menu_start_timer > 10) {
        if (gPlayer1Controller->buttonPressed & (A_BUTTON|START_BUTTON)) {
            mb64_menu_end_timer = 0;
            mb64_menu_going_back = 1;
            mb64_menu_start_timer = -1;
            mb64_mm_reset_all_buttons(0.f);
            play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
        }
        if (gPlayer1Controller->buttonPressed & (B_BUTTON)) {
            if (canBack) {
                mb64_menu_end_timer = 0;
                mb64_menu_going_back = -1;
                mb64_menu_start_timer = -1;
                mb64_mm_reset_all_buttons(0.f);
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
            }
        }
    }
}

void mb64_mm_files_anim_check(s32 canBack) {
    if (gPlayer1Controller->buttonPressed & (A_BUTTON)) {
        if (mb64_level_entry_count == 0) return;
        if (mb64_level_entry_version[mb64_mm_page * PAGE_SIZE+mb64_menu_index] > MB64_VERSION) {
            play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
            return;
        }
    }
    mb64_mm_generic_anim_check(canBack);
}

void mb64_mm_make_anim_check(UNUSED s32 canBack) {
    if (gPlayer1Controller->buttonPressed & (A_BUTTON|START_BUTTON) && (mb64_menu_index != 3)) return;
    mb64_mm_generic_anim_check(TRUE);
}

void mb64_mm_keyboard_anim_check(UNUSED s32 canBack) {
    if (mb64_menu_start_timer == -1) {
        if (gPlayer1Controller->buttonPressed & (START_BUTTON)) {
            u8 file_does_not_exist_already = (!level_file_exists(mb64_mm_keyboard_input));
            u8 something_is_entered = (mb64_mm_keyboard_input_index > 0);

            if (mb64_mm_keyboard_exit_mode != KXM_NEW_LEVEL) {
                file_does_not_exist_already = TRUE;
            }

            if ((something_is_entered)&&(file_does_not_exist_already)) { //ensure that people write _something_
                mb64_menu_end_timer = 0;
                mb64_menu_going_back = 1;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
            } else {
                play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                if (!something_is_entered) {
                    mb64_show_error_message("Please enter a name first.");
                }
                if (!file_does_not_exist_already) {
                    mb64_show_error_message("Name is already used!");
                }
            }
        }
        if (gPlayer1Controller->buttonPressed & (R_TRIG)) {
            if (mb64_mm_keyboard_exit_mode != KXM_AUTHOR) {
                mb64_menu_end_timer = 0;
                mb64_menu_going_back = -1;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
            } else {
                play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
            }
        }
    }
}

s32 mb64_mm_anim_out(s32 len, s32 canBack, void checkFunc(s32 canBack), f32 startVel) {
    if (mb64_menu_end_timer == -1) {
        checkFunc(canBack);
    } else {
        mb64_mm_anim_out_main(len, startVel);
        if (++mb64_menu_end_timer == 10 + len*2) {
            mb64_menu_end_timer = -1;
            return TRUE;
        }
    }
    return FALSE;
}

s32 mb64_mm_generic_anim_out(s32 len, s32 canBack) {
    return mb64_mm_anim_out(len, canBack, mb64_mm_generic_anim_check, 23.f);
}

s32 mb64_mm_files_anim_out(void) {
    return mb64_mm_anim_out(5, TRUE, mb64_mm_files_anim_check, 23.f);
}

s32 mb64_mm_keyboard_anim_out(void) {
    return mb64_mm_anim_out(6, TRUE, mb64_mm_keyboard_anim_check, 0.f);
}

s32 mb64_mm_make_anim_out(void) {
    return mb64_mm_anim_out(4, TRUE, mb64_mm_make_anim_check, 23.f);
}

s32 mb64_mm_anim_info(void) {
    if (mb64_menu_start_timer != -1) {
        animate_menu_overshoot_target(mb64_menu_title_vels, 20.f, -300.f, 55.f, -5.f, mb64_menu_start_timer == 0);
        mb64_menu_start_timer++;

        if (mb64_menu_start_timer > 10) {
            mb64_menu_start_timer = -1;
        }
    } else if (mb64_menu_end_timer == -1) {
        if (gPlayer1Controller->buttonPressed & (A_BUTTON|B_BUTTON|START_BUTTON)) {
            mb64_menu_end_timer = 0;
            mb64_menu_going_back = -1;
            play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
        }
    } else {
        animate_menu_generic(mb64_menu_title_vels, 20.f, 0.f, -10.f, mb64_menu_end_timer == 0);
        if (mb64_menu_end_timer++ == 10) {
            mb64_menu_end_timer = -1;
            return TRUE;
        }
    }
    return FALSE;
}

#define MENU_ANIM_IN_STARTVEL (mb64_mm_state == MM_KEYBOARD ? -60.f : -63.f)

u32 mb64_mm_anim_in(s32 len) {
    if (mb64_menu_start_timer == -1) return FALSE;

    animate_menu_overshoot_target(mb64_menu_title_vels, 0.f, 50.f, -16.f, 2.5f, mb64_menu_start_timer == 0);

    s8 step = -1;
    if (mb64_menu_start_timer < len*2 && mb64_menu_start_timer % 2 == 0) {
        step = mb64_menu_start_timer/2;
    }

    if (mb64_menu_start_timer == 0) mb64_mm_reset_all_buttons(1000.f);
    for (s32 i=0;i<len;i++) {
        animate_menu_overshoot_target(mb64_menu_button_vels[i], 0.f, 250.f*mb64_menu_going_back, MENU_ANIM_IN_STARTVEL * mb64_menu_going_back, 8.f * mb64_menu_going_back,
        i == step);
    }

    mb64_menu_start_timer++;

    if (mb64_menu_start_timer > len*2 && mb64_menu_button_vels[len-1][2] == 0.f) {
        mb64_menu_start_timer = -1;
        return TRUE;
    }
    return FALSE;
}

s32 mb64_main_menu(void) {
    mb64_joystick = joystick_direction();

    if (mb64_menu_end_timer != -1) {
        mb64_joystick = 0;
    }
    for (s32 i = 0; i < (mb64_joystick+1); i++) {
        random_u16(); // randomize for the initial tip
    }

    if ((mb64_mm_state != MM_CREDITS)&&(mb64_mm_state != MM_HELP)) {
        switch(mb64_joystick) {
            case 2:
                mb64_menu_index++;
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
            break;
            case 4:
                mb64_menu_index--;
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
            break;
        }
        mb64_menu_index = (mb64_menu_index + mb64_menu_index_max) % mb64_menu_index_max;
    }

    create_dl_ortho_matrix();
    
    switch(mb64_mm_state) {
        case MM_INIT:
            full_menu_reset();
            for (u8 i=0;i<sizeof(mb64_mm_keyboard_input);i++){
                mb64_mm_keyboard_input[i] = '\0';
            }
            if (mount_success == FR_OK) {
                //SD Card success

                if (mb64_sram_configuration.author[0] != '\0') {
                    //already have an author, go straight to the main menu
                    mb64_mm_state = MM_MAIN;

                    //set mb64_username to author in sram config
                    bcopy(&mb64_sram_configuration.author,&mb64_username,sizeof(mb64_username));
                    mb64_has_username = TRUE;
                } else {
                    //no author file detected, prompt user to enter an author name
                    mb64_mm_keyboard_exit_mode = KXM_AUTHOR;
                    mb64_mm_keyboard_max_input_length = MAX_USERNAME_SIZE - 1;
                    mb64_mm_state = MM_KEYBOARD;
                    mb64_mm_keyboard_input_index = 0;

                    //check for rhdc username
                    if (gSupportsLibpl) {
                        char * rhdc_username = libpl_get_my_rhdc_username();
                        if (rhdc_username) {
                            while ((rhdc_username[mb64_mm_keyboard_input_index] != 0)&&(mb64_mm_keyboard_input_index < MAX_USERNAME_SIZE - 1)) {
                                mb64_mm_keyboard_input[mb64_mm_keyboard_input_index] = rhdc_username[mb64_mm_keyboard_input_index];
                                mb64_mm_keyboard_input_index++;
                            }
                            mb64_mm_keyboard_input[mb64_mm_keyboard_input_index] = '\0';
                        }
                    }
                }
            } else {
                //SD Card failure, give player warning and limited play
                mb64_mm_state = MM_NO_SD_CARD;
                mb64_mm_main_state = MM_MAIN_LIMITED;
                mb64_menu_title_vels[0] = 25.f;
            }
            break;
        case MM_NO_SD_CARD:
            mb64_mm_shade_screen();
            print_maker_string_ascii(mb64_menu_title_vels[0],210,mb64_mm_warning,MB64_TEXT_WHITE);
            if (mb64_mm_anim_info()) {
                mb64_menu_start_timer = 0;
                mb64_mm_state = MM_MAIN_LIMITED;
                mb64_menu_index = 0;
            }
            break;
        case MM_MAIN:   
            mb64_menu_index_max = 4;
            mb64_mm_anim_in(4);
            render_mb64_mm_menu(mb64_mm_btns,"Mario Builder 64",4);
            if (mb64_mm_generic_anim_out(4, FALSE)) {
                switch(mb64_menu_index) {
                    case 0:
                        mb64_mm_state = MM_MAKE;
                        break;
                    case 1:
                        mb64_mm_state = MM_FILES;
                        mb64_mm_files_prev_menu = MM_MAIN;
                        mb64_tip_timer = 0;
                        mb64_mm_page = 0;
                        mb64_level_action = MB64_LA_PLAY_LEVELS;
                        break;
                    case 2:
                        mb64_mm_state = MM_HELP_MODE;
                        break;
                    case 3:
                        credits_y_offset = 0;
                        mb64_mm_state = MM_CREDITS;
                        mb64_mm_page_data = mb64_credits;
                        break;
                }
                mb64_menu_index = 0;
                mb64_menu_start_timer = 0;
            }
            break;
        case MM_MAIN_LIMITED:
            mb64_menu_index_max = 3;
            mb64_mm_anim_in(3);
            render_mb64_mm_menu(mb64_mm_btns_lim,"Mario Builder 64",3);
            if (mb64_mm_generic_anim_out(3, FALSE)) {
                switch(mb64_menu_index) {
                    case 0:
                        mb64_mm_state = MM_MAKE_MODE;
                        break;
                    case 1:
                        mb64_mm_state = MM_HELP_MODE;
                        break;
                    case 2:
                        mb64_mm_state = MM_CREDITS;
                        mb64_mm_page_data = mb64_credits;
                        break;
                }
                mb64_menu_index = 0;
                mb64_menu_start_timer = 0;
            }
            break;
            /**
        case MM_PLAY:
            mb64_menu_index_max = 2;
            mb64_mm_anim_in(2);
            render_mb64_mm_menu(mb64_mm_play_btns,"Play Levels",2);
            if (mb64_mm_generic_anim_out(2, TRUE)) {
                if (mb64_menu_going_back == -1) {
                    mb64_mm_state = mb64_mm_main_state;
                    mb64_menu_index = 1;
                    mb64_menu_start_timer = 0;
                } else {
                    switch(mb64_menu_index) {
                        case 0: //play levels
                            mb64_mm_files_prev_menu = MM_PLAY;
                            mb64_level_action = MB64_LA_PLAY_LEVELS;
                            mb64_mm_state = MM_FILES;
                            mb64_menu_index = 0;
                            mb64_mm_page = 0;
                            mb64_menu_start_timer = 0;
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
            mb64_menu_index_max = 3;
            mb64_mm_anim_in(3);
            render_mb64_mm_menu(mb64_mm_make_btns,"Make Levels",3);
            if (mb64_mm_generic_anim_out(3, TRUE)) {
                mb64_menu_start_timer = 0;
                if (mb64_menu_going_back == -1) {
                    mb64_mm_state = mb64_mm_main_state;
                    mb64_menu_index = 0;
                } else {
                    switch(mb64_menu_index) {
                        case 0:
                            //make new level
                            mb64_mm_state = MM_MAKE_MODE;
                            mb64_level_action = MB64_LA_BUILD;
                            mb64_target_mode = MB64_MODE_MAKE;
                            break;
                        case 1:
                            //load levels
                            mb64_mm_files_prev_menu = MM_MAKE;
                            mb64_level_action = MB64_LA_BUILD;
                            mb64_target_mode = MB64_MODE_MAKE;
                            mb64_mm_state = MM_FILES;
                            mb64_mm_page = 0;
                            break;
                        case 2:
                            //change name
                            mb64_mm_keyboard_exit_mode = KXM_CHANGE_AUTHOR;
                            mb64_mm_keyboard_max_input_length = MAX_USERNAME_SIZE - 1;
                            mb64_mm_state = MM_KEYBOARD;
                            mb64_mm_keyboard_input_index = 0;
                            mb64_mm_keyboard_input[0] = '\0';
                            break;
                    }
                    mb64_menu_index = 0;
                }
            }
            break;
        case MM_MAKE_MODE:
            mb64_menu_index_max = 4;
            mb64_mm_anim_in(4);
            f32 x,y;

            create_dl_scale_matrix(MENU_MTX_PUSH, 2.f, 2.f, 0.f);

            char *title = "Level Settings";
            print_maker_string_ascii(78 - (get_string_width_ascii(title)/2),95 + mb64_menu_title_vels[0]/2,title,0);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            for (s32 i=0; i<3; i++) {
                x = mb64_menu_button_vels[i][0] + 160;
                y = 150-(i*27);
                print_maker_string_ascii_centered(x - 60, y, mb64_mode_settings_buttons[i].str,MB64_TEXT_WHITE);
                render_mb64_mm_button(x + 20, y + 8, mb64_menu_index == i);
                mb64_menu_option_animation(x + 20, y, 43, &mb64_mode_settings_buttons[i], i, mb64_joystick);
            }
            x = mb64_menu_button_vels[3][0] + 160;
            y = 150-(4*27);
            render_mb64_mm_button(x, y + 8, mb64_menu_index == 3);
            print_maker_string_ascii_centered(x, y, "Create!",(mb64_menu_index == 3));


            if (mb64_mm_make_anim_out()) {
                mb64_menu_start_timer = 0;

                if (mb64_mm_main_state == MM_MAIN_LIMITED) {
                    if (mb64_menu_going_back == -1) {
                        mb64_mm_state = MM_MAIN_LIMITED;
                        mb64_menu_index = 0;
                    } else {
                        mb64_mm_keyboard_exit_mode = KXM_NEW_LEVEL_LIMITED;
                        mb64_mm_keyboard_max_input_length = MAX_FILE_NAME_SIZE - 6;
                        mb64_mm_state = MM_KEYBOARD;
                        mb64_mm_keyboard_input_index = 0;
                        mb64_mm_keyboard_input[0] = '\0';
                        mb64_menu_index = 0;
                    }
                } else {
                    if (mb64_menu_going_back == -1) {
                        mb64_mm_state = MM_MAKE;
                        mb64_menu_index = 0;
                    } else {
                        mb64_mm_keyboard_exit_mode = KXM_NEW_LEVEL;
                        mb64_mm_keyboard_max_input_length = MAX_FILE_NAME_SIZE - 6;
                        mb64_mm_state = MM_KEYBOARD;
                        mb64_mm_keyboard_input_index = 0;
                        mb64_mm_keyboard_input[0] = '\0';
                        mb64_menu_index = 0;
                    }
                }
            }
            //if (mb64_mm_main_state == MM_MAIN_LIMITED && mb64_menu_end_timer == 0 && mb64_menu_going_back == 1) {
            //    mb64_tip_timer = 60;
            //    return 1;
            //}
            break;
        case MM_HELP_MODE:
            mb64_menu_index_max = 4;
            mb64_mm_anim_in(4);
            render_mb64_mm_menu(mb64_mm_help_btns,"Help",4);
            if (mb64_mm_generic_anim_out(4, TRUE)) {
                mb64_menu_start_timer = 0;
                if (mb64_menu_going_back == -1) {
                    mb64_mm_state = mb64_mm_main_state;
                    mb64_menu_index = 2;
                } else {
                    mb64_mm_state = MM_HELP;
                    switch(mb64_menu_index) {
                        case 0:
                            mb64_mm_page_data = mb64_mm_help_page1;
                            break;
                        case 1:
                            mb64_mm_page_data = mb64_mm_help_page2;
                            break;
                        case 2:
                            mb64_mm_page_data = mb64_mm_help_page3;
                            break;
                        case 3:
                            mb64_mm_state = MM_CREDITS;
                            mb64_mm_page_data = mb64_v1_1_changelog;
                    }
                }
            }
            break;
        case MM_HELP:
            mb64_mm_shade_screen();
            if (mb64_mm_anim_info()) {
                mb64_menu_start_timer = 0;
                mb64_mm_state = MM_HELP_MODE;
            }
            print_maker_string(mb64_menu_title_vels[0],210,mb64_mm_page_data,FALSE);
            break;
        case MM_CREDITS:
            mb64_mm_shade_screen();
            if (mb64_mm_anim_info()) {
                mb64_menu_start_timer = 0;
                if (mb64_mm_page_data == mb64_credits) {
                    mb64_mm_state = mb64_mm_main_state;
                    mb64_menu_index = 3;
                } else {
                    mb64_mm_state = MM_HELP_MODE;
                    mb64_menu_index = 3;
                }
            }
            print_maker_credits();
            break;
        case MM_KEYBOARD:
            mb64_mm_anim_in(6);
            switch(mb64_joystick) {
                case 1:
                    mb64_mm_keyboard_index--;
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                break;
                case 2:
                    mb64_mm_keyboard_index+=10;
                break;
                case 3:
                    mb64_mm_keyboard_index++;
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                break;
                case 4:
                    mb64_mm_keyboard_index-=10;
                break;
            }
            mb64_mm_keyboard_index = (mb64_mm_keyboard_index+KEYBOARD_SIZE)%KEYBOARD_SIZE;

            if (gPlayer1Controller->buttonPressed & A_BUTTON) { // extension
                if (mb64_mm_keyboard_input_index >= mb64_mm_keyboard_max_input_length) {
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                } else {
                    if (gPlayer1Controller->buttonDown & Z_TRIG) {
                        //shift
                        mb64_mm_keyboard_input[mb64_mm_keyboard_input_index] = mb64_mm_keyboard_caps[mb64_mm_keyboard_index];
                    } else {
                        mb64_mm_keyboard_input[mb64_mm_keyboard_input_index] = mb64_mm_keyboard[mb64_mm_keyboard_index];
                    }
                    mb64_mm_keyboard_input_index++;
                    mb64_mm_keyboard_input[mb64_mm_keyboard_input_index] = '\0';
                }
            }

            if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                if (mb64_mm_keyboard_input_index > 0) {
                    mb64_mm_keyboard_input_index--;
                    mb64_mm_keyboard_input[mb64_mm_keyboard_input_index] = '\0';
                } else {
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
            }

            if (mb64_mm_keyboard_anim_out()) {
                mb64_menu_start_timer = 0;
                if (mb64_menu_going_back == -1) {
                    mb64_mm_state = MM_MAKE_MODE;
                    mb64_menu_index = 0;
                }
                if ((mb64_menu_going_back == 1)&&(mb64_mm_keyboard_exit_mode == KXM_AUTHOR)) {
                    mb64_mm_state = MM_MAIN;
                    mb64_menu_index = 0;
                }
                if (mb64_mm_keyboard_exit_mode == KXM_CHANGE_AUTHOR) {
                    mb64_mm_state = MM_MAKE;
                    mb64_menu_index = 0;
                }
            }

            mb64_mm_shade_screen();

            f32 inputX = CLAMP(30 + mb64_menu_button_vels[1][0], -320, 320);
            gDPPipeSync(gDisplayListHead++);
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 100);
            gDPSetCombineMode(gDisplayListHead++, G_CC_ENVIRONMENT, G_CC_ENVIRONMENT);
            gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPFillRectangle(gDisplayListHead++, MAX(inputX, 0), (240-185)-16, inputX + 250, (240-185)+3);


            print_maker_string_ascii(35 + mb64_menu_button_vels[0][0],208,mb64_mm_keyboard_prompt[mb64_mm_keyboard_exit_mode],MB64_TEXT_WHITE);
            print_maker_string_ascii(35 + mb64_menu_button_vels[1][0],185,mb64_mm_keyboard_input,MB64_TEXT_WHITE);
            print_maker_string_ascii(35,45 - mb64_menu_title_vels[0],mb64_mm_txt_keyboard[mb64_mm_keyboard_exit_mode],MB64_TEXT_WHITE);

            mb64_render_topleft_text();

            for (u8 i=0; i<(sizeof(mb64_mm_keyboard)-1); i++) {
                u16 x = i%10;
                u16 y = i/10;
                gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
                create_dl_translation_matrix(MENU_MTX_PUSH, 40+(x*25)+mb64_menu_button_vels[y+2][0], 160-(y*25), 0);
                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
                if (mb64_mm_keyboard_index == i) {
                    gDPSetEnvColor(gDisplayListHead++, 100, 100, 100, 150);
                }
                gSPDisplayList(gDisplayListHead++, &mm_btn_sm_mm_btn_sm_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
                char single_char[2];
                if (gPlayer1Controller->buttonDown & Z_TRIG) {
                    //shift
                    single_char[0] = mb64_mm_keyboard_caps[i];
                } else {
                    single_char[0] = mb64_mm_keyboard[i];
                }
                single_char[1] = '\0';
                print_maker_string_ascii(37+(x*25)+mb64_menu_button_vels[y+2][0],152-(y*25),single_char,(mb64_mm_keyboard_index == i));
            }

            if (mb64_menu_end_timer == 0 && mb64_menu_going_back == 1) {
                switch(mb64_mm_keyboard_exit_mode) {
                    case KXM_NEW_LEVEL:
                    case KXM_NEW_LEVEL_LIMITED:
                        bcopy(&mb64_mm_keyboard_input,&mb64_file_name,mb64_mm_keyboard_input_index);
                        //manually add file extension
                        mb64_file_name[mb64_mm_keyboard_input_index+0] = '.';
                        mb64_file_name[mb64_mm_keyboard_input_index+1] = 'm';
                        mb64_file_name[mb64_mm_keyboard_input_index+2] = 'b';
                        mb64_file_name[mb64_mm_keyboard_input_index+3] = '6';
                        mb64_file_name[mb64_mm_keyboard_input_index+4] = '4';
                        mb64_file_name[mb64_mm_keyboard_input_index+5] = '\0';

                        mb64_mode = MB64_MODE_UNINITIALIZED;
                        return 1;
                    break;
                    case KXM_AUTHOR:
                    case KXM_CHANGE_AUTHOR:
                        strncpy(&mb64_username,&mb64_mm_keyboard_input,MAX_USERNAME_SIZE);

                        bcopy(&mb64_username,&mb64_sram_configuration.author,sizeof(mb64_sram_configuration.author));
                        if (gSramProbe != 0) {
                            nuPiWriteSram(0, &mb64_sram_configuration, ALIGN8(sizeof(mb64_sram_configuration)));
                        }

                        mb64_has_username = TRUE;
                    break;
                }
            }
            break;
        case MM_FILES:
            mb64_mm_anim_in(5);

            FILINFO * level_entries_ptr = segmented_to_virtual(mb64_level_entries);
            u16 (*u16_array)[MAX_FILES][64][64] = segmented_to_virtual(mb64_level_entry_piktcher);

            if (mb64_level_entry_count == 0) {
                //no levels, do not render anything
                gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
                create_dl_translation_matrix(MENU_MTX_PUSH, 160 + mb64_menu_button_vels[0][0], 210, 0);
                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
                gSPDisplayList(gDisplayListHead++, &mm_btn_lg_mm_btn_lg_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

                print_maker_string_ascii(55 + mb64_menu_button_vels[0][0],200,"No levels currently loaded yet.",MB64_TEXT_YELLOW);
                if (mb64_mm_files_anim_out()) {
                    mb64_menu_start_timer = 0;
                    if (mb64_menu_going_back == -1) {
                        mb64_mm_state = mb64_mm_files_prev_menu;
                        mb64_menu_index = 1;
                        break;
                    }
                }
                return 0;
            }

            mb64_menu_index_max = mb64_level_entry_count;

            mb64_mm_pages = ((mb64_level_entry_count - 1)/PAGE_SIZE)+1;

            s32 oldPage = mb64_mm_page;
            mb64_mm_page = mb64_menu_index/PAGE_SIZE;

            if (oldPage == mb64_mm_page + 1) {
                mb64_menu_scrolling[0][0] = 9;
                mb64_menu_scrolling[0][1] = -1;
            } else if (oldPage == mb64_mm_page - 1) {
                mb64_menu_scrolling[0][0] = 9;
                mb64_menu_scrolling[0][1] = 1;
            }

            s32 tempindex = mb64_menu_index;
            mb64_menu_index -= mb64_mm_page*PAGE_SIZE; // horrible code to fix animation
            if (mb64_mm_files_anim_out()) {
                mb64_menu_start_timer = 0;
                if (mb64_menu_going_back == -1) {
                    mb64_mm_state = mb64_mm_files_prev_menu;
                    mb64_menu_index = 1;
                    break;
                }
            }
            mb64_menu_index = tempindex;

            s32 startRenderY = 210;
            s32 startRenderIndex = mb64_mm_page * PAGE_SIZE;
            s32 numPagesRender = PAGE_SIZE;
            s32 indexOffset = 0;

            if (mb64_menu_scrolling[0][0] > 0) {
                if (mb64_menu_scrolling[0][1] == 1) {
                    startRenderY = 210 + ((9-mb64_menu_scrolling[0][0]) * 20);
                    numPagesRender += PAGE_SIZE;
                    startRenderIndex -= PAGE_SIZE;
                    indexOffset = PAGE_SIZE;
                } else {
                    startRenderY = 210 + (mb64_menu_scrolling[0][0] * 20);
                    numPagesRender += PAGE_SIZE;
                }
                mb64_menu_scrolling[0][0]--;
            }
            numPagesRender = MIN(numPagesRender, mb64_level_entry_count - startRenderIndex);

            gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 15, SCREEN_WIDTH, SCREEN_HEIGHT - 45);

            for (s32 i=0; i<numPagesRender; i++) {
                s32 xPosAnim = 0;
                s32 renderIndex = i - indexOffset;
                s32 selectedIndex = mb64_menu_index -(mb64_mm_page*PAGE_SIZE);
                if (renderIndex >= 0 && renderIndex < PAGE_SIZE) {
                    xPosAnim = mb64_menu_button_vels[renderIndex][0];
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
                    gDPSetTextureImage(gDisplayListHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, (*u16_array)[startRenderIndex + i]);
                    gSPDisplayList(gDisplayListHead++, &bigpainting_bigpainting_mesh_part2);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                //


                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

                if (MB64_VERSION < mb64_level_entry_version[startRenderIndex + i]) {
                    print_maker_string_ascii(75 + xPosAnim,startRenderY - 10 -(i*36),"Created in future version, update to play.",MB64_TEXT_RED);
                } else {
                    print_maker_string_ascii(75 + xPosAnim,startRenderY - 10 -(i*36),level_entries_ptr[startRenderIndex + i].fname,(selectedIndex == renderIndex));
                }

            }

            gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

            //render pages
            create_dl_translation_matrix(MENU_MTX_PUSH, 90, 20 - mb64_menu_title_vels[0], 0);
            gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
            gSPDisplayList(gDisplayListHead++, mm_btn2_mm_btn_mesh);
            gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
            int_to_str_slash(mb64_mm_page+1, mb64_mm_pages, (u8 *)&mb64_mm_txt_pages[6]);
            print_maker_string(42,12 - mb64_menu_title_vels[0],mb64_mm_txt_pages,FALSE);

            if (mb64_menu_end_timer == 1 && mb64_menu_going_back == 1) {
                mb64_mode = MB64_MODE_UNINITIALIZED;
                reset_play_state();
                int i = 0;
                while(level_entries_ptr[mb64_menu_index].fname[i] && (i < MAX_FILE_NAME_SIZE - 1)) {
                    mb64_file_name[i] = level_entries_ptr[mb64_menu_index].fname[i];
                    i++;
                }
                mb64_file_name[i] = '\0'; // add null terminator

                struct mb64_level_save_header * level_info = get_level_info_from_filename(mb64_file_name);
                mb64_lopt_game = level_info->game;
                mb64_mm_selected_level = mb64_menu_index;
                if (mb64_level_action == MB64_LA_BUILD) mb64_tip_timer = 60;
                else mb64_tip_timer = 0;

                return 1;
            }

            break;
    }

    return 0;
}


// Pause menu during play
u8 mb64_pause_menu_state = 0;
u8 mb64_elta = FALSE;

char * mb64_pause_menu_buttons_main[] = {
    "Continue",
    "Exit Level",
    "Options",
    "Badges",
};

//#define OPTIONTEXT _("Play Music\nWidescreen Mode\nShow HUD\nCamera Collision")
char * mb64_pause_menu_buttons_options[] = {
    "Play Music",
    "Show HUD",
    "Lakitu Collision",
    "HUD Layout",
    "Speedrun Timer",
    "Return",
};

void mb64_init_pause_menu(void) {
    mb64_menu_index = 0;
    mb64_pause_menu_state = 0;
}

#define RETURN_OPTION_INDEX ARRAY_COUNT(mb64_pause_menu_buttons_options)-1

s32 draw_mb64_pause_menu(void) {
    u8 returnval = 0;
    s16 badge_count = count_u32_bits(save_file_get_badge_equip());
    s32 xoff;
    s32 yoff;
    char stringBuf[50];

    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);

    switch(mb64_pause_menu_state) {
        case 0: // main pause menu
            //print title and author
            if (mb64_save.author[0] != 0) {

                create_dl_translation_matrix(MENU_MTX_PUSH, 160, 0, 0);
                create_dl_scale_matrix(MENU_MTX_PUSH, 1.5f, 1.5f, 0.f);
                print_generic_string_ascii_centered_nofileext(0,134,mb64_file_name);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

                sprintf(stringBuf,"%s%s","By: ",mb64_save.author);
                print_generic_string_ascii_centered(160,184,stringBuf);
            } else {
                print_generic_string_ascii_centered(160,192,mb64_file_name);
            }

            xoff = (get_string_width_ascii(mb64_pause_menu_buttons_main[3])/2);
            yoff = 0;
            for (s32 i=0;i<4;i++) {
                if (i==3&&badge_count==0) {
                    continue;
                }
                print_generic_string_ascii(160-xoff  ,120+yoff,mb64_pause_menu_buttons_main[i]);
                yoff-=16;
            }

            gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

            // Print selector triangle
            if ((badge_count==0)&&(mb64_menu_index == 3)) {
                create_dl_translation_matrix(MENU_MTX_PUSH, 144-xoff, 120-(2*16), 0);
            } else {
                create_dl_translation_matrix(MENU_MTX_PUSH, 144-xoff, 120-(mb64_menu_index*16), 0);
            }
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
            gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            // print level collectibles
            // generate string
            sprintf(stringBuf,"^%dQ%d",mb64_play_stars, mb64_play_stars_max);
            print_text_centered(160,160, stringBuf);

            if (gRedCoinsTotal > 0) {
                //sprintf(stringBuf,"%s @%dQ%d", stringBuf, gRedCoinsCollected, gRedCoinsTotal);
                sprintf(stringBuf,"@%dQ%d", gRedCoinsCollected, gRedCoinsTotal);
            }
            if (mb64_lopt_coinstar > 0) {
                sprintf(stringBuf,"%s $%dQ%d", stringBuf, gMarioState->numCoins, (mb64_lopt_coinstar*20));
            }
            if ((gRedCoinsTotal > 0)||(mb64_lopt_coinstar > 0)) {
                print_text_centered(160,10, stringBuf);
            }

            mb64_joystick = joystick_direction();
            s32 oldindex = mb64_menu_index;
            switch(mb64_joystick) {
                case 2:
                    mb64_menu_index = MIN(mb64_menu_index + 1, (badge_count==0 ? 2 : 3));
                    break;
                case 4:
                    mb64_menu_index = MAX(mb64_menu_index - 1, 0);
                    break;
            }
            if (oldindex != mb64_menu_index) {
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
            }

            if (gPlayer1Controller->buttonPressed & (A_BUTTON|B_BUTTON|START_BUTTON)) {
                switch(mb64_menu_index) {
                    case 0: // continue
                        returnval = 1;
                        break;
                    case 1: // leave
                        returnval = 2;
                        break;
                    case 2: // options
                        mb64_pause_menu_state = 1;
                        mb64_menu_index = RETURN_OPTION_INDEX;
                        play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                        break;
                    case 3: // badges (btcm only)
                        if (badge_count == 0) break; // Prevent an infinite loop if this somehow gets selected when hidden
                        play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                        mb64_pause_menu_state = 2;
                        //make sure the first unlocked badge is selected
                        gMarioState->numBadgeSelect = 0;
                        while (!(save_file_get_badge_equip() & (1<<gMarioState->numBadgeSelect))) {
                            gMarioState->numBadgeSelect++;
                        }
                        break;
                }
            }
            break;

        case 1: //options
            xoff = (get_string_width_ascii(mb64_pause_menu_buttons_options[2])/2);
            for (s32 i=0;i<ARRAY_COUNT(mb64_pause_menu_buttons_options);i++) {
                char * onoroff_string = ": OFF";
                if (i==3) {
                    onoroff_string = ": Vanilla";
                }
                if (mb64_sram_configuration.option_flags & (1<<i)) {
                    onoroff_string = ": ON";
                    if (i==3) {
                        onoroff_string = ": Modern";
                    }
                }
                if (i==RETURN_OPTION_INDEX) {
                    onoroff_string="";
                }
                sprintf(stringBuf,"%s%s",mb64_pause_menu_buttons_options[i],onoroff_string);
                print_generic_string_ascii(160-xoff ,160-(i*16),stringBuf);
            }

            if (mb64_elta) {
                print_generic_string_ascii(245-xoff ,160,"(Exit level to apply)");
            }

            create_dl_translation_matrix(MENU_MTX_PUSH, 144-xoff, 160-(mb64_menu_index*16), 0);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
            gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            mb64_joystick = joystick_direction();
            switch(mb64_joystick) {
                case 2:
                    mb64_menu_index++;
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                    break;
                case 4:
                    mb64_menu_index--;
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                    break;
            }
            u32 numMenuOptions = ARRAY_COUNT(mb64_pause_menu_buttons_options);
            mb64_menu_index = (mb64_menu_index + numMenuOptions) % numMenuOptions;

            if (gPlayer1Controller->buttonPressed & (B_BUTTON)) {
                mb64_pause_menu_state = 0;
                mb64_menu_index = 0;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                if (gSramProbe != 0) {
                    nuPiWriteSram(0, &mb64_sram_configuration, ALIGN8(sizeof(mb64_sram_configuration)));
                }
            } else if (gPlayer1Controller->buttonPressed & (A_BUTTON|START_BUTTON)) {
                if (gPlayer1Controller->buttonPressed & START_BUTTON) {
                    mb64_menu_index = RETURN_OPTION_INDEX;
                }
                switch(mb64_menu_index) {
                    case RETURN_OPTION_INDEX:
                        mb64_elta = FALSE;
                        mb64_pause_menu_state = 0;
                        mb64_menu_index = 0;
                        if (gSramProbe != 0) {
                            nuPiWriteSram(0, &mb64_sram_configuration, ALIGN8(sizeof(mb64_sram_configuration)));
                        }
                        play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                        break;
                    default:
                        if (mb64_menu_index == 0) {
                            mb64_elta = TRUE;
                        }
                        play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                        mb64_sram_configuration.option_flags ^= (1<<mb64_menu_index);
                        break;
                }
            }
            break;

        case 2: //badge view
            if (gPlayer1Controller->buttonPressed & (A_BUTTON|B_BUTTON|START_BUTTON)) {
                mb64_pause_menu_state = 0;
            }
            draw_mb64_pause_badges();
            break;
    }

    return returnval;
}