// bowser.inc.c

/**
 * Behavior for Bowser and it's actions (Tail, Flame, Body)
 */

// Bowser's Tail

/**
 * Checks whenever the Bowser and his tail should be intangible or not
 * By default it starts tangible
 */
void bowser_tail_anchor_act_default(void) {

}

/**
 * While Bowser get's thrown, wait 30 frames then
 * return to the default tail action check
 */
void bowser_tail_anchor_thrown(void) {

}

/**
 * Makes the tail intangible so Mario can grab it
 */
void bowser_tail_anchor_act_touched_mario(void) {

}

ObjActionFunc sBowserTailAnchorActions[] = {
    bowser_tail_anchor_act_default,
    bowser_tail_anchor_thrown,
    bowser_tail_anchor_act_touched_mario,
};

/**
 * Bowser's tail main loop
 */
void bhv_bowser_tail_anchor_loop(void) {
    // Call its actions
    cur_obj_call_action_function(sBowserTailAnchorActions);
    // Position the tail
    o->oParentRelativePosX = 90.0f;

    // Make it intangible while Bowser is dead
    if (o->parentObj->oAction == BOWSER_ACT_DEAD) {
        o->parentObj->oIntangibleTimer = -1;
    }

    o->oInteractStatus = INT_STATUS_NONE;
}

// Bowser's Flame

/**
 * Bowser's Flame spawn main loop
 */
void bhv_bowser_flame_spawn_loop(void) {

}

/**
 * Bowser's Body main loop
 */
void bhv_bowser_body_anchor_loop(void) {

}

/**
 * Bowser's shockwave attack, spawns only in BitS
 */
s32 bowser_spawn_shockwave(void) {
    return 0;
}

/**
 * Misc effects that Bowser plays when he lands with drastic actions
 * Plays step sound, spawns particles and changes camera event
 */
void bowser_bounce_effects(UNUSED s32 *timer) {

}

/**
 * Makes Bowser look up and walk on an specific animation frame
 * Returns TRUE if the animation is almost over
 */
s32 bowser_set_anim_look_up_and_walk(void) {
    return 0;
}

/**
 * Makes Bowser do a slow gait (or slow walk)
 * Returns TRUE if the animation is almost over
 */
s32 bowser_set_anim_slow_gait(void) {
    return 0;
}

/**
 * Makes Bowser look down and stop on an specific animation frame
 * Returns TRUE if the animation is almost over
 */
s32 bowser_set_anim_look_down_stop_walk(void) {
    return 0;
}

/**
 * Set Bowser an action depending of the CamAct value
 * CamAct changes value on the cutscene itself (cutscene_bowser_arena)
 */
void bowser_init_camera_actions(void) {

}

/**
 * Bowser's idle action that plays when he is initialized
 * or the CamAct gets in idle mode
 */
void bowser_act_wait(void) {

}

/**
 * Bowser's cutscene walk that last a few seconds to introduce itself
 * Do subactions until the animation ends, then go to next subaction
 */
void bowser_act_intro_walk(void) {

}

/**
 * List of actions to debug Bowser
 */
s8 sBowserDebugActions[] = {
    BOWSER_ACT_CHARGE_MARIO,
    BOWSER_ACT_SPIT_FIRE_INTO_SKY,
    BOWSER_ACT_SPIT_FIRE_ONTO_FLOOR,
    BOWSER_ACT_HIT_MINE,
    BOWSER_ACT_BIG_JUMP,
    BOWSER_ACT_WALK_TO_MARIO,
    BOWSER_ACT_BREATH_FIRE,
    BOWSER_ACT_DEAD,
    BOWSER_ACT_DANCE,
    BOWSER_ACT_TELEPORT,
    BOWSER_ACT_QUICK_JUMP,
    BOWSER_ACT_TILT_LAVA_PLATFORM,
    BOWSER_ACT_DANCE,
    BOWSER_ACT_DANCE,
    BOWSER_ACT_DANCE,
    BOWSER_ACT_DANCE,
};

/**
 * Debug function that allows to change Bowser's actions (most of them)
 */
UNUSED static void bowser_debug_actions(void) {

}

/**
 * Set actions (and attacks) for Bowser in "Bowser in the Dark World"
 */
void bowser_bitdw_actions(void) {

}

/**
 * Set actions (and attacks) for Bowser in "Bowser in the Fire Sea"
 */
void bowser_bitfs_actions(void) {

}

/**
 * List of actions (and attacks) for "Bowser in the Sky"
 */
void bowser_bits_action_list(void) {

}

/**
 * Sets big jump action, not much to say
 * Never gets called since oBowserBitsJustJump is always FALSE
 */
void bowser_set_act_big_jump(void) {

}

/**
 * Set actions (and attacks) for Bowser in "Bowser in the Sky"
 */
void bowser_bits_actions(void) {

}

/**
 * Reset Bowser position and speed if he wasn't able to land properly on stage
 */
void bowser_reset_fallen_off_stage(void) {

}

