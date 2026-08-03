#include "tile.h"
#include "gfx.h"

#include <PR/gbi.h>
#include "mb64/collision.h"
#include "game/emutest.h"
#include "game/geo_misc.h"
#include "engine/math_util.h"

u8 mb64_use_alt_uvs = FALSE; // Used for decals and special tile shapes
s8 mb64_uv_offset = -16;
u8 mb64_render_flip_normals = FALSE; // Used for drawing water tiles
u8 mb64_render_vertical = FALSE; // Used for prioritizing vertical UVs over horizontal ones
u8 mb64_growth_render_type = 0; // 0 - normal, 1 - grass top, 2 - grass side, 3 - fence, 4 - pole
u8 mb64_curr_mat_has_topside = FALSE;
u8 mb64_curr_poly_vert_count = 4; // 3 = tri, 4 = quad

void mb64_transform_vtx_with_rot(s8 v[][3], s8 oldv[][3], u32 rot) {
    for (u32 i = 0; i < mb64_curr_poly_vert_count; i++) {
        s8 x = oldv[i][0];
        s8 z = oldv[i][2];
        switch (rot) {
            case 0: v[i][0] = x; v[i][2] = z; break;
            case 1: v[i][0] = z; v[i][2] = 16-x; break;
            case 2: v[i][0] = 16-x; v[i][2] = 16-z; break;
            case 3: v[i][0] = 16-z; v[i][2] = x; break;
        }
        v[i][1] = oldv[i][1];
    }
}

s32 render_get_normal_and_uvs(s8 v[3][3], u32 direction, u32 rot, u8 *uAxis, u8 *vAxis, s8 n[3]) {
    // Find normal
    Vec3f normal;
    if (direction != MB64_DIRECTION_UP) {
        find_vector_perpendicular_to_plane(normal, v[0], v[1], v[2]);
        vec3_normalize(normal);
        n[0] = normal[0] * 0x7F;
        n[1] = normal[1] * 0x7F;
        n[2] = normal[2] * 0x7F;
    } else {
        n[0] = 0;
        n[1] = 0x7F;
        n[2] = 0;
    }
    // Find UVs
    direction = rotate_direction(direction, rot);
    switch (direction) {
        case MB64_DIRECTION_NEG_X: *uAxis = 2; *vAxis = 1; return TRUE;
        case MB64_DIRECTION_POS_X: *uAxis = 2; *vAxis = 1; return FALSE;
        case MB64_DIRECTION_DOWN: // fallthrough
        case MB64_DIRECTION_UP: *uAxis = 2; *vAxis = 0; return FALSE;
        case MB64_DIRECTION_NEG_Z: *uAxis = 0; *vAxis = 1; return FALSE;
        /*case MB64_DIRECTION_POS_Z:*/ default: *uAxis = 0; *vAxis = 1; return TRUE;
    }
}

