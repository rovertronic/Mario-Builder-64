


void check_phantasm_attack(void) {

    cur_obj_set_hitbox_radius_and_height(100.0f, 100.0f);
    cur_obj_set_hurtbox_radius_and_height(100.0f, 80.0f);

    o->oDamageOrCoinValue = 3;

    cur_obj_become_tangible();
    o->oInteractType = INTERACT_BOUNCE_TOP;

    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
            o->oAction = 3;
            cur_obj_init_animation_with_sound(4);//hurt
            o->oForwardVel = -30.0f;
            o->oMoveAngleYaw = gMarioState->faceAngle[1]+0x8000;
            o->oFaceAngleYaw = o->oMoveAngleYaw;

            if (mb64_play_badge_bitfield & (1 << BADGE_DAMAGE)) {
                o->oHealth = 0;
            } else {
                o->oHealth --;
            }
        }
    }

    o->oInteractStatus = 0;
    o->oIntangibleTimer = 0;
}

void phantasm_invincible(void) {
    cur_obj_set_hitbox_radius_and_height(100.0f, 100.0f);
    cur_obj_set_hurtbox_radius_and_height(150.0f, 120.0f);

    o->oDamageOrCoinValue = 3;

    cur_obj_become_tangible();
    o->oInteractType = INTERACT_DAMAGE;

    o->oInteractStatus = 0;
    o->oIntangibleTimer = 0;
}

