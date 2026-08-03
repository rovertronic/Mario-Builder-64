#include "tile.h"

#include "mb64/collision.h"
#include "engine/math_util.h"

u8 mb64_render_culling_off = FALSE; // Used for drawing preview blocks in custom theme menu

// Classifications for culling checks.
// Lower types of faces cull higher types of faces
enum BlockSideClassifications {
    CLASS_OPAQUE, // < CUTOUT
    CLASS_HOLLOW_TRANSPARENT,
    CLASS_HOLLOW_CUTOUT,
    CLASS_TRANSPARENT, // > CUTOUT
    CLASS_CUTOUT, // = CUTOUT
};

static u32 get_side_class(s32 mat, u32 dir) {
    if (mat == -1) return CLASS_CUTOUT;
    u32 mattype = TOPMAT(mat).type;
    if (dir != MB64_DIRECTION_UP) {
        mattype = MATERIAL(mat).type;
        if (mattype < MAT_CUTOUT) {
            if (TOPMAT(mat).type == MAT_CUTOUT) return CLASS_HOLLOW_CUTOUT;
            if (TOPMAT(mat).type > MAT_CUTOUT) return CLASS_HOLLOW_TRANSPARENT;
        }
    }
    if (mattype < MAT_CUTOUT) return CLASS_OPAQUE;
    if (mattype == MAT_CUTOUT) return CLASS_CUTOUT;
    return CLASS_TRANSPARENT;
}

u32 get_faceshape(s8 pos[3], u32 dir) {
    struct mb64_terrain *terrain;
    if (mb64_render_culling_off) return MB64_FACESHAPE_EMPTY;

    struct mb64_grid_obj *tile = get_grid_tile(pos);
    s8 tileType = tile->type;
    if (tileType == TILE_TYPE_EMPTY) return MB64_FACESHAPE_EMPTY;

    if (tileType == TILE_TYPE_POLE) terrain = &mb64_terrain_pole;
    else terrain = mb64_terrain_info_list[tileType].terrain;

    if (!terrain) return MB64_FACESHAPE_EMPTY;

    u8 rot = tile->rot;
    dir = rotate_direction(dir,((4-rot) % 4)) ^ 1;

    for (u32 i = 0; i < terrain->numTris; i++) {
        struct mb64_terrain_poly *tri = &terrain->tris[i];
        if (tri->faceDir == dir) {
            return tri->faceshape;
        }
    }
    for (u32 i = 0; i < terrain->numQuads; i++) {
        struct mb64_terrain_poly *quad = &terrain->quads[i];
        if (quad->faceDir == dir) {
            return quad->faceshape;
        }
    }
    return MB64_FACESHAPE_EMPTY;
}

ALWAYS_INLINE s32 get_mat(s8 pos[3]) {
    struct mb64_grid_obj *tile = get_grid_tile(pos);
    if (tile->type >= TILE_TYPE_CULL || tile->type == TILE_TYPE_EMPTY) return -1;
    return tile->mat;
}

// Used to compare material types and see if any future culling checks can be skipped
// WARNING! using grid tile ->mat directly will result in mat being 0 if the tile is empty/water
// Use get_mat for curMat (-1 = non-material tile)
// If this returns FALSE then the material can be culled.
s32 cutout_skip_culling_check(s32 curMat, s32 otherMat, s32 direction) {
    u32 curMatClass, otherMatClass;
    if (curMat == otherMat) return FALSE;
    curMatClass = get_side_class(curMat, direction);
    otherMatClass = get_side_class(otherMat, direction^1);
    if (curMatClass == otherMatClass) {
        return (curMatClass == CLASS_TRANSPARENT);
    } else {
        if ((curMatClass == CLASS_HOLLOW_CUTOUT) || (curMatClass == CLASS_HOLLOW_TRANSPARENT)) {
            if (direction == MB64_DIRECTION_DOWN) {
                if (get_side_class(otherMat, MB64_DIRECTION_DOWN) == curMatClass) return FALSE;
            }
        }
        return (curMatClass < otherMatClass);
    }
}

