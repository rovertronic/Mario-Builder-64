#include "main.h"
#include "menu.h"

#include "audio/external.h"
#include <PR/gbi.h>
#include "game/game_init.h"
#include "levels/menu/header.h"
#include "game/rendering_graph_node.h"
#include "game/level_update.h"
#include "game/ingame_menu.h"
#include "actors/group0.h"
#include "engine/math_util.h"
#include "text_strings.h"
#include "game/print.h"
#include "game/save_file.h"
#include "libpl/libpl-rhdc.h"
#include "game/sram.h"
#include <string.h>

#include "menu_data.inc.c"

u8 mb64_txt_recording[] = {TXT_RECORDING};
u8 mb64_txt_freecam[] = {TXT_FREECAM};
u8 mb64_mm_txt_pages[] = {TXT_MM_PAGE};

extern u8 gDialogCharWidths[256];

u8 mb64_menu_state = MB64_MAKE_MAIN;
s16 mb64_menu_index = 0;
s16 mb64_menu_index_max = 1;
s8 mb64_toolbar_index = 0;
s8 mb64_toolbox_index = 0;
s16 mb64_tip_timer = 0;

char *mb64_topleft_message = NULL;
u8 mb64_topleft_is_tip = FALSE;
u16 mb64_topleft_max_timer = 120;
u16 mb64_topleft_timer = 0;
f32 mb64_topleft_vels[3];

// Position, velocity, acceleration
f32 mb64_menu_button_vels[10][3] = {0.f};
f32 mb64_menu_title_vels[3] = {0.f};
s16 mb64_menu_start_timer = -1;
s16 mb64_menu_end_timer = -1;
s8 mb64_menu_going_back = 1;
void (*mb64_option_changed_func)(void) = NULL;

s8 mb64_mm_selected_level = 0;
u8 mb64_greyed_text = FALSE;
u8 mb64_joystick;
u8 mb64_joystick_timer = 0;

u8 joystick_direction(void) {
    if (mb64_joystick_timer > 0) {
        mb64_joystick_timer--;
    }

    if ((gPlayer1Controller->rawStickX < 10)&&(gPlayer1Controller->rawStickX > -10)&&(gPlayer1Controller->rawStickY < 10)&&(gPlayer1Controller->rawStickY > -10)) {
        mb64_joystick_timer = 0;
    }

    if (mb64_joystick_timer == 0) {
        if (gPlayer1Controller->rawStickX > 60) {
            mb64_joystick_timer = 5;
            return 3;
        }
        if (gPlayer1Controller->rawStickX < -60) {
            mb64_joystick_timer = 5;
            return 1;
        }
        if (gPlayer1Controller->rawStickY > 60) {
            mb64_joystick_timer = 5;
            return 4;
        }
        if (gPlayer1Controller->rawStickY < -60) {
            mb64_joystick_timer = 5;
            return 2;
        }
    }

    return 0;
}

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
    print_generic_string_ascii(x-1, y-1, str);
    if (mb64_greyed_text) color += 2;
    gDPSetEnvColor(gDisplayListHead++, mb64_text_colors[color][0], mb64_text_colors[color][1], mb64_text_colors[color][2], alpha);
    print_generic_string_ascii(x, y, str);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

void print_maker_string_ascii(s32 x, s32 y, char *str, s32 color) {
    print_maker_string_ascii_alpha(x, y, str, color, 255);
}

