#include <PR/ultratypes.h>

#include "audio/external.h"
#include "game/sound_init.h"
#include "seq_ids.h"
#include "sm64.h"
#include "title_screen.h"

/**
 * @file title_screen.c
 * Title / intro helpers used by the splash LevelScript.
 */

/**
 * Plays the casual "It's a me mario" when the game starts.
 */
s32 lvl_intro_update(UNUSED s16 arg, UNUSED s32 unusedArg) {
    set_background_music(0, SEQ_SOUND_PLAYER, 0);
    play_sound(SOUND_GENERAL_COIN, gGlobalSoundSource);
    return 1;
}
