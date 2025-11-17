#include "main.h"
#include "collision.h"
#include "gfx.h"

#include "engine/surface_load.h"
#include "game/object_list_processor.h"
#include "game/mario_actions_automatic.h"
#include "behavior_data.h"
#include "engine/math_util.h"

TerrainData mb64_curr_coltype = SURFACE_DEFAULT;
u16 mb64_build_collision_type = 0; // 0 = none, 1 = floor, 2 = ceil, 3 = wall

u32 coords_in_range(s8 pos[3]) {
    if (pos[0] < mb64_grid_min || pos[0] > mb64_grid_min + mb64_grid_size - 1) return FALSE;
    if (pos[1] < 0 || pos[1] > 63) return FALSE;
    if (pos[2] < mb64_grid_min || pos[2] > mb64_grid_min + mb64_grid_size - 1) return FALSE;
    return TRUE;
}

// Create new static surface
struct Surface *alloc_surface();
void add_surface(struct Surface *surface, s32 dynamic);
void add_surface_to_cell(s32 type, s32 cellX, s32 cellZ, struct Surface *surface);

void mb64_create_surface(TerrainData v1[3], TerrainData v2[3], TerrainData v3[3], u32 isStatic) { 
    struct Surface *surface = alloc_surface();

    vec3_copy(surface->vertex1, v1);
    vec3_copy(surface->vertex2, v2);
    vec3_copy(surface->vertex3, v3);

    s16 min,max;
    min_max_3s(v1[1], v2[1], v3[1], &min, &max);
    surface->lowerY = (min - SURFACE_VERTICAL_BUFFER);
    surface->upperY = (max + SURFACE_VERTICAL_BUFFER);

    surface->type = mb64_curr_coltype;
    if (isStatic)
        add_surface(surface, FALSE);
    else
        add_surface_to_cell(2, 0, 0, surface); // 2 = block surface, cell parameters unused
};

TerrainData colVtxs[4][3];
void mb64_create_poly(struct mb64_terrain_poly *poly, s8 pos[3], u32 rot) {
    switch (mb64_build_collision_type) {
        case 1: // floors
            if (poly->faceDir != MB64_DIRECTION_UP) return;
            break;
        case 2: // ceils
            if (poly->faceDir != MB64_DIRECTION_DOWN) return;
            break;
        case 3: // walls
            if ((poly->faceDir == MB64_DIRECTION_DOWN) || (poly->faceDir == MB64_DIRECTION_UP)) return;
            break;
    }
    s8 newVtx[4][3];
    mb64_transform_vtx_with_rot(newVtx, poly->vtx, rot);
    for (u32 k = 0; k < mb64_curr_poly_vert_count; k++) {
        colVtxs[k][0] = GRID_TO_POS(pos[0]) + ((newVtx[k][0] - 8) * (TILE_SIZE/16)),
        colVtxs[k][1] = GRID_TO_POS(pos[1]) + ((newVtx[k][1] - 8) * (TILE_SIZE/16)),
        colVtxs[k][2] = GRID_TO_POS(pos[2]) + ((newVtx[k][2] - 8) * (TILE_SIZE/16));
    }
    mb64_create_surface(colVtxs[0], colVtxs[1], colVtxs[2], FALSE);
    if (mb64_curr_poly_vert_count == 4) {
        mb64_create_surface(colVtxs[1], colVtxs[3], colVtxs[2], FALSE);
    }
}

void generate_block_collision(s8 pos[3]) {
    if (!coords_in_range(pos)) return;
    s32 tileType = get_grid_tile(pos)->type;

    mb64_growth_render_type = 0;
    mb64_curr_poly_vert_count = 4;

    if (tileType == TILE_TYPE_FENCE) {
        if (gCollisionFlags & COLLISION_FLAG_CAMERA) return;
        mb64_curr_coltype = SURFACE_NO_CAM_COLLISION;
        process_tile(pos, &mb64_terrain_fence_col, get_grid_tile(pos)->rot);
        return;
    }

    if (tileType == TILE_TYPE_BARS) {
        if (gCollisionFlags & COLLISION_FLAG_CAMERA) return;
        u8 connections[5];
        mb64_curr_coltype = SURFACE_VANISH_CAP_WALLS;
        check_bar_connections(pos, connections);
        render_bars_side(pos, connections);
        render_bars_top(pos, connections);
        return;
    }

    if (tileType == TILE_TYPE_EMPTY || tileType >= TILE_TYPE_CULL) {
        return;
    }

    if (mb64_build_collision_type == 1) {
        mb64_growth_render_type = 1;
        mb64_curr_coltype = TOPMAT(get_grid_tile(pos)->mat).col;
    }
    else mb64_curr_coltype = MATERIAL(get_grid_tile(pos)->mat).col;

    process_tile(pos, mb64_terrain_info_list[tileType].terrain, get_grid_tile(pos)->rot);
}

