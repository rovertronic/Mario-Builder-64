// scuttlebug.inc.c

struct ObjectHitbox sSlobHitbox = {
    /* interactType: */ INTERACT_BOUNCE_TOP,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 2,
    /* health: */ 3,
    /* numLootCoins: */ 3,
    /* radius: */ 130,
    /* height: */ 70,
    /* hurtboxRadius: */ 90,
    /* hurtboxHeight: */ 60,
};

struct ObjectHitbox sRexBossHitbox = {
    /* interactType: */ INTERACT_BOUNCE_TOP,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 3,
    /* health: */ 25,
    /* numLootCoins: */ 20,
    /* radius: */ 130,
    /* height: */ 70,
    /* hurtboxRadius: */ 90,
    /* hurtboxHeight: */ 60,
};

struct ObjectHitbox sScuttlebugHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 3,
    /* numLootCoins:      */ 4,
    /* radius:            */ 130,
    /* height:            */ 70,
    /* hurtboxRadius:     */ 90,
    /* hurtboxHeight:     */ 60,
};

struct ObjectHitbox sScuttlebugSpawnedHitbox = {
    /* interactType: */ INTERACT_BOUNCE_TOP,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 1,
    /* health: */ 2,
    /* numLootCoins: */ 0,
    /* radius: */ 130,
    /* height: */ 70,
    /* hurtboxRadius: */ 90,
    /* hurtboxHeight: */ 60,
};

struct ObjectHitbox sHammerBroHitbox = {
    /* interactType: */ INTERACT_BOUNCE_TOP,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 2,
    /* health: */ 1,
    /* numLootCoins: */ 6,
    /* radius: */ 80,
    /* height: */ 140,
    /* hurtboxRadius: */ 90,
    /* hurtboxHeight: */ 130,
};

struct ObjectHitbox sHammerHitbox = {
    /* interactType: */ INTERACT_DAMAGE,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 2,
    /* health: */ 1,
    /* numLootCoins: */ 7,
    /* radius: */ 40,
    /* height: */ 40,
    /* hurtboxRadius: */ 40,
    /* hurtboxHeight: */ 40,
};

struct ObjectHitbox sCactusHitbox = {
    /* interactType: */ INTERACT_DAMAGE,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 3,
    /* health: */ 1,
    /* numLootCoins: */ 7,
    /* radius: */ 20,
    /* height: */ 20,
    /* hurtboxRadius: */ 20,
    /* hurtboxHeight: */ 20,
};

struct ObjectHitbox sMaskHitbox = {
    /* interactType: */ INTERACT_MR_BLIZZARD,
    /* downOffset: */ 32,
    /* damageOrCoinValue: */ 4,
    /* health: */ 1,
    /* numLootCoins: */ 7,
    /* radius: */ 75,
    /* height: */ 75,
    /* hurtboxRadius: */ 75,
    /* hurtboxHeight: */ 75,
};

struct ObjectHitbox sTrapHitbox = {
    /* interactType: */ INTERACT_DAMAGE,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 6,
    /* health: */ 1,
    /* numLootCoins: */ 7,
    /* radius: */ 100,
    /* height: */ 40,
    /* hurtboxRadius: */ 150,
    /* hurtboxHeight: */ 60,
};

struct ObjectHitbox sRetroPlantHitbox = {
    /* interactType: */ INTERACT_DAMAGE,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 3,
    /* health: */ 1,
    /* numLootCoins: */ 7,
    /* radius: */ 75,
    /* height: */ 150,
    /* hurtboxRadius: */ 75,
    /* hurtboxHeight: */ 300,
};

struct ObjectHitbox sBillHitbox = {
    /* interactType: */ INTERACT_BOUNCE_TOP,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 3,
    /* health: */ 1,
    /* numLootCoins: */ 0,
    /* radius: */ 70,
    /* height: */ 85,
    /* hurtboxRadius: */ 75,
    /* hurtboxHeight: */ 35,
};

struct ObjectHitbox sLadybugHitbox = {
    /* interactType: */ INTERACT_BOUNCE_TOP,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 3,
    /* health: */ 1,
    /* numLootCoins: */ 5,
    /* radius: */ 70,
    /* height: */ 95,
    /* hurtboxRadius: */ 75,
    /* hurtboxHeight: */ 45,
};

struct ObjectHitbox sRBowserHitbox = {
    /* interactType: */ INTERACT_DAMAGE,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 3,
    /* health: */ 1,
    /* numLootCoins: */ 0,
    /* radius: */ 130,
    /* height: */ 130,
    /* hurtboxRadius: */ 130,
    /* hurtboxHeight: */ 130,
};

s32 update_angle_from_move_flags(s32 *angle) {
    if (o->oMoveFlags & OBJ_MOVE_HIT_WALL) {
        *angle = o->oWallAngle;
        return 1;
    } else if (o->oMoveFlags & OBJ_MOVE_HIT_EDGE) {
        *angle = o->oMoveAngleYaw + 0x8000;
        return -1;
    }
    return 0;
}

