#include "menu_engine.h"

#include "main.h"

AnimatedComponent *gToolbar;
int gToolboxIndex = 0;

u8 mb64_toolbar[9];
u8 mb64_toolbar_params[9];
u8 mb64_toolbox[18 * 5];
u8 mb64_toolbox_params[18 * 5];

MenuStyle toolbar_style = {
    .listOffsetSelected = TRUE
};

Gfx *get_button_tex(u32 buttonId, u32 objIndex) {
    struct mb64_ui_button_type *button = &mb64_ui_buttons[buttonId];
    if (button->placeMode != MB64_PM_TILE) {
        u32 id;
        if (button->multiObj) {
            id = button->idList[objIndex];
        } else {
            id = button->id;
        }
        return mb64_object_type_list[id].btn;
    }
    if (buttonId == MB64_BUTTON_BLANK) return mat_b_btn_blank;
    return mb64_terrain_info_list[button->id].button;
}

char *get_button_str(u32 buttonId) {
    struct mb64_ui_button_type *button = &mb64_ui_buttons[buttonId];
    if (button->placeMode != MB64_PM_TILE) {
        if (button->multiObj) {
            return button->name;
        } else {
            u32 id = button->id;
            return mb64_object_type_list[id].name;
        }
    }
    return mb64_terrain_info_list[button->id].name;
}

void render_button(int button, int param, int selected, s16 x, s16 y) {
    s32 op = (selected ? 150 : 255);
    create_dl_translation_matrix(MENU_MTX_PUSH, x, y, 0);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, op, 255);

    Gfx *mat = get_button_tex(button, param);

    gSPDisplayList(gDisplayListHead++, mat);//texture
    gSPDisplayList(gDisplayListHead++, &uibutton_button_mesh);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    gDPSetTextureLUT(gDisplayListHead++, G_TT_NONE);
}

#define buttonID params[0].asBytes[0]
#define buttonParam params[0].asBytes[1]
void component_button_render(MenuComponent *m, s16 x, s16 y) {
    FrameComponent *button = (FrameComponent *)m;
    x += m->xpos;
    y += m->ypos;

    render_button(button->buttonID, button->buttonParam, gMenuState.selected, x, y);
}

void set_toolbar(int index, int id, int param) {
    ListComponent *toolbar = get_first_child(gToolbar);
    FrameComponent *button = get_first_child(component_list_get(toolbar, index));
    button->buttonID = id;
    button->buttonParam = param;
    mb64_toolbar[index] = id;
    mb64_toolbar_params[index] = param;
}

// Copy tile type of current cursor position to current toolbar slot
int sample_block(int index) {
    int isObject = FALSE;
    int targetId;
    int targetBparam;
    // Iterate over objects
    for (int i = 0; i < mb64_object_count; i++) {
        struct mb64_obj *obj = &mb64_object_data[i];
        if ((obj->x == mb64_cursor_pos[0]) && (obj->y == mb64_cursor_pos[1]) && (obj->z == mb64_cursor_pos[2])) {
            isObject = TRUE;
            targetId = obj->type;
            targetBparam = obj->bparam;
            mb64_rot_selection = obj->rot;
            break;
        }
    }
    // Look at tile array
    if (!isObject) {
        struct mb64_grid_obj *tile = get_grid_tile(mb64_cursor_pos);
        if (tile->type == TILE_TYPE_EMPTY) {
            return FALSE;
        }
        targetId = tile->type;
        targetBparam = tile->mat;
        mb64_rot_selection = tile->rot;
        mb64_upsidedown_tile = FALSE;
        if (targetId < TILE_END_OF_FLIPPABLE && targetId & 1) {
            targetId &= ~1;
            mb64_upsidedown_tile = TRUE;
        }
    }

    // Find relevant button
    for (int i = 0; i < MB64_BUTTON_COUNT; i++) {
        struct mb64_ui_button_type *buttonInfo = &mb64_ui_buttons[i];
        if (isObject ^ (buttonInfo->placeMode == MB64_PM_OBJ)) {
            continue;
        }

        if (isObject && buttonInfo->multiObj) {
            // Iterate over multilist
            for (u32 j = 0; j < buttonInfo->paramCount; j++) {
                if (buttonInfo->idList[j] == targetId) {
                    set_toolbar(index, i, j);
                    return TRUE;
                }
            }
        } else if (buttonInfo->id == targetId) {
            if (!isObject) mb64_mat_selection = targetBparam;
            set_toolbar(index, i, targetBparam);
            return TRUE;
        }
    }
    return FALSE;
}

