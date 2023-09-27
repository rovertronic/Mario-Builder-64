#include <PR/ultratypes.h>

#include "sm64.h"
#include "area.h"
#include "audio/external.h"
#include "behavior_actions.h"
#include "behavior_data.h"
#include "camera.h"
#include "engine/graph_node.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "engine/surface_load.h"
#include "game_init.h"
#include "interaction.h"
#include "level_table.h"
#include "level_update.h"
#include "main.h"
#include "mario.h"
#include "mario_actions_airborne.h"
#include "mario_actions_automatic.h"
#include "mario_actions_cutscene.h"
#include "mario_actions_moving.h"
#include "mario_actions_object.h"
#include "mario_actions_stationary.h"
#include "mario_actions_submerged.h"
#include "mario_misc.h"
#include "mario_step.h"
#include "memory.h"
#include "object_fields.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "print.h"
#include "save_file.h"
#include "menu/file_select.h"
#include "sound_init.h"
#include "rumble_init.h"
#include "puppycamold.h"
#include "actors/group0.h"
#include "levels/castle_grounds/header.inc.h"
#include "levels/castle_inside/header.inc.h"
#include "levels/castle_courtyard/header.inc.h"
#include "levels/ccm/header.inc.h"
#include "rovent.h"
#include "ingame_menu.h"
#include "cursed_mirror_maker.h"
#include "levels/castle_grounds/shrnling1/geo_header.h"

#include "src/buffers/framebuffers.h"
//gFrameBuffer0

#include "src/audio/synthesis.h"

u8 near_music_box = FALSE;

//COSTUME TABLE
u8 VanillaMario[] = {0xFE, 0x0, 0x0, 0x0, 0x0, 0xFE,0x72, 0x1B, 0xE};
u8 FireMario[] = {0xFF, 0xFF, 0xFF, 0xFE, 0x0, 0x0,0x72, 0x1B, 0xE};
u8 SMG4Mario[] = {0x0, 0x0, 0xFE, 0xFF, 0xFF, 0xFF,0x72, 0x1B, 0xE};
u8 LuigiMario[] = {0x0, 0xFE, 0x0, 0x0, 0x0, 0xFE,0x72, 0x1B, 0xE};
u8 WarioMario[] = {0xFE, 0xFE, 0x0, 0x80, 0x0, 0x80, 0x0, 0xA0, 0x0};
u8 RainbowMario[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0xFE,0x72, 0x1B, 0xE};
u8 CumMario[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,0x72, 0x1B, 0xE};
u8 SpookMario[] = {0x72, 0x72, 0x72, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08};
u8 FordMario[] = {0x57, 0x57, 0x57, 0x57, 0x57, 0x57,0xB8,0x6F,0x38};
u8 Darius[] = {0x7A,0xD2,0xC2,0x7A,0xD2,0xC2,0x72, 0x1B, 0xE};
u8 ButlerMario[] = {0x05, 0x05, 0x05, 0xF0, 0xF0, 0xF0, 0x10, 0x10, 0x10};
u8 RetroMario[] = {0x6E, 0x65 ,0x0B, 0xD5, 0x0F, 0x0F, 0x6E, 0x65, 0x0B};
u8 ThwompMario[] = {0x20,0xA0,0xF8, 0x0, 0x0, 0xFE, 0x20,0xA0,0xF8};
u8 BuilderMario[] = {0xFC,0xB7,0x2E,0xEE,0x00,0x00, 0x72, 0x1B, 0xE};
u8 ShowrunnerMario[] = {0x6E,0x20,0x00,0x00,0x7E,0xA7,0xFF,0xFF,0xFF};
u8 Phantasm[] = {0x61,0x3F,0x75,0x61,0x3F,0x75,0x61,0x3F,0x75};//Color values not actually used; except for the token

u8* CostumeData[] = {
    VanillaMario,//unlocked at start
    FireMario,//c1
    SMG4Mario,//c10
    LuigiMario,//hub
    WarioMario,//c2
    RainbowMario,//c10
    SpookMario,//c5
    FordMario,//c4
    Darius,//c2
    ButlerMario,//c7
    RetroMario,//c8
    ThwompMario,//c9
    BuilderMario,
    ShowrunnerMario,
    Phantasm,
};

u16 ColorShift;

void clear_costmic_phantasms(void) {
    struct Object *phantasm;
    phantasm = cur_obj_nearest_object_with_behavior(bhvPhantasm);
    while (phantasm) {
        //kill phantasms until there are no more left
        mark_obj_for_deletion(phantasm);
        phantasm = cur_obj_nearest_object_with_behavior(bhvPhantasm);
    }
}

/**************************************************
 *                    ANIMATIONS                  *
 **************************************************/

/**
 * Checks if Mario's animation has reached its end point.
 */
s32 is_anim_at_end(struct MarioState *m) {
    struct Object *marioObj = m->marioObj;

    return (marioObj->header.gfx.animInfo.animFrame + 1) == marioObj->header.gfx.animInfo.curAnim->loopEnd;
}

/**
 * Checks if Mario's animation has surpassed 2 frames before its end point.
 */
s32 is_anim_past_end(struct MarioState *m) {
    struct Object *marioObj = m->marioObj;

    return marioObj->header.gfx.animInfo.animFrame >= (marioObj->header.gfx.animInfo.curAnim->loopEnd - 2);
}

/**
 * Sets Mario's animation without any acceleration, running at its default rate.
 */
s16 set_mario_animation(struct MarioState *m, s32 targetAnimID) {
    struct Object *marioObj = m->marioObj;
    struct Animation *targetAnim = m->animList->bufTarget;

    if (load_patchable_table(m->animList, targetAnimID)) {
        targetAnim->values = (void *) VIRTUAL_TO_PHYSICAL((u8 *) targetAnim + (uintptr_t) targetAnim->values);
        targetAnim->index  = (void *) VIRTUAL_TO_PHYSICAL((u8 *) targetAnim + (uintptr_t) targetAnim->index);
    }

    if (marioObj->header.gfx.animInfo.animID != targetAnimID) {
        marioObj->header.gfx.animInfo.animID = targetAnimID;
        marioObj->header.gfx.animInfo.curAnim = targetAnim;
        marioObj->header.gfx.animInfo.animAccel = 0;
        marioObj->header.gfx.animInfo.animYTrans = m->animYTrans;

        if (targetAnim->flags & ANIM_FLAG_NO_ACCEL) {
            marioObj->header.gfx.animInfo.animFrame = targetAnim->startFrame;
        } else {
            if (targetAnim->flags & ANIM_FLAG_FORWARD) {
                marioObj->header.gfx.animInfo.animFrame = targetAnim->startFrame + 1;
            } else {
                marioObj->header.gfx.animInfo.animFrame = targetAnim->startFrame - 1;
            }
        }
    }

    return marioObj->header.gfx.animInfo.animFrame;
}

/**
 * Sets Mario's animation where the animation is sped up or
 * slowed down via acceleration.
 */
s16 set_mario_anim_with_accel(struct MarioState *m, s32 targetAnimID, s32 accel) {
    struct Object *marioObj = m->marioObj;
    struct Animation *targetAnim = m->animList->bufTarget;

    if (load_patchable_table(m->animList, targetAnimID)) {
        targetAnim->values = (void *) VIRTUAL_TO_PHYSICAL((u8 *) targetAnim + (uintptr_t) targetAnim->values);
        targetAnim->index = (void *) VIRTUAL_TO_PHYSICAL((u8 *) targetAnim + (uintptr_t) targetAnim->index);
    }

    if (marioObj->header.gfx.animInfo.animID != targetAnimID) {
        marioObj->header.gfx.animInfo.animID = targetAnimID;
        marioObj->header.gfx.animInfo.curAnim = targetAnim;
        marioObj->header.gfx.animInfo.animYTrans = m->animYTrans;

        if (targetAnim->flags & ANIM_FLAG_NO_ACCEL) {
            marioObj->header.gfx.animInfo.animFrameAccelAssist = (targetAnim->startFrame << 0x10);
        } else {
            if (targetAnim->flags & ANIM_FLAG_FORWARD) {
                marioObj->header.gfx.animInfo.animFrameAccelAssist = (targetAnim->startFrame << 0x10) + accel;
            } else {
                marioObj->header.gfx.animInfo.animFrameAccelAssist = (targetAnim->startFrame << 0x10) - accel;
            }
        }

        marioObj->header.gfx.animInfo.animFrame = (marioObj->header.gfx.animInfo.animFrameAccelAssist >> 0x10);
    }

    marioObj->header.gfx.animInfo.animAccel = accel;

    return marioObj->header.gfx.animInfo.animFrame;
}

/**
 * Sets the animation to a specific "next" frame from the frame given.
 */
void set_anim_to_frame(struct MarioState *m, s16 animFrame) {
    struct AnimInfo *animInfo = &m->marioObj->header.gfx.animInfo;
    struct Animation *curAnim = animInfo->curAnim;

    if (animInfo->animAccel) {
        if (curAnim->flags & ANIM_FLAG_FORWARD) {
            animInfo->animFrameAccelAssist = (animFrame << 0x10) + animInfo->animAccel;
        } else {
            animInfo->animFrameAccelAssist = (animFrame << 0x10) - animInfo->animAccel;
        }
    } else {
        if (curAnim->flags & ANIM_FLAG_FORWARD) {
            animInfo->animFrame = animFrame + 1;
        } else {
            animInfo->animFrame = animFrame - 1;
        }
    }
}

s32 is_anim_past_frame(struct MarioState *m, s16 animFrame) {
    s32 isPastFrame;
    s32 acceleratedFrame = animFrame << 0x10;
    struct AnimInfo *animInfo = &m->marioObj->header.gfx.animInfo;
    struct Animation *curAnim = animInfo->curAnim;

    if (animInfo->animAccel) {
        if (curAnim->flags & ANIM_FLAG_FORWARD) {
            isPastFrame =
                (animInfo->animFrameAccelAssist > acceleratedFrame)
                && (acceleratedFrame >= (animInfo->animFrameAccelAssist - animInfo->animAccel));
        } else {
            isPastFrame =
                (animInfo->animFrameAccelAssist < acceleratedFrame)
                && (acceleratedFrame <= (animInfo->animFrameAccelAssist + animInfo->animAccel));
        }
    } else {
        if (curAnim->flags & ANIM_FLAG_FORWARD) {
            isPastFrame = (animInfo->animFrame == (animFrame + 1));
        } else {
            isPastFrame = ((animInfo->animFrame + 1) == animFrame);
        }
    }

    return isPastFrame;
}

/**
 * Rotates the animation's translation into the global coordinate system
 * and returns the animation's flags.
 */
s16 find_mario_anim_flags_and_translation(struct Object *obj, s32 yaw, Vec3s translation) {
    f32 dx, dz;

    struct Animation *curAnim = (void *) obj->header.gfx.animInfo.curAnim;
    s16 animFrame = geo_update_animation_frame(&obj->header.gfx.animInfo, NULL);
    u16 *animIndex = segmented_to_virtual((void *) curAnim->index);
    s16 *animValues = segmented_to_virtual((void *) curAnim->values);

    f32 s = (f32) sins(yaw);
    f32 c = (f32) coss(yaw);

    dx = *(animValues + (retrieve_animation_index(animFrame, &animIndex))) / 4.0f;
    translation[1] = *(animValues + (retrieve_animation_index(animFrame, &animIndex))) / 4.0f;
    dz = *(animValues + (retrieve_animation_index(animFrame, &animIndex))) / 4.0f;

    translation[0] = ( dx * c) + (dz * s);
    translation[2] = (-dx * s) + (dz * c);

    return curAnim->flags;
}

/**
 * Updates Mario's position from his animation's translation.
 */
void update_mario_pos_for_anim(struct MarioState *m) {
    Vec3s translation;
    s16 flags;

    flags = find_mario_anim_flags_and_translation(m->marioObj, m->faceAngle[1], translation);

    if (flags & (ANIM_FLAG_HOR_TRANS | ANIM_FLAG_NO_TRANS)) {
        m->pos[0] += (f32) translation[0];
        m->pos[2] += (f32) translation[2];
    }

    if (flags & (ANIM_FLAG_VERT_TRANS | ANIM_FLAG_NO_TRANS)) {
        m->pos[1] += (f32) translation[1];
    }
}

/**
 * Finds the vertical translation from Mario's animation.
 */
s16 return_mario_anim_y_translation(struct MarioState *m) {
    Vec3s translation;
    find_mario_anim_flags_and_translation(m->marioObj, 0, translation);

    return translation[1];
}

/**************************************************
 *                      AUDIO                     *
 **************************************************/

/**
 * Plays a sound if if Mario doesn't have the flag being checked.
 */
void play_sound_if_no_flag(struct MarioState *m, u32 soundBits, u32 flags) {
    if (!(m->flags & flags)) {
        play_sound(soundBits, m->marioObj->header.gfx.cameraToObject);
        m->flags |= flags;
    }
}

/**
 * Plays a jump sound if one has not been played since the last action change.
 */
void play_mario_jump_sound(struct MarioState *m) {
    if (!(m->flags & MARIO_MARIO_SOUND_PLAYED)) {
        if (m->action == ACT_TRIPLE_JUMP) {
            play_sound(SOUND_MARIO_YAHOO_WAHA_YIPPEE + ((gAudioRandom % 5) << 16),
                       m->marioObj->header.gfx.cameraToObject);
        } else {
            play_sound(SOUND_MARIO_YAH_WAH_HOO + ((gAudioRandom % 3) << 16),
                       m->marioObj->header.gfx.cameraToObject);
        }
        m->flags |= MARIO_MARIO_SOUND_PLAYED;
    }
}