void bhv_scuttlebug_loop(void) {
    Vec3f crabDisplacement, crabNewDisplacement;
    struct ObjectHitbox *hitbox_to_use;
    Vec3f original_pos;
    vec3f_copy(original_pos,&o->oPosX);

    hitbox_to_use = &sScuttlebugHitbox;
    if (gCurrAreaIndex == 4) {
        hitbox_to_use = &sScuttlebugSpawnedHitbox;
    }

    if ((gMarioState->gCurrMinigame == 1)||(gCurrentArea->index == 4)) {
        o->oHomeX = gMarioState->pos[0];
        o->oHomeY = gMarioState->pos[1];
        o->oHomeZ = gMarioState->pos[2];

        if (o->oDistanceToMario > 800.0f) {
            o->oFaceAngleYaw = o->oAngleToMario;
            o->oMoveAngleYaw = o->oAngleToMario;
            o->oForwardVel = 15.0f;
            o->oDrawingDistance = 9000.0f;
            }
        }

    cur_obj_update_floor_and_walls();

    if (o->oSubAction != 0
        && cur_obj_set_hitbox_and_die_if_attacked(hitbox_to_use, SOUND_OBJ_DYING_ENEMY1, o->oScuttlebugHasNoLootCoins)) {
        o->oSubAction = 3;
    }

    if (o->oSubAction != 1) {
        o->oScuttlebugIsAtttacking = 0;
    }

    //fuck mario's head
    if ((o->oDistanceToMario < 200.0f)&&(o->oPosY-30.0f>gMarioState->pos[1])) {
        o->oSubAction = 6;
    }

    vec3f_set(o->header.gfx.scale,1.0f,1.0f,1.0f);
    switch (o->oSubAction) {
        case 6:
            mtxf_copy(o->transform,gMarioState->HeadMatrix);
            o->header.gfx.throwMatrix = &o->transform;

            vec3f_set(crabDisplacement, 150.f, -40.f, 10.0f); // local displacement of the crab
            linear_mtxf_mul_vec3f(o->transform, crabNewDisplacement, crabDisplacement); // rotate it with mario's head
            vec3f_add(o->transform[3], crabNewDisplacement); // add position
            vec3f_copy(&o->oPosX,o->transform[3]); // copy crab position to object
            vec3f_set(o->header.gfx.scale,3.5f,3.5f,3.5f);

            o->oVelY = 0.0f;
            //o->oMoveAngleYaw = gMarioState->faceAngle[1];
            if (o->oTimer > 20) {
                gMarioState->hurtCounter ++;
                if (gMarioState->CostumeID != 7) {
                    gMarioState->hurtCounter ++;
                }
                o->oTimer = 0;
            }
        break;
        case 0:
            if (o->oMoveFlags & OBJ_MOVE_LANDED) {
                cur_obj_play_sound_2(SOUND_OBJ_GOOMBA_ALERT);
            }
            if (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND) {
                vec3f_copy(&o->oHomeVec, &o->oPosVec);
                o->oSubAction++;
            }
            break;

        case 1:
            o->oForwardVel = 5.0f;
            if (cur_obj_lateral_dist_from_mario_to_home() > 1000.0f) {
                o->oAngleToMario = cur_obj_angle_to_home();
            } else {
                if (o->oScuttlebugIsAtttacking == 0) {
                    o->oScuttlebugTimer = 0;
                    o->oAngleToMario = obj_angle_to_object(o, gMarioObject);
                    if (abs_angle_diff(o->oAngleToMario, o->oMoveAngleYaw) < 0x800) {
                        o->oScuttlebugIsAtttacking = 1;
                        o->oVelY = 50.0f;
                        cur_obj_play_sound_2(SOUND_OBJ2_SCUTTLEBUG_ALERT);
                    }
                } else if (o->oScuttlebugIsAtttacking == 1) {
                    o->oForwardVel = 30.0f;
                    o->oScuttlebugTimer++;
                    if (o->oScuttlebugTimer > 50) {
                        o->oScuttlebugIsAtttacking = FALSE;
                    }
                }
            }
            if (update_angle_from_move_flags(&o->oAngleToMario)) {
                o->oSubAction = 2;
            }
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x200);
            break;

        case 2:
            o->oForwardVel = 5.0f;
            if ((s16) o->oMoveAngleYaw == (s16) o->oAngleToMario) {
                o->oSubAction = 1;
            }
            //if (o->oPosY - o->oHomeY < -200.0f)
                //gMarioState->EA_ACTIVE --;
                //gMarioState->EA_LEFT --;
                //obj_mark_for_deletion(o);
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x400);
            break;

        case 3:
            o->oFlags &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
            o->oForwardVel = -10.0f;
            o->oVelY = 30.0f;
            cur_obj_play_sound_2(SOUND_OBJ2_SCUTTLEBUG_ALERT);
            o->oSubAction++;
            break;

        case 4:
            o->oForwardVel = -10.0f;
            if (o->oMoveFlags & OBJ_MOVE_LANDED) {
                o->oSubAction++;
                o->oVelY = 0.0f;
                o->oScuttlebugTimer = 0;
                o->oFlags |= OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
                o->oInteractStatus = INT_STATUS_NONE;
            }
            break;

        case 5:
            o->oForwardVel = 2.0f;
            o->oScuttlebugTimer++;
            if (o->oScuttlebugTimer > 30) {
                o->oSubAction = 0;
            }
            break;
    }

    f32 animSpeed = o->oForwardVel < 10.0f ? 1.0f : 3.0f;

    cur_obj_init_animation_with_accel_and_sound(0, animSpeed);

    if (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND) {
        set_obj_anim_with_accel_and_sound(1, 23, SOUND_OBJ2_SCUTTLEBUG_WALK);
    }

    if (o->parentObj != o) {
        if (obj_is_hidden(o)) {
                //gMarioState->EA_ACTIVE --;
                //gMarioState->EA_LEFT --;
            obj_mark_for_deletion(o);
        }
        if (o->activeFlags == ACTIVE_FLAG_DEACTIVATED) {
            o->parentObj->oScuttlebugSpawnerIsDeactivated = 1;
        }
    }

    cur_obj_move_standard(-50);

    if (revent_stop_enemies) {
        vec3f_copy(&o->oPosX,&original_pos);
    }
}

