#ifndef SEGMENT_NAMES_H
#define SEGMENT_NAMES_H

/**
 * TLB Segment Names
 * 
 * Most are set in sm64.ld, Makefile.split, and in level scripts, some are set elsewuere.
 * If you change these numbers, make sure to also change them in Makefile.split,
 *  and in your level scripts (in places marked with *seg*).
 * 
 * TODO: Make this an enum without breaking sm64.ld
 * TODO: Find a way to use these with SEG_ADDRESS in sm64.ld without breaking Fast64
 * TODO: Find a way to use these with SEG_ADDRESS in Makefile.split
 */

#define SEGMENT_MAIN                 0x00 // | Segment  0 | General Segment, includes most of /src/ (engine, buffers, menu helpers, audio, etc.)
#define SEGMENT_RENDER               0x01 // | Segment  1 | SPTask, GFX pool buffer
#define SEGMENT_SEGMENT2             0x02 // | Segment  2 | Segment 2 (Fonts, Text, etc)
#define SEGMENT_MB64_BUTTONS         0x03 // | Segment  3 | Editor button textures (MAKE only)
#define SEGMENT_GROUP_GLOBAL_YAY0    0x04 // | Segment  4 | /actors/group_global_yay0, also includes boot (/src/boot/)
#define SEGMENT_UNUSED_05            0x05 // | Segment  5 |
#define SEGMENT_GROUP_THEME_YAY0     0x06 // | Segment  6 | Theme actor yay0 (group_btcm / group_vanilla)
#define SEGMENT_LEVEL_DATA           0x07 // | Segment  7 | Level Data (menu seg7)
#define SEGMENT_UNUSED_08            0x08 // | Segment  8 |
#define SEGMENT_UNUSED_09            0x09 // | Segment  9 |
#define SEGMENT_SKYBOX               0x0A // | Segment 10 | Skybox textures (/textures/skyboxes/)
#define SEGMENT_EFFECT_YAY0          0x0B // | Segment 11 | effect_yay0
#define SEGMENT_UNUSED_0C            0x0C // | Segment 12 |
#define SEGMENT_GROUP_THEME_GEO      0x0D // | Segment 13 | Theme actor geo (group_btcm / group_vanilla)
#define SEGMENT_LEVEL_SCRIPT         0x0E // | Segment 14 | Levelscript
#define SEGMENT_UNUSED_0F            0x0F // | Segment 15 |
#define SEGMENT_UNUSED_10            0x10 // | Segment 16 |
#define SEGMENT_MARIO_ANIMS          0x11 // | Segment 17 | Mario Animations
#define SEGMENT_UNKNOWN_18           0x12 // | Segment 18 |
#define SEGMENT_BEHAVIOR_DATA        0x13 // | Segment 19 | Behavior Data
#define SEGMENT_UNUSED_14            0x14 // | Segment 20 |
#define SEGMENT_UNUSED_15            0x15 // | Segment 21 |
#define SEGMENT_UNUSED_16            0x16 // | Segment 22 |
#define SEGMENT_GROUP_GLOBAL_GEO     0x17 // | Segment 23 | /actors/group_global_geo
#define SEGMENT_UNUSED_18            0x18 // | Segment 24 |
#define SEGMENT_EU_TRANSLATION       0x19 // | Segment 25 | EU language translations
#define SEGMENT_UNKNOWN_26           0x1A // | Segment 26 |
#define SEGMENT_UNKNOWN_27           0x1B // | Segment 27 |
#define SEGMENT_UNKNOWN_28           0x1C // | Segment 28 |
#define SEGMENT_UNKNOWN_29           0x1D // | Segment 29 |
#define SEGMENT_UNKNOWN_30           0x1E // | Segment 30 |
#define SEGMENT_UNKNOWN_31           0x1F // | Segment 31 |

#define SEG_ADDRESS(segment) ((segment) << 24)

#endif