/**
 * Adjusts the volume/pitch of sounds from Mario's speed.
 */
void adjust_sound_for_speed(struct MarioState *m) {
    s32 absForwardVel = (m->forwardVel > 0.0f) ? m->forwardVel : -m->forwardVel;
    set_sound_moving_speed(SOUND_BANK_MOVING, (absForwardVel > 100) ? 100 : absForwardVel);
}

/**
 * Spawns particles if the step sound says to, then either plays a step sound or relevant other sound.
 */
void play_sound_and_spawn_particles(struct MarioState *m, u32 soundBits, u32 waveParticleType) {
    if (m->terrainSoundAddend == (SOUND_TERRAIN_WATER << 16)) {
        if (waveParticleType != 0) {
            m->particleFlags |= PARTICLE_SHALLOW_WATER_SPLASH;
        } else {
            m->particleFlags |= PARTICLE_SHALLOW_WATER_WAVE;
        }
    } else {
        if (m->terrainSoundAddend == (SOUND_TERRAIN_SAND << 16)) {
            m->particleFlags |= PARTICLE_DIRT;
        } else if (m->terrainSoundAddend == (SOUND_TERRAIN_SNOW << 16)) {
            m->particleFlags |= PARTICLE_SNOW;
        }
    }

    if ((m->flags & METAL_SOUND_FLAG) || soundBits == SOUND_ACTION_UNSTUCK_FROM_GROUND
        || soundBits == SOUND_MARIO_PUNCH_HOO) {
        play_sound(soundBits, m->marioObj->header.gfx.cameraToObject);
    } else {
        play_sound(m->terrainSoundAddend + soundBits, m->marioObj->header.gfx.cameraToObject);
    }
}

/**
 * Plays an environmental sound if one has not been played since the last action change.
 */
void play_mario_action_sound(struct MarioState *m, u32 soundBits, u32 waveParticleType) {
    if (!(m->flags & MARIO_ACTION_SOUND_PLAYED)) {
        play_sound_and_spawn_particles(m, soundBits, waveParticleType);
        m->flags |= MARIO_ACTION_SOUND_PLAYED;
    }
}

/**
 * Plays a landing sound, accounting for metal cap.
 */
void play_mario_landing_sound(struct MarioState *m, u32 soundBits) {
    play_sound_and_spawn_particles(
        m, (m->flags & METAL_SOUND_FLAG) ? SOUND_ACTION_METAL_LANDING : soundBits, 1);
}

/**
 * Plays a landing sound, accounting for metal cap. Unlike play_mario_landing_sound,
 * this function uses play_mario_action_sound, making sure the sound is only
 * played once per action.
 */
void play_mario_landing_sound_once(struct MarioState *m, u32 soundBits) {
    play_mario_action_sound(
        m, (m->flags & METAL_SOUND_FLAG) ? SOUND_ACTION_METAL_LANDING : soundBits, 1);
}

/**
 * Plays a heavy landing (ground pound, etc.) sound, accounting for metal cap.
 */
void play_mario_heavy_landing_sound(struct MarioState *m, u32 soundBits) {
    play_sound_and_spawn_particles(
        m, (m->flags & METAL_SOUND_FLAG) ? SOUND_ACTION_METAL_HEAVY_LANDING : soundBits, 1);
}

/**
 * Plays a heavy landing (ground pound, etc.) sound, accounting for metal cap.
 * Unlike play_mario_heavy_landing_sound, this function uses play_mario_action_sound,
 * making sure the sound is only played once per action.
 */
void play_mario_heavy_landing_sound_once(struct MarioState *m, u32 soundBits) {
    play_mario_action_sound(
        m, (m->flags & METAL_SOUND_FLAG) ? SOUND_ACTION_METAL_HEAVY_LANDING : soundBits, 1);
}

/**
 * Plays action and Mario sounds relevant to what was passed into the function.
 */
void play_mario_sound(struct MarioState *m, s32 actionSound, s32 marioSound) {
    if (actionSound == SOUND_ACTION_TERRAIN_JUMP) {
        play_mario_action_sound(m, (m->flags & METAL_SOUND_FLAG) ? (s32) SOUND_ACTION_METAL_JUMP
                                                                : (s32) SOUND_ACTION_TERRAIN_JUMP, 1);
    } else {
        play_sound_if_no_flag(m, actionSound, MARIO_ACTION_SOUND_PLAYED);
    }

    if (marioSound == 0) {
        play_mario_jump_sound(m);
    }

    if (marioSound != -1) {
        play_sound_if_no_flag(m, marioSound, MARIO_MARIO_SOUND_PLAYED);
    }
}

/**************************************************
 *                     ACTIONS                    *
 **************************************************/

/**
 * Sets Mario's other velocities from his forward speed.
 */
void mario_set_forward_vel(struct MarioState *m, f32 forwardVel) {
    m->forwardVel = forwardVel;

    m->slideVelX = sins(m->faceAngle[1]) * m->forwardVel;
    m->slideVelZ = coss(m->faceAngle[1]) * m->forwardVel;

    m->vel[0] = (f32) m->slideVelX;
    m->vel[2] = (f32) m->slideVelZ;
}

/**
 * Returns the slipperiness class of Mario's floor.
 */
s32 mario_get_floor_class(struct MarioState *m) {
    s32 floorClass;

    // The slide terrain type defaults to slide slipperiness.
    // This doesn't matter too much since normally the slide terrain
    // is checked for anyways.
    if ((m->area->terrainType & TERRAIN_MASK) == TERRAIN_SLIDE) {
        floorClass = SURFACE_CLASS_VERY_SLIPPERY;
    } else {
        floorClass = SURFACE_CLASS_DEFAULT;
    }

    if (m->floor != NULL) {
        switch (m->floor->type) {
            case SURFACE_NOT_SLIPPERY:
            case SURFACE_HARD_NOT_SLIPPERY:
            case SURFACE_SWITCH:
            case SURFACE_GRASS:
            case SURFACE_SAND:
            case SURFACE_CREAKWOOD:
            case SURFACE_DEEP_QUICKSAND:
            case SURFACE_VANISH_CAP_WALLS:
                floorClass = SURFACE_CLASS_NOT_SLIPPERY;
                break;

            case SURFACE_SLIPPERY:
            case SURFACE_NOISE_SLIPPERY:
            case SURFACE_HARD_SLIPPERY:
            case SURFACE_NO_CAM_COL_SLIPPERY:
                floorClass = SURFACE_CLASS_SLIPPERY;
                break;

            case SURFACE_VERY_SLIPPERY:
            case SURFACE_ICE:
            case SURFACE_HARD_VERY_SLIPPERY:
            case SURFACE_NOISE_VERY_SLIPPERY_73:
            case SURFACE_NOISE_VERY_SLIPPERY_74:
            case SURFACE_NOISE_VERY_SLIPPERY:
            case SURFACE_NO_CAM_COL_VERY_SLIPPERY:
            case SURFACE_SNOW:
                floorClass = SURFACE_CLASS_VERY_SLIPPERY;
                break;
        }
    }

    // Crawling allows Mario to not slide on certain steeper surfaces.
    if (m->action == ACT_CRAWLING && m->floorNormal[1] > 0.5f && floorClass == SURFACE_CLASS_DEFAULT) {
        floorClass = SURFACE_CLASS_NOT_SLIPPERY;
    }

    return floorClass;
}

// clang-format off
s8 sTerrainSounds[7][6] = {
    // default,              hard,                 slippery,
    // very slippery,        noisy default,        noisy slippery
    { SOUND_TERRAIN_DEFAULT, SOUND_TERRAIN_STONE,  SOUND_TERRAIN_GRASS,
      SOUND_TERRAIN_GRASS,   SOUND_TERRAIN_GRASS,  SOUND_TERRAIN_DEFAULT }, // TERRAIN_GRASS
    { SOUND_TERRAIN_STONE,   SOUND_TERRAIN_STONE,  SOUND_TERRAIN_STONE,
      SOUND_TERRAIN_STONE,   SOUND_TERRAIN_GRASS,  SOUND_TERRAIN_GRASS }, // TERRAIN_STONE
    { SOUND_TERRAIN_SNOW,    SOUND_TERRAIN_ICE,    SOUND_TERRAIN_SNOW,
      SOUND_TERRAIN_ICE,     SOUND_TERRAIN_STONE,  SOUND_TERRAIN_STONE }, // TERRAIN_SNOW
    { SOUND_TERRAIN_SAND,    SOUND_TERRAIN_STONE,  SOUND_TERRAIN_SAND,
      SOUND_TERRAIN_SAND,    SOUND_TERRAIN_STONE,  SOUND_TERRAIN_STONE }, // TERRAIN_SAND
    { SOUND_TERRAIN_SPOOKY,  SOUND_TERRAIN_SPOOKY, SOUND_TERRAIN_SPOOKY,
      SOUND_TERRAIN_SPOOKY,  SOUND_TERRAIN_STONE,  SOUND_TERRAIN_STONE }, // TERRAIN_SPOOKY
    { SOUND_TERRAIN_DEFAULT, SOUND_TERRAIN_STONE,  SOUND_TERRAIN_GRASS,
      SOUND_TERRAIN_ICE,     SOUND_TERRAIN_STONE,  SOUND_TERRAIN_ICE }, // TERRAIN_WATER
    { SOUND_TERRAIN_STONE,   SOUND_TERRAIN_STONE,  SOUND_TERRAIN_STONE,
      SOUND_TERRAIN_STONE,   SOUND_TERRAIN_ICE,    SOUND_TERRAIN_ICE }, // TERRAIN_SLIDE
};
// clang-format on

/**
 * Computes a value that should be added to terrain sounds before playing them.
 * This depends on surfaces and terrain.
 */
u32 mario_get_terrain_sound_addend(struct MarioState *m) {
    s16 floorSoundType;
    s16 terrainType = m->area->terrainType & TERRAIN_MASK;
    s32 ret = SOUND_TERRAIN_DEFAULT << 16;
    s32 floorType;
    u8 setret = FALSE;

    if (m->floor != NULL) {
        floorType = m->floor->type;

        if ((gCurrLevelNum != LEVEL_LLL) && (m->floorHeight < (m->waterLevel - 10))) {
            // Water terrain sound, excluding LLL since it uses water in the volcano.
            ret = SOUND_TERRAIN_WATER << 16;
        } else if (SURFACE_IS_QUICKSAND(floorType)) {
            ret = SOUND_TERRAIN_SAND << 16;
        } else {
            switch (floorType) {
                default:
                    floorSoundType = 0;
                    break;

                case SURFACE_NOT_SLIPPERY:
                case SURFACE_HARD:
                case SURFACE_HARD_NOT_SLIPPERY:
                case SURFACE_SWITCH:
                    floorSoundType = 1;
                    break;

                case SURFACE_SLIPPERY:
                case SURFACE_HARD_SLIPPERY:
                case SURFACE_NO_CAM_COL_SLIPPERY:
                    floorSoundType = 2;
                    break;

                case SURFACE_VERY_SLIPPERY:
                case SURFACE_ICE:
                case SURFACE_HARD_VERY_SLIPPERY:
                case SURFACE_NOISE_VERY_SLIPPERY_73:
                case SURFACE_NOISE_VERY_SLIPPERY_74:
                case SURFACE_NOISE_VERY_SLIPPERY:
                case SURFACE_NO_CAM_COL_VERY_SLIPPERY:
                    floorSoundType = 3;
                    break;

                case SURFACE_NOISE_DEFAULT:
                    floorSoundType = 4;
                    break;

                case SURFACE_NOISE_SLIPPERY:
                    floorSoundType = 5;
                    break;

                case SURFACE_GRASS:
                    floorSoundType = 4;
                    terrainType = TERRAIN_GRASS & TERRAIN_MASK;
                    break;
                case SURFACE_SAND:
                    setret = TRUE;
                    ret = SOUND_TERRAIN_SAND << 16;
                    break;
                case SURFACE_SNOW:
                    setret = TRUE;
                    ret = SOUND_TERRAIN_SNOW << 16;
                break;
                case SURFACE_CREAKWOOD:
                    setret = TRUE;
                    ret = SOUND_TERRAIN_SPOOKY << 16;
                break;
            }

            if (!setret) {
                ret = sTerrainSounds[terrainType][floorSoundType] << 16;
            }
        }
    }

    return ret;
}

/**
 * Determines if Mario is facing "downhill."
 */
s32 mario_facing_downhill(struct MarioState *m, s32 turnYaw) {
    s16 faceAngleYaw = m->faceAngle[1];

    // This is never used in practice, as turnYaw is
    // always passed as zero.
    if (turnYaw && m->forwardVel < 0.0f) {
        faceAngleYaw += 0x8000;
    }

    faceAngleYaw = m->floorYaw - faceAngleYaw;

    return (-0x4000 < faceAngleYaw) && (faceAngleYaw < 0x4000);
}

/**
 * Determines if a surface is slippery based on the surface class.
 */