void render_poly(struct mb64_terrain_poly *poly, s8 pos[3], u32 rot) {
    s8 n[3];
    u8 uAxis, vAxis;
    s8 newVtx[4][3];

    s8 vertexIndices[4];
    s32 numNewVertices = 0;

    mb64_transform_vtx_with_rot(newVtx, poly->vtx, rot);
    s32 facedir = poly->faceDir;
    s32 useAltUVs = mb64_use_alt_uvs;
    if (mb64_render_vertical && (poly->faceshape > MB64_FACESHAPE_EMPTY)) {
        facedir = (poly->faceshape - MB64_FACESHAPE_EMPTY) + 1;
        // The four fixed UV shapes are 0x41 through 0x44
        // This maps them to 2 through 5 (the four lateral directions)
        // 0x40 is mapped to Down which results in no rotation
        useAltUVs = TRUE; // should not coincide with a decal UV
    }
    s32 flipU = render_get_normal_and_uvs(newVtx, facedir, rot, &uAxis, &vAxis, n);
    s32 clampV = (mb64_growth_render_type == 2) || (mb64_growth_render_type == 3);

    for (u32 i = 0; i < mb64_curr_poly_vert_count; i++) {
        s32 x = GRID_TO_POS(pos[0]) + ((newVtx[i][0] - 8) * 16);
        s32 y = GRID_TO_POS(pos[1]) + ((newVtx[i][1] - 8) * 16);
        s32 z = GRID_TO_POS(pos[2]) + ((newVtx[i][2] - 8) * 16);

        s16 u, v;
        if (useAltUVs && poly->altuvs) {
            u = 16 - (*poly->altuvs)[i][0];
            v = 16 - (*poly->altuvs)[i][1];
        } else {
            u = newVtx[i][uAxis];
            if (!flipU) u = 16 - u;
            v = 16 - newVtx[i][vAxis];
        }

        s32 upos = (flipU ? 64-pos[uAxis] : pos[uAxis]);
        s32 vpos = pos[vAxis];
        if (mb64_growth_render_type == 3) {
            upos *= 2; // fences
        } else if (mb64_growth_render_type == 4) {
            vpos *= 2; // poles
        }

        upos = (upos % 48) - 24;
        vpos = (vpos % 48) - 24;

        u -= upos * 16;
        if (!clampV) v -= vpos * 16;

        u = (u * 64 + mb64_uv_offset);
        v = (v * 64 + mb64_uv_offset);

        s32 vert = find_duplicate_vertex(x, y, z, n[0], n[1], n[2], u, v);
        if (vert != -1) {
            vertexIndices[i] = vert;
            continue;
        }

        make_vertex(mb64_curr_vtx, mb64_num_vertices_cached + numNewVertices, x, y, z,
            u, v,
            n[0], n[1], n[2], 0xFF);
        vertexIndices[i] = mb64_num_vertices_cached + numNewVertices;
        numNewVertices++;
    }
    
    u32 isQuad = (mb64_curr_poly_vert_count == 4);
    if (mb64_render_flip_normals) {
        cache_tri(vertexIndices[0], vertexIndices[2], vertexIndices[1]);
        if (isQuad) cache_tri(vertexIndices[1], vertexIndices[2], vertexIndices[3]);
    } else {
        cache_tri(vertexIndices[0], vertexIndices[1], vertexIndices[2]);
        if (isQuad) cache_tri(vertexIndices[1], vertexIndices[3], vertexIndices[2]);
    }
    mb64_num_vertices_cached += numNewVertices;
    check_cached_tris();
}

void process_poly(s8 pos[3], struct mb64_terrain_poly *quad, u32 rot) {
    if (!mb64_build_collision_type)
        render_poly(quad, pos, rot);
    else
        mb64_create_poly(quad, pos, rot);
}

void grass_slope_extra_decal_uvs(s8 newUVs[][2], s8 vtx[][3], s32 side, s32 scalefactor, s32 count) {
    for (s32 i = 0; i < count; i++) {
        newUVs[i][0] = 16 - vtx[i][0];
        s32 upFactor = (side == 0 ? vtx[i][0] : 16 - vtx[i][0]);
        newUVs[i][1] = vtx[i][1] - ((upFactor*scalefactor) >> 1); // multiply by scalefactor/2
    }
}

