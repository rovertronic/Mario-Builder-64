#include "menu_engine.h"

#include "menu.h"
#include "game/level_update.h"

#include "actors/bigpainting2/header.h"
#include "main.h"
#include "gfx.h"

MenuComponent *settingsRoot = NULL;

u8 gSettingsPage = 0;
u8 gSettingsCustomOpen = 0;

char *settings_menu_pages[] = {
    "Environment",
    "Level Boundary",
    "Music",
    "Miscellaneous",
    "System",
};

void component_level_portrait_render(MenuComponent *m, s16 x, s16 y) {
    x += m->xpos;
    y += m->ypos;

    create_dl_translation_matrix(MENU_MTX_PUSH, x, y, 0);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    gSPDisplayList(gDisplayListHead++, &bigpainting2_bigpainting2_mesh);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

// Environment page

char *mb64_theme_string_table[] = {
    "Generic",
    "Shifting Sand Land",
    "Red Hot Reservoir",
    "Hazy Maze Cave",
    "Peach's Castle",
    "Virtuaplex",
    "Snowy Palace",
    "Big Boo's Haunt",
    "Jolly Roger Bay",
    "Retroland",
    "Custom",
    "Minecraft",
};

ListComponent *gEnvironmentList;
void theme_changed(UNUSED SelectorComponent *s) {
    AnimatedComponent *customtheme = get_child(component_list_get(gEnvironmentList, 3));

    if (mb64_lopt_theme == MB64_THEME_CUSTOM) {
        // Enable custom theme button
        component_animate_ease_in(customtheme, -30.f, 0.4f, DIR_VERTICAL);
        gEnvironmentList->count = 4;
    } else if (gEnvironmentList->count == 4) {
        // Disable custom theme button
        component_animate_ease_out(customtheme, -2.f, 10, DIR_VERTICAL);
        gEnvironmentList->count = 3;
    }

    reload_theme();
} 

char *mb64_bg_string_table[] = {
    "Ocean Hills",
    "Cloudy Sky",
    "Fiery Sky",
    "Green Cave",
    "Haunted Forest", // 4 - doesn't generate black chasm
    "Ice Mountains",
    "Desert Pyramids",
    "Underwater City",
    "Pink Sky",
    "None", // 9 - doesn't generate black chasm
};

char *mb64_envfx_string_table[] = {
    "None",
    "Ashes",
    "Snow",
    "Rain",
    "Sandstorm",
};

// Boundary page

char *mb64_bound_string_table[] = {
    "Void",
    "Plain",
    "Valley",
    "Chasm",
    "Plateau",
    "Interior",
};

char *mb64_get_floor_name(s32 index, UNUSED char *buffer) {
    return TILE_MATDEF(index).name;
}

char *mb64_get_boundaryheight_name(s32 index, char *buffer) {
    sprintf(buffer, "Y: %d", index);
    return buffer;
}

ListComponent *gBoundaryList;
void check_boundary_list_disable(void) {
    component_list_get(gBoundaryList, 2)->disabled = !(mb64_boundary_table[mb64_lopt_boundary] & MB64_BOUNDARY_INNER_WALLS);
    component_list_get(gBoundaryList, 1)->disabled = (mb64_lopt_boundary == 0);
}
void settings_boundary_changed(UNUSED SelectorComponent *s) {
    check_boundary_list_disable();
    reload_boundary_and_gfx();
}

// Music page

char *mb64_music_type_string_table[] = {
    "Level",
    "Koopa Race",
    "Bossfight",
};

char *mb64_music_album_string_table[] = {
    "Super Mario 64 OST",
    "Beyond the Cursed Mirror OST",
    "ROM Hack Music Ports",
    "Retro 2D Mario Music"
};

char *mb64_music_vanilla_string_table[] = {
    "Bob-omb Battlefield",
    "Slider",
    "Dire, Dire Docks",
    "Dire, Dire Docks (Underwater)",
    "Lethal Lava Land",
    "Cool, Cool Mountain",
    "Big Boo's Haunt",
    "Hazy Maze Cave",
    "Hazy Maze Cave (Haze)",
    "Koopa's Road",
    "Stage Boss",
    "Koopa's Theme",
    "Ultimate Koopa",
    "Inside the Castle Walls",
};

char *mb64_music_btcm_string_table[] = {
    "Cosmic Castle",
    "Red-Hot Reservoir",
    "Lonely Floating Farm",
    "Jurassic Savanna",
    "The Phantom Strider",
    "Virtuaplex",
    "Immense Residence",
    "Thwomp Towers",
    "Cursed Boss",
    "Road To The Boss",
    "Urbowser",
    "The Show's Finale",
    "Parasite Moon",
    "AGAMEMNON",
};

char *mb64_music_romhack_string_table[] = {
    "Bianco Hills (Super Mario Sunshine)",
    "Sky and Sea (Super Mario Sunshine)",
    "Secret Course (Super Mario Sunshine)",
    "Comet Observatory (Mario Galaxy)",
    "Buoy Base Galaxy (Mario Galaxy)",
    "Battlerock Galaxy (Mario Galaxy)",
    "Ghostly Galaxy (Mario Galaxy)",
    "Purple Comet (Mario Galaxy)",
    "Honeybloom Galaxy (Mario Galaxy 2)",
    "Piranha Creeper Creek (3D World)",
    "Desert (New Super Mario Bros.)",

    "Koopa Troopa Beach (Mario Kart 64)",
    "Frappe Snowland (Mario Kart 64)",
    "Bowser's Castle (Mario Kart 64)",
    "Rainbow Road (Mario Kart 64)",
    "Waluigi Pinball (Mario Kart DS)",
    "Rainbow Road (Mario Kart 8)",

    "Mario's Pad (Super Mario RPG)",
    "Nimbus Land (Super Mario RPG)",
    "Forest Maze (Super Mario RPG)",
    "Sunken Ship (Super Mario RPG)",

    "Dry Dry Desert (Paper Mario 64)",
    "Forever Forest (Paper Mario 64)",
    "Petal Meadows (Paper Mario: TTYD)",
    "Riddle Tower (Paper Mario: TTYD)",
    "Rogueport Sewers (Paper Mario: TTYD)",
    "X-Naut Fortress (Paper Mario: TTYD)",
    "Flipside (Super Paper Mario)",
    "Lineland Road (Super Paper Mario)",
    "Sammer Kingdom (Super Paper Mario)",
    "Floro Caverns (Super Paper Mario)",
    "Overthere Stair (Super Paper Mario)",

    "Yoshi's Tropical Island (Mario Party)",
    "Rainbow Castle (Mario Party)",
    "Behind Yoshi Village (Partners in Time)",
    "Gritzy Desert (Partners in Time)",
    "Bumpsy Plains (Bowser's Inside Story)",
    "Deep Castle (Bowser's Inside Story)",

    "Overworld (Yoshi's Island)",
    "Underground (Yoshi's Island)",
    "Title (Yoshi's Story)",

    "Kokiri Forest (Ocarina of Time)",
    "Lost Woods (Ocarina of Time)",
    "Gerudo Valley (Ocarina of Time)",
    "Stone Tower Temple (Majora's Mask)",
    "Outset Island (Wind Waker)",
    "Lake Hylia (Twilight Princess)",
    "Gerudo Desert (Twilight Princess)",
    "Skyloft (Skyward Sword)",

    "Frantic Factory (Donkey Kong 64)",
    "Hideout Helm (Donkey Kong 64)",
    "Creepy Castle (Donkey Kong 64)",
    "Gloomy Galleon (Donkey Kong 64)",
    "Fungi Forest (Donkey Kong 64)",
    "Crystal Caves (Donkey Kong 64)",
    "Angry Aztec (Donkey Kong 64)",
    "In a Snow-Bound Land (DKC 2)",

    "Bubblegloop Swamp (Banjo-Kazooie)",
    "Freezeezy Peak (Banjo-Kazooie)",
    "Gobi's Valley (Banjo-Kazooie)",

    "Factory Inspection (Kirby 64)",
    "Green Garden (Bomberman 64)",
    "Black Fortress (Bomberman 64)",
    "Windy Hill (Sonic Adventure)",
    "Sky Tower (Pokemon Mystery Dungeon)",
    "Youkai Mountain (Touhou 10)",
    "Forest Temple (Final Fantasy VII)",
    "Band Land (Rayman)",
};

char *mb64_music_retro_string_table[] = {
    "Overworld (Super Mario Bros.)",
    "Castle Mix (Super Mario Bros.)",
    "Overworld (Super Mario Bros. 2)",
    "Overworld Mix (Super Mario Bros. 3)",
    "Fortress (Super Mario Bros. 3)",
    "Athletic (Super Mario World)",
    "Castle (Super Mario World)",
};

char **mb64_music_string_tables[] = {
    mb64_music_vanilla_string_table,
    mb64_music_btcm_string_table,
    mb64_music_romhack_string_table,
    mb64_music_retro_string_table,
};

u8 mb64_music_table_lengths[] = {
    ARRAY_COUNT(mb64_music_vanilla_string_table),
    ARRAY_COUNT(mb64_music_btcm_string_table),
    ARRAY_COUNT(mb64_music_romhack_string_table),
    ARRAY_COUNT(mb64_music_retro_string_table),
};

// Set mb64_lopt_seq_album and mb64_lopt_seq_song based on mb64_lopt_seq
void set_album_and_song_from_seq(u8 index) {
    u32 song = mb64_lopt_seq[index];
    u32 i = 0;
    do {
        if (song < mb64_music_table_lengths[i]) {
            mb64_lopt_seq_album = i;
            mb64_lopt_seq_song = song;
            return;
        }
        song -= mb64_music_table_lengths[i];
    } while (++i < ARRAY_COUNT(mb64_music_album_string_table));
}
// Set mb64_lopt_seq from mb64_lopt_seq_album and mb64_lopt_seq_song
void set_seq_from_album_and_song(u8 index) {
    mb64_lopt_seq[index] = 0;
    u32 i = 0;
    do {
        if (i == mb64_lopt_seq_album) {
            mb64_lopt_seq[index] += mb64_lopt_seq_song;
            return;
        }
        mb64_lopt_seq[index] += mb64_music_table_lengths[i];
    } while (++i < ARRAY_COUNT(mb64_music_album_string_table));
}

SelectorComponent *gSongSelector;
void song_changed() {
    set_seq_from_album_and_song(mb64_lopt_seq_seqtype);
    stop_background_music(get_current_background_music());
    play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, seq_musicmenu_array[mb64_lopt_seq[mb64_lopt_seq_seqtype]]), 0);
}
void music_type_changed(UNUSED SelectorComponent *s) {
    set_album_and_song_from_seq(mb64_lopt_seq_seqtype);
    gSongSelector->string.array = mb64_music_string_tables[mb64_lopt_seq_album];
    gSongSelector->scroll.count = mb64_music_table_lengths[mb64_lopt_seq_album];
    song_changed();
}
void music_category_changed(UNUSED SelectorComponent *s) {
    mb64_lopt_seq_song = 0;
    gSongSelector->string.array = mb64_music_string_tables[mb64_lopt_seq_album];
    gSongSelector->scroll.count = mb64_music_table_lengths[mb64_lopt_seq_album];
    song_changed();
}

