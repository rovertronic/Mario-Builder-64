// scuttlebug.inc.c

// struct ObjectHitbox sSlobHitbox = {
//     /* interactType: */ INTERACT_BOUNCE_TOP,
//     /* downOffset: */ 0,
//     /* damageOrCoinValue: */ 2,
//     /* health: */ 3,
//     /* numLootCoins: */ 3,
//     /* radius: */ 130,
//     /* height: */ 70,
//     /* hurtboxRadius: */ 90,
//     /* hurtboxHeight: */ 60,
// };

// struct ObjectHitbox sRexBossHitbox = {
//     /* interactType: */ INTERACT_BOUNCE_TOP,
//     /* downOffset: */ 0,
//     /* damageOrCoinValue: */ 3,
//     /* health: */ 25,
//     /* numLootCoins: */ 20,
//     /* radius: */ 130,
//     /* height: */ 70,
//     /* hurtboxRadius: */ 90,
//     /* hurtboxHeight: */ 60,
// };

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

// struct ObjectHitbox sScuttlebugSpawnedHitbox = {
//     /* interactType: */ INTERACT_BOUNCE_TOP,
//     /* downOffset: */ 0,
//     /* damageOrCoinValue: */ 1,
//     /* health: */ 2,
//     /* numLootCoins: */ 0,
//     /* radius: */ 130,
//     /* height: */ 70,
//     /* hurtboxRadius: */ 90,
//     /* hurtboxHeight: */ 60,
// };

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

// struct ObjectHitbox sCactusHitbox = {
//     /* interactType: */ INTERACT_DAMAGE,
//     /* downOffset: */ 0,
//     /* damageOrCoinValue: */ 3,
//     /* health: */ 1,
//     /* numLootCoins: */ 7,
//     /* radius: */ 20,
//     /* height: */ 20,
//     /* hurtboxRadius: */ 20,
//     /* hurtboxHeight: */ 20,
// };

// struct ObjectHitbox sMaskHitbox = {
//     /* interactType: */ INTERACT_MR_BLIZZARD,
//     /* downOffset: */ 32,
//     /* damageOrCoinValue: */ 4,
//     /* health: */ 1,
//     /* numLootCoins: */ 7,
//     /* radius: */ 75,
//     /* height: */ 75,
//     /* hurtboxRadius: */ 75,
//     /* hurtboxHeight: */ 75,
// };

// struct ObjectHitbox sTrapHitbox = {
//     /* interactType: */ INTERACT_DAMAGE,
//     /* downOffset: */ 0,
//     /* damageOrCoinValue: */ 6,
//     /* health: */ 1,
//     /* numLootCoins: */ 7,
//     /* radius: */ 100,
//     /* height: */ 40,
//     /* hurtboxRadius: */ 150,
//     /* hurtboxHeight: */ 60,
// };

// struct ObjectHitbox sRetroPlantHitbox = {
//     /* interactType: */ INTERACT_DAMAGE,
//     /* downOffset: */ 0,
//     /* damageOrCoinValue: */ 3,
//     /* health: */ 1,
//     /* numLootCoins: */ 7,
//     /* radius: */ 75,
//     /* height: */ 150,
//     /* hurtboxRadius: */ 75,
//     /* hurtboxHeight: */ 300,
// };

// struct ObjectHitbox sBillHitbox = {
//     /* interactType: */ INTERACT_BOUNCE_TOP,
//     /* downOffset: */ 0,
//     /* damageOrCoinValue: */ 3,
//     /* health: */ 1,
//     /* numLootCoins: */ 0,
//     /* radius: */ 70,
//     /* height: */ 85,
//     /* hurtboxRadius: */ 75,
//     /* hurtboxHeight: */ 35,
// };

