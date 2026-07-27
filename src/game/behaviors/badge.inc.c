void bhv_badge(void) {
    switch (o->oAction) {
        case 0:
            if ((mb64_play_badge_bitfield >> o->oBehParams2ndByte) & 1) {
                o->oAction++;
                o->oHomeY = 1.0f;
                cur_obj_drop_imbued_object(0);
                break;
            }
            if ((detect_object_hitbox_overlap(gMarioObject, o)) && (gMarioState->action != ACT_LVUP_DANCE)) {
                o->oAction++;
                if (gMarioState->area->camera->mode != gMarioState->area->camera->defMode) {
                    set_camera_mode(gMarioState->area->camera, gMarioState->area->camera->defMode, 1);
                }
                mario_stop_riding_object(gMarioState);
                (mb64_play_badge_bitfield |= (1 << o->oBehParams2ndByte));

                o->oHomeY = 1.0f;

                if ((o->oBehParams2ndByte == BADGE_BRITTLE) || (o->oBehParams2ndByte == BADGE_WITHER)) {
                    set_mario_action(gMarioState, ACT_LVUP_DANCE, 1);
                    play_sound(SOUND_OBJ_BOWSER_LAUGH, gGlobalSoundSource);
                } else {
                    set_mario_action(gMarioState, ACT_LVUP_DANCE, 0);
                    play_puzzle_jingle();
                }
                create_badge_dialog(o->oBehParams2ndByte);
                cur_obj_drop_imbued_object(0);
            }
            break;
        case 1:
            o->oAngleVelYaw += 0x70;
            o->oFaceAngleYaw += o->oAngleVelYaw;
            cur_obj_scale(o->oHomeY);
            o->oHomeY = o->oHomeY * .95f;
            if (o->oHomeY < .2f) {
                obj_mark_for_deletion(o);
            }
            break;
    }
}
