// exclamation_box.inc.c
//sorry that this file is a convoluted cluster fuck

struct ObjectHitbox sExclamationBoxHitbox = {
    .interactType      = INTERACT_BREAKABLE,
    .downOffset        = 5,
    .damageOrCoinValue = 0,
    .health            = 1,
    .numLootCoins      = 0,
    .radius            = 40,
    .height            = 30,
    .hurtboxRadius     = 40,
    .hurtboxHeight     = 30,
};

void bhv_rotating_exclamation_mark_loop(void) {
    if (o->parentObj->oAction != EXCLAMATION_BOX_ACT_OUTLINE) {
        obj_mark_for_deletion(o);
    }
}

void exclamation_box_act_init(void) {
    o->oAction = EXCLAMATION_BOX_ACT_ACTIVE;

    if (mb64_lopt_game == MB64_GAME_VANILLA) {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_VEXCLAMATION_BOX];
    }

    o->oAnimState = mb64_exclamation_box_contents[o->oBehParams2ndByte].animState;


    //u32 stardata = save_file_get_star_flags(gCurrSaveFileNum - 1, gCurrCourseNum-1);
    //struct Object *tempobj;

    /*
    if (o->oBehParams2ndByte < EXCLAMATION_BOX_BP_COINS_1) {
        o->oAnimState = o->oBehParams2ndByte;
#ifdef UNLOCK_ALL
        const u8 tangible = TRUE;
#else
        const u8 tangible = ((save_file_get_flags() & sCapSaveFlags[o->oBehParams2ndByte])
                          || (GET_BPARAM1(o->oBehParams) != EXCLAMATION_BOX_BP1_NEEDS_SWITCH));
#endif
        o->oAction = tangible ? EXCLAMATION_BOX_ACT_ACTIVE : EXCLAMATION_BOX_ACT_OUTLINE;
    } else {
        o->oAnimState = 4;
        o->oAction = EXCLAMATION_BOX_ACT_ACTIVE;
    }*/
}

static s32 sCapSaveFlags[] = {
    SAVE_FLAG_HAVE_WING_CAP,
    SAVE_FLAG_HAVE_METAL_CAP,
    SAVE_FLAG_HAVE_VANISH_CAP,
    SAVE_FLAG_HAVE_YELLOW
};

void exclamation_box_act_outline(void) {
    cur_obj_become_intangible();
    if (o->oTimer == 0) {
        spawn_object(o, MODEL_EXCLAMATION_POINT, bhvRotatingExclamationMark);
        cur_obj_set_model(MODEL_EXCLAMATION_BOX_OUTLINE);
    }
    // if ((save_file_get_flags() & sCapSaveFlags[o->oBehParams2ndByte])
    //  || (GET_BPARAM1(o->oBehParams) != EXCLAMATION_BOX_BP1_NEEDS_SWITCH)) {
        o->oAction = EXCLAMATION_BOX_ACT_ACTIVE;
        cur_obj_set_model(MODEL_EXCLAMATION_BOX);
    // }
}

void exclamation_box_act_active(void) {
    obj_set_hitbox(o, &sExclamationBoxHitbox);
    if (o->oTimer == 0) {
        cur_obj_unhide();
        cur_obj_become_tangible();
        o->oInteractStatus = INT_STATUS_NONE;
        o->oPosY = o->oHomeY;
        o->oGraphYOffset = 0.0f;
    }
    if (cur_obj_was_attacked_or_ground_pounded()) {
        cur_obj_become_intangible();
        o->oExclamationBoxScaleAngle = 0x4000;
        o->oVelY = 30.0f;
        o->oGravity = -8.0f;
        o->oFloorHeight = o->oPosY;
        o->oAction = EXCLAMATION_BOX_ACT_SCALING;
#if ENABLE_RUMBLE
        queue_rumble_data(5, 80);
#endif
    }
    load_object_collision_model();
}

void exclamation_box_act_scaling(void) {
    cur_obj_move_using_fvel_and_gravity();
    if (o->oVelY < 0.0f) {
        o->oVelY = 0.0f;
        o->oGravity = 0.0f;
    }
    o->oGraphYOffset                  = ((-sins(o->oExclamationBoxScaleAngle) + 1.0f) * 26.0f);
    o->oExclamationBoxHorizontalScale = ((-sins(o->oExclamationBoxScaleAngle) + 1.0f) *  0.5f) + 1.0f;
    o->oExclamationBoxVerticalScale   = (( sins(o->oExclamationBoxScaleAngle) + 1.0f) *  0.3f) + 0.0f;
    o->oExclamationBoxScaleAngle += 0x1000;
    obj_scale_xyz(o,
        (o->oExclamationBoxHorizontalScale * 2.0f),
        (o->oExclamationBoxVerticalScale   * 2.0f),
        (o->oExclamationBoxHorizontalScale * 2.0f)
    );
    if (o->oTimer == 7) {
        o->oAction = EXCLAMATION_BOX_ACT_EXPLODE;
    }
}

void exclamation_box_spawn_contents(struct ExclamationBoxContents *contentsList, u8 boxType) {
    struct Object *contentsObj = NULL;
    
    if (o->oImbue != IMBUE_NONE) {
        o->oPosY += 60.f;
        cur_obj_drop_imbued_object(0);
        return;
    }

    if (boxType < 7) { // hardcoded
        struct ExclamationBoxContents *contents = &mb64_exclamation_box_contents[boxType];
        contentsObj = spawn_object(o, contents->model, contents->behavior);
        contentsObj->oVelY = 20.0f;
        contentsObj->oForwardVel = 3.0f;
        contentsObj->oMoveAngleYaw = gMarioObject->oMoveAngleYaw;
        OR_BPARAM1(o->oBehParams, contents->behParams);
        if (contents->model == MODEL_STAR) {
            o->oFlags |= OBJ_FLAG_PERSISTENT_RESPAWN;
        }
    }
}

void exclamation_box_act_explode(void) {
    exclamation_box_spawn_contents(mb64_exclamation_box_contents, o->oBehParams2ndByte);
    spawn_mist_particles_variable(0, 0, 46.0f);
    if (mb64_lopt_game == MB64_GAME_BTCM) {
        spawn_triangle_break_particles(10, MODEL_CARTOON_STAR, 0.3f, o->oAnimState);
    } else {
        spawn_triangle_break_particles(10, MODEL_CARTOON_STAR, 0.3f, 3);
    }

    create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
    if (mb64_exclamation_box_contents[o->oBehParams2ndByte].doRespawn) {
        o->oAction = EXCLAMATION_BOX_ACT_WAIT_FOR_RESPAWN;
        cur_obj_hide();
    } else {
        obj_mark_for_deletion(o);
    }
}

void exclamation_box_act_wait_for_respawn(void) {
    if (o->oTimer > 300) {
        o->oAction = EXCLAMATION_BOX_ACT_ACTIVE;
    }
}

ObjActionFunc sExclamationBoxActions[] = {
    exclamation_box_act_init,
    exclamation_box_act_outline,
    exclamation_box_act_active,
    exclamation_box_act_scaling,
    exclamation_box_act_explode,
    exclamation_box_act_wait_for_respawn,
};

void bhv_exclamation_box_loop(void) {
    o->oFloor = NULL;

    cur_obj_scale(2.0f);
    cur_obj_call_action_function(sExclamationBoxActions);
}