// struct ObjectHitbox sLadybugHitbox = {
//     /* interactType: */ INTERACT_BOUNCE_TOP,
//     /* downOffset: */ 0,
//     /* damageOrCoinValue: */ 3,
//     /* health: */ 1,
//     /* numLootCoins: */ 5,
//     /* radius: */ 70,
//     /* height: */ 95,
//     /* hurtboxRadius: */ 75,
//     /* hurtboxHeight: */ 45,
// };

// struct ObjectHitbox sRBowserHitbox = {
//     /* interactType: */ INTERACT_DAMAGE,
//     /* downOffset: */ 0,
//     /* damageOrCoinValue: */ 3,
//     /* health: */ 1,
//     /* numLootCoins: */ 0,
//     /* radius: */ 130,
//     /* height: */ 130,
//     /* hurtboxRadius: */ 130,
//     /* hurtboxHeight: */ 130,
// };

s32 update_angle_from_move_flags(s16 *angle) {
    if (o->oMoveFlags & OBJ_MOVE_HIT_WALL) {
        *angle = o->oWallAngle;
        return 1;
    } else if (o->oMoveFlags & OBJ_MOVE_HIT_EDGE) {
        *angle = o->oMoveAngleYaw + 0x8000;
        return 1;
    }
    return 0;
}

void bhv_scuttlebug_loop(void) {
    if (o->oSubAction >= 6) {
        if ((gMarioState->action & ACT_FLAG_ATTACKING) || (o->oSubAction == 7)) {
            spawn_mist_particles();
            if (!cur_obj_drop_imbued_object(MB64_STAR_HEIGHT)) {
                obj_spawn_loot_yellow_coins(o, o->oNumLootCoins, 20.0f);
            }
            obj_mark_for_deletion(o);
            gMarioState->faceCrablet = NULL;
            play_sound(SOUND_OBJ_DYING_ENEMY1, o->header.gfx.cameraToObject);
            return;
        }
        vec3_copy(&o->oPosVec, gMarioState->pos);
        o->oPosX += 60.f * sins(gMarioState->faceAngle[1]);
        o->oPosY += 100.f;
        o->oPosZ += 60.f * coss(gMarioState->faceAngle[1]);
        o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
        cur_obj_set_home_if_safe_held();

        o->oVelY = 0.0f;
        if (o->oTimer > 20) {
            gMarioState->hurtCounter ++;
            o->oTimer = 0;
        }
        return;
    }

    struct ObjectHitbox *hitbox_to_use;
    Vec3f original_pos;
    vec3f_copy(original_pos,&o->oPosX);

    hitbox_to_use = &sScuttlebugHitbox;
    cur_obj_update_floor_and_walls();
    cur_obj_set_home_if_safe();

    if (is_cur_obj_interact_with_lava(0)) {
        o->oInteractStatus = (INT_STATUS_WAS_ATTACKED | INT_STATUS_INTERACTED);
    }

    if (o->oSubAction != 0
        && cur_obj_set_hitbox_and_die_if_attacked(hitbox_to_use, SOUND_OBJ_DYING_ENEMY1, o->oScuttlebugHasNoLootCoins)) {
        o->oSubAction = 3;
    }

    if (o->oSubAction != 1) {
        o->oScuttlebugIsAtttacking = 0;
    }

    switch (o->oSubAction) {
        case 0:
            if (o->oMoveFlags & OBJ_MOVE_LANDED) {
                cur_obj_play_sound_2(SOUND_OBJ_GOOMBA_ALERT);
            } else if (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND) {
                o->oSubAction++;
            }
            break;

        case 1:
            o->oForwardVel = 5.0f;
            if (!o->oScuttlebugIsAtttacking) {
                o->oScuttlebugTimer = 0;
                o->oAngleToMario;
                if ((abs_angle_diff(o->oAngleToMario, o->oMoveAngleYaw) < 0x2000) && (o->oDistanceToMario < 1000.0f)) {
                    o->oScuttlebugIsAtttacking = TRUE;
                    o->oVelY = 50.0f;
                    cur_obj_play_sound_2(SOUND_OBJ2_SCUTTLEBUG_ALERT);
                    if (o->oQuicksandDepth > 0) {
                        // Quicksand will stunt their jumps heavily
                        o->oVelY = 0;
                        o->oQuicksandDepth = CLAMP(o->oQuicksandDepth-15,0,255);
                    }
                }
                o->oMoveAngleYaw += 0x200;
                o->oScuttlebugTargetAngle = o->oMoveAngleYaw;
                if (update_angle_from_move_flags(&o->oScuttlebugTargetAngle)) {
                    o->oSubAction = 2;
                }
            } else {
                o->oForwardVel = 30.0f;
                o->oScuttlebugTimer++;
                if (o->oScuttlebugTimer > 50) {
                    o->oScuttlebugIsAtttacking = FALSE;
                }
                cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x200);
            }
            break;

        case 2:
            o->oForwardVel = 5.0f;
            if ((s16) o->oMoveAngleYaw == (s16) o->oScuttlebugTargetAngle) {
                o->oSubAction = 1;
            }
            cur_obj_rotate_yaw_toward(o->oScuttlebugTargetAngle, 0x400);
            break;

        case 3:
            o->oFlags &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
            o->oForwardVel = -10.0f;
            o->oVelY = 30.0f;
            cur_obj_play_sound_2(SOUND_OBJ2_SCUTTLEBUG_ALERT);

            if (o->oQuicksandDepth > 0) {
                // Quicksand will stunt their jumps heavily
                o->oVelY = 0;
                o->oQuicksandDepth = CLAMP(o->oQuicksandDepth-15,0,255);
            }

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

    //fuck mario's head
    if ((o->oDistanceToMario < 200.0f)&&(o->oPosY-30.0f>gMarioState->pos[1])&&(!gMarioState->faceCrablet)) {
        o->oSubAction = 6;
        gMarioState->faceCrablet = o;
    }

    f32 animSpeed = o->oForwardVel < 10.0f ? 1.0f : 3.0f;

    cur_obj_init_animation_with_accel_and_sound(0, animSpeed);

    if (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND) {
        set_obj_anim_with_accel_and_sound(1, 23, SOUND_OBJ2_SCUTTLEBUG_WALK);
    }

    cur_obj_move_standard(-50);
    cur_obj_die_if_on_death_barrier(MB64_STAR_HEIGHT);
}