// Miscellaneous page

char *mb64_get_coinstar_str(s32 index, char *buffer) {
    if (index == 0) {
        return "Disabled";
    }
    sprintf(buffer, "%d Coins", index*20);
    return buffer;
}
char *mb64_get_waterlevel_name(s32 index, char *buffer) {
    if (index == 0) {
        return "Disabled";
    }
    sprintf(buffer, "Y: %d", index);
    return buffer;
}


char *mb64_costume_string_table[] = {
    "Mario",
    "Fire Mario",
    "Glitchy",
    "Luigi",
    "Wario",
    "Disco Mario",
    "Undead Pirate",
    "Mocap Mario",
    "Darius",
    "Butler Mario",
    "Retro Mario",
    "Thwompio",
    "Builder Mario",
    "Showrunner",
    "Cosmic Phantasm",
};


// System page

void settings_save_and_quit(void) {
    if (gSDCard) {
        save_level();
        play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
    }
    set_page_to_level_list();
    fade_into_special_warp(WARP_SPECIAL_MARIO_HEAD_REGULAR, 0); // reset game
}

void settings_play_level(void) {
    if (gSDCard) {
        save_level();
    }
    mb64_target_mode = MB64_MODE_PLAY;
    mb64_level_action = MB64_LA_TEST_LEVEL;
    reset_play_state();
    level_trigger_warp(gMarioState, WARP_OP_LOOK_UP);
    sSourceWarpNodeId = 0x0A;
    play_sound(SOUND_MENU_STAR_SOUND_LETS_A_GO, gGlobalSoundSource);
}