void bhv_scuttlebug_spawn_loop(void) {
    if (o->oAction == 0) {
        if (o->oTimer > 30 && 500.0f < o->oDistanceToMario && o->oDistanceToMario < 1500.0f) {
            struct Object *scuttlebug;
            cur_obj_play_sound_2(SOUND_OBJ2_SCUTTLEBUG_ALERT);
            scuttlebug = spawn_object(o, MODEL_SCUTTLEBUG, bhvScuttlebug);
            scuttlebug->oScuttlebugHasNoLootCoins = o->oScuttlebugSpawnerSpawnWithNoLootCoins;
            scuttlebug->oForwardVel = 30.0f;
            scuttlebug->oVelY = 80.0f;
            o->oAction++;
            o->oScuttlebugHasNoLootCoins = 1;
        }
    } else if (o->oScuttlebugSpawnerIsDeactivated != 0) {
        o->oScuttlebugSpawnerIsDeactivated = 0;
        o->oAction = 0;
    }
}

u16 RandomMinMaxU16(u16 min, u16 max) {
    u16 num = random_u16();
    return (num % ((max + 1) - min)) + min;
}

void throw_hammer(void) {
    struct Object *hammer;

    if (gMarioState->pos[1] > o->oPosY - 200.0f) { //do not throw hammers if mario is far below
        if (o->oAnimState == 0) {//hammer
            hammer = spawn_object(o, 0xEC, bhvHammer);
            hammer->oMoveAngleYaw = o->oFaceAngleYaw;
            hammer->oVelY = RandomMinMaxU16(30,50);
            hammer->oForwardVel = RandomMinMaxU16(20,50);
            hammer->oPosY += 20.0f;
            hammer->oTimer =0;
            hammer->oFlags |= OBJ_FLAG_ACTIVE_FROM_AFAR;
            cur_obj_play_sound_2(SOUND_OBJ_KOOPA_DAMAGE);
        } else {
            hammer = spawn_object(o, MODEL_RED_FLAME, bhvFireBroBall);
            hammer->oMoveAngleYaw = o->oFaceAngleYaw;
            hammer->oVelY = 20.0f;
            hammer->oForwardVel = 30.0f;
            hammer->oPosY += 20.0f;
            hammer->oFlags |= OBJ_FLAG_ACTIVE_FROM_AFAR;
            cur_obj_play_sound_2(SOUND_OBJ_KOOPA_DAMAGE);
            cur_obj_play_sound_2(SOUND_OBJ_FLAME_BLOWN);
        }
    }
}

//SOUND_OBJ_KOOPA_DAMAGE

void bhv_hammer_bro_loop(void) {
    struct Object *hammer;

    if (o->oBehParams2ndByte == 1) {
        o->oAnimState = 1;
    }

    if (gMarioState->gCurrMinigame == 1) {
        o->oHomeX = gMarioState->pos[0];
        o->oHomeY = gMarioState->pos[1];
        o->oHomeZ = gMarioState->pos[2];

        if (o->oDistanceToMario > 800.0f) {
            o->oFaceAngleYaw = o->oAngleToMario;
            o->oMoveAngleYaw = o->oAngleToMario;
            o->oForwardVel = 15.0f;
            o->oDrawingDistance = 9000.0f;
            }
        }

    cur_obj_set_hitbox_and_die_if_attacked(&sHammerBroHitbox, SOUND_OBJ_KOOPA_DAMAGE,0);
    o->oFaceAngleYaw = o->oAngleToMario;

    //ONLY DO IF ACTIVE
    if ((o->oDistanceToMario < 3000.0f)||(o->oFlags & OBJ_FLAG_ACTIVE_FROM_AFAR)) {
        cur_obj_enable_rendering();
        //INIT
        if (o->oAction == 0) {
            obj_set_hitbox(o, &sHammerBroHitbox);
            o->oAction = 1;
            o->oHomeX = o->oPosX;
            o->oHomeY = o->oPosY;
            o->oHomeZ = o->oPosZ;
            o->oScuttlebugHasNoLootCoins = 0;
        }

        //LOOP
        if (o->oAction == 1) {

            if (o->oTimer > 40) {
                cur_obj_init_animation_with_sound(2);
                o->oAction = 4;
                if (o->oBehParams2ndByte == 1) {
                    o->oAction = 2;
                }
                throw_hammer();
                o->oExtraVariable1 = RandomMinMaxU16(1,3);
                o->oTimer = 0;
                }
            }



        //Hold hammer in hand
        if (o->oAction == 4) {
            o->header.gfx.animInfo.animFrame = 0;

            if (o->oTimer > 15) {
                o->oAction = 2;
                o->oTimer = 0;
            }
        }

        if (o->oAction == 2) {

            if (o->oTimer > 25) {
                o->oTimer = 0;
                o->oExtraVariable1 --;

                if (o->oExtraVariable1 < 1) {
                        o->oAction = 3;
                        o->oVelY = 60;
                        o->oMoveAngleYaw += 0x8000;
                        cur_obj_init_animation_with_sound(3);
                    } else {
                        o->oAction = 4;
                        if (o->oBehParams2ndByte == 1) {
                            o->oAction = 2;
                        }
                        throw_hammer();
                        cur_obj_init_animation_with_sound(0);
                        cur_obj_init_animation_with_sound(2);
                    }
                }
            }

        if (o->oAction == 3) {

            o->oForwardVel = 35.0f;

            if (o->oTimer > 5) {
                if (o->oMoveFlags & 3) {
                    cur_obj_init_animation_with_sound(0);
                    o->oAction = 1;
                    o->oTimer = RandomMinMaxU16(0,30);
                    o->oForwardVel = 0.0f;

                    if (o->oScuttlebugHasNoLootCoins > 0) {
                        if (gMarioState->gCurrMinigame == 0) {
                            o->oPosX = o->oHomeX;
                            o->oPosY = o->oHomeY;
                            o->oPosZ = o->oHomeZ;
                            }
                        o->oScuttlebugHasNoLootCoins = 0;
                        }
                        else
                        {
                        o->oScuttlebugHasNoLootCoins ++;
                        }
                    }
                }
            }

        cur_obj_update_floor_and_walls();
        cur_obj_move_standard(-50);
        }
        else
        {
        cur_obj_disable_rendering();
        o->oTimer --;
        }
    }

