#include "menu_engine.h"

#include "game/ingame_menu.h"
#include "game/game_init.h"
#include "game/segment2.h"
#include "audio/external.h"
#include "main.h"

#include "actors/b/header.h"
#include "actors/bg/header.h"
#include "actors/uibutton/header.h"

AnimatedComponent *gToolbar;

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
    s32 op = 255;//(selected ? 50 : 255);
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

// Copy tile type of current cursor position to current toolbar slot
int sample_block(FrameComponent *button) {
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
                    button->buttonParam = j;
                    // the pain of nested loops
                    button->buttonID = i;
                    return TRUE;
                }
            }
        } else if (buttonInfo->id == targetId) {
            button->buttonParam = targetBparam;
            if (!isObject) mb64_mat_selection = targetBparam;
            button->buttonID = i;
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
    if (ACTIVE) {
        if (do_sample_buffer_check()) {
            if (sample_block(curButton)) {
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
            play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
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
        }
        mb64_param_selection = curButton->buttonParam;
    } else {
        mb64_id_selection = buttonInfo->id;
        // Tiles with materials
        if (mb64_terrain_info_list[mb64_id_selection].terrain) {
            // Tile flipping
            int tileFlippable = (mb64_id_selection < TILE_END_OF_FLIPPABLE) && (mb64_place_mode == MB64_PM_TILE);
            if (tileFlippable) {
                if (ACTIVE && gPlayer1Controller->buttonPressed & U_JPAD) {
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
                play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
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