void settings_take_screenshot(void) {
    freecam_camera_init();
    mb64_menu_state = MB64_MAKE_SCREENSHOT;
    create_yellow_text("Analog Stick: Look around\n\x14 ^ / |: Move forward / backward\n\x14 < / >: Move sideways\n\x15 / \x13: Zoom\n\x12: Toggle Help\nSTART: Take screenshot\n\x11: Exit");
    play_sound(SOUND_MENU_CLICK_CHANGE_VIEW, gGlobalSoundSource);
    dealloc_component(get_id(settingsRoot));
    settingsRoot = NULL;
}


// Custom theme page

// FrameComponent params for storing intermediate custom theme variables
#define POLE_PAGE NUM_MATERIALS_PER_THEME
#define FENCE_PAGE (NUM_MATERIALS_PER_THEME + 1)
#define BARS_PAGE (NUM_MATERIALS_PER_THEME + 2)
#define WATER_PAGE (NUM_MATERIALS_PER_THEME + 3)

#define matCategory params[0].asBytes[0]
#define matIndex params[0].asBytes[1]
#define topmatCategory params[0].asBytes[2]
#define topmatIndex params[0].asBytes[3]
#define pageIndex params[1].asInt

void component_block_preview_render(MenuComponent *m, s16 x, s16 y) {
    FrameComponent *frame = get_parent(m);
    x += m->xpos;
    y += m->ypos;

    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    custom_theme_draw_block(x - SCREEN_WIDTH/2, y - SCREEN_HEIGHT/2, frame->pageIndex);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
}

