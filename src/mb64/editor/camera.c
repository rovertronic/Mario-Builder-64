#include "camera.h"

#include "main.h"
#include "grid.h"
#include "object.h"
#include "mb64/file.h"

#include "mb64/menu/misc.h"
#include "mb64/menu/toolbox.h"

#include "game/object_list_processor.h"
#include "game/main.h"
#include "game/level_update.h"
#include "audio/external.h"

Vec3f mb64_camera_pos = {0.0f,0.0f,0.0f};
Vec3f mb64_camera_pos_prev;
Vec3f mb64_camera_foc = {0.0f,0.0f,0.0f};
f32 mb64_camera_fov = 45.0f;
s16 mb64_camera_angle = 0;
u8 mb64_camera_rot_offset = 0;
s8 mb64_camera_zoom_index = 2;
f32 mb64_camera_zoom_table[][2] = {
    {900.0f,50.0f},
    {900.0f,400.0f},
    {1500.0f,800.0f},
    {2000.0f,900.0f},
    {2100.0f,1500.0f},
};
f32 mb64_current_camera_zoom[2] = {1500.0f,800.0f};
s16 mb64_freecam_pitch;
s16 mb64_freecam_yaw;
u8 mb64_freecam_snap = FALSE;
u8 mb64_freecam_snap_timer = 0;

static u8 c_button_timer = 0;
static u8 cursor_wrap = FALSE;
static u8 mb64_joystick_timer = 0;

s32 snap_cursor(void) {
    s32 gridmax = mb64_grid_min + mb64_grid_size - 1;
    s32 gridymax = (mb64_curr_boundary & MB64_BOUNDARY_CEILING) ? mb64_lopt_boundary_height-1 : 63;
    if (mb64_cursor_pos[0] < mb64_grid_min) {mb64_cursor_pos[0] = mb64_grid_min; return TRUE;}
    if (mb64_cursor_pos[0] > gridmax) {mb64_cursor_pos[0] = gridmax; return TRUE;}
    if (mb64_cursor_pos[2] < mb64_grid_min) {mb64_cursor_pos[2] = mb64_grid_min; return TRUE;}
    if (mb64_cursor_pos[2] > gridmax) {mb64_cursor_pos[2] = gridmax; return TRUE;}
    if (mb64_cursor_pos[1] < 0) {mb64_cursor_pos[1] = 0; return TRUE;}
    if (mb64_cursor_pos[1] > gridymax) {mb64_cursor_pos[1] = gridymax; return TRUE;}
    return FALSE;
}

void wrap_cursor(void) {
    s32 gridmax = mb64_grid_min + mb64_grid_size - 1;
    s32 gridymax = (mb64_curr_boundary & MB64_BOUNDARY_CEILING) ? mb64_lopt_boundary_height-1 : 63;
    if (mb64_cursor_pos[0] < mb64_grid_min) {mb64_cursor_pos[0] = gridmax; return;}
    if (mb64_cursor_pos[0] > gridmax) {mb64_cursor_pos[0] = mb64_grid_min; return;}
    if (mb64_cursor_pos[2] < mb64_grid_min) {mb64_cursor_pos[2] = gridmax; return;}
    if (mb64_cursor_pos[2] > gridmax) {mb64_cursor_pos[2] = mb64_grid_min; return;}
    if (mb64_cursor_pos[1] < 0) {mb64_cursor_pos[1] = gridymax; return;}
    if (mb64_cursor_pos[1] > gridymax) {mb64_cursor_pos[1] = 0; return;}
}

