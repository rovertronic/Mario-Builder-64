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
    o->oFriction = 0.97f;
    o->oBuoyancy = 1.4f;
    cur_obj_scale(0.4f);
    obj_set_hitbox(o, &sBreakableBoxSmallHitbox);
    o->oAnimState = BREAKABLE_BOX_ANIM_STATE_CORK_BOX;
    o->activeFlags |= ACTIVE_FLAG_DESTRUCTIVE_OBJ_DONT_DESTROY;
}

void small_breakable_box_spawn_dust(void) {
    struct Object *smokeObj = spawn_object(o, MODEL_SMOKE, bhvSmoke);
    smokeObj->oPosX += (s32)(random_float() * 80.0f) - 40;
    smokeObj->oPosZ += (s32)(random_float() * 80.0f) - 40;
}

void small_breakable_box_act_move(void) {
    s16 collisionFlags = object_step();

    obj_attack_collided_from_other_object(o);

    if (collisionFlags == OBJ_COL_FLAG_GROUNDED) {
        cur_obj_play_sound_2(SOUND_GENERAL_SMALL_BOX_LANDING);
    }

    if (collisionFlags & OBJ_COL_FLAG_GROUNDED) {
        if (o->oForwardVel > 20.0f) {
            cur_obj_play_sound_2(SOUND_ENV_SLIDING);
            small_breakable_box_spawn_dust();
        }
    }

    if (collisionFlags & OBJ_COL_FLAG_HIT_WALL) {
        // spawn_mist_particles();
        // spawn_triangle_break_particles(20, MODEL_DIRT_ANIMATION, 0.7f, 3);
        // obj_spawn_yellow_coins(o, 3);
        // create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
        // o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }

    obj_check_floor_death(collisionFlags, sObjFloor);
}

void breakable_box_small_released_loop(void) {
    o->oBreakableBoxSmallFramesSinceReleased++;


}

void breakable_box_small_idle_loop(void) {
    switch (o->oAction) {
        case BREAKABLE_BOX_SMALL_ACT_MOVE:
            small_breakable_box_act_move();
            break;

        case OBJ_ACT_LAVA_DEATH:
            // obj_lava_death();
                o->oPosX = o->oHomeX;
                o->oPosY = o->oHomeY;
                o->oPosZ = o->oHomeZ;
                o->oAction = 0;
            break;

        case OBJ_ACT_DEATH_PLANE_DEATH:
            // o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            // create_respawner(MODEL_BREAKABLE_BOX, bhvBreakableBoxSmall, 3000);
                o->oPosX = o->oHomeX;
                o->oPosY = o->oHomeY;
                o->oPosZ = o->oHomeZ;
                o->oAction = 0;

            break;
    }

    if (o->oBreakableBoxSmallReleased == TRUE) {
        breakable_box_small_released_loop();
    }
}

void breakable_box_small_get_dropped(void) {
    cur_obj_become_tangible();
    cur_obj_enable_rendering();
    cur_obj_get_dropped();
    o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
    o->oHeldState = HELD_FREE;
    o->oBreakableBoxSmallReleased = TRUE;
    o->oBreakableBoxSmallFramesSinceReleased = 0;
}

void breakable_box_small_get_thrown(void) {
    cur_obj_become_tangible();

    cur_obj_enable_rendering();
    o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
    o->oHeldState = HELD_FREE;
    o->oFlags &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
    o->oForwardVel = 40.0f;
    o->oVelY = 20.0f;
    o->oBreakableBoxSmallReleased = TRUE;
    o->oBreakableBoxSmallFramesSinceReleased = 0;
    o->activeFlags &= ~ACTIVE_FLAG_DESTRUCTIVE_OBJ_DONT_DESTROY;
}

void bhv_breakable_box_small_loop(void) {

    o->oForwardVel = 0.0f;
    near_music_box = FALSE;

    if (o->oBehParams2ndByte == 0) {
        if (o->oDistanceToMario < 1000.0f) {
                play_secondary_music(0x0B, 0, 255, 1000);
                o->oPiranhaPlantSleepMusicState = 0;
            } else if ((o->oPiranhaPlantSleepMusicState == 0)&&(o->oHeldState == 0)) {
                o->oPiranhaPlantSleepMusicState++;
                func_80321080(50);
            }
        }

    switch (o->oHeldState) {
        case HELD_FREE:
            breakable_box_small_idle_loop();
            break;

        case HELD_HELD:
            near_music_box = TRUE;
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
