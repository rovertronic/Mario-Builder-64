#pragma once

struct mb64_terrain_poly {
    s8 vtx[4][3];
    u8 faceDir;
    u8 faceshape;
    u8 growthType;
    s8 (*altuvs)[4][2];
};

struct mb64_terrain {
    u8 numQuads;
    u8 numTris;
    struct mb64_terrain_poly * quads;
    struct mb64_terrain_poly * tris;
};

struct mb64_tile {
    u32 x:6, y:6, z:6, type:5, mat:4, rot:2, waterlogged:1;
};

struct mb64_obj {
    u8 bparam;
    u8 x;
    u8 y;
    u8 z;
    u8 type;
    u8 rot;
    u8 imbue;
    u8 pad;
};

struct mb64_grid_obj {
    u16 type:5, mat:4, rot:2, waterlogged:1;
};

typedef void (*DisplayFunc)(s32);
struct mb64_object_info {
    char *name;
    Gfx *btn;
    const BehaviorScript *behavior;
    f32 y_offset;
    u16 model_id;
    u8 flags;
    u8 occupy;
    u8 numCoins;
    u8 numExtraObjects;
    f32 scale;
    const struct Animation *const *anim;
    DisplayFunc disp_func;
    u32 soundBits;
};

#define NUM_MATERIALS_PER_THEME 10
enum tiletypeIndices {
    FENCE_TILETYPE_INDEX = NUM_MATERIALS_PER_THEME,
    POLE_TILETYPE_INDEX,
    BARS_TILETYPE_INDEX,
    CULL_TILETYPE_INDEX,
    WATER_TILETYPE_INDEX,
    END_TILE_INDEX
};

// Represents a material texture and collision
struct mb64_material {
    Gfx *gfx;
    u8 type;
    u8 vertical;
    TerrainData col;
    char *name; // Only used for Custom Theme menu
};

// Represents a material as a top texture with optional side decal
struct mb64_topmaterial {
    u8 mat;
    Gfx *decaltex;
};

// Defines materials of a full block
struct mb64_tilemat_def {
    u8 mat;
    u8 topmat;
    char *name;
};

struct mb64_theme {
    struct mb64_tilemat_def mats[NUM_MATERIALS_PER_THEME];
    u8 fence;
    u8 pole;
    u8 bars;
    u8 water;
};

struct mb64_terrain_info {
    char *name;
    Gfx *button;
    struct mb64_terrain *terrain;
};

struct mb64_template {
    u8 music[2]; // vanilla, btcm
    u32 envfx:3;
    u32 bg:4;
    u32 theme:4;
    u32 boundaryMat:4;
    u32 boundaryHeight:6;
    u32 boundary:3;
    u32 water:6;

    u32 spawnHeight:6;
    u32 platform:1; // spawns 3 blocks below spawn height
    u32 platformmat:4;
};

struct mb64_settings_button {
    char *str;
    u8 *value;
    char **nametable;
    u8 size;
    char *(*nameFunc)(s32, char *);
    void (*changedFunc)(void);
};

struct mb64_ui_button_type {
    u32 placeMode:2;
    u32 multiObj:1;
    u32 paramCount:8;

    union {
        u32 id;
        u8 *idList;
    };
    union {
        char *name;
        char **names;
    };
};

struct imbue_model {
    s16 model;
    u8 billboarded:1;
    u8 doShrink:1;
    u8 doMove:1;
    f32 scale;
    s16 spin;
};

struct ImbueData {
    u32 coins;
    u32 model;
    u32 color;
};

struct ExclamationBoxContents {
    u8 behParams;
    ModelID16 model;
    const BehaviorScript *behavior;
    u8 animState; //not shitcum
    u8 doRespawn;
    u8 numCoins;
};
