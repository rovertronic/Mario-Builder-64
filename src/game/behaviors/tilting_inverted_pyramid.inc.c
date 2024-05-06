
// u8 aghealth = 3;
// u8 agstate = 0;


// //bowser 1 stuff
// u8 lava_pit_stage = 1;
// f32 lava_pit_heights[] = {10.1414f,26.5116f,61.8791f,80.975};
// f32 lava_pit_scales[] = {1.0f,1.578f,2.055f,2.071};
// f32 lava_pit_scale = 1.0f;;
// f32 lava_pit_height = 10.1414f;

// f32 lava_crate_height = 0.0f;
// //

// u16 eRandomMinMaxU16(u16 min, u16 max) {
//     u16 num = random_u16();
//     return (num % ((max + 1) - min)) + min;
// }

// /**
//  * Initialize the object's transform matrix with Y being up.
//  */
// void bhv_platform_normals_init(void) {
//     vec3f_set(&o->oTiltingPyramidNormalVec, 0.0f, 1.0f, 0.0f);
//     obj_scale(o,(o->oBehParams2ndByte/2.0f));
//     mtxf_align_terrain_normal(o->transform, &o->oTiltingPyramidNormalVec, &o->oPosVec, 0);
// }

// /**
//  * Main behavior for the tilting pyramids in LLL/BitFS. These platforms calculate rough normals from Mario's position,
//  * then gradually tilt back moving Mario with them.
//  */
// void bhv_tilting_inverted_pyramid_loop(void) {
// #ifndef PLATFORM_DISPLACEMENT_2
//     Vec3f posBeforeRotation, posAfterRotation;
//     Vec3f marioPos, dist;
// #endif
//     Vec3f targetNormal;
//     Mat4 *transform = &o->transform;
//     s32 marioOnPlatform = (gMarioObject->platform == o);

//     if (marioOnPlatform) {
// #ifndef PLATFORM_DISPLACEMENT_2
//         // Target the normal in Mario's direction
//         vec3_diff(dist, gMarioStates[0].pos, &o->oPosVec);

//         // Get Mario's position before the rotation
//         vec3f_copy(marioPos, gMarioStates[0].pos);

//         linear_mtxf_mul_vec3f(*transform, posBeforeRotation, dist);
//         targetNormal[0] = dist[0];
//         targetNormal[2] = dist[2];
// #else // PLATFORM_DISPLACEMENT_2
//         targetNormal[0] = gMarioStates[0].pos[0] - o->oPosX;
//         targetNormal[2] = gMarioStates[0].pos[2] - o->oPosZ;
// #endif
//         targetNormal[1] = 500.0f;
//         vec3f_normalize(targetNormal);
//     } else {
//         // Target normal is directly upwards when Mario is not on the platform.
//         vec3f_set(targetNormal, 0.0f, 1.0f, 0.0f);
//     }

//     // Approach the normals by 0.01f towards the new goal, then create a transform matrix and orient the object. 
//     // Outside of the other conditionals since it needs to tilt regardless of whether Mario is on.
//     approach_f32_symmetric_bool(&o->oTiltingPyramidNormalX, targetNormal[0], 0.01f);
//     approach_f32_symmetric_bool(&o->oTiltingPyramidNormalY, targetNormal[1], 0.01f);
//     approach_f32_symmetric_bool(&o->oTiltingPyramidNormalZ, targetNormal[2], 0.01f);
//     mtxf_align_terrain_normal(*transform, &o->oTiltingPyramidNormalVec, &o->oPosVec, 0x0);

// #ifndef PLATFORM_DISPLACEMENT_2
//     // If Mario is on the platform, adjust his position for the platform tilt.
//     if (marioOnPlatform) {
//         linear_mtxf_mul_vec3f(*transform, posAfterRotation, dist);
//         marioPos[0] += posAfterRotation[0] - posBeforeRotation[0];
//         marioPos[1] += posAfterRotation[1] - posBeforeRotation[1];
//         marioPos[2] += posAfterRotation[2] - posBeforeRotation[2];
//         vec3f_copy(gMarioStates[0].pos, marioPos);
//     }
// #endif

//     o->header.gfx.throwMatrix = transform;
// }

// void bhv_HotBackForth_loop(void) {
//     o->oDontInertia = TRUE;

//     if (o->oAction == 0) {
//         o->oAction = 1;

//         obj_scale(o,1.5f);
//         o->oMoveAngleYaw += 0x4000;
//         o->oHomeX = o->oPosX;

//         if (o->oBehParams2ndByte == 1) {
//             o->oPosX -= 400.0f;
//             }
//         }

//     if (o->oAction == 1) {
//         cur_obj_move_using_fvel_and_gravity();

//         if (o->oTimer > 40) {
//             cur_obj_shake(o);
//         }
//         if (o->oTimer > 60) {
//             o->oAction = 2;
//             o->oPosY = o->oHomeY;
//             }
//         }

//     if (o->oAction == 2) {
//         cur_obj_move_using_fvel_and_gravity();

//         if (o->oBehParams2ndByte == 0) {
//             o->oForwardVel = -30.0f;
//             cur_obj_play_sound_1(SOUND_ENV_METAL_BOX_PUSH);
//             if (o->oPosX < o->oHomeX-400.0f) {
//                 o->oAction = 1;
//                 o->oBehParams2ndByte = 1;
//                 o->oTimer = 0;
//                 o->oForwardVel = 0.0f;
//                 }
//             }
//             else
//             {
//             o->oForwardVel = 30.0f;
//             cur_obj_play_sound_1(SOUND_ENV_METAL_BOX_PUSH);
//             if (o->oPosX > o->oHomeX) {
//                 o->oAction = 1;
//                 o->oBehParams2ndByte = 0;
//                 o->oTimer = 0;
//                 o->oForwardVel = 0.0f;
//                 }
//             }
//         }
//     }

// void loop_bone_platform (void) {
//     f32 mdist3;
//     o->oDontInertia = TRUE;

//         if (o->oAction == 0) {
//             if (gMarioObject->platform == o) {
//                 o->oAction = 1;
//                 o->oTimer = 0;
//                 }
//             }
//         if (o->oAction == 1) {


//             cur_obj_play_sound_1(SOUND_ENV_METAL_BOX_PUSH);
//             if (o->oTimer%2 == 0) {
//                 o->oPosY = o->oHomeY;
//                 }
//                 else
//                 {
//                 o->oPosY = o->oHomeY+7.0f;
//                 }
//             if (o->oTimer > 60) {
//                 o->oAction = 2;
//                 o->oTimer = 0;
//                 cur_obj_play_sound_2(SOUND_GENERAL_PLATFORM);
//                 }
//             }
//         if (o->oAction == 2) {
            
//             o->oPosY += o->oVelY;
//             o->oVelY -= 2.0f;
//             if (o->oPosY < -5000.0f) {
//                 o->oPosY = -5000.0f;
//                 o->oVelY = 0;
//                 }

//             if (o->oTimer > 90) {
//                 o->oPosY = o->oHomeY;
//                 o->oAction = 0;
//                 o->oVelY = 0;
//                 }
//             }
//     }

// u16 RandomMinMaxU162(u16 min, u16 max) {
//     u16 num = random_u16();
//     return (num % ((max + 1) - min)) + min;
// }

// u32 ooftable[] = {SOUND_MARIO_OOOF,SOUND_MARIO_ON_FIRE,SOUND_MARIO_ATTACKED};

// void loop_bone_elevator (void) {
//         if (o->oBehParams2ndByte == 1) {
//             switch(o->oAction) {
//                 case 0:
//                 o->oAction++;
//                 o->oHomeY = o->oPosY;
//                 o->oPosY -= 600.0f;
//                 break;
//                 case 1:
//                 if (o->oPosY < o->oHomeY) {
//                     o->oPosY += 2.0f;
//                     cur_obj_play_sound_1(SOUND_ENV_ELEVATOR1);
//                     }
//                     else
//                     {
//                     o->oAction++;
//                     o->oPosY = o->oHomeY;
//                     cur_obj_play_sound_2(SOUND_GENERAL_ELEVATOR_LAND);
//                     }
//                 break;
//                 }
//             return;
//             }

//         if (o->oAction == 0) {
//             if (gMarioObject->platform == o) {
//                 o->oAction = 1;
//                 }
//             }
//         if (o->oAction == 1) {

//             o->oPosY += 15.0f;
//             o->oVelY = 15.0f;
//             cur_obj_play_sound_1(SOUND_ENV_ELEVATOR1);

            
//             if (gMarioState->pos[1] < o->oPosY-50.0f) {
//                 o->oAction = 2;
//                 o->oHealth = 0;
//                 }
//             }
//         if (o->oAction == 2) {
//             o->oPosY += o->oVelY;
//             if (o->oVelY > -60.0f) {
//                 o->oVelY -= 2.0f;
//                 }
//             if (o->oPosY < o->oHomeY) {
//                 o->oPosY = o->oHomeY;
//                 if (o->oHealth < 5) {
//                     o->oVelY = (-o->oVelY)/2;
//                     o->oHealth ++;
//                     if (gMarioState->pos[1] < o->oPosY-50.0f) {
//                         gMarioState->hurtCounter += 8;
//                         play_sound(ooftable[RandomMinMaxU162(0,2)], gMarioState->marioObj->header.gfx.cameraToObject);
//                         }
//                     }
//                     else
//                     {
//                     o->oAction = 0;
//                     o->oVelY = 0;
//                     }
//                 cur_obj_shake_screen(SHAKE_POS_SMALL);
//                 cur_obj_play_sound_2(SOUND_GENERAL_ELEVATOR_LAND);
//                 }
//             }
//     }

// void loop_flimboard (void) {
//     o->oDontInertia = TRUE;

//         if (o->oAction == 0) {
//             if (gMarioObject->platform == o) {
//                 o->oAction = 1;
//                 play_sound(SOUND_GENERAL_OPEN_CHEST, o->header.gfx.cameraToObject);
//                 }
//             }
//         if (o->oAction == 1) {
//             o->oFaceAnglePitch += o->oMoveAnglePitch;
//             if (o->oFaceAnglePitch > 0x4000) {
//                 o->oMoveAnglePitch -= 0x50;
//                 }
//                 else
//                 {
//                 o->oMoveAnglePitch += 0x50;
//                 }
//             o->oMoveAnglePitch *= .98;
//             }
//         if (o->oDistanceToMario > 2700.0f) {
//             o->oAction = 0;
//             o->oMoveAnglePitch = 0;;
//             o->oFaceAnglePitch = 0;
//             }
//     }

// void bhv_ship_elevator_loop(void) {
//         struct Object *sp1C;
//         struct Object *sp2C;
//         Vtx *RopeVertex = segmented_to_virtual(&ship_elevator_rope_StretchRopes_mesh_vtx_0);

//         if (o->oAction == 0) {
//             //INIT
//             o->oPosY = o->oHomeY-2100.0f;
//             o->oAction = 1;
//             }
//         if (o->oAction == 1) {
//             if (gMarioObject->platform == o) {
//                 o->oAction = 2;
//                 }
//             }
//         if (o->oAction == 2) {
//             o->oVelY = 10;
//             o->oPosY += 10;
//             if (o->oPosY > o->oHomeY) {
//                 o->oPosY = o->oHomeY;
//                 o->oVelY = 0;
//                 }
//             if (gMarioObject->platform == o) {
//                 o->oTimer = 0;
//                 }
//             if (o->oTimer > 60) {
//                 o->oAction = 3;
//                 }
//             }
//         if (o->oAction == 3) {
//             o->oVelY = -10;
//             o->oPosY -= 10;
//             if (o->oPosY < o->oHomeY-2100.0f) {
//                 o->oPosY = o->oHomeY-2100.0f;
//                 o->oVelY = 0;
//                 o->oAction = 1;
//                 // o->oHomeY - 2100.0f; // what is this meant to do?
//                 }
//             }

//         //CONTROL ROPES
        
//         sp1C = cur_obj_nearest_object_with_behavior(bhvShipElevatorRope);
//         if (sp1C) {
//             sp1C->header.gfx.scale[1] = (sp1C->oPosY-o->oPosY)/100.0f;
//             RopeVertex[2].n.tc[0] = (s32)(sp1C->header.gfx.scale[1]*1016.0f);
//             RopeVertex[3].n.tc[0] = (s32)(sp1C->header.gfx.scale[1]*1016.0f);
//             RopeVertex[6].n.tc[0] = (s32)(sp1C->header.gfx.scale[1]*1016.0f);
//             RopeVertex[7].n.tc[0] = (s32)(sp1C->header.gfx.scale[1]*1016.0f);
//             }

//         //CONTROL PULLEY
//         sp2C = cur_obj_nearest_object_with_behavior(bhvShipElevatorPulley);
//         if (sp2C) {
//             sp2C->oFaceAnglePitch += o->oVelY*-64;
//             }
//     }

// u8 Lflash = 255;

// void bhv_GhostBoard_loop(void) {

//     o->header.gfx.scale[2] = 2.0f; //make those boards fat ass
//     o->header.gfx.scale[1] = 2.0f;

//     if (o->oAction == 0) {
//         o->oAction = 1;
//         o->oVelY = 5.0f;
//         o->oFaceAngleYaw += o->oBehParams2ndByte*0x4000;
//         }


//     //FADE
//     if (o->oDistanceToMario > 1100.0f) {
//         cur_obj_disable_rendering();
//         }
//         else
//         {
//         cur_obj_enable_rendering();
//         o->oOpacity = 255-((o->oDistanceToMario*255)/1100.0f);

//         //oscilate
//         o->oPosY += o->oVelY;
//         if (o->oPosY > o->oHomeY) {
//             o->oVelY -=.5;
//             }
//             else
//             {
//             o->oVelY +=.5;
//             }
//         }

//     if (Lflash > 120) {
//         if (o->oDistanceToMario < 2000.0f) {
//             cur_obj_enable_rendering();
//         }
//         o->oOpacity = Lflash;
//     }

//     }
// //->oOpacity

// //even = positive, odd = negative
// //0,1 = X, 2,3 = Y, 4,5 = Z
// //6 = END
// u8 SnakePath[] = {1,1,1,1,1,1,2,2,2,2,2,2,0,0,0,0,
// 2,2,5,5,5,5,5,5,5,5,0,0,0,2,2,1,
// 1,3,3,3,3,0,0,2,2,0,0,4,4,4,4,4,
// 4,2,2,2,2,2,2,2,2,2,2,1,1,1,1,6};

// u8 SnakePath2[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,4,0,0,0,0,0,4,4,4,4,4,1,2,0,2,1,2,0,2,0,4,4,4,4,4,4,4,4,4,4,4,4,4,6};

// //u8 SnakePath3[] = {1,1,1,1,1,1,5,5,5,5,5,0,0,0,0,3,3,3,0,0,0,0,2,2,2,2,2,2,2,2,2,2,4,4,4,4,};

// u8 SnakePath3[] = {1,1,1,1,1,1,1,1, 4,4,4,4,4,  0,0,0,  3,3,3, 0,0,0,0,  2,2,2,2,2,2,2,2,2,2,   5,5,5,5,
// //cbt
// 2,2,2, 5,5,5,  2, 4,4,4,  2,2,2,2, 
// 4,4,4, 1, 5,5,5, 0,//loop 4 times
// //4,4,4, 1, 5,5,5, 0, actually 3
// 4,4,4, 1, 5,5,5, 0,
// 4,4,4, 1, 5,5,5, 0,//
// 3,3,3,3,5,5,5,1,1,1,1,1,1,1,1, 4,4,4,4,4, 3,3,3, 4,4,
// 6};

// u8 SnakePath4[] = {
//     1,1,1,1,1,1,
//     1,1,1,1,1,1,1,1,1,1,
//     5,5,5,5,5,5,5,
//     2,2,2,2,2,
//     5,5,5,5,5,5,5,5,5,5,
//     3,
//     4,4,
//     3,3,3,3,3,
//     5,5,
//     2,2,2,2,2,2,2,
//     2,2,2,2,2,2,2,2,
//     0,0,0,0,0,0,0,0,0,0,0,
//     3,4,4,2,2,4,2,4,2,
//     4,4,4,4,4,4,
//     0,0,
//     2,2,2,2,2,2,2,2,2,2,
//     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//     2,
//     4,4,4,4,4,4,4,4,4,4,

//     6
// };

// u8 *SnakePathList[] = {
//     &SnakePath,
//     &SnakePath2,
//     &SnakePath3,
//     &SnakePath4
//     };

// u16 time_off_snakeblock;

// void loop_snakeblock_main(void) {
//         struct Object *obj;
//         o->oDontInertia = TRUE;
//         //oExtraVariable1 = what kind of individual snakeblock

//         if (o->oAction == 0) {
//             o->header.gfx.scale[0] = 5;
//             o->header.gfx.sharedChild = gLoadedGraphNodes[0xE4];
//             o->oAnimState = 2;

//             if (gMarioObject->platform == o) {
//                 time_off_snakeblock = 0;

//                 o->header.gfx.scale[0] = 1;
//                 o->oAnimState = 0;

//                 o->oPosX += 400;

//                 o->oAction = 1;
//                 o->oTimer = 0;
                
//                 obj = spawn_object(o,0xE4,bhvSnakeMain);
//                 obj->oAnimState = 0;
//                 obj->oHealth = 0;
//                 obj->oExtraVariable1 = 1;
//                 obj->oAction = 1;
//                 obj->oTimer = 0;
//                 obj->oBehParams2ndByte = o->oBehParams2ndByte;
            
//                 //i coullda did a for loop but idgaf
//                 obj = spawn_object(o,0xE4,bhvSnakeMinion);
//                 obj->oTimer = 60;
//                 obj->oPosX -= 200;
//                 obj->oAnimState = 1;
//                 obj->oBehParams2ndByte = o->oBehParams2ndByte;

//                 obj = spawn_object(o,0xE4,bhvSnakeMinion);
//                 obj->oTimer = 40;
//                 obj->oPosX -= 400;
//                 obj->oAnimState = 1;
//                 obj->oBehParams2ndByte = o->oBehParams2ndByte;

//                 obj = spawn_object(o,0xE4,bhvSnakeMinion);
//                 obj->oTimer = 20;
//                 obj->oPosX -= 600;
//                 obj->oAnimState = 1;
//                 obj->oBehParams2ndByte = o->oBehParams2ndByte;

//                 obj = spawn_object(o,0xE4,bhvSnakeMinion);
//                 obj->oTimer = 0;
//                 obj->oPosX -= 800;
//                 obj->oAnimState = 1;
//                 obj->oBehParams2ndByte = o->oBehParams2ndByte;

//                 o->oHealth = 4;
//                 o->oPosX -= 790;
//                 }
//             }

//         if (o->oAction == 1) {

//             time_off_snakeblock ++;

//             if (time_off_snakeblock > 500) {
//                 o->oAction = 3;
//             }

//             if (o->oTimer > 19) {
//                 o->oTimer = 0;
//                 o->oHealth += 1; //using health as an index for direction tbh
//                 if (o->oExtraVariable1 == 0) {
//                     obj = spawn_object(o,0xE4,bhvSnakeMinion);
//                     obj->oAnimState = 1;
//                     obj->oBehParams2ndByte = o->oBehParams2ndByte;
//                     }
//                 }

//             switch(SnakePathList[o->oBehParams2ndByte][o->oHealth]) {
//                 case 0: //backward
//                 o->oPosX += 10;
//                 break;
//                 case 1: //forward
//                 o->oPosX -= 10;
//                 break;
//                 case 2: //up
//                 o->oPosY += 10;
//                 break;
//                 case 3: //down
//                 o->oPosY -= 10;
//                 break;
//                 case 4: //left
//                 o->oPosZ += 10;
//                 break;
//                 case 5: //right
//                 o->oPosZ -= 10;
//                 break;
//                 case 6: //right
//                 o->oAction = 3;
//                 break;
//                 }

//             }
        
//         if (o->oAction == 3) {
//             o->oVelY -= 1;
//             o->oPosY += o->oVelY;

//             if (o->oPosY < -3000.0f) {
//                 if (o->oExtraVariable1 == 0) {
//                     o->oVelY = 0;
//                     o->oPosX = o->oHomeX;
//                     o->oPosY = o->oHomeY;
//                     o->oPosZ = o->oHomeZ;
//                     o->oAction = 0;
//                     o->oAnimState = 0;
//                     }
//                     else
//                     {
//                     obj_mark_for_deletion(o);
//                     }
//                 }
//             }
//     }

// void loop_snakeblock_minion(void) {
//     if (gMarioState->pos[1] > o->oPosY - 1000.0f) {
//         time_off_snakeblock = 0;
//     }
//     if (time_off_snakeblock > 500) {
//         obj_mark_for_deletion(o);
//         }
//     if (o->oTimer > 79) {
//         obj_mark_for_deletion(o);
//         }
//     }

// struct Surface *sp24;

// //wow past rovert this code is awful, if i could come back i would kick the shit out of you for writing this
// //you lazy dumb ass
// //Lightning
// void loop_lightning(void) {
//     u8 *Shiplights = segmented_to_virtual(&bbh_dl_crate_lights);
//     f32 mdist;

//     //STRICKING
//     if (o->oAction == 1) {
//         if (random_u16() > 20000) {
//             o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
//             Lflash = 255;
//             }
//             else
//             {
//             o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
//             o->oFaceAngleYaw = random_u16();
//             Lflash = 140;
//             }

//             if (o->oTimer > 30)
//                 {
//                 o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
//                 o->oTimer = 0;
//                 o->oAction = 0;
//                 Lflash = 255;
//                 }
//         }

//     //WAITING
//     if (o->oAction == 0) {
//         o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;

//         if (o->oTimer > random_u16()/2)
//             {
//             if (gMarioState->pos[1] > 10000.0f) {
//                 o->oPosX = gMarioState->pos[0] + ((random_float()*6,553.6)-3276.8f);
//                 o->oPosZ = gMarioState->pos[2] + ((random_float()*6,553.6)-3276.8f);
//                 }
//                 else
//                 {
//                 o->oPosX = ((random_float()*16000.0f)-8000.0f);
//                 o->oPosZ = ((random_float()*16000.0f)-8000.0f);
//                 }
//             o->oPosX = CLAMP(o->oPosX, -32768, 32768); // TODO: Make sure random value is between level bounds
//             o->oPosZ = CLAMP(o->oPosZ, -32768, 32768); // TODO: Make sure random value is between level bounds
//             //o->oPosY = 19000.0f;

//             f32 waterLevel  = cmm_get_water_level(o->oPosX, o->oPosY, o->oPosZ);
//             f32 floorHeight = find_floor_height((f32)o->oPosX, 19000.0f, (f32)o->oPosZ);

//             if (waterLevel > floorHeight) {
//                 o->oPosY = waterLevel;
//             } else {
//                 o->oPosY = floorHeight;
//             }

//             set_camera_shake_from_point(SHAKE_POS_LARGE, o->oPosX, o->oPosY, o->oPosZ);

//             mdist = lateral_dist_between_objects(o,gMarioObject);

//             if (mdist < 2000.0f) {
//                 play_sound(SOUND_GENERAL_BOWSER_BOMB_EXPLOSION, gGlobalSoundSource);
//                 queue_rumble_data(30, 255);
//                 }
//                 else
//                 {
//                 play_sound(SOUND_CUSTOM_PEACH_POWER_OF_THE_STARS, gGlobalSoundSource);   //SOUND_PEACH_DEAR_MARIO
//                 queue_rumble_data(20, 200);
//                 }

//             if ((mdist < 500.0f)&&(gMarioState->pos[1] > o->oPosY-100.0f))  {
//                 o->oPosX = gMarioState->pos[0];
//                 o->oPosZ = gMarioState->pos[2];
//                 o->oPosY = gMarioState->pos[1];
//                 gMarioState->health = 0x100;
//                 //get shocked idiot
//                     if (gMarioState->action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER)) {
//                         drop_and_set_mario_action(gMarioState, ACT_WATER_SHOCKED, 0);
//                     } else {
//                         update_mario_sound_and_camera(gMarioState);
//                         drop_and_set_mario_action(gMarioState, ACT_SHOCKED, 0);
//                     }
//                 }
//             o->oTimer = 0;
//             o->oAction = 1;
//             }
//         }

//     if (o->oBehParams2ndByte == 0) {
//         if (Lflash > 120) {
//             Lflash -=4;
//             }

//         //UPDATE LEVEL LIGHTS
//         Shiplights[8] = Lflash-5;//Diffuse
//         Shiplights[9] = Lflash;
//         Shiplights[10] = Lflash-5;
//         Shiplights[12] = Lflash-5;
//         Shiplights[13] = Lflash;
//         Shiplights[14] = Lflash-5;

//         Shiplights[0] = (Lflash/2)-20;//Ambient
//         Shiplights[1] = (Lflash/2);
//         Shiplights[2] = (Lflash/2)-20;
//         Shiplights[4] = (Lflash/2)-20;
//         Shiplights[5] = (Lflash/2);
//         Shiplights[6] = (Lflash/2)-20;
//         }
//     }

// void loop_VRset(void) {
//     f32 mdist2;

//     if (o->oAction == 0) {
//         o->oAction = 1;
//         o->oPosY += 100.0f;
//         }

//     if (o->oAction == 1) {
//         mdist2 = lateral_dist_between_objects(o,gMarioObject);
//         if (mdist2 < 50.0f) {
//             o->oAction = 2;
//             }
//         }

//     if (o->oAction == 2) {
//         o->oPosY -= 5.0f;
//         cur_obj_play_sound_1(SOUND_ENV_ELEVATOR1);

//         if (o->oPosY < o->oHomeY) {
//             o->oAction = 3;
//             }
//         }

//     if (o->oAction == 3) {
//         load_object_collision_model();
//         }

//     if (o->oAction > 1) {
//         gMarioState->pos[0] = o->oPosX;
//         if (gMarioState->pos[1] > o->oPosY) {
//             gMarioState->pos[1] = o->oPosY;
//             }
//         gMarioState->pos[2] = o->oPosZ;
//         o->oFaceAngleYaw = gMarioState->faceAngle[1];
//         }
//     }

// void loop_bone_train(void) {

//     cur_obj_move_using_fvel_and_gravity();

//     if (o->oAction == 0) {

//         if (o->oForwardVel < 90.0f) {
//             o->oForwardVel += 1.0f;
//             cur_obj_play_sound_1(SOUND_ENV_ELEVATOR1);

//             }
//         if (o->oPosX < o->oHomeX-((f32)(o->oBehParams2ndByte)*3200.0f)) {
//             o->oAction = 1;
//             o->oTimer = 0;
//             }
//         }

//     if (o->oAction == 1) {
//         if (o->oForwardVel > 0.0f) {
//             o->oForwardVel -= 2.0f;
//             }
//             else
//             {
//             if (o->oTimer > 200) {
//                 o->oTimer = 0;
//                 o->oAction = 2;
//                 }
//             }
//         }

//     if (o->oAction == 2) {

//         if (o->oForwardVel > -90.0f) {
//             o->oForwardVel -= 1.0f;
//             cur_obj_play_sound_1(SOUND_ENV_ELEVATOR1);
//             }
//         if (o->oPosX > o->oHomeX) {
//             o->oAction = 3;
//             o->oTimer = 0;
//             }
//         }

//     if (o->oAction == 3) {
//         if (o->oForwardVel < 0.0f) {
//             o->oForwardVel += 2.0f;
//             }
//             else
//             {
//             if (o->oTimer > 200) {
//                 o->oTimer = 0;
//                 o->oAction = 0;
//                 }
//             }
//         }

//     }

// void loop_bone_gate(void) {
//     switch (o->oAction) {
//         case 0:
//         if (gMarioState->SwitchPressed == 10) {
//             o->oAction = 1;
//             switch (o->oBehParams2ndByte) {
//                 case 0:
//                     run_event(2);
//                 break;
//                 case 1://shell sewers gate
                    
//                 break;
//                 }
//             }

