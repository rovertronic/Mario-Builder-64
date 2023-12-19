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

    if (cmm_lopt_game == CMM_GAME_VANILLA) {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_VEXCLAMATION_BOX];
    }

    o->oAnimState = cmm_exclamation_box_contents[o->oBehParams2ndByte].animState;


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
    if ((save_file_get_flags() & sCapSaveFlags[o->oBehParams2ndByte])
     || (GET_BPARAM1(o->oBehParams) != EXCLAMATION_BOX_BP1_NEEDS_SWITCH)) {
        o->oAction = EXCLAMATION_BOX_ACT_ACTIVE;
        cur_obj_set_model(MODEL_EXCLAMATION_BOX);
    }
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
    
    if (boxType < 7) { // hardcoded
        struct ExclamationBoxContents *contents = &cmm_exclamation_box_contents[boxType];
        contentsObj = spawn_object(o, contents->model, contents->behavior);
        contentsObj->oVelY = 20.0f;
        contentsObj->oForwardVel = 3.0f;
        contentsObj->oMoveAngleYaw = gMarioObject->oMoveAngleYaw;
        OR_BPARAM1(o->oBehParams, contents->behParams);
        if (contents->model == MODEL_STAR) {
            o->oFlags |= OBJ_FLAG_PERSISTENT_RESPAWN;
        }
    }


    //this doesn't work...

    /*
    u32 bparam2u32 = o->oBehParams2ndByte;
    u32 id_u32 = 7;

    //This prevents the star from spawning with the wrong model id
    switch(o->oBehParams2ndByte) {
        case 1: //cosmic box
            id_u32 = 7;
        break;
        case EXCLAMATION_BOX_BP_STAR_1:
            id_u32 = 0;
        break;
        case EXCLAMATION_BOX_BP_STAR_2:
            id_u32 = 1;
        break;
        case EXCLAMATION_BOX_BP_STAR_3:
            id_u32 = 2;
        break;
        case EXCLAMATION_BOX_BP_STAR_4:
            id_u32 = 3;
        break;
        case EXCLAMATION_BOX_BP_STAR_5:
            id_u32 = 4;
        break;
        case EXCLAMATION_BOX_BP_STAR_6:
            id_u32 = 5;
        break;
        o->oBehParams = (bparam2u32 << 16) | (id_u32 << 24);
    }
    */

    /*
    if (o->oBehParams2ndByte == 1) {
        //metal star event spawner
        switch(gCurrLevelNum) {
            case LEVEL_BITDW:
                contentsObj = spawn_object(o, MODEL_DARKBOWSER, bhvBowser);
                contentsObj->oPosX = -1683; 
                contentsObj->oHomeY = 1339;
                contentsObj->oPosZ = 13179;
                contentsObj->oPosY = o->oHomeY + 2000.0f;
                contentsObj->oBehParams2ndByte = 1;
            break;

            case LEVEL_BOB: //bully king
                contentsObj = spawn_object(o, 0xFC, bhvBigBully);
                contentsObj->oBehParams = 0x06000000;
                //stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_BOSS), 0);
                gMarioState->BossHealth = 30;
                gMarioState->BossHealthMax = 30;
            break;
            case LEVEL_WF: //metal hog warp
                contentsObj = spawn_object(o, MODEL_NONE, bhvInstantWarp);
                contentsObj->oBehParams = 0x00020000;
                contentsObj->oPosY -= 400.0f;
            break;
            case LEVEL_JRB: //WORM
                //stop_background_music(SEQUENCE_ARGS(4, SEQ_LEVEL_HOT));
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_BOSS), 0);
                contentsObj = spawn_object(o, 0xF8, bhvPodeHead);
                contentsObj->oPosY -= 1000.0f;
                contentsObj->oBehParams = 0x06000000;
                run_event(EVENT_PODE_INTRO);
            break;
            case LEVEL_CCM://core
                o->oBehParams = 0x06000000;
                contentsObj = spawn_object(o, 0xED, bhvSpawnedStar);
                contentsObj->oVelY = 20.0f;
                contentsObj->oForwardVel = 3.0f;
                contentsObj->oMoveAngleYaw = gMarioObject->oMoveAngleYaw;
                contentsObj->oBehParams = 0x06000000;
            break;
            case LEVEL_BBH://giant evil ghost ship
                contentsObj = spawn_object(o, 0xF1, bhvVoidShip);
                contentsObj->oBehParams = 0x06000000;
                contentsObj->oDrawingDistance = 32000.0f;
                contentsObj->oPosY = 4500.0f;
                contentsObj->oPosZ = 10000.0f;
                //stop_background_music(SEQUENCE_ARGS(4, SEQ_LEVEL_HOT));
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_BOSS), 0);
                gMarioState->BossHealth = 5;
                gMarioState->BossHealthMax = 5;

                run_event(EVENT_SHIP_INTRO);
            break;
            case LEVEL_HMC: //evil train
                contentsObj = spawn_object(o, MODEL_NONE, bhvInstantWarp);
                contentsObj->oBehParams = 0x00010000;
            break;
            case LEVEL_LLL: //evil vaccum
                contentsObj = spawn_object(o, MODEL_NONE, bhvInstantWarp);
                contentsObj->oBehParams = 0x00020000;
                contentsObj->oPosY -= 400.0f;
            break;
            case LEVEL_SSL: //evil pixel bowser (unused)
                contentsObj = spawn_object(o, MODEL_NONE, bhvRetroPipe);
                contentsObj->oBehParams = 0x00010000;
            break;
            case LEVEL_DDD: //thwomp queen
                contentsObj = spawn_object(o, MODEL_NONE, bhvInstantWarp);
                contentsObj->oBehParams = 0x00010000;
            break;
            case LEVEL_SL: //
                run_event(EVENT_QUIZ);
            break;
        }
    }
    else
    {
    }
    */
}

void exclamation_box_act_explode(void) {
    exclamation_box_spawn_contents(cmm_exclamation_box_contents, o->oBehParams2ndByte);
    spawn_mist_particles_variable(0, 0, 46.0f);
    if (cmm_lopt_game == CMM_GAME_BTCM) {
        spawn_triangle_break_particles(20, MODEL_CARTOON_STAR, 0.3f, o->oAnimState);
    } else {
        spawn_triangle_break_particles(20, MODEL_CARTOON_STAR, 0.3f, 3);
    }

    create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
    if (cmm_exclamation_box_contents[o->oBehParams2ndByte].doRespawn) {
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
