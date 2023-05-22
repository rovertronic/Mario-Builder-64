
/**
 * Behavior for MIPS (everyone's favorite yellow rabbit).
 */

/**
 * Initializes MIPS' physics parameters and checks if he should be active,
 * hiding him if necessary.
 */
void bhv_mips_init(void) {
#ifndef UNLOCK_ALL
    // Retrieve star flags for Castle Secret Stars on current save file.
    u8 starFlags = save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(COURSE_NONE));

    // If the player has >= 15 stars and hasn't collected first MIPS star...
    if (save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1) >= 15
        && !(starFlags & SAVE_FLAG_TO_STAR_FLAG(SAVE_FLAG_COLLECTED_MIPS_STAR_1))) {
        o->oBehParams2ndByte    = MIPS_BP_STAR_1;
        o->oMipsForwardVelocity = 40.0f;
    }
    // If the player has >= 50 stars and hasn't collected second MIPS star...
    else if (save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1) >= 50
             && !(starFlags & SAVE_FLAG_TO_STAR_FLAG(SAVE_FLAG_COLLECTED_MIPS_STAR_2))) {
#endif
        o->oBehParams2ndByte = MIPS_BP_STAR_2;
        o->oMipsForwardVelocity = 45.0f;
#ifndef UNLOCK_ALL
    } else {
        // No MIPS stars are available, hide MIPS.
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
#endif
    o->oInteractionSubtype = INT_SUBTYPE_HOLDABLE_NPC;

    o->oGravity = 15.0f;
    o->oFriction = 0.89f;
    o->oBuoyancy = 1.2f;

    cur_obj_init_animation(0);
}

/**
 * Helper function that finds the waypoint that is both within 800 units of MIPS
 * and furthest from Mario's current location.
 */
s32 bhv_mips_find_furthest_waypoint_to_mario(void) {
    s8 i;
    Vec3s pos;
    s16 furthestWaypointIndex = -1;
    f32 furthestWaypointDistance = -10000.0f;
    f32 distanceToMario;
    struct Waypoint **pathBase = segmented_to_virtual(&inside_castle_seg7_trajectory_mips);
    f32 dx, dz;
    // For each waypoint in MIPS path...
    for (i = 0; i < 10; i++) {
        struct Waypoint *waypoint = segmented_to_virtual(pathBase[i]);
        vec3s_copy(pos, waypoint->pos);

        // Is the waypoint within 800 units of MIPS?
        if (is_point_close_to_object(o, pos[0], pos[1], pos[2], 800)) {
            // Is this further from Mario than the last waypoint?
            dx = pos[0] - gMarioObject->header.gfx.pos[0];
            dz = pos[2] - gMarioObject->header.gfx.pos[2];
            distanceToMario = sqr(dx) + sqr(dz);
            if (furthestWaypointDistance < distanceToMario) {
                furthestWaypointIndex = i;
                furthestWaypointDistance = distanceToMario;
            }
        }
    }

    // Set MIPS' next waypoint to be the closest waypoint to Mario.
    o->oMipsStartWaypointIndex = furthestWaypointIndex;
    return (s16) o->oMipsStartWaypointIndex;
}

/**
 * Wait until Mario comes close, then resume following our path.
 */
void bhv_mips_act_wait_for_nearby_mario(void) {
    o->oForwardVel = 0.0f;
    object_step();

    // If Mario is within 500 units...
    if (is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 500)) {
        // If we fail to find a suitable waypoint...
        if (bhv_mips_find_furthest_waypoint_to_mario() == -1) {
            // Call it quits.
            o->oAction = MIPS_ACT_WAIT_FOR_ANIMATION_DONE;
        } else {
            // Resume path following.
            cur_obj_init_animation(1);
            o->oAction = MIPS_ACT_FOLLOW_PATH;
        }
    }
}

/**
 * Continue to follow our path around the basement area.
 */
