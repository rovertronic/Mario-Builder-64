#include "menu_engine.h"

char *mb64_tips[] = {
    "Tip: Use D-Pad ^ to flip certain tiles like slopes or slabs!",
    "Tip: Use D-Pad | to change the camera's\n   zoom level while building!",
    "Tip: Press \x15 and \x13 at the same time to copy\n the tile or object the cursor is on!",
    "Tip: You can place objects or tiles inside\n   water blocks to submerge them!",
    "Tip: The thin Iron Meshes can be used to create walls\n   that require a Vanish Cap to pass through.",
    "Tip: Mesh materials can be used as both\n   hangable ceilings and Vanish Cap walls.",
    "Tip: Objects such as coin formations or bosses\n   can use up the object limit rather quickly.",
    "Tip: The available items inside an Item Box will change\n   depending on the chosen gamemode.",
    "Tip: Thwomps and Grindels will use the height they are\n   placed at as the peak of their movement.",
    "Tip: If you hit the vertex limit, use Cull Markers\n   wherever you can to optimise your level!",
    "Tip: If you want to rename your level, simply rename the\n   .mb64 file itself.",
    "Tip: Entering and exiting water from the side with a shell\n   will let you transition between riding and swimming!",
    "Tip: Entering a famous code while on a certain menu\n   might reward you with a little surprise...",
    "Tip: Transparent materials such as water, flames or ice\n   can look strange when layered together, so watch out.",
    "Tip: Using the Cursed Mirror gamemode will let you use a\n   bunch of new enemies and collectible badges!",
    "Tip: Remember to use the Set Level Thumbnail option to\n   set a thumbnail before publishing your level!",
    "Tip: You can place stars and other objects inside of\n   enemies or boxes as loot!",
    "Tip: Make sure to place a star or other reward inside\n   any bosses you place, otherwise they'll drop nothing!",
    "Tip: Placing Wooden Platforms on top of each other\n   will cause them to combine into one object.",
    "Tip: Many objects and enemies can be placed in the\n   same tile as coin rings or On-Off Blocks.",
    "Tip: On-Off Switches and coins can be placed inside\n   enemies to appear when they are killed!",
    "Tip: The Reinforced Box will not break unless hit by\n a Bob-omb, Bullet Bill, or other destructive object!",
// BTCM
    "Tip: The Double Time badge extends the timer of\n   hidden corkboxes and blue coin switches!",
    "Tip: Badges that the player collects will be kept\n   as permanent collectibles even after death.",
    "Tip: You can use the Burden badges as a punishment\n   when touched, or an optional challenge!",
    "Tip: Green Coins heal the player for 4 HP when collected,\n   or fully with the Heal Plus badge.",
    "Tip: Badges can be placed inside enemies or boxes!",
};
#define NUM_BTCM_TIPS 5

// System for a temporary message in the top left of the screen
// Used for errors and editor tips

AnimatedComponent *sActiveMessage = NULL;
int sMessageTimer = 0;

void move_message(void) {
    component_animate_ease_out(sActiveMessage, 0.2f, 30, DIR_VERTICAL);
    sActiveMessage->delay = sMessageTimer;
}

void hide_message(void) {
    if (sActiveMessage) {
        dealloc_component(get_id(sActiveMessage));
        sActiveMessage = NULL;
    }
}

// Generic error message
void show_message(char *msg, int color, int timer, int delay) {
    if (sActiveMessage) {
        TextComponent *t = get_child(sActiveMessage);
        t->text = msg;
    } else {
        sActiveMessage = alloc_component(gMenuRoot, MENU_ANIMATED);
        init_text_component(sActiveMessage, 15, 215, msg, TEXT_LEFT, color);
    }
    component_animate_ease_in(sActiveMessage, 50.f, 0.4f, DIR_VERTICAL);
    sActiveMessage->onFinish = move_message;
    sActiveMessage->delay = delay;
    sMessageTimer = timer;
}

void show_error(char *msg) {
    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
    show_message(msg, TEXT_RED, 90, 0);
}

void show_tip(void) {
    s32 count = ARRAY_COUNT(mb64_tips);
    if (mb64_lopt_game != MB64_GAME_BTCM) count -= NUM_BTCM_TIPS;
    show_message(mb64_tips[(s32)(random_float() * count)], TEXT_WHITE, 180, 30);
}

// Coord display

AnimatedComponent *sCoordDisplay = NULL;

char coord_display_buf[20];
void update_coord_display(UNUSED MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    sprintf(coord_display_buf, "%d, %d, %d", mb64_cursor_pos[0], mb64_cursor_pos[1], mb64_cursor_pos[2]);
}

void show_coord_display(void) {
    component_animate_ease_in(sCoordDisplay, 50.f, 0.4f, DIR_VERTICAL);
}

void hide_coord_display(void) {
    // If coords are still hidden, don't try to animate them and keep them hidden offscreen
    if (sCoordDisplay->delay) {
        sCoordDisplay->timer = 0;
        sCoordDisplay->offset = 50.f;
        return;
    }
    component_animate_ease_out(sCoordDisplay, 0.4f, 30, DIR_VERTICAL);
}

void create_coord_display(void) {
    sCoordDisplay = alloc_component(gMenuRoot, MENU_ANIMATED);
    TextComponent *t = init_text_component(sCoordDisplay, SCREEN_WIDTH - 15, 215, coord_display_buf, TEXT_RIGHT, TEXT_WHITE);
    t->base.prerender = update_coord_display;
    show_coord_display();
    sCoordDisplay->delay = 255;
}

// Control text for trajectories and screenshots

TextComponent *sYellowText = NULL;
int sYellowTextVisible = TRUE;

void yellow_text_set_visibility(void) {
    if (gPlayer1Controller->buttonPressed & Z_TRIG) {
        sYellowTextVisible ^= 1;
    }
    int visible = sYellowTextVisible && !mb64_freecam_snap;
    sYellowText->alpha = visible ? 255 : 0;
}

void destroy_yellow_text(void) {
    dealloc_component(get_id(sYellowText));
    sYellowText = NULL;
}

void create_yellow_text(char *msg) {
    if (sYellowText) destroy_yellow_text();
    sYellowText = init_text_component(gMenuRoot, 15, 215, msg, TEXT_LEFT, TEXT_YELLOW);
    sYellowText->base.prerender = yellow_text_set_visibility;
    sYellowTextVisible = TRUE;
    hide_message();
}

void reset_misc_menu_state(void) {
    sActiveMessage = NULL;
    sCoordDisplay = NULL;
    sYellowText = NULL;
}
