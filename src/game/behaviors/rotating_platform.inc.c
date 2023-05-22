// rotating_platform.inc.c

#include "levels/wf/header.h"
#include "levels/wdw/header.h"

struct WFRotatingPlatformData {
    s16 unused;
    s16 scale;
    const Collision *collisionData;
    s16 collisionDistance;
};

struct WFRotatingPlatformData sWFRotatingPlatformData[] = {
    { 0, 100, wf_seg7_collision_rotating_platform, 2000 },
    { 0, 150, wdw_seg7_collision_rotating_platform, 1000 }
};

void bhv_wf_rotating_wooden_platform_loop(void) {
    if (o->oAction == 0) {
        o->oAngleVelYaw = 0;
        if (o->oTimer > 60) {
            o->oAction++;
        }
    } else {
        o->oAngleVelYaw = 0x100;
        if (o->oTimer > 126) {
            o->oAction = ROTATING_PLATFORM_ACT_STOPPED;
        }
        cur_obj_play_sound_1(SOUND_ENV_ELEVATOR2);
    }
    cur_obj_rotate_face_angle_using_vel();
}

void bhv_rotating_platform_loop(void) {
    if (o->oBehParams2ndByte < 10) {
        o->oAngleVelYaw = o->oBehParams2ndByte * 0x100;
    }
    else
    {
        o->oAngleVelYaw = (o->oBehParams2ndByte-10) * -0x100;
    }
    o->oFaceAngleYaw += o->oAngleVelYaw;

    if (o->oAction == 0) {
        o->oAction = 1;
        o->oVelY = 6.0f;
        o->oHomeY = o->oPosY;
    }

    o->oPosY += o->oVelY;
    if (o->oPosY > o->oHomeY) {
        o->oVelY -= .5f;
    }
    else
    {
        o->oVelY += .5f;
    }

}
