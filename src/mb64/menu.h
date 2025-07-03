#pragma once

extern u8 mb64_menu_state;
extern s16 mb64_menu_index;
extern s16 mb64_menu_index_max;
extern s8 mb64_toolbar_index;
extern s8 mb64_toolbox_index;
extern s16 mb64_tip_timer;

extern s16 mb64_menu_start_timer;
extern s16 mb64_menu_end_timer;
extern void (*mb64_option_changed_func)(void);
extern u8 mb64_joystick;

Gfx *get_button_tex(u32 buttonId, u32 objIndex);
u8 joystick_direction(void);
void mb64_show_error_message(char *message);

enum TextColors {
    MB64_TEXT_WHITE,
    MB64_TEXT_YELLOW,
    MB64_TEXT_GRAY,
    MB64_TEXT_DARK_YELLOW,
    MB64_TEXT_RED,
    MB64_TEXT_LIGHTBLUE,
};
