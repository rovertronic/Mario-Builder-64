#ifndef BOB_HEADER_H
#define BOB_HEADER_H

#include "types.h"

// geo
extern const GeoLayout bob_geo_000440[];
extern const GeoLayout bob_geo_000458[];
extern const GeoLayout bob_geo_000470[];
extern const GeoLayout bob_geo_000488[];

// leveldata
extern const Gfx bob_seg7_dl_07004390[];
extern const Gfx bob_seg7_dl_07009D80[];
extern const Gfx bob_seg7_dl_0700A470[];
extern const Gfx bob_seg7_dl_0700A920[];
extern const Gfx bob_seg7_dl_0700DD18[];
extern const Gfx bob_seg7_dl_0700E338[];
extern const Gfx bob_seg7_dl_0700E458[];
extern const Gfx bob_seg7_dl_0700E768[];
extern const Gfx bob_seg7_dl_0700E8A0[];

extern const Collision bob_seg7_collision_level[];
extern const MacroObject bob_seg7_macro_objs[];
extern const Collision bob_seg7_collision_chain_chomp_gate[];
extern const Collision bob_seg7_collision_bridge[];
extern const Collision bob_seg7_collision_gate[];
extern const Trajectory bob_seg7_metal_ball_path0[];
extern const Trajectory bob_seg7_metal_ball_path1[];
extern const Trajectory bob_seg7_trajectory_koopa[];

//MY DATA

//Tilt rock
extern const Collision hotform_col_collision[];
extern Vtx popeop_Cylinder_003_mesh_vtx_0[19];
extern Gfx popeop_Cylinder_003_mesh_tri_0[];
extern Vtx popeop_Cylinder_003_mesh_vtx_1[9];
extern Gfx popeop_Cylinder_003_mesh_tri_1[];
extern Gfx popeop_Cylinder_003_mesh[];
extern const GeoLayout Tilt_Slate[];
//Lava_Spewer_Geo

//Lava Spewer
extern const Collision spewer_collision[];
extern Vtx spewer_Cylinder_002_mesh_vtx_0[18];
extern Gfx spewer_Cylinder_002_mesh_tri_0[];
extern Vtx spewer_Cylinder_002_mesh_vtx_1[16];
extern Gfx spewer_Cylinder_002_mesh_tri_1[];
extern Vtx spewer_Cylinder_002_mesh_vtx_2[8];
extern Gfx spewer_Cylinder_002_mesh_tri_2[];
extern Gfx spewer_Cylinder_002_mesh[];
extern const GeoLayout Lava_Spewer_Geo[];


// script
extern const LevelScript level_bob_entry[];

#include "levels/bob/header.inc.h"

#include "levels/bob/Map1/header.h"

#include "levels/bob/shock/geo_header.h"

#include "levels/bob/kingbully/geo_header.h"

#include "levels/bob/shard/geo_header.h"


#include "levels/bob/maker2/header.h"

#endif
