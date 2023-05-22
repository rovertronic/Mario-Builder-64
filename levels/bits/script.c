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
#include "levels/bits/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_bits_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _bits_segment_7SegmentRomStart, _bits_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x0A, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _sky_yay0SegmentRomStart, _sky_yay0SegmentRomEnd), 
	LOAD_YAY0(0x06, _group14_yay0SegmentRomStart, _group14_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group14_geoSegmentRomStart, _group14_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_15), 
	JUMP_LINK(script_func_global_1), 
	LOAD_MODEL_FROM_GEO(MODEL_FOUNTAIN, fountain_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BITS_WARP_PIPE, warp_pipe_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BITS_STAIRS, bits_stairs_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_MGB, mgba_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_TVSHOP, tvshop_geo),

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, bits_area_1),
		WARP_NODE(0x01, LEVEL_TTM, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02, LEVEL_THI, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x03, LEVEL_TTC, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x04, LEVEL_RR, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x05/*ok_d*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x06/*ok_w*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x07 /*13_d*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x08 /*14_w*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x09/*14_w*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B/*14_d*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0A/*spawn*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0C/*escape*/, LEVEL_CASTLE, 0x01, 0x1F, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0D/*c15_w*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0E/*c15_d*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(241 /*death!*/, LEVEL_BITS, 0x01, 0x0D, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_BITS_STAIRS, 12942, -7, 4578, 0, 0, 0, 0x00000000, bhvBitsStairs),
		OBJECT(MODEL_NONE, 9343, 5134, -7103, 0, -88, 0, (0x05 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 404, 5134, 9306, 0, 2, 0, (0x07 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -7689, 4646, 59, 0, -88, 0, (0x0B << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -3565, 315, -74, 0, 92, 0, (0x0D << 16), bhvDeathWarp),
		OBJECT(MODEL_FOUNTAIN, 0, 0, 0, 0, 0, 0, 0x00000000, bhvFountain),
		OBJECT(MODEL_MGB, 12196, 1004, -1200, 0, 0, 0, (3 << 16), bhvMGBA),
		OBJECT(MODEL_BITS_WARP_PIPE, 9762, 4827, -7207, 0, 0, 0, (1 << 16), bhvWarpPipe),
		OBJECT(MODEL_BITS_WARP_PIPE, 409, 4827, 9558, 0, 0, 0, (2 << 16), bhvWarpPipe),
		OBJECT(MODEL_BITS_WARP_PIPE, -7963, 4376, 24, 0, 0, 0, (3 << 16), bhvWarpPipe),
		OBJECT(MODEL_NONE, 10879, 27, 4595, 0, -90, 0, (0x0A << 16), bhvAirborneWarp),
		MARIO_POS(0x01, 0, -832, 82, 3851),
		OBJECT(MODEL_TVSHOP, 12378, 1004, -5475, 0, -90, 0, (0 << 24) | (1 << 16), bhvTvshop),
		OBJECT(MODEL_TVSHOP, 12378, 1004, -5175, 0, -90, 0, (3 << 24) | (1 << 16), bhvTvshop),
		OBJECT(MODEL_TVSHOP, 12378, 1004, -4875, 0, -90, 0, (4 << 24) | (1 << 16), bhvTvshop),
		OBJECT(MODEL_TVSHOP, 12378, 1004, -4575, 0, -90, 0, (5 << 24) | (1 << 16), bhvTvshop),
		OBJECT(MODEL_TVSHOP, 12378, 1004, -4275, 0, -90, 0, (6 << 24) | (1 << 16), bhvTvshop),
		OBJECT(MODEL_TVSHOP, 12378, 1004, -3975, 0, -90, 0, (7 << 24) | (1 << 16), bhvTvshop),
		OBJECT(MODEL_TVSHOP, 12378, 1004, -3675, 0, -90, 0, (9 << 24) | (1 << 16), bhvTvshop),
		OBJECT(MODEL_TVSHOP, 12378, 1004, -3375, 0, -90, 0, (11 << 24) | (1 << 16), bhvTvshop),
		OBJECT(MODEL_NONE, 9343, 5134, -7103, 0, -88, 0, (0x06 << 16), bhvAirborneStarCollectWarp),
		OBJECT(MODEL_NONE, 404, 5134, 9306, 0, 2, 0, (0x08 << 16), bhvAirborneStarCollectWarp),
		OBJECT(MODEL_NONE, -7689, 4646, 59, 0, -88, 0, (0x09 << 16), bhvAirborneStarCollectWarp),
		OBJECT(MODEL_NONE, -3565, 315, -74, 0, 92, 0, (0x0E << 16), bhvAirborneStarCollectWarp),
		TERRAIN(bits_area_1_collision),
		MACRO_OBJECTS(bits_area_1_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, -832, 82, 3851),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
