#ifndef MB64_BUTTONS_H
#define MB64_BUTTONS_H

#include "mb64/gfx/tile.h"

#define DEFINE_CI8_BUTTON(name) \
    const struct ci_texture_define name = { \
        GLUE2(name, _ci8), \
        GLUE2(name, _pal_rgba16), \
        (u8)(ARRAY_COUNT(GLUE2(name, _pal_rgba16)) / 2 - 1), \
    }

#define DEFINE_CI4_BUTTON(name) \
    const struct ci_texture_define name = { \
        GLUE2(name, _ci4), \
        GLUE2(name, _pal_rgba16), \
        (u8)(ARRAY_COUNT(GLUE2(name, _pal_rgba16)) / 2 - 1), \
    }

extern const Gfx mb64_btn_dl_begin[];
extern const Gfx mb64_btn_dl_end[];
extern const Gfx mb64_btn_dl_ci8[];
extern const Gfx mb64_btn_dl_ci4[];
extern const Gfx mb64_btn_dl_ia4[];

extern const struct ci_texture_define mb64_btn_block;
extern const struct ci_texture_define mb64_btn_slab;
extern const struct ci_texture_define mb64_btn_slope;
extern const struct ci_texture_define mb64_btn_outercorner;
extern const struct ci_texture_define mb64_btn_innercorner;
extern const struct ci_texture_define mb64_btn_verticalslab;
extern const struct ci_texture_define mb64_btn_verticalslope;
extern const struct ci_texture_define mb64_btn_cornerslope;
extern const struct ci_texture_define mb64_btn_invertedcorner;
extern const struct ci_texture_define mb64_btn_lowergentle;
extern const struct ci_texture_define mb64_btn_uppergentle;
extern const struct ci_texture_define mb64_btn_intangible;
extern const struct ci_texture_define mb64_btn_water;
extern const struct ci_texture_define mb64_btn_fence;
extern const struct ci_texture_define mb64_btn_ironmesh;
extern const struct ci_texture_define mb64_btn_pole;
extern const struct ci_texture_define mb64_btn_bubblytree;
extern const struct ci_texture_define mb64_btn_palmtree;
extern const struct ci_texture_define mb64_btn_spikytree;
extern const struct ci_texture_define mb64_btn_snowytree;
extern const struct ci_texture_define mb64_btn_farmtree;
extern const struct ci_texture_define mb64_btn_deadtree;
extern const struct ci_texture_define mb64_btn_cullmarker;
extern const struct ci_texture_define mb64_btn_star;
extern const struct ci_texture_define mb64_btn_redcoinstar;
extern const struct ci_texture_define mb64_btn_triggerstar;
extern const struct ci_texture_define mb64_btn_coin;
extern const struct ci_texture_define mb64_btn_coinline;
extern const struct ci_texture_define mb64_btn_verticalcoinline;
extern const struct ci_texture_define mb64_btn_coinring;
extern const struct ci_texture_define mb64_btn_verticalcoinring;
extern const struct ci_texture_define mb64_btn_coinarrow;
extern const struct ci_texture_define mb64_btn_greencoin;
extern const struct ci_texture_define mb64_btn_redcoin;
extern const struct ci_texture_define mb64_btn_bluecoin;
extern const struct ci_texture_define mb64_btn_bluecoinswitch;
extern const struct ci_texture_define mb64_btn_exclamationbox;
extern const struct ci_texture_define mb64_btn_rocketbox;
extern const struct ci_texture_define mb64_btn_vanetalbox;
extern const struct ci_texture_define mb64_btn_wingbox;
extern const struct ci_texture_define mb64_btn_metalbox;
extern const struct ci_texture_define mb64_btn_vanishbox;
extern const struct ci_texture_define mb64_btn_questionbox;
extern const struct ci_texture_define mb64_btn_trigger;
extern const struct ci_texture_define mb64_btn_recoveryheart;
extern const struct ci_texture_define mb64_btn_movingplatform;
extern const struct ci_texture_define mb64_btn_loopplatform;
extern const struct ci_texture_define mb64_btn_purpleswitch;
extern const struct ci_texture_define mb64_btn_timedbox;
extern const struct ci_texture_define mb64_btn_invertedtimedblock;
extern const struct ci_texture_define mb64_btn_box;
extern const struct ci_texture_define mb64_btn_rfbox;
extern const struct ci_texture_define mb64_btn_waterdiamond;
extern const struct ci_texture_define mb64_btn_woodplatform;
extern const struct ci_texture_define mb64_btn_fullwoodplatform;
extern const struct ci_texture_define mb64_btn_signpost;
extern const struct ci_texture_define mb64_btn_bobombbuddy;
extern const struct ci_texture_define mb64_btn_moleman;
extern const struct ci_texture_define mb64_btn_cowboy;
extern const struct ci_texture_define mb64_btn_badgelava;
extern const struct ci_texture_define mb64_btn_badgefall;
extern const struct ci_texture_define mb64_btn_badgedefense;
extern const struct ci_texture_define mb64_btn_badgedamage;
extern const struct ci_texture_define mb64_btn_badgegills;
extern const struct ci_texture_define mb64_btn_badgefins;
extern const struct ci_texture_define mb64_btn_badgehp;
extern const struct ci_texture_define mb64_btn_badgemana;
extern const struct ci_texture_define mb64_btn_badgegreed;
extern const struct ci_texture_define mb64_btn_badgetime;
extern const struct ci_texture_define mb64_btn_badgemagnet;
extern const struct ci_texture_define mb64_btn_badgeburn;
extern const struct ci_texture_define mb64_btn_badgesquish;
extern const struct ci_texture_define mb64_btn_badgefeather;
extern const struct ci_texture_define mb64_btn_badgeweight;
extern const struct ci_texture_define mb64_btn_badgesticky;
extern const struct ci_texture_define mb64_btn_badgefeet;
extern const struct ci_texture_define mb64_btn_badgeheal;
extern const struct ci_texture_define mb64_btn_badgebottomless;
extern const struct ci_texture_define mb64_btn_badgeslowfall;
extern const struct ci_texture_define mb64_btn_badgebrittle;
extern const struct ci_texture_define mb64_btn_badgewither;
extern const struct ci_texture_define mb64_btn_noteblock;
extern const struct ci_texture_define mb64_btn_redswitch;
extern const struct ci_texture_define mb64_btn_blueswitch;
extern const struct ci_texture_define mb64_btn_redblock;
extern const struct ci_texture_define mb64_btn_blueblock;
extern const struct ci_texture_define mb64_btn_conveyor;
extern const struct ci_texture_define mb64_btn_fullconveyor;
extern const struct ci_texture_define mb64_btn_upconveyor;
extern const struct ci_texture_define mb64_btn_downconveyor;
extern const struct ci_texture_define mb64_btn_redconveyor;
extern const struct ci_texture_define mb64_btn_redfullconveyor;
extern const struct ci_texture_define mb64_btn_redupconveyor;
extern const struct ci_texture_define mb64_btn_reddownconveyor;
extern const struct ci_texture_define mb64_btn_toad;
extern const struct ci_texture_define mb64_btn_tuxie;
extern const struct ci_texture_define mb64_btn_ukiki;
extern const struct ci_texture_define mb64_btn_ktq;
extern const struct ci_texture_define mb64_btn_goomba;
extern const struct ci_texture_define mb64_btn_biggoomba;
extern const struct ci_texture_define mb64_btn_tinygoomba;
extern const struct ci_texture_define mb64_btn_bobomb;
extern const struct ci_texture_define mb64_btn_chuckya;
extern const struct ci_texture_define mb64_btn_koopa;
extern const struct ci_texture_define mb64_btn_lakitu;
extern const struct ci_texture_define mb64_btn_flyguy;
extern const struct ci_texture_define mb64_btn_snufit;
extern const struct ci_texture_define mb64_btn_thwomp;
extern const struct ci_texture_define mb64_btn_grindel;
extern const struct ci_texture_define mb64_btn_whomp;
extern const struct ci_texture_define mb64_btn_kingwhomp;
extern const struct ci_texture_define mb64_btn_bully;
extern const struct ci_texture_define mb64_btn_chillbully;
extern const struct ci_texture_define mb64_btn_bigbully;
extern const struct ci_texture_define mb64_btn_chiefchilly;
extern const struct ci_texture_define mb64_btn_motos;
extern const struct ci_texture_define mb64_btn_heaveho;
extern const struct ci_texture_define mb64_btn_bulletbill;
extern const struct ci_texture_define mb64_btn_amp;
extern const struct ci_texture_define mb64_btn_piranha;
extern const struct ci_texture_define mb64_btn_bigfirepiranha;
extern const struct ci_texture_define mb64_btn_firepiranha;
extern const struct ci_texture_define mb64_btn_boo;
extern const struct ci_texture_define mb64_btn_bigboo;
extern const struct ci_texture_define mb64_btn_mri;
extern const struct ci_texture_define mb64_btn_scuttlebug;
extern const struct ci_texture_define mb64_btn_spindrift;
extern const struct ci_texture_define mb64_btn_mrblizzard;
extern const struct ci_texture_define mb64_btn_moneybag;
extern const struct ci_texture_define mb64_btn_skeeter;
extern const struct ci_texture_define mb64_btn_pokey;
extern const struct ci_texture_define mb64_btn_rex;
extern const struct ci_texture_define mb64_btn_hammerbro;
extern const struct ci_texture_define mb64_btn_firebro;
extern const struct ci_texture_define mb64_btn_podoboo;
extern const struct ci_texture_define mb64_btn_cosmicphantasm;
extern const struct ci_texture_define mb64_btn_redflame;
extern const struct ci_texture_define mb64_btn_blueflame;
extern const struct ci_texture_define mb64_btn_flamethrower;
extern const struct ci_texture_define mb64_btn_firespitter;
extern const struct ci_texture_define mb64_btn_firespinner;
extern const struct ci_texture_define mb64_btn_bowlingball;
extern const struct ci_texture_define mb64_btn_chicken;
extern const struct ci_texture_define mb64_btn_crablet;
extern const struct ci_texture_define mb64_btn_showrunner;
extern const struct ci_texture_define mb64_btn_spawn;
extern const struct ci_texture_define mb64_btn_smallbox;
extern const struct ci_texture_define mb64_btn_crazybox;
extern const struct ci_texture_define mb64_btn_pipebar;
extern const struct ci_texture_define mb64_btn_bulletmask;
extern const struct ci_texture_define mb64_btn_kingbobomb;
extern const struct ci_texture_define mb64_btn_wiggler;
extern const struct ci_texture_define mb64_btn_bowser;
extern const struct ci_texture_define mb64_btn_bowserbomb;
extern const struct ci_texture_define mb64_btn_check;
extern const struct ci_texture_define mb64_btn_settings;
extern const struct ci_texture_define mb64_btn_blank;
extern const struct ci_texture_define mb64_btn_folderopen;
extern const struct ci_texture_define mb64_btn_pipe;

