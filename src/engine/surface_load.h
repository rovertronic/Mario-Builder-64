#ifndef SURFACE_LOAD_H
#define SURFACE_LOAD_H

#include <PR/ultratypes.h>

#include "surface_collision.h"
#include "types.h"

#define SURFACE_VERTICAL_BUFFER 5

#define NORMAL_FLOOR_THRESHOLD 0.01f
#define NORMAL_CEIL_THRESHOLD -NORMAL_FLOOR_THRESHOLD

/**
 * The size of the surface pools
 */
#define MAIN_SURFACE_POOL_SIZE 1500
#define MAIN_SURFACE_NODE_POOL_SIZE 2000

#define BLOCK_SURFACE_POOL_SIZE 1500
#define BLOCK_SURFACE_NODE_POOL_SIZE 1600

struct SurfaceNode {
    struct SurfaceNode *next;
    struct Surface *surface;
};

enum SpatialPartitions {
    SPATIAL_PARTITION_FLOORS,
    SPATIAL_PARTITION_CEILS,
    SPATIAL_PARTITION_WALLS,
    NUM_SPATIAL_PARTITIONS
};

typedef struct SurfaceNode *SpatialPartitionCell[NUM_SPATIAL_PARTITIONS];

extern SpatialPartitionCell gStaticSurfacePartition[NUM_CELLS][NUM_CELLS];
extern SpatialPartitionCell gDynamicSurfacePartition[NUM_CELLS][NUM_CELLS];
extern SpatialPartitionCell gBlockSurfaces;
extern struct Surface *gSurfacePool;
extern struct SurfaceNode *gSurfaceNodePool;
extern struct Surface *gMainSurfacePool;
extern struct SurfaceNode *gMainSurfaceNodePool;
extern struct Surface *gBlockSurfacePool;
extern struct SurfaceNode *gBlockSurfaceNodePool;

void alloc_surface_pools(void);
#ifdef NO_SEGMENTED_MEMORY
u32 get_area_terrain_size(TerrainData *data);
#endif
void load_area_terrain(s32 index, TerrainData *data, RoomData *surfaceRooms, MacroObject *macroObjects);
void clear_dynamic_surfaces(void);
void load_object_collision_model(void);
void clear_static_surfaces(void);
// void load_object_static_model(void);
/**
 * Clears the static (level) surface partitions for new use.
 */
#define clear_static_surfaces() clear_spatial_partition(&gStaticSurfacePartition[0][0])

#endif // SURFACE_LOAD_H
