// spindrift.inc.c

struct ObjectHitbox sSpindriftHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 2,
    /* health:            */ 1,
    /* numLootCoins:      */ 3,
    /* radius:            */ 90,
    /* height:            */ 80,
    /* hurtboxRadius:     */ 80,
    /* hurtboxHeight:     */ 70,
};

void bhv_spindrift_loop(void) {
    o->activeFlags |= ACTIVE_FLAG_IGNORE_ENV_BOXES;

    cur_obj_set_hitbox_and_die_if_attacked(&sSpindriftHitbox, SOUND_OBJ_DYING_ENEMY1, 0);
    cur_obj_update_floor_and_walls();
    cur_obj_set_home_if_safe();

    approach_f32_symmetric_bool(&o->oForwardVel, 4.0f, 1.0f);
    switch (o->oAction) {
        case 0:
            o->oMoveAngleYaw += 0x400;
            if (o->oDistanceToMario < 1500.0f) {
                o->oAction = 1;
            }
            break;
        case 1:
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x400);
            if (o->oDistanceToMario > 2000.0f) {
                o->oAction = 0;
            }
            break;

    }

    cur_obj_move_standard(-60);
    cur_obj_die_if_on_death_barrier(MB64_STAR_HEIGHT);
}
