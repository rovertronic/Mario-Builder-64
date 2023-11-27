void df_follow_parent(s32 context) {
    Vec3f tmp;
    s16 ang[3];
    vec3_set(ang, 0, o->parentObj->oFaceAngleYaw, 0);
    Mat4 mtx;
    mtxf_rotate_zxy_and_translate(mtx, &o->oParentRelativePosVec, ang);
    linear_mtxf_mul_vec3f(mtx, tmp, &o->oParentRelativePosVec);
    vec3f_sum(&o->oPosVec, &o->parentObj->oPosVec, tmp);
    o->oFaceAngleYaw = o->parentObj->oFaceAngleYaw;// + o->oAngleVelYaw;
}

void df_star(UNUSED s32 context) {
    o->oFaceAngleYaw = (s16)(0x800 * gGlobalTimer);
}

void df_heart(UNUSED s32 context) {
    o->oFaceAngleYaw = (s16)(400 * gGlobalTimer);
}
void df_corkbox(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) o->oAnimState = 1;
}

void df_reds_marker(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) {
        o->oFaceAnglePitch = 0x4000;
        vec3_set(o->header.gfx.scale, 1.5f, 1.5f, 0.75f);
        o->oPosY -= (TILE_SIZE/2 - 60);
    }
    o->oFaceAngleYaw = (s16)(0x100 * gGlobalTimer);
}

void df_tree(s32 context) {
    if (context != CMM_DF_CONTEXT_INIT) return;
    switch(o->oBehParams2ndByte) {
        case 1:
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_TREE_2];
            break;
        case 2:
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_TREE_3];
            break;
        case 3:
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_TREE_4];
            break;
    }
}

void df_exbox(s32 context) {
    if (context != CMM_DF_CONTEXT_INIT) return;
    if (cmm_lopt_game == CMM_GAME_VANILLA) {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_VEXCLAMATION_BOX];
    }
    o->oAnimState = cmm_exclamation_box_contents[o->oBehParams2ndByte].animState;
}

void df_koopa(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) super_cum_working(o, 7);
}
void df_ktq(s32 context) {
    df_koopa(context);
    if (context != CMM_DF_CONTEXT_INIT) return;

    if (o->behavior == segmented_to_virtual(bhvPreviewObject)) {
        // Get trajectory and iterate over it to find the end
        s32 traj_id = o->oBehParams2ndByte;
        if ((cmm_trajectory_list[traj_id][0][0] == -1)||(cmm_trajectory_list[traj_id][1][0] == -1)) return;

        for (s32 i = 0; i < CMM_TRAJECTORY_LENGTH; i++) {
            if (cmm_trajectory_list[traj_id][i][0] == -1) {
                // Spawn flagpole
                struct Object *flagpole = spawn_object(o, MODEL_KOOPA_FLAG, bhvPreviewObject);
                flagpole->oAnimations = koopa_flag_seg6_anims_06001028;
                super_cum_working(flagpole, 0);
                flagpole->oPosX = cmm_trajectory_list[traj_id][i-1][1];
                flagpole->oPosY = cmm_trajectory_list[traj_id][i-1][2] - TILE_SIZE/2;
                flagpole->oPosZ = cmm_trajectory_list[traj_id][i-1][3];
                break;
            }
        }
    }
}

