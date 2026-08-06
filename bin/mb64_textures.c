#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include "macros.h"
#include "types.h"
#include "make_const_nonconst.h"
#include "mb64/gfx/mb64_textures.h"

// Terrain
ALIGNED8 static const Texture mb64_tex_Grass_ci8[] = {
#include "textures/mb64_textures/Grass.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_Grass_pal_rgba16[] = {
#include "textures/mb64_textures/Grass.ci8.pal"
};
DEFINE_CI8(mb64_tex_Grass, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_GrassSide_ci8[] = {
#include "textures/mb64_textures/GrassSide.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_GrassSide_pal_rgba16[] = {
#include "textures/mb64_textures/GrassSide.ci8.pal"
};
DEFINE_CI8(mb64_tex_GrassSide, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_VanillaGrass_ci8[] = {
#include "textures/mb64_textures/VanillaGrass.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_VanillaGrass_pal_rgba16[] = {
#include "textures/mb64_textures/VanillaGrass.ci8.pal"
};
DEFINE_CI8(mb64_tex_VanillaGrass, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_CartoonGrass_ci8[] = {
#include "textures/mb64_textures/CartoonGrass.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_CartoonGrass_pal_rgba16[] = {
#include "textures/mb64_textures/CartoonGrass.ci8.pal"
};
DEFINE_CI8(mb64_tex_CartoonGrass, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_CartoonGrassSide_ci8[] = {
#include "textures/mb64_textures/CartoonGrassSide.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_CartoonGrassSide_pal_rgba16[] = {
#include "textures/mb64_textures/CartoonGrassSide.ci8.pal"
};
DEFINE_CI8(mb64_tex_CartoonGrassSide, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_DarkGrass_ci4[] = {
#include "textures/mb64_textures/DarkGrass.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_DarkGrass_pal_rgba16[] = {
#include "textures/mb64_textures/DarkGrass.ci4.pal"
};
DEFINE_CI4(mb64_tex_DarkGrass, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_DarkGrassSide_ci8[] = {
#include "textures/mb64_textures/DarkGrassSide.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_DarkGrassSide_pal_rgba16[] = {
#include "textures/mb64_textures/DarkGrassSide.ci8.pal"
};
DEFINE_CI8(mb64_tex_DarkGrassSide, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_HGrass_ci4[] = {
#include "textures/mb64_textures/HGrass.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_HGrass_pal_rgba16[] = {
#include "textures/mb64_textures/HGrass.ci4.pal"
};
DEFINE_CI4(mb64_tex_HGrass, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_HGrassSide_ci8[] = {
#include "textures/mb64_textures/HGrassSide.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_HGrassSide_pal_rgba16[] = {
#include "textures/mb64_textures/HGrassSide.ci8.pal"
};
DEFINE_CI8(mb64_tex_HGrassSide, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_OrangeGrass_ci4[] = {
#include "textures/mb64_textures/OrangeGrass.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_OrangeGrass_pal_rgba16[] = {
#include "textures/mb64_textures/OrangeGrass.ci4.pal"
};
DEFINE_CI4(mb64_tex_OrangeGrass, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_OrangeGrassSide_ci8[] = {
#include "textures/mb64_textures/OrangeGrassSide.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_OrangeGrassSide_pal_rgba16[] = {
#include "textures/mb64_textures/OrangeGrassSide.ci8.pal"
};
DEFINE_CI8(mb64_tex_OrangeGrassSide, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_RedGrass_ci8[] = {
#include "textures/mb64_textures/RedGrass.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RedGrass_pal_rgba16[] = {
#include "textures/mb64_textures/RedGrass.ci8.pal"
};
DEFINE_CI8(mb64_tex_RedGrass, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RedGrassSide_ci8[] = {
#include "textures/mb64_textures/RedGrassSide.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RedGrassSide_pal_rgba16[] = {
#include "textures/mb64_textures/RedGrassSide.ci8.pal"
};
DEFINE_CI8(mb64_tex_RedGrassSide, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_PurpleGrass_ci8[] = {
#include "textures/mb64_textures/PurpleGrass.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_PurpleGrass_pal_rgba16[] = {
#include "textures/mb64_textures/PurpleGrass.ci8.pal"
};
DEFINE_CI8(mb64_tex_PurpleGrass, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_PurpleGrassSide_ci8[] = {
#include "textures/mb64_textures/PurpleGrassSide.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_PurpleGrassSide_pal_rgba16[] = {
#include "textures/mb64_textures/PurpleGrassSide.ci8.pal"
};
DEFINE_CI8(mb64_tex_PurpleGrassSide, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_Sand_ci4[] = {
#include "textures/mb64_textures/Sand.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_Sand_pal_rgba16[] = {
#include "textures/mb64_textures/Sand.ci4.pal"
};
DEFINE_CI4(mb64_tex_Sand, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_SandSide_ci8[] = {
#include "textures/mb64_textures/SandSide.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_SandSide_pal_rgba16[] = {
#include "textures/mb64_textures/SandSide.ci8.pal"
};
DEFINE_CI8(mb64_tex_SandSide, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_JRBSand_ci8[] = {
#include "textures/mb64_textures/JRBSand.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_JRBSand_pal_rgba16[] = {
#include "textures/mb64_textures/JRBSand.ci8.pal"
};
DEFINE_CI8(mb64_tex_JRBSand, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_Snow_ci8[] = {
#include "textures/mb64_textures/Snow.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_Snow_pal_rgba16[] = {
#include "textures/mb64_textures/Snow.ci8.pal"
};
DEFINE_CI8(mb64_tex_Snow, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_SnowSide_ci8[] = {
#include "textures/mb64_textures/SnowSide.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_SnowSide_pal_rgba16[] = {
#include "textures/mb64_textures/SnowSide.ci8.pal"
};
DEFINE_CI8(mb64_tex_SnowSide, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_VanillaSnow_ci8[] = {
#include "textures/mb64_textures/VanillaSnow.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_VanillaSnow_pal_rgba16[] = {
#include "textures/mb64_textures/VanillaSnow.ci8.pal"
};
DEFINE_CI8(mb64_tex_VanillaSnow, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_Dirt_ci4[] = {
#include "textures/mb64_textures/Dirt.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_Dirt_pal_rgba16[] = {
#include "textures/mb64_textures/Dirt.ci4.pal"
};
DEFINE_CI4(mb64_tex_Dirt, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_SandDirt_ci8[] = {
#include "textures/mb64_textures/SandDirt.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_SandDirt_pal_rgba16[] = {
#include "textures/mb64_textures/SandDirt.ci8.pal"
};
DEFINE_CI8(mb64_tex_SandDirt, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_LightDirt_ci8[] = {
#include "textures/mb64_textures/LightDirt.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_LightDirt_pal_rgba16[] = {
#include "textures/mb64_textures/LightDirt.ci8.pal"
};
DEFINE_CI8(mb64_tex_LightDirt, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_HDirt_ci8[] = {
#include "textures/mb64_textures/HDirt.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_HDirt_pal_rgba16[] = {
#include "textures/mb64_textures/HDirt.ci8.pal"
};
DEFINE_CI8(mb64_tex_HDirt, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RockyDirt_ci8[] = {
#include "textures/mb64_textures/RockyDirt.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RockyDirt_pal_rgba16[] = {
#include "textures/mb64_textures/RockyDirt.ci8.pal"
};
DEFINE_CI8(mb64_tex_RockyDirt, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_VanillaDirt_ci8[] = {
#include "textures/mb64_textures/VanillaDirt.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_VanillaDirt_pal_rgba16[] = {
#include "textures/mb64_textures/VanillaDirt.ci8.pal"
};
DEFINE_CI8(mb64_tex_VanillaDirt, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_WavyDirt_ci8[] = {
#include "textures/mb64_textures/WavyDirt.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_WavyDirt_pal_rgba16[] = {
#include "textures/mb64_textures/WavyDirt.ci8.pal"
};
DEFINE_CI8(mb64_tex_WavyDirt, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_WavyDirtBlue_ci8[] = {
#include "textures/mb64_textures/WavyDirtBlue.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_WavyDirtBlue_pal_rgba16[] = {
#include "textures/mb64_textures/WavyDirtBlue.ci8.pal"
};
DEFINE_CI8(mb64_tex_WavyDirtBlue, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_SnowDirt_ci8[] = {
#include "textures/mb64_textures/SnowDirt.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_SnowDirt_pal_rgba16[] = {
#include "textures/mb64_textures/SnowDirt.ci8.pal"
};
DEFINE_CI8(mb64_tex_SnowDirt, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_PurpleDirt_ci8[] = {
#include "textures/mb64_textures/PurpleDirt.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_PurpleDirt_pal_rgba16[] = {
#include "textures/mb64_textures/PurpleDirt.ci8.pal"
};
DEFINE_CI8(mb64_tex_PurpleDirt, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_HLakewall_ci8[] = {
#include "textures/mb64_textures/HLakewall.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_HLakewall_pal_rgba16[] = {
#include "textures/mb64_textures/HLakewall.ci8.pal"
};
DEFINE_CI8(mb64_tex_HLakewall, 5, 5, G_TX_WRAP, G_TX_WRAP);

// Stone
ALIGNED8 static const Texture mb64_tex_StoneSide_ci8[] = {
#include "textures/mb64_textures/StoneSide.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_StoneSide_pal_rgba16[] = {
#include "textures/mb64_textures/StoneSide.ci8.pal"
};
DEFINE_CI8(mb64_tex_StoneSide, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_HStone_ci8[] = {
#include "textures/mb64_textures/HStone.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_HStone_pal_rgba16[] = {
#include "textures/mb64_textures/HStone.ci8.pal"
};
DEFINE_CI8(mb64_tex_HStone, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_HMazefloor_ci4[] = {
#include "textures/mb64_textures/HMazefloor.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_HMazefloor_pal_rgba16[] = {
#include "textures/mb64_textures/HMazefloor.ci4.pal"
};
DEFINE_CI4(mb64_tex_HMazefloor, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_CCMWall_ci8[] = {
#include "textures/mb64_textures/CCMWall.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_CCMWall_pal_rgba16[] = {
#include "textures/mb64_textures/CCMWall.ci8.pal"
};
DEFINE_CI8(mb64_tex_CCMWall, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_MountainFloor_ci8[] = {
#include "textures/mb64_textures/MountainFloor.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_MountainFloor_pal_rgba16[] = {
#include "textures/mb64_textures/MountainFloor.ci8.pal"
};
DEFINE_CI8(mb64_tex_MountainFloor, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_MountainRock_ci8[] = {
#include "textures/mb64_textures/MountainRock.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_MountainRock_pal_rgba16[] = {
#include "textures/mb64_textures/MountainRock.ci8.pal"
};
DEFINE_CI8(mb64_tex_MountainRock, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_Stone_ci8[] = {
#include "textures/mb64_textures/Stone.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_Stone_pal_rgba16[] = {
#include "textures/mb64_textures/Stone.ci8.pal"
};
DEFINE_CI8(mb64_tex_Stone, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_JRBWall_ci8[] = {
#include "textures/mb64_textures/JRBWall.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_JRBWall_pal_rgba16[] = {
#include "textures/mb64_textures/JRBWall.ci8.pal"
};
DEFINE_CI8(mb64_tex_JRBWall, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_BlackStone_ci8[] = {
#include "textures/mb64_textures/BlackStone.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_BlackStone_pal_rgba16[] = {
#include "textures/mb64_textures/BlackStone.ci8.pal"
};
DEFINE_CI8(mb64_tex_BlackStone, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RHRStone_ci4[] = {
#include "textures/mb64_textures/RHRStone.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RHRStone_pal_rgba16[] = {
#include "textures/mb64_textures/RHRStone.ci4.pal"
};
DEFINE_CI4(mb64_tex_RHRStone, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_LavaRock_ci8[] = {
#include "textures/mb64_textures/LavaRock.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_LavaRock_pal_rgba16[] = {
#include "textures/mb64_textures/LavaRock.ci8.pal"
};
DEFINE_CI8(mb64_tex_LavaRock, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_LavaRockEdge_ci8[] = {
#include "textures/mb64_textures/LavaRockEdge.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_LavaRockEdge_pal_rgba16[] = {
#include "textures/mb64_textures/LavaRockEdge.ci8.pal"
};
DEFINE_CI8(mb64_tex_LavaRockEdge, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_VolcanicRock_ci8[] = {
#include "textures/mb64_textures/VolcanicRock.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_VolcanicRock_pal_rgba16[] = {
#include "textures/mb64_textures/VolcanicRock.ci8.pal"
};
DEFINE_CI8(mb64_tex_VolcanicRock, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RHRBasalt_ci8[] = {
#include "textures/mb64_textures/RHRBasalt.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RHRBasalt_pal_rgba16[] = {
#include "textures/mb64_textures/RHRBasalt.ci8.pal"
};
DEFINE_CI8(mb64_tex_RHRBasalt, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_Obsidian_ci8[] = {
#include "textures/mb64_textures/Obsidian.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_Obsidian_pal_rgba16[] = {
#include "textures/mb64_textures/Obsidian.ci8.pal"
};
DEFINE_CI8(mb64_tex_Obsidian, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_CastleCobble_ci8[] = {
#include "textures/mb64_textures/CastleCobble.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_CastleCobble_pal_rgba16[] = {
#include "textures/mb64_textures/CastleCobble.ci8.pal"
};
DEFINE_CI8(mb64_tex_CastleCobble, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_JRBUnderwater_ci8[] = {
#include "textures/mb64_textures/JRBUnderwater.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_JRBUnderwater_pal_rgba16[] = {
#include "textures/mb64_textures/JRBUnderwater.ci8.pal"
};
DEFINE_CI8(mb64_tex_JRBUnderwater, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_SnowRock_ci8[] = {
#include "textures/mb64_textures/SnowRock.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_SnowRock_pal_rgba16[] = {
#include "textures/mb64_textures/SnowRock.ci8.pal"
};
DEFINE_CI8(mb64_tex_SnowRock, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_IcyRock_ci8[] = {
#include "textures/mb64_textures/IcyRock.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_IcyRock_pal_rgba16[] = {
#include "textures/mb64_textures/IcyRock.ci8.pal"
};
DEFINE_CI8(mb64_tex_IcyRock, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_DStone_ci8[] = {
#include "textures/mb64_textures/DStone.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_DStone_pal_rgba16[] = {
#include "textures/mb64_textures/DStone.ci8.pal"
};
DEFINE_CI8(mb64_tex_DStone, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RHRObsidian_ci4[] = {
#include "textures/mb64_textures/RHRObsidian.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RHRObsidian_pal_rgba16[] = {
#include "textures/mb64_textures/RHRObsidian.ci4.pal"
};
DEFINE_CI4(mb64_tex_RHRObsidian, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_JRBStone_ci8[] = {
#include "textures/mb64_textures/JRBStone.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_JRBStone_pal_rgba16[] = {
#include "textures/mb64_textures/JRBStone.ci8.pal"
};
DEFINE_CI8(mb64_tex_JRBStone, 5, 5, G_TX_WRAP, G_TX_WRAP);

// Bricks
ALIGNED8 static const Texture mb64_tex_Bricks_ci8[] = {
#include "textures/mb64_textures/Bricks.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_Bricks_pal_rgba16[] = {
#include "textures/mb64_textures/Bricks.ci8.pal"
};
DEFINE_CI8(mb64_tex_Bricks, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_DBrick_ci8[] = {
#include "textures/mb64_textures/DBrick.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_DBrick_pal_rgba16[] = {
#include "textures/mb64_textures/DBrick.ci8.pal"
};
DEFINE_CI8(mb64_tex_DBrick, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RHRBrick_ci4[] = {
#include "textures/mb64_textures/RHRBrick.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RHRBrick_pal_rgba16[] = {
#include "textures/mb64_textures/RHRBrick.ci4.pal"
};
DEFINE_CI4(mb64_tex_RHRBrick, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_HBrick_ci8[] = {
#include "textures/mb64_textures/HBrick.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_HBrick_pal_rgba16[] = {
#include "textures/mb64_textures/HBrick.ci8.pal"
};
DEFINE_CI8(mb64_tex_HBrick, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_LightBrownBricks_ci8[] = {
#include "textures/mb64_textures/LightBrownBricks.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_LightBrownBricks_pal_rgba16[] = {
#include "textures/mb64_textures/LightBrownBricks.ci8.pal"
};
DEFINE_CI8(mb64_tex_LightBrownBricks, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_BrownBricks_ci8[] = {
#include "textures/mb64_textures/BrownBricks.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_BrownBricks_pal_rgba16[] = {
#include "textures/mb64_textures/BrownBricks.ci8.pal"
};
DEFINE_CI8(mb64_tex_BrownBricks, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_TTMBricks_ci8[] = {
#include "textures/mb64_textures/TTMBricks.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_TTMBricks_pal_rgba16[] = {
#include "textures/mb64_textures/TTMBricks.ci8.pal"
};
DEFINE_CI8(mb64_tex_TTMBricks, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_CBrick_ci8[] = {
#include "textures/mb64_textures/CBrick.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_CBrick_pal_rgba16[] = {
#include "textures/mb64_textures/CBrick.ci8.pal"
};
DEFINE_CI8(mb64_tex_CBrick, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_BBHBricks_ci8[] = {
#include "textures/mb64_textures/BBHBricks.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_BBHBricks_pal_rgba16[] = {
#include "textures/mb64_textures/BBHBricks.ci8.pal"
};
DEFINE_CI8(mb64_tex_BBHBricks, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RoofBricks_ci8[] = {
#include "textures/mb64_textures/RoofBricks.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RoofBricks_pal_rgba16[] = {
#include "textures/mb64_textures/RoofBricks.ci8.pal"
};
DEFINE_CI8(mb64_tex_RoofBricks, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_COutsideBricks_ci4[] = {
#include "textures/mb64_textures/COutsideBricks.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_COutsideBricks_pal_rgba16[] = {
#include "textures/mb64_textures/COutsideBricks.ci4.pal"
};
DEFINE_CI4(mb64_tex_COutsideBricks, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_SnowBricks_ci8[] = {
#include "textures/mb64_textures/SnowBricks.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_SnowBricks_pal_rgba16[] = {
#include "textures/mb64_textures/SnowBricks.ci8.pal"
};
DEFINE_CI8(mb64_tex_SnowBricks, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_JRBBricks_ci8[] = {
#include "textures/mb64_textures/JRBBricks.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_JRBBricks_pal_rgba16[] = {
#include "textures/mb64_textures/JRBBricks.ci8.pal"
};
DEFINE_CI8(mb64_tex_JRBBricks, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_SnowTileSide_ci8[] = {
#include "textures/mb64_textures/SnowTileSide.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_SnowTileSide_pal_rgba16[] = {
#include "textures/mb64_textures/SnowTileSide.ci8.pal"
};
DEFINE_CI8(mb64_tex_SnowTileSide, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_TileBricks_ci8[] = {
#include "textures/mb64_textures/TileBricks.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_TileBricks_pal_rgba16[] = {
#include "textures/mb64_textures/TileBricks.ci8.pal"
};
DEFINE_CI8(mb64_tex_TileBricks, 5, 5, G_TX_WRAP, G_TX_WRAP);

// Tiling
ALIGNED8 static const Texture mb64_tex_Tiles_ci4[] = {
#include "textures/mb64_textures/Tiles.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_Tiles_pal_rgba16[] = {
#include "textures/mb64_textures/Tiles.ci4.pal"
};
DEFINE_CI4(mb64_tex_Tiles, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_TileEdge_ci8[] = {
#include "textures/mb64_textures/TileEdge.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_TileEdge_pal_rgba16[] = {
#include "textures/mb64_textures/TileEdge.ci8.pal"
};
DEFINE_CI8(mb64_tex_TileEdge, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_CTiles_ci8[] = {
#include "textures/mb64_textures/CTiles.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_CTiles_pal_rgba16[] = {
#include "textures/mb64_textures/CTiles.ci8.pal"
};
DEFINE_CI8(mb64_tex_CTiles, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_DTiles_ci8[] = {
#include "textures/mb64_textures/DTiles.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_DTiles_pal_rgba16[] = {
#include "textures/mb64_textures/DTiles.ci8.pal"
};
DEFINE_CI8(mb64_tex_DTiles, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_VBlueTiles_ci8[] = {
#include "textures/mb64_textures/VBlueTiles.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_VBlueTiles_pal_rgba16[] = {
#include "textures/mb64_textures/VBlueTiles.ci8.pal"
};
DEFINE_CI8(mb64_tex_VBlueTiles, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_SnowTiles_ci4[] = {
#include "textures/mb64_textures/SnowTiles.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_SnowTiles_pal_rgba16[] = {
#include "textures/mb64_textures/SnowTiles.ci4.pal"
};
DEFINE_CI4(mb64_tex_SnowTiles, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_SnowTileRim_ci4[] = {
#include "textures/mb64_textures/SnowTileRim.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_SnowTileRim_pal_rgba16[] = {
#include "textures/mb64_textures/SnowTileRim.ci4.pal"
};
DEFINE_CI4(mb64_tex_SnowTileRim, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_JRBTileTop_ci8[] = {
#include "textures/mb64_textures/JRBTileTop.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_JRBTileTop_pal_rgba16[] = {
#include "textures/mb64_textures/JRBTileTop.ci8.pal"
};
DEFINE_CI8(mb64_tex_JRBTileTop, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_JRBTileRim_ci4[] = {
#include "textures/mb64_textures/JRBTileRim.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_JRBTileRim_pal_rgba16[] = {
#include "textures/mb64_textures/JRBTileRim.ci4.pal"
};
DEFINE_CI4(mb64_tex_JRBTileRim, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_JRBTileSide_ci4[] = {
#include "textures/mb64_textures/JRBTileSide.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_JRBTileSide_pal_rgba16[] = {
#include "textures/mb64_textures/JRBTileSide.ci4.pal"
};
DEFINE_CI4(mb64_tex_JRBTileSide, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_HTileTop_ci4[] = {
#include "textures/mb64_textures/HTileTop.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_HTileTop_pal_rgba16[] = {
#include "textures/mb64_textures/HTileTop.ci4.pal"
};
DEFINE_CI4(mb64_tex_HTileTop, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_GraniteTiles_ci8[] = {
#include "textures/mb64_textures/GraniteTiles.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_GraniteTiles_pal_rgba16[] = {
#include "textures/mb64_textures/GraniteTiles.ci8.pal"
};
DEFINE_CI8(mb64_tex_GraniteTiles, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RHRTiles_ci8[] = {
#include "textures/mb64_textures/RHRTiles.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RHRTiles_pal_rgba16[] = {
#include "textures/mb64_textures/RHRTiles.ci8.pal"
};
DEFINE_CI8(mb64_tex_RHRTiles, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_VTiles_ci4[] = {
#include "textures/mb64_textures/VTiles.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_VTiles_pal_rgba16[] = {
#include "textures/mb64_textures/VTiles.ci4.pal"
};
DEFINE_CI4(mb64_tex_VTiles, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_DiamondPattern_ci8[] = {
#include "textures/mb64_textures/DiamondPattern.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_DiamondPattern_pal_rgba16[] = {
#include "textures/mb64_textures/DiamondPattern.ci8.pal"
};
DEFINE_CI8(mb64_tex_DiamondPattern, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_CStone_ci4[] = {
#include "textures/mb64_textures/CStone.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_CStone_pal_rgba16[] = {
#include "textures/mb64_textures/CStone.ci4.pal"
};
DEFINE_CI4(mb64_tex_CStone, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_CastleHexRim_ci4[] = {
#include "textures/mb64_textures/CastleHexRim.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_CastleHexRim_pal_rgba16[] = {
#include "textures/mb64_textures/CastleHexRim.ci4.pal"
};
DEFINE_CI4(mb64_tex_CastleHexRim, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_SnowBrickTiles_ci8[] = {
#include "textures/mb64_textures/SnowBrickTiles.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_SnowBrickTiles_pal_rgba16[] = {
#include "textures/mb64_textures/SnowBrickTiles.ci8.pal"
};
DEFINE_CI8(mb64_tex_SnowBrickTiles, 5, 5, G_TX_WRAP, G_TX_WRAP);

// Cut Stone
ALIGNED8 static const Texture mb64_tex_DStoneBlock_ci8[] = {
#include "textures/mb64_textures/DStoneBlock.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_DStoneBlock_pal_rgba16[] = {
#include "textures/mb64_textures/DStoneBlock.ci8.pal"
};
DEFINE_CI8(mb64_tex_DStoneBlock, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_VBlock_ci8[] = {
#include "textures/mb64_textures/VBlock.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_VBlock_pal_rgba16[] = {
#include "textures/mb64_textures/VBlock.ci8.pal"
};
DEFINE_CI8(mb64_tex_VBlock, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_BBHWall_ci8[] = {
#include "textures/mb64_textures/BBHWall.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_BBHWall_pal_rgba16[] = {
#include "textures/mb64_textures/BBHWall.ci8.pal"
};
DEFINE_CI8(mb64_tex_BBHWall, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_BBHMetalSide_ci8[] = {
#include "textures/mb64_textures/BBHMetalSide.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_BBHMetalSide_pal_rgba16[] = {
#include "textures/mb64_textures/BBHMetalSide.ci8.pal"
};
DEFINE_CI8(mb64_tex_BBHMetalSide, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_BBHStonePattern_ci8[] = {
#include "textures/mb64_textures/BBHStonePattern.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_BBHStonePattern_pal_rgba16[] = {
#include "textures/mb64_textures/BBHStonePattern.ci8.pal"
};
DEFINE_CI8(mb64_tex_BBHStonePattern, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_LauncherTex_ci8[] = {
#include "textures/mb64_textures/LauncherTex.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_LauncherTex_pal_rgba16[] = {
#include "textures/mb64_textures/LauncherTex.ci8.pal"
};
DEFINE_CI8(mb64_tex_LauncherTex, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_HTileSide_ci8[] = {
#include "textures/mb64_textures/HTileSide.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_HTileSide_pal_rgba16[] = {
#include "textures/mb64_textures/HTileSide.ci8.pal"
};
DEFINE_CI8(mb64_tex_HTileSide, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RHRPattern_ci4[] = {
#include "textures/mb64_textures/RHRPattern.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RHRPattern_pal_rgba16[] = {
#include "textures/mb64_textures/RHRPattern.ci4.pal"
};
DEFINE_CI4(mb64_tex_RHRPattern, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_GraniteBlock_ci8[] = {
#include "textures/mb64_textures/GraniteBlock.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_GraniteBlock_pal_rgba16[] = {
#include "textures/mb64_textures/GraniteBlock.ci8.pal"
};
DEFINE_CI8(mb64_tex_GraniteBlock, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_CStoneSide_ci4[] = {
#include "textures/mb64_textures/CStoneSide.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_CStoneSide_pal_rgba16[] = {
#include "textures/mb64_textures/CStoneSide.ci4.pal"
};
DEFINE_CI4(mb64_tex_CStoneSide, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_CPillar_ci8[] = {
#include "textures/mb64_textures/CPillar.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_CPillar_pal_rgba16[] = {
#include "textures/mb64_textures/CPillar.ci8.pal"
};
DEFINE_CI8(mb64_tex_CPillar, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_BBHPillar_ci8[] = {
#include "textures/mb64_textures/BBHPillar.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_BBHPillar_pal_rgba16[] = {
#include "textures/mb64_textures/BBHPillar.ci8.pal"
};
DEFINE_CI8(mb64_tex_BBHPillar, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RHRPillar_ci4[] = {
#include "textures/mb64_textures/RHRPillar.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RHRPillar_pal_rgba16[] = {
#include "textures/mb64_textures/RHRPillar.ci4.pal"
};
DEFINE_CI4(mb64_tex_RHRPillar, 5, 5, G_TX_WRAP, G_TX_WRAP);

// Wood
ALIGNED8 static const Texture mb64_tex_Wood_ci4[] = {
#include "textures/mb64_textures/Wood.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_Wood_pal_rgba16[] = {
#include "textures/mb64_textures/Wood.ci4.pal"
};
DEFINE_CI4(mb64_tex_Wood, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_BBHWoodWall_ci8[] = {
#include "textures/mb64_textures/BBHWoodWall.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_BBHWoodWall_pal_rgba16[] = {
#include "textures/mb64_textures/BBHWoodWall.ci8.pal"
};
DEFINE_CI8(mb64_tex_BBHWoodWall, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_BBHWoodFloor_ci8[] = {
#include "textures/mb64_textures/BBHWoodFloor.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_BBHWoodFloor_pal_rgba16[] = {
#include "textures/mb64_textures/BBHWoodFloor.ci8.pal"
};
DEFINE_CI8(mb64_tex_BBHWoodFloor, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_CWood_ci8[] = {
#include "textures/mb64_textures/CWood.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_CWood_pal_rgba16[] = {
#include "textures/mb64_textures/CWood.ci8.pal"
};
DEFINE_CI8(mb64_tex_CWood, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_JRBWood_ci8[] = {
#include "textures/mb64_textures/JRBWood.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_JRBWood_pal_rgba16[] = {
#include "textures/mb64_textures/JRBWood.ci8.pal"
};
DEFINE_CI8(mb64_tex_JRBWood, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_JRBShipSide_ci8[] = {
#include "textures/mb64_textures/JRBShipSide.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_JRBShipSide_pal_rgba16[] = {
#include "textures/mb64_textures/JRBShipSide.ci8.pal"
};
DEFINE_CI8(mb64_tex_JRBShipSide, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_JRBShipTop_ci8[] = {
#include "textures/mb64_textures/JRBShipTop.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_JRBShipTop_pal_rgba16[] = {
#include "textures/mb64_textures/JRBShipTop.ci8.pal"
};
DEFINE_CI8(mb64_tex_JRBShipTop, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_BBHHauntedPlanks_ci8[] = {
#include "textures/mb64_textures/BBHHauntedPlanks.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_BBHHauntedPlanks_pal_rgba16[] = {
#include "textures/mb64_textures/BBHHauntedPlanks.ci8.pal"
};
DEFINE_CI8(mb64_tex_BBHHauntedPlanks, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_BBHRoof_ci4[] = {
#include "textures/mb64_textures/BBHRoof.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_BBHRoof_pal_rgba16[] = {
#include "textures/mb64_textures/BBHRoof.ci4.pal"
};
DEFINE_CI4(mb64_tex_BBHRoof, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_SolidWood_ci8[] = {
#include "textures/mb64_textures/SolidWood.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_SolidWood_pal_rgba16[] = {
#include "textures/mb64_textures/SolidWood.ci8.pal"
};
DEFINE_CI8(mb64_tex_SolidWood, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RHRWood_ci4[] = {
#include "textures/mb64_textures/RHRWood.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RHRWood_pal_rgba16[] = {
#include "textures/mb64_textures/RHRWood.ci4.pal"
};
DEFINE_CI4(mb64_tex_RHRWood, 5, 5, G_TX_WRAP, G_TX_WRAP);

// Metal
ALIGNED8 static const Texture mb64_tex_BBHMetal_ci8[] = {
#include "textures/mb64_textures/BBHMetal.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_BBHMetal_pal_rgba16[] = {
#include "textures/mb64_textures/BBHMetal.ci8.pal"
};
DEFINE_CI8(mb64_tex_BBHMetal, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_JRBMetalSide_ci8[] = {
#include "textures/mb64_textures/JRBMetalSide.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_JRBMetalSide_pal_rgba16[] = {
#include "textures/mb64_textures/JRBMetalSide.ci8.pal"
};
DEFINE_CI8(mb64_tex_JRBMetalSide, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_JRBMetal_ci8[] = {
#include "textures/mb64_textures/JRBMetal.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_JRBMetal_pal_rgba16[] = {
#include "textures/mb64_textures/JRBMetal.ci8.pal"
};
DEFINE_CI8(mb64_tex_JRBMetal, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_CBasementWall_ci8[] = {
#include "textures/mb64_textures/CBasementWall.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_CBasementWall_pal_rgba16[] = {
#include "textures/mb64_textures/CBasementWall.ci8.pal"
};
DEFINE_CI8(mb64_tex_CBasementWall, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_DTiles2_ci8[] = {
#include "textures/mb64_textures/DTiles2.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_DTiles2_pal_rgba16[] = {
#include "textures/mb64_textures/DTiles2.ci8.pal"
};
DEFINE_CI8(mb64_tex_DTiles2, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_VRustyBlock_ci8[] = {
#include "textures/mb64_textures/VRustyBlock.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_VRustyBlock_pal_rgba16[] = {
#include "textures/mb64_textures/VRustyBlock.ci8.pal"
};
DEFINE_CI8(mb64_tex_VRustyBlock, 5, 5, G_TX_WRAP, G_TX_WRAP);

// Other
ALIGNED8 static const Texture mb64_tex_CCarpet_ci4[] = {
#include "textures/mb64_textures/CCarpet.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_CCarpet_pal_rgba16[] = {
#include "textures/mb64_textures/CCarpet.ci4.pal"
};
DEFINE_CI4(mb64_tex_CCarpet, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_CWall_ci8[] = {
#include "textures/mb64_textures/CWall.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_CWall_pal_rgba16[] = {
#include "textures/mb64_textures/CWall.ci8.pal"
};
DEFINE_CI8(mb64_tex_CWall, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_Roof_ci8[] = {
#include "textures/mb64_textures/Roof.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_Roof_pal_rgba16[] = {
#include "textures/mb64_textures/Roof.ci8.pal"
};
DEFINE_CI8(mb64_tex_Roof, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_CRoof_ci8[] = {
#include "textures/mb64_textures/CRoof.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_CRoof_pal_rgba16[] = {
#include "textures/mb64_textures/CRoof.ci8.pal"
};
DEFINE_CI8(mb64_tex_CRoof, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_SnowRoof_ci8[] = {
#include "textures/mb64_textures/SnowRoof.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_SnowRoof_pal_rgba16[] = {
#include "textures/mb64_textures/SnowRoof.ci8.pal"
};
DEFINE_CI8(mb64_tex_SnowRoof, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_BBHWindow_ci8[] = {
#include "textures/mb64_textures/BBHWindow.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_BBHWindow_pal_rgba16[] = {
#include "textures/mb64_textures/BBHWindow.ci8.pal"
};
DEFINE_CI8(mb64_tex_BBHWindow, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_HLight_ci8[] = {
#include "textures/mb64_textures/HLight.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_HLight_pal_rgba16[] = {
#include "textures/mb64_textures/HLight.ci8.pal"
};
DEFINE_CI8(mb64_tex_HLight, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_Caution_ci8[] = {
#include "textures/mb64_textures/Caution.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_Caution_pal_rgba16[] = {
#include "textures/mb64_textures/Caution.ci8.pal"
};
DEFINE_CI8(mb64_tex_Caution, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RRBlocks_ci8[] = {
#include "textures/mb64_textures/RRBlocks.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RRBlocks_pal_rgba16[] = {
#include "textures/mb64_textures/RRBlocks.ci8.pal"
};
DEFINE_CI8(mb64_tex_RRBlocks, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_StuddedFloor_ci8[] = {
#include "textures/mb64_textures/StuddedFloor.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_StuddedFloor_pal_rgba16[] = {
#include "textures/mb64_textures/StuddedFloor.ci8.pal"
};
DEFINE_CI8(mb64_tex_StuddedFloor, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_YellowBlock_ci4[] = {
#include "textures/mb64_textures/YellowBlock.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_YellowBlock_pal_rgba16[] = {
#include "textures/mb64_textures/YellowBlock.ci4.pal"
};
DEFINE_CI4(mb64_tex_YellowBlock, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_TTCSide_ci8[] = {
#include "textures/mb64_textures/TTCSide.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_TTCSide_pal_rgba16[] = {
#include "textures/mb64_textures/TTCSide.ci8.pal"
};
DEFINE_CI8(mb64_tex_TTCSide, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_TTCWall_ci8[] = {
#include "textures/mb64_textures/TTCWall.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_TTCWall_pal_rgba16[] = {
#include "textures/mb64_textures/TTCWall.ci8.pal"
};
DEFINE_CI8(mb64_tex_TTCWall, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_FlowerTop_ci8[] = {
#include "textures/mb64_textures/FlowerTop.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_FlowerTop_pal_rgba16[] = {
#include "textures/mb64_textures/FlowerTop.ci8.pal"
};
DEFINE_CI8(mb64_tex_FlowerTop, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_FlowerEdge_ci8[] = {
#include "textures/mb64_textures/FlowerEdge.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_FlowerEdge_pal_rgba16[] = {
#include "textures/mb64_textures/FlowerEdge.ci8.pal"
};
DEFINE_CI8(mb64_tex_FlowerEdge, 5, 5, G_TX_WRAP, G_TX_CLAMP);

// Hazards
ALIGNED8 static const Texture mb64_tex_Lava_ci8[] = {
#include "textures/mb64_textures/Lava.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_Lava_pal_rgba16[] = {
#include "textures/mb64_textures/Lava.ci8.pal"
};
DEFINE_CI8(mb64_tex_Lava, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_VanillaLava_ci8[] = {
#include "textures/mb64_textures/VanillaLava.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_VanillaLava_pal_rgba16[] = {
#include "textures/mb64_textures/VanillaLava.ci8.pal"
};
DEFINE_CI8(mb64_tex_VanillaLava, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_ServerAcid_ci8[] = {
#include "textures/mb64_textures/ServerAcid.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_ServerAcid_pal_rgba16[] = {
#include "textures/mb64_textures/ServerAcid.ci8.pal"
};
DEFINE_CI8(mb64_tex_ServerAcid, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_BurningIce_ci8[] = {
#include "textures/mb64_textures/BurningIce.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_BurningIce_pal_rgba16[] = {
#include "textures/mb64_textures/BurningIce.ci8.pal"
};
DEFINE_CI8(mb64_tex_BurningIce, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_Quicksand_ci4[] = {
#include "textures/mb64_textures/Quicksand.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_Quicksand_pal_rgba16[] = {
#include "textures/mb64_textures/Quicksand.ci4.pal"
};
DEFINE_CI4(mb64_tex_Quicksand, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_Slowsand_ci8[] = {
#include "textures/mb64_textures/Slowsand.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_Slowsand_pal_rgba16[] = {
#include "textures/mb64_textures/Slowsand.ci8.pal"
};
DEFINE_CI8(mb64_tex_Slowsand, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_Void_ci8[] = {
#include "textures/mb64_textures/Void.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_Void_pal_rgba16[] = {
#include "textures/mb64_textures/Void.ci8.pal"
};
DEFINE_CI8(mb64_tex_Void, 5, 5, G_TX_WRAP, G_TX_WRAP);

// Transparent
ALIGNED8 static const Texture mb64_tex_RHRMesh_ci8[] = {
#include "textures/mb64_textures/RHRMesh.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RHRMesh_pal_rgba16[] = {
#include "textures/mb64_textures/RHRMesh.ci8.pal"
};
DEFINE_CI8(mb64_tex_RHRMesh, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_VPMesh_ci4[] = {
#include "textures/mb64_textures/VPMesh.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_VPMesh_pal_rgba16[] = {
#include "textures/mb64_textures/VPMesh.ci4.pal"
};
DEFINE_CI4(mb64_tex_VPMesh, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_HMesh_ci8[] = {
#include "textures/mb64_textures/HMesh.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_HMesh_pal_rgba16[] = {
#include "textures/mb64_textures/HMesh.ci8.pal"
};
DEFINE_CI8(mb64_tex_HMesh, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_BBHMesh_ci8[] = {
#include "textures/mb64_textures/BBHMesh.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_BBHMesh_pal_rgba16[] = {
#include "textures/mb64_textures/BBHMesh.ci8.pal"
};
DEFINE_CI8(mb64_tex_BBHMesh, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_GratePink_ci8[] = {
#include "textures/mb64_textures/GratePink.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_GratePink_pal_rgba16[] = {
#include "textures/mb64_textures/GratePink.ci8.pal"
};
DEFINE_CI8(mb64_tex_GratePink, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_TTCGrate_ci8[] = {
#include "textures/mb64_textures/TTCGrate.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_TTCGrate_pal_rgba16[] = {
#include "textures/mb64_textures/TTCGrate.ci8.pal"
};
DEFINE_CI8(mb64_tex_TTCGrate, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_Ice_ci8[] = {
#include "textures/mb64_textures/Ice.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_Ice_pal_rgba16[] = {
#include "textures/mb64_textures/Ice.ci8.pal"
};
DEFINE_CI8_ALPHA(mb64_tex_Ice, 5, 5, G_TX_WRAP, G_TX_WRAP, 191);

ALIGNED8 static const Texture mb64_tex_Crystal_ci8[] = {
#include "textures/mb64_textures/Crystal.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_Crystal_pal_rgba16[] = {
#include "textures/mb64_textures/Crystal.ci8.pal"
};
DEFINE_CI8_ALPHA(mb64_tex_Crystal, 5, 5, G_TX_WRAP, G_TX_WRAP, 217);

ALIGNED8 static const Texture mb64_tex_Screen_ci4[] = {
#include "textures/mb64_textures/Screen.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_Screen_pal_rgba16[] = {
#include "textures/mb64_textures/Screen.ci4.pal"
};
DEFINE_CI4(mb64_tex_Screen, 6, 6, G_TX_MIRROR, G_TX_MIRROR);

// Retro
ALIGNED8 static const Texture mb64_tex_RetroGround_ci4[] = {
#include "textures/mb64_textures/RetroGround.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RetroGround_pal_rgba16[] = {
#include "textures/mb64_textures/RetroGround.ci4.pal"
};
DEFINE_CI4(mb64_tex_RetroGround, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RetroBrick_ci4[] = {
#include "textures/mb64_textures/RetroBrick.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RetroBrick_pal_rgba16[] = {
#include "textures/mb64_textures/RetroBrick.ci4.pal"
};
DEFINE_CI4(mb64_tex_RetroBrick, 4, 4, G_TX_WRAP, G_TX_WRAP);

DEFINE_SOLID(mb64_tex_RetroTreeTop, 128, 208, 16);

ALIGNED8 static const Texture mb64_tex_RetroTreeSide_ci4[] = {
#include "textures/mb64_textures/RetroTreeSide.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RetroTreeSide_pal_rgba16[] = {
#include "textures/mb64_textures/RetroTreeSide.ci4.pal"
};
DEFINE_CI4(mb64_tex_RetroTreeSide, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_RetroTree_ci4[] = {
#include "textures/mb64_textures/RetroTree.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RetroTree_pal_rgba16[] = {
#include "textures/mb64_textures/RetroTree.ci4.pal"
};
DEFINE_CI4(mb64_tex_RetroTree, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RetroBlock_ci4[] = {
#include "textures/mb64_textures/RetroBlock.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RetroBlock_pal_rgba16[] = {
#include "textures/mb64_textures/RetroBlock.ci4.pal"
};
DEFINE_CI4(mb64_tex_RetroBlock, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RetroBGround_ci4[] = {
#include "textures/mb64_textures/RetroBGround.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RetroBGround_pal_rgba16[] = {
#include "textures/mb64_textures/RetroBGround.ci4.pal"
};
DEFINE_CI4(mb64_tex_RetroBGround, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RetroBBrick_ci4[] = {
#include "textures/mb64_textures/RetroBBrick.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RetroBBrick_pal_rgba16[] = {
#include "textures/mb64_textures/RetroBBrick.ci4.pal"
};
DEFINE_CI4(mb64_tex_RetroBBrick, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RetroBBlock_ci4[] = {
#include "textures/mb64_textures/RetroBBlock.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RetroBBlock_pal_rgba16[] = {
#include "textures/mb64_textures/RetroBBlock.ci4.pal"
};
DEFINE_CI4(mb64_tex_RetroBBlock, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RetroWBrick_ci4[] = {
#include "textures/mb64_textures/RetroWBrick.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RetroWBrick_pal_rgba16[] = {
#include "textures/mb64_textures/RetroWBrick.ci4.pal"
};
DEFINE_CI4(mb64_tex_RetroWBrick, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RetroLava_ci4[] = {
#include "textures/mb64_textures/RetroLava.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RetroLava_pal_rgba16[] = {
#include "textures/mb64_textures/RetroLava.ci4.pal"
};
DEFINE_CI4(mb64_tex_RetroLava, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RetroUnderwater_ci4[] = {
#include "textures/mb64_textures/RetroUnderwater.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RetroUnderwater_pal_rgba16[] = {
#include "textures/mb64_textures/RetroUnderwater.ci4.pal"
};
DEFINE_CI4(mb64_tex_RetroUnderwater, 4, 4, G_TX_WRAP, G_TX_WRAP);

// Minecraft
ALIGNED8 static const Texture mb64_tex_MCDirt_ci4[] = {
#include "textures/mb64_textures/MCDirt.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_MCDirt_pal_rgba16[] = {
#include "textures/mb64_textures/MCDirt.ci4.pal"
};
DEFINE_CI4(mb64_tex_MCDirt, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_MCGrassTop_ci4[] = {
#include "textures/mb64_textures/MCGrassTop.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_MCGrassTop_pal_rgba16[] = {
#include "textures/mb64_textures/MCGrassTop.ci4.pal"
};
DEFINE_CI4(mb64_tex_MCGrassTop, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_MCGrassEdge_ci4[] = {
#include "textures/mb64_textures/MCGrassEdge.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_MCGrassEdge_pal_rgba16[] = {
#include "textures/mb64_textures/MCGrassEdge.ci4.pal"
};
DEFINE_CI4(mb64_tex_MCGrassEdge, 4, 4, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_MCCobblestone_ci4[] = {
#include "textures/mb64_textures/MCCobblestone.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_MCCobblestone_pal_rgba16[] = {
#include "textures/mb64_textures/MCCobblestone.ci4.pal"
};
DEFINE_CI4(mb64_tex_MCCobblestone, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_MCStone_ci4[] = {
#include "textures/mb64_textures/MCStone.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_MCStone_pal_rgba16[] = {
#include "textures/mb64_textures/MCStone.ci4.pal"
};
DEFINE_CI4(mb64_tex_MCStone, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_MCOakLogTop_ci4[] = {
#include "textures/mb64_textures/MCOakLogTop.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_MCOakLogTop_pal_rgba16[] = {
#include "textures/mb64_textures/MCOakLogTop.ci4.pal"
};
DEFINE_CI4(mb64_tex_MCOakLogTop, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_MCOakLogSide_ci4[] = {
#include "textures/mb64_textures/MCOakLogSide.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_MCOakLogSide_pal_rgba16[] = {
#include "textures/mb64_textures/MCOakLogSide.ci4.pal"
};
DEFINE_CI4(mb64_tex_MCOakLogSide, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_MCOakLeaves_ci4[] = {
#include "textures/mb64_textures/MCOakLeaves.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_MCOakLeaves_pal_rgba16[] = {
#include "textures/mb64_textures/MCOakLeaves.ci4.pal"
};
DEFINE_CI4(mb64_tex_MCOakLeaves, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_MCWoodPlanks_ci4[] = {
#include "textures/mb64_textures/MCWoodPlanks.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_MCWoodPlanks_pal_rgba16[] = {
#include "textures/mb64_textures/MCWoodPlanks.ci4.pal"
};
DEFINE_CI4(mb64_tex_MCWoodPlanks, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_MCSand_ci4[] = {
#include "textures/mb64_textures/MCSand.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_MCSand_pal_rgba16[] = {
#include "textures/mb64_textures/MCSand.ci4.pal"
};
DEFINE_CI4(mb64_tex_MCSand, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_MCBricks_ci4[] = {
#include "textures/mb64_textures/MCBricks.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_MCBricks_pal_rgba16[] = {
#include "textures/mb64_textures/MCBricks.ci4.pal"
};
DEFINE_CI4(mb64_tex_MCBricks, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_MCLava_ci8[] = {
#include "textures/mb64_textures/MCLava.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_MCLava_pal_rgba16[] = {
#include "textures/mb64_textures/MCLava.ci8.pal"
};
DEFINE_CI8(mb64_tex_MCLava, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_MCFlowingLava_ci8[] = {
#include "textures/mb64_textures/MCFlowingLava.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_MCFlowingLava_pal_rgba16[] = {
#include "textures/mb64_textures/MCFlowingLava.ci8.pal"
};
DEFINE_CI8(mb64_tex_MCFlowingLava, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_MCGlass_ci4[] = {
#include "textures/mb64_textures/MCGlass.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_MCGlass_pal_rgba16[] = {
#include "textures/mb64_textures/MCGlass.ci4.pal"
};
DEFINE_CI4(mb64_tex_MCGlass, 4, 4, G_TX_WRAP, G_TX_WRAP);

// Fences
ALIGNED8 static const Texture mb64_tex_Fence_ci8[] = {
#include "textures/mb64_textures/Fence.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_Fence_pal_rgba16[] = {
#include "textures/mb64_textures/Fence.ci8.pal"
};
DEFINE_CI8(mb64_tex_Fence, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_WoodenFence_ci8[] = {
#include "textures/mb64_textures/WoodenFence.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_WoodenFence_pal_rgba16[] = {
#include "textures/mb64_textures/WoodenFence.ci8.pal"
};
DEFINE_CI8(mb64_tex_WoodenFence, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_DFence_ci8[] = {
#include "textures/mb64_textures/DFence.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_DFence_pal_rgba16[] = {
#include "textures/mb64_textures/DFence.ci8.pal"
};
DEFINE_CI8(mb64_tex_DFence, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_BarbedWire_ci8[] = {
#include "textures/mb64_textures/BarbedWire.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_BarbedWire_pal_rgba16[] = {
#include "textures/mb64_textures/BarbedWire.ci8.pal"
};
DEFINE_CI8(mb64_tex_BarbedWire, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_RHRFence_ci4[] = {
#include "textures/mb64_textures/RHRFence.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RHRFence_pal_rgba16[] = {
#include "textures/mb64_textures/RHRFence.ci4.pal"
};
DEFINE_CI4(mb64_tex_RHRFence, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_HFence_ci8[] = {
#include "textures/mb64_textures/HFence.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_HFence_pal_rgba16[] = {
#include "textures/mb64_textures/HFence.ci8.pal"
};
DEFINE_CI8(mb64_tex_HFence, 5, 4, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_CFence_ci8[] = {
#include "textures/mb64_textures/CFence.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_CFence_pal_rgba16[] = {
#include "textures/mb64_textures/CFence.ci8.pal"
};
DEFINE_CI8(mb64_tex_CFence, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_VPFence_ci8[] = {
#include "textures/mb64_textures/VPFence.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_VPFence_pal_rgba16[] = {
#include "textures/mb64_textures/VPFence.ci8.pal"
};
DEFINE_CI8(mb64_tex_VPFence, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_BBHFence_ci8[] = {
#include "textures/mb64_textures/BBHFence.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_BBHFence_pal_rgba16[] = {
#include "textures/mb64_textures/BBHFence.ci8.pal"
};
DEFINE_CI8(mb64_tex_BBHFence, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_JRBFence_ci8[] = {
#include "textures/mb64_textures/JRBFence.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_JRBFence_pal_rgba16[] = {
#include "textures/mb64_textures/JRBFence.ci8.pal"
};
DEFINE_CI8(mb64_tex_JRBFence, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_SnowFence2_ci8[] = {
#include "textures/mb64_textures/SnowFence2.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_SnowFence2_pal_rgba16[] = {
#include "textures/mb64_textures/SnowFence2.ci8.pal"
};
DEFINE_CI8(mb64_tex_SnowFence2, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_SnowFence_ci8[] = {
#include "textures/mb64_textures/SnowFence.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_SnowFence_pal_rgba16[] = {
#include "textures/mb64_textures/SnowFence.ci8.pal"
};
DEFINE_CI8(mb64_tex_SnowFence, 5, 5, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_RetroFence_ci4[] = {
#include "textures/mb64_textures/RetroFence.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RetroFence_pal_rgba16[] = {
#include "textures/mb64_textures/RetroFence.ci4.pal"
};
DEFINE_CI4(mb64_tex_RetroFence, 4, 4, G_TX_WRAP, G_TX_CLAMP);

ALIGNED8 static const Texture mb64_tex_MCFence_ci8[] = {
#include "textures/mb64_textures/MCFence.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_MCFence_pal_rgba16[] = {
#include "textures/mb64_textures/MCFence.ci8.pal"
};
DEFINE_CI8(mb64_tex_MCFence, 4, 4, G_TX_WRAP, G_TX_CLAMP);

// Bars
ALIGNED8 static const Texture mb64_tex_IronBars_ci4[] = {
#include "textures/mb64_textures/IronBars.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_IronBars_pal_rgba16[] = {
#include "textures/mb64_textures/IronBars.ci4.pal"
};
DEFINE_CI4(mb64_tex_IronBars, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_IronBarsTop_ci4[] = {
#include "textures/mb64_textures/IronBarsTop.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_IronBarsTop_pal_rgba16[] = {
#include "textures/mb64_textures/IronBarsTop.ci4.pal"
};
DEFINE_CI4(mb64_tex_IronBarsTop, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_ChainTop_ci4[] = {
#include "textures/mb64_textures/ChainTop.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_ChainTop_pal_rgba16[] = {
#include "textures/mb64_textures/ChainTop.ci4.pal"
};
DEFINE_CI4(mb64_tex_ChainTop, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_HMCTop_ci4[] = {
#include "textures/mb64_textures/HMCTop.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_HMCTop_pal_rgba16[] = {
#include "textures/mb64_textures/HMCTop.ci4.pal"
};
DEFINE_CI4(mb64_tex_HMCTop, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_ChainTopPink_ci4[] = {
#include "textures/mb64_textures/ChainTopPink.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_ChainTopPink_pal_rgba16[] = {
#include "textures/mb64_textures/ChainTopPink.ci4.pal"
};
DEFINE_CI4(mb64_tex_ChainTopPink, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_TTCGrateTop_ci8[] = {
#include "textures/mb64_textures/TTCGrateTop.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_TTCGrateTop_pal_rgba16[] = {
#include "textures/mb64_textures/TTCGrateTop.ci8.pal"
};
DEFINE_CI8(mb64_tex_TTCGrateTop, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_DMesh_ci8[] = {
#include "textures/mb64_textures/DMesh.ci8.inc.c"
};
ALIGNED8 static const Texture mb64_tex_DMesh_pal_rgba16[] = {
#include "textures/mb64_textures/DMesh.ci8.pal"
};
DEFINE_CI8(mb64_tex_DMesh, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_DesertMeshTop_ci4[] = {
#include "textures/mb64_textures/DesertMeshTop.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_DesertMeshTop_pal_rgba16[] = {
#include "textures/mb64_textures/DesertMeshTop.ci4.pal"
};
DEFINE_CI4(mb64_tex_DesertMeshTop, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_BOBBars_ci4[] = {
#include "textures/mb64_textures/BOBBars.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_BOBBars_pal_rgba16[] = {
#include "textures/mb64_textures/BOBBars.ci4.pal"
};
DEFINE_CI4(mb64_tex_BOBBars, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_BOBBarsTop_ci4[] = {
#include "textures/mb64_textures/BOBBarsTop.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_BOBBarsTop_pal_rgba16[] = {
#include "textures/mb64_textures/BOBBarsTop.ci4.pal"
};
DEFINE_CI4(mb64_tex_BOBBarsTop, 5, 5, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_RetroMesh_ci4[] = {
#include "textures/mb64_textures/RetroMesh.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RetroMesh_pal_rgba16[] = {
#include "textures/mb64_textures/RetroMesh.ci4.pal"
};
DEFINE_CI4(mb64_tex_RetroMesh, 4, 4, G_TX_WRAP, G_TX_MIRROR);

ALIGNED8 static const Texture mb64_tex_RetroMeshTop_ci4[] = {
#include "textures/mb64_textures/RetroMeshTop.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RetroMeshTop_pal_rgba16[] = {
#include "textures/mb64_textures/RetroMeshTop.ci4.pal"
};
DEFINE_CI4(mb64_tex_RetroMeshTop, 5, 5, G_TX_WRAP, G_TX_MIRROR);

ALIGNED8 static const Texture mb64_tex_MCIronBars_ci4[] = {
#include "textures/mb64_textures/MCIronBars.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_MCIronBars_pal_rgba16[] = {
#include "textures/mb64_textures/MCIronBars.ci4.pal"
};
DEFINE_CI4(mb64_tex_MCIronBars, 4, 4, G_TX_WRAP, G_TX_WRAP);

ALIGNED8 static const Texture mb64_tex_MCIronBarsTop_ci4[] = {
#include "textures/mb64_textures/MCIronBarsTop.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_MCIronBarsTop_pal_rgba16[] = {
#include "textures/mb64_textures/MCIronBarsTop.ci4.pal"
};
DEFINE_CI4(mb64_tex_MCIronBarsTop, 4, 4, G_TX_WRAP, G_TX_WRAP);

// Water
ALIGNED8 static const Texture mb64_tex_Water_ci4[] = {
#include "textures/mb64_textures/Water.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_Water_pal_rgba16[] = {
#include "textures/mb64_textures/Water.ci4.pal"
};
DEFINE_CI4_ALPHA(mb64_tex_Water, 5, 5, G_TX_WRAP, G_TX_WRAP, 178);

ALIGNED8 static const Texture mb64_tex_GreenWater_ci4[] = {
#include "textures/mb64_textures/GreenWater.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_GreenWater_pal_rgba16[] = {
#include "textures/mb64_textures/GreenWater.ci4.pal"
};
DEFINE_CI4_ALPHA(mb64_tex_GreenWater, 5, 5, G_TX_WRAP, G_TX_WRAP, 178);

ALIGNED8 static const Texture mb64_tex_RetroWater_ci4[] = {
#include "textures/mb64_textures/RetroWater.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_RetroWater_pal_rgba16[] = {
#include "textures/mb64_textures/RetroWater.ci4.pal"
};
DEFINE_CI4_ALPHA(mb64_tex_RetroWater, 4, 4, G_TX_WRAP, G_TX_WRAP, 178);

ALIGNED8 static const Texture mb64_tex_MCWater_ci4[] = {
#include "textures/mb64_textures/MCWater.ci4.inc.c"
};
ALIGNED8 static const Texture mb64_tex_MCWater_pal_rgba16[] = {
#include "textures/mb64_textures/MCWater.ci4.pal"
};
DEFINE_CI4_ALPHA(mb64_tex_MCWater, 4, 4, G_TX_WRAP, G_TX_WRAP, 191);

const Gfx mb64_dl_Black[] = {
    gsDPPipeSync(),
    gsSPLightColor(LIGHT_1, 0xffffffff),
    gsSPLightColor(LIGHT_2, 0x7f7f7fff),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, 0, 0, 0, 1,
                       PRIMITIVE, 0, SHADE, 0, 0, 0, 0, 1),
    gsDPSetPrimColor(0, 0, 0, 0, 0, 255),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