// Used for determining if a water side should be culled.
u32 block_side_is_solid(s32 adjMat, s32 mat, s32 direction) {
    s32 adjMatClass = get_side_class(adjMat, direction^1);
    if (adjMatClass == CLASS_CUTOUT) return FALSE;
    if (adjMatClass != CLASS_HOLLOW_CUTOUT) return TRUE; // cannot be waterlogged
    // Now we know that the side is a hollow cutout
    s32 matClass = get_side_class(mat, MB64_DIRECTION_DOWN);
    return (matClass != CLASS_HOLLOW_CUTOUT);
    // Will return FALSE if both materials are hollow cutouts but the waterlogged block
    // isn't a full faceshape. Not a big deal
}

s32 should_cull(s8 pos[3], s32 direction, s32 faceshape, s32 rot) {
    if (faceshape & MB64_FACESHAPE_EMPTY) return FALSE;
    if (mb64_render_culling_off) return FALSE;
    direction = rotate_direction(direction, rot);

    s8 adjPos[3];
    vec3_sum(adjPos, pos, cullOffsetLUT[direction]);

    if (AT_CEILING(pos[1]) && (direction == MB64_DIRECTION_UP)) return TRUE;

    if (!coords_in_range(adjPos)) {
        if (direction == MB64_DIRECTION_UP) return FALSE;
        if (direction == MB64_DIRECTION_DOWN) {
            return (mb64_curr_boundary & MB64_BOUNDARY_INNER_FLOOR) != 0;
        }
        return ((mb64_curr_boundary & MB64_BOUNDARY_INNER_WALLS) && (pos[1] < mb64_lopt_boundary_height));
    }
    struct mb64_grid_obj *adjTile = get_grid_tile(adjPos);
    s32 tileType = adjTile->type;
    switch(tileType) {
        case TILE_TYPE_CULL:
            return TRUE;
        case TILE_TYPE_TROLL:
            if (mb64_build_collision_type != 0) return FALSE;
            break;
    }

    if (cutout_skip_culling_check(get_mat(pos), adjTile->mat, direction)) return FALSE;
    s32 otherFaceshape = get_faceshape(adjPos, direction);

    if (otherFaceshape & MB64_FACESHAPE_EMPTY) return FALSE;
    if (otherFaceshape == MB64_FACESHAPE_FULL) return TRUE;
    if (faceshape == MB64_FACESHAPE_FULL) return FALSE;
    if ((faceshape == MB64_FACESHAPE_TOPTRI) || (faceshape == MB64_FACESHAPE_TOPHALF)) {
        if (otherFaceshape == faceshape) {
            u8 otherrot = adjTile->rot;
            return (otherrot == rot);
        } else return FALSE;
    }
    if (faceshape == MB64_FACESHAPE_BOTTOMSLAB || faceshape == MB64_FACESHAPE_TOPSLAB || faceshape == MB64_FACESHAPE_POLETOP) {
        if (otherFaceshape == faceshape) return TRUE;
    }
    if (faceshape == (otherFaceshape^1)) return TRUE;
    // Slab priority lists
    if (((faceshape & 0x10) && (otherFaceshape & 0x10)) ||
        ((faceshape & 0x20) && (otherFaceshape & 0x20))) return (faceshape > otherFaceshape);
    return FALSE;
}

// Additional culling check for certain grass overhangs. Assumes should_cull has already failed.
s32 should_cull_topslab_check(s8 pos[3], s32 direction) {
    s8 adjPos[3];
    vec3_sum(adjPos, pos, cullOffsetLUT[direction]);
    if (!coords_in_range(adjPos)) return FALSE;

    if (cutout_skip_culling_check(get_mat(pos), get_mat(adjPos), direction)) return FALSE;
    s32 otherFaceshape = get_faceshape(adjPos, direction);
    if ((otherFaceshape >= MB64_FACESHAPE_DOWNUPPERGENTLE_1) && (otherFaceshape <= MB64_FACESHAPE_TOPSLAB)) return TRUE;
    return FALSE;
}