//         break;
//         case 1:
//         switch (o->oBehParams2ndByte) {
//             case 0:
//             if ((o->oTimer < 60)&&(o->oTimer > 30)) {
//                 o->oPosY += 15.0f;
//                 }
//             break;
//             case 1://shell sewers gate
//                 obj_mark_for_deletion(o);
//             break;
//             }
//         break;
//         }
//     }

// u8 poundsound;

// void loop_bone_swap_gate(void) {
//     u8 crateblockaddition;
//     u8 triggerd = gMarioState->SwitchPressed == 11;
//     struct Object *potentialcrate;
//     potentialcrate = cur_obj_nearest_object_with_behavior(bhvMetalCrate);

//     crateblockaddition = 0;
//     if (potentialcrate != NULL) {
//         if ((potentialcrate->oPosZ < o->oPosZ+50.0f)&&(potentialcrate->oPosZ > o->oPosZ-50.0f)&&(lateral_dist_between_objects(o,potentialcrate) < 700.0f)) {
//             crateblockaddition += 200.0f;
//             }
//         }

//     if (o->oBehParams2ndByte == 1) {
//         triggerd = !triggerd;
//         }

//     if (triggerd != o->oAction) {
//         o->oAction = triggerd;
//         poundsound = TRUE;
//         }

//     if (triggerd) {
//         if (o->oPosY < o->oHomeY+500.0f) {
//             o->oPosY += 30.0f;
//             }
//         }
//     else
//         {
//         if (o->oPosY > o->oHomeY+crateblockaddition) {
//             o->oPosY -= 30.0f;
//             }
//             else
//             {
//             o->oPosY = o->oHomeY+crateblockaddition;
//             if (poundsound) {
//                 poundsound = FALSE;
//                 cur_obj_play_sound_2(SOUND_GENERAL_ELEVATOR_LAND);
//                 }
//             }
//         }

//     }

// //this sucks but i dont care
// //stretchblock
// s8  veltable[] = {  -2,   -1,    0,     1,     2};
// f32 scatable[] = {1.0f,0.99f,0.98f,0.985f,0.995f};

// void bhv_turnblock_update(void) {
//     struct Object *child;
//     u8 i;
//     o->oDontInertia = TRUE;

//     if (o->oAction == 0) {
//         for (i = 0; i < 5; i++) {
//             child = spawn_object(o,0xFE,bhvTurnBlock);
//             child->oAction = 1;
//             child->oBehParams2ndByte = i;
//             }
//         o->oAction = 2;
//         }

//     if (o->oAction == 2) {
//         if (o->oDistanceToMario > 4000.0f) {
//             o->oAction = 3;
//             }
//         }

//     if (o->oAction == 3) {
//         if (o->oDistanceToMario < 4000.0f) {
//             o->oAction = 0;
//             }
//         }

//     if (o->oAction == 1) {

//         if (o->parentObj->oAction == 3) {
//             obj_mark_for_deletion(o);
//             }

//         obj_scale(o,scatable[o->oBehParams2ndByte]);
//         o->oForwardVel = veltable[o->oBehParams2ndByte]*2;
//         if (o->oTimer > 99) {
//             o->oForwardVel = 0;
//             obj_scale(o,1.0f);
//             }
//         if (o->oTimer > 120) {
//             obj_scale(o,scatable[o->oBehParams2ndByte]);
//             o->oForwardVel = veltable[o->oBehParams2ndByte]*(-2);
//             }
//         if (o->oTimer > 219) {
//             o->oForwardVel = 0;
//             obj_scale(o,1.0f);
//             }
//         if (o->oTimer > 240) {
//             o->oTimer = 0;
//             o->oPosX = o->oHomeX;
//             o->oPosY = o->oHomeY;
//             o->oPosZ = o->oHomeZ;
//             }
        
//         if (o->parentObj->oBehParams2ndByte == 0) {
//             cur_obj_move_using_fvel_and_gravity();
//             }
//             else
//             {
//             o->oVelY = o->oForwardVel;
//             o->oPosY += o->oVelY;
//             }

//         o->oVelX = 0;
//         o->oVelZ = 0;
//         }
//     }

// void bhv_scroll_obj() {
//         o->oPosZ -= 90.0f;
//         if (o->oPosZ < o->oHomeZ - 16384.0f) {
//             o->oPosZ += 16384.0f;
//         }
//     }

// void bhv_truck() {
//     struct Surface *ptr;

//     if (o->oBehParams2ndByte != 2) {
//         if ((o->oPosZ < 15000)&&(o->oPosZ > -14000)&&(o->oBehParams2ndByte < 2)) {
//             load_object_collision_model();
//         }
//     } else {
//         load_object_collision_model();//be hard unconditionally
//     }

//     //bowser truck (careens off)
//     if (o->oBehParams2ndByte == 2) {
//         o->oPosX += o->oVelX;
//         if (o->oVelX > -60.0f) {
//             o->oVelX -= 1.5f;
//             }
//         switch(o->oAction) {
//             case 0:
//                 //vroom vroom
//                 o->oHomeY = find_floor(o->oPosX, o->oPosY, o->oPosZ, &ptr);
//                 if (o->oHomeY < 8000.0f) {
//                     o->oAction = 1;
//                 }
//             break;
//             case 1:
//                 o->oFaceAnglePitch += 0x22;
//                 o->oPosY += o->oVelY;
//                 if (o->oVelY > -80.0f) {
//                     o->oVelY-= 1.5f;
//                     }
//                 if (o->oPosY < -800.0f) {
//                     play_sound(SOUND_OBJ_DIVING_INTO_WATER, gGlobalSoundSource);
//                     mark_obj_for_deletion(o);
//                 }
//             break;
//         }
//         }

//     //backwash truck
//     if (o->oBehParams2ndByte == 1) {
//         cur_obj_move_using_fvel_and_gravity();

//         o->oForwardVel = 140.0f;
//         if (lateral_dist_between_objects(o,gMarioObject) < 4000.0f) {
//             o->oForwardVel = 40.0f;
//         }

//         if (o->oPosZ < -32768.0f) {
//             o->oPosZ = 32768.0f;
//         }

//         //make red coin
//         if (o->oHealth != 1) {
//             o->oHealth = 1;
//             o->prevObj = spawn_object(o,MODEL_RED_COIN, bhvRedCoin);
//             o->prevObj->prevObj = o;
//         }

//         if (o->prevObj != NULL) {
//             o->prevObj->oPosX = o->oPosX;
//             o->prevObj->oPosY = o->oPosY + 800.0f;
//             o->prevObj->oPosZ = o->oPosZ+1000.0f;
//             }

//         }

//     if (o->oBehParams2ndByte == 0) {//forwardwash truck
//         switch(o->oAction) {
//             case 0:
//             if (cur_obj_is_mario_on_platform()) {
//                 o->oAction ++;
//                 o->oHealth = 75;
//                 }
//             break;
//             case 1:
//                 o->oForwardVel = 12.0f;
//                 cur_obj_move_using_fvel_and_gravity();

//                 if (o->oTimer > o->oHealth) {
//                     o->oHealth -= 3;
//                     if (o->oHealth < 45) {
//                         o->oHealth = 45;
//                         }
//                     o->oTimer = 0;
//                     o->prevObj = spawn_object(o,0xF8, bhvBadSign);
//                     o->prevObj->oPosZ = 32768.0f;
//                     o->prevObj->oFaceAngleYaw = 0;
//                     }

//                 if (o->oPosZ > o->oHomeZ + 5000.0f) {
//                     o->oForwardVel = 0;
//                     o->oAction ++;
//                     }
//             break;
//             case 2:
//                 o->oForwardVel = 0;
//                 cur_obj_move_using_fvel_and_gravity();
//             break;
//             }
//         }
//     }

void bhv_podoboo_loop() {
    struct Surface *sp24;
    struct Object *spobj;
    u32 i;

    //Home X is where the Podoboo rests in the lava.
    //Home Y is the peak of the Podoboo's jump

    switch(o->oAction) {
        case 0: //Init
        o->oHomeX = find_floor(o->oPosX, o->oPosY, o->oPosZ, &sp24);
        o->oAction++;
        o->oFaceAngleRoll = 0x7FFF;
        o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
        break;
        case 1: //Fall into lava
        o->oVelY -= 2.0f;
        o->oPosY += o->oVelY;

        //rotate back down
        if (o->oFaceAngleRoll < 0x7FFF) {
            o->oFaceAngleRoll += 0x0FFF;
            }
            else
            {
            o->oFaceAngleRoll = 0x7FFF;
            }

        if (o->oPosY < o->oHomeX) {
            for (i = 0; i < 3; i++) {
                spobj = spawn_object(o, MODEL_RED_FLAME, bhvKoopaShellFlame);
                spobj->oPosY += 40.0f;
                }
            cur_obj_play_sound_2(SOUND_OBJ_DIVING_INTO_WATER);
            o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            o->oAction ++;
            o->oTimer = 0;
            o->oPosY = o->oHomeX;
            o->oVelY = 0;
            }
        break;
        case 2: //Sit idle in lava
            cur_obj_become_intangible();
            //If mario is too far away, just break
            if (o->oDistanceToMario > 2500.0f) {
                o->oTimer = 0;
                }

            if (o->oTimer > 35) {
                spobj = spawn_object(o, MODEL_RED_FLAME, bhvKoopaShellFlame);
                spobj->oPosY += 40.0f;
            }

            if (o->oTimer > 50) {
                //Calculate upward velocity
                o->oHomeZ = o->oPosY;
                while(o->oHomeZ < o->oHomeY) {
                    o->oVelY += 1.5;
                    o->oHomeZ += o->oVelY;
                    }
                //End
                cur_obj_become_tangible();
                o->oAction ++;
                o->oFaceAngleRoll = 0x0;
                cur_obj_play_sound_2(SOUND_OBJ_FLAME_BLOWN);
                o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
                }
        break;
        case 3: //New hop out 
            o->oPosY += o->oVelY;
            o->oVelY -= 2.0f;

            if (o->oVelY < 0.0f) {
                o->oAction = 1;
                }
        break;
        }
    }

// void bhv_badsign() {
//         o->oPosZ -= 90.0f;
//         if (o->oPosZ < -16384.0f) {
//             obj_mark_for_deletion(o);
//         }
//     }

// void bhv_garage() {
//     switch(o->oAction) {
//         case 0:
//         if ((o->oDistanceToMario < 400.0f)&&(gMarioState->numStars >= 10)) {
//             o->oAction ++;
//             o->oTimer = 0;
//             }
//         break;
//         case 1:
//             cur_obj_play_sound_1(SOUND_ENV_METAL_BOX_PUSH);
//             o->oPosY += 10.0f;
//             if (o->oTimer > 35) {
//                 o->oAction ++;
//                 }
//         break;
//         }
//     }

// void bhv_bad_apple() {
//     if ((o->oDistanceToMario < 600.0f)&&(gMarioState->BadAppleActivate == FALSE)) {
//         gMarioState->BadAppleActivate = TRUE; // activate bad apple
//         stop_background_music(SEQUENCE_ARGS(4, SEQ_LEVEL_INSIDE_CASTLE));
//         //play_music(SEQ_PLAYER_ENV, SEQUENCE_ARGS(15, SEQ_STREAMED_BAD_APPLE), 0);
//         }
//     }

// void bhv_valve() {
//     if (o->oBehParams2ndByte) {
//         o->oMoveAngleYaw = sins(o->oTimer * 0x400) * 2000;
//         }
//         else
//         {
//         o->oMoveAngleYaw = coss(o->oTimer * 0x400) * 2000;
//         }
//     }

// void bhv_crablet_spawner() {
//     struct Object *spawnenemy;

//     switch(o->oAction) {
//         case 0:
//             spawnenemy = spawn_object(o,0xFE, bhvCrabletSpawned);
//             spawnenemy->oDrawingDistance = 20000.0f;
//             spawnenemy->oNumLootCoins = 0;
//             o->oAction = 1;
//             o->oHealth = gMarioState->BossHealth;
//         break;
//         case 1:
//             if (o->oHealth != gMarioState->BossHealth) {
//                 o->oAction = 0;
//             }
//         break;
//     }

// }

// u8 EnemyPool[11][10] = {
//     {1,1,1,1,1,1,1,1,1,1},//1
//     {2,2,2,1,1,1,1,1,1,1},//2
//     {3,2,2,2,1,1,1,1,1,1},//3
//     {3,3,3,2,2,2,2,2,1,1},//4
//     {4,4,3,3,2,2,2,2,2,2},//5
//     {1,1,4,4,4,4,3,1,1,1},//6
//     {4,4,4,3,3,3,3,3,2,2},//7
//     {3,3,3,3,3,2,2,2,2,2},//8
//     {5,5,1,1,1,1,1,1,1,1},//9
//     {5,5,5,1,1,2,2,2,1,6},//10
//     {5,5,5,4,4,6,6,3,3,2},//rest
// };

// void bhv_enemy_arena_spawner() {
//     s16 true_enemies_left = gMarioState->EA_LEFT - gMarioState->EA_ACTIVE;
//     u8 random = 0;
//     struct Object *spawnenemy;

//         if (o->oTimer > 60) {
//             o->oTimer = 0;

//             if ((gMarioState->EA_ACTIVE < 10)&&(true_enemies_left > 0)) {
//                 random = eRandomMinMaxU16(0,9);
//                 switch (EnemyPool[gMarioState->EA_WAVES-1][random]) {
//                     case 1:
//                     spawnenemy = spawn_object(o,MODEL_GOOMBA, bhvGoomba);
//                     break;
//                     case 2:
//                     spawnenemy = spawn_object(o,0xE1, bhvRex);
//                     break;
//                     case 3:
//                     spawnenemy = spawn_object(o,0xE7, bhvChicken);
//                     spawnenemy->oBehParams2ndByte = 2;
//                     break;
//                     case 4:
//                     spawnenemy = spawn_object(o,0xFE, bhvScuttlebug);
//                     spawnenemy->oHealth = 4;//?
//                     break;
//                     case 5:
//                     spawnenemy = spawn_object(o,0xEE, bhvHammerBro);
//                     break;
//                     case 6:
//                     spawnenemy = spawn_object(o,MODEL_MARIO, bhvPhantasm);
//                     spawnenemy->oBehParams2ndByte = 2;
//                     spawnenemy->oHomeY = -5000.0f;
//                     break;
//                     }
                
//             spawnenemy->oFlags |= OBJ_FLAG_ACTIVE_FROM_AFAR;
//             gMarioState->EA_ACTIVE ++;
//             }
//         }
//     }

// void bhv_SafeZone_function() {
//     f32 dist = o->oBehParams2ndByte*400.0f;
//     if (o->oBehParams2ndByte==0) {
//         dist = 200.0f;
//     }
//     if (o->oDistanceToMario < dist) {
//         gMarioState->ISSAFE = TRUE;
//         }
//     }

void noteblock_function(void) {

    o->oDontFallDamage = TRUE;

    o->oPosY = o->oHomeY + (sins(o->oTimer*5000) * o->oVelY);
    o->oVelY *= 0.95f;

    if ((gMarioState->action != ACT_LVUP_DANCE)&&(gMarioState->action != ACT_STAR_DANCE_NO_EXIT)&&(gMarioState->health > 0x100)&&cur_obj_is_mario_on_platform()) {
            mario_stop_riding_and_holding(gMarioState);
            o->oTimer = 0;
            o->oVelY = 50.0f;
            cur_obj_play_sound_2(SOUND_GENERAL_CRAZY_BOX_BOING_SLOW);
            set_mario_action(gMarioState, ACT_DOUBLE_JUMP, 0);
            gMarioStates[0].vel[1] = 95.0f;
            gMarioState->squishTimer = 0;
        }
    }

// struct Object *post;

// void bhv_pig_loop(void) {
//     f32 distance;
//     struct Object *musicbox;

//     //o->oAnimState = 1;

//     musicbox = cur_obj_nearest_object_with_behavior(bhvBreakableBoxSmall);


//     o->oFaceAngleYaw = approach_s16_asymptotic(o->oFaceAngleYaw,o->oMoveAngleYaw,4);

//     switch (o->oAction) {
//         case 0://init
//             post = spawn_object(o,0x00,bhvStaticObject);
//             o->oAction = 1;
//         break;
//         case 1://roam
//             o->oPosY += o->oVelY;
//             o->oVelY -= 2.0f;
//             o->oForwardVel = 30.0f;

//             distance = lateral_dist_between_objects(o,post);

//             if (o->oPosY < o->oHomeY) {
//                 o->oVelY = 20.0f;
//                 o->oPosY = o->oHomeY;
//                 if (distance < 1000.0f) {
//                     o->oMoveAngleYaw = random_u16();
//                     }
//                     else
//                     {
//                     o->oMoveAngleYaw = obj_angle_to_object(o,post);
//                     }
//                 }
//             if (lateral_dist_between_objects(gMarioObject,post) < 1200.0f) {
//                 o->oMoveAngleYaw = o->oAngleToMario;
//                 //o->oPosY = gMarioState->pos[1];
//                 o->oVelY = gMarioState->vel[1];
//                 o->oForwardVel = 60.0f;
//                 }

//             o->oPosX += sins(o->oMoveAngleYaw) * o->oForwardVel;
//             o->oPosZ += coss(o->oMoveAngleYaw) * o->oForwardVel;

//             if ((lateral_dist_between_objects(o,musicbox) < 1300.0f)||((o->oDistanceToMario < 1300.0f)&&near_music_box)) {
//                 o->oAction = 3;
//                 cur_obj_init_animation_with_sound(2);
//             }

//             if (o->oDistanceToMario < 400.0f) {
//                 o->oAction = 2;
//                 }
//         break;
//         case 2://throw mario
//             o->oPosY += o->oVelY;
//             o->oVelY -= 2.0f;
//             if (o->oPosY < o->oHomeY) {
//                 o->oPosY = o->oHomeY;
//                 o->oVelY = 0.0f;
//                 }

//             if (o->oTimer < 15) {
//                 gMarioState->vel[1] = 0.0f;
//                 gMarioState->faceAngle[1] = o->oAngleToMario;
//                 gMarioState->pos[1] = o->oPosY+150.0f;
//                 gMarioState->pos[0] = o->oPosX + sins(o->oMoveAngleYaw) * 300.0f;
//                 gMarioState->pos[2] = o->oPosZ + coss(o->oMoveAngleYaw) * 300.0f;
//                 }

//             switch(o->oTimer) {
//                 case 1:
//                 gMarioObject->oInteractStatus |= INT_STATUS_MARIO_THROWN_BY_OBJ;
//                 set_mario_action(gMarioState, ACT_THROWN_BACKWARD, 0);
//                 cur_obj_init_animation_with_sound(1);
//                 break;
//                 case 15:
//                 gMarioState->hurtCounter = 10;
//                 cur_obj_play_sound_2(SOUND_OBJ_HEAVEHO_TOSSED);
//                 gMarioStates->forwardVel = 45.0f;
//                 gMarioStates->vel[1] = 95.0f;
//                 break;
//                 case 30:
//                 cur_obj_init_animation_with_sound(0);
//                 o->oAction = 1;
//                 break;
//                 }
//         break;
//         case 3://go to sleep
//             o->oPosY += o->oVelY;
//             o->oVelY -= 2.0f;
//             if (o->oPosY < o->oHomeY) {
//                 o->oPosY = o->oHomeY;
//                 o->oVelY = 0.0f;
//                 }
//         break;
//         }
//     }

// void bhv_GhostGate(void) {
//     struct Object *keyobj;
//     u8 allowopen;

//     keyobj = cur_obj_nearest_object_with_behavior(bhvBreakableBoxSmall);

//     allowopen = FALSE;
//     if (keyobj != NULL) {
//         if (keyobj->oBehParams2ndByte == 2) {
//             if (lateral_dist_between_objects(o,keyobj) < 400.0f) {
//                 allowopen = TRUE;
//                 }
//             }
//         }

//     switch (o->oAction) {
//         case 0:
//         if (allowopen) {
//             o->oAction ++;
//             obj_mark_for_deletion(keyobj);
//             }
//         break;
//         case 1:
//             obj_scale(o,1.0f - ((f32)o->oTimer)/50.0f);
//             if (o->oTimer > 50) {
//                 obj_mark_for_deletion(o);
//                 }
//         break;
//         }
//     }

// struct Object *deleteobj;

// void shipmove(void) {
//     o->oPosX = sins(o->oMoveAngleYaw) * 15900.0f;
//     o->oPosZ = coss(o->oMoveAngleYaw) * 15900.0f;
//     o->oMoveAngleYaw += 0x50;
//     }

// void detect_damage(void) {
//     deleteobj = cur_obj_nearest_object_with_behavior(bhvBooball);
//     if (deleteobj != NULL) {
//         if (lateral_dist_between_objects(o,deleteobj) < 6000.0f) {

//             if (save_file_get_badge_equip() & (1 << BADGE_SLAYER)) {
//                 gMarioState->BossHealth -= 2;
//             } else {
//                 gMarioState->BossHealth --;
//             }
//             o->oVelX = 5000.0f;
//             spawn_object(deleteobj, MODEL_EXPLOSION, bhvExplosion);
//             obj_mark_for_deletion(deleteobj);
//             }
//         }
//     }

// void bhv_evil_ship_loop(void) {

//     deleteobj = cur_obj_nearest_object_with_behavior(bhvBobomb);
//     if (deleteobj != NULL) {
//         obj_mark_for_deletion(deleteobj);
//         }
//     deleteobj = cur_obj_nearest_object_with_behavior(bhvFadingWarp);
//     if (deleteobj != NULL) {
//         obj_mark_for_deletion(deleteobj);
//         }

//     o->oFaceAngleRoll = sins(o->oTimer*5000) * o->oVelX;
//     o->oVelX *= 0.95f;

//     o->oInteractStatus = 0;
//     switch(o->oAction) {
//         case 0:
//         o->oAction++;
//         o->oVelX = 0;
//         shipmove();
//         o->oHomeY = o->oPosY;
//         o->oHomeX = 0.0f;
//         o->oHomeZ = 0.0f;
//         o->oPosY -= 5000.0f;
//         o->oVelY = 140.0f;
//         break;
//         case 1:
//         o->oPosY += o->oVelY;
//         o->oVelY -= 2.0f;
//         if (o->oVelY < 0) {
//             o->oAction++;
//             o->oHomeY = o->oPosY;
//             }
//         o->oFaceAngleYaw = o->oMoveAngleYaw+0x4000;
//         break;
//         case 2:
//             shipmove();
//             detect_damage();
//             o->oFaceAngleYaw = approach_s16_asymptotic(o->oFaceAngleYaw,o->oMoveAngleYaw+0x4000,4);
//             if ((gMarioState->BossHealth < 1)&&(o->oTimer > 25)) {
//                 o->oFaceAnglePitch -= 0x50;
//                 o->oAction = 4;
//                 }
//             if ((o->oTimer%(24+gMarioState->BossHealth) == 0)&&(o->oTimer > 40)&&(o->oTimer < 160)) {
//                 deleteobj = spawn_object(gMarioObject,MODEL_BBH_STAIRCASE_STEP,bhvPuddle);
//                 deleteobj->oHomeY = find_floor(deleteobj->oPosX, deleteobj->oPosY, deleteobj->oPosZ, &sp24);
//                 deleteobj->oPosY += 1200.0f;
//                 }
//             if (o->oTimer > 260) {
//                 o->oAction++;
//                 }
//         break;
//         case 3:
//             detect_damage();

//             if (o->oTimer > 30) {
//                 o->oPosX += sins(o->oMoveAngleYaw) * (100.0f-(f32)(gMarioState->BossHealth*5));
//                 o->oPosZ += coss(o->oMoveAngleYaw) * (100.0f-(f32)(gMarioState->BossHealth*5));
//                 if (cur_obj_lateral_dist_to_home() > 16000.0f) {
//                     o->oMoveAngleYaw = cur_obj_angle_to_home()+0x8000;
//                     o->oAction = 2;
                    
//                     }
//                 }
//                 else
//                 {
//                 o->oMoveAngleYaw = o->oFaceAngleYaw;
//                 o->oFaceAngleYaw = approach_s16_asymptotic(o->oFaceAngleYaw,o->oAngleToMario,4);
//                 }
//         break;
//         case 4:
//             if (o->oTimer < 120) {
//                 o->oFaceAnglePitch -= 0x50;
//                 }
//             o->oPosY -= 10.0f;

//             if (o->oTimer == 250) {
//                 spawn_default_star(gMarioState->pos[0],gMarioState->pos[1]+300.0f,gMarioState->pos[2]);
//                 }
//         break;
//         }
//     }

// void bhv_puddle_loop(void) {

//     switch(o->oAction) {
//         case 0:
//             obj_scale(o,1.0f);
//             o->oPosY -= 40.0f-(gMarioState->BossHealth*3);
//             o->oFaceAnglePitch += 0x100;
//             o->oFaceAngleRoll += 0x200;
//             o->oFaceAngleYaw += 0x300;
//             if (o->oDistanceToMario < 125.0f) {
//                 spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
//                 obj_mark_for_deletion(o);
//                 }
//             if (o->oPosY < o->oHomeY+20.0f) {
//                 /*
//                 o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_BBH_HAUNTED_DOOR];
//                 spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
//                 o->oFaceAnglePitch = 0;
//                 o->oFaceAngleRoll = 0;
//                 o->oAction++;
//                 */
//                 spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
//                 obj_mark_for_deletion(o);
//                 //quicksand puddles are not a fun mechanic
//                 }
//         break;
//         case 1:
//             o->oPosY = o->oHomeY + 5.0f;
//             if (o->oTimer < 180-(gMarioState->BossHealth*4)) {
//                 obj_scale(o,(f32)(o->oTimer)/3.0f);
//                 }
//             if (o->oTimer > 1800) {
//                 obj_mark_for_deletion(o);
//                 }
//         break;
//         }
//     }

// void bhv_boocannon_loop(void) {
//     struct Object *ball;

//     o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;

//     deleteobj = cur_obj_nearest_object_with_behavior(bhvVoidShip);
//     if (deleteobj != NULL) {
//         o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
//         load_object_collision_model();
//         }
    
//     if (cur_obj_was_attacked_or_ground_pounded() && (o->oTimer > 30)) {
//         ball = spawn_object(o,0xF6,bhvBooball);
//         ball->oPosY += 100.0f;
//         ball->oPosX += sins(o->oMoveAngleYaw) * 300.0f;
//         ball->oPosZ += coss(o->oMoveAngleYaw) * 300.0f;
//         play_sound(SOUND_GENERAL_BOWSER_BOMB_EXPLOSION, gGlobalSoundSource);
//         o->oTimer = 0;
//         }
//     }

// void bhv_booball_loop(void) {
//     o->oPosX += sins(o->oMoveAngleYaw) * 170.0f;
//     o->oPosZ += coss(o->oMoveAngleYaw) * 170.0f;
//     o->oFaceAngleRoll += 0x300;

//     if (o->oTimer > 400) {
//         obj_mark_for_deletion(o);
//         }
//     }

// //crimas only
// void bhv_darius_spawner(void) {
//     struct Object *obj;
//     if (gMarioState->numStars > 5) {
//         obj = spawn_object(o,MODEL_WOODEN_SIGNPOST, bhvMessagePanel);
//         obj->oBehParams2ndByte = 34;
//         obj = spawn_object(o,0xE6, bhv_costume_token);
//         obj->oPosX += 300.0f;
//         obj->oBehParams2ndByte = 8;
//         }
//     }

// void bhv_trash(void) {

//     }

