#include "menu_engine.h"

#include "game/game_init.h"
#include "game/ingame_menu.h"
#include "audio/external.h"

#include "game/sram.h"
#include "game/segment2.h"
#include "levels/menu/mm_btn2/header.h"
#include "levels/menu/mm_btn_lg/header.h"
#include "levels/menu/header.h"
#include "libpl/libpl.h"

char *info_credits[] = {
    "3Mario Builder 64",
    "2By Arthurtilly & Rovertronic",
    "22024 - 2025",
    NULL,
    "3SD Card Support",
    "2Devwizard",
    "2Falcobuster",
    NULL,
    "3Title Screen Model",
    "2Biobak",
    NULL,
    "3Various Assets",
    "2BroDute",
    "2Thodds",
    "2Yoshi Milkman",
    "2Dorrieal",
    "2CowQuack",
    "2Pixelissimo",
    NULL,
    "3GitHub Contributors",
    "2aglab2",
    "2ArcticJaguar725",
    "2jefftastic",
    "2Polprzewodnikowy",
    "2Stevoisiak",
    NULL,
    "3Beyond the Cursed Mirror OST",
    "2SpK",
    "2Thorndust",
    NULL,
    "3Music Ports",
    "2SMWCentral",
    "2SM64 Editor",
    NULL,
    "3HackerSM64",
    "2HackerN64 Team",
};

char *info_setup_guide[] = {
    "3Emulator Setup",
    NULL,
    "0To save your Mario Builder 64 levels and play levels",
    "0created by other people, you will need to use an emulator",
    "0that supports SD card emulation. This does NOT require",
    "0you to own a physical SD card.",
    NULL,
    "0Alternatively, you can use a flashcart on a real",
    "0N64 together with a physical SD card.",
    NULL,
    "3Supported Emulators",
    NULL,
    "3Parallel Launcher",
    "2https://parallel-launcher.ca/",
    NULL,
    "3Luna's Project64",
    "2https://github.com/Luna-Project64/Luna-Project64",
    NULL,
    NULL,
    "3Recommended Settings",
    NULL,
    "0Use the GlideN64 graphics plugin. Make sure that",
    "0FBE (Framebuffer Emulation) is enabled.",
    NULL,
    "0For Parallel Launcher, make sure 'Overclock VI' is ticked,",
    "0and the setting 'Emulate SummerCart64 SD card interface'",
    "0is enabled.",
    NULL,
    "0For Luna's PJ64, set Counter Factor to 0.",
    NULL,
    "3Accessing Level Files",
    NULL,
    "0To access your level files, you will need to mount the",
    "0SD card image through the emulator. This will require",
    "0administrative permissions through a popup.",
    "0Once you have done this, you can find any saved levels",
    "0in the 'Mario Builder 64 Levels' folder in the drive.",
    "0You can also move any downloaded levels into this folder",
    "0to play them.",
    NULL,
    "3Parallel Launcher",
    NULL,
    "0Click the button to the right of the SD card dropdown",
    "0to open the SD card menu. Select the SD card and click",
    "0'Browse Files' to mount the SD card.",
    "0Click 'OK' to unmount once you are done.",
    NULL,
    "3Luna's Project64",
    NULL,
    "0Click 'File' -> 'Mount SD Card'.",
    "0When you are done, eject the SD card drive through",
    "0File Explorer, and click 'File' -> 'Unmount SD Card'.",
    NULL,
    NULL,
    "0Note: You may get a false virus alert from Windows Defender",
    "0upon attempting to mount the SD card. These emulators are",
    "0guaranteed to be safe to use, so you may need to exclude",
    "0the .exe file from Windows Defender.",
    NULL,
    "0For a more detailed guide, visit",
    "0https://rentry.co/mb64-setup-guide",
    NULL,
};

char *info_no_sd_card[] = {
    "3WARNING!",
    "3SD card emulation not detected.",
    NULL,
    "0You can still use the level editor, but you cannot save the",
    "0levels you create, or play levels created by other people.",
    NULL,
    "0Go to \"Help -> MB64 Setup Guide\" to get help",
    "0on how to set up SD card emulation.",
    NULL,
    "0Otherwise, your level will be lost when you exit the",
    "0editor, so use savestates to save your progress."
};

char *info_level_sharing[] = {
    "3Level Sharing",
    NULL,
    "0You can upload your .mb64 files online and download levels",
    "0from other people at Level Share Square, the dedicated",
    "0website.",
    NULL,
    "3Level Share Square",
    "2https://levelsharesquare.com/levels",
    NULL,
    NULL,
    "0Be sure to also join the official Mario Builder 64 Discord",
    "0server for updates, announcements and discussion!",
    NULL,
    "3Mario Builder 64 Discord",
    "2https://discord.gg/4qt2DP4Dyy",
};

char *info_editor_controls[] = {
    "3Navigation Controls",
    NULL,
    "0  Analog Stick:  Move cursor horizontally",
    "0  \x14 ^ / |:  Move cursor vertically",
    "0  \x14 < / >:  Rotate camera",
    "0  D-Pad |:  Change camera zoom",
    NULL,
    "3Building Controls",
    NULL,
    "0  \x10:  Place tile",
    "0  \x11:  Delete tile(s)",
    "0  \x12:  Rotate tile",
    "0  D-Pad < / >:  Change object parameters",
    "0  D-Pad ^:  Flip tile vertically",
    NULL,
    "3Toolbar Controls",
    NULL,
    "0  \x15 / \x13:  Navigate hotbar",
    "0  \x15+\x13:  Sample tile",
    "0  START:  Open toolbox",
};