void render_grass_slope_extra_decal(s8 pos[3], u32 direction, u32 grassType) {
    // Check if below block is in range
    s8 newpos[3];
    s8 newUVs[4][2];
    vec3_set(newpos, pos[0], pos[1]-1, pos[2]);
    if (!coords_in_range(newpos)) return;

    // Check if below block matches material
    u8 curMat = get_mat(pos);
    u8 belowMat = get_mat(newpos);
    if (curMat != belowMat) return;

    // Check if below block is right shape and culled
    // Shape of face of above block on same side
    s32 otherFaceshape = get_faceshape(newpos, direction^1);
    if (should_cull(newpos, direction, otherFaceshape, 0)) return;
    if (should_cull_topslab_check(newpos, direction)) return;
    
    // Calculate effective rotation of face to print. very ugly
    u8 targetRot = 0;
    switch (direction) {
        case MB64_DIRECTION_POS_X:
            targetRot = 1;
            break;
        case MB64_DIRECTION_NEG_X:
            targetRot = 3;
            break;
        //case MB64_DIRECTION_POS_Z:
            //targetRot = 0;
            //break;
        case MB64_DIRECTION_NEG_Z:
            targetRot = 2;
            break;
    }

    s32 index;
    s32 oldVerts = mb64_curr_poly_vert_count;

    switch (otherFaceshape) {
        default:
            return;
        // Face is full quad
        case MB64_FACESHAPE_FULL:
            index = 0; mb64_curr_poly_vert_count = 4;
            break;
        case MB64_FACESHAPE_DOWNTRI_1:
            index = 1; mb64_curr_poly_vert_count = 3;
            break;
        case MB64_FACESHAPE_DOWNTRI_2:
            index = 2; mb64_curr_poly_vert_count = 3;
            break;
        case MB64_FACESHAPE_DOWNUPPERGENTLE_1:
        case MB64_FACESHAPE_DOWNUPPERGENTLE_2:
        case MB64_FACESHAPE_TOPSLAB:
            index = 3; mb64_curr_poly_vert_count = 4;
            break;
        case MB64_FACESHAPE_HALFSIDE_1:
            if (grassType == MB64_GROWTH_SLOPE_SIDE_L) return;
            index = 4; mb64_curr_poly_vert_count = 4;
            break;
        case MB64_FACESHAPE_HALFSIDE_2:
            if (grassType == MB64_GROWTH_SLOPE_SIDE_R) return;
            index = 5; mb64_curr_poly_vert_count = 4;
            break;
        case MB64_FACESHAPE_DOWNLOWERGENTLE_1:
            index = 6; mb64_curr_poly_vert_count = 3;
            break;
        case MB64_FACESHAPE_DOWNLOWERGENTLE_2:
            index = 7; mb64_curr_poly_vert_count = 3;
            break;
    }

    s32 side = grassType & 1;
    s32 scalefactor = (grassType & 2) ? 1 : 2;

    struct mb64_terrain_poly *poly = slope_decal_below_surfs[index];
    grass_slope_extra_decal_uvs(newUVs, poly->vtx, side, scalefactor, mb64_curr_poly_vert_count);
    poly->altuvs = &newUVs;
    render_poly(poly, newpos, targetRot);
    mb64_curr_poly_vert_count = oldVerts;

    return;
}

// Determines if the faceshape as a solid bottom edge and two vertical edges on either side
u32 faceshape_has_full_bottom(u32 faceshape) {
    return (faceshape == MB64_FACESHAPE_FULL) ||
        (faceshape >= MB64_FACESHAPE_UPPERGENTLE_1 && faceshape <= MB64_FACESHAPE_BOTTOMSLAB);
}

u32 should_render_grass_side(s8 pos[3], u32 direction, u32 faceshape, u32 rot, u32 grassType) {
    s8 abovePos[3];
    vec3_set(abovePos, pos[0], pos[1]+1, pos[2]);
    struct mb64_grid_obj *tile = get_grid_tile(pos);
    struct mb64_grid_obj *aboveTile = get_grid_tile(abovePos);
    if (should_cull(pos, direction, faceshape, rot)) return FALSE;

    // Other sides that don't care about the above block (e.g. bottom slab)
    if (grassType == MB64_GROWTH_UNCONDITIONAL) return TRUE;

    // Render extra decal for slopes if necessary
    // The side of the slope itself is unconditional and will always render
    if (grassType >= MB64_GROWTH_EXTRADECAL_START) {
        render_grass_slope_extra_decal(pos, rotate_direction(direction, rot), grassType);
        return TRUE;
    }

    if (AT_CEILING(pos[1])) return FALSE;
    if (!coords_in_range(abovePos)) return TRUE;

    if (!(faceshape & MB64_FACESHAPE_EMPTY)) {
        if ((grassType == MB64_GROWTH_HALF_SIDE) || (grassType == MB64_GROWTH_NORMAL_SIDE)) {
            if (should_cull_topslab_check(pos, rotate_direction(direction, rot))) return FALSE;
        }
    }

    // Render if above tile is empty
    if (aboveTile->type == TILE_TYPE_EMPTY) return TRUE;
    // Render if above tile is seethrough (some exceptions)
    if (cutout_skip_culling_check(tile->mat, aboveTile->mat, MB64_DIRECTION_UP)) return TRUE;

    if (faceshape > MB64_FACESHAPE_EMPTY) {
        direction = (faceshape - MB64_FACESHAPE_EMPTY) + 1;
    }

    u32 otherFaceshape;
    switch (grassType) {
        case MB64_GROWTH_NORMAL_SIDE:
        case MB64_GROWTH_HALF_SIDE:
            // Shape of face of above block on same side
            otherFaceshape = get_faceshape(abovePos, rotate_direction(direction, rot)^1);
            switch (otherFaceshape) {
                case MB64_FACESHAPE_TRI_1:
                case MB64_FACESHAPE_TRI_2:
                case MB64_FACESHAPE_FULL:
                case MB64_FACESHAPE_UPPERGENTLE_1:
                case MB64_FACESHAPE_UPPERGENTLE_2:
                case MB64_FACESHAPE_LOWERGENTLE_1:
                case MB64_FACESHAPE_LOWERGENTLE_2:
                case MB64_FACESHAPE_BOTTOMSLAB:
                    return FALSE;
            }
            if ((grassType == MB64_GROWTH_HALF_SIDE) && (faceshape == otherFaceshape)) {
                return FALSE;
            }
            return TRUE;
        case MB64_GROWTH_UNDERSLOPE_CORNER:
            ;// some very cursed logic here, this is solely for upside-down inside corners
            u8 faceshape1 = get_faceshape(abovePos, rotate_direction(MB64_DIRECTION_POS_Z, rot)^1);
            u8 faceshape2 = get_faceshape(abovePos, rotate_direction(MB64_DIRECTION_POS_X, rot)^1);
            // this is basically just checking for if a normal slope corner is on top at the right angle
            if (faceshape1 == MB64_FACESHAPE_TRI_1 && faceshape2 == MB64_FACESHAPE_TRI_2)
                return FALSE;
            // don't display if either face on top of the inside corner is full
            return !(faceshape_has_full_bottom(faceshape1) || faceshape_has_full_bottom(faceshape2));

        case MB64_GROWTH_DIAGONAL_SIDE:
        case MB64_GROWTH_VSLAB_SIDE:
            otherFaceshape = get_faceshape(abovePos, MB64_DIRECTION_UP);
            if (otherFaceshape == MB64_FACESHAPE_FULL) return FALSE;
            if (otherFaceshape != (grassType == MB64_GROWTH_DIAGONAL_SIDE ? MB64_FACESHAPE_TOPTRI : MB64_FACESHAPE_TOPHALF)) return TRUE;
            if (aboveTile->type == TILE_TYPE_SCORNER) return TRUE;
            u8 otherrot = aboveTile->rot;
            return (otherrot != rot);
    }
    return FALSE;
}

