// metal_box.inc.c
#include "src/game/obj_behaviors.h"

struct ObjectHitbox sMetalBoxHitbox = {
    /* interactType:      */ INTERACT_NONE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 1,
    /* numLootCoins:      */ 0,
    /* radius:            */ 220,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 220,
    /* hurtboxHeight:     */ 300,
};

s32 check_if_moving_over_floor(f32 maxDist, f32 offset) {
    struct Surface *floor;
    f32 xPos = o->oPosX + sins(o->oMoveAngleYaw) * offset;
    f32 zPos = o->oPosZ + coss(o->oMoveAngleYaw) * offset;

    f32 floorHeight = find_floor(xPos, o->oPosY, zPos, &floor);

    return (absf(floorHeight - o->oPosY) < maxDist);
}

void bhv_pushable_loop(void) {
    obj_set_hitbox(o, &sMetalBoxHitbox);
    o->oForwardVel = 0.0f;

    if (obj_check_if_collided_with_object(o, gMarioObject) && gMarioStates[0].flags & MARIO_PUSHING) {
        s16 angleToMario = obj_angle_to_object(o, gMarioObject);
        if (abs_angle_diff(angleToMario, gMarioObject->oMoveAngleYaw) > 0x4000) {
            o->oMoveAngleYaw = (s16)((gMarioObject->oMoveAngleYaw + 0x2000) & 0xc000);
            if (check_if_moving_over_floor(8.0f, 150.0f)) {
                o->oForwardVel = 4.0f;
                cur_obj_play_sound_1(SOUND_ENV_METAL_BOX_PUSH);
            }
        }
    }

    cur_obj_move_using_fvel_and_gravity();
}

// void bhv_metal_crate(void) {
//     s16 sp1C;
//     s8 starId;
//     f32 floorY;
//     s16 collisionFlags;
//     f32 marioDist;
//     //struct Surface ffloor*;
//     starId = (o->oBehParams >> 24) & 0xFF;

//     //STAR RADAR TRACKER
//     if ((gDialogCourseActNum-1 == starId)&&(o->oBehParams2ndByte == 2)) {
//         gMarioState->StarRadarLocation[0] = (s16)o->oPosX;
//         gMarioState->StarRadarLocation[1] = (s16)o->oPosY;
//         gMarioState->StarRadarLocation[2] = (s16)o->oPosZ;
//         gMarioState->StarRadarExist = TRUE;
//         }

//     //INIT
//     if (o->oHealth == 4) {
//         o->oHealth = 3;
//         o->prevObj = spawn_object(o,MODEL_NONE, bhvMetalCrateCol);
//         }

//     //In-range to calculate physics
//      marioDist = lateral_dist_between_objects(gCurrentObject, gMarioObject);
//     if (marioDist < 1200.0f) {

//         o->oGravity = 3.0f;
//         o->oFriction = 1.0f;
//         o->oBuoyancy = 1.0f;

//         o->oForwardVel = 0.0f;

//         if (o->oDistanceToMario < 180.0f) {
//             sp1C = obj_angle_to_object(o, gMarioObject);
//             if (abs_angle_diff(sp1C, gMarioObject->oMoveAngleYaw) > 0x4000) {
//                 o->oMoveAngleYaw = gMarioObject->oMoveAngleYaw;
//                 o->oForwardVel = 4.0f;
//                 cur_obj_play_sound_1(SOUND_ENV_METAL_BOX_PUSH);
//                 }
//             }
//         cur_obj_compute_vel_xz();
//         collisionFlags = object_step_without_floor_orient();


//         obj_check_floor_death(collisionFlags, sObjFloor);
//         if (o->oAction == OBJ_ACT_LAVA_DEATH) {
//             o->oHealth = 0;
//             }


//         if (o->oHealth < 1) {
//                 switch(o->oBehParams2ndByte) {
//                     case 0:
//                     spawn_object(o,MODEL_NONE, bhvThreeCoinsSpawn);
//                     break;
//                     case 1:
//                     spawn_object(o,MODEL_BULLY, bhvSmallBully);
//                     break;
//                     case 2:
//                     spawn_default_star(o->oPosX, o->oPosY+ 100.0f, o->oPosZ);
//                     break;
//                     case 4:
//                     spawn_object(o,0xFE, bhvScuttlebug);
//                     break;
//                     }
//                 spawn_mist_particles_variable(0, 0, 46.0f);
//                 spawn_triangle_break_particles(20, 139, 0.3f, 3);
//                 create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
//                 o->prevObj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
//                 o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
//             }

//         }
//     }
// //

// struct Object *myhorse;
// f32 droptoheight=0.0f;

// void bhv_horse_carriage_loop(void) {

//     //struct Surface *sp24;

//     if (o->oAction==0) {
//         o->oGravity = 3.0f;
//         o->oFriction = 1.0f;
//         o->oBuoyancy = 1.0f;
//         o->oForwardVel = 0.0f;
//         o->prevObj = spawn_object(o,0xFB, bhvStaticObject);
//         myhorse = spawn_object(o,0xFA, bhvHorse);
//         o->oAction = 1;
//         }
//         else
//         {
//         cur_obj_compute_vel_xz();
//         object_step_without_floor_orient();

//         if (gMarioObject->platform == o) {

//             if (o->oAction == 1) {
//                 super_cum_working(myhorse,1);
//                 o->oAction = 2;
//             }

//             o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, gMarioObject->oMoveAngleYaw, 0x300);
//             o->oMoveAngleYaw = o->oFaceAngleYaw;
//             if (o->oForwardVel < 15.0f) {
//                 o->oForwardVel ++;
//                 }

//             if (cur_obj_is_mario_ground_pounding_platform()) {
//                 o->oForwardVel += 5.0f;
//                 }

//             gMarioState->pos[0] = (gMarioState->pos[0]+o->oPosX)/2;
//             gMarioState->pos[2] = (gMarioState->pos[2]+o->oPosZ)/2;
//             }
//         }

//         //cur_obj_align_gfx_with_floor_lerp();


//         //WHEEL CODE
//         o->prevObj->oPosX = o->oPosX;
//         o->prevObj->oPosY = o->oPosY+160.0f;
//         o->prevObj->oPosZ = o->oPosZ;
//         o->prevObj->oFaceAnglePitch += o->oForwardVel*40;
//         o->prevObj->oFaceAngleYaw = o->oFaceAngleYaw;

//         if (o->oPosY < 0.0f) {
//             o->oPosX = o->oHomeX;
//             o->oPosY = o->oHomeY;
//             o->oPosZ = o->oHomeZ;
//             o->oForwardVel = 0;
//             o->oAction = 1;
//             super_cum_working(myhorse,0);
//             }

//         //horse code

//         myhorse->oPosX = o->oPosX + (sins(o->oFaceAngleYaw) * 300.0f);
//         myhorse->oPosZ = o->oPosZ + (coss(o->oFaceAngleYaw) * 300.0f);
//         myhorse->oFaceAngleYaw = o->oFaceAngleYaw;
//         droptoheight = find_floor_height(myhorse->oPosX,myhorse->oPosY+500.0f,myhorse->oPosZ);
//         if (droptoheight < o->oPosY) {
//             myhorse->oPosY = o->oPosY-150.0f;
//         } else {
//             myhorse->oPosY = droptoheight-150.0f;
//         }

//         o->oDontInertia = FALSE;
//     }

// void bhv_metal_crate_col(void) {
//     o->oPosX = o->parentObj->oPosX;
//     o->oPosY = o->parentObj->oPosY;
//     o->oPosZ = o->parentObj->oPosZ;
//     load_object_collision_model();
//     }