char *info_v1_1_changelog[] = {
    "3Mario Builder 64 - v1.1 Changelog",
    NULL,
    NULL,
    "3Major Changes",
    NULL,
    "0- Increased vertex limit from 40,000 to 50,000",
    "0- Increased tile limit from 10,000 to 20,000",
    "0- Optimized vertex generation by up to 25%",
    "0- New boundary type: Interior",
    "0- New object: On-Off Conveyor",
    "0- New object: Inverted Timed Box",
    "0- New object: Star Trigger",
    "0- New Sample Tile building shortcut by pressing \x15+\x13",
    "0- Ability to place multiple objects/tiles in the same spot",
    "0- Dialog to exit a level after collecting every star",
    "0- Added a speedrun timer option in the pause menu",
    "0- Added a Star Radar option in the pause menu",
    "0- Added 5 new level templates",
    NULL,
    "3Conveyors",
    NULL,
    "0- Added thin and sloped conveyors",
    "0- Added red/blue on-off conveyors",
    "0- The underside of conveyors are now hangable",
    "0- Improved conveyor physics",
    NULL,
    "3Imbuing System",
    NULL,
    "0- All enemies can be given objects to drop on death",
    "0- Objects can be placed inside ! Boxes",
    "0- Can now place Red Coins and Green Coins inside objects",
    "0- Can now place Badges and Powerups inside objects",
    "0- Dropped objects appear at the object's last safe location",
    "0- Boxes with yellow coins drop 3 coins instead of 1",
    "0- Boos and Moneybags show the item they will drop",
    "0- New Star Trigger can only be placed inside objects",
    "0    When all Star Triggers are activated, a star will spawn",
    "0    Star Triggers can also be placed inside coins and badges",
    NULL,
    "3Badge Changes",
    NULL,
    "0- Removed Star Radar badge in favor of a pause menu option",
    "0- Star Radar consistently always shows the closest star",
    "0- Star Radar shows red coins if all stars are collected",
    "0- Buffed Heal Plus badge to apply to all coins",
    "0- Buffed/renamed Double Damage badge to One Hit badge",
    "0- Buffed Defense badge to spend 1 mana per hit instead of 4",
    "0- Buffed Burn badge to not consume mana",
    NULL,
    "3Editor Tweaks",
    NULL,
    "0- Ability to hide help text in screenshot mode",
    "0- Screenshot mode has been moved to the System menu",
    "0- Custom Theme menu shows slipperiness of current tile",
    "0- Display the current number of placed objects in the",
    "0    editor when placing Stars or Red Coins",
    "0- Objects now have shadows in the editor",
    "0- Improved vertex/tile/object limit display",
    "0- Better warnings for vertex limit and having FBE disabled",
    "0- Improved cursor wrapping around the sides of the level",
    "0- Faster navigation between level pages using left/right",
    "0- Muting music no longer requires a level reset",
    "0- Added the Bowling Ball to the BTCM gamemode",
    NULL,
    "3Gameplay Tweaks",
    NULL,
    "0- Objects can trigger Activated Moving Platforms",
    "0- Wooden Platforms form a stack when placed vertically",
    "0- Bowling Balls can destroy boxes and kill enemies",
    "0- Hammer Bro's hammers can destroy boxes and kill enemies",
    "0- Throwable and Crazy Boxes respawn after being broken",
    "0- Using a Noteblock no longer forces you to drop objects",
    "0    or stop riding a shell",
    "0- Koopa the Quick respawns after losing the race",
    "0- Nerfed the Showrunner",
    "0- Collecting a Power Star fully heals Mario",
    "0- Bowser no longer instantly dies to lava",
    "0- BTCM Powerups can be used simultaneously",
    "0- The crowbar can hit multiple objects at once",
    "0- The crowbar can be used to pick up coins",
    "0- Heavily improved Thwomp physics and interactions",
    "0- Physics given to Mr. Blizzard and Piranha Plants",
    "0- AI and physics improvements for all enemies",
    NULL,
    "3Improved Assets",
    NULL,
    "0- Better texture mapping for slopes",
    "0- Better object models for Wooden Platform, On-Off Block,",
    "0    On-Off Switch, Reinforced Box, Fire Spinner",
    "0- Improved textures: Quicksand, Cosmic Void, Rocky Dirt,",
    "0    Green Rock, Ocean Floor, Scorched Pillar, Hazard Stripes",
    "0- Improved certain music ports (thanks to Pixelissimo)",
    NULL,
    "3Bug Fixes",
    NULL,
    "0- BTCM void respawn mechanic not working",
    "0- Bottomless badge having no effect",
    "0- Incorrect star IDs with 8 or more stars",
    "0- Infinite coin exploit from Blue Coin previews",
    "0- Trajectory data not resetting between levels",
    "0- Crash when climbing poles with Mario cam",
    "0- Wooden platforms not squishing Mario",
    "0- Softlock on top of fences at the level boundary",
    "0- Lava bubbles appearing far below the level",
    "0- Glitchy bully physics in midair and on snow/ice",
    "0- Bug allowing unlimited stars to be placed",
    "0- Failure to load levels on some flashcarts",
    "0- String overflow glitches in level and author names",
    "0- Periods not being allowed in level names",
    "0- Bad handling of invalid level files",
    "0- Level files corrupting if the vertex limit is exceeded",
    "0- Broken menus with widescreen viewport hack enabled",
    "0- BTCM templates selecting the wrong music tracks",
    "0- Infinite flight time bug with the Bullet Bill Mask",
    "0- Fire spinners having the incorrect rotation ingame",
    "0- Broken boss music with multiple bosses",
    "0- Exiting on a moving platform not resetting inertia",
    "0- HUD issues with the air bubble and rocket fuel meters",
    "0- Spinning around when flying after sliding down a pole",
    "0- Broken camera when collecting a badge while flying",
    "0- Cosmic Phantasms copying model state from Mario",
    "0- Countless minor physics and AI fixes",
};