int gLTrigBuff = FALSE;
int gRTrigBuff = FALSE;
int do_sample_buffer_check(void) {
    int doSample = FALSE;
    // 1-frame buffer check for holding both L and R
    // If L and R are pressed within 1 frame of each other,
    // enable bothPressed and disable L and R pressed
    int LPressed = gPlayer1Controller->buttonPressed & L_TRIG;
    int RPressed = gPlayer1Controller->buttonPressed & R_TRIG;
    gPlayer1Controller->buttonPressed &= ~(L_TRIG | R_TRIG);
    int bothPressed = FALSE;

    if ((LPressed && gRTrigBuff) || (RPressed && gLTrigBuff) || (LPressed && RPressed)) {
        bothPressed = TRUE;
        gLTrigBuff = 0;
        gRTrigBuff = 0;
    }

    if (bothPressed && mb64_place_mode != MB64_PM_ACTION) {
        doSample = TRUE;
    }

    if (!bothPressed) {
        gLTrigBuff = LPressed;
        gRTrigBuff = RPressed;
    }
    gPlayer1Controller->buttonPressed |= gLTrigBuff | gRTrigBuff;
    return doSample;
}

void component_toolbar_loop(MenuComponent *m, s16 x, s16 y) {
    ListComponent *toolbar = (ListComponent *)m;

    set_menu_style(toolbar_style);

    create_dl_translation_matrix(MENU_MTX_PUSH, x, y - 65, 0);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
    gSPDisplayList(gDisplayListHead++, &bg_back_graund_mesh);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    FrameComponent *curButton = get_first_child(component_list_get(toolbar, toolbar->index));
    int id = curButton->buttonID;
    struct mb64_ui_button_type *buttonInfo = &mb64_ui_buttons[id];

    x += m->xpos - 140;
    y += m->ypos + 25;
    char *string = get_button_str(id);
    menu_text_display(string, x, y, TEXT_WHITE, TEXT_LEFT, 255);
    x += get_string_width_ascii(string);
    char *yellowStr = NULL;
    mb64_place_mode = buttonInfo->placeMode;

    // Handle updating editor values and switching types with Dpad
    int dir = 0;
    int toolbarActive = ACTIVE && mb64_menu_state == MB64_MAKE_MAIN;
    if (toolbarActive) {
        if (do_sample_buffer_check()) {
            if (sample_block(toolbar->index)) {
                play_sound(SOUND_ACTION_BRUSH_HAIR, gGlobalSoundSource);
            }
        }
        dir = get_input(MENU_INPUT_DPAD, DIR_HORIZONTAL);
    }

    if (mb64_place_mode != MB64_PM_TILE) {
        // Switch parameters with Dpad
        int param = buttonInfo->paramCount;
        if (param != 0 && dir) {
            curButton->buttonParam = (curButton->buttonParam + dir + param) % param;
            mb64_toolbar_params[toolbar->index] = curButton->buttonParam;
            menu_play_move_sound();
        }
        // Set mb64_id_selection and the string to display
        if (buttonInfo->multiObj) {
            mb64_id_selection = buttonInfo->idList[curButton->buttonParam];
            yellowStr = mb64_object_type_list[mb64_id_selection].name;
        } else {
            mb64_id_selection = buttonInfo->id;
            if (buttonInfo->names) {
                yellowStr = buttonInfo->names[curButton->buttonParam];
            }
            mb64_param_selection = curButton->buttonParam;
        }
    } else {
        mb64_id_selection = buttonInfo->id;
        // Tiles with materials
        if (mb64_terrain_info_list[mb64_id_selection].terrain) {
            // Tile flipping
            int tileFlippable = (mb64_id_selection < TILE_END_OF_FLIPPABLE) && (mb64_place_mode == MB64_PM_TILE);
            if (tileFlippable) {
                if (toolbarActive && gPlayer1Controller->buttonPressed & U_JPAD) {
                    play_sound(SOUND_ACTION_SIDE_FLIP_UNK, gGlobalSoundSource);
                    mb64_upsidedown_tile ^= 1;
                }
                if (mb64_upsidedown_tile) {
                    mb64_id_selection = (mb64_id_selection & ~1) | 1;
                    menu_text_display(" (|)", x, y, TEXT_WHITE, TEXT_LEFT, 255);
                } else {
                    menu_text_display(" (^)", x, y, TEXT_WHITE, TEXT_LEFT, 255);
                }
                x += 30;
            } else {
                mb64_upsidedown_tile = FALSE;
            }
            // Material switching
            if (dir) {
                mb64_mat_selection = (mb64_mat_selection + dir + NUM_MATERIALS_PER_THEME) % NUM_MATERIALS_PER_THEME;
                menu_play_move_sound();
            }
            yellowStr = TILE_MATDEF(mb64_mat_selection).name;
        }
    }


    if (yellowStr) {
        x += 15;
        menu_text_display("<", x, y, TEXT_YELLOW, TEXT_LEFT, 255);

        menu_text_display(yellowStr, x + 20, y, TEXT_YELLOW, TEXT_LEFT, 255);
        x += get_string_width_ascii(yellowStr) + 30;

        menu_text_display(">", x, y, TEXT_YELLOW, TEXT_LEFT, 255);
    }
}

