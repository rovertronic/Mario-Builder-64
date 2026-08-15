#include "toolbox.h"
#include "misc.h"

#include "mb64/editor/main.h"
#include "mb64/editor/object.h"
#include "mb64/gfx/tile.h"

#include "mb64/gfx/mb64_buttons.h"
#include "game/memory.h"

AnimatedComponent *gToolbar;
static AnimatedComponent *sToolbox;
static int sToolboxIndex;
static u8 sFolderIndices[MB64_FOLDER_COUNT];

u8 mb64_toolbar[MB64_TOOLBAR_SIZE];
u8 mb64_toolbar_params[MB64_TOOLBAR_SIZE];

static MenuStyle sToolboxStyle;

// screen pos of the focused toolbox button for flyout and tooltip
static s16 sCursorX;
static s16 sCursorY;

// reuse framecomponent params for toolbar and flyout buttons
#define buttonID params[0].asBytes[0]
#define buttonParam params[0].asBytes[1]
#define targetIndex params[0].asBytes[2]
#define frames params[0].asBytes[3]

#define BTN_TILE 32
#define TAB_HEIGHT 16
#define TAB_MARGIN 10
#define FOLDER_BOX_PAD 7
#define TOOLBOX_BOX_PAD 8
#define BOX_CORNER 10
#define TOOLTIP_CORNER 6
#define TOOLTIP_ALPHA 180
#define TOOLBAR_Y 20
#define TOOLBAR_HALF_W (MB64_TOOLBAR_SIZE * (BTN_TILE / 2) + TOOLBOX_BOX_PAD)
#define TOOLBAR_HALF_H (BTN_TILE / 2 + TOOLBOX_BOX_PAD)
#define OUTLINE_WIDTH 1

static void get_toolbox_cell_pos(int index, s16 *x, s16 *y) {
    int col = index % MB64_TOOLBOX_COLUMNS;
    int row = index / MB64_TOOLBOX_COLUMNS;
    *x = (col - MB64_TOOLBOX_COLUMNS / 2) * BTN_TILE;
    *y = (MB64_TOOLBOX_ROWS - 1 - 2 * row) * (BTN_TILE / 2);
}

static void render_outline_box(s16 x, s16 y, s16 width, s16 height) {
    s32 left = x - width - OUTLINE_WIDTH;
    s32 right = x + width;
    s32 screenTop = SCREEN_HEIGHT - (y + height + OUTLINE_WIDTH);
    s32 screenBottom = SCREEN_HEIGHT - (y - height);

    gDPPipeSync(gDisplayListHead++);
    gDPSetCombineMode(gDisplayListHead++, G_CC_ENVIRONMENT, G_CC_ENVIRONMENT);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetEnvColor(gDisplayListHead++, 120, 120, 120, 255);

    gDPFillRectangle(gDisplayListHead++, left, screenTop, right + OUTLINE_WIDTH, screenTop + OUTLINE_WIDTH);
    gDPFillRectangle(gDisplayListHead++, left, screenBottom, right + OUTLINE_WIDTH, screenBottom + OUTLINE_WIDTH);

    gDPFillRectangle(gDisplayListHead++, left, screenTop + OUTLINE_WIDTH, left + OUTLINE_WIDTH, screenBottom);
    gDPFillRectangle(gDisplayListHead++, right, screenTop + OUTLINE_WIDTH, right + OUTLINE_WIDTH, screenBottom);
}

// tab sitting on a panel top edge (flat bottom against the rounded rect).
// edgeX is the left, right, or center of the tab per align (TEXT_LEFT/RIGHT/CENTER).
// returns the right edge of the drawn tab.
static s16 render_title_tab(s16 edgeX, s16 y, int align, char *name, int color) {
    s16 halfW = get_string_width_ascii(name) / 2 + TOOLTIP_CORNER;
    s16 x = edgeX;

    if (align == TEXT_LEFT) {
        x = edgeX + halfW;
    } else if (align == TEXT_RIGHT) {
        x = edgeX - halfW;
    }

    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, TOOLTIP_ALPHA);
    render_4slice_box_top(x, y, halfW, TAB_HEIGHT, TOOLTIP_CORNER);
    menu_text_display(name, x, y, color, TEXT_CENTER, 255);
    return x + halfW;
}

