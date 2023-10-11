#ifndef MARIO_ACTIONS_AUTOMATIC_H
#define MARIO_ACTIONS_AUTOMATIC_H

#include <PR/ultratypes.h>

#include "types.h"

enum ActionStatesInCannon { // act_in_cannon
    ACT_STATE_IN_CANNON_INIT,
    ACT_STATE_IN_CANNON_WAIT_FOR_CANNON,
    ACT_STATE_IN_CANNON_READY
};

enum PolePositions { // set_pole_position
    POLE_NONE,
    POLE_TOUCHED_FLOOR,
    POLE_FELL_OFF
};

enum HangingSteps { // perform_hanging_step
    HANG_NONE,
    HANG_HIT_CEIL_OR_OOB,
    HANG_LEFT_CEIL
};

struct Pole {
    Vec3s pos;
    u16 height;
    u8 poleType; // 0 - no leaves, 1 - leaves, 2 - palm tree
};

extern struct Pole *gPoleArray;

extern s16 gMarioCurrentPole; // -1 = no pole
extern s16 gNumPoles;
#define curPole (gPoleArray[gMarioCurrentPole])

s32 mario_execute_automatic_action(struct MarioState *m);

#endif // MARIO_ACTIONS_AUTOMATIC_H
