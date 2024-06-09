// moneybag.inc.c

static struct ObjectHitbox sMoneybagHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 2,
    /* health:            */ 1,
    /* numLootCoins:      */ 0,
    /* radius:            */ 120,
    /* height:            */ 60,
    /* hurtboxRadius:     */ 100,
    /* hurtboxHeight:     */ 50,
};

static struct ObjectHitbox sMoneybagHiddenHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 2,
    /* health:            */ 1,
    /* numLootCoins:      */ 0,
    /* radius:            */ 120,
    /* height:            */ 60,
    /* hurtboxRadius:     */ 100,
    /* hurtboxHeight:     */ 50,
};

void bhv_moneybag_init(void) {
    o->oGravity = 3.0f;
    o->oFriction = 1.0f;
    o->oBuoyancy = 2.0f;
    cur_obj_init_animation(0);
    o->oOpacity = 0;
}

void moneybag_check_mario_collision(void) {
    obj_set_hitbox(o, &sMoneybagHitbox);

    if (is_cur_obj_interact_with_lava(1)) {
        o->oInteractStatus = (INT_STATUS_WAS_ATTACKED | INT_STATUS_INTERACTED);
    }

    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        if (o->oInteractStatus & INT_STATUS_ATTACKED_MARIO) {
            o->oMoveAngleYaw = o->oAngleToMario + 0x8000;
            o->oVelY = 30.0f;
            if (o->oQuicksandDepth > 0) {
                // Quicksand will stunt their jumps heavily
                o->oVelY = 0;
                o->oQuicksandDepth = CLAMP(o->oQuicksandDepth-15,0,255);
            }
        }

        if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
            o->oAction = MONEYBAG_ACT_DEATH;
        }

        o->oInteractStatus = INT_STATUS_NONE;
    }
}

void moneybag_jump(s16 collisionFlags) {
    s16 animFrame = o->header.gfx.animInfo.animFrame;

    if ((collisionFlags & OBJ_COL_FLAG_GROUNDED) == OBJ_COL_FLAG_GROUNDED) {
        if (o->oPosY < o->oHomeY - 10.f) {
            vec3_copy(&o->oHomeVec, &o->oPosVec);
        }
    }

    switch (o->oMoneybagJumpState) {
        case MONEYBAG_JUMP_PREPARE:
            cur_obj_init_animation(1);
            if (animFrame == 5) {
                o->oForwardVel = 20.0f;
                o->oVelY = 40.0f;
                if (o->oQuicksandDepth > 0) {
                    // Quicksand will stunt their jumps heavily
                    o->oVelY = 0;
                    o->oQuicksandDepth = CLAMP(o->oQuicksandDepth-15,0,255);
                }
            }

            if (cur_obj_check_if_near_animation_end()) {
                o->oMoneybagJumpState = MONEYBAG_JUMP_JUMP;
                cur_obj_play_sound_2(SOUND_GENERAL_MONEYBAG_BOING_LOWPRIO);
            }
            break;

        case MONEYBAG_JUMP_JUMP:
            cur_obj_init_animation(2);

            if ((collisionFlags & OBJ_COL_FLAG_GROUNDED) == OBJ_COL_FLAG_GROUNDED) {
                o->oForwardVel = 0;
                o->oVelY = 0;
                o->oMoneybagJumpState = MONEYBAG_JUMP_LANDING;
            }
            break;

        case MONEYBAG_JUMP_JUMP_AND_BOUNCE:
            cur_obj_init_animation(3);

            if (cur_obj_check_if_near_animation_end()) {
                o->oMoneybagJumpState = MONEYBAG_JUMP_LANDING;
            }
            break;

        case MONEYBAG_JUMP_WALK_AROUND:
            cur_obj_init_animation(4);
            o->oForwardVel = 10.0f;

            if (o->oTimer > 60) {
                o->oMoneybagJumpState = MONEYBAG_JUMP_LANDING;
                o->oForwardVel = 0;
                o->header.gfx.animInfo.animFrame = 0;
            }
            break;

        case MONEYBAG_JUMP_WALK_HOME:
            cur_obj_init_animation(4);
            o->oForwardVel = 5.0f;
            break;
    }
}

