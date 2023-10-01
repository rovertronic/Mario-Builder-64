#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"

#include "actors/common1.h"
#include "actors/group0.h"

/* Fast64 begin persistent block [includes] */
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/castle_grounds/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_castle_grounds_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _castle_grounds_segment_7SegmentRomStart, _castle_grounds_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x0A, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _outside_yay0SegmentRomStart, _outside_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group10_yay0SegmentRomStart, _group10_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group10_geoSegmentRomStart, _group10_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group15_yay0SegmentRomStart, _group15_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group15_geoSegmentRomStart, _group15_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_YAY0(0xb, _effect_yay0SegmentRomStart, _effect_yay0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_11), 
	JUMP_LINK(script_func_global_16), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_03, castle_grounds_geo_0006F4), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, bubbly_tree_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_WARP_PIPE, warp_pipe_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_CASTLE_DOOR, castle_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_METAL_DOOR, metal_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_VCUTM_GRILL, castle_grounds_geo_00070C), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_FLAG, castle_grounds_geo_000660), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_CANNON_GRILL, castle_grounds_geo_000724), 
	LOAD_MODEL_FROM_GEO(MODEL_GIANT_TREE, giant_tree_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CURSED_MIRROR, cursedmirror_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_MIRROR_SHARD, mirror_shard_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_TTRAP, t_trap_geo), 
	//LOAD_MODEL_FROM_GEO(MODEL_CG_SPOTLIGHT, spotlight_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_TUTORIAL_GATE, tutorialgate_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_SHRNLING, shrnling1_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, castle_grounds_area_1),
		WARP_NODE(241/*death warp*/, LEVEL_CASTLE_GROUNDS, 0x01, 0x03, WARP_NO_CHECKPOINT),
		WARP_NODE(0x03/*death dest*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x00, LEVEL_CASTLE_GROUNDS, 0x02, 0x00, WARP_NO_CHECKPOINT),
		WARP_NODE(0x01, LEVEL_CASTLE_GROUNDS, 0x02, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02/*shortcut*/, LEVEL_CASTLE, 0x01, 0x1F, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_1UP, -5, 5050, -10802, 0, 0, 0, 0x00000000, bhv1Up),
		OBJECT(MODEL_1UP, 295, 5050, -10802, 0, 0, 0, 0x00000000, bhv1Up),
		OBJECT(MODEL_1UP, -305, 5050, -10802, 0, 0, 0, 0x00000000, bhv1Up),
		OBJECT(MODEL_NONE, 1, 3026, -6110, 0, 0, 0, (3 << 16), bhvDeathWarp),
		OBJECT(MODEL_CASTLE_CASTLE_DOOR, -75, 2679, -8832, 0, 0, 0, (0 << 16) | (0 << 8), bhvDoorWarp),
		OBJECT(MODEL_CASTLE_CASTLE_DOOR, 75, 2679, -8832, 0, -180, 0, (1 << 16) | (0 << 8), bhvDoorWarp),
		OBJECT(MODEL_GIANT_TREE, -5058, 2227, -2467, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, -6213, 2346, -2226, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, -6504, 2139, -4272, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, -5198, 2170, -4872, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, -4706, 2221, -5249, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, -5511, 2246, -6325, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, -6269, 2298, -7822, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, -5594, 2325, -8309, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, -5950, 2396, -9123, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, -2012, 2513, -4216, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, -1321, 2593, -3808, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, -1906, 2301, -2809, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, -2556, 2338, -3045, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, -124, 2506, -2664, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, 765, 2397, -3071, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, 1126, 2246, -3694, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, 1919, 2168, -4520, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, 1472, 2092, -2391, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, 3159, 2107, -5213, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, 6176, 2097, -5508, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, 5774, 2301, -6792, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, 6404, 2374, -7362, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, 5956, 2406, -8526, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, 5466, 2410, -8945, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, 5864, 2577, -10126, 0, 0, 0, 0x00000000, bhvGiantTree),
		OBJECT(MODEL_GIANT_TREE, 6407, 2748, -10990, 0, 0, 0, 0x00000000, bhvGiantTree),
		MARIO_POS(0x01, 0, -10912, 1287, 11760),
		OBJECT(MODEL_WOODEN_SIGNPOST, 585, 5050, -11312, 0, 90, 0, (DIALOG_093 << 16), bhvMessagePanel),
		OBJECT(0xE3, -591, 5050, -11282, 0, 0, 0, (10 << 16), bhv_Wallet),
		OBJECT(MODEL_NONE, -5, 4733, -11283, 0, 0, 0, (20 << 24) | (2 << 16), bhvWarp),
		TERRAIN(castle_grounds_area_1_collision),
		MACRO_OBJECTS(castle_grounds_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_STREAMED_RAIN_OUTSIDE),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, castle_grounds_area_2),
		WARP_NODE(0x00, LEVEL_CASTLE_GROUNDS, 0x01, 0x00, WARP_NO_CHECKPOINT),
		WARP_NODE(0x01, LEVEL_CASTLE_GROUNDS, 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(0x2, LEVEL_CASTLE_GROUNDS, 0x03, 0x00, WARP_NO_CHECKPOINT),
		WARP_NODE(0x3, LEVEL_CASTLE_GROUNDS, 0x03, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(241/*death warp*/, LEVEL_CASTLE_GROUNDS, 0x01, 0x03, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_CASTLE_CASTLE_DOOR, 822, -174, 3116, 0, 0, 0, 0x00000000, bhvDoorWarp),
		OBJECT(MODEL_CASTLE_CASTLE_DOOR, 922, 1029, -2003, 0, 0, 0, 0x00000000, bhvDoor),
		OBJECT(MODEL_CASTLE_CASTLE_DOOR, 3590, 1605, -1328, 0, 90, 0, 0x00000000, bhvDoor),
		OBJECT(MODEL_CASTLE_CASTLE_DOOR, 972, -174, 3116, 0, -180, 0, 0x00010000, bhvDoorWarp),
		OBJECT(MODEL_CASTLE_CASTLE_DOOR, 9664, 1810, -1253, 0, 90, 0, 0x00030000, bhvDoorWarp), //fuck you. no more crooked
		OBJECT(MODEL_CASTLE_CASTLE_DOOR, 9664, 1810, -1403, 0, -90, 0, 0x00020000, bhvDoorWarp),
		OBJECT(MODEL_MARIO, 6461, 1810, -1327, 0, -90, 0, 0x00000000, bhvMirrorMario),
		OBJECT(MODEL_CURSED_MIRROR, 6252, 2210, -1327, 0, 0, 0, 0x00000000, bhvCursedMirror),
		OBJECT(MODEL_NONE, 2032, 500, 12, 0, 0, 0, (150 << 16), bhvPoleGrabbing),
		OBJECT(MODEL_NONE, 6252, 2010, -1127, 0, 0, 0, 0x00000000, bhvStaticObject),
		TERRAIN(castle_grounds_area_2_collision),
		MACRO_OBJECTS(castle_grounds_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_STREAMED_RAIN_INSIDE),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(3, castle_grounds_area_3),
		WARP_NODE(241/*death warp*/, LEVEL_CASTLE_GROUNDS, 0x01, 0x03, WARP_NO_CHECKPOINT),
		WARP_NODE(0x00/*entrance*/, LEVEL_CASTLE_GROUNDS, 0x02, 0x02, WARP_NO_CHECKPOINT),
		WARP_NODE(0x01/*entrance*/, LEVEL_CASTLE_GROUNDS, 0x02, 0x03, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02/*castle*/, LEVEL_CASTLE, 0x01, 0x2B, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_CASTLE_CASTLE_DOOR, -10810, -128, 75, 0, 90, 0, (1 << 16), bhvDoorWarp),
		OBJECT(MODEL_CASTLE_CASTLE_DOOR, -10810, -128, -75, 0, -90, 0, (0 << 16), bhvDoorWarp),
		OBJECT(MODEL_CASTLE_GROUNDS_CASTLE_DOOR, 9278, -128, -4047, 0, 0, 0, 0x00000000, bhvDoor),
		OBJECT(MODEL_TUTORIAL_GATE, -6941, -128, 3839, 0, -90, 0, (0 << 16), bhvTutorialGate),
		OBJECT(MODEL_TUTORIAL_GATE, -1360, -128, -1742, 0, -90, 0, (1 << 16), bhvTutorialGate),
		OBJECT(MODEL_TUTORIAL_GATE, 7012, -128, 6630, 0, -90, 0, (2 << 16), bhvTutorialGate),
		OBJECT(0xEF, 2144, -128, 573, 0, 0, 0, 0x00000000, bhvGreenCoin),
		OBJECT(0xEA, 3071, -128, 5600, 0, 0, 0, 0x00000000, bhvSamplePlatform1),
		OBJECT(0xEA, 3071, -128, 4983, 0, 0, 0, 0x00000000, bhvSamplePlatform2),
		OBJECT(MODEL_SHOWRUNNER, 9278, 1341, -8514, 0, 0, 0, 0x00000000, bhvShowrunner),
		OBJECT(MODEL_SHRNLING, -7466, -128, 0, 0, -90, 0, (DIALOG_TUTORIAL_1 << 16), bhvShrnling),
		OBJECT(MODEL_SHRNLING, -7466, -128, 3839, 0, 180, 0, (DIALOG_TUTORIAL_2 << 16), bhvShrnling),
		OBJECT(MODEL_SHRNLING, -3626, -128, 1920, 0, 0, 0, (8 << 24) | (DIALOG_TUTORIAL_3 << 16), bhvShrnling),
		OBJECT(MODEL_SHRNLING, -2005, -128, -1621, 0, -50, 0, (DIALOG_TUTORIAL_4 << 16), bhvShrnling),
		OBJECT(MODEL_SHRNLING, 1737, -128, 573, 0, 178, 0, (DIALOG_TUTORIAL_5 << 16), bhvShrnling),
		OBJECT(MODEL_SHRNLING, 2211, -128, 5721, 0, 178, 0, (DIALOG_TUTORIAL_6 << 16), bhvShrnling),
		OBJECT(MODEL_SHRNLING, 5496, -128, 6630, 0, -92, 0, (DIALOG_TUTORIAL_7 << 16), bhvShrnling),
		OBJECT(MODEL_SHRNLING, 8462, -128, 4675, 0, -27, 0, (DIALOG_TUTORIAL_8 << 16), bhvShrnling),
		OBJECT(MODEL_CG_SPOTLIGHT, 10278, 1441, -8514, 0, 0, 0, 0x00000000, bhvSpotlight),
		OBJECT(MODEL_CG_SPOTLIGHT, 8278, 1441, -8514, 0, 0, 0, 0x00000000, bhvSpotlight),
		OBJECT(MODEL_CG_SPOTLIGHT, 7675, -28, -4286, 0, 0, 0, 0x00000000, bhvSpotlight),
		OBJECT(MODEL_CG_SPOTLIGHT, 10881, -28, -4286, 0, 0, 0, 0x00000000, bhvSpotlight),
		OBJECT(MODEL_CG_SPOTLIGHT, 7675, 292, -7856, 0, 0, 0, 0x00000000, bhvSpotlight),
		OBJECT(MODEL_CG_SPOTLIGHT, 10881, 292, -7856, 0, 0, 0, 0x00000000, bhvSpotlight),
		OBJECT(MODEL_CG_SPOTLIGHT, 9278, 292, -7856, 0, 0, 0, 0x00000000, bhvSpotlight),
		OBJECT(MODEL_CG_SPOTLIGHT, 7775, 132, -6155, 0, 0, 0, 0x00000000, bhvSpotlight),
		OBJECT(MODEL_CG_SPOTLIGHT, 10781, 132, -6155, 0, 0, 0, 0x00000000, bhvSpotlight),
		OBJECT(MODEL_TTRAP, 9278, 602, -5830, 0, 0, 0, 0x00000000, bhvTTrap),
		OBJECT(0xE3, 6401, -128, 6630, 0, 0, 0, (10 << 16), bhv_Wallet),
		OBJECT(MODEL_NONE, 9278, -1714, -6106, 0, 0, 0, (100 << 24) | (2 << 16), bhvWarp),
		OBJECT(MODEL_NONE, 9278, 602, -6198, 0, 0, 0, 0x00000000, bhvStaticObject),
		TERRAIN(castle_grounds_area_3_collision),
		MACRO_OBJECTS(castle_grounds_area_3_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, -10912, 1287, 11760),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
