#pragma once

struct mb64_boundary_quad {
    s8 vtx[4][3];
    s8 u[2];
    s8 v[2];
    u8 uYScale; // Scale U by Y instead of width
    u8 vYScale; // Scale V by Y instead of width
    u8 flipUvs;
};