void bhv_mips_act_follow_path(void) {
    // Retrieve current waypoint.
    struct Waypoint **pathBase = segmented_to_virtual(&inside_castle_seg7_trajectory_mips);
    struct Waypoint *waypoint = segmented_to_virtual(*(pathBase + o->oMipsStartWaypointIndex));

    // Set start waypoint and follow the path from there.
    o->oPathedStartWaypoint = waypoint;
    s32 followStatus = cur_obj_follow_path();

    // Update velocity and angle and do movement.
    o->oForwardVel = o->oMipsForwardVelocity;
    o->oMoveAngleYaw = o->oPathedTargetYaw;
    s16 collisionFlags = object_step();

    // If we are at the end of the path, do idle animation and wait for Mario.
    if (followStatus == PATH_REACHED_END) {
        cur_obj_init_animation(0);
        o->oAction = MIPS_ACT_WAIT_FOR_NEARBY_MARIO;
    }

    // Play sounds during walk animation.
    if (cur_obj_check_if_near_animation_end() && (collisionFlags & OBJ_COL_FLAG_UNDERWATER)) {
        cur_obj_play_sound_2(SOUND_OBJ_MIPS_RABBIT_WATER);
        spawn_object(o, MODEL_NONE, bhvShallowWaterSplash);
    } else if (cur_obj_check_if_near_animation_end()) {
        cur_obj_play_sound_2(SOUND_OBJ_MIPS_RABBIT);
    }
}

/**
 * Seems to wait until the current animation is done, then go idle.
 */
void bhv_mips_act_wait_for_animation_done(void) {
    if (cur_obj_check_if_near_animation_end()) {
        cur_obj_init_animation(0);
        o->oAction = MIPS_ACT_IDLE;
    }
}

/**
 * Handles MIPS falling down after being thrown.
 */
void bhv_mips_act_fall_down(void) {
    s16 collisionFlags = object_step();

    o->header.gfx.animInfo.animFrame = 0;

    if (collisionFlags & OBJ_COL_FLAG_GROUNDED) {
        o->oAction = MIPS_ACT_WAIT_FOR_ANIMATION_DONE;

        o->oFlags |= OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
        o->oMoveAngleYaw = o->oFaceAngleYaw;

        if (collisionFlags & OBJ_COL_FLAG_UNDERWATER) {
            spawn_object(o, MODEL_NONE, bhvShallowWaterSplash);
        }
    }
}

/**
 * Idle loop, after you catch MIPS and put him down.
 */
void bhv_mips_act_idle(void) {
    o->oForwardVel = 0.0f;
    object_step();

    // Spawn a star if he was just picked up for the first time.
    if (o->oMipsStarStatus == MIPS_STAR_STATUS_SHOULD_SPAWN_STAR) {
        bhv_spawn_star_no_level_exit(o->oBehParams2ndByte + 3);
        o->oMipsStarStatus = MIPS_STAR_STATUS_ALREADY_SPAWNED_STAR;
    }
}

/**
 * Handles all the actions MIPS does when he is not held.
 */
void bhv_mips_free(void) {
    switch (o->oAction) {
        case MIPS_ACT_WAIT_FOR_NEARBY_MARIO:
            bhv_mips_act_wait_for_nearby_mario();
            break;

        case MIPS_ACT_FOLLOW_PATH:
            bhv_mips_act_follow_path();
            break;

        case MIPS_ACT_WAIT_FOR_ANIMATION_DONE:
            bhv_mips_act_wait_for_animation_done();
            break;

        case MIPS_ACT_FALL_DOWN:
            bhv_mips_act_fall_down();
            break;

        case MIPS_ACT_IDLE:
            bhv_mips_act_idle();
            break;
    }
}

/**
 * Handles MIPS being held by Mario.
 */
void bhv_mips_held(void) {
    s16 dialogID;

    o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
    cur_obj_init_animation(4); // Held animation.
    cur_obj_set_pos_relative(gMarioObject, 0, 60.0f, 100.0f);
    cur_obj_become_intangible();

    // If MIPS hasn't spawned his star yet...
    if (o->oMipsStarStatus == MIPS_STAR_STATUS_HAVENT_SPAWNED_STAR) {
        // Choose dialog based on which MIPS encounter this is.
        if (o->oBehParams2ndByte == MIPS_BP_STAR_1) {
            dialogID = DIALOG_084;
        } else {
            dialogID = DIALOG_162;
        }

        if (set_mario_npc_dialog(MARIO_DIALOG_LOOK_FRONT) == MARIO_DIALOG_STATUS_SPEAK) {
            o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
            if (cutscene_object_with_dialog(CUTSCENE_DIALOG, o, dialogID)) {
                o->oInteractionSubtype |= INT_SUBTYPE_DROP_IMMEDIATELY;
                o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
                o->oMipsStarStatus = MIPS_STAR_STATUS_SHOULD_SPAWN_STAR;
                set_mario_npc_dialog(MARIO_DIALOG_STOP);
            }
        }
    }
}