u32 main_cursor_logic(void) {
    u8 cursorMoved = FALSE;
    int joystick = 0;

    if (mb64_joystick_timer > 0) {
        mb64_joystick_timer--;
    }

    if ((gPlayer1Controller->rawStickX < 10)&&(gPlayer1Controller->rawStickX > -10)&&(gPlayer1Controller->rawStickY < 10)&&(gPlayer1Controller->rawStickY > -10)) {
        mb64_joystick_timer = 0;
    }

    if (mb64_joystick_timer == 0) {
        if (gPlayer1Controller->rawStickX > 60) {
            mb64_joystick_timer = 5;
            joystick = 3;
        } else if (gPlayer1Controller->rawStickX < -60) {
            mb64_joystick_timer = 5;
            joystick = 1;
        } else if (gPlayer1Controller->rawStickY > 60) {
            mb64_joystick_timer = 5;
            joystick = 4;
        } else if (gPlayer1Controller->rawStickY < -60) {
            mb64_joystick_timer = 5;
            joystick = 2;
        }
    }

    if (sDelayedWarpOp == WARP_OP_NONE) {
        if (joystick != 0) {
            switch(((joystick-1)+mb64_camera_rot_offset)%4) {
                case 0:
                    mb64_cursor_pos[0]++;
                    cursorMoved = TRUE;
                break;
                case 1:
                    mb64_cursor_pos[2]--;
                    cursorMoved = TRUE;
                break;
                case 2:
                    mb64_cursor_pos[0]--;
                    cursorMoved = TRUE;
                break;
                case 3:
                    mb64_cursor_pos[2]++;
                    cursorMoved = TRUE;
                break;
            }
        }

        c_button_timer ++;
        if (!(gPlayer1Controller->buttonDown & (U_CBUTTONS|D_CBUTTONS))) {
            c_button_timer = 0;
        }

        if ((gPlayer1Controller->buttonDown & U_CBUTTONS)&&(c_button_timer%5 == 1)) {
            mb64_cursor_pos[1]++;
            cursorMoved = TRUE;
        }
        if ((gPlayer1Controller->buttonDown & D_CBUTTONS)&&(c_button_timer%5 == 1)) {
            mb64_cursor_pos[1]--;
            cursorMoved = TRUE;
        }
    }
    if (gPlayer1Controller->buttonPressed & R_CBUTTONS) {
        mb64_camera_rot_offset++;
    }
    if (gPlayer1Controller->buttonPressed & L_CBUTTONS) {
        mb64_camera_rot_offset--;
    }
    mb64_camera_rot_offset = (mb64_camera_rot_offset % 4)+4;

    if (cursorMoved) {
        if (!cursor_wrap) {
           if (snap_cursor()) cursor_wrap = TRUE;
        } else {
            wrap_cursor();
            cursor_wrap = FALSE;
        }
    }

    if (gPlayer1Controller->buttonPressed & D_JPAD) {
        mb64_camera_zoom_index++;
    }
    mb64_camera_zoom_index = (mb64_camera_zoom_index+5)%5;

    o->oPosX = GRID_TO_POS(mb64_cursor_pos[0]);
    o->oPosY = GRID_TO_POS(mb64_cursor_pos[1]);
    o->oPosZ = GRID_TO_POS(mb64_cursor_pos[2]);

    return cursorMoved;
}

void freecam_camera_init(void) {
    vec3f_copy(mb64_camera_pos_prev,mb64_camera_pos);

    Vec3f d;
    vec3_diff(d, mb64_camera_pos, mb64_camera_foc);
    f32 xz = (sqr(d[0]) + sqr(d[2]));
    mb64_freecam_pitch = atan2s(sqrtf(xz), d[1]) + 0x4000;
    mb64_freecam_yaw = atan2s(d[2], d[0]);

    mb64_freecam_snap = FALSE;
    mb64_freecam_snap_timer = 0;
    mb64_prepare_level_screenshot = TRUE;
}

void freecam_return(void) {
    mb64_menu_state = MB64_MAKE_MAIN;
    mb64_camera_fov = 45.0f;
    mb64_prepare_level_screenshot = FALSE;
    mb64_freecam_snap = FALSE;
    vec3f_copy(mb64_camera_pos,mb64_camera_pos_prev);
    generate_object_preview();
    show_coord_display();
    destroy_yellow_text();

    show_toolbar();
    toolbar_set_active(TRUE);
}

