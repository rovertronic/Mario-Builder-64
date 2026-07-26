#include "dialog.h"
#include "pause.h"

MatrixComponent *gCurDialog;
int gDialogResponse; // 0 for none, 1 for yes, 2 for closed

// Default dialog
#define DIALOG_LINES 5
#define DIALOG_MAXLENGTH 30
#define DIALOG_SIZE (DIALOG_LINES * (DIALOG_MAXLENGTH + 1))

// Badge collection dialog
#define DIALOG_BADGE_LINES 2
#define DIALOG_BADGE_MAXLENGTH (DIALOG_SIZE / DIALOG_BADGE_LINES) - 1

union {
    char normal[DIALOG_LINES][DIALOG_MAXLENGTH + 1];
    char badge[DIALOG_BADGE_LINES][DIALOG_BADGE_MAXLENGTH + 1];
} dialog_text_buffer;

#define gDialogBuf dialog_text_buffer.normal
#define gDialogBadgeBuf dialog_text_buffer.badge

MenuStyle dialog_menu_style = {
    .textHighlightSelected = FALSE,
    .noClickSounds = TRUE,
    .textNoShadow = TRUE,
};

void destroy_dialog_component(void) {
    if (gCurDialog) {
        dealloc_component(get_id(gCurDialog));
        gCurDialog = NULL;
    }
}

#define animTimer params[0].asInt
#define goingBack params[1].asInt
void begin_dialog_close(void) {
    FrameComponent *box = get_child(gCurDialog);
    box->goingBack = TRUE;
    play_sound(SOUND_MENU_MESSAGE_DISAPPEAR, gGlobalSoundSource);
}

void dialog_box_render(MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    FrameComponent *box = (FrameComponent *)m;
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    set_menu_style(dialog_menu_style);

    if (box->goingBack && box->animTimer < 8) {
        box->animTimer++;
        if (box->animTimer == 8) {
            destroy_dialog_component();
        }
    } else {
        if (gPlayer1Controller->buttonPressed & (A_BUTTON | B_BUTTON)) {
            gDialogResponse = 1;
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
    while (line < DIALOG_LINES) {
        if (!(*dialog) || *dialog == '\n') {
            gDialogBuf[line][index] = 0;
            line++;
            index = 0;
            if (*dialog) dialog++;
        } else if (index < DIALOG_MAXLENGTH) {
            gDialogBuf[line][index++] = *dialog;
            dialog++;
        }
    }
}

void (*gResponseFunc)(int);

void create_dialog_box(char *dialog) {
    destroy_dialog_component();
    gCurDialog = init_matrix_component(gMenuRoot, 0, 0.f, 0.f);
    component_set_pos(gCurDialog, 70, 200);
    gCurDialog->base.prerender = dialog_box_set_transform;
    FrameComponent *handler = init_dynamic_component(gCurDialog, dialog_box_render);
    component_set_pos(handler, -7, 5);
    handler->animTimer = 8;
    gResponseFunc = NULL;
    gDialogResponse = 0;

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
    gDialogResponse = 2 - b->onClickArg; // yes -> 1, no -> 2
    begin_dialog_close();
}

void create_dialog_box_with_response(char *dialog, void (*response)(int)) {
    create_dialog_box(dialog);
    FrameComponent *handler = get_child(gCurDialog);
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


// BTCM badge get dialog

MenuStyle badge_dialog_menu_style = {
    .noClickSounds = TRUE,
};

void badge_dialog_text_set_alpha(MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    set_menu_style(badge_dialog_menu_style);
    TextComponent *t = (TextComponent *)m;
    RectComponent *rect = get_parent(m);
    t->alpha = (rect->curAlpha / 150.f) * 255.f;
}

void begin_badge_dialog_close(void) {
    if (!gCurDialog) return;
    component_rect_do_fade(get_child(gCurDialog), 0, 20, destroy_dialog_component);
}

void create_badge_dialog(int badgeid) {
    destroy_dialog_component();
    gCurDialog = init_matrix_component(gMenuRoot, 0, 1.f, 1.f); // empty
    RectComponent *rect = init_rect_component(gCurDialog, 0, SCREEN_WIDTH/2, 30, SCREEN_WIDTH/2, 30);
    component_rect_do_fade(rect, 150, 20, NULL);
    sprintf(gDialogBadgeBuf[0], "You got the %s!", badge_info[badgeid].name);
    sprintf(gDialogBadgeBuf[1], "%s.", badge_info[badgeid].desc);

    for (int line = 0; line < DIALOG_BADGE_LINES; line++) {
        if (gDialogBadgeBuf[line][0]) {
            TextComponent *t = init_text_component(rect, -150, 10-line*16, gDialogBadgeBuf[line], TEXT_LEFT, TEXT_WHITE);
            t->base.prerender = badge_dialog_text_set_alpha;
        }
    }
}