char *get_custom_theme_page_name(s32 index, UNUSED char *buf) {
    if (index < 10) return mb64_theme_table[MB64_THEME_CUSTOM].mats[index].name;
    switch (index - 10) {
        case 0: return "Poles";
        case 1: return "Fences";
        case 2: return "Iron Meshes";
        case 3: return "Water";
    }
    return NULL;
}

u8 mb64_matlist[] = {
    MB64_MATLIST_START,
    MB64_MATLIST_TERRAIN_END,
    MB64_MATLIST_STONE_END,
    MB64_MATLIST_BRICKS_END,
    MB64_MATLIST_TILES_END,
    MB64_MATLIST_CUTSTONE_END,
    MB64_MATLIST_WOOD_END,
    MB64_MATLIST_METAL_END,
    MB64_MATLIST_BUILDING_END,
    MB64_MATLIST_HAZARD_END,
    MB64_MATLIST_END,
};

char *mb64_matlist_names[] = {
    "Terrain",
    "Stone",
    "Bricks",
    "Tiling",
    "Cut Stone",
    "Wood",
    "Metal",
    "Other",
    "Hazards",
    "Transparent",
};

char *mb64_fence_names[] = {
    "Wooden (1)",
    "Wooden (2)",
    "Wooden (3)",
    "Barbed Wire",
    "Metal",
    "Netting",
    "Castle",
    "Stanchion",
    "Mansion",
    "Rope",
    "Snowy (1)",
    "Snowy (2)",
};

char *mb64_bar_names[] = {
    "Grille",
    "Mesh",
    "Fine Mesh",
    "Red Grille",
    "Red Mesh",
    "Pink Mesh",
    "Clock Grille",
    "Desert Grille",
    "Cage Bars",
};

char *mb64_water_names[] = {
    "Default",
    "Swampy",
};

char *mb64_slipperiness_strs[] = {
    /* SURFACE_CLASS_DEFAULT */        "(Smooth)",
    /* SURFACE_CLASS_VERY_SLIPPERY */  "(Slippery)",
    /* SURFACE_CLASS_SLIPPERY */       "(Slippery)",
    /* SURFACE_CLASS_NOT_SLIPPERY */   "(Walkable)",
    /* Hazard */                       "(Hazardous)",
};
u8 mb64_slipperiness_clrs[] = {
    TEXT_YELLOW,
    TEXT_LIGHTBLUE,
    TEXT_LIGHTBLUE,
    TEXT_WHITE,
    TEXT_RED,
};

void get_category_and_index_from_mat(u8 *category, u8 *index, u8 mat) {
    u8 i = 1;
    do {
        if (mat < mb64_matlist[i]) {
            *category = i-1;
            *index = mat - mb64_matlist[i-1];
            return;
        }
    } while (++i <= MB64_MATLIST_END);
}
void set_mat_from_category_and_index(u8 category, u8 index, u8 *mat) {
    *mat = mb64_matlist[category] + index;
}

int get_category_size(u8 category) {
    return mb64_matlist[category+1] - mb64_matlist[category];
}

// This is a prerender function called before the frame for the custom theme page.
// Sets global variables so that the material selector can access the current category.
int gCurrMatCategory = 0;
int gCurrTopmatCategory = 0;
void custom_theme_page_get_categories(MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    FrameComponent *f = (FrameComponent *)m;
    gCurrMatCategory = f->matCategory;
    gCurrTopmatCategory = f->topmatCategory;
}

void custom_theme_set_floor_class_name(TextComponent *t, int index) {
    s32 col;
    if (mb64_curr_custom_theme.topmatsEnabled[index]) {
        col = mb64_mat_table[mb64_curr_custom_theme.topmats[index]].col;
    } else {
        col = mb64_mat_table[mb64_curr_custom_theme.mats[index]].col;
    }
    s32 class;
    if (SURFACE_IS_BURNING(col) || SURFACE_IS_QUICKSAND(col)) class = 4;
    else class = get_floor_class(col);

    t->text = mb64_slipperiness_strs[class];
    t->color = mb64_slipperiness_clrs[class];
}

void custom_theme_update_material(FrameComponent *f) {
    int index = f->pageIndex;
    switch (index) {
        case POLE_PAGE:
            set_mat_from_category_and_index(f->matCategory, f->matIndex, &mb64_curr_custom_theme.pole);
            break;
        default:
            set_mat_from_category_and_index(f->matCategory, f->matIndex, &mb64_curr_custom_theme.mats[index]);
            set_mat_from_category_and_index(f->topmatCategory, f->topmatIndex, &mb64_curr_custom_theme.topmats[index]);
            custom_theme_set_floor_class_name(get_child_of_type(f, MENU_TEXT, 0), index);
    }
}

