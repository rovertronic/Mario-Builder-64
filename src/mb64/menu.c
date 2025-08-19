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

// sets some stuff after exiting play mode into the file selector
void mb64_init_exit_to_files() {
    mb64_mode = MB64_MODE_UNINITIALIZED;
    mb64_lopt_template = 0;
    mb64_lopt_size = 0;
    mb64_lopt_game = MB64_GAME_VANILLA;
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

Gfx *custom_preview_gfx;
Vtx *custom_preview_vtx;

void draw_mb64_menu(void) {
    return;

    //TOOLBOX
    switch (mb64_menu_state) {
        case MB64_MAKE_MAIN:
            break;

        case MB64_MAKE_TRAJECTORY:
            //print_maker_string(20,210,mb64_txt_recording,TRUE);
            break;

        case MB64_MAKE_SCREENSHOT:
            //print_maker_string(20,210,mb64_txt_freecam,TRUE);
            break;

        case MB64_MAKE_SELECT_DIALOG:
            break;

    }
}