// void bhv_mess(void) {
//     f32 dist;
//     // u16 random_range; // unused?
//     struct Object *obj;
//     switch(o->oAction) {
//         case 0:
//                 o->oAction = 1;
//                 o->oFaceAngleYaw = random_u16();
//                 //random_range = random_u16()%3;
//                 //switch (random_range) {
//                 //    case 0:
//                 //    o->header.gfx.sharedChild = gLoadedGraphNodes[0xF2];
//                 //    break;
//                 //    case 1:
//                 //    o->header.gfx.sharedChild = gLoadedGraphNodes[0xF3];
//                 //    break;
//                 //    case 2:
//                 //    o->header.gfx.sharedChild = gLoadedGraphNodes[0xF4];
//                 //    break;
//                 //    }
//         break;
//         case 1:
//         if ((o->oDistanceToMario<70.0f)&&(!gMarioState->MessHeld)) {
//             o->oAction =2;
//             gMarioState->MessHeld = TRUE;
//             cur_obj_play_sound_2(SOUND_GENERAL_HAUNTED_CHAIR_SWISH_AIR);
//             }
//         break;
//         case 2:
//             o->oPosX = gMarioState->pos[0];
//             o->oPosY = gMarioState->pos[1]+200.0f;
//             o->oPosZ = gMarioState->pos[2];
            
//             obj = cur_obj_nearest_object_with_behavior(bhvTrash);
//             dist = dist_between_objects(gMarioObject,obj);
//             if ((dist < 150.0f)&&(obj)) {
//                 gMarioState->SockCollection ++;
//                 gMarioState->MessHeld = FALSE;
//                 o->oAction = 3;
//                 cur_obj_play_sound_2(SOUND_GENERAL_SWISH_AIR_UNUSED);
//                 o->oPosX = obj->oPosX;
//                 o->oPosY = obj->oPosY+(gMarioState->SockCollection*30.0f);
//                 o->oPosZ = obj->oPosZ;
//                 }
//         break;
//         case 3:
//         //print_text_fmt_int(20, 185, "TASKS LEFT %d", 10-gMarioState->MessNumber);
//         //if (o->oTimer > 30) {
//             //obj_mark_for_deletion(o);
//             //}
//         break;
//         }

//     }
// //crimas only

// void bhv_tollbridge_loop(void) {
//     switch(o->oAction) {
//         case 0:
//             o->oPosY -= 400.0f;
//             o->oAction = 1;
//         break;
//         case 1:
//             if (gMarioState->TollPaid) {
//                 o->oAction = 2;
//             }
//         break;
//         case 2:
//             if (o->oPosY < o->oHomeY) {
//                 o->oPosY += 15.0f;
//             } else {
//                 o->oPosY = o->oHomeY;
//             }
//         break;
//     }
// };

// void bhv_bookelevator_loop(void) {
//     switch(o->oAction) {
//         case 0:
//             o->oFaceAngleYaw = 0x2000;
//             o->oAction = 1;
//         break;
//         case 1:
//             if (cur_obj_was_attacked_or_ground_pounded() && gMarioState->numStars >= 1) {
//                 o->oAction = 2;
//             }
//         break;
//         case 2:
//             if (o->oPosY < o->oHomeY+600.0f) {
//                 o->oPosY += 15.0f;
//                 cur_obj_play_sound_1(SOUND_ENV_ELEVATOR1);
//             } else {
//                 o->oPosY = o->oHomeY+600.0f;
//                 o->oAction = 3;
//             }
//         break;
//         case 3:
//             if ((o->oFaceAngleYaw != 0)&&(o->oTimer>30)) {
//                 o->oFaceAngleYaw -= 0x100;
//                 cur_obj_play_sound_1(SOUND_ENV_ELEVATOR1);
//             }
//         break;
//     }
// };


// f32 charge;
// void bhv_evil_pig(void) {
//     struct Object *obj;
//     f32 dist;
//     o->oInteractStatus = 0;
//     obj = cur_obj_nearest_object_with_behavior(bhvTarget);
//     cur_obj_update_floor_and_walls();
//     cur_obj_move_standard(-5);

//     if (o->oPosY < o->oHomeY-100.0f) {
//         //safeguard
//         o->oPosX = o->oHomeX;
//         o->oPosY = o->oHomeY;
//         o->oPosZ = o->oHomeZ;
//     }

//     switch(o->oAction) {
//         case 0://init
//             o->oAction = 1;
//             gMarioState->BossHealth = 7;
//             gMarioStates->BossHealthMax = 7;
//         break;
//         case 1://face
//             o->oForwardVel = 0.0f;
//             o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw,o->oAngleToMario,4);
//             if (o->oTimer%30 == 0) {
//                 cur_obj_play_sound_2(SOUND_ACTION_QUICKSAND_STEP);
//                 cur_obj_init_animation_with_sound(0);
//                 cur_obj_init_animation_with_sound(3);
//                 }

//             if (o->oTimer > 90) {
//                 o->oAction = 2;
//                 o->oForwardVel = 30.0f;
//                 charge = 30.0f;
//                 cur_obj_init_animation_with_sound(0);
//                 cur_obj_play_sound_2(SOUND_GENERAL_RACE_GUN_SHOT);
//                 }
//         break;
//         case 2://charge
//             o->oForwardVel = charge;
//             charge += .5f;
//             if (obj != NULL) {
//                 dist = dist_between_objects(o,obj);
//                 if ((dist < 400.0f)&&(obj->oAction == 0)) {
//                     obj->oAction = 1;
//                     o->oAction = 3;
//                     o->prevObj = obj;
//                     cur_obj_play_sound_2(SOUND_OBJ_BULLY_METAL);
//                     o->oForwardVel = 0.0f;
//                     cur_obj_init_animation_with_sound(2);
//                     if (save_file_get_badge_equip() & (1 << BADGE_SLAYER)) {
//                         gMarioState->BossHealth -= 2;
//                     }else{
//                         gMarioState->BossHealth --;
//                     }
//                     if (gMarioStates->BossHealth <= 0) {
//                         o->oAction = 4;    
//                     }
//                 }
//             }
//             if (o->oMoveFlags & OBJ_MOVE_HIT_EDGE) {
//                 o->oAction = 1;
//                 cur_obj_init_animation_with_sound(0);
//                 cur_obj_init_animation_with_sound(3);
//             }
//         break;
//         case 3://target hit
//             if (o->oTimer > 30) {
//                 o->oAction = 1;
//                 cur_obj_init_animation_with_sound(0);
//                 cur_obj_init_animation_with_sound(3);
//             }
//             o->prevObj->oFaceAnglePitch -= 0x120;
//         break;
//         case 4://die
//             if (o->oTimer == 50) {
//                 o->oBehParams = 0x06000000;
//                 spawn_default_star(gMarioState->pos[0],gMarioState->pos[1]+300.0f,gMarioState->pos[2]);
//                 }
//         break;
//     }
// }

// void bhv_cheese(void) {
//     if (o->oDistanceToMario < 150.0f) {
//         cur_obj_play_sound_2(SOUND_OBJ2_PIRANHA_PLANT_BITE);
//         spawn_object(o, MODEL_SPARKLES, bhvCoinSparklesSpawner);
//         gMarioState->CheeseCollection ++;
//         obj_mark_for_deletion(o);
//     }
// }

// void bhv_vaccum(void) {
//     struct Surface *sp24;
//     u8 amount;

//     if ((o->oAction==0) && (cur_obj_update_dialog_with_cutscene(2, 1, CUTSCENE_DIALOG, DIALOG_056))) {
//         play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_BOSS), 0);
//         o->oAction = 3;
//         o->oTimer = 0;
//     }
//     if (o->oAction == 3) {
//         if (o->oTimer > 60) {
//             o->oAction = 2;
//         }
//     }

//     if ((gMarioState->action & ACT_GROUP_MASK) == ACT_GROUP_CUTSCENE) {
//         o->oPosY = find_floor(o->oPosX, o->oPosY, o->oPosZ, &sp24);
//         return;
//     }
//     if (o->oAction != 2) {
//         cur_obj_play_sound_1(SOUND_ENV_WIND1);
//         return;
//     }

//     gMarioObject->oInteractStatus |= INT_STATUS_MARIO_THROWN_BY_OBJ;

//     if ((gMarioState->posDelay[0]!=o->oPosX)&&(gMarioState->posDelay[2]!=o->oPosZ)) {
//         o->oMoveAngleYaw = -atan2s(gMarioState->posDelay[0]-o->oPosX,gMarioState->posDelay[2]-o->oPosZ);
//         }
//     o->oPosX = gMarioState->posDelay[0];
//     o->oPosY = gMarioState->posDelay[1];
//     o->oPosZ = gMarioState->posDelay[2];

//     if (o->oDistanceToMario < 40.0f) {
//         set_mario_action(gMarioState, ACT_EATEN_BY_BUBBA, 0);
//         o->oAction = 1;
//     }

//     amount = (u8)(((f32)(o->oTimer%140)/90)*100);
//     if (amount > 100) {
//         amount = 100;    
//     }

//     gMarioState->BossHealth = (s8)(amount);
//     gMarioState->BossHealthMax = 100;

//     if (o->oTimer%140 > 90) {
//         cur_obj_play_sound_1(SOUND_ENV_WIND1);
//         gMarioState->pos[0] -= sins(o->oAngleToMario)*10.0f;
//         gMarioState->pos[2] -= coss(o->oAngleToMario)*10.0f;
//     }

// }

// void bhv_smb_platform(void) {
//     if (o->oBehParams2ndByte==0) {
//         o->oPosX = o->oHomeX + sins((o->oTimer*200)+o->oMoveAngleYaw)*400.0f;
//         o->oPosY = o->oHomeY + coss((o->oTimer*200)+o->oMoveAngleYaw)*400.0f;
//     } else {
//         o->oPosX = o->oHomeX + sins((-o->oTimer*200)+o->oMoveAngleYaw)*400.0f;
//         o->oPosY = o->oHomeY + coss((-o->oTimer*200)+o->oMoveAngleYaw)*400.0f;
//     }

// }

// void bhv_smb_platform_spawn(void) {
//     struct Object *obj;
//     u8 i = 0;//.... (kitchen nightmare sound effect)
//     for (i = 0; i < 3; i++) {
//         obj = spawn_object(o,MODEL_SMB_PLATFORM,bhvSMBplatform);
//         obj->oMoveAngleYaw = i*21845;
//         obj->oBehParams2ndByte = o->oBehParams2ndByte;
//     }
// }

// void bhv_retrobill_spawner(void) {
//     struct Object *obj;
//     if ((o->oBehParams2ndByte==1)&&(o->oAction=0)){
//         o->oAction = 1;
//         o->oTimer = 45;
//     }
//     if ((o->oTimer > 90)&&(o->oDistanceToMario < 4000.0f)) {
//         o->oTimer = 0;
//         obj = spawn_object(o,MODEL_RETROBILL,bhvRetrobill);
//         obj->oBehParams2ndByte = o->oBehParams2ndByte;
//         cur_obj_play_sound_2(SOUND_OBJ_POUNDING_CANNON);
//     }
// }

// u8 secret_timer;
// void bhv_retro_pipe(void) {
//     s32 behparam1 = (gCurrentObject->oBehParams >> 24) & 0xFF;

//     if ((o->oDistanceToMario < 90.0f)&&(gPlayer1Controller->buttonDown & Z_TRIG)&&(o->oAction==0)) {
//         if (behparam1 == 0) {
//             o->oAction = 1;
//             cur_obj_play_sound_2(SOUND_MENU_ENTER_PIPE);
//             gMarioState->pos[0] = o->oPosX;
//             set_mario_action(gMarioState, ACT_WARP_PIPE, 0);
//             gMarioState->usedObj = o;
//         } else {
//             secret_timer ++;
//             if (secret_timer > 200) {
//                 secret_timer = 0;
//                 gMarioState->_2DSecret = TRUE;
//                 o->oAction = 1;
//             }
//         }
//     }
// }

// void bhv_retro_thwomp(void) {
//     switch(o->oAction) {
//         case 0:
//             //init
//             o->oHomeY = find_floor(o->oPosX, o->oPosY, o->oPosZ, &sp24);
//             o->oHomeX = o->oPosY;
//             o->oAction = 1;
//         break;
//         case 1:
//             //wait
//             if ((gMarioState->pos[0] > o->oPosX-200.0f)&&(gMarioState->pos[0] < o->oPosX+200.0f)&&(gMarioState->pos[1] < o->oPosY+300.0f)) {
//                 o->oAction = 2;
//                 o->oGravity = 0.0f;
//             }
//         break;
//         case 2:
//             //fall
//             o->oGravity -= 4.0f;
//             o->oPosY += o->oGravity;
//             if (o->oPosY < o->oHomeY) {
//                 o->oPosY = o->oHomeY;
//                 o->oAction = 3;
//                 if (o->oDistanceToMario < 1000.0f) {
//                     cur_obj_shake_screen(SHAKE_POS_LARGE);
//                     cur_obj_play_sound_2(SOUND_OBJ_THWOMP);
//                     }
//             }
//         break;
//         case 3:
//             //wait on ground
//             if (o->oTimer > 30) {
//                 o->oAction = 4;
//             }
//         break;
//         case 4:
//             //rise
//             o->oPosY += 8.0f;
//             if (o->oPosY > o->oHomeX) {
//                 o->oPosY = o->oHomeX;
//                 o->oAction = 1;
//             }
//         break;
//     }

// }

// void bhv_log2(void) {
//     switch(o->oAction) {
//         case 0://init
//             o->oAction = 1;
//             o->oPosY -= (f32)(o->oBehParams2ndByte*150);
//         break;
//         case 1://go down
//             load_object_collision_model();
//             o->oPosY -= 7.0f;
//             if (o->oPosY < -678.0f) {
//                 o->oAction = 3;
//             }

//         break;
//         case 2:
//             load_object_collision_model();
//             o->oPosY += 4.0f;
//             if (o->oPosY > o->oHomeY) {
//                 o->oAction = 1;
//                 o->oPosZ = o->oHomeZ;
//             }
//         break;
//         case 3:
//             if (o->oTimer > 5) {
//                 o->oPosY = o->oHomeY - 150.0f;
//                 o->oPosZ = o->oHomeZ - 150.0f;
//                 o->oAction = 2;
//             }
//         break;
//     }
// }

// void bhv_keydoor2(void) {
//     if (o->oAction == 1) {
//         if (o->oTimer > 5) {
//             obj_mark_for_deletion(o);
//         }
//     }
//     if ((o->oDistanceToMario < 350.0f)&&(o->oAction == 0)&&(gMarioState->MaskChase)) {
//         o->oAction = 1;
//         o->oTimer = 0;
//         cur_obj_hide();
//         cur_obj_become_intangible();
//         spawn_mist_particles_variable(0, 0, 200.0f);
//         spawn_triangle_break_particles(20, 138, 3.0f, 4);
//         cur_obj_shake_screen(SHAKE_POS_SMALL);
//         o->oPosY += 100.0f;
//         spawn_default_star(o->oPosX,o->oPosY,o->oPosZ);
//         cur_obj_play_sound_2(SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION);
//     }
// }

// void bhv_donut(void) {
//     switch(o->oAction) {
//         case 0://grow into place
//             cur_obj_scale((f32)(o->oTimer)/(30.0f));
//             if (o->oTimer > 29) {
//                 cur_obj_scale(1.0f);
//                 o->oAction = 1;
//             }
//         break;
//         case 1://wait for mario
//             load_object_collision_model();
//             if (gMarioObject->platform == o) {
//                 o->oAction = 2;
//             }
//         break;
//         case 2://shaking
//             load_object_collision_model();
//             o->oPosX = o->oHomeX + (f32)(o->oTimer%2==0)*4.0f;
//             if (o->oTimer > 30) {
//                 o->oAction = 3;
//             }
//         break;
//         case 3://fall
//             load_object_collision_model();
//             if (o->oVelY > -6.0f) {
//                 o->oVelY -= 1.0f;
//             }
//             o->oPosY += o->oVelY;
//             if (o->oTimer > 120) {
//                 o->oAction = 4;
//                 o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
//             }
//         break;
//         case 4://no collision

//             if (o->oTimer > 5) {
//                 o->oVelY = 0.0f;
//                 o->oAction = 0;
//                 o->oPosY = o->oHomeY;
//                 o->oPosX = o->oHomeX;
//                 cur_obj_scale(0.0f);
//                 o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
//             }
//         break;
//     }
// }

// u16 pathlengths[] = {
// 299,
// 899,
// 899,
// 395,
// 369,
// 310,
// };

// void bhv_minecart(void) {
//     // f32 a, b, c;
//     f32 a, b; // c is unused
//     u8 behparam1 = (o->oBehParams >> 24);
//     u16 pl = pathlengths[o->oBehParams2ndByte];
//     f32 (*Path)[6][3] = segmented_to_virtual(&blender_export);

//     switch(o->oAction) {
//         case 0://init
//             o->oPosX = Path[o->oTimer%pl][o->oBehParams2ndByte][0];
//             o->oPosY = Path[o->oTimer%pl][o->oBehParams2ndByte][1];
//             o->oPosZ = Path[o->oTimer%pl][o->oBehParams2ndByte][2];
//             a = Path[(o->oTimer+1)%pl][o->oBehParams2ndByte][2] - o->oPosZ;
//             b = Path[(o->oTimer+1)%pl][o->oBehParams2ndByte][0] - o->oPosX;
//             o->oFaceAngleYaw = atan2s(a,b);

//         if (behparam1) {//activate it
//             o->oAction = 2;
//         } else {//autoride
//             o->oAction = 1;
//         }
//         break;
//         case 1://move
//             o->oPosX = Path[o->oTimer%pl][o->oBehParams2ndByte][0];
//             o->oPosY = Path[o->oTimer%pl][o->oBehParams2ndByte][1];
//             o->oPosZ = Path[o->oTimer%pl][o->oBehParams2ndByte][2];
//             a = Path[(o->oTimer+1)%pl][o->oBehParams2ndByte][2] - o->oPosZ;
//             b = Path[(o->oTimer+1)%pl][o->oBehParams2ndByte][0] - o->oPosX;
//             o->oFaceAngleRoll = (atan2s(a,b)-o->oFaceAngleYaw)*2;
//             o->oFaceAngleYaw = atan2s(a,b);
//             o->oFaceAnglePitch = atan2s( sqrtf((a*a) + (b*b)) ,(-Path[(o->oTimer+1)%pl][o->oBehParams2ndByte][1]) - (-o->oPosY));
//             if ((behparam1)&&(o->oTimer>pl)) {
//                 o->oTimer = 0;
//                 o->oAction = 2;
//             }
//         break;
//         case 2://wait for mario
//             if (o->oTimer > 60) {
//                 if (gMarioObject->platform == o) {
//                     o->oAction = 1;
//                     o->oTimer = 0;
//                 }
//             }
//         break;
//     }
// }

// struct ObjectHitbox sBoulderHitbox = {
//     /* interactType: */ INTERACT_MR_BLIZZARD,
//     /* downOffset: */ 0,
//     /* damageOrCoinValue: */ 4,
//     /* health: */ 1,
//     /* numLootCoins: */ 7,
//     /* radius: */ 300,
//     /* height: */ 1200,
//     /* hurtboxRadius: */ 300,
//     /* hurtboxHeight: */ 600,
// };

// void bhv_boulder(void) {
//     u8 behparam1 = (o->oBehParams >> 24);
//     u16 offset = behparam1*2;

//     // f32 a, b, c; // c is unused
//     f32 a, b;
//     // f32 x, y, z; // unused
//     u16 pl = pathlengths[o->oBehParams2ndByte];
//     f32 dist;
//     Vec3f bro;
//     f32 (*Path)[6][3] = segmented_to_virtual(&blender_export);

//     o->oHomeX = o->oPosX;
//     o->oHomeY = o->oPosY;
//     o->oHomeZ = o->oPosZ;
//     o->oPosX = Path[(o->oTimer+offset)%pl][o->oBehParams2ndByte][0];
//     o->oPosY = Path[(o->oTimer+offset)%pl][o->oBehParams2ndByte][1]-300.0f;
//     o->oGraphYOffset = 300.0f;
//     o->oPosZ = Path[(o->oTimer+offset)%pl][o->oBehParams2ndByte][2];

//     bro[0] = o->oHomeX - o->oPosX;
//     bro[1] = o->oHomeY - o->oPosY;
//     bro[2] = o->oHomeZ - o->oPosZ;
//     dist = vec3f_length(bro);

//     a = Path[(o->oTimer+1+offset)%pl][o->oBehParams2ndByte][2] - o->oPosZ;
//     b = Path[(o->oTimer+1+offset)%pl][o->oBehParams2ndByte][0] - o->oPosX;
//     o->oFaceAngleYaw = atan2s(a,b);
//     o->oFaceAnglePitch += (s16)(dist*30.0f);

//     cur_obj_play_sound_1(SOUND_ENV_BOWLING_BALL_ROLL);

//     o->oInteractStatus = 0;
//     obj_set_hitbox(o,&sBoulderHitbox);
// }

// struct Object *fires[9];
// s32 Rope_Progress;

// void bhv_jumprope(void) {
//     u8 i;
//     f32 ratio;
//     f32 sinlocation;
//     f32 dist;

//     switch (o->oAction) {

//         case 0://init
//             Rope_Progress = 0;
//             o->oHealth = 500;
//             for (i=0;i<9;i++) {
//                 fires[i] = spawn_object(o,MODEL_BLUE_FLAME,bhvFlame);
//             }
//             o->oAction = 1;
//         break;

//         case 1://jumprope loop
//             dist = lateral_dist_between_objects(o,gMarioObject);
//             o->oHealth += 1;
//             gMarioState->gCurrMinigame = 2;
//             if ((dist > 200.0f)||(gMarioState->gMinigameWon)) {//stop minigame
//                 if (minigame_real) {
//                     end_minigame();
//                 } else {
//                     gMarioState->EA_WAVES = 0;
//                     gMarioState->gCurrMinigame = 0;
//                     o->oHealth = 500;
//                 }
//             }

//             Rope_Progress += o->oHealth;

//             if (Rope_Progress > 0xFFFF) {
//                 Rope_Progress -= 0xFFFF;
//                 if (gMarioState->gCurrMinigame == 2) {
//                     gMarioState->EA_WAVES ++;
//                     if (minigame_real) {
//                         save_file_set_hiscore(1,gMarioState->EA_WAVES);
//                         }
//                     cur_obj_play_sound_2(SOUND_GENERAL_WATER_LEVEL_TRIG);

//                     if ((gMarioState->EA_WAVES == 25)&&(!minigame_real)) {
//                         spawn_default_star(o->oPosX,o->oPosY,o->oPosZ-400.0f);
//                         gMarioState->gMinigameWon = TRUE;
//                     }
//                 }
//             }

//             for (i=0;i<9;i++) {
//                 ratio = ((f32)i/8.0f);
//                 sinlocation = sins(ratio*0x7FFF);
//                 fires[i]->oPosX = (o->oHomeX - 472.0f) + (i*118);
//                 fires[i]->oPosY = o->oHomeY + (sins(Rope_Progress-0x3FFF)*200.0f*sinlocation);
//                 fires[i]->oPosZ = o->oHomeZ + (coss(Rope_Progress-0x3FFF)*200.0f*sinlocation);
//             }
//         break;
//     }

// }

// s16 iangles[] = {
//     0,
//     0x300,
//     -0x300,
//     0x500,
//     -0x500
// };

// void bhv_boss_cobie(void) {
//     struct Object *bullet;
//     u8 i;

//     switch(o->oAction) {
//         case 0://init
//             gMarioState->BossHealth = 5;
//             gMarioState->BossHealthMax = 5;
//             o->oHealth = 5;
//             o->oAction = 1;
//         break;
//         case 1://wait and shoot

//             if (o->oTimer%(25+gMarioState->BossHealth)==0) {
//                 cur_obj_play_sound_2(SOUND_GENERAL_RACE_GUN_SHOT);
//                 cur_obj_init_animation_with_sound(0);
//                 cur_obj_init_animation_with_sound(1);
//                 for (i = 0; i<(6-gMarioState->BossHealth); i++) {
//                     bullet = spawn_object(o, MODEL_BOWLING_BALL, bhvSnufitBalls);
//                     bullet->oPosY += 90.0f;
//                     gMarioObject->oPosY+= 80.0f;
//                     bullet->oMoveAnglePitch = obj_turn_toward_object(bullet, gMarioObject, O_MOVE_ANGLE_PITCH_INDEX, 200);
//                     gMarioObject->oPosY-= 80.0f;
//                     bullet->oMoveAngleYaw = obj_turn_toward_object(bullet, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 200)+iangles[i];
//                 }
//             }


//             if (gMarioState->pos[0] < o->oPosX+300.0f) {
//                 //escape
//                 if (gMarioState->BossHealth > 1) {
//                     cur_obj_init_animation_with_sound(2);
//                     o->oHomeX -= 2504.0f;
//                     cur_obj_play_sound_2(SOUND_OBJ_GOOMBA_ALERT);
//                     o->oAction = 2;
//                     o->oVelY = 20.0f;
//                 } else {// dead
//                     cur_obj_hide();
//                     cur_obj_become_intangible();
//                     spawn_mist_particles_variable(0, 0, 200.0f);
//                     spawn_triangle_break_particles(20, 138, 3.0f, 4);
//                     cur_obj_shake_screen(SHAKE_POS_SMALL);
//                     spawn_default_star(o->oPosX-900.0f,o->oPosY+200.0f,o->oPosZ);
//                     cur_obj_play_sound_2(SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION);
//                     o->oAction = 3; //dead
//                 }

//                 if (save_file_get_badge_equip() & (1 << BADGE_SLAYER)) {
//                     gMarioState->BossHealth -= 2;
//                 } else {
//                     gMarioState->BossHealth --;
//                 }
//             }
//         break;
//         case 2://go to next car
//             gMarioState->forwardVel = 0.0f;
//             o->oPosX -= 60.0f;
//             if (o->oPosX < o->oHomeX) {
//                 o->oAction = 1;
//             }
//         break;
//     }

//     //gravity;
//     o->oVelY -= 2.0f;
//     o->oPosY += o->oVelY;
//     if (o->oPosY < o->oHomeY) {
//         o->oPosY = o->oHomeY;
//         o->oVelY = 0.0f;
//     }
// }

// void bhv_thwompform(void) {
//     o->oAnimState = 0;
//     if (gMarioObject->platform == o) {
//         o->oAnimState = 1;
//         o->oVelY = lerp(o->oVelY,-40.0f,0.1f);
//     } else {
//         o->oVelY = lerp(o->oVelY,0.0f,0.1f);
//     }
//     o->oPosY = o->oHomeY + (sins(o->oTimer*400)*30.0f) + o->oVelY;
// }

// struct Object *skewbox[6];

// void bhv_bewer(void) {
//     u8 i;
//     f32 reverse = 1.0f;
//     if (o->oBehParams2ndByte==1) {
//         reverse= -1.0f;
//     }

//     switch(o->oAction) {
//         case 0://init
//             o->oAction = 1;
//             for (i = 0; i<3; i++) {
//                 skewbox[(o->oBehParams2ndByte*3)+i] = spawn_object(o,MODEL_NONE,bhvBewerHitbox);
//             }
//         break;
//         case 1://retract
//             o->oPosX += -20.0f*reverse;
//             if (o->oTimer%10 == 5) {
//                 cur_obj_play_sound_2(SOUND_OBJ_CANNON_BARREL_PITCH);
//             }
//             if (o->oTimer > 90) {
//                 o->oAction = 2;
//             }
//         break;
//         case 2://wait in place
//             if (o->oTimer > 40) {
//                 o->oAction = 3;
//             }
//         break;
//         case 3://attack
//             o->oPosX += 40.0f*reverse;
//             o->oFaceAnglePitch += 0x400;
//             if (o->oTimer > 45) {
//                 o->oAction = 4;
//                 o->oPosX = o->oHomeX;
//                 cur_obj_play_sound_2(SOUND_GENERAL_ELEVATOR_LAND);
//             }
//         break;
//         case 4://wait in place 2
//             if (o->oTimer > 40) {
//                 o->oAction = 1;
//             }
//         break;
//     }

//     for (i = 0; i<3; i++) {
//         skewbox[(o->oBehParams2ndByte*3)+i]->oPosX = o->oPosX+(700.0f*reverse*(f32)i);
//     }
// }