char *material_selector_get_mat_name(s32 index, UNUSED char *buffer) {
    return mb64_mat_table[mb64_matlist[gCurrMatCategory] + index].name;
}
char *material_selector_get_topmat_name(s32 index, UNUSED char *buffer) {
    return mb64_mat_table[mb64_matlist[gCurrTopmatCategory] + index].name;
}

char *topmatToggleText[2] = {
    "Enable Top Material...",
    "Disable Top Material...",
};

void settings_custom_toggle_topmat_enabled(TextComponent *b) {
    ListComponent *l = get_parent(get_parent(b)); // Assumes List -> ListItem -> Text
    FrameComponent *f = get_parent(l);
    u8 topmatEnabled = mb64_curr_custom_theme.topmatsEnabled[f->pageIndex];

    topmatEnabled ^= 1;
    component_list_get(l, 3)->disabled = !topmatEnabled;
    component_list_get(l, 4)->disabled = !topmatEnabled;
    b->text = topmatToggleText[topmatEnabled];

    mb64_curr_custom_theme.topmatsEnabled[f->pageIndex] = topmatEnabled;
}

// Update custom theme material when category or material is changed
void material_changed(SelectorComponent *s) {
    FrameComponent *f = get_parent(get_parent(get_parent(s))); // Assumes Frame -> List -> ListItem -> Selector
    custom_theme_update_material(f);
}
// Grab the following item in the list to find the material selector component.
// Update its size and then update the material as well
void category_changed(SelectorComponent *s) {
    ListItemComponent *li = get_parent(s);
    ListItemComponent *mli = get_component(li->base.next); // hacky way to get the next item in the list, which is the material selector
    SelectorComponent *s2 = get_child_of_type(mli, MENU_SELECTOR, 0);
    s2->scroll.count = get_category_size(*s->value);
    *s2->value = 0;
    FrameComponent *f = get_parent(get_parent(li)); // Assumes Frame -> List -> ListItem
    custom_theme_update_material(f);
}

void settings_custom_create_material_selector(ListComponent *list, u8 i, u8 *category, u8 *index, u8 isTopmat) {
    TextComponent *t1 = init_text_component(NULL, 0, 0, "Category:", TEXT_LEFT, 0);
    ListItemComponent *li1 = component_list_append(list, t1, -140, -i * 16);
    TextComponent *t2 = init_text_component(NULL, 0, 0, "Material:", TEXT_LEFT, 0);
    ListItemComponent *li2 = component_list_append(list, t2, -140, -(i + 1) * 16);

    SelectorComponent *selector = init_array_selector(li1, category, 45, ARRAY_COUNT(mb64_matlist_names),
        mb64_matlist_names, category_changed);
    component_set_pos(selector, 130, 0);
    SelectorComponent *selector2 = init_func_selector(li2, index, 45, get_category_size(*category),
        (isTopmat ? material_selector_get_topmat_name : material_selector_get_mat_name), material_changed);
    component_set_pos(selector2, 130, 0);
}

void settings_custom_create_other_selector(ListComponent *list, u8 i, char *text, u8 *var, char **array, u8 count) {
    TextComponent *t = init_text_component(NULL, 0, 0, text, TEXT_LEFT, 0);
    ListItemComponent *li = component_list_append(list, t, -140, -i * 16);

    SelectorComponent *selector = init_array_selector(li, var, 45, count, array, NULL);
    component_set_pos(selector, 130, 0);
}


// Main stuff

void settings_create_array_selector(ListComponent *list, u8 index, char *text, u8 *var, char **array, u8 count, ComponentUpdateFunc func) {
    TextComponent *t = init_text_component(NULL, 0, 0, text, TEXT_LEFT, 0);
    ListItemComponent *li = component_list_append(list, t, -100, -index * 16);

    SelectorComponent *selector = init_array_selector(li, var, 50, count, array, func);
    component_set_pos(selector, 140, 0);
}

void settings_create_func_selector(ListComponent *list, u8 index, char *text, u8 *var, SelectorStringFunc func, u8 count, ComponentUpdateFunc onChange) {
    TextComponent *t = init_text_component(NULL, 0, 0, text, TEXT_LEFT, 0);
    ListItemComponent *li = component_list_append(list, t, -100, -index * 16);

    SelectorComponent *selector = init_func_selector(li, var, 50, count, func, onChange);
    component_set_pos(selector, 140, 0);
}

SelectorComponent *settings_create_music_selector(ListComponent *list, u8 index, char *text, u8 *var, char **array, u8 count, ComponentUpdateFunc func) {
    TextComponent *t = init_text_component(NULL, 0, 0, text, TEXT_LEFT, 0);
    ListItemComponent *li = component_list_append(list, t, -130, -index * 22);

    SelectorComponent *selector = init_array_selector(li, var, 95, count, array, func);
    component_set_pos(selector, 160, 0);
    return selector;
}