/**
 * Unused, makes Bowser be in idle and after it returns to default action
 */
void bowser_act_idle(void) {

}

/**
 * Default Bowser act that doesn't last very long
 */
void bowser_act_default(void) {

}

/**
 * Makes Bowser play breath animation and sound effect
 * The actual breath attack is in bhv_bowser_flame_spawn_loop
 * called as a child obj behavior in Bowser
 */
void bowser_act_breath_fire(void) {

}

/**
 * Makes Bowser walk towards Mario
 */
void bowser_act_walk_to_mario(void) {

}

/**
 * Makes Bowser teleport while invisible
 */
void bowser_act_teleport(void) {

}

/**
 * Makes Bowser do a fire split into the sky
 */
void bowser_act_spit_fire_into_sky(void) {

}

/**
 * Flips Bowser back on stage if he hits a mine with more than 1 health
 */
void bowser_act_hit_mine(void) {

}

/**
 * Makes Bowser do his jump start animation
 * Returns TRUE on the middle of the jump
 */
s32 bowser_set_anim_jump(void) {
    return 0;
}

/**
 * Reset speed, play jump stop animation and do attacks in BitDW
 * Returns TRUE when Bowser lands
 */
s32 bowser_land(void) {
    return 0;
}

/**
 * Makes Bowser do a second hop speed only in BitS
 */
void bowser_short_second_hop(void) {

}

/**
 * Makes Bowser do a big jump
 */
void bowser_act_big_jump(void) {

}

/**
 * Makes Bowser do a "quick" jump in BitDW
 */
void bowser_act_quick_jump(void) {

}

/**
 * Makes Bowser moving around if he is on an edge floor
 */
void bowser_act_hit_edge(void) {

}

/**
 * Makes Bowser do a fire split attack
 */
void bowser_act_spit_fire_onto_floor(void) {

}

/**
 * Turns around Bowser from an specific yaw angle
 * Returns TRUE once the timer is bigger than the time set
 */
s32 bowser_turn_on_timer(UNUSED s32 time, UNUSED s16 yaw) {
    return 0;
}

/**
 * Makes Bowser turn around after hitting the edge
 */
void bowser_act_turn_from_edge(void) {

}

/**
 * Makes Bowser charge (run) to Mario
 */
void bowser_act_charge_mario(void) {

}

/**
 * Checks if Bowser hits a mine from a distance, returns TRUE if so
 */
s32 bowser_check_hit_mine(void) {
    return 0;
}

/**
 * Bowser's thrown act that gets called after Mario releases him
 */
void bowser_act_thrown(void) {

}

/**
 * Set Bowser invisible and stops him (after falling)
 */
void bowser_set_goal_invisible(void) {

}

/**
 * Makes Bowser jump back on stage after falling
 */
void bowser_act_jump_onto_stage(void) {

}

/**
 * The frames of the Bowser's timer on which to play a "stomp" sound
 */
s8 sBowserDanceStepNoises[] = { 24, 42, 60, -1 };

/**
 * Makes Bowser's dance as a "taunt"
 */
void bowser_act_dance(void) {
    // Play a stomp sound effect on certain frames
    if (is_item_in_array(o->oTimer, sBowserDanceStepNoises)) {
        cur_obj_play_sound_2(SOUND_OBJ_BOWSER_WALK);
        cur_obj_play_sound_2(SOUND_ACTION_METAL_HEAVY_LANDING);
    }
    // Play dance animation and after that return to default action
    if (cur_obj_init_animation_and_check_if_near_end(BOWSER_ANIM_DANCE)) {
        o->oAction = BOWSER_ACT_DEFAULT;
    }
}

/**
 * Spawn collectable that Bowser spawns after despawning
 * Spawns a Key in BitDW/BitFS or Grand Star in BitS
 */
void bowser_spawn_collectable(void) {
    if (o->oBehParams2ndByte == BOWSER_BP_BITS) {
        gSecondCameraFocus = spawn_object(o, MODEL_STAR, bhvGrandStar);
    } else {
        gSecondCameraFocus = spawn_object(o, MODEL_BOWSER_KEY, bhvBowserKey);
        cur_obj_play_sound_2(SOUND_GENERAL2_BOWSER_KEY);
    }
    gSecondCameraFocus->oAngleVelYaw = o->oAngleVelYaw;
}

/**
 * Makes Bowser fly back on stage defeated
 */
void bowser_fly_back_dead(void) {
    cur_obj_init_animation_with_sound(BOWSER_ANIM_FLIP_DOWN);
    // More knockback in BitS
    if (o->oBehParams2ndByte == BOWSER_BP_BITS) {
        o->oForwardVel = -400.0f;
    } else {
        o->oForwardVel = -200.0f;
    }
    o->oVelY = 100.0f;
    o->oMoveAngleYaw = o->oBowserAngleToCenter + 0x8000;
    o->oBowserTimer = 0;
    o->oSubAction++; // BOWSER_SUB_ACT_DEAD_BOUNCE
}

/**
 * Plays bounce effects after landing upside down
 */