void moneybag_act_move_around(void) {
    s16 collisionFlags;

    obj_return_and_displace_home(o, o->oHomeX, o->oHomeY, o->oHomeZ, 200);

    collisionFlags = object_step();

    if (((collisionFlags & OBJ_COL_FLAGS_LANDED) == OBJ_COL_FLAGS_LANDED)
        && (o->oMoneybagJumpState == MONEYBAG_JUMP_LANDING)) {
        if ((s32)(random_float() * 6.0f) == 1) {
            o->oMoneybagJumpState = MONEYBAG_JUMP_WALK_AROUND;
            o->oTimer = 0;
        } else {
            o->oMoneybagJumpState = MONEYBAG_JUMP_PREPARE;
        }
    }

    moneybag_jump(collisionFlags);
    moneybag_check_mario_collision();

    if (!is_point_within_radius_of_mario(o->oHomeX, o->oHomeY, o->oHomeZ, 800)
        && ((collisionFlags & OBJ_COL_FLAGS_LANDED) == OBJ_COL_FLAGS_LANDED)) {
        o->oAction = MONEYBAG_ACT_RETURN_HOME;
    }
    cur_obj_die_if_on_death_barrier(MB64_STAR_HEIGHT);
}

void moneybag_act_return_home(void) {
    f32 dx = o->oHomeX - o->oPosX;
    f32 dz = o->oHomeZ - o->oPosZ;
    s16 yawToHome = atan2s(dz, dx);

    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, yawToHome, 0x800);

    s16 collisionFlags = object_step();

    if (((collisionFlags & OBJ_COL_FLAGS_LANDED) == OBJ_COL_FLAGS_LANDED)
        && (o->oMoneybagJumpState == MONEYBAG_JUMP_LANDING)) {
        o->oMoneybagJumpState = MONEYBAG_JUMP_WALK_HOME;
    }

    moneybag_jump(collisionFlags);
    moneybag_check_mario_collision();

    if (is_point_close_to_object(o, o->oHomeX, o->oHomeY, o->oHomeZ, 100)) {
        spawn_object(o, MODEL_YELLOW_COIN, bhvMoneybagHidden);
        cur_obj_play_sound_2(SOUND_ACTION_TELEPORT);
        cur_obj_init_animation(0);
        o->oAction = MONEYBAG_ACT_DISAPPEAR;
        o->oMoneybagJumpState = MONEYBAG_JUMP_LANDING;
    }

    if (is_point_within_radius_of_mario(o->oHomeX, o->oHomeY, o->oHomeZ, 800)) {
        o->oAction = MONEYBAG_ACT_MOVE_AROUND;
        o->oMoneybagJumpState = MONEYBAG_JUMP_LANDING;
    }
}

void moneybag_act_disappear(void) {
    o->oOpacity -= 6;
    if (o->oOpacity < 0) {
        o->oOpacity = 0;
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

void moneybag_act_death(void) {
    if (o->oTimer == 1) {
        obj_spawn_yellow_coins(o, 5);
        create_sound_spawner(SOUND_GENERAL_SPLATTERING);
        spawn_mist_particles();
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

void bhv_moneybag_loop(void) {
    switch (o->oAction) {
        case MONEYBAG_ACT_APPEAR:
        case MONEYBAG_ACT_UNUSED_APPEAR:
            o->oOpacity += 12;
            if (o->oOpacity > 255) {
                o->oOpacity = 255;
                o->parentObj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
                o->oAction = MONEYBAG_ACT_MOVE_AROUND;
            }
            object_step();
            break;

        case MONEYBAG_ACT_MOVE_AROUND:
            moneybag_act_move_around();
            if (o->oTimer > 30) {
                cur_obj_become_tangible();
            }
            break;

        case MONEYBAG_ACT_RETURN_HOME:
            moneybag_act_return_home();
            break;

        case MONEYBAG_ACT_DISAPPEAR:
            moneybag_act_disappear();
            object_step();
            break;

        case MONEYBAG_ACT_DEATH:
            moneybag_act_death();
            break;
    }
}

void bhv_moneybag_hidden_loop(void) {
    if (o->oTimer == 0) {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_YELLOW_COIN];
    }
    obj_set_hitbox(o, &sMoneybagHiddenHitbox);

    switch (o->oAction) {
        case FAKE_MONEYBAG_COIN_ACT_IDLE:
            if (is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 400)) {
                spawn_object(o, MODEL_MONEYBAG, bhvMoneybag);
                cur_obj_play_sound_2(SOUND_ACTION_TELEPORT);
                o->oAction = FAKE_MONEYBAG_COIN_ACT_TRANSFORM;
            }
            break;

        case FAKE_MONEYBAG_COIN_ACT_TRANSFORM:
            break;
    }

    o->oInteractStatus = INT_STATUS_NONE;

    o->oGravity = 3.0f;
    o->oFriction = 1.0f;
    o->oBuoyancy = 2.0f;
    object_step();
    cur_obj_die_if_on_death_barrier(MB64_STAR_HEIGHT);
}