u32 mario_floor_is_slippery(struct MarioState *m) {
    f32 normY;

    if ((m->area->terrainType & TERRAIN_MASK) == TERRAIN_SLIDE  && m->floorNormal[1] < COS1) {
        return TRUE;
    }

    switch (mario_get_floor_class(m)) {
        case SURFACE_CLASS_VERY_SLIPPERY: normY = COS10; break;
        case SURFACE_CLASS_SLIPPERY:      normY = COS20; break;
        default:                          normY = COS38; break;
        case SURFACE_CLASS_NOT_SLIPPERY:  normY = 0.0f;  break;
    }

    return m->floorNormal[1] <= normY;
}

/**
 * Determines if a surface is a slope based on the surface class.
 */
s32 mario_floor_is_slope(struct MarioState *m) {
    f32 normY;

    if ((m->area->terrainType & TERRAIN_MASK) == TERRAIN_SLIDE
        && m->floorNormal[1] < COS1) {
        return TRUE;
    }

    switch (mario_get_floor_class(m)) {
        case SURFACE_CLASS_VERY_SLIPPERY: normY = COS5;  break;
        case SURFACE_CLASS_SLIPPERY:      normY = COS10; break;
        default:                          normY = COS15; break;
        case SURFACE_CLASS_NOT_SLIPPERY:  normY = COS20; break;
    }

    return m->floorNormal[1] <= normY;
}

/**
 * Determines if a surface is steep based on the surface class.
 */
s32 mario_floor_is_steep(struct MarioState *m) {
    f32 normY;

#ifdef JUMP_KICK_FIX
    if (mario_get_floor_class(m) == SURFACE_CLASS_NOT_SLIPPERY) {
        return FALSE;
    }
#endif

    // Interestingly, this function does not check for the
    // slide terrain type. This means that steep behavior persists for
    // non-slippery and slippery surfaces.
    // This does not matter in vanilla game practice.
    if (!mario_facing_downhill(m, FALSE)) {
        switch (mario_get_floor_class(m)) {
            case SURFACE_CLASS_VERY_SLIPPERY: normY = COS15; break;
            case SURFACE_CLASS_SLIPPERY:      normY = COS20; break;
            default:                          normY = COS30; break;
            case SURFACE_CLASS_NOT_SLIPPERY:  normY = COS30; break;
        }

        return m->floorNormal[1] <= normY;
    }

    return FALSE;
}

/**
 * Finds the floor height relative from Mario given polar displacement.
 */
f32 find_floor_height_relative_polar(struct MarioState *m, s16 angleFromMario, f32 distFromMario) {
    struct Surface *floor;

    f32 y = sins(m->faceAngle[1] + angleFromMario) * distFromMario;
    f32 x = coss(m->faceAngle[1] + angleFromMario) * distFromMario;

    return find_floor(m->pos[0] + y, m->pos[1] + 100.0f, m->pos[2] + x, &floor);
}

extern f32 get_floor_height_at_location(s32, s32, struct Surface *);

/**
 * Returns the slope of the floor based off points around Mario.
 */
s16 find_floor_slope(struct MarioState *m, s16 yawOffset) {
    struct Surface *floor = m->floor;
    f32 forwardFloorY, backwardFloorY;
    f32 forwardYDelta, backwardYDelta;
    s16 result;

    f32 x = sins(m->faceAngle[1] + yawOffset) * 5.0f;
    f32 z = coss(m->faceAngle[1] + yawOffset) * 5.0f;
#ifdef FAST_FLOOR_ALIGN
    if (absf(m->forwardVel) > FAST_FLOOR_ALIGN) {
        forwardFloorY  = get_floor_height_at_location(m->pos[0] + x, m->pos[2] + z, floor);
        backwardFloorY = get_floor_height_at_location(m->pos[0] - x, m->pos[2] - z, floor);
    } else {
        forwardFloorY  = find_floor(m->pos[0] + x, m->pos[1] + 100.0f, m->pos[2] + z, &floor);
        if (floor == NULL)  forwardFloorY = m->floorHeight; // handle OOB slopes
        backwardFloorY = find_floor(m->pos[0] - x, m->pos[1] + 100.0f, m->pos[2] - z, &floor);
        if (floor == NULL) backwardFloorY = m->floorHeight; // handle OOB slopes
    }
#else
    forwardFloorY  = find_floor(m->pos[0] + x, m->pos[1] + 100.0f, m->pos[2] + z, &floor);
    if (floor == NULL)  forwardFloorY = m->floorHeight; // handle OOB slopes
    backwardFloorY = find_floor(m->pos[0] - x, m->pos[1] + 100.0f, m->pos[2] - z, &floor);
    if (floor == NULL) backwardFloorY = m->floorHeight; // handle OOB slopes
#endif

    forwardYDelta = forwardFloorY - m->pos[1];
    backwardYDelta = m->pos[1] - backwardFloorY;

    if (sqr(forwardYDelta) < sqr(backwardYDelta)) {
        result = atan2s(5.0f, forwardYDelta);
    } else {
        result = atan2s(5.0f, backwardYDelta);
    }

    return result;
}

Bool32 set_mario_wall(struct MarioState *m, struct Surface *wall) {
    if (m->wall != wall) {
        m->wall = wall;
        if (m->wall != NULL) m->wallYaw = SURFACE_YAW(wall);
    }
    return (m->wall != NULL);
}

Bool32 set_mario_ceil(struct MarioState *m, struct Surface *ceil, f32 ceilHeight) {
    if (m->ceil != ceil) {
        m->ceil = ceil;
        if (m->ceil != NULL) m->ceilYaw = SURFACE_YAW(ceil);
    }
    m->ceilHeight = ceilHeight;
    return (m->ceil != NULL);
}

Bool32 set_mario_floor(struct MarioState *m, struct Surface *floor, f32 floorHeight) {
    if (m->floor != floor) {
        m->floor = floor;
        if (m->floor != NULL) m->floorYaw = SURFACE_YAW(floor);
    }
    get_surface_normal(m->floorNormal, floor);
    m->floorHeight = floorHeight;
    return (m->floor != NULL);
}

/**
 * Adjusts Mario's camera and sound based on his action status.
 */
void update_mario_sound_and_camera(struct MarioState *m) {
    u32 action = m->action;
    s32 camPreset = m->area->camera->mode;

    if (action == ACT_FIRST_PERSON) {
        raise_background_noise(2);
        gCameraMovementFlags &= ~CAM_MOVE_C_UP_MODE;
        // Go back to the last camera mode
        set_camera_mode(m->area->camera, -1, 1);
    } else if (action == ACT_SLEEPING) {
        raise_background_noise(2);
    }

    if (!(action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER)) && (camPreset == DEEP_WATER_CAMERA_MODE || camPreset == WATER_SURFACE_CAMERA_MODE)) {
        set_camera_mode(m->area->camera, m->area->camera->defMode, 1);
    }
}

/**
 * Transitions Mario to a steep jump action.
 */
void set_steep_jump_action(struct MarioState *m) {
    m->marioObj->oMarioSteepJumpYaw = m->faceAngle[1];

    if (m->forwardVel > 0.0f) {
        //! ((s16)0x8000) has undefined behavior. Therefore, this downcast has
        // undefined behavior if m->floorYaw >= 0.
        s16 angleTemp = m->floorYaw + 0x8000;
        s16 faceAngleTemp = m->faceAngle[1] - angleTemp;

        f32 y = sins(faceAngleTemp) * m->forwardVel;
        f32 x = coss(faceAngleTemp) * m->forwardVel * 0.75f;

        m->forwardVel = sqrtf(sqr(y) + sqr(x));
        m->faceAngle[1] = atan2s(x, y) + angleTemp;
    }

    drop_and_set_mario_action(m, ACT_STEEP_JUMP, 0);
}

/**
 * Sets Mario's vertical speed from his forward speed.
 */
void set_mario_y_vel_based_on_fspeed(struct MarioState *m, f32 initialVelY, f32 multiplier) {
    // get_additive_y_vel_for_jumps is always 0 and a stubbed function.
    // It was likely trampoline related based on code location.
    m->vel[1] = initialVelY + get_additive_y_vel_for_jumps() + m->forwardVel * multiplier;

    //if (m->marioObj->platform != NULL && m->marioObj->platform->oVelY > 0.0f)
    //{
        //m->vel[1] += m->marioObj->platform->oVelY;
        //m->pos[1] += m->marioObj->platform->oVelY;
    //}

    if (m->squishTimer != 0 || m->quicksandDepth > 1.0f) {
        m->vel[1] *= 0.5f;
    }
}

/**
 * Transitions for a variety of airborne actions.
 */
u32 set_mario_action_airborne(struct MarioState *m, u32 action, u32 actionArg) {
    f32 forwardVel;

    if ((m->squishTimer != 0 || m->quicksandDepth >= 1.0f)
        && (action == ACT_DOUBLE_JUMP || action == ACT_TWIRLING)) {
        action = ACT_JUMP;
    }

    switch (action) {
        case ACT_DOUBLE_JUMP:
            set_mario_y_vel_based_on_fspeed(m, 52.0f, 0.25f);
            m->forwardVel *= 0.8f;
            break;

        case ACT_BACKFLIP:
            m->marioObj->header.gfx.animInfo.animID = -1;
            m->forwardVel = -16.0f;
            set_mario_y_vel_based_on_fspeed(m, 62.0f, 0.0f);
            break;

        case ACT_TRIPLE_JUMP:
            set_mario_y_vel_based_on_fspeed(m, 69.0f, 0.0f);
            m->forwardVel *= 0.8f;
            break;

        case ACT_FLYING_TRIPLE_JUMP:
            set_mario_y_vel_based_on_fspeed(m, 82.0f, 0.0f);
            break;

        case ACT_WATER_JUMP:
        case ACT_HOLD_WATER_JUMP:
            if (actionArg == 0) {
                set_mario_y_vel_based_on_fspeed(m, 42.0f, 0.0f);
            }
            break;

        case ACT_BURNING_JUMP:
            m->vel[1] = 31.5f;
            m->forwardVel = 8.0f;
            break;

        case ACT_RIDING_SHELL_JUMP:
            set_mario_y_vel_based_on_fspeed(m, 42.0f, 0.25f);
            break;

        case ACT_JUMP:
        case ACT_HOLD_JUMP:
            m->marioObj->header.gfx.animInfo.animID = -1;
            set_mario_y_vel_based_on_fspeed(m, 42.0f, 0.25f);
            m->forwardVel *= 0.8f;
            break;

        case ACT_WALL_KICK_AIR:
        case ACT_TOP_OF_POLE_JUMP:
            set_mario_y_vel_based_on_fspeed(m, 62.0f, 0.0f);
            if (m->forwardVel < 24.0f) {
                m->forwardVel = 24.0f;
            }
            m->wallKickTimer = 0;
            break;

        case ACT_SIDE_FLIP:
            set_mario_y_vel_based_on_fspeed(m, 62.0f, 0.0f);
            m->forwardVel = 8.0f;
            m->faceAngle[1] = m->intendedYaw;
            break;

        case ACT_STEEP_JUMP:
            m->marioObj->header.gfx.animInfo.animID = -1;
            set_mario_y_vel_based_on_fspeed(m, 42.0f, 0.25f);
            m->faceAngle[0] = -0x2000;
            break;

        case ACT_LAVA_BOOST:
            m->vel[1] = 84.0f;
            if (actionArg == 0) {
                m->forwardVel = 0.0f;
            }
            break;

        case ACT_DIVE:
            if ((forwardVel = m->forwardVel + 15.0f) > 48.0f) {
                forwardVel = 48.0f;
            }
            mario_set_forward_vel(m, forwardVel);
            break;

        case ACT_LONG_JUMP:
            m->marioObj->header.gfx.animInfo.animID = -1;
            set_mario_y_vel_based_on_fspeed(m, 30.0f, 0.0f);
            m->marioObj->oMarioLongJumpIsSlow = m->forwardVel > 16.0f ? FALSE : TRUE;

            //! (BLJ's) This properly handles long jumps from getting forward speed with
            //  too much velocity, but misses backwards longs allowing high negative speeds.
            if ((m->forwardVel *= 1.5f) > 48.0f) {
                m->forwardVel = 48.0f;
            }
            break;

        case ACT_SLIDE_KICK:
            m->vel[1] = 12.0f;
            if (m->forwardVel < 32.0f) {
                m->forwardVel = 32.0f;
            }
            break;

        case ACT_JUMP_KICK:
            m->vel[1] = 20.0f;
            break;
    }

    m->peakHeight = m->pos[1];
    m->flags |= MARIO_JUMPING;

    return action;
}

/**
 * Transitions for a variety of moving actions.
 */
u32 set_mario_action_moving(struct MarioState *m, u32 action, UNUSED u32 actionArg) {
    s16 floorClass = mario_get_floor_class(m);
    f32 forwardVel = m->forwardVel;
    f32 mag = MIN(m->intendedMag, 8.0f);

    switch (action) {
        case ACT_WALKING:
            if (floorClass != SURFACE_CLASS_VERY_SLIPPERY) {
                if (0.0f <= forwardVel && forwardVel < mag) {
                    m->forwardVel = mag;
                }
            }

            m->marioObj->oMarioWalkingPitch = 0;
            break;

        case ACT_HOLD_WALKING:
            if (0.0f <= forwardVel && forwardVel < mag / 2.0f) {
                m->forwardVel = mag / 2.0f;
            }
            break;

        case ACT_BEGIN_SLIDING:
            if (mario_facing_downhill(m, FALSE)) {
                action = ACT_BUTT_SLIDE;
            } else {
                action = ACT_STOMACH_SLIDE;
            }
            break;

        case ACT_HOLD_BEGIN_SLIDING:
            if (mario_facing_downhill(m, FALSE)) {
                action = ACT_HOLD_BUTT_SLIDE;
            } else {
                action = ACT_HOLD_STOMACH_SLIDE;
            }
            break;
    }

    return action;
}