u16 RandomMinMaxU16(u16 min, u16 max) {
    u16 num = random_u16();
    return (num % ((max + 1) - min)) + min;
}

void throw_hammer(void) {
    struct Object *hammer;

    if (gMarioState->pos[1] > o->oPosY - 200.0f) { //do not throw hammers if mario is far below
        if (o->oAnimState == 0) {//hammer
            hammer = spawn_object(o, MODEL_HAMMER, bhvHammer);
            hammer->oMoveAngleYaw = o->oFaceAngleYaw;
            hammer->oVelY = RandomMinMaxU16(30,50);
            hammer->oForwardVel = RandomMinMaxU16(20,50);
            hammer->oPosY += 20.0f - o->oQuicksandDepth*2.0f;
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

    o->oFaceAngleYaw = o->oAngleToMario;

    //ONLY DO IF ACTIVE
    if (!(o->activeFlags & ACTIVE_FLAG_FAR_AWAY)) {
        cur_obj_enable_rendering();
        //INIT
        if (o->oAction == 0) {
            obj_set_hitbox(o, &sHammerBroHitbox);
            o->oAction = 1;

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
                        if (o->oQuicksandDepth > 0) {
                            // Quicksand will stunt their jumps heavily
                            o->oVelY = 0;
                            o->oQuicksandDepth = CLAMP(o->oQuicksandDepth-15,0,255);
                        }
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

            //o->oForwardVel = 35.0f;

            if (o->oTimer > 5) {
                if (o->oMoveFlags & 3) {
                    cur_obj_init_animation_with_sound(0);
                    o->oAction = 1;
                    o->oTimer = RandomMinMaxU16(0,30);
                    o->oForwardVel = 0.0f;

                    if (o->oScuttlebugHasNoLootCoins > 0) {
                        o->oScuttlebugHasNoLootCoins = 0;
                        } else {
                        o->oScuttlebugHasNoLootCoins ++;
                        }
                    }
                }
            }

        cur_obj_update_floor_and_walls();
        cur_obj_set_home_if_safe();
        cur_obj_move_standard(-50);

        //TODO: Replace with generic handler
        if (o->oMoveFlags & OBJ_MOVE_MASK_IN_WATER) {
            o->oInteractStatus |= INT_STATUS_WAS_ATTACKED;
            o->oInteractStatus |= INT_STATUS_INTERACTED;
        }
        f32 floorY = find_floor_short(o->oPosX, o->oPosY, o->oPosZ, &sObjFloor);
        if (sObjFloor != NULL) {
            if ((floorY + 1.f > o->oPosY) && (SURFACE_IS_BURNING(sObjFloor->type))) {
                o->oInteractStatus |= INT_STATUS_WAS_ATTACKED;
                o->oInteractStatus |= INT_STATUS_INTERACTED;
            }
        }

        cur_obj_set_hitbox_and_die_if_attacked(&sHammerBroHitbox, SOUND_OBJ_KOOPA_DAMAGE,0);
        cur_obj_die_if_on_death_barrier(MB64_STAR_HEIGHT);
    } else {
        cur_obj_disable_rendering();
        o->oTimer --;
    }
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
    cur_obj_set_home_if_safe();

    if (is_cur_obj_interact_with_lava(0)) {
        o->oInteractStatus = (INT_STATUS_WAS_ATTACKED | INT_STATUS_INTERACTED);
    }

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
                o->oSubAction++;
            }
            break;

        case 1:
            o->oForwardVel = 5.0f;
            if (!o->oScuttlebugIsAtttacking) {
                o->oScuttlebugTimer = 0;
                if ((abs_angle_diff(o->oAngleToMario, o->oMoveAngleYaw) < 0x2000) && (o->oDistanceToMario < 1000.0f)) {
                    o->oScuttlebugIsAtttacking = TRUE;
                    o->oVelY = 20.0f;
                    if (o->oQuicksandDepth > 0) {
                        // Quicksand will stunt their jumps heavily
                        o->oVelY = 0;
                        o->oQuicksandDepth = CLAMP(o->oQuicksandDepth-15,0,255);
                    }
                    cur_obj_play_sound_2(SOUND_OBJ2_SCUTTLEBUG_ALERT);
                }
                o->oMoveAngleYaw += 0x200;
                o->oScuttlebugTargetAngle = o->oMoveAngleYaw;
                if (update_angle_from_move_flags(&o->oScuttlebugTargetAngle)) {
                    o->oSubAction = 2;
                }
            } else {
                o->oForwardVel = 15.0f;
                o->oScuttlebugTimer++;
                if (o->oScuttlebugTimer > 50) {
                    o->oScuttlebugIsAtttacking = FALSE;
                }
                cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x200);
            }
            break;

        case 2:
            o->oForwardVel = 5.0f;
            if ((s16) o->oMoveAngleYaw == (s16) o->oScuttlebugTargetAngle) {
                o->oSubAction = 1;
            }
            cur_obj_rotate_yaw_toward(o->oScuttlebugTargetAngle, 0x400);
            break;

        case 3:
            o->oFlags &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
            o->oForwardVel = -10.0f;
            o->oVelY = 30.0f;
            if (o->oQuicksandDepth > 0) {
                // Quicksand will stunt their jumps heavily
                o->oVelY = 0;
                o->oQuicksandDepth = CLAMP(o->oQuicksandDepth-15,0,255);
            }
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
    cur_obj_die_if_on_death_barrier(MB64_STAR_HEIGHT);
}