void df_chuckya(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) super_cum_working(o, 4);
}
void df_kingbomb(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) super_cum_working(o, 5);
}
void df_moneybag(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) super_cum_working(o, 4);
}
void df_blizzard(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) o->oAction = 0;
    o->oGraphYOffset = 24.f;
    switch (o->oAction) {
        case 0:
            if (cur_obj_init_animation_and_check_if_near_end(1)) o->oAction = 1;
            break;
        case 1:
            if (cur_obj_init_animation_and_check_if_near_end(0)) o->oAction = 2;
            break;
        case 2:
            if (o->oTimer > 30) o->oAction = 0;
    }
}
// why did i overengineer these so much
void df_podoboo(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) {
        o->oAction = 0;
        o->oHomeY = o->oPosY;
        o->oPosY -= 180.f;
        o->oVelY = 30.f;
        o->oAngleVelYaw = 0;
    }

    o->oVelY -= 2.f;
    o->oPosY += o->oVelY;

    switch (o->oAction) {
        case 0:
            o->oAngleVelYaw = approach_s16_symmetric(o->oAngleVelYaw, 100, 20);
            if (o->oVelY < 0.f) o->oAction = 1;
            break;
        case 1:
            o->oFaceAngleRoll = approach_s16_symmetric(o->oFaceAngleRoll, 0x7FFF, 0x1000);
            if (o->oTimer > 8) o->oAngleVelYaw = approach_s16_symmetric(o->oAngleVelYaw, 0, 20);
            if (o->oPosY < o->oHomeY - 180.f) {
                o->oAction = 2;
            }
            break;
        case 2:
        if (o->oTimer > 10) {
            o->oAction = 0;
            o->oAngleVelYaw = 0;
            o->oFaceAngleRoll = 0;
            o->oVelY = 30.f;
            o->oPosY = o->oHomeY - 180.f;
        }
    }
    cur_obj_scale(((f32)o->oAngleVelYaw) / 100);
}
void df_checkerboard_elevator(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) {
        if ((o->oBehParams >> 24) == 1) {
            cur_obj_set_model(MODEL_LOOPINGP);
        }
    }
}

void df_mri(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) {
        o->oGraphYOffset = 100.0f;
        struct Object * iris = spawn_object(o,MODEL_MAKER_MRI_2, VIRTUAL_TO_PHYSICAL(o->behavior));

        iris->oParentRelativePosZ = 100.0f;
        iris->oParentRelativePosX = 0.0f;
        iris->oParentRelativePosY = 100.0f;
        iris->oPreviewObjDisplayFunc = (void *)df_follow_parent;
    }

    o->oFaceAngleYaw = (s16)(256 * gGlobalTimer);
}
void df_booser(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) super_cum_working(o, BOWSER_ANIM_IDLE);
}

void df_spinner_flame(s32 context) {
    df_follow_parent(context);
    if (gGlobalTimer % 2) o->oAnimState++;
}

void df_fire_spinner(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) {
        o->oAngleVelYaw = o->oFaceAngleYaw;
        for (s32 y = 0; y < 2; y++) {
            s16 yaw = (y * 0x8000);
            f32 xOffset = sins(yaw) * 200.0f;
            f32 zOffset = coss(yaw) * 200.0f;
            s32 amt = o->oBehParams2ndByte + 2; // Amount of flames to spawn

            // Use the vanilla default value if the bparam is 0
            //if (amt == 0) {
            //    amt = 4;
            //}

            for (s32 i = 0; i < amt; i++) {
                struct Object *flameObj = spawn_object(o, MODEL_RED_FLAME, VIRTUAL_TO_PHYSICAL(o->behavior));
                flameObj->oParentRelativePosX = xOffset;
                flameObj->oParentRelativePosY = 100.0f;
                flameObj->oParentRelativePosZ = zOffset;
                obj_scale(flameObj, 6.0f);
                xOffset += sins(yaw) * 150.0f;
                zOffset += coss(yaw) * 150.0f;
                obj_set_billboard(flameObj);
                flameObj->oPreviewObjDisplayFunc = (void *)df_spinner_flame;
            }
        }
    }
    o->oFaceAngleYaw = (s16)(-0x100 * gGlobalTimer) + o->oAngleVelYaw;
}

