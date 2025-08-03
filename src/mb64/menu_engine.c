#include "menu_engine.h"

#include "game/game_init.h"
#include "audio/external.h"

// Global states for the currently processed menu
MenuStyle gMenuStyle;
MenuState gMenuState;

union MenuComponentData menu_pool[MENU_POOL_SIZE] = {0};

void menu_text_display(char *str, s16 x, s16 y, u8 color, u8 align, u8 alpha) {
    if (gMenuState.selected) color += 1;
    if (gMenuState.disabled) color += 2;
    if (align) {
        int width = get_string_width_ascii(str);
        x -= width * align / 2; // 1 - center, 2 - right
    }
    print_maker_string_ascii_alpha(x, y, str, color, alpha);
}

enum JoystickState {
    JOYSTICK_NONE,
    JOYSTICK_UP,
    JOYSTICK_DOWN,
    JOYSTICK_LEFT,
    JOYSTICK_RIGHT,
};

u8 gJoystickState = JOYSTICK_NONE;
u8 gJoystickTimer = 0;

void menu_update_joystick(void) {
    if (gJoystickTimer > 0) {
        gJoystickTimer--;
    }

    if ((gPlayer1Controller->rawStickX < 10) &&
        (gPlayer1Controller->rawStickX > -10) &&
        (gPlayer1Controller->rawStickY < 10) && 
        (gPlayer1Controller->rawStickY > -10)) {
        gJoystickTimer = 0;
    }

    gJoystickState = JOYSTICK_NONE;

    if (gJoystickTimer == 0) {
        if (gPlayer1Controller->rawStickX > 60) {
            gJoystickTimer = 5;
            gJoystickState = JOYSTICK_RIGHT;
        } else if (gPlayer1Controller->rawStickX < -60) {
            gJoystickTimer = 5;
            gJoystickState = JOYSTICK_LEFT;
        } else if (gPlayer1Controller->rawStickY > 60) {
            gJoystickTimer = 5;
            gJoystickState = JOYSTICK_UP;
        } else if (gPlayer1Controller->rawStickY < -60) {
            gJoystickTimer = 5;
            gJoystickState = JOYSTICK_DOWN;
        }
    }
}

s32 get_input(int inputMethod, int direction) {
    int dir = 0;
    switch (direction) {
        case DIR_VERTICAL:
            switch (inputMethod) {
                case MENU_INPUT_JOYSTICK:
                    if      (gJoystickState == JOYSTICK_UP) dir = -1;
                    else if (gJoystickState == JOYSTICK_DOWN) dir = 1;
                    break;
                case MENU_INPUT_DPAD:
                    if      (gPlayer1Controller->buttonPressed & U_JPAD) dir = -1;
                    else if (gPlayer1Controller->buttonPressed & D_JPAD) dir = 1;
                    break;
            }
            break;
        case DIR_HORIZONTAL:
            switch (inputMethod) {
                case MENU_INPUT_JOYSTICK:
                    if      (gJoystickState == JOYSTICK_LEFT) dir = -1;
                    else if (gJoystickState == JOYSTICK_RIGHT) dir = 1;
                    break;
                case MENU_INPUT_DPAD:
                    if      (gPlayer1Controller->buttonPressed & L_JPAD) dir = -1;
                    else if (gPlayer1Controller->buttonPressed & R_JPAD) dir = 1;
                    break;
                case MENU_INPUT_TRIGGERS:
                    if      (gPlayer1Controller->buttonPressed & L_TRIG) dir = -1;
                    else if (gPlayer1Controller->buttonPressed & R_TRIG) dir = 1;
                    break;
            }
    }
    return dir;
}

void add_child(void *parent, MenuComponent *child) {
    MenuComponent *p = parent;
    child->parent = get_id(p);
    if (!p->child) {
        p->child = get_id(child);
    } else {
        MenuComponent *current = get_component(p->child);
        while (current->next) {
            current = get_component(current->next);
        }
        current->next = get_id(child);
    }
}

// Gets the index'th child of specified type from the parent component.
void *get_child(void *parent, u8 type, u8 index) {
    MenuComponent *p = parent;
    MenuComponent *current = get_component(p->child);
    u8 count = 0;

    while (current) {
        if (current->type == type) {
            if (count == index) {
                return current;
            }
            count++;
        }
        if (!current->next) {
            return NULL;
        }
        current = get_component(current->next);
    }
    return NULL;
}