void bhv_slob_loop(void) {
    //o->oDontInertia = hit ground yet
    switch(o->oAction) {
        case 0:
        o->oForwardVel = 0;
        o->oParentRelativePosY = 0;
        o->oDontInertia = FALSE;
        if (o->oDistanceToMario < 1200.0f) {
            o->oAction = 1;
            }
        break;
        case 1:
        if (!o->oDontInertia) {
            o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw,o->oAngleToMario,4);
            }

        if ((o->oMoveFlags & 1)&&(o->oDontInertia)) {
            o->oForwardVel = 0;
            o->oParentRelativePosY = -0.5f;
            cur_obj_init_animation_with_sound(0);
            cur_obj_play_sound_2(SOUND_OBJ_WALKING_WATER);
            o->oDontInertia = FALSE;
            }

        if (o->oTimer%40==0) {
            cur_obj_play_sound_2(SOUND_OBJ_WALKING_WATER);
            o->oForwardVel = 20.0f;
            o->oVelY = 35.0f;
            o->oParentRelativePosY = 2.0f;
            cur_obj_init_animation_with_sound(1);
            o->oDontInertia = TRUE;
            }
        

        if (o->oDistanceToMario > 1300.0f) {
            cur_obj_init_animation_with_sound(0);
            o->oAction = 0;
            }
        break;
        }

    o->oParentRelativePosY /= 1.25;
    vec3f_set(o->header.gfx.scale,1.0f,1.0f+o->oParentRelativePosY,1.0f);

    cur_obj_set_hitbox_and_die_if_attacked(&sSlobHitbox, SOUND_GENERAL_SPLATTERING,0);
    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(-50);
    }

void bhv_hammer_loop(void) {

    //INIT
    if (o->oAction == 0) {
        o->oPosY += 210.0f;
        o->oAction = 1;
        }

    if (o->oTimer < 20) {
        o->oFaceAnglePitch = -0x2000;
        return;
    }

    obj_set_hitbox(o, &sHammerHitbox);
    o->oFaceAnglePitch += 0x2000;

    if ((o->oMoveFlags & 3)||(o->oTimer > 300)||(o->oMoveFlags & 0x200)) {
        play_sound(SOUND_ACTION_METAL_STEP, gGlobalSoundSource);
        spawn_mist_particles();
        obj_mark_for_deletion(o);
        }

    cur_obj_update_floor_and_walls();
    o->activeFlags &= ~ACTIVE_FLAG_FAR_AWAY;
    cur_obj_move_standard(50);
    }


void bhv_firebroball_loop(void) {

    o->oForwardVel = 35.0f;

    if ((o->oTimer > 300)||(o->oMoveFlags & 0x200)) {
        obj_mark_for_deletion(o);
        }

    if (o->oMoveFlags & 3) {
        cur_obj_play_sound_2(SOUND_OBJ_SNOW_SAND1);
        o->oVelY = 40.0f;
        }

    cur_obj_update_floor_and_walls();
    o->activeFlags &= ~ACTIVE_FLAG_FAR_AWAY;
    cur_obj_move_standard(50);
}

void bhv_cactusball_loop(void) {

    //INIT
    if (o->oAction == 0) {
        obj_set_hitbox(o, &sCactusHitbox);
        o->oAction = 1;
        }

    if (o->oTimer > 300) {
        //play_sound(SOUND_ACTION_METAL_STEP, gGlobalSoundSource);
        spawn_mist_particles();
        obj_mark_for_deletion(o);
        }

    cur_obj_update_floor_and_walls();
    o->activeFlags &= ~ACTIVE_FLAG_FAR_AWAY;
    cur_obj_move_standard(72);
    }

void bhv_rex_boss_loop(void) {

    o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw,o->oAngleToMario,4);

    o->oAnimState = 2;
    cur_obj_scale(3.0f);

    if (o->oDmgFade < 1) {
        cur_obj_set_hitbox_and_die_if_attacked(&sRexBossHitbox, SOUND_GENERAL_SPLATTERING,0);
    }

    gMarioState->BossHealth = o->oHealth;

    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(-50);
}

void bhv_trap(void) {
    struct Object *cheese;
        //INIT
    if (o->oAction == 0) {
        obj_set_hitbox(o, &sTrapHitbox);
        o->oAction = 1;
        cheese = spawn_object(o, MODEL_CHEESE, bhvCheese);
        cheese->oPosY += 200.0f;
    }

    if (o->oAction == 1) {
        if (o->oInteractStatus & INT_STATUS_ATTACKED_MARIO) {
            cur_obj_init_animation_with_sound(0);
            o->oAction = 2;
        }
    }
}

