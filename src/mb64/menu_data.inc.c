u8 mb64_ascii_lut[] = {
    0,0,0,0,0,0,0,0, // 0 - 7
    0,0,0xFE,0,0,0,0,0, // 8 - 15
    0x54,0x55,0x57,0x58,0x56,0,0,0, // 16 - 23
    0,0,0,0,0,0,0,0, // 24 - 31
    0x9E, /* */ 0xF2, /*!*/ 0x00, /*"*/ 0x00, /*#*/
    0x00, /*$*/ 0x71, /*%*/ 0xE5, /*&*/ 0x3E, /*'*/
    0xE1, /*(*/ 0xE3, /*)*/ 0x00, /***/ 0x00, /*+*/
    0x6F, /*,*/ 0x9F, /*-*/ 0x3F, /*.*/ 0x70, /*/*/
    0x00, /*0*/ 0x01, /*1*/ 0x02, /*2*/ 0x03, /*3*/
    0x04, /*4*/ 0x05, /*5*/ 0x06, /*6*/ 0x07, /*7*/
    0x08, /*8*/ 0x09, /*9*/ 0xE6, /*:*/ 0x00, /*;*/
    0x52, /*<*/ 0x00, /*=*/ 0x53, /*>*/ 0x00, /*?*/
    0x00, /*@*/ 0x0A, /*A*/ 0x0B, /*B*/ 0x0C, /*C*/
    0x0D, /*D*/ 0x0E, /*E*/ 0x0F, /*F*/ 0x10, /*G*/
    0x11, /*H*/ 0x12, /*I*/ 0x13, /*J*/ 0x14, /*K*/
    0x15, /*L*/ 0x16, /*M*/ 0x17, /*N*/ 0x18, /*O*/
    0x19, /*P*/ 0x1A, /*Q*/ 0x1B, /*R*/ 0x1C, /*S*/
    0x1D, /*T*/ 0x1E, /*U*/ 0x1F, /*V*/ 0x20, /*W*/
    0x21, /*X*/ 0x22, /*Y*/ 0x23, /*Z*/ 0x00, /*[*/
    0x00, /*\*/ 0x00, /*]*/ 0x50, /*^*/ 0x00, /*_*/
    0x00, /*`*/ 0x24, /*a*/ 0x25, /*b*/ 0x26, /*c*/
    0x27, /*d*/ 0x28, /*e*/ 0x29, /*f*/ 0x2A, /*g*/
    0x2B, /*h*/ 0x2C, /*i*/ 0x2D, /*j*/ 0x2E, /*k*/
    0x2F, /*l*/ 0x30, /*m*/ 0x31, /*n*/ 0x32, /*o*/
    0x33, /*p*/ 0x34, /*q*/ 0x35, /*r*/ 0x36, /*s*/
    0x37, /*t*/ 0x38, /*u*/ 0x39, /*v*/ 0x3A, /*w*/
    0x3B, /*x*/ 0x3C, /*y*/ 0x3D, /*z*/ 0x00, /*{*/
    0x51, /*|*/ 0x00, /*}*/ 0x00, /*~*/
};

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

