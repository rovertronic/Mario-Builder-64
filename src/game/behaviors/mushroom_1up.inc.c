// mushroom_1up.inc.c

// void bhv_1up_interact(void) {
//     if (obj_check_if_collided_with_object(o, gMarioObject)) {
//         play_sound(SOUND_GENERAL_COLLECT_1UP, gGlobalSoundSource);
// #ifdef MUSHROOMS_HEAL
//         gMarioState->healCounter   = 31;
// #ifdef BREATH_METER
//         gMarioState->breathCounter = 31;
// #endif
// #endif
// #ifdef ENABLE_LIVES
//         gMarioState->numLives++;
// #endif
//         o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
// #if ENABLE_RUMBLE
//         queue_rumble_data(5, 80);
// #endif
//     }
// }

// void bhv_1up_common_init(void) {
//     o->oMoveAnglePitch = -0x4000;
//     o->oGravity = 3.0f;
//     o->oFriction = 1.0f;
//     o->oBuoyancy = 1.0f;
// }
// //gMarioState->powerup

// void bhv_1up_init(void) {
//     bhv_1up_common_init();
// #ifndef UNLOCK_ALL
//     if (o->oBehParams2ndByte == MUSHROOM_BP_REQUIRES_BOWSER_1) {
//         if (!(save_file_get_flags() & (SAVE_FLAG_HAVE_KEY_1 | SAVE_FLAG_UNLOCKED_BASEMENT_DOOR))) {
//             o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
//         }
//     } else if (o->oBehParams2ndByte == MUSHROOM_BP_REQUIRES_BOWSER_2) {
//         if (!(save_file_get_flags() & (SAVE_FLAG_HAVE_KEY_2 | SAVE_FLAG_UNLOCKED_UPSTAIRS_DOOR))) {
//             o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
//         }
//     }
// #endif
// }

// void one_up_loop_in_air(void) {
//     if (o->oTimer < 5) {
//         o->oVelY = 40.0f;
//     } else {
//         o->oAngleVelPitch = -0x1000;
//         o->oMoveAnglePitch += o->oAngleVelPitch;
//         o->oVelY = coss(o->oMoveAnglePitch) * 30.0f + 2.0f;
//         o->oForwardVel = -sins(o->oMoveAnglePitch) * 30.0f;
//     }
// }

// void pole_1up_move_towards_mario(void) {
//     f32 dx = gMarioObject->header.gfx.pos[0] - o->oPosX;
//     f32 dy = gMarioObject->header.gfx.pos[1] - o->oPosY + 120.0f;
//     f32 dz = gMarioObject->header.gfx.pos[2] - o->oPosZ;
//     s16 targetPitch = atan2s(sqrtf(sqr(dx) + sqr(dz)), dy);

//     obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x1000);

//     o->oMoveAnglePitch = approach_s16_symmetric(o->oMoveAnglePitch, targetPitch, 0x1000);
//     o->oVelY = sins(o->oMoveAnglePitch) * 30.0f;
//     o->oForwardVel = coss(o->oMoveAnglePitch) * 30.0f;

//     bhv_1up_interact();
// }

// void one_up_move_away_from_mario(s16 collisionFlags) {
//     o->oForwardVel = 8.0f;
//     o->oMoveAngleYaw = o->oAngleToMario + 0x8000;

//     bhv_1up_interact();

//     if (collisionFlags & OBJ_COL_FLAG_HIT_WALL) {
//         o->oAction = MUSHROOM_ACT_DISAPPEARING;
//     }

//     if (!is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 3000)) {
//         o->oAction = MUSHROOM_ACT_DISAPPEARING;
//     }
// }

// void bhv_1up_walking_loop(void) {
//     object_step();//

//     switch (o->oAction) {
//         case MUSHROOM_ACT_INIT:
//             if (o->oTimer > 17) {
//                 spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
//             }

//             if (o->oTimer == 0) {
//                 play_sound(SOUND_GENERAL2_1UP_APPEAR, gGlobalSoundSource);
//             }

//             one_up_loop_in_air();

//             if (o->oTimer == 37) {
//                 cur_obj_become_tangible();
//                 o->oAction = MUSHROOM_ACT_MOVING;
//                 o->oForwardVel = 2.0f;
//             }
//             break;