void *alloc_component(void *parent, u8 type) {
    for (int i = 0; i < ARRAY_COUNT(menu_pool); i++) {
        MenuComponent *m = (MenuComponent *)&menu_pool[i];
        if (m->type == MENU_NONE) {
            bzero(m, sizeof(union MenuComponentData));
            m->type = type;
            if (parent) {
                add_child(parent, m);
            }
            return m;
        }
    }
    return NULL;
}

void component_set_pos(void *m, s16 x, s16 y) {
    struct MenuComponent *c = m;
    c->xpos = x;
    c->ypos = y;
}

// Deallocates component and its children as well as all following sibling components 
void dealloc_component_full(ComponentID id) {
    if (!id) return;
    MenuComponent *m = get_component(id);
    dealloc_component_full(m->next);
    m->next = 0;
    dealloc_component(id);
}

// Deallocates only this component and its children
void dealloc_component(ComponentID id) {
    if (!id) return;
    MenuComponent *m = get_component(id);
    dealloc_component_full(m->child);
    if (m->type == MENU_PAGE_HANDLER) {
        PageHandlerComponent *ph = (PageHandlerComponent *)m;
        dealloc_component_full(ph->oldPage);
        dealloc_component_full(ph->currentPage);
    }

    // If sibling exists, link it to the parent or the previous sibling
    if (m->parent) {
        MenuComponent *parent = get_component(m->parent);
        if (m->next) {
            if (parent->child == id) {
                parent->child = m->next;
            } else {
                MenuComponent *current = get_component(parent->child);
                while (current && current->next != id) {
                    current = get_component(current->next);
                }
                if (current) {
                    current->next = m->next;
                }
            }
        } else {
            parent->child = 0;
        }
    }

    m->type = MENU_NONE;
}

s16 gScissorStack[8][4] = {{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}};
u8 gScissorStackIndex = 0;

void push_scissor(int lx, int ly2, int ux, int uy2) {
    // invert y values
    int ly = SCREEN_HEIGHT - uy2;
    int uy = SCREEN_HEIGHT - ly2;
    lx = MAX(lx, gScissorStack[gScissorStackIndex][0]);
    ly = MAX(ly, gScissorStack[gScissorStackIndex][1]);
    ux = MIN(ux, gScissorStack[gScissorStackIndex][2]);
    uy = MIN(uy, gScissorStack[gScissorStackIndex][3]);
    gScissorStackIndex++;
    gScissorStack[gScissorStackIndex][0] = lx;
    gScissorStack[gScissorStackIndex][1] = ly;
    gScissorStack[gScissorStackIndex][2] = ux;
    gScissorStack[gScissorStackIndex][3] = uy;

    // Set new scissor state
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, lx, ly, ux, uy);
}

void pop_scissor(void) {
    gScissorStackIndex--;
    int lx = gScissorStack[gScissorStackIndex][0];
    int ly = gScissorStack[gScissorStackIndex][1];
    int ux = gScissorStack[gScissorStackIndex][2];
    int uy = gScissorStack[gScissorStackIndex][3];

    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, lx, ly, ux, uy);
}

// ================ FRAME ===================

FrameComponent *init_frame_component(void *parent) {
    return alloc_component(parent, MENU_FRAME);
}

void component_frame_render(MenuComponent *m, s16 x, s16 y) {
    render_child(m, x + m->xpos, y + m->ypos);
}

// ================ TEXT ===================

TextComponent *init_text_component(void *parent, s16 x, s16 y, char *text, u8 align, u8 color) {
    TextComponent *t = alloc_component(parent, MENU_TEXT);
    component_set_pos(t, x, y);
    t->text = text;
    t->align = align;
    t->color = color;
    t->alpha = 255;
    return t;
}

TextComponent *init_text_button(void *parent, s16 x, s16 y, char *text, u8 align, ComponentUpdateFunc onClick, int onClickArg) {
    TextComponent *t = init_text_component(parent, x, y, text, align, 0);
    t->onClick = onClick;
    t->onClickArg = onClickArg;
    return t;
}

void component_text_render(MenuComponent *m, s16 x, s16 y) {
    TextComponent *t = (TextComponent *)m;
    menu_text_display(t->text, x + m->xpos, y + m->ypos, t->color, t->align, t->alpha);

    if (gMenuState.selected && t->onClick && !gMenuState.inactive) {
        if (gPlayer1Controller->buttonPressed & (A_BUTTON)) {
            t->onClick(t, t->onClickArg);
            play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
        }
    }
};

// ================ DYNAMIC ===================