// void bhv_path_coin(void) {
//     f32 (*Path)[2][3] = segmented_to_virtual(&coinpath);
//     u8 pathid = 0;
//     u16 offset = (o->oTimer+o->oBehParams2ndByte)%199;
//     o->oPosX = Path[offset][pathid][0];
//     o->oPosY = Path[offset][pathid][1];
//     o->oPosZ = Path[offset][pathid][2];
// }

// void bhv_whform(void) {
//     switch(o->oAction) {
//         case 0:
            
//         break;
//         case 1:
//             o->oPosY += o->oVelY;
//             o->oVelY -= 2.0f;
//             if (o->oTimer > 80) {
//                 o->oAction = 0;
//             }
//         break;
//         case 3:
//             o->oVelY = 0.0f;
//             o->oPosY = o->oHomeY;
//             o->oAction = 0;
//         break;
//     }
// }

// struct Object *chosen_platform;
// u8 thwomp_attacks;
// s16 angle_vel;
// u8 do_attack;
// u8 pindex;

// //FLAME COLOR, FLAME AMOUNT, FLAME SPEED, FLAME ANGLE(22.5), JUMP HEIGHT
// u8 thw_patterns[][5] = {
// {MODEL_RED_FLAME,4,15,0,5},
// {MODEL_RED_FLAME,4,15,2,25},
// {MODEL_BLUE_FLAME,8,30,0,20},
// {MODEL_RED_FLAME,16,8,0,7},
// {MODEL_BLUE_FLAME,16,30,0,20},

// {MODEL_RED_FLAME,12,20,0,10},
// {MODEL_RED_FLAME,12,20,1,10},
// {MODEL_RED_FLAME,12,20,2,25},

// {MODEL_BLUE_FLAME,30,40,0,10},
// {MODEL_BLUE_FLAME,30,40,0,10},
// {MODEL_BLUE_FLAME,30,40,0,10},

// {MODEL_RED_FLAME,6,15,0,8},
// {MODEL_RED_FLAME,6,15,1,8},
// {MODEL_RED_FLAME,6,15,2,8},
// {MODEL_RED_FLAME,6,15,0,8},
// {MODEL_RED_FLAME,6,15,1,8},
// {MODEL_RED_FLAME,6,15,2,20},

// {MODEL_BLUE_FLAME,50,40,0,10},
// {MODEL_BLUE_FLAME,50,40,0,10},
// {MODEL_BLUE_FLAME,50,40,0,10},

// {MODEL_RED_FLAME,6,25,0,6},
// {MODEL_BLUE_FLAME,6,25,1,6},
// {MODEL_RED_FLAME,6,25,2,6},
// {MODEL_BLUE_FLAME,6,25,0,6},
// {MODEL_RED_FLAME,6,25,1,6},
// {MODEL_BLUE_FLAME,6,25,2,6},
// {MODEL_RED_FLAME,6,25,1,6},
// {MODEL_BLUE_FLAME,6,25,0,6},
// {MODEL_RED_FLAME,6,25,1,20},

// {MODEL_BLUE_FLAME,50,40,0,10},
// {MODEL_BLUE_FLAME,50,40,0,10},
// {MODEL_BLUE_FLAME,50,40,0,30},

// {MODEL_BLUE_FLAME,200,15,0,10},
// };

// f32 prevx;
// f32 prevz;

// void bhv_thwomp_king(void) {
//     struct Object *flame;
//     u32 stardata = save_file_get_star_flags(gCurrSaveFileNum - 1, gCurrCourseNum-1);
//     u16 angle_inc; 
//     u8 i;

//     switch(o->oAction) {
//         case 0://init
//             o->oAction = 1;
//             o->oHealth = 4;
//             o->oMoveAngleYaw = o->oAngleToMario;
//             o->oFaceAngleYaw = o->oMoveAngleYaw;
//             do_attack = TRUE;

//             if (o->oBehParams2ndByte == 1) {
//                 o->oAction = 15;
//             }
//         break;
//         case 1://talk
//             if (cur_obj_update_dialog_with_cutscene(2, 1, CUTSCENE_DIALOG, DIALOG_067)) {
//                 o->oAction = 2;
//                 o->oHomeX = 0.0f;
//                 o->oHomeY = 0.0f;
//                 o->oHomeZ = 0.0f;
//                 //set home to centere of arenae
//                 cur_obj_play_sound_2(SOUND_OBJ_KING_BOBOMB_JUMP);
//                 o->oPosY += 30.0f;
//                 o->oVelY = 85.0f;
//             }
//         break;
//         case 2://jump on to arena

//             gCamera->focus[0] = o->oPosX;
//             gCamera->focus[1] = o->oPosY;
//             gCamera->focus[2] = o->oPosZ;

//             if (cur_obj_lateral_dist_to_home() < 40.0f) {
//                 o->oForwardVel = 0.0f;
//             }
//             o->oForwardVel = 80.0f;
//             o->oMoveAngleYaw = cur_obj_angle_to_home();
//             o->oFaceAngleYaw = 0;
//             if (o->oMoveFlags & OBJ_MOVE_ON_GROUND) {
//                 play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_BOSS), 0);
//                 cur_obj_play_sound_2(SOUND_OBJ_KING_BOBOMB_POUNDING1_HIGHPRIO);
//                 o->oAction = 6;
//                 o->oHomeY = o->oPosY;
//                 o->oAnimState = 1;
//                 o->oFaceAngleYaw = 0;
//                 o->oMoveAngleYaw = 0;
//             }
//             cur_obj_update_floor_and_walls();
//             cur_obj_move_standard(72);
//         break;
//         case 3://persue mario
//             if (o->oHomeY+500.0f > o->oPosY) {
//                 o->oPosY+= 10.0f;
//             }

//             prevx = o->oPosX;
//             prevz = o->oPosZ;

//             //hover over mario
//             if (o->oPosX < gMarioState->pos[0]+20.0f) {
//                 o->oPosX += 15.0f;
//             }
//             if (o->oPosX > gMarioState->pos[0]-20.0f) {
//                 o->oPosX -= 15.0f;
//             }
//             if (o->oPosZ < gMarioState->pos[2]+20.0f) {
//                 o->oPosZ += 15.0f;
//             }
//             if (o->oPosZ > gMarioState->pos[2]-20.0f) {
//                 o->oPosZ -= 15.0f;
//             }
//             cur_obj_update_floor_and_walls();

//             if (SURFACE_IS_BURNING(o->oFloor->type)) {
//                 o->oPosX = prevx;
//                 o->oPosZ = prevz;
//             }


//             if (o->oTimer > 100) {
//                 o->oAction = 4;
//                 o->oAnimState = 1;
//                 o->oPosX += 6.0f;
//             }
//         break;
//         case 4://shake
//             if (o->oTimer%2==0) {
//                 o->oPosX -= 12.0f;
//             } else {
//                 o->oPosX += 12.0f;
//             }
//             if (o->oTimer > 30) {
//                 cur_obj_play_sound_2(SOUND_OBJ_KING_BOBOMB_JUMP);
//                 o->oAction = 5;
//                 o->oAnimState = 2;
//                 o->oVelY = -10.0f;
//             }
//         break;
//         case 5://fall
//             o->oForwardVel = 0.0f;
//             cur_obj_update_floor_and_walls();
//             cur_obj_move_standard(72);
//             if (o->oMoveFlags & OBJ_MOVE_ON_GROUND) {
//                 cur_obj_play_sound_2(SOUND_OBJ_THWOMP);
//                 o->oAction = 6;
//                 o->oAnimState = 1;
//                 chosen_platform = o->oFloor->object;
//                 if (chosen_platform != NULL) {
//                     o->oAction = 7;
//                     cur_obj_play_sound_2(SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION);
//                 }
//             }
//         break;
//         case 6://post fall judgement
//             if (o->oTimer > 30) {
//                 angle_vel = 0;
//                 o->oVelY = 0.0f;
//                 o->oAction = 3;

//                 if (do_attack) {
//                     do_attack = FALSE;
//                     switch(o->oHealth) {
//                         case 4://charge attack
//                             o->oAnimState = 0;
//                             o->oAction = 10;
//                             thwomp_attacks = 4;
//                         break;
//                         case 3:
//                             o->oAnimState = 2;
//                             o->oAction = 9;
//                         break;
//                         case 2:
//                             o->oVelY = 20.0f;
//                             o->oAnimState = 2;
//                             o->oAction = 12;
//                             thwomp_attacks = 5;
//                             pindex = 0;
//                         break;
//                         case 1:
//                             o->oVelY = 20.0f;
//                             o->oAnimState = 2;
//                             o->oAction = 12;
//                             thwomp_attacks = 33;
//                             pindex = 0;
//                         break;
//                         case 0:
//                             stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
//                             o->oAction = 13;
//                             o->oAnimState = 0;
//                         break;
//                     }
//                 }
//             }
//         break;
//         case 7://fall into lava
//             o->oVelY -= 5.0f;
//             o->oPosY += o->oVelY;
//             chosen_platform->oPosY = o->oPosY;
//             if (o->oPosY < 0.0f) {
//                 o->oAction = 8;
//                 o->oPosY += 200.0f;
//                 o->oVelY = 80.0f;
//                 o->oFaceAngleYaw = cur_obj_angle_to_home();
//                 obj_mark_for_deletion(chosen_platform);
//                 o->oAnimState = 1;

//                 if (save_file_get_badge_equip() & (1 << BADGE_SLAYER)) {
//                     o->oHealth -= 2;
//                 } else {
//                     o->oHealth --;
//                 }
//                 do_attack = TRUE;
//             }
//         break;
//         case 8://hot!
//             spawn_object(o,MODEL_BURN_SMOKE ,bhvBlackSmokeMario);

//             o->oForwardVel = 80.0f;
//             if ((cur_obj_lateral_dist_to_home() < 100.0f)||(o->oPosY<500.0f)) {
//                 o->oForwardVel = 0.0f;
//             }
//             o->oMoveAngleYaw = cur_obj_angle_to_home();
//             o->oFaceAngleYaw = o->oMoveAngleYaw;

//             cur_obj_update_floor_and_walls();
//             cur_obj_move_standard(72);

//             if (o->oMoveFlags & OBJ_MOVE_ON_GROUND) {
//                 cur_obj_play_sound_2(SOUND_OBJ_KING_BOBOMB_POUNDING1_HIGHPRIO);
//                 o->oAction = 6;
//                 o->oHomeY = o->oPosY;
//                 o->oAnimState = 1;
//                 o->oFaceAngleYaw = 0;
//                 o->oMoveAngleYaw = 0;
//             }
//         break;
//         case 9://fire spin attack
//             cur_obj_play_sound_1(SOUND_AIR_BLOW_FIRE);

//             o->oFaceAngleYaw += angle_vel;
//             o->oMoveAngleYaw = o->oFaceAngleYaw;
//             angle_vel += 8;
//             if (o->oTimer%3 == 0) {
//                 flame = spawn_object(o,MODEL_RED_FLAME,bhvThwompFlame);
//                 flame->oPosY += 30.0f;
//                 flame->oForwardVel = 10.0f;
//             }
//             if (o->oTimer > 400) {
//                 //done attacking
//                 o->oAction = 6;
//                 o->oAnimState = 0;
//                 o->oFaceAngleYaw = 0;
//                 o->oMoveAngleYaw = 0;
//             }
//         break;
//         case 10://charge attack face
//             o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw,o->oAngleToMario,4);
//             o->oFaceAngleYaw = o->oMoveAngleYaw;
//             if (o->oTimer > 30) {
//                 o->oAction = 11;
//                 o->oAnimState = 2;
//                 cur_obj_play_sound_2(SOUND_OBJ_MRI_SHOOT);
//             }
//         break;
//         case 11://charge TODO: telegraph
//             cur_obj_update_floor_and_walls();
//             cur_obj_move_standard(-5);
//             o->oForwardVel = 50.0f;
//             if (o->oTimer%5 == 0) {
//                 flame = spawn_object(o,MODEL_RED_FLAME,bhvThwompFlame);
//                 flame->oPosY += 40.0f;
//                 flame->oForwardVel = 0.0f;
//             }
//             if (o->oMoveFlags & OBJ_MOVE_HIT_EDGE) {
//                 cur_obj_play_sound_2(SOUND_OBJ_THWOMP);
//                 if (thwomp_attacks > 0) {
//                     thwomp_attacks --;
//                     o->oAction = 10;
//                     o->oAnimState = 0;
//                 } else {
//                     //done attacking
//                     o->oAction = 6;
//                     o->oAnimState = 0;
//                     o->oFaceAngleYaw = 0;
//                     o->oMoveAngleYaw = 0;
//                 }
//             }
//         break;
//         case 12://touhou stompie
//             o->oPosX = o->oHomeX;
//             o->oPosZ = o->oHomeZ;
//             o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw,o->oAngleToMario,4);
//             o->oFaceAngleYaw = o->oMoveAngleYaw;

//             o->oAnimState = 2;
//             if (o->oVelY > 0.0f) {
//                 o->oAnimState = 0;
//             }

//             cur_obj_update_floor_and_walls();
//             cur_obj_move_standard(-5);
//             if (o->oMoveFlags & OBJ_MOVE_ON_GROUND) {
//                 if (thwomp_attacks > 0) {
//                     angle_inc = 0xFFFF/thw_patterns[pindex][1];
//                     for (i=0;i<thw_patterns[pindex][1];i++){
//                         flame = spawn_object(o,thw_patterns[pindex][0],bhvThwompFlame);
//                         flame->oPosY += 40.0f;
//                         flame->oForwardVel = (f32)thw_patterns[pindex][2];
//                         flame->oMoveAngleYaw = (angle_inc*i)+(thw_patterns[pindex][3]*0xFFF)+o->oAngleToMario;
//                     }

//                     cur_obj_play_sound_2(SOUND_OBJ_KING_BOBOMB_POUNDING1_HIGHPRIO);
//                     o->oVelY += (f32)(thw_patterns[pindex][4])*4.0f;
//                     thwomp_attacks--;
//                     pindex ++;
//                 } else {
//                     //done attacking
//                     cur_obj_play_sound_2(SOUND_OBJ_THWOMP);
//                     o->oAction = 6;
//                     o->oAnimState = 0;
//                     o->oFaceAngleYaw = 0;
//                     o->oMoveAngleYaw = 0;
//                 }
//             }
//         break;
//         case 13:
//             //winning state
//             if (cur_obj_update_dialog_with_cutscene(2, 1, CUTSCENE_DIALOG, DIALOG_068)) {
//                 o->oAction = 14;
//                 spawn_default_star(gMarioState->pos[0],gMarioState->pos[1]+300.0f,gMarioState->pos[2]);
//             }
//         break;
//         case 14://do nothing

//         break;
//         case 15:
//             if (stardata & 0x40) {//already collected
//                 if (cur_obj_update_dialog_with_cutscene(2, 1, CUTSCENE_DIALOG, DIALOG_133)) {
//                     o->oAction = 14;
//                 }
//             } else {
//                 //my poor wifey uwAAA
//                 if (cur_obj_update_dialog_with_cutscene(2, 1, CUTSCENE_DIALOG, DIALOG_069)) {
//                     o->oAction = 14;
//                 }
//             }   
//         break;
//     }
// }

void bhv_thwomp_king_flame(void) {
    u8 exp_date = 200;
    if (o->oForwardVel > 4.0f) {
        exp_date = 100;
    }
    if (o->oForwardVel > 16.0f) {
        exp_date = 35;
    }
    o->oPosX += sins(o->oMoveAngleYaw)*o->oForwardVel;
    o->oPosZ += coss(o->oMoveAngleYaw)*o->oForwardVel;
    switch(o->oAction) {
        case 0: //exist
            if (o->oTimer > exp_date) {
                o->oAction = 1;//delete
            }
        break;
        case 1://delete
            cur_obj_scale(7.0f-(7.0f*(o->oTimer/30.0f)));
            if (o->oTimer>30) {
                obj_mark_for_deletion(o);
            }
        break;
    }
}

// void bhv_weak_platform(void) {
//     //only for queen fight, king fight controls the platform behavior
//     if ((gCurrAreaIndex == 4)&&(gMarioState->BossHealthMax > 0)) {
//         if (gMarioState->BossHealth == o->oBehParams2ndByte) {
//             mark_obj_for_deletion(o);
//         }
//     }
// }

// static struct SpawnParticlesInfo sQueenParticles = {
//     /* behParam:        */ 0,
//     /* count:           */ 8,
//     /* model:           */ MODEL_QUEEN_ROCK,
//     /* offsetY:         */ 10,
//     /* forwardVelBase:  */ 8,
//     /* forwardVelRange: */ 8,
//     /* velYBase:        */ 20,
//     /* velYRange:       */ 15,
//     /* gravity:         */ -4,
//     /* dragStrength:    */ 0,
//     /* sizeBase:        */ 3.0f,
//     /* sizeRange:       */ 4.0f,
// };

// static struct SpawnParticlesInfo sCrumbleParticles = {
//     /* behParam:        */ 0,
//     /* count:           */ 5,
//     /* model:           */ MODEL_AGCRUMBLE,
//     /* offsetY:         */ 10,
//     /* forwardVelBase:  */ 8,
//     /* forwardVelRange: */ 8,
//     /* velYBase:        */ 20,
//     /* velYRange:       */ 15,
//     /* gravity:         */ -4,
//     /* dragStrength:    */ 0,
//     /* sizeBase:        */ 2.0f,
//     /* sizeRange:       */ 0.5f,
// };

// struct Object *queen_hitbox;

// void bhv_thwomp_queen(void) {
//     struct Object *bullet;
//     switch(o->oAction) {
//         case 0://init
//             o->oAction =1;
//             if (o->oBehParams2ndByte == 1) {
//                 o->oAction = 10;
//             }
//         break;
//         case 1://wait for madio
//             if (o->oDistanceToMario < 1500.0f) {
//                 if (cur_obj_update_dialog_with_cutscene(2, 1, CUTSCENE_DIALOG, DIALOG_070)) {
//                     run_event(EVENT_QUEEN_INTRO);
//                     o->oAction = 2;
//                     cur_obj_init_animation_with_sound(1);
//                 }
//             }
//         break;
//         case 2://jumping
//             if (o->oTimer == 47) {
//                 cur_obj_play_sound_2(SOUND_OBJ_KING_BOBOMB_JUMP);
//                 cur_obj_play_sound_2(SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION);
//                 cur_obj_spawn_particles(&sQueenParticles);
//             }
//             if (o->oTimer == 68) {
//                 cur_obj_shake_screen(SHAKE_POS_LARGE);
//                 cur_obj_play_sound_2(SOUND_OBJ_KING_BOBOMB_POUNDING1_HIGHPRIO);
//             }
//             if (o->oTimer == 94) {
//                 o->oAction = 3;
//                 play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_BOSS), 0);
//                 cur_obj_init_animation_with_sound(2);
//             }
//         break;
//         case 3://evil transition
//             o->oAnimState = (o->oTimer%2);
//             if (o->oTimer > 30) {
//                 o->oAction = 4;
//                 o->oAnimState = 1;
//                 queen_hitbox = spawn_object(o,MODEL_NONE,bhvQueenHitbox);
//                 gMarioState->BossHealth = 3;
//                 gMarioState->BossHealthMax = 3;
//             }
//         break;
//         case 4: //attack mario!

//             if (o->oTimer > 60) {
//                 if (o->oTimer % (7+gMarioState->BossHealth) == 0) {
//                     if ((gMarioState->pos[1] < 2200.0f)&&(gMarioState->pos[1] > o->oPosY + 200.0f)) {
//                         bullet = spawn_object(o, MODEL_COSMIC_SPIKE, bhvCosmicProjectile);
//                         bullet->oPosY = gMarioState->pos[1] + random_float()*30.0f;
//                         bullet->oMoveAngleYaw = o->oAngleToMario+(sins(o->oTimer*0x300)*0x700);
//                     }
//                 }
//             }

//             if (gMarioState->pos[1] < 1500.0f) {
//                 o->oFaceAngleYaw = approach_s16_asymptotic(o->oFaceAngleYaw,o->oAngleToMario,4);
//                 queen_hitbox->oFaceAngleYaw = o->oFaceAngleYaw;
//             }
//         break;
//         case 5://init fumble
//             if (save_file_get_badge_equip() & (1 << BADGE_SLAYER)) {
//                 gMarioState->BossHealth -= 2;
//             } else {
//                 gMarioState->BossHealth --;
//             }
//             if (gMarioState->BossHealth > 0) {
//                 o->oAction = 6;
//                 cur_obj_init_animation_with_sound(3);
//             } else {
//                 o->oAction = 7;//end
//             }
//         break;
//         case 6:
//             if (o->oTimer == 20) {
//                 gMarioState->powerup = 0;
//                 cur_obj_play_sound_2(SOUND_OBJ_CHUCKYA_DEATH);
//                 set_mario_action(gMarioState, ACT_THROWN_BACKWARD, 0);
//                 gMarioState->faceAngle[1] = 0x7FFF;
//                 gMarioState->pos[1] += 50.0f;
//                 gMarioState->vel[1] = 40.0f;
//                 gMarioState->forwardVel = 40.0f;
//             }
//             if (o->oTimer > 29) {
//                 o->oAction = 4;
//                 cur_obj_init_animation_with_sound(2);
//             }
//         break;
//         case 7:
//             o->oAnimState = (o->oTimer%2);
//             if (o->oTimer > 30) {
//                 o->oAnimState = 0;
//                 o->oAction = 8;
//                 stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
//             }
//         break;
//         case 8:
//             if (cur_obj_update_dialog_with_cutscene(2, 1, CUTSCENE_DIALOG, DIALOG_071)) {
//                 o->oAction = 9;
//                 spawn_default_star(o->oPosX,o->oPosY+300.0f,o->oPosZ-500.0f);
//             }
//         break;
//         case 9://do nothing

//         break;

//         case 10://hitbox
//             if (cur_obj_was_attacked_or_ground_pounded()) {
//                 if (o->parentObj->oAction == 4) {
//                     o->parentObj->oAction = 5;
//                 }
//             }
//         break;
//     }
// }

// void bhv_thwompgate(void) {
//     switch(o->oAction) {
//         case 0://init
//             if (save_file_get_flags() & SAVE_FLAG_THWOMPGATE_OPEN) {
//                 o->oPosY += 1000.0f;
//                 o->oAction = 3;
//             } else {
//                 o->oAction = 1;
//             }
//         break;
//         case 1://wait for switch to be pressed
//             if (gMarioState->SwitchPressed == 10) {
//                 o->oAction = 2;
//                 run_event(1);
//                 save_file_set_flags(SAVE_FLAG_THWOMPGATE_OPEN);
//             }
//         break;
//         case 2:
//             if (o->oPosY < o->oHomeY+1000.0f) {
//                 o->oPosY += 5.0f;
//             } else {
//                 o->oAction = 3;
//                 cur_obj_play_sound_2(SOUND_GENERAL_SWITCH_DOOR_OPEN);
//             }
//         break;
//         case 3://do nothing

//         break;
//     }
// }

// void bhv_thomwpguard(void) {
//     switch(o->oAction) {
//         case 0://wai for morio to taok to me
//             o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x140);
//             o->oFaceAngleYaw = o->oMoveAngleYaw;
//             if (o->oDistanceToMario < 400.0f) {
//                 o->oAction = 1;
//             }
//         break;
//         case 1://bla bla bla
//             if (cur_obj_update_dialog_with_cutscene(2, 1, CUTSCENE_DIALOG, o->oBehParams2ndByte)) {
//                 o->oAction = 2;
//             }
//         break;
//         case 2://gooby
//             if (o->oDistanceToMario > 450.0f) {
//                 o->oAction = 0;
//             }
//         break;
//     }
// }

// void bhv_mgb(void) {
//     u8 i;
//     s8 star_to_spawn = -1;
//     u8 event = EVENT_MINIGAME;
//     // struct Object *star; // unused

//     switch (o->oBehParams2ndByte) {
//         case 1://costume
//             event = EVENT_COSTUME_SELECT;
//         break;
//         case 2://music
//             event = EVENT_MUSIC_SELECT;
//         break;
//         case 3:
//             event = EVENT_COSTUME_SELECT_AG;
//         break;
//     }

//     switch(o->oAction) {
//         case 0://initiation
//             o->oAction = 1;

//             switch (o->oBehParams2ndByte) {
//                 case 0://minigame button
//                     if (dist_between_objects(o,gMarioObject) < 2000.0f) {
                        
//                         for (i=0;i<8;i++) {
//                             if (!(((save_file_get_flags()) >> (24+i))&1)) {
//                                 if (save_file_get_hiscore(i) >= mg_minscores[i]) {
//                                     star_to_spawn = i;
//                                 }
//                             }
//                         }

//                         if (star_to_spawn != -1) {
//                             bhv_spawn_star_no_level_exit(star_to_spawn);
//                         }
//                     }
//                 break;
//                 case 1://costume button
//                 case 2://music button
//                     cur_obj_scale(.5f);
//                 break;
//             }
//         break;
//         case 1:
//             if (gMarioObject->platform == o) {
//                 o->oAction = 2;
//                 run_event(event);
//             }
//             if (o->oHomeY > o->oPosY) {
//                 o->oPosY += 1.5f;
//                 cur_obj_play_sound_1(SOUND_ENV_BOWLING_BALL_ROLL);
//             }
//         break;
//         case 2:
//             if (gMarioObject->platform != o) {
//                 o->oAction = 1;
//             }
//             if (o->oHomeY-20.0f < o->oPosY) {
//                 o->oPosY -= 1.5f;
//                 cur_obj_play_sound_1(SOUND_ENV_BOWLING_BALL_ROLL);
//             }
//         break;
//         case 3://minigame button init

//         break;
//     }
// }

// void bhv_instant_warp(void) {
//     gMarioState->usedObj = o;
//     level_trigger_warp(gMarioState, WARP_OP_TELEPORT);
// }

// void bhv_fern(void) {

//     o->oFaceAngleRoll = (s16)(sins(o->oTimer*8000) * o->oVelY);
//     o->oVelY *= 0.95f;

//     switch(o->oAction) {
//         case 0:
//             o->oAction = 1;
//         break;
//         case 1:
//             if (o->oDistanceToMario < 70.0f) {
//                 o->oAction = 2;
//                 o->oVelY = 5000.0f;
//                 cur_obj_play_sound_2(SOUND_ACTION_CLIMB_UP_TREE);
//                 if (o->oNumLootCoins == 1) {
//                     o->oNumLootCoins = 0;
//                     spawn_object(o,MODEL_YELLOW_COIN,bhvSingleCoinGetsSpawned);
//                 }
//             }
//         break;
//         case 2:
//             if (o->oDistanceToMario > 70.0f) {
//                 o->oAction = 1;
//             }
//         break;
//     }
// }

// #define WOOGLY_LENGTH 375.0f

// void bhv_woogly(void) {
//     s16 toffset;
//     cur_obj_scale(1.25f);

//     switch(o->oAction) {
//         case 0://init
//             o->oAction = 1;
//             if (o->oBehParams2ndByte != 1) {
//                 o->oAction = 2;

//                 o->prevObj = spawn_object(o,MODEL_NONE,bhvWoogly);//extension 1
//                 o->prevObj->oBehParams2ndByte = 1;
//                 o->parentObj = spawn_object(o,MODEL_NONE,bhvWoogly);//extension 2
//                 o->parentObj->oBehParams2ndByte = 1;

//                 o->oMoveAngleYaw = o->oFaceAngleYaw;
                
//                 cur_obj_init_animation_with_sound(0);
//             }
//         break;
//         //1 is for the other platforms
//         case 2:
//             toffset = 0;
//             if (o->oBehParams2ndByte == 2) {
//                 toffset = 60;
//             }