//         case MUSHROOM_ACT_MOVING:
//             if (o->oTimer > 300) {
//                 o->oAction = MUSHROOM_ACT_DISAPPEARING;
//             }

//             bhv_1up_interact();
//             break;

//         case MUSHROOM_ACT_DISAPPEARING:
//             obj_flicker_and_disappear(o, 30);
//             bhv_1up_interact();
//             break;
//     }

//     set_object_visibility(o, 3000);
// }

// void bhv_1up_running_away_loop(void) {
//     s16 collisionFlags = object_step();

//     switch (o->oAction) {
//         case MUSHROOM_ACT_INIT:
//             if (o->oTimer > 17) {
//                 spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
//             }

//             if (o->oTimer == 0) {
//                 play_sound(SOUND_GENERAL2_1UP_APPEAR, gGlobalSoundSource);
//             }

//             one_up_loop_in_air();

//             if (o->oTimer == 37) {
//                 cur_obj_become_tangible();
//                 o->oAction = MUSHROOM_ACT_MOVING;
//                 o->oForwardVel = 8.0f;
//             }
//             break;

//         case MUSHROOM_ACT_MOVING:
//             spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
//             one_up_move_away_from_mario(collisionFlags);
//             break;

//         case MUSHROOM_ACT_DISAPPEARING:
//             obj_flicker_and_disappear(o, 30);
//             bhv_1up_interact();
//             break;
//     }

//     set_object_visibility(o, 3000);
// }

// void sliding_1up_move(void) {
//     s16 collisionFlags = object_step();

//     if (collisionFlags & OBJ_COL_FLAG_GROUNDED) {
//         o->oForwardVel += 25.0f;
//         o->oVelY = 0.0f;
//     } else {
//         o->oForwardVel *= 0.98f;
//     }

//     if (o->oForwardVel > 40.0) {
//         o->oForwardVel = 40.0f;
//     }

//     if (!is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 5000)) {
//         o->oAction = MUSHROOM_ACT_DISAPPEARING;
//     }
// }

// void bhv_1up_sliding_loop(void) {
//     switch (o->oAction) {
//         case MUSHROOM_ACT_INIT:
//             set_object_visibility(o, 3000);
//             if (is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 1000)) {
//                 o->oAction = MUSHROOM_ACT_MOVING;
//             }
//             break;

//         case MUSHROOM_ACT_MOVING:
//             sliding_1up_move();
//             break;

//         case MUSHROOM_ACT_DISAPPEARING:
//             obj_flicker_and_disappear(o, 30);
//             bhv_1up_interact();
//             break;
//     }

//     bhv_1up_interact();
//     spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
// }

// void bhv_1up_loop(void) {
//     bhv_1up_interact();
//     set_object_visibility(o, 3000);
// }

// void bhv_1up_jump_on_approach_loop(void) {
//     s16 collisionFlags;

//     switch (o->oAction) {
//         case MUSHROOM_ACT_INIT:
//             if (is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 1000)) {
//                 o->oVelY = 40.0f;
//                 o->oAction = MUSHROOM_ACT_MOVING;
//             }
//             break;

//         case MUSHROOM_ACT_MOVING:
//             collisionFlags = object_step();
//             one_up_move_away_from_mario(collisionFlags);
//             spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
//             break;

//         case MUSHROOM_ACT_DISAPPEARING:
//             collisionFlags = object_step();
//             bhv_1up_interact();
//             obj_flicker_and_disappear(o, 30);
//             break;
//     }

//     set_object_visibility(o, 3000);
// }

// void bhv_1up_hidden_loop(void) {
//     s16 collisionFlags;

//     switch (o->oAction) {
//         case MUSHROOM_ACT_INIT:
//             o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
//             if (o->o1UpHiddenTimesTriggered == o->oBehParams2ndByte) {
//                 o->oVelY = 40.0f;
//                 o->oAction = MUSHROOM_ACT_LOOP_IN_AIR;
//                 o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
//                 play_sound(SOUND_GENERAL2_1UP_APPEAR, gGlobalSoundSource);
//             }
//             break;

