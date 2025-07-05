#pragma once

#include "types.h"

typedef struct MenuComponent MenuComponent;
typedef void (*ComponentRenderFunc)(MenuComponent *m, s16 x, s16 y);
typedef void (*ComponentUpdateFunc)(void);

enum MenuDirection {
    DIR_VERTICAL,
    DIR_HORIZONTAL
};

typedef struct {
    u8 selected;
    u8 disabled;
    u8 inactive;
} MenuState;

// Base component for all other component types
struct MenuComponent {
    u8 type;
    s16 xpos;
    s16 ypos;
    MenuComponent *child;
    MenuComponent *next;
    ComponentRenderFunc prerender; // Optional function for extra logic
};

// Empty component, only exists to contain other components
typedef struct {
    MenuComponent base;
} FrameComponent;

enum TextAlignment {
    TEXT_LEFT,
    TEXT_CENTER,
    TEXT_RIGHT
};
typedef struct {
    MenuComponent base;
    char *text;
    u8 align;
    u8 color;
} TextComponent;


typedef struct {
    MenuComponent base;
    u8 count;
    u8 index;
    u8 dir;
} ListComponent;

typedef struct {
    MenuComponent base;
    u8 selected;
    u8 disabled;
    s8 xoffset;
} ListItemComponent;

typedef struct {
    u8 count;
    s8 offset;
    u16 width;
} ScrollParams;

enum SelectorComponentType {
    SELECTOR_ARRAY, // Uses a string array to get option name
    SELECTOR_FUNC,  // Uses a function to get option name
};
typedef char *(*SelectorStringFunc)(s32 index, char *buf);
typedef struct {
    MenuComponent base;
    union {
        char **options;
        SelectorStringFunc stringFunc;
    };
    ComponentUpdateFunc onChange;
    ScrollParams scroll;
    u8 *value;
    u8 selectorType;
} SelectorComponent;

enum AnimationTypes {
    ANIM_NONE,
    ANIM_EASE_IN,
    ANIM_EASE_OUT,
};
typedef struct {
    MenuComponent base;
    f32 offset;
    f32 velocity;
    f32 accel;
    u8 animType;
    u8 moving;
    u8 direction;
} AnimatedComponent;

typedef FrameComponent *(*PageCreator)(s32 index);
typedef struct {
    MenuComponent base;
    PageCreator pageCreator;
    FrameComponent *currentPage;
    FrameComponent *oldPage;
    ScrollParams scroll;
    u8 index;
} PageHandlerComponent;

typedef struct {
    MenuComponent base;
    ScrollParams *parentScroll;
    ScrollParams scroll;
    char **array;
    u8 *value;
} PageTitleComponent;

enum MenuComponents {
    MENU_NONE = 0,
    MENU_FRAME,
    MENU_TEXT,
    MENU_LIST,
    MENU_LISTITEM,
    MENU_SELECTOR,
    MENU_DYNAMIC,
    MENU_ANIMATED,

    // For settings menu
    MENU_PAGE_HANDLER,
    MENU_PAGE_TITLE,
};

union MenuComponentData {
    MenuComponent base;
    FrameComponent frame;
    TextComponent text;
    ListItemComponent listitem;
    ListComponent list;
    SelectorComponent selector;
    AnimatedComponent animated;
    PageHandlerComponent pageHandler;
};

void menu_update_joystick(void);
void *alloc_component(void *parent, u8 type);
void component_set_pos(MenuComponent *m, s16 x, s16 y);
void dealloc_component(MenuComponent *m);
void render_component(MenuComponent *m, s16 x, s16 y);

ALWAYS_INLINE void render_child(MenuComponent *m, s16 x, s16 y) {
    if (m->child) {
        render_component(m->child, x, y);
    }
}

FrameComponent *init_frame_component(void *parent);
TextComponent *init_text_component(void *parent, s16 x, s16 y, char *text, u8 align, u8 color);
FrameComponent *init_dynamic_component(void *parent, ComponentRenderFunc render);
PageHandlerComponent *init_page_handler(void *parent, PageCreator pageCreator, u8 count, u16 width);
PageTitleComponent *init_page_title(void *parent, MenuComponent *p, s16 x, s16 y, s16 width, char **array);

SelectorComponent *init_array_selector(void *parent, u8 *value, u8 width, u8 count, char **array, ComponentUpdateFunc onChange);
SelectorComponent *init_func_selector(void *parent, u8 *value, u8 width, u8 count, SelectorStringFunc func, ComponentUpdateFunc onChange);

ListItemComponent *component_list_append(ListComponent *l, void *m, s16 x, s16 y);
ListItemComponent *component_list_get(ListComponent *l, u8 index);

void component_animate_ease_in(AnimatedComponent *a, f32 offset, f32 multiplier, u8 direction);
void component_animate_ease_out(AnimatedComponent *a, f32 accel, u8 direction);