void scan_fences(s8 pos[3]) {
    for (s32 dir = 2; dir < 6; dir++) {
        s8 newPos[3];
        vec3_sum(newPos, pos, cullOffsetLUT[dir]);
        if ((get_grid_tile(newPos)->type == TILE_TYPE_FENCE) && (rotate_direction(MB64_DIRECTION_POS_Z, get_grid_tile(newPos)->rot) == dir)) {
            generate_block_collision(newPos);
        }
    }
}

#define COL_POS_TO_GRID(pos) (((pos) + (32 * TILE_SIZE)) / TILE_SIZE)

#define begin_block_collision() { \
    gSurfacePool = gBlockSurfacePool; \
    gSurfaceNodePool = gBlockSurfaceNodePool; \
    gSurfacesAllocated = &gBlockSurfacesAllocated; \
    gSurfaceNodesAllocated = &gBlockSurfaceNodesAllocated; \
}
#define end_block_collision() { \
    gSurfacePool = gMainSurfacePool; \
    gSurfaceNodePool = gMainSurfaceNodePool; \
    gSurfacesAllocated = &gMainSurfacesAllocated; \
    gSurfaceNodesAllocated = &gMainSurfaceNodesAllocated; \
}


void block_floor_collision(f32 x, f32 y, f32 z) {
    s8 pos[3];
    mb64_build_collision_type = 1;

    pos[0] = COL_POS_TO_GRID(x);
    pos[1] = COL_POS_TO_GRID(y + FIND_FLOOR_BUFFER);
    pos[2] = COL_POS_TO_GRID(z);

    begin_block_collision();
    scan_fences(pos);
    generate_block_collision(pos);
    pos[1]--;

    while (pos[1] >= 0) {
        scan_fences(pos);
        generate_block_collision(pos);

        if (!coords_in_range(pos) || (gCollisionFlags & COLLISION_FLAG_SHORT_FLOOR_CHECK)) {
            break;
        }
        s32 faceshapeTop = get_faceshape(pos, MB64_DIRECTION_UP);
        s32 faceshapeBottom = get_faceshape(pos, MB64_DIRECTION_DOWN);
        if (faceshapeTop == MB64_FACESHAPE_FULL || faceshapeBottom == MB64_FACESHAPE_FULL) {
            // Tile covers entire block, so stop searching
            break;
        }
        pos[1]--;
    }

    end_block_collision();
}

void block_ceil_collision(f32 x, f32 y, f32 z) {
    s8 pos[3];
    mb64_build_collision_type = 2;

    pos[0] = COL_POS_TO_GRID(x);
    pos[1] = COL_POS_TO_GRID(y-5) + 1;
    pos[2] = COL_POS_TO_GRID(z);

    begin_block_collision();

    generate_block_collision(pos);
    pos[1]--;
    generate_block_collision(pos);

    end_block_collision();
}

void block_wall_collision(f32 x, f32 y, f32 z, f32 r) {
    s8 pos[3];
    mb64_build_collision_type = 3;

    s32 minx = COL_POS_TO_GRID(x - r);
    s32 maxx = COL_POS_TO_GRID(x + r);
    pos[1] = COL_POS_TO_GRID(y);
    s32 minz = COL_POS_TO_GRID(z - r);
    s32 maxz = COL_POS_TO_GRID(z + r);

    begin_block_collision();

    for (s32 x = minx; x <= maxx; x++) {
        pos[0] = x;
        for (s32 z = minz; z <= maxz; z++) {
            pos[2] = z;
            generate_block_collision(pos);
        }
    }

    end_block_collision();
}

u32 interact_pole(struct MarioState *m, UNUSED u32 interactType);
int check_pole(struct MarioState *m, s8 pos[3]) {
    if (get_grid_tile(pos)->type == TILE_TYPE_POLE) {
        f32 poleX = GRID_TO_POS(pos[0]);
        f32 poleZ = GRID_TO_POS(pos[2]);
        f32 horizDist = sqrtf(sqr(m->pos[0] - poleX) + sqr(m->pos[2] - poleZ));
        if (horizDist < 118) {
            // Get dimensions of pole
            s8 poleY = pos[1];
            do {
                pos[1]++;
            } while (pos[1] < 64 && get_grid_tile(pos)->type == TILE_TYPE_POLE);
            f32 poleTop = GRID_TO_POS(pos[1]) - TILE_SIZE/2;
            pos[1] = poleY;
            do {
                pos[1]--;
            } while (pos[1] >= 0 && get_grid_tile(pos)->type == TILE_TYPE_POLE);
            f32 poleBottom = GRID_TO_POS(pos[1]) + TILE_SIZE/2;

            gMarioCurrentPole.pos[0] = poleX;
            gMarioCurrentPole.pos[1] = poleBottom;
            gMarioCurrentPole.pos[2] = poleZ;
            gMarioCurrentPole.height = poleTop - poleBottom;
            gMarioCurrentPole.poleType = 0;
            interact_pole(m, 0);
            return TRUE;
        }
    }
    return FALSE;
}

