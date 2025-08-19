#pragma once

#include "types.h"

#include "engine/math_util.h"
#include "audio/external.h"
#include "game/segment2.h"
#include "game/game_init.h"
#include "game/ingame_menu.h"
#include "game/geo_misc.h"

#include "actors/uiCorner/header.h"
// Temp dls
#include "levels/menu/mm_btn_sm/header.h"
#include "levels/menu/mm_btn2/header.h"
#include "levels/menu/mm_btn_lg/header.h"
#include "actors/b/header.h"
#include "actors/bg/header.h"
#include "actors/uibutton/header.h"

#define MENU_POOL_SIZE 128

typedef struct MenuComponent MenuComponent;
typedef u8 ComponentID;
typedef void (*ComponentRenderFunc)(MenuComponent *m, s16 x, s16 y);
typedef void (*ComponentUpdateFunc)(); // Passes one optional parameter for the component itself


extern u32 gGlobalTimer;
#define get_selected_color_value() (100 + sins(gGlobalTimer * 0x1000) * 15)

#define ACTIVE (!gMenuState.inactive && !gMenuState.disabled)
#define SELECTED (gMenuState.selected && ACTIVE)

enum MenuDirection {
    DIR_VERTICAL,
    DIR_HORIZONTAL
};

enum InputMethod {
    MENU_INPUT_NONE = 0,
    MENU_INPUT_JOYSTICK  = (1 << 0),
    MENU_INPUT_DPAD      = (1 << 1),
    MENU_INPUT_CBUTTONS  = (1 << 2),
    MENU_INPUT_TRIGGERS  = (1 << 3),
};

enum TextColors {
    TEXT_WHITE,
    TEXT_YELLOW,
    TEXT_GRAY,
    TEXT_DARK_YELLOW,
    TEXT_RED,
    TEXT_LIGHTBLUE,
    TEXT_DARKRED,
    TEXT_DARKBLUE,
};

typedef struct {
    u8 selected;
    u8 disabled;
    u8 inactive;
} MenuState;

typedef struct {
    u8 textHighlightSelected:1;
    u8 listOffsetSelected:1;
    u8 textNoShadow:1;

    u8 noClickSounds:1;
    u8 noMoveSounds:1;
} MenuStyle;

extern MenuStyle gMenuStyle;
extern MenuState gMenuState;

ALWAYS_INLINE void menu_play_click_sound(void) {
    if (!gMenuStyle.noClickSounds) {
        play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
    }
}
ALWAYS_INLINE void menu_play_move_sound(void) {
    if (!gMenuStyle.noMoveSounds) {
        play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
    }
}

#define set_menu_style(style) (gMenuStyle = style)

// Base component for all other component types
struct MenuComponent {
    u8 type:7;
    u8 inactive:1;
    ComponentID child;
    ComponentID next;
    ComponentID parent;
    s16 xpos;
    s16 ypos;
    ComponentRenderFunc prerender; // Optional function for extra logic
};

// Empty component, only exists to contain other components
typedef struct {
    MenuComponent base;
    union {
        void *asPtr;
        int asInt;
        f32 asFloat;
        s16 asShorts[2];
        u8 asBytes[4];
    } params[4];
} FrameComponent;

enum TextAlignment {
    TEXT_LEFT,
    TEXT_CENTER,
    TEXT_RIGHT
};
typedef struct {
    MenuComponent base;
    ComponentUpdateFunc onClick;
    char *text;
    u8 onClickArg;
    u8 align:2;
    u8 color:5;
    u8 skipExtension:1;
    u8 showCursor:1;
    u8 cursorPos:6;
    u8 alpha;
} TextComponent;

typedef struct {
    u8 count;
    s8 offset;
    u8 width;
} ScrollParams;

enum SelectorComponentType {
    SELECTOR_ARRAY, // Uses a string array to get option name
    SELECTOR_FUNC,  // Uses a function to get option name
};

typedef char *(*SelectorStringFunc)(s32 index, char *buf);

typedef union {
    char **array;
    SelectorStringFunc func;
} SelectorStrings;