static const struct ci_texture_define *get_button_tex(int buttonId, int optIndex) {
    struct mb64_ui_button_type *button = &mb64_ui_buttons[buttonId];
    if (button->placeMode == MB64_PM_NONE) {
        return button->folder.icon;
    }
    if (button->count > 0) {
        const struct mb64_ui_param *param = &button->leaf.params[optIndex];
        if (param->btn) return param->btn;
    }
    if (button->placeMode != MB64_PM_TILE) {
        return mb64_object_type_list[button->leaf.id].btn;
    }
    if (buttonId == MB64_BUTTON_BLANK) return &mb64_btn_blank;
    return mb64_terrain_info_list[button->leaf.id].button;
}

static char *get_button_str(int buttonId) {
    struct mb64_ui_button_type *button = &mb64_ui_buttons[buttonId];
    if (button->placeMode == MB64_PM_NONE) {
        return (char *)button->folder.label;
    }
    if (button->placeMode != MB64_PM_TILE) {
        return mb64_object_type_list[button->leaf.id].name;
    }
    return mb64_terrain_info_list[button->leaf.id].name;
}

// menu y is bottom-up; texrects use top-down screen coords. buttons are 32x32 centered on (x, y).
static void mb64_btn_draw_texrect(s16 x, s16 y) {
    s32 xl = (x - BTN_TILE / 2) << 2;
    s32 yl = (SCREEN_HEIGHT - y - BTN_TILE / 2) << 2;
    s32 xh = (x + BTN_TILE / 2) << 2;
    s32 yh = (SCREEN_HEIGHT - y + BTN_TILE / 2) << 2;

    gSPTextureRectangle(gDisplayListHead++, xl, yl, xh, yh, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
}

static void mb64_render_button_tex(const struct ci_texture_define *tex, s16 x, s16 y) {
    const struct ci_texture_define *t = segmented_to_virtual(tex);

    gDPLoadTLUT(gDisplayListHead++, t->palCount + 1, 256, t->pal);
    if (CI_TEXTURE_IS_CI4(t)) {
        gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_CI, G_IM_SIZ_16b, 1, t->tex);
        gSPDisplayList(gDisplayListHead++, mb64_btn_dl_ci4);
    } else {
        gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 1, t->tex);
        gSPDisplayList(gDisplayListHead++, mb64_btn_dl_ci8);
    }
    mb64_btn_draw_texrect(x, y);
}

static void render_button(int buttonId, int param, s16 x, s16 y) {
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    mb64_render_button_tex(get_button_tex(buttonId, param), x, y);
}

static void render_button_outline(s16 x, s16 y) {
    f32 blink = (sins(gGlobalTimer * 0xC00) + 1) / 2.f;
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 255, 200 + 20 * blink, 80 * blink, 255);
    gSPDisplayList(gDisplayListHead++, mb64_btn_dl_ia4);
    mb64_btn_draw_texrect(x, y);
    gSPDisplayList(gDisplayListHead++, mb64_btn_dl_begin);
}

static void selection_cursor_target(void *src, s16 *x, s16 *y) {
    MenuComponent *p = src;

    if (p->type == MENU_LIST) {
        ListComponent *list = src;
        ListItemComponent *item = component_list_get(list, list->index);
        MenuComponent *box = get_parent(list);

        *x = item->base.xpos;
        *y = item->base.ypos;
        // folder list is in panel space; toolbox overlay lives in toolbox space
        if (box->type == MENU_BOX) {
            *x += box->xpos;
            *y += box->ypos;
        }
    } else {
        get_toolbox_cell_pos(((Selector2DComponent *)src)->index, x, y);
    }
}

// params[0] start, params[1] dest, params[2] timer/duration
static void selection_cursor_move(MenuComponent *m, MenuComponent *src, s16 x, s16 y) {
    FrameComponent *f = (FrameComponent *)m;
    s16 *start = f->params[0].asShorts;
    s16 *dest = f->params[1].asShorts;
    u8 *timer = &f->params[2].asBytes[0];
    u8 *duration = &f->params[2].asBytes[1];
    s16 targetX, targetY;

    if (src->inactive) return;

    selection_cursor_target(src, &targetX, &targetY);
    if (targetX != dest[0] || targetY != dest[1]) {
        int dx = targetX - m->xpos;
        int dy = targetY - m->ypos;
        int dist = sqrtf(dx * dx + dy * dy);
        start[0] = m->xpos;
        start[1] = m->ypos;
        dest[0] = targetX;
        dest[1] = targetY;
        *duration = dist / 50 + 2;
        *timer = 1;
    } else if (*timer < *duration) {
        (*timer)++;
    }

    if (*timer >= *duration) {
        m->xpos = dest[0];
        m->ypos = dest[1];
    } else {
        m->xpos = start[0] + (dest[0] - start[0]) * *timer / *duration;
        m->ypos = start[1] + (dest[1] - start[1]) * *timer / *duration;
    }
    render_button_outline(x + m->xpos, y + m->ypos);
}

