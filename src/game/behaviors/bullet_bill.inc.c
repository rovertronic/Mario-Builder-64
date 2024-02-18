// bullet_bill.inc.c

void bhv_white_puff_smoke_init(void) {
    cur_obj_scale(random_float() * 2 + 2.0);
}

static struct ObjectHitbox sBulletBillHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 250,
    /* damageOrCoinValue: */ 2,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 200,
    /* height:            */ 400,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

void bhv_bullet_bill_init(void) {
    o->oBulletBillInitialMoveYaw = o->oMoveAngleYaw;
}

void bullet_bill_act_0(void) {
    cur_obj_become_intangible();
    cur_obj_hide();
    o->oForwardVel = 0.0f;
    o->oMoveAngleYaw = o->oBulletBillInitialMoveYaw;
    o->oFaceAnglePitch = 0;
    o->oFaceAngleRoll = 0;
    o->oMoveFlags = OBJ_MOVE_NONE;
    cur_obj_set_pos_to_home();
    o->oAction = 1;
}

void bullet_bill_act_1(void) {
    s16 sp1E = abs_angle_diff(o->oAngleToMario, o->oMoveAngleYaw);
    if (sp1E < 0x2000 && 400.0f < o->oDistanceToMario && o->oDistanceToMario < 1500.0f) {
        cur_obj_unhide();
        o->oAction = 2;
    }
}

void bullet_bill_act_2(void) {
    if (o->oTimer < 40) {
        o->oForwardVel = 3.0f;
    } else if (o->oTimer < 50) {
        if (o->oTimer % 2) {
            o->oForwardVel = 3.0f;
        } else {
            o->oForwardVel = -3.0f;
        }
    } else {
        if (o->oTimer == 50) {
            cur_obj_become_tangible();
        }
        if (o->oTimer > 70) {
            cur_obj_update_floor_and_walls();
        }

        spawn_object(o, MODEL_SMOKE, bhvWhitePuffSmoke);
        o->oForwardVel = 30.0f;

        if (o->oDistanceToMario > 300.0f) {
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x100);
        }

        if (o->oTimer == 50) {
            cur_obj_play_sound_2(SOUND_OBJ_POUNDING_CANNON);
            cur_obj_shake_screen(SHAKE_POS_SMALL);
        }

        if (o->oTimer > 150) {
            o->oAction = 3;
            spawn_mist_particles();
        }

        if (o->oMoveFlags & OBJ_MOVE_HIT_WALL) {
            o->oAction = 4;
        }
    }
}

void bullet_bill_act_3(void) {
    o->oAction = 0;
}

void bullet_bill_act_4(void) {
    if (o->oTimer == 0) {
        cur_obj_become_intangible();
        cur_obj_hide();
        struct Object *explosion = spawn_object(o, MODEL_EXPLOSION, bhvExplosionFake);
        explosion->oGraphYOffset += 100.0f;
    }

    if (o->oTimer > 90) {
        o->oAction = 0;
        cur_obj_unhide();
    }
}

ObjActionFunc sBulletBillActions[] = {
    bullet_bill_act_0,
    bullet_bill_act_1,
    bullet_bill_act_2,
    bullet_bill_act_3,
    bullet_bill_act_4,
};

void bhv_bullet_bill_loop(void) {
    cur_obj_call_action_function(sBulletBillActions);
    obj_set_hitbox(o, &sBulletBillHitbox);
    if (cur_obj_check_interacted() || obj_attack_collided_from_other_object(o)) {
        cur_obj_become_intangible();
        o->oAction = 4;
    }
}