/**
 * Transition for certain submerged actions, which is actually just the metal jump actions.
 */
u32 set_mario_action_submerged(struct MarioState *m, u32 action, UNUSED u32 actionArg) {
    if (action == ACT_METAL_WATER_JUMP || action == ACT_HOLD_METAL_WATER_JUMP) {
        m->vel[1] = 32.0f;
    }

    return action;
}

/**
 * Transitions for a variety of cutscene actions.
 */
u32 set_mario_action_cutscene(struct MarioState *m, u32 action, UNUSED u32 actionArg) {
    switch (action) {
        case ACT_EMERGE_FROM_PIPE:
            m->vel[1] = 52.0f;
            break;

        case ACT_FALL_AFTER_STAR_GRAB:
            mario_set_forward_vel(m, 0.0f);
            break;

        case ACT_SPAWN_SPIN_AIRBORNE:
            mario_set_forward_vel(m, 2.0f);
            break;

        case ACT_SPECIAL_EXIT_AIRBORNE:
        case ACT_SPECIAL_DEATH_EXIT:
            m->vel[1] = 64.0f;
            break;
    }

    return action;
}

/**
 * Puts Mario into a given action, putting Mario through the appropriate
 * specific function if needed.
 */
u32 set_mario_action(struct MarioState *m, u32 action, u32 actionArg) {
    switch (action & ACT_GROUP_MASK) {
        case ACT_GROUP_MOVING:    action = set_mario_action_moving(   m, action, actionArg); break;
        case ACT_GROUP_AIRBORNE:  action = set_mario_action_airborne( m, action, actionArg); break;
        case ACT_GROUP_SUBMERGED: action = set_mario_action_submerged(m, action, actionArg); break;
        case ACT_GROUP_CUTSCENE:  action = set_mario_action_cutscene( m, action, actionArg); break;
    }

    // Resets the sound played flags, meaning Mario can play those sound types again.
    m->flags &= ~(MARIO_ACTION_SOUND_PLAYED | MARIO_MARIO_SOUND_PLAYED);

    if (!(m->action & ACT_FLAG_AIR)) {
        m->flags &= ~MARIO_FALL_SOUND_PLAYED;
    }

    // Initialize the action information.
    m->prevAction = m->action;
    m->action = action;
    m->actionArg = actionArg;
    m->actionState = 0;
    m->actionTimer = 0;

    return TRUE;
}

/**
 * Puts Mario into a specific jumping action from a landing action.
 */
s32 set_jump_from_landing(struct MarioState *m) {
    if (m->quicksandDepth >= 11.0f) {
        if (m->heldObj == NULL) {
            return set_mario_action(m, ACT_QUICKSAND_JUMP_LAND, 0);
        } else {
            return set_mario_action(m, ACT_HOLD_QUICKSAND_JUMP_LAND, 0);
        }
    }

    if (mario_floor_is_steep(m)) {
        set_steep_jump_action(m);
    } else {
        if ((m->doubleJumpTimer == 0) || (m->squishTimer != 0)) {
            set_mario_action(m, ACT_JUMP, 0);
        } else {
            switch (m->prevAction) {
                case ACT_JUMP_LAND:
                    set_mario_action(m, ACT_DOUBLE_JUMP, 0);
                    break;

                case ACT_FREEFALL_LAND:
                    set_mario_action(m, ACT_DOUBLE_JUMP, 0);
                    break;

                case ACT_SIDE_FLIP_LAND_STOP:
                    set_mario_action(m, ACT_DOUBLE_JUMP, 0);
                    break;

                case ACT_DOUBLE_JUMP_LAND:
                    // If Mario has a wing cap, he ignores the typical speed
                    // requirement for a triple jump.
                    if (m->flags & MARIO_WING_CAP) {
                        set_mario_action(m, ACT_FLYING_TRIPLE_JUMP, 0);
                    } else if (m->forwardVel > 20.0f) {
                        set_mario_action(m, ACT_TRIPLE_JUMP, 0);
                    } else {
                        set_mario_action(m, ACT_JUMP, 0);
                    }
                    break;

                default:
                    set_mario_action(m, ACT_JUMP, 0);
                    break;
            }
        }
    }

    m->doubleJumpTimer = 0;

    return TRUE;
}

/**
 * Puts Mario in a given action, as long as it is not overruled by
 * either a quicksand or steep jump.
 */
s32 set_jumping_action(struct MarioState *m, u32 action, u32 actionArg) {
    if (m->quicksandDepth >= 11.0f) {
        // Checks whether Mario is holding an object or not.
        if (m->heldObj == NULL) {
            return set_mario_action(m, ACT_QUICKSAND_JUMP_LAND, 0);
        } else {
            return set_mario_action(m, ACT_HOLD_QUICKSAND_JUMP_LAND, 0);
        }
    }

    if (mario_floor_is_steep(m)) {
        set_steep_jump_action(m);
    } else {
        set_mario_action(m, action, actionArg);
    }

    return TRUE;
}

/**
 * Drop anything Mario is holding and set a new action.
 */
s32 drop_and_set_mario_action(struct MarioState *m, u32 action, u32 actionArg) {
    mario_stop_riding_and_holding(m);

    return set_mario_action(m, action, actionArg);
}

/**
 * Increment Mario's hurt counter and set a new action.
 */
s32 hurt_and_set_mario_action(struct MarioState *m, u32 action, u32 actionArg, s16 hurtCounter) {
    m->hurtCounter = hurtCounter;

    return set_mario_action(m, action, actionArg);
}

/**
 * Checks a variety of inputs for common transitions between many different
 * actions. A common variant of the below function.
 */
s32 check_common_action_exits(struct MarioState *m) {
    if (m->input & INPUT_A_PRESSED) {
        return set_mario_action(m, ACT_JUMP, 0);
    }
    if (m->input & INPUT_OFF_FLOOR) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }
    if (m->input & INPUT_NONZERO_ANALOG) {
        return set_mario_action(m, ACT_WALKING, 0);
    }
    if (m->input & INPUT_ABOVE_SLIDE) {
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    }

    return FALSE;
}

/**
 * Checks a variety of inputs for common transitions between many different
 * object holding actions. A holding variant of the above function.
 */
s32 check_common_hold_action_exits(struct MarioState *m) {
    if (m->input & INPUT_A_PRESSED     ) return set_mario_action(m, ACT_HOLD_JUMP,          0);
    if (m->input & INPUT_OFF_FLOOR     ) return set_mario_action(m, ACT_HOLD_FREEFALL,      0);
    if (m->input & INPUT_NONZERO_ANALOG) return set_mario_action(m, ACT_HOLD_WALKING,       0);
    if (m->input & INPUT_ABOVE_SLIDE   ) return set_mario_action(m, ACT_HOLD_BEGIN_SLIDING, 0);
    return FALSE;
}

/**
 * Transitions Mario from a submerged action to a walking action.
 */
s32 transition_submerged_to_walking(struct MarioState *m) {
    set_camera_mode(m->area->camera, m->area->camera->defMode, 1);

    vec3_zero(m->angleVel);

    if (m->heldObj == NULL) {
        return set_mario_action(m, ACT_WALKING, 0);
    } else {
        return set_mario_action(m, ACT_HOLD_WALKING, 0);
    }
}

/**
 * Transitions Mario from a submerged action to an airborne action.
 * You may want to change these actions to fit your hack
 */
s32 transition_submerged_to_airborne(struct MarioState *m) {
    set_camera_mode(m->area->camera, m->area->camera->defMode, 1);

    vec3_zero(m->angleVel);

    if (m->heldObj == NULL) {
        if (m->input & INPUT_A_DOWN) return set_mario_action(m, ACT_DIVE, 0);
        else return set_mario_action(m, ACT_FREEFALL, 0);
    } else {
        if (m->input & INPUT_A_DOWN) return set_mario_action(m, ACT_HOLD_JUMP, 0);
        else return set_mario_action(m, ACT_HOLD_FREEFALL, 0);
    }
}

/**
 * This is the transition function typically for entering a submerged action for a
 * non-submerged action. This also applies the water surface camera preset.
 */
s32 set_water_plunge_action(struct MarioState *m) {
    m->forwardVel = m->forwardVel / 4.0f;
    m->vel[1] = m->vel[1] / 2.0f;

#ifdef WATER_PLUNGE_UPWARP
    m->pos[1] = m->waterLevel - 100;
#endif

    m->faceAngle[2] = 0;

    vec3_zero(m->angleVel);

    if (!(m->action & ACT_FLAG_DIVING)) {
        m->faceAngle[0] = 0;
    }

    if (m->area->camera->mode != WATER_SURFACE_CAMERA_MODE) {
        set_camera_mode(m->area->camera, WATER_SURFACE_CAMERA_MODE, 1);
    }

    return set_mario_action(m, ACT_WATER_PLUNGE, 0);
}

/**
 * These are the scaling values for the x and z axis for Mario
 * when he is close to unsquishing.
 */
u8 sSquishScaleOverTime[16] = { 0x46, 0x32, 0x32, 0x3C, 0x46, 0x50, 0x50, 0x3C,
                                0x28, 0x14, 0x14, 0x1E, 0x32, 0x3C, 0x3C, 0x28 };

/**
 * Applies the squish to Mario's model via scaling.
 */
void squish_mario_model(struct MarioState *m) {
    if (m->squishTimer != 0xFF) {
        // If no longer squished, scale back to default.
        if (m->squishTimer == 0) {
            vec3f_set(m->marioObj->header.gfx.scale, 1.0f, 1.0f, 1.0f);
        }
        // If timer is less than 16, rubber-band Mario's size scale up and down.
        else if (m->squishTimer <= 16) {
            m->squishTimer -= 1;

            m->marioObj->header.gfx.scale[1] =
                1.0f - ((sSquishScaleOverTime[15 - m->squishTimer] * 0.6f) / 100.0f);
            m->marioObj->header.gfx.scale[0] =
                ((sSquishScaleOverTime[15 - m->squishTimer] * 0.4f) / 100.0f) + 1.0f;

            m->marioObj->header.gfx.scale[2] = m->marioObj->header.gfx.scale[0];
        } else {
            m->squishTimer -= 1;

            vec3f_set(m->marioObj->header.gfx.scale, 1.4f, 0.4f, 1.4f);
        }
    }
}

#ifdef VANILLA_DEBUG
/**
 * Debug function that prints floor normal, velocity, and action information.
 */
void debug_print_speed_action_normal(struct MarioState *m) {
    f32 steepness;
    f32 floor_nY;

    if (gShowDebugText) {
        steepness = sqrtf(sqr(m->floorNormal[0]) + sqr(m->floorNormal[2]));
        floor_nY = m->floorNormal[1];

        print_text_fmt_int(210, 88, "ANG %d", (atan2s(floor_nY, steepness) * 180.0f) / 32768.0f);

        print_text_fmt_int(210, 72, "SPD %d", m->forwardVel);

        // STA short for "status," the official action name via SMS map.
        print_text_fmt_int(210, 56, "STA %x", (m->action & ACT_ID_MASK));
    }
}
#endif

/**
 * Update the button inputs for Mario.
 */
void update_mario_button_inputs(struct MarioState *m) {
    if (m->controller->buttonPressed & A_BUTTON) m->input |= INPUT_A_PRESSED;
    if (m->controller->buttonDown    & A_BUTTON) m->input |= INPUT_A_DOWN;

    // Don't update for these buttons if squished.
    if (m->squishTimer == 0) {
        if (m->controller->buttonDown    & B_BUTTON) m->input |= INPUT_B_DOWN;
        if (m->controller->buttonPressed & B_BUTTON) m->input |= INPUT_B_PRESSED;
        if (m->controller->buttonDown    & Z_TRIG  ) m->input |= INPUT_Z_DOWN;
        if (m->controller->buttonPressed & Z_TRIG  ) m->input |= INPUT_Z_PRESSED;
    }

    if (m->input & INPUT_A_PRESSED) {
        m->framesSinceA = 0;
    } else if (m->framesSinceA < 0xFF) {
        m->framesSinceA++;
    }

    if (m->input & INPUT_B_PRESSED) {
        m->framesSinceB = 0;
    } else if (m->framesSinceB < 0xFF) {
        m->framesSinceB++;
    }
}

/**
 * Updates the joystick intended magnitude.
 */
void update_mario_joystick_inputs(struct MarioState *m) {
    struct Controller *controller = m->controller;
    f32 mag = ((controller->stickMag / 64.0f) * (controller->stickMag / 64.0f)) * 64.0f;

    if (m->squishTimer == 0) {
        m->intendedMag = mag / 2.0f;
    } else {
        m->intendedMag = mag / 8.0f;
    }

    if (m->intendedMag > 0.0f) {
        m->intendedYaw = atan2s(-controller->stickY, controller->stickX) + m->area->camera->yaw;
        m->input |= INPUT_NONZERO_ANALOG;
    } else {
        m->intendedYaw = m->faceAngle[1];
    }

    if (gMarioState->_2D) {
        if (gPlayer1Controller->rawStickX > 0.0f) {
            m->intendedYaw = 0x4000;
        }
        if (gPlayer1Controller->rawStickX < 0.0f) {
            m->intendedYaw = -0x4000;
        }
    }
}

