#include "main.h"
#include "trajectory.h"
#include "gfx.h"
#include "menu.h"

#include <PR/gbi.h>
#include "game/game_init.h"
#include "game/object_list_processor.h"
#include "actors/maker/header.h"
#include "engine/math_util.h"

Trajectory mb64_trajectory_list[MB64_MAX_TRAJECTORIES][MB64_TRAJECTORY_LENGTH][4];
u16 mb64_trajectory_edit_index = 0;
u8 mb64_trajectory_to_edit = 0;
u8 mb64_trajectories_used = 0;

void init_trajectories(void) {
    mb64_trajectories_used = 0;
    for (int i = 0; i < mb64_object_count; i++) {
        if (mb64_object_type_list[mb64_object_data[i].type].flags & OBJ_TYPE_TRAJECTORY) {
            mb64_trajectories_used++;
        }
    }

    for (int i = 0; i < MB64_MAX_TRAJECTORIES; i++) {
        for (int j = 0; j < MB64_TRAJECTORY_LENGTH; j++) {
            mb64_trajectory_list[i][j][0] = mb64_save.trajectories[i][j].t;
            mb64_trajectory_list[i][j][1] = GRID_TO_POS(mb64_save.trajectories[i][j].x);
            mb64_trajectory_list[i][j][2] = GRID_TO_POS(mb64_save.trajectories[i][j].y);
            mb64_trajectory_list[i][j][3] = GRID_TO_POS(mb64_save.trajectories[i][j].z);
        }
    }
}

void begin_editing_trajectory(void) {
    mb64_trajectory_to_edit = mb64_trajectories_used;
    mb64_object_data[mb64_object_count].bparam = mb64_trajectories_used;
    mb64_trajectories_used++;

    mb64_menu_state = MB64_MAKE_TRAJECTORY;
    create_yellow_text("Building path in progress!\n\n\x10: Place waypoint\n\x11: Undo\nSTART: Confirm");
    toolbar_set_active(FALSE);

    mb64_trajectory_list[mb64_trajectory_to_edit][0][0] = -1;
    mb64_trajectory_edit_index = 0;
}

void remove_trajectory(u32 index) {
    // Scan all objects
    // If their trajectory index is past the one being deleted, lower it by 1
    for (u32 i = 0; i < mb64_object_count; i++) {
        if (mb64_object_type_list[mb64_object_data[i].type].flags & OBJ_TYPE_TRAJECTORY) {
            if (mb64_object_data[i].bparam > index) {
                mb64_object_data[i].bparam--;
            }
        }
    }
    // Move trajectories back by one
    for (s32 i = index; i < mb64_trajectories_used - 1; i++) {
        bcopy(mb64_trajectory_list[i + 1], mb64_trajectory_list[i], sizeof(mb64_trajectory_list[0]));
    }
    // Zero out the last one
    bzero(mb64_trajectory_list[mb64_trajectories_used - 1], sizeof(mb64_trajectory_list[0]));
    mb64_trajectories_used--;
}

u32 trajectory_get_target_angle(s16 *yaw, s16 prevWaypoint[4], s16 targetWaypoint[4]);
void rotate_obj_toward_trajectory_angle(struct Object * obj, u32 traj_id) {
    if ((mb64_trajectory_list[traj_id][0][0] == -1)||(mb64_trajectory_list[traj_id][1][0] == -1)) return;

    s16 angle_to_trajectory;
    if (!trajectory_get_target_angle(&angle_to_trajectory, mb64_trajectory_list[traj_id][0], mb64_trajectory_list[traj_id][1])) {
        return;
    }

    if ( obj_has_model(obj ,MODEL_CHECKERBOARD_PLATFORM) ) {
        angle_to_trajectory += 0x4000;
    }

    obj->oFaceAngleYaw = angle_to_trajectory;
    obj->oMoveAngleYaw = angle_to_trajectory;
}

Gfx *mb64_trajectory_gfx;
Vtx *mb64_trajectory_vtx;