static void selection_cursor_render(MenuComponent *m, s16 x, s16 y) {
    selection_cursor_move(m, get_parent(m), x, y);
}

static void component_button_render(MenuComponent *m, s16 x, s16 y) {
    FrameComponent *button = (FrameComponent *)m;
    x += m->xpos;
    y += m->ypos;
    render_button(button->buttonID, button->buttonParam, x, y);
}

static void set_toolbar(int index, int id, int param) {
    ListComponent *toolbar = get_child(gToolbar);
    FrameComponent *button = get_child(component_list_get(toolbar, index));
    button->buttonID = id;
    button->buttonParam = param;
    mb64_toolbar[index] = id;
    mb64_toolbar_params[index] = param;
}

static void set_toolbar_utility_disabled(int disabled) {
    ListComponent *bar = get_child(gToolbar);
    component_list_get(bar, MB64_TOOLBAR_SIZE - 2)->disabled = disabled;
    component_list_get(bar, MB64_TOOLBAR_SIZE - 1)->disabled = disabled;
}

static int leaf_uses_material(int buttonId) {
    struct mb64_ui_button_type *button = &mb64_ui_buttons[buttonId];
    return button->placeMode == MB64_PM_TILE
        && mb64_terrain_info_list[button->leaf.id].terrain != NULL;
}

static int collect_folder_children(int folderId, u8 *outIds) {
    struct mb64_ui_button_type *folder = &mb64_ui_buttons[folderId];
    int mask = 1 << mb64_lopt_game;
    int count = 0;

    for (int i = 0; i < folder->count && count < MB64_FOLDER_MAX_CHILDREN; i++) {
        const struct mb64_folder_child *child = &folder->folder.children[i];
        if (child->gameMask & mask) {
            outIds[count++] = child->buttonId;
        }
    }
    return count;
}

static u8 *get_toolbox_layout(void) {
    return (mb64_lopt_game == MB64_GAME_BTCM)
        ? mb64_toolbox_layout_btcm
        : mb64_toolbox_layout_vanilla;
}

// dpad cycles siblings only if no child uses dpad for params or materials
static int get_sibling_cycle(int leafId, u8 *outIds, int *outCount, int *outCur) {
    u8 *layout = get_toolbox_layout();

    for (int i = 0; i < MB64_TOOLBOX_SIZE; i++) {
        if (layout[i] < MB64_LEAF_COUNT) continue;

        int count = collect_folder_children(layout[i], outIds);
        int cur = -1;
        int blocked = count < 2;
        for (int j = 0; j < count; j++) {
            int id = outIds[j];
            if (id == leafId) cur = j;
            if (mb64_ui_buttons[id].count > 0 || leaf_uses_material(id)) blocked = TRUE;
        }
        if (cur < 0) continue;
        if (blocked) return FALSE;

        *outCount = count;
        *outCur = cur;
        return TRUE;
    }
    return FALSE;
}

// copy the tile or object under the cursor into a toolbar slot
static int sample_block(int index) {
    int isObject = FALSE;
    u32 targetId;
    u32 targetBparam;

    for (int i = 0; i < mb64_object_count; i++) {
        struct mb64_obj *obj = &mb64_object_data[i];
        if (obj->x != mb64_cursor_pos[0] || obj->y != mb64_cursor_pos[1] || obj->z != mb64_cursor_pos[2]) continue;
        isObject = TRUE;
        targetId = obj->type;
        targetBparam = obj->bparam;
        mb64_rot_selection = obj->rot;
        break;
    }

    if (!isObject) {
        struct mb64_grid_obj *tile = get_grid_tile(mb64_cursor_pos);
        if (tile->type == TILE_TYPE_EMPTY) return FALSE;
        targetId = tile->type;
        targetBparam = tile->mat;
        mb64_rot_selection = tile->rot;
        mb64_upsidedown_tile = (targetId < TILE_END_OF_FLIPPABLE) && (targetId & 1);
        if (mb64_upsidedown_tile) targetId &= ~1;
    }

    for (int i = 0; i < MB64_LEAF_COUNT; i++) {
        struct mb64_ui_button_type *button = &mb64_ui_buttons[i];
        if (isObject ^ (button->placeMode == MB64_PM_OBJ)) continue;
        // Bugfix: Prevent sample from sampling the BTCM ! box when in vanilla (they share an object ID)
        if (i == MB64_BUTTON_EXCLA && mb64_lopt_game != MB64_GAME_BTCM) continue;
        if (i == MB64_BUTTON_VEXCLA && mb64_lopt_game != MB64_GAME_VANILLA) continue;
        if (button->leaf.id != targetId) continue;

        int param = 0;
        if (button->count > 0) {
            for (int j = 0; j < button->count; j++) {
                if (button->leaf.params[j].bparam == targetBparam) {
                    param = j;
                    break;
                }
            }
        } else if (!isObject) {
            mb64_mat_selection = targetBparam;
        }
        set_toolbar(index, i, param);
        return TRUE;
    }
    return FALSE;
}

