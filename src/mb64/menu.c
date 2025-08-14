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
    return;

    //TOOLBOX
    switch (mb64_menu_state) {
        case MB64_MAKE_MAIN:
            mb64_render_coord_display();
            break;

        case MB64_MAKE_TRAJECTORY:
            print_maker_string(20,210,mb64_txt_recording,TRUE);
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
            break;

    }
}
