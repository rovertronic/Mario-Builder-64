// floating_platform.inc.c

f32 floating_platform_find_home_y(void) {
    struct Surface *floor;
    f32 waterLevel  = cmm_get_water_level(o->oPosX, o->oPosY, o->oPosZ);
    f32 floorHeight = find_floor(o->oPosX, o->oPosY, o->oPosZ, &floor);

    if (waterLevel > floorHeight + o->oFloatingPlatformHeightOffset) {
        o->oFloatingPlatformIsOnFloor = FALSE;
        return (waterLevel + o->oFloatingPlatformHeightOffset);
    } else {
        o->oFloatingPlatformIsOnFloor = TRUE;
        return (floorHeight + o->oFloatingPlatformHeightOffset);
    }
}

void floating_platform_act_move_to_home(void) {
    if (gMarioPlatform == o) {
        f32 dx = gMarioObject->header.gfx.pos[0] - o->oPosX;
        f32 dz = gMarioObject->header.gfx.pos[2] - o->oPosZ;
        f32 cy = coss(-o->oMoveAngleYaw);
        f32 sy = sins(-o->oMoveAngleYaw);
        o->oFaceAnglePitch = o->oFaceAnglePitch + ((dz * cy) + (dx * sy / o->oBehParams2ndByte));
        o->oFaceAngleRoll = o->oFaceAngleRoll - ((dx * cy) + (dz * sy / o->oBehParams2ndByte));
        o->oVelY -= 1.0f;
        if (o->oVelY < 0.0f) {
            o->oVelY = 0.0f;
        }

        o->oFloatingPlatformMarioWeightWobbleOffset += o->oVelY;
        if (o->oFloatingPlatformMarioWeightWobbleOffset > 90.0f) {
            o->oFloatingPlatformMarioWeightWobbleOffset = 90.0f;
        }
    } else {
        o->oFaceAnglePitch /= 1.1;
        o->oFaceAngleRoll /= 1.1;
        o->oFloatingPlatformMarioWeightWobbleOffset -= 5.0f;

        o->oVelY = 10.0f;

        if (o->oFloatingPlatformMarioWeightWobbleOffset < 0.0f) {
            o->oFloatingPlatformMarioWeightWobbleOffset = 0.0f;
        }
    }

    o->oPosY = o->oHomeY - 64.0f - o->oFloatingPlatformMarioWeightWobbleOffset
               + sins(o->oFloatingPlatformWaterSurfaceWobbleOffset * 0x800) * 10.0f;

    o->oFloatingPlatformWaterSurfaceWobbleOffset++;

    if (o->oFloatingPlatformWaterSurfaceWobbleOffset == 32) {
        o->oFloatingPlatformWaterSurfaceWobbleOffset = 0;
    }

    o->oFaceAnglePitch = 0;
    o->oFaceAngleRoll = 0;
    //vetoed because this apparently actually sucks cock and balls
}

void bhv_floating_platform_loop(void) {
    if (o->oHealth != 5) {//init
        o->oHealth = 5;
        obj_scale(o,o->oBehParams2ndByte);
    }

    o->oHomeY = floating_platform_find_home_y();

    // o->oAction = o->oFloatingPlatformIsOnFloor;
    if (o->oFloatingPlatformIsOnFloor) {
        o->oPosY = o->oHomeY;
    } else {
        floating_platform_act_move_to_home();
    }

    //LOD
    o->header.gfx.sharedChild = gLoadedGraphNodes[0xFE];
    if (o->oDistanceToMario > 5000) {
        //far
        o->header.gfx.sharedChild = gLoadedGraphNodes[0xF9];
        }
}