static int sLTrigBuff;
static int sRTrigBuff;

// 1-frame buffer: L and R pressed within one frame of each other is sample,
// and the leftover single trigger is eaten
static int do_sample_buffer_check(void) {
    int l = gPlayer1Controller->buttonPressed & L_TRIG;
    int r = gPlayer1Controller->buttonPressed & R_TRIG;
    int both = (l && sRTrigBuff) || (r && sLTrigBuff) || (l && r);

    gPlayer1Controller->buttonPressed &= ~(L_TRIG | R_TRIG);
    sLTrigBuff = both ? 0 : l;
    sRTrigBuff = both ? 0 : r;
    gPlayer1Controller->buttonPressed |= sLTrigBuff | sRTrigBuff;
    return both;
}

static void component_toolbar_loop(MenuComponent *m, s16 x, s16 y) {
    ListComponent *toolbar = (ListComponent *)m;
    FrameComponent *curButton = get_child(component_list_get(toolbar, toolbar->index));
    int id = curButton->buttonID;
    int toolbarActive = ACTIVE && mb64_menu_state == MB64_MAKE_MAIN;
    int dir = 0;
    struct mb64_ui_button_type *buttonInfo;

    set_menu_style(sToolboxStyle);

    gSPDisplayList(gDisplayListHead++, &dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, TOOLTIP_ALPHA);
    render_4slice_box_top(x, y - TOOLBAR_HALF_H, TOOLBAR_HALF_W, TOOLBAR_HALF_H * 2, BOX_CORNER);
    render_outline_box(x + m->xpos, y + m->ypos, MB64_TOOLBAR_SIZE * (BTN_TILE / 2), BTN_TILE / 2);

    if (toolbarActive) {
        if (do_sample_buffer_check() && mb64_place_mode != MB64_PM_ACTION && sample_block(toolbar->index)) {
            play_sound(SOUND_ACTION_BRUSH_HAIR, gGlobalSoundSource);
        }
        dir = get_input(MENU_INPUT_DPAD, DIR_HORIZONTAL);
    }

    if (dir) {
        u8 siblingIds[MB64_FOLDER_MAX_CHILDREN];
        int siblingCount, siblingCur;

        if (get_sibling_cycle(id, siblingIds, &siblingCount, &siblingCur)) {
            set_toolbar(toolbar->index, siblingIds[(siblingCur + siblingCount + dir) % siblingCount], 0);
            id = curButton->buttonID;
            menu_play_move_sound();
        } else if (mb64_ui_buttons[id].count > 0) {
            int count = mb64_ui_buttons[id].count;
            set_toolbar(toolbar->index, id, (curButton->buttonParam + dir + count) % count);
            menu_play_move_sound();
        } else if (leaf_uses_material(id)) {
            mb64_mat_selection = (mb64_mat_selection + dir + NUM_MATERIALS_PER_THEME) % NUM_MATERIALS_PER_THEME;
            menu_play_move_sound();
        }
    }

    buttonInfo = &mb64_ui_buttons[id];
    mb64_place_mode = buttonInfo->placeMode;
    mb64_id_selection = buttonInfo->leaf.id;
    mb64_param_selection = (buttonInfo->placeMode != MB64_PM_TILE && buttonInfo->count > 0)
        ? buttonInfo->leaf.params[curButton->buttonParam].bparam
        : 0;

    if (leaf_uses_material(id)) {
        if (mb64_id_selection < TILE_END_OF_FLIPPABLE) {
            if (toolbarActive && gPlayer1Controller->buttonPressed & U_JPAD) {
                play_sound(SOUND_ACTION_SIDE_FLIP_UNK, gGlobalSoundSource);
                mb64_upsidedown_tile ^= 1;
            }
            if (mb64_upsidedown_tile) {
                mb64_id_selection = (mb64_id_selection & ~1) | 1;
            }
        } else {
            mb64_upsidedown_tile = FALSE;
        }
    }

    gSPDisplayList(gDisplayListHead++, mb64_btn_dl_begin);
}

