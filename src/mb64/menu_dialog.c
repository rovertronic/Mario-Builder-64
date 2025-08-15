#include "menu_engine.h"

MenuComponent *curDialog;

#define DIALOG_LINES 5
#define DIALOG_MAXLENGTH 30

char gDialogBuf[DIALOG_LINES][DIALOG_MAXLENGTH + 1];

MenuStyle dialog_menu_style = {
    .textHighlightSelected = FALSE,
    .noClickSounds = TRUE,
    .textNoShadow = TRUE,
};

#define animTimer params[0].asInt
#define goingBack params[1].asInt
void dialog_box_render(MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    FrameComponent *box = (FrameComponent *)m;
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    set_menu_style(dialog_menu_style);

    if (box->goingBack && box->animTimer < 8) {
        box->animTimer++;
        if (box->animTimer == 8) {
            dealloc_component(get_id(curDialog));
            curDialog = NULL;
        }
    } else {
        if (gPlayer1Controller->buttonPressed & (A_BUTTON | B_BUTTON)) {
            begin_dialog_close();
        }
    }
    if (box->animTimer > 0) {
        if (!box->goingBack) box->animTimer--;
        gMenuState.inactive = TRUE;
    }
}

void dialog_box_set_transform(MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    MatrixComponent *mtx = (MatrixComponent *)m;
    FrameComponent *box = get_child(m);
    int timer = box->animTimer;
    mtx->rot = (timer * 0x10000) / 8;
    mtx->xScale = mtx->yScale = 1.f / (timer*2 + 1);
}

void parse_dialog(char *dialog) {
    int index = 0;
    int line = 0;
    while (*dialog && line < DIALOG_LINES) {
        if (*dialog == '\n') {
            gDialogBuf[line][index] = 0;
            line++;
            index = 0;
        } else if (index < DIALOG_MAXLENGTH) {
            gDialogBuf[line][index++] = *dialog;
        }
        dialog++;
    }
}

void (*gResponseFunc)(int);
void begin_dialog_close(void) {
    FrameComponent *box = get_child(curDialog);
    box->goingBack = TRUE;
    play_sound(SOUND_MENU_MESSAGE_DISAPPEAR, gGlobalSoundSource);
}

void create_dialog_box(char *dialog) {
    curDialog = init_matrix_component(gMenuRoot, 0, 0.f, 0.f);
    component_set_pos(curDialog, 70, 200);
    curDialog->prerender = dialog_box_set_transform;
    FrameComponent *handler = init_dynamic_component(curDialog, dialog_box_render);
    component_set_pos(handler, -7, 5);
    handler->animTimer = 8;
    gResponseFunc = NULL;

    parse_dialog(dialog);
    for (int line = 0; line < DIALOG_LINES; line++) {
        if (gDialogBuf[line][0]) {
            init_text_component(handler, 15, -25-line*16, gDialogBuf[line], TEXT_LEFT, TEXT_WHITE);
        }
    }

    play_sound(SOUND_MENU_MESSAGE_APPEAR, gGlobalSoundSource);
}

void dialog_response(TextComponent *b) {
    gResponseFunc(b->onClickArg);
    begin_dialog_close();
}

void create_dialog_box_with_response(char *dialog, void (*response)(int)) {
    create_dialog_box(dialog);
    FrameComponent *handler = get_child(curDialog);
    ListComponent *list = init_list(handler, DIR_HORIZONTAL, MENU_INPUT_JOYSTICK);
    component_set_pos(list, 50, -25-4*16);

    gResponseFunc = response;
    TextComponent *yes = init_text_button(NULL, 0, 0, "Yes", TEXT_LEFT, dialog_response, 1);
    TextComponent *no = init_text_button(NULL, 0, 0, "No", TEXT_LEFT, dialog_response, 0);
    yes->base.prerender = listitem_render_triangle;
    no->base.prerender = listitem_render_triangle;
    component_list_append(list, yes, 0, 0);
    component_list_append(list, no, 80, 0);
}