//         case MUSHROOM_ACT_MOVING:
//             collisionFlags = object_step();
//             one_up_move_away_from_mario(collisionFlags);
//             spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
//             break;

//         case MUSHROOM_ACT_DISAPPEARING:
//             collisionFlags = object_step();
//             bhv_1up_interact();
//             obj_flicker_and_disappear(o, 30);
//             break;

//         case MUSHROOM_ACT_LOOP_IN_AIR:
//             collisionFlags = object_step();
//             if (o->oTimer > 17) {
//                 spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
//             }

//             one_up_loop_in_air();

//             if (o->oTimer == 37) {
//                 cur_obj_become_tangible();
//                 o->oAction = MUSHROOM_ACT_MOVING;
//                 o->oForwardVel = 8.0f;
//             }
//             break;
//     }
// }

// void bhv_1up_hidden_trigger_loop(void) {
//     if (obj_check_if_collided_with_object(o, gMarioObject)) {
//         struct Object *nearestHidden1up = cur_obj_nearest_object_with_behavior(bhvHidden1up);
//         if (nearestHidden1up != NULL) {
//             nearestHidden1up->o1UpHiddenTimesTriggered++;
//         }

//         o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
//     }
// }

// void bhv_1up_hidden_in_pole_loop(void) {
//     switch (o->oAction) {
//         case MUSHROOM_ACT_INIT:
//             o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
//             if (o->o1UpHiddenTimesTriggered == o->oBehParams2ndByte) {
//                 o->oVelY = 40.0f;
//                 o->oAction = MUSHROOM_ACT_LOOP_IN_AIR;
//                 o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
//                 play_sound(SOUND_GENERAL2_1UP_APPEAR, gGlobalSoundSource);
//             }
//             break;

//         case MUSHROOM_ACT_MOVING:
//             pole_1up_move_towards_mario();
//             object_step();
//             break;

//         case MUSHROOM_ACT_LOOP_IN_AIR:
//             object_step();
//             if (o->oTimer > 17) {
//                 spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
//             }

//             one_up_loop_in_air();

//             if (o->oTimer == 37) {
//                 cur_obj_become_tangible();
//                 o->oAction = MUSHROOM_ACT_MOVING;
//                 o->oForwardVel = 10.0f;
//             }
//             break;
//     }
// }

// void bhv_1up_hidden_in_pole_trigger_loop(void) {
//     if (obj_check_if_collided_with_object(o, gMarioObject)) {
//         struct Object *nearestHidden1upInPole = cur_obj_nearest_object_with_behavior(bhvHidden1upInPole);
//         if (nearestHidden1upInPole != NULL) {
//             nearestHidden1upInPole->o1UpHiddenTimesTriggered++;
//         }

//         o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
//     }
// }

// void bhv_1up_hidden_in_pole_spawner_loop(void) {
//     if (is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 700)) {
//         s8 i;
//         spawn_object_relative(2, 0, 50, 0, o, MODEL_1UP, bhvHidden1upInPole);
//         for (i = 0; i < 2; i++) {
//             spawn_object_relative(0, 0, i * -200, 0, o, MODEL_NONE, bhvHidden1upInPoleTrigger);
//         }

//         o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
//     }
// }

void bhv_crowbar_power_loop() {
        struct Object *sp1C;
        u8 power = o->oBehParams2ndByte+1;
        sp1C = cur_obj_nearest_object_with_behavior(bhvCrowbarThrow);

        if (gMarioState->powerup != power && sp1C == NULL) {
            spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
            o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            o->oFaceAngleYaw += 1000;
            o->oFaceAnglePitch = 0x1A00;
        
            if (obj_check_if_collided_with_object(o, gMarioObject) == 1) {
                play_sound(SOUND_MENU_EXIT_PIPE, gGlobalSoundSource);
                gMarioState->powerup = power;
            }
        }
        else
        {
        o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
        }
    }