// after the selector so tabs sit over the outline
static void toolbar_render_tabs(s16 x, s16 y) {
    ListComponent *toolbar = get_child(gToolbar);
    FrameComponent *curButton = get_child(component_list_get(toolbar, toolbar->index));
    int id = curButton->buttonID;
    struct mb64_ui_button_type *buttonInfo = &mb64_ui_buttons[id];
    u8 siblingIds[MB64_FOLDER_MAX_CHILDREN];
    int siblingCount, siblingCur;
    int canCycleSiblings = get_sibling_cycle(id, siblingIds, &siblingCount, &siblingCur);
    char nameBuf[64];
    char cycleBuf[64];
    char *nameStr = get_button_str(id);
    char *yellowStr = NULL;
    s16 tabY = y + TOOLBAR_HALF_H;
    s16 nameLeft = x - TOOLBAR_HALF_W + TAB_MARGIN;
    s16 nameRight;

    if (leaf_uses_material(id)) {
        if (buttonInfo->leaf.id < TILE_END_OF_FLIPPABLE) {
            sprintf(nameBuf, mb64_upsidedown_tile ? "%s (|)" : "%s (^)", nameStr);
            nameStr = nameBuf;
        }
        yellowStr = TILE_MATDEF(mb64_mat_selection).name;
    } else if (buttonInfo->count > 0) {
        yellowStr = (char *)buttonInfo->leaf.params[curButton->buttonParam].name;
    }

    if (canCycleSiblings) {
        sprintf(cycleBuf, "   %s   ", nameStr);
        nameStr = cycleBuf;
    }

    nameRight = render_title_tab(nameLeft, tabY, TEXT_LEFT, nameStr, TEXT_WHITE);
    if (canCycleSiblings) {
        s16 textLeft = nameLeft + TOOLTIP_CORNER;
        menu_text_display("<", textLeft, tabY, TEXT_YELLOW, TEXT_LEFT, 255);
        menu_text_display(">", textLeft + get_string_width_ascii(nameStr), tabY, TEXT_YELLOW, TEXT_RIGHT, 255);
    }

    if (yellowStr) {
        sprintf(nameBuf, "< %s >", yellowStr);
        render_title_tab(nameRight + 8, tabY, TEXT_LEFT, nameBuf, TEXT_YELLOW);
    }
}

static void component_toolbar_btn_end(UNUSED MenuComponent *m, s16 x, s16 y) {
    gSPDisplayList(gDisplayListHead++, mb64_btn_dl_end);
    toolbar_render_tabs(x, y);
}

void create_toolbar(void) {
    s16 x, y;
    FrameComponent *cursor;

    gToolbar = alloc_component(gMenuRoot, MENU_ANIMATED);
    component_set_pos(gToolbar, SCREEN_WIDTH/2, TOOLBAR_Y);

    ListComponent *list = init_list(gToolbar, DIR_HORIZONTAL, MENU_INPUT_TRIGGERS);
    list->base.prerender = component_toolbar_loop;

    for (int i = 0; i < MB64_TOOLBAR_SIZE; i++) {
        FrameComponent *button = init_dynamic_component(NULL, component_button_render);
        button->buttonID = mb64_toolbar[i];
        button->buttonParam = mb64_toolbar_params[i];
        component_list_append(list, button, (i - MB64_TOOLBAR_SIZE / 2) * BTN_TILE, 0);
    }

    cursor = init_dynamic_component(list, selection_cursor_render);
    selection_cursor_target(list, &x, &y);
    component_set_pos(cursor, x, y);

    init_dynamic_component(gToolbar, component_toolbar_btn_end);
}

void toolbar_set_active(int active) {
    ListComponent *l = get_child(gToolbar);
    l->base.inactive = !active;
}

void hide_toolbar(void) {
    component_animate_ease_out(gToolbar, -2.f, 10, DIR_VERTICAL);
    toolbar_set_active(FALSE);
}

void show_toolbar(void) {
    component_animate_ease_in(gToolbar, -50.f, 0.4f, DIR_VERTICAL);
}

// this is the button that travels from the toolbox button you click to the toolbar
static FrameComponent *sAnimatedButton;

static void component_animated_button_finish(void) {
    set_toolbar(sAnimatedButton->targetIndex, sAnimatedButton->buttonID, sAnimatedButton->buttonParam);
    dealloc_component(get_id(sAnimatedButton));
    sAnimatedButton = NULL;
}

