// swing_platform.inc.c

void bhv_swing_platform_init(void) {
    o->oVelY = 0x1000;
}

void bhv_swing_platform_update(void) {
    if (o->oFaceAngleRoll < 0) {
        o->oVelX += 4.0f;
    } else {
        o->oVelX -= 4.0f;
    }

    o->oVelY += o->oVelX;
    o->oFaceAngleRoll = o->oVelY;
}
