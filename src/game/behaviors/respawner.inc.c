// respawner.inc.c

void bhv_respawner_loop(void) {
    struct Object *spawnedObject;
    if (o->oAction == 0) return;
    if (!is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, o->oRespawnerMinSpawnDist)) {
        spawnedObject = spawn_object(o, o->oRespawnerModelToRespawn, o->oRespawnerBehaviorToRespawn);
        spawnedObject->oBehParams = o->oBehParams;
        spawnedObject->oImbue = o->oImbue;
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

void create_respawner(ModelID32 model, const BehaviorScript *behToSpawn, s32 minSpawnDist) {
    struct Object *respawner = spawn_object_abs_with_rot(o, 0, MODEL_NONE, bhvRespawner, o->oHomeX, o->oHomeY, o->oHomeZ, 0, 0, 0);
    respawner->oRespawnerModelToRespawn = model;
    respawner->oRespawnerMinSpawnDist = minSpawnDist;
    respawner->oRespawnerBehaviorToRespawn = behToSpawn;
    respawner->oAction = 0;
}

void cur_obj_trigger_respawner() {
    // Search all respawner objects
    uintptr_t *behaviorAddr = segmented_to_virtual(bhvRespawner);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *obj = (struct Object *) listHead->next;

    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr && obj->parentObj == o) {
            obj->oAction = 1;
            obj->oBehParams = o->oBehParams;
            obj->oImbue = o->oImbue;
        }

        obj = (struct Object *) obj->header.next;
    }
}