/**
 * Resolves wall collisions, and updates a variety of inputs.
 */
void update_mario_geometry_inputs(struct MarioState *m) {
    f32 gasLevel;
    f32 ceilToFloorDist;

    f32_find_wall_collision(&m->pos[0], &m->pos[1], &m->pos[2], 60.0f, 50.0f);
    f32_find_wall_collision(&m->pos[0], &m->pos[1], &m->pos[2], 30.0f, 24.0f);

    m->floorHeight = find_floor(m->pos[0], m->pos[1], m->pos[2], &m->floor);

    // If Mario is OOB, move his position to his graphical position (which was not updated)
    // and check for the floor there.
    // This can cause errant behavior when combined with astral projection,
    // since the graphical position was not Mario's previous location.
    if (m->floor == NULL) {
        vec3f_copy(m->pos, m->marioObj->header.gfx.pos);
        m->floorHeight = find_floor(m->pos[0], m->pos[1], m->pos[2], &m->floor);
    }

    m->ceilHeight = find_mario_ceil(m->pos, m->floorHeight, &m->ceil);
    gasLevel = find_poison_gas_level(m->pos[0], m->pos[2]);
    m->waterLevel = find_water_level(m->pos[0], m->pos[2]);

    if (m->floor != NULL) {
        m->floorYaw = atan2s(m->floorNormal[2], m->floorNormal[0]);
        m->terrainSoundAddend = mario_get_terrain_sound_addend(m);

        if ((m->pos[1] > m->waterLevel - 40) && mario_floor_is_slippery(m)) {
            m->input |= INPUT_ABOVE_SLIDE;
        }

        if ((m->floor->object)
            || (m->ceil && m->ceil->object)) {
            ceilToFloorDist = m->ceilHeight - m->floorHeight;

            if ((0.0f <= ceilToFloorDist) && (ceilToFloorDist <= 150.0f)) {
                m->input |= INPUT_SQUISHED;
            }
        }

        if (m->pos[1] > m->floorHeight + 100.0f) {
            m->input |= INPUT_OFF_FLOOR;
        }

        if (m->pos[1] < (m->waterLevel - 10)) {
            m->input |= INPUT_IN_WATER;
        }

        if (m->pos[1] < (gasLevel - 100.0f)) {
            m->input |= INPUT_IN_POISON_GAS;
        }

    } else {
        level_trigger_warp(m, WARP_OP_DEATH);
    }
}

/**
 * Handles Mario's input flags as well as a couple timers.
 */
void update_mario_inputs(struct MarioState *m) {
    m->particleFlags = PARTICLE_NONE;
    m->input = INPUT_NONE;
    m->collidedObjInteractTypes = m->marioObj->collidedObjInteractTypes;
    m->flags &= 0xFFFFFF;

#ifdef PUPPYCAM
    if (gPuppyCam.mode3Flags & PUPPYCAM_MODE3_ENTER_FIRST_PERSON || (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_FREE && gPuppyCam.debugFlags & PUPPYDEBUG_LOCK_CONTROLS)) {
        m->input = INPUT_FIRST_PERSON;
        return;
    }
#endif

    if (!revent_active) {
        update_mario_button_inputs(m);
        update_mario_joystick_inputs(m);
    }
    update_mario_geometry_inputs(m);
#ifdef VANILLA_DEBUG
    debug_print_speed_action_normal(m);
#endif
    if (gCameraMovementFlags & CAM_MOVE_C_UP_MODE) {
        if (m->action & ACT_FLAG_ALLOW_FIRST_PERSON) {
            m->input |= INPUT_FIRST_PERSON;
        } else {
            gCameraMovementFlags &= ~CAM_MOVE_C_UP_MODE;
        }
    }

    if (!(m->input & (INPUT_NONZERO_ANALOG | INPUT_A_PRESSED))) {
        m->input |= INPUT_IDLE;
    }

    // These 3 flags are defined by Bowser stomping attacks
    if (m->marioObj->oInteractStatus
        & (INT_STATUS_MARIO_STUNNED | INT_STATUS_MARIO_KNOCKBACK_DMG | INT_STATUS_MARIO_SHOCKWAVE)) {
        m->input |= INPUT_STOMPED;
    }

    // This function is located near other unused trampoline functions,
    // perhaps logically grouped here with the timers.
    stub_mario_step_1(m);

    if (m->wallKickTimer > 0) {
        m->wallKickTimer--;
    }

    if (m->doubleJumpTimer > 0) {
        m->doubleJumpTimer--;
    }
}

/**
 * Set's the camera preset for submerged action behaviors.
 */
void set_submerged_cam_preset_and_spawn_bubbles(struct MarioState *m) {
    f32 heightBelowWater;
    s16 camPreset;

    if ((m->action & ACT_GROUP_MASK) == ACT_GROUP_SUBMERGED) {
        heightBelowWater = (f32)(m->waterLevel - 80) - m->pos[1];
        camPreset = m->area->camera->mode;

        if (m->action & ACT_FLAG_METAL_WATER) {
#ifdef USE_COURSE_DEFAULT_MODE
            // Being metal and in the water uses the default camera mode
            if (camPreset != m->area->camera->defMode) {
                set_camera_mode(m->area->camera, m->area->camera->defMode, 1);
            }
#else
            if (camPreset != CAMERA_MODE_CLOSE) {
                set_camera_mode(m->area->camera, CAMERA_MODE_CLOSE, 1);
            }
#endif
        } else {
            if ((heightBelowWater > 800.0f) && (camPreset != DEEP_WATER_CAMERA_MODE)) {
                set_camera_mode(m->area->camera, DEEP_WATER_CAMERA_MODE, 1);
            }

            if ((heightBelowWater < 400.0f) && (camPreset != WATER_SURFACE_CAMERA_MODE)) {
                set_camera_mode(m->area->camera, WATER_SURFACE_CAMERA_MODE, 1);
            }

            // As long as Mario isn't drowning or at the top
            // of the water with his head out, spawn bubbles.
            if (!(m->action & ACT_FLAG_INTANGIBLE)) {
                if ((m->pos[1] < (f32)(m->waterLevel - 160)) || (m->faceAngle[0] < -0x800)) {
                    m->particleFlags |= PARTICLE_BUBBLE;
                }
            }
        }
    }
}

/**
 * Both increments and decrements Mario's HP.
 */
void update_mario_health(struct MarioState *m) {
    s32 terrainIsSnow;



    if (m->health >= 0x100) {
        // When already healing or hurting Mario, Mario's HP is not changed any more here.
        if (((u32) m->healCounter | (u32) m->hurtCounter) == 0) {
            if ((m->input & INPUT_IN_POISON_GAS) && !(m->action & ACT_FLAG_INTANGIBLE)) {
                if (!(m->flags & MARIO_METAL_CAP) && !gDebugLevelSelect) {
                    m->health -= 4;
                }
            } else {
                if ((m->action & ACT_FLAG_SWIMMING) && !(m->action & ACT_FLAG_INTANGIBLE)) {
                    terrainIsSnow = (m->area->terrainType & TERRAIN_MASK) == TERRAIN_SNOW;
#ifdef BREATH_METER
                    // when in snow terrains lose 3 health.
                    if ((m->pos[1] < (m->waterLevel - 140)) && terrainIsSnow) {
                        m->health -= 3;
                    }
#else
                    // When Mario is near the water surface, recover health (unless in snow),
                    // when in snow terrains lose 3 health.
                    // If using the debug level select, do not lose any HP to water.
                    if ((m->pos[1] >= (m->waterLevel - 140)) && !terrainIsSnow) {
                        //m->health += 0x1A;  REPLACE WITH SEPARATE OXYGEN METER LATER (axo: possibly use BREATH_METER?)
                    } else if (!gDebugLevelSelect) {
                        // m->health -= (terrainIsSnow ? 3 : 1);
                    }
#endif
                }
            }
        }

        if (m->healCounter > 0) {
            m->health += 0x40;
            m->healCounter--;
        }
        if (m->hurtCounter > 0) {
            if ((gMarioState->numBadgePoints > 0) && ((save_file_get_badge_equip() & (1<<2)))) {
                gMarioState->numBadgePoints --;
            }
            else
            {
                //lose double health if brittle
                if (save_file_get_badge_equip() & (1<<BADGE_BRITTLE)) {
                    m->health -= 0x80;
                } else {
                    m->health -= 0x40;
                }

            }

            m->hurtCounter--;

            //don't.
            //GET RID OF ANY POWERUP ON HEALTH LOSS
            /*
            if (gMarioState->powerup != 0) {
                gMarioState->powerup = 0;
                play_sound(SOUND_MENU_ENTER_PIPE, gGlobalSoundSource);
            }
            */
        }

        if (cmm_lopt_game == CMM_GAME_BTCM) {
            //AIR: BTCM Behavior
            //air doesn't exist if you have gills
            if (!(save_file_get_badge_equip() & (1<<4))) {
                if ((m->pos[1] < m->waterLevel - 80)&&(((m->action & ACT_GROUP_MASK) == ACT_GROUP_SUBMERGED))) {
                    if (gMarioState->numAir > 0) {
                        gMarioState->numAir --;
                    }
                    else
                    {
                        gMarioState->numAir = 0;
                        m->health -= 20;
                    }
                }
                else
                {
                    if (gMarioState->numAir < 700) {
                        gMarioState->numAir += 5;
                    }
                    else
                    {
                        gMarioState->numAir = 700;
                    }
                }
            }

            // Play a noise to alert the player when Mario is close to drowning.
            if (((m->action & ACT_GROUP_MASK) == ACT_GROUP_SUBMERGED) && (gMarioState->numAir < 200)) {
                play_sound(SOUND_MOVING_ALMOST_DROWNING, gGlobalSoundSource);
                if (gRumblePakTimer == 0) {
                    gRumblePakTimer = 36;
                    if (is_rumble_finished_and_queue_empty()) {
                        queue_rumble_data(3, 30);
                    }
                }
            } else {
                gRumblePakTimer = 0;
            }
        } else {
            //AIR: Vanilla Behavior
            if ((m->action & ACT_FLAG_SWIMMING) && !(m->action & ACT_FLAG_INTANGIBLE)) {
                terrainIsSnow = FALSE;
                if ((m->pos[1] >= (m->waterLevel - 140)) && !terrainIsSnow) {
                    m->health += 0x1A;
                } else if (!gDebugLevelSelect) {
                    m->health -= (terrainIsSnow ? 3 : 1);
                }
            }
        }

        if (m->health > 255 + (255*gMarioState->numMaxHP)) {
            m->health = 255 + (255*gMarioState->numMaxHP);
        }
        if (m->health < 0x100) m->health = 0xFF;
    }
}

#ifdef BREATH_METER
void update_mario_breath(struct MarioState *m) {
    if (m->breath >= 0x100 && m->health >= 0x100) {
        if (m->pos[1] < (m->waterLevel - 140) && !(m->flags & MARIO_METAL_CAP) && !(m->action & ACT_FLAG_INTANGIBLE)) {
            m->breath--;
            if (m->breath < 0x300) {
                // Play a noise to alert the player when Mario is close to drowning.
                play_sound(SOUND_MOVING_ALMOST_DROWNING, gGlobalSoundSource);
#if ENABLE_RUMBLE
                if (gRumblePakTimer == 0) {
                    gRumblePakTimer = 36;
                    if (is_rumble_finished_and_queue_empty()) {
                        queue_rumble_data(3, 30);
                    }
                }
            } else {
                gRumblePakTimer = 0;
#endif
            }
        } else if (!(m->input & INPUT_IN_POISON_GAS)) {
            m->breath += 0x1A;
        }
        if (m->breathCounter > 0) {
            m->breath += 0x40;
            m->breathCounter--;
        }
        if (m->breath > 0x880) m->breath = 0x880;
        if (m->breath < 0x100) {
            // If breath is "zero", set health to "zero"
            m->breath =  0xFF;
            m->health =  0xFF;
        }
    }
}
#endif

/**
 * Updates some basic info for camera usage.
 */
void update_mario_info_for_cam(struct MarioState *m) {
    m->marioBodyState->action = m->action;
    m->statusForCamera->action = m->action;

    vec3s_copy(m->statusForCamera->faceAngle, m->faceAngle);

    if (!(m->flags & MARIO_LEDGE_CLIMB_CAMERA)) {
        vec3f_copy(m->statusForCamera->pos, m->pos);
    }
}

/**
 * Resets Mario's model, done every time an action is executed.
 */
void mario_reset_bodystate(struct MarioState *m) {
    struct MarioBodyState *bodyState = m->marioBodyState;

    bodyState->capState = MARIO_HAS_DEFAULT_CAP_OFF;
    bodyState->eyeState = MARIO_EYES_BLINK;
    bodyState->handState = MARIO_HAND_FISTS;
    bodyState->modelState = 0;
    bodyState->wingFlutter = FALSE;


    m->flags &= ~MARIO_METAL_SHOCK;
}

/**
 * Adjusts Mario's graphical height for quicksand.
 */
void sink_mario_in_quicksand(struct MarioState *m) {
    struct Object *marioObj = m->marioObj;

    if (marioObj->header.gfx.throwMatrix) {
        (*marioObj->header.gfx.throwMatrix)[3][1] -= m->quicksandDepth;
    }

    marioObj->header.gfx.pos[1] -= m->quicksandDepth;
}

