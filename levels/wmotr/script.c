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

/* Fast64 begin persistent block [includes] */
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/wmotr/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_wmotr_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _wmotr_segment_7SegmentRomStart, _wmotr_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x0A, _wdw_skybox_yay0SegmentRomStart, _wdw_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _sky_yay0SegmentRomStart, _sky_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group8_yay0SegmentRomStart, _group8_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group8_geoSegmentRomStart, _group8_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_9), 
	LOAD_MODEL_FROM_GEO(0xFF, palm_tree_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, wmotr_area_1),
		WARP_NODE(0x0A, LEVEL_WMOTR, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(240/*win*/, LEVEL_DDD, 0x01, 0x02, WARP_NO_CHECKPOINT),
		WARP_NODE(241/*death*/, LEVEL_DDD, 0x01, 0x03, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_1UP, 5381, 4396, -6827, 0, 0, 0, 0x00000000, bhv1Up),
		OBJECT(MODEL_EXCLAMATION_BOX, -7936, 5366, 9283, 0, 0, 0, (7 << 16), bhvExclamationBox),
		OBJECT(MODEL_CAP_SWITCH, 8873, 8131, -6717, 0, 0, 0, 0x00000000, bhvCapSwitch),
		MARIO_POS(0x01, 0, -5642, 2184, -354),
		OBJECT(MODEL_NOTEBLOCK, -8719, 2446, -2991, 0, 0, 0, 0x00000000, bhvNoteblock),
		OBJECT(MODEL_NOTEBLOCK, 5290, 4425, -834, 0, 0, 0, 0x00000000, bhvNoteblock),
		OBJECT(0xFF, -5289, 2185, -3431, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(0xFF, 5221, 4181, -391, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(0xFF, 4983, 4181, -6091, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(0xFF, 4126, 4181, -6562, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(0xFF, 9618, 8131, -6282, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(0xFF, 8127, 8131, -6282, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(0xFF, -9701, 3144, -3419, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(0xFF, -9738, 3993, -6895, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(0xFF, 9618, 8131, -5737, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(0xFF, 8127, 8131, -5737, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(0xFF, 9618, 8131, -5145, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(0xFF, 8127, 8131, -5145, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(0xFF, 15348, 9508, -1127, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_RED_COIN, 4555, 3379, -2721, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -4910, 4769, -6261, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 10561, 7784, 8304, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -1854, 2095, -1594, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 4577, 4194, -6557, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 14835, 9508, -659, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -3781, 5800, 8981, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 4669, 4935, -12133, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, 3571, 4555, -934, 0, 0, 0, 0x00000000, bhvHiddenRedCoinStar),
		OBJECT(MODEL_EXCLAMATION_BOX, -5788, 2496, -3012, 0, 0, 0, (0 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 9428, 8503, -4341, 0, 0, 0, (0 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -1492, 2510, -1979, 0, 0, 0, (0 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 4231, 5354, -12523, 0, 0, 0, (0 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 15245, 9863, -302, 0, 0, 0, (0 << 16), bhvExclamationBox),
		OBJECT(MODEL_NONE, -5746, 3402, -34, 0, -180, 0, (0x0A << 16), bhvSpinAirborneWarp),
		TERRAIN(wmotr_area_1_collision),
		MACRO_OBJECTS(wmotr_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_UNDERGROUND),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, -5642, 2184, -354),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
