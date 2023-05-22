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

#include "actors/common0.h"
#include "actors/common1.h"
#include "actors/group0.h"
#include "actors/group1.h"
#include "actors/group2.h"
#include "actors/group3.h"
#include "actors/group4.h"
#include "actors/group5.h"
#include "actors/group6.h"
#include "actors/group7.h"
#include "actors/group8.h"
#include "actors/group9.h"
#include "actors/group10.h"
#include "actors/group11.h"
#include "actors/group12.h"
#include "actors/group13.h"
#include "actors/group14.h"
#include "actors/group15.h"
#include "actors/group16.h"
#include "actors/group17.h"

/* Fast64 begin persistent block [includes] */
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/jrb/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_jrb_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _jrb_segment_7SegmentRomStart, _jrb_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x0B, _effect_yay0SegmentRomStart, _effect_yay0SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _water_yay0SegmentRomStart, _water_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0A, _ssl_skybox_yay0SegmentRomStart, _ssl_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group5_yay0SegmentRomStart, _group5_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group5_geoSegmentRomStart, _group5_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group13_yay0SegmentRomStart, _group13_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group13_geoSegmentRomStart, _group13_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_6), 
	JUMP_LINK(script_func_global_14), 
	LOAD_MODEL_FROM_GEO(MODEL_SSL_PALM_TREE, palm_tree_geo), 
	LOAD_MODEL_FROM_GEO(0xFF, rockplate_geo), 
	LOAD_MODEL_FROM_GEO(0xFE, turnblock_geo), 
	LOAD_MODEL_FROM_GEO(0xFD, lily_geo), 
	LOAD_MODEL_FROM_GEO(0xFC, dcoin_geo), 
	LOAD_MODEL_FROM_GEO(0xFB, yoshi_geo), 
	LOAD_MODEL_FROM_GEO(0xFA, moleman_geo), 
	LOAD_MODEL_FROM_GEO(0xF9, pode_seg_geo), 
	LOAD_MODEL_FROM_GEO(0xF8, pode_head_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BIGMINE, bigmine_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, jrb_area_1),
		WARP_NODE(0x0A, LEVEL_JRB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(240, LEVEL_CASTLE, 0x1, 0x24, WARP_NO_CHECKPOINT),
		WARP_NODE(241, LEVEL_CASTLE, 0x1, 0x25, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ATM, 6141, 4792, 5153, 0, 29, 0, 0x00000000, bhvATM),
		OBJECT(MODEL_BIGMINE, -12740, 4075, 3711, 0, 0, 0, 0x00000000, bhvBigmine),
		OBJECT(MODEL_BIGMINE, -879, 5746, -6088, 0, 0, 0, 0x00000000, bhvBigmine),
		OBJECT(MODEL_BIGMINE, 5325, 3010, 1939, 0, 0, 0, 0x00000000, bhvBigmine),
		OBJECT(MODEL_BIGMINE, 3145, 3227, 8476, 0, 0, 0, 0x00000000, bhvBigmine),
		OBJECT(MODEL_BIGMINE, -6295, 3622, -6210, 0, 0, 0, 0x00000000, bhvBigmine),
		OBJECT(MODEL_BLUE_COIN, 1428, 3236, 8983, 0, 0, 0, 0x00020000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, 483, 3236, 8434, 0, 0, 0, 0x00020000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -660, 3236, 8760, 0, 0, 0, 0x00020000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -931, 3236, 10606, 0, 0, 0, 0x00020000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN_SWITCH, 1980, 3227, 8211, 0, 0, 0, 0x00000000, bhvBlueCoinSwitch),
		OBJECT(0xE7, -7359, 3254, -3765, 0, 0, 0, 0x00020000, bhvChicken),
		OBJECT(0xE7, -2316, 5997, -5725, 0, 0, 0, 0x00020000, bhvChicken),
		OBJECT(0xE7, 4569, 3897, 8388, 0, 0, 0, 0x00020000, bhvChicken),
		OBJECT(0xE7, 5993, 4771, 8217, 0, 0, 0, 0x00020000, bhvChicken),
		OBJECT(MODEL_YELLOW_COIN, -50, 5425, -5246, 0, 90, 0, 0x00010000, bhvYellowCoin),
		OBJECT(MODEL_YELLOW_COIN, 166, 5319, -5913, 0, 90, 0, 0x00010000, bhvYellowCoin),
		OBJECT(MODEL_YELLOW_COIN, -377, 2586, -1549, 0, 90, 0, 0x00010000, bhvYellowCoin),
		OBJECT(MODEL_YELLOW_COIN, 430, 2551, -2631, 0, 90, 0, 0x00010000, bhvYellowCoin),
		OBJECT(0xFC, 405, 5377, -5336, 0, 90, 0, 0x00010000, bhvDragonCoin),
		OBJECT(0xFC, -6766, 2447, -5751, 0, 90, 0, 0x00010000, bhvDragonCoin),
		OBJECT(0xFC, -4600, 2114, -2417, 0, 90, 0, 0x00010000, bhvDragonCoin),
		OBJECT(0xFC, 198, 1325, 6411, 0, 90, 0, 0x00010000, bhvDragonCoin),
		OBJECT(0xFC, 198, 3899, 9873, 0, 90, 0, 0x00010000, bhvDragonCoin),
		OBJECT(MODEL_NONE, -1896, 4083, -3754, 0, 120, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 1702, 1724, 4004, 0, 90, 0, 0x00010000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -6747, 2860, -4956, 0, 90, 0, 0x00010000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -5600, 4494, -4865, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1767, 2047, -820, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1800, 4552, -8272, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 1822, 1208, 7008, 0, 90, 0, 0x00010000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 241, 5886, 86, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 541, 6686, 1899, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_EXCLAMATION_BOX, -10483, 4475, 3711, 0, 0, 0, 0x00010000, bhvExclamationBox),
		OBJECT(MODEL_RED_FLAME, 6770, 4830, 5607, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, 6945, 4803, 3883, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_NONE, -3508, 7051, -473, 0, -19, 0, 0x00040000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -7975, 4860, 10678, 0, -158, 0, 0x00040000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -13380, 4324, -5156, 0, 150, 0, 0x00040000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -9202, 4458, -12259, 0, 99, 0, 0x00040000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 331, 3519, -13362, 0, 42, 0, 0x00040000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 6591, 3796, -5716, 0, -63, 0, 0x00040000, bhvCoinFormation),
		OBJECT(0xEB, -7619, 5381, 11122, 0, 90, 0, 0x00000000, bhvGoldRing),
		OBJECT(0xEB, -13592, 4845, -4809, 0, 90, 0, 0x00000000, bhvGoldRing),
		OBJECT(0xEB, -9671, 4979, -12106, 0, 0, 0, 0x00000000, bhvGoldRing),
		OBJECT(0xEB, 114, 4040, -13636, 0, 0, 0, 0x00000000, bhvGoldRing),
		OBJECT(0xEB, 6938, 4317, -6006, 0, 0, 0, 0x00000000, bhvGoldRing),
		OBJECT(0xEF, 3505, 3010, -693, 0, 0, 0, 0x00000000, bhvGreenCoin),
		OBJECT(0xEF, 6905, 4765, 3231, 0, 0, 0, 0x00000000, bhvGreenCoin),
		OBJECT(0xEF, 5511, 4284, 8013, 0, 0, 0, 0x00000000, bhvGreenCoin),
		OBJECT(0xFD, -931, 3136, 10606, 0, 0, 0, 0x00000000, bhvLily),
		OBJECT(0xFD, -660, 3136, 8760, 0, 39, 0, 0x00000000, bhvLily),
		OBJECT(0xFD, 1966, 3136, 10606, 0, -31, 0, 0x00000000, bhvLily),
		OBJECT(0xFD, 1428, 3136, 8983, 0, -5, 0, 0x00000000, bhvLily),
		OBJECT(0xFD, 2415, 3136, 9757, 0, -5, 0, 0x00000000, bhvLily),
		OBJECT(0xFD, 955, 3136, 10632, 0, 41, 0, 0x00000000, bhvLily),
		OBJECT(0xFD, 483, 3136, 8434, 0, 41, 0, 0x00000000, bhvLily),
		OBJECT(0xFD, 246, 1108, 6413, 0, 41, 0, 0x00000000, bhvLily),
		OBJECT(0xFD, -524, 1108, 5619, 0, -46, 0, 0x00000000, bhvLily),
		OBJECT(0xFD, 884, 1108, 5619, 0, 17, 0, 0x00000000, bhvLily),
		OBJECT(0xFD, 1822, 1108, 7008, 0, 17, 0, 0x00000000, bhvLily),
		OBJECT(0xFA, 6123, 4792, 6232, 0, 0, 0, (2 << 24) | (3 << 16), bhvMoleman),
		OBJECT(0xFA, 6957, 4792, 3651, 0, 0, 0, (2 << 16), bhvMoleman),
		OBJECT(0xFA, 4457, 4765, 6111, 0, -93, 0, (0 << 16), bhvMoleman),
		OBJECT(0xFA, -4542, 8985, -7445, 0, 116, 0, (8 << 16), bhvMoleman),
		OBJECT(MODEL_1UP, 717, 5221, -5782, 0, 90, 0, 0x00000000, bhv1Up),
		OBJECT(MODEL_1UP, -4445, 3333, -2156, 0, 90, 0, 0x00000000, bhv1Up),
		OBJECT(MODEL_NONE, -1202, 2114, -2941, 0, 90, 0, 0x00010000, bhvPokey),
		OBJECT(MODEL_NONE, -2504, 4552, -4189, 0, 90, 0, 0x00010000, bhvPokey),
		OBJECT(MODEL_NONE, 224, 4552, -6847, 0, 90, 0, 0x00010000, bhvPokey),
		OBJECT(MODEL_NONE, 532, 3227, 11852, 0, 90, 0, 0x00010000, bhvPokey),
		OBJECT(MODEL_NONE, 3165, 1325, 7099, 0, 90, 0, 0x00010000, bhvPokey),
		OBJECT(MODEL_EXCLAMATION_BOX, -5613, 4045, -6601, 0, 0, 0, 0x00040000, bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 3397, 3367, 3133, 0, 0, 0, 0x00050000, bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -3241, 2479, -997, 0, 0, 0, 0x00050000, bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -5881, 4064, -3550, 0, 0, 0, 0x00050000, bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -1521, 7517, -7260, 0, 0, 0, 0x00000000, bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -3031, 7388, -495, 0, 0, 0, 0x00000000, bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 4010, 5759, -504, 0, 0, 0, 0x00000000, bhvExclamationBox),
		OBJECT(0xE1, -861, 1249, -478, 0, -180, 0, 0x00000000, bhvRex),
		OBJECT(0xE1, -2666, 1163, -494, 0, -180, 0, 0x00000000, bhvRex),
		OBJECT(0xE1, -6326, 3622, -4675, 0, -180, 0, 0x00000000, bhvRex),
		OBJECT(0xE1, -2411, 1325, 6184, 0, -180, 0, 0x00000000, bhvRex),
		OBJECT(0xE1, 4974, 3354, 8894, 0, -180, 0, 0x00000000, bhvRex),
		OBJECT(MODEL_SSL_PALM_TREE, -690, 1325, 1541, 0, -180, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_SSL_PALM_TREE, -1880, 1325, 2290, 0, -180, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_SSL_PALM_TREE, -1480, 1325, 5226, 0, -180, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_SSL_PALM_TREE, -1686, 1325, 5583, 0, -180, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_SSL_PALM_TREE, -1977, 1325, 6056, 0, -180, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_SSL_PALM_TREE, 1252, 1325, 5158, 0, -180, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_SSL_PALM_TREE, 1821, 1937, -3, 0, -180, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_SSL_PALM_TREE, 2646, 3010, 2832, 0, -180, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_SSL_PALM_TREE, -1471, 3227, 8764, 0, -180, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_SSL_PALM_TREE, 1948, 3227, 11511, 0, -180, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_SSL_PALM_TREE, 1538, 3227, 11814, 0, -180, 0, 0x00000000, bhvTree),
		OBJECT(0xE1, -88, 4552, -8076, 0, -180, 0, 0x00000000, bhvRex),
		OBJECT(0xE1, 6090, 3804, 9027, 0, -180, 0, 0x00000000, bhvRex),
		OBJECT(0xE1, 3597, 4659, 1073, 0, -180, 0, 0x00000000, bhvRex),
		OBJECT(0xE1, -2715, 7189, -7115, 0, -180, 0, 0x01000000, bhvRex),
		OBJECT(0xE1, -3826, 9225, -7006, 0, -180, 0, 0x01000000, bhvRex),
		OBJECT(0xE1, 1241, 6686, 1886, 0, -180, 0, 0x01000000, bhvRex),
		OBJECT(0xE1, 650, 6686, 1626, 0, -180, 0, 0x00000000, bhvRex),
		OBJECT(0xE1, 431, 6686, 2177, 0, -180, 0, 0x00000000, bhvRex),
		OBJECT(0xFB, 5049, 3010, 2661, 0, -180, 0, 0x00000000, bhvRideYoshi),
		OBJECT(MODEL_PURPLE_SWITCH, -3115, 7141, -886, 0, 0, 0, 0x04230000, bhvPurpleSwitchHiddenBoxes),
		OBJECT(MODEL_NONE, -1122, 1249, 2318, 0, 0, 0, 0x00010000, bhv_SafeZone),
		OBJECT(MODEL_NONE, -1064, 1170, -769, 0, 0, 0, 0x00020000, bhv_SafeZone),
		OBJECT(MODEL_NONE, -4164, 4552, -3719, 0, 0, 0, 0x00020000, bhv_SafeZone),
		OBJECT(MODEL_NONE, -5478, 3622, -4413, 0, 0, 0, 0x00020000, bhv_SafeZone),
		OBJECT(MODEL_NONE, 2573, 1937, 1654, 0, 0, 0, 0x00040000, bhv_SafeZone),
		OBJECT(MODEL_NONE, 5135, 3354, 8499, 0, 0, 0, 0x00020000, bhv_SafeZone),
		OBJECT(MODEL_NONE, -1572, 3227, 9930, 0, 0, 0, 0x00020000, bhv_SafeZone),
		OBJECT(MODEL_WOODEN_SIGNPOST, -4455, 2114, -2029, 0, 53, 0, (DIALOG_127 << 16), bhvMessagePanel),
		OBJECT(0xE2, 4041, 5586, 86, 0, 0, 0, 0x00010000, bhvSnakeMain),
		OBJECT(MODEL_NONE, -1122, 1249, 2336, 0, -180, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_STAR, -4358, 9922, -7045, 0, 0, 0, (1 << 24), bhvStar),
		OBJECT(MODEL_STAR, 841, 7008, 4286, 0, 0, 0, 0x03000000, bhvStar),
		OBJECT(0x00, -727, 1273, 3874, 0, -90, 0, 0x00000000, bhvTurnBlock),
		OBJECT(0x00, 1005, 1887, -957, 0, 45, 0, 0x00000000, bhvTurnBlock),
		OBJECT(0x00, -6859, 3106, -4189, 0, 23, 0, 0x00000000, bhvTurnBlock),
		OBJECT(0x00, -6503, 3106, -3341, 0, 23, 0, 0x00010000, bhvTurnBlock),
		OBJECT(0x00, -2650, 1978, 8949, 0, 0, 0, 0x00010000, bhvTurnBlock),
		OBJECT(0x00, -136, 6010, -7502, 0, 0, 0, 0x00000000, bhvTurnBlock),
		OBJECT(0x00, -1926, 6406, -8277, 0, 0, 0, 0x00010000, bhvTurnBlock),
		OBJECT(0x00, -2650, 1778, 8749, 0, 0, 0, 0x00010000, bhvTurnBlock),
		OBJECT(0xFF, -2957, 5268, -5557, 0, 121, 0, 0x00000000, bhvSeesawPlatform),
		OBJECT(0xFF, -959, 6406, -8277, 0, 90, 0, 0x00000000, bhvSeesawPlatform),
		OBJECT(0xFF, -3125, 2704, 9565, 0, -180, 0, 0x00000000, bhvSeesawPlatform),
		OBJECT(0xE3, 3574, 4765, 4909, 0, 0, 0, 0x00020000, bhv_Wallet),
		OBJECT(MODEL_NONE, 93, 3008, 7769, 0, 0, 0, 0x00000000, bhvWaterfallSoundLoop),
		TERRAIN(jrb_area_1_collision),
		MACRO_OBJECTS(jrb_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_JUNGLE),
		TERRAIN_TYPE(TERRAIN_GRASS),
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
