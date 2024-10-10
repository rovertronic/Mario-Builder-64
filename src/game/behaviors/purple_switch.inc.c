
/**
 * Behavior for bhvFloorSwitchHardcodedModel, bhvFloorSwitchGrills, and
 * bhvFloorSwitchAnimatesObject.
 *
 * This controls the purple switches that Mario can step on to affect parts of
 * the environment.
 */

void bhv_purple_switch_loop(void) {
    struct Object *crate;
    u8 crateon = FALSE;
    s32 behparam1 = (gCurrentObject->oBehParams >> 24) & 0xFF;

    //STAR RADAR TRACKER
    if ((gDialogCourseActNum-1 == behparam1)&&(behparam1 < 6)) {
        gMarioState->StarRadarLocation[0] = (s16)o->oPosX;
        gMarioState->StarRadarLocation[1] = (s16)o->oPosY;
        gMarioState->StarRadarLocation[2] = (s16)o->oPosZ;
        gMarioState->StarRadarExist = TRUE;
        }

    // crate = cur_obj_nearest_object_with_behavior(bhvMetalCrate);

    // if (crate != NULL) {
    //     if (lateral_dist_between_objects(o,crate) < 200.0f) {
    //         crateon = TRUE;
    //         }
    //     }


    switch (o->oAction) {
        /**
         * Set the switch's model and scale. If Mario is standing near the
         * switch's middle section, transition to the pressed state.
         */
        case PURPLE_SWITCH_ACT_IDLE:
            cur_obj_set_model(MODEL_PURPLE_SWITCH);
            cur_obj_scale(1.28f);
            if (
                gMarioPlatform == o
                && !(gMarioStates[0].action & MARIO_NO_PURPLE_SWITCH)
                && lateral_dist_between_objects(o, gMarioObject) < 127.5f
            ) {
                o->oAction = PURPLE_SWITCH_ACT_PRESSED;
            }

            if (crateon) {
                o->oAction = PURPLE_SWITCH_ACT_PRESSED;
            }
            break;

        /**
         * Collapse the switch downward, play a sound, and shake the screen.
         * Immediately transition to the ticking state.
         */
        case PURPLE_SWITCH_ACT_PRESSED:
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 1.28f, 0.2f);
            if (o->oTimer == 3) {
                cur_obj_play_sound_2(SOUND_GENERAL2_PURPLE_SWITCH);
                cur_obj_shake_screen(SHAKE_POS_SMALL);
#if ENABLE_RUMBLE
                queue_rumble_data(5, 80);
#endif

                if (behparam1 > 9) {
                    o->oAction = PURPLE_SWITCH_ACT_WAIT_FOR_MARIO_TO_GET_OFF;
                    gMarioState->SwitchPressed = behparam1;
                    
                    if (gMarioState->NewTimerMode == 1) {
                        gMarioState->NewTimerMode = 0;
                        gMarioState->NewTimer = 0;
                    }
                }
                else
                {
                    gMarioState->NewTimer = o->oBehParams2ndByte;
                    o->oAction = PURPLE_SWITCH_ACT_TICKING;
                    gMarioState->NewTimerMode = 0;
                }
            }
            break;

        /**
         * Play a continuous ticking sound that gets faster when time is almost
         * up. When time is up, move to a waiting-while-pressed state.
         */
        case PURPLE_SWITCH_ACT_TICKING:
            if (gMarioState->NewTimer < 1) {
                o->oAction = PURPLE_SWITCH_ACT_WAIT_FOR_MARIO_TO_GET_OFF;
            } else {
                if (gMarioState->GoldRingCount > 4) {
                    spawn_default_star(o->oPosX, o->oPosY+ 200.0f, o->oPosZ);
                    o->oAction = 15;
                    gMarioState->NewTimer = 0;
                } else if (cur_obj_was_attacked_or_ground_pounded()) {
                    //ground pound the switch for a quick reset
                    gMarioState->NewTimer = 0;
                    o->oAction = PURPLE_SWITCH_ACT_WAIT_FOR_MARIO_TO_GET_OFF;
                }
            }
            break;

        /**
         * Make the switch look unpressed again, and transition back to the
         * idle state.
         */
        case PURPLE_SWITCH_ACT_UNPRESSED:
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 0.2f, 1.28f);
            if (o->oTimer == 3) {
                o->oAction = PURPLE_SWITCH_ACT_IDLE;
            }
            break;

        /**
         * Mario is standing on the switch, but time has expired. Wait for
         * him to get off the switch, and when he does so, transition to the
         * unpressed state.
         */
        case PURPLE_SWITCH_ACT_WAIT_FOR_MARIO_TO_GET_OFF:
            if ((!cur_obj_is_mario_on_platform()) && (!crateon)) {
                o->oAction = PURPLE_SWITCH_ACT_UNPRESSED;
                gMarioState->SwitchPressed = 0;
            }
            break;

        //Dud function
        case 15:
            break;
    }
}