void settings_create_button(ListComponent *list, u8 index, char *text, ComponentUpdateFunc func) {
    TextComponent *t = init_text_button(NULL, 0, 0, text, TEXT_CENTER, func, 0);
    component_list_append(list, t, 0, -index * 16);
}

FrameComponent *custom_theme_page_creator(UNUSED PageHandlerComponent *unusedph, s32 index) {
    FrameComponent *frame = init_frame_component(NULL);
    ListComponent *list = init_list(frame, DIR_VERTICAL, MENU_INPUT_JOYSTICK);

    switch (index) {
        case POLE_PAGE:
            get_category_and_index_from_mat(&frame->matCategory, &frame->matIndex, mb64_curr_custom_theme.pole);
            settings_custom_create_material_selector(list, 0, &frame->matCategory, &frame->matIndex, 0);
            break;
        case FENCE_PAGE:
            settings_custom_create_other_selector(list, 1, "Fence:", &mb64_curr_custom_theme.fence, mb64_fence_names, ARRAY_COUNT(mb64_fence_names));
            break;
        case BARS_PAGE:
            settings_custom_create_other_selector(list, 1, "Iron Mesh:", &mb64_curr_custom_theme.bars, mb64_bar_names, ARRAY_COUNT(mb64_bar_names));
            break;
        case WATER_PAGE:
            settings_custom_create_other_selector(list, 1, "Water:", &mb64_curr_custom_theme.water, mb64_water_names, ARRAY_COUNT(mb64_water_names));
            break;
        default:
            get_category_and_index_from_mat(&frame->matCategory, &frame->matIndex, mb64_curr_custom_theme.mats[index]);
            settings_custom_create_material_selector(list, 0, &frame->matCategory, &frame->matIndex, 0);
            
            TextComponent *t = init_text_button(NULL, 0, 0, topmatToggleText[1], TEXT_CENTER, settings_custom_toggle_topmat_enabled, 0);
            component_list_append(list, t, -50, -32);

            get_category_and_index_from_mat(&frame->topmatCategory, &frame->topmatIndex, mb64_curr_custom_theme.topmats[index]);
            settings_custom_create_material_selector(list, 3, &frame->topmatCategory, &frame->topmatIndex, 1);

            if (!mb64_curr_custom_theme.topmatsEnabled[index]) {
                t->text = topmatToggleText[0];
                component_list_get(list, 3)->disabled = TRUE;
                component_list_get(list, 4)->disabled = TRUE;
            }

            TextComponent *class = init_text_component(frame, 100, -50, NULL, TEXT_CENTER, 0);
            custom_theme_set_floor_class_name(class, index);
            class->alpha = 150;
    }

    FrameComponent *block = init_dynamic_component(frame, component_block_preview_render);
    component_set_pos(block, 100, -20);

    frame->pageIndex = index;
    frame->base.prerender = custom_theme_page_get_categories;
    return frame;
}

void custom_theme_button_pressed(void) {
    PageHandlerComponent *ph = get_child_of_type(settingsRoot, MENU_PAGE_HANDLER, 0);
    page_handler_scroll(ph, 1);
}

char settings_stats_buf_1[20];
char settings_stats_buf_2[24];
char settings_stats_buf_3[30];
char settings_stats_buf_4[28];

u16 konami[] = {U_JPAD, U_JPAD, D_JPAD, D_JPAD, L_JPAD, R_JPAD, L_JPAD, R_JPAD, B_BUTTON, A_BUTTON, START_BUTTON};
u8 konami_index = 0;
u8 konami_disable_inputs = FALSE;
void konami_code_check(MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    if (gMenuState.inactive) {
        konami_index = 0;
        konami_disable_inputs = FALSE;
        return;
    }
    if (!mb64_lopt_secret && gPlayer1Controller->buttonPressed) {
        if (gPlayer1Controller->buttonPressed == konami[konami_index]) {
            konami_index++;
            if (konami_index >= 8) {
                konami_disable_inputs = TRUE;
            }
            if (konami_index == 11) {
                mb64_lopt_secret = TRUE;
                play_puzzle_jingle();
                konami_disable_inputs = FALSE;
                konami_index = 0;

                SelectorComponent *s = get_child_of_type(component_list_get(get_child_of_type(m, MENU_LIST, 0), 0), MENU_SELECTOR, 0);
                s->scroll.count = ARRAY_COUNT(mb64_theme_string_table);
            }
        } else {
            konami_index = 0;
            konami_disable_inputs = FALSE;
        }
    }
}