/**
 * Is a binary representation of the frames to flicker Mario's cap when the timer
 * is running out.
 * 0x4444449249255555
 *
 * Equals [1000]^5 . [100]^8 . [10]^9 . [1] in binary, which is
 * 100010001000100010001001001001001001001001001010101010101010101.
 */
u64 sCapFlickerFrames = 0b100010001000100010001001001001001001001001001010101010101010101;

/**
 * Updates the cap flags mainly based on the cap timer.
 */
u32 update_and_return_cap_flags(struct MarioState *m) {
    u32 flags = m->flags;
    u32 action;

    if (m->flags & (MARIO_VANISH_CAP | MARIO_METAL_CAP) ) {
        action = m->action;

        if ((m->capTimer <= 60)
            || ((action != ACT_READING_AUTOMATIC_DIALOG) && (action != ACT_READING_NPC_DIALOG)
                && (action != ACT_READING_SIGN) && (action != ACT_IN_CANNON))) {
            m->capTimer -= 1;
        }

        if (m->capTimer == 0) {

            m->flags &= ~MARIO_SPECIAL_CAPS;
            if (!(m->flags & MARIO_CAPS)) {
                m->flags &= ~MARIO_CAP_ON_HEAD;
            }
        }

        // This code flickers the cap through a long binary string, increasing in how
        // common it flickers near the end.
        if ((m->capTimer < 64) && ((1ULL << m->capTimer) & sCapFlickerFrames)) {
            flags &= ~MARIO_SPECIAL_CAPS;
            if (!(flags & MARIO_CAPS)) {
                flags &= ~MARIO_CAP_ON_HEAD;
            }
        }
    } else {//mario is a flier

        if (gMarioState->RFuel < 1) {

            m->flags &= ~(MARIO_VANISH_CAP | MARIO_METAL_CAP | MARIO_WING_CAP);
            if ((m->flags & (MARIO_NORMAL_CAP | MARIO_VANISH_CAP | MARIO_METAL_CAP | MARIO_WING_CAP))
                == 0) {
                m->flags &= ~MARIO_CAP_ON_HEAD;
            }
        }

    }

    return flags;
}

/**
 * Updates the Mario's cap, rendering, and hitbox.
 */
void mario_update_hitbox_and_cap_model(struct MarioState *m) {
    struct MarioBodyState *bodyState = m->marioBodyState;
    s32 flags = update_and_return_cap_flags(m);

    if (flags & MARIO_VANISH_CAP) {
        bodyState->modelState = MODEL_STATE_NOISE_ALPHA;
    }

    if (flags & (MARIO_METAL_CAP | MARIO_METAL_SHOCK)) {
        bodyState->modelState |= MODEL_STATE_METAL;
    }

    //! (Pause buffered hitstun) Since the global timer increments while paused,
    //  this can be paused through to give continual invisibility. This leads to
    //  no interaction with objects.
    if ((m->invincTimer >= 3) && (gGlobalTimer & 1) && (gCurrLevelNum!=LEVEL_CCM)) {
        m->marioObj->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
    }

    if (flags & MARIO_CAP_IN_HAND) {
        if (flags & MARIO_WING_CAP) {
            bodyState->handState = MARIO_HAND_HOLDING_WING_CAP;
        } else {
            bodyState->handState = MARIO_HAND_HOLDING_CAP;
        }
    }

    if (flags & MARIO_CAP_ON_HEAD) {
        if (flags & MARIO_WING_CAP) {
            bodyState->capState = MARIO_HAS_WING_CAP_ON;
        } else {
            bodyState->capState = MARIO_HAS_DEFAULT_CAP_ON;
        }
    }

    // Short hitbox for crouching/crawling/etc.
    if (m->action & ACT_FLAG_SHORT_HITBOX) {
        m->marioObj->hitboxHeight = 100.0f;
    } else {
        m->marioObj->hitboxHeight = 160.0f;
    }

    if ((m->flags & MARIO_TELEPORTING) && (m->fadeWarpOpacity != MODEL_STATE_MASK)) {
        bodyState->modelState &= ~MODEL_STATE_MASK;
        bodyState->modelState |= (MODEL_STATE_ALPHA | m->fadeWarpOpacity);
    }
}

/**
 * An unused and possibly a debug function. Z + another button input
 * sets Mario with a different cap.
 */
UNUSED static void debug_update_mario_cap(u16 button, s32 flags, u16 capTimer, u16 capMusic) {
    // This checks for Z_TRIG instead of Z_DOWN flag
    // (which is also what other debug functions do),
    // so likely debug behavior rather than unused behavior.
    if ((gPlayer1Controller->buttonDown & Z_TRIG) && (gPlayer1Controller->buttonPressed & button)
        && !(gMarioState->flags & flags)) {
        gMarioState->flags |= (flags + MARIO_CAP_ON_HEAD);

        if (capTimer > gMarioState->capTimer) {
            gMarioState->capTimer = capTimer;
        }

        play_cap_music(capMusic);
    }
}

#if ENABLE_RUMBLE
void queue_rumble_particles(struct MarioState *m) {
    if (m->particleFlags & PARTICLE_HORIZONTAL_STAR) {
        queue_rumble_data(5, 80);
    } else if (m->particleFlags & PARTICLE_VERTICAL_STAR) {
        queue_rumble_data(5, 80);
    } else if (m->particleFlags & PARTICLE_TRIANGLE) {
        queue_rumble_data(5, 80);
    }
    if (m->heldObj && m->heldObj->behavior == segmented_to_virtual(bhvBobomb)) {
        reset_rumble_timers_slip();
    }
}
#endif

u16 bapple_frame = 0;
u8 regentime;
u8 did_started;

//u8 waveamount[] = {5,10,12,15,20,20,20,25,25,30,30};

u8 waveamount[] = {5,8,8,10,12,12,15,15,10,15,20};
/**
 * Main function for executing Mario's behavior. Returns particleFlags.
 */
u8 costumechange;
u8 entry_timer;
u8 entry_index = 1;

u8 among_init;

Vec3f posRecord[60];
u16 posRecordIndex;

f32 bad_apple_par = 0.0f;

#include "memory.h"
#include "libcart/include/cart.h"
#include "libcart/ff/ff.h"
#include "game_init.h"

