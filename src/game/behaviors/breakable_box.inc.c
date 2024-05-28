// breakable_box.inc.c

//200 -> 256
//128% increase

struct ObjectHitbox sBreakableBoxHitbox = {
    /* interactType:      */ INTERACT_BREAKABLE,
    /* downOffset:        */  20,
    /* damageOrCoinValue: */   0,
    /* health:            */   1,
    /* numLootCoins:      */   0,
    /* radius:            */ /*150,*/ 192,
    /* height:            */ /*200,*/ 256,
    /* hurtboxRadius:     */ /*150,*/ 192,
    /* hurtboxHeight:     */ /*200,*/ 256,
};

struct ObjectHitbox sBreakableBoxRfHitbox = {
    /* interactType:      */ INTERACT_BREAKABLE,
    /* downOffset:        */  20,
    /* damageOrCoinValue: */   0,
    /* health:            */   1,
    /* numLootCoins:      */   0,
    /* radius:            */ /*150,*/ 192,
    /* height:            */ /*200,*/ 300,
    /* hurtboxRadius:     */ /*150,*/ 192,
    /* hurtboxHeight:     */ /*200,*/ 300,
};

void breakable_box_init(void) {
    o->oHiddenObjectSwitchObj = NULL;
    o->oAnimState = BREAKABLE_BOX_ANIM_STATE_CORK_BOX;
    o->oNumLootCoins = 3;
    // switch (o->oBehParams2ndByte) {
    //     case BREAKABLE_BOX_BP_NO_COINS: o->oNumLootCoins = 0; break;
    //     case BREAKABLE_BOX_BP_3_COINS:  o->oNumLootCoins = 3; break;
    //     case BREAKABLE_BOX_BP_5_COINS:  o->oNumLootCoins = 5; break;
    //     case BREAKABLE_BOX_BP_LARGE:    cur_obj_scale(1.5f);  break;
    // }
}

void hidden_breakable_box_actions(void) {
    obj_set_hitbox(o, &sBreakableBoxHitbox);
    cur_obj_set_model(MODEL_BREAKABLE_BOX);
    switch (o->oAction) {
        case BREAKABLE_BOX_ACT_HIDDEN:
            cur_obj_disable_rendering();
            cur_obj_become_intangible();
            if (o->oTimer == 0) {
                breakable_box_init();
            }

            if (gMarioState->hiddenBoxTimer > 0) {
                o->oAction = BREAKABLE_BOX_ACT_ACTIVE;
                cur_obj_enable_rendering();
                cur_obj_unhide();
            }
            break;
        case BREAKABLE_BOX_ACT_ACTIVE:
            cur_obj_become_tangible();

            if (gMarioState->hiddenBoxTimer == 0) o->oAction = BREAKABLE_BOX_ACT_HIDDEN;
            else if (gMarioState->hiddenBoxTimer < 40) {
                if (gMarioState->hiddenBoxTimer & 1) {
                    cur_obj_hide();
                } else {
                    cur_obj_unhide();
                }
            }
            if (cur_obj_was_attacked_or_ground_pounded()) {
                spawn_mist_particles();
                spawn_triangle_break_particles(30, MODEL_DIRT_ANIMATION, 3.0f, TINY_DIRT_PARTICLE_ANIM_STATE_YELLOW);
                o->oAction = BREAKABLE_BOX_ACT_BROKEN;
                cur_obj_play_sound_2(SOUND_GENERAL_BREAK_BOX);
            }
            load_object_collision_model();
            break;
        case BREAKABLE_BOX_ACT_BROKEN:
            cur_obj_become_intangible();
            cur_obj_disable_rendering();
            o->oInteractStatus = INT_STATUS_NONE;
            if (gMarioState->hiddenBoxTimer == 0) {
                o->oAction = BREAKABLE_BOX_ACT_HIDDEN;
            }
            break;
    }
}

void bhv_hidden_object_loop(void) {
    hidden_breakable_box_actions();
}

void bhv_breakable_box_loop(void) {
    obj_set_hitbox(o, &sBreakableBoxHitbox);
    if (o->oTimer == 0) {
        breakable_box_init();
        o->oNumLootCoins = 0;
    }
    if (cur_obj_was_attacked_or_ground_pounded()) {
        obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
        create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
        cur_obj_drop_imbued_object(128);
    }
}

s32 cur_obj_was_attacked_not_by_mario(void) {
    s32 attacked = FALSE;

    if ((o->oInteractStatus & INT_STATUS_INTERACTED)
        && (o->oInteractStatus & INT_STATUS_WAS_ATTACKED)
        && (gMarioState->interactObj != o)) {
        attacked = TRUE;
    }

    return attacked;
}

void bhv_breakable_box_rf_loop(void) {
    obj_set_hitbox(o, &sBreakableBoxRfHitbox);
    // doesnt update gfx pos automatically, so that the "shake" can be done without affecting position/collision
    vec3_copy(o->header.gfx.pos, &o->oPosVec);
    vec3_copy(o->header.gfx.angle, &o->oFaceAngleVec);
    if (o->oTimer == 0) {
        breakable_box_init();
        o->oNumLootCoins = 0;
        o->oTimer = 15;
    }
    if (cur_obj_was_attacked_not_by_mario()) {
        obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
        create_sound_spawner(SOUND_OBJ_POUNDING_LOUD);
        cur_obj_drop_imbued_object(128);
    } else if (cur_obj_was_attacked_or_ground_pounded()) {
        if (o->oTimer > 15) {
            create_sound_spawner(SOUND_OBJ_BULLY_METAL);
            o->oTimer = 1;
            o->oIntangibleTimer = -1;
        }
    }

    if (o->oTimer < 10) {
        o->header.gfx.pos[0] += random_float() * 6.f - 3.f;
        o->header.gfx.pos[1] += random_float() * 6.f - 3.f;
        o->header.gfx.pos[2] += random_float() * 6.f - 3.f;
    } else {
        o->oIntangibleTimer = 0;
    }

    if (gMarioState->interactObj == o) {
        gMarioState->interactObj = NULL;
    }

    o->oInteractStatus = INT_STATUS_NONE;
}