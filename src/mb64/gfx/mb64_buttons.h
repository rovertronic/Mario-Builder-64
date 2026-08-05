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

extern const struct texture_define mb64_btn_tile;
extern const struct texture_define mb64_btn_slabtile;
extern const struct texture_define mb64_btn_slope;
extern const struct texture_define mb64_btn_corner;
extern const struct texture_define mb64_btn_icorner;
extern const struct texture_define mb64_btn_vslab;
extern const struct texture_define mb64_btn_sideslope;
extern const struct texture_define mb64_btn_triangle;
extern const struct texture_define mb64_btn_isc;
extern const struct texture_define mb64_btn_lgs;
extern const struct texture_define mb64_btn_ugs;
extern const struct texture_define mb64_btn_troll;
extern const struct texture_define mb64_btn_water;
extern const struct texture_define mb64_btn_fence;
extern const struct texture_define mb64_btn_bars;
extern const struct texture_define mb64_btn_pole;
extern const struct texture_define mb64_btn_tree;
extern const struct texture_define mb64_btn_cull;
extern const struct texture_define mb64_btn_star;
extern const struct texture_define mb64_btn_rcs;
extern const struct texture_define mb64_btn_triggerstar;
extern const struct texture_define mb64_btn_coin;
extern const struct texture_define mb64_btn_cformation;
extern const struct texture_define mb64_btn_greencoin;
extern const struct texture_define mb64_btn_redcoin;
extern const struct texture_define mb64_btn_bluecoin;
extern const struct texture_define mb64_btn_bcs;
extern const struct texture_define mb64_btn_excla;
extern const struct texture_define mb64_btn_trigger;
extern const struct texture_define mb64_btn_heart;
extern const struct texture_define mb64_btn_checker;
extern const struct texture_define mb64_btn_purpleswitch;
extern const struct texture_define mb64_btn_tbox;
extern const struct texture_define mb64_btn_tblock;
extern const struct texture_define mb64_btn_corkbox;
extern const struct texture_define mb64_btn_rfbox;
extern const struct texture_define mb64_btn_water_diamond;
extern const struct texture_define mb64_btn_woodplat;
extern const struct texture_define mb64_btn_sign;
extern const struct texture_define mb64_btn_buddy;
extern const struct texture_define mb64_btn_moleman;
extern const struct texture_define mb64_btn_cobie;
extern const struct texture_define mb64_btn_badge;
extern const struct texture_define mb64_btn_noteblock;
extern const struct texture_define mb64_btn_switch;
extern const struct texture_define mb64_btn_block;
extern const struct texture_define mb64_btn_conveyor;
extern const struct texture_define mb64_btn_toad;
extern const struct texture_define mb64_btn_tuxie;
extern const struct texture_define mb64_btn_ukiki;
extern const struct texture_define mb64_btn_kuppaq;
extern const struct texture_define mb64_btn_goomba;
extern const struct texture_define mb64_btn_goomba_b;
extern const struct texture_define mb64_btn_goomba_s;
extern const struct texture_define mb64_btn_bobomb;
extern const struct texture_define mb64_btn_chuckya;
extern const struct texture_define mb64_btn_kuppa;
extern const struct texture_define mb64_btn_lakitu;
extern const struct texture_define mb64_btn_flyguy;
extern const struct texture_define mb64_btn_snufit;
extern const struct texture_define mb64_btn_thwomp;
extern const struct texture_define mb64_btn_grindel;
extern const struct texture_define mb64_btn_whomp;
extern const struct texture_define mb64_btn_boss_whomp;
extern const struct texture_define mb64_btn_bully;
extern const struct texture_define mb64_btn_chillbully;
extern const struct texture_define mb64_btn_boss_bully;
extern const struct texture_define mb64_btn_boss_chillbully;
extern const struct texture_define mb64_btn_motos;
extern const struct texture_define mb64_btn_heaveho;
extern const struct texture_define mb64_btn_bill;
extern const struct texture_define mb64_btn_amp;
extern const struct texture_define mb64_btn_plant;
extern const struct texture_define mb64_btn_plant_b;
extern const struct texture_define mb64_btn_plant_s;
extern const struct texture_define mb64_btn_boo;
extern const struct texture_define mb64_btn_boss_boo;
extern const struct texture_define mb64_btn_mri;
extern const struct texture_define mb64_btn_scuttlebug;
extern const struct texture_define mb64_btn_spindrift;
extern const struct texture_define mb64_btn_blizzard;
extern const struct texture_define mb64_btn_moneybag;
extern const struct texture_define mb64_btn_skeeter;
extern const struct texture_define mb64_btn_pokey;
extern const struct texture_define mb64_btn_rex;
extern const struct texture_define mb64_btn_hammerbro;
extern const struct texture_define mb64_btn_firebro;
extern const struct texture_define mb64_btn_podoboo;
extern const struct texture_define mb64_btn_phantasm;
extern const struct texture_define mb64_btn_fire_red;
extern const struct texture_define mb64_btn_fire_blue;
extern const struct texture_define mb64_btn_flamethrower;
extern const struct texture_define mb64_btn_firespitter;
extern const struct texture_define mb64_btn_firebar;
extern const struct texture_define mb64_btn_bball;
extern const struct texture_define mb64_btn_chicken;
extern const struct texture_define mb64_btn_crablet;
extern const struct texture_define mb64_btn_showrunner;
extern const struct texture_define mb64_btn_spawn;
extern const struct texture_define mb64_btn_sbox;
extern const struct texture_define mb64_btn_cbox;
extern const struct texture_define mb64_btn_pipebar;
extern const struct texture_define mb64_btn_mask;
extern const struct texture_define mb64_btn_boss_kb;
extern const struct texture_define mb64_btn_boss_wiggler;
extern const struct texture_define mb64_btn_boss_bowser;
extern const struct texture_define mb64_btn_bbomb;
extern const struct texture_define mb64_btn_check;
extern const struct texture_define mb64_btn_settings;
extern const struct texture_define mb64_btn_blank;
extern const struct texture_define mb64_btn_pipe;

#endif
