#define WORM_SIZE 20

struct Object *PodeSegment[WORM_SIZE];

Vec3f WormTarget;
f32 WormTargetDistance = 0.0f;
s16 WormSinTimer = 0;
s16 TargetPitch;
s16 TargetYaw;

f32 WormWobble = 0.0f;
u8 destroy_index = 0;

void fly_to_target(void) {
    Vec3f mag;
    f32 a, b;

    a=WormTarget[0] - o->oPosX;
    b=WormTarget[2] - o->oPosZ;

    TargetYaw = atan2s(b,a);
    TargetPitch = atan2s( sqrtf((a*a) + (b*b)) ,o->oPosY-WormTarget[1]);

    o->oMoveAnglePitch = approach_s16_asymptotic(o->oMoveAnglePitch,TargetPitch,20);
    o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw,TargetYaw,40);

    o->oPosX += sins(o->oMoveAngleYaw)*o->oForwardVel;
    o->oPosY += -sins(o->oMoveAnglePitch)*o->oForwardVel;
    o->oPosZ += coss(o->oMoveAngleYaw)*o->oForwardVel;

    Vec3f pos;
    pos[0] = o->oPosX;
    pos[1] = o->oPosY;
    pos[2] = o->oPosZ;

    vec3f_diff(&mag, &WormTarget, &pos);
    WormTargetDistance = vec3f_length(&mag);

    o->oFaceAngleYaw = o->oMoveAngleYaw;
    o->oFaceAnglePitch = o->oMoveAnglePitch;
}

static struct SpawnParticlesInfo sWormParticles = {
    /* behParam:        */ 0,
    /* count:           */ 10,
    /* model:           */ MODEL_PEBBLE,
    /* offsetY:         */ 0,
    /* forwardVelBase:  */ 30,
    /* forwardVelRange: */ 15,
    /* velYBase:        */ 60,
    /* velYRange:       */ 30,
    /* gravity:         */ -6,
    /* dragStrength:    */ 0,
    /* sizeBase:        */ 50.0f,
    /* sizeRange:       */ 20.0f,
};

struct Surface *PrevSurf;

