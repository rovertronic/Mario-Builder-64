
/**
 * Behavior for bhvHiddenBlueCoin and bhvBlueCoinSwitch.
 * bhvHiddenBlueCoin are the stationary blue coins that appear when
 * you press a blue coin switch (a.k.a. bhvBlueCoinSwitch).
 */

/**
 * Update function for bhvHiddenBlueCoin.
 */
void bhv_hidden_blue_coin_loop(void) {
    switch (o->oAction) {
        case HIDDEN_BLUE_COIN_ACT_INACTIVE:
            // Become invisible and intangible
            cur_obj_disable_rendering();
            cur_obj_become_intangible();

            o->oAction = HIDDEN_BLUE_COIN_ACT_WAITING;

            break;

        case HIDDEN_BLUE_COIN_ACT_WAITING:
            cur_obj_disable_rendering();
            if (gMarioState->onbluecoinswitch) {
                cur_obj_enable_rendering();
            }

            if (gMarioState->blueCoinSwitchTimer > 0) {
                o->oAction = HIDDEN_BLUE_COIN_ACT_ACTIVE;
                cur_obj_enable_rendering();
                cur_obj_become_tangible();
            }

            break;

        case HIDDEN_BLUE_COIN_ACT_ACTIVE:
            // Become tangible
            cur_obj_enable_rendering();

            // Delete the coin once collected
            if (o->oInteractStatus & INT_STATUS_INTERACTED) {
                spawn_object(o, MODEL_SPARKLES, bhvCoinSparklesSpawner);
                cur_obj_drop_imbued_object(0);
                obj_mark_for_deletion(o);
            }

            if (gMarioState->blueCoinSwitchTimer == 0) {
                o->oAction = HIDDEN_BLUE_COIN_ACT_INACTIVE;
            } else if (gMarioState->blueCoinSwitchTimer < 40) {
                if (gMarioState->blueCoinSwitchTimer & 1) {
                    cur_obj_disable_rendering();
                }
            }

            break;
    }

    o->oInteractStatus = INT_STATUS_NONE;
}

/**
 * Update function for bhvBlueCoinSwitch.
 */
void bhv_blue_coin_switch_loop(void) {
    // The switch's model is 1/3 size.
    cur_obj_scale(3.0f);

    u32 time = (save_file_get_badge_equip() & (1<<BADGE_TIME)) ? 480 : 240;
    u32 blueCoinsExist = (cur_obj_nearest_object_with_behavior(bhvHiddenBlueCoin) != NULL);

    if (gMarioPlatform == NULL) gMarioState->onbluecoinswitch = FALSE;

    switch (o->oAction) {
        case BLUE_COIN_SWITCH_ACT_IDLE:
            // If Mario is on the switch and has ground-pounded,
            // recede and get ready to start ticking.
            if (gMarioPlatform == o) {
                gMarioState->onbluecoinswitch = TRUE;
                if (gMarioStates[0].action == ACT_GROUND_POUND_LAND) {
                    // Set to BLUE_COIN_SWITCH_ACT_RECEDING
                    o->oAction = BLUE_COIN_SWITCH_ACT_RECEDING;
#ifdef BLUE_COIN_SWITCH_RETRY
                    // Recede at a rate of 16 units/frame.
                    o->oVelY = -16.0f;
#else
                    // Recede at a rate of 20 units/frame.
                    o->oVelY = -20.0f;
#endif
                    // Set gravity to 0 so it doesn't accelerate when receding.
                    o->oGravity = 0.0f;

                    cur_obj_play_sound_2(SOUND_GENERAL_SWITCH_DOOR_OPEN);
                    cur_obj_drop_imbued_object(0);
                }
            }

            // Have collision
            load_object_collision_model();

            break;

        case BLUE_COIN_SWITCH_ACT_RECEDING:
            // Recede for 6 frames before going invisible and ticking.
            // This is probably an off-by-one error, since the switch is 100 units tall
            // and recedes at 20 units/frame, which means it will fully recede after 5 frames.
            if (o->oTimer > 5) {
                cur_obj_hide();

                // Spawn particles. There's a function that calls this same function
                // with the same arguments, spawn_mist_particles, why didn't they just call that?
                spawn_mist_particles_variable(0, 0, 46.0f);

                if (!blueCoinsExist) {
                    obj_mark_for_deletion(o);
                    return;
                }

                // Set to BLUE_COIN_SWITCH_ACT_TICKING
                o->oAction = BLUE_COIN_SWITCH_ACT_TICKING;
                o->oPosY = gMarioObject->oPosY - 40.0f;
                gMarioState->blueCoinSwitchTimer = time;
            } else {
                // Have collision while receding
                load_object_collision_model();
                // Recede
                cur_obj_move_using_fvel_and_gravity();
            }

            break;

        case BLUE_COIN_SWITCH_ACT_TICKING:
            // Tick faster when the blue coins start blinking
            // Delete the switch (which stops the sound) after the last coin is collected,
            // or after the coins unload after the 240-frame timer expires.
            if (o->oTimer > time) {
                obj_mark_for_deletion(o);
            } else if (!blueCoinsExist) {
                obj_mark_for_deletion(o);
                gMarioState->blueCoinSwitchTimer = 0;
            }
            break;
    }
}