static void component_animated_button_loop(MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    FrameComponent *f = (FrameComponent *)m;
    int targetX = SCREEN_WIDTH/2 + (f->targetIndex - MB64_TOOLBAR_SIZE / 2) * BTN_TILE;
    int targetY = TOOLBAR_Y + 3;

    f->frames--;
    targetX += (m->xpos - targetX) * (f->frames / 8.f);
    targetY += (m->ypos - targetY) * (f->frames / 8.f);
    gSPDisplayList(gDisplayListHead++, mb64_btn_dl_begin);
    render_button(f->buttonID, f->buttonParam, targetX, targetY);
    render_button_outline(targetX, targetY);
    gSPDisplayList(gDisplayListHead++, mb64_btn_dl_end);

    if (!f->frames) {
        component_animated_button_finish();
    }
}

static void create_animated_button(s16 x, s16 y, int index, int id) {
    if (sAnimatedButton) component_animated_button_finish();
    sAnimatedButton = init_dynamic_component(gMenuRoot, component_animated_button_loop);
    sAnimatedButton->buttonID = id;
    component_set_pos(sAnimatedButton, x, y);
    sAnimatedButton->frames = 9;
    sAnimatedButton->targetIndex = index;
}

static void assign_to_toolbar(int buttonId) {
    play_sound(SOUND_ACTION_BRUSH_HAIR, gGlobalSoundSource);
    ListComponent *toolbar = get_child(gToolbar);
    create_animated_button(sCursorX, sCursorY + 3, toolbar->index, buttonId);
}

static void toolbox_begin_buttons(MenuComponent *m, s16 x, s16 y) {
    s16 cx = x + m->xpos;
    s16 cy = y + m->ypos;
    s16 halfW, halfH;

    if (m->type == MENU_SELECTOR_2D) {
        halfW = MB64_TOOLBOX_COLUMNS * (BTN_TILE / 2);
        halfH = MB64_TOOLBOX_ROWS * (BTN_TILE / 2);
    } else {
        halfW = ((ListComponent *)m)->count * (BTN_TILE / 2);
        halfH = BTN_TILE / 2;
    }
    render_outline_box(cx, cy, halfW, halfH);
    gSPDisplayList(gDisplayListHead++, mb64_btn_dl_begin);
}

// grid and folder live in the bg box; overlay is a later sibling so it draws over both
static BoxComponent *get_toolbox_bg(void) {
    return get_child(sToolbox);
}

static BoxComponent *get_folder_panel(void) {
    return get_child_of_type(get_toolbox_bg(), MENU_BOX, 0);
}

static Selector2DComponent *get_toolbox_grid(void) {
    return get_child(get_toolbox_bg());
}

static void save_open_folder_index(void) {
    BoxComponent *panel = get_folder_panel();
    if (panel) {
        sFolderIndices[get_toolbox_layout()[get_toolbox_grid()->index] - MB64_LEAF_COUNT] =
            ((ListComponent *)get_child(panel))->index;
    }
}

static void toolbox_render_tooltip(int buttonId) {
    char *buttonName;
    s16 halfW;
    s16 halfH = 8;
    s16 x, y;

    if (buttonId == MB64_BUTTON_BLANK) return;

    buttonName = get_button_str(buttonId);
    halfW = get_string_width_ascii(buttonName) / 2 + TOOLTIP_CORNER;
    x = sCursorX;
    y = sCursorY - BTN_TILE / 2 - halfH + 2;

    // keep tooltip clear of the screen edges
    if (x - halfW < 8) {
        x = halfW + 8;
    } else if (x + halfW > SCREEN_WIDTH - 8) {
        x = SCREEN_WIDTH - 8 - halfW;
    }

    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, TOOLTIP_ALPHA);
    render_4slice_box(x, y, halfW, halfH, TOOLTIP_CORNER);
    menu_text_display(
        buttonName, x, y - 7,
        mb64_ui_buttons[buttonId].placeMode == MB64_PM_NONE ? TEXT_YELLOW : TEXT_WHITE,
        TEXT_CENTER, 255
    );
}

// last child of sToolbox: selector over folder/grid, tooltip over selector
static void toolbox_overlay_render(MenuComponent *m, s16 x, s16 y) {
    BoxComponent *panel = get_folder_panel();
    MenuComponent *src;
    int buttonId;

    if (panel) {
        ListComponent *list = get_child(panel);
        FrameComponent *btn = get_child(component_list_get(list, list->index));
        src = (MenuComponent *)list;
        buttonId = btn->buttonID;
    } else {
        Selector2DComponent *grid = get_toolbox_grid();
        src = (MenuComponent *)grid;
        buttonId = get_toolbox_layout()[grid->index];
    }

    selection_cursor_move(m, src, x, y);
    gSPDisplayList(gDisplayListHead++, mb64_btn_dl_end);
    toolbox_render_tooltip(buttonId);
}