void generate_trajectory_gfx(void) {
    mb64_curr_gfx = mb64_trajectory_gfx;
    mb64_curr_vtx = mb64_trajectory_vtx;
    mb64_gfx_index = 0;
    gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], mat_maker_MakerLineMat_layer1);

    for (s32 traj = 0; traj < mb64_trajectories_used; traj++) {
        Trajectory (*curr_trajectory)[4] = mb64_trajectory_list[traj];
        if (curr_trajectory[0][0] == -1) continue;
        s16 pos1[3], pos2[3];
        s32 isLoop = FALSE;

        // Find object corresponding to this trajectory
        for (s32 i = 0; i < mb64_object_count; i++) {
            if (mb64_object_type_list[mb64_object_data[i].type].flags & OBJ_TYPE_TRAJECTORY) {
                if (mb64_object_data[i].bparam == traj) {
                    // Check if it loops or not
                    if (mb64_object_data[i].type == OBJECT_TYPE_PLATFORM_LOOPING) {
                        isLoop = TRUE;
                        gDPSetPrimColor(&mb64_curr_gfx[mb64_gfx_index++], 0, 0, 0, 0, 255, 255);
                    } else {
                        gDPSetPrimColor(&mb64_curr_gfx[mb64_gfx_index++], 0, 0, 255, 255, 0, 255);
                    }
                    break;
                }
            }
        }
        s32 i;
        for (i = 0; curr_trajectory[i+1][0] == i+1; i++) {
            vec3_set(pos1, curr_trajectory[i][1], curr_trajectory[i][2], curr_trajectory[i][3]);
            vec3_set(pos2, curr_trajectory[i+1][1], curr_trajectory[i+1][2], curr_trajectory[i+1][3]);
            draw_dotted_line(pos1, pos2);
        }
        if (traj == mb64_trajectory_to_edit && mb64_menu_state == MB64_MAKE_TRAJECTORY) {
            vec3_set(pos1, curr_trajectory[i][1], curr_trajectory[i][2], curr_trajectory[i][3]);
            vec3_set(pos2, GRID_TO_POS(mb64_cursor_pos[0]), GRID_TO_POS(mb64_cursor_pos[1]), GRID_TO_POS(mb64_cursor_pos[2]));
            draw_dotted_line(pos1, pos2);
        }
        if (isLoop) {
            vec3_set(pos1, curr_trajectory[0][1], curr_trajectory[0][2], curr_trajectory[0][3]);
            draw_dotted_line(pos2, pos1);
        }
        display_cached_tris();
    }

    gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], mat_revert_maker_MakerLineMat_layer1);
    gSPEndDisplayList(&mb64_curr_gfx[mb64_gfx_index]);
}

void sb_edit_trajectory(void) {
    if (mb64_trajectory_edit_index == 0) {
        // Initial placement on top of the object
        mb64_trajectory_list[mb64_trajectory_to_edit][0][0] = 0;
        mb64_trajectory_list[mb64_trajectory_to_edit][0][1] = o->oPosX;
        mb64_trajectory_list[mb64_trajectory_to_edit][0][2] = o->oPosY;
        mb64_trajectory_list[mb64_trajectory_to_edit][0][3] = o->oPosZ;
        mb64_trajectory_list[mb64_trajectory_to_edit][1][0] = -1;
        mb64_trajectory_edit_index++; 
    } else {
        if (gPlayer1Controller->buttonPressed & A_BUTTON) {
            if (mb64_trajectory_edit_index == MB64_TRAJECTORY_LENGTH - 1) {
                show_error("Maximum trajectory length reached! (max 50)");
            // i fucking hate this, worst code ever. this hopefully won't have floating point inaccuracies
            } else if (mb64_trajectory_list[mb64_trajectory_to_edit][mb64_trajectory_edit_index - 1][1] == o->oPosX
                    && mb64_trajectory_list[mb64_trajectory_to_edit][mb64_trajectory_edit_index - 1][2] == o->oPosY
                    && mb64_trajectory_list[mb64_trajectory_to_edit][mb64_trajectory_edit_index - 1][3] == o->oPosZ) {
                show_error("");
            } else {
                mb64_trajectory_list[mb64_trajectory_to_edit][mb64_trajectory_edit_index][0] = mb64_trajectory_edit_index;
                mb64_trajectory_list[mb64_trajectory_to_edit][mb64_trajectory_edit_index][1] = o->oPosX;
                mb64_trajectory_list[mb64_trajectory_to_edit][mb64_trajectory_edit_index][2] = o->oPosY;
                mb64_trajectory_list[mb64_trajectory_to_edit][mb64_trajectory_edit_index][3] = o->oPosZ;
                mb64_trajectory_list[mb64_trajectory_to_edit][mb64_trajectory_edit_index+1][0] = -1;
                mb64_trajectory_edit_index++;
                play_place_sound(SOUND_MENU_CLICK_FILE_SELECT | SOUND_VIBRATO);
                generate_object_preview();
            }
        } else if (gPlayer1Controller->buttonPressed & B_BUTTON) {
            if (mb64_trajectory_edit_index <= 1) {
                show_error("Nothing to delete!");
            } else {
                mb64_trajectory_edit_index--;
                mb64_trajectory_list[mb64_trajectory_to_edit][mb64_trajectory_edit_index][0] = -1;
                play_place_sound(SOUND_GENERAL_DOOR_INSERT_KEY | SOUND_VIBRATO);
                generate_object_preview();
            }
        }
    }

    if (gPlayer1Controller->buttonPressed & START_BUTTON) {
        if (mb64_trajectory_edit_index == 1) {
            show_error("Trajectory is too short!");
        } else {
            mb64_menu_state = MB64_MAKE_MAIN;
            generate_object_preview();
            destroy_yellow_text();
            toolbar_set_active(TRUE);
        }
    }
}