//             if (o->oTimer>119) {
//                 o->oTimer = 0;
//             }
//             o->oFaceAngleYaw = o->oMoveAngleYaw + sins((o->oTimer+toffset) * 546) * 0x1000;
//             o->prevObj->oFaceAngleYaw = o->oMoveAngleYaw + sins((o->oTimer+toffset) * 546) * 0x1600;
//             o->parentObj->oFaceAngleYaw = o->oMoveAngleYaw + sins((o->oTimer+toffset) * 546) * 0x2200;
//             //move extension 1
//             o->prevObj->oPosX = o->oPosX + sins(o->oFaceAngleYaw)*WOOGLY_LENGTH;
//             o->prevObj->oPosZ = o->oPosZ + coss(o->oFaceAngleYaw)*WOOGLY_LENGTH;
//             //move extension 2
//             o->parentObj->oPosX = o->prevObj->oPosX + sins(o->prevObj->oFaceAngleYaw)*WOOGLY_LENGTH;
//             o->parentObj->oPosZ = o->prevObj->oPosZ + coss(o->prevObj->oFaceAngleYaw)*WOOGLY_LENGTH;

//             o->header.gfx.animInfo.animFrame = ((o->oTimer+toffset)/2)%60;
//         break;
//     }
// }

// struct Object *Hex[4];
// s16 rotate_speed;
// s16 rotate_value;
// u8 hh_select;
// f32 fall_speed;
// f32 hh_frames_to_jump;

// void bhv_HH(void) {
//     u8 i;

//     switch(o->oAction) {
//         case 0:
//             //init
//             if (o->oAnimState == 0) {
//                 rotate_speed = 0x50;
//                 rotate_value = 0;
//                 hh_select = 0;
//                 fall_speed = -10.0f;
//                 hh_frames_to_jump = 60.0f;

//                 Hex[0] = spawn_object(o,MODEL_HEXAGON,bhvHH);
//                 Hex[0]->oAnimState = 1;

//                 Hex[1] = spawn_object(o,MODEL_HEXAGON,bhvHH);
//                 Hex[1]->oAnimState = 2;

//                 Hex[2] = spawn_object(o,MODEL_HEXAGON,bhvHH);
//                 Hex[2]->oAnimState = 3;

//                 Hex[3] = spawn_object(o,MODEL_HEXAGON,bhvHH);
//                 Hex[3]->oAnimState = 4;

//                 o->oAction = 1;
//             }
//         break;
//         case 1: //rotate around
//             rotate_value += rotate_speed;
//             for(i=0;i<4;i++) {
//                 Hex[i]->oPosX = sins(rotate_value+(0x4000*i))*500.0f;
//                 Hex[i]->oPosZ = coss(rotate_value+(0x4000*i))*500.0f;
//             }

//             //sound
//             switch(o->oTimer) {
//                 case 0:
//                 case 15:
//                 case 30:
//                 case 37:
//                 case 45:
//                 case 52:
//                     play_sound(SOUND_GENERAL2_SWITCH_TICK_SLOW, gGlobalSoundSource);
//                 break;
//             }

//             if (o->oTimer > 60) {
//                 play_sound(SOUND_GENERAL2_RIGHT_ANSWER, gGlobalSoundSource);
//                 hh_select = (random_u16()%4)+1;
//                 o->oAction = 2;
//             }
//         break;
//         case 2://get on!
//             //shake plats
//             for(i=0;i<4;i++) {
//                 if (i+1 != hh_select) {
//                     Hex[i]->oPosY += (((o->oTimer%2)*8.0f)-4.0f);
//                 }
//             }

//             if (o->oTimer > hh_frames_to_jump) {
//                 o->oAction = 3;
//             }
//         break;
//         case 3://platforms fall
//             for(i=0;i<4;i++) {
//                 if (i+1 != hh_select) {
//                     Hex[i]->oPosY += fall_speed;
//                 }
//             }
//             o->oPosY += fall_speed;

//             if (o->oPosY < -50.0f) {
//                 o->oAction = 4;
//                 play_sound(SOUND_OBJ_DIVING_IN_WATER, gGlobalSoundSource);
//             }
//         break;
//         case 4://platforms wait underlava
//             if ((o->oTimer > 30)&&(gMarioObject->platform != NULL)) {
//                 o->oAction = 5;
//             }
//         break;
//         case 5://platforms return
//             for(i=0;i<4;i++) {
//                 if (i+1 != hh_select) {
//                     Hex[i]->oPosY += 30.0f;
//                 }
//             }
//             o->oPosY += 30.0f;
//             if (o->oPosY > o->oHomeY) {
//                 //reset & increase difficulty
//                 o->oAction = 1;
//                 hh_select = 0;
//                 fall_speed -= 2.0f;
//                 rotate_speed += 0x20;
//                 hh_frames_to_jump *= .98f;
//                 if (hh_frames_to_jump < 5.0f) {
//                     hh_frames_to_jump = 5.0f;
//                 }
//                 gMarioState->EA_WAVES++;
//                 if (minigame_real) {
//                     save_file_set_hiscore(2,gMarioState->EA_WAVES);
//                 } else {
//                     if (gMarioState->EA_WAVES == 20) {
//                         spawn_default_star(o->oPosX,o->oPosY+500.0f,o->oPosZ);
//                         o->oAction = 6;
//                     }
//                 }
//             }
//         break;
//         case 6://winstate

//         break;
//     }
//     //everyone
//     if (o->oPosY < -50.0f) {
//         o->oPosY = -50.0f;
//     }
// }

// void bhv_HH_screen(void) {
//     o->oAnimState = hh_select;
// }

// u16 tubemovetimer;
// void bhv_spiketube(void) {
//     o->oPosY = o->oHomeY + (sins(o->oTimer*400)*30.0f);

//     switch(o->oBehParams2ndByte) {
//         case 0://starting tube
//             if ((o->oAction == 0)&&(gMarioObject->platform == o)) {
//                 gMarioState->usedObj = o;
//                 level_trigger_warp(gMarioState, WARP_OP_TELEPORT);
//                 o->oAction = 1;
//             }
//         break;
//         case 1://moving tube
//             switch(o->oAction) {
//                 case 0:
//                     tubemovetimer = 0;
//                     o->oAction = 1;
//                 break;
//                 case 1:
//                     o->oFaceAngleYaw -= 0x50;
//                     o->oPosX += 15.0f;
//                     tubemovetimer ++;
//                     //you dumb fuck.
//                     //do i even need to explain why a fucking timer is a bad idea
//                     if (tubemovetimer > 1240) {
//                         o->oAction = 2;
//                     }
//                 break;
//             }
//         break;
//     }
// }

// void bhv_obj_random_rotate(void) {
//     o->oFaceAngleYaw = random_u16();
// }

// void bhv_cursed_mirror(void) {
//     struct Object *shard;
//     u8 i;

//     switch(o->oAction) {
//         case 0:
//             o->oAction = 2;
//             if (save_file_check_progression(PROG_MIRROR)) {
//                 o->oPosY -= 2000.0f;
//                 o->oAction = 1;
//             }
//         break;
//         case 1:
//             //mirror broken
//         break;
//         case 2://not first frame
//             if (save_file_check_progression(PROG_MIRROR)) {
                
//                 for (i=0;i<9;i++) {
//                     u32 rotated = (random_u16() > 0x8000);
//                     s16 angOffset = (rotated) ? 0x4000 : 0;
//                     f32 posOffset = (rotated) ? -66.66f : 66.66f;
//                     shard = spawn_object(o,MODEL_MIRROR_SHARD,bhvMirrorShard);
//                     shard->oFaceAnglePitch = angOffset;
//                     shard->oPosY -= 200.0f+66.66f;;
//                     shard->oPosZ += -1600.0f+(i*400.0f)+posOffset;
//                     shard = spawn_object(o,MODEL_MIRROR_SHARD,bhvMirrorShard);
//                     shard->oFaceAnglePitch = 0x8000 + angOffset;
//                     shard->oPosY -= 200.0f-66.66f;
//                     shard->oPosZ += -1600.0f+(i*400.0f)-posOffset;

//                     rotated = (random_u16() > 0x8000);
//                     angOffset = (rotated) ? 0x4000 : 0;
//                     posOffset = (rotated) ? -66.66f : 66.66f;
//                     shard = spawn_object(o,MODEL_MIRROR_SHARD,bhvMirrorShard);
//                     shard->oFaceAnglePitch = angOffset;
//                     shard->oPosY += 200.0f-66.66f;
//                     shard->oPosZ += -1600.0f+(i*400.0f)+posOffset;
//                     shard = spawn_object(o,MODEL_MIRROR_SHARD,bhvMirrorShard);
//                     shard->oFaceAnglePitch = 0x8000 + angOffset;
//                     shard->oPosY += 200.0f+66.66f;
//                     shard->oPosZ += -1600.0f+(i*400.0f)-posOffset;
//                 }
        
//                 o->oAction = 3;
//             }
//         break;
//         case 3:
//             o->oPosY -= 2000.0f;
//             o->oAction = 1;
//         break;
//     }
// }

// #include "game/rigid_body.h"

// Vec3f Shard_Size = {0.0f,200.0f,200.0f};

// Vec3f Shard_Vertices[3] = {
// 	{0.0f, 1.0f, .5f},//top right corner
// 	{0.0f, -.5f, -1.0f},//bottom left corner
// 	{0.0f, -.5f, .5f},//bottom right corner
// };

// struct MeshInfo Shard_Mesh = {
//     Shard_Vertices,
//     NULL,
//     NULL,
//     NULL,
//     3, // Number of vertices
//     0,
//     0,
//     0
// };

// #define MIRROR_SHARD_CONTACT_MAX_OFFSET 100.f

// void bhv_mirror_shard(void) {
//     //real cock physics:
//     struct RigidBody *body = allocate_rigid_body_from_object(o, &Shard_Mesh, 1.f, Shard_Size, TRUE);
//     rigid_body_set_pitch(body, o->oFaceAnglePitch);

//     Vec3f contactPoint, force, kick_location, force_offset;
//     //vec3f_set(contactPoint, o->oPosX+20.f, o->oPosY + 20.f, o->oPosZ+20.f);

//     vec3f_set(kick_location, 6272.0f, 2210.0f, -1327.0f);
//     vec3f_diff(force_offset,&o->oPosVec,kick_location);
    
//     f32 dist = sqrtf(force_offset[1]*force_offset[1] + force_offset[2]*force_offset[2]);
//     f32 forward_force = 60.f / (1.f + dist*0.005f);
    
//     if (dist < MIRROR_SHARD_CONTACT_MAX_OFFSET) {
//         vec3f_copy(contactPoint, kick_location);
//     } else {
//         vec3f_normalize(force_offset);
//         vec3_mul_val(force_offset, MIRROR_SHARD_CONTACT_MAX_OFFSET);
//         vec3f_set(contactPoint, o->oPosX-force_offset[0], o->oPosY-force_offset[1], o->oPosZ-force_offset[2]);
//     }

//     vec3f_set(force, -forward_force, random_float()*8.f - 4.f, random_float()*8.f - 4.f);
//     rigid_body_add_force(body, contactPoint, force, TRUE);
    
//     //fake cock physics:
//     /*
//     switch(o->oAction) {
//         case 0:
//             o->oMoveAngleYaw = random_u16();
//             o->oVelY = random_float() * 30.0f;
//             o->oForwardVel = random_float() * 50.0f;
//             o->oAction = 1;
        
//             o->oHomeX = (f32)(random_u16()%2000)-1000;
//             o->oHomeY = (f32)(random_u16()%2000)-1000;
//             o->oHomeZ += (f32)(random_u16()%2000)-1000;
//         break;
//         case 1:
//             o->oFaceAngleYaw += (s16)o->oHomeX;
//             o->oFaceAnglePitch += (s16)o->oHomeY;
//             o->oFaceAngleRoll += (s16)o->oHomeZ;
//             cur_obj_update_floor_and_walls();
//             cur_obj_move_standard(-5);
//             if (o->oMoveFlags & OBJ_MOVE_ON_GROUND) {
//                 o->oGraphYOffset += 10.0f;
//                 o->oAction = 2;
//                 o->oFaceAngleYaw = random_u16();
//                 o->oFaceAnglePitch = 0;
//                 o->oFaceAngleRoll = 0x4000;
//             }
//         break;
//         case 2:
//             cur_obj_update_floor_and_walls();
//             cur_obj_move_standard(-5);
//             o->oForwardVel *= 0.8f;
//             if (o->oForwardVel < 1.0f) {
//                 o->oAction = 3;
//             }
//         break;
//     }
//     */
// }

// void bhv_mirror_shard_loop(void) {
//     struct RigidBody *body = o->rigidBody;
//     if ((o->oDistanceToMario < 150.0f)&&(gMarioState->forwardVel > 5.0f)&&(o->oAction == 0)) {
//         Vec3f contactPoint, force;
//         vec3f_copy(&contactPoint,&gMarioState->pos);
//         vec3f_copy(&force,&gMarioState->vel);
//         if (force[1] > 10.0f) {
//             force[1] = 10.0f;
//         }
//         rigid_body_add_force(body, contactPoint, force, TRUE);

//         o->oAction = 1;
//     }
//     if (o->oDistanceToMario > 155.0f) {
//         o->oAction = 0;
//     }
// }

// void bhv_ttrap(void) {
//     switch(o->oAction) {
//         case 0:
//         //wait for mario
//         if (o->oDistanceToMario < 2642.0f) {
//             o->oAction = 1;
//             run_event(EVENT_SHOWRUNNER_1);
//         }
//         break;
//         //act 1 is cutscene + waiting
//         case 2://flip down
//             o->oFaceAnglePitch -= o->oMoveAnglePitch;
//             if (o->oFaceAnglePitch < -0x4000) {
//                 o->oMoveAnglePitch -= 0x50;
//                 }
//                 else
//                 {
//                 o->oMoveAnglePitch += 0x50;
//                 }
//             o->oMoveAnglePitch *= .95;
//         break;
//     }
// }

// void bhv_hint(void) {
//     //remove if showrunner is dead
//     if (save_file_check_progression(PROG_DEFEAT_SHOWRUNNER)) {
//         obj_mark_for_deletion(o);
//     }
//     if ((o->oTimer == 1)&&(save_file_get_progression() == PROG_QUIZ_COMPLETE_ANGRY)) {
//         o->header.gfx.sharedChild =  gLoadedGraphNodes[MODEL_SHOWRUNNER_TV_ANGRY];
//     }
//     switch(o->oAction) {
//         case 0://wai for morio to taok to me
//             if (o->oDistanceToMario < 1000.0f) {
//                 o->oAction = 1;
//             }
//         break;
//         case 1://bla bla bla
//             if (cur_obj_update_dialog_with_cutscene(2, 1, CUTSCENE_DIALOG, (DIALOG_HINT1+save_file_get_progression())-3)) {
//                 o->oAction = 2;
//             }
//         break;
//         case 2://gooby
//             if (o->oDistanceToMario > 1050.0f) {
//                 o->oAction = 0;
//                 save_file_set_progression(PROG_TALK_2);
//             }
//         break;
//     }
// }


// //cool bowser fight behaviors
// void bhv_lava_pit(void) {
//     switch(o->oAction) {
//         case 0://init
//             lava_pit_stage = 0;
//             lava_pit_scale = 1.0f;
//             lava_pit_height = 10.1414f;
//             o->oAction = 1;
//         break;
//         case 1:
//             cur_obj_scale(lava_pit_scale);
//             o->oPosY = lava_pit_height*100.0f;
//             if (lava_pit_height < lava_pit_heights[lava_pit_stage]) {
//                 lava_pit_height += 0.04f;
//             }
//             if (lava_pit_scale < lava_pit_scales[lava_pit_stage]) {
//                 lava_pit_scale += 0.01f;
//             }
//         break;
//     }
// }

// void bhv_metal_crate_platform(void) {
//     o->oPosX = sins((o->oTimer*0x50)+(o->oBehParams2ndByte*0x2000))*1780.0f;
//     o->oPosZ = coss((o->oTimer*0x50)+(o->oBehParams2ndByte*0x2000))*1780.0f;
//     o->oPosY = ((lava_pit_height*100.0f)+(sins(o->oTimer*0x250)*80.0f))-150.0f;;
//     lava_crate_height = o->oPosY;
// }

// void bhv_pump(void) {
//     struct Object *rock_delete;
//     switch(o->oAction) {
//         case 0:
//             if (gMarioObject->platform == o) {
//                 o->oAction = 1;
//                 if (o->oBehParams2ndByte == 2) {

//                     //prevent unfair deaths
//                     rock_delete = cur_obj_nearest_object_with_behavior(bhvAgcrumble);
//                     while (rock_delete) {
//                         mark_obj_for_deletion(rock_delete);
//                         rock_delete = cur_obj_nearest_object_with_behavior(bhvAgcrumble);
//                     }

//                     run_event(EVENT_BOWSER_DEFEAT);
//                 }
//             }
//         break;
//         case 1:
//             o->oPosY -= 5.0f;
//             if (o->oTimer > 10) {
//                 o->oAction = 3;//do nothing
//                 lava_pit_stage = o->oBehParams2ndByte+1;
//             }
//         break;
//     }
// }

// void bhv_pipespew(void) {
//     switch(o->oAction) {
//         case 0 ://wait for lava pit stage to defnitely be 0
//             if (o->oTimer > 2) {
//                 o->oAction = 1;
//             }
//         break;
//         case 1:
//             if (lava_pit_stage == o->oBehParams2ndByte) {
//                 o->oAction = 2;
//             }
//         break;
//         case 2://spew for awhile
//             hexagonal_ring_spawn_flames();
//             if (o->oTimer > 200) {
//                 o->oAction = 3;//do nothing
//             }
//         break;
//     }
// }

// f32 bowser_offset = 0.0f;
// void new_bowser(void) {
//     struct Object *flame;
//     switch(o->oBehParams2ndByte) {
//         case 0: //urbowser
//             switch(o->oAction) {
//                 case 0://init mate
//                     run_event(EVENT_BOWSER_INTRO);
//                     o->oAction = 1;
//                     bowser_offset = 0.0f;
//                     cur_obj_init_animation_with_sound(12);
//                 break;
//                 case 1://on graund
//                     if (lava_pit_height*100.0f > o->oPosY) {
//                         o->oAction = 2;//start swimming
//                         cur_obj_init_animation_with_sound(23); //swimming anim
//                     }
//                     if (o->oDistanceToMario < 5000.0f) {
//                         o->oFaceAngleYaw = approach_s16_asymptotic(o->oFaceAngleYaw,o->oAngleToMario,4);
//                     }
//                 break;
//                 case 2://swimming in lava
//                     o->oPosY = (lava_pit_height*100.0f)-bowser_offset;
//                     if (bowser_offset < lava_pit_stage*450.0f) {
//                         bowser_offset += 2.0f;
//                     }
//                     if (o->oDistanceToMario < 3000.0f) {
//                         if (o->oTimer > 60) {
//                             cur_obj_play_sound_2(SOUND_OBJ_FLAME_BLOWN);
//                             cur_obj_init_animation_with_sound(BOWSER_ANIM_BREATH_QUICK);
//                             o->oAction = 6;
//                         }
//                     } else {
//                         if (lava_pit_stage < 3) {
//                             if (o->oTimer % (16-(lava_pit_stage*3)) == 0) {
//                                 spawn_object(o,MODEL_AGCRUMBLE,bhvAgcrumble);
//                             }
//                         }
//                     }
//                     if (o->oDistanceToMario < 5000.0f) {
//                         o->oFaceAngleYaw = approach_s16_asymptotic(o->oFaceAngleYaw,o->oAngleToMario,4);
//                     }
//                 break;
//                 case 3://DEFEAT CUTSCENE
//                     o->oAction = 4;
//                     cur_obj_init_animation_with_sound(16);
//                 break;
//                 case 4://DEFEAT CUTSCENE 2
//                     o->oPosY -= 10.0f;
//                     if (o->oTimer > 90) {
//                         mark_obj_for_deletion(o);
//                     }
//                 break;
//                 case 5://TURN EVIL
//                     if (o->oTimer > 30) {
//                         o->oAnimState = !o->oAnimState;
//                     }
//                     if (o->oTimer > 60) {
//                         o->oAnimState = 1;
//                     }
//                     if (o->oTimer > 90) {
//                         o->oAction = 1;
//                     }
//                 break;
//                 case 6://Blow fire
//                     flame = spawn_object(o,MODEL_BLUE_FLAME,bhvThwompFlame);
//                     flame->oPosY = gMarioState->pos[1];
//                     flame->oForwardVel = 50.0f;
//                     flame->oMoveAngleYaw = o->oFaceAngleYaw - 0x400 + (o->oTimer * 0x200);
//                     flame->oPosX += sins(o->oFaceAngleYaw)*500.0f;
//                     flame->oPosZ += coss(o->oFaceAngleYaw)*500.0f;

//                     if (o->oTimer > 15) {
//                         cur_obj_init_animation_with_sound(23); //swimming anim
//                         o->oAction = 2;
//                     }
//                 break;
//             }
//         break;
//         case 1://saved bowser
//             switch(o->oAction) {
//                 case 0://init
//                     o->oAction = 1;
//                     o->oAnimState = 1;
//                     o->oFaceAngleYaw = obj_angle_to_object(o,gMarioObject);
//                     cur_obj_init_animation_with_sound(9);
//                     obj_scale(o,1.0f);
//                     run_event(EVENT_BOWSER_POST);
//                 break;
//                 case 1://fall from the sky
//                     o->oVelY -= 2.0f;
//                     o->oPosY += o->oVelY;
//                     if (o->oPosY < o->oHomeY) {
//                         o->oPosY = o->oHomeY;
//                         o->oAction = 2;
//                         cur_obj_play_sound_2(SOUND_OBJ_BOWSER_WALK);
//                         cur_obj_init_animation_with_sound(12);
//                     }
//                 break;
//                 case 2://chill

//                 break;
//                 case 3://transition back to normal
//                     o->oAnimState = !o->oAnimState;
//                     if (o->oTimer > 30) {
//                         o->oAnimState = 0;
//                         o->oAction = 2;
//                     }
//                 break;
//                 case 4:
//                     //give cosmic seed
//                     o->oBehParams = 0x06010000;
//                     save_file_set_flags(SAVE_FLAG_HAVE_KEY_1);
//                     save_file_set_progression(PROG_DEFEAT_BOWSER_2);
//                     spawn_default_star(gMarioState->pos[0],gMarioState->pos[1]+300.0f,gMarioState->pos[2]);
//                     o->oAction = 2;
//                 break;
//         break;
//         }
//     }
// }

void bhv_Showrunner(void) {
    showrunner_battle_function();
}

// u8 tv_head_showrunner_fire = FALSE;
// void bhv_Showrunner(void) {
//     switch(o->oBehParams2ndByte) {
//         case 0://malleable actor (does nothing, just stands there)
//         break;
//         case 1://bowser defeat cutscene
//             switch(o->oAction) {
//                 case 0: //spawns at mario, so move away a bit
//                     cur_obj_init_animation_with_sound(11);//floaty animation
//                     o->oPosX += 500.0f;
//                     o->oPosY += 200.0f;
//                     o->oHomeY = o->oPosY;
//                     o->oPosY += 1000.0f;
//                     o->oAction = 1;
//                 break;
//                 case 1: //descent from the heavans
//                     o->oFaceAngleYaw = o->oAngleToMario;
//                     o->oPosY = lerp(o->oPosY,o->oHomeY,0.05f);
//                 break;
//                 case 2://give star
//                     o->oBehParams = 0x01020000;
//                     save_file_set_progression(PROG_DEFEAT_BOWSER_1);
//                     spawn_default_star(gMarioState->pos[0],gMarioState->pos[1]+300.0f,gMarioState->pos[2]);
//                     o->oHomeY += 3000.0f;
//                     o->oAction = 3;
//                 break;
//                 case 3:
//                     o->oPosY = lerp(o->oPosY,o->oHomeY,0.05f);
//                     if (o->oTimer > 90) {
//                         mark_obj_for_deletion(o);
//                     }
//                 break;
//             }

//         break;
//         case 2://showrunner battle final
//             showrunner_battle_function();
//         break;
//         case 3://suspended in tube
//             o->oPosY = o->oHomeY + (sins(o->oTimer*0x500)*10.0f);
//             o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_LOPALAM];
//         break;
//         case 4://exectuive fight showrunner (sits on TV head / Bird Monitor)
//             vec3f_copy(&o->oPosVec,&o->parentObj->oPosVec);
//             o->oPosY-=210.0f;
//             o->oFaceAngleYaw = o->parentObj->oFaceAngleYaw;

//             switch(o->oAction) {
//                 case 0:
//                     //init
//                     tv_head_showrunner_fire = FALSE;
//                     cur_obj_init_animation_with_sound(12);//floaty animation
//                     o->oAction ++;
//                 break;
//                 case 1: //Just Talkin'

//                 break;
//                 case 2: //Active
//                     if (o->oTimer == 0) {
//                         o->oTimer = random_u16()%20;
//                     }
//                     if (o->oTimer > 70) {
//                         o->oAction = 5;
//                         cur_obj_init_animation_with_sound(15);//cane whack animation
//                     }
//                 break;
//                 case 3: //Facepalm
//                     cur_obj_init_animation_with_sound(13);//facepalm
//                 break;
//                 case 4: //Facepalm2
//                     cur_obj_init_animation_with_sound(14);//facepalm2
//                 break;
//                 case 5: //Cane whack
//                     if (o->oTimer == 27) {
//                         tv_head_showrunner_fire = TRUE;
//                     }
//                     if (o->oTimer > 40) {
//                         o->oAction = 2;
//                         cur_obj_init_animation_with_sound(12);//floaty animation
//                     }
//                 break;
//             }
//         break;
//     }
// }

// void bhv_flappy_pipe(void) {
//     struct Object *obj;
//     switch(o->oBehParams2ndByte) {
//         case 0://spawner object
//             if (o->oTimer > 120) {
//                 obj = spawn_object(o,MODEL_FLAPPY_PIPE,bhvFlappyPipe);
//                 obj->oBehParams2ndByte = 1;
//                 obj->oPosY = 400.0f + (random_float()*900.0f);
//                 obj->oTimer = 0;
//                 o->oTimer = 0;
//             }
//         break;
//         case 1:
//         case 2://case 2 means passed
//             o->oPosX -= 8;

//             switch(o->oAction) {
//                 case 0:

//                 if (o->oPosX < -2000.0f) {
//                     mark_obj_for_deletion(o);
//                 }

//                 if ((gMarioState->pos[0] > o->oPosX)&&(o->oBehParams2ndByte==1)) {
//                     gMarioState->EA_WAVES++;
//                     save_file_set_hiscore(6,gMarioState->EA_WAVES);
//                     o->oBehParams2ndByte = 2;
//                     play_sound(SOUND_GENERAL_WATER_LEVEL_TRIG, gGlobalSoundSource);
//                 }

//                 if ((gMarioState->pos[0] > o->oPosX-200.0f)&&(gMarioState->pos[0] < o->oPosX+200.0f)) { //horizontal check
//                     if ((gMarioState->pos[1] < o->oPosY-200.0f)||(gMarioState->pos[1] > o->oPosY+80.0f)) { //vertical check
//                         drop_and_set_mario_action(gMarioState, ACT_BACKWARD_AIR_KB, 0);
//                         play_sound(SOUND_MARIO_ATTACKED, gGlobalSoundSource);
//                         o->oAction = 1;
//                     }
//                 }
//                 break;
//                 case 1:
//                 if (o->oTimer > 30) {
//                     end_minigame();
//                 }
//                 break;
//             }
//         break;
//     }
// }

// u8 movie = 0;

// u32 movie_collision_table[] = {
//     movie_1_collision,
//     movie_2_collision,
//     movie3_collision,//bitfs
//     movie4_collision,//bitfs
//     movie5_collision,//bitfs
//     movie6_collision,//bitfs
//     movie7_collision,//bitfs
//     movie_8_collision,
//     movie_9_collision,
// };

// u16 movie_model_table[] = {
//     MODEL_MOVIE_1,
//     MODEL_MOVIE_2,
//     MODEL_MOVIE_3,
//     MODEL_MOVIE_4,
//     MODEL_MOVIE_5,
//     MODEL_MOVIE_6,
//     MODEL_MOVIE_7,
//     MODEL_MOVIE_8,
//     MODEL_MOVIE_9,
// };