u16 mario_decay;
s32 execute_mario_action(UNUSED struct Object *obj) {
    s32 inLoop = TRUE;
    u8 CostumeId = gMarioState->CostumeID;
    struct Object *sp1C;
    struct SpawnParticlesInfo D_8032F270 = { 2, 20, MODEL_MIST, 0, 40, 5, 30, 20, 252, 30, 10.0f, 10.0f };
    u8 *Hatcol = segmented_to_virtual(&mario_hat_v4_lights);
    u8 *Pantcol = segmented_to_virtual(&mario_button_v4_lights);
    u8 *Shoecol = segmented_to_virtual(&mario_shoes_v4_lights);
    u8 *Tokencol = segmented_to_virtual(&token_token_lights);
    u16 *walltex = segmented_to_virtual(&ccm_dl_Screen_ia8);
    u8 timerdelay = 0;
    u16 i;
    u8 x, y;
    u32 tempAddr = _bad_appleSegmentRomStart;
    u8 *sus = segmented_to_virtual(&castle_courtyard_dl_output_0_custom_i8_ia8);
    u8 coinrepeats = 1;
    u16 *walltex2 = segmented_to_virtual(&shrnling1_Static_i8);

    if (cmm_lopt_game == CMM_GAME_VANILLA) {
         gMarioObject->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MARIO2];
    }

    //if (mount_success != FR_OK) {
       //print_text_fmt_int(10, 56, "%d", global_code); 
    //}

    if (cmm_mode == CMM_MODE_MAKE) {
        gMarioState->marioObj->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
        return ACTIVE_PARTICLE_NONE;
    }

    if ((gCurrLevelNum == LEVEL_CASTLE_GROUNDS)&&(gCurrAreaIndex == 3)) {
        //I hope the models are loaded before these variables change.
        //Otherwise. Memory leak!
        for (i = 0; i<2048; i++) {
            walltex2[i] = random_u16();
            }
    }

    //manage global coins
    if (gMarioState->gGlobalCoinGain > 0) {
        if (gMarioState->numGlobalCoins < gMarioState->numMaxGlobalCoins) {
            gMarioState->numGlobalCoins ++;
            gMarioState->gGlobalCoinGain --;
            //save game when complete
            if (gMarioState->gGlobalCoinGain == 0) {
                //saving the game while collecting 1-ups is annoying
                //save_file_set_stats();
                //save_file_do_save(gCurrSaveFileNum - 1);
            }
        } else {
            gMarioState->gGlobalCoinGain = 0;
        }
    }

    if (gMarioState->gGlobalCoinGain < -15) {
        coinrepeats++;
    }
    if (gMarioState->gGlobalCoinGain < -100) {
        coinrepeats++;
    }//PENIS!!!!

    for (i=0;i<coinrepeats;i++) {

        if (gMarioState->gGlobalCoinGain < 0) {
            if (gMarioState->numGlobalCoins > 0) {
                gMarioState->numGlobalCoins --;
                gMarioState->gGlobalCoinGain ++;
                gMarioObject->oNumLootCoins = 1;
                if (gMarioState->gGlobalCoinGain >= -10) {
                    sp1C = spawn_object(gMarioObject, MODEL_YELLOW_COIN, bhvSingleCoinGetsSpawned);
                }
                //save game when complete
                if (gMarioState->gGlobalCoinGain == 0) {
                    save_file_set_stats();
                    save_file_do_save(gCurrSaveFileNum - 1);
                }
            } else {
                gMarioState->gGlobalCoinGain = 0;
            }
        }

    }

    //withering badge
    if (save_file_get_badge_equip() & (1<<BADGE_WITHER)) {
        mario_decay++;
        if (mario_decay > 450) {
            mario_decay = 0;
            gMarioState->hurtCounter += 4;
        }
    }

    //gMarioState->numStars = 120;
    //CONFIGURE GRAVITY
    gMarioState->gravMult = 1.0f;
    //badge gravity
    if (save_file_get_badge_equip() & (1<<BADGE_WEIGHT)) {
        gMarioState->gravMult *= 1.3f;
    }
    if (save_file_get_badge_equip() & (1<<BADGE_FEATHER)) {
        gMarioState->gravMult *= 0.9f;
    }
    //flappy bird is pretty light
    if ((gCurrLevelNum == LEVEL_CASTLE_COURTYARD)&&(gCurrAreaIndex == 4)) {
        gMarioState->gravMult *= 0.4f;
    }
    //lower gravity if cheating
    if (gMarioState->Cheats & (1 << 5)) {
        gMarioState->gravMult *= 0.5f;
    }
    if (gCurrLevelNum == LEVEL_BITS) {
        //MOON, low gravity
        gMarioState->gravMult *= 0.17f;
    }
    //CONFIGURE GRAVITY


    posRecordIndex ++;
    vec3f_copy(gMarioState->posDelay, posRecord[posRecordIndex%60]);
    vec3f_copy(posRecord[posRecordIndex%60], gMarioState->pos);

    //toggle minimap
    if (gPlayer1Controller->buttonPressed & L_TRIG) {
        gMarioState->Options ^= (1<<OPT_MINIMAP);
    }

    //cheats
    if (gMarioState->Cheats & (1 << 2)) {//moon jump with A
        if (gPlayer1Controller->buttonDown & A_BUTTON) {
            gMarioState->vel[1] = 30.0f;
            if (gMarioState->action != ACT_DOUBLE_JUMP) {
                set_mario_action(gMarioState, ACT_DOUBLE_JUMP,35);
                }
            }
        }
    if (gMarioState->Cheats & 1) {//
        gMarioState->health = 0x7FFF;
    }
    if (gMarioState->Cheats & (1 << 1)) {//infinite mana
        gMarioState->numBadgePoints = gMarioState->numMaxFP;
    }
    if (gMarioState->Cheats & (1 << 3)) {//infinite vanetal
        gMarioState->capTimer = 2;
        gMarioState->flags |= MARIO_METAL_CAP | MARIO_VANISH_CAP;
    }
    if (gMarioState->Cheats & (1 << 4)) {//infinite rocket boots
        gMarioState->RFuel=100;
        gMarioState->flags |= MARIO_WING_CAP;
    }
    
    //print_text_fmt_int(110, 56, "MEM %d", sPoolFreeSpace);

    if (gMarioState->CostumeID != costumechange) {
            cur_obj_spawn_particles(&D_8032F270);
            costumechange = gMarioState->CostumeID;
        }


    // clock boss code
    //its dogshit but im just trying to get thru this lol
    if (gCurrLevelNum == 0x05) {
        if (gCurrentArea->index == 0x04) {
            if (gMarioState->BossHealth < 3) {
                //static texture
                for (i = 0; i<512; i++) {
                    walltex[i] = random_u16();
                    }
                }
            if (gMarioState->BossHealth < 1) {
                sp1C = spawn_object(o, MODEL_EXPLOSION, bhvExplosionFake);
                sp1C->oGraphYOffset += 100.0f;
                sp1C->oPosX += (f32)(RandomMinMaxU16(0,1000))-500.0f;
                sp1C->oPosY += (f32)(RandomMinMaxU16(0,1000))-500.0f;
                sp1C->oPosZ += (f32)(RandomMinMaxU16(0,1000))-500.0f;
                }
            }
        }

    //minigame code
    switch (gMarioState->gCurrMinigame) {
        case 1://boneworks enemy arena
            if (gMarioState->EA_LEFT < 1) {
                cur_obj_play_sound_2(SOUND_GENERAL_WATER_LEVEL_TRIG);
                gMarioState->EA_WAVES ++;
                if ((gMarioState->EA_WAVES == 6)&&(!minigame_real)) {
                    sp1C = spawn_object_abs_with_rot(o, 0, MODEL_STAR, bhvStarSpawnCoordinates, o->oPosX, o->oPosY,o->oPosZ, 0, 0, 0);
                    sp1C->oHomeX = gMarioState->pos[0];
                    sp1C->oHomeY = gMarioState->pos[1]+200.0f;
                    sp1C->oHomeZ = gMarioState->pos[2];
                    sp1C->oBehParams = 0x03000000;
                    gMarioState->gCurrMinigame = 0;
                    }
                    else
                    {
                    gMarioState->EA_TOTAL = waveamount[gMarioState->EA_WAVES-1];
                    gMarioState->EA_LEFT = gMarioState->EA_TOTAL;
                    gMarioState->EA_ACTIVE = 0;
                    if (minigame_real) {
                        save_file_set_hiscore(0,gMarioState->EA_WAVES);
                        }
                    }

                //restore (temporary?)
                gMarioState->health = 255 + (255*gMarioState->numMaxHP);
                gMarioState->numBadgePoints = gMarioState->numMaxFP;
                gMarioState->powerup = 0; //mario cannot have a crowbar because he could softlock by killing eggs
                }
        break;
        case 2://hot jumprope

        break;
        }

    if (!gMarioState->IntroDid) {
        //set_mario_action(gMarioState, ACT_READING_AUTOMATIC_DIALOG,35);
        gMarioState->IntroDid = TRUE;
        }

    if (gMarioState->BadAppleActivate) {
        dma_read(sus,(bapple_frame*1024)+_bad_appleSegmentRomStart,(bapple_frame*1024)+_bad_appleSegmentRomStart+1024);

        if (bapple_frame < 6560) {
            if (gMarioState->gCurrMinigame == 6) {
                x = (u8)(((gMarioState->pos[0]+1000.0f)/2000.0f)*32.0f);
                y = (u8)(((gMarioState->pos[2]+1000.0f)/2000.0f)*32.0f);

                //Mario in air will do nothing.
                //Mario must be on the ground to gain/lose points.
                if (gMarioState->pos[1] < 10.0f) {
                    //Mario MUST stand on white
                    if (sus[(y*32)+x] > 20) {
                        bad_apple_par += 1.0f;
                    }
                    //Mario standing on black will deplete score
                    if (sus[(y*32)+x] <= 20) {
                        spawn_object(gMarioState->marioObj, MODEL_RED_FLAME, bhvKoopaShellFlame);
                        bad_apple_par -= 1.0f;
                        if (bad_apple_par < 0.0f) {
                            bad_apple_par = 0.0f;
                        }
                    }
                }

                gMarioState->EA_WAVES = (u8)((bad_apple_par/6560.0f)*255.0f);
                save_file_set_hiscore(5,gMarioState->EA_WAVES);
            }

            bapple_frame++;
            }
            else
            {
            gMarioState->BadAppleActivate = FALSE;
            bapple_frame = 0;
            if (gMarioState->gCurrMinigame == 6) {
                end_minigame();
            }
        }
    }


    //this code is dumb lol
    if ((gCurrDemoInput != NULL)&&(did_started == 0)) {
        start_cutscene(gCamera,CUTSCENE_CREDITS);
        did_started = TRUE;
        }

    //move warp for safe ground
    sp1C = cur_obj_nearest_object_with_behavior(bhvSpinAirborneWarp);

    if (gMarioState->ISSAFE) {
        if (sp1C != NULL) {
            //if ((!(gMarioState->floor->type == SURFACE_DEATH_PLANE))&&(!(gMarioState->floor->type == SURFACE_HARD_VERY_SLIPPERY))
            //..&&(gMarioState->input & INPUT_OFF_FLOOR)&&(gMarioState->floor->object == NULL)&&((gMarioState->area->terrainType & TERRAIN_MASK) != TERRAIN_SLIDE)) {
                sp1C->oPosX = gMarioState->pos[0];
                sp1C->oPosY = gMarioState->floorHeight;
                sp1C->oPosZ = gMarioState->pos[2];
                //}
            }
        gMarioState->ISSAFE = FALSE;
        }

    //print_text_fmt_int(110, 36, "DEBUG %d", gMarioState->MaskChase);


    //let mario change badges if near pipe
    struct Object *pipe;
    pipe = cur_obj_nearest_object_with_behavior(bhvWarpPipe);
    if (pipe) {
        if (lateral_dist_between_objects(gMarioObject,pipe) < 800.0f) {
            gMarioState->nearVendor = 20;
        }
    }


    if ((uintptr_t) gDynamicSurfacePoolEnd >= (uintptr_t) gDynamicSurfacePool + DYNAMIC_SURFACE_POOL_SIZE) {
        print_text_fmt_int(10, 56, "OUT OF POOL SPACE 0*%08x", (uintptr_t) gDynamicSurfacePoolEnd - (uintptr_t) gDynamicSurfacePool);
    }
        // print_text_fmt_int(10, 76, "0*%08x", (uintptr_t) gDynamicSurfacePoolEnd - (uintptr_t) gDynamicSurfacePool);
        //print_text_fmt_int(5, 16, "TELL ROVERT IF YOU SEE THIS",0);
        //Nah! nobody needs to see this
        //}

    //if (gMarioState->heldObjParam2 != 0) {
        //print_text_fmt_int(110, 36, "OBJPARAM %d", gMarioState->heldObjParam2);
        //}

    regentime ++;
    if (regentime > 200) {
        regentime = 0;

        // HP REGEN BADGE
        if (save_file_get_badge_equip() & (1<<6)) {
            if ((gMarioState->health < gMarioState->numMaxHP*0xFF)&&(gMarioState->numBadgePoints > 0)) {
                gMarioState->numBadgePoints --;
                gMarioState->health += 0xFF;
            }
        }
            // FP REGEN BADGE
        if (save_file_get_badge_equip() & (1<<7)) {
            if ((gMarioState->numBadgePoints < gMarioState->numMaxFP)&&(gMarioState->health > 510)) {
                gMarioState->numBadgePoints ++;
                gMarioState->health -= 0xFF;
                play_sound(SOUND_GENERAL_HEART_SPIN, gGlobalSoundSource);
            }
        }
    }

    //Gamer Mario
    ColorShift += 0x200;
    RainbowMario[0] = (coss(ColorShift)+1)*127;
    RainbowMario[1] = (coss(ColorShift + 21845)+1)*127;
    RainbowMario[2] = (coss(ColorShift - 21845)+1)*127;
    RainbowMario[3] = (sins(ColorShift)+1)*127;
    RainbowMario[4] = (sins(ColorShift + 21845)+1)*127;
    RainbowMario[5] = (sins(ColorShift - 21845)+1)*127;

    //HAT
    Hatcol[8] = CostumeData[CostumeId][0];//Diffuse
    Hatcol[9] = CostumeData[CostumeId][1];
    Hatcol[10] = CostumeData[CostumeId][2];
    Hatcol[12] = CostumeData[CostumeId][0];
    Hatcol[13] = CostumeData[CostumeId][1];
    Hatcol[14] = CostumeData[CostumeId][2];

    Hatcol[0] = CostumeData[CostumeId][0]/2;//Ambient
    Hatcol[1] = CostumeData[CostumeId][1]/2;
    Hatcol[2] = CostumeData[CostumeId][2]/2;
    Hatcol[4] = CostumeData[CostumeId][0]/2;
    Hatcol[5] = CostumeData[CostumeId][1]/2;
    Hatcol[6] = CostumeData[CostumeId][2]/2;

    //TOKEN
    Tokencol[8] = CostumeData[gMarioState->TokenParam2][0];//Diffuse
    Tokencol[9] = CostumeData[gMarioState->TokenParam2][1];
    Tokencol[10] = CostumeData[gMarioState->TokenParam2][2];
    Tokencol[12] = CostumeData[gMarioState->TokenParam2][0];
    Tokencol[13] = CostumeData[gMarioState->TokenParam2][1];
    Tokencol[14] = CostumeData[gMarioState->TokenParam2][2];

    Tokencol[0] = CostumeData[gMarioState->TokenParam2][0]/2;//Ambient
    Tokencol[1] = CostumeData[gMarioState->TokenParam2][1]/2;
    Tokencol[2] = CostumeData[gMarioState->TokenParam2][2]/2;
    Tokencol[4] = CostumeData[gMarioState->TokenParam2][0]/2;
    Tokencol[5] = CostumeData[gMarioState->TokenParam2][1]/2;
    Tokencol[6] = CostumeData[gMarioState->TokenParam2][2]/2;

    //JEANS
    Pantcol[8] = CostumeData[CostumeId][3];//Diffuse
    Pantcol[9] = CostumeData[CostumeId][4];
    Pantcol[10] = CostumeData[CostumeId][5];
    Pantcol[12] = CostumeData[CostumeId][3];
    Pantcol[13] = CostumeData[CostumeId][4];
    Pantcol[14] = CostumeData[CostumeId][5];

    Pantcol[0] = CostumeData[CostumeId][3]/2;//Ambient
    Pantcol[1] = CostumeData[CostumeId][4]/2;
    Pantcol[2] = CostumeData[CostumeId][5]/2;
    Pantcol[4] = CostumeData[CostumeId][3]/2;
    Pantcol[5] = CostumeData[CostumeId][4]/2;
    Pantcol[6] = CostumeData[CostumeId][5]/2;

    //SHOES
    Shoecol[8] = CostumeData[CostumeId][6];//Diffuse
    Shoecol[9] = CostumeData[CostumeId][7];
    Shoecol[10] = CostumeData[CostumeId][8];
    Shoecol[12] = CostumeData[CostumeId][6];
    Shoecol[13] = CostumeData[CostumeId][7];
    Shoecol[14] = CostumeData[CostumeId][8];

    Shoecol[0] = CostumeData[CostumeId][6]/2;//Ambient
    Shoecol[1] = CostumeData[CostumeId][7]/2;
    Shoecol[2] = CostumeData[CostumeId][8]/2;
    Shoecol[4] = CostumeData[CostumeId][6]/2;
    Shoecol[5] = CostumeData[CostumeId][7]/2;
    Shoecol[6] = CostumeData[CostumeId][8]/2;

    timerdelay = 30;

    if (save_file_get_badge_equip() & (1<<9)) {
        timerdelay = 60;
        }

    //only run timer code if not in cutscene
    if ((gMarioState->action & ACT_GROUP_MASK) != ACT_GROUP_CUTSCENE) {
        //MAKE TIMER GO DOWN
        if (gMarioState->NewTimer > 0) {
            gMarioState->SubNewTimer ++;
            if (gMarioState->SubNewTimer > timerdelay) {
                gMarioState->NewTimer --;
                gMarioState->SubNewTimer = 0;
                play_sound(SOUND_GENERAL2_SWITCH_TICK_SLOW, gGlobalSoundSource);
                }
            }
            else
            {
            if (gMarioState->NewTimerMode == 1) {
                gMarioState->health = 0xFF;
                }
            }
        }

    //press b to start cutscene
    //if (gPlayer1Controller->buttonPressed & L_TRIG) {
        //*(vs8*)0=0;
        //start_a_cutscene(gCamera);
        //set_mario_action(gMarioState,ACT_HOLD_FREEFALL,0);
        //gMarioState->heldObj = spawn_object(gMarioState->marioObj,MODEL_GOOMBA,bhvGoomba);
        //gMarioState->heldObjParam2 = gMarioState->heldObj->oBehParams2ndByte;
        //run_event(0);
        //}

    if (gMarioState->nearVendor > 0) {
        gMarioState->nearVendor--;
    }

    if (gMarioState->_2D) {
        gMarioState->pos[2] = 0.0f;
        if (gMarioState->_2DSecret) {
            gMarioState->pos[2] = -150.0f;
        }
    }

    // Updates once per frame:
    vec3f_get_dist_and_lateral_dist_and_angle(gMarioState->prevPos, gMarioState->pos, &gMarioState->moveSpeed, &gMarioState->lateralSpeed, &gMarioState->movePitch, &gMarioState->moveYaw);
    vec3f_copy(gMarioState->prevPos, gMarioState->pos);

    if (gMarioState->action) {
        if (gMarioState->Cheats & (1 << 7)) {
            if (gPlayer1Controller->buttonDown & U_JPAD && !(gPlayer1Controller->buttonDown & L_TRIG)) {
                set_camera_mode(gMarioState->area->camera, CAMERA_MODE_8_DIRECTIONS, 1);
                set_mario_action(gMarioState, ACT_DEBUG_FREE_MOVE, 0);
            }
        }
#ifdef ENABLE_CREDITS_BENCHMARK
        static s32 startedBenchmark = FALSE;
        if (!startedBenchmark) {
            set_mario_action(gMarioState, ACT_IDLE, 0);
            level_trigger_warp(gMarioState, WARP_OP_CREDITS_START);
            startedBenchmark = TRUE;
        }
#endif

        gMarioState->marioObj->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        mario_reset_bodystate(gMarioState);
        update_mario_inputs(gMarioState);

#ifdef PUPPYCAM
        if (!(gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_FREE)) {
#endif
        mario_handle_special_floors(gMarioState);
#ifdef PUPPYCAM
        }
#endif
        mario_process_interactions(gMarioState);

        // If Mario is OOB, stop executing actions.
        if (gMarioState->floor == NULL) {
            return ACTIVE_PARTICLE_NONE;
        }

        //CROWBAR
        if (gMarioState->powerup == 1) {
            if (gMarioState->input & INPUT_B_PRESSED) {
                switch(gMarioState->action) {
                    case ACT_IDLE:
                    case ACT_BRAKING:
                    case ACT_WALKING:
                    case ACT_JUMP:
                    case ACT_DOUBLE_JUMP:
                    case ACT_WALL_KICK_AIR:
                        play_sound(SOUND_ACTION_SIDE_FLIP_UNK, gMarioState->marioObj->header.gfx.cameraToObject);
                        sp1C = spawn_object(o, 0xF0, bhvCrowbarThrow);
                        sp1C->oForwardVel = 50.0f;
                        sp1C->oPosY += 50.0f;
                        sp1C->oFriction = 1.0f;
                        gMarioState->powerup = 0;
                        sp1C->oFaceAnglePitch = 0x4000;
                    break;
                }
            }
        }

        // The function can loop through many action shifts in one frame,
        // which can lead to unexpected sub-frame behavior. Could potentially hang
        // if a loop of actions were found, but there has not been a situation found.
        while (inLoop) {
            switch (gMarioState->action & ACT_GROUP_MASK) {
                case ACT_GROUP_STATIONARY: inLoop = mario_execute_stationary_action(gMarioState); break;
                case ACT_GROUP_MOVING:     inLoop = mario_execute_moving_action(gMarioState);     break;
                case ACT_GROUP_AIRBORNE:   inLoop = mario_execute_airborne_action(gMarioState);   break;
                case ACT_GROUP_SUBMERGED:  inLoop = mario_execute_submerged_action(gMarioState);  break;
                case ACT_GROUP_CUTSCENE:   inLoop = mario_execute_cutscene_action(gMarioState);   break;
                case ACT_GROUP_AUTOMATIC:  inLoop = mario_execute_automatic_action(gMarioState);  break;
                case ACT_GROUP_OBJECT:     inLoop = mario_execute_object_action(gMarioState);     break;
            }
        }

        sink_mario_in_quicksand(gMarioState);
        squish_mario_model(gMarioState);
        set_submerged_cam_preset_and_spawn_bubbles(gMarioState);
        update_mario_health(gMarioState);
#ifdef BREATH_METER
        update_mario_breath(gMarioState);
#endif
        update_mario_info_for_cam(gMarioState);
        mario_update_hitbox_and_cap_model(gMarioState);

        // Both of the wind handling portions play wind audio only in
        // non-Japanese releases.
        if (gMarioState->floor->type == SURFACE_HORIZONTAL_WIND) {
            //spawn_wind_particles(0, (gMarioState->floor->force << 8));
            play_sound(SOUND_ENV_WIND2, gMarioState->marioObj->header.gfx.cameraToObject);
        }

        if (gMarioState->floor->type == SURFACE_VERTICAL_WIND) {
            spawn_wind_particles(1, 0);
            play_sound(SOUND_ENV_WIND2, gMarioState->marioObj->header.gfx.cameraToObject);
        }

        play_infinite_stairs_music();
        gMarioState->marioObj->oInteractStatus = INT_STATUS_NONE;
#if ENABLE_RUMBLE
        queue_rumble_particles(gMarioState);
#endif

        return gMarioState->particleFlags;
    }

    return ACTIVE_PARTICLE_NONE;
}

