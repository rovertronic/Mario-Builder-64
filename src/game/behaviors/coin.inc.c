// coin.inc.c

struct ObjectHitbox sYellowCoinHitbox = {
    /* interactType:      */ INTERACT_COIN,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 100,
    /* height:            */ 64,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

struct ObjectHitbox sGreenCoinHitbox = {
    /* interactType: */ INTERACT_COIN,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 3,
    /* health: */ 0,
    /* numLootCoins: */ 0,
    /* radius: */ 100,
    /* height: */ 64,
    /* hurtboxRadius: */ 0,
    /* hurtboxHeight: */ 0,
};


//fuck you arrow, let's take this asshole down!!!
/**
 *     3
 *   4   6
 * 5   2   7
 * 
 *     1
 * 
 *     0
 **/
 //some arrows don't realize what a piece of shit they are!!!
s16 sCoinArrowPositions[][2] = {
    { 0, -150 },
    { 0, -50 },
    { 0, 50 },
    { 0, 150 },
    { -50, 100 },
    { -100, 50 },
    { 50, 100 },
    { 100, 50 },
};

s16 cock_hard_resevoir[][2] = { {-200, 0} , {200, 0}, {0, 200}, {0, -200} , {-100, 0} , {100, 0}, {0, 100}, {0, -100} };

s32 bhv_coin_sparkles_init(void) {
    if (o->oInteractStatus & INT_STATUS_INTERACTED
        && !(o->oInteractStatus & INT_STATUS_ATTACKED_BY_OBJECT)) {
        spawn_object(o, MODEL_SPARKLES, bhvCoinSparklesSpawner);
        obj_mark_for_deletion(o);
        return TRUE;
    }

    o->oInteractStatus = INT_STATUS_NONE;

    return FALSE;
}

void bhv_yellow_coin_init(void) {
    cur_obj_set_behavior(bhvYellowCoin);
    obj_set_hitbox(o, &sYellowCoinHitbox);
    cur_obj_update_floor_height();

    if (500.0f < absf(o->oPosY - o->oFloorHeight)) {
        if (cur_obj_has_model(MODEL_YELLOW_COIN)) {
            cur_obj_set_model(MODEL_YELLOW_COIN_NO_SHADOW);
        } else if (cur_obj_has_model(MODEL_BLUE_COIN)) {
            cur_obj_set_model(MODEL_BLUE_COIN_NO_SHADOW);
        } else if (cur_obj_has_model(MODEL_RED_COIN)) {
            cur_obj_set_model(MODEL_RED_COIN_NO_SHADOW);
#ifdef IA8_30FPS_COINS
        } else if (cur_obj_has_model(MODEL_SILVER_COIN)) {
            cur_obj_set_model(MODEL_SILVER_COIN_NO_SHADOW);
#endif
        }
    }

    if (o->oFloorHeight < FLOOR_LOWER_LIMIT_MISC) {
        obj_mark_for_deletion(o);
    }
}

void bhv_green_coin_init(void) {
    cur_obj_set_behavior(bhvYellowCoin);
    obj_set_hitbox(o, &sGreenCoinHitbox);
    cur_obj_update_floor_height();
    //if (500.0f < absf(o->oPosY - o->oFloorHeight))
    //    cur_obj_set_model(MODEL_YELLOW_COIN_NO_SHADOW);
    if (o->oFloorHeight < -10000.0f)
        obj_mark_for_deletion(o);
}

void bhv_yellow_coin_loop(void) {
    bhv_coin_sparkles_init();
    o->oAnimState++;
}

void bhv_temp_coin_loop(void) {
    o->oAnimState++;

    if (cur_obj_wait_then_blink(200, 20)) {
        obj_mark_for_deletion(o);
    }

    bhv_coin_sparkles_init();
}

void bhv_coin_init(void) {
    o->oVelY = random_float() * 10.0f + 30 + o->oCoinBaseYVel;
    o->oForwardVel = random_float() * 10.0f;
    o->oMoveAngleYaw = random_u16();

    cur_obj_set_behavior(bhvYellowCoin);
    obj_set_hitbox(o, &sYellowCoinHitbox);
    cur_obj_become_intangible();
}

void bhv_coin_loop(void) {
    cur_obj_update_floor_and_walls();
    cur_obj_if_hit_wall_bounce_away();
    cur_obj_move_standard(-62);

    struct Surface *floor = o->oFloor;

    if ((save_file_get_badge_equip() & (1<<10))) {
        o->oMoveAngleYaw = obj_angle_to_object(o,gMarioObject);
    }

    if (floor != NULL) {
        if (o->oMoveFlags & OBJ_MOVE_ON_GROUND) {
            o->oAction = BOUNCING_COIN_ACT_BOUNCING;
        }
        if (o->oAction == BOUNCING_COIN_ACT_BOUNCING) {
            o->oBounciness = 0;
            Vec3f normal;
            get_surface_normal(normal, floor);
            if (normal[1] < 0.9f) {
                s16 targetYaw = SURFACE_YAW(floor);
                cur_obj_rotate_yaw_toward(targetYaw, 0x400);
            }
        }
    }

    if (o->oTimer == 0) {
        cur_obj_play_sound_2(SOUND_GENERAL_COIN_SPURT);
    }

    if (o->oVelY <= 0) {
        cur_obj_become_tangible();
    }

    if (o->oMoveFlags & OBJ_MOVE_LANDED) {
#ifdef COIN_LAVA_FLICKER
        if ((o->oMoveFlags & OBJ_MOVE_ABOVE_DEATH_BARRIER)
        || ((o->oMoveFlags & OBJ_MOVE_ABOVE_LAVA) && cur_obj_wait_then_blink(0, 20))) {
            obj_mark_for_deletion(o);
        }
#else
        if (o->oMoveFlags & (OBJ_MOVE_ABOVE_DEATH_BARRIER | OBJ_MOVE_ABOVE_LAVA)) {
            obj_mark_for_deletion(o);
        }
#endif
    }

    if (o->oMoveFlags & OBJ_MOVE_BOUNCE) {
        if (o->oCoinBounceTimer < 5) {
            cur_obj_play_sound_2(SOUND_GENERAL_COIN_DROP);
        }
        o->oCoinBounceTimer++;
    }

    if (cur_obj_wait_then_blink(400, 20)) {
        obj_mark_for_deletion(o);
    }

    bhv_coin_sparkles_init();
}

void bhv_coin_formation_spawned_coin_loop(void) {
    if (o->oTimer == 0) {
        cur_obj_set_behavior(bhvYellowCoin);
        obj_set_hitbox(o, &sYellowCoinHitbox);
        if (o->oCoinSnapToGround) {
            //o->oPosY += 300.0f;
            cur_obj_update_floor_height();

            if (o->oPosY + FIND_FLOOR_BUFFER < o->oFloorHeight || o->oFloorHeight < FLOOR_LOWER_LIMIT_MISC) {
                obj_mark_for_deletion(o);
            } else {
                //o->oPosY = o->oFloorHeight;
            }
        } else {
            cur_obj_update_floor_height();

            if (absf(o->oPosY - o->oFloorHeight) > 250.0f) {
                cur_obj_set_model(MODEL_YELLOW_COIN_NO_SHADOW);
            }
        }
    } else {
        if (bhv_coin_sparkles_init()) {
            o->parentObj->oCoinRespawnBits |= (1 << o->oBehParams2ndByte);
        }
        o->oAnimState++;
    }
    if (o->parentObj->oAction == COIN_FORMATION_ACT_DEACTIVATE) {
        obj_mark_for_deletion(o);
    }
}

void spawn_coin_in_formation(s32 index, s32 shape) {
    Vec3i pos = { 0, 0, 0 };
    s32 spawnCoin    = TRUE;
    s32 snapToGround = TRUE;

    switch (shape & COIN_FORMATION_BP_SHAPE_MASK) {
        case COIN_FORMATION_BP_SHAPE_HORIZONTAL_LINE:
            pos[2] = 160 * (index - 2);
            if (index > 4) spawnCoin = FALSE;
            break;
        case COIN_FORMATION_BP_SHAPE_VERTICAL_LINE:
            snapToGround = FALSE;
            pos[1] = index << 7;
            if (index > 4) spawnCoin = FALSE;
            break;
        case COIN_FORMATION_BP_SHAPE_HORIZONTAL_RING:
            pos[0] = sins(index << 13) * 300.0f;
            pos[2] = coss(index << 13) * 300.0f;
            break;
        case COIN_FORMATION_BP_SHAPE_VERTICAL_RING:
            snapToGround = FALSE;
            pos[0] = coss(index << 13) * 200.0f;
            pos[1] = sins(index << 13) * 200.0f + 256.0f;
            break;
        case COIN_FORMATION_BP_SHAPE_ARROW:
            pos[0] = sCoinArrowPositions[index][0];
            pos[2] = sCoinArrowPositions[index][1];
            break;
        case 5:
            pos[0] = cock_hard_resevoir[index][0];
            pos[2] = cock_hard_resevoir[index][1];
            break;
    }

    if (shape & COIN_FORMATION_BP_FLYING) {
        snapToGround = FALSE;
    }

    if (spawnCoin) {
        struct Object *newCoin =
            spawn_object_relative(index, pos[0], pos[1], pos[2], o,
                                  MODEL_YELLOW_COIN, bhvCoinFormationSpawnedCoin);
        newCoin->oCoinSnapToGround = snapToGround;
    }
}

void bhv_coin_formation_init(void) {
    o->oCoinRespawnBits = GET_BPARAM3(o->oBehParams);
}

void bhv_coin_formation_loop(void) {
    s32 bitIndex;

    switch (o->oAction) {
        case COIN_FORMATION_ACT_INACTIVE:
            if (o->oDistanceToMario < COIN_FORMATION_DISTANCE) {
                for (bitIndex = 0; bitIndex < 8; bitIndex++) {
                    if (!(o->oCoinRespawnBits & (1 << bitIndex))) {
                        spawn_coin_in_formation(bitIndex, o->oBehParams2ndByte);
                    }
                }
                o->oAction = COIN_FORMATION_ACT_ACTIVE;
            }
            break;
        case COIN_FORMATION_ACT_ACTIVE:
            if (o->oDistanceToMario > (COIN_FORMATION_DISTANCE + 100.0f)) {
                o->oAction = COIN_FORMATION_ACT_DEACTIVATE;
            }
            break;
        case COIN_FORMATION_ACT_DEACTIVATE:
            o->oAction = COIN_FORMATION_ACT_INACTIVE;
            break;
    }

    // Casting to u8 doesn't seem to match
    set_object_respawn_info_bits(o, o->oCoinRespawnBits & RESPAWN_INFO_DONT_RESPAWN);
}


void coin_inside_boo_act_carried(void) {
    struct Object *parent = o->parentObj;

    cur_obj_become_intangible();


    obj_copy_pos(o, parent);

    if (parent->oImbue == IMBUE_STAR) {
        o->oFaceAngleYaw += 0x800;
        o->oPosY += 30.f;
    } else {
        o->oFaceAngleYaw = parent->oFaceAngleYaw;
    }
    if (o->parentObj->behavior == segmented_to_virtual(bhvBalconyBigBoo)) {
        o->oPosY += 150.f;
    }

    if (parent->oBooDeathStatus == BOO_DEATH_STATUS_DYING) {
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

ObjActionFunc sCoinInsideBooActions[] = {
    coin_inside_boo_act_carried,
    //coin_inside_boo_act_dropped
};

struct imbue_model imbue_model_data[] = {
    /* IMBUE_NONE */ {MODEL_NONE, FALSE, 1.f},
    /* IMBUE_STAR */ {MODEL_STAR, FALSE, 0.6f},
    /* IMBUE_THREE_COINS */ {MODEL_YELLOW_COIN, TRUE, 1.f},
    /* IMBUE_ONE_COIN */ {MODEL_YELLOW_COIN, TRUE, 1.f},
    /* IMBUE_EIGHT_COINS */ {MODEL_YELLOW_COIN, TRUE, 1.f},
    /* IMBUE_BLUE_COIN */ {MODEL_BLUE_COIN, TRUE, 0.7f},
    /* IMBUE_RED_SWITCH */ {MODEL_MAKER_BUTTON, FALSE, 0.4f},
    /* IMBUE_BLUE_SWITCH */ {MODEL_MAKER_BUTTON, FALSE, 0.4f},
    /* IMBUE_RED_COIN */ {MODEL_RED_COIN, TRUE, 1.f},
};

void bhv_coin_inside_boo_init(void) {
    s32 imbue = o->parentObj->oImbue;
    cur_obj_set_model(imbue_model_data[imbue].model);
    if (imbue_model_data[imbue].billboarded) o->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
    cur_obj_scale(imbue_model_data[imbue].scale);

    if (imbue == IMBUE_BLUE_SWITCH) {
        o->oAnimState = 1;
    }
}

void bhv_coin_inside_boo_loop(void) {
    s32 imbue = o->parentObj->oImbue;
    if ((imbue != IMBUE_RED_SWITCH) && (imbue != IMBUE_BLUE_SWITCH)) {
        o->oAnimState += 1;
    }
    cur_obj_call_action_function(sCoinInsideBooActions);
}

void bhv_coin_sparkles_loop(void) {
    cur_obj_scale(0.6f);
}

void bhv_golden_coin_sparkles_loop(void) {
    struct Object *sparkleObj = spawn_object(o, MODEL_SPARKLES, bhvCoinSparkles);
    sparkleObj->oPosX += random_float() * 30.0f - 15.0f;
    sparkleObj->oPosZ += random_float() * 30.0f - 15.0f;
}