void process_poly_with_growth(s8 pos[3], struct mb64_terrain_poly *poly, u32 rot) {
    switch (mb64_growth_render_type) {
        case 1: // grass top
            if (poly->growthType != MB64_GROWTH_FULL) return;
            if (should_cull(pos, poly->faceDir, poly->faceshape, rot)) return;
            break;
        case 2: // grass decal
            if (poly->growthType == MB64_GROWTH_FULL || poly->growthType == MB64_GROWTH_NONE) return;
            if (!should_render_grass_side(pos, poly->faceDir, poly->faceshape, rot, poly->growthType)) return;
            break;
        default:
            if (mb64_curr_mat_has_topside && (poly->growthType == MB64_GROWTH_FULL)) return;
            if (should_cull(pos, poly->faceDir, poly->faceshape, rot)) return;
            break;
    }
    process_poly(pos, poly, rot);
}

void process_tile(s8 pos[3], struct mb64_terrain *terrain, u32 rot) {
    mb64_curr_poly_vert_count = 4;
    for (u32 j = 0; j < terrain->numQuads; j++) {
        struct mb64_terrain_poly *quad = &terrain->quads[j];
        process_poly_with_growth(pos, quad, rot);
    }
    mb64_curr_poly_vert_count = 3;
    for (u32 j = 0; j < terrain->numTris; j++) {
        struct mb64_terrain_poly *tri = &terrain->tris[j];
        process_poly_with_growth(pos, tri, rot);
    }
}

#define BAR_CONNECTED_SIDE(bar) ((bar) & 1)
#define BAR_CONNECTED_TOP(bar) (((bar) >> 1) & 0x1)
#define BAR_CONNECTED_BOTTOM(bar) (((bar) >> 2) & 0x1)