// u16 movie_times[] = {
//     300,
//     600,
//     400,
//     400,
//     250,
//     300,
//     1000,
//     470,
//     300,
// };

// void bhv_projector(void) {
//     u16 multiplier = 1;
//     if (save_file_get_badge_equip() & (1<<9)) {
//         multiplier = 2;
//     }

//     switch(o->oAction) {
//         case 0:
//             movie = 0;
//             o->prevObj = spawn_object(o,MODEL_PROJECTOR_HANDLE,bhvStaticObject);
//             if (o->oBehParams2ndByte == 9) { //9 is giant projector
//                 if (save_file_check_progression(PROG_DEFEAT_SHOWRUNNER)) {
//                     cur_obj_scale(1.5f);
//                     o->prevObj->oPosY += 300.0f;
//                     spawn_object(o,MODEL_STAR_SIGN,bhvStaticObject);
//                     o->oAction = 3;
//                 } else {
//                     //destroy if showrunner is still alive
//                     mark_obj_for_deletion(o->prevObj);
//                     mark_obj_for_deletion(o);
//                 }
//             } else {//not the final projector
//                 o->prevObj->oPosY += 200.0f;
//                 o->oAction = 1;
//             }
//         break;
//         case 1:
//             if (cur_obj_was_attacked_or_ground_pounded()) {
//                 o->oAction = 2;
//                 movie = o->oBehParams2ndByte;
//             }
//         break;
//         case 3://required to have specific stars
//             if ((gMarioState->numStars >= 50)&&(gMarioState->numMetalStars >= 6)) {
//                 if (cur_obj_was_attacked_or_ground_pounded()) {
//                     o->oAction = 2;
//                     movie = o->oBehParams2ndByte;
//                 }
//             }
//         break;
//         case 2:
//             cur_obj_play_sound_1(SOUND_AIR_CHUCKYA_MOVE);
//             o->prevObj->oFaceAnglePitch += 0x800;
//             o->oAnimState = 1+((o->oTimer/2)%2);
//             if (o->oBehParams2ndByte != movie) {
//                 o->oAction = 1;
//                 o->oAnimState = 0;
//             }
//             if (o->oTimer > multiplier * movie_times[o->oBehParams2ndByte-1]) {
//                 movie = 0;
//                 o->oAction = 1;
//                 o->oAnimState = 0;
//             }
//             if (cur_obj_was_attacked_or_ground_pounded()) {
//                 movie = 0;
//                 o->oAction = 1;
//                 o->oAnimState = 0;
//                 //INTENTIONAL BUG: The way this function works causes the state to rapidly flip between on & off,
//                 //but it actually looks kind of cool how the platforms "blink" into place!
//                 //somehow the ground pounding state ends on the right odd/even frame to cause this to work.
//             }
//         break;
//     }
// }

// void bhv_movie(void) {
//     o->oDontInertia = TRUE;
//     switch(o->oAction) {
//         case 0:
//             //wait for my movie
//             if (movie == o->oBehParams2ndByte) {
//                 o->oAction = 1;
//                 o->collisionData = segmented_to_virtual(movie_collision_table[o->oBehParams2ndByte-1]);
//                 o->header.gfx.sharedChild = gLoadedGraphNodes[movie_model_table[o->oBehParams2ndByte-1]];
//             }
//         break;
//         case 1:
//             load_object_collision_model();
//             o->oPosX = o->oHomeX+((o->oTimer%3)*2.0f);
//             if (o->oTimer > movie_times[o->oBehParams2ndByte-1]*.75) {
//                 if ((o->oTimer/2)%2 == 0) {
//                     o->header.gfx.sharedChild = gLoadedGraphNodes[movie_model_table[o->oBehParams2ndByte-1]];
//                 } else {
//                     o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_NONE];
//                 }
//             }
//             if (movie != o->oBehParams2ndByte) {
//                 o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_NONE];
//                 o->oAction = 0;
//             }
//         break;
//     }
// }


// Vec3f spotlight_target;
// void bhv_spotlight(void) {
//     f32 a;
//     f32 b;
    
//     vec3f_copy(&spotlight_target,&gMarioState->SpotlightTarget->oPosX);

//     o->oHomeX = lerp(o->oHomeX,spotlight_target[0],.1f);
//     o->oHomeY = lerp(o->oHomeY,spotlight_target[1]+gMarioState->SpotlightTargetYOffset,.1f);
//     o->oHomeZ = lerp(o->oHomeZ,spotlight_target[2],.1f);

//     a = o->oHomeX - o->oPosX;
//     b = o->oHomeZ - o->oPosZ;

//     o->oFaceAngleYaw = atan2s(b,a);
//     o->oFaceAnglePitch = atan2s( sqrtf((a*a) + (b*b)) ,o->oPosY-o->oHomeY);
// }

// void bhv_curtain_call(void) {
//     switch(o->oAction) {
//         case 1:
//             o->oPosY += o->oVelY;
//             o->oVelY ++;

//             if (o->oTimer > 90) {
//                 mark_obj_for_deletion(o);
//             }
//         break;
//     }
// }

// void bhv_manual_key(void) {
//     switch(o->oAction) {
//         case 0:
//             cur_obj_scale(.5f);
//             o->oFaceAngleYaw += 0x200;
//             o->oFaceAngleRoll = -0x4000;
//             if (o->oDistanceToMario < 150.0f) {
//                 o->oAction = 1;
//                 o->oHomeY = 1.0f;
//                 save_file_set_flags(SAVE_FLAG_HAVE_KEY_1|SAVE_FLAG_HAVE_KEY_2);
//                 save_file_do_save(gCurrSaveFileNum - 1);
//                 cur_obj_play_sound_2(SOUND_GENERAL_BOWSER_KEY_LAND);
//             }
//         break;
//         case 1:
//             o->oAngleVelYaw += 0x70;
//             o->oFaceAngleYaw += o->oAngleVelYaw;
//             cur_obj_scale(o->oHomeY/2.0f);
//             o->oHomeY = o->oHomeY *.98f;
//             if (o->oHomeY < .2f) {
//                 obj_mark_for_deletion(o);
//             }
//         break;
//     }
// }

// void bhv_contestant(void) {
//     struct Object *obj;

//     switch(o->oAction) {
//         case 0:

//         break;
//         case 1://fall through trap door
//             o->oPosY -= o->oVelY;
//             o->oVelY += 0.5f;
//             if (o->oTimer > 120) {
//                 obj_mark_for_deletion(o);
//             }
//         break;
//         case 2: //turn into real whomp
//             for (u8 i=0;i<2;i++) {
//                 obj = spawn_object(o,MODEL_MARIO,bhvPhantasm);
//                 obj->oPosY += 2000.0f;
//                 obj->oMoveAngleYaw = random_u16();
//                 obj->oForwardVel = 10.0f;
//                 obj->oBehParams2ndByte = 2;
//                 obj->oAction = 7;
//             }

//             obj = spawn_object(o,MODEL_WHOMP,bhvSmallWhomp);
//             obj->oBehParams2ndByte = 1;
//             obj->oAction = 2;
//             obj->oHealth = 4;
//             obj_mark_for_deletion(o);
//         break;
//     }
// }

// void bhv_whomp_wall(void) {
//     switch(o->oAction) {
//         case 0:
//             if (save_file_get_flags() & SAVE_FLAG_DEFEATED_WHOMP) {
//                 obj_mark_for_deletion(o);
//             } else {
//                 o->oAction = 1;
//             }
//         break;
//         case 1://wai for morio to taok to me
//             if (o->oDistanceToMario < 700.0f) {
//                 o->oAction = 2;
//             }
//         break;
//         case 2://bla bla bla
//             if (cur_obj_update_dialog_with_cutscene(2, 1, CUTSCENE_DIALOG, o->oBehParams2ndByte)) {
//                 o->oAction = 3;
//             }
//         break;
//         case 3://gooby
//             if (o->oDistanceToMario > 750.0f) {
//                 o->oAction = 1;
//             }
//         break;
//     }
//     o->oFaceAngleYaw = -0x4000;
//     o->oMoveAngleYaw = -0x4000;
// }

// Vec3f Cone_Size = {105.0f,105.0f,105.0f};

// Vec3f Cone_Vertices[5] = {
// 	{0.0f, 1.0f, 0.0f},//cone top
// 	{-0.6f, -0.23f, -0.6f},
//     {-0.6f, -0.23f, 0.6f},
//     {0.6f, -0.23f, 0.6f},
//     {0.6f, -0.23f, -0.6f},
// };

// struct MeshInfo Cone_Mesh = {
//     Cone_Vertices,
//     NULL,
//     NULL,
//     NULL,
//     5, // Number of vertices
//     0,
//     0,
//     0
// };

// void bhv_cone_init(void) {
//     o->oPosY += 30.0f;
//     struct RigidBody *body = allocate_rigid_body_from_object(o, &Cone_Mesh, 1.f, Cone_Size, FALSE);
// };

// void bhv_cone(void) {
//     struct RigidBody *body = o->rigidBody;

//     switch(o->oAction) {
//         case 0:
//             o->oAction = 1;
//         break;
//         case 1:
//             if (o->oDistanceToMario < 100.0f) {
//                 o->oAction = 2;

//                 set_object_respawn_info_bits(o, RESPAWN_INFO_DONT_RESPAWN);
//                 switch(o->oBehParams2ndByte) {
//                     case 1:
//                         if (o->oNumLootCoins > 0) {
//                             spawn_object(o,MODEL_YELLOW_COIN,bhvSingleCoinGetsSpawned);
//                             o->oNumLootCoins --;
//                         }
//                     break;
//                     case 2:
//                         if (o->oNumLootCoins != 0) {
//                             o->oNumLootCoins = 0;
//                             spawn_object(o, MODEL_BLUE_COIN, bhvMrIBlueCoin);
//                         }
//                     break;
//                     case 3:
//                         if (o->oNumLootCoins > 0) {
//                             spawn_object(o, 0xEF, bhvMovingGreenCoin);
//                             o->oNumLootCoins = 0;
//                         }
//                     break;
//                 }

//                 cur_obj_play_sound_2(SOUND_GENERAL_SMALL_BOX_LANDING);
//                 drop_and_set_mario_action(gMarioState, ACT_JUMP_KICK, 0);

//                 Vec3f force;
//                 force[0] = gMarioState->vel[0];
//                 force[2] = gMarioState->vel[2];
//                 force[1] = 50.0f;
//                 rigid_body_add_force(body, &gMarioState->pos, force, TRUE);
//             }
//         break;
//         case 2:
//             if (body->linearVel[1] < 0.0f) {
//                 o->oAction = 0;
//             }
//             /*
//             if (colflags & 1) {
//                 cur_obj_play_sound_2(SOUND_GENERAL_SMALL_BOX_LANDING);
//                 o->oFaceAnglePitch = 0;
//                 o->oAction = 1;
//             }
//             if (colflags & 2) {
//                 cur_obj_play_sound_2(SOUND_GENERAL_SMALL_BOX_LANDING);
//             }
//             */
//         break;
//     }

//     if (o->oPosY < -5000.0f) {
//         o->rigidBody->allocated = FALSE;
//         mark_obj_for_deletion(o);
//     }
// }

// void bhv_balloon(void) {
//     struct surface *ptr;

//     switch(o->oAction) {
//         case 0:
//             o->oAction = 1;
//         break;
//         case 1:
//             o->oPosY = o->oHomeY + (sins(o->oTimer*0x200)*50.0f);
//             if (o->oDistanceToMario < 250.0f) {
//                 spawn_triangle_break_particles(20, 139, 0.3f, 0);
//                 play_sound(SOUND_ACTION_BOUNCE_OFF_OBJECT, gMarioState->marioObj->header.gfx.cameraToObject);
//                 o->oPosY = find_floor(o->oPosX, o->oPosY, o->oPosZ, &ptr) - 200.0f;
//                 drop_and_set_mario_action(gMarioState, ACT_TWIRLING, 0);
//                 gMarioState->vel[1] = 70.0f;
//                 o->oAction = 2;
//             }
//         break;
//         case 2://return to home
//             if (o->oDistanceToMario < 250.0f) {
//                 spawn_triangle_break_particles(20, 139, 0.3f, 0);
//                 play_sound(SOUND_ACTION_BOUNCE_OFF_OBJECT, gMarioState->marioObj->header.gfx.cameraToObject);
//                 o->oPosY = find_floor(o->oPosX, o->oPosY, o->oPosZ, &ptr) - 200.0f;
//                 drop_and_set_mario_action(gMarioState, ACT_TWIRLING, 0);
//                 gMarioState->vel[1] = 70.0f;
//                 o->oAction = 2;
//             }
//             if (o->oTimer > 100) {
//                 o->oPosY = lerp(o->oPosY,o->oHomeY,0.05f);
//             }
//             if (o->oPosY > o->oHomeY-5.0f) {
//                 o->oAction = 1;
//             }
//         break;
//     }
// }


// struct Object *fcart[8];

// void bhv_ferris(void) {
//     u8 i;
//     s16 target_angle_speed = 0x20;

//     switch(o->oAction) {
//         case 0://init
//             for (i=0;i<8;i++) {
//                 fcart[i] = spawn_object(o,MODEL_FERRISCART,bhvFerrisCart);
//             }
//             o->oAction = 1;
//             o->oAngleVelRoll = 0x20;
//         break;
//         case 1://run
//             o->oFaceAnglePitch += o->oAngleVelRoll;
//             target_angle_speed = 0x20;
//             for (i=0;i<8;i++) {
//                 fcart[i]->oPosZ = o->oPosZ + coss(-o->oFaceAnglePitch+(i*0x2000))*4500.0f;
//                 fcart[i]->oPosY = o->oPosY + sins(-o->oFaceAnglePitch+(i*0x2000))*4500.0f;

//                 if (gMarioObject->platform == fcart[i]) {
//                     target_angle_speed = 0x60;
//                 }
//             }
//             o->oAngleVelRoll = approach_s16_symmetric(o->oAngleVelRoll, target_angle_speed, 5);


//         break;
//     }
// }


// //sloppy programming, health is if sound can play
// void bhv_press(void) {
//     if (o->oBehParams2ndByte == 0) {
//         if (o->oPosY > o->oHomeY) {
//             o->oPosY -= 40.0f;
//         }
//         if (o->oPosY < o->oHomeY) {
//             o->oPosY = o->oHomeY;
//             if (o->oHealth == 1) {
//                 cur_obj_play_sound_2(SOUND_GENERAL_ELEVATOR_LAND);
//                 o->oHealth = 0;
//             }
//         }
//     } else {
//         o->oHealth = 1;
//         o->oPosY = lerp(o->oPosY,o->oHomeY+500.0f,.2f);
//     }
//     if (o->oTimer > 50) {
//         o->oTimer = 0;
//         o->oBehParams2ndByte = !o->oBehParams2ndByte;
//     }
// }

// void bhv_fountain(void) {
//     f32 scale = 1.0f + (sins(o->oMoveAngleYaw)*0.05f);

//     if ((gMarioState->numMetalStars > 12)&&(gMarioState->numMetalStars < 18)) {
//         scale *= 0.8f;
//     }
//     if (gMarioState->numMetalStars > 17) {
//         scale *= 0.25f;
//     }

//     if (gMarioState->numMetalStars > 30) {
//         scale *= 0.5f;
//     }

//     if (gMarioState->numMetalStars == 40) {
//         scale *= 0.5f;
//     }

//     o->oFaceAngleYaw += 0x800;
//     o->oMoveAngleYaw += 0x200;
//     o->header.gfx.scale[0] = scale;
//     o->header.gfx.scale[2] = scale;
//     cur_obj_play_sound_1(SOUND_ENV_WATERFALL2);

//     if (lateral_dist_between_objects(o,gMarioObject) < 17.9103f*100.0f*scale) {
//         if (o->oAction == 0) {
//             o->oAction = 1;
//             set_mario_action(gMarioState, ACT_EATEN_BY_BUBBA, 0);
//             }
//     }
// }

// void bhv_killer_laser(void) {
//     Vec3f origin;
//     Vec3f dir;
//     Vec3f hitpos;
//     f32 a, b;
//     struct Surface *surf;
//     struct Object *boom;

//     vec3f_copy(origin,&o->oPosX);
//     dir[0] = gMarioState->pos[0] - origin[0];
//     dir[1] = (gMarioState->pos[1]+50.0f) - origin[1];
//     dir[2] = gMarioState->pos[2] - origin[2];

//     find_surface_on_ray(origin, dir, &surf, &hitpos, RAYCAST_FIND_ALL);

//     if (surf) { //hit wall
//         if (o->oAction == 3) {
//             o->oTimer = 0;
//             o->oOpacity = 0;
//         }
//     } else { //aim at mario
//         vec3f_copy(&hitpos,&gMarioState->pos);
//     }
//     dir[0] = hitpos[0]- o->oPosX;
//     dir[1] = hitpos[1]- o->oPosY;
//     dir[2] = hitpos[2]- o->oPosZ;

//     o->header.gfx.scale[2] = (sqrtf(dir[0]*dir[0] + dir[1]*dir[1] + dir[2]*dir[2])/100.0f);

//     a=hitpos[0] - o->oPosX;
//     b=hitpos[2] - o->oPosZ;

//     o->oFaceAngleYaw = atan2s(b,a);
//     o->oFaceAnglePitch = atan2s( sqrtf((a*a) + (b*b)) ,o->oPosY-hitpos[1]);

//     //do not activate under these conditions
//     if ((gCurrLevelNum == LEVEL_RR)&&((agstate==1)||(aghealth>1))) {
//         o->oTimer = 0;
//         o->oAction = 0;
//     }

//     switch(o->oAction) {
//         case 0:
//             o->oAction = 3;
//         break;
//         case 1:
//             cur_obj_play_sound_1(SOUND_AIR_AMP_BUZZ);
//             o->oOpacity = (u8)(100.0f+(sins(o->oTimer*0x1000)*50.0f));
//             if (o->oTimer > 150) {
//                 o->oAction = 2;
//             }
//         break;
//         case 2:
//             cur_obj_play_sound_1(SOUND_ENV_WATERFALL2);

//             if (o->oOpacity < 254) {
//                 o->oOpacity +=2;
//                 o->oTimer = 0;
//             } else {
//                 //play warning sound
//                 if (o->oTimer % 8 == 0) {
//                     cur_obj_play_sound_2(SOUND_OBJ_MR_BLIZZARD_ALERT);
//                 }
//             }
//             if (o->oTimer > 30) {
//                 o->oAction = 3;
//                 boom = spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
//                 vec3f_copy(&boom->oPosX,&hitpos);
//                 o->oOpacity = 0;

//                 //destroy alien balls
//                 if ((surf)&&(surf->object)) {
//                     if (surf->object->behavior == segmented_to_virtual(bhvAlienball)) {
//                         surf->object->oAction = 2;
//                     }
//                 }
//             }
//         break;
//         case 3:
//             if (o->oTimer > 150) {
//                 o->oOpacity += 3;
//             }
//             if (o->oOpacity > (u8)(100.0f+(sins(o->oTimer*0x1000)*50.0f))) {
//                 o->oAction = 1;
//             }
//         break;
//     }
// }

// u8 alien_ball_count = 0;
// void bhv_alienball(void) {
//     switch(o->oAction) {
//         case 0:
//             alien_ball_count = 0;
//             o->oAction = 1;
//         break;
//         case 1:
//             o->oPosY = o->oHomeY + (sins(o->oTimer*0x200)*20.0f);
//         break;
//         case 2:
//             alien_ball_count ++;
//             cur_obj_play_sound_2(SOUND_GENERAL_PAINTING_EJECT);
//             if (alien_ball_count == 5) {
//                 spawn_default_star(gMarioState->pos[0],gMarioState->pos[1]+300.0f,gMarioState->pos[2]);
//             } else {
//                 spawn_orange_number(alien_ball_count, 0, 0, 0);
//             }
//             mark_obj_for_deletion(o);
//         break;
//     }
// }

// void bhv_vflood(void) {
//     if (o->oPosY < 39.114f*100.0f) {
//         o->oPosY += 3.0f;
//         if (gMarioState->pos[1] > o->oPosY+1000.0f) {
//             o->oPosY += 2.0f;
//         }
//         if (gMarioState->pos[1] > o->oPosY+2000.0f) {
//             o->oPosY += 2.0f;
//         }
//         if (gMarioState->pos[1] > o->oPosY+3000.0f) {
//             o->oPosY += 2.0f;
//         }
//     }
// }

// void bhv_flip(void) {
//     u16 desired_angle = ((tile_flip_state+o->oBehParams2ndByte)%2)*0x8000;
//     desired_angle %= 0x10000;

//     switch(o->oAction) {
//         case 0:
//             o->oMoveAngleRoll = desired_angle;
//             o->oAction = 1;
//             switch(o->oBehParams2ndByte) {
//                 case 2:
//                     o->oAction = 2;
//                     o->oHealth = 0;
//                 break;
//                 case 3:
//                     o->oAction = 2;
//                     o->oHealth = 2;
//                     o->oHomeX += 400.0f;
//                     o->oHomeZ -= 400.0f;
//                 break;
//             }
//         break;
//         case 2:
//             switch(o->oHealth) {
//                 case 0://-x
//                     o->oPosX = o->oHomeX - (o->oTimer * 10.0f);
//                     if (o->oTimer > 39) {
//                         o->oTimer = 0;
//                         o->oHealth++;
//                     }
//                 break;
//                 case 1://+z
//                     o->oPosZ = o->oHomeZ + (o->oTimer * 10.0f);
//                     if (o->oTimer > 39) {
//                         o->oTimer = 0;
//                         o->oHealth++;
//                     }
//                 break;
//                 case 2://+x
//                     o->oPosX = (o->oHomeX - 400.0f) + (o->oTimer * 10.0f);
//                     if (o->oTimer > 39) {
//                         o->oTimer = 0;
//                         o->oHealth++;
//                     }
//                 break;
//                 case 3://-z
//                     o->oPosZ = (o->oHomeZ + 400.0f) - (o->oTimer * 10.0f);
//                     if (o->oTimer > 39) {
//                         o->oTimer = 0;
//                         o->oHealth=0;
//                     }
//                 break;
//             }
//         break;
//     }

//     if (o->oMoveAngleRoll != desired_angle) {
//         o->oMoveAngleRoll += 0x1000;
//         o->oMoveAngleRoll %= 0x10000;
//     } else {
//         load_object_collision_model();
//     }

//     if (o->oBehParams2ndByte % 2 == 0) {
//         o->oFaceAngleRoll = o->oMoveAngleRoll;
//     } else {
//         o->oFaceAngleRoll = -o->oMoveAngleRoll;
//     }
// }

// void bhv_saw(void) {
//     if (o->oDistanceToMario < 2000.0f) {
//         cur_obj_play_sound_1(SOUND_AIR_AMP_BUZZ);
//     }
//     switch(o->oBehParams2ndByte) {
//         case 0:
//             o->oPosX = o->oHomeX + (sins(o->oTimer*0x300)*600.0f);
//         break;
//         case 1:
//             o->oPosX = o->oHomeX + (coss(o->oTimer*0x300)*600.0f);
//         break;
//     }
// }

// void bhv_showrunner_statue(void) {
//     switch(o->oAction) {
//         case 0:
//             //do nthing bitch
//         break;
//         case 1:
//             o->oFaceAngleYaw -= 0x111;
//             cur_obj_play_sound_1(SOUND_ENV_METAL_BOX_PUSH);
//             if (o->oTimer > 29) {
//                 o->oAction = 0;
//             }
//         break;
//     }
// }

// u8 sister_count = 0;
// void bhv_girl(void) {
//     o->oAnimState = o->oBehParams2ndByte;
//     o->oInteractionSubtype = INT_SUBTYPE_NPC;

//     switch(o->oAction) {
//         case 0:
//             sister_count = 0;
//             o->oAction = 1;
//             o->oHealth = 0;
//         break;
//         case 1://invisible until hint is given
//             o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
//             cur_obj_become_intangible();

//             if (sister_count == o->oBehParams2ndByte) {
//                 o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
//                 cur_obj_become_tangible();
//                 o->oAction = 2;
//                 }
//         break;
//         case 2:
//             if (o->oInteractStatus & INT_STATUS_INTERACTED) {
//                 o->oAction = 3;
//                 if (o->oBehParams2ndByte == sister_count) {
//                     sister_count++;
//                 }
//             }
//         break;
//         case 3:
//             if (cur_obj_update_dialog_with_cutscene(2, 1, CUTSCENE_DIALOG, (DIALOG_GIRL_1A+o->oHealth)+(2*o->oBehParams2ndByte))) {
//                 if ((o->oBehParams2ndByte == 3)&&(o->oHealth == 0)) {
//                     o->oAction = 2;
//                     o->oHealth = 1;
//                     spawn_default_star(o->oPosX+200.0f,o->oPosY+400.0f,o->oPosZ);
//                 } else {
//                     o->oAction = 2;
//                     o->oHealth = 1;
//                 }
//             }
//         break;
//     }

//     if ((o->oBehParams2ndByte == 2)&&(fcart[0]!=NULL)) {
//         vec3f_copy(&o->oPosX,&fcart[0]->oPosX);
//         o->oPosY -= 600.0f;
//     }

//     o->oInteractStatus = 0;
// }

// u8 trial_counter = 0;
// void bhv_blocker(void) {
//     u32 stardata = save_file_get_star_flags(gCurrSaveFileNum - 1, gCurrCourseNum-1);
//     switch(o->oAction) {
//         case 0://everyone resets the counter on first frame
//             trial_counter = 0;
//             o->oAction = 1;
//         break;
//         case 1://second frame, increase counter if applicable
//             if ((stardata >> o->oBehParams2ndByte)&1) {
//                 trial_counter ++;
//                 mark_obj_for_deletion(o);
//             } else {
//                 o->oAction = 2;//not collected
//             }
//         break;
//         //third frame and on, do nothing
//     }
// }

// void bhv_rr_door(void) {
//     switch(o->oAction) {
//         case 0:
//             if (o->oBehParams2ndByte == 0) {
//                 o->prevObj = spawn_object(o,MODEL_RR_DOOR,bhvRR_Door);
//                 o->prevObj->oBehParams2ndByte = 1;
//                 o->prevObj->oPosX = o->oPosX + 454.0f;
//                 o->oAction = 1;
//             } else {
//                 o->oAction = 3;
//             }
//         break;
//         case 1:
//             //wait for mario
//             if ((o->oDistanceToMario < 1000.0f)&&(trial_counter >= 3)) {
//                 o->oAction = 2;
//                 cur_obj_play_sound_2(SOUND_GENERAL_STAR_DOOR_OPEN);
//             }
//         break;
//         case 2://open
//             o->oPosX -= 10.0f;
//             o->prevObj->oPosX += 10.0f;
//             if (o->oTimer > 29) {
//                 o->oAction = 3;
//             }
//         break;
//         case 3://do nothing

//         break;
//         case 4://close
//             o->oPosX += 10.0f;
//             o->prevObj->oPosX -= 10.0f;
//             if (o->oTimer > 29) {
//                 o->oAction = 3;
//             }
//         break;    
//     }
// }

// void bhv_event_object(void) {
//     if (o->oDistanceToMario < 300.0f) {
//         run_event(EVENT_ELEVATOR);
//         mark_obj_for_deletion(o);
//     }
// }

// void bhv_rr_tube(void) {
//     o->oDontInertia = TRUE;
//     if (gMarioState->pos[0] != 0.0f) {
//         o->oFaceAngleRoll -= (s16)(gMarioState->pos[0]*8.0f);
//         gMarioState->pos[0] = 0.0f;
//     }
// }

