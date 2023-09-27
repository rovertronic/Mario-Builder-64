void bhv_edward_orient(void) {
    f32 a, b, c;

    a= o->oVelX;
    c= -o->oVelY;
    b= o->oVelZ;

    o->oFaceAngleYaw = atan2s(b,a);
    o->oFaceAnglePitch = atan2s( sqrtf((a*a) + (b*b)) , c);
}


void bhv_edward(void) {
    struct Surface *surf;
    Vec3f hitpos;
    Vec3f reflect;

    switch(o->oAction) {
        case 0://init
            {
                Vec3f initVel;
                initVel[0] = (random_float()-.5f)*2.0f;
                initVel[1] = (random_float()-.5f)*2.0f;
                initVel[2] = (random_float()-.5f)*2.0f;
                vec3f_normalize2(&initVel);
                initVel[0] *= 15.0f;
                initVel[1] *= 15.0f;
                initVel[2] *= 15.0f;
                o->oVelX = initVel[0];
                o->oVelY = initVel[1];
                o->oVelZ = initVel[2];
                
                bhv_edward_orient();
                o->oAction = 1;
            }
        break;
        case 1://normal active
            find_surface_on_ray(&o->oPosX, &o->oVelX, &surf, &hitpos, RAYCAST_FIND_ALL);
            if (surf) {
                Vec3f normal;
                get_surface_normal(normal, surf);
                vec3f_sum(&o->oPosX,&o->oPosX,normal);

                vec3f_copy(reflect,normal);
                int dotMultiplier = 2.0f * vec3f_dot(&o->oVelX,normal);
                reflect[0] *= dotMultiplier;
                reflect[1] *= dotMultiplier;
                reflect[2] *= dotMultiplier;
                vec3f_diff(&reflect, &o->oVelX, &reflect);
                vec3f_copy(&o->oVelX, reflect);

                cur_obj_play_sound_2(SOUND_ACTION_BONK);
                bhv_edward_orient();
            } else {
                //go forth
                o->oPosX += o->oVelX;
                o->oPosY += o->oVelY;
                o->oPosZ += o->oVelZ;
            }
            if (o->oInteractStatus != 0) {
                o->oInteractStatus = 0;
                cur_obj_play_sound_2(SOUND_OBJ_BOO_LAUGH_LONG);
            }

            //failsafe
            Vec3f vzero;
            vzero[0] = 0.0f;
            vzero[1] = 0.0f;
            vzero[2] = 0.0f;
            f32 dresult;
            vec3f_get_dist(&o->oPosX, &vzero, &dresult);
            if (dresult > 10000.0f) {
                vec3f_copy(&o->oPosX,&vzero);
            }
        break;
    }
};

void bhv_edward_mother(void) {
    o->oFaceAngleYaw += 0x220;
    if (o->oTimer > 60) {
        o->oTimer = 0;
        spawn_object(o,MODEL_EDWARD,bhvEdward);
        gMarioState->EA_WAVES++;
        save_file_set_hiscore(4,gMarioState->EA_WAVES);
    }
}