void bhv_spork_loop(void) {
    switch(o->oAction) {
        case 0: //INIT
            o->oAction = 3;
            o->oHealth = 3;
            o->oNumLootCoins = 6;
            o->oFlags |= OBJ_FLAG_HITBOX_WAS_SET;
            cur_obj_become_tangible();
        break;

        case 1://ATTACKING
            o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw,o->oAngleToMario,4);

            if (o->oTimer == 40) {
                cur_obj_play_sound_2(SOUND_OBJ_BOWSER_SPINNING);
                cur_obj_init_animation_with_sound(1);
            }

            if (o->oTimer > 50) {
                o->oAction = 2;//VULNERABLE
                }
            
            if (o->oDistanceToMario > 900.0f) {
                o->oAction = 3;//IDLE
                cur_obj_init_animation_with_sound(0);
                }

            o->oInteractType = INTERACT_DAMAGE;
            o->hurtboxRadius = 80;
            o->hurtboxHeight = 400;
            o->hitboxRadius = 80;
            o->hitboxHeight = 400;
            o->oDamageOrCoinValue = 2;
        break;

        case 2://VULNERABLE
            if (o->oTimer == 2) {
                cur_obj_play_sound_2(SOUND_OBJ_BOWSER_SPINNING);
            }
            o->oMoveAngleYaw = o->oAngleToMario;
            o->oInteractType = INTERACT_BOUNCE_TOP;
            o->hurtboxRadius = 450;
            o->hurtboxHeight = 90;
            o->hitboxRadius = 400;
            o->hitboxHeight = 100;
            o->oDamageOrCoinValue = 4;
            if (o->oTimer > 20) {
                o->oAction = 1;//ATTACKING
                cur_obj_init_animation_with_sound(0);
                }
            if (o->oDistanceToMario > 900.0f) {
                o->oAction = 3;//IDLE
                cur_obj_init_animation_with_sound(0);
                }
        break;

        case 3: //IDLE
            o->oForwardVel = 0;
            o->oParentRelativePosY = 0;
            o->oDontInertia = FALSE;
            //Attack if mario is nearby
            if (o->oDistanceToMario < 800.0f) {
                o->oAction = 1;//ATTACK
                o->oTimer = 20;
                }
        break;
        }

    cur_obj_set_hitbox_and_die_if_attacked(NULL, SOUND_GENERAL_SPLATTERING,0);
    }

void bhv_retroplant(void) {
    switch(o->oAction) {
        case 0:
            //obj_set_hitbox(o, &sHammerHitbox);
            if (o->oBehParams2ndByte == 1) {
                o->oAction = 1;
            } else {
                o->oAction = 3;
                o->oPosY -= 300.0f;
            }
        break;
        case 1:
            //above ground, waiting
            cur_obj_set_hitbox_and_die_if_attacked(&sRetroPlantHitbox, SOUND_GENERAL_SPLATTERING,0);
            if (o->oTimer > 70) {
                o->oAction =2;
            }
        break;
        case 2:
            //go down
            o->oPosY-=20.0f;
            if (o->oPosY < o->oHomeY-300.0f) {
                o->oPosY = o->oHomeY-300.0f;
                o->oAction = 3;
            }
        break;
        case 3:
            //under ground, waiting
            if ((o->oTimer > 60)&& (!((gMarioState->pos[0] > o->oPosX-150.0f)&&((gMarioState->pos[0] < o->oPosX+150.0f))))) {//dont go up if mario is above
                o->oAction =4;
            }
        break;
        case 4:
            //go up
            o->oPosY+=20.0f;
            cur_obj_set_hitbox_and_die_if_attacked(&sRetroPlantHitbox, SOUND_GENERAL_SPLATTERING,0);
            if (o->oPosY > o->oHomeY) {
                o->oPosY = o->oHomeY;
                o->oAction = 1;
            }
    }
}

void bhv_retrobill(void) {
    switch(o->oAction) {
        case 0:
            o->oPosY += 30.0f;
            o->oGraphYOffset = -30.0f;
            if (o->oBehParams2ndByte == 0) {
                o->oMoveAngleYaw = -0x4000;
                o->oFaceAngleYaw = 0;
                }
                else
                {
                o->oMoveAngleYaw = 0x4000;
                o->oFaceAngleYaw = 0x8000;
                }
            o->oAction = 1;
        break;
        case 1:
            cur_obj_set_hitbox_and_die_if_attacked(&sBillHitbox, SOUND_GENERAL_SPLATTERING,0);
            o->oForwardVel = 16.0f;
            o->activeFlags &= ~ACTIVE_FLAG_FAR_AWAY;
            cur_obj_move_standard(-5);

            if (o->oTimer > 60) {
                cur_obj_update_floor_and_walls();
                if ((o->oMoveFlags & OBJ_MOVE_HIT_WALL)||(o->oMoveFlags & OBJ_MOVE_HIT_EDGE)) {
                    spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
                    obj_mark_for_deletion(o);
                }
            }
        break;
    }
}