void create_toolbar(void) {
    gToolbar = alloc_component(gMenuRoot, MENU_ANIMATED);
    component_set_pos(gToolbar, SCREEN_WIDTH/2, 20);

    ListComponent *list = init_list(gToolbar, DIR_HORIZONTAL, MENU_INPUT_TRIGGERS);
    list->base.prerender = component_toolbar_loop;

    for (int i = 0; i < 9; i++) {
        FrameComponent *button = init_dynamic_component(NULL, component_button_render);
        button->buttonID = mb64_toolbar[i];
        button->buttonParam = mb64_toolbar_params[i];

        component_list_append(list, button, (i - 4) * 32, 0);
    }
}

void toolbar_set_active(int active) {
    ListComponent *l = get_first_child(gToolbar);
    l->base.inactive = !active;
}

void hide_toolbar(void) {
    component_animate_ease_out(gToolbar, -2.f, 10, DIR_VERTICAL);
    toolbar_set_active(FALSE);
}

void show_toolbar(void) {
    component_animate_ease_in(gToolbar, -50.f, 0.4f, DIR_VERTICAL);
}

// This is the button that travels from the toolbox button you click to the toolbar
FrameComponent *sAnimatedButton = NULL;

// reuses buttonID and buttonParam fields
#define targetIndex params[0].asBytes[2]
#define frames params[0].asBytes[3]

void component_animated_button_finish(void) {
    set_toolbar(sAnimatedButton->targetIndex, sAnimatedButton->buttonID, sAnimatedButton->buttonParam);
    dealloc_component(get_id(sAnimatedButton));
    sAnimatedButton = NULL;
}

void component_animated_button_loop(MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    FrameComponent *f = (FrameComponent *)m;
    int targetX = SCREEN_WIDTH/2 + (f->targetIndex - 4) * 32;
    int targetY = 20 + 3;

    f->frames--;
    targetX += (m->xpos - targetX) * (f->frames / 8.f);
    targetY += (m->ypos - targetY) * (f->frames / 8.f);
    render_button(f->buttonID, f->buttonParam, TRUE, targetX, targetY);

    if (!f->frames) {
        component_animated_button_finish();
    }
}

