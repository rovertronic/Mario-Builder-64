#include "main.h"

#include "camera.h"
#include "grid.h"
#include "object.h"

#include "mb64/menu/engine.h"
#include "mb64/menu/misc.h"
#include "mb64/menu/settings.h"
#include "mb64/menu/toolbox.h"
#include "mb64/gfx/gfx.h"
#include "trajectory.h"
#include "boundary.h"
#include "mb64/file.h"


#include "boot/slidec.h"
#include "game/object_list_processor.h"
#include "game/level_update.h"
#include "game/main.h"
#include "behavior_data.h"
#include "game/puppyprint.h"
#include "game/mario.h"
#include "audio/external.h"
#include "game/object_helpers.h"
#include "game/camera.h"
#include "sounds.h"

u8 mb64_menu_state = MB64_MAKE_MAIN;
u8 mb64_level_action = MB64_LA_BUILD;
u8 mb64_mode = MB64_MODE_UNINITIALIZED;
u8 mb64_target_mode = MB64_MODE_MAKE;
s8 mb64_cursor_pos[3] = {32,8,32};

u8 mb64_place_mode = MB64_PM_NONE;

s8 mb64_id_selection = 0;
u8 mb64_rot_selection = 0;
s16 mb64_param_selection = 0;
s16 mb64_mat_selection = 0;

u8 mb64_curr_boundary = 0;
u8 mb64_upsidedown_tile = FALSE;

u8 mb64_lopt_costume = 0;

u8 mb64_lopt_seq[5] = {0,0,0,0,0};
u8 mb64_lopt_seq_seqtype = 0;
u8 mb64_lopt_seq_album = 0;
u8 mb64_lopt_seq_song = 0;
u8 mb64_lopt_coinstar_max = 0;

u8 mb64_lopt_envfx = 0;
u8 mb64_lopt_theme = 0;
u8 mb64_lopt_bg = 0;
u8 mb64_lopt_boundary_mat = 0;
u8 mb64_lopt_boundary = 0;
u8 mb64_lopt_boundary_height = 0;
u8 mb64_lopt_game = MB64_GAME_VANILLA;
u8 mb64_lopt_size = 0;
u8 mb64_lopt_template = 0;
u8 mb64_lopt_coinstar = 0;
u8 mb64_lopt_waterlevel = 0;
u8 mb64_lopt_secret = 0;

u8 mb64_prepare_level_screenshot = FALSE;
u8 mb64_do_save = FALSE;

s16 mb64_play_stars = 0;
s16 mb64_play_stars_max = 0;
u64 mb64_play_stars_bitfield = 0;
u32 mb64_play_badge_bitfield = 0;
u8 mb64_play_onoff = FALSE;
s16 mb64_play_s16_water_level = 0;
u32 mb64_play_speedrun_timer = 0;

void reset_play_state(void) {
    mb64_play_stars = 0;
    mb64_play_stars_bitfield = 0;
    mb64_play_badge_bitfield = 0;

    mb64_play_s16_water_level = -8224+(mb64_lopt_waterlevel*TILE_SIZE);
    gWDWWaterLevelChanging = FALSE;
    mb64_play_onoff = FALSE;

    mb64_play_speedrun_timer = 0;
}

void delete_tile_action(s8 pos[3]) {
    s16 index = -1;

    for (u32 i = 0; i < mb64_tile_count; i++) {
        if ((mb64_tile_data[i].x == pos[0])&&(mb64_tile_data[i].y == pos[1])&&(mb64_tile_data[i].z == pos[2])) {
            index = i;
            remove_terrain_data(pos);
            play_place_sound(SOUND_GENERAL_DOOR_INSERT_KEY | SOUND_VIBRATO);
            mb64_tile_count--;
        }
    }

    if (index != -1) {
        u32 tiletypeIndex = get_tiletype_index(mb64_tile_data[index].type, mb64_tile_data[index].mat);

        for (u32 i = tiletypeIndex + 1; i < ARRAY_COUNT(mb64_tile_data_indices); i++) {
            mb64_tile_data_indices[i]--;
        }
        for (u32 i = index; i < mb64_tile_count; i++) {
            mb64_tile_data[i] = mb64_tile_data[i+1];
        }
        delete_useless_cull_markers();
        generate_terrain_gfx();
    }

    for (u32 i=0;i<mb64_object_count;i++) {
        if ((mb64_object_data[i].x == pos[0])&&(mb64_object_data[i].y == pos[1])&&(mb64_object_data[i].z == pos[2])) {
            if (mb64_object_data[i].type == OBJECT_TYPE_MARIO_SPAWN) {
                show_error("Cannot delete spawn point!");
                break;
            }
            delete_object(i);
            i--;
            play_place_sound(SOUND_GENERAL_DOOR_INSERT_KEY | SOUND_VIBRATO);
        }
    }
}