// first child sits 1/2 tile left of the folder, then clamp to the grid edges
static s16 folder_row_first_x(s16 folderX, int count) {
    s16 left = -(MB64_TOOLBOX_COLUMNS / 2) * BTN_TILE;
    s16 right = (MB64_TOOLBOX_COLUMNS / 2) * BTN_TILE;
    s16 first = folderX - BTN_TILE / 2;
    s16 last = first + (count - 1) * BTN_TILE;

    if (last > right) {
        first -= last - right;
    }
    if (first < left) {
        first = left;
    }
    return first;
}

static void collapse_folder(void) {
    save_open_folder_index();
    dealloc_component(get_id(get_folder_panel()));
    get_toolbox_grid()->base.inactive = FALSE;
}

static void folder_button_render(MenuComponent *m, s16 x, s16 y) {
    FrameComponent *button = (FrameComponent *)m;
    x += m->xpos;
    y += m->ypos;

    if (SELECTED) {
        sCursorX = x;
        sCursorY = y;
        if (gPlayer1Controller->buttonPressed & A_BUTTON) {
            assign_to_toolbar(button->buttonID);
        }
    }
    render_button(button->buttonID, 0, x, y);
}

// title tab - half-slice on the panel top when it fits right-aligned, else centered full box
static void folder_tab_render(MenuComponent *m, s16 x, s16 y) {
    FrameComponent *tab = (FrameComponent *)m;
    BoxComponent *panel = get_parent(m);
    char *name = tab->params[0].asPtr;
    s16 halfW = get_string_width_ascii(name) / 2 + TOOLTIP_CORNER;

    x += m->xpos;
    y += m->ypos;

    if (halfW <= panel->width - TAB_MARGIN) {
        render_title_tab(x, y, TEXT_RIGHT, name, TEXT_YELLOW);
    } else {
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, TOOLTIP_ALPHA);
        render_4slice_box(x, y + TAB_HEIGHT / 2, halfW, TAB_HEIGHT / 2, TOOLTIP_CORNER);
        menu_text_display(name, x, y, TEXT_YELLOW, TEXT_CENTER, 255);
    }
}

// open a horizontal child row in a rounded box under the selected folder
static void expand_folder(int folderId) {
    u8 childIds[MB64_FOLDER_MAX_CHILDREN];
    int count = collect_folder_children(folderId, childIds);
    Selector2DComponent *grid = get_toolbox_grid();
    int row = grid->index / MB64_TOOLBOX_COLUMNS;
    s16 folderX, folderY;
    s16 firstX, panelX, panelY;
    s16 panelW, panelH;
    char *name;
    int fits;

    if (count == 0) return;

    grid->base.inactive = TRUE;

    get_toolbox_cell_pos(grid->index, &folderX, &folderY);
    firstX = folder_row_first_x(folderX, count);
    panelW = count * (BTN_TILE / 2) + FOLDER_BOX_PAD;
    panelH = BTN_TILE / 2 + FOLDER_BOX_PAD;
    panelX = firstX + (count - 1) * (BTN_TILE / 2);
    // bottom row: sit above the folder instead of below
    panelY = folderY + (row == MB64_TOOLBOX_ROWS - 1 ? BTN_TILE : -BTN_TILE);

    BoxComponent *panel = init_box_component(
        get_toolbox_bg(), panelX, panelY,
        panelW, panelH,
        BOX_CORNER, TOOLTIP_ALPHA
    );

    ListComponent *folder = init_list(panel, DIR_HORIZONTAL, MENU_INPUT_JOYSTICK);
    folder->base.prerender = toolbox_begin_buttons;
    for (int i = 0; i < count; i++) {
        FrameComponent *button = init_dynamic_component(NULL, folder_button_render);
        button->buttonID = childIds[i];
        component_list_append(folder, button, (i * 2 - (count - 1)) * (BTN_TILE / 2), 0);
    }
    folder->index = sFolderIndices[folderId - MB64_LEAF_COUNT];
    if (folder->index >= count) folder->index = 0;

    name = get_button_str(folderId);
    fits = get_string_width_ascii(name) / 2 + TOOLTIP_CORNER <= panelW - TAB_MARGIN;

    FrameComponent *tab = init_dynamic_component(panel, folder_tab_render);
    if (fits) {
        // xpos is the right edge; tab renders TEXT_RIGHT from there
        component_set_pos(tab, panelW - TAB_MARGIN, panelH);
    } else {
        component_set_pos(tab, 0, panelH);
    }
    tab->params[0].asPtr = name;
}