void create_animated_button(s16 x, s16 y, int index, int id, int param) {
    if (sAnimatedButton) component_animated_button_finish();
    sAnimatedButton = init_dynamic_component(gMenuRoot, component_animated_button_loop);
    sAnimatedButton->buttonID = id;
    sAnimatedButton->buttonParam = param;
    sAnimatedButton->base.xpos = x;
    sAnimatedButton->base.ypos = y;
    sAnimatedButton->frames = 9;
    sAnimatedButton->targetIndex = index;
}

AnimatedComponent *gToolbox;

#define TOOLBOX_PAGE_GAP ((9 * 32) + 40)
void toolbox_render_bg(UNUSED MenuComponent *m, s16 x, s16 y) {
    create_dl_translation_matrix(MENU_MTX_PUSH, x, y, 0);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
    gSPDisplayList(gDisplayListHead++, &bg_back_graund_mesh);
    create_dl_translation_matrix(MENU_MTX_NOPUSH, TOOLBOX_PAGE_GAP, 0, 0);
    gSPDisplayList(gDisplayListHead++, &bg_back_graund_mesh);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void close_toolbox(void) {
    dealloc_component(get_id(gToolbox));
    gToolbox = NULL;
    mb64_menu_state = MB64_MAKE_MAIN;

    ListComponent *bar = get_first_child(gToolbar);
    component_list_get(bar, 7)->disabled = FALSE;
    component_list_get(bar, 8)->disabled = FALSE;
}

void toolbox_loop(MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    AnimatedComponent *a = (AnimatedComponent *)m;
    if (!a->timer && ACTIVE && gPlayer1Controller->buttonPressed & (B_BUTTON | START_BUTTON)) {
        component_animate_ease_out(a, 4.f, 12, DIR_VERTICAL);
        a->onFinish = close_toolbox;
        menu_play_click_sound();
    }
}

void toolbox_handle_scroll(MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    AnimatedComponent *a = (AnimatedComponent *)m;
    Selector2DComponent *box = get_first_child(m);

    if (a->timer) return;

    if (gPlayer1Controller->buttonPressed & (L_CBUTTONS | R_CBUTTONS)) {
        if (box->index % 18 >= 9) {
            box->index -= 9;
        } else {
            box->index += 9;
        }
        menu_play_move_sound();
    }

    if (box->index % box->columns >= 9) {
        if (!a->offset) {
            component_animate_linear(a, 0.f, -TOOLBOX_PAGE_GAP, -50.f, DIR_HORIZONTAL);
        }
    } else if (a->offset) {
        component_animate_linear(a, -TOOLBOX_PAGE_GAP, 0.f, 50.f, DIR_HORIZONTAL);
    }
}

static u8 sSelectedRow = 0;
static u8 sSelectedColumn = 0;
static u8 sPrevSelectedRow = 0;
static u8 sPrevSelectedColumn = 0;
static u8 sSelectedTimer = 0;

static s16 sSelectedX = 0;
static s16 sSelectedY = 0;

void toolbox_render_button(Selector2DComponent *s, s16 x, s16 y, u8 column, u8 row, int selected) {
    x += (column - 4) * 32;
    y -= (row - 2) * 32;
    if (column >= 9) x += 40;

    int index = column + row * s->columns;
    if (selected) {
        gToolboxIndex = index;
        sSelectedX = x;
        sSelectedY = y;
        if (mb64_ui_buttons[mb64_toolbox[index]].multiObj) {
            int maxParam = mb64_ui_buttons[mb64_toolbox[index]].paramCount;
            int dir = get_input(MENU_INPUT_DPAD, DIR_HORIZONTAL);
            mb64_toolbox_params[index] = (mb64_toolbox_params[index] + maxParam + dir) % maxParam;
            if (dir) menu_play_move_sound();
        }
    }

    // Recreate list effect of animating the selected button
    if (sPrevSelectedColumn == column && sPrevSelectedRow == row) {
        y += (3 - sSelectedTimer);
    }
    if (sSelectedColumn == column && sSelectedRow == row) {
        sSelectedTimer = MIN(sSelectedTimer + 1, 3);
        y += sSelectedTimer;
    } else if (selected) {
        sSelectedTimer = 0;
        sPrevSelectedColumn = sSelectedColumn;
        sPrevSelectedRow = sSelectedRow;
        sSelectedColumn = column;
        sSelectedRow = row;
    }

    render_button(mb64_toolbox[index], mb64_toolbox_params[index], selected, x, y);
}

void toolbox_select_button(Selector2DComponent *s, u8 column, u8 row) {
    if (mb64_toolbox[s->index] == MB64_BUTTON_BLANK) return;
    play_sound(SOUND_ACTION_BRUSH_HAIR, gGlobalSoundSource);

    ListComponent *toolbar = get_first_child(gToolbar);
    create_animated_button(sSelectedX, sSelectedY + 3, toolbar->index, mb64_toolbox[s->index], mb64_toolbox_params[s->index]);
}

void toolbox_render_text(MenuComponent *m, s16 x, s16 y) {
    FrameComponent *f = (FrameComponent *)m;
    Selector2DComponent *box = get_parent(f);
    if (mb64_toolbox[box->index] == MB64_BUTTON_BLANK) return;

    x = sSelectedX + 18;
    y = sSelectedY - 3;

    // Render name for selected button
    char *buttonName = get_button_str(mb64_toolbox[box->index]);
    struct mb64_ui_button_type *buttonInfo = &mb64_ui_buttons[mb64_toolbox[box->index]];
    u32 isMulti = buttonInfo->multiObj;

    char stringBuf[50];
    if (isMulti) y += 8;
    s16 lowerX = x;

    s32 strLen = get_string_width_ascii(buttonName);
    s32 lowerStrLen = 0;

    if (isMulti) {
        u32 objId = buttonInfo->idList[mb64_toolbox_params[box->index]];
        sprintf(stringBuf, "< %s >", mb64_object_type_list[objId].name);
        lowerStrLen = get_string_width_ascii(stringBuf);
    }

    if ((lowerX + lowerStrLen > SCREEN_WIDTH - 5) || (x + strLen > SCREEN_WIDTH - 5)) {
        lowerX -= lowerStrLen + 40;
        x -= strLen + 40;
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
    gDPSetCombineMode(gDisplayListHead++, G_CC_ENVIRONMENT, G_CC_ENVIRONMENT);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPFillRectangle(gDisplayListHead++, x - 5, SCREEN_HEIGHT - (y + 15), x + 5 + strLen, SCREEN_HEIGHT - (y - 1));
    if (isMulti) {
        gDPFillRectangle(gDisplayListHead++, lowerX - 5, SCREEN_HEIGHT - (y - 1), lowerX + 5 + lowerStrLen, SCREEN_HEIGHT - (y - 17));
        menu_text_display(stringBuf, lowerX, y - 15, TEXT_YELLOW, TEXT_LEFT, 255);
    }
    menu_text_display(buttonName, x, y, TEXT_YELLOW, TEXT_LEFT, 255);
}

void create_toolbox(void) {
    gToolbox = alloc_component(gMenuRoot, MENU_ANIMATED);
    component_set_pos(gToolbox, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 30);
    component_animate_ease_in(gToolbox, 150.f, 0.4f, DIR_VERTICAL);
    gToolbox->base.prerender = toolbox_loop;

    AnimatedComponent *scroller = alloc_component(gToolbox, MENU_ANIMATED);
    scroller->base.prerender = toolbox_handle_scroll;

    Selector2DComponent *box = init_selector_2d_component(scroller, 0, 0, 18, 5, toolbox_render_button, toolbox_select_button);
    box->base.prerender = toolbox_render_bg;

    box->index = gToolboxIndex;
    if (box->index % 18 >= 9) {
        scroller->direction = DIR_HORIZONTAL;
        scroller->offset = -TOOLBOX_PAGE_GAP;
    }

    init_dynamic_component(box, toolbox_render_text);

    ListComponent *bar = get_first_child(gToolbar);
    component_list_get(bar, 7)->disabled = TRUE;
    component_list_get(bar, 8)->disabled = TRUE;
}

void reset_toolbox_state(void) {
    gToolboxIndex = 0;
}
