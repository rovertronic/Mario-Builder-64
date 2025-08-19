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

void print_maker_string_ascii_alpha(s32 x, s32 y, char *str, s32 color, s32 alpha) {
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, alpha);
    print_generic_string_ascii(x-1, y-1, str);
    gDPSetEnvColor(gDisplayListHead++, mb64_text_colors[color][0], mb64_text_colors[color][1], mb64_text_colors[color][2], alpha);
    print_generic_string_ascii(x, y, str);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

void print_maker_string_ascii(s32 x, s32 y, char *str, s32 color) {
    print_maker_string_ascii_alpha(x, y, str, color, 255);
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

void full_menu_reset() {
}

// sets some stuff after exiting play mode into the file selector
void mb64_init_exit_to_files() {
    mb64_mode = MB64_MODE_UNINITIALIZED;
    mb64_lopt_template = 0;
    mb64_lopt_size = 0;
    mb64_lopt_game = MB64_GAME_VANILLA;
}

void mb64_show_tip() {
    //s32 count = ARRAY_COUNT(mb64_tips);
    //if (mb64_lopt_game != MB64_GAME_BTCM) count -= NUM_BTCM_TIPS;
    //mb64_show_topleft_message(mb64_tips[(s32)(random_float() * count)], TRUE);
}

void mb64_render_coord_display(void) {
    // if (mb64_tip_timer != 0) {
    //     mb64_coord_vels[0] = 250.f;
    //     mb64_coord_vels[1] = 0.f;
    //     mb64_coord_vels[2] = 0.f;
    //     return;
    // }
    // animate_menu_ease_in(mb64_coord_vels, 255.f, 215.f, 0.4f, (mb64_topleft_is_tip && mb64_topleft_timer != 0));

    // char buf[20];
    // sprintf(buf, "%d, %d, %d", mb64_cursor_pos[0], mb64_cursor_pos[1], mb64_cursor_pos[2]);
    // print_maker_string_ascii(255, mb64_coord_vels[0], buf, MB64_TEXT_WHITE);
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