void check_poles(struct MarioState *m) {
    s8 pos[3];

    pos[0] = COL_POS_TO_GRID(m->pos[0]);
    pos[1] = COL_POS_TO_GRID(m->pos[1]);
    pos[2] = COL_POS_TO_GRID(m->pos[2]);

    if (check_pole(m, pos)) return;

    s8 topPos = COL_POS_TO_GRID(m->pos[1] + 160);
    if (topPos != pos[1]) {
        pos[1] = topPos;
        if (check_pole(m, pos)) return;
    }

    // Iterate over polelike objects
    struct ObjectNode *listHead = &gObjectLists[OBJ_LIST_POLELIKE];
    struct Object *obj = (struct Object *) listHead->next;

    while (obj != (struct Object *) listHead) {
        f32 horizDist = sqrtf(sqr(m->pos[0] - obj->oPosX) + sqr(m->pos[2] - obj->oPosZ));
        if (horizDist < 118.f) {
            u16 poleHeight;
            u8 poleType = 0;
            if (obj->behavior == segmented_to_virtual(bhvTree)) {
                poleHeight = 500;
                poleType = (obj->oBehParams2ndByte == 2 ? 2 : 1);
            } else if (obj->behavior == segmented_to_virtual(bhvKoopaFlag)) {
                poleHeight = 700;
            } else {
                obj = (struct Object *) obj->header.next;
                continue;
            }
            if (m->pos[1] > obj->oPosY && m->pos[1] + 160.f < obj->oPosY + poleHeight) {
                gMarioCurrentPole.pos[0] = obj->oPosX;
                gMarioCurrentPole.pos[1] = obj->oPosY;
                gMarioCurrentPole.pos[2] = obj->oPosZ;
                gMarioCurrentPole.height = poleHeight;
                gMarioCurrentPole.poleType = poleType;
                interact_pole(m, 0);
                return;
            }
        }

        obj = (struct Object *) obj->header.next;
    }
}

s32 mb64_get_water_level(s32 x, s32 y, s32 z) {
    //(mb64_lopt_waterlevel - 32) * TILE_SIZE - (TILE_SIZE / 8)
    y += 10;
    s32 waterPlaneHeight = (mb64_lopt_waterlevel == 0 ? FLOOR_LOWER_LIMIT : mb64_play_s16_water_level);
    if (y < waterPlaneHeight) {
        return waterPlaneHeight;
    }
    // Convert world coordinates into grid coordinates
    s8 pos[3];
    vec3_set(pos, (x + 32*TILE_SIZE) / TILE_SIZE, (y + 32*TILE_SIZE) / TILE_SIZE, (z + 32*TILE_SIZE) / TILE_SIZE);

    // Check if out of range
    if (pos[1] > 63) {
        pos[1] = 63;
    }
    if (y < -32*TILE_SIZE) {
        return waterPlaneHeight;
    }
    if (!coords_in_range(pos)) return waterPlaneHeight;
    // If block contains water, scan upwards, otherwise scan downwards
    if (get_grid_tile(pos)->waterlogged) {
        // Find grid Y coordinate of highest water block.
        // Stop scanning once we hit a non-water block or the top is reached
        pos[1]++;
        while (pos[1] < 64 && get_grid_tile(pos)->waterlogged) {
            pos[1]++;
        }
        pos[1]--;
    } else {
        // Find grid Y coordinate of lowest non-water block.
        // Stop scanning once we hit a water block or the bottom is reached
        pos[1]--;
        while (pos[1] > -1 && !get_grid_tile(pos)->waterlogged) {
            pos[1]--;
        }
        if (pos[1] == -1) {
            return waterPlaneHeight;
        }
    }

    s32 waterBlockHeight;
    if (is_water_fullblock(pos)) {
        waterBlockHeight = (pos[1] - 31) * TILE_SIZE;
    } else {
        waterBlockHeight = (pos[1] - 31) * TILE_SIZE - (TILE_SIZE / 8);
    }
    return MAX(waterBlockHeight, waterPlaneHeight);
}