static void close_toolbox(void) {
    sToolboxIndex = get_toolbox_grid()->index;
    save_open_folder_index();
    dealloc_component(get_id(sToolbox));
    sToolbox = NULL;
    mb64_menu_state = MB64_MAKE_MAIN;
    show_coord_display();
    set_toolbar_utility_disabled(FALSE);
}

static void toolbox_loop(MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    AnimatedComponent *a = (AnimatedComponent *)m;
    set_menu_style(sToolboxStyle);

    if (!a->timer && ACTIVE) {
        u16 pressed = gPlayer1Controller->buttonPressed;
        if ((pressed & B_BUTTON) && get_folder_panel()) {
            collapse_folder();
            menu_play_click_sound();
            return;
        }
        if (pressed & (B_BUTTON | START_BUTTON)) {
            component_animate_ease_out(a, 4.f, 12, DIR_VERTICAL);
            a->onFinish = close_toolbox;
            menu_play_click_sound();
        }
    }
}

static void toolbox_render_button(Selector2DComponent *s, s16 x, s16 y, u8 column, u8 row, int selected) {
    int index = column + row * s->columns;
    int buttonId = get_toolbox_layout()[index];
    s16 bx, by;

    get_toolbox_cell_pos(index, &bx, &by);
    x += bx;
    y += by;

    if (selected) {
        sCursorX = x;
        sCursorY = y;
    }

    // open folder: folderopen texture only, no icon overlay
    if (index == s->index && s->base.inactive) {
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        mb64_render_button_tex(&mb64_btn_folderopen, x, y);
        return;
    }

    render_button(buttonId, 0, x, y);
}

static void toolbox_select_button(Selector2DComponent *s, UNUSED u8 column, UNUSED u8 row) {
    int buttonId = get_toolbox_layout()[s->index];
    if (buttonId == MB64_BUTTON_BLANK) return;

    if (mb64_ui_buttons[buttonId].placeMode == MB64_PM_NONE) {
        play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
        expand_folder(buttonId);
        // consume so the new child list does not assign on this same press
        gPlayer1Controller->buttonPressed &= ~A_BUTTON;
        return;
    }

    assign_to_toolbar(buttonId);
}

void create_toolbox(void) {
    sToolbox = alloc_component(gMenuRoot, MENU_ANIMATED);
    component_set_pos(sToolbox, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 30);
    component_animate_ease_in(sToolbox, 150.f, 0.4f, DIR_VERTICAL);
    sToolbox->base.prerender = toolbox_loop;

    BoxComponent *bg = init_box_component(
        sToolbox, 0, 0,
        MB64_TOOLBOX_COLUMNS * (BTN_TILE / 2) + TOOLBOX_BOX_PAD,
        MB64_TOOLBOX_ROWS * (BTN_TILE / 2) + TOOLBOX_BOX_PAD,
        BOX_CORNER, 150
    );

    Selector2DComponent *box = init_selector_2d_component(
        bg, 0, 0,
        MB64_TOOLBOX_COLUMNS, MB64_TOOLBOX_SIZE,
        toolbox_render_button, toolbox_select_button
    );
    box->base.prerender = toolbox_begin_buttons;
    box->index = sToolboxIndex;

    s16 cx, cy;
    FrameComponent *overlay = init_dynamic_component(sToolbox, toolbox_overlay_render);
    get_toolbox_cell_pos(box->index, &cx, &cy);
    component_set_pos(overlay, cx, cy);

    // test and settings are not assignable from the toolbox
    set_toolbar_utility_disabled(TRUE);
}

void init_toolbox(void) {
    mb64_exclamation_box_contents = (mb64_lopt_game == MB64_GAME_BTCM)
        ? sExclamationBoxContents_btcm
        : sExclamationBoxContents_vanilla;

    bzero(sFolderIndices, sizeof(sFolderIndices));

    for (int i = 0; i < MB64_TOOLBAR_SIZE; i++) {
        int id = mb64_toolbar[i];
        if (id >= MB64_LEAF_COUNT || id == MB64_BUTTON_BLANK) {
            mb64_toolbar[i] = mb64_toolbar_defaults[i];
            mb64_toolbar_params[i] = 0;
        } else if (mb64_toolbar_params[i] >= mb64_ui_buttons[id].count) {
            mb64_toolbar_params[i] = 0;
        }
    }
}

void reset_toolbox_state(void) {
    sToolboxIndex = 0;
    sToolbox = NULL;
    sAnimatedButton = NULL;
}