extern s8 sCloudPartHeights[];
s32 obj_y_vel_approach(f32 target, f32 delta);
void df_lakitu(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) {
        o->oHomeY = o->oPosY;
        o->oVelY = -4.f;
        for (int i = 0; i < 5; i++) {
            struct Object * cloudPart = spawn_object(o,MODEL_MIST,VIRTUAL_TO_PHYSICAL(o->behavior));
            obj_scale(cloudPart,2.0f);
            cloudPart->oOpacity = 255;
            obj_set_billboard(cloudPart);
            obj_scale(cloudPart,2.0f);
            cloudPart->oParentRelativePosY = sCloudPartHeights[i];
            cloudPart->oParentRelativePosX = sins(0x3333*i)*40.0f;
            cloudPart->oParentRelativePosZ = coss(0x3333*i)*40.0f;
            cloudPart->oPreviewObjDisplayFunc = (void *)df_follow_parent;
        }
    }

    if (o->oPosY < o->oHomeY) {
        obj_y_vel_approach(4.0f, 0.4f);
    } else {
        obj_y_vel_approach(-4.0f, 0.4f);
    }
    o->oPosY += o->oVelY;
}

void df_snufit(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) {
        o->oSnufitBodyScale = 600.0f;
        vec3f_copy(&o->oHomeVec, &o->oPosVec);
        o->oAngleVelYaw = o->oFaceAngleYaw;
    }

    o->oPosX = o->oHomeX + 50.0f * coss(400 * gGlobalTimer);
    o->oPosY = o->oHomeY + 8.0f * coss(4000 * gGlobalTimer);
    o->oPosZ = o->oHomeZ + 50.0f * sins(400 * gGlobalTimer);
    o->oFaceAngleYaw = (s16)(200 * gGlobalTimer) + o->oAngleVelYaw;
}

extern enum CMM_THEMES cmm_themes;
void df_bully(s32 context) {
    if ((context == CMM_DF_CONTEXT_INIT)&&(cmm_lopt_theme == CMM_THEME_SNOW)) {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_CHILL_BULLY];
    }
}

void df_flyguy(s32 context) {
    o->oAngleVelYaw++;
    o->oPosY += coss(0x400 * o->oAngleVelYaw) * 1.5f;
}

void df_boo(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) {
        o->oHomeY = o->oPosY - 30.f;
    }
    o->oAngleVelYaw = 0x400 * gGlobalTimer;
    o->oFaceAnglePitch = sins(o->oAngleVelYaw) * 0x400;

    o->oPosY = o->oHomeY - sins(o->oAngleVelYaw) * 20.f;
}

extern s16 sCoinArrowPositions[][2];
void df_coin_formation(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) {
        Vec3i pos = { 0, 0, 0 };
        s32 spawnCoin    = TRUE;
        u32 index = 0;

        while (spawnCoin && index < 8) {
            switch (o->oBehParams2ndByte & COIN_FORMATION_BP_SHAPE_MASK) {
                case COIN_FORMATION_BP_SHAPE_HORIZONTAL_LINE:
                    pos[2] = 160 * (index - 2);
                    if (index > 4) spawnCoin = FALSE;
                    break;
                case COIN_FORMATION_BP_SHAPE_VERTICAL_LINE:
                    pos[1] = index << 7;
                    if (index > 4) spawnCoin = FALSE;
                    break;
                case COIN_FORMATION_BP_SHAPE_HORIZONTAL_RING:
                    pos[0] = sins(index << 13) * 300.0f;
                    pos[2] = coss(index << 13) * 300.0f;
                    break;
                case COIN_FORMATION_BP_SHAPE_VERTICAL_RING:
                    pos[0] = coss(index << 13) * 200.0f;
                    pos[1] = sins(index << 13) * 200.0f + 256.0f;
                    break;
                case COIN_FORMATION_BP_SHAPE_ARROW:
                    pos[0] = sCoinArrowPositions[index][0];
                    pos[2] = sCoinArrowPositions[index][1];
                    break;

            }

            if (spawnCoin) {
                struct Object *newCoin =spawn_object_relative(index, pos[0], pos[1], pos[2], o, MODEL_YELLOW_COIN, VIRTUAL_TO_PHYSICAL(o->behavior));
                obj_set_billboard(newCoin);
            }
            index ++;
        }
    }
}

void df_grindel(s32 context) {
    if (context == CMM_DF_CONTEXT_INIT) {
        o->oFaceAngleYaw += 0x4000;
        o->oMoveAngleYaw += 0x4000;
    }
}