extern const struct ci_texture_define mb64_btn_folder_gentle_slopes;
extern const struct ci_texture_define mb64_btn_folder_slopes;
extern const struct ci_texture_define mb64_btn_folder_platforms;
extern const struct ci_texture_define mb64_btn_folder_switches;
extern const struct ci_texture_define mb64_btn_folder_boxes;
extern const struct ci_texture_define mb64_btn_folder_fire;
extern const struct ci_texture_define mb64_btn_folder_power_stars;
extern const struct ci_texture_define mb64_btn_folder_coins;
extern const struct ci_texture_define mb64_btn_folder_powerups;
extern const struct ci_texture_define mb64_btn_folder_npcs;
extern const struct ci_texture_define mb64_btn_folder_generic_enemies;
extern const struct ci_texture_define mb64_btn_folder_bullies;
extern const struct ci_texture_define mb64_btn_folder_mechanical_enemies;
extern const struct ci_texture_define mb64_btn_folder_misc_enemies;
extern const struct ci_texture_define mb64_btn_folder_slabs;
extern const struct ci_texture_define mb64_btn_folder_stone_enemies;
extern const struct ci_texture_define mb64_btn_folder_flying_enemies;
extern const struct ci_texture_define mb64_btn_folder_vanilla_bosses;
extern const struct ci_texture_define mb64_btn_folder_diagonal_slopes;
extern const struct ci_texture_define mb64_btn_folder_special_tiles;
extern const struct ci_texture_define mb64_btn_folder_btcm_enemies;
extern const struct ci_texture_define mb64_btn_folder_btcm_bosses;

#endif