void check_bar_side_connections(s8 pos[3], u8 connections[4]) {
    s8 adjacentPos[3];

    for (u32 rot = 0; rot < 4; rot++) {
        connections[rot] = 0;
        s32 dir = rotate_direction(MB64_DIRECTION_POS_Z, rot);
        vec3_sum(adjacentPos, pos, cullOffsetLUT[dir]);
        struct mb64_grid_obj *adjTile = get_grid_tile(adjacentPos);

        if (!coords_in_range(adjacentPos)) {
            if ((mb64_curr_boundary & MB64_BOUNDARY_INNER_WALLS) && 
                adjacentPos[1] < mb64_lopt_boundary_height) {
                connections[rot] = 1;
            }
            continue;
        }

        // If adjacent block is a bar, return true
        if (adjTile->type == TILE_TYPE_BARS) {
            connections[rot] = 1; continue;
        }

        // Else check its a full block
        if ((get_faceshape(adjacentPos, dir) == MB64_FACESHAPE_FULL) || (adjTile->type == TILE_TYPE_CULL)) {
            connections[rot] = 1;
        }
    }
}

void check_bar_connections(s8 pos[3], u8 connections[5]) {
    check_bar_side_connections(pos, connections);
    connections[4] = 0;
    // Check top
    s8 adjacentPos[3];
    u8 adjacentConnections[4];

    for (u32 updown = 0; updown < 2; updown++) { // 0 = Up, 1 = Down
        vec3_sum(adjacentPos, pos, cullOffsetLUT[updown]);
        struct mb64_grid_obj *adjTile = get_grid_tile(adjacentPos);

        if (coords_in_range(adjacentPos)) {
            u32 faceshape = get_faceshape(adjacentPos, updown);
            if ((faceshape == MB64_FACESHAPE_FULL) || (adjTile->type == TILE_TYPE_CULL)) {
                for (u32 rot = 0; rot < 4; rot++) {
                    connections[rot] |= (1 << (updown+1)); // Apply top flag to all bars
                }
                connections[4] |= (1 << (updown + 1));
            } else if (faceshape == MB64_FACESHAPE_TOPHALF) {
                connections[(adjTile->rot + 2) % 4] |= (1 << (updown + 1));
            } else if (adjTile->type == TILE_TYPE_BARS) {
                check_bar_side_connections(adjacentPos, adjacentConnections);
                for (u32 rot = 0; rot < 4; rot++) {
                    connections[rot] |= adjacentConnections[rot] << (updown+1); // Apply top flag to all bars
                }
                connections[4] |= (1 << (updown + 1));
            }
        }
    }
    if ((pos[1] == 0) && (mb64_curr_boundary & MB64_BOUNDARY_INNER_FLOOR)) { // Culling for bottom
        for (u32 rot = 0; rot < 5; rot++) {
            connections[rot] |= (1 << 2);
        }
    }
    if (AT_CEILING(pos[1])) { // Culling for top
        for (u32 rot = 0; rot < 5; rot++) {
            connections[rot] |= (1 << 1);
        }
    }
}

void render_bars_side(s8 pos[3], u8 connections[5]) {
    for (u32 rot = 0; rot < 4; rot++) {
        u32 leftRot = (rot + 3) % 4;
        u32 rightRot = (rot + 1) % 4;
        if (BAR_CONNECTED_SIDE(connections[rot])) {
            process_poly(pos, &mb64_terrain_bars_connected_quads[0], rot);
            process_poly(pos, &mb64_terrain_bars_connected_quads[1], rot);
        }
        if (!BAR_CONNECTED_SIDE(connections[rot]) ||
            (BAR_CONNECTED_SIDE(connections[leftRot]) && BAR_CONNECTED_SIDE(connections[rightRot]))) {
            process_poly(pos, mb64_terrain_bars_unconnected_quad, rot);
        }
    }
}

void render_bars_top(s8 pos[3], u8 connections[5]) {
    for (u32 rot = 0; rot < 4; rot++) {
        if (BAR_CONNECTED_SIDE(connections[rot])) {
            if (!BAR_CONNECTED_TOP(connections[rot])) {
                process_poly(pos, &mb64_terrain_bars_connected_quads[2], rot);
            }
            if (!BAR_CONNECTED_BOTTOM(connections[rot])) {
                process_poly(pos, &mb64_terrain_bars_connected_quads[3], rot);
            }
        }
    }
    if (!BAR_CONNECTED_TOP(connections[4])) process_poly(pos, &mb64_terrain_bars_center_quads[0], 0);
    if (!BAR_CONNECTED_BOTTOM(connections[4])) process_poly(pos, &mb64_terrain_bars_center_quads[1], 0);
}

