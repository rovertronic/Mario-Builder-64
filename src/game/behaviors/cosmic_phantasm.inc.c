


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

            if (save_file_get_badge_equip() & (1 << BADGE_DAMAGE)) {
                o->oHealth -= 2;
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

    o->oDamageOrCoinValue = 4;

    cur_obj_become_tangible();
    o->oInteractType = INTERACT_DAMAGE;

    o->oInteractStatus = 0;
    o->oIntangibleTimer = 0;
}

void bhv_cosmic_phantasm(void) {
    struct Object *hammer;
    struct Surface *ptr;

    Vec3f previous;
    vec3f_copy(&previous,&o->oPosVec); //record position before moving step

    cur_obj_update_floor_and_walls();
    if (gMarioState->gCurrMinigame == 0) {
        cur_obj_move_standard(-78);
    }else{
        o->oHomeY = -5000.0f;
        cur_obj_move_standard(78);
    }

    f32 kept_new_y = o->oPosY; //keeping the new y position, a little scuffed

    f32 current_floor_height = find_floor(o->oPosX, o->oPosY, o->oPosZ, &ptr);

    if (current_floor_height < o->oHomeY-100.0f) {
        vec3f_copy(&o->oPosVec,&previous);//Prevent him from going off the ledge
        o->oPosY = kept_new_y;//this is a little cringe, but who cares
    }


    o->oGravity = -4.0f;

    if (o->oBehParams2ndByte == 2) {
        //param 2 means that they always persue mario
        vec3f_copy(&o->oHomeX,&gMarioState->pos[0]);
    }

    switch(o->oAction) {
        case 0:
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
            if (obj_check_if_facing_toward_angle(o->oMoveAngleYaw, o->oAngleToMario, 0x2000)&&
            (o->oDistanceToMario < 1000.0f)) {
                o->oAction = 4;
                cur_obj_init_animation_with_sound(5);//spin
                if (o->oBehParams2ndByte == 1) { //only ground attacks
                    o->oAction = 6;
                }
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
            if (cur_obj_lateral_dist_to_home() > 500.0f) {
                o->oAngleVelYaw = cur_obj_angle_to_home();
            }
            if (o->oTimer > 100) {//idle after a bit
                o->oAction = 1;
                o->oTimer = random_u16()%60;
                cur_obj_init_animation_with_sound(2);//walk
            }
            if (obj_check_if_facing_toward_angle(o->oMoveAngleYaw, o->oAngleToMario, 0x2000)&&
            (o->oDistanceToMario < 1000.0f)) {
                o->oAction = 4;
                cur_obj_init_animation_with_sound(5);//spin
                if (o->oBehParams2ndByte == 1) { //only ground attacks
                    o->oAction = 6;
                }
            }
            check_phantasm_attack();
        break;
        case 3://attacked
            o->oForwardVel *= .93f;
            o->oInteractStatus |= INT_STATUS_INTERACTED;

            if (o->oTimer == 30) {//die if killed
                if (o->oHealth < 1) {
                    gMarioState->EA_ACTIVE --;
                    gMarioState->EA_LEFT --;

                    obj_spawn_loot_yellow_coins(o, 5, 20.0f);
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
                o->oAction = 5+(random_u16()%2);
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
                    if (o->oMoveFlags & OBJ_MOVE_ON_GROUND) {
                        o->oSubAction = 1;
                        cur_obj_init_animation_with_sound(7);
                        o->oVelY = 0.0f;
                    }
                break;
                case 1:
                    if (o->oTimer > 30) {
                        o->oSubAction = 2;
                        o->oTimer = 0;
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
}

void bhv_paparazzi(void) {
    cur_obj_set_hitbox_radius_and_height(100.0f, 100.0f);
    cur_obj_set_hurtbox_radius_and_height(100.0f, 80.0f);

    cur_obj_become_tangible();
    o->oInteractType = INTERACT_BOUNCE_TOP;

    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
            set_mario_action(gMarioState, ACT_DOUBLE_JUMP, 0);
            mario_stop_riding_and_holding(gMarioState);
            run_event(EVENT_STATUE_ROTATE);
            spawn_mist_particles_variable(0, 0, 100.0f);
            obj_mark_for_deletion(o);
        }
    }

    o->oInteractStatus = 0;
    o->oIntangibleTimer = 0;
}

Vec3f spike_attack;
u8 spike_attacks_left = 4;
f32 spike_close = FALSE;
s16 spike_locked_angle = 0;
struct Object *showrunner_obj;
u8 tennis_bool = 0;//0 = attack mario, 1 = attack showrunner
f32 death_scale;

void showrunner_battle_function(void) {
    struct Object *obj_attack;
    struct Surface *ptr;

    showrunner_obj = o;

    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(-30);

    cur_obj_set_hitbox_radius_and_height(300.0f, 800.0f);
    cur_obj_set_hurtbox_radius_and_height(300.0f, 800.0f);
    o->oInteractType = INTERACT_DAMAGE;

    cur_obj_become_tangible();
    o->oDamageOrCoinValue = 0;

    switch(o->oAction) {
        case 0://init

            if (save_file_check_progression(PROG_DEFEAT_SHOWRUNNER) && (!save_file_check_progression(PROG_POSTGAME)) ) {
                //showrunner dead, unless in afterlife
                mark_obj_for_deletion(o);
            } else {
                if (save_file_get_flags() & SAVE_FLAG_HAPPY_SHOWRUNNER) {
                    run_event(EVENT_SHOWRUNNER_BATTLE_1);
                } else {
                    run_event(EVENT_SHOWRUNNER_BATTLE_2);
                }
            }
        break;
        case 1://init
            gMarioState->BossHealth = 3;
            gMarioState->BossHealthMax = 3;
            o->oAction = 2;
        break;
        case 2://back away
            if (o->oTimer == 1) {
                cur_obj_init_animation_with_sound(2);//back_away
                o->oForwardVel = -70.0f;
                o->oMoveAngleYaw = o->oAngleToMario;
                o->oFaceAngleYaw = o->oMoveAngleYaw;
            }
            if (o->oTimer > 1) {
                o->oForwardVel *= .94f;
                if (o->oForwardVel > -5.0f) {
                    spike_attacks_left = 4;
                    o->oAction = 3;//first attack are spikes
                    o->oForwardVel = 0.0f;
                }
            }
        break;
        case 3://spike attack
            o->oFaceAngleYaw = o->oAngleToMario;

            if (o->oTimer == 1) {//init
                spike_attack[0] = o->oPosX;
                spike_attack[1] = o->oPosY;
                spike_attack[2] = o->oPosZ;
                spike_attack[0] += sins(o->oAngleToMario) * 400.0f;
                spike_attack[2] += coss(o->oAngleToMario) * 400.0f;
                cur_obj_init_animation_with_sound(0);//reset
                cur_obj_init_animation_with_sound(1);//spike
                spike_close = FALSE;
            }
            if ((o->oTimer >= 20) && (o->oTimer < 90)) { //loop
                if (o->oTimer % 5 == 0) {
                    obj_attack = spawn_object(o, MODEL_SR_SPIKE, bhvSrSpike);
                    obj_attack->oPosX = spike_attack[0];
                    obj_attack->oPosY = spike_attack[1];
                    obj_attack->oPosZ = spike_attack[2];
                    obj_attack->oPosY = find_floor(obj_attack->oPosX, obj_attack->oPosY, obj_attack->oPosZ, &ptr);
                    obj_attack->oPosY -= 400.0f;
                    obj_attack->oHomeY = obj_attack->oPosY;

                    if (obj_attack->oPosY < 10.0f) {
                        mark_obj_for_deletion(obj_attack);
                    }
                }
            }
            if (o->oTimer > 110) {
                if (spike_attacks_left > 0) {
                    o->oTimer = 0;
                    spike_attacks_left--;
                } else {
                    if (gMarioState->BossHealth == 1) {
                        o->oAction = 16;
                    } else {
                        o->oAction = 10;
                        tennis_bool = 0;
                    }
                }
            }
        break;

        case 10://tennis time
            if (o->oTimer == 1) {
                cur_obj_init_animation_with_sound(0);//reset
                cur_obj_init_animation_with_sound(3);//wind_up

                //no cosmic phantasms allowed during tennis
                clear_costmic_phantasms();
            }
            o->oForwardVel = 10.0f;
            if (o->oTimer % 30 == 0) {
                o->oAngleVelYaw = random_u16();
            }
            if (cur_obj_lateral_dist_to_home() > 1800.0f) {
                o->oAngleVelYaw = cur_obj_angle_to_home();
            }
            o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw,o->oAngleVelYaw,4);
            if (o->oTimer > 60) {
                obj_attack = cur_obj_nearest_object_with_behavior(bhvTennis);
                if (obj_attack == NULL) {
                    cur_obj_init_animation_with_sound(0);//reset
                    cur_obj_init_animation_with_sound(4);//block
                    cur_obj_play_sound_2(SOUND_OBJ_MRI_SHOOT);
                    obj_attack = spawn_object(o,MODEL_SR_BALL,bhvTennis);
                    obj_attack->oPosY += 500.0f;
                }
            }
        break;
        case 11://stunned
            o->oInteractType = INTERACT_BOUNCE_TOP;
            o->oForwardVel = 0.0f;

            if (o->oTimer > 160) {
                //back to tennis if you miss
                o->oAction = 10;
            }

            if (o->oInteractStatus & INT_STATUS_INTERACTED) {
                if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
                    gMarioState->BossHealth--;
                    if (gMarioState->BossHealth > 0) {
                        o->oAction = 12;
                        cur_obj_init_animation_with_sound(6);//hurt
                    } else {
                        o->oAction = 13;
                        clear_costmic_phantasms();
                        cur_obj_init_animation_with_sound(7);//dead
                        if (save_file_get_flags() & SAVE_FLAG_HAPPY_SHOWRUNNER) {
                            run_event(EVENT_SHOWRUNNER_BATTLE_3);
                        } else {
                            run_event(EVENT_SHOWRUNNER_BATTLE_4);
                        }
                    }
                }
            }
        break;
        case 12://damaged

            if (o->oTimer > 60) {
                if (gMarioState->BossHealth == 2) {
                    o->oAction = 16;
                } else {
                    o->oAction = 17;
                }
            }
        break;
        case 13://battle end

        break;
        case 14://drop items
            spawn_default_star(o->oPosX,o->oPosY+400.0f,o->oPosZ);
            o->oAction = 15;
            death_scale = 1.0f;
        break;
        case 15://die
            cur_obj_set_hitbox_radius_and_height(0.0f, 0.0f);
            cur_obj_set_hurtbox_radius_and_height(0.0f, 0.0f);
            cur_obj_become_intangible();

            if (o->oTimer == 20) {
                cur_obj_play_sound_2(SOUND_OBJ_PIRANHA_PLANT_SHRINK);
            }
            if (o->oTimer > 20) {
                cur_obj_scale(death_scale);
                death_scale -= 0.01f;
                if (death_scale < 0.1f) {
                    o->oNumLootCoins = 50.0f;
                    obj_spawn_loot_yellow_coins(o, 50, 20.0f);
                    spawn_mist_particles_variable(0, 0, 100.0f);
                    obj_mark_for_deletion(o);
                }
            }
        break;

        case 16: //ballerina attack
            cur_obj_init_animation_with_sound(9);//ballerina attack
            o->oDamageOrCoinValue = 8;

            if (o->oTimer == 0) { //init
                o->oForwardVel = 0.0f;
                o->oAngleVelYaw = 0;
                o->oSubAction = 0;
            }

            if (o->oTimer > 30) {
                s16 old_angle = o->oFaceAngleYaw;
                o->oFaceAngleYaw += o->oAngleVelYaw;

                if ((old_angle < 0)&&(o->oFaceAngleYaw > 0)) {
                    cur_obj_play_sound_2(SOUND_OBJ_BOWSER_SPINNING);
                }

                f32 suck = ((f32)o->oAngleVelYaw/500.0f);
                if (o->oDistanceToMario < 300.0f) {
                    //TOO CLOSE! Blow mario out
                    gMarioState->pos[0] += sins(o->oAngleToMario)*suck;
                    gMarioState->pos[2] += coss(o->oAngleToMario)*suck;
                } else {
                    gMarioState->pos[0] -= sins(o->oAngleToMario)*suck;
                    gMarioState->pos[2] -= coss(o->oAngleToMario)*suck;
                }
                if (o->oAngleVelYaw > 0x2000) {
                    o->oAngleVelYaw = 0x2000;
                }
                if (o->oSubAction==0) {
                    if ((o->oTimer % 3 == 0)&&(o->oAngleVelYaw>0x1000)) {
                        obj_attack = spawn_object(o,MODEL_METAL_STAR,bhvCosmicProjectile);
                        obj_attack->oPosY = o->oPosY+(random_float()*500.0f);
                        obj_attack->oMoveAngleYaw = random_u16();
                        obj_attack->oMoveAnglePitch = 0;
                    }
                    if ((o->oTimer % 2 == 0)&&(o->oTimer>400)&&(gMarioState->BossHealth==2)) { //not to overwhelm the player in the final phase
                        obj_attack = spawn_object(o,MODEL_METAL_STAR,bhvCosmicProjectile);
                        obj_attack->oPosY = o->oPosY+(random_float()*500.0f);
                        obj_attack->oMoveAngleYaw = random_u16();
                        obj_attack->oMoveAnglePitch = 0;
                    }
                }


                switch(o->oSubAction) {
                    case 0:
                        o->oAngleVelYaw += 0x20;
                        o->oMoveAngleYaw = o->oAngleToMario;
                        if (o->oForwardVel < 20.0f) {
                            o->oForwardVel += 0.05f;
                        }
                        if (o->oTimer == 600) {
                            o->oSubAction = 1;
                            o->oTimer = 31;
                        }

                        break;
                    case 1:
                        if (o->oTimer > 90) {
                            o->oVelY = 80.0f;
                            cur_obj_play_sound_2(SOUND_OBJ_KING_BOBOMB_JUMP);
                            o->oSubAction = 2;
                        }
                        break;
                    case 2:
                        o->oMoveAngleYaw = cur_obj_angle_to_home();
                        o->oForwardVel = 50.0f;
                        if (cur_obj_lateral_dist_to_home() < 60.0f) {
                            o->oForwardVel = 0.0f;
                        }
                        
                        if (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND) {
                            //summon flurry of flames when landing
                            struct Object *flame;
                            for (u8 i=0;i<32;i++){
                                flame = spawn_object(o,MODEL_BLUE_FLAME,bhvThwompFlame);
                                flame->oPosY += 40.0f;
                                flame->oForwardVel = 30.0f;
                                flame->oMoveAngleYaw = i*0x800;
                            }

                            cur_obj_play_sound_2(SOUND_GENERAL_BOWSER_BOMB_EXPLOSION);
                            o->oSubAction = 3;
                            o->oTimer = 31;
                            }
                        break;
                    case 3:
                        o->oAngleVelYaw = (s16)((f32)o->oAngleVelYaw*.9f);
                        if (o->oTimer > 120) {
                            o->oAction = 10;
                            tennis_bool = 0;
                        }
                        break;
                }
            }
        break;

        case 17://let out cosmic phantasms
            o->oForwardVel = 0.0f;
            o->oMoveAngleYaw = cur_obj_angle_to_home();
            if (cur_obj_lateral_dist_to_home() > 60.0f) {
                o->oForwardVel = 50.0f;
                o->oTimer = 0;
            }

            if (o->oTimer == 30) {
                //spawn them
                cur_obj_init_animation_with_sound(10);
                for (u8 i=0;i<4;i++) {
                    obj_attack = spawn_object(o,MODEL_MARIO,bhvPhantasm);
                    obj_attack->oPosY += 200.0f;
                    obj_attack->oMoveAngleYaw = random_u16();
                    obj_attack->oForwardVel = 90.0f;
                    obj_attack->oVelY = 30.0f;
                    obj_attack->oBehParams2ndByte = 2;
                    obj_attack->oAction = 7;
                }
            }
            if (o->oTimer > 60) {
                spike_attacks_left = 2;
                o->oAction = 3;
            }
        break;
    }

    o->oInteractStatus = 0;
    o->oIntangibleTimer = 0;
}

static struct SpawnParticlesInfo sSpikeParticles = {
    /* behParam:        */ 0,
    /* count:           */ 2,
    /* model:           */ MODEL_PEBBLE,
    /* offsetY:         */ 0,
    /* forwardVelBase:  */ 10,
    /* forwardVelRange: */ 10,
    /* velYBase:        */ 20,
    /* velYRange:       */ 10,
    /* gravity:         */ -6,
    /* dragStrength:    */ 0,
    /* sizeBase:        */ 10.0f,
    /* sizeRange:       */ 10.0f,
};

void bhv_sr_spike(void) {
    switch(o->oAction) {
        case 0://init
            if (o->oTimer == 1) {
                if (spike_close == FALSE) {
                    if (lateral_dist_between_objects(o,gMarioObject) < 300.0f) {
                        spike_close = TRUE;
                        spike_locked_angle = o->oAngleToMario;
                    }
                }
                if (spike_close) {
                    spike_attack[0] += sins(spike_locked_angle) * 350.0f;
                    spike_attack[2] += coss(spike_locked_angle) * 350.0;
                } else {
                    spike_attack[0] += sins(o->oAngleToMario) * 350.0f;
                    spike_attack[2] += coss(o->oAngleToMario) * 350.0f;
                }
                o->oAction = 1;
                }
        break;
        case 1://rumble underneath
            o->oPosY+=400.0f;
            cur_obj_spawn_particles(&sSpikeParticles);
            o->oPosY-=400.0f;

            if (o->oTimer > 10) {
                o->oAction = 2;
                cur_obj_play_sound_2(SOUND_OBJ_KING_BOBOMB_JUMP);
            }
        break;
        case 2:
            o->oPosY += 20.0f;
            if (o->oPosY > o->oHomeY+400.0f) {
                o->oPosY = o->oHomeY+400.0f;
                o->oAction = 2;
                o->oAction = 3;
            }
        break;
        case 3:
            if ((showrunner_obj->oAction != 3)&&(showrunner_obj->oAction != 16)) {
                o->oPosY -= 20.0f;
                if (o->oPosY < o->oHomeY) {
                    obj_mark_for_deletion(o);
                }
            }
        break;
    }
}

u8 tennis_turns[] = {
    0,15,8,4,
};//table for how much vollying until showrunner gives in. also reverse order

#include "actors/group0.h"

void bhv_tennis(void) {
    o->oOpacity = 255;
    spawn_object(o,MODEL_SR_BALL,bhvTennis2);

    switch(o->oAction) {
        case 0:
            o->oAction = 1;
            o->oDamageOrCoinValue = 1;
            o->oForwardVel = 20.0f;
        break;
        case 1:
            cur_obj_set_hitbox_radius_and_height(100.0f, 100.0f);
            cur_obj_set_hurtbox_radius_and_height(80.0f, 80.0f);

            cur_obj_become_tangible();
            o->oInteractType = INTERACT_BOUNCE_TOP;


            if (tennis_bool == 0) {
                o->oMoveAngleYaw = obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 200);
                o->oMoveAnglePitch = obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_PITCH_INDEX, 200);

                if (o->oInteractStatus & INT_STATUS_INTERACTED) {
                    if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
                        tennis_bool = 1;
                    } else {
                        showrunner_obj->oTimer = 0;
                        obj_mark_for_deletion(o);
                    }
                }
            } else {
                o->oMoveAngleYaw = obj_turn_toward_object(o, showrunner_obj, O_MOVE_ANGLE_YAW_INDEX, 200);
                showrunner_obj->oFaceAngleYaw = approach_s16_asymptotic(showrunner_obj->oFaceAngleYaw,o->oMoveAngleYaw+0x8000,4);
                showrunner_obj->oPosY += 500.0f;
                o->oMoveAnglePitch = obj_turn_toward_object(o, showrunner_obj, O_MOVE_ANGLE_PITCH_INDEX, 200);
                showrunner_obj->oPosY -= 500.0f;

                if (lateral_dist_between_objects(o,showrunner_obj) < 400.0f) {
                    tennis_bool = 0;
                    o->oForwardVel += 10.0f;
                    o->oDamageOrCoinValue ++;
                    o->oInteractStatus = 0;
                    o->oIntangibleTimer = 0;
                    cur_obj_play_sound_2(SOUND_OBJ_MRI_SHOOT);
                    obj_init_animation_with_sound(showrunner_obj,showrunner_anims,0);//reset
                    obj_init_animation_with_sound(showrunner_obj,showrunner_anims,4);//block

                    if (o->oDamageOrCoinValue == tennis_turns[gMarioState->BossHealth]) {
                        showrunner_obj->oAction = 11;
                        obj_init_animation_with_sound(showrunner_obj,showrunner_anims,5);//shocked
                        obj_mark_for_deletion(o);
                    }
                }
            }
            
            o->oPosX += sins(o->oMoveAngleYaw) * o->oForwardVel;
            o->oPosZ += coss(o->oMoveAngleYaw) * o->oForwardVel;
            o->oPosY += sins(-o->oMoveAnglePitch) * o->oForwardVel;
        break;
    }
}

void bhv_tennis2(void) {
    switch(o->oAction) {
        case 0:
            o->oOpacity = 255;
            o->oAction = 1;
        break;
        case 1:
            if (o->oOpacity > 12) {
                o->oOpacity -= 10;
            } else {
                mark_obj_for_deletion(o);
            }
        break;
    }
}