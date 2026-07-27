void reset_mario_pitch(struct MarioState *m);

void noteblock_function(void) {
    load_object_collision_model();
    o->oGraphYOffset = (sins(o->oTimer * 5000) * o->oVelY);
    o->oVelY *= 0.95f;
    o->header.gfx.throwMatrix = NULL;

    if (!(gMarioState->action & ACT_FLAG_INTANGIBLE) &&
        !(gMarioState->action & ACT_FLAG_SWIMMING) &&
        (gMarioState->health > 0x100) && cur_obj_is_mario_on_platform()) {
            o->oTimer = 0;
            o->oVelY = 50.0f;
            cur_obj_play_sound_2(SOUND_GENERAL_CRAZY_BOX_BOING_SLOW);
            reset_mario_pitch(gMarioState);

            u32 targetAction = ACT_DOUBLE_JUMP;
            u32 targetSubaction = 0;
            u32 metalMario = (gMarioState->action & ACT_FLAG_METAL_WATER);

            if (gMarioState->heldObj != NULL) {
                if (gMarioState->heldObj->behavior == segmented_to_virtual(bhvJumpingBox)) {
                    targetAction = ACT_CRAZY_BOX_BOUNCE;
                    targetSubaction = 2;
                } else if (gMarioState->heldObj->behavior == segmented_to_virtual(bhvBreakableBoxSmall)) {
                    if (metalMario) {
                        targetAction = ACT_HOLD_METAL_WATER_JUMP;
                    } else {
                        targetAction = ACT_HOLD_JUMP;
                    }
                } else {
                    mario_stop_riding_and_holding(gMarioState);
                }
            } else if (gMarioState->riddenObj != NULL) {
                targetAction = ACT_RIDING_SHELL_JUMP;
            } else if (metalMario) {
                targetAction = ACT_METAL_WATER_JUMP;
            }

            set_mario_action(gMarioState, targetAction, targetSubaction);

            gMarioState->vel[1] = 95.0f;
            gMarioState->squishTimer = 0;
        }
}