void freecam_camera_main(void) {
    if (mb64_freecam_snap) {
        mb64_freecam_snap_timer++;
        if (mb64_freecam_snap_timer == 3) {
            play_sound(SOUND_MENU_CLICK_CHANGE_VIEW, gGlobalSoundSource);
            for (u8 i=0; i<16; i++) {
                osRecvMesg(&gGameVblankQueue, &gMainReceivedMesg, OS_MESG_BLOCK);
            }
            save_level();
        }
        if (mb64_freecam_snap_timer > 30) {
            freecam_return();
        }
        return;
    }

    mb64_freecam_yaw += gPlayer1Controller->rawStickX*-4;
    mb64_freecam_pitch += gPlayer1Controller->rawStickY*-4;

    if (mb64_freecam_pitch < 0x100) {
        mb64_freecam_pitch = 0x100;
    }
    if (mb64_freecam_pitch > 0x7000) {
        mb64_freecam_pitch = 0x7000;
    }

    if (gPlayer1Controller->buttonDown & U_CBUTTONS) {
        mb64_camera_pos[0] += ( sins(mb64_freecam_yaw) * -sins(mb64_freecam_pitch) * 45.0f );
        mb64_camera_pos[1] += ( coss(mb64_freecam_pitch) * 45.0f );
        mb64_camera_pos[2] += ( coss(mb64_freecam_yaw) * -sins(mb64_freecam_pitch) * 45.0f );
    }

    if (gPlayer1Controller->buttonDown & D_CBUTTONS) {
        mb64_camera_pos[0] += ( sins(mb64_freecam_yaw) * -sins(mb64_freecam_pitch) * -45.0f );
        mb64_camera_pos[1] += ( coss(mb64_freecam_pitch) * -45.0f );
        mb64_camera_pos[2] += ( coss(mb64_freecam_yaw) * -sins(mb64_freecam_pitch) * -45.0f );
    }

    if (gPlayer1Controller->buttonDown & R_CBUTTONS) {
        mb64_camera_pos[0] += ( sins(mb64_freecam_yaw + 0x4000) * 30.0f );
        mb64_camera_pos[2] += ( coss(mb64_freecam_yaw + 0x4000) * 30.0f );
    }

    if (gPlayer1Controller->buttonDown & L_CBUTTONS) {
        mb64_camera_pos[0] += ( sins(mb64_freecam_yaw - 0x4000) * 30.0f );
        mb64_camera_pos[2] += ( coss(mb64_freecam_yaw - 0x4000) * 30.0f );
    }

    if (gPlayer1Controller->buttonDown & L_TRIG) {
        mb64_camera_fov -= 1.0f;
        play_sound(SOUND_AIR_AMP_BUZZ, gGlobalSoundSource);

        if (mb64_camera_fov < 1.0f) {
            mb64_camera_fov = 1.0f;
        }
    }

    if (gPlayer1Controller->buttonDown & R_TRIG) {
        mb64_camera_fov += 1.0f;
        play_sound(SOUND_AIR_AMP_BUZZ, gGlobalSoundSource);

        if (mb64_camera_fov > 100.0f) {
            mb64_camera_fov = 100.0f;
        }
    }

    if (gPlayer1Controller->buttonPressed & START_BUTTON) {
        mb64_freecam_snap = TRUE;
    }

    if (gPlayer1Controller->buttonPressed & B_BUTTON) {
        freecam_return();
    }

    mb64_camera_foc[0] = mb64_camera_pos[0] + ( sins(mb64_freecam_yaw) * -sins(mb64_freecam_pitch) * 100.0f );
    mb64_camera_foc[1] = mb64_camera_pos[1] + ( coss(mb64_freecam_pitch) * 100.0f );
    mb64_camera_foc[2] = mb64_camera_pos[2] + ( coss(mb64_freecam_yaw) * -sins(mb64_freecam_pitch) * 100.0f );
}
