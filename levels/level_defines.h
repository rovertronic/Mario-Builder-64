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

STUB_LEVEL("", LEVEL_UNKNOWN_1, COURSE_NONE, 20000, 0x00, 0x00, 0x00, _, _) 
STUB_LEVEL("", LEVEL_UNKNOWN_2, COURSE_NONE, 20000, 0x00, 0x00, 0x00, _, _) 
STUB_LEVEL("", LEVEL_UNKNOWN_3, COURSE_NONE, 20000, 0x00, 0x00, 0x00, _, _) 
DEFINE_LEVEL("SHIP", LEVEL_BBH, COURSE_CCM, bbh, spooky, 20000, 0x00, 0x00, 0x00, _, sCamBBH) 
DEFINE_LEVEL("BONEWORLD", LEVEL_CCM, COURSE_BBH, ccm, snow, 20000, 0x00, 0x00, 0x00, _, sCamCCM) 
DEFINE_LEVEL("HUB", LEVEL_CASTLE, COURSE_NONE, castle_inside, inside, 20000, 0x00, 0x00, 0x00, _, sCamCastle) 
DEFINE_LEVEL("COWBOY", LEVEL_HMC, COURSE_HMC, hmc, cave, 20000, 0x00, 0x00, 0x00, _, sCamHMC) 
DEFINE_LEVEL("RETRO", LEVEL_SSL, COURSE_SSL, ssl, generic, 20000, 0x00, 0x00, 0x00, _, sCamSSL) 
DEFINE_LEVEL("HOT", LEVEL_BOB, COURSE_BOB, bob, generic, 20000, 0x01, 0x00, 0x00, _, sCamBOB) 
DEFINE_LEVEL("ACID", LEVEL_SL, COURSE_SL, sl, snow, 20000, 0x00, 0x00, 0x00, _, sCamSL) 
DEFINE_LEVEL("FAIR", LEVEL_WDW, COURSE_WDW, wdw, grass, 20000, 0x00, 0x00, 0x00, _, sCamWDW) 
DEFINE_LEVEL("CASCADE", LEVEL_JRB, COURSE_JRB, jrb, water, 20000, 0x01, 0x00, 0x00, _, sCamJRB) 
DEFINE_LEVEL("WHOMP FORT 2", LEVEL_THI, COURSE_THI, thi, grass, 20000, 0x00, 0x00, 0x00, _, sCamTHI) 
DEFINE_LEVEL("EMPIRE", LEVEL_TTC, COURSE_TTC, ttc, machine, 20000, 0x00, 0x00, 0x00, _, sCamTTC) 
DEFINE_LEVEL("AGAMEMNON", LEVEL_RR, COURSE_RR, rr, sky, 20000, 0x00, 0x00, 0x00, _, sCamRR) 
DEFINE_LEVEL("OW1 C GROUNDS", LEVEL_CASTLE_GROUNDS, COURSE_NONE, castle_grounds, outside, 20000, 0x00, 0x00, 0x00, _, sCamCastleGrounds) 
DEFINE_LEVEL("BC1 BITDW", LEVEL_BITDW, COURSE_BITDW, bitdw, sky, 20000, 0x01, 0x00, 0x00, _, sCamBitDW) 
DEFINE_LEVEL("VCL VCUTM", LEVEL_VCUTM, COURSE_VCUTM, vcutm, outside, 30000, 0x28, 0x28, 0x28, _, _) 
DEFINE_LEVEL("BC2 BITFS", LEVEL_BITFS, COURSE_BITFS, bitfs, sky, 20000, 0x00, 0x00, 0x00, _, sCamBitFS) 
DEFINE_LEVEL("BOARD", LEVEL_SA, COURSE_SA, sa, inside, 20000, 0x01, 0x00, 0x00, _, sCamSA) 
DEFINE_LEVEL("MOON", LEVEL_BITS, COURSE_NONE, bits, sky, 20000, 0x00, 0x00, 0x00, _, sCamBitS) 
DEFINE_LEVEL("HOUSE", LEVEL_LLL, COURSE_LLL, lll, fire, 20000, 0x00, 0x00, 0x00, _, sCamLLL) 
DEFINE_LEVEL("THWOMP", LEVEL_DDD, COURSE_DDD, ddd, water, 80000, 0x00, 0x00, 0x00, _, sCamDDD) 
DEFINE_LEVEL("FARM", LEVEL_WF, COURSE_WF, wf, grass, 20000, 0x00, 0x00, 0x00, _, sCamWF) 
DEFINE_LEVEL("END CAKE", LEVEL_ENDING, COURSE_CAKE_END, ending, generic, 20000, 0x00, 0x00, 0x00, _, _) 
DEFINE_LEVEL("MINI", LEVEL_CASTLE_COURTYARD, COURSE_NONE, castle_courtyard, outside, 20000, 0x00, 0x00, 0x00, _, sCamCastleCourtyard) 
DEFINE_LEVEL("SEWER", LEVEL_PSS, COURSE_PSS, pss, mountain, 20000, 0x00, 0x00, 0x00, _, sCamPSS) 
DEFINE_LEVEL("MCL COTMC", LEVEL_COTMC, COURSE_COTMC, cotmc, cave, 18000, 0x28, 0x28, 0x28, _, sCamCotMC) 
DEFINE_LEVEL("WCL TOTWC", LEVEL_TOTWC, COURSE_TOTWC, totwc, sky, 20000, 0x20, 0x20, 0x20, _, _) 
DEFINE_LEVEL("B BATTLE1", LEVEL_BOWSER_1, COURSE_BITDW, bowser_1, generic, 60000, 0x40, 0x40, 0x40, _, _) 
DEFINE_LEVEL("SC2 WMOTR", LEVEL_WMOTR, COURSE_WMOTR, wmotr, generic, 20000, 0x00, 0x00, 0x00, _, sCamWMOtR) 
STUB_LEVEL("", LEVEL_UNKNOWN_32, COURSE_NONE, 20000, 0x70, 0x00, 0x00, _, _) 
DEFINE_LEVEL("B BATTLE2", LEVEL_BOWSER_2, COURSE_BITFS, bowser_2, fire, 60000, 0x40, 0x40, 0x40, _, _) 
DEFINE_LEVEL("B BATTLE3", LEVEL_BOWSER_3, COURSE_BITS, bowser_3, generic, 60000, 0x40, 0x40, 0x40, _, _) 
STUB_LEVEL("", LEVEL_UNKNOWN_35, COURSE_NONE, 20000, 0x00, 0x00, 0x00, _, _) 
DEFINE_LEVEL("OKEYS", LEVEL_TTM, COURSE_TTM, ttm, mountain, 20000, 0x00, 0x00, 0x00, _, sCamTTM) 
STUB_LEVEL("", LEVEL_UNKNOWN_37, COURSE_NONE, 20000, 0x00, 0x00, 0x00, _, _) 
STUB_LEVEL("", LEVEL_UNKNOWN_38, COURSE_NONE, 20000, 0x00, 0x00, 0x00, sDynUnk38, _) 