/**
 * Handles MIPS being dropped by Mario.
 */
void bhv_mips_dropped(void) {
    cur_obj_get_dropped();
    o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
    cur_obj_init_animation(0);
    o->oHeldState = HELD_FREE;
    cur_obj_become_tangible();
    o->oForwardVel = 3.0f;
    o->oAction = MIPS_ACT_IDLE;
}

/**
 * Handles MIPS being thrown by Mario.
 */
void bhv_mips_thrown(void) {
    cur_obj_enable_rendering();
    o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
    o->oHeldState = HELD_FREE;
    o->oFlags &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
    cur_obj_init_animation(2);
    cur_obj_become_tangible();
    o->oForwardVel = 25.0f;
    o->oVelY = 20.0f;
    o->oAction = MIPS_ACT_FALL_DOWN;
}

/**
 * MIPS' main loop.
 */
void bhv_mips_loop(void) {
    // Determine what to do based on MIPS' held status.
    switch (o->oHeldState) {
        case HELD_FREE:
            bhv_mips_free();
            break;

        case HELD_HELD:
            bhv_mips_held();
            break;

        case HELD_THROWN:
            bhv_mips_thrown();
            break;

        case HELD_DROPPED:
            bhv_mips_dropped();
            break;
    }
}

u8 Map[20][20] = {
{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
{0xFF,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0xFF,0,0,0xFF},
{0xFF,0,0,0xFE,0xFE,0xFE,0,0xFF,0,0xFF,0xFF,0xFF,0xFF,0xFF,0,0,0,0,0,0xFF},
{0xFF,0,0xFE,0xFE,0xFE,0xFE,0,0xFF,0,0,0,0,0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
{0xFF,0,0xFE,0xFE,0xFE,0,0,0xFF,0,0,0,0xFF,0,0xFF,0,0,0,0,0,0xFF},
{0xFF,0,0,0xFE,0xFE,0,0,0xFF,0xFF,0,0xFF,0xFF,0,0xFF,0,0,0,0xFF,0,0xFF},
{0xFF,0,0xFE,0xFE,0xFE,0xFE,0,0xFF,0,0,0,0xFF,0,0xFF,0,0,0,0xFF,0,0xFF},
{0xFF,0,0,0,0,0,0,0xFF,0,0,0,0xFF,0,0xFF,0xFF,0,0xFF,0xFF,0,0xFF},
{0xFF,0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0,0,0,0,0,0xFF,0,0xFF},
{0xFF,0,0xFF,0,0,0xFF,0,0,0,0,0,0xFF,0,0xFF,0xFF,0,0xFF,0xFF,0,0xFF},
{0xFF,0,0xFF,0,0,0xFF,0,0xFF,0,0xFF,0,0xFF,0,0xFF,0,0,0,0xFF,0,0xFF},
{0xFF,0,0,0,0,0,0,0,0,0,0,0,0,0xFF,0,0,0,0xFF,0,0xFF},
{0xFF,0,0xFF,0,0,0xFF,0,0xFF,0,0xFF,0,0xFF,0,0xFF,0xFF,0xFF,0xFF,0xFF,0,0xFF},
{0xFF,0,0xFF,0xFF,0xFF,0xFF,0,0,0,0,0,0xFF,0,0,0,0,0,0xFF,0,0xFF},
{0xFF,0,0xFF,0,0,0xFF,0xFF,0xFF,0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0,0,0xFF,0,0xFF},
{0xFF,0,0,0,0,0xFF,0,0,0,0,0,0,0,0,0xFF,0,0,0xFF,0,0xFF},
{0xFF,0,0xFF,0,0,0xFF,0,0xFF,0,0xFF,0xFF,0,0xFF,0,0xFF,0,0,0xFF,0,0xFF},
{0xFF,0,0xFF,0xFF,0xFF,0xFF,0,0xFF,0,0,0,0,0xFF,0,0xFF,0xFF,0xFF,0xFF,0,0xFF},
{0xFF,0,0,0,0,0,0,0xFF,0,0,0,0,0xFF,0,0,0,0,0,0,0xFF},
{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
};
u8 PathArray[20][20];

void resetarray(void) {
    u8 i = 0;
    u8 e = 0;
    while (i < 19) {
        e = 0;
        while(e < 19) {
            PathArray[i][e] = Map[i][e];
            e++;
            }
        i++;
        } 
}

u8 txpos = 10;
u8 typos = 18;

u8 old_txpos;
u8 old_typos;

u8 xsignpos = 10;
u8 ysignpos = 18;
u8 founded = FALSE;
u8 id = 0;

u8 fourdirs[4];
u8 lowest = 255;
u8 whichone = 5;

u32 pathfind(u8 xpos, u8 ypos, u8 id) {
    s8 i, xOffset, yOffset;
    u8 val;

    //Check if sign founded
    if ((xpos == xsignpos)&&(ypos == ysignpos)) {
        founded = TRUE;
        }

    //pathfind
    PathArray[ypos][xpos] = id;

    for (i = 0; i < 4; i++) {
        if (i < 2) {
           xOffset = 0;
           yOffset = i * 2 - 1;
        } else {
           yOffset = 0;
           xOffset = i * 2 - 5;
        }
        if ((xpos + xOffset < 0) || (xpos + xOffset > 20 - 1) || (ypos + yOffset < 0) || (ypos + yOffset > 20 - 1)) {
            continue;
        }
        val = PathArray[ypos + yOffset][xpos + xOffset];
        if ((val == 0) || ((val > id + 1) && (val < 0xFE))) {
            pathfind(xpos + xOffset, ypos + yOffset, id + 1);
        }
    }
}

u32 newtarget(f32 xpos, f32 ypos) {
    if ((Map[(u8)((ypos/800)+10)][(u8)((xpos/800)+10)] != 0xFF)&&(Map[(u8)((ypos/800)+10)][(u8)((xpos/800)+10)] != 0xFE)) {
        txpos = (u8)((xpos/800)+10);
        typos = (u8)((ypos/800)+10);

        //cur_obj_play_sound_2(SOUND_OBJ2_BOWSER_ROAR);
        }
    }

u32 newtarget_grid(u8 xpos, u8 ypos) {
    if ((Map[ypos][xpos] != 0xFF)&&(Map[ypos][xpos] != 0xFE)) {
        txpos = xpos;
        typos = ypos;
        }
    }

void generate_new_path(void) {
    bcopy(Map, PathArray, sizeof(Map));
    founded = FALSE;
    pathfind(txpos, typos, 1);
    }

u16 random_range(u16 min, u16 max) {
    u16 num = random_u16();
    return (num % ((max + 1) - min)) + min;
    }

u8 visible = FALSE;
u8 straightline = FALSE;

u8 RAN = FALSE;
u8 badmarks =0;

f32 speed = 15.0f;
f32 basespeed = 15.0f;
u8 sighttimer = 250;

u16 lookdir;

s16 power = 2000;
u8 powerfixes = 0;

f32 signreadposx;
f32 signreadposz;
f32 signreadposy;
u16 signreadrot;

u8 old_red_coin;

void bhv_monster_loop(void) {
    u8 rayhitx;
    u8 rayhity;
    f32 dist = 0.0f;
    f32 dx = 0.0f;
    f32 dz = 0.0f;
    s8 i;
    f32 worldposx = o->oPosX;
    f32 worldposy = o->oPosY;

    f32 homeDistX = 0.0f;
    f32 homeDistZ = 0.0f;
    s16 angleTowardsHome;

    f32 raycastx = 0.0f;
    f32 raycastz = 0.0f;

    f32 floor = 0.0f;

    basespeed = 15.0f + ((f32)(gMarioState->EA_WAVES)*5.0f);
    if (speed < basespeed) {
        speed = basespeed;
    }

    //"Raycast"
    raycastx = o->oPosX;
    raycastz = o->oPosZ;

    visible = FALSE;
    straightline = TRUE;

    rayhitx = (u8)((raycastx/800)+10);
    rayhity = (u8)((raycastz/800)+10);

    //only raycast if mario is not behind the sign
    if ((obj_check_if_facing_toward_angle(o->oFaceAngleYaw+0x2000, o->oAngleToMario, 0x7000))||(obj_check_if_facing_toward_angle(o->oFaceAngleYaw-0x2000, o->oAngleToMario, 0x7000))||(obj_check_if_facing_toward_angle(o->oFaceAngleYaw, o->oAngleToMario, 0x7000))||(sighttimer < 10)) {
        while (Map[rayhity][rayhitx] != 0xFF) {
            //Check if can see mario
            dx = raycastx - gMarioObject->oPosX;
            dz = raycastz - gMarioObject->oPosZ;

            dist = sqrtf(dx * dx + dz * dz);
            if (dist < 75.0f) {
                visible = TRUE;
                sighttimer = 0;
                }

            if (Map[rayhity][rayhitx] == 0xFE) {
                straightline = FALSE;
                }

            //move
            raycastx += 75.0f * sins(o->oAngleToMario);
            raycastz += 75.0f * coss(o->oAngleToMario);

            rayhitx = (u8)((raycastx/800)+10);
            rayhity = (u8)((raycastz/800)+10);
            }
        }
    

    if (sighttimer > 254) {
        sighttimer = 254;
        }
        else
        {
        sighttimer ++;
        }

    //TRUE INIT
    if (o->oAction == 0) {
        old_red_coin = 0;
        visible = FALSE;
        straightline = FALSE;
        badmarks =0;
        speed = 15.0f;
        basespeed = 15.0f;
        sighttimer = 250;
        power = 2000;
        powerfixes = 0;
        txpos = 10;
        typos = 18;
        xsignpos = 10;
        ysignpos = 18;
        MouthOpen = FALSE;
        gMarioState->EA_WAVES = 0;
        gMarioState->gCurrMinigame = 8;

        o->oAction = 3;
        }

    if (o->oAction == 1) {

        worldposx = -8000+(xsignpos*800)+400;
        worldposy = -8000+(ysignpos*800)+400;
        homeDistX = worldposx - o->oPosX;
        homeDistZ = worldposy - o->oPosZ;
        angleTowardsHome = atan2s(homeDistZ, homeDistX);

        if ((straightline)&&(visible)) {
            MouthOpen = TRUE;
            o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, o->oAngleToMario, 45*(s16)(speed));
            if ((Map[(u8)((o->oPosZ/800)+10)][(u8)((o->oPosX/800)+10)] != 0xFF)&&(Map[(u8)((o->oPosZ/800)+10)][(u8)((o->oPosX/800)+10)] != 0xFE)) {
                xsignpos = (u8)((o->oPosX/800)+10);
                ysignpos = (u8)((o->oPosZ/800)+10);
                generate_new_path();
                }
            }
            else
            {
            o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, angleTowardsHome, 45*(s16)(speed));
            MouthOpen = FALSE;
            }

        o->oPosX += speed * sins(o->oFaceAngleYaw);
        o->oPosZ += speed * coss(o->oFaceAngleYaw);

        floor = find_floor_height(o->oPosX, o->oHomeY + 600.0f, o->oPosZ);
        if (floor > o->oHomeY-300.0f) {
            o->oPosY = floor;
            }

        //set new target if find old one (roam)
        dx = o->oPosX - (-8000+(txpos*800)+400);
        dz = o->oPosZ - (-8000+(typos*800)+400);

        dist = sqrtf(dx * dx + dz * dz);
        if (dist < 400.0f) {
            newtarget_grid(random_range(1,18),random_range(1,18));

            //give audio cue 
            if ((visible == FALSE)&&(random_range(1,3) == 3)) {
                cur_obj_play_sound_2(SOUND_GENERAL_DRAWBRIDGE_LOWER);
                }
            }

            //GO TO SOUND IF HEAR SOUND
        //if ((gMarioState->enableglobalsound == TRUE)&&(dist > 400.0f)) {
        //    newtarget(gMarioState->globalsoundX,gMarioState->globalsoundZ);
        //    gMarioState->enableglobalsound = FALSE;
        //    }

        if (speed > basespeed) {
            speed -= .5;
            }

        //target mario if he sees him
        if ((visible == TRUE)||(sighttimer < 250)) {
            if (sighttimer < 7) {
                if (speed < basespeed*1.5) {
                    speed ++;
                    }
                }
            newtarget(gMarioState->pos[0],gMarioState->pos[2]);
            }

        if ((gMarioState->action & ACT_GROUP_MASK) == ACT_GROUP_CUTSCENE) {
            speed = 0;
        }

        //jumpscare if close
        dx = o->oPosX - gMarioObject->oPosX;
        dz = o->oPosZ - gMarioObject->oPosZ;

        dist = sqrtf(dx * dx + dz * dz);
        if (dist < 400.0f) {
            o->oAction = 2;
            o->oTimer = 0;
            }


        }
    
    if (o->oAction == 2) {
        if (o->oTimer == 1) {
            gCamera->cutscene = 0xFF;
            play_sound(SOUND_OBJ2_BOWSER_ROAR, gGlobalSoundSource);
            cur_obj_init_animation(2);
            MouthOpen = FALSE;
            }

        if (random_range(0,5) == 5) {
            MouthOpen = !MouthOpen;
            }

        if (o->oTimer == 40) {
            level_trigger_warp(gMarioState, WARP_OP_DEATH);
            }
            gMarioState->faceAngle[1] = o->oAngleToMario+0x8000;

            set_environmental_camera_shake(SHAKE_ENV_FALLING_BITS_PLAT);
            o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, o->oAngleToMario, 1800);


            o->oPosX = gMarioObject->oPosX+(1000.0f*sins(gMarioState->faceAngle[1]));
            o->oPosZ = gMarioObject->oPosZ+(1000.0f*coss(gMarioState->faceAngle[1]));
            o->oPosY = o->oHomeY;
        }

    if (o->oAction == 3) {

        if (gMarioState->EA_WAVES == 1) {
            create_sound_spawner(SOUND_GENERAL2_BOBOMB_EXPLOSION);
            set_environmental_camera_shake(SHAKE_ENV_EXPLOSION);
            o->oAction = 1;
            cur_obj_init_animation(1);
            }
        }

    if ((txpos != old_txpos)||(typos != old_typos)) {
        old_txpos = txpos;
        old_typos = typos;
        generate_new_path();
        }

    dx = worldposx - o->oPosX;
    dz = worldposy - o->oPosZ;

    dist = sqrtf(dx * dx + dz * dz);

    if ((dist < 350.0f)&&(founded==TRUE)) {

        lowest = 255;
        fourdirs[0] = PathArray[ysignpos+1][xsignpos];
        fourdirs[1] = PathArray[ysignpos-1][xsignpos];
        fourdirs[2] = PathArray[ysignpos][xsignpos+1];
        fourdirs[3] = PathArray[ysignpos][xsignpos-1];

        badmarks = 0;

        for (i = 0; i < 4; i++) {
            if ((fourdirs[i] > 253)&&(fourdirs[i] == 0)) {
                badmarks ++;
                }

            if ((fourdirs[i] < lowest)&&(fourdirs[i] < 254)&&(fourdirs[i] != 0)) {
                whichone = i;
                lowest = fourdirs[i];
                }
            }

        if (badmarks < 4) {
            if (whichone == 0) {
                ysignpos ++;
                }
            if (whichone == 1) {
                ysignpos --;
                }
            if (whichone == 2) {
                xsignpos ++;
                }
            if (whichone == 3) {
                xsignpos --;
                }
            }
        }

    signreadposx = o->oPosX;
    signreadposz = o->oPosZ;
    signreadposy = o->oPosY;
    signreadrot = o->oFaceAngleYaw;
}