void print_maker_string_ascii_nofileext(s32 x, s32 y, char *str, s32 color) {
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
    print_generic_string_ascii_nofileext(x-1, y-1, str);
    if (mb64_greyed_text) color += 2;
    gDPSetEnvColor(gDisplayListHead++, mb64_text_colors[color][0], mb64_text_colors[color][1], mb64_text_colors[color][2], 255);
    print_generic_string_ascii_nofileext(x, y, str);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
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
void animate_list_reset(void) {
    animate_list_offset_reset(mb64_menu_list_offsets, ARRAY_COUNT(mb64_menu_list_offsets));
}
void animate_toolbar_reset(void) {
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
u8 mb64_disable_menu_inputs = FALSE;

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
    mb64_custom_theme_menu_open = FALSE;
    mb64_greyed_text = FALSE;
    mb64_disable_menu_inputs = FALSE;
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


Gfx *get_button_tex(u32 buttonId, u32 objIndex) {
    if (mb64_ui_buttons[buttonId].placeMode == MB64_PM_OBJ) {
        u32 id;
        if (mb64_ui_buttons[buttonId].multiObj) {
            id = mb64_ui_buttons[buttonId].idList[objIndex];
        } else {
            id = mb64_ui_buttons[buttonId].id;
        }
        return mb64_object_type_list[id].btn;
    }
    if (buttonId == MB64_BUTTON_BLANK) return mat_b_btn_blank;
    return mb64_terrain_info_list[mb64_ui_buttons[buttonId].id].button;
}

char *get_button_str(u32 buttonId) {
    if (mb64_ui_buttons[buttonId].placeMode == MB64_PM_OBJ) {
        if (mb64_ui_buttons[buttonId].multiObj) {
            return mb64_ui_buttons[buttonId].name;
        } else {
            u32 id = mb64_ui_buttons[buttonId].id;
            return mb64_object_type_list[id].name;
        }
    }
    return mb64_terrain_info_list[mb64_ui_buttons[buttonId].id].name;
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
                                s8 scroll[2], u32 color, s32 dir) {
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

void mb64_show_topleft_message(char *message, s32 isTip) {
    mb64_topleft_is_tip = isTip;
    mb64_topleft_max_timer = (isTip ? 220 : 120);
    if ((message != mb64_topleft_message) || (mb64_topleft_timer < 30)) {
        mb64_topleft_message = message;
        mb64_topleft_timer = mb64_topleft_max_timer;
    } else {
        if (mb64_topleft_timer < mb64_topleft_max_timer - 30) mb64_topleft_timer = mb64_topleft_max_timer - 30;
    }
}
void mb64_show_error_message(char *message) {
    mb64_show_topleft_message(message, FALSE);
    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
}

void mb64_show_tip() {
    s32 count = ARRAY_COUNT(mb64_tips);
    if (mb64_lopt_game != MB64_GAME_BTCM) count -= NUM_BTCM_TIPS;
    mb64_show_topleft_message(mb64_tips[(s32)(random_float() * count)], TRUE);
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

void mb64_set_data_overrides(void) {
    //Theme-specific data
    bzero(&mb64_toolbox_params, sizeof(mb64_toolbox_params));
    switch(mb64_lopt_game) {
        case MB64_GAME_BTCM:
            bcopy(&mb64_toolbox_btcm,&mb64_toolbox,sizeof(mb64_toolbox));
            mb64_exclamation_box_contents = sExclamationBoxContents_btcm;
            break;
        case MB64_GAME_VANILLA:
            bcopy(&mb64_toolbox_vanilla,&mb64_toolbox,sizeof(mb64_toolbox));
            mb64_exclamation_box_contents = sExclamationBoxContents_vanilla;
            break;
    }
}



Gfx * custom_preview_gfx;
Vtx * custom_preview_vtx;


void draw_mb64_menu(void) {
    if (mb64_menu_state != MB64_MAKE_SCREENSHOT) {
        create_dl_translation_matrix(MENU_MTX_PUSH, 19 + 142, 36 - 80, 0);
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

    if (mb64_disable_menu_inputs) {
        gPlayer1Controller->buttonPressed = 0;
        gPlayer1Controller->buttonDown = 0;
        gPlayer1Controller->rawStickX = 0;
        gPlayer1Controller->rawStickY = 0;
        mb64_joystick = 0;
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

            create_dl_translation_matrix(MENU_MTX_PUSH, 19 + 142, 235 - 80 +yOff, 0);
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

struct mb64_info_entry {
    char * text;
    u32 color;
};

struct mb64_info_entry mb64_credits[] = {
    {"Mario Builder 64",1},
    {"By Arthurtilly & Rovertronic",0},
    {"2024",0},
    {"",0},
    {"SD Card Support",1},
    {"Devwizard",0},
    {"Falcobuster",0},
    {"",0},
    {"Title Screen Model",1},
    {"Biobak",0},
    {"",0},
    {"Various Assets",1},
    {"BroDute",0},
    {"Thodds",0},
    {"Yoshi Milkman",0},
    {"Dorrieal",0},
    {"CowQuack",0},
    {"Pixelissimo",0},
    {"",0},
    {"GitHub Contributors",1},
    {"aglab2",0},
    {"ArcticJaguar725",0},
    {"jefftastic",0},
    {"Polprzewodnikowy",0},
    {"Stevoisiak", 0},
    {"",0},
    {"Beyond the Cursed Mirror OST",1},
    {"SpK",0},
    {"Thorndust",0},
    {"",0},
    {"Music Ports",1},
    {"SMWCentral",0},
    {"SM64 Editor",0},
    {"",0},
    {"HackerSM64",1},
    {"HackerN64 Team",0},
    {NULL, 0},
};

struct mb64_info_entry mb64_v1_1_changelog[] = {
    {"Mario Builder 64 - v1.1 Changelog",1},
    {"",0},
    {"", 0},
    {"Major Changes", 1},
    {"", 0},
    {"- Increased vertex limit from 40,000 to 50,000", 0},
    {"- Increased tile limit from 10,000 to 20,000", 0},
    {"- Optimized vertex generation by up to 25%", 0},
    {"- New boundary type: Interior",0},
    {"- New object: On-Off Conveyor",0},
    {"- New object: Inverted Timed Box",0},
    {"- New object: Star Trigger",0},
    {"- New Sample Tile building shortcut by pressing L & R", 0},
    {"- Ability to place multiple objects/tiles in the same spot", 0},
    {"- Dialog to exit a level after collecting every star",0},
    {"- Added a speedrun timer option in the pause menu", 0},
    {"- Added a Star Radar option in the pause menu", 0},
    {"- Added 5 new level templates", 0},
    {"", 0},
    {"Conveyors", 1},
    {"", 0},
    {"- Added thin and sloped conveyors", 0},
    {"- Added red/blue on-off conveyors", 0},
    {"- The underside of conveyors are now hangable", 0},
    {"- Improved conveyor physics", 0},
    {"", 0},
    {"Imbuing System", 1},
    {"", 0},
    {"- All enemies can be given objects to drop on death", 0},
    {"- Objects can be placed inside ! Boxes", 0},
    {"- Can now place Red Coins and Green Coins inside objects", 0},
    {"- Can now place Badges and Powerups inside objects", 0},
    {"- Dropped objects appear at the object's last safe location", 0},
    {"- Boxes with yellow coins drop 3 coins instead of 1", 0},
    {"- Boos and Moneybags show the item they will drop", 0},
    {"- New Star Trigger can only be placed inside objects",0},
    {"    When all Star Triggers are activated, a star will spawn",0},
    {"    Star Triggers can also be placed inside coins and badges",0},
    {"", 0},
    {"Badge Changes", 1},
    {"", 0},
    {"- Removed Star Radar badge in favor of a pause menu option", 0},
    {"- Star Radar consistently always shows the closest star", 0},
    {"- Star Radar shows red coins if all stars are collected", 0},
    {"- Buffed Heal Plus badge to apply to all coins", 0},
    {"- Buffed/renamed Double Damage badge to One Hit badge", 0},
    {"- Buffed Defense badge to spend 1 mana per hit instead of 4", 0},
    {"- Buffed Burn badge to not consume mana", 0},
    {"", 0},
    {"Editor Tweaks", 1},
    {"", 0},
    {"- Ability to hide help text in screenshot mode", 0},
    {"- Screenshot mode has been moved to the System menu", 0},
    {"- Custom Theme menu shows slipperiness of current tile", 0},
    {"- Display the current number of placed objects in the", 0},
    {"    editor when placing Stars or Red Coins", 0},
    {"- Objects now have shadows in the editor", 0},
    {"- Improved vertex/tile/object limit display", 0},
    {"- Better warnings for vertex limit and having FBE disabled", 0},
    {"- Improved cursor wrapping around the sides of the level", 0},
    {"- Faster navigation between level pages using left/right", 0},
    {"- Muting music no longer requires a level reset", 0},
    {"- Added the Bowling Ball to the BTCM gamemode", 0},
    {"", 0},
    {"Gameplay Tweaks", 1},
    {"", 0},
    {"- Objects can trigger Activated Moving Platforms", 0},
    {"- Wooden Platforms form a stack when placed vertically", 0},
    {"- Bowling Balls can destroy boxes and kill enemies", 0},
    {"- Hammer Bro's hammers can destroy boxes and kill enemies", 0},
    {"- Throwable and Crazy Boxes respawn after being broken", 0},
    {"- Using a Noteblock no longer forces you to drop objects", 0},
    {"    or stop riding a shell", 0},
    {"- Koopa the Quick respawns after losing the race", 0},
    {"- Nerfed the Showrunner", 0},
    {"- Collecting a Power Star fully heals Mario", 0},
    {"- Bowser no longer instantly dies to lava", 0},
    {"- BTCM Powerups can be used simultaneously",0},
    {"- The crowbar can hit multiple objects at once", 0},
    {"- The crowbar can be used to pick up coins", 0},
    {"- Heavily improved Thwomp physics and interactions", 0},
    {"- Physics given to Mr. Blizzard and Piranha Plants", 0},
    {"- AI and physics improvements for all enemies", 0},
    {"", 0},
    {"Improved Assets", 1},
    {"", 0},
    {"- Better texture mapping for slopes", 0},
    {"- Better object models for Wooden Platform, On-Off Block,", 0},
    {"    On-Off Switch, Reinforced Box, Fire Spinner", 0},
    {"- Improved textures: Quicksand, Cosmic Void, Rocky Dirt,", 0},
    {"    Green Rock, Ocean Floor, Scorched Pillar, Hazard Stripes",0},
    {"- Improved certain music ports (thanks to Pixelissimo)",0},
    {"", 0},
    {"Bug Fixes", 1},
    {"", 0},
    {"- BTCM void respawn mechanic not working", 0},
    {"- Bottomless badge having no effect", 0},
    {"- Incorrect star IDs with 8 or more stars", 0},
    {"- Infinite coin exploit from Blue Coin previews", 0},
    {"- Trajectory data not resetting between levels", 0},
    {"- Crash when climbing poles with Mario cam", 0},
    {"- Wooden platforms not squishing Mario", 0},
    {"- Softlock on top of fences at the level boundary", 0},
    {"- Lava bubbles appearing far below the level", 0},
    {"- Glitchy bully physics in midair and on snow/ice", 0},
    {"- Bug allowing unlimited stars to be placed", 0},
    {"- Failure to load levels on some flashcarts", 0},
    {"- String overflow glitches in level and author names", 0},
    {"- Periods not being allowed in level names",0},
    {"- Bad handling of invalid level files", 0},
    {"- Level files corrupting if the vertex limit is exceeded", 0},
    {"- Broken menus with widescreen viewport hack enabled",0},
    {"- BTCM templates selecting the wrong music tracks", 0},
    {"- Infinite flight time bug with the Bullet Bill Mask", 0},
    {"- Fire spinners having the incorrect rotation ingame",0},
    {"- Broken boss music with multiple bosses",0},
    {"- Exiting on a moving platform not resetting inertia",0},
    {"- HUD issues with the air bubble and rocket fuel meters",0},
    {"- Spinning around when flying after sliding down a pole", 0},
    {"- Broken camera when collecting a badge while flying", 0},
    {"- Cosmic Phantasms copying model state from Mario", 0},
    {"- Countless minor physics and AI fixes", 0},
    {NULL, 0},
};

struct mb64_info_entry mb64_editor_controls[] = {
    {"Navigation Controls",1},
    {"",0},
    {"  Analog Stick:  Move cursor horizontally",0},
    {"  \x14 ^ / |:  Move cursor vertically",0},
    {"  \x14 < / >:  Rotate camera",0},
    {"  D-Pad |:  Change camera zoom",0},
    {"",0},
    {"Building Controls",1},
    {"",0},
    {"  \x10:  Place tile",0},
    {"  \x11:  Delete tile(s)",0},
    {"  \x12:  Rotate tile",0},
    {"  D-Pad < / >:  Change object parameters",0},
    {"  D-Pad ^:  Flip tile vertically",0},
    {"",0},
    {"Toolbar Controls",1},
    {"",0},
    {"  L / R:  Navigate hotbar",0},
    {"  L & R:  Sample tile",0},
    {"  START:  Open toolbox",0},
    {NULL, 0},
};

struct mb64_info_entry mb64_setup_guide[] = {
    {"Emulator Setup", 1},
    {"",0},
    {"To save your Mario Builder 64 levels and play levels",0},
    {"created by other people, you will need to use an emulator",0},
    {"that supports SD card emulation. This does NOT require",0},
    {"you to own a physical SD card.",0},
    {"",0},
    {"Alternatively, you can use a flashcart on a real",0},
    {"N64 together with a physical SD card.", 0},
    {"",0},
    {"Supported Emulators", 1},
    {"",0},
    {"Parallel Launcher",1},
    {"               https://parallel-launcher.ca/",0},
    {"",0},
    {"Luna's Project64",1},
    {"    https://github.com/Luna-Project64/Luna-Project64",0},
    {"",0},
    {"",0},
    {"Recommended Settings",1},
    {"",0},
    {"Use the GlideN64 graphics plugin. Make sure that",0},
    {"FBE (Framebuffer Emulation) is enabled.",0},
    {"",0},
    {"For Parallel Launcher, make sure 'Overclock VI' is ticked,",0},
    {"and the setting 'Emulate SummerCart64 SD card interface'",0},
    {"is enabled.",0},
    {"",0},
    {"For Luna's PJ64, set Counter Factor to 0.",0},
    {"",0},
    {"Accessing Level Files",1},
    {"",0},
    {"To access your level files, you will need to mount the",0},
    {"SD card image through the emulator. This will require",0},
    {"administrative permissions through a popup.",0},
    {"Once you have done this, you can find any saved levels",0},
    {"in the 'Mario Builder 64 Levels' folder in the drive.",0},
    {"You can also move any downloaded levels into this folder",0},
    {"to play them.",0},
    {"",0},
    {"Parallel Launcher",1},
    {"Click the button to the right of the SD card dropdown",0},
    {"to open the SD card menu. Select the SD card and click",0},
    {"'Browse Files' to mount the SD card.",0},
    {"Click 'OK' to unmount once you are done.",0},
    {"",0},
    {"Luna's Project64",1},
    {"Click 'File' -> 'Mount SD Card'.",0},
    {"When you are done, eject the SD card drive through",0},
    {"File Explorer, and click 'File' -> 'Unmount SD Card'.",0},
    {"",0},
    {"",0},
    {"Note: You may get a false virus alert from Windows Defender",0},
    {"upon attempting to mount the SD card. These emulators are",0},
    {"guaranteed to be safe to use, so you may need to exclude",0},
    {"the .exe file from Windows Defender.",0},
    {"",0},
    {"For a more detailed guide, visit",0},
    {"https://rentry.co/mb64-setup-guide",0},
    {NULL, 0},
};

struct mb64_info_entry mb64_level_sharing[] = {
    {"Level Sharing", 1},
    {"",0},
    {"You can upload your .mb64 files online and download levels", 0},
    {"from other people at Level Share Square, the dedicated",0},
    {"website.",0},
    {"",0},
    {"Level Share Square",1},
    {"           https://levelsharesquare.com/levels",0},
    {"",0},
    {"",0},
    {"Be sure to also join the official Mario Builder 64 Discord",0},
    {"server for updates, announcements and discussion!",0},
    {"",0},
    {"Mario Builder 64 Discord",1},
    {"             https://discord.gg/4qt2DP4Dyy",0},
    {NULL, 0},
};

void *mb64_mm_page_data = NULL;
s32 info_y_offset = 0;
void print_maker_info_page(void) {
    struct mb64_info_entry *curPage = mb64_mm_page_data;
    u32 leftalign = (mb64_mm_page_data != mb64_credits);
    
    s32 info_entries = 0;
    while (curPage[info_entries].text != NULL) {
        info_entries++;
    }

    s32 lower_limit = (info_entries*16) - 160;

    u8 base_alpha = 255;
    if (mb64_menu_start_timer != -1) {
        u8 time = MIN(mb64_menu_start_timer, 8);
        base_alpha = (time * 255) / 8;
    } else if (mb64_menu_end_timer != -1 && !(mb64_mm_state == MM_KEYBOARD && mb64_menu_going_back == 1)) {
        u8 time = MIN(mb64_menu_end_timer, 8);
        base_alpha = 255 - ((time * 255) / 8);
    }

    info_y_offset -= (gPlayer1Controller->rawStickY/10.0f);
    if (info_y_offset <= 0) {
        info_y_offset = 0;
    }
    if (info_y_offset >= lower_limit) {
        info_y_offset = lower_limit;
    }
    if (info_y_offset != lower_limit) {
        print_maker_string_ascii_centered_alpha(300,20 + sins(gGlobalTimer*0x300)*2.5f ,"|",MB64_TEXT_WHITE,base_alpha);
    }
    if (info_y_offset != 0) {
        print_maker_string_ascii_centered_alpha(300,40 - sins(gGlobalTimer*0x300)*2.5f,"^",MB64_TEXT_WHITE,base_alpha);
    }

    for (int i=0; i<info_entries; i++) {
        u8 alpha = base_alpha;
        s32 ypos = info_y_offset+200-(16*i);
        if ((ypos < 220)&&(ypos >10)) {
            if (ypos > 200) {
                alpha = ((base_alpha/255.0f)*smoothstep2(220.0f,200.0f,ypos))*255.0f;
            }
            if (ypos < 30) {
                alpha = ((base_alpha/255.0f)*smoothstep2(10.0f,30.0f,ypos))*255.0f;
            }
            if (leftalign && curPage[i].color == 0) {
                print_maker_string_ascii_alpha(15,ypos, curPage[i].text, curPage[i].color, alpha);
            } else {
                print_maker_string_ascii_centered_alpha(160,ypos, curPage[i].text, curPage[i].color, alpha);
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
    "MB64 Setup Guide",
    "Editor Controls",
    "Share Levels",
    "Changelog",
};

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
        print_maker_string_ascii(243, 188 + mb64_menu_title_vels[0], "v1.1", MB64_TEXT_WHITE);
        print_maker_string_ascii_centered(160, 175 + mb64_menu_title_vels[0], "By: Arthurtilly & Rovertronic", MB64_TEXT_WHITE);
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

    if ((mb64_mm_state != MM_INFO)) {
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
                    strncpy(&mb64_username, &mb64_sram_configuration.author, MAX_USERNAME_SIZE);
                    mb64_has_username = TRUE;
                } else {
                    //no author file detected, prompt user to enter an author name
                    mb64_mm_keyboard_exit_mode = KXM_AUTHOR;
                    mb64_mm_keyboard_max_input_length = MAX_USERNAME_SIZE - 1;
                    mb64_mm_state = MM_KEYBOARD;
                    mb64_mm_keyboard_input_index = 0;

                    //check for rhdc username
                    if (gSupportsLibpl) {
                        const char *rhdc_username = libpl_get_my_rhdc_username();
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
                        info_y_offset = 0;
                        mb64_mm_state = MM_INFO;
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
                        info_y_offset = 0;
                        mb64_mm_state = MM_INFO;
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
                    info_y_offset = 0;
                    mb64_mm_state = MM_INFO;
                    switch(mb64_menu_index) {
                        case 0:
                            mb64_mm_page_data = mb64_setup_guide;
                            break;
                        case 1:
                            mb64_mm_page_data = mb64_editor_controls;
                            break;
                        case 2:
                            mb64_mm_page_data = mb64_level_sharing;
                            break;
                        case 3:
                            mb64_mm_page_data = mb64_v1_1_changelog;
                    }
                }
            }
            break;
        case MM_INFO:
            mb64_mm_shade_screen();
            if (mb64_mm_anim_info()) {
                mb64_menu_start_timer = 0;
                if (mb64_mm_page_data == mb64_credits) {
                    mb64_mm_state = mb64_mm_main_state;
                    mb64_menu_index = 3;
                } else {
                    mb64_mm_state = MM_HELP_MODE;
                }
            }
            print_maker_info_page();
            break;
        case MM_KEYBOARD:
            mb64_mm_anim_in(6);
            switch(mb64_joystick) {
                case 1:
                    mb64_mm_keyboard_index--;
                    if ((mb64_mm_keyboard_index+10)%10 == 9) {
                        mb64_mm_keyboard_index+=10;
                    }
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                break;
                case 2:
                    mb64_mm_keyboard_index+=10;
                break;
                case 3:
                    mb64_mm_keyboard_index++;
                    if (mb64_mm_keyboard_index%10 == 0) {
                        mb64_mm_keyboard_index-=10;
                    }
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

            f32 inputX = 30 + mb64_menu_button_vels[1][0];
            gDPPipeSync(gDisplayListHead++);
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 100);
            gDPSetCombineMode(gDisplayListHead++, G_CC_ENVIRONMENT, G_CC_ENVIRONMENT);
            gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPFillRectangle(gDisplayListHead++, CLAMP(inputX, 0, 320), (240-185)-16, CLAMP(inputX + 250, 0, 320), (240-185)+3);


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
                        strncpy(&mb64_sram_configuration.author, &mb64_username, MAX_USERNAME_SIZE);
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
            } else {
                if ((mb64_joystick == 3 || gPlayer1Controller->buttonPressed & R_TRIG) && (mb64_mm_page < mb64_mm_pages - 1)) {
                    startRenderIndex += PAGE_SIZE;
                    mb64_menu_index += PAGE_SIZE;
                    mb64_menu_index = MIN(mb64_menu_index, mb64_level_entry_count - 1);
                    mb64_mm_page++;
                } else if ((mb64_joystick == 1 || gPlayer1Controller->buttonPressed & L_TRIG) && mb64_mm_page > 0) {
                    startRenderIndex -= PAGE_SIZE;
                    mb64_menu_index -= PAGE_SIZE;
                    mb64_mm_page--;
                }
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
                    print_maker_string_ascii_nofileext(75 + xPosAnim,startRenderY - 10 -(i*36),level_entries_ptr[startRenderIndex + i].fname,(selectedIndex == renderIndex));
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
    "Star Radar",
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
                create_dl_scale_matrix(MENU_MTX_NOPUSH, 1.5f, 1.5f, 0.f);
                print_generic_string_ascii_centered_nofileext(0,134,mb64_file_name);
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
                        mb64_pause_menu_state = 0;
                        mb64_menu_index = 0;
                        if (gSramProbe != 0) {
                            nuPiWriteSram(0, &mb64_sram_configuration, ALIGN8(sizeof(mb64_sram_configuration)));
                        }
                        play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                        break;
                    default:
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