void mb64_init(void) {
    load_level();
    if (mb64_level_action != MB64_LA_PLAY_LEVELS) {
        vec3_set(mb64_cursor_pos, 32, 8, 32);
        mb64_camera_foc[0] = GRID_TO_POS(32);
        mb64_camera_foc[1] = 0.0f;
        mb64_camera_foc[2] = GRID_TO_POS(32);
    }
}

void reload_bg(void) {
    void *srcStart = mb64_skybox_table[mb64_lopt_bg*2];
    void *srcEnd = mb64_skybox_table[mb64_lopt_bg*2+1];

    if (srcStart == NULL) {
        return;
    }

    u32 compSize = ALIGN16(srcEnd - srcStart);
    u8 *compressed = main_pool_alloc(compSize, MEMORY_POOL_RIGHT);

    if (compressed != NULL) {
        dma_read(compressed, srcStart, srcEnd);
        slidstart(compressed, get_segment_base_addr(SEGMENT_SKYBOX));
        sSegmentROMTable[SEGMENT_SKYBOX] = (uintptr_t) srcStart;
        main_pool_free(compressed);
    }

    generate_terrain_gfx();
}

void reload_boundary_and_gfx(void) {
    generate_terrain_gfx();
    generate_boundary_collision();
}

void sb_init(void) {
    struct Object *spawn_obj;

    reload_bg();
    reload_boundary_and_gfx();

    switch(mb64_mode) {
        case MB64_MODE_MAKE:
            mb64_menu_state = MB64_MAKE_MAIN;
            o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            generate_object_preview();

            init_boundary_wall_objects(o);

            play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, seq_musicmenu_array[mb64_lopt_seq[0]]), 0);
            create_toolbar();
            create_coord_display();
            break;
        case MB64_MODE_PLAY:
            mb64_menu_state = MB64_MAKE_PLAY;
            reset_rng();
            gGlobalTimer = 0;
            generate_objects_to_level();

            spawn_obj = cur_obj_nearest_object_with_behavior(bhvSpawn);
            if (spawn_obj) {
                if (mb64_level_action == MB64_LA_BUILD) {
                    gMarioState->pos[0] = (f32)(GRID_TO_POS(mb64_cursor_pos[0]));
                    gMarioState->pos[1] = (f32)(GRID_TO_POS(mb64_cursor_pos[1]));
                    gMarioState->pos[2] = (f32)(GRID_TO_POS(mb64_cursor_pos[2]));
                    set_mario_action(gMarioState,ACT_IDLE,0);
                    gMarioState->faceAngle[1] = mb64_rot_selection*0x4000;
                } else {
                    gMarioState->faceAngle[1] = spawn_obj->oFaceAngleYaw;
                    vec3_copy(gMarioState->pos,&spawn_obj->oPosVec);
                    set_mario_action(gMarioState,ACT_SPAWN_SPIN_AIRBORNE,0);
                }
                gMarioState->pos[1] -= TILE_SIZE/2;

                reset_camera(gCurrentArea->camera);

                struct Object *warpobj = cur_obj_nearest_object_with_behavior(bhvSpinAirborneWarp);
                if (warpobj) {
                    vec3_copy(&warpobj->oPosVec,&spawn_obj->oPosVec);
                    warpobj->oPosY -= TILE_SIZE/2;
                }
            }

            o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;

            play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, seq_musicmenu_array[mb64_lopt_seq[0]]), 0);

        break;
    }
}