void bowser_dead_bounce(void) {
    o->oBowserEyesShut = TRUE; // close eyes
    bowser_bounce_effects(&o->oBowserTimer);
    if (o->oMoveFlags & OBJ_MOVE_LANDED) {
        cur_obj_play_sound_2(SOUND_OBJ_BOWSER_WALK);
    }
    if (o->oMoveFlags & OBJ_MOVE_ON_GROUND) {
        o->oForwardVel = 0.0f;
        o->oSubAction++; // BOWSER_SUB_ACT_DEAD_WAIT
    }
}

/**
 * Wait for Mario to get close while Bowser is defeated
 * Returns TRUE if he is close enough
 */
s32 bowser_dead_wait_for_mario(void) {
    s32 ret = FALSE;
    cur_obj_become_intangible();
    if (cur_obj_init_animation_and_check_if_near_end(BOWSER_ANIM_LAY_DOWN) && o->oDistanceToMario < 700.0f
        && abs_angle_diff(gMarioObject->oMoveAngleYaw, o->oAngleToMario) > 0x6000) {
        ret = TRUE;
    }
    cur_obj_extend_animation_if_at_end();
    o->oBowserTimer = 0;
    return ret;
}

/**
 * Makes Bowser twirl up by changing his scale
 * Returns TRUE once done
 */
s32 bowser_dead_twirl_up(void) {
    s32 ret = FALSE;

    // Set angle rotation once he has low X scale value
    if (o->header.gfx.scale[0] < 0.8f) {
        o->oAngleVelYaw += 0x80;
    }
    // Slowly scale down his X and Z value
    if (o->header.gfx.scale[0] > 0.2f) {
        o->header.gfx.scale[0] = o->header.gfx.scale[0] - 0.02f;
        o->header.gfx.scale[2] = o->header.gfx.scale[2] - 0.02f;
    } else {
        // Now scale down his Y value (and send Bowser up)
        o->header.gfx.scale[1] = o->header.gfx.scale[1] - 0.01f;
        o->oVelY = 20.0f;
        o->oGravity = 0.0f;
    }
    // At half Y scale value, he is high enough, so we are done
    if (o->header.gfx.scale[1] < 0.5f) {
        ret = TRUE;
    }
    // Copy angle rotation to moving rotation
    o->oMoveAngleYaw += o->oAngleVelYaw;
    // Slowly fade out
    if (o->oOpacity >= 3) {
        o->oOpacity -= 2;
    }

    return ret;
}

/**
 * Hides Bowser after his death sequence is done
 */
void bowser_dead_hide(void) {
    cur_obj_scale(0);
    o->oForwardVel = 0;
    o->oVelY = 0;
    o->oGravity = 0;
}

/**
 * Dialog values that are set on each stage Bowser's is defeated
 */
s16 sBowserDefeatedDialogText[3] = { DIALOG_119, DIALOG_120, DIALOG_121 };

/**
 * Bowser's dead sequence that plays in BitDW/BitFS
 * Returns TRUE once done
 */
s32 bowser_dead_default_stage_ending(void) {
    if (o->oBowserTimer < 2) {
        // Lower music volume
        if (o->oBowserTimer == 0) {
            seq_player_lower_volume(SEQ_PLAYER_LEVEL, 60, 40);
            o->oBowserTimer++;
        }
        // Play Bowser defeated dialog
        if (cur_obj_update_dialog(MARIO_DIALOG_LOOK_UP,
            (DIALOG_FLAG_TEXT_DEFAULT | DIALOG_FLAG_TIME_STOP_ENABLED),
            sBowserDefeatedDialogText[o->oBehParams2ndByte], 0)) {
            // Dialog is done, fade out music and play explode sound effect
            o->oBowserTimer++;
            cur_obj_play_sound_2(SOUND_GENERAL2_BOWSER_EXPLODE);
            seq_player_unlower_volume(SEQ_PLAYER_LEVEL, 60);
            seq_player_fade_out(SEQ_PLAYER_LEVEL, 1);
        }
    // Hide Bowser and spawn collectable once done twirling
    } else if (bowser_dead_twirl_up()) {
        bowser_dead_hide();
        spawn_triangle_break_particles(20, MODEL_YELLOW_COIN, 1.0f, 0);
        bowser_spawn_collectable();
        set_mario_npc_dialog(MARIO_DIALOG_STOP);
        return TRUE;
    }
    return FALSE;
}

/**
 * Bowser's dead sequence that plays in BitS
 * Returns TRUE once done
 */