void bhv_crowbar_attack_loop() {
        s16 sp1E = object_step_without_floor_orient();
        struct Object *sp1C;
        //sp1C = cur_obj_nearest_object_with_behavior(bhvMetalCrate);

        o->oFaceAngleYaw += 8000;
            if (o->oFaceAngleYaw > 0x10000) {
                cur_obj_play_sound_2(SOUND_ACTION_SIDE_FLIP_UNK);
                o->oFaceAngleYaw = 0;
            }


        if (o->oInteractStatus & INT_STATUS_INTERACTED) {
            cur_obj_play_sound_2(SOUND_ACTION_METAL_STEP);
        }

        if (o->oAction == 0) {
            //DESTROY METAL CRATE
            // if (sp1C != 0) {
            //     if (dist_between_objects(o,sp1C) < 250.0f) {
            //         sp1C->oHealth --;
            //         sp1C->oPosY += 10.0f;
            //         sp1C->oVelY -= 20.0f;
            //         cur_obj_play_sound_2(SOUND_ACTION_METAL_STEP);
            //         o->oAction = 1;
            //         o->oTimer = 0;
            //         o->oMoveAngleYaw += 0x8000;
            //         cur_obj_become_intangible();
            //         }
            //     }
            //KILL ENEMIES
            obj_attack_collided_from_other_object(o);

            if (o->oTimer > 5) {
                cur_obj_become_tangible();
                }

            if (sp1E & 2) {
                cur_obj_play_sound_2(SOUND_ACTION_METAL_STEP);
                }

            o->oForwardVel --;

            if (o->oTimer > 40) {
                o->oAction = 1;
                o->oTimer = 0;
                o->oMoveAngleYaw += 0x8000;
                cur_obj_become_intangible();
                }
            
            if (o->numCollidedObjs > 0) {
                o->oAction = 1;
                o->oTimer = 0;
                o->oMoveAngleYaw += 0x8000;
                cur_obj_become_intangible();
                }
            }
        
        if (o->oAction == 1) {
            f32 sp34 = gMarioObject->header.gfx.pos[0] - o->oPosX;
            f32 sp30 = gMarioObject->header.gfx.pos[1] + 120.0f - o->oPosY;
            f32 sp2C = gMarioObject->header.gfx.pos[2] - o->oPosZ;
            s16 sp2A = atan2s(sqrtf(sqr(sp34) + sqr(sp2C)), sp30);

            obj_turn_toward_object(o, gMarioObject, 16, 0x1000);
            o->oMoveAnglePitch = approach_s16_symmetric(o->oMoveAnglePitch, sp2A, 0x1000);
            o->oVelY = sins(o->oMoveAnglePitch) * 80.0f;
            o->oForwardVel = coss(o->oMoveAnglePitch) * 80.0f;

            //DIE
            if (o->oDistanceToMario < 200.0f || o->oTimer > 120) {
                if (gMarioState->powerup == 0) {
                    gMarioState->powerup = 1;
                    }
                mark_obj_for_deletion(o);
                }

            }
    }

//>forwardVel mario

void bhv_zipline_loop() {
    if (o->oAction == 0) {
        if ((o->oDistanceToMario < 200.0f)&&(gMarioState->powerup == 1)) {
            gMarioState->faceAngle[0] = o->oFaceAngleYaw;
            gMarioObject->header.gfx.angle[1] = o->oFaceAngleYaw;
            set_mario_action(gMarioState, ACT_ZIPLINE, 0);
            o->oAction = 1;
            o->oForwardVel = 20;
            o->oHomeY = gMarioState->forwardVel;
            }
        }
    if (o->oAction == 1) {
            o->oForwardVel += o->oHomeY;
            if (o->oHomeY < 40.0f) {
                o->oHomeY += 1.0f;
                }
            gMarioState->pos[0] = o->oPosX + o->oForwardVel * sins(o->oFaceAngleYaw);
            gMarioState->pos[1] = o->oPosY + o->oForwardVel * -sins(o->oFaceAnglePitch);
            gMarioState->pos[2] = o->oPosZ + o->oForwardVel * coss(o->oFaceAngleYaw);
            gMarioState->faceAngle[0] = o->oFaceAngleYaw;
            gMarioObject->header.gfx.angle[1] = o->oFaceAngleYaw;

            if (o->oForwardVel > o->oBehParams2ndByte*100.0f) {
                o->oAction = 0;
                gMarioState->forwardVel = o->oHomeY;
                set_mario_action(gMarioState, ACT_FREEFALL, 0);
                }
        }
    }



