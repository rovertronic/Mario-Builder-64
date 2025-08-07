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