void update_custom_theme(void) {
    for (u32 i = 0; i < NUM_MATERIALS_PER_THEME; i++) {
        mb64_theme_table[MB64_THEME_CUSTOM].mats[i].mat = mb64_curr_custom_theme.mats[i];
        if (mb64_curr_custom_theme.topmatsEnabled[i]) {
            mb64_theme_table[MB64_THEME_CUSTOM].mats[i].topmat = mb64_curr_custom_theme.topmats[i];
        } else {
            mb64_theme_table[MB64_THEME_CUSTOM].mats[i].topmat = mb64_curr_custom_theme.mats[i];
        }
    }
    mb64_theme_table[MB64_THEME_CUSTOM].fence = mb64_curr_custom_theme.fence;
    mb64_theme_table[MB64_THEME_CUSTOM].pole = mb64_curr_custom_theme.pole;
    mb64_theme_table[MB64_THEME_CUSTOM].bars = mb64_curr_custom_theme.bars;
    mb64_theme_table[MB64_THEME_CUSTOM].water = mb64_curr_custom_theme.water;
}

void reload_theme(void) {
    reload_boundary_and_gfx();
    generate_object_preview();
}

static u8 sPrevPreviewID;
static u8 sPrevPreviewParam;

void sb_loop(void) {
    Vec3f cam_pos_offset = {0.0f,mb64_current_camera_zoom[1],0};
    u8 cursorMoved = FALSE;

    if (mb64_do_save) {
        mb64_do_save = FALSE;
        save_level();
    }

    mb64_camera_angle = approach_s16_asymptotic(mb64_camera_angle,mb64_camera_rot_offset*0x4000,4);
    cam_pos_offset[0] = sins(mb64_camera_angle+0x8000)*mb64_current_camera_zoom[0];
    cam_pos_offset[2] = coss(mb64_camera_angle+0x8000)*mb64_current_camera_zoom[0];

    mb64_current_camera_zoom[0] = lerp(mb64_current_camera_zoom[0], mb64_camera_zoom_table[mb64_camera_zoom_index][0],0.2f);
    mb64_current_camera_zoom[1] = lerp(mb64_current_camera_zoom[1], mb64_camera_zoom_table[mb64_camera_zoom_index][1],0.2f);

    switch(mb64_menu_state) {
        case MB64_MAKE_MAIN:
            ListComponent *toolbarlist = get_child(gToolbar);
            if (toolbarlist->base.inactive) {
                break;
            }
            cursorMoved = main_cursor_logic();

            if (cursorMoved || (sPrevPreviewID != mb64_id_selection) || (sPrevPreviewParam != mb64_param_selection)) {
                delete_preview_object();
            }
            sPrevPreviewID = mb64_id_selection;
            sPrevPreviewParam = mb64_param_selection;

            if (gPlayer1Controller->buttonPressed & Z_TRIG) {
                mb64_rot_selection = (mb64_rot_selection + 1) % 4;
                delete_preview_object();
            }

            if (mb64_place_mode == MB64_PM_ACTION) {
                if (gPlayer1Controller->buttonPressed & (A_BUTTON | START_BUTTON)) {
                    switch (mb64_id_selection) {
                        case OBJECT_TYPE_TEST_MARIO:
                            if ((!can_place(mb64_cursor_pos, OBJ_OCCUPY_INNER)) && !can_place(mb64_cursor_pos, OBJ_OCCUPY_OUTER)) {
                                show_error("Cannot start test here!");
                                break;
                            }
                            if (!gWarpTransition.isActive && sDelayedWarpOp == WARP_OP_NONE) {
                                if (gSDCard) {
                                    save_level();
                                }
                                toolbar_set_active(FALSE);
                                mb64_target_mode = MB64_MODE_PLAY;
                                reset_play_state();
                                level_trigger_warp(gMarioState, WARP_OP_LOOK_UP);
                                sSourceWarpNodeId = 0x0A;
                                play_sound(SOUND_MENU_STAR_SOUND_LETS_A_GO, gGlobalSoundSource);
                            }
                            break;
                        case OBJECT_TYPE_SETTINGS:
                            mb64_menu_state = MB64_MAKE_SETTINGS;
                            hide_toolbar();
                            hide_coord_display();
                            settings_menu_create();
                            play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                            break;
                    }
                }
            } else {
                if (gPlayer1Controller->buttonPressed & A_BUTTON || ((gPlayer1Controller->buttonDown & A_BUTTON) && cursorMoved)) {
                    place_thing_action();
                }
            }

            if (gPlayer1Controller->buttonPressed & B_BUTTON || ((gPlayer1Controller->buttonDown & B_BUTTON) && cursorMoved)) {
                delete_tile_action(mb64_cursor_pos);
            }

            if (gPlayer1Controller->buttonPressed & START_BUTTON && (mb64_place_mode != MB64_PM_ACTION)) {
                mb64_menu_state = MB64_MAKE_TOOLBOX;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                create_toolbox();
                hide_coord_display();
                delete_preview_object();
            }

            struct Object *spawnobjp = get_spawn_preview_object();
            if (mb64_prepare_level_screenshot) {
                o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
                if (spawnobjp) spawnobjp->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            } else {
                o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
                if (spawnobjp) spawnobjp->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            }

            update_boundary_wall(o);
            break;
        case MB64_MAKE_TOOLBOX:
            delete_preview_object();
            break;
        case MB64_MAKE_TRAJECTORY:
            delete_preview_object();
            cursorMoved = main_cursor_logic();

            if (cursorMoved) {
                generate_trajectory_gfx();
            }

            sb_edit_trajectory();

            update_boundary_wall(o);
            break;
        case MB64_MAKE_SCREENSHOT:
            o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            freecam_camera_main();
            update_boundary_wall(o);
            break;
    }

    if (mb64_menu_state == MB64_MAKE_MAIN || mb64_menu_state == MB64_MAKE_SETTINGS || mb64_menu_state == MB64_MAKE_TOOLBOX) {
        struct Object *previewObj = cur_obj_nearest_object_with_behavior(bhvCurrPreviewObject);
        if (!previewObj) {
            s8 pos[3];
            vec3_set(pos, mb64_cursor_pos[0], mb64_cursor_pos[1], mb64_cursor_pos[2]);

            if (mb64_place_mode != MB64_PM_TILE) {
                struct mb64_object_info *info = &mb64_object_type_list[mb64_id_selection];
                spawn_preview_object(pos, mb64_rot_selection, mb64_param_selection, info, bhvCurrPreviewObject);
            } else if (mb64_id_selection == TILE_TYPE_CULL) {
                spawn_preview_object(pos, mb64_rot_selection, 0, &mb64_object_type_list[OBJECT_TYPE_CULL_PREVIEW], bhvCurrPreviewObject);
            }
        }
    }

    if (mb64_menu_state != MB64_MAKE_SCREENSHOT) {
        mb64_camera_foc[0] = lerp(mb64_camera_foc[0], GRID_TO_POS(mb64_cursor_pos[0]),  0.2f);
        mb64_camera_foc[1] = lerp(mb64_camera_foc[1], GRID_TO_POS(mb64_cursor_pos[1]), 0.2f);
        mb64_camera_foc[2] = lerp(mb64_camera_foc[2], GRID_TO_POS(mb64_cursor_pos[2]),  0.2f);

        vec3_copy(mb64_camera_pos,mb64_camera_foc);
        vec3_add(mb64_camera_pos,cam_pos_offset);
    }
}

void play_mb64_extra_music(u8 index) {
    if (seq_musicmenu_array[mb64_lopt_seq[index]] != seq_musicmenu_array[mb64_lopt_seq[0]]) {
        play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, seq_musicmenu_array[mb64_lopt_seq[index]]), 0);
    }
}

void stop_mb64_extra_music(u8 index) {
    if (seq_musicmenu_array[mb64_lopt_seq[index]] != seq_musicmenu_array[mb64_lopt_seq[0]]) {
        stop_background_music(SEQUENCE_ARGS(4, seq_musicmenu_array[mb64_lopt_seq[index]]));
    }
}
