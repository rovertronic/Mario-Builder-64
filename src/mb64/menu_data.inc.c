u8 mb64_ascii_lut[] = {
    0,0,0,0,0,0,0,0, // 0 - 7
    0,0,0xFE,0,0,0,0,0, // 8 - 15
    0x54,0x55,0x57,0x58,0x56,0,0,0, // 16 - 23
    0,0,0,0,0,0,0,0, // 24 - 31
    0x9E, /* */ 0xF2, /*!*/ 0xF6, /*"*/ 0xFA, /*#*/
    0xF9, /*$*/ 0xF3, /*%*/ 0xE5, /*&*/ 0x3E, /*'*/
    0xE1, /*(*/ 0xE3, /*)*/ 0x00, /***/ 0xE8, /*+*/
    0x6F, /*,*/ 0x9F, /*-*/ 0x3F, /*.*/ 0x70, /*/*/
    0x00, /*0*/ 0x01, /*1*/ 0x02, /*2*/ 0x03, /*3*/
    0x04, /*4*/ 0x05, /*5*/ 0x06, /*6*/ 0x07, /*7*/
    0x08, /*8*/ 0x09, /*9*/ 0xE6, /*:*/ 0xE7, /*;*/
    0x52, /*<*/ 0xE9, /*=*/ 0x53, /*>*/ 0xF4, /*?*/
    0xFD, /*@*/ 0x0A, /*A*/ 0x0B, /*B*/ 0x0C, /*C*/
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

