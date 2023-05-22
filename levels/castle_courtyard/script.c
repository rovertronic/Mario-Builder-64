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
#include "levels/castle_courtyard/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_castle_courtyard_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _castle_courtyard_segment_7SegmentRomStart, _castle_courtyard_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x0A, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _outside_yay0SegmentRomStart, _outside_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group9_yay0SegmentRomStart, _group9_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group9_geoSegmentRomStart, _group9_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_10), 
	LOAD_MODEL_FROM_GEO(MODEL_EDWARD, edward_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_FLAPPY_PIPE, flappy_pipe_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_SNAKEBALL, snakeball_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, castle_courtyard_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_1UP, 5, 606, -556, 0, 0, 0, 0x00000000, bhvSnakeFood),
		OBJECT(MODEL_NONE, 0, 570, 0, 0, 0, 0, (0x0A << 16), bhvInstantActiveWarp),
		TERRAIN(castle_courtyard_area_1_collision),
		MACRO_OBJECTS(castle_courtyard_area_1_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, castle_courtyard_area_2),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_EDWARD, 0, 0, 0, 0, 0, 0, 0x00000000, bhvEdwardMother),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, 0, 0, (0x0A << 16), bhvInstantActiveWarp),
		TERRAIN(castle_courtyard_area_2_collision),
		MACRO_OBJECTS(castle_courtyard_area_2_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(3, castle_courtyard_area_3),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, 0, 0, (0x0A << 16), bhvInstantActiveWarp),
		TERRAIN(castle_courtyard_area_3_collision),
		MACRO_OBJECTS(castle_courtyard_area_3_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_STREAMED_BAD_APPLE),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(4, castle_courtyard_area_4),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 1860, 0, 0, 0, 0, 0, 0x00000000, bhvFlappyPipe),
		OBJECT(MODEL_NONE, 0, -78, -6, 0, 90, 0, (0x0A << 16), bhvInstantActiveWarp),
		TERRAIN(castle_courtyard_area_4_collision),
		MACRO_OBJECTS(castle_courtyard_area_4_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(1, 0, 0, 0, 0),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