// Find if specific tile of water is fullblock or shallow
u32 is_water_fullblock(s8 pos[3]) {
    s8 abovePos[3];
    if (AT_CEILING(pos[1])) {
        if (MATERIAL(mb64_lopt_boundary_mat).type != MAT_CUTOUT) return TRUE;
    }
    vec3_set(abovePos, pos[0], pos[1]+1, pos[2]);
    if (!coords_in_range(abovePos)) return FALSE;
    // Full block if above block is water
    struct mb64_grid_obj *aboveTile = get_grid_tile(abovePos);
    struct mb64_grid_obj *tile = get_grid_tile(pos);
    if (aboveTile->waterlogged) return TRUE;

    // Full block if above block has solid bottom face
    if (get_faceshape(abovePos, MB64_DIRECTION_UP) == MB64_FACESHAPE_FULL) {
        u8 aboveMat = get_mat(abovePos);
        // If above block is troll, but current block is also troll, then not full block
        if ((tile->type == TILE_TYPE_TROLL) && (aboveTile->type == TILE_TYPE_TROLL)) return FALSE;
        // If bottom block is hollow cutout and top block is some kind of cutout then not full block
        u8 curMat = get_mat(pos);
        if (!block_side_is_solid(aboveMat, curMat, MB64_DIRECTION_UP)) return FALSE;
        return TRUE;
    }
    return FALSE;
}

// return type of render to use
// 0: cull
// 1: normal (low side)
// 2: full (full side)
// 3: top (thin top at side)
u32 get_water_side_render(s8 pos[3], u32 dir, u32 isFullblock) {
    s8 adjacentPos[3];
    vec3_sum(adjacentPos, pos, cullOffsetLUT[dir]);
    if (AT_CEILING(pos[1])) {
        if ((dir == MB64_DIRECTION_UP) && (MATERIAL(mb64_lopt_boundary_mat).type != MAT_CUTOUT)) return 0;
    }
    struct mb64_grid_obj *adjTile = get_grid_tile(adjacentPos);

    if (!coords_in_range(adjacentPos)) {
        if (dir == MB64_DIRECTION_UP) return 1;
        u32 type = isFullblock ? 2 : 1;
        if (dir == MB64_DIRECTION_DOWN) {
            return (mb64_curr_boundary & MB64_BOUNDARY_INNER_FLOOR) ? 0 : type;
        }
        return ((mb64_curr_boundary & MB64_BOUNDARY_INNER_WALLS) && (pos[1] < mb64_lopt_boundary_height)) ? 0 : type;
    }
    if (adjTile->type == TILE_TYPE_CULL) return 0;

    s32 mat = get_mat(pos);
    s32 adjMat = get_mat(adjacentPos);

    // Apply normal side culling
    // Usually this would fail if next to a mesh, but it will pass if
    // the current tile is the same material, which in this case will happen
    // if an entire mesh is waterlogged.
    if ((get_faceshape(adjacentPos, dir) == MB64_FACESHAPE_FULL) && block_side_is_solid(adjMat, mat, dir)) return 0;

    // Check if the block that's waterlogged has a full face on the same side
    if ((get_faceshape(pos, dir^1) == MB64_FACESHAPE_FULL) && block_side_is_solid(mat, adjMat, dir^1)) {
        if (!isFullblock && (dir == MB64_DIRECTION_UP)) {
            return 1;
        }
        return 0;
    }

    if (adjTile->waterlogged) {
        // Check if this is a full block, next to a non-full block.
        // If so, use special thin side
        if (dir != MB64_DIRECTION_UP && dir != MB64_DIRECTION_DOWN) {
            if (isFullblock && !is_water_fullblock(adjacentPos)) {
                return 3;
            }
        }
        // Full block next to full block so cull
        return 0;
    }


    return isFullblock ? 2 : 1;
}

void render_water(s8 pos[3]) {
    u32 isFullblock = is_water_fullblock(pos);
    for (u32 j = 0; j < 6; j++) {
        u8 sideRender = get_water_side_render(pos, mb64_terrain_fullblock_quads[j].faceDir, isFullblock);
        if (sideRender != 0) {
            struct mb64_terrain_poly *poly = &mb64_terrain_water_quadlists[sideRender - 1][j];
            process_poly(pos, poly, 0);
        }
    }
}

