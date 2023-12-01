// Define lists for list of level for macros. Each of the following fields are described:
// Argument 1: Internal ROM name of the level.
// Argument 2: Level enumerator for enum used to identify the level ID.
// Argument 3: Course enumerator for enum used to identify the course ID.
// Argument 4: Shorthand name of the level which should be the name of the levels/ folder of the level.
// Argument 5: The shared texture bin used.
// Argument 6: Acoustic reaches for each levels.
// Argument 7, 8, 9: Echo levels for individual areas.  < Clueless hackers should change these for their levels btw
// Argument 10: Specify dynamic music tables for levels, if specified. _ for none.
// Argument 11: Specify level camera table, if specified. _ for none.

// NOTE: Be sure to edit sZoomOutAreaMasks in camera.c, as there isnt a good way to macro those right now.
// TODO: Figure something out for sZoomOutAreaMasks?

DEFINE_LEVEL("HOT", LEVEL_BOB, COURSE_BOB, bob, 0, 20000, 0x01, 0x00, 0x00, _, sCamBOB)