/**************************************************
 *                  INITIALIZATION                *
 **************************************************/

void init_mario(void) {
    s16 currenthp = gMarioState->health > 0 ? gMarioState->health >> 8 : 0;

    struct Object *capObject;

    struct Object *holdTransferObject;
    did_started = 0;
    among_init = TRUE;

    mario_decay = 0;

    gMarioState->onbluecoinswitch = FALSE;
    gMarioState->nearVendor = 0;

    gMarioState->SpotlightTarget = gMarioObject;
    gMarioState->SpotlightTargetYOffset = 0.0f;

    //2d in flappy bird
    if ((gCurrLevelNum == LEVEL_CASTLE_COURTYARD)&&(gCurrAreaIndex == 4)) {
        gMarioState->_2D = TRUE;
    }
    //2d in trial
    if (gCurrLevelNum == LEVEL_RR) {
        gMarioState->_2D = FALSE;
        if (gCurrAreaIndex == 4) {
            gMarioState->_2D = TRUE;
        }
    }

    gMarioState->isAfterlife = FALSE;
    if (save_file_get_progression() == PROG_POSTGAME) {
        gMarioState->isAfterlife = TRUE;
    }

    stop_event();
    if ((gCurrLevelNum == LEVEL_CASTLE_GROUNDS)&&(save_file_get_progression() == PROG_LETTER_INIT)) {
        save_file_set_progression(PROG_START);
        run_event(EVENT_LETTER);
    }
    if ((gCurrAreaIndex == 0)&&(gCurrLevelNum == LEVEL_RR)) {
        run_event(EVENT_AG_INTRO);
    }

    if (gCurrLevelNum == LEVEL_BITS) {
        save_file_set_progression(PROG_ON_AGAMEMNON);
    }

    if (minigame_transition) {
        minigame_transition_func();
    }

    gMarioState->_2DSecret = FALSE;
    gMarioState->BadAppleActivate = FALSE;
    bapple_frame = 0;

    if (gCurrLevelNum == 0x05) {
        if (gCurrentArea->index == 0x04) {
            gMarioState->BossHealth = 3;
            gMarioState->BossHealthMax = 3;
            }
        }

    gMarioState->numAir = 700;
    gMarioState->RFuel=0;

    //crimas only!!!
    gMarioState->MessHeld = 0;
    gMarioState->MessNumber = 0;
    //crimas only!!

    gMarioState->gCurrMinigame = 0;
    gMarioState->EA_WAVES = 0;
    //arena
    if ((gCurrLevelNum == LEVEL_CCM)&&(gCurrAreaIndex == 3)) {
        gMarioState->gCurrMinigame = 1;
        gMarioState->EA_WAVES = 0;
        gMarioState->EA_TOTAL = 0;
        gMarioState->EA_LEFT = 0;
        gMarioState->EA_ACTIVE = 0;
        }
    //minigame things
    if (gCurrLevelNum == LEVEL_CASTLE_COURTYARD) {
        gMarioState->EA_WAVES = 0;
        if (gCurrAreaIndex == 2) {
            gMarioState->gCurrMinigame = 5;
        }
        if (gCurrAreaIndex == 1) {
            gMarioState->gCurrMinigame = 4;
        }
        if (gCurrAreaIndex == 3) {
            gMarioState->gCurrMinigame = 6;
            gMarioState->BadAppleActivate = TRUE;
            bad_apple_par = 0.0f;
            bapple_frame = 0;
        }
        if (gCurrAreaIndex == 4) {
            gMarioState->gCurrMinigame = 7;
        }
    }
    //hexagon heat
    if ((gCurrLevelNum == LEVEL_SL)&&(gCurrAreaIndex == 2)) {
        gMarioState->gCurrMinigame = 3;
        gMarioState->EA_WAVES = 0;
        }


    gMarioState->SwitchPressed = 0;

    gMarioState->actionTimer = 0;
    gMarioState->framesSinceA = 0xFF;
    gMarioState->framesSinceB = 0xFF;

    gMarioState->invincTimer = 0;

    if (save_file_get_flags()
        & (SAVE_FLAG_CAP_ON_GROUND | SAVE_FLAG_CAP_ON_KLEPTO | SAVE_FLAG_CAP_ON_UKIKI
           | SAVE_FLAG_CAP_ON_MR_BLIZZARD)) {
        gMarioState->flags = 0;
    } else {
        gMarioState->flags = (MARIO_NORMAL_CAP | MARIO_CAP_ON_HEAD);
    }



    gMarioState->forwardVel = 0.0f;
    gMarioState->squishTimer = 0;

    gMarioState->hurtCounter = 0;
    gMarioState->healCounter = 0;

    gMarioState->capTimer = 0;
    gMarioState->quicksandDepth = 0.0f;

    gMarioState->riddenObj = NULL;
    gMarioState->usedObj = NULL;

    gMarioState->waterLevel = find_water_level(gMarioSpawnInfo->startPos[0], gMarioSpawnInfo->startPos[2]);

    gMarioState->area = gCurrentArea;
    gMarioState->marioObj = gMarioObject;
    gMarioState->marioObj->header.gfx.animInfo.animID = -1;
    vec3s_copy(gMarioState->faceAngle, gMarioSpawnInfo->startAngle);
    vec3_zero(gMarioState->angleVel);
    vec3s_to_vec3f(gMarioState->pos, gMarioSpawnInfo->startPos);
    vec3f_copy(gMarioState->prevPos, gMarioState->pos);
    vec3_zero(gMarioState->vel);
    gMarioState->floorHeight =
        find_floor(gMarioState->pos[0], gMarioState->pos[1], gMarioState->pos[2], &gMarioState->floor);

    if (gMarioState->pos[1] < gMarioState->floorHeight) {
        gMarioState->pos[1] = gMarioState->floorHeight;
    }

    gMarioState->marioObj->header.gfx.pos[1] = gMarioState->pos[1];

    gMarioState->action =
        (gMarioState->pos[1] <= (gMarioState->waterLevel - 100)) ? ACT_WATER_IDLE : ACT_IDLE;

    mario_reset_bodystate(gMarioState);
    update_mario_info_for_cam(gMarioState);
    gMarioState->marioBodyState->punchState = 0;

    vec3f_copy(&gMarioState->marioObj->oPosVec, gMarioState->pos);
    vec3s_to_vec3i(&gMarioState->marioObj->oMoveAngleVec, gMarioState->faceAngle);

    vec3f_copy(gMarioState->marioObj->header.gfx.pos, gMarioState->pos);
    vec3s_set(gMarioState->marioObj->header.gfx.angle, 0, gMarioState->faceAngle[1], 0);

    if (gMarioState->MaskChase) {
        if (!cur_obj_nearest_object_with_behavior(bhvMask2)) {
            capObject = spawn_object(gMarioState->marioObj, MODEL_MASK2, bhvMask2);
            capObject->oAction = 1;
            capObject->oPosY -= 1000.0f;
            capObject->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        }
    }

    Vec3s capPos;
    if (save_file_get_cap_pos(capPos)) {
        capObject = spawn_object(gMarioState->marioObj, MODEL_MARIOS_CAP, bhvNormalCap);
        vec3s_to_vec3f(&capObject->oPosVec, capPos);

        capObject->oForwardVel = 0;
        capObject->oMoveAngleYaw = 0;
    }

    if (gMarioState->NewLevel == TRUE) {
        gMarioState->invincTimer = 60;
        if (save_file_get_badge_equip() & (1<<BADGE_BOTTOMLESS)) {
            gMarioState->numBadgePoints --;
        } else {
            gMarioState->hurtCounter += 4 * ((f32)(gMarioState->numMaxHP)/3.0f);
        }

        if (gMarioState->MaskChase) {
            gMarioState->hurtCounter += 999;
        }
        gMarioState->NewLevel = FALSE;
    }

    gMarioState->heldObj = NULL;
    if (gMarioState->heldObjParam2 != 0) {
        switch(gMarioState->heldObjParam2) {
            case 1: //goblet of semen
                holdTransferObject = spawn_object(gMarioState->marioObj,0xF3,bhvBreakableBoxSmall);
                holdTransferObject->oBehParams2ndByte = 1;
                //gMarioState->usedObj = holdTransferObject;
                //mario_grab_used_object(gMarioState);
                break;
            case 2: //key
                holdTransferObject = spawn_object(gMarioState->marioObj,0xF4,bhvBreakableBoxSmall);
                holdTransferObject->oBehParams2ndByte = 2;
                break;
        }
        gMarioState->heldObjParam2 = 0;
    }


    
}

void init_mario_from_save_file(void) {
    save_file_get_stats();
    
    sSelectedFileNum = FALSE;
    fs_ms = 0;

    gMarioState->toggleHud = TRUE;
    gMarioState->playerID = 0;
    gMarioState->flags = MARIO_NONE;
    gMarioState->action = ACT_UNINITIALIZED;
    gMarioState->spawnInfo = &gPlayerSpawnInfos[0];
    gMarioState->statusForCamera = &gPlayerCameraState[0];
    gMarioState->marioBodyState = &gBodyStates[0];
    gMarioState->animList = &gMarioAnimsBuf;
    if (gIsConsole && __osControllerTypes[1] == CONT_TYPE_GCN) {
        gMarioState->controller = &gControllers[1];
    } else {
        gMarioState->controller = &gControllers[0];
    }

    gMarioState->numCoins = 0;
    gMarioState->lastStarCollected = 0;
    gMarioState->numStars = save_file_get_total_golden_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1);
    gMarioState->numMetalStars = save_file_get_total_metal_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1);

    gMarioState->numKeys = 0;

    gMarioState->numLives = DEFAULT_NUM_LIVES;
    gMarioState->health = 255 + (255*gMarioState->numMaxHP);
    gMarioState->numBadgePoints = gMarioState->numMaxFP;
#ifdef BREATH_METER
    gMarioState->breath = 0x880;
    gHudDisplay.breath = 8;
#endif
    gMarioState->prevNumStarsForDialog = gMarioState->numStars;
    gMarioState->animYTrans = 0xBD;

    gHudDisplay.coins = 0;
    gHudDisplay.wedges = 8;
}
