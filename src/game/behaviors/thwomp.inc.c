// thwomp.inc.c
#define oHomeY2 oHomeX

void grindel_thwomp_act_on_ground(void) {
    o->oFloorHeight = find_floor_height_short(o->oPosX, o->oPosY+30.f, o->oPosZ);
    if (ABS(o->oPosY - o->oFloorHeight) < 30.0f) {
        o->oPosY = o->oFloorHeight;
    }

    if (o->oTimer > 25) {
        o->oAction = GRINDEL_THWOMP_ACT_RISING;
    }
}

void grindel_thwomp_act_falling(void) {
    o->oThwompCrushHandler->oTimer = 0;
    o->oThwompCrushHandler->oPosY = o->oPosY - 50.f;
    if (o->oVelY > -80.0f) { //terminal velocity
        o->oVelY += -4.0f;
    }
    o->oPosY += o->oVelY;
    o->oFloorHeight = find_floor_height_short(o->oPosX, o->oPosY+30.f, o->oPosZ);
    if (o->oPosY < o->oFloorHeight) {
        o->oPosY = o->oFloorHeight;
        o->oVelY = 0.0f;
        o->oAction = GRINDEL_THWOMP_ACT_LAND;
    }
}

void grindel_thwomp_act_land(void) {
    o->oFloorHeight = find_floor_short(o->oPosX, o->oPosY+30.f, o->oPosZ, &o->oFloor);
    if (ABS(o->oPosY - o->oFloorHeight) < 30.0f) {
        o->oPosY = o->oFloorHeight;
    }
    o->oThwompCrushHandler->oPosY = o->oPosY - 50.f;
    if (o->oTimer == 0 && o->oDistanceToMario < 3000.0f) {
        cur_obj_shake_screen(SHAKE_POS_SMALL);
        cur_obj_play_sound_2(SOUND_OBJ_THWOMP);
    }
    if (o->oTimer >= 10) {
        o->oAction = GRINDEL_THWOMP_ACT_ON_GROUND;
    }
    o->oFloorType = o->oFloor->type;
    if (cur_obj_die_if_on_death_barrier(MB64_STAR_HEIGHT)) {
        o->prevObj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

void grindel_thwomp_act_floating(void) {
    if (o->oTimer > 25) {
        o->oAction = GRINDEL_THWOMP_ACT_FALLING;
        o->oThwompCrushHandler = spawn_object(o,MODEL_NONE,bhvCrushHandler);
        o->oThwompCrushHandler->hitboxRadius = 200.f;
        o->oThwompCrushHandler->hitboxHeight = 100.f;
    }
}

void grindel_thwomp_act_rising(void) {
    if (o->oPosY > o->oHomeY) {
        o->oAction = GRINDEL_THWOMP_ACT_FLOATING;
        o->oPosY += 5.0f;
    } else {
        o->oPosY += 10.0f;
    }
}

ObjActionFunc sGrindelThwompActions[] = {
    grindel_thwomp_act_rising,
    grindel_thwomp_act_floating,
    grindel_thwomp_act_falling,
    grindel_thwomp_act_land,
    grindel_thwomp_act_on_ground
};

void bhv_grindel_thwomp_init(void) {
    add_obj_to_physics_list(o);
    if (cur_obj_has_model(MODEL_MAKER_GRINDEL)) {
        o->oFaceAngleYaw += 0x4000;
        o->oMoveAngleYaw += 0x4000;
    }
    o->prevObj = spawn_object(o, MODEL_NONE, bhvGrindelThwompCol);
    o->prevObj->collisionData = o->collisionData;
    vec3_copy(o->prevObj->header.gfx.scale, o->header.gfx.scale);
    o->header.gfx.angle[1] = o->oFaceAngleYaw;
}

void bhv_grindel_thwomp_loop(void) {
    cur_obj_call_action_function(sGrindelThwompActions);

    Vec3f oldPos;
    vec3f_copy(oldPos, &o->prevObj->oPosVec);
    vec3f_copy(&o->prevObj->oPosVec,&o->oPosVec);
    vec3f_copy(&o->header.gfx.pos,oldPos);
}

// void bhv_lava_spewer_loop(void) {

//     if (o->oTimer > (o->oExtraVariable1-20) && o->oAction == 0) {
//         cur_obj_shake(o);
//         }

//     //what the fuck is this incoherent gopher scrawling??!
//     if (o->oTimer > o->oExtraVariable1 && o->oAction == 0) {
//         o->oTimer = 0;
//         o->oPosY = o->oHomeY;
//         cur_obj_play_sound_2(SOUND_GENERAL_VOLCANO_EXPLOSION);
//         o->oAction = 1;
//         }
        
//     if (o->oAction == 1) {
//         o->oPosY += o->oVelY;
//         cur_obj_shake_screen(SHAKE_POS_BOWLING_BALL);

//         if (o->oPosY > o->oHomeY+(250.0f*o->oBehParams2ndByte)) {
//             o->oVelY = 2;
//             o->oAction = 2;
//             o->oTimer = 0;
//             }
//             else
//             {
//             if (o->oVelY < 30.0f) {
//                 o->oVelY += 4;
//                 }
//             }
//         }
//     if (o->oAction == 2) {
//         o->oPosY += o->oVelY;

//         if (o->oPosY > o->oHomeY+(250.0f*o->oBehParams2ndByte)) {
//             o->oVelY -= 2;
//             }
//             else
//             {
//             o->oVelY += 2;
//             }

//         if (o->oTimer > 90) {
//             o->oTimer = 0;
//             o->oAction = 3;
//             }
//         }
//     if (o->oAction == 3) {
//         o->oVelY -= 1;
//         o->oPosY += o->oVelY;

//         if (o->oPosY < o->oHomeY) {
//             o->oPosY = o->oHomeY-30.0f;
//             o->oAction = 0;
//             o->oTimer = 0;
//             o->oVelY = 0;
//             o->oExtraVariable1 = random_float() * 40.0f + 60.0f;
//             }
//         }
// }
