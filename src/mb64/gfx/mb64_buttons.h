#ifndef MB64_BUTTONS_H
#define MB64_BUTTONS_H

#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include "macros.h"

enum texture_type {
    TEXTURE_TYPE_CI8,
    TEXTURE_TYPE_CI4,
    TEXTURE_TYPE_RGBA16,
};

struct texture_define {
    const Texture *tex;
    const Texture *pal;
    u16 palCount;
    u8 type;
};

#define DEFINE_CI8(name) \
    const struct texture_define name = { \
        GLUE2(name, _ci8), \
        GLUE2(name, _pal_rgba16), \
        ARRAY_COUNT(GLUE2(name, _pal_rgba16)) / 2, \
        TEXTURE_TYPE_CI8, \
    }

#define DEFINE_CI4(name) \
    const struct texture_define name = { \
        GLUE2(name, _ci4), \
        GLUE2(name, _pal_rgba16), \
        ARRAY_COUNT(GLUE2(name, _pal_rgba16)) / 2, \
        TEXTURE_TYPE_CI4, \
    }

extern const Gfx mb64_btn_dl_begin[];
extern const Gfx mb64_btn_dl_end[];
extern const Gfx mb64_btn_dl_ci8[];
extern const Gfx mb64_btn_dl_ci4[];

