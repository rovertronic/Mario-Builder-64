extern const Collision conveyor_collision[];
extern const Collision conveyor_half_collision[];
extern const Collision conveyor_dslope_collision[];
extern const Collision conveyor_slope_collision[];
extern u8 mb64_play_onoff;

void bhv_conveyor_init(void) {
    s32 shape = o->oBehParams2ndByte & 0x3;
    o->oExtraVariable1 = 0;
    if (shape == 1) {
        cur_obj_set_model(MODEL_MAKER_CONVEYOR);
        o->collisionData = segmented_to_virtual(conveyor_collision);
    } else if (shape == 2) {
        cur_obj_set_model(MODEL_MAKER_CONVEYOR_SLOPE);
        o->collisionData = segmented_to_virtual(conveyor_slope_collision);
        o->oExtraVariable1 = 1;
    } else if (shape == 3) {
        cur_obj_set_model(MODEL_MAKER_CONVEYOR_DSLOPE);
        o->collisionData = segmented_to_virtual(conveyor_dslope_collision);
        o->oExtraVariable1 = -1;
    } else {
        o->collisionData = segmented_to_virtual(conveyor_half_collision);
    }
    o->oAnimState = o->oBehParams2ndByte >> 2;
}

void bhv_conveyor_loop(void) {
    if (o->oAnimState > 0) {
        if (o->oAnimState != (mb64_play_onoff + 1)) {
            o->oAnimState = (mb64_play_onoff + 1);
            o->oFaceAngleYaw += 0x8000;
            o->oExtraVariable1 *= -1;

            s32 shape = o->oBehParams2ndByte & 0x3;
            if (shape < 2) return;
            s32 targetModel = MODEL_MAKER_CONVEYOR_SLOPE;
            const void *targetCol = conveyor_slope_collision;
            if ((shape == 2 && mb64_play_onoff) || (shape == 3 && !mb64_play_onoff)) {
                targetModel = MODEL_MAKER_CONVEYOR_DSLOPE;
                targetCol = conveyor_dslope_collision;
            }
            cur_obj_set_model(targetModel);
            o->collisionData = segmented_to_virtual(targetCol);
        }
    }
}
