static void bhv_onoffswitch_falling(void) {
    o->oVelY -= 4.f;
    o->oPosY += o->oVelY;

    f32 floorHeight = find_floor_short(o->oPosX, o->oPosY + 50.f, o->oPosZ, &o->oFloor);
    if (o->oPosY < floorHeight) {
        o->oPosY = floorHeight;
        o->oVelY = 0.f;
        o->oExtraVariable1 = 0;
        if (o->oFloor->type == SURFACE_DEATH_PLANE) {
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        } else {
            remove_object_from_physics_list(o);
        }
    }
}

void bhv_onoffswitch(void) {
    if (o->oExtraVariable1) {
        bhv_onoffswitch_falling();
    }
    if (o->header.gfx.scale[1] > 0.11f) {
        load_object_collision_model();
    }
    switch (o->oAction) {
        case 0: // init
            o->oAnimState = o->oBehParams2ndByte;
            o->oAction = 1;
            if ((o->oAnimState == 0) && (!mb64_play_onoff)) {
                o->header.gfx.scale[1] = 0.1f;
                o->oAction = 2;
            } else if ((o->oAnimState != 0) && (mb64_play_onoff)) {
                o->header.gfx.scale[1] = 0.1f;
                o->oAction = 2;
            }
            break;
        case 1: // switch up
            o->header.gfx.scale[1] = approach_f32_symmetric(o->header.gfx.scale[1], 1.0f, 0.1f);
            if (gMarioPlatform == o && !(gMarioState->action & MARIO_NO_PURPLE_SWITCH)) {
                cur_obj_play_sound_2(SOUND_GENERAL2_BUTTON_PRESS);
                mb64_play_onoff = o->oBehParams2ndByte;
            }
            if ((o->oAnimState == 0) && (!mb64_play_onoff)) {
                o->oAction = 2;
            } else if ((o->oAnimState != 0) && (mb64_play_onoff)) {
                o->oAction = 2;
            }
            break;
        case 2: // switch down
            o->header.gfx.scale[1] = approach_f32_symmetric(o->header.gfx.scale[1], 0.1f, 0.1f);
            if (o->oBehParams2ndByte == 0) {
                if (mb64_play_onoff) {
                    o->oAction = 1;
                }
            } else { // Blue
                if (!mb64_play_onoff) {
                    o->oAction = 1;
                }
            }
            break;
    }
}

void bhv_onoffblock_init(void) {
    if (o->oBehParams2ndByte == 0) {
        o->oAnimState = 0;
    } else {
        o->oAnimState = 1;
    }
}

void bhv_onoffblock(void) {
    if (o->oBehParams2ndByte == 0) {
        if (mb64_play_onoff) {
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_BLOCK_OFF];
        } else {
            load_object_collision_model();
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_BLOCK_ON];
        }
    } else {
        if (mb64_play_onoff) {
            load_object_collision_model();
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_BLOCK_ON];
        } else {
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_BLOCK_OFF];
        }
    }
}