u8 gFromCustomTheme = FALSE;
FrameComponent *settings_main_page_creator(UNUSED PageHandlerComponent *unusedph, s32 index) {
    FrameComponent *frame = init_frame_component(NULL);
    ListComponent *list = init_list(frame, DIR_VERTICAL, MENU_INPUT_JOYSTICK);

    switch (index) {
        case 0: // Environment
            gEnvironmentList = list;
            int theme_count = mb64_lopt_secret ? ARRAY_COUNT(mb64_theme_string_table) : ARRAY_COUNT(mb64_theme_string_table) - 1;
            settings_create_array_selector(list, 0, "Theme:", &mb64_lopt_theme, mb64_theme_string_table, theme_count, theme_changed);
            settings_create_array_selector(list, 1, "Skybox:", &mb64_lopt_bg, mb64_bg_string_table, ARRAY_COUNT(mb64_bg_string_table), reload_bg);
            settings_create_array_selector(list, 2, "Effect:", &mb64_lopt_envfx, mb64_envfx_string_table, ARRAY_COUNT(mb64_envfx_string_table), NULL);
            
            AnimatedComponent *customtheme = alloc_component(NULL, MENU_ANIMATED);
            component_list_append(list, customtheme, 0, -58);
            customtheme->direction = DIR_VERTICAL;
            init_text_button(customtheme, 0, 0, "Edit Custom Theme...", TEXT_CENTER, custom_theme_button_pressed, 0);
            if (mb64_lopt_theme != MB64_THEME_CUSTOM) {
                customtheme->offset = -30.f;
                list->count = 3; // hack to make custom theme button unselectable without appearing disabled
            }
            if (gFromCustomTheme) {
                list->index = 3;
            }
            frame->base.prerender = konami_code_check;
            break;
        case 1: // Level Boundary
            gBoundaryList = list;
            settings_create_array_selector(list, 0, "Boundary:", &mb64_lopt_boundary, mb64_bound_string_table, ARRAY_COUNT(mb64_bound_string_table), settings_boundary_changed);
            settings_create_func_selector( list, 1, "Material:", &mb64_lopt_boundary_mat, mb64_get_floor_name, NUM_MATERIALS_PER_THEME, reload_boundary_and_gfx);
            settings_create_func_selector( list, 2, "Height:", &mb64_lopt_boundary_height, mb64_get_boundaryheight_name, 65, reload_boundary_and_gfx);
            check_boundary_list_disable();
            break;
        case 2: // Music
            set_album_and_song_from_seq(mb64_lopt_seq_seqtype);
            settings_create_music_selector(list, 0, "Type:", &mb64_lopt_seq_seqtype, mb64_music_type_string_table, ARRAY_COUNT(mb64_music_type_string_table), music_type_changed);
            settings_create_music_selector(list, 1, "Album:", &mb64_lopt_seq_album, mb64_music_album_string_table, ARRAY_COUNT(mb64_music_album_string_table), music_category_changed);
            gSongSelector = settings_create_music_selector(list, 2, "Song:", &mb64_lopt_seq_song, mb64_music_string_tables[mb64_lopt_seq_album], mb64_music_table_lengths[mb64_lopt_seq_album], song_changed);
            break;
        case 3: // Miscellaneous
            settings_create_func_selector(list, 0, "Coin Star:", &mb64_lopt_coinstar, mb64_get_coinstar_str, mb64_lopt_coinstar_max + 1, NULL);
            settings_create_func_selector(list, 1, "Water Level:", &mb64_lopt_waterlevel, mb64_get_waterlevel_name, 65, reload_boundary_and_gfx);
            if (mb64_lopt_game == MB64_GAME_BTCM) {
                settings_create_array_selector(list, 2, "Costume:", &mb64_lopt_costume, mb64_costume_string_table, ARRAY_COUNT(mb64_costume_string_table), NULL);
            }
            sprintf(settings_stats_buf_1, "Total Coins: %d", mb64_total_coin_count);
            sprintf(settings_stats_buf_2, "Total Objects: %d/512", mb64_object_limit_count);
            init_text_component(frame, -140, -65, settings_stats_buf_1, TEXT_LEFT, 0);
            init_text_component(frame, 140, -65, settings_stats_buf_2, TEXT_RIGHT, 0);
            break;
        case 4: // System
            settings_create_button(list, 0, gSDCard ? "Save & Quit" : "Quit Editor", settings_save_and_quit);
            settings_create_button(list, 1, "Play Level", settings_play_level);
            if (gSDCard) {
                settings_create_button(list, 2, "Set Level Thumbnail", settings_take_screenshot);
            }

            int vtx_perc = ((f32)mb64_vtx_total/(f32)MB64_VTX_SIZE)*100.0f;
            int tile_perc = ((f32)mb64_tile_count/(f32)MB64_TILE_POOL_SIZE)*100.0f;
            sprintf(settings_stats_buf_3, "Vertices: %d/50k (%d%%)", mb64_vtx_total, vtx_perc);
            sprintf(settings_stats_buf_4, "Tiles: %d/20k (%d%%)", mb64_tile_count, tile_perc);
            init_text_component(frame, -140, -65, settings_stats_buf_3, TEXT_LEFT, 0);
            init_text_component(frame, 140, -65, settings_stats_buf_4, TEXT_RIGHT, 0);
            break;
    }

    gFromCustomTheme = FALSE;
    return frame;
}