extern const struct texture_define mb64_btn_block;
extern const struct texture_define mb64_btn_slab;
extern const struct texture_define mb64_btn_slope;
extern const struct texture_define mb64_btn_outercorner;
extern const struct texture_define mb64_btn_innercorner;
extern const struct texture_define mb64_btn_verticalslab;
extern const struct texture_define mb64_btn_verticalslope;
extern const struct texture_define mb64_btn_cornerslope;
extern const struct texture_define mb64_btn_invertedcorner;
extern const struct texture_define mb64_btn_lowergentle;
extern const struct texture_define mb64_btn_uppergentle;
extern const struct texture_define mb64_btn_intangible;
extern const struct texture_define mb64_btn_water;
extern const struct texture_define mb64_btn_fence;
extern const struct texture_define mb64_btn_ironmesh;
extern const struct texture_define mb64_btn_pole;
extern const struct texture_define mb64_btn_bubblytree;
extern const struct texture_define mb64_btn_palmtree;
extern const struct texture_define mb64_btn_spikytree;
extern const struct texture_define mb64_btn_snowytree;
extern const struct texture_define mb64_btn_farmtree;
extern const struct texture_define mb64_btn_deadtree;
extern const struct texture_define mb64_btn_cullmarker;
extern const struct texture_define mb64_btn_star;
extern const struct texture_define mb64_btn_redcoinstar;
extern const struct texture_define mb64_btn_triggerstar;
extern const struct texture_define mb64_btn_coin;
extern const struct texture_define mb64_btn_coinline;
extern const struct texture_define mb64_btn_verticalcoinline;
extern const struct texture_define mb64_btn_coinring;
extern const struct texture_define mb64_btn_verticalcoinring;
extern const struct texture_define mb64_btn_coinarrow;
extern const struct texture_define mb64_btn_greencoin;
extern const struct texture_define mb64_btn_redcoin;
extern const struct texture_define mb64_btn_bluecoin;
extern const struct texture_define mb64_btn_bluecoinswitch;
extern const struct texture_define mb64_btn_exclamationbox;
extern const struct texture_define mb64_btn_rocketbox;
extern const struct texture_define mb64_btn_vanetalbox;
extern const struct texture_define mb64_btn_wingbox;
extern const struct texture_define mb64_btn_metalbox;
extern const struct texture_define mb64_btn_vanishbox;
extern const struct texture_define mb64_btn_questionbox;
extern const struct texture_define mb64_btn_trigger;
extern const struct texture_define mb64_btn_recoveryheart;
extern const struct texture_define mb64_btn_movingplatform;
extern const struct texture_define mb64_btn_loopplatform;
extern const struct texture_define mb64_btn_purpleswitch;
extern const struct texture_define mb64_btn_timedbox;
extern const struct texture_define mb64_btn_invertedtimedblock;
extern const struct texture_define mb64_btn_box;
extern const struct texture_define mb64_btn_rfbox;
extern const struct texture_define mb64_btn_waterdiamond;
extern const struct texture_define mb64_btn_woodplatform;
extern const struct texture_define mb64_btn_fullwoodplatform;
extern const struct texture_define mb64_btn_signpost;
extern const struct texture_define mb64_btn_bobombbuddy;
extern const struct texture_define mb64_btn_moleman;
extern const struct texture_define mb64_btn_cowboy;
extern const struct texture_define mb64_btn_badge;
extern const struct texture_define mb64_btn_noteblock;
extern const struct texture_define mb64_btn_redswitch;
extern const struct texture_define mb64_btn_blueswitch;
extern const struct texture_define mb64_btn_redblock;
extern const struct texture_define mb64_btn_blueblock;
extern const struct texture_define mb64_btn_conveyor;
extern const struct texture_define mb64_btn_fullconveyor;
extern const struct texture_define mb64_btn_upconveyor;
extern const struct texture_define mb64_btn_downconveyor;
extern const struct texture_define mb64_btn_redconveyor;
extern const struct texture_define mb64_btn_redfullconveyor;
extern const struct texture_define mb64_btn_redupconveyor;
extern const struct texture_define mb64_btn_reddownconveyor;
extern const struct texture_define mb64_btn_toad;
extern const struct texture_define mb64_btn_tuxie;
extern const struct texture_define mb64_btn_ukiki;
extern const struct texture_define mb64_btn_ktq;
extern const struct texture_define mb64_btn_goomba;
extern const struct texture_define mb64_btn_biggoomba;
extern const struct texture_define mb64_btn_tinygoomba;
extern const struct texture_define mb64_btn_bobomb;
extern const struct texture_define mb64_btn_chuckya;
extern const struct texture_define mb64_btn_koopa;
extern const struct texture_define mb64_btn_lakitu;
extern const struct texture_define mb64_btn_flyguy;
extern const struct texture_define mb64_btn_snufit;
extern const struct texture_define mb64_btn_thwomp;
extern const struct texture_define mb64_btn_grindel;
extern const struct texture_define mb64_btn_whomp;
extern const struct texture_define mb64_btn_kingwhomp;
extern const struct texture_define mb64_btn_bully;
extern const struct texture_define mb64_btn_chillbully;
extern const struct texture_define mb64_btn_bigbully;
extern const struct texture_define mb64_btn_chiefchilly;
extern const struct texture_define mb64_btn_motos;
extern const struct texture_define mb64_btn_heaveho;
extern const struct texture_define mb64_btn_bulletbill;
extern const struct texture_define mb64_btn_amp;
extern const struct texture_define mb64_btn_piranha;
extern const struct texture_define mb64_btn_bigfirepiranha;
extern const struct texture_define mb64_btn_firepiranha;
extern const struct texture_define mb64_btn_boo;
extern const struct texture_define mb64_btn_bigboo;
extern const struct texture_define mb64_btn_mri;
extern const struct texture_define mb64_btn_scuttlebug;
extern const struct texture_define mb64_btn_spindrift;
extern const struct texture_define mb64_btn_mrblizzard;
extern const struct texture_define mb64_btn_moneybag;
extern const struct texture_define mb64_btn_skeeter;
extern const struct texture_define mb64_btn_pokey;
extern const struct texture_define mb64_btn_rex;
extern const struct texture_define mb64_btn_hammerbro;
extern const struct texture_define mb64_btn_firebro;
extern const struct texture_define mb64_btn_podoboo;
extern const struct texture_define mb64_btn_cosmicphantasm;
extern const struct texture_define mb64_btn_redflame;
extern const struct texture_define mb64_btn_blueflame;
extern const struct texture_define mb64_btn_flamethrower;
extern const struct texture_define mb64_btn_firespitter;
extern const struct texture_define mb64_btn_firespinner;
extern const struct texture_define mb64_btn_bowlingball;
extern const struct texture_define mb64_btn_chicken;
extern const struct texture_define mb64_btn_crablet;
extern const struct texture_define mb64_btn_showrunner;
extern const struct texture_define mb64_btn_spawn;
extern const struct texture_define mb64_btn_smallbox;
extern const struct texture_define mb64_btn_crazybox;
extern const struct texture_define mb64_btn_pipebar;
extern const struct texture_define mb64_btn_bulletmask;
extern const struct texture_define mb64_btn_kingbobomb;
extern const struct texture_define mb64_btn_wiggler;
extern const struct texture_define mb64_btn_bowser;
extern const struct texture_define mb64_btn_bowserbomb;
extern const struct texture_define mb64_btn_check;
extern const struct texture_define mb64_btn_settings;
extern const struct texture_define mb64_btn_blank;
extern const struct texture_define mb64_btn_blankterrain;
extern const struct texture_define mb64_btn_blanksettings;
extern const struct texture_define mb64_btn_pipe;

#endif