// void bhv_rr_eye(void) {
//     o->oPosY = o->oHomeY + (sins(o->oTimer*0x200)*20.0f);
//     switch(o->oAction) {
//         case 0://z+
//             o->oFaceAngleYaw = 0;
//             o->oPosZ += 4.0f;
//             if (o->oPosZ > o->oHomeZ+1600.0f) {
//                 o->oAction ++;
//             }
//         break;
//         case 1://x-
//             o->oFaceAngleYaw = -0x4000;
//             o->oPosX -= 4.0f;
//             if (o->oPosX < o->oHomeX-2400.0f) {
//                 o->oAction ++;
//             }
//         break;
//         case 2://z-
//             o->oFaceAngleYaw = 0x7FFF;
//             o->oPosZ -= 4.0f;
//             if (o->oPosZ < o->oHomeZ) {
//                 o->oAction ++;
//             }
//         break;
//         case 3://x-
//             o->oFaceAngleYaw = 0x4000;
//             o->oPosX += 4.0f;
//             if (o->oPosX > o->oHomeX) {
//                 o->oAction = 0;
//             }
//         break;
//     }
// }

// void bhv_rr_pyramid(void) {
//     switch(o->oAction) {
//         case 0:
//             if (gMarioObject->platform == o) {
//                 o->oAction = 1;
//             }
//         break;
//         case 1:
//             if (o->oFaceAnglePitch < 0x7FFF) {
//                 cur_obj_play_sound_1(SOUND_ENV_METAL_BOX_PUSH);
//                 o->oFaceAnglePitch += 0x30;
//             }
//             if (o->oFaceAnglePitch > 0x7FFF) {
//                 o->oFaceAnglePitch = 0x7FFF;
//             }

//             if (gMarioObject->platform == o) {
//                 o->oTimer = 0;
//             }
//             if (o->oTimer > 400) {
//                 o->oFaceAnglePitch = 0;
//                 o->oAction = 0;
//             }
//         break;
//     }   
// }

// void bhv_spinseed(void) {
//     struct Object *staticobj;

//     if (gMarioObject->platform == o) {
//         o->oAngleVelYaw += 0x10;
//         if (o->oAngleVelYaw > 0x200) {
//             o->oAngleVelYaw = 0x200;
//         }
//     } else {
//         o->oAngleVelYaw -= 0x10;
//         if (o->oAngleVelYaw < 0) {
//             o->oAngleVelYaw = 0;
//         }
//     }
//     o->oFaceAngleYaw += o->oAngleVelYaw;

//     staticobj = cur_obj_nearest_object_with_behavior(bhvStaticFlood);

//     if (staticobj) {
//         if (o->oBehParams2ndByte == 1) {
//             switch(o->oAction) {
//                 case 0:
//                     if (gMarioObject->platform == o) {
//                         o->oAction = 1;
//                         staticobj->oAction = 1;
//                     }
//                 break;
//                 case 1:
//                     o->oPosY = staticobj->oPosY;
//                 break;
//             }
//         }
//     }
// }

// void bhv_staticflood(void) {
//     switch(o->oAction) {
//         case 1:
//             o->oPosY += 2.0f;
//         break;
//     }
// }

// u8 idols_crushed = 0;
// void bhv_idol(void) {
//     switch(o->oAction) {
//         case 0://init
//             idols_crushed = 0;
//             o->oAction++;
//             break;
//         case 1:
//         case 2:
//         case 3:
//             if (cur_obj_was_attacked_or_ground_pounded() & (o->oTimer > 10)) {
//                 o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_IDOL_1-o->oAction];
//                 o->oAction++;
//             }
//             if (o->oAction == 4) {
//                 idols_crushed ++;
//                 if (idols_crushed == 5) {
//                     spawn_default_star(gMarioState->pos[0],gMarioState->pos[1]+300.0f,gMarioState->pos[2]);
//                     }
//             }
//             break;
//     }
// }

// void bhv_tvhead(void) {
//     s16 home_angle = cur_obj_angle_to_home();
//     s8 i;
//     f32 back_speed = -30.0f;
//     f32 fwd_speed = 20.0f;
//     s16 sin_speed = 0x300;
//     struct Object *bullet;
//     u8 mario_super_close = (o->oDistanceToMario < 450.0f);
//     u8 shboss = (o->oBehParams2ndByte == 1);

//     switch(o->oAction) {
//         case 0://init
//             if (shboss) {
//                 o->oExtraVariable1 = FALSE;
//                 o->prevObj = spawn_object(o,MODEL_SHOWRUNNER,bhvShowrunner);
//                 o->prevObj->oBehParams2ndByte = 4; //BehParam 4 is showrunner riding on a tv head / bird monitor
//                 run_event(EVENT_EXECUTIVE_MIDDLE);
//                 o->oAction = 2;
//             } else {
//                 o->oNumLootCoins = 5;
//                 o->oAction ++;
//             }
//         break;
//         case 1: //wander
//             o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, home_angle, 0x100);
//             o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 15.0f ,0.4f);

//             if (o->oDistanceToMario < 1500.0f) {
//                 o->oAction = 2;//aggro
//             }
//         break;
//         case 2: //aggro
//             if (shboss) {
//                 mario_super_close = FALSE;
//                 o->oHomeY = lerp(o->oHomeY, gMarioState->pos[1]+200.0f, 0.1f);
//             } else {
//                 if (o->oTimer > 300) {
//                     back_speed = -5.0f;
//                 }
//             }

//             if (revent_active) {
//                 back_speed = 0.0f;
//             }

//             if ((shboss)&&(!revent_active)) {
//                 fwd_speed = 40.0f;
//             }

//             o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, o->oAngleToMario, 0x200);
//             if (mario_super_close) {
//                 o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 0.0f ,2.0f);
//             } else {
//                 if (o->oDistanceToMario < 800.0f) {
//                     o->oForwardVel = approach_f32_symmetric(o->oForwardVel, back_speed ,2.0f);
//                 } else {
//                     o->oForwardVel = approach_f32_symmetric(o->oForwardVel, fwd_speed ,1.0f);
//                 }
//             }

//             if (gMarioObject->platform == o) {
//                 sin_speed = 0x1500;
//             }

//             if (!shboss) {
//                 if ((o->oTimer % 90 > 70)&&(!mario_super_close)) {
//                     o->oForwardVel = 0;
//                     o->header.gfx.animInfo.animFrame = 0;
//                     //telegraph about to attack
//                 }

//                 //fire bullets at mario every 90 frames, also not when mario is on top
//                 if ((o->oTimer % 90 == 0)&&(!mario_super_close)) {
//                     o->oForwardVel = -20.0f;
//                     cur_obj_play_sound_2(SOUND_GENERAL_CASTLE_TRAP_OPEN);

//                     for (i = -1; i<2; i++) {
//                         bullet = spawn_object(o, MODEL_COSMIC_SPIKE, bhvCosmicProjectile);
//                         bullet->oPosY += 20.0f;
//                         gMarioObject->oPosY+= 80.0f;
//                         bullet->oMoveAnglePitch = obj_turn_toward_object(bullet, gMarioObject, O_MOVE_ANGLE_PITCH_INDEX, 200);
//                         gMarioObject->oPosY-= 80.0f;
//                         bullet->oMoveAngleYaw = o->oFaceAngleYaw+(i*0x600);
//                     }
//                 }
//             } else {
//                 //Only shoot when whacked by the showrunner cane
//                 if ((tv_head_showrunner_fire)&&(!revent_active)) {
//                     tv_head_showrunner_fire = FALSE;
//                     o->oForwardVel = -10.0f;
//                     cur_obj_play_sound_2(SOUND_GENERAL_CASTLE_TRAP_OPEN);
//                     for (i = -1; i<2; i++) {
//                         bullet = spawn_object(o, MODEL_COSMIC_SPIKE, bhvCosmicProjectile);
//                         bullet->oPosY += 20.0f;
//                         gMarioObject->oPosY+= 80.0f;
//                         bullet->oMoveAnglePitch = obj_turn_toward_object(bullet, gMarioObject, O_MOVE_ANGLE_PITCH_INDEX, 200);
//                         gMarioObject->oPosY-= 80.0f;
//                         bullet->oMoveAngleYaw = o->oFaceAngleYaw+(i*0x600);
//                     }
//                 }
//             }

//             if ((o->oDistanceToMario > 2100.0f)&&(!shboss)) {
//                 o->oAction = 1;//wander
//             }
//         break;
//         case 3://fly away
//             if (o->oTimer == 0) {
//                 o->oHomeY =0;
//             }
//             o->oHomeY += o->oHomeY;
//             o->oHomeY += 0.1f;

//             if (o->oHomeY > 12000.0f) {
//                 mark_obj_for_deletion(o->prevObj);
//                 mark_obj_for_deletion(o);
//             }
//         break;
//     }

//     o->oPosY = o->oHomeY + sins(o->oTimer*sin_speed)*30.0f;
//     o->oFaceAnglePitch = coss(o->oTimer*sin_speed)*0x500;

//     if (cur_obj_was_attacked_or_ground_pounded() && (!shboss)) {
//         //create corpse
//         bullet = spawn_object(o,MODEL_TV_CORPSE,bhvTVcorpse);
//         bullet->oFaceAnglePitch = 0x4000;
//         bullet->oFaceAngleYaw = o->oFaceAngleYaw;
//         bullet = spawn_object(o,MODEL_TV_CORPSE,bhvTVcorpse);
//         bullet->header.gfx.scale[0] = -1;
//         bullet->oFaceAnglePitch = 0x4000;
//         bullet->oFaceAngleYaw = o->oFaceAngleYaw;

//         create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
//         cur_obj_spawn_loot_blue_coin();
//         mark_obj_for_deletion(o);
//     }

//     //Collide with walls
//     if (!shboss) {
//         o->oGravity = 0.0f;
//         o->oMoveAngleYaw = o->oFaceAngleYaw;
//         object_step_without_floor_orient();
//     } else {
//         o->oMoveAngleYaw = o->oFaceAngleYaw;
//         o->oPosX += sins(o->oMoveAngleYaw) * o->oForwardVel;
//         o->oPosZ += coss(o->oMoveAngleYaw) * o->oForwardVel;
//     }
// }

void tv_head_projectile(void) {
    cur_obj_update_floor_and_walls();
    o->oFaceAngleRoll += 0x400;
    o->oForwardVel = 35.0f;
    o->oPosX += sins(o->oMoveAngleYaw)*o->oForwardVel;
    o->oPosZ += coss(o->oMoveAngleYaw)*o->oForwardVel;
    o->oPosY += -sins(o->oMoveAnglePitch)*o->oForwardVel;
    if ((o->oTimer > 110)||(o->oMoveFlags & OBJ_MOVE_HIT_WALL)) {
        mark_obj_for_deletion(o);
    }
}

// void bhv_thi_cage_init(void) {
//     o->prevObj = spawn_object(o,0xED,bhvStaticObject);
// }

// void bhv_thi_cage(void) {
//     struct Object *slot;

//     cur_obj_update_floor_and_walls();
//     cur_obj_move_standard(78);

//     switch(o->oAction) {
//         case 0:
//             vec3f_copy(&o->prevObj->oPosX,&o->oPosX);
//             switch (o->oHeldState) {
//                 case HELD_FREE:
//                     break;
//                 case HELD_HELD:
//                     cur_obj_unrender_set_action_and_anim(-1,0);
//                     obj_copy_pos(o, gMarioObject);
//                     vec3f_copy(&o->prevObj->oPosX,&gMarioState->marioBodyState->heldObjLastPosition);
//                     break;
//                 case HELD_THROWN:
//                     cur_obj_get_thrown_or_placed(0, 0, 0);
//                     break;
//                 case HELD_DROPPED:
//                     cur_obj_get_dropped();
//                     break;
//                 }
//             o->prevObj->oPosY += 150.0f;
//             o->prevObj->oFaceAngleYaw += 0x300;

//             //detect if its in slot

//             slot = cur_obj_nearest_object_with_behavior(bhvStaticObject);
//             if ((dist_between_objects(slot,o) < 70.0f)&&(o->oHeldState==HELD_FREE)) {
//                 o->oAction = 1;
//                 o->oInteractStatus = INTERACT_IGLOO_BARRIER;
//                 o->oInteractStatus = 0;
//                 o->oIntangibleTimer = 0;
//                 play_sound(SOUND_GENERAL_OPEN_CHEST, o->header.gfx.cameraToObject);
//                 vec3f_copy(&o->oPosX,&slot->oPosX);
                
//                 vec3f_copy(&o->prevObj->oPosX,&o->oPosX);
//                 o->prevObj->oPosY += 150.0f;
//             }
//             break;
//         case 1:
//             if (o->oTimer > 40) {
//                 spawn_triangle_break_particles(20, 138, 3.0f, 4);
//                 create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
//                 mark_obj_for_deletion(o->prevObj);
//                 mark_obj_for_deletion(o);
//                 spawn_default_star(o->oPosX,o->oPosY+150.0f,o->oPosZ);
//             } else {
//                 o->prevObj->oFaceAngleYaw += 0x300;
//             }
//         break;
//     }
// }

// void bhv_grate30(void) {
//     if (gMarioState->numStars > 29) {
//         obj_mark_for_deletion(o);
//     }
// }

// void bhv_bleed_particle(void) {
//     o->oVelY -= 1.0f;
//     o->oPosY += o->oVelY;
//     if (o->oPosY < o->oHomeY) {
//         mark_obj_for_deletion(o);
//     }
// }

// void agheart_spawn_blood(void) {
//     struct Object *oparticle;
//     oparticle = spawn_object(o,MODEL_BLOOD_PARTICLE,bhvBleed);
//     oparticle->oPosX = (random_float()*500.0f)-250.0f;
//     oparticle->oPosZ = (random_float()*500.0f)-250.0f;
//     oparticle->oPosY -= 550.0f;
// }

// u16 agheart_beat_offset = 0;
// void bhv_agheart(void) {
//     struct Object *bloodcol = cur_obj_nearest_object_with_behavior(bhvBloodCollision);
//     struct Object *blood = cur_obj_nearest_object_with_behavior(bhvBlood);
//     struct Object *spawnobj;
//     f32 scale1 = 0.2f*(sins(agheart_beat_offset*200));
//     f32 scale2 = 0.05f*(sins(agheart_beat_offset*1430));
//     f32 scale3 = 0.02f*(sins(agheart_beat_offset*2980));
//     u16 agcrumble_freq = 0;
//     obj_scale(o,1.0f + scale1 + scale2 + scale3);

//     agheart_beat_offset += (4 - aghealth);

//     if (blood&&bloodcol) {
//         bloodcol->oPosY = blood->oPosY;
//         bloodcol->oPosX = gMarioState->pos[0];
//         bloodcol->oPosZ = gMarioState->pos[2];
//     }

//     switch(o->oAction) {
//         case 0://init
//             spawn_object(o,MODEL_NONE,bhvBloodCollision);
//             agheart_beat_offset = 0;
//             aghealth = 3;
//             agstate = 0;
//             o->oAction++;
//         break;
//         case 1://wait to be struck
//             switch(aghealth) {
//                 case 2:
//                     agcrumble_freq = 20 + (random_u16()%6);
//                 break;
//                 case 1:
//                     agcrumble_freq = 8 + (random_u16()%4);
//                 break;
//             }

//             if (aghealth != 3) {
//                 if (o->oTimer % agcrumble_freq == 0) {
//                     spawn_object(o,MODEL_AGCRUMBLE,bhvAgcrumble);
//                     agheart_spawn_blood();
//                 }
//             }


//             if (o->oDistanceToMario < 1500.0f) {
//                 gMarioState->flags &= ~MARIO_SPECIAL_CAPS;
//                 gMarioState->RFuel = 0;
//                 drop_and_set_mario_action(gMarioState, ACT_BACKWARD_AIR_KB, 0);
//                 o->oAction = 2;
//                 run_event(EVENT_AGHEART_STRUCK);
//             }
//         break;
//         case 2://struck
//             agheart_beat_offset += 6;
//         break;
//         case 3://bleeding
//             cur_obj_play_sound_1(SOUND_ENV_WATER_DRAIN);
//             if (blood) {
//                 blood->oPosY += 4.0f;
//             }
//             agheart_spawn_blood();

//             if (o->oTimer > 60) {
//                 o->oAction = 4;
//             }
//         break;
//         //4: do nothing
//         case 5://send a portal at mario
//             spawn_object(o,MODEL_AGPORTAL,bhvAgportal);
//             o->oAction ++;
//         break;
//         case 6://wait for mario to get warped
//             if (agstate == 1) {
//                 o->oAction++;
//             }
//         break;
//         case 7://wait for mario to come back
//             if (agstate == 0) {
//                 o->oAction=1;
//             }
//         break;
//         case 8://DEAD!!! DYING!!! DONE!!!!
//             agstate = 0;
//             agheart_beat_offset += 15;
//             set_camera_shake_from_point(SHAKE_POS_LARGE, gLakituState.pos[0],gLakituState.pos[1],gLakituState.pos[2]);
//             if (o->oTimer % 3 == 0) {
//                 agheart_spawn_blood();
//                 spawnobj = spawn_object(o,MODEL_EXPLOSION,bhvExplosionFake);
//                 spawnobj->oPosX = (random_float()*1300.0f) - 650.0f;
//                 spawnobj->oPosY = o->oPosY + (random_float()*1600.0f) - 800.0f;
//                 spawnobj->oPosZ = (random_float()*1300.0f) - 650.0f;
//             }
//         break;
//         //9 do nothing
//         case 10:
//             agstate = 1;
//             o->oAction = 9;
//         break;
//     }
// }

// void bhv_agportal(void) {
//     f32 dx = gMarioObject->header.gfx.pos[0] - o->oPosX;
//     f32 dy = gMarioObject->header.gfx.pos[1] - o->oPosY + 120.0f;
//     f32 dz = gMarioObject->header.gfx.pos[2] - o->oPosZ;
//     s16 targetPitch = atan2s(sqrtf(sqr(dx) + sqr(dz)), dy);
//     obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x1000);
//     o->oMoveAnglePitch = approach_s16_symmetric(o->oMoveAnglePitch, targetPitch, 0x1000);
//     o->oVelY = sins(o->oMoveAnglePitch) * 30.0f;
//     o->oForwardVel = coss(o->oMoveAnglePitch) * 30.0f;
//     object_step();

//     if ((o->oDistanceToMario < 300.0f)&&(o->oTimer > 20)) {
//         create_sound_spawner(SOUND_GENERAL_PAINTING_EJECT);
//         gMarioState->PortalTint = 1.0f;
//         mark_obj_for_deletion(o);

//         agstate = !agstate;
//         if (agstate) {
//             aghealth--;
//             gMarioState->pos[0] = 0.0f;
//             gMarioState->pos[1] = -9000.0f;
//             gMarioState->pos[2] = 1400.0f;

//             warp_camera(0.0f, -9000.0f ,0.0f);
//         } else {
//             gMarioState->pos[0] = 0.0f;
//             gMarioState->pos[1] = 2000.0f;
//             gMarioState->pos[2] = 6000.0f;

//             gLakituState.curPos[1] = 9000.0f;
//             gLakituState.curFocus[1] = 9000.0f;
//             gLakituState.goalPos[1] = 9000.0f;
//             gLakituState.goalFocus[1] = 9000.0f;
//         }
//     }
// }

// s32 check_mario_cracking(void) {
//     if (lateral_dist_between_objects(gMarioObject,o)<300.0f) {
//         /*
//         if (abs_angle_diff(o->oFaceAngleYaw, gMarioObject->oMoveAngleYaw) > 0x6000) {
//             if (gMarioStates[0].action == ACT_SLIDE_KICK      ) return TRUE;
//             if (gMarioStates[0].action == ACT_PUNCHING        ) return TRUE;
//             if (gMarioStates[0].action == ACT_MOVE_PUNCHING   ) return TRUE;
//             if (gMarioStates[0].action == ACT_SLIDE_KICK_SLIDE) return TRUE;
//             if (gMarioStates[0].action == ACT_JUMP_KICK       ) return TRUE;
//             if (gMarioStates[0].action == ACT_WALL_KICK_AIR   ) return TRUE;
//         }
//         */
//         if (wall_slapped == TRUE) {
//             return TRUE;
//         }
//     }

//     if (lateral_dist_between_objects(gMarioObject,o)<400.0f) {
//         wall_slapped = FALSE;
//     }

//     return FALSE;
// }

// void bhv_agcrack(void) {
//     switch(o->oAction) {
//         case 0:
//             if (check_mario_cracking()) {
//                 if (o->oAnimState < 2) {
//                         create_sound_spawner(SOUND_GENERAL_POUND_WOOD_POST);
//                         o->oAnimState ++;
//                         o->oAction ++;
//                     } else {
//                         create_sound_spawner(SOUND_CUSTOM_PEACH_BAKE_A_CAKE);
//                         spawn_triangle_break_particles(20, MODEL_DIRT_ANIMATION, 3.0f, 4);
//                         if (aghealth > 0) {
//                             spawn_object(o,MODEL_AGPORTAL,bhvAgportal);
//                         } else {
//                             spawn_default_star(o->oPosX,o->oPosY,o->oPosZ);
//                         }
//                         obj_mark_for_deletion(o);
//                     }
//             }
//             break;
//         case 1:
//             if (o->oTimer > 20) {
//                 o->oAction = 0;
//             }
//             break;
//     }
// }

// u16 agpillar_model_table[] = {
//     MODEL_AGPILLAR1,
//     MODEL_AGPILLAR2,
//     MODEL_AGPILLAR3
// };

// u32 agpillar_collision_table[] = {
//     agpillar1_collision,
//     agpillar2_collision,
//     agpillar3_collision,
// };

// void bhv_agpillars(void) {
//     u8 pillar_set = 0;

//     switch(o->oAction) {
//         case 0://init
//             o->oAction++;
//             o->oPosY = o->oHomeY-3000.0f;
//         break;
//         case 1://pick
//             switch(aghealth) {
//                 case 3:
//                     pillar_set = 0;
//                 break;
//                 case 2:
//                     pillar_set = 1;
//                 break;
//                 case 1:
//                     pillar_set = 2;
//                 break;
//             }

//             o->collisionData = segmented_to_virtual(agpillar_collision_table[pillar_set]);
//             o->header.gfx.sharedChild = gLoadedGraphNodes[agpillar_model_table[pillar_set]];
//             o->oAction++;
//         break;
//         case 2://come out of the ground
//             cur_obj_play_sound_1(SOUND_ENV_METAL_BOX_PUSH);
//             o->oPosY += 40.0f;
//             if (o->oPosY > o->oHomeY) {
//                 o->oPosY = o->oHomeY;
//                 o->oAction++;
//             }
//         break;
//         case 3://exist out of the ground, wait for player to get warped out
//             load_object_collision_model();
//             if (agstate == 1) {
//                 o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_NONE];
//                 o->oAction ++;
//             }
//         break;
//         case 4://sit above surface model unloaded til mario comes back
//             if ((agstate == 0)&&(aghealth!=0)) {
//                 o->oPosY = o->oHomeY-3000.0f;
//                 o->oAction = 1;
//             }
//         break;
//     }
// }

// void bhv_agwall(void) {
//     u16 wall_spin_speed = 0x50;
//     f32 blood_height = 0.0f;
//     struct Object *blood_obj;

//     blood_obj = cur_obj_nearest_object_with_behavior(bhvBlood);
//     if (blood_obj != NULL) {
//         blood_height = blood_obj->oPosY;
//     }

//     switch(aghealth) {
//         case 2:
//             wall_spin_speed = 0x100;
//         break;
//         case 1:
//             wall_spin_speed = 0x140;
//         break;
//     }

//     switch(o->oAction) {
//         case 0:
//             o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_NONE];
//             o->oPosY = o->oHomeY + 4000.0f;

//             if (gMarioState->RFuel > 0) {
//                 o->oAction = 1; //MARIO HAS THE ROCKET BOOTS! PROTECT YOURSELF!
//                 o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_AGWALL];
//             }
//         break;
//         case 1://cum down
//             o->oPosY = lerp(o->oPosY,o->oHomeY,0.15f) + (sins(o->oTimer*0x200)*100.0f);
//             o->oFaceAngleYaw += wall_spin_speed;
//             if (aghealth < 3) {
//                 o->oHomeY = gMarioState->pos[1];
//             }
//             if (gMarioState->RFuel == 0) {
//                 o->oAction ++; //welp no more worry
//             }
//             if (o->oPosY < 1250.0f+blood_height) {
//                 o->oPosY = 1251.0f+blood_height;
//             }
//         break;
//         case 2://no more rocket boots so go away
//             o->oPosY = lerp(o->oPosY,o->oHomeY+4000.0f,0.05f);
//             if (o->oTimer > 100) {
//                 o->oAction = 0;
//             }
//         break;
//     }
// }

// void bhv_agcrumble(void) {
//     f32 range = 8000.0f;

//     /*
//     if (revent_stop_enemies) {
//         return;
//     }

//     if (gCurrLevelNum == LEVEL_BITDW) {
//         range = 2000.0f;
//         o->oDamageOrCoinValue = 2;
//     }
//     */

//     f32 half_range = range/2.0f;
//     switch(o->oAction) {
//         case 0:
//             o->oPosX = gMarioState->pos[0] + /*(sins(gMarioState->faceAngle[1])*2000.0f) +*/ ((random_float()*range)-half_range);
//             o->oPosY = gMarioState->pos[1] + 3500.0f;
//             o->oPosZ = gMarioState->pos[2] + /*(coss(gMarioState->faceAngle[1])*2000.0f) +*/ ((random_float()*range)-half_range);

//             //this is decoration, so delete nearby to not confuse player
//             if (lateral_dist_between_objects(o,gMarioObject) < 2500.0f) {
//                 mark_obj_for_deletion(o);
//             }

//             o->oHomeY = find_floor_height(o->oPosX,o->oPosY,o->oPosZ);
//             o->oAction++;
//         break;
//         case 1:
//             o->oVelY -= 0.6f;
//             o->oPosY += o->oVelY;
//             if (o->oVelY < -30.0f) {
//                 o->oVelY = -30.0f;
//             }
//             o->oFaceAngleYaw += 0x200*3;
//             o->oFaceAnglePitch += 0x100*3;
//             o->oFaceAngleRoll += 0x136*3;
//             if ((o->oPosY < o->oHomeY)||(o->oPosY < 0.0f)) {
//                 set_camera_shake_from_point(SHAKE_POS_SMALL, o->oPosX, o->oPosY, o->oPosZ);
//                 create_sound_spawner(SOUND_GENERAL_POUND_ROCK);
//                 cur_obj_spawn_particles(&sCrumbleParticles);
//                 obj_mark_for_deletion(o);
//             }
//         break;
//     }
// }

// void bhv_agring(void) {
//     s16 extra_speed = 0;
//     if (aghealth == 1) {
//         extra_speed = 0x30;
//     }
//     if (aghealth == 0) {
//         extra_speed = 0x120;
//     }

//     switch(o->oAction) {
//         case 0://wait for ag to be damaged
//             o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
//             if (aghealth == 2) {
//                 o->oAngleVelYaw = 0x40 + (random_u16()%0x30);
//                 o->oAngleVelRoll = 0x40 + (random_u16()%0x30);
//                 o->oAction = 1;
//             }
//         break;
//         case 1:
//             o->oFaceAngleYaw += o->oAngleVelYaw + extra_speed;
//             o->oFaceAngleRoll += o->oAngleVelRoll + extra_speed;
//             if (agstate == 1) {
//                 o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
//                 o->oAction = 2;
//             }
//         break;
//         case 2://in static dimension, wait for mario to come back
//             if (agstate == 0) {
//                 o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
//                 o->oAction = 1;
//             }
//         break;
//     }
// }

// void bhv_palamedes(void) {
//     s8 i;
//     struct Object *bullet;

//     if (agstate == 1 || revent_stop_enemies) {
//         o->oTimer = 0;
//         if (agstate == 1) {
//             o->oPosX = 0.0f;
//             o->oPosY = 0.0f;
//             o->oPosZ = 0.0f;
//         }
//         return;
//     }

//     switch(o->oAction) {
//         case 0://init
//             o->oAction = 1;
//         break;
//         //1 = nothing
//         case 2://chase mario
//             //look at mario
//             o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, o->oAngleToMario, 0x200);