s32 bowser_dead_final_stage_ending(void) {
    s32 dialogID;

    if (o->oBowserTimer < 2) {
        // Set dialog whenever you have 120 stars or not
        if (gHudDisplay.stars < 120) {
            dialogID = DIALOG_121;
        } else {
            dialogID = DIALOG_163;
        }
        // Lower music volume
        if (o->oBowserTimer == 0) {
            seq_player_lower_volume(SEQ_PLAYER_LEVEL, 60, 40);
            o->oBowserTimer++;
        }
        // Play Bowser defeated dialog
        if (cur_obj_update_dialog(MARIO_DIALOG_LOOK_UP,
            (DIALOG_FLAG_TEXT_DEFAULT | DIALOG_FLAG_TIME_STOP_ENABLED), dialogID, 0)) {
            // Dialog is done, fade out music and spawn grand star
            cur_obj_set_model(MODEL_BOWSER_NO_SHADOW);
            seq_player_unlower_volume(SEQ_PLAYER_LEVEL, 60);
            seq_player_fade_out(SEQ_PLAYER_LEVEL, 1);
            bowser_spawn_collectable();
            o->oBowserTimer++;
        }
    // Slowly fade him out
    } else if (o->oOpacity > 4) {
        o->oOpacity -= 4;
    } else {
        // And at last, hide him
        bowser_dead_hide();
        return TRUE;
    }
    return FALSE;
}

/**
 * Bowser's dead action, plays when he has no health left
 * This action is divided in subaction functions
 */
void bowser_act_dead(void) {
    switch (o->oSubAction) {
        case BOWSER_SUB_ACT_DEAD_FLY_BACK:
            bowser_fly_back_dead();
            break;

        case BOWSER_SUB_ACT_DEAD_BOUNCE:
            bowser_dead_bounce();
            break;

        case BOWSER_SUB_ACT_DEAD_WAIT:
            // Check if Mario is close to Bowser
            if (bowser_dead_wait_for_mario()) {
                o->oBowserTimer = 0;
                // Set different (final) subaction in BitS
                // Non-BitS Bowser uses default subaction and sets dithering
                if (o->oBehParams2ndByte == BOWSER_BP_BITS) {
                    o->oSubAction = BOWSER_SUB_ACT_DEAD_FINAL_END;
                } else {
                    o->activeFlags |= ACTIVE_FLAG_DITHERED_ALPHA;
                    o->oSubAction++; // BOWSER_SUB_ACT_DEAD_DEFAULT_END
                }
            }
            break;

        case BOWSER_SUB_ACT_DEAD_DEFAULT_END:
            if (bowser_dead_default_stage_ending()) {
                o->oSubAction++; // BOWSER_SUB_ACT_DEAD_DEFAULT_END_OVER
            }
            break;

        case BOWSER_SUB_ACT_DEAD_DEFAULT_END_OVER:
            break;

        case BOWSER_SUB_ACT_DEAD_FINAL_END:
            if (bowser_dead_final_stage_ending()) {
                o->oSubAction++; // BOWSER_SUB_ACT_DEAD_FINAL_END_OVER
            }
            break;

        case BOWSER_SUB_ACT_DEAD_FINAL_END_OVER:
            break;
    }
}

/**
 * Sets values for the BitFS platform to tilt
 */
void bowser_tilt_platform(struct Object *platform, s16 angSpeed) {
    s16 angle = o->oBowserAngleToCenter + 0x8000;
    platform->oAngleVelPitch = coss(angle) * angSpeed;
    platform->oAngleVelRoll = -sins(angle) * angSpeed;
}

/**
 * Struct for the BitFS tilt platform
 */
struct BowserTiltPlatformInfo {
    // Flag value to make sure platform moves smoothly
    //  0 = Don't move
    //  1 = Move angle behind Bowser
    // -1 = Move angle in front of Bowser
    s16 flag;
    // Sets platform's tilt angle speed (pattern: positive then negative)
    s16 angSpeed;
    // Sets how much time the platform can tilt, increases each move
    s16 time;
};

/**
 * Data for the BitFS tilt Platform
 */
struct BowserTiltPlatformInfo sBowsertiltPlatformData[] = {
    {  1,   10,  40 },
    {  0,    0,  74 },
    { -1,  -10, 114 },
    {  1,  -20, 134 },
    { -1,   20, 154 },
    {  1,   40, 164 },
    { -1,  -40, 174 },
    {  1,  -80, 179 },
    { -1,   80, 184 },
    {  1,  160, 186 },
    { -1, -160, 186 },
    {  1,    0,   0 },
};

/**
 * Makes the platform in BitFS tilt from left to right
 */
