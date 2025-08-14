#include "menu_engine.h"

#include "game/area.h"

RectComponent *gPauseMenu;
int sPauseMenuClosed = FALSE;

MenuStyle pause_menu_style = {
    .textHighlightSelected = FALSE,
    .textNoShadow = TRUE,
    .noClickSounds = TRUE,
};

void pause_menu_loop(UNUSED MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    if (sPauseMenuClosed) {
        play_sound(SOUND_MENU_PAUSE_CLOSE, gGlobalSoundSource);
        dealloc_component(get_id(gPauseMenu));
        gPauseMenu = NULL;
        return;
    }

    gMenuOptSelectIndex = MENU_OPT_NONE;
    set_menu_style(pause_menu_style);

    if (gPlayer1Controller->buttonPressed & START_BUTTON) {
        gPlayer1Controller->buttonPressed |= A_BUTTON;
    }
}

void render_list_triangle(MenuComponent *m, s16 x, s16 y) {
    if (!gMenuState.selected) return;
    x += m->xpos - 15;
    y += m->ypos - 1;

    create_dl_translation_matrix(MENU_MTX_PUSH, x, y, 0);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void add_pause_menu_option(ListComponent *options, int i, char *text, ComponentUpdateFunc onClick) {
    TextComponent *t = init_text_button(NULL, 0, 0, text, TEXT_LEFT, onClick, 0);
    t->base.prerender = render_list_triangle;
    component_list_append(options, t, 0, -i * 16);
}

void begin_pause_menu_close(int menuOpt) {
    if (gMenuOptSelectIndex != MENU_OPT_NONE) return;
    sPauseMenuClosed = TRUE;
    level_set_transition(0, NULL);
    gMenuOptSelectIndex = menuOpt;
}

void pause_menu_continue(void) {
    begin_pause_menu_close(MENU_OPT_CONTINUE);
}
void pause_menu_exit_course(void) {
    begin_pause_menu_close(MENU_OPT_EXIT_COURSE);
}

char authornamebuf[MAX_USERNAME_SIZE + 3];
void create_pause_menu(void) {
    level_set_transition(-1, NULL);
    play_sound(SOUND_MENU_PAUSE_OPEN, gGlobalSoundSource);
    sPauseMenuClosed = FALSE;

    gPauseMenu = init_rect_component(gMenuRoot, 150, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    gPauseMenu->base.prerender = pause_menu_loop;

    MatrixComponent *scale = init_matrix_component(gPauseMenu, 0, 2.f, 2.f);
    component_set_pos(scale, 0, 65);
    TextComponent *name = init_text_component(scale, 0, 0, mb64_file_name, TEXT_CENTER, TEXT_WHITE);
    name->skipExtension = TRUE;
    sprintf(authornamebuf, "By %s", mb64_save.author);
    init_text_component(gPauseMenu, 0, 50, authornamebuf, TEXT_CENTER, TEXT_WHITE);

    ListComponent *options = init_list(gPauseMenu, DIR_VERTICAL, MENU_INPUT_JOYSTICK);
    component_set_pos(options, -20, -20);
    add_pause_menu_option(options, 0, "Continue", pause_menu_continue);
    add_pause_menu_option(options, 1, "Exit Level", pause_menu_exit_course);
    add_pause_menu_option(options, 2, "Options", NULL);
}
