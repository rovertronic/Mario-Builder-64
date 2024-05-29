// breakable_box.inc.c

struct ObjectHitbox sBreakableBoxSmallHitbox = {
    /* interactType:      */ INTERACT_GRABBABLE,
    /* downOffset:        */ 20,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 1,
    /* numLootCoins:      */ 0,
    /* radius:            */ 150,
    /* height:            */ 250,
    /* hurtboxRadius:     */ 150,
    /* hurtboxHeight:     */ 250,
};

void bhv_breakable_box_small_init(void) {
    o->oGravity = 2.5f;
    o->oFriction = 0.99f;
    o->oBuoyancy = 1.4f;
    cur_obj_scale(0.31f);
    obj_set_hitbox(o, &sBreakableBoxSmallHitbox);
    o->oAnimState = BREAKABLE_BOX_ANIM_STATE_CORK_BOX;
}

void small_breakable_box_spawn_dust(void) {
    struct Object *smokeObj = spawn_object(o, MODEL_SMOKE, bhvSmoke);
    smokeObj->oPosX += (s32)(random_float() * 80.0f) - 40;
    smokeObj->oPosZ += (s32)(random_float() * 80.0f) - 40;
}

void small_breakable_box_act_move(void) {
    s16 collisionFlags = object_step();

    s32 class = get_floor_class(o->oFloorType);
    if (class == SURFACE_CLASS_VERY_SLIPPERY) o->oFriction = 0.999f;
    else o->oFriction = 0.99f;

    if (o->oForwardVel > 5.f) {
        obj_attack_collided_from_other_object(o);
    }

    if (collisionFlags == OBJ_COL_FLAG_GROUNDED) {
        cur_obj_play_sound_2(SOUND_GENERAL_SMALL_BOX_LANDING);
    }

    if (collisionFlags & OBJ_COL_FLAG_GROUNDED) {
        if (o->oForwardVel > 20.0f) {
            cur_obj_play_sound_2(SOUND_ENV_SLIDING);
            small_breakable_box_spawn_dust();
        }
    }

    if ((collisionFlags & OBJ_COL_FLAG_HIT_WALL) && (ABS(o->oForwardVel) > 1.0f)) {
        spawn_mist_particles();
        spawn_triangle_break_particles(10, MODEL_DIRT_ANIMATION, 0.7f, 3);
        if (!GET_BPARAM3(o->oBehParams)) {
            obj_spawn_yellow_coins(o, 3);
        }
        create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
        o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
        o->oBreakableBoxSmallReleased = TRUE;
        o->oBreakableBoxSmallFramesSinceReleased = 900 - (5 * 30); // respawn after 5 seconds
        o->oIntangibleTimer = -1;
        o->oAction = 1; // empty action
        SET_BPARAM3(o->oBehParams, 1);
    }

    obj_check_floor_death(collisionFlags, sObjFloor);
}

void breakable_box_small_respawn(void) {
    struct Object *newbox = spawn_object(o->parentObj, MODEL_BREAKABLE_BOX, bhvBreakableBoxSmall);
    newbox->oPosX = o->oHomeX;
    newbox->oPosY = o->oHomeY;
    newbox->oPosZ = o->oHomeZ;
    newbox->oMoveAngleYaw = 0;
    newbox->oBehParams = o->oBehParams;
    spawn_mist_at_obj(newbox);
    o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
}

void breakable_box_small_released_loop(void) {
    o->oBreakableBoxSmallFramesSinceReleased++;

    // Begin flashing
    if (o->oBreakableBoxSmallFramesSinceReleased > 810 && o->oAction == 0) {
        COND_BIT((o->oBreakableBoxSmallFramesSinceReleased & 0x1), o->header.gfx.node.flags, GRAPH_RENDER_INVISIBLE);
    }

    // Despawn, and create a corkbox respawner
    if (o->oBreakableBoxSmallFramesSinceReleased > 900) {
        breakable_box_small_respawn();
    }
}

void breakable_box_small_idle_loop(void) {
    switch (o->oAction) {
        case BREAKABLE_BOX_SMALL_ACT_MOVE:
            small_breakable_box_act_move();
            break;

        case OBJ_ACT_LAVA_DEATH:
            if (obj_lava_death()) {
                breakable_box_small_respawn();
            }
            break;

        case OBJ_ACT_DEATH_PLANE_DEATH:
            breakable_box_small_respawn();
            return;
    }

    if (o->oBreakableBoxSmallReleased == TRUE) {
        breakable_box_small_released_loop();
    }
}

void breakable_box_small_get_dropped(void) {
    cur_obj_get_dropped();
    o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
    o->oBreakableBoxSmallReleased = TRUE;
    o->oBreakableBoxSmallFramesSinceReleased = 0;
}

void breakable_box_small_get_thrown(void) {
    cur_obj_become_tangible();

    cur_obj_enable_rendering();
    o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
    o->oHeldState = HELD_FREE;
    o->oForwardVel = 40.0f;
    o->oVelY = 20.0f;
    o->oBreakableBoxSmallReleased = TRUE;
    o->oBreakableBoxSmallFramesSinceReleased = 0;
}

void bhv_breakable_box_small_loop(void) {
    switch (o->oHeldState) {
        case HELD_FREE:
            breakable_box_small_idle_loop();
            break;

        case HELD_HELD:
            cur_obj_disable_rendering();
            cur_obj_become_intangible();
            break;

        case HELD_THROWN:
            breakable_box_small_get_thrown();
            break;

        case HELD_DROPPED:
            breakable_box_small_get_dropped();
            break;
    }

    o->oInteractStatus = INT_STATUS_NONE;
}
