#ifndef PLATFORM_DISPLACEMENT_H
#define PLATFORM_DISPLACEMENT_H

#include <PR/ultratypes.h>

#include "types.h"

struct PlatformDisplacementInfo {
	Vec3f prevPos;
	Vec3f prevTransformedPos;
	Vec3f prevTransformedYawVec;
	s16 prevYaw;
	struct Object *prevPlatform;
	s32 prevTimer;
};

void update_mario_platform(void);
void get_mario_pos(f32 *x, f32 *y, f32 *z);
void set_mario_pos(f32 x, f32 y, f32 z);
void apply_platform_displacement(struct PlatformDisplacementInfo *displaceInfo, Vec3f pos, s16 *yaw, struct Object *platform);
void apply_mario_platform_displacement(void);
#ifndef VERSION_JP
void clear_mario_platform(void);
#endif

#endif // PLATFORM_DISPLACEMENT_H