void worm_loop(void) {
    u8 i;
    f32 dist;
    Vec3f vecbet;
    f32 a, b;

    struct Object *boom;

    struct Surface *PenSurf;
    Vec3f PenVec;

    Vec3f origin;
    Vec3f raydir;

    Vec3f oldpos;

    WormSinTimer += 400;

    if (revent_queue == 2) {
        return;
    }

    switch(o->oAction) {
        case 0://init worm
            if (revent_queue == 0) {
                return;
            }

            PrevSurf = NULL;

            PodeSegment[0] = o; //i am the first segment
            PodeSegment[0]->oIntangibleTimer = 0;
            for (i=1;i<WORM_SIZE;i++) {
                    PodeSegment[i] = spawn_object(o,0xF9,bhvPodeSeg);
                    PodeSegment[i]->oPosY -= ((f32)i*400.0f);
                    PodeSegment[i]->oIntangibleTimer = 0;
                }
            o->oHomeY += 5000.0f;
            o->oForwardVel = 40.0f;
            o->oAction = 1;

        break;
        case 1:
            //intro
            vec3f_copy(&WormTarget,&o->oHomeX);
            fly_to_target();

            if (WormTargetDistance < 1000.0f) {
                o->oAction = 2;
                gMarioState->BossHealth = 4;
                gMarioState->BossHealthMax = 4;
            }
        break;
        case 2:
            gMarioState->RFuel = 100;
            gMarioState->flags |= MARIO_WING_CAP;

            //pursue target
            vec3f_copy(&WormTarget,&gMarioState->pos);
            WormTarget[1] += sins(WormSinTimer)*2000.0f;
            fly_to_target();

            //print_text_fmt_int(10,10,"ANGD%d",ABS(TargetYaw - o->oMoveAngleYaw));
            if ((ABS(TargetYaw - o->oMoveAngleYaw) < 10000)||(WormTargetDistance < 3000.0f)) {
                //speed up
                if (o->oForwardVel < 200.0f) {
                    o->oForwardVel += .2f;
                }
            } else {
                //slow down to turn
                if (o->oForwardVel > 25.0f) {
                    o->oForwardVel -= 2.0f;
                }
            }
        break;
        case 3://damaged
            WormWobble *= .95f;
            if (gMarioState->BossHealth == 0) {
                if (o->oTimer % 15 == 0) {
                    WormWobble = 500.0f;
                    boom = spawn_object(o,MODEL_EXPLOSION,bhvExplosionFake);
                    boom->oBehParams2ndByte = 6;
                    create_sound_spawner(SOUND_GENERAL_BOWSER_BOMB_EXPLOSION);
                }
                if (o->oTimer > 120) {
                    destroy_index = 19;
                    o->oAction = 4;
                }
            } else {
                //recover
                if (o->oTimer > 60) {
                    o->oAction = 2;
                }
            }
        break;
        case 4://destroy and release star
            if (o->oTimer % 7 == 0) {
                boom = spawn_object(PodeSegment[destroy_index],MODEL_EXPLOSION,bhvExplosionFake);
                boom->oBehParams2ndByte = 6;
                play_sound(SOUND_GENERAL2_BOBOMB_EXPLOSION, gMarioState->marioObj->header.gfx.cameraToObject);
                PodeSegment[destroy_index]->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
                PodeSegment[destroy_index]->oIntangibleTimer = -1;
                if (destroy_index == 0) {
                    //head
                    o->oFaceAnglePitch = 0;
                    spawn_default_star(gMarioState->pos[0],gMarioState->pos[1]+300.0f,gMarioState->pos[2]);
                    o->oAction = 5;
                } else {
                    destroy_index --;
                }
            }
        break;
        case 5:
            //do nothing
        break;
    }

    //make wormsegs follow eachother
    if (o->oAction != 3) {
        for (i=1;i<WORM_SIZE;i++) {
                //Example:
                //PodeSegment[i]->oPosX = PodeSegment[i-1]->oPosX + 400.0f;
                Vec3f aSegPos;
                Vec3f bSegPos;
                aSegPos[0] = PodeSegment[i]->oPosX;
                aSegPos[1] = PodeSegment[i]->oPosY;
                aSegPos[2] = PodeSegment[i]->oPosZ;
                bSegPos[0] = PodeSegment[i - 1]->oPosX;
                bSegPos[1] = PodeSegment[i - 1]->oPosY;
                bSegPos[2] = PodeSegment[i - 1]->oPosZ;

                dist = dist_between_objects(PodeSegment[i],PodeSegment[i-1]);
                if (dist > 500.0f) {
                    vec3f_diff(&vecbet, &aSegPos, &bSegPos);
                    vec3f_normalize(&vecbet);
                    vecbet[0] *= 500.0f;
                    vecbet[1] *= 500.0f;
                    vecbet[2] *= 500.0f;
                    vec3f_sum(&PodeSegment[i]->oPosX,&PodeSegment[i-1]->oPosX,&vecbet);

                    a = bSegPos[0] - aSegPos[0];
                    b = bSegPos[2] - aSegPos[2];

                    PodeSegment[i]->oFaceAngleYaw = atan2s(b,a);
                    PodeSegment[i]->oFaceAnglePitch = atan2s( sqrtf((a*a) + (b*b)), aSegPos[1] - bSegPos[1]);
                }
                if (dist < 400.0f) {
                    vec3f_diff(&vecbet, &aSegPos, &bSegPos);
                    vec3f_normalize(&vecbet);
                    vecbet[0] *= 400.0f;
                    vecbet[1] *= 400.0f;
                    vecbet[2] *= 400.0f;
                    vec3f_sum(&PodeSegment[i]->oPosX,&PodeSegment[i-1]->oPosX,&vecbet);
                }
            }
    } else {
        for (i=1;i<WORM_SIZE;i++) {
                PodeSegment[i]->oPosY = PodeSegment[i]->oHomeY + sins((i*4000)+(WormSinTimer*10))*WormWobble;
            }
    }

    //set up ray
    vec3f_copy(&origin,&o->oPosX);
    raydir[0] = sins(o->oFaceAngleYaw)*200.0f;
    raydir[1] = -sins(o->oFaceAnglePitch)*200.0f;
    raydir[2] = coss(o->oFaceAngleYaw)*200.0f;

    // find_surface_on_ray(origin, raydir, &PenSurf, &PenVec, RAYCAST_FIND_ALL);

    if ((PenSurf)&&(PenSurf!=PrevSurf)) {
        PrevSurf = PenSurf;
        cur_obj_play_sound_2(SOUND_GENERAL_VOLCANO_EXPLOSION);
        vec3f_copy(&oldpos,&o->oPosX);
        vec3f_copy(&o->oPosX,&PenVec);
        cur_obj_spawn_particles(&sWormParticles);
        vec3f_copy(&o->oPosX,&oldpos);
    }
}

void mine_hit(void) {
    u8 i;
    struct Object *boom;
    if (save_file_get_badge_equip() & (1 << BADGE_SLAYER)) {
        gMarioState->BossHealth-=2;
    } else {
        gMarioState->BossHealth--;
    }
    PodeSegment[0]->oAction = 3;
    PodeSegment[0]->oForwardVel = 0.0f;
    boom = spawn_object(o,MODEL_EXPLOSION,bhvExplosionFake);
    boom->oBehParams2ndByte = 6;
    o->oAction = 2;
    cur_obj_hide();
    create_sound_spawner(SOUND_GENERAL_BOWSER_BOMB_EXPLOSION);
    WormWobble = 500.0f;

    for (i=1;i<WORM_SIZE;i++) {
        PodeSegment[i]->oHomeY = PodeSegment[i]->oPosY;
    }
}

void bhv_bigmine(void) {
    struct Object *head = cur_obj_nearest_object_with_behavior(bhvPodeHead);
    struct Object *body;
    f32 dist;

    switch(o->oAction) {
        case 0://wait for boss to start
            cur_obj_hide();
            if (revent_queue == 2) {
                cur_obj_unhide();
                o->oAction = 1;
            }
        break;
        case 1:
            load_object_collision_model();

            if (head != NULL) {//if the head is null it will never check body parts, but in 99.99% of cases it shouldn't happen
                dist = dist_between_objects(o,head);
                if (dist < 700.0f) {
                    mine_hit();
                } else {
                    //not close enough to head, check for a body part (this kind of sucks ik)
                    body = cur_obj_nearest_object_with_behavior(bhvPodeSeg);
                    if (body != NULL) {
                        dist = dist_between_objects(o,body);
                        if (dist < 700.0f) {
                            mine_hit();
                        }
                    }
                }
            }
        break;
        case 2:
            //do nothing
        break;
    }
}