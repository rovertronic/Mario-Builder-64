static f32 woodplat_get_stack_height(struct Object *basePlat) {
    f32 stackHeight = 0.f;
    do {
        stackHeight += (basePlat->oBehParams2ndByte == 1 ? 256.f : 96.f);
        basePlat = basePlat->oWoodPlatAbovePlatform;
    } while (basePlat);
    return stackHeight;
}

static void bhv_woodplat_check_above(void) {
    // Check if there is a wooden platform immediately above this one
    // Fake the Y position
    o->oPosY += 256.f;
    struct Object *platform = cur_obj_nearest_object_with_behavior(bhvWoodPlat);
    if (!platform) {
        o->oPosY -= 256.f;
        return;
    }
    f32 dist = dist_between_objects(o, platform);
    o->oPosY -= 256.f;

    if (dist < 5.f) {
        o->oWoodPlatAbovePlatform = platform;
        platform->oWoodPlatIsStacked = TRUE;
        return;
    }
}

void bhv_woodplat_init(void) {
    o->oWallHitboxRadius = 127.8f; // VERY EXACT, needs to be less than 127.9 for the .1 wall buffer
    o->hitboxDownOffset = 0.f;
    o->oGravity = -4.f;
    o->oBuoyancy = 0.f;
    if (o->oBehParams2ndByte == 1) {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_FATPLAT];
        bhv_woodplat_check_above();
    }
}

void bhv_woodplat_loop(void) {
    f32 waterLevel = mb64_get_water_level(o->oPosX, o->oPosY + 80.f, o->oPosZ);
    if (o->oWoodPlatIsStacked) {
        return;
    }
    add_obj_to_physics_list(o);
    if (o->oTimer == 1) {
        o->prevObj = spawn_object(o, MODEL_NONE, bhvWoodPlatCol);
        o->prevObj->prevObj = o;
        vec3f_copy(&o->prevObj->oPosVec, &o->oPosVec);
        o->hitboxHeight = woodplat_get_stack_height(o);
    }
    if (waterLevel > o->oPosY) {
        // Underwater Behavior
        o->oVelY *= 0.9f;
        f32 gravity = CLAMP((waterLevel - 64.f - o->oPosY) * 0.1f, -2.0f, 2.0f);
        o->oVelY += 4 + gravity;
        if (gMarioPlatform == o->prevObj) {
            o->oVelY -= 1.f;
            if (gMarioState->action == ACT_GROUND_POUND_LAND) {
                o->oVelY -= 2.f;
            }
        }
    }
    cur_obj_update_floor();
    cur_obj_update_ceiling();

    // This code is very hacky. Use higher wall checks when on an
    // upwards sloped conveyor in order to not get stuck on the wall of
    // the conveyor above.
    if (o->oFloor && o->oFloor->type == SURFACE_CONVEYOR &&
        o->oFloor->object->oExtraVariable1 != 0 &&
        o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND) {
        o->oFlags &= ~OBJ_FLAG_SIMPLE_WALL_CHECKS;
    } else {
        o->oFlags |= OBJ_FLAG_SIMPLE_WALL_CHECKS;
    }
    cur_obj_move_standard(-20);
    cur_obj_resolve_wall_collisions();

    if (cur_obj_die_if_on_death_barrier(MB64_STAR_HEIGHT)) {
        if (!o->oWoodPlatIsStacked) {
            o->prevObj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        }
        struct Object *curPlat = o;
        do {
            curPlat->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            curPlat = curPlat->oWoodPlatAbovePlatform;
        } while (curPlat);
    }

    Vec3f oldPos;
    vec3f_copy(oldPos, &o->prevObj->oPosVec);
    vec3f_copy(&o->prevObj->oPosVec, &o->oPosVec);
    vec3f_copy(o->header.gfx.pos, oldPos);
    vec3_copy(o->header.gfx.angle, &o->oFaceAngleVec);

    struct Object *curPlat = o;
    while (curPlat->oWoodPlatAbovePlatform) {
        vec3f_copy(&curPlat->oWoodPlatAbovePlatform->oPosVec, curPlat->header.gfx.pos);
        curPlat = curPlat->oWoodPlatAbovePlatform;
        curPlat->oPosY += 256.f;
        vec3f_copy(curPlat->header.gfx.pos, &curPlat->oPosVec);
        vec3_copy(curPlat->header.gfx.angle, &curPlat->oFaceAngleVec);
    }
}

void bhv_woodplat_col_init(void) {
    f32 height = woodplat_get_stack_height(o->prevObj);
    o->oCollisionDistance = height;

    o->header.gfx.scale[1] = height / 100.f;
}
