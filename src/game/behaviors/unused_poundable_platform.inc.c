void bhv_unused_poundable_platform(void) {

if (o->oAction == 0) {
    if (save_file_get_flags() & SAVE_FLAG_BOOKSHELF_MOVED) {
        //DO NOTHING
        o->oAction = 3;
        o->oPosX -= 375.0f;
        o->oPosZ -= 375.0f;
        }
        else {
        o->oAction = 1;
        }
    }

    if (o->oAction == 1) {
        if (cur_obj_is_mario_ground_pounding_platform()) {
            play_puzzle_jingle();
            save_file_set_flags(SAVE_FLAG_BOOKSHELF_MOVED);
            o->oAction++;
        }
    }
    
    if (o->oAction == 2) {

        if (o->oTimer < 25) {
            cur_obj_move_using_fvel_and_gravity();
            o->oVelX -= 15.0f;
            o->oVelZ -= 15.0f;
            o->oPosX -= 15.0f;
            o->oPosZ -= 15.0f;
            cur_obj_play_sound_1(SOUND_ENV_METAL_BOX_PUSH);
        }
        else{
        o->oVelX = 0.0f;
        o->oVelZ = 0.0f;
        }
    }
}