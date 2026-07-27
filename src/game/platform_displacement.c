#include <PR/ultratypes.h>

#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "level_update.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "platform_displacement.h"
#include "game_init.h"
#include "types.h"
#include "sm64.h"
#include "behavior_data.h"

u16 D_8032FEC0 = 0;

u32 unused_8032FEC4[4] = { 0 };

struct Object *gMarioPlatform = NULL;
struct PlatformDisplacementInfo sMarioDisplacementInfo;
Vec3f sMarioAmountDisplaced;

/**
 * Determine if Mario is standing on a platform object, meaning that he is
 * within 4 units of the floor. Set his referenced platform object accordingly.
 */
void update_mario_platform(void) {
    struct Surface *floor;
    UNUSED u32 unused;
    f32 marioX;
    f32 marioY;
    f32 marioZ;
    f32 floorHeight;
    u32 awayFromFloor;

	if (gTimeStopState & TIME_STOP_ACTIVE) {
		return;
	}

    if (gMarioObject == NULL) {
        return;
    }

    //! If Mario moves onto a rotating platform in a PU, the find_floor call
    //  will detect the platform and he will end up receiving a large amount
    //  of displacement since he is considered to be far from the platform's
    //  axis of rotation.

    marioX = gMarioObject->oPosX;
    marioY = gMarioObject->oPosY;
    marioZ = gMarioObject->oPosZ;
    floorHeight = find_floor_short(marioX, marioY, marioZ, &floor);

    if (absf(marioY - floorHeight) < 4.0f) {
        awayFromFloor = 0;
    } else {
        awayFromFloor = 1;
    }

    switch (awayFromFloor) {
        case 1:
            gMarioPlatform = NULL;
            break;

        case 0:
            if (floor != NULL && floor->object != NULL) {
                gMarioPlatform = floor->object;
				if ((floor->object != sMarioDisplacementInfo.prevPlatform) || (gGlobalTimer != sMarioDisplacementInfo.prevTimer)) {
					update_platform_displacement_info(&sMarioDisplacementInfo, gMarioState->pos, gMarioState->faceAngle[1], floor->object);
				}
            } else {
                gMarioPlatform = NULL;

				if (floor->object != NULL) {
					gMarioPlatform = floor->object;
					sMarioAmountDisplaced[1] = 0.0f;
				}
            }
            break;
    }
}

/**
 * Set the values in the platform displacement struct for use next frame
 */
void update_platform_displacement_info(struct PlatformDisplacementInfo *displaceInfo, Vec3f pos, s16 yaw, struct Object *platform) {
    Vec3f scaledPos, yawVec, localPos;

    // Avoid a crash if the platform unloaded its collision while stood on or is static
    if (platform->header.gfx.throwMatrix == NULL) return;

    // Update position
    vec3_diff(localPos, pos, (*platform->header.gfx.throwMatrix)[3]);
    linear_mtxf_transpose_mul_vec3(*platform->header.gfx.throwMatrix, scaledPos, localPos);
    vec3_quot(displaceInfo->prevTransformedPos, scaledPos, platform->header.gfx.scale);
    vec3_copy(displaceInfo->prevPos, pos);

    // Update yaw
    vec3_set(yawVec, sins(yaw), 0, coss(yaw));
    linear_mtxf_transpose_mul_vec3(*platform->header.gfx.throwMatrix, displaceInfo->prevTransformedYawVec, yawVec);
    displaceInfo->prevYaw = yaw;

    // Update platform and timer
    displaceInfo->prevPlatform = platform;
    displaceInfo->prevTimer = gGlobalTimer;
}

void apply_conveyor_displacement() {
	s16 currentAngle = gMarioPlatform->oFaceAngleYaw;
	f32 currentSpeed = 10.76f;

	if (((gMarioState->action & ACT_GROUP_MASK) == ACT_GROUP_MOVING) || ((gMarioState->action & ACT_GROUP_MASK) == ACT_GROUP_STATIONARY)) {
		f32 perpendicularDistance = (gMarioState->pos[0] - gMarioPlatform->oPosX) * coss(currentAngle) - (gMarioState->pos[2] - gMarioPlatform->oPosZ) * sins(currentAngle);
		// If too close to edge, tilt angle a little
		if (perpendicularDistance < -105.0f) {
			currentAngle += 0x2000;
		} else if (perpendicularDistance > 105.0f) {
			currentAngle -= 0x2000;
		}
	}

	f32 xVel = currentSpeed * sins(currentAngle);
	f32 zVel = currentSpeed * coss(currentAngle);

	gMarioState->pos[0] += xVel;
	gMarioState->pos[2] += zVel;
	vec3f_set(sMarioAmountDisplaced, xVel, 0.f, zVel);
	if (gMarioPlatform->oExtraVariable1 > 0) {
		gMarioState->forwardVel = MAX(-15.f, gMarioState->forwardVel); // bljs are far too easy otherwise
	}

	// Check if left floor
	f32 floorHeight = find_floor_height_short(gMarioState->pos[0], gMarioState->pos[1], gMarioState->pos[2]);
	if ((floorHeight < gMarioState->pos[1] - 5.f) && (abs_angle_diff(gMarioState->faceAngle[1], currentAngle) > 0x4000)) {
		gMarioState->forwardVel = MIN(5.f, gMarioState->forwardVel);
	} 
}