void set_render_mode(u32 tileType, u32 disableZ) {
    u32 rendermode = mb64_render_mode_table[tileType];
    if (disableZ) rendermode &= ~(Z_UPD | Z_CMP);
    if (!gIsConsole && (tileType != MAT_TRANSPARENT)) rendermode |= AA_EN;
    gDPPipeSync(&mb64_curr_gfx[mb64_gfx_index++]);
    gDPSetRenderMode(&mb64_curr_gfx[mb64_gfx_index++], rendermode, 0);
}

Gfx *get_sidetex(s32 matid) {
    for (s32 i = 0; i < ARRAY_COUNT(mb64_topmat_table); i++) {
        if (mb64_topmat_table[i].mat == matid) {
            return mb64_topmat_table[i].decaltex;
        }
    }
    return NULL;
}

// Returns true if tile should be processed
// If in vplex screen processing mode, can also override target mat type in order
// to render screen
u32 do_process(u8 *targetMatType, u32 processTileRenderMode) {
    switch (processTileRenderMode) {
        case PROCESS_TILE_NORMAL:
            return (*targetMatType != MAT_TRANSPARENT);
        case PROCESS_TILE_TRANSPARENT:
            return (*targetMatType == MAT_TRANSPARENT);
        case PROCESS_TILE_VPLEX:
            if (*targetMatType == MAT_DECAL) {
                *targetMatType = MAT_SCREEN;
                return TRUE;
            }
            return FALSE;
    }
    return TRUE; // PROCESS_TILE_BOTH
}

void process_tiles(u32 processTileRenderMode) {
    u32 startIndex, endIndex;
    u8 tileType, rot;
    s8 pos[3];

    // Poles
    u8 poleMatType = mb64_mat_table[mb64_theme_table[mb64_lopt_theme].pole].type;
    if (do_process(&poleMatType, processTileRenderMode)) {
        mb64_use_alt_uvs = TRUE;
        mb64_growth_render_type = 4; // poles
        startIndex = mb64_tile_data_indices[POLE_TILETYPE_INDEX];
        endIndex = mb64_tile_data_indices[POLE_TILETYPE_INDEX+1];
        set_render_mode( poleMatType, FALSE);
        gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], POLE_TEX());
        for (u32 i = startIndex; i < endIndex; i++) {
            s8 pos[3];
            vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);
            process_tile(pos, &mb64_terrain_pole, mb64_tile_data[i].rot);
        }
        display_cached_tris();
    }
    mb64_use_alt_uvs = FALSE;
    mb64_render_vertical = FALSE;

    for (u32 mat = 0; mat < NUM_MATERIALS_PER_THEME; mat++) {
        u8 matType = MATERIAL(mat).type;
        mb64_growth_render_type = 0;
        mb64_curr_mat_has_topside = HAS_TOPMAT(mat);
        startIndex = mb64_tile_data_indices[mat];
        endIndex = mb64_tile_data_indices[mat+1];

        if (!do_process(&matType, processTileRenderMode)) {
            goto skip_maintex;
        }

        set_render_mode( matType, FALSE);
        gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], MATERIAL(mat).gfx);
        mb64_render_vertical = MATERIAL(mat).vertical;

        // Important to not use matType here so that it's still opaque for screens
        if ((matType == MAT_CUTOUT) || ((MATERIAL(mat).type < MAT_CUTOUT) && (TOPMAT(mat).type >= MAT_CUTOUT))) {
            gSPClearGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK);
        }

        for (u32 i = startIndex; i < endIndex; i++) {
            tileType = mb64_tile_data[i].type;
            rot = mb64_tile_data[i].rot;
            vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);
            
            process_tile(pos, mb64_terrain_info_list[tileType].terrain, rot);
        }

        display_cached_tris();