typedef struct {
    MenuComponent base;
    SelectorStrings string;
    ComponentUpdateFunc onChange;
    ScrollParams scroll;
    u8 selectorType;
    u8 *value;
} SelectorComponent;

enum AnimationTypes {
    ANIM_NONE,
    ANIM_EASE_IN,
    ANIM_EASE_OUT,
    ANIM_BOUNCE_IN,
    ANIM_LINEAR,
};
typedef struct {
    MenuComponent base;
    ComponentUpdateFunc onFinish;
    f32 offset;
    f32 velocity;
    f32 accel;
    u8 animType;
    u8 timer;
    u8 delay;
    u8 direction;
} AnimatedComponent;

typedef struct {
    MenuComponent base;
    ComponentUpdateFunc onFinish;
    u8 curAlpha;
    u8 targetAlpha;
    u8 dAlpha;
    u8 color[3];
    u8 width;
    u8 height;
} RectComponent;

typedef struct {
    MenuComponent base;
    u8 alpha;
    u8 width;
    u8 height;
    u8 corner;
} BoxComponent;

typedef struct {
    MenuComponent base;
    s16 rot;
    f32 xScale;
    f32 yScale;
} MatrixComponent;

typedef struct PageHandlerComponent PageHandlerComponent;
typedef FrameComponent *(*PageCreator)(PageHandlerComponent *ph, s32 index);
struct PageHandlerComponent {
    MenuComponent base;
    PageCreator pageCreator;
    ScrollParams scroll;
    ComponentID currentPage;
    ComponentID oldPage;
    u16 direction:1;
    u16 activeOnScroll:1;
    u16 input:4;
    u16 frames:4;
    u8 index;
};

typedef struct {
    MenuComponent base;
    ScrollParams scroll;
    SelectorStrings string;
    ComponentID original;
    u8 selectorType;
} PageTitleComponent;

typedef struct {
    MenuComponent base;
    u8 count;
    u8 index;
    u8 dir;
    // Sublist fields
    u8 indexOffset;
    ComponentID pageHandler;
    u8 isSublist:1;
    u8 input:4;
    u8 direction:1;
} ListComponent;

typedef struct {
    MenuComponent base;
    u8 disabled;
    s8 offset;
    u8 index;
} ListItemComponent;

typedef struct Selector2DComponent Selector2DComponent;
typedef void (*Selector2DRenderFunc)(Selector2DComponent *m, s16 x, s16 y, u8 column, u8 row, int selected);
typedef void (*Selector2DUpdateFunc)(Selector2DComponent *m, u8 column, u8 row);
struct Selector2DComponent {
    MenuComponent base;
    Selector2DRenderFunc render;
    Selector2DUpdateFunc update;
    u8 columns;
    u8 rows;
    u8 index;
    u8 count;
};

typedef struct {
    MenuComponent base;
    char *buf;
    ComponentID text;
    u8 maxLength;
    u8 isRestricted:1; // Filename restrictions
} KeyboardComponent;

typedef struct {
    MenuComponent base;
    s16 *value;
    s16 max;
    u8 symbol;
    u8 align;
} CounterComponent;

enum MenuComponents {
    MENU_NONE = 0,
    MENU_FRAME,
    MENU_TEXT,
    MENU_LIST,
    MENU_LISTITEM,
    MENU_SELECTOR,
    MENU_DYNAMIC,
    MENU_ANIMATED,
    MENU_RECT,
    MENU_BOX,
    MENU_MATRIX,
    MENU_PAGE_HANDLER,
    MENU_PAGE_TITLE,
    MENU_SELECTOR_2D,
    MENU_KEYBOARD,
    MENU_COUNTER,
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
    PageTitleComponent pageTitle;
    MatrixComponent matrix;
    RectComponent rect;
    BoxComponent box;
    Selector2DComponent selector2D;
    KeyboardComponent keyboard;
    CounterComponent counter;
};

extern union MenuComponentData menu_pool[MENU_POOL_SIZE];
extern FrameComponent *gMenuRoot;

