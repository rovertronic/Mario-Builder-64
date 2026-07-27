#include <PR/ultratypes.h>

#include "types.h"
#include "audio/external.h"
#include "behavior_actions.h"
#include "behavior_data.h"
#include "camera.h"
#include "debug.h"
#include "engine/behavior_script.h"
#include "engine/graph_node.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "game_init.h"
#include "ingame_menu.h"
#include "interaction.h"
#include "level_misc_macros.h"
#include "level_table.h"
#include "level_update.h"
#include "main.h"
#include "mario.h"
#include "mario_actions_cutscene.h"
#include "mario_step.h"
#include "obj_behaviors.h"
#include "obj_behaviors_2.h"
#include "object_constants.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "paintings.h"
#include "platform_displacement.h"
#include "rendering_graph_node.h"
#include "seq_ids.h"
#include "sm64.h"
#include "spawn_object.h"
#include "spawn_sound.h"
#include "rumble_init.h"
#include "object_collision.h"
#include "mb64/editor/object.h"
#include "mb64/editor/display_funcs.h"
#include "mb64/editor/main.h"
#include "include/config/config_objects.h"
#include "mb64/menu/dialog.h"

#include "behaviors/mr_i.inc.c"
#include "behaviors/king_bobomb.inc.c"
#include "behaviors/water_objs.inc.c"
#include "behaviors/chuckya.inc.c"
#include "behaviors/koopa_shell_underwater.inc.c"
#include "behaviors/warp.inc.c"
#include "behaviors/white_puff_explode.inc.c"
#include "actors/common1.h"
#include "actors/group0.h"
#include "area.h"
#include "engine/surface_load.h"

// not in behavior file
static struct SpawnParticlesInfo sMistParticles = {
    /* behParam:        */ 2,
    /* count:           */ 20,
    /* model:           */ MODEL_MIST,
    /* offsetY:         */ 0,
    /* forwardVelBase:  */ 40,
    /* forwardVelRange: */ 5,
    /* velYBase:        */ 30,
    /* velYRange:       */ 20,
    /* gravity:         */ 252,
    /* dragStrength:    */ 30,
    /* sizeBase:        */ 330.0f,
    /* sizeRange:       */ 10.0f,
};

// generate_wind_puffs/dust (something like that)
void spawn_mist_particles_variable(s32 count, s32 offsetY, f32 size) {
    sMistParticles.sizeBase = size;
    sMistParticles.sizeRange = size / 20.0f;
    sMistParticles.offsetY = offsetY;

    if (count == 0) {
        sMistParticles.count = 20;
    } else if (count > 20) {
        sMistParticles.count = count;
    } else {
        sMistParticles.count = 4;
    }

    cur_obj_spawn_particles(&sMistParticles);
}

#include "behaviors/sparkle_spawn_star.inc.c"
#include "behaviors/coin.inc.c"
#include "behaviors/collide_particles.inc.c"
#include "behaviors/door.inc.c"
#include "behaviors/thwomp.inc.c"
#include "behaviors/water_mist_particle.inc.c"
#include "behaviors/break_particles.inc.c"
#include "behaviors/water_mist.inc.c"
#include "behaviors/ground_particles.inc.c"
#include "behaviors/flamethrower.inc.c"
#include "behaviors/bouncing_fireball.inc.c"
#include "behaviors/shock_wave.inc.c"
#include "behaviors/flame_mario.inc.c"
#include "behaviors/beta_fish_splash_spawner.inc.c"
#include "behaviors/spindrift.inc.c"
#include "behaviors/tree_particles.inc.c"
#include "behaviors/piranha_bubbles.inc.c"
#include "behaviors/purple_switch.inc.c"
#include "behaviors/breakable_box.inc.c"

// not sure what this is doing here. not in a behavior file.
Gfx *geo_move_mario_part_from_parent(s32 callContext, UNUSED struct GraphNode *node, Mat4 mtx) {

    if (callContext == GEO_CONTEXT_RENDER) {
        struct Object *obj = (struct Object *) gCurGraphNodeObject;
        if (obj == gMarioObject && obj->prevObj != NULL) {
            obj_update_pos_from_parent_transformation(mtx, obj->prevObj);
            obj_set_gfx_pos_from_pos(obj->prevObj);
        }
    }

    return NULL;
}