skip_maintex:
        
        if (mb64_curr_mat_has_topside) {
            u8 topmatType = TOPMAT(mat).type;
            if (!do_process(&topmatType, processTileRenderMode)) continue;
            Gfx *sidetex = get_sidetex(TILE_MATDEF(mat).topmat);
            if (sidetex) {
                mb64_use_alt_uvs = TRUE;
                mb64_render_vertical = TRUE;
                gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], sidetex);
                mb64_growth_render_type = 2;

                // This code is pretty ugly. It renders the side decal in decal mode
                // for opaque parts of the texture, and in cutout mode for transparent parts.
                // Luckily this will only double the number of triangles in the rare case
                // that a custom block with a cutout side texture and a topmat with a side decal
                // is made (in order to cover both the opaque and alpha parts of the side tex.)
                // DECAL MODE
                if (matType != MAT_TRANSPARENT) { // Render in decal mode for cutouts, opaque and screen
                    set_render_mode( MAT_DECAL, FALSE);
                    for (u32 i = startIndex; i < endIndex; i++) {
                        tileType = mb64_tile_data[i].type;
                        rot = mb64_tile_data[i].rot;
                        vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);

                        process_tile(pos, mb64_terrain_info_list[tileType].terrain, rot);
                    }
                    display_cached_tris();
                }
                // OPAQUE MODE
                if (matType >= MAT_CUTOUT) { // Render in cutout mode for cutouts and transparent
                    set_render_mode( MAT_CUTOUT, FALSE);
                    for (u32 i = startIndex; i < endIndex; i++) {
                        tileType = mb64_tile_data[i].type;
                        rot = mb64_tile_data[i].rot;
                        vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);

                        process_tile(pos, mb64_terrain_info_list[tileType].terrain, rot);
                    }
                    display_cached_tris();
                }
                mb64_use_alt_uvs = FALSE;
            }

            set_render_mode(topmatType, FALSE);
            gSPDisplayList(&mb64_curr_gfx[mb64_gfx_index++], TOPMAT(mat).gfx);
            mb64_render_vertical = TOPMAT(mat).vertical;

            mb64_growth_render_type = 1;
            for (u32 i = startIndex; i < endIndex; i++) {
                tileType = mb64_tile_data[i].type;
                rot = mb64_tile_data[i].rot;
                vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);

                process_tile(pos, mb64_terrain_info_list[tileType].terrain, rot);
            }
            display_cached_tris();
        }
        gSPSetGeometryMode(&mb64_curr_gfx[mb64_gfx_index++], G_CULL_BACK);
    }
}

// Fade: 0 = no fade, 1 = fade at bottom, 2 = fade at top
void render_boundary_quad(struct mb64_boundary_quad *quad, s16 y, s16 yHeight, u32 fade) {
    // Get normal
    Vec3f normal;
    find_vector_perpendicular_to_plane(normal, quad->vtx[0], quad->vtx[1], quad->vtx[2]);
    vec3_normalize(normal);
    s8 n[3];
    s32 normalMult = (mb64_render_flip_normals ? -0x7F : 0x7F);
    n[0] = normal[0]*normalMult;
    n[1] = normal[1]*normalMult;
    n[2] = normal[2]*normalMult;

    s32 uScale = quad->uYScale ? (yHeight * 64) : mb64_grid_size*16;
    s32 vScale = quad->vYScale ? (yHeight * 64) : mb64_grid_size*16;
    for (u32 i = 0; i < 4; i++) {
        s16 u = (quad->u[i & 1])*uScale + mb64_uv_offset;
        s16 v = (quad->v[i >> 1])*vScale + mb64_uv_offset;
        if (quad->flipUvs) { s16 tmp = u; u = v; v = tmp;}
        if (yHeight % 2) v += 512; // offset for odd number of blocks
        u8 alpha = 255;
        if ((ABS(quad->vtx[i][0]) > 32) || (ABS(quad->vtx[i][2]) > 32)) {
            alpha = 0;
        } else if (((fade == 1) && (quad->vtx[i][1] == 0)) || ((fade == 2) && (quad->vtx[i][1] == 1))) {
            alpha = 0;
        }
        make_vertex(mb64_curr_vtx, i+mb64_num_vertices_cached, quad->vtx[i][0]*mb64_grid_size*4, (quad->vtx[i][1]*yHeight*TILE_SIZE + y), quad->vtx[i][2]*mb64_grid_size*4,
            u, v, n[0], n[1], n[2], alpha);
    }
    if (mb64_render_flip_normals) {
        cache_tri(mb64_num_vertices_cached, mb64_num_vertices_cached+2, mb64_num_vertices_cached+1);
        cache_tri(mb64_num_vertices_cached+1, mb64_num_vertices_cached+2, mb64_num_vertices_cached+3);
    } else {
        cache_tri(mb64_num_vertices_cached, mb64_num_vertices_cached+1,mb64_num_vertices_cached+2);
        cache_tri(mb64_num_vertices_cached+1, mb64_num_vertices_cached+3, mb64_num_vertices_cached+2);
    }
    mb64_num_vertices_cached += 4;
    check_cached_tris();
}
