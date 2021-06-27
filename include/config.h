#ifndef CONFIG_H
#define CONFIG_H

/**
 * @file config.h
 * A catch-all file for configuring various bugfixes and other settings
 * (maybe eventually) in SM64
 */

// Bug Fixes
// --| US Version Nintendo Bug Fixes
/// Fixes bug where obtaining over 999 coins sets the number of lives to 999 (or -25)
#define BUGFIX_MAX_LIVES (0 || VERSION_US || VERSION_EU || VERSION_SH)
/// Fixes bug where the Boss music won't fade out after defeating King Bob-omb
#define BUGFIX_KING_BOB_OMB_FADE_MUSIC (0 || VERSION_US || VERSION_EU || VERSION_SH)
/// Fixes bug in Bob-Omb Battlefield where entering a warp stops the Koopa race music
#define BUGFIX_KOOPA_RACE_MUSIC (0 || VERSION_US || VERSION_EU || VERSION_SH)
/// Fixes bug where Piranha Plants do not reset their action state when the
/// player exits their activation radius.
#define BUGFIX_PIRANHA_PLANT_STATE_RESET (0 || VERSION_US || VERSION_EU || VERSION_SH)
/// Fixes bug where sleeping Piranha Plants damage players that bump into them
#define BUGFIX_PIRANHA_PLANT_SLEEP_DAMAGE (0 || VERSION_US || VERSION_SH)
/// Fixes bug where it shows a star when you grab a key in bowser battle stages
#define BUGFIX_STAR_BOWSER_KEY (0 || VERSION_US || VERSION_EU || VERSION_SH)

// Support Rumble Pak
//#define ENABLE_RUMBLE (1 || VERSION_SH)

// Clear RAM on boot
#define CLEARRAM 1

// Screen Size Defines
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// Border Height Define for NTSC Versions
#ifdef TARGET_N64
#ifndef VERSION_EU
#define BORDER_HEIGHT 0
#else
#define BORDER_HEIGHT 0
#endif
#else
// What's the point of having a border?
#define BORDER_HEIGHT 0

#endif

// --ultrasm64-extbounds specific settings--
// Enable widescreen (16:9) support
#define WIDE
// When this option is enabled, LODs will ONLY work on console.
// When this option is disabled, LODs will work regardless of whether console or emulator is used.
// Regardless of whether this setting is enabled or not, you can use gIsConsole to wrap your own code in a console check.
#define AUTO_LOD
// Skip peach letter cutscene
#define PEACH_SKIP
// Remove course specific camera processing
#define CAMERA_FIX
// Increase the maximum pole length (it will treat bparam1 and bparam2 as a single value)
#define LONGER_POLES
// Disable lives and hide the lives counter
#define DISABLE_LIVES
// Disable AA (Recommended: it changes nothing on emulator, and it makes console run better)
#define DISABLE_AA
// Fix instant warp offset not working when warping across different areas
#define INSTANT_WARP_OFFSET_FIX
// Allows Mario to ledgegrab sloped floors
#define NO_FALSE_LEDGEGRABS
// Allows Mario to jump kick on steep surfaces that are set to be non slippery, instead of being forced to dive
#define JUMP_KICK_FIX
// Disables fall damage
#define NO_FALL_DAMAGE
// Disables the scream that mario makes when falling off a great height (this is separate from actual fall damage)
//#define NO_FALL_DAMAGE_SOUND
// Number of coins to spawn the "100 coin" star. If you remove the define altogether, then there won't be a 100 coin star at all.
#define X_COIN_STAR 100
// Platform displacement 2 also known as momentum patch. Makes Mario keep the momemtum from moving platforms. Breaks treadmills.
#define PLATFORM_DISPLACEMENT_2
// Whether a tree uses snow particles or not is decided via the model IDs instead of the course number
#define TREE_PARTICLE_FIX
// Stars don't kick you out of the level
// #define NON_STOP_STARS
// Uncomment this if you want global star IDs (useful for creating an open world hack ala MVC)
//#define GLOBAL_STAR_IDS
// Uncomment this if you want to skip the title screen (Super Mario 64 logo)
//#define SKIP_TITLE_SCREEN
// Uncomment this if you want to keep the mario head and not skip it
//#define KEEP_MARIO_HEAD
// Number of possible unique model ID's (keep it higher than 256)
#define MODEL_ID_COUNT 256

// If you want to change the extended boundaries mode, go to engine/extended_bounds.h and change EXTENDED_BOUNDS_MODE

#endif // CONFIG_H
