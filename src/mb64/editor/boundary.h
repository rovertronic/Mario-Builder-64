#pragma once

#include "types.h"

struct Object;

#define MB64_BOUNDARY_INNER_FLOOR   (1 << 0)
#define MB64_BOUNDARY_OUTER_FLOOR   (1 << 1)
#define MB64_BOUNDARY_INNER_WALLS   (1 << 2)
#define MB64_BOUNDARY_OUTER_WALLS   (1 << 3)
#define MB64_BOUNDARY_CEILING       (1 << 4)

extern u8 mb64_curr_boundary;

struct mb64_boundary_quad {
    s8 vtx[4][3];
    s8 u[2];
    s8 v[2];
    u8 uYScale;
    u8 vYScale;
    u8 flipUvs;
};

void generate_boundary_collision(void);
void process_boundary(u32 processRenderMode);
void render_water_plane(void);

void init_boundary_wall_objects(struct Object *parent);
void update_boundary_wall(struct Object *source);