//             //follow him
//             if (o->oDistanceToMario < 1600.0f) {
//                 o->oForwardVel = approach_f32_symmetric(o->oForwardVel, -20.0f ,0.5f);
//             } else {
//                 o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 25.0f ,0.7f);
//                 if (o->oDistanceToMario > 2500.0f) {
//                     o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 40.0f ,1.0f);
//                 }
//             }

//             o->oPosX += o->oForwardVel*sins(o->oFaceAngleYaw);
//             o->oPosZ += o->oForwardVel*coss(o->oFaceAngleYaw);
//             o->oPosY = lerp(o->oPosY, gMarioState->pos[1], 0.1f);

//             if (o->oTimer > 120) {
//                 if (random_u16()%2==0) {
//                     o->oAction = 3;
//                     cur_obj_play_sound_2(SOUND_OBJ_BOWSER_SPINNING);
//                     cur_obj_init_animation_with_sound(1);
//                 } else {
//                     o->oAction = 4;
//                     cur_obj_init_animation_with_sound(2);
//                 }
//             }
//         break;
//         case 3://slap the shit out of mario
//             o->oForwardVel = 0.0f;
//             if (o->oTimer == 30) {
//                 cur_obj_play_sound_2(SOUND_OBJ_BOWSER_SPINNING);
//             }
//             if (o->oTimer > 30) {
//                 o->oForwardVel = 60.0f;
//             }
//             o->oPosX += o->oForwardVel*sins(o->oFaceAngleYaw);
//             o->oPosZ += o->oForwardVel*coss(o->oFaceAngleYaw);

//             if (o->oTimer > 90) {
//                 o->oForwardVel /= 2.0f;
//                 o->oAction = 2;
//                 cur_obj_init_animation_with_sound(0);
//             }
//         break;
//         case 4://throw shit everywhere
//             //look at mario
//             o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, o->oAngleToMario, 0x200);

//             if (o->oTimer == 30) {
//                 cur_obj_play_sound_2(SOUND_GENERAL_CASTLE_TRAP_OPEN);

//                 for (i = -2; i<3; i++) {
//                     bullet = spawn_object(o, MODEL_COSMIC_SPIKE, bhvCosmicProjectile);
//                     bullet->oPosY += 80.0f;
//                     gMarioObject->oPosY+= 80.0f;
//                     bullet->oMoveAnglePitch = obj_turn_toward_object(bullet, gMarioObject, O_MOVE_ANGLE_PITCH_INDEX, 200);
//                     gMarioObject->oPosY-= 80.0f;
//                     bullet->oMoveAngleYaw = o->oFaceAngleYaw+(i*0x600);
//                 }
//             }
//             if (o->oTimer > 59) {
//                 o->oAction = 2;
//                 cur_obj_init_animation_with_sound(0);   
//             }
//         break;
//     }
// }

// void bhv_agboom(void) {
//     f32 size = (o->oTimer*0.25f);
//     if (size > 88.0f) {
//         size = 88.0f;
//     }
//     cur_obj_scale(size);
// }

// struct Object *fptr;
// f32 flame_scale = 3.0f;
// //probably not a good idea but who fucking cares at this point

// void bhv_agmoon(void) {
//     switch(o->oAction) {
//         case 0://wait for final cutscene
//             o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
//         break;
//         case 1://slowly fall to the earth
//             o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
//             o->oPosX = o->oHomeX - (f32)((o->oTimer) + (o->oTimer%3));
//             o->oPosZ = o->oHomeZ + (f32)((o->oTimer) + (o->oTimer%3));
//             o->oPosY = o->oHomeY - (f32)((o->oTimer) + (o->oTimer%3));

//             if (o->oTimer > 910) {
//                 create_sound_spawner(SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION);
//                 o->oAction = 2;
//                 fptr = spawn_object(o,MODEL_AGFLAMES,bhvStaticObject);
//                 flame_scale = 6.0f;
//             }
//         break;
//         case 2://control the flames
//             o->oPosX -=0.5f;
//             o->oPosZ +=0.5f;
//             o->oPosY -=0.5f;

//             fptr->header.gfx.scale[0] = flame_scale;
//             fptr->header.gfx.scale[2] = flame_scale;
//             flame_scale+=.015f;
//             if (flame_scale > 23.0f) {
//                 flame_scale = 23.0f;
//             }
//         break;
//     }
// }

// void bhv_quest(void) {
//     o->oPosY = o->oHomeY + 320.0f + (sins(o->oTimer*0x100)*20.0f);
// }

// void bhv_agamemnon_stairs(void) {
//     if (!save_file_check_progression(PROG_POSTGAME)) {
//         mark_obj_for_deletion(o);
//     }
// }

// void bhv_highcane(void) {
//     struct Object *crow;
//     switch(o->oAction) {
//         case 0://init
//             o->oFaceAngleYaw = random_u16();
//             o->oAction = 1;
//         break;
//         case 1://wait to be cut
//             crow = cur_obj_nearest_object_with_behavior(bhvCrowbarThrow);
//             if (crow) {
//                 if ((lateral_dist_between_objects(o,crow) < 300.0f)&&(crow->oPosY < o->oPosY+400.0f)) {
//                     o->oAction = 2;
//                     gMarioState->CheeseCollection ++; //highcane is cannonically made out of cheese- confirmed???
//                     create_sound_spawner(SOUND_GENERAL_DOOR_TURN_KEY);
//                 }
//             }
//         break;
//         case 2://cut
//             o->oPosY += o->oVelY;
//             o->oVelY -= 1.0f;

//             o->oFaceAngleRoll += 0x40;

//             if (o->oTimer > 40) {
//                 mark_obj_for_deletion(o);
//             }
//         break;
//     }
// }

// u8 pipes_blown = 0;

// void bhv_pipe_ccm(void) {
//     struct Object *obj;
//     struct Object *obj2;

//     switch(o->oAction) {
//         case 0:
//             o->oAction++;
//             pipes_blown = 0;
//         break;
//         case 1:
//             if (cur_obj_was_attacked_or_ground_pounded()) {
//                 o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_PIPE2_CCM];
//                 o->oAction++;
//                 pipes_blown++;

//                 set_mario_action(gMarioState, ACT_THROWN_BACKWARD, 0);
//                 gMarioState->vel[1] = 35.0f;
//                 gMarioState->forwardVel = -200.0f;
//                 gMarioState->faceAngle[1] = o->oFaceAngleYaw;

//                 if (pipes_blown == 2) {
//                     obj2 = cur_obj_nearest_object_with_behavior(bhvExecutive);
//                     //No NULL check. Too bad! Cry like little neurotypical programmers, bitches.

//                     //note from future me: is this technically ableist? if so, i'm sorry...
//                     obj = spawn_object(obj2,MODEL_TVHEAD_CCM,bhvTVhead);
//                     obj->oBehParams2ndByte = 1;//BehParam2 = For the showrunner boss.
//                     obj->oPosY -= 1200.0f; //Just a guesstimation, slightly below the cylinder...
//                     obj->oFlags |= OBJ_FLAG_ACTIVE_FROM_AFAR;
//                 }

//                 if (pipes_blown >= 4) {
//                     clear_costmic_phantasms();
//                     run_event(EVENT_EXECUTIVE_DEFEAT);
//             }
//             }
//         break;
//         case 2:
//             //smoking
//             if (o->oTimer % 15 == 0) {
//                 struct Object *smoke;
//                 smoke = spawn_object(o,MODEL_BURN_SMOKE ,bhvBlackSmokeMario);
//                 smoke->oPosY += 800.0f;
//                 smoke->oPosX += sins(o->oFaceAngleYaw) * 300.0f;
//                 smoke->oPosZ += coss(o->oFaceAngleYaw) * 300.0f;
//             }
//         break;
//     }
// }

// s16 missile_side_to_shoot = 1200;
// s16 missile_angle = 0x4000;
// void bhv_executive_cylinder(void) {
//     s16 old_angle;
//     u8 run_conveyor = (pipes_blown!=4);
//     struct Object *conv;
//     struct Object *spawnobj;

//     switch(o->oAction) {
//         case 0:
//             //init
//             missile_side_to_shoot = 1200;
//             missile_angle = 0x4000;
//             run_event(EVENT_EXECUTIVE_INTRO);
//             o->oAction++;
//         break;
//         case 1:
//             //normal operation
//             o->oFaceAngleYaw += (pipes_blown+1)*0x120;

//             if (!revent_active) {
//                 if (o->oTimer % (45-(7*pipes_blown)) == 0) {
//                     missile_side_to_shoot = -missile_side_to_shoot;
//                     missile_angle = -missile_angle;
//                     cur_obj_play_sound_2(SOUND_OBJ_POUNDING_CANNON);
//                     spawnobj = spawn_object_relative(0, missile_side_to_shoot, 300, 0, o, MODEL_EXEC_MISSILE, bhvMissile);
//                     spawnobj->oMoveAngleYaw = o->oFaceAngleYaw+missile_angle;
//                     spawnobj->oHomeY = o->oPosY;
//                 }
//             }
//         break;
//         case 2://destruction init
//             o->oAction++;
//             o->oAngleVelYaw = 0x100;
//         break;
//         case 3://destruction loop
//             o->oAngleVelYaw += 0x20;
//             old_angle = o->oFaceAngleYaw;
//             o->oFaceAngleYaw += o->oAngleVelYaw;
//             if ((old_angle < 0)&&(o->oFaceAngleYaw>0)) {
//                 cur_obj_play_sound_2(SOUND_OBJ_BOWSER_SPINNING);
//             }

//             if (o->oTimer > 300) {
//                 o->oAction++;
//                 play_sound(SOUND_GENERAL_BOWSER_BOMB_EXPLOSION, gGlobalSoundSource);
//                 o->oVelX = 70.0f;
//                 o->oVelY = 0.0f;
//             }
//         break;
//         case 4://explode and fall off
//             o->oPosX += o->oVelX;
//             o->oPosY += o->oVelY;
//             o->oVelY -= 1.0f;
//             o->oVelX *= .95;
//             o->oFaceAngleRoll += 0x150;

//             if (o->oPosY < 0.0f) {
//                 o->oAction ++;
//                 //on ground now
//                 cur_obj_play_sound_2(SOUND_GENERAL_ELEVATOR_LAND);
//             }
            
//         break;
//         //case 5 is nothing
//         case 6: //talk to mario
//             o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, o->oAngleToMario, 0x200);
//         break;
//     }

//     if (run_conveyor) {
//         conv = cur_obj_nearest_object_with_behavior(bhvConv2CCM);
//         conv->oFaceAngleYaw += 0x50;
//         conv = cur_obj_nearest_object_with_behavior(bhvConv1CCM);
//         conv->oFaceAngleYaw -= 0x100;
//     }
// }

// Vec3f tv_corpse_Size = {80.0f,100.0f,100.0f};

// Vec3f Cube_Vertices[8] = {
//     {1.0f,1.0f,1.0f},
//     {-1.0f,1.0f,1.0f},
//     {-1.0f,1.0f,-1.0f},
//     {1.0f,1.0f,-1.0f},
//     {1.0f,-1.0f,1.0f},
//     {-1.0f,-1.0f,1.0f},
//     {-1.0f,-1.0f,-1.0f},
//     {1.0f,-1.0f,-1.0f}
// };

// struct MeshInfo Cube_Mesh = {
//     Cube_Vertices,
//     NULL,
//     NULL,
//     NULL,
//     8, // Number of vertices
//     0,
//     0,
//     0
// };

// void bhv_tv_head_corpse(void) {
//     struct RigidBody *body = allocate_rigid_body_from_object(o, &Cube_Mesh, 2.f, tv_corpse_Size, FALSE);
//     Vec3f force;
//     force[1] = -20.0f;
//     force[0] = sins(o->header.gfx.angle[1]+0x4000)*80.0f*o->header.gfx.scale[0];
//     force[2] = coss(o->header.gfx.angle[1]+0x4000)*80.0f*o->header.gfx.scale[0];
//     rigid_body_add_force(body, &gMarioState->pos[0], force, TRUE);
// }

// void bhv_tv_head_corpse_loop(void) {
//     if (o->oTimer > 60) {
//         o->rigidBody->allocated = FALSE;
//         mark_obj_for_deletion(o);
//     }
// }



// void bhv_new_motos(void) {
//     struct Object *flame;

//     switch(o->oAction) {
//         case 0:
//             //init
//             o->oPosY = o->oHomeY - 900.0f;
//             o->oAction++;
//         break;
//         case 1:
//             //wait underwater for mario
//             if (o->oDistanceToMario < 2500.0f) {
//                 o->oAction++;
//                 cur_obj_init_animation_with_sound(6);
//             }
//         break;
//         case 2:
//             //rise from the water
//             o->oPosY = lerp(o->oPosY,o->oHomeY-300.0f,0.1f);
//             if (o->oTimer > 25) {
//                 o->oAction++;
//                 cur_obj_init_animation_with_sound(2);
//                 o->oHealth = random_u16()%20;//in this context, health means random timer offset
//             }
//         break;
//         case 3://blow 
//             o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x200);

//             if ((o->oTimer+o->oHealth) % 90 < 30) {
//                 cur_obj_play_sound_1(SOUND_AIR_BLOW_FIRE);

//                 o->oFlameThowerTimeRemaining = 40;
//                 flame = spawn_object_relative(o->oBehParams2ndByte, 0, 760, 0, o, MODEL_BLUE_FLAME, bhvFlamethrowerFlame);
//                 flame->oForwardVel = 40.0f;
//                 flame->oGravity = random_float()-.5f;

//                 cur_obj_play_sound_1(SOUND_AIR_BLOW_FIRE);
//             }

//             if (o->oDistanceToMario > 3000.0f) {
//                 //go underwater
//                 o->oAction++;
//                 cur_obj_init_animation_with_sound(5);
//             }
//         break;
//         case 4://submerge
//             o->oPosY = lerp(o->oPosY,o->oHomeY-900.0f,0.1f);
//             if (o->oTimer > 50) {
//                 o->oAction = 0;
//             }
//         break;
//     }
// }

// void bhv_tutorial_gate_loop(void) {
//     switch(o->oAction) {
//         case 0:
//             o->oOpacity = 255;
//             o->oAction = 1;
//         break;
//         case 1:

//             switch(o->oBehParams2ndByte) {
//                 case 0: // Upgrade character
//                     if (gMarioState->Level > 0) {
//                         o->oAction = 2;
//                     }
//                 break;
//                 case 1: // Equip a badge
//                     if (save_file_get_badge_equip()) {
//                         o->oAction = 2;
//                     }
//                 break;
//                 case 2: // Grab a wallet
//                     if (save_file_get_wallet_unlock()) {
//                         o->oAction = 2;
//                     }
//                 break;
//             }

//         break;
//         case 2: //Vanish
//             if (o->oOpacity > 4) {
//                 o->oOpacity -= 4;
//             } else {
//                 mark_obj_for_deletion(o);
//             }
//         break;
//     }
// }

// void bhv_tutorial_platform_loop(void) {
//     switch((o->oTimer/25)%4) {
//         case 0:
//             o->oPosX += 30.0f;
//         break;
//         case 2:
//             o->oPosX -= 30.0f;
//         break;
//     }
// }

// void bhv_agtri_loop(void) {
//     if ((agstate == 0)&&(aghealth!=0)) {
//         o->oTimer = 0;
//         o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
//         o->oPosY = o->oHomeY-1000.0f;
//     }

//     if (o->oTimer > 600) {
//         o->oPosY = lerp(o->oPosY,o->oHomeY,0.1f);
//         o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
//         load_object_collision_model();
//     }
// }

// //"form" in the context of my own code usually means a "platform"
// //however, here, it's uhhh, a "form" as in an entity
// //kind of shit i know, but this is literally the last behavior i have
// //to code before i finish cursed mirror ONCE AND FOR ALLLLLLLL
// void bhv_agform_loop(void) {
//     struct Object *flame;
//     u8 scaleaxis = 1;

//     o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;

//     if ((agstate == 0)||(revent_active)) {
//         o->oAction = 0;
//         o->oTimer = 0;
//         return;
//     }

//     switch(o->oAction) {
//         case 0:
//         cur_obj_become_tangible();
//         o->header.gfx.scale[1] = 1.0f + (sins(o->oTimer*0x300)*0.2f);
//         o->header.gfx.scale[0] = 1.0f + (coss(o->oTimer*0x300)*0.2f);
//         o->header.gfx.scale[2] = 1.0f + (coss(o->oTimer*0x300)*0.2f);

//         switch(aghealth) {
//             case 2: //urbowser reprise
//                 o->oFaceAngleYaw = o->oAngleToMario;
//                 o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
//                 o->header.gfx.sharedChild =  gLoadedGraphNodes[MODEL_FORM1];
//                 o->oFaceAnglePitch = 0x4000;
//                 if ((o->oTimer%60) == 44) {
//                     cur_obj_play_sound_2(SOUND_OBJ_FLAME_BLOWN);
//                 }
//                 if ((o->oTimer%60) > 45) {
//                     flame = spawn_object(o,MODEL_BLUE_FLAME,bhvThwompFlame);
//                     flame->oForwardVel = 50.0f;
//                     flame->oMoveAngleYaw = o->oFaceAngleYaw;
//                 }
//             break;
//             case 1: //executive reprise
//                 o->oFaceAngleYaw = o->oAngleToMario;
//                 o->oFaceAnglePitch = 0x0;
//                 o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
//                 o->header.gfx.sharedChild =  gLoadedGraphNodes[MODEL_FORM2];

//                 if (o->oTimer < 2) {
//                     missile_side_to_shoot = 200;
//                     missile_angle = 0x4000;
//                 }

//                 if (o->oTimer % 30 == 0) {
//                     missile_side_to_shoot = -missile_side_to_shoot;
//                     missile_angle = -missile_angle;
//                     cur_obj_play_sound_2(SOUND_OBJ_POUNDING_CANNON);
//                     flame = spawn_object_relative(0, missile_side_to_shoot, 100, 0, o, MODEL_FORM2A, bhvMissile);
//                     flame->oMoveAngleYaw = o->oFaceAngleYaw+missile_angle;
//                     flame->oHomeY = o->oPosY;
//                 }
//             break;
//             case 0://showrunner reprise
//                 o->oFaceAnglePitch = 0x0;
//                 o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
//                 o->header.gfx.sharedChild =  gLoadedGraphNodes[MODEL_FORM3];
//                 if (o->oTimer < 2) {
//                     o->oAngleVelYaw = 0;
//                 }
//                 if (o->oTimer > 30) {
//                     s16 old_angle = o->oFaceAngleYaw;
//                     o->oFaceAngleYaw += o->oAngleVelYaw;
//                     o->oAngleVelYaw += 0x20;

//                     if ((old_angle < 0)&&(o->oFaceAngleYaw > 0)) {
//                         cur_obj_play_sound_2(SOUND_OBJ_BOWSER_SPINNING);
//                     }

//                     f32 suck = ((f32)o->oAngleVelYaw/500.0f);
//                     if (o->oDistanceToMario < 300.0f) {
//                         //TOO CLOSE! Blow mario out
//                         gMarioState->pos[0] += sins(o->oAngleToMario)*suck;
//                         gMarioState->pos[2] += coss(o->oAngleToMario)*suck;
//                     } else {
//                         gMarioState->pos[0] -= sins(o->oAngleToMario)*suck;
//                         gMarioState->pos[2] -= coss(o->oAngleToMario)*suck;
//                     }
//                     if (o->oAngleVelYaw > 0x2000) {
//                         o->oAngleVelYaw = 0x2000;
//                     }
//                     if (o->oSubAction==0) {
//                         if ((o->oTimer % 3 == 0)&&(o->oAngleVelYaw>0x1000)) {
//                             flame = spawn_object(o,MODEL_METAL_STAR,bhvCosmicProjectile);
//                             flame->oPosY = o->oPosY+(random_float()*500.0f);
//                             flame->oMoveAngleYaw = random_u16();
//                             flame->oMoveAnglePitch = 0;
//                         }
//                         if ((o->oTimer % 2 == 0)&&(o->oTimer>400)) { //not to overwhelm the player in the final phase
//                             flame = spawn_object(o,MODEL_METAL_STAR,bhvCosmicProjectile);
//                             flame->oPosY = o->oPosY+(random_float()*500.0f);
//                             flame->oMoveAngleYaw = random_u16();
//                             flame->oMoveAnglePitch = 0;
//                         }
//                     }
//                 }
//             break;
//         }
//         if (o->oTimer > 600) {
//             o->oAction = 1;
//         }
//         break;
//         case 1: //shrink and vanish
//             cur_obj_become_intangible();
//             if (aghealth == 2) {
//                 scaleaxis = 2;
//             }
//             if (o->header.gfx.scale[scaleaxis] > 0.03f) {
//                 o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
//                 o->header.gfx.scale[scaleaxis] = o->header.gfx.scale[scaleaxis] * 0.95f;
//             } else {
//                 o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
//             }
//         break;
//     }
// }

// //hint dispenser

// void bhv_postgame_hint() {
//     u16 costume_flags = save_file_get_costume_unlock();
//     u16 hint_dialog = DIALOG_COSTUME_END;
//     u8 i;

//     o->oInteractionSubtype = INT_SUBTYPE_NPC;

//     switch(o->oAction) {
//         case 0:
//             if (save_file_check_progression(PROG_POSTGAME)) {
//                 o->oAction = 2;
//                 o->oHealth = 0;
//             } else {
//                 mark_obj_for_deletion(o);
//             }
//         break;
//         case 1://unused
//         break;
//         case 2:
//             if (o->oInteractStatus & INT_STATUS_INTERACTED) {
//                 o->oAction = 3;
//             }
//         break;
//         case 3:
//             for (i=0;i<15;i++) {
//                 if (!((costume_flags >> i) & 1)) {
//                     hint_dialog = (DIALOG_COSTUME_HINT1+i)-1;
//                 }
//             }

//             if (cur_obj_update_dialog_with_cutscene(2, 1, CUTSCENE_DIALOG, hint_dialog)) {
//                 o->oAction = 2;
//                 o->oBehParams2ndByte ++;
//             }
//         break;
//     }

//     o->oInteractStatus = 0;
// }

void bhv_tree_init() {
    df_tree(CMM_DF_CONTEXT_INIT);
}

void bhv_badge(void) {
    switch(o->oAction) {
        case 0:
            if ((save_file_get_badge_equip() >> o->oBehParams2ndByte) & 1) {
                o->oAction++;
                o->oHomeY = 1.0f;
                break;
            }
            if ((o->oDistanceToMario < 180.0f)&&(gMarioState->action != ACT_LVUP_DANCE)) {
                o->oAction++;
                mario_stop_riding_object(gMarioState);
                save_file_set_badge_equip(1 << o->oBehParams2ndByte);

                rtext_insert_pointer[0] = badgenames[o->oBehParams2ndByte];
                rtext_insert_pointer[1] = badgedescs[o->oBehParams2ndByte];

                o->oHomeY = 1.0f;

                if ((o->oBehParams2ndByte == BADGE_BRITTLE)||(o->oBehParams2ndByte == BADGE_WITHER)) {
                    run_event(EVENT_GET_BURDEN);
                } else {
                    run_event(EVENT_GET_BADGE);
                }
            }
            break;
        case 1:
            o->oAngleVelYaw += 0x70;
            o->oFaceAngleYaw += o->oAngleVelYaw;
            cur_obj_scale(o->oHomeY*5.0f);
            o->oHomeY = o->oHomeY *.95f;
            if (o->oHomeY < .2f) {
                obj_mark_for_deletion(o);
            }
            break;
    }
}

void bhv_warp_pipe_init(void) {
    // switch(o->oAction) {
    //     case 0:
    //         o->oPosY += 200.0f;
    //         spawn_object(o,MODEL_NONE,bhvCannon);
    //         o->oPosY -= 200.0f;
    //         o->oAction++;
    //     break;
    // }
}

void bhv_boss(void) {
    struct Object * baws;
    switch(o->oBehParams2ndByte) {
        case 0:
            baws = spawn_object(o,MODEL_KINGBOMB_MAKER,bhvKingBobomb);
        break;
        case 1:
            baws = spawn_object(o,MODEL_WHOMP_MAKER,bhvWhompKingBoss);
        break;
        case 3:
            baws = spawn_object(o,MODEL_WIGGLER_HEAD,bhvWigglerHead);
        break;
    }
    baws->oBehParams = o->oBehParams;
    mark_obj_for_deletion(o);
}

void bhv_onoffswitch(void) {
    switch(o->oAction) {
        case 0: // init
            o->oAnimState = o->oBehParams2ndByte;
            o->oAction = 1;
            break;
        case 1: // switch up
            o->header.gfx.scale[1] = approach_f32_symmetric(o->header.gfx.scale[1], 1.0f ,0.1f);
            if (gMarioObject->platform == o) {
                cur_obj_play_sound_2(SOUND_GENERAL_DOOR_TURN_KEY);
                cmm_play_onoff = o->oBehParams2ndByte;
            }
            if (o->oBehParams2ndByte == 0) {
                if (!cmm_play_onoff) {
                    o->oAction = 2;
                }
            } else { // Blue
                if (cmm_play_onoff) {
                    o->oAction = 2;
                }
            }
            break;
        case 2: // switch down
            o->header.gfx.scale[1] = approach_f32_symmetric(o->header.gfx.scale[1], 0.1f ,0.1f);
            if (o->oBehParams2ndByte == 0) {
                if (cmm_play_onoff) {
                    o->oAction = 1;
                }
            } else { // Blue
                if (!cmm_play_onoff) {
                    o->oAction = 1;
                }
            }
            break;
    }
}

void bhv_onoffblock(void) {
    o->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;

    switch(o->oAction){
        case 0: //init
            if (o->oBehParams2ndByte == 0) {
                o->oAnimState = 0;
            } else {
                o->oAnimState = 1;
            }
            o->oAction = 1;
            o->prevObj = spawn_object(o,MODEL_MAKER_BLOCK_3,bhvStaticObject);
            o->prevObj->oAnimState = !o->oBehParams2ndByte;
            break;
        case 1: //loop
            if (o->oBehParams2ndByte == 0) {
                if (cmm_play_onoff) {
                    o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_BLOCK_1];
                } else {
                    load_object_collision_model();
                    o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_BLOCK_2];
                }
            } else {
                if (cmm_play_onoff) {
                    load_object_collision_model();
                    o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_BLOCK_2];
                } else {
                    o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_BLOCK_1];
                }
            }
            o->prevObj->oFaceAngleYaw += 0x100;
            o->prevObj->oPosY = o->oPosY + sins(o->oTimer*0x200) * 4.0f;
            break;
    }
}

void bhv_woodplat(void) {
    f32 waterLevel = cmm_get_water_level(o->oPosX, o->oPosY, o->oPosZ);

    switch(o->oAction) {
        case 0:
            if (o->oBehParams2ndByte == 1) {
                o->prevObj = spawn_object(o,MODEL_NONE,bhvFatPlatCol);
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_FATPLAT];
                o->oWallHitboxRadius = 120.0f;
            } else {
                o->prevObj = spawn_object(o,MODEL_NONE,bhvWoodPlatCol);
                o->oWallHitboxRadius = 49.0f;
            }
            o->prevObj->prevObj = o;
            o->oAction = 1;
            break;
        case 1:
            if (waterLevel < o->oPosY) {
                // Air Behavior
                o->oGravity = -4.0f;
            } else {
                // Underwater Behavior
                if (ABS(o->oVelY) > 4.0f) {
                    o->oVelY *= 0.95f;
                }
                o->oGravity = -1.0f;
                if (waterLevel-50.0f > o->oPosY) {
                    o->oVelY += 2.0f;
                }
            }
            cur_obj_update_floor_and_walls();
            cur_obj_move_standard(-20);
            vec3f_copy(&o->prevObj->oPosVec,&o->oPosVec);
            break;
    }
}

void bhv_crush_handler(void) {
    obj_attack_collided_from_other_object(o);
    if (o->oTimer > 30) {
        mark_obj_for_deletion(o);
    }
    o->oInteractStatus = INT_NONE;
}