FrameComponent *init_dynamic_component(void *parent, ComponentRenderFunc render) {
    FrameComponent *f = alloc_component(parent, MENU_FRAME);
    f->base.prerender = render;
    return f;
}

// ================ LIST ===================

ListItemComponent *component_list_append(ListComponent *l, void *m, s16 x, s16 y) {
    ListItemComponent *item = alloc_component(l, MENU_LISTITEM);
    component_set_pos(item, x, y);
    add_child(item, m);
    l->count++;
    return item;
}

ListItemComponent *component_list_get(ListComponent *l, u8 index) {
    MenuComponent *current = get_component(l->base.child);
    for (u8 i = 0; i < index; i++) {
        if (current->next) {
            current = get_component(current->next);
        } else {
            return NULL;
        }
    }
    return (ListItemComponent *)current;
}

void component_list_render(MenuComponent *m, s16 x, s16 y) {
    ListComponent *l = (ListComponent *)m;
    ListItemComponent *item = component_list_get(l, l->index);

    if (l->count == 0) return;
    if (l->count != 1) {
        s8 dir = 0;
        if (gJoystickState == JOYSTICK_UP) {
            dir = -1;
        } else if (gJoystickState == JOYSTICK_DOWN) {
            dir = 1;
        }

        if (dir && !gMenuState.inactive) {
            play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
            item->selected = 0;
            do {
                l->index = (l->index + dir + l->count) % l->count;
                item = component_list_get(l, l->index);
            } while (item->disabled);
        }
    }
    item->selected = 1;

    render_child(m, x + m->xpos, y + m->ypos);
}

// ================ LIST ITEM ===================

void component_listitem_render(MenuComponent *m, s16 x, s16 y) {
    ListItemComponent *item = (ListItemComponent *)m;

    gMenuState.selected = item->selected;
    gMenuState.disabled = item->disabled;
    if (gMenuStyle.listOffsetSelected) {
        if (gMenuState.selected) {
            item->xoffset = MIN(item->xoffset+1, 3);
        } else {
            item->xoffset = MAX(item->xoffset-1, 0);
        }
    }
    render_child(m, x + m->xpos + item->xoffset, y + m->ypos);
}

// ================ GENERIC SCROLL ===================

#define SCROLL_ANIM_FRAMES 5
int handle_scroll(ScrollParams *params, s8 dir, u8 *value) {
    if (params->offset) {
        if (params->offset > 0) {
            params->offset--;
        } else if (params->offset < 0) {
            params->offset++;
        }
    } else if (!gMenuState.inactive) {
        if (dir) {
            params->offset = dir * SCROLL_ANIM_FRAMES;
            *value = (*value + dir + params->count) % params->count;
            return TRUE;
        }
    }
    return FALSE;
}

// Calculate X offset for currently indexed component
ALWAYS_INLINE int scroll_get_offset(ScrollParams *params) {
    return (params->offset * params->width * 2) / SCROLL_ANIM_FRAMES;
}
// Calculate additional offset for previous component
int scroll_get_extra_offset(ScrollParams *params) {
    if (params->offset < 0) {
        return params->width * 2;
    } else {
        return -params->width * 2;
    }
}
void scroll_push_scissor_horiz(ScrollParams *params, s16 x) {
    push_scissor(x - params->width, 0, x + params->width, SCREEN_HEIGHT);
}
void scroll_push_scissor_vert(ScrollParams *params, s16 y) {
    push_scissor(0, y - params->width, SCREEN_WIDTH, y + params->width);
}

// ================ SELECTOR ===================

SelectorComponent *init_array_selector(void *parent, u8 *value, u8 width, u8 count, char **array, ComponentUpdateFunc onChange) {
    SelectorComponent *s = alloc_component(parent, MENU_SELECTOR);
    s->string.array = array;
    s->value = value;
    s->selectorType = SELECTOR_ARRAY;
    s->scroll.width = width;
    s->scroll.count = count;
    s->onChange = onChange;
    return s;
}

SelectorComponent *init_func_selector(void *parent, u8 *value, u8 width, u8 count, SelectorStringFunc func, ComponentUpdateFunc onChange) {
    SelectorComponent *s = alloc_component(parent, MENU_SELECTOR);
    s->string.func = func;
    s->value = value;
    s->selectorType = SELECTOR_FUNC;
    s->scroll.width = width;
    s->scroll.count = count;
    s->onChange = onChange;
    return s;
}