void bowser_act_tilt_lava_platform(void) {
    // Set platform object
    struct Object *platform = cur_obj_nearest_object_with_behavior(bhvTiltingBowserLavaPlatform);
    s16 angSpeed;
    // If there's not platform, return to default action
    if (platform == NULL) {
        o->oAction = BOWSER_ACT_DEFAULT;
    } else {
        s32 i = 0;
        s32 isNotTilting = TRUE;
        // Active platform tilting if the timer is not 0
        while (sBowsertiltPlatformData[i].time != 0) {
            // Move if the time values is more than the timer
            if (o->oTimer < sBowsertiltPlatformData[i].time) {
                // Set angle speed
                angSpeed = sBowsertiltPlatformData[i].angSpeed;
                // Move angle behind Bowser
                if (sBowsertiltPlatformData[i].flag > 0) {
                    angSpeed = (sBowsertiltPlatformData[i].time - o->oTimer - 1) * angSpeed;
                } else { // Move angle in front of Bowser
                    angSpeed = (o->oTimer - sBowsertiltPlatformData[i - 1].time) * angSpeed;
                }
                // Set angle values to the platform
                bowser_tilt_platform(platform, angSpeed);
                // Play sound effect
                if (angSpeed != 0) {
                    play_sound(SOUND_ENV_MOVING_BIG_PLATFORM, platform->header.gfx.cameraToObject);
                }
                isNotTilting = FALSE;
                break;
            }
            i++;
        }
        // If Bowser is done tilting, reset platform angles
        // and set Bowser to default action
        if (isNotTilting) {
            o->oAction = BOWSER_ACT_DEFAULT;
            platform->oAngleVelPitch = 0;
            platform->oAngleVelRoll = 0;
            platform->oFaceAnglePitch = 0;
            platform->oFaceAngleRoll = 0;
        }
    }
    // Extend "idle" animation
    cur_obj_extend_animation_if_at_end();
}

/**
 * Check if Bowser is offstage from a large distance or landed on a lethal floor
 */
