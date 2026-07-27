void bhv_podoboo_loop(void) {
    struct Surface *sp24;
    struct Object *spobj;
    u32 i;

    // Home X is where the Podoboo rests in the lava.
    // Home Y is the peak of the Podoboo's jump

    switch (o->oAction) {
        case 0: // Init
            o->oHomeX = find_floor(o->oPosX, o->oPosY, o->oPosZ, &sp24);
            o->oAction++;
            o->oFaceAngleRoll = 0x7FFF;
            o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            break;
        case 1: // Fall into lava
            o->oVelY -= 2.0f;
            o->oPosY += o->oVelY;

            // rotate back down
            if (o->oFaceAngleRoll < 0x7FFF) {
                o->oFaceAngleRoll += 0x0FFF;
            } else {
                o->oFaceAngleRoll = 0x7FFF;
            }

            if (o->oPosY < o->oHomeX) {
                for (i = 0; i < 3; i++) {
                    spobj = spawn_object(o, MODEL_RED_FLAME, bhvKoopaShellFlame);
                    spobj->oPosY += 40.0f;
                }
                cur_obj_play_sound_2(SOUND_OBJ_DIVING_INTO_WATER);
                o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
                o->oAction++;
                o->oTimer = 0;
                o->oPosY = o->oHomeX;
                o->oVelY = 0;
            }
            break;
        case 2: // Sit idle in lava
            cur_obj_become_intangible();
            // If mario is too far away, just break
            if (o->oDistanceToMario > 2500.0f) {
                o->oTimer = 0;
            }

            if (o->oTimer > 35) {
                spobj = spawn_object(o, MODEL_RED_FLAME, bhvKoopaShellFlame);
                spobj->oPosY += 40.0f;
            }

            if (o->oTimer > 50) {
                // Calculate upward velocity
                o->oHomeZ = o->oPosY;
                while (o->oHomeZ < o->oHomeY) {
                    o->oVelY += 1.5;
                    o->oHomeZ += o->oVelY;
                }
                cur_obj_become_tangible();
                o->oAction++;
                o->oFaceAngleRoll = 0x0;
                cur_obj_play_sound_2(SOUND_OBJ_FLAME_BLOWN);
                o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            }
            break;
        case 3: // New hop out
            o->oPosY += o->oVelY;
            o->oVelY -= 2.0f;

            if (o->oVelY < 0.0f) {
                o->oAction = 1;
            }
            break;
    }
}
