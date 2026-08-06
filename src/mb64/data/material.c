#include "mb64/gfx/tile.h"
#include "surface_terrains.h"
#include "mb64/gfx/mb64_textures.h"

struct mb64_material mb64_mat_table[] = {
    // Terrain
    {&mb64_tex_Grass,        MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Grass"},       // MB64_MAT_GRASS
    {&mb64_tex_VanillaGrass, MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Grass (Old)"}, // MB64_MAT_GRASS_OLD
    {&mb64_tex_CartoonGrass, MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Smooth Grass"},// MB64_MAT_CARTOON_GRASS
    {&mb64_tex_DarkGrass,    MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Dark Grass"},  // MB64_MAT_DARK_GRASS
    {&mb64_tex_HGrass,       MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Cave Grass"},  // MB64_MAT_HMC_GRASS
    {&mb64_tex_OrangeGrass,  MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Orange Grass"},// MB64_MAT_ORANGE_GRASS
    {&mb64_tex_RedGrass,     MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Red Grass"},   // MB64_MAT_RED_GRASS
    {&mb64_tex_PurpleGrass,  MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Purple Grass"},// MB64_MAT_PURPLE_GRASS
    {&mb64_tex_Sand,         MAT_OPAQUE, FALSE, SURFACE_SAND,         "Sand"},        // MB64_MAT_SAND
    {&mb64_tex_JRBSand,      MAT_OPAQUE, FALSE, SURFACE_SAND,         "Ocean Sand"},  // MB64_MAT_JRB_SAND
    {&mb64_tex_Snow,         MAT_OPAQUE, FALSE, SURFACE_SNOW,         "Snow"},        // MB64_MAT_SNOW
    {&mb64_tex_VanillaSnow,  MAT_OPAQUE, FALSE, SURFACE_SNOW,         "Snow (Old)"},  // MB64_MAT_SNOW_OLD
    {&mb64_tex_Dirt,         MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Dirt"},        // MB64_MAT_DIRT
    {&mb64_tex_SandDirt,     MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Sandy Dirt"},  // MB64_MAT_SANDDIRT
    {&mb64_tex_LightDirt,    MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Light Dirt"},  // MB64_MAT_LIGHTDIRT
    {&mb64_tex_HDirt,        MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Cave Dirt"},   // MB64_MAT_HMC_DIRT
    {&mb64_tex_RockyDirt,    MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Rocky Dirt"},  // MB64_MAT_ROCKY_DIRT
    {&mb64_tex_VanillaDirt,  MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY,  "Dirt (Old)"}, // MB64_MAT_DIRT_OLD
    {&mb64_tex_WavyDirt,     MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Wavy Dirt"},   // MB64_MAT_WAVY_DIRT
    {&mb64_tex_WavyDirtBlue, MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Wavy Dirt (Blue)"}, // MB64_MAT_WAVY_DIRT_BLUE
    {&mb64_tex_SnowDirt,     MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Snowy Dirt"},  // MB64_MAT_SNOWDIRT
    {&mb64_tex_PurpleDirt,   MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Purple Dirt"}, // MB64_MAT_PURPLE_DIRT
    {&mb64_tex_HLakewall,    MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Clay"},        // MB64_MAT_HMC_LAKEGRASS

    // Stone
    {&mb64_tex_StoneSide,     MAT_OPAQUE, FALSE, SURFACE_DEFAULT,      "White Stone"},     // MB64_MAT_STONE
    {&mb64_tex_HStone,        MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Cave Stone"},      // MB64_MAT_HMC_STONE
    {&mb64_tex_HMazefloor,    MAT_OPAQUE, FALSE, SURFACE_DEFAULT,      "Beige Stone"},     // MB64_MAT_HMC_MAZEFLOOR
    {&mb64_tex_CCMWall,       MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Green Stone"},     // MB64_MAT_CCM_ROCK
    {&mb64_tex_MountainFloor, MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Mountain Stone"},  // MB64_MAT_TTM_FLOOR
    {&mb64_tex_MountainRock,  MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Mountain Rock"},   // MB64_MAT_TTM_ROCK
    {&mb64_tex_Stone,         MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "White Rock"},      // MB64_MAT_COBBLESTONE
    {&mb64_tex_JRBWall,       MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Green Rock"},      // MB64_MAT_JRB_WALL
    {&mb64_tex_BlackStone,    MAT_OPAQUE, FALSE, SURFACE_DEFAULT,      "Black Rock"},      // MB64_MAT_GABBRO
    {&mb64_tex_RHRStone,      MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Scorched Rock"},   // MB64_MAT_RHR_STONE
    {&mb64_tex_LavaRock,      MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Volcanic Rocks"},  // MB64_MAT_LAVA_ROCKS
    {&mb64_tex_VolcanicRock,  MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Volcanic Wall"},   // MB64_MAT_VOLCANO_WALL
    {&mb64_tex_RHRBasalt,     MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Basalt"},          // MB64_MAT_RHR_BASALT
    {&mb64_tex_Obsidian,      MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Obsidian"},        // MB64_MAT_OBSIDIAN
    {&mb64_tex_CastleCobble,  MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Plum Concrete"},   // MB64_MAT_CASTLE_STONE
    {&mb64_tex_JRBUnderwater, MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Ocean Floor"},     // MB64_MAT_JRB_UNDERWATER
    {&mb64_tex_SnowRock,      MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Snowy Rock"},      // MB64_MAT_SNOW_ROCK
    {&mb64_tex_IcyRock,       MAT_OPAQUE, TRUE,  SURFACE_VERY_SLIPPERY, "Icy Rock"},       // MB64_MAT_ICY_ROCK
    {&mb64_tex_DStone,        MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Cobblestone (1)"}, // MB64_MAT_DESERT_STONE
    {&mb64_tex_RHRObsidian,   MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Cobblestone (2)"}, // MB64_MAT_RHR_OBSIDIAN
    {&mb64_tex_JRBStone,      MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Cobblestone (3)"}, // MB64_MAT_JRB_STONE

    // Bricks
    {&mb64_tex_Bricks,           MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Stone Bricks"},     // MB64_MAT_BRICKS
    {&mb64_tex_DBrick,           MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Desert Bricks"},    // MB64_MAT_DESERT_BRICKS
    {&mb64_tex_RHRBrick,         MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Scorched Bricks"},  // MB64_MAT_RHR_BRICK
    {&mb64_tex_HBrick,           MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Cave Bricks"},      // MB64_MAT_HMC_BRICK
    {&mb64_tex_LightBrownBricks, MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,    "Fortress Bricks"},  // MB64_MAT_LIGHTBROWN_BRICK
    {&mb64_tex_BrownBricks,      MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Brown Bricks (1)"}, // MB64_MAT_WDW_BRICK
    {&mb64_tex_TTMBricks,        MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Brown Bricks (2)"}, // MB64_MAT_TTM_BRICK
    {&mb64_tex_CBrick,           MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Castle Bricks"},    // MB64_MAT_C_BRICK
    {&mb64_tex_BBHBricks,        MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Red Bricks (1)"},   // MB64_MAT_BBH_BRICKS
    {&mb64_tex_RoofBricks,       MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Red Bricks (2)"},   // MB64_MAT_ROOF_BRICKS
    {&mb64_tex_COutsideBricks,   MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "White Bricks (1)"}, // MB64_MAT_C_OUTSIDE_BRICK
    {&mb64_tex_SnowBricks,       MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "White Bricks (2)"}, // MB64_MAT_SNOW_BRICKS
    {&mb64_tex_JRBBricks,        MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Ocean Bricks"},     // MB64_MAT_JRB_BRICKS 
    {&mb64_tex_SnowTileSide,     MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Blue Bricks"},      // MB64_MAT_SNOW_TILE_SIDE
    {&mb64_tex_TileBricks,       MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Mixed Bricks"},     // MB64_MAT_TILESBRICKS

    // Tiling
    {&mb64_tex_Tiles,          MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Checkered Tiling"}, // MB64_MAT_TILES
    {&mb64_tex_CTiles,         MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Castle Tiling"},    // MB64_MAT_C_TILES
    {&mb64_tex_DTiles,         MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Desert Tiling"},    // MB64_MAT_DESERT_TILES
    {&mb64_tex_VBlueTiles,     MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Blue Tiling (1)"},  // MB64_MAT_VP_BLUETILES
    {&mb64_tex_SnowTiles,      MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Blue Tiling (2)"},  // MB64_MAT_SNOW_TILES
    {&mb64_tex_JRBTileTop,     MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Ocean Tiling (1)"}, // MB64_MAT_JRB_TILETOP
    {&mb64_tex_JRBTileSide,    MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Ocean Tiling (2)"}, // MB64_MAT_JRB_TILESIDE
    {&mb64_tex_HTileTop,       MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Dark Tiling"},     // MB64_MAT_HMC_TILES
    {&mb64_tex_GraniteTiles,   MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Granite Tiling"},   // MB64_MAT_GRANITE_TILES
    {&mb64_tex_RHRTiles,       MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Black Tiling"},    // MB64_MAT_RHR_TILES
    {&mb64_tex_VTiles,         MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Grey Tiling"},     // MB64_MAT_VP_TILES
    {&mb64_tex_DiamondPattern, MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Diamond Pattern"},  // MB64_MAT_DIAMOND_PATTERN
    {&mb64_tex_CStone,         MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Hex Tiling"},       // MB64_MAT_C_STONETOP
    {&mb64_tex_SnowBrickTiles, MAT_OPAQUE, FALSE, SURFACE_DEFAULT,      "Diamond Tiling"},   // MB64_MAT_SNOW_BRICK_TILES

    // Cut Stone
    {&mb64_tex_DStoneBlock,     MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, "Block"},           // MB64_MAT_DESERT_BLOCK
    {&mb64_tex_VBlock,          MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Smooth Block"},    // MB64_MAT_VP_BLOCK
    {&mb64_tex_BBHWall,         MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Mansion Wall"},    // MB64_MAT_BBH_STONE
    {&mb64_tex_BBHStonePattern, MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Chiseled Wall"},   // MB64_MAT_BBH_STONE_PATTERN
    {&mb64_tex_LauncherTex,     MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Patterned Block"}, // MB64_MAT_PATTERNED_BLOCK
    {&mb64_tex_HTileSide,       MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Black Slabs"},     // MB64_MAT_HMC_SLAB
    {&mb64_tex_RHRPattern,      MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Chiseled Block"},  // MB64_MAT_RHR_BLOCK
    {&mb64_tex_GraniteBlock,    MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, "Granite Block"},   // MB64_MAT_GRANITE_BLOCK
    {&mb64_tex_CStoneSide,      MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Stone Slab"},      // MB64_MAT_C_STONESIDE
    {&mb64_tex_CPillar,         MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Castle Pillar"},   // MB64_MAT_C_PILLAR
    {&mb64_tex_BBHPillar,       MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Mansion Pillar"},  // MB64_MAT_BBH_PILLAR
    {&mb64_tex_RHRPillar,       MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, "Scorched Pillar"}, // MB64_MAT_RHR_PILLAR

    // Wood
    {&mb64_tex_Wood,             MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Planks (1)"},    // MB64_MAT_WOOD
    {&mb64_tex_BBHWoodWall,      MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Planks (2)"},    // MB64_MAT_BBH_WOOD_WALL
    {&mb64_tex_BBHWoodFloor,     MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Dark Planks"},   // MB64_MAT_BBH_WOOD_FLOOR
    {&mb64_tex_CWood,            MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Castle Planks"}, // MB64_MAT_C_WOOD
    {&mb64_tex_JRBWood,          MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Docks"},         // MB64_MAT_JRB_WOOD
    {&mb64_tex_JRBShipSide,      MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Ship Planks"},   // MB64_MAT_JRB_SHIPSIDE
    {&mb64_tex_JRBShipTop,       MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Ship Decking"},  // MB64_MAT_JRB_SHIPTOP
    {&mb64_tex_BBHHauntedPlanks, MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Spooky Planks"}, // MB64_MAT_BBH_HAUNTED_PLANKS
    {&mb64_tex_BBHRoof,          MAT_OPAQUE, FALSE, SURFACE_CREAKWOOD,    "Mansion Roof"},  // MB64_MAT_BBH_ROOF
    {&mb64_tex_SolidWood,        MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Wood (Old)"},    // MB64_MAT_SOLID_WOOD
    {&mb64_tex_RHRWood,          MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Scorched Wood"}, // MB64_MAT_RHR_WOOD

    // Metal
    {&mb64_tex_BBHMetal,        MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Metal Flooring"},   // MB64_MAT_BBH_METAL
    {&mb64_tex_JRBMetalSide,    MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Metal Sheet"},      // MB64_MAT_JRB_METALSIDE
    {&mb64_tex_JRBMetal,        MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Metal Plating"},    // MB64_MAT_JRB_METAL
    {&mb64_tex_CBasementWall,   MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Basement Plating"}, // MB64_MAT_C_BASEMENTWALL
    {&mb64_tex_DTiles2,         MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Desert Plating"},   // MB64_MAT_DESERT_TILES2
    {&mb64_tex_VRustyBlock,     MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Rusted Block"},     // MB64_MAT_VP_RUSTYBLOCK

    // Other
    {&mb64_tex_CCarpet,      MAT_OPAQUE, FALSE, SURFACE_GRASS,         "Carpet"},         // MB64_MAT_C_CARPET
    {&mb64_tex_CWall,        MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,       "Castle Wall"},    // MB64_MAT_C_WALL
    {&mb64_tex_Roof,         MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY,  "Roof"},           // MB64_MAT_ROOF
    {&mb64_tex_CRoof,        MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY,  "Castle Roof"},    // MB64_MAT_C_ROOF
    {&mb64_tex_SnowRoof,     MAT_OPAQUE, TRUE,  SURFACE_VERY_SLIPPERY, "Blue Roof"},      // MB64_MAT_SNOW_ROOF
    {&mb64_tex_BBHWindow,    MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,       "Window"},         // MB64_MAT_BBH_WINDOW
    {&mb64_tex_HLight,       MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,       "Lantern"},        // MB64_MAT_HMC_LIGHT
    {&mb64_tex_Caution,      MAT_OPAQUE, FALSE, SURFACE_DEFAULT,       "Hazard Stripes"}, // MB64_MAT_VP_CAUTION
    {&mb64_tex_RRBlocks,     MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,       "Rainbow Blocks"},  // MB64_MAT_RR_BLOCKS
    {&mb64_tex_StuddedFloor, MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Studded Tile"},  // MB64_MAT_STUDDED_TILE
    {&mb64_tex_YellowBlock,  MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,     "Yellow Block"},   // MB64_MAT_TTC_BLOCK
    {&mb64_tex_TTCSide,      MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,       "Clock Platform"}, // MB64_MAT_TTC_SIDE
    {&mb64_tex_TTCWall,      MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,       "Clock Exterior"}, // MB64_MAT_TTC_WALL
    {&mb64_tex_FlowerTop,    MAT_OPAQUE, FALSE, SURFACE_GRASS,         "Flowers"},        // MB64_MAT_FLOWERS

    // Hazards
    {&mb64_tex_Lava,        MAT_OPAQUE, TRUE,  SURFACE_BURNING_BUBBLES,   "Lava"},           // MB64_MAT_LAVA
    {&mb64_tex_VanillaLava, MAT_OPAQUE, TRUE,  SURFACE_BURNING_BUBBLES,  "Lava (Old)"},     // MB64_MAT_LAVA_OLD
    {&mb64_tex_ServerAcid,  MAT_OPAQUE, TRUE,  SURFACE_BURNING_ICE,       "Server Acid"},    // MB64_MAT_SERVER_ACID
    {&mb64_tex_BurningIce,  MAT_OPAQUE, TRUE,  SURFACE_BURNING_ICE,       "Hazard Ice"},     // MB64_MAT_BURNING_ICE
    {&mb64_tex_Quicksand,   MAT_OPAQUE, TRUE,  SURFACE_INSTANT_QUICKSAND, "Quicksand"},      // MB64_MAT_QUICKSAND
    {&mb64_tex_Slowsand,    MAT_OPAQUE, FALSE, SURFACE_DEEP_QUICKSAND,    "Slow Quicksand"}, // MB64_MAT_DESERT_SLOWSAND
    {&mb64_tex_Void,        MAT_OPAQUE, TRUE,  SURFACE_INSTANT_QUICKSAND, "Cosmic Void"},           // MB64_MAT_VP_VOID

    // Seethrough
    {&mb64_tex_RHRMesh, MAT_CUTOUT,      TRUE,  SURFACE_HANGABLE_MESH, "Mesh"},         // MB64_MAT_RHR_MESH
    {&mb64_tex_VPMesh,  MAT_CUTOUT,      TRUE,  SURFACE_HANGABLE_MESH, "Fine Mesh"},    // MB64_MAT_VP_MESH
    {&mb64_tex_HMesh,   MAT_CUTOUT,      TRUE,  SURFACE_HANGABLE_MESH, "Red Grille"},   // MB64_MAT_HMC_MESH
    {&mb64_tex_BBHMesh, MAT_CUTOUT,      TRUE,  SURFACE_HANGABLE_MESH, "Red Mesh"},     // MB64_MAT_BBH_MESH
    {&mb64_tex_GratePink, MAT_CUTOUT,    TRUE,  SURFACE_HANGABLE_MESH, "Pink Mesh"},    // MB64_MAT_PINK_MESH
    {&mb64_tex_TTCGrate, MAT_CUTOUT,     TRUE,  SURFACE_HANGABLE_MESH, "Clock Grille"}, // MB64_MAT_TTC_MESH
    {&mb64_tex_Ice,     MAT_TRANSPARENT, FALSE, SURFACE_ICE,           "Ice"},          // MB64_MAT_ICE
    {&mb64_tex_Crystal, MAT_TRANSPARENT, FALSE, SURFACE_CRYSTAL,       "Crystal"},      // MB64_MAT_CRYSTAL
    {&mb64_tex_Screen,  MAT_DECAL,       TRUE,  SURFACE_DEFAULT,       "Screen"},       // MB64_MAT_VP_SCREEN

    // Retro
    {&mb64_tex_RetroGround,     MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_RETRO_GROUND
    {&mb64_tex_RetroBrick,      MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      NULL}, // MB64_MAT_RETRO_BRICKS
    {&mb64_tex_RetroTreeTop,    MAT_OPAQUE, TRUE, SURFACE_GRASS,        NULL}, // MB64_MAT_RETRO_TREETOP
    {&mb64_tex_RetroTree,       MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      NULL}, // MB64_MAT_RETRO_TREEPLAT
    {&mb64_tex_RetroBlock,      MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_RETRO_BLOCK
    {&mb64_tex_RetroBGround,    MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_RETRO_BLUEGROUND
    {&mb64_tex_RetroBBrick,     MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      NULL}, // MB64_MAT_RETRO_BLUEBRICKS
    {&mb64_tex_RetroBBlock,     MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_RETRO_BLUEBLOCK
    {&mb64_tex_RetroWBrick,     MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      NULL}, // MB64_MAT_RETRO_WHITEBRICK
    {&mb64_tex_RetroLava,       MAT_OPAQUE, TRUE, SURFACE_BURNING,      NULL}, // MB64_MAT_RETRO_LAVA
    {&mb64_tex_RetroUnderwater, MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_RETRO_UNDERWATERGROUND

    // Minecraft
    {&mb64_tex_MCDirt,        MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_MC_DIRT
    {&mb64_tex_MCGrassTop,    MAT_OPAQUE, TRUE, SURFACE_GRASS,        NULL}, // MB64_MAT_MC_GRASS
    {&mb64_tex_MCCobblestone, MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_MC_COBBLESTONE
    {&mb64_tex_MCStone,       MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      NULL}, // MB64_MAT_MC_STONE
    {&mb64_tex_MCOakLogTop,   MAT_OPAQUE, TRUE, SURFACE_CREAKWOOD,    NULL}, // MB64_MAT_MC_OAK_LOG_TOP
    {&mb64_tex_MCOakLogSide,  MAT_OPAQUE, TRUE, SURFACE_CREAKWOOD,    NULL}, // MB64_MAT_MC_OAK_LOG_SIDE
    {&mb64_tex_MCOakLeaves,   MAT_CUTOUT, TRUE, SURFACE_GRASS,        NULL}, // MB64_MAT_MC_OAK_LEAVES
    {&mb64_tex_MCWoodPlanks,  MAT_OPAQUE, TRUE, SURFACE_CREAKWOOD,    NULL}, // MB64_MAT_MC_WOOD_PLANKS
    {&mb64_tex_MCSand,        MAT_OPAQUE, TRUE, SURFACE_SAND,         NULL}, // MB64_MAT_MC_SAND
    {&mb64_tex_MCBricks,      MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      NULL}, // MB64_MAT_MC_BRICKS
    {&mb64_tex_MCLava,        MAT_OPAQUE, TRUE, SURFACE_BURNING,      NULL}, // MB64_MAT_MC_LAVA
    {&mb64_tex_MCFlowingLava, MAT_OPAQUE, TRUE, SURFACE_BURNING,      NULL}, // MB64_MAT_MC_FLOWING_LAVA
    {&mb64_tex_MCGlass,       MAT_CUTOUT_NOCULL, TRUE, SURFACE_VANISH_CAP_WALLS, NULL}, // MB64_MAT_MC_GLASS
};

u32 mb64_render_mode_table[] = {
    /* MAT_OPAQUE */        G_RM_ZB_OPA_SURF    | G_RM_ZB_OPA_SURF2,
    /* MAT_DECAL */         G_RM_TEX_EDGE_DECAL | G_RM_TEX_EDGE_DECAL2,
    /* MAT_CUTOUT */        G_RM_AA_ZB_TEX_EDGE | G_RM_AA_ZB_TEX_EDGE2,
    /* MAT_CUTOUT_NOCULL */ G_RM_AA_ZB_TEX_EDGE | G_RM_AA_ZB_TEX_EDGE2,
    /* MAT_TRANSPARENT */   G_RM_AA_ZB_XLU_SURF | G_RM_AA_ZB_XLU_SURF2,
    /* MAT_SCREEN */        G_RM_VPLEX_SCREEN   | G_RM_VPLEX_SCREEN2,
};

enum mb64_fences {
    MB64_FENCE_NORMAL,
    MB64_FENCE_WOOD2,
    MB64_FENCE_DESERT,
    MB64_FENCE_BARBED,
    MB64_FENCE_RHR,
    MB64_FENCE_HMC,
    MB64_FENCE_CASTLE,
    MB64_FENCE_VIRTUAPLEX,
    MB64_FENCE_BBH,
    MB64_FENCE_JRB,
    MB64_FENCE_SNOW2,
    MB64_FENCE_SNOW,
    MB64_FENCE_RETRO,
    MB64_FENCE_MC,
};

const struct texture_define *mb64_fence_texs[] = {
    &mb64_tex_Fence,
    &mb64_tex_WoodenFence,
    &mb64_tex_DFence,
    &mb64_tex_BarbedWire,
    &mb64_tex_RHRFence,
    &mb64_tex_HFence,
    &mb64_tex_CFence,
    &mb64_tex_VPFence,
    &mb64_tex_BBHFence,
    &mb64_tex_JRBFence,
    &mb64_tex_SnowFence2,
    &mb64_tex_SnowFence,
    &mb64_tex_RetroFence,
    &mb64_tex_MCFence,
};

enum mb64_bars {
    MB64_BAR_GENERIC,
    MB64_BAR_RHR,
    MB64_BAR_VP,
    MB64_BAR_HMC,
    MB64_BAR_BBH,
    MB64_BAR_LLL,
    MB64_BAR_TTC,
    MB64_BAR_DESERT,
    MB64_BAR_BOB,
    MB64_BAR_RETRO,
    MB64_BAR_MC,
};
const struct texture_define *mb64_bar_texs[][2] = {
    {&mb64_tex_IronBars,   &mb64_tex_IronBarsTop},
    {&mb64_tex_RHRMesh,    &mb64_tex_ChainTop},
    {&mb64_tex_VPMesh,     &mb64_tex_ChainTop},
    {&mb64_tex_HMesh,      &mb64_tex_HMCTop},
    {&mb64_tex_BBHMesh,    &mb64_tex_HMCTop},
    {&mb64_tex_GratePink,  &mb64_tex_ChainTopPink},
    {&mb64_tex_TTCGrate,   &mb64_tex_TTCGrateTop},
    {&mb64_tex_DMesh,      &mb64_tex_DesertMeshTop},
    {&mb64_tex_BOBBars,    &mb64_tex_BOBBarsTop},
    {&mb64_tex_RetroMesh,  &mb64_tex_RetroMeshTop},
    {&mb64_tex_MCIronBars, &mb64_tex_MCIronBarsTop},
};

enum mb64_water {
    MB64_WATER_DEFAULT,
    MB64_WATER_GREEN,
    MB64_WATER_RETRO,
    MB64_WATER_MC,
};

const struct texture_define *mb64_water_texs[] = {
    &mb64_tex_Water,
    &mb64_tex_GreenWater,
    &mb64_tex_RetroWater,
    &mb64_tex_MCWater,
};

struct mb64_topmaterial mb64_topmat_table[19] = {
    {MB64_MAT_GRASS,         &mb64_tex_GrassSide},
    {MB64_MAT_SAND,          &mb64_tex_SandSide},
    {MB64_MAT_SNOW,          &mb64_tex_SnowSide},
    {MB64_MAT_TILES,         &mb64_tex_TileEdge},
    {MB64_MAT_C_STONETOP,    &mb64_tex_CastleHexRim},
    {MB64_MAT_HMC_GRASS,     &mb64_tex_HGrassSide},
    {MB64_MAT_BBH_METAL,     &mb64_tex_BBHMetalSide},
    {MB64_MAT_BBH_STONE,     &mb64_tex_BBHMetalSide},
    {MB64_MAT_JRB_TILETOP,   &mb64_tex_JRBTileRim},
    {MB64_MAT_SNOW_TILES,    &mb64_tex_SnowTileRim},
    {MB64_MAT_FLOWERS,       &mb64_tex_FlowerEdge},
    {MB64_MAT_RETRO_TREETOP, &mb64_tex_RetroTreeSide},
    {MB64_MAT_MC_GRASS,      &mb64_tex_MCGrassEdge},
    {MB64_MAT_LAVA_ROCKS,    &mb64_tex_LavaRockEdge},
    {MB64_MAT_DARK_GRASS,    &mb64_tex_DarkGrassSide},
    {MB64_MAT_CARTOON_GRASS, &mb64_tex_CartoonGrassSide},
    {MB64_MAT_ORANGE_GRASS,  &mb64_tex_OrangeGrassSide},
    {MB64_MAT_RED_GRASS,     &mb64_tex_RedGrassSide},
    {MB64_MAT_PURPLE_GRASS,  &mb64_tex_PurpleGrassSide},
};

struct mb64_theme mb64_theme_table[] = {
    // GENERIC
    {
        {
            {MB64_MAT_DIRT,        MB64_MAT_GRASS,     "Grass"},
            {MB64_MAT_BRICKS,      MB64_MAT_BRICKS,    "Bricks"},
            {MB64_MAT_COBBLESTONE, MB64_MAT_STONE,     "Rock"},
            {MB64_MAT_TILESBRICKS, MB64_MAT_TILES,     "Tiling"},
            {MB64_MAT_ROOF,        MB64_MAT_ROOF,      "Roof"},
            {MB64_MAT_WOOD,        MB64_MAT_WOOD,      "Wood"},
            {MB64_MAT_SANDDIRT,    MB64_MAT_SAND,      "Sand"},
            {MB64_MAT_SNOWDIRT,    MB64_MAT_SNOW,      "Snow"},
            {MB64_MAT_LAVA,        MB64_MAT_LAVA,      "Lava"},
            {MB64_MAT_QUICKSAND,   MB64_MAT_QUICKSAND, "Quicksand"},
        },
        MB64_FENCE_NORMAL, MB64_MAT_STONE, MB64_BAR_GENERIC, MB64_WATER_DEFAULT
    },
    // DESERT
    {
        {
            {MB64_MAT_SANDDIRT,        MB64_MAT_SAND,            "Sand"},
            {MB64_MAT_DESERT_BRICKS,   MB64_MAT_DESERT_BRICKS,   "Bricks"},
            {MB64_MAT_DESERT_STONE,    MB64_MAT_DESERT_STONE,    "Cobblestone"},
            {MB64_MAT_DESERT_TILES,    MB64_MAT_DESERT_TILES,    "Tiling"},
            {MB64_MAT_DESERT_BLOCK,    MB64_MAT_DESERT_BLOCK,    "Stone Block"},
            {MB64_MAT_DESERT_SLOWSAND, MB64_MAT_DESERT_SLOWSAND, "Slow Quicksand"},
            {MB64_MAT_DESERT_BRICKS,   MB64_MAT_DESERT_TILES2,   "Plating"},
            {MB64_MAT_DIRT,            MB64_MAT_GRASS,           "Grass"},
            {MB64_MAT_LAVA,            MB64_MAT_LAVA,            "Lava"},
            {MB64_MAT_QUICKSAND,       MB64_MAT_QUICKSAND,       "Quicksand"},
        },
        MB64_FENCE_DESERT, MB64_MAT_DESERT_TILES2, MB64_BAR_DESERT, MB64_WATER_GREEN
    },
    // LAVA
    {
        {
            {MB64_MAT_RHR_STONE,   MB64_MAT_RHR_OBSIDIAN, "Rock"},
            {MB64_MAT_RHR_BRICK,   MB64_MAT_RHR_OBSIDIAN, "Bricks"},
            {MB64_MAT_RHR_BASALT,  MB64_MAT_RHR_BASALT,   "Basalt"},
            {MB64_MAT_RHR_TILES,   MB64_MAT_RHR_TILES,    "Tiling"},
            {MB64_MAT_RHR_BLOCK,   MB64_MAT_RHR_BLOCK,    "Stone Block"},
            {MB64_MAT_RHR_WOOD,    MB64_MAT_RHR_WOOD,     "Wood"},
            {MB64_MAT_RHR_PILLAR,  MB64_MAT_RHR_TILES,    "Pillar"},
            {MB64_MAT_RHR_MESH,    MB64_MAT_RHR_MESH,     "Mesh"},
            {MB64_MAT_LAVA,        MB64_MAT_LAVA,         "Lava"},
            {MB64_MAT_SERVER_ACID, MB64_MAT_SERVER_ACID,  "Server Acid"},
        },
        MB64_FENCE_RHR, MB64_MAT_RHR_PILLAR, MB64_BAR_RHR, MB64_WATER_DEFAULT
    },
    // CAVE
    {
        {
            {MB64_MAT_HMC_DIRT,      MB64_MAT_HMC_GRASS,     "Grass"},
            {MB64_MAT_HMC_BRICK,     MB64_MAT_HMC_MAZEFLOOR, "Bricks"},
            {MB64_MAT_HMC_STONE,     MB64_MAT_HMC_STONE,     "Rock"},
            {MB64_MAT_HMC_SLAB,      MB64_MAT_HMC_TILES,     "Tiling"},
            {MB64_MAT_HMC_BRICK,     MB64_MAT_HMC_GRASS,     "Grassy Bricks"},
            {MB64_MAT_HMC_LAKEGRASS, MB64_MAT_HMC_GRASS,     "Lake Wall"},
            {MB64_MAT_HMC_LIGHT,     MB64_MAT_HMC_LIGHT,     "Light"},
            {MB64_MAT_HMC_MESH,      MB64_MAT_HMC_MESH,      "Grille"},
            {MB64_MAT_LAVA,          MB64_MAT_LAVA,          "Lava"},
            {MB64_MAT_QUICKSAND,     MB64_MAT_QUICKSAND,     "Quicksand"},
        },
        MB64_FENCE_HMC, MB64_MAT_HMC_LAKEGRASS, MB64_BAR_HMC, MB64_WATER_GREEN
    },
    // CASTLE
    {
        {
            {MB64_MAT_C_WOOD,         MB64_MAT_C_TILES,        "Tiling"},
            {MB64_MAT_C_BRICK,        MB64_MAT_C_TILES,        "Tiling (Bricks)"},
            {MB64_MAT_C_STONESIDE,    MB64_MAT_C_STONETOP,     "Tiling (Stone)"},
            {MB64_MAT_C_WOOD,         MB64_MAT_C_CARPET,       "Carpet"},
            {MB64_MAT_C_ROOF,         MB64_MAT_C_ROOF,         "Roof"},
            {MB64_MAT_C_WALL,         MB64_MAT_C_WALL,         "Castle Wall"},
            {MB64_MAT_C_PILLAR,       MB64_MAT_C_STONETOP,     "Pillar"},
            {MB64_MAT_C_BASEMENTWALL, MB64_MAT_C_BASEMENTWALL, "Basement Wall"},
            {MB64_MAT_LAVA,           MB64_MAT_LAVA,           "Lava"},
            {MB64_MAT_C_OUTSIDEBRICK, MB64_MAT_C_OUTSIDEBRICK, "Castle Bricks"},
        },
        MB64_FENCE_CASTLE, MB64_MAT_C_STONESIDE, MB64_BAR_VP, MB64_WATER_DEFAULT
    },
    // VIRTUAPLEX
    {
        {
            {MB64_MAT_VP_BLOCK,      MB64_MAT_VP_BLOCK,      "Block"},
            {MB64_MAT_VP_TILES,      MB64_MAT_VP_TILES,      "Tiling"},
            {MB64_MAT_DIRT,          MB64_MAT_GRASS,         "Grass"},
            {MB64_MAT_VP_TILES,      MB64_MAT_VP_BLUETILES,  "Blue Tiling"},
            {MB64_MAT_VP_RUSTYBLOCK, MB64_MAT_VP_RUSTYBLOCK, "Rusted Block"},
            {MB64_MAT_VP_SCREEN,     MB64_MAT_VP_SCREEN,     "Screen"},
            {MB64_MAT_VP_CAUTION,    MB64_MAT_VP_CAUTION,    "Hazard Stripes"},
            {MB64_MAT_VP_BLOCK,      MB64_MAT_SNOW,          "Snowy Block"},
            {MB64_MAT_LAVA,          MB64_MAT_LAVA,          "Lava"},
            {MB64_MAT_VP_VOID,       MB64_MAT_VP_VOID,       "Cosmic Void"},
        },
        MB64_FENCE_VIRTUAPLEX, MB64_MAT_VP_CAUTION, MB64_BAR_VP, MB64_WATER_DEFAULT
    },
    // SNOW
    {
        {
            {MB64_MAT_SNOWDIRT,       MB64_MAT_SNOW,             "Snow"},
            {MB64_MAT_SNOW_BRICKS,    MB64_MAT_SNOW_BRICK_TILES, "Bricks"},
            {MB64_MAT_SNOW_ROCK,      MB64_MAT_SNOW_ROCK,        "Rock"},
            {MB64_MAT_SNOW_TILE_SIDE, MB64_MAT_SNOW_TILES,       "Tiling"},
            {MB64_MAT_SNOW_ROOF,      MB64_MAT_SNOW_ROOF,        "Roof"},
            {MB64_MAT_WOOD,           MB64_MAT_WOOD,             "Wood"},
            {MB64_MAT_CRYSTAL,        MB64_MAT_CRYSTAL,          "Crystal"},
            {MB64_MAT_ICE,            MB64_MAT_ICE,              "Ice"},
            {MB64_MAT_BURNING_ICE,    MB64_MAT_BURNING_ICE,      "Hazard Ice"},
            {MB64_MAT_LAVA,           MB64_MAT_LAVA,             "Lava"},
        },
        MB64_FENCE_SNOW, MB64_MAT_SNOW_TILE_SIDE, MB64_BAR_GENERIC, MB64_WATER_DEFAULT
    },
    // BBH
    {
        {
            {MB64_MAT_BBH_BRICKS,         MB64_MAT_BBH_STONE,          "Stone Floor"},
            {MB64_MAT_BBH_HAUNTED_PLANKS, MB64_MAT_BBH_HAUNTED_PLANKS, "Haunted Planks"},
            {MB64_MAT_BBH_STONE_PATTERN,  MB64_MAT_BBH_WOOD_FLOOR,     "Wood Floor"},
            {MB64_MAT_BBH_BRICKS,         MB64_MAT_BBH_METAL,          "Metal Floor"},
            {MB64_MAT_BBH_ROOF,           MB64_MAT_BBH_ROOF,           "Roof"},
            {MB64_MAT_BBH_WOOD_WALL,      MB64_MAT_BBH_WOOD_WALL,      "Wood"},
            {MB64_MAT_BBH_STONE,          MB64_MAT_BBH_STONE,          "Wall"},
            {MB64_MAT_BBH_PILLAR,         MB64_MAT_BBH_STONE,          "Pillar"},
            {MB64_MAT_LAVA,               MB64_MAT_LAVA,               "Lava"},
            {MB64_MAT_BBH_WINDOW,         MB64_MAT_BBH_WINDOW,         "Window"},
        },
        MB64_FENCE_BBH, MB64_MAT_BBH_BRICKS, MB64_BAR_BBH, MB64_WATER_DEFAULT
    },
    // JRB
    {
        {
            {MB64_MAT_JRB_STONE,      MB64_MAT_JRB_SAND,       "Sand"},
            {MB64_MAT_JRB_BRICKS,     MB64_MAT_JRB_BRICKS,     "Bricks"},
            {MB64_MAT_JRB_UNDERWATER, MB64_MAT_JRB_UNDERWATER, "Ocean Floor"},
            {MB64_MAT_JRB_TILESIDE,   MB64_MAT_JRB_TILETOP,    "Tiles"},
            {MB64_MAT_JRB_SHIPSIDE,   MB64_MAT_JRB_SHIPTOP,    "Wood (Ship)"},
            {MB64_MAT_JRB_METAL,      MB64_MAT_JRB_WOOD,       "Wood (Docks)"},
            {MB64_MAT_JRB_METALSIDE,  MB64_MAT_JRB_METAL,      "Metal"},
            {MB64_MAT_HMC_MESH,       MB64_MAT_HMC_MESH,       "Grille"},
            {MB64_MAT_JRB_WALL,       MB64_MAT_JRB_WALL,       "Wall"},
            {MB64_MAT_QUICKSAND,      MB64_MAT_QUICKSAND,      "Quicksand"},
        },
        MB64_FENCE_JRB, MB64_MAT_VP_CAUTION, MB64_BAR_HMC, MB64_WATER_DEFAULT
    },
    // RETRO
    {
        {
            {MB64_MAT_RETRO_GROUND,           MB64_MAT_RETRO_GROUND,           "Ground"},
            {MB64_MAT_RETRO_BRICKS,           MB64_MAT_RETRO_BRICKS,           "Bricks"},
            {MB64_MAT_RETRO_TREEPLAT,         MB64_MAT_RETRO_TREETOP,          "Treetop"},
            {MB64_MAT_RETRO_BLOCK,            MB64_MAT_RETRO_BLOCK,            "Block"},
            {MB64_MAT_RETRO_BLUEGROUND,       MB64_MAT_RETRO_BLUEGROUND,       "Blue Ground"},
            {MB64_MAT_RETRO_BLUEBRICKS,       MB64_MAT_RETRO_BLUEBRICKS,       "Blue Bricks"},
            {MB64_MAT_RETRO_BLUEBLOCK,        MB64_MAT_RETRO_BLUEBLOCK,        "Blue Block"},
            {MB64_MAT_RETRO_WHITEBRICK,       MB64_MAT_RETRO_WHITEBRICK,       "White Bricks"},
            {MB64_MAT_RETRO_LAVA,             MB64_MAT_RETRO_LAVA,             "Lava"},
            {MB64_MAT_RETRO_UNDERWATERGROUND, MB64_MAT_RETRO_UNDERWATERGROUND, "Underwater Tile"},
        },
        MB64_FENCE_RETRO, MB64_MAT_RETRO_BRICKS, MB64_BAR_RETRO, MB64_WATER_RETRO
    },
    // CUSTOM
    {
        {
            {0, 0, "Tile 1"},
            {0, 0, "Tile 2"},
            {0, 0, "Tile 3"},
            {0, 0, "Tile 4"},
            {0, 0, "Tile 5"},
            {0, 0, "Tile 6"},
            {0, 0, "Tile 7"},
            {0, 0, "Tile 8"},
            {0, 0, "Tile 9"},
            {0, 0, "Tile 10"},
        },
        0, 0, 0, 0
    },
    // MINECRAFT
    {
        {
            {MB64_MAT_MC_DIRT,         MB64_MAT_MC_GRASS,       "Grass"},
            {MB64_MAT_MC_COBBLESTONE,  MB64_MAT_MC_COBBLESTONE, "Cobblestone"},
            {MB64_MAT_MC_STONE,        MB64_MAT_MC_STONE,       "Stone"},
            {MB64_MAT_MC_OAK_LOG_SIDE, MB64_MAT_MC_OAK_LOG_TOP, "Oak Log"},
            {MB64_MAT_MC_OAK_LEAVES,   MB64_MAT_MC_OAK_LEAVES,  "Oak Leaves"},
            {MB64_MAT_MC_WOOD_PLANKS,  MB64_MAT_MC_WOOD_PLANKS, "Oak Planks"},
            {MB64_MAT_MC_SAND,         MB64_MAT_MC_SAND,        "Sand"},
            {MB64_MAT_MC_BRICKS,       MB64_MAT_MC_BRICKS,      "Bricks"},
            {MB64_MAT_MC_FLOWING_LAVA, MB64_MAT_MC_LAVA,        "Lava"},
            {MB64_MAT_MC_GLASS,        MB64_MAT_MC_GLASS,       "Glass"},
        },
        MB64_FENCE_MC, MB64_MAT_MC_OAK_LOG_SIDE, MB64_BAR_MC, MB64_WATER_MC
    },
};

struct mb64_custom_theme mb64_default_custom = {
    {
        MB64_MAT_DIRT,
        MB64_MAT_BRICKS,
        MB64_MAT_COBBLESTONE,
        MB64_MAT_TILESBRICKS,
        MB64_MAT_ROOF,
        MB64_MAT_WOOD,
        MB64_MAT_SANDDIRT,
        MB64_MAT_SNOWDIRT,
        MB64_MAT_LAVA,
        MB64_MAT_QUICKSAND,
    },
    {
        MB64_MAT_GRASS,
        MB64_MAT_TILES,
        MB64_MAT_STONE,
        MB64_MAT_TILES,
        MB64_MAT_ROOF,
        MB64_MAT_WOOD,
        MB64_MAT_SAND,
        MB64_MAT_SNOW,
        MB64_MAT_LAVA,
        MB64_MAT_QUICKSAND,
    },
    {1, 0, 1, 1, 0, 0, 1, 1, 0, 0},
    MB64_FENCE_NORMAL, MB64_MAT_STONE, MB64_BAR_GENERIC, MB64_WATER_DEFAULT,
};
struct mb64_custom_theme mb64_curr_custom_theme;