char *mb64_tips[] = {
    "Tip: Use D-Pad ^ to flip certain tiles like slopes or slabs!",
    "Tip: Use D-Pad | to change the camera's\n   zoom level while building!",
    "Tip: Press L and R at the same time to copy\n the tile or object the cursor is on!",
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



void music_type_changed(void);
void music_category_changed(void);
char *mb64_get_category(s32 index, UNUSED char *buffer);
char *mb64_get_waterlevel_name(s32 index, char *buffer);
char *mb64_get_floor_name(s32 index, UNUSED char *buffer);
char *mb64_get_coinstar_str(s32 index, char *buffer);
char *mb64_get_boundaryheight_name(s32 index, char *buffer);
char *mb64_get_custom_mat(s32 index, char *buffer);

struct mb64_settings_button mb64_settings_misc_buttons[] = {
    // {"Coin Star:", &mb64_lopt_coinstar, NULL, 1, mb64_get_coinstar_str, NULL},
    // {"Water Level:", &mb64_lopt_waterlevel, NULL,               65,               mb64_get_waterlevel_name, reload_boundary_and_gfx},
    // {"Costume:", &mb64_lopt_costume, mb64_costume_string_table, ARRAY_COUNT(mb64_costume_string_table), NULL, NULL},
};

#define MISC_COINSTAR_INDEX 0
#define MISC_WATER_INDEX 1
#define MISC_COSTUME_INDEX 2

struct mb64_settings_button mb64_settings_misc_buttons_vanilla[] = {
    {"Coin Star:", &mb64_lopt_coinstar, NULL, 1, mb64_get_coinstar_str, NULL},
    {"Water Level:", &mb64_lopt_waterlevel, NULL,               65,               mb64_get_waterlevel_name, reload_boundary_and_gfx},
};
#define MISCV_COINSTAR_INDEX 0
#define MISCV_WATER_INDEX 1

struct mb64_settings_button mb64_settings_env_buttons[] = {
    //{"Theme:",   &mb64_lopt_theme,   mb64_theme_string_table,   ARRAY_COUNT(mb64_theme_string_table) - 1, NULL, reload_theme},
    //{"Skybox:",  &mb64_lopt_bg,      mb64_bg_string_table,      ARRAY_COUNT(mb64_bg_string_table),    NULL, reload_bg},
    //{"Effect:",  &mb64_lopt_envfx,   mb64_envfx_string_table,   ARRAY_COUNT(mb64_envfx_string_table), NULL, NULL},
};
#define ENV_THEME_INDEX 0
#define ENV_SKYBOX_INDEX 1
#define ENV_EFFECT_INDEX 2

struct mb64_settings_button mb64_settings_boundary_buttons[] = {
    // {"Boundary:", &mb64_lopt_boundary, mb64_bound_string_table, ARRAY_COUNT(mb64_bound_string_table), NULL, reload_boundary_and_gfx},
    // {"Material:",   &mb64_lopt_boundary_mat, NULL, NUM_MATERIALS_PER_THEME, mb64_get_floor_name, reload_boundary_and_gfx}, // Filled in by code
    // {"Height:", &mb64_lopt_boundary_height,   NULL, 65, mb64_get_boundaryheight_name, reload_boundary_and_gfx},
};

#define BOUNDARY_BOUNDARY_INDEX 0
#define BOUNDARY_TILE_INDEX 1
#define BOUNDARY_HEIGHT_INDEX 2

struct mb64_settings_button mb64_settings_music_buttons[] = {
    // {"Type:", &mb64_lopt_seq_seqtype, mb64_music_type_string_table, ARRAY_COUNT(mb64_music_type_string_table), NULL, music_type_changed},
    // {"Album:",   &mb64_lopt_seq_album,  mb64_music_album_string_table,  ARRAY_COUNT(mb64_music_album_string_table), NULL, music_category_changed},
    // {"Song:", NULL, NULL, 0, NULL, NULL}, // Filled in by code
};
#define MUSIC_ALBUM_INDEX 1
#define MUSIC_SONG_INDEX 2

struct mb64_settings_button mb64_settings_mat_selector[] = {
    {"Category:", NULL, NULL, ARRAY_COUNT(mb64_matlist) - 1, mb64_get_category,   NULL},
    {"Material:", NULL, NULL, 0, mb64_get_custom_mat, NULL},
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

struct mb64_settings_button mb64_settings_other_selectors[] = {
    {"Fence:", &mb64_curr_custom_theme.fence, mb64_fence_names, ARRAY_COUNT(mb64_fence_names), NULL, NULL},
    {"Iron Mesh:", &mb64_curr_custom_theme.bars, mb64_bar_names, ARRAY_COUNT(mb64_bar_names), NULL, NULL},
    {"Water:", &mb64_curr_custom_theme.water, mb64_water_names, ARRAY_COUNT(mb64_water_names), NULL, NULL},
};

char *mb64_settings_menu_names[] = {
    "Environment",
    "Level Boundary",
    "Music",
    "Miscellaneous",
    "System",
};

char *mb64_settings_system_buttons[] = {
    "Save & Quit",
    "Play Level",
    "Set Level Thumbnail",
    //"Level Size:",
    //"Apply Size Change (Dangerous!)",
};

extern void draw_mb64_settings_env(f32 xoff, f32 yoff);
extern void draw_mb64_settings_boundary(f32 xoff, f32 yoff);
extern void draw_mb64_settings_music(f32 xoff, f32 yoff);
extern void draw_mb64_settings_misc(f32 xoff, f32 yoff);
extern void draw_mb64_settings_system(f32 xoff, f32 yoff);
extern void draw_mb64_settings_misc_vanilla(f32 xoff, f32 yoff);
void (*mb64_settings_menus[])(f32, f32) = {
    draw_mb64_settings_env,
    draw_mb64_settings_boundary,
    draw_mb64_settings_music,
    draw_mb64_settings_misc,
    draw_mb64_settings_system,
};

u8 mb64_settings_menu_lengths[] = {
    ARRAY_COUNT(mb64_settings_env_buttons),
    ARRAY_COUNT(mb64_settings_boundary_buttons),
    ARRAY_COUNT(mb64_settings_music_buttons),
    ARRAY_COUNT(mb64_settings_misc_buttons),
    ARRAY_COUNT(mb64_settings_system_buttons),
};

#define SETTINGS_ENV_INDEX 0
#define SETTINGS_BOUNDARY_INDEX 1
#define SETTINGS_MUSIC_INDEX 2
#define SETTINGS_MISC_INDEX 3
#define SETTINGS_SYSTEM_INDEX 4

void song_changed(void);

// These get copied over to the above array
struct mb64_settings_button mb64_settings_music_albums[] = {
    // {"Song:",  &mb64_lopt_seq_song, mb64_music_vanilla_string_table, ARRAY_COUNT(mb64_music_vanilla_string_table), NULL, song_changed},
    // {"Song:",  &mb64_lopt_seq_song, mb64_music_btcm_string_table, ARRAY_COUNT(mb64_music_btcm_string_table), NULL, song_changed},
    // {"Song:",  &mb64_lopt_seq_song, mb64_music_romhack_string_table, ARRAY_COUNT(mb64_music_romhack_string_table), NULL, song_changed},
    // {"Song:",  &mb64_lopt_seq_song, mb64_music_retro_string_table, ARRAY_COUNT(mb64_music_retro_string_table), NULL, song_changed},
};

struct mb64_settings_button mb64_settings_backtomainmenu[] = {
};

char *mb64_gamemode_string_table[] = {
    "Vanilla SM64",
    "Cursed Mirror",
};

char *mb64_levelsize_string_table[] = {
    "Small (32)",
    "Medium (48)",
    "Large (64)",
};

char *mb64_template_string_table[] = {
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

struct mb64_settings_button mb64_mode_settings_buttons[] = {
    {"Mode:", &mb64_lopt_game, mb64_gamemode_string_table, ARRAY_COUNT(mb64_gamemode_string_table), NULL, NULL},
    {"Size:", &mb64_lopt_size, mb64_levelsize_string_table, ARRAY_COUNT(mb64_levelsize_string_table), NULL, NULL},
    {"Template:", &mb64_lopt_template, mb64_template_string_table, ARRAY_COUNT(mb64_template_string_table), NULL, NULL},
};