char *selector_get_str(SelectorStrings *s, u8 selectorType, s32 index, char *buf) {
    switch (selectorType) {
        case SELECTOR_ARRAY:
            return s->array[index];
        case SELECTOR_FUNC:
            return s->func(index, buf);
    }
    return NULL;
}

void component_selector_render(MenuComponent *m, s16 x, s16 y) {
    SelectorComponent *s = (SelectorComponent *)m;
    char buf[64];

    s8 dir = 0;
    if (gMenuState.selected) {
        if (gJoystickState == JOYSTICK_LEFT) {
            dir = -1;
        } else if (gJoystickState == JOYSTICK_RIGHT) {
            dir = 1;
        }
    }
            
    if (handle_scroll(&s->scroll, dir, s->value)) {
        play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
        if (s->onChange) {
            s->onChange(s, 0);
        }
    }

    x += m->xpos;
    y += m->ypos;
    menu_text_display("<", x - s->scroll.width - 1, y, 0, TEXT_RIGHT, 255);
    menu_text_display(">", x + s->scroll.width + 3, y, 0, TEXT_LEFT, 255);
    int offset = scroll_get_offset(&s->scroll);

    scroll_push_scissor_horiz(&s->scroll, x);

    menu_text_display(selector_get_str(&s->string, s->selectorType, *s->value, buf), x + offset, y, 0, TEXT_CENTER, 255);
    if (s->scroll.offset) {
        if (s->scroll.offset < 0) {
            dir = 1;
        } else {
            dir = -1;
        }
        menu_text_display(selector_get_str(&s->string, s->selectorType, (*s->value + dir + s->scroll.count) % s->scroll.count, buf),
                          x + offset + scroll_get_extra_offset(&s->scroll), y, 0, TEXT_CENTER, 255);
    }
    pop_scissor();
}

// ================ ANIMATED ===================

void component_reset_animation(AnimatedComponent *a) {
    a->offset = 0.f;
    a->velocity = 0.f;
    a->accel = 0.f;
    a->animType = ANIM_NONE;
    a->timer = 0;
    a->delay = 0;
}

void component_animate_ease_in(AnimatedComponent *a, f32 offset, f32 multiplier, u8 direction) {
    a->animType = ANIM_EASE_IN;
    a->offset = offset;
    a->accel = multiplier;
    a->timer = 1;
    a->direction = direction;
}

void component_animate_ease_out(AnimatedComponent *a, f32 accel, u8 timer, u8 direction) {
    a->animType = ANIM_EASE_OUT;
    a->offset = 0.f;
    a->velocity = 0.f;
    a->accel = accel;
    a->timer = timer;
    a->direction = direction;
}

void component_animate_bounce_in(AnimatedComponent *a, f32 offset, f32 accel, f32 initialVel, u8 direction) {
    a->animType = ANIM_BOUNCE_IN;
    a->offset = offset;
    a->accel = accel;
    a->velocity = initialVel;
    a->timer = 1;
    a->direction = direction;
}

void component_animate_bounce_out(AnimatedComponent *a, f32 accel, f32 initialVel, u8 timer, u8 direction) {
    component_animate_ease_out(a, accel, timer, direction);
    a->velocity = initialVel;
}

void component_animated_render(MenuComponent *m, s16 x, s16 y) {
    AnimatedComponent *a = (AnimatedComponent *)m;

    if (a->delay) {
        a->delay--;
    } else if (a->timer) {
        switch (a->animType) {
            case ANIM_EASE_IN:
                a->offset -= a->offset * a->accel;
                if (ABS(a->offset) < 0.5f) {
                    component_reset_animation(a);
                }
                break;
            case ANIM_EASE_OUT:
                a->velocity += a->accel;
                a->offset += a->velocity;
                a->timer--;
                break;
            case ANIM_BOUNCE_IN:
                a->velocity += a->accel;
                a->offset += a->velocity;
                if ((a->velocity * a->accel > 0.f) && (a->offset * a->accel > 0.f)) {
                    component_reset_animation(a);
                }
                break;
        }
    }
    if (a->timer == 0 && a->onFinish) {
        a->onFinish(a, 0);
        a->onFinish = NULL;
    }

    switch (a->direction) {
        case DIR_HORIZONTAL:
            x += a->offset;
            break;
        case DIR_VERTICAL:
            y += a->offset;
            break;
    }

    gMenuState.inactive = (a->timer > 0);
    render_child(m, x + m->xpos, y + m->ypos);
}

// ================ MATRIX ===================

