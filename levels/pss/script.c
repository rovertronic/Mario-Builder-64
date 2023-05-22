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
#include "levels/pss/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_pss_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _pss_segment_7SegmentRomStart, _pss_segment_7SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _mountain_yay0SegmentRomStart, _mountain_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group8_yay0SegmentRomStart, _group8_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group8_geoSegmentRomStart, _group8_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_9), 
	LOAD_MODEL_FROM_GEO(0xFF, valve_geo), 
	LOAD_MODEL_FROM_GEO(0xFE, gatess_geo), 
	LOAD_MODEL_FROM_GEO(0xFD, slob_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, pss_area_1),
		WARP_NODE(0x0A, LEVEL_PSS, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(240, LEVEL_CASTLE, 0x01, 0x2A, WARP_NO_CHECKPOINT),
		WARP_NODE(241, LEVEL_CASTLE, 0x01, 0x29, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ATM, -1340, -222, -3710, 0, 48, 0, 0x00000000, bhvATM),
		OBJECT(MODEL_EXCLAMATION_BOX, 9112, -8083, -8547, 0, 90, 0, 0x00030000, bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 1148, 57, -3490, 0, 90, 0, 0x00030000, bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -4455, -1723, -1077, 0, 90, 0, 0x00030000, bhvExclamationBox),
		OBJECT(0xFE, -8, 204, 3963, 0, 0, 0, 0x00010000, bhv_SSGate),
		MARIO_POS(0x01, 0, -993, 9407, 3823),
		OBJECT(MODEL_RED_COIN, -7721, -1239, -637, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 6317, 1593, -9061, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 5080, 2309, -3007, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -108, -6422, -8976, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -8, -222, 4486, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -8, 393, -850, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 850, -2286, 2327, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -10210, -1323, 1581, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, -8, 45, 3487, 0, 0, 0, 0x00000000, bhvHiddenRedCoinStar),
		OBJECT(MODEL_PURPLE_SWITCH, 3178, 2309, -5191, 0, 90, 0, 0x0A000000, bhvPurpleSwitchHiddenBoxes),
		OBJECT(MODEL_NONE, -4481, -5897, -8236, 0, 0, 0, 0x00010000, bhv_SafeZone),
		OBJECT(MODEL_NONE, 3585, -6500, -9028, 0, 0, 0, 0x00020000, bhv_SafeZone),
		OBJECT(MODEL_NONE, 3717, 1593, 1118, 0, 0, 0, 0x00010000, bhv_SafeZone),
		OBJECT(MODEL_NONE, 65, 1593, -5960, 0, 0, 0, 0x00010000, bhv_SafeZone),
		OBJECT(0xFD, -4824, -2037, -2019, 0, 0, 0, 0x00000000, bhvSlob),
		OBJECT(0xFD, -5432, -2037, 504, 0, 50, 0, 0x00000000, bhvSlob),
		OBJECT(0xFD, -9589, -2037, -617, 0, 112, 0, 0x00000000, bhvSlob),
		OBJECT(0xFD, -2765, -6512, -8080, 0, -93, 0, 0x00000000, bhvSlob),
		OBJECT(0xFD, -3174, -6512, -8625, 0, -1, 0, 0x00000000, bhvSlob),
		OBJECT(0xFD, 7075, -8601, -9181, 0, -93, 0, 0x00000000, bhvSlob),
		OBJECT(MODEL_NONE, -939, 9617, 3824, 0, -90, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_CAP_SWITCH, 9891, -8131, -9024, 0, 90, 0, 0x00030000, bhvCapSwitch),
		OBJECT(0xFF, -108, -6604, -8976, 0, 0, 0, 0x00000000, bhvValve),
		OBJECT(0xFF, 418, -6609, -9914, 0, 0, 0, 0x00010000, bhvValve),
		OBJECT(0xFF, 1248, -6625, -9179, 0, 0, 0, 0x00000000, bhvValve),
		OBJECT(0xFF, -652, -6629, -7499, 0, 0, 0, 0x00010000, bhvValve),
		OBJECT(0xFF, -1161, -6621, -8235, 0, 0, 0, 0x00000000, bhvValve),
		OBJECT(0xFF, 5080, 2293, -4061, 0, 0, 0, 0x00000000, bhvValve),
		TERRAIN(pss_area_1_collision),
		MACRO_OBJECTS(pss_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_UNDERGROUND),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, -993, 9407, 3823),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