void bhv_mask2(void) {
    f32 dist;
    o->oFaceAngleYaw = 0;
    o->oFaceAnglePitch = 0;
    o->oFaceAngleRoll = 0;
    if (gMarioState->action == ACT_WARP_PIPE) {
        return;
    }


    switch(o->oAction) {
        case 0:
            dist = pythag(gMarioState->pos[0] - o->oPosX, gMarioState->pos[1] - o->oPosY);
            if ((dist < 120.0f)||(gMarioState->MaskChase)) {
                gMarioState->MaskChase = TRUE;
                o->oPosY += 2000.0f;
                o->oPosX += 500.0f;
                play_puzzle_jingle();
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MASK2];
                o->oAction = 1;
            }
        break;
        case 1:
            o->oMoveAngleRoll = atan2s(o->oHomeY - o->oPosY,o->oHomeX - o->oPosX);

            dist = pythag(o->oHomeX - o->oPosX, o->oHomeY - o->oHomeY);

            if (dist < 50.0f) {
                o->oHomeX = gMarioState->pos[0];
                o->oHomeY = gMarioState->pos[1];
            }

            o->oVelX += sins(o->oMoveAngleRoll)*((dist*.025f)+0.05f);
            o->oVelY += coss(o->oMoveAngleRoll)*((dist*.025f)+0.05f);
            if (dist < 2500.0f) {
                o->oVelX = floatclamp(o->oVelX, -22.0f,25.0f);
                o->oVelY = floatclamp(o->oVelY, -22.0f,25.0f);
            } else {
                o->oVelX = floatclamp(o->oVelX, -70.0f,70.0f);
                o->oVelY = floatclamp(o->oVelY, -70.0f,70.0f);         
            }

            o->oPosX += o->oVelX;
            o->oPosY += o->oVelY;

            //cur_obj_set_hitbox_and_die_if_attacked(&sMaskHitbox, SOUND_GENERAL_SPLATTERING,0);
            o->oInteractStatus = 0;
            obj_set_hitbox(o,&sMaskHitbox);
        break;
    }
}

void bhv_ladybug(void) {
    cur_obj_set_hitbox_and_die_if_attacked(&sLadybugHitbox, SOUND_GENERAL_SPLATTERING,0);
    switch(o->oAction) {
        case 0:
            o->oAction = 1;
            o->oPosY += o->oBehParams2ndByte*150.0f;
        break;
        case 1:
            o->oPosY -= 20.0f;
            if (o->oPosY < o->oHomeY-1050.0f) {
                o->oAction = 2;
                o->oFaceAngleRoll = 0x7FFF;
            }
        break;
        case 2:
            o->oPosY += 10.0f;
            if (o->oPosY > o->oHomeY) {
                o->oAction = 1;
                o->oFaceAngleRoll = 0;
            }
        break;
    }
}

#define floored (!(o->oMoveFlags & OBJ_MOVE_IN_AIR))

u8 pounded;

void bhv_rbowser(void) {
    struct Object *brick;
    struct Surface *f;
    u8 i;
    f32 y;
    u8 didbreak;

    o->oPosZ = 0.0f; //prevent falling off the stage

    cur_obj_set_hitbox_and_die_if_attacked(&sRBowserHitbox, SOUND_GENERAL_SPLATTERING,0);
    if (o->oAction != 6) {
        cur_obj_move_standard(-70);
        cur_obj_update_floor_and_walls();
    }

    o->oFaceAngleYaw = 0;
    if (gMarioState->pos[0] > o->oPosX) {
        o->oFaceAngleYaw = 0x7FFF;
    }

    switch(o->oAction) {
        case 0:
            o->oMoveAngleYaw = 0x4000;
            if (cur_obj_update_dialog_with_cutscene(2, 1, CUTSCENE_DIALOG, DIALOG_057)) {
                o->oAction = 1;
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_BOSS), 0);
            }
        break;
        case 1://jump around
            o->oAnimState = 0;
            if (o->oMoveFlags & OBJ_MOVE_IN_AIR) {
                o->oAnimState = 1;
            } else {
                o->oForwardVel = 0.0f;
            }

            if ((floored)&&(!pounded)) {
                pounded = TRUE;
                cur_obj_play_sound_2(SOUND_OBJ_BOWSER_WALK);
            }
            if (!floored) {
                pounded = FALSE;
            }

            if ((o->oTimer%20==0)&&floored) {
                o->oVelY = 15.0f + (random_float()*50.0f);
                o->oForwardVel = (random_float()*70.0f) - 35.0f;
            }

            if (floored&&(o->oTimer > 150)) {
                o->oAnimState = 1;
                o->oAction = 5;
            }

            y = find_floor(o->oPosX, o->oPosY, o->oPosZ, &f);
            if (f != NULL) {
                if ((y + 1.f > o->oPosY) && (SURFACE_IS_BURNING(f->type))) {
                    stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
                    o->oAction = 6;
                    o->oAnimState = 2;
                    cur_obj_play_sound_2(SOUND_GENERAL2_BOWSER_EXPLODE);
                }
            }
        break;
        case 2://jump
            o->oVelY = 35.0f;
            o->oVelX = 0.0f;

            if (o->oPosX > o->oHomeX+30.0f) {
                o->oPosX -= 30.0f;
            }
            if (o->oPosX < o->oHomeX-30.0f) {
                o->oPosX += 30.0f;
            }

            if (o->oPosY > gMarioState->pos[1]+1000.0f) {
                o->oAction = 3;
            }
        break;
        case 3://wait midair
            o->oVelY = 0.0f;
            if (o->oTimer > 20) {
                o->oAction = 4;
            }
        break;
        case 4://fall
            o->oVelY = -50.0f;
            didbreak = FALSE;
            if (floored) {
                for (i=0;i<2;i++) {
                    brick = cur_obj_nearest_object_with_behavior(bhvSmashbrick);
                    if (brick) {
                        if (pythag(brick->oPosX - o->oPosX,brick->oPosY - o->oPosY) < 180.0f) {
                            didbreak = TRUE;
                            obj_mark_for_deletion(brick);
                        }
                    }
                }

                cur_obj_play_sound_2(SOUND_OBJ_BOWSER_WALK);
                if (didbreak) {
                    spawn_mist_particles_variable(0, 0, 200.0f);
                    spawn_triangle_break_particles(20, 138, 3.0f, 4);
                    cur_obj_shake_screen(SHAKE_POS_LARGE);
                    cur_obj_play_sound_2(SOUND_GENERAL_BOWSER_PLATFORM_FALL);
                }

                o->oAction = 1;
            }
        break;
        case 5://anticipate
            if (o->oTimer > 30) {
                o->oAction = 2;
                o->oAnimState = 3;
                o->oHomeX = gMarioState->pos[0];
                cur_obj_play_sound_2(SOUND_OBJ_BOWSER_TAIL_PICKUP);
            }
        break;
        case 6://die
            o->oPosY -= 2.0f;
            if (o->oTimer == 50) {
                cur_obj_play_sound_2(SOUND_OBJ_BOWSER_DEFEATED);
            }
            if (o->oTimer > 60) {
                spawn_default_star(gMarioState->pos[0],gMarioState->pos[1]+300.0f,gMarioState->pos[2]);
                obj_mark_for_deletion(o);
            }
        break;
    }
}