/**
 * Apply one frame of platform displacement to Mario or an object using the given
 * platform.
 */
void apply_platform_displacement(struct PlatformDisplacementInfo *displaceInfo, Vec3f pos, s16 *yaw, struct Object *platform) {
    Vec3f posDifference;
    Vec3f yawVec;
    Vec3f scaledPos;
    // Determine how much Mario turned on his own since last frame
    s16 yawDifference = *yaw - displaceInfo->prevYaw;

    // Avoid a crash if the platform unloaded its collision while stood on or is static
	if (platform->header.gfx.throwMatrix == NULL) {
		vec3f_set(sMarioAmountDisplaced,0,0,0);
		return;
	}

    if (platform->behavior == segmented_to_virtual(bhvConveyor)) {
		apply_conveyor_displacement();
		return;
	}

    // Determine how far Mario moved on his own since last frame
    vec3_diff(posDifference, pos, displaceInfo->prevPos);

    if ((platform == displaceInfo->prevPlatform) && (gGlobalTimer == displaceInfo->prevTimer + 1)) {
        // For certain objects, only use velocity for displacement rather than the transform
        // E.g. TTC treadmills
        if (platform->oFlags & OBJ_FLAG_NO_AUTO_DISPLACEMENT) {
            pos[0] += platform->oVelX;
            pos[1] += platform->oVelY;
            pos[2] += platform->oVelZ;
        } else {
            // Transform from relative positions to world positions
            vec3_prod(scaledPos, displaceInfo->prevTransformedPos, platform->header.gfx.scale);
            linear_mtxf_mul_vec3(*platform->header.gfx.throwMatrix, pos, scaledPos);
            vec3_add(pos, (*platform->header.gfx.throwMatrix)[3]);

            // Add on how much Mario moved in the previous frame
            vec3_add(pos, posDifference);

            // Calculate new yaw
            linear_mtxf_mul_vec3(*platform->header.gfx.throwMatrix, yawVec, displaceInfo->prevTransformedYawVec);
            *yaw = atan2s(yawVec[2], yawVec[0]) + yawDifference;
        }
    }

    Vec3f oldPos;
    vec3_sum(oldPos, displaceInfo->prevPos, posDifference);
    update_platform_displacement_info(displaceInfo, pos, *yaw, platform);

    // If the object is Mario, set inertia
    if (pos == gMarioState->pos) {
        vec3_diff(sMarioAmountDisplaced, pos, oldPos);
    }
}

u8 sShouldApplyInertia = FALSE;
u8 sInertiaFirstFrame = FALSE;

/**
 * Apply inertia based on Mario's last platform.
 */
static void apply_mario_inertia(void) {
#ifdef MARIO_INERTIA_UPWARD
    // On the first frame of leaving the ground, boost Mario's y velocity
    if (sInertiaFirstFrame) {
        if (sMarioAmountDisplaced[1] > 0.0f) {
            gMarioState->vel[1] += sMarioAmountDisplaced[1];
        }
    }
#endif

#ifdef MARIO_INERTIA_LATERAL
    // Apply sideways inertia
    gMarioState->pos[0] += sMarioAmountDisplaced[0];
    gMarioState->pos[2] += sMarioAmountDisplaced[2];

    // Drag
    sMarioAmountDisplaced[0] *= 0.97f;
    sMarioAmountDisplaced[2] *= 0.97f;
#endif

    // Stop applying inertia once Mario has landed, or when ground pounding
    if (!(gMarioState->action & ACT_FLAG_AIR) || (gMarioState->action == ACT_GROUND_POUND)) {
        sShouldApplyInertia = FALSE;
    }
}

/**
 * Apply platform displacement or inertia if required.
 */
void apply_mario_platform_displacement(void) {
    struct Object *platform;

    platform = gMarioPlatform;
    if (!(gTimeStopState & TIME_STOP_ACTIVE) && gMarioObject != NULL) {
        if (platform != NULL) {
            apply_platform_displacement(&sMarioDisplacementInfo, gMarioState->pos, &gMarioState->faceAngle[1], platform);
            sShouldApplyInertia = TRUE;
            sInertiaFirstFrame = TRUE;
        } else if (sShouldApplyInertia) {
            apply_mario_inertia();
            sInertiaFirstFrame = FALSE;
        }
    }
}
