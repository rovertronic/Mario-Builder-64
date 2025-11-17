#pragma once

#include "types.h"

extern Gfx *mb64_trajectory_gfx;
extern Vtx *mb64_trajectory_vtx;

extern u8 mb64_trajectories_used;

extern struct Waypoint mb64_trajectory_list[MB64_MAX_TRAJECTORIES][MB64_TRAJECTORY_LENGTH];
void rotate_obj_toward_trajectory_angle(struct Object * obj, u32 traj_id);

void init_trajectories(void);
void begin_editing_trajectory(void);
void remove_trajectory(u32 index);
void generate_trajectory_gfx(void);
void sb_edit_trajectory(void);