s32 bowser_check_fallen_off_stage(void) {
    if (o->oAction != BOWSER_ACT_JUMP_ONTO_STAGE && o->oAction != BOWSER_ACT_TILT_LAVA_PLATFORM) {
        if (o->oPosY < o->oHomeY - 1000.0f) {
            return TRUE;
        }
        if (o->oMoveFlags & OBJ_MOVE_LANDED) {
            // Check for Fire Sea
            if (o->oFloorType == SURFACE_BURNING) {
                return TRUE;
            }
            // Check for Dark World - Sky
            if (o->oFloorType == SURFACE_DEATH_PLANE) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

#ifdef PLATFORM_DISPLACEMENT_2
struct PlatformDisplacementInfo sBowserDisplacementInfo;
#endif

/**
 * Set Bowser's actions
 */
ObjActionFunc sBowserActions[] = {
    bowser_act_default,
    bowser_act_thrown,
    bowser_act_jump_onto_stage,
    bowser_act_dance,
    bowser_act_dead,
    bowser_act_wait,
    bowser_act_intro_walk,
    bowser_act_charge_mario,
    bowser_act_spit_fire_into_sky,
    bowser_act_spit_fire_onto_floor,
    bowser_act_hit_edge,
    bowser_act_turn_from_edge,
    bowser_act_hit_mine,
    bowser_act_big_jump,
    bowser_act_walk_to_mario,
    bowser_act_breath_fire,
    bowser_act_teleport,
    bowser_act_quick_jump,
    bowser_act_idle,
    bowser_act_tilt_lava_platform,
};

/**
 * Set Bowser's sound animations
 */
struct SoundState sBowserSoundStates[] = {
    { 0, 0, 0, NO_SOUND },
    { 0, 0, 0, NO_SOUND },
    { 0, 0, 0, NO_SOUND },
    { 0, 0, 0, NO_SOUND },
    { 0, 0, 0, NO_SOUND },
    { 0, 0, 0, NO_SOUND },
    { 0, 0, 0, NO_SOUND },
    { 0, 0, 0, NO_SOUND },
    { 1, 0, -1, SOUND_OBJ_BOWSER_WALK },
    { 1, 0, -1, SOUND_OBJ2_BOWSER_ROAR },
    { 1, 0, -1, SOUND_OBJ2_BOWSER_ROAR },
    { 0, 0, 0, NO_SOUND },
    { 0, 0, 0, NO_SOUND },
    { 1, 20, 40, SOUND_OBJ_BOWSER_WALK },
    { 1, 20, -1, SOUND_OBJ_BOWSER_WALK },
    { 1, 20, 40, SOUND_OBJ_BOWSER_WALK },
    { 1, 0, -1, SOUND_OBJ_BOWSER_TAIL_PICKUP },
    { 1, 0, -1, SOUND_OBJ_BOWSER_DEFEATED },
    { 1, 8, -1, SOUND_OBJ_BOWSER_WALK },
    { 1, 8, 17, SOUND_OBJ_BOWSER_WALK },
    { 1, 8, -10, SOUND_OBJ_BOWSER_WALK },
    { 0, 0, 0, NO_SOUND },
    { 1, 5, -1, SOUND_OBJ_FLAME_BLOWN },
    { 0, 0, 0, NO_SOUND },
    { 0, 0, 0, NO_SOUND },
    { 1, 0, -1, SOUND_OBJ_BOWSER_TAIL_PICKUP },
    { 1, 0, -1, SOUND_OBJ2_BOWSER_ROAR },
};

/**
 * Set whenever Bowser should have rainbow light or not on each stage
 */
s8 sBowserRainbowLight[] = { FALSE, FALSE, TRUE };

/**
 * Set how much health Bowser has on each stage
 */
s8 sBowserHealth[] = { 1, 1, 3 };

/**
 * Update Bowser's actions when he's hands free
 */
void bowser_free_update(void) {
    struct Object *platform = o->platform;
#ifdef PLATFORM_DISPLACEMENT_2
    s16 tmpOFaceAngleYaw = (s16) o->oFaceAngleYaw;
    if (platform != NULL) {
        // NOTE: This function was at one point using '&o->oFaceAngleYaw', which is a s32 address. Should tmpOFaceAngleYaw be using the first 16 bits instead, or was that a bug?
        apply_platform_displacement(&sBowserDisplacementInfo, &o->oPosVec, &tmpOFaceAngleYaw, platform);
        o->oFaceAngleYaw = tmpOFaceAngleYaw;
    }
#else
    if (platform != NULL) {
        apply_platform_displacement(FALSE, platform);
    }
#endif
    // Reset grabbed status
    o->oBowserGrabbedStatus = BOWSER_GRAB_STATUS_NONE;
    // Update positions and actions (default action)
    cur_obj_update_floor_and_walls();
    cur_obj_call_action_function(sBowserActions);
    cur_obj_move_standard(-78);
    // Jump on stage if Bowser has fallen off
    if (bowser_check_fallen_off_stage()) {
        o->oAction = BOWSER_ACT_JUMP_ONTO_STAGE;
    }
    // Check floor height and platform
    if ((o->oFloor != NULL) && (o->oFloor->object != NULL)) {
        o->platform = o->oFloor->object;
    } else {
        o->platform = NULL;
    }
    // Sound states for Bowser Animations
    exec_anim_sound_state(sBowserSoundStates);
}

/**
 * Update Bowser's actions when he's getting held
 */
void bowser_held_update(void) {
    // Reset fire sky status and make him intangible
    o->oBowserStatus &= ~BOWSER_STATUS_FIRE_SKY;
    cur_obj_become_intangible();

    switch (o->oBowserGrabbedStatus) {
        // Play pickup sound, start grabbed animation, and set throw action
        // Throw action won't be played until he's actually released
        case BOWSER_GRAB_STATUS_NONE:
            cur_obj_play_sound_2(SOUND_OBJ_BOWSER_TAIL_PICKUP);
            cur_obj_unrender_set_action_and_anim(BOWSER_ANIM_GRABBED, BOWSER_ACT_THROWN);
            o->oBowserGrabbedStatus++;
            break;
        // After the grabbed animation ends, play shaking animation in a loop
        case BOWSER_GRAB_STATUS_GRABBED:
            if (cur_obj_check_if_near_animation_end()) {
                cur_obj_init_animation_with_sound(BOWSER_ANIM_SHAKING);
                o->oBowserGrabbedStatus++;
            }
            break;
        case BOWSER_GRAB_STATUS_HOLDING:
            break;
    }

    // Reset move flags
    o->oMoveFlags = OBJ_MOVE_NONE;
    // Copy angle values from Mario
    o->oBowserHeldAnglePitch = gMarioObject->oMoveAnglePitch;
    o->oBowserHeldAngleVelYaw = gMarioObject->oAngleVelYaw/1.2f;
    o->oMoveAngleYaw = gMarioObject->oMoveAngleYaw;
}

/**
 * Update Bowser's actions when he's thrown and dropped
 */
void bowser_thrown_dropped_update(void) {
    // Reset grabbed status
    o->oBowserGrabbedStatus = BOWSER_GRAB_STATUS_NONE;
    // Set throw action and vel values
    cur_obj_get_thrown_or_placed(1.0f, 1.0f, BOWSER_ACT_THROWN);
    // Set swing speed based of angle
    f32 swingSpd = o->oBowserHeldAngleVelYaw / 3000.0f * 70.0f;
    // If less than 0, reduce speed
    if (swingSpd < 0.0f) {
        swingSpd = -swingSpd;
    }
    // If more than 90, increase speed
    if (swingSpd > 90.0f) {
        swingSpd *= 2.5f;
    }
    // Set distance speed when throwing
    o->oForwardVel = coss(o->oBowserHeldAnglePitch) * swingSpd;
    o->oVelY = -sins(o->oBowserHeldAnglePitch) * swingSpd;
    cur_obj_become_intangible();

    // Reset timer and subactions
    o->prevObj->oAction = BOWSER_ACT_TAIL_THROWN; // prevObj is Bowser's Tail
    o->prevObj->oTimer = 0;
    o->prevObj->oSubAction = 0; //! Tail doesn't have sub actions

    o->oTimer = 0;
    o->oSubAction = 0;
}

/**
 * Bowser's main loop
 */
void bhv_bowser_loop(void) {
    s16 angleToMario;  // AngleToMario from Bowser's perspective
    s16 angleToCenter; // AngleToCenter from Bowser's perspective

    // Set distance/angle values
    o->oBowserDistToCenter = sqrtf(o->oPosX * o->oPosX + o->oPosZ * o->oPosZ);
    o->oBowserAngleToCenter = atan2s(0.0f - o->oPosZ, 0.0f - o->oPosX);
    angleToMario = abs_angle_diff(o->oMoveAngleYaw, o->oAngleToMario);
    angleToCenter = abs_angle_diff(o->oMoveAngleYaw, o->oBowserAngleToCenter);

    // Reset Status
    o->oBowserStatus &= ~0xFF;

    // Set bitflag status for distance/angle values
    // Only the first one is used
    if (angleToMario < 0x2000) {
        o->oBowserStatus |= BOWSER_STATUS_ANGLE_MARIO;
    }
    if (angleToCenter < 0x3800) {
        o->oBowserStatus |= BOWSER_STATUS_ANGLE_CENTER; // unused
    }
    if (o->oBowserDistToCenter < 1000.0f) {
        o->oBowserStatus |= BOWSER_STATUS_DIST_CENTER; // unused
    }
    if (o->oDistanceToMario < 850.0f) {
        o->oBowserStatus |= BOWSER_STATUS_DIST_MARIO; // unused
    }

    // Update Held state actions
    switch (o->oHeldState) {
        case HELD_FREE:
            bowser_free_update();
            break;
        case HELD_HELD:
            bowser_held_update();
            break;
        case HELD_THROWN:
            bowser_thrown_dropped_update();
            break;
        case HELD_DROPPED:
            bowser_thrown_dropped_update();
            break;
    }
    // Adjust model to the floor
    cur_obj_align_gfx_with_floor();

    // Adjust opacity (when not dead)
    // Mostly for the teleport action in BitFS
    if (o->oAction != BOWSER_ACT_DEAD) {
        if (o->oBowserTargetOpacity != o->oOpacity) {
            // increase opacity when oBowserTargetOpacity is 255
            if (o->oBowserTargetOpacity > o->oOpacity) {
                o->oOpacity += 20;
                if (o->oOpacity > 255) {
                    o->oOpacity = 255;
                }
            // reduce opacity when oBowserTargetOpacity is 0
            } else {
                o->oOpacity -= 20;
                if (o->oOpacity < 0) {
                    o->oOpacity = 0;
                }
            }
        }
    }
}

/**
 * Bowser's initial values and actions
 */
void bhv_bowser_init(void) {
    s32 level;
    // Set "reaction" value
    // It goes true when Bowser is a non-walking state
    o->oBowserIsReacting = TRUE;
    // Set no transparency opacity
    o->oOpacity = 255;
    o->oBowserTargetOpacity = 255;
    level = 0;
    // o->oBehParams2ndByte = level;
    // Set health and rainbow light depending of the level
    o->oBowserRainbowLight = sBowserRainbowLight[level];
    o->oHealth = 4; // sBowserHealth[level];
    gMarioState->BossHealth = o->oHealth;
    gMarioState->BossHealthMax = o->oHealth;
    // Start camera event, this event is not defined so maybe
    // the "start arena" cutscene was originally called this way
    cur_obj_start_cam_event(o, CAM_EVENT_BOWSER_INIT);
    o->oAction = 3;
    // Set eyes status
    o->oBowserEyesTimer = 0;
    o->oBowserEyesShut = FALSE;
}

Gfx *geo_update_body_rot_from_parent(s32 callContext, UNUSED struct GraphNode *node, Mat4 mtx) {
    if (callContext == GEO_CONTEXT_RENDER) {
        Mat4 mtx2;
        struct Object *obj = (struct Object *) gCurGraphNodeObject;
        if (obj->prevObj != NULL) {
            create_transformation_from_matrices(mtx2, mtx, *gCurGraphNodeCamera->matrixPtr);
            obj_update_pos_from_parent_transformation(mtx2, obj->prevObj);
            obj_set_gfx_pos_from_pos(obj->prevObj);
        }
    }

    return NULL;
}

/**
 * Bowser's eyes Geo-Switch-Case IDs, defined from Mario's POV
 */
enum BowserEyesGSCId {
    /*0x00*/ BOWSER_EYES_OPEN,
    /*0x01*/ BOWSER_EYES_HALF_CLOSED,
    /*0x02*/ BOWSER_EYES_CLOSED,
    /*0x03*/ BOWSER_EYES_LEFT,
    /*0x04*/ BOWSER_EYES_FAR_LEFT,
    /*0x05*/ BOWSER_EYES_RIGHT,
    /*0x06*/ BOWSER_EYES_FAR_RIGHT,
    /*0x07*/ BOWSER_EYES_DERP, // unused
    /*0x08*/ BOWSER_EYES_CROSS, // unused
    /*0x08*/ BOWSER_EYES_RESET // set eyes back to open
};

/**
 * Controls Bowser's eye open stage, including blinking and look directions
 */
void bowser_open_eye_switch(struct Object *obj, struct GraphNodeSwitchCase *switchCase) {
    s32 eyeCase;
    s16 angleFromMario;

    angleFromMario = abs_angle_diff(obj->oMoveAngleYaw, obj->oAngleToMario);
    eyeCase = switchCase->selectedCase;

    switch (eyeCase) {
        case BOWSER_EYES_OPEN:
            // Mario is in Bowser's field of view
            if (angleFromMario > 0x2000) {
                if (obj->oAngleVelYaw > 0) {
                    switchCase->selectedCase = BOWSER_EYES_RIGHT;
                }
                if (obj->oAngleVelYaw < 0) {
                    switchCase->selectedCase = BOWSER_EYES_LEFT;
                }
            }
            // Half close, start blinking
            if (obj->oBowserEyesTimer > 50) {
                switchCase->selectedCase = BOWSER_EYES_HALF_CLOSED;
            }
            break;

        case BOWSER_EYES_HALF_CLOSED:
            // Close, blinking
            if (obj->oBowserEyesTimer > 2) {
                switchCase->selectedCase = BOWSER_EYES_CLOSED;
            }
            break;

        case BOWSER_EYES_CLOSED:
            // Reset blinking
            if (obj->oBowserEyesTimer > 2) {
                switchCase->selectedCase = BOWSER_EYES_RESET;
            }
            break;

        case BOWSER_EYES_RESET:
            // Open, no longer blinking
            if (obj->oBowserEyesTimer > 2) {
                switchCase->selectedCase = BOWSER_EYES_OPEN;
            }
            break;

        case BOWSER_EYES_RIGHT:
            // Look more on the right if angle didn't change
            // Otherwise, look at the center (open)
            if (obj->oBowserEyesTimer > 2) {
                switchCase->selectedCase = BOWSER_EYES_FAR_RIGHT;
                if (obj->oAngleVelYaw <= 0) {
                    switchCase->selectedCase = BOWSER_EYES_OPEN;
                }
            }
            break;

        case BOWSER_EYES_FAR_RIGHT:
            // Look close right if angle was drastically changed
            if (obj->oAngleVelYaw <= 0) {
                switchCase->selectedCase = BOWSER_EYES_RIGHT;
            }
            break;

        case BOWSER_EYES_LEFT:
            // Look more on the left if angle didn't change
            // Otherwise, look at the center (open)
            if (obj->oBowserEyesTimer > 2) {
                switchCase->selectedCase = BOWSER_EYES_FAR_LEFT;
                if (obj->oAngleVelYaw >= 0) {
                    switchCase->selectedCase = BOWSER_EYES_OPEN;
                }
            }
            break;

        case BOWSER_EYES_FAR_LEFT:
            // Look close left if angle was drastically changed
            if (obj->oAngleVelYaw >= 0) {
                switchCase->selectedCase = BOWSER_EYES_LEFT;
            }
            break;

        default:
            switchCase->selectedCase = BOWSER_EYES_OPEN;
    }

    // Reset timer if eye case has changed
    if (switchCase->selectedCase != eyeCase) {
        obj->oBowserEyesTimer = -1;
    }
}

/**
 * Geo switch for controlling the state of Bowser's eye direction and open/closed
 * state. Checks whether oBowserEyesShut is TRUE and closes eyes if so and processes
 * direction otherwise.
 */
Gfx *geo_switch_bowser_eyes(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    struct Object *obj = (struct Object *) gCurGraphNodeObject;
    struct GraphNodeSwitchCase *switchCase = (struct GraphNodeSwitchCase *) node;

    if (callContext == GEO_CONTEXT_RENDER) {
        if (gCurGraphNodeHeldObject != NULL) {
            obj = gCurGraphNodeHeldObject->objNode;
        }
        if (obj->oBowserEyesShut) { // eyes closed, blinking
            switchCase->selectedCase = BOWSER_EYES_CLOSED;
        } else { // eyes open, handle eye looking direction
            bowser_open_eye_switch(obj, switchCase);
        }

        obj->oBowserEyesTimer++;
    }

    return NULL;
}

/**
 * Geo switch that sets Bowser's Rainbow coloring (in BitS)
 */
Gfx *geo_bits_bowser_coloring(s32 callContext, struct GraphNode *node, UNUSED s32 context) {
    Gfx *gfxHead = NULL;

    if (callContext == GEO_CONTEXT_RENDER) {
        struct Object *obj = (struct Object *) gCurGraphNodeObject;
        struct GraphNodeGenerated *graphNode = (struct GraphNodeGenerated *) node;
        if (gCurGraphNodeHeldObject != NULL) {
            obj = gCurGraphNodeHeldObject->objNode;
        }

        // Set layers if object is transparent or not
        if (obj->oOpacity == 255) {
            SET_GRAPH_NODE_LAYER(graphNode->fnNode.node.flags, LAYER_OPAQUE);
        } else {
            SET_GRAPH_NODE_LAYER(graphNode->fnNode.node.flags, LAYER_TRANSPARENT);
        }
        Gfx *gfx = gfxHead = alloc_display_list(2 * sizeof(Gfx));
        // If TRUE, clear lighting to give rainbow color
        if (obj->oBowserRainbowLight) {
            gSPClearGeometryMode(gfx++, G_LIGHTING);
        }

        gSPEndDisplayList(gfx);
    }

    return gfxHead;
}