#include "behaviors/heave_ho.inc.c"
#include "behaviors/spawn_star_exit.inc.c"
#include "behaviors/jumping_box.inc.c"

// not in behavior file
// n is the number of objects to spawn, r if the rate of change of phase (frequency?)
void spawn_sparkle_particles(s32 n, s32 radius, s32 height, s32 r) {
    static s16 spawnSparkleParticleAngle = 0x0;
    s32 i;
    s16 separation = 0x10000 / n; // Evenly spread around a circle

    for (i = 0; i < n; i++) {
        spawn_object_relative(OBJ_BP_NONE, sins(spawnSparkleParticleAngle + i * separation) * radius, (i + 1) * height,
                              coss(spawnSparkleParticleAngle + i * separation) * radius, o, MODEL_NONE, bhvSparkleSpawn);
    }

    spawnSparkleParticleAngle += r * 0x100;
}

#include "behaviors/bullet_bill.inc.c"
#include "behaviors/bowser.inc.c"
#include "behaviors/bowser_flame.inc.c"
#include "behaviors/lll_rotating_hex_flame.inc.c"
#include "behaviors/cosmic_phantasm.inc.c"
#include "behaviors/showrunner.inc.c"
#include "behaviors/podoboo.inc.c"
#include "behaviors/noteblock.inc.c"
#include "behaviors/tree.inc.c"
#include "behaviors/badge.inc.c"
#include "behaviors/onoff.inc.c"
#include "behaviors/woodplat.inc.c"
#include "behaviors/crush_handler.inc.c"
#include "behaviors/conveyor.inc.c"
#include "behaviors/piranha_plant.inc.c"

void set_obj_anim_with_accel_and_sound(s16 frame1, s16 frame2, s32 sound) {
    s32 range = o->header.gfx.animInfo.animAccel / 0x10000;
    if (range == 0) {
        range = 1;
    }

    if (cur_obj_check_anim_frame_in_range(frame1, range) || cur_obj_check_anim_frame_in_range(frame2, range)) {
        cur_obj_play_sound_2(sound);
    }
}

#include "behaviors/tuxie.inc.c"
#include "behaviors/exclamation_box.inc.c"
#include "behaviors/sound_spawner.inc.c"
#include "behaviors/white_puff.inc.c"
#include "behaviors/blue_coin.inc.c"
#include "behaviors/wdw_water_level.inc.c"
#include "behaviors/boo.inc.c"
#include "behaviors/pole_base.inc.c"
#include "behaviors/sparkle_spawn.inc.c"
#include "behaviors/scuttlebug.inc.c" // :scuttleeyes:
#include "behaviors/whomp.inc.c"
#include "behaviors/water_splashes_and_waves.inc.c"

u8 MouthOpen;

Gfx *geo_rotate_signjaw1(s32 run, struct GraphNode *node) {
    if (run == TRUE) {
        if (MouthOpen == FALSE) {
            if (((struct GraphNodeRotation *) node->next)->rotation[2] > -0x4000) {
                ((struct GraphNodeRotation *) node->next)->rotation[2] -= 0x400;
                }
            }
            else
            {
            if (((struct GraphNodeRotation *) node->next)->rotation[2] < 0x3000) {
                ((struct GraphNodeRotation *) node->next)->rotation[2] += 0x400;
                }
            }
    }
    return 0;
}

Gfx *geo_rotate_signjaw2(s32 run, struct GraphNode *node) {
    if (run == TRUE) {
        if (MouthOpen == TRUE) {
            if (((struct GraphNodeRotation *) node->next)->rotation[2] > -0x3000) {
                ((struct GraphNodeRotation *) node->next)->rotation[2] -= 0x400;
                }
            }
            else
            {
            if (((struct GraphNodeRotation *) node->next)->rotation[2] < 0x4000) {
                ((struct GraphNodeRotation *) node->next)->rotation[2] += 0x400;
                }
            }
    }
    return 0;
}