void bhv_BadCobie(void) {
    struct Object *bullet;
    u8 shoot;
    switch(o->oAction) {
        case 0:
            o->oExtraVariable1 = 6; //ammunition
            o->oAction = 1;
            o->oTimer = random_u16();
        break;
        case 1:
            o->oFaceAnglePitch = 0;
            o->oMoveAngleYaw = o->oAngleToMario;

            o->oForwardVel *= .9f;

            if (o->oDistanceToMario < 600.0f) {//back away
                if (o->oForwardVel > -22.0f) {
                    o->oForwardVel -= 2.0f;
                }
            }

            if ((o->oDistanceToMario > 900.0f)&&(!(cur_obj_lateral_dist_from_mario_to_home() > 1200.0f))) {//get closer
                if (o->oForwardVel < 22.0f) {
                    o->oForwardVel += 2.0f;
                }
            }

            if (o->oTimer % 12 == 11) {
                cur_obj_init_animation_with_sound(0);
                shoot = (o->oDistanceToMario < 1100.0f);
                cur_obj_init_animation_with_sound(2-shoot);
                if (shoot) {
                    o->oExtraVariable1--;
                    bullet = spawn_object(o, MODEL_BOWLING_BALL, bhvSnufitBalls);
                    bullet->oPosY += 70.0f;
                    gMarioObject->oPosY += 70.0f;
                    bullet->oMoveAnglePitch = obj_turn_toward_object(bullet, gMarioObject, O_MOVE_ANGLE_PITCH_INDEX, 200);
                    gMarioObject->oPosY -= 70.0f;
                    cur_obj_play_sound_2(SOUND_GENERAL_RACE_GUN_SHOT);
                }

                if (o->oExtraVariable1 < 1) {
                    o->oAction = 2;
                    cur_obj_init_animation_with_sound(0);
                }
            }
        break;
        case 2: //reloading
            if (o->oTimer > 15) {
                o->oForwardVel = 0.0f;
                o->oFaceAnglePitch = 0x1000;
                if (o->oTimer % 15 == 0) {
                    cur_obj_play_sound_2(SOUND_MENU_CLICK_CHANGE_VIEW);
                    o->oExtraVariable1++;
                    if (o->oExtraVariable1 > 5) {
                        o->oAction = 1;
                    }
                }
            }

        break;
    }

    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(-30);
    cur_obj_set_hitbox_and_die_if_attacked(&sLadybugHitbox, SOUND_GENERAL_SPLATTERING,0);
}

struct ObjectHitbox sMissileHitbox = {
    /* interactType: */ INTERACT_DAMAGE,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 2,
    /* health: */ 1,
    /* numLootCoins: */ 7,
    /* radius: */ 40,
    /* height: */ 40,
    /* hurtboxRadius: */ 40,
    /* hurtboxHeight: */ 40,
};

static s16 obj_turn_pitch_toward_mario_rovert(f32 targetOffsetY, s16 turnAmount) {
    s16 targetPitch;

    o->oPosY -= targetOffsetY;
    targetPitch = obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_PITCH_INDEX, turnAmount);
    o->oPosY += targetOffsetY;

    return targetPitch;
}

