#include "menu_engine.h"

#include "game/area.h"
#include "game/save_file.h"

u8 badgecolors[24][3] = {
    {255,0x00,0x00},
    {0x9C,0x43,0x22},
    {0x19,0x6B,0xC7},
    {0xDF,0x4A,0x18},
    {0x6C,0xC6,0xD7},
    {0x6C,0xC6,0xD7},
    {0x72,0xC6,0xAE},
    {0xF9,0x8D,0xCF},
    {0xF8,0xB6,0x4B},
    {0x4A,0x52,0x8C},
    {0x44,0xC6,0x53},

    {0xEA,0x55,0x20},
    {0x46,0x4D,0xBE},
    {0x60,0x8E,0xA0},
    {0xAC,0x6E,0x56},
    {0x44,0xAF,0x19},
    {0x21,0xE9,0xA1},
    {0x57,0xFF,0x4C},
    {0x4B,0x6D,0x7A},
    {8,231,247},
    {0xA0,0x00,0x00},
    {0xA0,0x00,0x00},
};

enum PauseMenuPages {
    PAUSE_PAGE_MAIN,
    PAUSE_PAGE_OPTIONS,
    PAUSE_PAGE_BADGES,
};

RectComponent *gPauseMenu;
int sPauseMenuClosed = FALSE;
int sPauseMenuPage = PAUSE_PAGE_MAIN;
int sPrevMenuIndex = 0;

MenuStyle pause_menu_style = {
    .textHighlightSelected = FALSE,
    .textNoShadow = TRUE,
    .noClickSounds = TRUE,
};

void close_pause_menu(int menuOpt) {
    if (gMenuOptSelectIndex != MENU_OPT_NONE) return;
    sPauseMenuClosed = TRUE;
    level_set_transition(0, NULL);
    gMenuOptSelectIndex = menuOpt;
}

void pause_menu_change_page(int page) {
    play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
    sPauseMenuPage = page;
}

void pause_menu_loop(UNUSED MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    if (sPauseMenuClosed) {
        play_sound(SOUND_MENU_PAUSE_CLOSE, gGlobalSoundSource);
        dealloc_component(get_id(gPauseMenu));
        gPauseMenu = NULL;
        return;
    }

    gMenuOptSelectIndex = MENU_OPT_NONE;
    set_menu_style(pause_menu_style);

    FrameComponent *curPage = get_child(gPauseMenu);
    if (curPage->params[0].asInt != sPauseMenuPage) {
        dealloc_component(get_id(curPage));
        create_pause_menu_page(sPauseMenuPage);
    } else {
        switch (sPauseMenuPage) {
            case PAUSE_PAGE_MAIN:
                if (gPlayer1Controller->buttonPressed & START_BUTTON) {
                    gPlayer1Controller->buttonPressed |= A_BUTTON;
                }
                if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                    close_pause_menu(MENU_OPT_CONTINUE);
                }
                break;
            case PAUSE_PAGE_BADGES:
            case PAUSE_PAGE_OPTIONS:
                if (gPlayer1Controller->buttonPressed & START_BUTTON) {
                    close_pause_menu(MENU_OPT_CONTINUE);
                } else if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                    pause_menu_change_page(PAUSE_PAGE_MAIN);
                }
        }
    }
}

