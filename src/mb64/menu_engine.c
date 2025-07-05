#include "menu_engine.h"

#include "game/game_init.h"
#include "audio/external.h"

// Global states for the currently processed menu
MenuState gMenuState;

union MenuComponentData menu_pool[64] = {0};

void menu_text_display(char *str, s16 x, s16 y, u8 color, u8 align) {
    if (gMenuState.selected) color += 1;
    if (gMenuState.disabled) color += 2;
    if (align) {
        int width = get_string_width_ascii(str);
        x -= width * align / 2; // 1 - center, 2 - right
    }
    print_maker_string_ascii(x, y, str, color);
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

void add_child(MenuComponent *parent, MenuComponent *child) {
    if (parent->child == NULL) {
        parent->child = child;
    } else {
        MenuComponent *current = parent->child;
        while (current->next) {
            current = current->next;
        }
        current->next = child;
    }
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

void component_set_pos(MenuComponent *m, s16 x, s16 y) {
    m->xpos = x;
    m->ypos = y;
}

void dealloc_component(MenuComponent *m) {
    if (!m) return;
    dealloc_component(m->next);
    dealloc_component(m->child);
    if (m->type == MENU_PAGE_HANDLER) {
        PageHandlerComponent *ph = (PageHandlerComponent *)m;
        dealloc_component(&ph->oldPage->base);
        dealloc_component(&ph->currentPage->base);
    }
    m->type = MENU_NONE;
}

s16 gScissorStack[8][4] = {{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}};
u8 gScissorStackIndex = 0;

void push_scissor(int lx, int ly, int ux, int uy) {
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
    component_set_pos(&t->base, x, y);
    t->text = text;
    t->align = align;
    t->color = color;
    return t;
}

void component_text_render(MenuComponent *m, s16 x, s16 y) {
    TextComponent *t = (TextComponent *)m;
    menu_text_display(t->text, x + m->xpos, y + m->ypos, t->color, t->align);
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
    if (index >= l->count) {
        return NULL;
    }
    MenuComponent *current = l->base.child;
    for (u8 i = 0; i < index; i++) {
        if (current->next) {
            current = current->next;
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
    if (gMenuState.selected) {
        item->xoffset = MIN(item->xoffset+1, 3);
    } else {
        item->xoffset = MAX(item->xoffset-1, 0);
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
            play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
            return TRUE;
        }
    }
    return FALSE;
}

// Calculate X offset for currently indexed component
ALWAYS_INLINE int scroll_get_offset(ScrollParams *params) {
    return (params->offset * params->width) / SCROLL_ANIM_FRAMES;
}
// Calculate additional offset for previous component
int scroll_get_extra_offset(ScrollParams *params) {
    if (params->offset < 0) {
        return params->width;
    } else if (params->offset > 0) {
        return -params->width;
    }
}
void scroll_push_scissor(ScrollParams *params, s16 x) {
    push_scissor(x - params->width/2, 0, x + params->width/2, SCREEN_HEIGHT);
}

// ================ SELECTOR ===================

SelectorComponent *init_array_selector(void *parent, u8 *value, u8 width, u8 count, char **array, ComponentUpdateFunc onChange) {
    SelectorComponent *s = alloc_component(parent, MENU_SELECTOR);
    s->options = array;
    s->value = value;
    s->selectorType = SELECTOR_ARRAY;
    s->scroll.width = width;
    s->scroll.count = count;
    s->onChange = onChange;
    return s;
}

SelectorComponent *init_func_selector(void *parent, u8 *value, u8 width, u8 count, SelectorStringFunc func, ComponentUpdateFunc onChange) {
    SelectorComponent *s = alloc_component(parent, MENU_SELECTOR);
    s->stringFunc = func;
    s->value = value;
    s->selectorType = SELECTOR_FUNC;
    s->scroll.width = width;
    s->scroll.count = count;
    s->onChange = onChange;
    return s;
}

char *selector_get_str(SelectorComponent *s, s32 index, char *buf) {
    switch (s->selectorType) {
        case SELECTOR_ARRAY:
            return s->options[index];
        case SELECTOR_FUNC:
            return s->stringFunc(index, buf);
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
        if (s->onChange) {
            s->onChange();
        }
    }

    x += m->xpos;
    y += m->ypos;
    menu_text_display("<", x - s->scroll.width/2 - 1, y, 0, TEXT_RIGHT);
    menu_text_display(">", x + s->scroll.width/2 + 3, y, 0, TEXT_LEFT);
    int offset = scroll_get_offset(&s->scroll);

    scroll_push_scissor(&s->scroll, x);

    menu_text_display(selector_get_str(s, *s->value, buf), x + offset, y, 0, TEXT_CENTER);
    if (s->scroll.offset) {
        if (s->scroll.offset < 0) {
            dir = 1;
        } else {
            dir = -1;
        }
        menu_text_display(selector_get_str(s, (*s->value + dir + s->scroll.count) % s->scroll.count, buf),
                          x + offset + scroll_get_extra_offset(&s->scroll), y, 0, TEXT_CENTER);
    }
    pop_scissor();
}

// ================ ANIMATED ===================

void component_reset_animation(AnimatedComponent *a) {
    a->offset = 0.f;
    a->velocity = 0.f;
    a->accel = 0.f;
    a->animType = ANIM_NONE;
    a->moving = FALSE;
}

void component_animate_ease_in(AnimatedComponent *a, f32 offset, f32 multiplier, u8 direction) {
    a->animType = ANIM_EASE_IN;
    a->offset = offset;
    a->accel = multiplier; // use accel field
    a->moving = TRUE;
    a->direction = direction;
}

void component_animate_ease_out(AnimatedComponent *a, f32 accel, u8 direction) {
    a->animType = ANIM_EASE_OUT; // Reuse ease in for now
    a->offset = 0.f;
    a->velocity = 0.f;
    a->accel = accel; // use accel field
    a->moving = TRUE;
    a->direction = direction;
}

void component_animated_render(MenuComponent *m, s16 x, s16 y) {
    AnimatedComponent *a = (AnimatedComponent *)m;

    switch (a->animType) {
        case ANIM_EASE_IN:
            a->offset -= a->offset * a->accel;
            if (a->offset > 0.f) {
                if (a->offset < 1.f) {
                    a->offset = 0.f;
                }
            } else {
                if (a->offset > -1.f) {
                    a->offset = 0.f;
                }
            }
            if (a->offset == 0.f) {
                component_reset_animation(a);
            }
            break;
        case ANIM_EASE_OUT:
            a->velocity += a->accel;
            a->offset += a->velocity;
            break;
    }

    switch (a->direction) {
        case DIR_HORIZONTAL:
            x += a->offset;
            break;
        case DIR_VERTICAL:
            y += a->offset;
            break;
    }

    gMenuState.inactive = a->moving;
    render_child(m, x + m->xpos, y + m->ypos);
}

// ================ PAGE HANDLER ===================

#define PAGE_HANDLER_ANIM_FRAMES 5
PageHandlerComponent *init_page_handler(void *parent, PageCreator pageCreator, u8 count, u16 width) {
    PageHandlerComponent *ph = alloc_component(parent, MENU_PAGE_HANDLER);
    ph->pageCreator = pageCreator;
    ph->scroll.count = count;
    ph->scroll.width = width;
    return ph;
}

FrameComponent *page_handler_create_page(PageHandlerComponent *ph, s8 index) {
    return ph->pageCreator(index);
}

void component_page_handler_render(MenuComponent *m, s16 x, s16 y) {
    PageHandlerComponent *ph = (PageHandlerComponent *)m;

    if (!ph->currentPage) {
        ph->currentPage = ph->pageCreator(ph->index);
    }

    s8 dir = 0;
    if (gPlayer1Controller->buttonPressed & L_TRIG) {
        dir = -1;
    } else if (gPlayer1Controller->buttonPressed & R_TRIG) {
        dir = 1;
    }
    if (handle_scroll(&ph->scroll, dir, &ph->index)) {
        ph->oldPage = ph->currentPage;
        ph->currentPage = page_handler_create_page(ph, ph->index);
    }

    x += m->xpos;
    y += m->ypos;
    int offset = scroll_get_offset(&ph->scroll);

    scroll_push_scissor(&ph->scroll, x);

    if (ph->scroll.offset) {
        int extraOffset = scroll_get_extra_offset(&ph->scroll);
        gMenuState.inactive = TRUE;
        render_component(&ph->oldPage->base, x + offset + extraOffset, y);
    } else if (ph->oldPage) {
        dealloc_component(&ph->oldPage->base);
        ph->oldPage = NULL;
    }
    render_component(&ph->currentPage->base, x + offset, y);

    pop_scissor();
}

// ================ PAGE TITLE ===================

PageTitleComponent *init_page_title(void *parent, MenuComponent *p, s16 x, s16 y, s16 width, char **array) {
    PageTitleComponent *pt = alloc_component(parent, MENU_PAGE_TITLE);
    component_set_pos(&pt->base, x, y);
    pt->array = array;
    pt->scroll.width = width;
    if (p) {
        if (p->type == MENU_PAGE_HANDLER) {
            PageHandlerComponent *ph = (PageHandlerComponent *)p;
            pt->parentScroll = &ph->scroll;
            pt->value = &ph->index;
        } else if (p->type == MENU_SELECTOR) {
            SelectorComponent *s = (SelectorComponent *)p;
            pt->parentScroll = &s->scroll;
            pt->value = s->value;
        }
    }
    return pt;
}

void component_page_title_render(MenuComponent *m, s16 x, s16 y) {
    PageTitleComponent *pt = (PageTitleComponent *)m;

    x += m->xpos;
    y += m->ypos;
    // Copy scroll data from parent
    pt->scroll.offset = pt->parentScroll->offset;
    pt->scroll.count = pt->parentScroll->count;

    int offset = scroll_get_offset(&pt->scroll);

    scroll_push_scissor(&pt->scroll, x);

    menu_text_display(pt->array[*pt->value], x + offset, y, 0, TEXT_CENTER);
    if (pt->scroll.offset) {
        int dir;
        if (pt->scroll.offset < 0) {
            dir = 1;
        } else {
            dir = -1;
        }
        menu_text_display(pt->array[(*pt->value + dir + pt->scroll.count) % pt->scroll.count],
                          x + offset + scroll_get_extra_offset(&pt->scroll), y, 0, TEXT_CENTER);
    }
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
    [MENU_PAGE_HANDLER] = component_page_handler_render,
    [MENU_PAGE_TITLE] = component_page_title_render,
};

void render_component(MenuComponent *m, s16 x, s16 y) {
    if (!m) return;
    MenuState prevState = gMenuState; // Push state

    if (m->type < ARRAY_COUNT(component_render_funcs)) {
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
        render_component(m->next, x, y);
    }
}