void bhv_item_bubble_loop() {
    s32 behparam1 = (gCurrentObject->oBehParams >> 24) & 0xFF;

    struct Object *bubble;
    f32 BubDist;
    BubDist = 999.0f;

    bubble = cur_obj_nearest_object_with_behavior(bhvItemBubble);

    if (bubble != NULL) {
            BubDist = lateral_dist_between_objects(o,bubble);
            }

    switch (o->oAction) {
        case 0:
            o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            if (o->oDistanceToMario < 3000) {
                o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
                o->oAction = 1;
                switch(o->oBehParams2ndByte) {
                    case 0:
                    o->prevObj = spawn_object(o, MODEL_YELLOW_COIN, bhvMovingYellowCoin);
                    break;
                    case 1:
                    o->prevObj = spawn_object(o, MODEL_1UP, bhv1upSliding);
                    break;
                    case 2:
                    o->prevObj = spawn_object(o, 0xEF, bhvMovingGreenCoin);
                    break;
                    case 3:
                    o->prevObj = spawn_object(o, MODEL_GOOMBA, bhvGoomba);
                    break;
                    case 4:
                    o->prevObj = spawn_object(o, MODEL_THWOMP, bhvThwomp);
                    break;
                    }
                }

        break;
        case 1:
            //set object
            o->prevObj->oTimer = 0;
            o->prevObj->oVelY = 0;
            o->prevObj->oPosX = o->oPosX;
            o->prevObj->oPosZ = o->oPosZ;
            o->prevObj->oAction = 0;


            o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            o->prevObj->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;

            if (o->oDistanceToMario < 3000) {
                o->prevObj->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
                o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;

                if (o->oBehParams2ndByte > 2) {
                    o->prevObj->oFaceAngleRoll = 0x7FFF;
                    o->prevObj->oPosY = o->oPosY+140;
                    }
                    else
                    {
                    o->prevObj->oPosY = o->oPosY+70;
                    }

                //Move
                o->oPosY = o->oHomeY + (55.0f * sins(o->oTimer*500));

                if (o->oBehParams2ndByte > 2) {
                //CHASE MARIO CUZ UR EVIL
                    if (cur_obj_lateral_dist_from_mario_to_home() > 2000.0f) {
                        o->oAngleToMario = cur_obj_angle_to_home();
                        o->oForwardVel = 5.0f;
                    } else {
                        o->oAngleToMario = obj_angle_to_object(o, gMarioObject);
                        o->oForwardVel = 20.0f;
                        }

                    cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x400);
                    cur_obj_move_using_vel_and_gravity();
                    }
                }

            //collision
            if ((o->oDistanceToMario < 200)||(BubDist < 200)) {
                cur_obj_play_sound_2(SOUND_OBJ2_PIRANHA_PLANT_BITE);
                spawn_object(o,MODEL_BUBBLE,bhvKoopaShellFlame);
                spawn_object(o,MODEL_BUBBLE,bhvKoopaShellFlame);
                spawn_object(o,MODEL_BUBBLE,bhvKoopaShellFlame);
                o->prevObj->oFaceAngleRoll = 0;
                o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
                o->oAction = 5;
                o->oTimer = 0;
                }

        break;
        case 5:
            if (o->oTimer > 30) {
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
                }
        break;
        }

    }

// u8 shitcum_animstate_table[] = {0,0,0,0,0,0,1,1,2,2,3,3,3,3,3,3,2,2,1,1};
// //im eating fucking doritos right now
// // im such a sfucking labzy slob

// //shut the fuck up bruh ^^^

// void bhv_dragon_coin_loop() {

//     //change B pressed to not B pressed
//     if (gMarioState->IsYoshi) {
//         o->oAnimState = shitcum_animstate_table[o->oTimer];
//         if (o->oTimer == 19) {
//             o->oTimer = 0;
//             }

//         if (o->oDistanceToMario < 100.0f) {
//             gMarioState->numCoins += 2;
//             gMarioState->YoshiCoins ++;
//             spawn_object(o, MODEL_SPARKLES, bhvCoinSparklesSpawner);
//             mark_obj_for_deletion(o);
//             }
//         }
//         else
//         {
//         o->oAnimState = 4;
//         o->oTimer = 0;
//         }
//     }
