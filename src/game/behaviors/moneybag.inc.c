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

    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 320);

    collisionFlags = object_step();

    if ((collisionFlags & OBJ_COL_FLAGS_LANDED)
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

    if ((o->oDistanceToMario > 800.f)
        && (collisionFlags & OBJ_COL_FLAGS_LANDED)) {
        o->oAction = MONEYBAG_ACT_RETURN_HOME;
    }
}

void moneybag_act_return_home(void) {
    s16 collisionFlags = object_step();

    if ((collisionFlags & OBJ_COL_FLAGS_LANDED)
        && (o->oMoneybagJumpState == MONEYBAG_JUMP_LANDING)) {
        o->oMoneybagJumpState = MONEYBAG_JUMP_WALK_HOME;
    }

    moneybag_jump(collisionFlags);
    moneybag_check_mario_collision();

    if (o->oDistanceToMario < 800.f) {
        o->oAction = MONEYBAG_ACT_MOVE_AROUND;
        o->oMoneybagJumpState = MONEYBAG_JUMP_LANDING;
    } else if (o->oMoneybagJumpState == MONEYBAG_JUMP_WALK_HOME) {
        o->prevObj = spawn_object(o, MODEL_YELLOW_COIN, bhvMoneybagHidden);
        o->prevObj->oImbue = o->oImbue;
        o->prevObj->prevObj = o;
        cur_obj_play_sound_2(SOUND_ACTION_TELEPORT);
        cur_obj_init_animation(0);
        o->oAction = MONEYBAG_ACT_DISAPPEAR;
        o->oForwardVel = 0.f;
    }
}

void moneybag_act_disappear(void) {
    o->oOpacity -= 6;
    if (o->oOpacity < 0) {
        o->oOpacity = 0;
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        vec3_copy(&o->prevObj->oHomeVec, &o->oHomeVec);
    }
}

void moneybag_act_death(void) {
    if (o->oTimer == 1) {
        cur_obj_drop_imbued_object(MB64_STAR_HEIGHT);
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
                vec3_copy(&o->oHomeVec, &o->parentObj->oHomeVec);
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
    cur_obj_set_home_if_safe();
    cur_obj_die_if_on_death_barrier(MB64_STAR_HEIGHT);
}

extern struct imbue_model imbue_model_data[];

void bhv_moneybag_hidden_init(void) {
    cur_obj_set_model(imbue_model_data[o->oImbue].model);
    // Billboard coins
    if (imbue_model_data[o->oImbue].billboarded) o->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
    // Set blue switch to blue
    if ((o->oImbue == IMBUE_BLUE_SWITCH) || (o->oImbue == IMBUE_RED_SWITCH)) {
        if (o->prevObj) o->oMoneybagHiddenScale = 0.1f;
        if (o->oImbue == IMBUE_BLUE_SWITCH) o->oAnimState = 1;
        o->oFaceAngleYaw = 0;
    }
    // Set star height
    if (!o->prevObj && o->oImbue == IMBUE_STAR) o->oGraphYOffset = 128.f;
}

void bhv_moneybag_hidden_loop(void) {
    obj_set_hitbox(o, &sMoneybagHiddenHitbox);

    switch (o->oAction) {
        case FAKE_MONEYBAG_COIN_ACT_IDLE:
            if (o->oDistanceToMario < 400.f) {
                o->prevObj = spawn_object(o, MODEL_MONEYBAG, bhvMoneybag);
                o->prevObj->oImbue = o->oImbue;
                vec3_copy(&o->prevObj->oHomeVec, &o->oHomeVec);
                cur_obj_play_sound_2(SOUND_ACTION_TELEPORT);
                o->oAction = FAKE_MONEYBAG_COIN_ACT_TRANSFORM;
            }
            break;

        case FAKE_MONEYBAG_COIN_ACT_TRANSFORM:
            break;
    }

    if (o->prevObj) vec3_copy(&o->oHomeVec, &o->prevObj->oHomeVec);

    if (o->oImbue == IMBUE_STAR) {
        o->oFaceAngleYaw += 0x800;
        if (o->oAction == FAKE_MONEYBAG_COIN_ACT_TRANSFORM) {
            o->oGraphYOffset -= 4.f;
        } else if (o->oGraphYOffset < 128.f) {
            o->oGraphYOffset += 4.f;
        }
    } else if ((o->oImbue == IMBUE_RED_SWITCH) || (o->oImbue == IMBUE_BLUE_SWITCH)) {
        if (o->oAction == FAKE_MONEYBAG_COIN_ACT_TRANSFORM) {
            approach_f32_symmetric_bool(&o->oMoneybagHiddenScale, 0.1f, 0.03f);
        } else {
            approach_f32_symmetric_bool(&o->oMoneybagHiddenScale, 1.f, 0.03f);
        }
    } else {
        o->oAnimState += 1;
    }

    cur_obj_scale(o->oMoneybagHiddenScale);
    o->oInteractStatus = INT_STATUS_NONE;

    o->oGravity = 3.0f;
    o->oFriction = 1.0f;
    o->oBuoyancy = 2.0f;
    object_step();
    cur_obj_set_home_if_safe();

    if (is_cur_obj_interact_with_lava(1)) {
        if (o->prevObj) o->prevObj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        cur_obj_drop_imbued_object(MB64_STAR_HEIGHT);
        create_sound_spawner(SOUND_GENERAL_SPLATTERING);
        spawn_mist_particles();
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }

    cur_obj_die_if_on_death_barrier(MB64_STAR_HEIGHT);
}
