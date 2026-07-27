#include "mb64/gfx/tile.h"
#include "surface_terrains.h"
#include "actors/maker/header.h"

extern Gfx mat_maker_MakerMCWater[];
extern Gfx mat_maker_MakerMCLava[];
extern Gfx mat_maker_MakerMCFlowingLava[];

struct mb64_material mb64_mat_table[] = {
    // Terrain
    {mat_maker_MakerGrass,        MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Grass"},       // MB64_MAT_GRASS
    {mat_maker_MakerVanillaGrass, MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Grass (Old)"}, // MB64_MAT_GRASS_OLD
    {mat_maker_MakerCartoonGrass, MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Smooth Grass"},// MB64_MAT_CARTOON_GRASS
    {mat_maker_MakerDarkGrass,    MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Dark Grass"},  // MB64_MAT_DARK_GRASS
    {mat_maker_MakerHGrass,       MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Cave Grass"},  // MB64_MAT_HMC_GRASS
    {mat_maker_MakerOrangeGrass,  MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Orange Grass"},// MB64_MAT_ORANGE_GRASS
    {mat_maker_MakerRedGrass,     MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Red Grass"},   // MB64_MAT_RED_GRASS
    {mat_maker_MakerPurpleGrass,  MAT_OPAQUE, FALSE, SURFACE_GRASS,        "Purple Grass"},// MB64_MAT_PURPLE_GRASS
    {mat_maker_MakerSand,         MAT_OPAQUE, FALSE, SURFACE_SAND,         "Sand"},        // MB64_MAT_SAND
    {mat_maker_MakerJRBSand,      MAT_OPAQUE, FALSE, SURFACE_SAND,         "Ocean Sand"},  // MB64_MAT_JRB_SAND
    {mat_maker_MakerSnow,         MAT_OPAQUE, FALSE, SURFACE_SNOW,         "Snow"},        // MB64_MAT_SNOW
    {mat_maker_MakerVanillaSnow,  MAT_OPAQUE, FALSE, SURFACE_SNOW,         "Snow (Old)"},  // MB64_MAT_SNOW_OLD
    {mat_maker_MakerDirt,         MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Dirt"},        // MB64_MAT_DIRT
    {mat_maker_MakerSandDirt,     MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Sandy Dirt"},  // MB64_MAT_SANDDIRT
    {mat_maker_MakerLightDirt,    MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Light Dirt"},  // MB64_MAT_LIGHTDIRT
    {mat_maker_MakerHDirt,        MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Cave Dirt"},   // MB64_MAT_HMC_DIRT
    {mat_maker_MakerRockyDirt,    MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Rocky Dirt"},  // MB64_MAT_ROCKY_DIRT
    {mat_maker_MakerVanillaDirt,  MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY,  "Dirt (Old)"}, // MB64_MAT_DIRT_OLD
    {mat_maker_MakerWavyDirt,     MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Wavy Dirt"},   // MB64_MAT_WAVY_DIRT
    {mat_maker_MakerWavyDirtBlue, MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Wavy Dirt (Blue)"}, // MB64_MAT_WAVY_DIRT_BLUE
    {mat_maker_MakerSnowDirt,     MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Snowy Dirt"},  // MB64_MAT_SNOWDIRT
    {mat_maker_MakerPurpleDirt,   MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Purple Dirt"}, // MB64_MAT_PURPLE_DIRT
    {mat_maker_MakerHLakewall,    MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Clay"},        // MB64_MAT_HMC_LAKEGRASS

    // Stone
    {mat_maker_MakerStoneSide,     MAT_OPAQUE, FALSE, SURFACE_DEFAULT,      "White Stone"},     // MB64_MAT_STONE
    {mat_maker_MakerHStone,        MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Cave Stone"},      // MB64_MAT_HMC_STONE
    {mat_maker_MakerHMazefloor,    MAT_OPAQUE, FALSE, SURFACE_DEFAULT,      "Beige Stone"},     // MB64_MAT_HMC_MAZEFLOOR
    {mat_maker_MakerCCMWall,       MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Green Stone"},     // MB64_MAT_CCM_ROCK
    {mat_maker_MakerMountainFloor, MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Mountain Stone"},  // MB64_MAT_TTM_FLOOR
    {mat_maker_MakerMountainRock,  MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Mountain Rock"},   // MB64_MAT_TTM_ROCK
    {mat_maker_MakerStone,         MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "White Rock"},      // MB64_MAT_COBBLESTONE
    {mat_maker_MakerJRBWall,       MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Green Rock"},      // MB64_MAT_JRB_WALL
    {mat_maker_MakerBlackStone,    MAT_OPAQUE, FALSE, SURFACE_DEFAULT,      "Black Rock"},      // MB64_MAT_GABBRO
    {mat_maker_MakerRHRStone,      MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Scorched Rock"},   // MB64_MAT_RHR_STONE
    {mat_maker_MakerLavaRock,      MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Volcanic Rocks"},  // MB64_MAT_LAVA_ROCKS
    {mat_maker_MakerVolcanicRock,  MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Volcanic Wall"},   // MB64_MAT_VOLCANO_WALL
    {mat_maker_MakerRHRBasalt,     MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Basalt"},          // MB64_MAT_RHR_BASALT
    {mat_maker_MakerObsidian,      MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Obsidian"},        // MB64_MAT_OBSIDIAN
    {mat_maker_MakerCastleCobble,  MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Plum Concrete"},   // MB64_MAT_CASTLE_STONE
    {mat_maker_MakerJRBUnderwater, MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Ocean Floor"},     // MB64_MAT_JRB_UNDERWATER
    {mat_maker_MakerSnowRock,      MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Snowy Rock"},      // MB64_MAT_SNOW_ROCK
    {mat_maker_MakerIcyRock,       MAT_OPAQUE, TRUE,  SURFACE_VERY_SLIPPERY, "Icy Rock"},       // MB64_MAT_ICY_ROCK
    {mat_maker_MakerDStone,        MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Cobblestone (1)"}, // MB64_MAT_DESERT_STONE
    {mat_maker_MakerRHRObsidian,   MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Cobblestone (2)"}, // MB64_MAT_RHR_OBSIDIAN
    {mat_maker_MakerJRBStone,      MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Cobblestone (3)"}, // MB64_MAT_JRB_STONE

    // Bricks
    {mat_maker_MakerBricks,           MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Stone Bricks"},     // MB64_MAT_BRICKS
    {mat_maker_MakerDBrick,           MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Desert Bricks"},    // MB64_MAT_DESERT_BRICKS
    {mat_maker_MakerRHRBrick,         MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Scorched Bricks"},  // MB64_MAT_RHR_BRICK
    {mat_maker_MakerHBrick,           MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Cave Bricks"},      // MB64_MAT_HMC_BRICK
    {mat_maker_MakerLightBrownBricks, MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,    "Fortress Bricks"},  // MB64_MAT_LIGHTBROWN_BRICK
    {mat_maker_MakerBrownBricks,      MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Brown Bricks (1)"}, // MB64_MAT_WDW_BRICK
    {mat_maker_MakerTTMBricks,        MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Brown Bricks (2)"}, // MB64_MAT_TTM_BRICK
    {mat_maker_MakerCBrick,           MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Castle Bricks"},    // MB64_MAT_C_BRICK
    {mat_maker_MakerBBHBricks,        MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Red Bricks (1)"},   // MB64_MAT_BBH_BRICKS
    {mat_maker_MakerRoofBricks,       MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Red Bricks (2)"},   // MB64_MAT_ROOF_BRICKS
    {mat_maker_MakerCOutsideBricks,   MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "White Bricks (1)"}, // MB64_MAT_C_OUTSIDE_BRICK
    {mat_maker_MakerSnowBricks,       MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "White Bricks (2)"}, // MB64_MAT_SNOW_BRICKS
    {mat_maker_MakerJRBBricks,        MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Ocean Bricks"},     // MB64_MAT_JRB_BRICKS 
    {mat_maker_MakerSnowTileSide,     MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Blue Bricks"},      // MB64_MAT_SNOW_TILE_SIDE
    {mat_maker_MakerTileBricks,       MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Mixed Bricks"},     // MB64_MAT_TILESBRICKS

    // Tiling
    {mat_maker_MakerTiles,          MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Checkered Tiling"}, // MB64_MAT_TILES
    {mat_maker_MakerCTiles,         MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Castle Tiling"},    // MB64_MAT_C_TILES
    {mat_maker_MakerDTiles,         MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Desert Tiling"},    // MB64_MAT_DESERT_TILES
    {mat_maker_MakerVBlueTiles,     MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Blue Tiling (1)"},  // MB64_MAT_VP_BLUETILES
    {mat_maker_MakerSnowTiles,      MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Blue Tiling (2)"},  // MB64_MAT_SNOW_TILES
    {mat_maker_MakerJRBTileTop,     MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Ocean Tiling (1)"}, // MB64_MAT_JRB_TILETOP
    {mat_maker_MakerJRBTileSide,    MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Ocean Tiling (2)"}, // MB64_MAT_JRB_TILESIDE
    {mat_maker_MakerHTileTop,       MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Dark Tiling"},     // MB64_MAT_HMC_TILES
    {mat_maker_MakerGraniteTiles,   MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Granite Tiling"},   // MB64_MAT_GRANITE_TILES
    {mat_maker_MakerRHRTiles,       MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Black Tiling"},    // MB64_MAT_RHR_TILES
    {mat_maker_MakerVTiles,         MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Grey Tiling"},     // MB64_MAT_VP_TILES
    {mat_maker_MakerDiamondPattern, MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Diamond Pattern"},  // MB64_MAT_DIAMOND_PATTERN
    {mat_maker_MakerCStone,         MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Hex Tiling"},       // MB64_MAT_C_STONETOP
    {mat_maker_MakerSnowBrickTiles, MAT_OPAQUE, FALSE, SURFACE_DEFAULT,      "Diamond Tiling"},   // MB64_MAT_SNOW_BRICK_TILES

    // Cut Stone
    {mat_maker_MakerDStoneBlock,     MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, "Block"},           // MB64_MAT_DESERT_BLOCK
    {mat_maker_MakerVBlock,          MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Smooth Block"},    // MB64_MAT_VP_BLOCK
    {mat_maker_MakerBBHWall,         MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Mansion Wall"},    // MB64_MAT_BBH_STONE
    {mat_maker_MakerBBHStonePattern, MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Chiseled Wall"},   // MB64_MAT_BBH_STONE_PATTERN
    {mat_maker_MakerLauncherTex,     MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Patterned Block"}, // MB64_MAT_PATTERNED_BLOCK
    {mat_maker_MakerHTileSide,       MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Black Slabs"},     // MB64_MAT_HMC_SLAB
    {mat_maker_MakerRHRPattern,      MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Chiseled Block"},  // MB64_MAT_RHR_BLOCK
    {mat_maker_MakerGraniteBlock,    MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, "Granite Block"},   // MB64_MAT_GRANITE_BLOCK
    {mat_maker_MakerCStoneSide,      MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Stone Slab"},      // MB64_MAT_C_STONESIDE
    {mat_maker_MakerCPillar,         MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Castle Pillar"},   // MB64_MAT_C_PILLAR
    {mat_maker_MakerBBHPillar,       MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      "Mansion Pillar"},  // MB64_MAT_BBH_PILLAR
    {mat_maker_MakerRHRPillar,       MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, "Scorched Pillar"}, // MB64_MAT_RHR_PILLAR

    // Wood
    {mat_maker_MakerWood,             MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Planks (1)"},    // MB64_MAT_WOOD
    {mat_maker_MakerBBHWoodWall,      MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Planks (2)"},    // MB64_MAT_BBH_WOOD_WALL
    {mat_maker_MakerBBHWoodFloor,     MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Dark Planks"},   // MB64_MAT_BBH_WOOD_FLOOR
    {mat_maker_MakerCWood,            MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Castle Planks"}, // MB64_MAT_C_WOOD
    {mat_maker_MakerJRBWood,          MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Docks"},         // MB64_MAT_JRB_WOOD
    {mat_maker_MakerJRBShipSide,      MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Ship Planks"},   // MB64_MAT_JRB_SHIPSIDE
    {mat_maker_MakerJRBShipTop,       MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Ship Decking"},  // MB64_MAT_JRB_SHIPTOP
    {mat_maker_MakerBBHHauntedPlanks, MAT_OPAQUE, TRUE,  SURFACE_CREAKWOOD,    "Spooky Planks"}, // MB64_MAT_BBH_HAUNTED_PLANKS
    {mat_maker_MakerBBHRoof,          MAT_OPAQUE, FALSE, SURFACE_CREAKWOOD,    "Mansion Roof"},  // MB64_MAT_BBH_ROOF
    {mat_maker_MakerSolidWood,        MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Wood (Old)"},    // MB64_MAT_SOLID_WOOD
    {mat_maker_MakerRHRWood,          MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY, "Scorched Wood"}, // MB64_MAT_RHR_WOOD

    // Metal
    {mat_maker_MakerBBHMetal,        MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Metal Flooring"},   // MB64_MAT_BBH_METAL
    {mat_maker_MakerJRBMetalSide,    MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Metal Sheet"},      // MB64_MAT_JRB_METALSIDE
    {mat_maker_MakerJRBMetal,        MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Metal Plating"},    // MB64_MAT_JRB_METAL
    {mat_maker_MakerCBasementWall,   MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Basement Plating"}, // MB64_MAT_C_BASEMENTWALL
    {mat_maker_MakerDTiles2,         MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Desert Plating"},   // MB64_MAT_DESERT_TILES2
    {mat_maker_MakerVRustyBlock,     MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,      "Rusted Block"},     // MB64_MAT_VP_RUSTYBLOCK

    // Other
    {mat_maker_MakerCCarpet,      MAT_OPAQUE, FALSE, SURFACE_GRASS,         "Carpet"},         // MB64_MAT_C_CARPET
    {mat_maker_MakerCWall,        MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,       "Castle Wall"},    // MB64_MAT_C_WALL
    {mat_maker_MakerRoof,         MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY,  "Roof"},           // MB64_MAT_ROOF
    {mat_maker_MakerCRoof,        MAT_OPAQUE, TRUE,  SURFACE_NOT_SLIPPERY,  "Castle Roof"},    // MB64_MAT_C_ROOF
    {mat_maker_MakerSnowRoof,     MAT_OPAQUE, TRUE,  SURFACE_VERY_SLIPPERY, "Blue Roof"},      // MB64_MAT_SNOW_ROOF
    {mat_maker_MakerBBHWindow,    MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,       "Window"},         // MB64_MAT_BBH_WINDOW
    {mat_maker_MakerHLight,       MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,       "Lantern"},        // MB64_MAT_HMC_LIGHT
    {mat_maker_MakerCaution,      MAT_OPAQUE, FALSE, SURFACE_DEFAULT,       "Hazard Stripes"}, // MB64_MAT_VP_CAUTION
    {mat_maker_MakerRRBlocks,     MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,       "Rainbow Blocks"},  // MB64_MAT_RR_BLOCKS
    {mat_maker_MakerStuddedFloor, MAT_OPAQUE, FALSE, SURFACE_NOT_SLIPPERY, "Studded Tile"},  // MB64_MAT_STUDDED_TILE
    {mat_maker_MakerYellowBlock,  MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,     "Yellow Block"},   // MB64_MAT_TTC_BLOCK
    {mat_maker_MakerTTCSide,      MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,       "Clock Platform"}, // MB64_MAT_TTC_SIDE
    {mat_maker_MakerTTCWall,      MAT_OPAQUE, TRUE,  SURFACE_DEFAULT,       "Clock Exterior"}, // MB64_MAT_TTC_WALL
    {mat_maker_MakerFlowerTop,    MAT_OPAQUE, FALSE, SURFACE_GRASS,         "Flowers"},        // MB64_MAT_FLOWERS

    // Hazards
    {mat_maker_MakerLava,        MAT_OPAQUE, TRUE,  SURFACE_BURNING_BUBBLES,   "Lava"},           // MB64_MAT_LAVA
    {mat_maker_MakerVanillaLava, MAT_OPAQUE, TRUE,  SURFACE_BURNING_BUBBLES,  "Lava (Old)"},     // MB64_MAT_LAVA_OLD
    {mat_maker_MakerServerAcid,  MAT_OPAQUE, TRUE,  SURFACE_BURNING_ICE,       "Server Acid"},    // MB64_MAT_SERVER_ACID
    {mat_maker_MakerBurningIce,  MAT_OPAQUE, TRUE,  SURFACE_BURNING_ICE,       "Hazard Ice"},     // MB64_MAT_BURNING_ICE
    {mat_maker_MakerQuicksand,   MAT_OPAQUE, TRUE,  SURFACE_INSTANT_QUICKSAND, "Quicksand"},      // MB64_MAT_QUICKSAND
    {mat_maker_MakerSlowsand,    MAT_OPAQUE, FALSE, SURFACE_DEEP_QUICKSAND,    "Slow Quicksand"}, // MB64_MAT_DESERT_SLOWSAND
    {mat_maker_MakerVoid,        MAT_OPAQUE, TRUE,  SURFACE_INSTANT_QUICKSAND, "Cosmic Void"},           // MB64_MAT_VP_VOID

    // Seethrough
    {mat_maker_MakerRHRMesh, MAT_CUTOUT,      TRUE,  SURFACE_HANGABLE_MESH, "Mesh"},         // MB64_MAT_RHR_MESH
    {mat_maker_MakerVPMesh,  MAT_CUTOUT,      TRUE,  SURFACE_HANGABLE_MESH, "Fine Mesh"},    // MB64_MAT_VP_MESH
    {mat_maker_MakerHMesh,   MAT_CUTOUT,      TRUE,  SURFACE_HANGABLE_MESH, "Red Grille"},   // MB64_MAT_HMC_MESH
    {mat_maker_MakerBBHMesh, MAT_CUTOUT,      TRUE,  SURFACE_HANGABLE_MESH, "Red Mesh"},     // MB64_MAT_BBH_MESH
    {mat_maker_MakerGratePink, MAT_CUTOUT,    TRUE,  SURFACE_HANGABLE_MESH, "Pink Mesh"},    // MB64_MAT_PINK_MESH
    {mat_maker_MakerTTCGrate, MAT_CUTOUT,     TRUE,  SURFACE_HANGABLE_MESH, "Clock Grille"}, // MB64_MAT_TTC_MESH
    {mat_maker_MakerIce,     MAT_TRANSPARENT, FALSE, SURFACE_ICE,           "Ice"},          // MB64_MAT_ICE
    {mat_maker_MakerCrystal, MAT_TRANSPARENT, FALSE, SURFACE_CRYSTAL,       "Crystal"},      // MB64_MAT_CRYSTAL
    {mat_maker_MakerScreen,  MAT_DECAL,       TRUE,  SURFACE_DEFAULT,       "Screen"},       // MB64_MAT_VP_SCREEN

    // Retro
    {mat_maker_MakerRetroGround,     MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_RETRO_GROUND
    {mat_maker_MakerRetroBrick,      MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      NULL}, // MB64_MAT_RETRO_BRICKS
    {mat_maker_MakerRetroTreeTop,    MAT_OPAQUE, TRUE, SURFACE_GRASS,        NULL}, // MB64_MAT_RETRO_TREETOP
    {mat_maker_MakerRetroTree,       MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      NULL}, // MB64_MAT_RETRO_TREEPLAT
    {mat_maker_MakerRetroBlock,      MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_RETRO_BLOCK
    {mat_maker_MakerRetroBGround,    MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_RETRO_BLUEGROUND
    {mat_maker_MakerRetroBBrick,     MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      NULL}, // MB64_MAT_RETRO_BLUEBRICKS
    {mat_maker_MakerRetroBBlock,     MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_RETRO_BLUEBLOCK
    {mat_maker_MakerRetroWBrick,     MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      NULL}, // MB64_MAT_RETRO_WHITEBRICK
    {mat_maker_MakerRetroLava,       MAT_OPAQUE, TRUE, SURFACE_BURNING,      NULL}, // MB64_MAT_RETRO_LAVA
    {mat_maker_MakerRetroUnderwater, MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_RETRO_UNDERWATERGROUND

    // Minecraft
    {mat_maker_MakerMCDirt,        MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_MC_DIRT
    {mat_maker_MakerMCGrassTop,    MAT_OPAQUE, TRUE, SURFACE_GRASS,        NULL}, // MB64_MAT_MC_GRASS
    {mat_maker_MakerMCCobblestone, MAT_OPAQUE, TRUE, SURFACE_NOT_SLIPPERY, NULL}, // MB64_MAT_MC_COBBLESTONE
    {mat_maker_MakerMCStone,       MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      NULL}, // MB64_MAT_MC_STONE
    {mat_maker_MakerMCOakLogTop,   MAT_OPAQUE, TRUE, SURFACE_CREAKWOOD,    NULL}, // MB64_MAT_MC_OAK_LOG_TOP
    {mat_maker_MakerMCOakLogSide,  MAT_OPAQUE, TRUE, SURFACE_CREAKWOOD,    NULL}, // MB64_MAT_MC_OAK_LOG_SIDE
    {mat_maker_MakerMCOakLeaves,   MAT_CUTOUT, TRUE, SURFACE_GRASS,        NULL}, // MB64_MAT_MC_OAK_LEAVES
    {mat_maker_MakerMCWoodPlanks,  MAT_OPAQUE, TRUE, SURFACE_CREAKWOOD,    NULL}, // MB64_MAT_MC_WOOD_PLANKS
    {mat_maker_MakerMCSand,        MAT_OPAQUE, TRUE, SURFACE_SAND,         NULL}, // MB64_MAT_MC_SAND
    {mat_maker_MakerMCBricks,      MAT_OPAQUE, TRUE, SURFACE_DEFAULT,      NULL}, // MB64_MAT_MC_BRICKS
    {mat_maker_MakerMCLava,        MAT_OPAQUE, TRUE, SURFACE_BURNING,      NULL}, // MB64_MAT_MC_LAVA
    {mat_maker_MakerMCFlowingLava, MAT_OPAQUE, TRUE, SURFACE_BURNING,      NULL}, // MB64_MAT_MC_FLOWING_LAVA
    {mat_maker_MakerMCGlass,       MAT_CUTOUT_NOCULL, TRUE, SURFACE_VANISH_CAP_WALLS, NULL}, // MB64_MAT_MC_GLASS
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

Gfx *mb64_fence_texs[] = {
    mat_maker_MakerFence,
    mat_maker_MakerWoodenFence,
    mat_maker_MakerDFence,
    mat_maker_MakerBarbedWire,
    mat_maker_MakerRHRFence,
    mat_maker_MakerHFence,
    mat_maker_MakerCFence,
    mat_maker_MakerVPFence,
    mat_maker_MakerBBHFence,
    mat_maker_MakerJRBFence,
    mat_maker_MakerSnowFence2,
    mat_maker_MakerSnowFence,
    mat_maker_MakerRetroFence,
    mat_maker_MakerMCFence,
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
Gfx *mb64_bar_texs[][2] = {
    {mat_maker_MakerIronBars,   mat_maker_MakerIronBarsTop},
    {mat_maker_MakerRHRMesh,    mat_maker_MakerChainTop},
    {mat_maker_MakerVPMesh,     mat_maker_MakerChainTop},
    {mat_maker_MakerHMesh,      mat_maker_MakerHMCTop},
    {mat_maker_MakerBBHMesh,    mat_maker_MakerHMCTop},
    {mat_maker_MakerGratePink,  mat_maker_MakerChainTopPink},
    {mat_maker_MakerTTCGrate,   mat_maker_MakerTTCGrateTop},
    {mat_maker_MakerDMesh,      mat_maker_MakerDesertMeshTop},
    {mat_maker_MakerBOBBars,    mat_maker_MakerBOBBarsTop},
    {mat_maker_MakerRetroMesh,  mat_maker_MakerRetroMeshTop},
    {mat_maker_MakerMCIronBars, mat_maker_MakerMCIronBarsTop},
};

enum mb64_water {
    MB64_WATER_DEFAULT,
    MB64_WATER_GREEN,
    MB64_WATER_RETRO,
    MB64_WATER_MC,
};

Gfx *mb64_water_texs[] = {
    mat_maker_MakerWater,
    mat_maker_MakerGreenWater,
    mat_maker_MakerRetroWater,
    mat_maker_MakerMCWater,
};

struct mb64_topmaterial mb64_topmat_table[19] = {
    {MB64_MAT_GRASS,         mat_maker_MakerGrassSide},
    {MB64_MAT_SAND,          mat_maker_MakerSandSide},
    {MB64_MAT_SNOW,          mat_maker_MakerSnowSide},
    {MB64_MAT_TILES,         mat_maker_MakerTileEdge},
    {MB64_MAT_C_STONETOP,    mat_maker_MakerCastleHexRim},
    {MB64_MAT_HMC_GRASS,     mat_maker_MakerHGrassSide},
    {MB64_MAT_BBH_METAL,     mat_maker_MakerBBHMetalSide},
    {MB64_MAT_BBH_STONE,     mat_maker_MakerBBHMetalSide},
    {MB64_MAT_JRB_TILETOP,   mat_maker_MakerJRBTileRim},
    {MB64_MAT_SNOW_TILES,    mat_maker_MakerSnowTileRim},
    {MB64_MAT_FLOWERS,       mat_maker_MakerFlowerEdge},
    {MB64_MAT_RETRO_TREETOP, mat_maker_MakerRetroTreeSide},
    {MB64_MAT_MC_GRASS,      mat_maker_MakerMCGrassEdge},
    {MB64_MAT_LAVA_ROCKS,    mat_maker_MakerLavaRockEdge},
    {MB64_MAT_DARK_GRASS,    mat_maker_MakerDarkGrassSide},
    {MB64_MAT_CARTOON_GRASS, mat_maker_MakerCartoonGrassSide},
    {MB64_MAT_ORANGE_GRASS,  mat_maker_MakerOrangeGrassSide},
    {MB64_MAT_RED_GRASS,     mat_maker_MakerRedGrassSide},
    {MB64_MAT_PURPLE_GRASS,  mat_maker_MakerPurpleGrassSide},
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
