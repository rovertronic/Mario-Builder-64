#include "config.h"

/**
 * This is the behavior file for the tilting inverted pyramids in BitFS/LLL.
 * The object essentially just tilts and moves Mario with it.
 */

/**
 * Creates a transform matrix on a variable passed in from given normals
 * and the object's position.
 */
void create_transform_from_normals(Mat4 transform, f32 xNorm, f32 yNorm, f32 zNorm) {
    Vec3f normal;
    Vec3f pos;

    pos[0] = o->oPosX;
    pos[1] = o->oPosY;
    pos[2] = o->oPosZ;

    normal[0] = xNorm;
    normal[1] = yNorm;
    normal[2] = zNorm;

    mtxf_align_terrain_normal(transform, normal, pos, 0);
}

/**
 * Initialize the object's transform matrix with Y being up.
 */
void bhv_platform_normals_init(void) {
    Mat4 *transform = &o->transform;

    o->oTiltingPyramidNormalX = 0.0f;
    o->oTiltingPyramidNormalY = 1.0f;
    o->oTiltingPyramidNormalZ = 0.0f;

    create_transform_from_normals(*transform, 0.0f, 1.0f, 0.0f);
}

/**
 * Returns a value that is src incremented/decremented by inc towards goal
 * until goal is reached. Does not overshoot.
 */
f32 approach_by_increment(f32 goal, f32 src, f32 inc) {
    f32 newVal;

    if (src <= goal) {
        if (goal - src < inc) {
            newVal = goal;
        } else {
            newVal = src + inc;
        }
    } else if (goal - src > -inc) {
        newVal = goal;
    } else {
        newVal = src - inc;
    }

    return newVal;
}

/**
 * Main behavior for the tilting pyramids in LLL/BitFS. These platforms calculate rough normals from Mario's position,
 * then gradually tilt back moving Mario with them.
 */
void bhv_tilting_inverted_pyramid_loop(void) {
    Vec3f d;
#ifndef PLATFORM_DISPLACEMENT_2
    Vec3f dist;
    Vec3f posBeforeRotation;
    Vec3f posAfterRotation;

    // Mario's position
    Vec3f m;
#endif
    Mat4 *transform = &o->transform;
    if (gMarioObject->platform == o) {
#ifndef PLATFORM_DISPLACEMENT_2
        get_mario_pos(&m[0], &m[1], &m[2]);
        vec3_diff(dist, &gMarioObject->oPosVec, &o->oPosVec);
        linear_mtxf_mul_vec3f(*transform, posBeforeRotation, dist);
#endif
        d[0] = gMarioObject->oPosX - o->oPosX;
        d[1] = 500.0f;
        d[2] = gMarioObject->oPosZ - o->oPosZ;
        vec3f_normalize(d);
        o->oTiltingPyramidMarioOnPlatform = TRUE;
    } else {
        vec3_copy(d, gVec3fY);
        o->oTiltingPyramidMarioOnPlatform = FALSE;
    }
    // Approach the normals by 0.01f towards the new goal, then create a transform matrix and orient the object.
    // Outside of the other conditionals since it needs to tilt regardless of whether Mario is on.
    o->oTiltingPyramidNormalX = approach_by_increment(d[0], o->oTiltingPyramidNormalX, 0.01f);
    o->oTiltingPyramidNormalY = approach_by_increment(d[1], o->oTiltingPyramidNormalY, 0.01f);
    o->oTiltingPyramidNormalZ = approach_by_increment(d[2], o->oTiltingPyramidNormalZ, 0.01f);
    create_transform_from_normals(*transform, o->oTiltingPyramidNormalX, o->oTiltingPyramidNormalY, o->oTiltingPyramidNormalZ);
#ifndef PLATFORM_DISPLACEMENT_2
    // If Mario is on the platform, adjust his position for the platform tilt.
    if (o->oTiltingPyramidMarioOnPlatform) {
        linear_mtxf_mul_vec3f(*transform, posAfterRotation, dist);
        m[0] += posAfterRotation[0] - posBeforeRotation[0];
        m[1] += posAfterRotation[1] - posBeforeRotation[1];
        m[2] += posAfterRotation[2] - posBeforeRotation[2];

        set_mario_pos(m[0], m[1], m[2]);
    }
#endif
    o->header.gfx.throwMatrix = transform;
}
