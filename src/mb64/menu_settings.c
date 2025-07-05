#include "menu_engine.h"

#include "game/game_init.h"
#include "game/ingame_menu.h"
#include "audio/external.h"

#include "actors/bg/header.h"
#include "actors/bigpainting2/header.h"

char *settings_menu_pages[] = {
    "Environment",
    "Level Boundary",
    "Music",
    "Miscellaneous",
    "System",
};

void component_settings_box_render(MenuComponent *m, s16 x, s16 y) {
    x += m->xpos;
    y += m->ypos;

    create_dl_translation_matrix(MENU_MTX_PUSH, x, y, 0);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
    gSPDisplayList(gDisplayListHead++, &bg_back_graund_mesh);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

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
void settings_boundary_changed(void) {
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
void music_type_changed(void) {
    set_album_and_song_from_seq(mb64_lopt_seq_seqtype);
    gSongSelector->options = mb64_music_string_tables[mb64_lopt_seq_album];
    gSongSelector->scroll.count = mb64_music_table_lengths[mb64_lopt_seq_album];
    song_changed();
}
void music_category_changed(void) {
    mb64_lopt_seq_song = 0;
    gSongSelector->options = mb64_music_string_tables[mb64_lopt_seq_album];
    gSongSelector->scroll.count = mb64_music_table_lengths[mb64_lopt_seq_album];
    song_changed();
}
void song_changed(void) {
    set_seq_from_album_and_song(mb64_lopt_seq_seqtype);
    stop_background_music(get_current_background_music());
    play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, seq_musicmenu_array[mb64_lopt_seq[mb64_lopt_seq_seqtype]]), 0);
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







MenuComponent *root;

void settings_create_array_selector(ListComponent *list, u8 index, char *text, u8 *var, char **array, u8 count, ComponentUpdateFunc func) {
    TextComponent *t = init_text_component(NULL, 0, 0, text, TEXT_LEFT, 0);
    ListItemComponent *li = component_list_append(list, t, -100, -index * 16);

    SelectorComponent *selector = init_array_selector(li, var, 100, count, array, func);
    component_set_pos(&selector->base, 140, 0);
}

void settings_create_func_selector(ListComponent *list, u8 index, char *text, u8 *var, SelectorStringFunc func, u8 count, ComponentUpdateFunc onChange) {
    TextComponent *t = init_text_component(NULL, 0, 0, text, TEXT_LEFT, 0);
    ListItemComponent *li = component_list_append(list, t, -100, -index * 16);

    SelectorComponent *selector = init_func_selector(li, var, 100, count, func, onChange);
    component_set_pos(&selector->base, 140, 0);
}

SelectorComponent *settings_create_music_selector(ListComponent *list, u8 index, char *text, u8 *var, char **array, u8 count, ComponentUpdateFunc func) {
    TextComponent *t = init_text_component(NULL, 0, 0, text, TEXT_LEFT, 0);
    ListItemComponent *li = component_list_append(list, t, -130, -index * 22);

    SelectorComponent *selector = init_array_selector(li, var, 190, count, array, func);
    component_set_pos(&selector->base, 160, 0);
    return selector;
}

void *settings_create_button(ListComponent *list, u8 index, char *text) {
    TextComponent *t = init_text_component(NULL, 0, 0, text, TEXT_CENTER, 0);
    ListItemComponent *li = component_list_append(list, t, 0, -index * 16);
}

// struct mb64_settings_button mb64_settings_misc_buttons[] = {
//     {"Coin Star:", &mb64_lopt_coinstar, NULL, 1, mb64_get_coinstar_str, NULL},
//     {"Water Level:", &mb64_lopt_waterlevel, NULL,               65,               mb64_get_waterlevel_name, reload_boundary_and_gfx},
//     {"Costume:", &mb64_lopt_costume, mb64_costume_string_table, ARRAY_COUNT(mb64_costume_string_table), NULL, NULL},
// };
char settings_stats_buf_1[32];
char settings_stats_buf_2[32];
char settings_stats_buf_3[32];
char settings_stats_buf_4[32];

FrameComponent *settings_page_creator(s32 index) {
    FrameComponent *frame = init_frame_component(NULL);

    ListComponent *list = alloc_component(frame, MENU_LIST);

    switch (index) {
        case 0: // Environment
            // todo: minecraft theme
            settings_create_array_selector(list, 0, "Theme:", &mb64_lopt_theme, mb64_theme_string_table, ARRAY_COUNT(mb64_theme_string_table) - 1, reload_theme);
            settings_create_array_selector(list, 1, "Skybox:", &mb64_lopt_bg, mb64_bg_string_table, ARRAY_COUNT(mb64_bg_string_table), reload_bg);
            settings_create_array_selector(list, 2, "Effect:", &mb64_lopt_envfx, mb64_envfx_string_table, ARRAY_COUNT(mb64_envfx_string_table), NULL);
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
            settings_create_button(list, 0, "Save & Quit");
            settings_create_button(list, 1, "Play Level");
            settings_create_button(list, 2, "Set Level Thumbnail");

            int vtx_perc = ((f32)mb64_vtx_total/(f32)MB64_VTX_SIZE)*100.0f;
            int tile_perc = ((f32)mb64_tile_count/(f32)MB64_TILE_POOL_SIZE)*100.0f;
            sprintf(settings_stats_buf_3, "Vertices: %d/50k (%d%%)", mb64_vtx_total, vtx_perc);
            sprintf(settings_stats_buf_4, "Tiles: %d/20k (%d%%)", mb64_tile_count, tile_perc);
            init_text_component(frame, -140, -65, settings_stats_buf_3, TEXT_LEFT, 0);
            init_text_component(frame, 140, -65, settings_stats_buf_4, TEXT_RIGHT, 0);
            break;
    }

    return frame;
}

void create_test_list(void) {
    AnimatedComponent *main = alloc_component(NULL, MENU_ANIMATED);
    component_set_pos(&main->base, SCREEN_WIDTH/2, 150);
    component_animate_ease_in(main, 150.f, 0.35f, DIR_VERTICAL);

    PageHandlerComponent *ph = init_page_handler(main, settings_page_creator, ARRAY_COUNT(settings_menu_pages), 290);
    ph->base.prerender = component_settings_box_render;
    init_page_title(main, &ph->base, 0, 25, 120, settings_menu_pages);

    init_text_component(main, 0, 50, mb64_file_info.fname, TEXT_CENTER, 0);
    init_text_component(main, -70, 25, "< L", TEXT_RIGHT, 0);
    init_text_component(main, 70, 25, "R >", TEXT_LEFT, 0);
    component_set_pos(init_dynamic_component(main, component_level_portrait_render), 128, 50);

    root = &main->base;
}

void menu_engine_init_test(void) {
    create_test_list();
}
void menu_engine_render_test(void) {
    if (!root) {
        return;
    }
    menu_update_joystick();
    render_component(root, 0, 0);

    AnimatedComponent *a = (AnimatedComponent *)root;
    if (!(a->moving) && gPlayer1Controller->buttonPressed & B_BUTTON) {
        component_animate_ease_out(a, 4.f, DIR_VERTICAL);
    }
}
void menu_engine_dealloc_test(void) {
    dealloc_component(root);
    root = NULL;
}