char *new_level_gamemodes[] = {
    "Vanilla SM64",
    "Cursed Mirror",
};

char *new_level_sizes[] = {
    "Small (32)",
    "Medium (48)",
    "Large (64)",
};

char *new_level_templates[] = {
    "Grass",
    "Sky",
    "Desert",
    "Snow",
    "Lava",
    "Water",
    "Cave",
    "Spooky",
    "Castle",
    "Retro",
};

void component_main_menu_button_render(MenuComponent *m, s16 x, s16 y) {
    x += m->xpos;
    y += m->ypos + 7;
    u8 value = gMenuState.selected ? get_selected_color_value() : 0;

    create_dl_translation_matrix(MENU_MTX_PUSH, x, y, 0);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, value, value, value, 190);
    gSPDisplayList(gDisplayListHead++, &mm_btn2_mm_btn_mesh);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

#define levelIndex params[0].asInt
void component_main_menu_level_render(MenuComponent *m, s16 x, s16 y) {
    FrameComponent *f = (FrameComponent *)m;
    u16 (*u16_array)[MAX_FILES][64][64] = segmented_to_virtual(mb64_level_entry_piktcher);

    x += m->xpos;
    y += m->ypos;
    u8 value = gMenuState.selected ? get_selected_color_value() : 0;

    create_dl_translation_matrix(MENU_MTX_PUSH, x, y, 0);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    if (gMenuState.disabled) {
        gDPSetEnvColor(gDisplayListHead++, 50, 0, 0, 150);
    } else {
        gDPSetEnvColor(gDisplayListHead++, value, value, value, 150);
    }
    gSPDisplayList(gDisplayListHead++, &mm_btn_lg_mm_btn_lg_mesh);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

    if (f->levelIndex != -2) {
        create_dl_translation_matrix(MENU_MTX_NOPUSH, -108, -2, 0);
        if (gMenuState.disabled) {
            gDPSetEnvColor(gDisplayListHead++, 150, 0, 0, 255);
        } else {
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        }
        gSPDisplayList(gDisplayListHead++, &bigpainting_bigpainting_mesh_part1);
        gDPLoadSync(gDisplayListHead++);
        if (f->levelIndex == -1) {
            gDPSetTextureImage(gDisplayListHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, mystery_painting_rgba16);
        } else {
            gDPSetTextureImage(gDisplayListHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, (*u16_array)[f->levelIndex]);
        }
        gSPDisplayList(gDisplayListHead++, &bigpainting_bigpainting_mesh_part2);
        create_dl_scale_matrix(MENU_MTX_NOPUSH, 3.f, 3.f, 1.f);
        if (gMenuState.disabled) {
            menu_text_display("X", 1, -7, TEXT_DARKRED, TEXT_CENTER, 255);
        }
    }
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

enum MainMenuPages {
    PAGE_NONE,
    PAGE_AUTHOR,
    PAGE_MAIN,

// Build
    PAGE_BUILD,
    PAGE_NEW_LEVEL,
    PAGE_LEVEL_NAME,
    PAGE_LOAD_LEVEL,
    PAGE_CHANGE_NAME,

// Play
    PAGE_PLAY_LEVEL,

// Help
    PAGE_HELP,
    PAGE_SETUP_GUIDE,
    PAGE_EDITOR_CONTROLS,
    PAGE_SHARE_LEVELS,
    PAGE_CHANGELOG,
    PAGE_NO_SD_CARD,

// Credits
    PAGE_CREDITS,
};

u8 gMB64LevelLoaded = FALSE;

#define TO_NEXT 1
#define TO_PREV -1

u8 gCurrMainMenuPage = PAGE_MAIN;
u8 gPrevMainMenuPage = PAGE_NONE; // Page to return to when B is pressed
u8 gPrevMainMenuButton = 0; // Index to select when returning to the previous page
u8 gScheduledNextPage = PAGE_NONE;
u8 gChangePage = PAGE_NONE;
s8 gMainMenuAnimateDir = TO_NEXT; // 1 for forwards, -1 for backwards
int gLevelSelectorIndex = 0;
FrameComponent *gMainMenuPageHandler;

void do_page_change(UNUSED AnimatedComponent *a) {
    gChangePage = gScheduledNextPage;
    gScheduledNextPage = PAGE_NONE;
}

void unfreeze_page(UNUSED AnimatedComponent *a) {
    MenuComponent *page = get_first_child(gMainMenuPageHandler);
    page->inactive = FALSE;
}

void main_menu_list_animate(ListComponent *l, int out) {
    int dir = gMainMenuAnimateDir;
    for (int i = 0; i < l->count; i++) {
        AnimatedComponent *a = get_first_child(component_list_get(l, i));
        if (out) {
            component_animate_bounce_out(a, -8.f*dir, 23.f*dir, 20, DIR_HORIZONTAL);
        } else {
            component_animate_bounce_in(a, 300.f*dir, 8.f*dir, -75.f*dir, DIR_HORIZONTAL);
        }
        a->delay = ABS(l->index - i)*2;
    }
}

void main_menu_text_animate(AnimatedComponent *a, int out, int dir) {
    if (out) {
        component_animate_ease_out(a, dir*3.f, 20, DIR_VERTICAL);
    } else {
        component_animate_ease_in(a, dir*50.f, 0.5f, DIR_VERTICAL);
    }
}

void main_menu_keyboard_animate(AnimatedComponent *k, int out) {
    if (out) {
        component_animate_ease_out(k, -3.f, 20, DIR_VERTICAL);
    } else {
        component_animate_ease_in(k, -100.f, 0.4f, DIR_VERTICAL);
    }
}

void main_menu_key_text_animate(FrameComponent *page, int out, int dir) {
    AnimatedComponent *a = get_child(page, MENU_ANIMATED, 0);
    main_menu_text_animate(a, out, dir);
    if (out) {
        a->onFinish = do_page_change;
    } else {
        a->onFinish = unfreeze_page;
    }
}

void main_menu_shade_animate(FrameComponent *page, int out) {
    RectComponent *rect = get_first_child(page);
    if (!out) rect->curAlpha = 0;
    component_rect_do_fade(rect, out ? 0 : 110, 12, out ? do_page_change : unfreeze_page);
}

void button_change_page(TextComponent *b) {
    gMainMenuAnimateDir = TO_NEXT;
    gScheduledNextPage = b->onClickArg;
    main_menu_page_change_animate(get_first_child(gMainMenuPageHandler), TRUE);
}

AnimatedComponent *main_menu_create_title(MenuComponent *parent, char *text, s16 y) {
    AnimatedComponent *a = alloc_component(parent, MENU_ANIMATED);
    component_set_pos(a, SCREEN_WIDTH/2, y);

    MatrixComponent *mat = init_matrix_component(a, 0, 2.f, 2.f);
    TextComponent *t = init_text_component(mat, 0, 0, text, TEXT_CENTER, 0);
    return a;
}

ListComponent *main_menu_create_list(MenuComponent *parent, s16 y) {
    ListComponent *l = alloc_component(parent, MENU_LIST);
    component_set_pos(l, SCREEN_WIDTH/2, y);
    return l;
}

void main_menu_list_set_index(ListComponent *l) {
    if (gMainMenuAnimateDir == TO_PREV) {
        l->index = gPrevMainMenuButton;
    }
}

void main_menu_create_button(ListComponent *l, char *text, s16 y, ComponentUpdateFunc func, int arg) {
    AnimatedComponent *a = alloc_component(NULL, MENU_ANIMATED);
    TextComponent *t = init_text_button(a, 0, 0, text, TEXT_CENTER, func, arg);
    t->base.prerender = component_main_menu_button_render;
    component_list_append(l, a, 0, y);
}

void main_menu_create_selector(ListComponent *l, char *text, s16 y, u8 *value, char **options, int count) {
    AnimatedComponent *a = alloc_component(NULL, MENU_ANIMATED);
    SelectorComponent *s = init_array_selector(a, value, 40, count, options, NULL);
    s->base.prerender = component_main_menu_button_render;
    component_set_pos(s, 20, 0);
    init_text_component(a, -45, 0, text, TEXT_RIGHT, 0);
    component_list_append(l, a, 0, y);
}

#define infoText params[0].asPtr
#define yScroll params[1].asInt
#define infoLen params[2].asBytes[0]
void main_menu_info_loop(MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    FrameComponent *info = (FrameComponent *)m;
    RectComponent *rect = get_parent(info);

    char **infoStrings = info->infoText;
    if (!infoStrings) return;

    int maxScroll = (info->infoLen * 16) - 176;
    if (!gMenuState.inactive && maxScroll > 0) {
        info->yScroll -= (gPlayer1Controller->rawStickY/10.0f);
        info->yScroll = CLAMP(info->yScroll, 0, maxScroll);
    }

    f32 alphaMult = rect->curAlpha / 110.f;

    if (info->yScroll != maxScroll) {
        menu_text_display("|", 300, 20 + sins(gGlobalTimer * 0x300) * 2.5f, TEXT_WHITE, TEXT_CENTER, alphaMult*255);
    }
    if (info->yScroll != 0) {
        menu_text_display("^", 300, 40 - sins(gGlobalTimer * 0x300) * 2.5f, TEXT_WHITE, TEXT_CENTER, alphaMult*255);
    }

    for (int i = 0; i < info->infoLen; i++) {
        if (infoStrings[i] == NULL) continue;
        int y = 200 - (i * 16) + info->yScroll;
        if (y < 20 || y > 220) continue;

        f32 alpha = 1.f;
        if (y < 40) { alpha = (y - 20) / 20.f; }
        else if (y > 200) { alpha = (220 - y) / 20.f; }

        int textRender = infoStrings[i][0] - '0';
        int align = (textRender & 2) != 0;
        menu_text_display(infoStrings[i]+1, (align ? SCREEN_WIDTH/2 : 16), y, textRender & 1, align, (u8)(alpha * alphaMult * 255.f));
    }

    if (gCurrMainMenuPage == PAGE_NO_SD_CARD && gPlayer1Controller->buttonPressed & (A_BUTTON | START_BUTTON)) {
        MenuComponent *page = get_first_child(gMainMenuPageHandler);
        gMainMenuAnimateDir = TO_NEXT;
        gScheduledNextPage = PAGE_MAIN;
        play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
        main_menu_page_change_animate(page, TRUE);
    }
}

FrameComponent *main_menu_create_info(MenuComponent *parent, char **text, int len) {
    RectComponent *rect = init_rect_component(parent, 110, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    FrameComponent *info = init_dynamic_component(rect, main_menu_info_loop);
    info->infoText = text;
    info->infoLen = len;
    return info;
}

void main_menu_load_level(TextComponent *b) {
    FILINFO * level_entries_ptr = segmented_to_virtual(mb64_level_entries);

    // Animate menu
    MenuComponent *m = get_first_child(gMainMenuPageHandler);
    gMainMenuAnimateDir = TO_NEXT;
    play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
    main_menu_page_change_animate(m, TRUE);

    mb64_mode = MB64_MODE_UNINITIALIZED;
    reset_play_state();
    strncpy(mb64_file_name, level_entries_ptr[gLevelSelectorIndex].fname, MAX_FILE_NAME_SIZE);
    struct mb64_level_save_header *level_info = get_level_info_from_filename(mb64_file_name);
    mb64_lopt_game = level_info->game;
    // Load level
    if (gCurrMainMenuPage == PAGE_LOAD_LEVEL) {
        mb64_target_mode = MB64_MODE_MAKE;
        mb64_level_action = MB64_LA_BUILD;
    } else {
        mb64_target_mode = MB64_MODE_PLAY;
        mb64_level_action = MB64_LA_PLAY_LEVELS;
    }
    gMB64LevelLoaded = TRUE;
}

#define LEVELS_PER_PAGE 5
FrameComponent *main_menu_create_level_page(PageHandlerComponent *ph, s32 index) {
    FILINFO * level_entries_ptr = segmented_to_virtual(mb64_level_entries);
    FrameComponent *f = init_frame_component(NULL);
    ListComponent *l = init_sublist(f, get_id(ph), index * LEVELS_PER_PAGE);

    int numLevels = MIN(LEVELS_PER_PAGE, mb64_level_entry_count - (index * LEVELS_PER_PAGE));
    for (int i = 0; i < numLevels; i++) {
        int levelindex = index * LEVELS_PER_PAGE + i;
        AnimatedComponent *a = alloc_component(NULL, MENU_ANIMATED);
        FrameComponent *level = init_dynamic_component(a, component_main_menu_level_render);
        level->levelIndex = levelindex;
        TextComponent *t = init_text_component(level, -82, -10, level_entries_ptr[levelindex].fname, TEXT_LEFT, 0);
        t->onClick = main_menu_load_level;
        t->skipExtension = TRUE;
        component_list_append(l, a, 0, 75 - (i * 36));

        if (MB64_VERSION < mb64_level_entry_version[levelindex]) {
            component_list_get(l, i)->disabled = TRUE;
            t->color = TEXT_RED;
        }
    }
    // Only set index if pagehandler is empty
    if (!ph->currentPage) l->index = gLevelSelectorIndex % LEVELS_PER_PAGE;
    return f;
}

void page_number_init_text(MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    component_main_menu_button_render(m, x, y);
    TextComponent *t = (TextComponent *)m;
    FrameComponent *page = get_parent(get_parent(t));
    PageHandlerComponent *ph = get_first_child(page);
    sprintf(t->text, "Page %d/%d", ph->index + 1, ph->scroll.count);
}

void main_menu_level_list_fast_scroll(MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    PageHandlerComponent *ph = (PageHandlerComponent *)m;
    if (ph->scroll.offset) return;
    int index = ph->index;
    int dir = get_input(MENU_INPUT_TRIGGERS | MENU_INPUT_JOYSTICK, DIR_HORIZONTAL);
    if (!dir) {
        return;
    }
    index = (index + dir + ph->scroll.count) % ph->scroll.count;

    ListComponent *l = get_child(get_component(ph->currentPage), MENU_LIST, 0);
    int curIndex = l->index;
    page_handler_set_page(ph, index);
    l = get_child(get_component(ph->currentPage), MENU_LIST, 0);
    l->index = CLAMP(curIndex, 0, l->count - 1);
}

char *page_buf[12];
void main_menu_create_level_list(MenuComponent *parent) {
    if (mb64_level_entry_count == 0) {
        AnimatedComponent *a = alloc_component(parent, MENU_ANIMATED);
        component_set_pos(a, SCREEN_WIDTH/2,200);
        TextComponent *t = init_text_component(a, 0, 0, "No levels...", TEXT_CENTER, TEXT_RED);
        t->base.prerender = component_main_menu_button_render;
        return;
    }
    int levelcount = (mb64_level_entry_count-1) / LEVELS_PER_PAGE + 1;
    PageHandlerComponent *ph = init_page_handler(parent, main_menu_create_level_page, levelcount, SCREEN_HEIGHT/2 - 30);
    component_set_pos(ph, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 15);
    ph->direction = DIR_VERTICAL;
    ph->input = MENU_INPUT_NONE;
    ph->frames = 8;
    ph->activeOnScroll = TRUE;
    ph->index = gLevelSelectorIndex / LEVELS_PER_PAGE;
    ph->base.prerender = main_menu_level_list_fast_scroll;

    AnimatedComponent *pageinfo = alloc_component(parent, MENU_ANIMATED);
    component_set_pos(pageinfo, 70, 15);
    TextComponent *t = init_text_component(pageinfo, 0, 0, page_buf, TEXT_CENTER, 0);
    t->base.prerender = page_number_init_text;
}

char main_menu_keyboard_input[MAX(MAX_FILE_NAME_SIZE, MAX_USERNAME_SIZE)];
#define KEYBOARD_CONFIRM (!gMenuState.inactive && (gPlayer1Controller->buttonPressed & START_BUTTON) && main_menu_keyboard_input[0] != 0)
void keyboard_start_level(MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    if (KEYBOARD_CONFIRM) {
        int fileExists = level_file_exists(main_menu_keyboard_input);
        if (fileExists) {
            show_error("Level already exists!");
            return;
        }
        MenuComponent *page = get_first_child(gMainMenuPageHandler);
        gMainMenuAnimateDir = TO_NEXT;
        play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
        main_menu_page_change_animate(page, TRUE);

        mb64_mode = MB64_MODE_UNINITIALIZED;
        reset_play_state();
        strcpy(mb64_file_name, main_menu_keyboard_input);
        strcat(mb64_file_name, ".mb64");

        mb64_target_mode = MB64_MODE_MAKE;
        mb64_level_action = MB64_LA_BUILD;
        gMB64LevelLoaded = TRUE;
    }
}

void no_sd_card_start_level(void) {
    play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
    mb64_mode = MB64_MODE_UNINITIALIZED;
    reset_play_state();
    mb64_target_mode = MB64_MODE_MAKE;
    mb64_level_action = MB64_LA_BUILD;
    gMB64LevelLoaded = TRUE;
}

void keyboard_set_author_name(MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    if (KEYBOARD_CONFIRM) {
        MenuComponent *page = get_first_child(gMainMenuPageHandler);
        if (gCurrMainMenuPage == PAGE_AUTHOR) {
            gMainMenuAnimateDir = TO_NEXT;
            gScheduledNextPage = PAGE_MAIN;
        } else {
            gMainMenuAnimateDir = TO_PREV;
            gScheduledNextPage = gPrevMainMenuPage;
        }
        play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
        main_menu_page_change_animate(page, TRUE);

        strncpy(mb64_username,main_menu_keyboard_input,MAX_USERNAME_SIZE);
        strncpy(mb64_sram_configuration.author, mb64_username, MAX_USERNAME_SIZE);
        if (gSramProbe != 0) {
            nuPiWriteSram(0, &mb64_sram_configuration, ALIGN8(sizeof(mb64_sram_configuration)));
        }
        mb64_has_username = TRUE;
    }
}

void main_menu_create_keyboard_page(MenuComponent *parent, char *text, ComponentRenderFunc *func, int isFilename) {
    RectComponent *rect = init_rect_component(parent, 110, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    AnimatedComponent *top = alloc_component(rect, MENU_ANIMATED);
    TextComponent *t = init_text_component(top, -120, 85, text, TEXT_LEFT, TEXT_WHITE);
    FrameComponent *f = init_dynamic_component(top, component_main_menu_level_render);
    f->levelIndex = (isFilename ? -1 : -2); // -1 for filename, -2 for author name
    component_set_pos(f, 0, 60);
    TextComponent *input = init_text_component(f, (isFilename ? -82 : -120), -10, main_menu_keyboard_input, TEXT_LEFT, 0);

    AnimatedComponent *bottom = alloc_component(rect, MENU_ANIMATED);
    KeyboardComponent *k = init_keyboard_component(bottom, -120, 18, main_menu_keyboard_input, input, isFilename ? MAX_FILE_NAME_INPUT : MAX_USERNAME_INPUT, isFilename);
    k->base.prerender = func;
    input->cursorPos = strlen(main_menu_keyboard_input);

    init_text_component(bottom, -130, -92, "\x12: Backspace", TEXT_LEFT, TEXT_WHITE);
    init_text_component(bottom, -130, -108, "\x15/\x13: Toggle Shift", TEXT_LEFT, TEXT_WHITE);
    init_text_component(bottom, 130, -92, "START: Confirm", TEXT_RIGHT, TEXT_WHITE);
    init_text_component(bottom, 130, -108, "D-Pad: Move cursor", TEXT_RIGHT, TEXT_WHITE);
}

void main_menu_page_change_animate(FrameComponent *page, int out) {
    page->base.inactive = TRUE;
    ListComponent *l;
    switch (gCurrMainMenuPage) {
        // Button pages
        case PAGE_MAIN:
        case PAGE_BUILD:
        case PAGE_HELP:
        case PAGE_NEW_LEVEL:
            l = get_child(page, MENU_LIST, 0);
            main_menu_list_animate(l, out);
            main_menu_key_text_animate(page, out, 1);
            break;
        // Info pages
        case PAGE_CREDITS:
        case PAGE_SETUP_GUIDE:
        case PAGE_EDITOR_CONTROLS:
        case PAGE_SHARE_LEVELS:
        case PAGE_CHANGELOG:
        case PAGE_NO_SD_CARD:
            main_menu_shade_animate(page, out);
            break;
        case PAGE_PLAY_LEVEL:
        case PAGE_LOAD_LEVEL:
            if (mb64_level_entry_count == 0) {
                main_menu_key_text_animate(page, out, 1);
                break;
            }
            PageHandlerComponent *ph = get_first_child(page);
            page_handler_load_initial_page(ph);
            l = get_child(get_component(ph->currentPage), MENU_LIST, 0);
            main_menu_list_animate(l, out);
            main_menu_key_text_animate(page, out, -1);
            gLevelSelectorIndex = ph->index * LEVELS_PER_PAGE + l->index;
            break;
        case PAGE_LEVEL_NAME:
        case PAGE_CHANGE_NAME:
        case PAGE_AUTHOR:
            main_menu_shade_animate(page, out);
            RectComponent *shade = get_first_child(page);
            main_menu_text_animate(get_child(shade, MENU_ANIMATED, 0), out, 1);
            main_menu_keyboard_animate(get_child(shade, MENU_ANIMATED, 1), out);
            break;
    }
}

void main_menu_page_loop(MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    if (!m->inactive && gPrevMainMenuPage != PAGE_NONE) {
        if (gPlayer1Controller->buttonPressed & B_BUTTON) {
            gMainMenuAnimateDir = TO_PREV;
            gScheduledNextPage = gPrevMainMenuPage;
            play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
            main_menu_page_change_animate(m, TRUE);

            m->inactive = TRUE;
        }
    }
}

void create_page(int page, int animate) {
    gCurrMainMenuPage = page;

    FrameComponent *frame = init_frame_component(gMainMenuPageHandler);
    frame->base.prerender = main_menu_page_loop;
    ListComponent *l;
    switch (page) {

        // Button pages
        case PAGE_MAIN:
            AnimatedComponent *title = main_menu_create_title(frame, "Mario Builder 64", 188);
            init_text_component(title, 0, -15, "By Arthurtilly & Rovertronic", TEXT_CENTER, 0);
            init_text_component(title, 85, -3, "v1.1", TEXT_LEFT, 0);
            l = main_menu_create_list(frame, 143);
            if (gSDCard) {
                main_menu_create_button(l, "Build",     0, button_change_page, PAGE_BUILD);
                main_menu_create_button(l, "Play",    -30, button_change_page, PAGE_PLAY_LEVEL);
                main_menu_create_button(l, "Help",    -60, button_change_page, PAGE_HELP);
                main_menu_create_button(l, "Credits", -90, button_change_page, PAGE_CREDITS);
            } else {
                main_menu_create_button(l, "Level Editor", 0, button_change_page, PAGE_NEW_LEVEL);
                main_menu_create_button(l, "Help",    -30, button_change_page, PAGE_HELP);
                main_menu_create_button(l, "Credits", -60, button_change_page, PAGE_CREDITS);    
            }
            main_menu_list_set_index(l);
            gPrevMainMenuPage = PAGE_NONE;
            break;
        case PAGE_BUILD:
            main_menu_create_title(frame, "Build Levels", 188);
            l = main_menu_create_list(frame, 143);
            main_menu_create_button(l, "New Level",     0, button_change_page, PAGE_NEW_LEVEL);
            main_menu_create_button(l, "Load Level",  -30, button_change_page, PAGE_LOAD_LEVEL);
            main_menu_create_button(l, "Change Name", -60, button_change_page, PAGE_CHANGE_NAME);
            main_menu_list_set_index(l);
            gPrevMainMenuPage = PAGE_MAIN;
            gPrevMainMenuButton = 0;
            break;
        case PAGE_HELP:
            main_menu_create_title(frame, "Help", 188);
            l = main_menu_create_list(frame, 143);
            main_menu_create_button(l, "MB64 Setup Guide",  0, button_change_page, PAGE_SETUP_GUIDE);
            main_menu_create_button(l, "Editor Controls", -30, button_change_page, PAGE_EDITOR_CONTROLS);
            main_menu_create_button(l, "Share Levels",    -60, button_change_page, PAGE_SHARE_LEVELS);
            main_menu_create_button(l, "Changelog",       -90, button_change_page, PAGE_CHANGELOG);
            main_menu_list_set_index(l);
            gPrevMainMenuPage = PAGE_MAIN;
            gPrevMainMenuButton = gSDCard ? 2 : 1;
            break;
        case PAGE_NEW_LEVEL:
            main_menu_create_title(frame, "Level Settings", 188);
            l = main_menu_create_list(frame, 153);
            main_menu_create_selector(l, "Mode:", 0, &mb64_lopt_game, new_level_gamemodes, ARRAY_COUNT(new_level_gamemodes));
            main_menu_create_selector(l, "Size:", -25, &mb64_lopt_size, new_level_sizes, ARRAY_COUNT(new_level_sizes));
            main_menu_create_selector(l, "Template:", -50, &mb64_lopt_template, new_level_templates, ARRAY_COUNT(new_level_templates));
            if (gSDCard) {
                main_menu_create_button(l, "Create!", -100, button_change_page, PAGE_LEVEL_NAME);
            } else {
                main_menu_create_button(l, "Create!", -100, no_sd_card_start_level, 0);
            }
            main_menu_list_set_index(l);
            gPrevMainMenuPage = PAGE_BUILD;
            gPrevMainMenuButton = 0;
            break;

        // Info pages
        case PAGE_CREDITS:
            main_menu_create_info(frame, info_credits, ARRAY_COUNT(info_credits));
            gPrevMainMenuPage = PAGE_MAIN;
            gPrevMainMenuButton = gSDCard ? 3 : 2;
            break;
        case PAGE_SETUP_GUIDE:
            main_menu_create_info(frame, info_setup_guide, ARRAY_COUNT(info_setup_guide));
            gPrevMainMenuPage = PAGE_HELP;
            gPrevMainMenuButton = 0;
            break;
        case PAGE_EDITOR_CONTROLS:
            main_menu_create_info(frame, info_editor_controls, ARRAY_COUNT(info_editor_controls));
            gPrevMainMenuPage = PAGE_HELP;
            gPrevMainMenuButton = 1;
            break;
        case PAGE_SHARE_LEVELS:
            main_menu_create_info(frame, info_level_sharing, ARRAY_COUNT(info_level_sharing));
            gPrevMainMenuPage = PAGE_HELP;
            gPrevMainMenuButton = 2;
            break;
        case PAGE_CHANGELOG:
            main_menu_create_info(frame, info_v1_1_changelog, ARRAY_COUNT(info_v1_1_changelog));
            gPrevMainMenuPage = PAGE_HELP;
            gPrevMainMenuButton = 3;
            break;
        case PAGE_NO_SD_CARD:
            main_menu_create_info(frame, info_no_sd_card, ARRAY_COUNT(info_no_sd_card));
            gPrevMainMenuPage = PAGE_MAIN;
            gPrevMainMenuButton = 0;
            break;
        // Level pages
        case PAGE_PLAY_LEVEL:
            main_menu_create_level_list(frame);
            gPrevMainMenuPage = PAGE_MAIN;
            gPrevMainMenuButton = 1;
            break;
        case PAGE_LOAD_LEVEL:
            main_menu_create_level_list(frame);
            gPrevMainMenuPage = PAGE_BUILD;
            gPrevMainMenuButton = 1;
            break;
        // Keyboard pages
        case PAGE_LEVEL_NAME:
            bzero(main_menu_keyboard_input, sizeof(main_menu_keyboard_input));
            main_menu_create_keyboard_page(frame, "Enter level name:", keyboard_start_level, TRUE);
            gPrevMainMenuPage = PAGE_NEW_LEVEL;
            gPrevMainMenuButton = 3;
            break;
        case PAGE_CHANGE_NAME:
            strncpy(main_menu_keyboard_input, mb64_sram_configuration.author, MAX_USERNAME_SIZE);
            main_menu_create_keyboard_page(frame, "Enter new author name:", keyboard_set_author_name, FALSE);
            gPrevMainMenuPage = PAGE_BUILD;
            gPrevMainMenuButton = 2;
            break;
        case PAGE_AUTHOR:
            if (gSupportsLibpl) {
                const char *rhdc_username = libpl_get_my_rhdc_username();
                if (rhdc_username) {
                    strncpy(main_menu_keyboard_input, rhdc_username, MAX_USERNAME_SIZE);
                }
            }
            main_menu_create_keyboard_page(frame, "Enter your username:", keyboard_set_author_name, FALSE);
            gPrevMainMenuPage = PAGE_NONE;
            break;
    }

    if (animate) main_menu_page_change_animate(frame, FALSE);
}

MenuStyle main_menu_style = {0};

void main_menu_loop(MenuComponent *m, UNUSED s16 x, UNUSED s16 y) {
    set_menu_style(main_menu_style);

    if (gChangePage != PAGE_NONE) {
        dealloc_component(gMainMenuPageHandler->base.child);
        create_page(gChangePage, TRUE);
        gChangePage = PAGE_NONE;
    }
}

void set_page_to_level_list(void) {
    gCurrMainMenuPage = PAGE_LOAD_LEVEL;
    gLevelSelectorIndex = 0;
    if (!gSDCard) {
        gCurrMainMenuPage = PAGE_MAIN;
    }
}

void set_initial_menu_page(void) {
    gCurrMainMenuPage = PAGE_MAIN;
    if (!gSDCard) {
        gCurrMainMenuPage = PAGE_NO_SD_CARD;
    } else if (mb64_sram_configuration.author[0] == 0) {
        gCurrMainMenuPage = PAGE_AUTHOR;
    }
}

void init_main_menu(int page) {
    FrameComponent *main = init_dynamic_component(gMenuRoot, main_menu_loop);
    gMainMenuPageHandler = main;

    create_page(page, FALSE);
}

void reset_main_menu_state(void) {
    gMB64LevelLoaded = FALSE;
    gMainMenuPageHandler = NULL;
    gPrevMainMenuPage = PAGE_NONE;
}