extern Gfx *bicon_table[];
void badge_page_render(Selector2DComponent *m, s16 x, s16 y, u8 column, u8 row, int selected) {
    int index = column + row * m->columns;
    int rowLength = (row == m->rows-1 ? (m->count-1) % m->columns + 1 : m->columns);
    x += -(((rowLength - 1) * 32) >> 1) + 32 * column;
    y -= 32 * row - 40;
    if (selected) {
        y += sins(gGlobalTimer * 0x600) * 3.2f;
    }

    // Get badge
    int badgeid = -1;
    for (int i = 0; i < index+1; i++) {
        do {
            badgeid++;
        } while (!(mb64_play_badge_bitfield & (1 << badgeid)));
    }
    create_dl_translation_matrix(MENU_MTX_PUSH, x, y, 0);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    gDPSetRenderMode(gDisplayListHead++,G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    gSPDisplayList(gDisplayListHead++, bicon_table[badgeid]);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    if (!selected) return;

    gDPSetEnvColor(gDisplayListHead++, badgecolors[badgeid][0], badgecolors[badgeid][1], badgecolors[badgeid][2], 255);
    int width = get_string_width(badgenames[badgeid])/2;
    print_generic_string(SCREEN_WIDTH/2 - width, 50, badgenames[badgeid]);
    width = get_string_width(badgedescs[badgeid])/2;
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    print_generic_string(SCREEN_WIDTH/2 - width, 30, badgedescs[badgeid]);
}

u8 pause_menu_options[5];

// Quick toggle for options when pressing A
void pause_selector_check_toggle(MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    SelectorComponent *s = (SelectorComponent *)m;
    if (gMenuState.selected && gPlayer1Controller->buttonPressed & A_BUTTON) {
        *(s->value) ^= 1;
        pause_option_changed();
        play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
    }
}

void pause_option_changed(void) {
    for (int i = 0; i < 5; i++) {
        mb64_sram_configuration.option_flags &= ~(1 << i);
        mb64_sram_configuration.option_flags |= (pause_menu_options[i] << i);
    }
}

char *pause_menu_toggle_vals[] = {"Off", "On"};
void add_pause_menu_option(ListComponent *options, int i, char *text) {
    TextComponent *t = init_text_component(NULL, 0, 0, text, TEXT_LEFT, TEXT_WHITE);
    t->base.prerender = listitem_render_triangle;
    ListItemComponent *listitem = component_list_append(options, t, 0, -i * 16);

    pause_menu_options[i] = (mb64_sram_configuration.option_flags & (1 << i)) != 0;
    SelectorComponent *s = init_array_selector(listitem, &pause_menu_options[i], 10, 2, pause_menu_toggle_vals, pause_option_changed);
    component_set_pos(s, 105, 0);
    s->base.prerender = pause_selector_check_toggle;
}

void add_pause_menu_button(ListComponent *options, int i, char *text, ComponentUpdateFunc onClick, int arg) {
    TextComponent *t = init_text_button(NULL, 0, 0, text, TEXT_LEFT, onClick, arg);
    t->base.prerender = listitem_render_triangle;
    component_list_append(options, t, 0, -i * 16);
}


void pause_button_close(TextComponent *btn) {
    close_pause_menu(btn->onClickArg);
}
void pause_button_change_page(TextComponent *btn) {
    pause_menu_change_page(btn->onClickArg);
}

char authornamebuf[MAX_USERNAME_SIZE + 3];
extern struct MarioState gMarioStates[1];
void create_pause_menu_page(int pagenum) {
    FrameComponent *page = init_frame_component(gPauseMenu);
    page->params[0].asInt = pagenum;
    ListComponent *options;
    int index = sPrevMenuIndex;

    switch (pagenum) {
        case PAUSE_PAGE_MAIN:
            MatrixComponent *scale = init_matrix_component(page, 0, 2.f, 2.f);
            component_set_pos(scale, 0, 65);
            TextComponent *name = init_text_component(scale, 0, 0, mb64_file_name, TEXT_CENTER, TEXT_WHITE);
            name->skipExtension = TRUE;
            sprintf(authornamebuf, "By %s", mb64_save.author);
            init_text_component(page, 0, 50, authornamebuf, TEXT_CENTER, TEXT_WHITE);

            options = init_list(page, DIR_VERTICAL, MENU_INPUT_JOYSTICK);
            component_set_pos(options, -20, -20);
            add_pause_menu_button(options, 0, "Continue", pause_button_close, MENU_OPT_CONTINUE);
            add_pause_menu_button(options, 1, "Exit Level", pause_button_close, MENU_OPT_EXIT_COURSE);
            add_pause_menu_button(options, 2, "Options", pause_button_change_page, PAUSE_PAGE_OPTIONS);
            if (mb64_lopt_game == MB64_GAME_BTCM && count_u32_bits(mb64_play_badge_bitfield) != 0) {
                add_pause_menu_button(options, 3, "Badges", pause_button_change_page, PAUSE_PAGE_BADGES);
            }

            init_counter_component(page, 0, 30, '#', &mb64_play_stars, mb64_play_stars_max, TEXT_CENTER);
            int hasRedCoins = (gRedCoinsTotal > 0);
            int hasCoinStar = (mb64_lopt_coinstar > 0);
            int redcoinX = (hasCoinStar ? -60 : 0);
            int coinstarX = (hasRedCoins ? 60 : 0);
            if (hasRedCoins) {
                init_counter_component(page, redcoinX, -90, '&', &gRedCoinsCollected, gRedCoinsTotal, TEXT_CENTER);
            }
            if (hasCoinStar) {
                init_counter_component(page, coinstarX, -90, '$', &gMarioStates[0].numCoins, mb64_lopt_coinstar*20, TEXT_CENTER);
            }
            sPrevMenuIndex = 5;
            break;
        case PAUSE_PAGE_OPTIONS:
            options = init_list(page, DIR_VERTICAL, MENU_INPUT_JOYSTICK);
            component_set_pos(options, -70, 40);
            add_pause_menu_option(options, 0, "Play Music:");
            add_pause_menu_option(options, 1, "Show HUD:");
            add_pause_menu_option(options, 2, "Camera Collision:");
            add_pause_menu_option(options, 3, "Speedrun Timer:");
            add_pause_menu_option(options, 4, "Star Radar:");
            add_pause_menu_button(options, 5, "Return", pause_button_change_page, PAUSE_PAGE_MAIN);
            sPrevMenuIndex = 2;
            break;
        case PAUSE_PAGE_BADGES:
            int numBadges = count_u32_bits(mb64_play_badge_bitfield);
            Selector2DComponent *badges = init_selector_2d_component(page, 0, 0, 8, numBadges, badge_page_render, NULL);
            sPrevMenuIndex = 3;
            break;
    }

    if (options) {
        options->index = index;
    }
}

void create_pause_menu(void) {
    level_set_transition(-1, NULL);
    play_sound(SOUND_MENU_PAUSE_OPEN, gGlobalSoundSource);
    sPauseMenuClosed = FALSE;
    sPauseMenuPage = PAUSE_PAGE_MAIN;
    sPrevMenuIndex = 0;

    gPauseMenu = init_rect_component(gMenuRoot, 150, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    gPauseMenu->base.prerender = pause_menu_loop;
    create_pause_menu_page(sPauseMenuPage);
}
