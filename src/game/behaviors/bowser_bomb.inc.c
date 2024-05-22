// bowser_bomb.inc.c

f32 bbomb_floating_platform_find_home_y(void) {
    struct Surface *sp24;
    f32 sp20;
    f32 sp1C;

    sp20 = cmm_get_water_level(o->oPosX, o->oPosY, o->oPosZ);
    sp1C = find_floor(o->oPosX, o->oPosY, o->oPosZ, &sp24);
    if (sp20 > sp1C) {
        return sp20;
    } else {
        return sp1C;
    }
}

void bhv_bowser_bomb_loop(void) {
    if (obj_check_if_collided_with_object(o, gMarioObject) == TRUE) {
        o->oInteractStatus &= ~INT_STATUS_INTERACTED;
        spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
        create_sound_spawner(SOUND_GENERAL_BOWSER_BOMB_EXPLOSION);
        set_camera_shake_from_point(SHAKE_POS_LARGE, o->oPosX, o->oPosY, o->oPosZ);
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }

    if (o->oInteractStatus & INT_STATUS_HIT_MINE) {
        spawn_object(o, MODEL_MAKER_BFLAMES, bhvBowserBombExplosion);
        create_sound_spawner(SOUND_GENERAL_BOWSER_BOMB_EXPLOSION);
        set_camera_shake_from_point(SHAKE_POS_LARGE, o->oPosX, o->oPosY, o->oPosZ);
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }

    if (o->oBehParams2ndByte == 1) {
        o->oHomeY = bbomb_floating_platform_find_home_y();
        o->oPosY = o->oHomeY + sins(o->oTimer * 0x800) * 10.0f;

        //CHASE MARIO CUZ UR EVIL
            if (cur_obj_lateral_dist_from_mario_to_home() > 2000.0f) {
                o->oAngleToMario = cur_obj_angle_to_home();
                o->oForwardVel = 5.0f;
            } else {
                o->oAngleToMario = obj_angle_to_object(o, gMarioObject);
                o->oForwardVel = 20.0f;
                }

            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x400);
            
        }
}

void bhv_bowser_bomb_explosion_loop(void) {
    cur_obj_scale((f32) o->oTimer / 14.0f * 9.0f + 1.0f);

    if ((o->oTimer % 4 == 0) && (o->oTimer < 20)) {
        struct Object *mineSmoke = spawn_object(o, MODEL_BOWSER_SMOKE, bhvBowserBombSmoke);
        mineSmoke->oPosX += random_float() * 600.0f - 400.0f;
        mineSmoke->oPosZ += random_float() * 600.0f - 400.0f;
        mineSmoke->oVelY += random_float() * 10.0f;
    }

    if (o->oTimer % 2 == 0) {
        o->oAnimState++;
    }

    if (o->oTimer == 28) {
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

void bhv_bowser_bomb_smoke_loop(void) {
    cur_obj_scale((f32) o->oTimer / 14.0f * 9.0 + 1.0);

    if (o->oTimer % 2 == 0) {
        o->oAnimState++;
    }

    o->oOpacity -= 10;

    if (o->oOpacity < 10) {
        o->oOpacity = 0;
    }

    o->oPosY += o->oVelY;

    if (o->oTimer == 28) {
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}