void bhv_cosmic_phantasm(void) {
    struct Object *hammer;
    struct Surface *ptr;

    Vec3f previous;
    vec3f_copy(previous,&o->oPosVec); //record position before moving step
    f32 old_floor_height = find_floor(o->oPosX, o->oPosY, o->oPosZ, &ptr);

    cur_obj_update_floor_and_walls();
    cur_obj_set_home_if_safe();
    cur_obj_move_standard(-78);

    if (is_cur_obj_interact_with_lava(0)) {
        spawn_object(o, MODEL_RED_FLAME, bhvKoopaShellFlame);
    }

    f32 kept_new_y = o->oPosY; //keeping the new y position, a little scuffed
    o->oGravity = -4.0f;

    switch(o->oAction) {
        case 0:
            o->oQuicksandDepthToDie = 0;
            o->oHealth = 3;
            o->oNumLootCoins = 5;
            if (o->oBehParams2ndByte == 2) {
                o->oHealth = 2;
                o->oNumLootCoins = 0;
            }

            o->oAction = 1;
            o->oTimer = random_u16()%60;
            cur_obj_init_animation_with_sound(2);//idle
        break;
        case 1://idle ground
            o->oForwardVel = 0.0f;
            if (o->oTimer > 100) {//move around a bit
                o->oAction = 2;
                o->oTimer = random_u16()%60;
                o->oAngleVelYaw = random_u16();
                cur_obj_init_animation_with_sound(3);//walk
            }
            if ((obj_check_if_facing_toward_angle(o->oMoveAngleYaw, o->oAngleToMario, 0x2000)&&
            (o->oDistanceToMario < 1000.0f)) || (o->oDistanceToMario < 400.f)) {
                o->oAction = (random_u16()%2) ? 4 : 6;
                o->oSubAction = 0;
                cur_obj_init_animation_with_sound(5);//spin

            }
            check_phantasm_attack();
        break;
        case 2://wander
            o->oForwardVel = 10.0f;
            o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw,o->oAngleVelYaw,4);
            o->oFaceAngleYaw = o->oMoveAngleYaw;
            if (o->oTimer % 8 == 0) {
                cur_obj_play_sound_2(SOUND_ACTION_METAL_STEP);
            }
            if (o->oTimer % 20 == 0) {
                o->oAngleVelYaw = random_u16();
            }
            if (o->oTimer > 100) {//idle after a bit
                o->oAction = 1;
                o->oTimer = random_u16()%60;
                cur_obj_init_animation_with_sound(2);//walk
            }
            if ((obj_check_if_facing_toward_angle(o->oMoveAngleYaw, o->oAngleToMario, 0x2000)&&
            (o->oDistanceToMario < 1000.0f)) || (o->oDistanceToMario < 400.f)) {
                o->oAction = (random_u16()%2) ? 4 : 6;
                o->oSubAction = 0;
                cur_obj_init_animation_with_sound(5);//spin
            }
            check_phantasm_attack();
        break;
        case 3://attacked
            o->oForwardVel *= .93f;
            o->oInteractStatus |= INT_STATUS_INTERACTED;

            if (o->oTimer == 30) {//die if killed
                if (o->oHealth < 1) {
                    //gMarioState->EA_ACTIVE --;
                    //gMarioState->EA_LEFT --;

                    if (!cur_obj_drop_imbued_object(MB64_STAR_HEIGHT)) {
                        obj_spawn_loot_yellow_coins(o, 5, 20.0f);
                    }
                    spawn_mist_particles_variable(0, 0, 100.0f);
                    obj_mark_for_deletion(o);
                }
            }

            if (o->oTimer > 50) {
                o->oInteractStatus = 0;
                o->oIntangibleTimer = 0;
                o->oAction = 4;
                cur_obj_init_animation_with_sound(5);//spin
            }
        break;
        case 4://alert

            o->oGravity = -0.5f;
            if (o->oPosY < gMarioState->pos[1] + 300.0f) {
                o->oGravity = 0.5f;
            }

            if (o->oTimer > 60) {
                o->oAction = 5;
                o->oSubAction = 0;
                cur_obj_play_sound_2(SOUND_OBJ_MRI_SHOOT);
            }

            if (o->oTimer < 40) {
                o->oMoveAngleYaw = o->oAngleToMario;
                o->oForwardVel -= 2.0f;
                if (o->oForwardVel < -20.0f) {
                    o->oForwardVel = -20.0f;
                    }
                o->oFaceAngleYaw += 0x2000;
                if (o->oTimer % 5 == 0) {
                    cur_obj_play_sound_2(SOUND_ACTION_SPIN);
                }
            } else {
                o->oForwardVel = 0.0f;
                o->oVelY = 0.0f;
                o->oGravity = 0.0f;
            }

            check_phantasm_attack();
        break;
        case 5://kick attack
            if (o->oTimer == 1) {//fake init
                cur_obj_init_animation_with_sound(6);
                o->oVelY = -3.0f;
                o->oForwardVel = (o->oDistanceToMario/3.0f)+40.0f;
                if (o->oForwardVel > 75.0f) {
                    o->oForwardVel = 75.0f;
                }
                o->oMoveAngleYaw = o->oAngleToMario;
                o->oFaceAngleYaw = o->oMoveAngleYaw;
            }
            if (o->oTimer>1) {//loop
                o->oForwardVel *= .95f;

                if (o->oForwardVel < 1.0f) {
                    o->oAction = 2;
                    o->oTimer = random_u16()%60;
                    cur_obj_init_animation_with_sound(3);//walk
                }
                if (o->oForwardVel < 10.0f) {
                    check_phantasm_attack();
                } else {
                    phantasm_invincible();
                }
            }
        break;
        case 6://throw fireballs
            switch(o->oSubAction) {
                case 0:
                    o->oForwardVel = 0.f;
                    if (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND) {
                        o->oSubAction = 2;
                        cur_obj_init_animation_with_sound(7);
                        o->oVelY = 0.0f;
                    }
                    break;
                case 2:
                    //throw fire
                    o->oForwardVel = 0.0f;
                    if (o->oTimer <= 125) {
                        o->oForwardVel = -10.0f;
                        o->oMoveAngleYaw = o->oAngleToMario;
                        o->oFaceAngleYaw = o->oAngleToMario;
                        if (o->oTimer % 25 == 0) {
                            cur_obj_init_animation_with_sound(7);
                            cur_obj_init_animation_with_sound(8);

                            cur_obj_play_sound_2(SOUND_OBJ_MRI_SHOOT);
                            hammer = spawn_object(o, MODEL_RED_FLAME, bhvFireBroBall);
                            hammer->oMoveAngleYaw = o->oFaceAngleYaw;
                            hammer->oVelY = 20.0f;
                            hammer->oForwardVel = 30.0f;
                            hammer->oPosY += 20.0f;
                            hammer->oFlags |= OBJ_FLAG_ACTIVE_FROM_AFAR;
                        }
                    }

                    if (o->oTimer > 160) {
                        o->oAction = 2;
                        o->oTimer = random_u16()%60;
                        cur_obj_init_animation_with_sound(3);//walk
                    }
                break;
            }
            check_phantasm_attack();
        break;
        case 7:
            //being dispensed
            if (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND) {
                o->oAction = 0;
            }
        break;
    }

    f32 current_floor_height = find_floor(o->oPosX, o->oPosY, o->oPosZ, &ptr);

    if (current_floor_height < old_floor_height-300.0f) {
        vec3f_copy(&o->oPosVec,previous);//Prevent him from going off the ledge
        o->oPosY = kept_new_y;//this is a little cringe, but who cares
        o->oForwardVel = 0.f;
    }

    cur_obj_die_if_on_death_barrier(MB64_STAR_HEIGHT);
}

// void bhv_paparazzi(void) {
//     cur_obj_set_hitbox_radius_and_height(100.0f, 100.0f);
//     cur_obj_set_hurtbox_radius_and_height(100.0f, 80.0f);

//     cur_obj_become_tangible();
//     o->oInteractType = INTERACT_BOUNCE_TOP;

//     if (o->oInteractStatus & INT_STATUS_INTERACTED) {
//         if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
//             set_mario_action(gMarioState, ACT_DOUBLE_JUMP, 0);
//             mario_stop_riding_and_holding(gMarioState);
//             run_event(EVENT_STATUE_ROTATE);
//             spawn_mist_particles_variable(0, 0, 100.0f);
//             obj_mark_for_deletion(o);
//         }
//     }

//     o->oInteractStatus = 0;
//     o->oIntangibleTimer = 0;
// }