void bhv_missile_loop(void) {
    u8 start_thresh = 30;
    f32 mispeed = 65.0f;
    if (gCurrLevelNum == LEVEL_RR) {
        start_thresh = 5;
        mispeed = 20.0f;
    }


    if (revent_active) {
        spawn_object(o,MODEL_EXPLOSION,bhvExplosion);
        obj_mark_for_deletion(o);
        return;
    }

    o->oGravity = 0;

    //this code is kind of stinky
    if(o->oTimer > start_thresh) {
        obj_turn_toward_object(o, gMarioObject, 16, 0x100);
        o->oMoveAnglePitch = obj_turn_pitch_toward_mario_rovert(150.0f, 1);
    }
    
    /*
    if (o->oDistanceToMario < 2000.0f) {
        o->oMoveAnglePitch += obj_turn_pitch_toward_mario_rovert(150.0f, 1)/15;
    } else {
        o->oMoveAnglePitch = obj_turn_pitch_toward_mario_rovert(150.0f, 1);
    }
    */

    if (o->oMoveAnglePitch < 0) {
        o->oMoveAnglePitch = 0;
    }

    o->oFaceAnglePitch = -o->oMoveAnglePitch;
    o->oFaceAngleYaw = o->oMoveAngleYaw+0x7FFF;

    o->oForwardVel = mispeed *  coss(o->oMoveAnglePitch);
    o->oVelY       = mispeed * -sins(o->oMoveAnglePitch);

    o->oPosY += o->oVelY;

    if ((o->oTimer > 100)&&(o->oMoveAnglePitch < 0xD000)) {
        o->oMoveAnglePitch += 0x100;
        }

    //INIT
    if (o->oAction == 0) {
        obj_set_hitbox(o, &sMissileHitbox);
        o->oAction = 1;
        }

    if ((o->oMoveFlags & (OBJ_MOVE_MASK_ON_GROUND | OBJ_MOVE_HIT_WALL))||(o->oTimer > 300)||(o->oMoveFlags & 0x200)||(o->parentObj->oHealth == 0)) {
        spawn_object(o,MODEL_EXPLOSION,bhvExplosion);
        obj_mark_for_deletion(o);
        }

    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(50);
    }

//

struct ObjectHitbox sScuttlebugNormalHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 1,
    /* numLootCoins:      */ 3,
    /* radius:            */ 130,
    /* height:            */ 70,
    /* hurtboxRadius:     */ 90,
    /* hurtboxHeight:     */ 60,
};

void bhv_scuttlebug_normal_loop(void) {
    cur_obj_update_floor_and_walls();

    if (o->oSubAction != 0
        && cur_obj_set_hitbox_and_die_if_attacked(&sScuttlebugNormalHitbox, SOUND_OBJ_DYING_ENEMY1, o->oScuttlebugHasNoLootCoins)) {
        o->oSubAction = 3;
    }

    if (o->oSubAction != 1) {
        o->oScuttlebugIsAtttacking = 0;
    }

    switch (o->oSubAction) {
        case 0:
            if (o->oMoveFlags & OBJ_MOVE_LANDED) {
                cur_obj_play_sound_2(SOUND_OBJ_GOOMBA_ALERT);
            }
            if (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND) {
                vec3f_copy(&o->oHomeVec, &o->oPosVec);
                o->oSubAction++;
            }
            break;

        case 1:
            o->oForwardVel = 5.0f;
            if (cur_obj_lateral_dist_from_mario_to_home() > 1000.0f) {
                o->oAngleToMario = cur_obj_angle_to_home();
            } else {
                if (o->oScuttlebugIsAtttacking == 0) {
                    o->oScuttlebugTimer = 0;
                    o->oAngleToMario = obj_angle_to_object(o, gMarioObject);
                    if (abs_angle_diff(o->oAngleToMario, o->oMoveAngleYaw) < 0x800) {
                        o->oScuttlebugIsAtttacking = 1;
                        o->oVelY = 20.0f;
                        cur_obj_play_sound_2(SOUND_OBJ2_SCUTTLEBUG_ALERT);
                    }
                } else if (o->oScuttlebugIsAtttacking == 1) {
                    o->oForwardVel = 15.0f;
                    o->oScuttlebugTimer++;
                    if (o->oScuttlebugTimer > 50) {
                        o->oScuttlebugIsAtttacking = FALSE;
                    }
                }
            }
            if (update_angle_from_move_flags(&o->oAngleToMario)) {
                o->oSubAction = 2;
            }
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x200);
            break;

        case 2:
            o->oForwardVel = 5.0f;
            if ((s16) o->oMoveAngleYaw == (s16) o->oAngleToMario) {
                o->oSubAction = 1;
            }
            if (o->oPosY - o->oHomeY < -200.0f) {
                obj_mark_for_deletion(o);
            }
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x400);
            break;

        case 3:
            o->oFlags &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
            o->oForwardVel = -10.0f;
            o->oVelY = 30.0f;
            cur_obj_play_sound_2(SOUND_OBJ2_SCUTTLEBUG_ALERT);
            o->oSubAction++;
            break;

        case 4:
            o->oForwardVel = -10.0f;
            if (o->oMoveFlags & OBJ_MOVE_LANDED) {
                o->oSubAction++;
                o->oVelY = 0.0f;
                o->oScuttlebugTimer = 0;
                o->oFlags |= OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
                o->oInteractStatus = INT_STATUS_NONE;
            }
            break;

        case 5:
            o->oForwardVel = 2.0f;
            o->oScuttlebugTimer++;
            if (o->oScuttlebugTimer > 30) {
                o->oSubAction = 0;
            }
            break;
    }

    f32 animSpeed = o->oForwardVel < 10.0f ? 1.0f : 3.0f;

    cur_obj_init_animation_with_accel_and_sound(0, animSpeed);

    if (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND) {
        set_obj_anim_with_accel_and_sound(1, 23, SOUND_OBJ2_SCUTTLEBUG_WALK);
    }

    if (o->parentObj != o) {
        if (obj_is_hidden(o)) {
            obj_mark_for_deletion(o);
        }
        if (o->activeFlags == ACTIVE_FLAG_DEACTIVATED) {
            o->parentObj->oScuttlebugSpawnerIsDeactivated = 1;
        }
    }

    cur_obj_move_standard(-50);
}