void menu_text_display(char *str, s16 x, s16 y, u8 color, u8 align, u8 alpha);
void menu_update_joystick(void);
void *alloc_component(void *parent, u8 type);
void component_set_pos(void *m, s16 x, s16 y);
void dealloc_component(ComponentID id);
void render_component(MenuComponent *m, s16 x, s16 y);

ALWAYS_INLINE void *get_component(int id) {
    return &menu_pool[id-1];
}
ALWAYS_INLINE u8 get_id(void *m) {
    return ((uintptr_t)(m - (void *)&menu_pool[0])) / sizeof(union MenuComponentData) + 1;
}
ALWAYS_INLINE void *get_parent(void *m) {
    return get_component(((MenuComponent *)m)->parent);
}
ALWAYS_INLINE void *get_child(void *parent) {
    MenuComponent *p = parent;
    return p->child ? get_component(p->child) : NULL;
}

ALWAYS_INLINE void render_child(MenuComponent *m, s16 x, s16 y) {
    if (m->child) {
        render_component(get_component(m->child), x, y);
    }
}

void *get_child_of_type(void *parent, u8 type, u8 index);

FrameComponent       *init_frame_component(void *parent);
FrameComponent       *init_dynamic_component(void *parent, ComponentRenderFunc render);
ListComponent        *init_list(void *parent, int direction, int input);
ListComponent        *init_sublist(void *parent, ComponentID ph, u8 indexOffset);
TextComponent        *init_text_component(void *parent, s16 x, s16 y, char *text, u8 align, u8 color);
TextComponent        *init_text_button(void *parent, s16 x, s16 y, char *text, u8 align, ComponentUpdateFunc onClick, int onClickArg);
MatrixComponent      *init_matrix_component(void *parent, s16 rot, f32 xScale, f32 yScale);
RectComponent        *init_rect_component(void *parent, u8 alpha, s16 x, s16 y, u8 width, u8 height);
BoxComponent         *init_box_component(void *parent, s16 x, s16 y, u8 width, u8 height, u8 alpha, u8 corner);
PageHandlerComponent *init_page_handler(void *parent, PageCreator pageCreator, u8 count, u16 width);
PageTitleComponent   *init_page_title_array(void *parent, void *p, s16 x, s16 y, s16 width, char **array);
PageTitleComponent   *init_page_title_func(void *parent, void *original, s16 x, s16 y, s16 width, SelectorStringFunc func);
SelectorComponent    *init_array_selector(void *parent, u8 *value, u8 width, u8 count, char **array, ComponentUpdateFunc onChange);
SelectorComponent    *init_func_selector(void *parent, u8 *value, u8 width, u8 count, SelectorStringFunc func, ComponentUpdateFunc onChange);
Selector2DComponent  *init_selector_2d_component(void *parent, s16 x, s16 y, u8 columns, u8 count, Selector2DRenderFunc *render, Selector2DUpdateFunc *update);
KeyboardComponent    *init_keyboard_component(void *parent, s16 x, s16 y, char *buf, TextComponent *t, u8 maxLength, int isRestricted);
CounterComponent     *init_counter_component(void *parent, s16 x, s16 y, u8 symbol, s16 *value, s16 max, int align);

ListItemComponent *component_list_append(ListComponent *l, void *m, s16 x, s16 y);
ListItemComponent *component_list_get(ListComponent *l, u8 index);

void component_animate_ease_in(AnimatedComponent *a, f32 offset, f32 multiplier, u8 direction);
void component_animate_ease_out(AnimatedComponent *a, f32 accel, u8 timer, u8 direction);
void component_animate_bounce_in(AnimatedComponent *a, f32 offset, f32 accel, f32 initialVel, u8 direction);
void component_animate_bounce_out(AnimatedComponent *a, f32 accel, f32 initialVel, u8 timer, u8 direction);
void component_animate_linear(AnimatedComponent *a, f32 offset, f32 target, f32 vel, u8 direction);
void component_rect_do_fade(RectComponent *rc, u8 targetAlpha, u8 dAlpha, ComponentUpdateFunc onFinish);
void listitem_render_triangle(MenuComponent *m, s16 x, s16 y);

void reset_menu(void);
void render_menu(void);