#define SETTINGS_PAGE_HEIGHT 140
#define SETTINGS_PAGE_WIDTH 290
FrameComponent *settings_page_creator(UNUSED PageHandlerComponent *unusedph, s32 index) {
    FrameComponent *frame = init_frame_component(NULL);
    PageHandlerComponent *ph;

    switch (index) {
        case 0: // Main
            ph = init_page_handler(frame, settings_main_page_creator, ARRAY_COUNT(settings_menu_pages), SETTINGS_PAGE_WIDTH/2);
            init_page_title_array(frame, ph, 0, 25, 60, settings_menu_pages);

            init_text_component(frame, -70, 25, "< L", TEXT_RIGHT, 0);
            init_text_component(frame, 70, 25, "R >", TEXT_LEFT, 0);
            if (gSDCard) {
                init_text_component(frame, 0, 50, mb64_file_info.fname, TEXT_CENTER, 0);
                component_set_pos(init_dynamic_component(frame, component_level_portrait_render), 128, 50);
            }
            break;
        case 1: // Custom theme
            ph = init_page_handler(frame, custom_theme_page_creator, 14, SETTINGS_PAGE_WIDTH/2);
            init_page_title_func(frame, ph, 0, 25, 60, get_custom_theme_page_name);

            init_text_component(frame, 0, 50, "Custom Theme Editor", TEXT_CENTER, 0);
            init_text_component(frame, -70, 25, "< L", TEXT_RIGHT, 0);
            init_text_component(frame, 70, 25, "R >", TEXT_LEFT, 0);
            break;
        default:
            return NULL;
    }

    ph->index = gSettingsPage;
    gSettingsPage = 0;

    return frame;
}

void settings_page_closed() {
    PageHandlerComponent *ph = get_child_of_type(settingsRoot, MENU_PAGE_HANDLER, 0);
    gSettingsCustomOpen = ph->index;
    PageHandlerComponent *ph2 = get_child(get_component(ph->currentPage));
    gSettingsPage = ph2->index;

    dealloc_component(get_id(settingsRoot));
    settingsRoot = NULL;
    mb64_menu_state = MB64_MAKE_MAIN;
    show_coord_display();
    toolbar_set_active(TRUE);
}

MenuStyle settings_menu_style = {
    .listOffsetSelected = TRUE,
    .textHighlightSelected = TRUE,
};

void settings_page_main(MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    AnimatedComponent *root = (AnimatedComponent *)m;

    set_menu_style(settings_menu_style);

    mb64_curr_gfx = (Gfx*)alloc_display_list(70*sizeof(Gfx));
    mb64_curr_vtx = (Vtx*)alloc_display_list(120*sizeof(Vtx));
    mb64_gfx_index = 0;

    if (!(root->timer) && !konami_disable_inputs && gPlayer1Controller->buttonPressed & (START_BUTTON | B_BUTTON)) {
        menu_play_click_sound();
        PageHandlerComponent *ph = get_child_of_type(root, MENU_PAGE_HANDLER, 0);
        if ((ph->index == 0) || (gPlayer1Controller->buttonPressed & START_BUTTON)) {
            component_animate_ease_out(root, 4.f, 12, DIR_VERTICAL);
            root->onFinish = settings_page_closed;
            show_toolbar();
        } else {
            gFromCustomTheme = TRUE;
            page_handler_scroll(ph, -1);
            // Save current page
            PageHandlerComponent *ph2 = get_child(get_component(ph->oldPage));
            gSettingsPage = ph2->index;
        }
        update_custom_theme();
        reload_boundary_and_gfx();
    }
}

void settings_menu_create(void) {
    AnimatedComponent *main = alloc_component(gMenuRoot, MENU_ANIMATED);
    component_set_pos(main, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    component_animate_ease_in(main, 180.f, 0.4f, DIR_VERTICAL);
    main->base.prerender = settings_page_main;

    init_box_component(main, 0, 0, 155, 72, 11, 150);
    PageHandlerComponent *ph = init_page_handler(main, settings_page_creator, 2, SETTINGS_PAGE_HEIGHT/2);
    ph->direction = DIR_VERTICAL;
    ph->input = MENU_INPUT_NONE;
    ph->index = gSettingsCustomOpen;

    settingsRoot = main;
}

// Called on level transition
void reset_settings_menu_state(void) {
    gSettingsPage = 0;
    gSettingsCustomOpen = FALSE;
}
