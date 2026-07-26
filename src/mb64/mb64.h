#pragma once

#include "types.h"

enum {
    MB64_MODE_PLAY,
    MB64_MODE_MAKE,
    MB64_MODE_UNINITIALIZED,
};

enum {
    MB64_GAME_VANILLA,
    MB64_GAME_BTCM,
};

extern u8 mb64_lopt_costume;

extern u8 mb64_lopt_seq[5];
extern u8 mb64_lopt_seq_seqtype;
extern u8 mb64_lopt_seq_album;
extern u8 mb64_lopt_seq_song;

extern u8 mb64_lopt_envfx;
extern u8 mb64_lopt_theme;
extern u8 mb64_lopt_bg;
extern u8 mb64_lopt_boundary_mat;
extern u8 mb64_lopt_boundary;
extern u8 mb64_lopt_boundary_height;
extern u8 mb64_lopt_game;
extern u8 mb64_lopt_size;
extern u8 mb64_lopt_template;
extern u8 mb64_lopt_coinstar;
extern u8 mb64_lopt_coinstar_max;
extern u8 mb64_lopt_waterlevel;
extern u8 mb64_lopt_secret;

extern u8 mb64_mode;
extern u8 mb64_target_mode;
