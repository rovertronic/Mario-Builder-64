#include "src/engine/math_util.h"

s16 snake_size;
Vec3f SnakeHead;
struct Object *snakesegs[100];

void bhv_snake_food(void) {
    u8 i;
    f32 dist;
    Vec3f vecbet;
    f32 a, b;
    s16 pitch;
    s16 yaw;


    switch(o->oAction) {
        case 0://init
            snake_size = 0;
            vec3f_copy(&SnakeHead,&gMarioState->pos);
            //snakesegs[0] = spawn_object(gMarioObject,MODEL_SNAKEBALL,bhvSnakeSegment);
            //vec3f_copy(&snakesegs[0]->oHomeX,&SnakeHead);
            o->oAction = 2;
        break;
        case 1://new position
            cur_obj_play_sound_2(SOUND_GENERAL_COLLECT_1UP);
            o->oPosX = (random_float()*1200)-800.0f;
            o->oPosZ = (random_float()*1200)-800.0f;
            o->oAction = 2;
        break;
        case 2://wait to be eaten
            if (o->oDistanceToMario < 100.0f) {
                o->oAction = 1;
                if (snake_size == 0) {
                    snakesegs[snake_size] = spawn_object(gMarioObject,MODEL_SNAKEBALL,bhvSnakeSegment);
                    snakesegs[snake_size]->oPosX = gMarioObject->oPosX + (sins(gMarioObject->oFaceAngleYaw+0x8000)*300.0f);
                    snakesegs[snake_size]->oPosZ = gMarioObject->oPosZ + (coss(gMarioObject->oFaceAngleYaw+0x8000)*300.0f);
                    snakesegs[snake_size]->oPosY = gMarioObject->oPosY;
                } else {
                    snakesegs[snake_size] = spawn_object(gMarioObject,MODEL_SNAKEBALL,bhvSnakeSegment);
                    snakesegs[snake_size]->oPosX = snakesegs[snake_size-1]->oPosX + (sins(snakesegs[snake_size-1]->oFaceAngleYaw)*100.0f);
                    snakesegs[snake_size]->oPosZ = snakesegs[snake_size-1]->oPosZ + (coss(snakesegs[snake_size-1]->oFaceAngleYaw)*100.0f);
                    snakesegs[snake_size]->oPosY = snakesegs[snake_size-1]->oPosY;
                }
                vec3f_copy(&snakesegs[snake_size]->oHomeX,&snakesegs[snake_size]->oPosX);
                snake_size++;

                gMarioState->EA_WAVES++;
                save_file_set_hiscore(3,gMarioState->EA_WAVES);

                if (snake_size == 100) {
                    end_minigame();
                }
            }
        break;
    }

    //the snake food also serves as a controller
    /*
    for (i=1;i<snake_size;i++) {
        dist = dist_between_objects(snakesegs[i],snakesegs[i-1]);
        if (dist > 100.0f) {
            vec3f_dif(&vecbet,&snakesegs[i]->oPosX,&snakesegs[i-1]->oPosX);
            vec3f_normalize(&vecbet);
            vec3f_mul(&vecbet,100.0f);
            vec3f_sum(&snakesegs[i]->oPosX,&snakesegs[i-1]->oPosX,&vecbet);
            a=snakesegs[i-1]->oPosX - snakesegs[i]->oPosX;
            b=snakesegs[i-1]->oPosZ - snakesegs[i]->oPosZ;

            snakesegs[i]->oFaceAngleYaw = atan2s(b,a);
        }
        if (dist < 90.0f) {
            vec3f_dif(&vecbet,&snakesegs[i]->oPosX,&snakesegs[i-1]->oPosX);
            vec3f_normalize(&vecbet);
            vec3f_mul(&vecbet,90.0f);
            vec3f_sum(&snakesegs[i]->oPosX,&snakesegs[i-1]->oPosX,&vecbet);
        }
    }
    */

    vec3f_get_dist_and_angle(gMarioState->pos,&SnakeHead,&dist,&pitch,&yaw);
    if (dist > 100.0f) {
        vec3f_copy(&SnakeHead,&gMarioState->pos);

        if (snake_size > 0) {
            for (i=snake_size-1;i>0;i--) {
                vec3f_copy(&snakesegs[i]->oHomeX,&snakesegs[i-1]->oHomeX);
                a=snakesegs[i-1]->oPosX - snakesegs[i]->oPosX;
                b=snakesegs[i-1]->oPosZ - snakesegs[i]->oPosZ;

                snakesegs[i]->oFaceAngleYaw = atan2s(b,a);
            }
            vec3f_copy(&snakesegs[0]->oHomeX,&SnakeHead);
        }
    }

    //lerpballs
    for (i=0;i<snake_size;i++) {
        snakesegs[i]->oPosX=lerp(snakesegs[i]->oPosX,snakesegs[i]->oHomeX,0.1f);
        snakesegs[i]->oPosY=lerp(snakesegs[i]->oPosY,snakesegs[i]->oHomeY,0.1f);
        snakesegs[i]->oPosZ=lerp(snakesegs[i]->oPosZ,snakesegs[i]->oHomeZ,0.1f);
    }

}