MatrixComponent *init_matrix_component(void *parent, s16 rot, f32 xScale, f32 yScale) {
    MatrixComponent *m = alloc_component(parent, MENU_MATRIX);
    m->rot = rot;
    m->xScale = xScale;
    m->yScale = yScale;
    return m;
}

void component_matrix_render(MenuComponent *m, s16 x, s16 y) {
    MatrixComponent *mc = (MatrixComponent *)m;

    s16 *mtx = alloc_display_list(sizeof(Mtx));
    if (!mtx) return;

    // Construct matrix with rotation, translation and scale
    Mtx temp;
    guRotate(&temp, (mc->rot * 45.f) / 0x2000, 0.f, 0.f, 1.f);
    guScale(mtx, mc->xScale, mc->yScale, 1.f);
    mtx[12] = x + m->xpos;
    mtx[13] = y + m->ypos;
    guMtxCatL(&temp, mtx, mtx);

    gSPMatrix(gDisplayListHead++, mtx, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    render_child(m, 0, 0);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

// ================ PAGE HANDLER ===================

#define PAGE_HANDLER_ANIM_FRAMES 5
PageHandlerComponent *init_page_handler(void *parent, PageCreator pageCreator, u8 count, u16 width) {
    PageHandlerComponent *ph = alloc_component(parent, MENU_PAGE_HANDLER);
    ph->pageCreator = pageCreator;
    ph->scroll.count = count;
    ph->scroll.width = width;
    ph->direction = DIR_HORIZONTAL;
    ph->input = MENU_INPUT_TRIGGERS;
    return ph;
}

FrameComponent *page_handler_create_page(PageHandlerComponent *ph, s8 index) {
    FrameComponent *f = ph->pageCreator(index);
    f->base.parent = get_id(ph);
    return f;
}

void page_handler_scroll(PageHandlerComponent *ph, int dir) {
    if (handle_scroll(&ph->scroll, dir, &ph->index)) {
        if (ph->input != MENU_INPUT_NONE) play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
        ph->oldPage = ph->currentPage;
        ph->currentPage = get_id(page_handler_create_page(ph, ph->index));
    }
}

void component_page_handler_render(MenuComponent *m, s16 x, s16 y) {
    PageHandlerComponent *ph = (PageHandlerComponent *)m;

    if (!ph->currentPage) {
        ph->currentPage = get_id(page_handler_create_page(ph, ph->index));
    }

    s8 dir = get_input(ph->input, ph->direction);
    page_handler_scroll(ph, dir);

    x += m->xpos;
    y += m->ypos;
    int offset = scroll_get_offset(&ph->scroll);
    if (ph->direction == DIR_VERTICAL) {
        scroll_push_scissor_vert(&ph->scroll, y);
        y -= offset;
    } else {
        scroll_push_scissor_horiz(&ph->scroll, x);
        x += offset;
    }

    if (ph->scroll.offset) {
        int extraOffset = scroll_get_extra_offset(&ph->scroll);
        int newx = x; int newy = y;
        if (ph->direction == DIR_VERTICAL) {
            newy -= extraOffset;
        } else {
            newx += extraOffset;
        }

        gMenuState.inactive = TRUE;
        render_component(get_component(ph->oldPage), newx, newy);
    } else if (ph->oldPage) {
        dealloc_component_full(ph->oldPage);
        ph->oldPage = 0;
    }
    render_component(get_component(ph->currentPage), x, y);

    pop_scissor();
}

// ================ PAGE TITLE ===================

PageTitleComponent *init_page_title_array(void *parent, void *original, s16 x, s16 y, s16 width, char **array) {
    PageTitleComponent *pt = alloc_component(parent, MENU_PAGE_TITLE);
    component_set_pos(pt, x, y);
    pt->string.array = array;
    pt->scroll.width = width;
    pt->original = get_id(original);
    pt->selectorType = SELECTOR_ARRAY;
    return pt;
}

PageTitleComponent *init_page_title_func(void *parent, void *original, s16 x, s16 y, s16 width, SelectorStringFunc func) {
    PageTitleComponent *pt = alloc_component(parent, MENU_PAGE_TITLE);
    component_set_pos(pt, x, y);
    pt->string.func = func;
    pt->scroll.width = width;
    pt->original = get_id(original);
    pt->selectorType = SELECTOR_FUNC;
    return pt;
}

void component_page_title_render(MenuComponent *m, s16 x, s16 y) {
    PageTitleComponent *pt = (PageTitleComponent *)m;
    char buf[64];

    x += m->xpos;
    y += m->ypos;
    // Copy scroll data from parent
    MenuComponent *orig = get_component(pt->original);
    u8 value;
    switch (orig->type) {
        case MENU_PAGE_HANDLER:
            pt->scroll.offset = ((PageHandlerComponent *)orig)->scroll.offset;
            pt->scroll.count = ((PageHandlerComponent *)orig)->scroll.count;
            value = ((PageHandlerComponent *)orig)->index;
            break;
        case MENU_SELECTOR:
            pt->scroll.offset = ((SelectorComponent *)orig)->scroll.offset;
            pt->scroll.count = ((SelectorComponent *)orig)->scroll.count;
            value = *((SelectorComponent *)orig)->value;
            break;
        default:
            return;
    }

    int offset = scroll_get_offset(&pt->scroll);

    scroll_push_scissor_horiz(&pt->scroll, x);

    menu_text_display(selector_get_str(&pt->string, pt->selectorType, value, buf), x + offset, y, 0, TEXT_CENTER, 255);
    if (pt->scroll.offset) {
        int dir;
        if (pt->scroll.offset < 0) {
            dir = 1;
        } else {
            dir = -1;
        }
        menu_text_display(selector_get_str(&pt->string, pt->selectorType, (value + dir + pt->scroll.count) % pt->scroll.count, buf),
                          x + offset + scroll_get_extra_offset(&pt->scroll), y, 0, TEXT_CENTER, 255);
    }
    pop_scissor();
}

// ================ PAGE SCROLL ===================
// Currently unused

PageScrollComponent *init_page_scroll(void *parent, PageScrollFunc func, u8 width, u8 direction) {
    PageScrollComponent *ps = alloc_component(parent, MENU_PAGE_SCROLL);
    ps->pageFunc = func;
    ps->width = width;
    ps->direction = direction;
    return ps;
}

void component_page_scroll_render(MenuComponent *m, s16 x, s16 y) {
    PageScrollComponent *ps = (PageScrollComponent *)m;

    x += m->xpos;
    y += m->ypos;

    s8 targetOffset = ps->pageFunc(ps) * SCROLL_ANIM_FRAMES;

    if (ps->offset != targetOffset) {
        gMenuState.inactive = TRUE;
        if (ps->offset < targetOffset) {
            ps->offset++;
        } else {
            ps->offset--;
        }
    }

    switch (ps->direction) {
        case DIR_HORIZONTAL:
            push_scissor(x - ps->width, 0, x + ps->width, SCREEN_HEIGHT);
            x -= ps->offset * ps->width * 2 / SCROLL_ANIM_FRAMES;
            break;
        case DIR_VERTICAL:
            push_scissor(0, y - ps->width, SCREEN_WIDTH, y + ps->width);
            y += ps->offset * ps->width * 2 / SCROLL_ANIM_FRAMES;
            break;
    }

    render_child(m, x, y);

    pop_scissor();
}

// ================ GENERAL ===================

ComponentRenderFunc component_render_funcs[] = {
    [MENU_FRAME] = component_frame_render,
    [MENU_TEXT] = component_text_render,
    [MENU_LIST] = component_list_render,
    [MENU_LISTITEM] = component_listitem_render,
    [MENU_SELECTOR] = component_selector_render,
    [MENU_ANIMATED] = component_animated_render,
    [MENU_MATRIX] = component_matrix_render,
    [MENU_PAGE_HANDLER] = component_page_handler_render,
    [MENU_PAGE_TITLE] = component_page_title_render,
    [MENU_PAGE_SCROLL] = component_page_scroll_render,
};

void render_component(MenuComponent *m, s16 x, s16 y) {
    if (!m) return;
    MenuState prevState = gMenuState; // Push state

    if (m->type < ARRAY_COUNT(component_render_funcs)) {
        if (m->inactive) {
            gMenuState.inactive = TRUE;
        }
        ComponentRenderFunc func = m->prerender;
        if (func) {
            func(m, x, y);
        }
        func = component_render_funcs[m->type];
        if (func) {
            func(m, x, y);
        }
    }

    gMenuState = prevState; // Pop state

    if (m->next) {
        render_component(get_component(m->next), x, y);
    }
}

FrameComponent *gMenuRoot;

void init_root(void) {
    gMenuRoot = init_frame_component(NULL);
}

void reset_menu(void) {
    bzero(&menu_pool, sizeof(menu_pool));
    reset_settings_menu_state();
    init_root();
}

extern ComponentID settingsRoot;

void render_menu(void) {
    menu_update_joystick();
    render_component(gMenuRoot, 0, 0);
}