void bhv_coin_ring_loop(void) {
    f32 scale = 1.0f;

    cur_obj_scale(scale);

    if (o->oAction == 0) {
        o->oMoveAngleYaw = o->oFaceAngleYaw;
        o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
        if ((gMarioState->NewTimer > 0)&&(gMarioState->NewTimerMode == 0)) {
            o->oAction = 1;
            }
        }

    if (o->oAction == 1) {
        o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;

        o->oPosY -= 50.0f;
        if (dist_between_objects(o,gMarioObject) < 225.0f*scale) {
            o->oAction = 2;
            gMarioState->GoldRingCount ++;
            spawn_orange_number(gMarioState->GoldRingCount, 0, 0, 0);
            play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
        }
    }
    o->oPosY = o->oHomeY;
    if (o->oAction == 2) {
        o->oFaceAngleYaw += 0x1000;
    }

    //Revert when time runs out
    if (o->oAction > 0) {
        if (gMarioState->NewTimer < 1) {
            o->oFaceAngleYaw = o->oMoveAngleYaw;
            o->oAction = 0;
            gMarioState->GoldRingCount = 0;
            }
        }

    }

void bhv_purple_switch_loop_vanilla(void) {
    u32 time = (save_file_get_badge_equip() & (1<<BADGE_TIME)) ? 800 : 400;
    switch (o->oAction) {
        /**
         * Set the switch's model and scale. If Mario is standing near the
         * switch's middle section, transition to the pressed state.
         */
        case PURPLE_SWITCH_ACT_IDLE:
            cur_obj_set_model(MODEL_PURPLE_SWITCH);
            cur_obj_scale(1.28f);
            if (
                gMarioPlatform == o
                && !(gMarioStates[0].action & MARIO_NO_PURPLE_SWITCH)
                && lateral_dist_between_objects(o, gMarioObject) < 127.5f
            ) {
                o->oAction = PURPLE_SWITCH_ACT_PRESSED;
            }
            break;

        /**
         * Collapse the switch downward, play a sound, and shake the screen.
         * Immediately transition to the ticking state.
         */
        case PURPLE_SWITCH_ACT_PRESSED:
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 1.28f, 0.2f);
            if (o->oTimer == 3) {
                cur_obj_play_sound_2(SOUND_GENERAL2_PURPLE_SWITCH);
                o->oAction = PURPLE_SWITCH_ACT_TICKING;
                gMarioState->hiddenBoxTimer = time;
                cur_obj_shake_screen(SHAKE_POS_SMALL);
#if ENABLE_RUMBLE
                queue_rumble_data(5, 80);
#endif
            }
            break;

        /**
         * Play a continuous ticking sound that gets faster when time is almost
         * up. When time is up, move to a waiting-while-pressed state.
         */
        case PURPLE_SWITCH_ACT_TICKING:
            if (o->oBehParams2ndByte != 0) {
                if (o->oBehParams2ndByte == 1 && gMarioPlatform != o) {
                    o->oAction++;
                } else {
                    if (o->oTimer > time) {
                        o->oAction = PURPLE_SWITCH_ACT_WAIT_FOR_MARIO_TO_GET_OFF;
                    }
                }
            }
            break;

        /**
         * Make the switch look unpressed again, and transition back to the
         * idle state.
         */
        case PURPLE_SWITCH_ACT_UNPRESSED:
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 0.2f, 1.28f);
            if (o->oTimer == 3) {
                o->oAction = PURPLE_SWITCH_ACT_IDLE;
            }
            break;

        /**
         * Mario is standing on the switch, but time has expired. Wait for
         * him to get off the switch, and when he does so, transition to the
         * unpressed state.
         */
        case PURPLE_SWITCH_ACT_WAIT_FOR_MARIO_TO_GET_OFF:
            if (!cur_obj_is_mario_on_platform()) {
                o->oAction = PURPLE_SWITCH_ACT_UNPRESSED;
            }
            break;
    }
}