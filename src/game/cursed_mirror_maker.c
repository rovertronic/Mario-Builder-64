//object includes (a lot)
#include "text_strings.h"
#include "types.h"
#include "actors/common0.h"
#include "actors/common1.h"
#include "actors/group2.h"
#include "actors/group12.h"
#include "actors/group13.h"
#include "area.h"
#include "audio/external.h"
#include "behavior_actions.h"
#include "behavior_data.h"
#include "camera.h"
#include "debug.h"
#include "dialog_ids.h"
#include "engine/behavior_script.h"
#include "engine/graph_node.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "engine/surface_load.h"
#include "game_init.h"
#include "ingame_menu.h"
#include "interaction.h"
#include "level_misc_macros.h"
#include "level_table.h"
#include "level_update.h"
#include "levels/bob/header.h"
#include "levels/bowser_3/header.h"
#include "levels/castle_inside/header.h"
#include "levels/hmc/header.h"
#include "levels/menu/header.h"
#include "main.h"
#include "mario.h"
#include "mario_actions_cutscene.h"
#include "mario_step.h"
#include "obj_behaviors.h"
#include "obj_behaviors_2.h"
#include "object_constants.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "paintings.h"
#include "platform_displacement.h"
#include "rendering_graph_node.h"
#include "save_file.h"
#include "seq_ids.h"
#include "sm64.h"
#include "spawn_object.h"
#include "spawn_sound.h"
#include "rumble_init.h"
#include "puppylights.h"
#include "rovent.h"
#include "cursed_mirror_maker.h"
#include "actors/group0.h"
#include "levels/bob/header.h"
#include "sram.h"
#include "level_geo.h"
#include "src/buffers/framebuffers.h"
#include "memory.h"

#include "libcart/include/cart.h"
#include "libcart/ff/ff.h"

u8 cmm_mode = CMM_MODE_UNINITIALIZED;
u8 cmm_target_mode = CMM_MODE_MAKE;
u8 cmm_joystick_timer = 0;
u8 cmm_sbx, cmm_sby, cmm_sbz = 0;

Vec3f cmm_camera_pos = {0.0f};
Vec3f cmm_camera_foc = {0.0f};
s16 cmm_camera_angle = 0;
u8 cmm_camera_rot_offset = 0;
s8 cmm_camera_zoom_index = 2;
f32 cmm_camera_zoom_table[][2] = {
    {900.0f,50.0f},
    {900.0f,400.0f},
    {1500.0f,800.0f},
    {2000.0f,900.0f},
    {2100.0f,1500.0f},
};
f32 cmm_current_camera_zoom[2] = {1500.0f,800.0f};

u8 cmm_place_mode = CMM_PM_TILE;

s8 cmm_id_selection = 0;
u8 cmm_rot_selection = 0;
s16 cmm_param_selection = 0;
s16 cmm_mat_selection = 0;

// lookup table for rotating blocks
u8 cmm_rotated_dirs[4][6] = {
    {CMM_DIRECTION_UP, CMM_DIRECTION_DOWN, CMM_DIRECTION_POS_X, CMM_DIRECTION_NEG_X, CMM_DIRECTION_POS_Z, CMM_DIRECTION_NEG_Z},
    {CMM_DIRECTION_UP, CMM_DIRECTION_DOWN, CMM_DIRECTION_NEG_Z, CMM_DIRECTION_POS_Z, CMM_DIRECTION_POS_X, CMM_DIRECTION_NEG_X},
    {CMM_DIRECTION_UP, CMM_DIRECTION_DOWN, CMM_DIRECTION_NEG_X, CMM_DIRECTION_POS_X, CMM_DIRECTION_NEG_Z, CMM_DIRECTION_POS_Z},
    {CMM_DIRECTION_UP, CMM_DIRECTION_DOWN, CMM_DIRECTION_POS_Z, CMM_DIRECTION_NEG_Z, CMM_DIRECTION_NEG_X, CMM_DIRECTION_POS_X},
};

#define ROTATE_DIRECTION(dir, rot) (cmm_rotated_dirs[rot][dir])

struct cmm_terrain_quad cmm_terrain_fullblock_quads[] = {
    {{{1, 1, 1},  {1, 1, -1},  {-1, 1, 1},  {-1, 1, -1}},  1, CMM_DIRECTION_UP, CMM_FACESHAPE_FULL, CMM_GROWTH_FULL, NULL}, // TOP
    {{{1, -1, 1}, {-1, -1, 1}, {1, -1, -1}, {-1, -1, -1}}, 1, CMM_DIRECTION_DOWN, CMM_FACESHAPE_FULL, 0, NULL}, // BOTTOM
    {{{1, 1, 1},  {1, -1, 1},  {1, 1, -1},  {1, -1, -1}},  0, CMM_DIRECTION_POS_X, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // LEFT
    {{{-1, 1, 1}, {-1, 1, -1}, {-1, -1, 1}, {-1, -1, -1}}, 0, CMM_DIRECTION_NEG_X, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
    {{{1, 1, 1},  {-1, 1, 1},  {1, -1, 1},  {-1, -1, 1}},  2, CMM_DIRECTION_POS_Z, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // FRONT
    {{{1, 1, -1}, {1, -1, -1}, {-1, 1, -1}, {-1, -1, -1}}, 2, CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // BACK
};
struct cmm_terrain_block cmm_terrain_fullblock = {
    6,
    0,
    &cmm_terrain_fullblock_quads,
    NULL
};

struct cmm_terrain_quad cmm_terrain_slope_quads[] = {
    {{{1, -1, 1},  {1, 1, -1},  {-1, -1, 1},  {-1, 1, -1}},  1, CMM_NO_CULLING, CMM_FACESHAPE_EMPTY, CMM_GROWTH_FULL, NULL}, // TOP
    {{{1, -1, 1}, {-1, -1, 1}, {1, -1, -1}, {-1, -1, -1}}, 1, CMM_DIRECTION_DOWN, CMM_FACESHAPE_FULL, 0, NULL}, // BOTTOM
    {{{1, 1, -1}, {1, -1, -1}, {-1, 1, -1}, {-1, -1, -1}}, 2, CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // BACK
};

s8 slope_decal_uvs1[3][2] = {{-1, -1}, {-1, 1}, {1, 1}};
s8 slope_decal_uvs2[3][2] = {{-1, 1}, {-1, -1}, {1, 1}};

struct cmm_terrain_tri cmm_terrain_slope_tris[] = {
    {{{1, -1, -1}, {1, 1, -1}, {1, -1, 1}},  0, CMM_DIRECTION_POS_X, CMM_FACESHAPE_TRI_1, CMM_GROWTH_UNCONDITIONAL_SIDE, &slope_decal_uvs1}, // LEFT
    {{{-1, 1, -1}, {-1, -1, -1}, {-1, -1, 1}}, 0, CMM_DIRECTION_NEG_X, CMM_FACESHAPE_TRI_2, CMM_GROWTH_UNCONDITIONAL_SIDE, &slope_decal_uvs2}, // RIGHT
};

struct cmm_terrain_block cmm_terrain_slope = {
    3,
    2,
    &cmm_terrain_slope_quads,
    &cmm_terrain_slope_tris,
};

struct cmm_terrain_quad cmm_terrain_corner_quads[] = {
    {{{1, -1, 1}, {-1, -1, 1}, {1, -1, -1}, {-1, -1, -1}}, 1, CMM_DIRECTION_DOWN, CMM_FACESHAPE_FULL, 0, NULL}, // BOTTOM
};

struct cmm_terrain_tri cmm_terrain_corner_tris[] = {
    {{{-1, -1, 1}, {1, -1, 1}, {-1, 1, -1}},  1, CMM_NO_CULLING, CMM_FACESHAPE_FULL, CMM_GROWTH_FULL, NULL}, // TOP-FRONT
    {{{-1, 1, -1}, {1, -1, 1}, {1, -1, -1}},  1, CMM_NO_CULLING, CMM_FACESHAPE_FULL, CMM_GROWTH_FULL, NULL}, // TOP-LEFT 
    {{{-1, 1, -1}, {-1, -1, -1}, {-1, -1, 1}}, 0, CMM_DIRECTION_NEG_X, CMM_FACESHAPE_TRI_2, CMM_GROWTH_UNCONDITIONAL_SIDE, &slope_decal_uvs2}, // RIGHT
    {{{-1, -1, -1}, {-1, 1, -1}, {1, -1, -1}},  2, CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_TRI_1, CMM_GROWTH_UNCONDITIONAL_SIDE, &slope_decal_uvs1}, // BACK
};

struct cmm_terrain_block cmm_terrain_corner = {
    1,
    4,
    &cmm_terrain_corner_quads,
    &cmm_terrain_corner_tris,
};

struct cmm_terrain_quad cmm_terrain_icorner_quads[] = {
    {{{1, -1, 1}, {-1, -1, 1}, {1, -1, -1}, {-1, -1, -1}}, 1, CMM_DIRECTION_DOWN, CMM_FACESHAPE_FULL, 0, NULL}, // BOTTOM
    {{{1, 1, -1}, {1, -1, -1}, {-1, 1, -1}, {-1, -1, -1}}, 2, CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // BACK
    {{{-1, 1, 1}, {-1, 1, -1}, {-1, -1, 1}, {-1, -1, -1}}, 0, CMM_DIRECTION_NEG_X, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
};

struct cmm_terrain_tri cmm_terrain_icorner_tris[] = {
    {{{-1, 1, 1}, {1, -1, 1}, {-1, 1, -1}},  1, CMM_NO_CULLING, CMM_FACESHAPE_FULL, CMM_GROWTH_FULL, NULL}, // TOP-FRONT
    {{{-1, 1, -1}, {1, -1, 1}, {1, 1, -1}},  1, CMM_NO_CULLING, CMM_FACESHAPE_FULL, CMM_GROWTH_FULL, NULL}, // TOP-LEFT
    {{{1, -1, -1}, {1, 1, -1}, {1, -1, 1}},  0, CMM_DIRECTION_POS_X, CMM_FACESHAPE_TRI_1, CMM_GROWTH_UNCONDITIONAL_SIDE, &slope_decal_uvs1}, // LEFT
    {{{-1, 1, 1}, {-1, -1, 1}, {1, -1, 1}},  2, CMM_DIRECTION_POS_Z, CMM_FACESHAPE_TRI_2, CMM_GROWTH_UNCONDITIONAL_SIDE, &slope_decal_uvs2}, // FRONT
};

struct cmm_terrain_block cmm_terrain_icorner = {
    3,
    4,
    &cmm_terrain_icorner_quads,
    &cmm_terrain_icorner_tris,
};

struct cmm_terrain_quad cmm_terrain_dslope_quads[] = {
    {{{1, 1, 1},  {1, 1, -1},  {-1, 1, 1},  {-1, 1, -1}},  1, CMM_DIRECTION_UP, CMM_FACESHAPE_FULL, CMM_GROWTH_FULL, NULL}, // TOP
    {{{1, 1, -1}, {1, -1, -1}, {-1, 1, -1}, {-1, -1, -1}}, 2, CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // BACK
    {{{1, 1, 1}, {-1, 1, 1}, {1, -1, -1}, {-1, -1, -1}}, 2, CMM_NO_CULLING, CMM_FACESHAPE_EMPTY, CMM_GROWTH_UNDERSLOPE, NULL}, // BOTTOM
};

struct cmm_terrain_tri cmm_terrain_dslope_tris[] = {
    {{{1, -1, -1}, {1, 1, -1}, {1, 1, 1}},  0, CMM_DIRECTION_POS_X, CMM_FACESHAPE_DOWNTRI_1, CMM_GROWTH_NORMAL_SIDE, NULL}, // LEFT
    {{{-1, 1, -1}, {-1, -1, -1}, {-1, 1, 1}}, 0, CMM_DIRECTION_NEG_X, CMM_FACESHAPE_DOWNTRI_2, CMM_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
};

struct cmm_terrain_block cmm_terrain_dslope = {
    3,
    2,
    &cmm_terrain_dslope_quads,
    &cmm_terrain_dslope_tris,
};

struct cmm_terrain_quad cmm_terrain_sslope_quads[] = {
    {{{1, 1, -1}, {1, -1, -1}, {-1, 1, -1}, {-1, -1, -1}}, 2, CMM_DIRECTION_NEG_Z, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // BACK
    {{{-1, 1, 1}, {-1, 1, -1}, {-1, -1, 1}, {-1, -1, -1}}, 0, CMM_DIRECTION_NEG_X, CMM_FACESHAPE_FULL, CMM_GROWTH_NORMAL_SIDE, NULL}, // RIGHT
    {{{1, 1, -1},  {-1, 1, 1},  {1, -1, -1},  {-1, -1, 1}},  2, CMM_NO_CULLING, CMM_FACESHAPE_EMPTY, CMM_GROWTH_DIAGONAL_SIDE, NULL}, // DIAGONAL
};

struct cmm_terrain_tri cmm_terrain_sslope_tris[] = {
    {{{-1, 1, 1}, {1, 1, -1}, {-1, 1, -1}}, 1, CMM_DIRECTION_UP, CMM_FACESHAPE_TOPTRI, CMM_GROWTH_FULL, NULL}, // TOP
    {{{1, -1, -1}, {-1, -1, 1}, {-1, -1, -1}}, 1, CMM_DIRECTION_DOWN, CMM_FACESHAPE_TOPTRI, 0, NULL}, // BOTTOM
};

struct cmm_terrain_block cmm_terrain_sslope = {
    3,
    2,
    &cmm_terrain_sslope_quads,
    &cmm_terrain_sslope_tris,
};

struct cmm_tile_type_struct cmm_tile_types[] = {
    //Model GFX           //F3D Material            //Collision Mesh             //Grass   //Transparent
    {NULL, &cmm_terrain_fullblock, NULL   , FALSE},//TILE_TYPE_BLOCK
    {NULL, &cmm_terrain_slope,     NULL  , FALSE},//TILE_TYPE_SLOPE
    {NULL, &cmm_terrain_corner,    NULL , FALSE},//TILE_TYPE_CORNER
    {NULL, &cmm_terrain_icorner,  NULL, FALSE},//TILE_TYPE_ICORNER
    {NULL, NULL,                   NULL                       , FALSE},//TILE_TYPE_TROLL
    {&cull_cull_mesh, NULL,        NULL                       , FALSE},//TILE_TYPE_CULL
    {NULL, &cmm_terrain_dslope,    NULL           , FALSE},//TILE_TYPE_DSLOPE
    {&makerwater_mw_mesh, NULL,    makerwater_collision       , TRUE },//TILE_TYPE_WATER
    {&makerfence_mfv_mesh, NULL,   makerfence_collision       , TRUE },//TILE_TYPE_FENCE
    {NULL, &cmm_terrain_sslope,    NULL           , FALSE },//TILE_TYPE_SSLOPE
};

void df_badge(struct Object * obj, int param) {
    obj->oBehParams2ndByte = param;
}

void df_tree(struct Object * obj, int param) {
    switch(param) {
        case 1:
            obj->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_TREE_2];
        break;
        case 2:
            obj->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_TREE_3];
        break;
        case 3:
            obj->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MAKER_TREE_4];
        break;
    }
}

void df_boss(struct Object * obj, int param) {
    switch(param) {
        case 1:
            obj->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_WHOMP_MAKER];
            obj->oAnimations = whomp_seg6_anims_06020A04;
            super_cum_working(obj,0);
            obj_scale(obj,2.0f);
        break;
        case 3:
            obj->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_WIGGLER_HEAD];
            obj->oAnimations = wiggler_seg5_anims_0500EC8C;
            super_cum_working(obj,0);
            obj_scale(obj,4.0f);
        break;
    }
}

void df_exbox(struct Object * obj, int param) {
    switch(param) {
        case 0:
            obj->oAnimState = 0;
        break;
        case 1:
            obj->oAnimState = 1;
        break;
        case 2:
            obj->oAnimState = 2;
        break;
        case 3:
            obj->oAnimState = 3;
        break;
        default:
            obj->oAnimState = 4;
        break;
    }
}

struct cmm_object_type_struct cmm_object_types[] = {
    //BEHAVIOR           //Y-OFF    //MODEL ID                  //BILLB //TRAJ //SCALE  //ANIMATION PTR              //MX BPRM   //DISP.FUNC
    {bhvStar             , 0.0f     ,MODEL_STAR                 ,FALSE  ,FALSE ,1.0f   ,NULL                         , 0       , NULL       },
    {bhvGoomba           ,-150.0f   ,MODEL_GOOMBA               ,FALSE  ,FALSE ,1.5f   ,goomba_seg8_anims_0801DA4C   , 0       , NULL       },
    {bhvYellowCoin       ,-150.0f   ,MODEL_YELLOW_COIN          ,TRUE   ,FALSE ,1.0f   ,NULL                         , 0       , NULL       },
    {bhvGreenCoin        ,-150.0f   ,0xEF                       ,TRUE   ,FALSE ,1.0f   ,NULL                         , 0       , NULL       },
    {bhvRedCoin          ,-150.0f   ,MODEL_RED_COIN             ,TRUE   ,FALSE ,1.0f   ,NULL                         , 0       , NULL       },
    {bhvHiddenBlueCoin   ,-150.0f   ,MODEL_BLUE_COIN            ,TRUE   ,FALSE ,1.0f   ,NULL                         , 0       , NULL       },
    {bhvBlueCoinSwitch   ,-150.0f   ,MODEL_BLUE_COIN_SWITCH     ,FALSE  ,FALSE ,3.0f   ,NULL                         , 0       , NULL       },
    {bhvHiddenRedCoinStar, 0.0f     ,MODEL_TRANSPARENT_STAR     ,FALSE  ,FALSE ,1.0f   ,NULL                         , 0       , NULL       },
    {bhvNoteblock        , 0.0f     ,MODEL_NOTEBLOCK            ,FALSE  ,FALSE ,1.0f   ,NULL                         , 0       , NULL       },
    {bhvPodoboo          , 0.0f     ,MODEL_PODOBOO              ,FALSE  ,FALSE ,1.0f   ,NULL                         , 0       , NULL       },
    {bhvRex              ,-150.0f   ,0xE1                       ,FALSE  ,FALSE ,1.5f   ,Rex_anims                    , 0       , NULL       },
    {bhvSmallBully       ,-150.0f   ,MODEL_BULLY                ,FALSE  ,FALSE ,1.0f   ,bully_seg5_anims_0500470C    , 0       , NULL       },
    {bhvBobomb           ,-150.0f   ,MODEL_BLACK_BOBOMB         ,FALSE  ,FALSE ,1.0f   ,bobomb_seg8_anims_0802396C   , 0       , NULL       },
    {bhvTree             ,-150.0f   ,MODEL_MAKER_TREE_1         ,TRUE   ,FALSE ,1.0f   ,NULL                         , 4       , &df_tree   },
    {bhvExclamationBox   , 0.0f     ,MODEL_EXCLAMATION_BOX      ,FALSE  ,FALSE ,2.0f   ,NULL                         , 8       , &df_exbox  },
    {bhvChuckya          ,-150.0f   ,MODEL_CHUCKYA              ,FALSE  ,FALSE ,2.0f   ,chuckya_seg8_anims_0800C070  , 0       , NULL       },
    {bhvSpawn            , 0.0f     ,MODEL_SPAWN                ,FALSE  ,FALSE ,1.0f   ,NULL                         , 0       , NULL       },
    {bhvPhantasm         ,-150.0f   ,MODEL_MARIO                ,FALSE  ,FALSE ,1.0f   ,&evil_mario_anims[2]         , 0       , NULL       },
    {bhvWarpPipe         ,-150.0f   ,MODEL_MAKER_PIPE           ,FALSE  ,FALSE ,1.0f   ,NULL                         , 1       , NULL       },
    {bhvBadge            ,0.0f      ,MODEL_BADGE                ,TRUE   ,FALSE ,5.0f   ,NULL                         , 23      , &df_badge  },
    {bhvBoss             ,-150.0f   ,MODEL_KINGBOMB_MAKER       ,FALSE  ,FALSE ,1.0f   ,king_bobomb_seg5_anims_0500FE30, 2     , &df_boss   },
    {bhvPlatformOnTrack  ,0.0f      ,MODEL_CHECKERBOARD_PLATFORM,FALSE  ,TRUE  ,1.0f   ,NULL                         , 0       , NULL       },
    {bhvBobBowlingBallSpawner,0.0f  ,MODEL_BOWLING_BALL         ,TRUE   ,TRUE  ,1.0f   ,NULL                         , 0       , NULL       },
    {bhvKoopa            ,-150.0f   ,MODEL_KOOPA_WITH_SHELL     ,FALSE  ,TRUE  ,3.0f   ,koopa_seg6_anims_06011364    , 0       , NULL       },
};

struct cmm_grid_obj cmm_grid_data[32][32][32] = {0};

Gfx cmm_terrain_gfx[23000]; //gfx
Gfx cmm_terrain_gfx_tp[8000];//transparent
Mtx cmm_terrain_mtx[5000]; //translations
Vtx cmm_terrain_vtx[25000];

u16 cmm_gfx_total = 0;
u16 cmm_mtx_total = 0;
u16 cmm_vtx_total = 0;
u16 cmm_gfx_tp_total = 0;

struct cmm_tile cmm_tile_data[2000];
struct cmm_obj cmm_object_data[200];
u16 cmm_tile_count = 0;
u16 cmm_object_count = 0;

struct Object *cmm_preview_object;
struct Object *cmm_boundary_object[6]; //one for each side

Trajectory cmm_trajectory_list[5][160];
u16 cmm_trajectory_edit_index = 0;
u8 cmm_trajectory_to_edit = 0;
u8 cmm_trajectories_used = 0; //bitfield
u8 cmm_txt_recording[] = {TXT_RECORDING};
Vtx cmm_trajectory_vtx[240];
Gfx cmm_trajectory_gfx[100]; //gfx

//play mode stuff
u8 cmm_play_stars = 0;
u8 cmm_play_stars_max = 0;
u32 cmm_play_stars_bitfield = 0;
u32 cmm_play_badge_bitfield = 0;

u8 cmm_star_objects[] = {
    OBJECT_TYPE_STAR,
    OBJECT_TYPE_RCS,
    OBJECT_TYPE_BOSS,
    OBJECT_TYPE_KTQ,
};

//skybox table
u8 *cmm_skybox_table[] = {
    _water_skybox_yay0SegmentRomStart,
    _water_skybox_yay0SegmentRomEnd,
    _cloud_floor_skybox_yay0SegmentRomStart,
    _cloud_floor_skybox_yay0SegmentRomEnd,
    _bitfs_skybox_yay0SegmentRomStart,
    _bitfs_skybox_yay0SegmentRomEnd,
    _bidw_skybox_yay0SegmentRomStart,
    _bidw_skybox_yay0SegmentRomEnd,
    _bbh_skybox_yay0SegmentRomStart,
    _bbh_skybox_yay0SegmentRomEnd,
    _ccm_skybox_yay0SegmentRomStart,
    _ccm_skybox_yay0SegmentRomEnd,
    _ssl_skybox_yay0SegmentRomStart,
    _ssl_skybox_yay0SegmentRomEnd,
    _bits_skybox_yay0SegmentRomStart,
    _bits_skybox_yay0SegmentRomEnd,
};

//envfx strings
u8 txt_envfx_1[] = {TXT_ENVFX_1};u8 txt_envfx_2[] = {TXT_ENVFX_2};u8 txt_envfx_3[] = {TXT_ENVFX_3};
u8 txt_envfx_4[] = {TXT_ENVFX_4};u8 txt_envfx_5[] = {TXT_ENVFX_5};u8 txt_envfx_6[] = {TXT_ENVFX_6};
u8 *cmm_envfx_string_table[] = {
    &txt_envfx_1,
    &txt_envfx_2,
    &txt_envfx_3,
    &txt_envfx_4,
    &txt_envfx_5,
    &txt_envfx_6,
};

//envfx table
u8 cmm_envfx_table[] = {
    ENVFX_MODE_NONE,         // no effects
    ENVFX_SNOW_NORMAL,       // CCM, SL
    ENVFX_SNOW_BLIZZARD,     // unused
    ENVFX_FLOWERS,           // unused
    ENVFX_LAVA_BUBBLES,      // LLL, BitFS, Bowser 2
    ENVFX_RAIN
};

//background strings
u8 txt_bg_1[] = {TXT_BG1}; u8 txt_bg_2[] = {TXT_BG2}; u8 txt_bg_3[] = {TXT_BG3}; u8 txt_bg_4[] = {TXT_BG4};
u8 txt_bg_5[] = {TXT_BG5}; u8 txt_bg_6[] = {TXT_BG6}; u8 txt_bg_7[] = {TXT_BG7}; u8 txt_bg_8[] = {TXT_BG8};
u8 *cmm_bg_string_table[] = {
    txt_bg_1,
    txt_bg_2,
    txt_bg_3,
    txt_bg_4,
    txt_bg_5,
    txt_bg_6,
    txt_bg_7,
    txt_bg_8,
};

//bottom plane strings
u8 txt_plane_1[] = {TXT_PLANE_1};u8 txt_plane_2[] = {TXT_PLANE_2};u8 txt_plane_3[] = {TXT_PLANE_3};
u8 *cmm_plane_string_table[] = {
    txt_plane_1,
    txt_plane_2,
    txt_plane_3,
};

//behparam2 strings
u8 txt_bp_box1[] = {TXT_BP_BOX_1}; u8 txt_bp_box2[] = {TXT_BP_BOX_2}; u8 txt_bp_box3[] = {TXT_BP_BOX_3}; u8 txt_bp_box4[] = {TXT_BP_BOX_4};
u8 txt_bp_box5[] = {TXT_BP_BOX_5}; u8 txt_bp_box6[] = {TXT_BP_BOX_6}; u8 txt_bp_box7[] = {TXT_BP_BOX_7}; u8 txt_bp_box8[] = {TXT_BP_BOX_8};
u8 *txt_bp_box[] = {
    txt_bp_box1,
    txt_bp_box2,
    txt_bp_box3,
    txt_bp_box4,
    txt_bp_box5,
    txt_bp_box6,
    txt_bp_box7,
    txt_bp_box8
};
u8 txt_bp_tree1[] = {TXT_BP_TREE_1}; u8 txt_bp_tree2[] = {TXT_BP_TREE_2};
u8 txt_bp_tree3[] = {TXT_BP_TREE_3}; u8 txt_bp_tree4[] = {TXT_BP_TREE_4};
u8 *txt_bp_tree[] = {
    txt_bp_tree1,
    txt_bp_tree2,
    txt_bp_tree3,
    txt_bp_tree4
};

u8 txt_bp_pipe1[] = {TXT_BP_PIPE_1};u8 txt_bp_pipe2[] = {TXT_BP_PIPE_2};
u8 *txt_pipe[] = {
    txt_bp_pipe1,
    txt_bp_pipe2,
    txt_bp_pipe1,
};

u8 txt_bp_boss1[] = {TXT_BP_BOSS_1};u8 txt_bp_boss2[] = {TXT_BP_BOSS_2};u8 txt_bp_boss3[] = {TXT_BP_BOSS_3};u8 txt_bp_boss4[] = {TXT_BP_BOSS_4};
u8 *txt_bp_boss[] = {
    txt_bp_boss1,
    txt_bp_boss2,
    txt_bp_boss3,
    txt_bp_boss4,
};

//theme strings
u8 txt_theme_1[] = {TXT_THEME_GENERIC};u8 txt_theme_2[] = {TXT_THEME_SAND};u8 txt_theme_3[] = {TXT_THEME_RHR};
u8 txt_theme_4[] = {TXT_THEME_CAVE}; u8 txt_theme_5[] = {TXT_THEME_CASTLE};u8 txt_theme_6[] = {TXT_THEME_VIRTUAPLEX};
u8 txt_theme_7[] = {TXT_THEME_RETRO};

u8 txt_mat_grass[] = {TXT_MAT_GRASS};u8 txt_mat_bricks[] = {TXT_MAT_BRICK};u8 txt_mat_stone[] = {TXT_MAT_STONE};u8 txt_mat_wood[] = {TXT_MAT_WOOD};u8 txt_mat_tiles[] = {TXT_MAT_TILES};u8 txt_mat_lava[] = {TXT_MAT_LAVA};
u8 txt_mat_sand[] = {TXT_MAT_SAND};u8 txt_mat_snow[] = {TXT_MAT_SNOW};u8 txt_mat_quicksand[] = {TXT_MAT_QUICKSAND};u8 txt_mat_roof[] = {TXT_MAT_ROOF};
u8 txt_mat_tiles2[] = {TXT_MAT_TILES2};u8 txt_mat_block[] = {TXT_MAT_BLOCK};
u8 txt_mat_basalt[] = {TXT_MAT_BASALT};u8 txt_mat_pillar[] = {TXT_MAT_PILLAR};u8 txt_mat_mesh[] = {TXT_MAT_MESH};
u8 txt_mat_mazewall[] = {TXT_MAT_MAZEWALL};u8 txt_mat_mazefloor[] = {TXT_MAT_MAZEFLOOR};u8 txt_mat_light[] = {TXT_MAT_LIGHT};u8 txt_mat_lakegrass[] = {TXT_MAT_LAKEGRASS};
u8 txt_mat_tileswood[] = {TXT_MAT_TILESWOOD};u8 txt_mat_tilesbricks[] = {TXT_MAT_TILESBRICKS};u8 txt_mat_tilesstone[] = {TXT_MAT_TILESSTONE};u8 txt_mat_carpet[] = {TXT_MAT_CARPET};u8 txt_mat_castlewall[] = {TXT_MAT_CASTLEWALL};u8 txt_mat_basementwall[] = {TXT_MAT_BASEMENTWALL};

u8 *cmm_theme_string_table[NUM_THEMES] = {
    &txt_theme_1,
    &txt_theme_2,
    &txt_theme_3,
    &txt_theme_4,
    &txt_theme_5,
    &txt_theme_6,
    &txt_theme_7,
};

struct cmm_theme cmm_theme_table[NUM_THEMES] = {
    // GENERIC
    {{
        {&mat_maker_MakerDirt, &mat_maker_MakerGrassSide_layer1, &mat_maker_MakerGrass, &txt_mat_grass,0},
        {&mat_maker_MakerBricks, NULL, NULL, &txt_mat_bricks,0},
        {&mat_maker_MakerStone, NULL, &mat_maker_MakerStoneSide, &txt_mat_stone,0},
        {&mat_maker_MakerTileBricks, NULL, &mat_maker_MakerTiles, &txt_mat_tiles,0}, // tiles
        {&mat_maker_MakerRoof, NULL, NULL, &txt_mat_roof,0}, // roof
        {&mat_maker_MakerWood, NULL, NULL, &txt_mat_wood,0},
        {&mat_maker_MakerSandDirt, &mat_maker_MakerDGrassSide_layer1, &mat_maker_MakerDGrass, &txt_mat_sand,0}, // sand
        {&mat_maker_MakerSnowDirt, &mat_maker_MakerSnowSide_layer1, &mat_maker_MakerSnow, &txt_mat_snow,0}, // snow
        {&mat_maker_MakerLava, NULL, NULL, &txt_mat_lava,0},
        {&mat_maker_MakerQuicksand, NULL, NULL, &txt_mat_quicksand,0}, // quicksand
    }},
    // DESERT
    {{
        {&mat_maker_MakerSandDirt, &mat_maker_MakerDGrassSide_layer1, &mat_maker_MakerDGrass, &txt_mat_sand,0},
        {&mat_maker_MakerDBrick, NULL, NULL, &txt_mat_bricks,0},
        {&mat_maker_MakerDStone, NULL, NULL, &txt_mat_stone,0},
        {&mat_maker_MakerDTiles, NULL, NULL, &txt_mat_tiles,0},
        {&mat_maker_MakerDStoneBlock, NULL, NULL, &txt_mat_block,0},
        {&mat_maker_MakerWood, NULL, NULL, &txt_mat_wood,0},
        {&mat_maker_MakerDBrick, NULL, mat_maker_MakerDWood, &txt_mat_tiles2,0},
        {&mat_maker_MakerDirt, &mat_maker_MakerGrassSide_layer1, &mat_maker_MakerGrass, &txt_mat_grass,0},
        {&mat_maker_MakerLava, NULL, NULL, &txt_mat_lava,0},
        {&mat_maker_MakerQuicksand, NULL, NULL, &txt_mat_quicksand,0},
    }},
    // LAVA
    {{
        {&mat_maker_MakerRHRStone, NULL, &mat_maker_MakerRHRObsidian, &txt_mat_stone,0},
        {&mat_maker_MakerRHRBrick, NULL, &mat_maker_MakerRHRObsidian, &txt_mat_bricks,0},
        {&mat_maker_MakerRHRBasalt, NULL, NULL, &txt_mat_basalt,0},
        {&mat_maker_MakerRHRTiles, NULL, NULL, &txt_mat_tiles,0},
        {&mat_maker_MakerRHRPattern, NULL, NULL, &txt_mat_block,0},
        {&mat_maker_MakerRHRWood, NULL, NULL, &txt_mat_wood,0},
        {&mat_maker_MakerRHRPillar, NULL, &mat_maker_MakerRHRTiles, &txt_mat_pillar,0},
        {&mat_maker_MakerRHRGrate_layer1, NULL, NULL, &txt_mat_mesh,1},
        {&mat_maker_MakerLava, NULL, NULL, &txt_mat_lava,0},
        {&mat_maker_MakerQuicksand, NULL, NULL, &txt_mat_quicksand,0},
    }},
    // CAVE
    {{
        {&mat_maker_MakerHDirt, mat_maker_MakerHGrassSide_layer1, &mat_maker_MakerHGrass, &txt_mat_grass,0},
        {&mat_maker_MakerHBrick, NULL, NULL, &txt_mat_bricks,0},
        {&mat_maker_MakerHStone2, NULL, NULL, &txt_mat_stone,0},
        {&mat_maker_MakerHStone4, NULL, NULL, &txt_mat_mazewall,0},
        {&mat_maker_MakerHStone, NULL, NULL, &txt_mat_mazefloor,0},
        {&mat_maker_MakerHCloud, NULL, NULL, &txt_mat_light,0}, // Light
        {&mat_maker_MakerHStone3, mat_maker_MakerHGrassSide_layer1, &mat_maker_MakerHGrass, &txt_mat_lakegrass,0}, // tiles?
        {&mat_maker_MakerHFence_layer1, NULL, NULL, &txt_mat_mesh,1}, // Mesh
        {&mat_maker_MakerLava, NULL, NULL, &txt_mat_lava,0},
        {&mat_maker_MakerQuicksand, NULL, NULL, &txt_mat_quicksand,0}, // Quicksand
    }},
    // CASTLE
    {{
        {&mat_maker_MakerCWood, NULL, &mat_maker_MakerCTile, &txt_mat_tileswood,0}, // hexagons on line
        {&mat_maker_MakerCBrick, NULL, &mat_maker_MakerCTile, &txt_mat_tilesbricks,0}, // bricks
        {&mat_maker_MakerCStoneSide, NULL, &mat_maker_MakerCStone, &txt_mat_tilesstone,0}, // hexagons on line
        {&mat_maker_MakerCWood, NULL, &mat_maker_MakerCCarpet, &txt_mat_carpet,0}, // carpet
        {&mat_maker_MakerCRoof, NULL, NULL, &txt_mat_roof,0},
        {&mat_maker_MakerCWall, NULL, NULL, &txt_mat_castlewall,0},
        {&mat_maker_MakerCPillar, NULL, &mat_maker_MakerCStone, &txt_mat_pillar,0},
        {&mat_maker_MakerCBasementWall, NULL, NULL, &txt_mat_basementwall,0},
        {&mat_maker_MakerLava, NULL, NULL, &txt_mat_lava,0},
        {&mat_maker_MakerQuicksand, NULL, NULL, &txt_mat_quicksand,0},
    }},
    // VIRTUAPLEX
    {{
        {&mat_maker_MakerVirtuaplex, NULL, NULL, &txt_mat_grass,0},
        {&mat_maker_Maker4Stone, NULL, NULL, &txt_mat_grass,0},
        {&mat_maker_MakerStone, NULL, NULL, &txt_mat_grass,0},
        {&mat_maker_MakerCaution, NULL, NULL, &txt_mat_grass,0},
        {&mat_maker_MakerScreen, NULL, NULL, &txt_mat_grass,0},
        {&mat_maker_MakerVoid, NULL, NULL, &txt_mat_grass,0},
        {&mat_maker_MakerLava, NULL, NULL, &txt_mat_lava,0},
        {&mat_maker_MakerLava, NULL, NULL, &txt_mat_lava,0},
        {&mat_maker_MakerLava, NULL, NULL, &txt_mat_lava,0},
        {&mat_maker_MakerLava, NULL, NULL, &txt_mat_lava,0},
    }},
    // RETRO
    {{
        {&mat_maker_MakerRetroGround, NULL, NULL, &txt_mat_grass,0},
        {&mat_maker_MakerRetroBrick, NULL, NULL, &txt_mat_grass,0},
        {&mat_maker_MakerRetroStone, NULL, NULL, &txt_mat_grass,0},
        {&mat_maker_MakerRetroBlock, NULL, NULL, &txt_mat_grass,0},
        {&mat_maker_MakerRetroCloud, NULL, NULL, &txt_mat_grass,0},
        {&mat_maker_MakerRetroLava, NULL, NULL, &txt_mat_grass,0},
        {&mat_maker_MakerLava, NULL, NULL, &txt_mat_lava,0},
        {&mat_maker_MakerLava, NULL, NULL, &txt_mat_lava,0},
        {&mat_maker_MakerLava, NULL, NULL, &txt_mat_lava,0},
        {&mat_maker_MakerLava, NULL, NULL, &txt_mat_lava,0},
    }},
};

#define MATERIAL(id) (cmm_theme_table[cmm_lopt_theme].mats[id])

//LEVEL SETTINGS INDEX
u8 cmm_lopt_costume = 0;
u8 cmm_lopt_seq = 0;
u8 cmm_lopt_envfx = 0;
u8 cmm_lopt_theme = 0;
u8 cmm_lopt_bg = 0;
u8 cmm_lopt_plane = 0;
u8 cmm_lopt_game = 0;//0 = BTCM, 1 = VANILLA

//UI
u8 cmm_menu_state = CMM_MAKE_MAIN;
s8 cmm_ui_index = 0;
u8 cmm_ui_bar[9] = {
    CMM_BUTTON_TERRAIN,
    CMM_BUTTON_FENCE,
    CMM_BUTTON_SLOPE,
    CMM_BUTTON_COIN,
    CMM_BUTTON_GOOMBA,
    CMM_BUTTON_STAR,
    CMM_BUTTON_PLAY,
    CMM_BUTTON_SETTINGS,
    CMM_BUTTON_SAVE,
};
s8 cmm_toolbox_index = 0;
//9x5 = 45 assets
u8 cmm_toolbox[45];
//Different toolboxes for different game styles
u8 cmm_toolbox_btcm[45] = {
    /*Tiles    */ CMM_BUTTON_TERRAIN, CMM_BUTTON_FENCE, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK,
    /*Tiles 2  */ CMM_BUTTON_SLOPE,CMM_BUTTON_CORNER,CMM_BUTTON_ICORNER,CMM_BUTTON_DSLOPE,CMM_BUTTON_SSLOPE,CMM_BUTTON_CULL, CMM_BUTTON_TROLL, CMM_BUTTON_WATER, CMM_BUTTON_BLANK,
    /*Items    */ CMM_BUTTON_STAR, CMM_BUTTON_RCS, CMM_BUTTON_COIN,CMM_BUTTON_GCOIN,CMM_BUTTON_RCOIN,CMM_BUTTON_BCOIN,CMM_BUTTON_BCS,CMM_BUTTON_BADGE,CMM_BUTTON_BLANK,
    /*Enemies  */ CMM_BUTTON_GOOMBA,CMM_BUTTON_REX,CMM_BUTTON_PODOBOO,CMM_BUTTON_BULLY,CMM_BUTTON_BOMB,CMM_BUTTON_CHUCKYA,CMM_BUTTON_PHANTASM,CMM_BUTTON_BLANK,CMM_BUTTON_BLANK,
    /*Obstacles*/ CMM_BUTTON_NOTEBLOCK,CMM_BUTTON_TREE,CMM_BUTTON_EXCLA,CMM_BUTTON_PIPE,CMM_BUTTON_MPLAT,CMM_BUTTON_SPAWN, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK,
};
u8 cmm_toolbox_vanilla[45] = {
    /*Tiles    */ CMM_BUTTON_TERRAIN, CMM_BUTTON_FENCE, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK,
    /*Tiles 2  */ CMM_BUTTON_SLOPE,CMM_BUTTON_CORNER,CMM_BUTTON_ICORNER,CMM_BUTTON_DSLOPE, CMM_BUTTON_SSLOPE, CMM_BUTTON_CULL, CMM_BUTTON_TROLL, CMM_BUTTON_WATER, CMM_BUTTON_BLANK,
    /*Items    */ CMM_BUTTON_STAR, CMM_BUTTON_RCS, CMM_BUTTON_COIN,CMM_BUTTON_RCOIN,CMM_BUTTON_BCOIN,CMM_BUTTON_BCS,CMM_BUTTON_KTQ,CMM_BUTTON_BLANK,CMM_BUTTON_BLANK,
    /*Enemies  */ CMM_BUTTON_GOOMBA,CMM_BUTTON_BULLY,CMM_BUTTON_BOMB,CMM_BUTTON_CHUCKYA,CMM_BUTTON_BBALL,CMM_BUTTON_BOSS,CMM_BUTTON_BLANK,CMM_BUTTON_BLANK,CMM_BUTTON_BLANK,
    /*Obstacles*/ CMM_BUTTON_TREE,CMM_BUTTON_PIPE,CMM_BUTTON_MPLAT,CMM_BUTTON_SPAWN,CMM_BUTTON_BLANK,CMM_BUTTON_BLANK,CMM_BUTTON_BLANK, CMM_BUTTON_BLANK, CMM_BUTTON_BLANK,
};
u8 cmm_ui_do_render = TRUE;
u8 cmm_do_save = FALSE;

struct cmm_hack_save cmm_save;

//button strings. is there a better way to do this?
u8 txt_btn_1[] = {TXT_BTN_1};u8 txt_btn_2[] = {TXT_BTN_2};u8 txt_btn_3[] = {TXT_BTN_3};u8 txt_btn_4[] = {TXT_BTN_4};u8 txt_btn_5[] = {TXT_BTN_5};
u8 txt_btn_6[] = {TXT_BTN_6};u8 txt_btn_7[] = {TXT_BTN_7};u8 txt_btn_8[] = {TXT_BTN_8};u8 txt_btn_9[] = {TXT_BTN_9};u8 txt_btn_10[] = {TXT_BTN_10};
u8 txt_btn_11[] = {TXT_BTN_11};u8 txt_btn_12[] = {TXT_BTN_12};u8 txt_btn_13[] = {TXT_BTN_13};u8 txt_btn_14[] = {TXT_BTN_14};u8 txt_btn_15[] = {TXT_BTN_15};
u8 txt_btn_16[] = {TXT_BTN_16};u8 txt_btn_17[] = {TXT_BTN_17};u8 txt_btn_18[] = {TXT_BTN_18};u8 txt_btn_19[] = {TXT_BTN_19};u8 txt_btn_20[] = {TXT_BTN_20};
u8 txt_btn_21[] = {TXT_BTN_21};u8 txt_btn_22[] = {TXT_BTN_22};u8 txt_btn_23[] = {TXT_BTN_23};u8 txt_btn_24[] = {TXT_BTN_24};u8 txt_btn_25[] = {TXT_BTN_25};
u8 txt_btn_26[] = {TXT_BTN_26};u8 txt_btn_27[] = {TXT_BTN_27};u8 txt_btn_28[] = {TXT_BTN_28};u8 txt_btn_29[] = {TXT_BTN_29};u8 txt_btn_30[] = {TXT_BTN_30};
u8 txt_btn_31[] = {TXT_BTN_31};u8 txt_btn_32[] = {TXT_BTN_32};u8 txt_btn_33[] = {TXT_BTN_33};u8 txt_btn_34[] = {TXT_BTN_34};u8 txt_btn_35[] = {TXT_BTN_35};
u8 txt_btn_36[] = {TXT_BTN_36};u8 txt_btn_37[] = {TXT_BTN_37};u8 txt_btn_38[] = {TXT_BTN_38};u8 txt_btn_39[] = {TXT_BTN_39};u8 txt_btn_40[] = {TXT_BTN_40};
u8 txt_btn_41[] = {TXT_BTN_41};u8 txt_btn_42[] = {TXT_BTN_42};u8 txt_btn_43[] = {TXT_BTN_43};

struct cmm_ui_button_type cmm_ui_buttons[] = {
    //button texture      //TILE/OBJ ID       //PLACE MODE //TXT POINTER   //PARAM STR
    {&mat_b_btn_save     , 0                  ,0           , &txt_btn_1    , NULL         }, //CMM_BUTTON_SAVE
    {&mat_b_btn_settings , 0                  ,0           , &txt_btn_2    , NULL         }, //CMM_BUTTON_SETTINGS
    {&mat_b_btn_check    , 0                  ,0           , &txt_btn_3    , NULL         }, //CMM_BUTTON_PLAY
    {&mat_b_btn_grass    , TILE_TYPE_BLOCK    ,CMM_PM_TILE , &txt_btn_4    , NULL         }, //CMM_BUTTON_GRASS
    {&mat_b_btn_slope    , TILE_TYPE_SLOPE    ,CMM_PM_TILE , &txt_btn_7    , NULL         }, //CMM_BUTTON_SLOPE
    {&mat_b_btn_troll    , TILE_TYPE_TROLL    ,CMM_PM_TILE , &txt_btn_8    , NULL         }, //CMM_BUTTON_TROLL
    {&mat_b_btn_star     , OBJECT_TYPE_STAR   ,CMM_PM_OBJ  , &txt_btn_9    , NULL         }, //CMM_BUTTON_STAR
    {&mat_b_btn_goomba   , OBJECT_TYPE_GOOMBA ,CMM_PM_OBJ  , &txt_btn_10   , NULL         }, //CMM_BUTTON_GOOMBA
    {&mat_b_btn_coin     , OBJECT_TYPE_COIN   ,CMM_PM_OBJ  , &txt_btn_11   , NULL         }, //CMM_BUTTON_COIN
    {&mat_b_btn_blank    , TILE_TYPE_BLOCK    ,CMM_PM_TILE , &txt_btn_12   , NULL         }, //CMM_BUTTON_BLANK
    {&mat_b_btn_greencoin, OBJECT_TYPE_GCOIN  ,CMM_PM_OBJ  , &txt_btn_15   , NULL         }, //CMM_BUTTON_GCOIN
    {&mat_b_btn_corner   , TILE_TYPE_CORNER   ,CMM_PM_TILE , &txt_btn_16   , NULL         }, //CMM_BUTTON_CORNER
    {&mat_b_btn_icorner  , TILE_TYPE_ICORNER  ,CMM_PM_TILE , &txt_btn_17   , NULL         }, //CMM_BUTTON_ICORNER
    {&mat_b_btn_redcoin  , OBJECT_TYPE_RCOIN  ,CMM_PM_OBJ  , &txt_btn_18   , NULL         }, //CMM_BUTTON_RCOIN
    {&mat_b_btn_bluecoin , OBJECT_TYPE_BCOIN  ,CMM_PM_OBJ  , &txt_btn_19   , NULL         }, //CMM_BUTTON_BCOIN
    {&mat_b_btn_bcs      , OBJECT_TYPE_BCS    ,CMM_PM_OBJ  , &txt_btn_20   , NULL         }, //CMM_BUTTON_BCS
    {&mat_b_btn_rcs      , OBJECT_TYPE_RCS    ,CMM_PM_OBJ  , &txt_btn_21   , NULL         }, //CMM_BUTTON_RCS
    {&mat_b_btn_noteblock, OBJECT_TYPE_NOTE   ,CMM_PM_OBJ  , &txt_btn_22   , NULL         }, //CMM_BUTTON_NOTEBLOCK
    {&mat_b_btn_cull     , TILE_TYPE_CULL     ,CMM_PM_TILE , &txt_btn_23   , NULL         }, //CMM_BUTTON_CULL
    {&mat_b_btn_podoboo  , OBJECT_TYPE_PODOB  ,CMM_PM_OBJ  , &txt_btn_25   , NULL         }, //CMM_BUTTON_PODOBOO
    {&mat_b_btn_rex      , OBJECT_TYPE_REX    ,CMM_PM_OBJ  , &txt_btn_26   , NULL         }, //CMM_BUTTON_REX
    {&mat_b_btn_bully    , OBJECT_TYPE_BULLY  ,CMM_PM_OBJ  , &txt_btn_27   , NULL         }, //CMM_BUTTON_BULLY
    {&mat_b_btn_bobomb   , OBJECT_TYPE_BOMB   ,CMM_PM_OBJ  , &txt_btn_28   , NULL         }, //CMM_BUTTON_BOMB
    {&mat_b_btn_tree     , OBJECT_TYPE_TREE   ,CMM_PM_OBJ  , &txt_btn_29   , txt_bp_tree  }, //CMM_BUTTON_TREE
    {&mat_b_btn_excla    , OBJECT_TYPE_EXCLA  ,CMM_PM_OBJ  , &txt_btn_30   , txt_bp_box   }, //CMM_BUTTON_EXCLA
    {&mat_b_btn_downslope, TILE_TYPE_DSLOPE   ,CMM_PM_TILE , &txt_btn_31   , NULL         }, //CMM_BUTTON_DSLOPE
    {&mat_b_btn_chuckya  , OBJECT_TYPE_CHUCKYA,CMM_PM_OBJ  , &txt_btn_32   , NULL         }, //CMM_BUTTON_CHUCKYA
    {&mat_b_btn_spawn    , OBJECT_TYPE_SPAWN  ,CMM_PM_OBJ  , &txt_btn_33   , NULL         }, //CMM_BUTTON_SPAWN
    {&mat_b_btn_phantasm , OBJECT_TYPE_PHNTSM ,CMM_PM_OBJ  , &txt_btn_34   , NULL         }, //CMM_BUTTON_PHANTASM
    {&mat_b_btn_pipe     , OBJECT_TYPE_PIPE   ,CMM_PM_OBJ  , &txt_btn_35   , txt_pipe     }, //CMM_BUTTON_PIPE
    {&mat_b_btn_badge    , OBJECT_TYPE_BADGE  ,CMM_PM_OBJ  , &txt_btn_36   , badgenames   }, //CMM_BUTTON_BADGE
    {&mat_b_btn_water    , TILE_TYPE_WATER    ,CMM_PM_TILE , &txt_btn_37   , NULL         }, //CMM_BUTTON_WATER
    {&mat_b_btn_fence    , TILE_TYPE_FENCE    ,CMM_PM_TILE , &txt_btn_38   , NULL         }, //CMM_BUTTON_FENCE
    {&mat_b_btn_boss     , OBJECT_TYPE_BOSS   ,CMM_PM_OBJ  , &txt_btn_39   , txt_bp_boss  }, //CMM_BUTTON_BOSS
    {&mat_b_btn_checker  , OBJECT_TYPE_MPLAT  ,CMM_PM_OBJ  , &txt_btn_40   , NULL         }, //CMM_BUTTON_MPLAT
    {&mat_b_btn_bball    , OBJECT_TYPE_BBALL  ,CMM_PM_OBJ  , &txt_btn_41   , NULL         }, //CMM_BUTTON_BBALL
    {&mat_b_btn_kuppa    , OBJECT_TYPE_KTQ    ,CMM_PM_OBJ  , &txt_btn_42   , NULL         }, //CMM_BUTTON_KTQ
    {&mat_b_btn_sideslope, TILE_TYPE_SSLOPE   ,CMM_PM_TILE , &txt_btn_43   , NULL         }, //CMM_BUTTON_SSLOPE
};

u8 txt_ls_costume[] = {TXT_LS_COSTUME};
u8 txt_ls_music[] = {TXT_LS_MUSIC};
u8 txt_ls_envfx[] = {TXT_LS_ENVFX};
u8 txt_ls_theme[] = {TXT_LS_THEME};
u8 txt_ls_bg[] = {TXT_LS_BG};
u8 txt_ls_plane[] = {TXT_LS_PLANE};

struct cmm_settings_button cmm_settings_buttons[] = {
    {&txt_ls_costume, &cmm_lopt_costume, &costume_text, 15},
    {&txt_ls_music, &cmm_lopt_seq, &musicmenu_titles, 29},
    {&txt_ls_envfx, &cmm_lopt_envfx, &cmm_envfx_string_table, 6},
    {&txt_ls_theme, &cmm_lopt_theme, &cmm_theme_string_table, NUM_THEMES},
    {&txt_ls_bg, &cmm_lopt_bg, &cmm_bg_string_table, 8},
    {&txt_ls_plane, &cmm_lopt_plane, &cmm_plane_string_table, 3},
};

#define SETTINGS_SIZE sizeof(cmm_settings_buttons)/sizeof(cmm_settings_buttons[0])

u8 cmm_settings_index = 0;
u8 cmm_settings_index_changed = FALSE;

void reset_play_state(void) {
    cmm_play_stars = 0;
    cmm_play_stars_bitfield = 0;
    cmm_play_badge_bitfield = 0;
}

u32 coords_in_range(s32 x, s32 y, s32 z) {
    if (x < 0 || x > 31) return FALSE;
    if (y < 0 || y > 31) return FALSE;
    if (z < 0 || z > 31) return FALSE;
    return TRUE;
}

s32 tile_sanity_check(void) {
    u8 allow = TRUE;

    if (cmm_tile_count >= 2000) {
        allow = FALSE;
    }
    if (cmm_vtx_total >= 24970) {
        allow = FALSE;
    }
    if (cmm_mtx_total >= 4970) {
        allow = FALSE;
    }
    if (cmm_gfx_total >= 22970) {
        allow = FALSE;
    }
    if (cmm_gfx_tp_total >= 7970) {
        allow = FALSE;
    }

    if (!allow) {
        //error sound
        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
    }
    return allow;
}

s32 object_sanity_check(void) {
    u8 allow = TRUE;

    if (cmm_object_count >= 200) {
        allow = FALSE;
    }

    if (!allow) {
        //error sound
        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
    }
    return allow;
}

void place_terrain_data(s32 x, s32 y, s32 z, u32 type, u32 rot, u32 mat) {
    cmm_grid_data[x][y][z].rot = rot;
    cmm_grid_data[x][y][z].type = type + 1;
    cmm_grid_data[x][y][z].mat = mat;
}

void remove_terrain_data(s32 x, s32 y, s32 z) {
    cmm_grid_data[x][y][z].rot = 0;
    cmm_grid_data[x][y][z].type = 0;
    cmm_grid_data[x][y][z].mat = 0;
}

u32 get_faceshape(s32 x, s32 y, s32 z, u32 dir) {
    u8 tileType = cmm_grid_data[x][y][z].type;
    if (tileType == 0) return CMM_FACESHAPE_EMPTY; // no tile

    u8 rot = cmm_grid_data[x][y][z].rot;
    dir = ROTATE_DIRECTION(dir,((4-rot) % 4)) ^ 1;

    struct cmm_terrain_block *terrain = cmm_tile_types[tileType - 1].terrain;
    for (u32 i = 0; i < terrain->numQuads; i++) {
        struct cmm_terrain_quad *quad = &terrain->quads[i];
        if (quad->cullDir == dir) {
            return quad->faceshape;
        }
    }
    for (u32 i = 0; i < terrain->numTris; i++) {
        struct cmm_terrain_tri *tri = &terrain->tris[i];
        if (tri->cullDir == dir) {
            return tri->faceshape;
        }
    }
    return CMM_FACESHAPE_EMPTY;
}

void place_occupy_data(s32 x, s32 y, s32 z) {
    cmm_grid_data[x][y][z].occupied = TRUE;
}

void remove_occupy_data(s32 x, s32 y, s32 z) {
    cmm_grid_data[x][y][z].occupied = FALSE;
}

u32 get_occupy_data(s32 x, s32 y, s32 z) {
    if (!coords_in_range(x, y, z)) return FALSE;
    return cmm_grid_data[x][y][z].occupied;
}

s8 cullOffsetLUT[6][3] = {
    {0, 1, 0},
    {0, -1, 0},
    {1, 0, 0},
    {-1, 0, 0},
    {0, 0, 1},
    {0, 0, -1},
};

u32 should_cull(s8 pos[3], u32 direction, u32 faceshape, u32 rot) {
    if (direction == CMM_NO_CULLING) return FALSE;
    direction = ROTATE_DIRECTION(direction, rot);

    s8 newpos[3];
    vec3_sum(newpos, pos, cullOffsetLUT[direction]);
    if (!coords_in_range(newpos[0], newpos[1], newpos[2])) return FALSE;

    u8 otherMat = cmm_grid_data[newpos[0]][newpos[1]][newpos[2]].mat;
    if (MATERIAL(otherMat).type != 0) {
        u8 curMat = cmm_grid_data[pos[0]][pos[1]][pos[2]].mat;
        if (curMat != otherMat) return FALSE;
    }

    u32 otherFaceshape = get_faceshape(
        newpos[0],
        newpos[1],
        newpos[2],
        direction);

    if (otherFaceshape == CMM_FACESHAPE_EMPTY) return FALSE;
    if (otherFaceshape == CMM_FACESHAPE_FULL) return TRUE;
    if (faceshape == CMM_FACESHAPE_FULL) return FALSE;
    if (faceshape == CMM_FACESHAPE_TOPTRI) {
        if (otherFaceshape == CMM_FACESHAPE_TOPTRI) {
            u8 otherrot = cmm_grid_data[newpos[0]][newpos[1]][newpos[2]].rot;
            return (otherrot == rot);
        } else return FALSE;
    }
    return (faceshape == (otherFaceshape^1));
}

u32 should_render_grass_side(s8 pos[3], u32 direction, u32 faceshape, u32 rot, u32 grassType) {
    if (should_cull(pos, direction, faceshape, rot)) return FALSE;
    if (!coords_in_range(pos[0], pos[1]+1, pos[2])) return TRUE;
    u8 topFaceshape;
    switch (grassType) {
        case CMM_GROWTH_UNDERSLOPE:
            direction = CMM_DIRECTION_POS_Z;
            // fallthrough
        case CMM_GROWTH_NORMAL_SIDE:
            topFaceshape = get_faceshape(pos[0], pos[1]+1, pos[2], ROTATE_DIRECTION(direction, rot)^1);
            switch (topFaceshape) {
                case CMM_FACESHAPE_FULL:
                case CMM_FACESHAPE_TRI_1:
                case CMM_FACESHAPE_TRI_2:
                    return FALSE;
            }
            return TRUE;
        case CMM_GROWTH_UNCONDITIONAL_SIDE:
            return TRUE;
        case CMM_GROWTH_DIAGONAL_SIDE:
            topFaceshape = get_faceshape(pos[0], pos[1]+1, pos[2], CMM_DIRECTION_UP);
            if (topFaceshape == CMM_FACESHAPE_FULL) return FALSE;
            if (topFaceshape != CMM_FACESHAPE_TOPTRI) return TRUE;
            u8 otherrot = cmm_grid_data[pos[0]][pos[1]+1][pos[2]].rot;
            return (otherrot != rot);
    }
    return FALSE;
}


s32 handle_wait_vblank(OSMesgQueue *mq) {
    // returns true if it lasts longer than 3 seconds (3 * 1000us * 1000ms)
    OSMesg msg;
    OSTimer timer;
    osSetTimer(&timer, OS_USEC_TO_CYCLES(3000000), 0, mq, (OSMesg)(111*3*2));
    osRecvMesg(mq, &msg, OS_MESG_BLOCK);
    osStopTimer(&timer);

    return msg == (OSMesg)(111*3*2);
}

void generate_path_gfx(void) {
    u16 gfx_index = 0;
    u16 vtx_index = 0;

    gSPDisplayList(&cmm_trajectory_gfx[gfx_index++], mat_maker_MakerLineMat);

    for (u8 i=1;i<cmm_trajectory_edit_index;i++) {
        make_vertex(cmm_trajectory_vtx, vtx_index+0, ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)+1])+0), ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)+2])+20), ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)+3])), -16, 1008, 0x0, 0x7F, 0x0, 0xFF);
        make_vertex(cmm_trajectory_vtx, vtx_index+1, ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)+1])+20), ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)+2])+0), ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)+3])), 1008, 1008, 0x0, 0x7F, 0x0, 0xFF);
        make_vertex(cmm_trajectory_vtx, vtx_index+2, ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)-3])+0), ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)-2])+20), ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)-1])), 1008, -16, 0x0, 0x7F, 0x0, 0xFF);
        make_vertex(cmm_trajectory_vtx, vtx_index+3, ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)-3])-20), ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)-2])+0), ((cmm_trajectory_list[cmm_trajectory_to_edit][(i*4)-1])), -16, -16, 0x0, 0x7F, 0x0, 0xFF);

        gSPVertex(&cmm_trajectory_gfx[gfx_index++], cmm_trajectory_vtx + vtx_index, 4, 0);
        gSP2Triangles(&cmm_trajectory_gfx[gfx_index++], 0, 1, 2, 0, 0, 2, 3, 0);
        vtx_index+=4;
    }

    gSPEndDisplayList(&cmm_trajectory_gfx[gfx_index]);
}

Vtx *cmm_curr_vtx;
Gfx *cmm_curr_gfx;
u16 cmm_vtx_index;
u16 cmm_gfx_index;


void cmm_transform_vtx_with_rot(s8 v[][3], s8 oldv[][3], u32 numVtx, u32 rot) {
    for (u32 i = 0; i < numVtx; i++) {
        s8 x = oldv[i][0];
        s8 z = oldv[i][2];
        switch (rot) {
            case 0: v[i][0] = x; v[i][2] = z; break;
            case 1: v[i][0] = z; v[i][2] = -x; break;
            case 2: v[i][0] = -x; v[i][2] = -z; break;
            case 3: v[i][0] = -z; v[i][2] = x; break;
        }
        v[i][1] = oldv[i][1];
    }
}

void render_get_normal_and_uvs(s8 v[3][3], u32 uvProjDir, u32 rot, u8 *uAxis, u8 *vAxis, s8 n[3]) {
    // Find normal
    Vec3f normal;
    find_vector_perpendicular_to_plane(normal, v[0], v[1], v[2]);
    vec3_normalize(normal);
    n[0] = normal[0] * 0x7F;
    n[1] = normal[1] * 0x7F;
    n[2] = normal[2] * 0x7F;
    // Find UVs
    if (rot & 1) uvProjDir = 2 - uvProjDir;
    switch (uvProjDir) {
        case 0: *uAxis = 2; *vAxis = 1; break;
        case 1: *uAxis = 2; *vAxis = 0; break;
        case 2: *uAxis = 0; *vAxis = 1; break;
    }
}

void render_quad(struct cmm_terrain_quad *quad, Gfx gfx[], s8 pos[3], u32 rot, u32 isDecal) {
    s8 n[3];
    u8 uAxis, vAxis;

    s8 newVtx[4][3];
    cmm_transform_vtx_with_rot(newVtx, quad->vtx, 4, rot);
    render_get_normal_and_uvs(newVtx, quad->uvProjDir, rot, &uAxis, &vAxis, n);

    for (u32 i = 0; i < 4; i++) {
        s16 u, v;
        if (isDecal && quad->decaluvs) {
            u = (*quad->decaluvs)[i][0];
            v = (*quad->decaluvs)[i][1];
        } else {
            u = newVtx[i][uAxis];
            v = newVtx[i][vAxis];
        }
        make_vertex(cmm_curr_vtx, cmm_vtx_index+i,
            (pos[0]*300)+newVtx[i][0]*150,
            (pos[1]*300)+newVtx[i][1]*150,
            (pos[2]*300)+newVtx[i][2]*150,
            u * -512 + 500, v * -512 + 500,
            n[0], n[1], n[2], 0xFF);
    }
    gSPVertex(&gfx[cmm_gfx_index++], cmm_curr_vtx + cmm_vtx_index, 4, 0);
    gSP2Triangles(&gfx[cmm_gfx_index++], 0, 1, 2, 0, 1, 3, 2, 0);
    cmm_vtx_index+=4;
}

void render_tri(struct cmm_terrain_tri *tri, Gfx gfx[], s8 pos[3], u32 rot, u32 isDecal) {
    s8 n[3];
    u8 uAxis, vAxis;

    s8 newVtx[3][3];
    cmm_transform_vtx_with_rot(newVtx, tri->vtx, 3, rot);
    render_get_normal_and_uvs(newVtx, tri->uvProjDir, rot, &uAxis, &vAxis, n);

    for (u32 i = 0; i < 3; i++) {
        s16 u, v;
        if (isDecal && tri->decaluvs) {
            u = (*tri->decaluvs)[i][0];
            v = (*tri->decaluvs)[i][1];
        } else {
            u = newVtx[i][uAxis];
            v = newVtx[i][vAxis];
        }
        make_vertex(cmm_curr_vtx, cmm_vtx_index+i,
            (pos[0]*300)+newVtx[i][0]*150,
            (pos[1]*300)+newVtx[i][1]*150,
            (pos[2]*300)+newVtx[i][2]*150,
            u * -512 + 500, v * -512 + 500,
            n[0], n[1], n[2], 0xFF);
    }
    gSPVertex(&gfx[cmm_gfx_index++], cmm_curr_vtx + cmm_vtx_index, 3, 0);
    gSP1Triangle(&gfx[cmm_gfx_index++], 0, 1, 2, 0);
    cmm_vtx_index+=3;
}

void render_block_main(s8 pos[3], u32 tileType, u32 mat, u32 rot) {
    struct cmm_terrain_block *terrain = cmm_tile_types[tileType].terrain;
    u8 hasTopside = (MATERIAL(mat).top != NULL);
    for (u32 j = 0; j < terrain->numQuads; j++) {
        struct cmm_terrain_quad *quad = &terrain->quads[j];
        if (!should_cull(pos, quad->cullDir, quad->faceshape, rot)) {
            if (!hasTopside || (quad->growthType != CMM_GROWTH_FULL)) {
                render_quad(quad, cmm_curr_gfx, pos, rot, FALSE);
            }
        }
    }
    for (u32 j = 0; j < terrain->numTris; j++) {
        struct cmm_terrain_tri *tri = &terrain->tris[j];
        if (!should_cull(pos, tri->cullDir, tri->faceshape, rot)) {
            if (!hasTopside || (tri->growthType != CMM_GROWTH_FULL)) {
                render_tri(tri, cmm_curr_gfx, pos, rot, FALSE);
            }
        }
    }
}

void render_block_grass_top(s8 pos[3], u32 tileType, u32 rot) {
    struct cmm_terrain_block *terrain = cmm_tile_types[tileType].terrain;
    for (u32 j = 0; j < terrain->numQuads; j++) {
        struct cmm_terrain_quad *quad = &terrain->quads[j];
        if (quad->growthType == CMM_GROWTH_FULL) {
            if (!should_cull(pos, quad->cullDir, quad->faceshape, rot)) {
                render_quad(quad, cmm_curr_gfx, pos, rot, FALSE);
            }
        }
    }
    
    for (u32 j = 0; j < terrain->numTris; j++) {
        struct cmm_terrain_tri *tri = &terrain->tris[j];
        if (tri->growthType == CMM_GROWTH_FULL) {
            if (!should_cull(pos, tri->cullDir, tri->faceshape, rot)) {
                render_tri(tri, cmm_curr_gfx, pos, rot, FALSE);
            }
        }
    }
}

void render_block_grass_side(s8 pos[3], u32 tileType, u32 rot) {
    struct cmm_terrain_block *terrain = cmm_tile_types[tileType].terrain;
    for (u32 j = 0; j < terrain->numQuads; j++) {
        struct cmm_terrain_quad *quad = &terrain->quads[j];
        if (quad->growthType != CMM_GROWTH_FULL && quad->growthType != CMM_GROWTH_NONE) {
            if (should_render_grass_side(pos, quad->cullDir, quad->faceshape, rot, quad->growthType)) {
                render_quad(quad, cmm_curr_gfx, pos, rot, TRUE);
            }
        }
    }

    for (u32 j = 0; j < terrain->numTris; j++) {
        struct cmm_terrain_tri *tri = &terrain->tris[j];
        if (tri->growthType != CMM_GROWTH_FULL && tri->growthType != CMM_GROWTH_NONE) {
            if (should_render_grass_side(pos, tri->cullDir, tri->faceshape, rot, tri->growthType)) {
                render_tri(tri, cmm_curr_gfx, pos, rot, TRUE);
            }
        }
    }
}

void generate_terrain_gfx(void) {
    u16 gfx_tdecal_index = 0;
    u16 gfx_tp_index = 0;
    u16 mtx_index = 0;

    while (sCurrentDisplaySPTask != NULL) {
        osRecvMesg(&gGameVblankQueue, &gMainReceivedMesg, OS_MESG_BLOCK);
    }

    cmm_curr_gfx = cmm_terrain_gfx;
    cmm_curr_vtx = cmm_terrain_vtx;
    cmm_vtx_index = 0;
    cmm_gfx_index = 0;

    //BOTTOM PLANE
    switch (cmm_lopt_plane) {
        case 1:
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], MATERIAL(TILE_MATERIAL_LAVA).gfx);
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], visualplane_visualplane_mesh);
        break;
        case 2:
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], MATERIAL(TILE_MATERIAL_GRASS).top);
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], visualplane_visualplane_mesh);
        break;
    }

    // Tiles with models
    for (u32 i = 0; i < cmm_tile_count; i++) {
        if (!cmm_tile_types[cmm_tile_data[i].type].terrain) {
            if ((cmm_target_mode == CMM_MODE_PLAY)&&(cmm_tile_data[i].type == TILE_TYPE_CULL)) {
                continue;
            }

            //has a model, so just print model
            guTranslate(&cmm_terrain_mtx[mtx_index], cmm_tile_data[i].x*300, cmm_tile_data[i].y*300, cmm_tile_data[i].z*300);
            mtx_index++;
            guRotate(&cmm_terrain_mtx[mtx_index],cmm_tile_data[i].rot*90.0f,0.0f,1.0f,0.0f);
            if (!cmm_tile_types[cmm_tile_data[i].type].transparent) {
                //opaque
                gSPMatrix(&cmm_curr_gfx[cmm_gfx_index++], VIRTUAL_TO_PHYSICAL(&cmm_terrain_mtx[mtx_index-1]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
                gSPMatrix(&cmm_curr_gfx[cmm_gfx_index++], VIRTUAL_TO_PHYSICAL(&cmm_terrain_mtx[mtx_index]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
                gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], cmm_tile_types[cmm_tile_data[i].type].model);
                gSPPopMatrix(&cmm_curr_gfx[cmm_gfx_index++], G_MTX_MODELVIEW);
            } else {
                //transparent
                gSPMatrix(&cmm_terrain_gfx_tp[gfx_tp_index++], VIRTUAL_TO_PHYSICAL(&cmm_terrain_mtx[mtx_index-1]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
                gSPMatrix(&cmm_terrain_gfx_tp[gfx_tp_index++], VIRTUAL_TO_PHYSICAL(&cmm_terrain_mtx[mtx_index]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
                gSPDisplayList(&cmm_terrain_gfx_tp[gfx_tp_index++], cmm_tile_types[cmm_tile_data[i].type].model);
                gSPPopMatrix(&cmm_terrain_gfx_tp[gfx_tp_index++], G_MTX_MODELVIEW);
            }
            mtx_index++;
        }
    }

    for (u32 mat = 0; mat < NUM_MATERIALS_PER_THEME; mat++) {
        u8 tileType, rot;
        s8 pos[3];
        gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], MATERIAL(mat).gfx);
        for (u32 i = 0; i < cmm_tile_count; i++) {
            if (cmm_tile_data[i].mat != mat || !cmm_tile_types[cmm_tile_data[i].type].terrain) continue;

            tileType = cmm_tile_data[i].type;
            rot = cmm_tile_data[i].rot;
            vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);

            render_block_main(pos, tileType, mat, rot);
        }
        // If it was a cutout material, set render mode back to opaque
        if (MATERIAL(mat).type == 1) {
            gDPSetRenderMode(&cmm_curr_gfx[cmm_gfx_index++], G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        }
        if (MATERIAL(mat).side) {
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], MATERIAL(mat).side);
            for (u32 i = 0; i < cmm_tile_count; i++) {
                if (cmm_tile_data[i].mat != mat || !cmm_tile_types[cmm_tile_data[i].type].terrain) continue;

                tileType = cmm_tile_data[i].type;
                rot = cmm_tile_data[i].rot;
                vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);

                render_block_grass_side(pos, tileType, rot);
            }
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], &mat_revert_maker_MakerGrassSide_layer1);
        }
        if (MATERIAL(mat).top) {
            gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], MATERIAL(mat).top);
            for (u32 i = 0; i < cmm_tile_count; i++) {
                if (cmm_tile_data[i].mat != mat || !cmm_tile_types[cmm_tile_data[i].type].terrain) continue;

                tileType = cmm_tile_data[i].type;
                rot = cmm_tile_data[i].rot;
                vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);

                render_block_grass_top(pos, tileType, rot);
            }
        }
    }

    //END OF ALL 3 DISPLAY LISTS
    gSPEndDisplayList(&cmm_terrain_gfx[cmm_gfx_index]);
    gSPEndDisplayList(&cmm_terrain_gfx_tp[gfx_tp_index]);

    //print_text_fmt_int(110, 56, "OPAQUE %d", gfx_index);
    //print_text_fmt_int(110, 76, "DECAL %d", gfx_tdecal_index);
    //print_text_fmt_int(110, 96, "TILES %d", cmm_tile_count);
    //print_text_fmt_int(110, 116, "TYPE %d", cmm_tile_data[cmm_tile_count-1].type);

    cmm_vtx_total = cmm_vtx_index;
    cmm_mtx_total = mtx_index;
    cmm_gfx_total = cmm_gfx_index;
    cmm_gfx_tp_total = gfx_tp_index;
};

Gfx preview_gfx[32];
Mtx preview_mtx[2];
Vtx preview_vtx[64];

Gfx *ccm_append(s32 callContext, UNUSED struct GraphNode *node, UNUSED Mat4 mtx) {

    if (callContext == GEO_CONTEXT_CREATE) {
        generate_terrain_gfx();
        generate_path_gfx();
    }
    if (callContext == GEO_CONTEXT_RENDER) {
        geo_append_display_list(cmm_terrain_gfx, LAYER_OPAQUE);
        geo_append_display_list(cmm_terrain_gfx_tp, LAYER_TRANSPARENT);

        if (cmm_menu_state == CMM_MAKE_TRAJECTORY) {
            geo_append_display_list(cmm_trajectory_gfx, LAYER_OPAQUE);
        }

        //this extra append is for the editor tile preview
        if ((cmm_mode == CMM_MODE_MAKE)&&(cmm_place_mode == CMM_PM_TILE)) {
            //generate dl
            u8 preview_mtx_index = 0;
            cmm_curr_gfx = preview_gfx;
            cmm_curr_vtx = preview_vtx;
            cmm_gfx_index = 0;
            cmm_vtx_index = 0;

            if (cmm_tile_types[cmm_id_selection].model) {
                guTranslate(&preview_mtx[preview_mtx_index], cmm_sbx*300, cmm_sby*300, cmm_sbz*300);
                preview_mtx_index++;
                guRotate(&preview_mtx[preview_mtx_index],90.0f*cmm_rot_selection,0.0f,1.0f,0.0f);
                gSPMatrix(&cmm_curr_gfx[cmm_gfx_index++], VIRTUAL_TO_PHYSICAL(&preview_mtx[preview_mtx_index-1]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
                gSPMatrix(&cmm_curr_gfx[cmm_gfx_index++], VIRTUAL_TO_PHYSICAL(&preview_mtx[preview_mtx_index]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
                //gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], MATERIAL(cmm_param_selection).gfx);
                gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], cmm_tile_types[cmm_id_selection].model);
                gSPPopMatrix(&cmm_curr_gfx[cmm_gfx_index++], G_MTX_MODELVIEW);
                preview_mtx_index++;
            } else {
                s8 pos[3];
                vec3_set(pos, cmm_sbx, cmm_sby, cmm_sbz);
                gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], MATERIAL(cmm_mat_selection).gfx);
                render_block_main(pos, cmm_id_selection, cmm_mat_selection, cmm_rot_selection);
                if (MATERIAL(cmm_mat_selection).top) {
                    if (MATERIAL(cmm_mat_selection).side) {
                        gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], MATERIAL(cmm_mat_selection).side);
                        render_block_grass_side(pos, cmm_id_selection, cmm_rot_selection);
                        gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], &mat_revert_maker_MakerGrassSide_layer1);
                    }
                    gSPDisplayList(&cmm_curr_gfx[cmm_gfx_index++], MATERIAL(cmm_mat_selection).top);
                    render_block_grass_top(pos, cmm_id_selection, cmm_rot_selection);
                }
            }

            gSPEndDisplayList(&cmm_curr_gfx[cmm_gfx_index]);

            if (!cmm_tile_types[cmm_id_selection].transparent) {
                geo_append_display_list(cmm_curr_gfx, LAYER_OPAQUE);
            } else {
                geo_append_display_list(cmm_curr_gfx, LAYER_TRANSPARENT);
            }
        }

    }
    return NULL;
}

// Create new static surface
extern struct Surface *alloc_surface(u32 dynamic);
extern void add_surface(struct Surface *surface, s32 dynamic);
void cmm_create_surface(TerrainData v1[3], TerrainData v2[3], TerrainData v3[3], TerrainData type) { 
    struct Surface *surface = alloc_surface(FALSE);

    Vec3f n;
    find_vector_perpendicular_to_plane(n, v1, v2, v3);
    if (!vec3f_normalize2(n)) return NULL;

    vec3_copy(surface->vertex1, v1);
    vec3_copy(surface->vertex2, v2);
    vec3_copy(surface->vertex3, v3);

    surface->normal.x = n[0];
    surface->normal.y = n[1];
    surface->normal.z = n[2];

    surface->originOffset = -vec3_dot(n, v1);

    s16 min,max;
    min_max_3s(v1[1], v2[1], v3[1], &min, &max);
    surface->lowerY = (min - SURFACE_VERTICAL_BUFFER);
    surface->upperY = (max + SURFACE_VERTICAL_BUFFER);

    surface->type = type;
    add_surface(surface, FALSE);
};

TerrainData floorVtxs[4][3] = {
    {-150, -150, 9450},
    {9450, -150, 9450},
    {-150, -150, -150},
    {9450, -150, -150},
};

extern TerrainData sVertexData[900];

TerrainData colVtxs[4][3];

void generate_terrain_collision(void) {
    s16 i;
    gCurrStaticSurfacePool = main_pool_alloc(main_pool_available() - 0x10, MEMORY_POOL_LEFT);
    gCurrStaticSurfacePoolEnd = gCurrStaticSurfacePool;
    gSurfaceNodesAllocated = gNumStaticSurfaceNodes;
    gSurfacesAllocated = gNumStaticSurfaces;
    //the first thing to do is to generate the plane... there's only 2 types so it's a hardcoded switchcase
    TerrainData floorType;
    switch(cmm_lopt_plane) {
        case 1:
        case 2:
            floorType = (cmm_lopt_plane == 2) ? SURFACE_DEFAULT : SURFACE_BURNING;
            cmm_create_surface(floorVtxs[0], floorVtxs[1], floorVtxs[2], floorType);
            cmm_create_surface(floorVtxs[1], floorVtxs[3], floorVtxs[2], floorType);
    }


    for (i=0; i<cmm_tile_count; i++) {
        struct cmm_terrain_block *terrain = cmm_tile_types[cmm_tile_data[i].type].terrain;
        if (terrain) {
            floorType = cmm_tile_data[i].mat == TILE_MATERIAL_LAVA ? SURFACE_BURNING : SURFACE_NOT_SLIPPERY;
            s8 pos[3];
            s8 newVtx[4][3];
            vec3_set(pos, cmm_tile_data[i].x, cmm_tile_data[i].y, cmm_tile_data[i].z);
            for (u32 j = 0; j < terrain->numQuads; j++) {
                struct cmm_terrain_quad *quad = &terrain->quads[j];
                if (!should_cull(pos, quad->cullDir, quad->faceshape, cmm_tile_data[i].rot)) {
                    cmm_transform_vtx_with_rot(newVtx, quad->vtx, 4, cmm_tile_data[i].rot);
                    for (u32 k = 0; k < 4; k++) {
                        colVtxs[k][0] = pos[0]*300 + newVtx[k][0]*150;
                        colVtxs[k][1] = pos[1]*300 + newVtx[k][1]*150;
                        colVtxs[k][2] = pos[2]*300 + newVtx[k][2]*150;
                    }
                    cmm_create_surface(colVtxs[0], colVtxs[1], colVtxs[2], floorType);
                    cmm_create_surface(colVtxs[1], colVtxs[3], colVtxs[2], floorType);
                }
            }
            for (u32 j = 0; j < terrain->numTris; j++) {
                struct cmm_terrain_tri *tri = &terrain->tris[j];
                if (!should_cull(pos, tri->cullDir, tri->faceshape, cmm_tile_data[i].rot)) {
                    cmm_transform_vtx_with_rot(newVtx, tri->vtx, 3, cmm_tile_data[i].rot);
                    for (u32 k = 0; k < 3; k++) {
                        colVtxs[k][0] = pos[0]*300 + newVtx[k][0]*150;
                        colVtxs[k][1] = pos[1]*300 + newVtx[k][1]*150;
                        colVtxs[k][2] = pos[2]*300 + newVtx[k][2]*150;
                    }
                    cmm_create_surface(colVtxs[0], colVtxs[1], colVtxs[2], floorType);
                }
            }
        } else if (cmm_tile_types[cmm_tile_data[i].type].collision_data) {
            Vec3f pos = {cmm_tile_data[i].x*300.0f, cmm_tile_data[i].y*300.0f, cmm_tile_data[i].z*300.0f};
            Vec3s rot = {0,cmm_tile_data[i].rot*0x4000,0};
            mtxf_rotate_zxy_and_translate(o->transform,pos,rot);

            //this code was written by accident... the collision doesn't generate properly without it though???
            o->oPosX = (cmm_tile_data[0].x*300.0f);
            o->oPosY = (cmm_tile_data[0].y*300.0f);
            o->oPosZ = (cmm_tile_data[0].z*300.0f);
            o->oFaceAngleYaw = (cmm_tile_data[i].rot*0x4000);
            
            TerrainData *collisionData = segmented_to_virtual(cmm_tile_types[cmm_tile_data[i].type].collision_data);
            collisionData++;
            transform_object_vertices(&collisionData, sVertexData);

            // TERRAIN_LOAD_CONTINUE acts as an "end" to the terrain data.
            while (*collisionData != TERRAIN_LOAD_CONTINUE) {
                load_object_surfaces(&collisionData, sVertexData, FALSE);
            }
        }
    }

    u32 surfacePoolData = (uintptr_t)gCurrStaticSurfacePoolEnd - (uintptr_t)gCurrStaticSurfacePool;
    gTotalStaticSurfaceData += surfacePoolData;
    main_pool_realloc(gCurrStaticSurfacePool, surfacePoolData);

    gNumStaticSurfaceNodes = gSurfaceNodesAllocated;
    gNumStaticSurfaces = gSurfacesAllocated;
}

void generate_object_preview(void) {
    struct Object *preview_object;
    u8 i;

    preview_object = cur_obj_nearest_object_with_behavior(bhvStaticObject);
    while(preview_object) {
        mark_obj_for_deletion(preview_object);
        preview_object = cur_obj_nearest_object_with_behavior(bhvStaticObject);
    }

    for(i=0;i<cmm_object_count;i++){
        preview_object = spawn_object(gMarioObject, cmm_object_types[cmm_object_data[i].type].model_id ,bhvStaticObject);
        preview_object->oPosX = cmm_object_data[i].x*300.0f;
        preview_object->oPosY = cmm_object_data[i].y*300.0f+cmm_object_types[cmm_object_data[i].type].y_offset;
        preview_object->oPosZ = cmm_object_data[i].z*300.0f;
        preview_object->oFaceAngleYaw = cmm_object_data[i].rot*0x4000;
        obj_scale(preview_object, cmm_object_types[cmm_object_data[i].type].scale);
        if (cmm_object_types[cmm_object_data[i].type].billboarded) {
            preview_object->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
        }
        if (cmm_object_types[cmm_object_data[i].type].anim) {
            preview_object->oAnimations = cmm_object_types[cmm_object_data[i].type].anim;
            super_cum_working(preview_object,0);
            preview_object->header.gfx.animInfo.animAccel = 0.0f;
        }
        if (cmm_object_types[cmm_object_data[i].type].disp_func) {
            (cmm_object_types[cmm_object_data[i].type].disp_func)(preview_object,cmm_object_data[i].param);
        }
    }
}

void generate_objects_to_level(void) {
    struct Object *obj;
    u8 i;
    cmm_play_stars_max = 0;
    for(i=0;i<cmm_object_count;i++){
        //obj = create_object(cmm_object_types[cmm_object_data[i].type].behavior);
        //obj->behavior = cmm_object_types[cmm_object_data[i].type].behavior;
        //obj->header.gfx.sharedChild = gLoadedGraphNodes[cmm_object_types[cmm_object_data[i].type].model_id];

        obj = spawn_object(gMarioObject, cmm_object_types[cmm_object_data[i].type].model_id , cmm_object_types[cmm_object_data[i].type].behavior);

        obj->oPosX = cmm_object_data[i].x*300.0f;
        obj->oPosY = cmm_object_data[i].y*300.0f+cmm_object_types[cmm_object_data[i].type].y_offset;
        obj->oPosZ = cmm_object_data[i].z*300.0f;
        obj->oFaceAngleYaw = cmm_object_data[i].rot*0x4000;
        obj->oMoveAngleYaw = cmm_object_data[i].rot*0x4000;
        obj->oBehParams2ndByte = cmm_object_data[i].param;

        //assign star ids
        for (u8 j=0;j<sizeof(cmm_star_objects);j++) {
            if (cmm_object_data[i].type == cmm_star_objects[j]) {
                if (cmm_play_stars_max < 32) {
                    obj->oBehParams = ((cmm_play_stars_max << 24)|(o->oBehParams2ndByte << 16));
                    cmm_play_stars_max++;
                }
                break;
            }
        }
    }
}

void place_tile(u8 x, u8 y, u8 z) {
    if ((!cmm_tile_types[cmm_id_selection].model)||(cmm_id_selection == TILE_TYPE_CULL)) {
        place_terrain_data(x,y,z,cmm_id_selection, cmm_rot_selection, cmm_mat_selection);
    }
    cmm_tile_data[cmm_tile_count].x = x;
    cmm_tile_data[cmm_tile_count].y = y;
    cmm_tile_data[cmm_tile_count].z = z;
    cmm_tile_data[cmm_tile_count].type = cmm_id_selection;
    cmm_tile_data[cmm_tile_count].mat = cmm_mat_selection;
    cmm_tile_data[cmm_tile_count].rot = cmm_rot_selection;
    cmm_tile_count++;
}

void place_object(u8 x, u8 y, u8 z) {
    if (cmm_object_count < 200) {
        cmm_object_data[cmm_object_count].x = x;
        cmm_object_data[cmm_object_count].y = y;
        cmm_object_data[cmm_object_count].z = z;
        cmm_object_data[cmm_object_count].type = cmm_id_selection;
        cmm_object_data[cmm_object_count].rot = cmm_rot_selection;
        cmm_object_data[cmm_object_count].param = cmm_param_selection;

        if (cmm_object_types[cmm_id_selection].use_trajectory) {
            u8 trajectory_found = FALSE;
            for (u8 i=0;i<5;i++) {
                if (!((cmm_trajectories_used>>i) & 1)) {
                    cmm_trajectories_used |= (1 << i);
                    cmm_trajectory_to_edit = i;
                    cmm_object_data[cmm_object_count].param = i;
                    trajectory_found = TRUE;
                    break;
                }
            }

            if (!trajectory_found) {
                play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                cmm_object_count --;
                remove_occupy_data(cmm_sbx,cmm_sby,cmm_sbz);
            } else {
                cmm_menu_state = CMM_MAKE_TRAJECTORY;
                o->oAction = 5; //trajectory editor
                cmm_trajectory_edit_index = 0;
                generate_path_gfx();
            }
        }

        cmm_object_count++;
    } else {
        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
    }
}

u8 joystick_direction(void) {
    if (cmm_joystick_timer > 0) {
        cmm_joystick_timer--;
    }

    if ((gPlayer1Controller->rawStickX < 10)&&(gPlayer1Controller->rawStickX > -10)&&(gPlayer1Controller->rawStickY < 10)&&(gPlayer1Controller->rawStickY > -10)) {
        cmm_joystick_timer = 0;
    }

    if (cmm_joystick_timer == 0) {
        if (gPlayer1Controller->rawStickX > 60) {
            cmm_joystick_timer = 5;
            return 3;
        }
        if (gPlayer1Controller->rawStickX < -60) {
            cmm_joystick_timer = 5;
            return 1;
        }
        if (gPlayer1Controller->rawStickY > 60) {
            cmm_joystick_timer = 5;
            return 4;
        }
        if (gPlayer1Controller->rawStickY < -60) {
            cmm_joystick_timer = 5;
            return 2;
        }
    }

    return 0;
}

void place_thing_action(void) {
    //tiles and objects share occupancy data
    if (!get_occupy_data(cmm_sbx,cmm_sby,cmm_sbz)) {
        if (cmm_place_mode == CMM_PM_TILE) {
            //CMM_PM_TILE
            if (tile_sanity_check()) {
                place_occupy_data(cmm_sbx,cmm_sby,cmm_sbz);
                place_tile(cmm_sbx,cmm_sby,cmm_sbz);
                generate_terrain_gfx();
            }
        } else {
            //CMM_PM_OBJECT
            if (object_sanity_check()) {
                place_occupy_data(cmm_sbx,cmm_sby,cmm_sbz);
                place_object(cmm_sbx,cmm_sby,cmm_sbz);
                generate_object_preview();
            }
        }
    }
}

//function name is delete tile, it deletes objects too
void delete_tile_action(void) {
    u16 i;
    u8 mode = 0;
    u8 found_tile = FALSE;

    //0 = searching
    //1 = targeting
    //(sport mode reference)

    for (i=0;i<cmm_tile_count;i++) {
        //search for tile to delete
        if (mode == 0) {
            if ((cmm_tile_data[i].x == cmm_sbx)&&(cmm_tile_data[i].y == cmm_sby)&&(cmm_tile_data[i].z == cmm_sbz)) {
                mode = 1;
                found_tile = TRUE;
                remove_occupy_data(cmm_sbx,cmm_sby,cmm_sbz);
                remove_terrain_data(cmm_sbx,cmm_sby,cmm_sbz);
                cmm_tile_count--;
            }
        }
        if (mode==1) {
            cmm_tile_data[i] = cmm_tile_data[i+1];
        }
    }

    if (found_tile) {
        generate_terrain_gfx();
    } else {
        //if there's no terrain here, it's probably an object
        mode = 0;
        for (i=0;i<cmm_object_count;i++) {
            //search for tile to delete
            if (mode == 0) {
                if ((cmm_object_data[i].x == cmm_sbx)&&(cmm_object_data[i].y == cmm_sby)&&(cmm_object_data[i].z == cmm_sbz)) {
                    mode = 1;
                    remove_occupy_data(cmm_sbx,cmm_sby,cmm_sbz);
                    cmm_object_count--;

                    if (cmm_object_types[cmm_object_data[i].type].use_trajectory) { 
                        //unlink trajectory
                        cmm_trajectories_used &= ~(1<<cmm_object_data[i].param);
                    }
                }
            }
            if (mode==1) {
                cmm_object_data[i].x     = cmm_object_data[i+1].x;
                cmm_object_data[i].y     = cmm_object_data[i+1].y;
                cmm_object_data[i].z     = cmm_object_data[i+1].z;
                cmm_object_data[i].type  = cmm_object_data[i+1].type;
                cmm_object_data[i].rot   = cmm_object_data[i+1].rot;
                cmm_object_data[i].param = cmm_object_data[i+1].param;
            }
        }
        generate_object_preview();
    }
}

void update_painting() {
    s16 x;
    s16 y;
    u16 *u16_array = segmented_to_virtual(b_LevelPainting_rgba16);
    for (x = 4; x < 28; x++) {
        for (y = 4; y < 28; y++) {
            u16_array[(y*32)+x] = cmm_save.lvl[0].piktcher[y-4][x-4];
        } 
    }
}

//if (gSramProbe != 0) {

TCHAR cmm_file_name[30];
FIL cmm_file;
FILINFO cmm_file_info;

void save_level(u8 index) {
    s16 i;
    s16 j;

    bzero(&cmm_save.lvl[index], sizeof(cmm_save.lvl[index]));
    //bzero(&cmm_grid_data, sizeof(cmm_grid_data));

    cmm_save.lvl[index].tile_count = cmm_tile_count;
    cmm_save.lvl[index].object_count = cmm_object_count;

    cmm_save.lvl[index].option[0] = cmm_lopt_costume;
    cmm_save.lvl[index].option[1] = cmm_lopt_seq;
    cmm_save.lvl[index].option[2] = cmm_lopt_envfx;
    cmm_save.lvl[index].option[3] = cmm_lopt_theme;
    cmm_save.lvl[index].option[4] = cmm_lopt_bg;
    cmm_save.lvl[index].option[5] = cmm_lopt_plane;
    cmm_save.lvl[index].option[18] = cmm_trajectories_used;
    cmm_save.lvl[index].option[19] = cmm_lopt_game;

    //SAVE
    for (i = 0; i < cmm_tile_count; i++) {
        //Save tiles
        bcopy(&cmm_tile_data[i],&cmm_save.lvl[index].tiles[i],sizeof(cmm_tile_data[i]));
    }

    for (i = 0; i < cmm_object_count; i++) {
        //Save Objects
        bcopy(&cmm_object_data[i],&cmm_save.lvl[index].objects[i],sizeof(cmm_object_data[i]));
    }

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 40; j++) {
            cmm_save.lvl[index].trajectories[i][j].t = cmm_trajectory_list[i][(j*4)+0];
            cmm_save.lvl[index].trajectories[i][j].x = cmm_trajectory_list[i][(j*4)+1]/300;
            cmm_save.lvl[index].trajectories[i][j].y = cmm_trajectory_list[i][(j*4)+2]/300;
            cmm_save.lvl[index].trajectories[i][j].z = cmm_trajectory_list[i][(j*4)+3]/300;
        }
    }

    for (i=0;i<784;i++) {
        //take a "screenshot" of the level
        cmm_save.lvl[index].piktcher[i/28][i%28] = gFramebuffers[(sRenderingFramebuffer+2)%3][ ((i/28)*320*8)+((i%28)*11)];
    }

    update_painting();

    //block_until_rumble_pak_free();
    //nuPiWriteSram(0,&cmm_save, sizeof(cmm_save));
    //release_rumble_pak_control();

    u32 bytes_written;
    f_open(&cmm_file,&cmm_file_name, FA_READ | FA_WRITE | FA_CREATE_ALWAYS);
    f_write(&cmm_file,&cmm_save,sizeof(cmm_save),&bytes_written);
    f_close(&cmm_file);
}

void load_level(u8 index) {
    s16 i;
    s16 j;
    u8 fresh = FALSE;

    bzero(&cmm_save.lvl[index], sizeof(cmm_save.lvl[index]));
    bzero(&cmm_grid_data, sizeof(cmm_grid_data));

    //LOAD
    //block_until_rumble_pak_free();
    //nuPiReadSram(0,&cmm_save, sizeof(cmm_save));
    //release_rumble_pak_control();

    u32 bytes_read;
    FRESULT code = f_stat(&cmm_file_name,&cmm_file_info);
    if (code == FR_OK) {
        //file exists, load it
        f_open(&cmm_file,&cmm_file_name, FA_READ | FA_WRITE);
        f_read(&cmm_file,&cmm_save,sizeof(cmm_save),&bytes_read);
        f_close(&cmm_file);
    } else {
        //Load into a fresh level
        fresh = TRUE;
        bzero(&cmm_save, sizeof(cmm_save));

        //Set version
        cmm_save.lvl[0].version = CMM_VERSION;

        //Place spawn location
        cmm_save.lvl[0].object_count = 1;
        cmm_save.lvl[0].objects[0].x = 16;
        cmm_save.lvl[0].objects[0].z = 16;
        cmm_save.lvl[0].objects[0].y = 4;
        cmm_save.lvl[0].objects[0].type = OBJECT_TYPE_SPAWN;

        cmm_save.lvl[index].option[19] = cmm_lopt_game;
    }

    cmm_tile_count = cmm_save.lvl[index].tile_count;
    cmm_object_count = cmm_save.lvl[index].object_count;

    cmm_lopt_costume = cmm_save.lvl[index].option[0];
    cmm_lopt_seq = cmm_save.lvl[index].option[1];
    cmm_lopt_envfx = cmm_save.lvl[index].option[2];
    cmm_lopt_theme = cmm_save.lvl[index].option[3];
    cmm_lopt_bg = cmm_save.lvl[index].option[4];
    cmm_lopt_plane = cmm_save.lvl[index].option[5];
    cmm_trajectories_used = cmm_save.lvl[index].option[18];
    cmm_lopt_game = cmm_save.lvl[index].option[19];

    //configure toolbox depending on game style
    switch(cmm_lopt_game) {
        case CMM_GAME_BTCM:
            bcopy(&cmm_toolbox_btcm,&cmm_toolbox,sizeof(cmm_toolbox));
        break;
        case CMM_GAME_VANILLA:
            bcopy(&cmm_toolbox_vanilla,&cmm_toolbox,sizeof(cmm_toolbox));
        break;
    }

    load_segment_decompress_skybox(0xA,cmm_skybox_table[cmm_lopt_bg*2],cmm_skybox_table[cmm_lopt_bg*2+1]);

    for (i = 0; i < cmm_tile_count; i++) {
        bcopy(&cmm_save.lvl[index].tiles[i],&cmm_tile_data[i],sizeof(cmm_tile_data[i]));
        if ((!cmm_tile_types[cmm_tile_data[i].type].model)||(cmm_tile_data[i].type == TILE_TYPE_CULL)) {
            place_terrain_data(cmm_tile_data[i].x,cmm_tile_data[i].y,cmm_tile_data[i].z,cmm_tile_data[i].type,cmm_tile_data[i].rot,cmm_tile_data[i].mat);
        }
        place_occupy_data(cmm_tile_data[i].x,cmm_tile_data[i].y,cmm_tile_data[i].z);
    }

    for (i = 0; i < cmm_object_count; i++) {
        bcopy(&cmm_save.lvl[index].objects[i],&cmm_object_data[i],sizeof(cmm_object_data[i]));
        place_occupy_data(cmm_object_data[i].x,cmm_object_data[i].y,cmm_object_data[i].z);
    }

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 40; j++) {
            cmm_trajectory_list[i][(j*4)+0] = cmm_save.lvl[index].trajectories[i][j].t;
            cmm_trajectory_list[i][(j*4)+1] = cmm_save.lvl[index].trajectories[i][j].x*300.0f;
            cmm_trajectory_list[i][(j*4)+2] = cmm_save.lvl[index].trajectories[i][j].y*300.0f;
            cmm_trajectory_list[i][(j*4)+3] = cmm_save.lvl[index].trajectories[i][j].z*300.0f;
        }
    }

    if (!fresh) {
        update_painting();
    }
}

void cmm_init() {
    load_level(0);
}

void sb_init(void) {
    struct Object *spawn_obj;

    cmm_sbx = 16;
    cmm_sby = 4;
    cmm_sbz = 16;

    cmm_ui_index = 0;
    vec3f_copy(&cmm_camera_foc,&o->oPosVec);
    load_segment_decompress_skybox(0xA,cmm_skybox_table[cmm_lopt_bg*2],cmm_skybox_table[cmm_lopt_bg*2+1]);

    switch(cmm_mode) {
        case CMM_MODE_MAKE:
            o->oAction = 1;
            o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            generate_object_preview();
            generate_terrain_gfx();
            cmm_preview_object = spawn_object(o,MODEL_NONE,bhvPreviewObject);

            //init visual tile bounds
            for (u8 i=0; i<6; i++) {
                cmm_boundary_object[i] = spawn_object(o,MODEL_MAKER_BOUNDARY,bhvPreviewObject);
            }
            cmm_boundary_object[2]->oFaceAngleRoll = -0x4000;
            cmm_boundary_object[3]->oFaceAngleRoll = -0x4000;
            cmm_boundary_object[4]->oFaceAnglePitch = 0x4000;
            cmm_boundary_object[5]->oFaceAnglePitch = 0x4000;
        break;
        case CMM_MODE_PLAY:
            generate_terrain_collision();
            generate_objects_to_level();
            load_obj_warp_nodes();

            spawn_obj = cur_obj_nearest_object_with_behavior(bhvSpawn);
            if (spawn_obj) {
                vec3f_copy(&gMarioState->pos,&spawn_obj->oPosVec);
                gMarioState->pos[1] += 150.0f;

                struct Object *warpobj = cur_obj_nearest_object_with_behavior(bhvInstantActiveWarp);
                if (warpobj) {
                    vec3f_copy(&warpobj->oPosVec,&spawn_obj->oPosVec);
                    warpobj->oPosY += 150.0f;
                }
            }

            gMarioState->CostumeID = cmm_lopt_costume;

            o->oAction = 2;
            o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;

            play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, seq_musicmenu_array[cmm_lopt_seq]), 0);
        break;
    }
}

void sb_loop(void) {
    Vec3f cam_pos_offset = {0.0f,cmm_current_camera_zoom[1],0};
    u8 joystick = joystick_direction();
    u8 cursor_did_move = FALSE;

    if (cmm_do_save) {
        cmm_do_save = FALSE;
        save_level(0);
    }
    //print_text_fmt_int(180, 200, "BUF %d", gGfxPoolEnd - (u8 *) gDisplayListHead);

    cmm_camera_angle = approach_s16_asymptotic(cmm_camera_angle,cmm_camera_rot_offset*0x4000,4);
    cam_pos_offset[0] = sins(cmm_camera_angle+0x8000)*cmm_current_camera_zoom[0];
    cam_pos_offset[2] = coss(cmm_camera_angle+0x8000)*cmm_current_camera_zoom[0];

    cmm_current_camera_zoom[0] = lerp(cmm_current_camera_zoom[0], cmm_camera_zoom_table[cmm_camera_zoom_index][0],0.2f);
    cmm_current_camera_zoom[1] = lerp(cmm_current_camera_zoom[1], cmm_camera_zoom_table[cmm_camera_zoom_index][1],0.2f);

    switch(o->oAction) {
        case 0: //init

        break;
        case 1: //MAKE MODE MAIN
            //START MOVE CURSOR
            if (joystick != 0) {
                switch(((joystick-1)+cmm_camera_rot_offset)%4) {
                    case 0:
                        cmm_sbx++;
                    break;
                    case 1:
                        cmm_sbz--;
                    break;
                    case 2:
                        cmm_sbx--;
                    break;
                    case 3:
                        cmm_sbz++;
                    break;
                }
            }

            if (gPlayer1Controller->buttonPressed & U_CBUTTONS) {
                cmm_sby++;
            }
            if (gPlayer1Controller->buttonPressed & D_CBUTTONS) {
                cmm_sby--;
            }
            if (gPlayer1Controller->buttonPressed & R_CBUTTONS) {
                cmm_camera_rot_offset++;
            }
            if (gPlayer1Controller->buttonPressed & L_CBUTTONS) {
                cmm_camera_rot_offset--;
            }
            cmm_camera_rot_offset = (cmm_camera_rot_offset % 4)+4;

            cmm_sbx=(cmm_sbx+32)%32;
            cmm_sbz=(cmm_sbz+32)%32;
            cmm_sby=(cmm_sby+32)%32;
            //END MOVE CURSOR

            if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                delete_tile_action();
            }

            if (gPlayer1Controller->buttonPressed & L_TRIG) {
                cmm_ui_index--;
                cmm_param_selection = 0;
            }
            if (gPlayer1Controller->buttonPressed & R_TRIG) {
                cmm_ui_index++;
                cmm_param_selection = 0;
            }
            cmm_id_selection = cmm_ui_buttons[cmm_ui_bar[cmm_ui_index]].id;
            cmm_place_mode = cmm_ui_buttons[cmm_ui_bar[cmm_ui_index]].isTile;
            cmm_ui_index = (cmm_ui_index+9)%9;

            //parameter changing
            if (gPlayer1Controller->buttonPressed & L_JPAD) {
                cmm_param_selection --;
            }
            if (gPlayer1Controller->buttonPressed & R_JPAD) {
                cmm_param_selection ++;
            }

            //camera zooming
            if (gPlayer1Controller->buttonPressed & U_JPAD) {
                cmm_camera_zoom_index--;
            }
            if (gPlayer1Controller->buttonPressed & D_JPAD) {
                cmm_camera_zoom_index++;
            }
            cmm_camera_zoom_index = (cmm_camera_zoom_index+5)%5;
  

            if ((gPlayer1Controller->buttonDown & A_BUTTON)&&(joystick > 0)&&(cmm_ui_index<6)) {
                place_thing_action();
            }

            //Single A press
            if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                switch(cmm_ui_index) {
                    case 8://save data
                        if (mount_success == FR_OK) {
                            cmm_do_save = TRUE;
                            cmm_ui_do_render = FALSE;
                        } else {
                            play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                        }
                    break;
                    case 7://settings
                        cmm_menu_state = CMM_MAKE_SETTINGS;
                        o->oAction = 4;
                    break;
                    case 6://test
                        cmm_target_mode = CMM_MODE_PLAY;
                        reset_play_state();
                        level_trigger_warp(gMarioState, WARP_OP_LOOK_UP);
                        sSourceWarpNodeId = 0x0A;
                        o->oAction = 2;
                    break;
                    default://everything else places
                        place_thing_action();
                    break; 
                }
            }

            if (o->oAction != 1) {
                return;
            }

            if (gPlayer1Controller->buttonPressed & START_BUTTON) {
                o->oAction = 3;
                cmm_menu_state = CMM_MAKE_TOOLBOX;
                if (cmm_ui_index > 5) {
                    cmm_ui_index = 5;
                }
            }

            if (gPlayer1Controller->buttonPressed & Z_TRIG) {
                cmm_rot_selection++;
                cmm_rot_selection%=4;
            }

            cmm_camera_foc[0] = lerp(cmm_camera_foc[0], cmm_sbx*300.0f, 0.2f);
            cmm_camera_foc[1] = lerp(cmm_camera_foc[1], cmm_sby*300.0f, 0.2f);
            cmm_camera_foc[2] = lerp(cmm_camera_foc[2], cmm_sbz*300.0f, 0.2f);

            vec3f_copy(&cmm_camera_pos,&cmm_camera_foc);
            vec3f_add(&cmm_camera_pos,&cam_pos_offset);

            o->oPosX = cmm_sbx*300.0f; 
            o->oPosY = cmm_sby*300.0f; 
            o->oPosZ = cmm_sbz*300.0f; 

            for (u8 i=0; i<6; i++) {
                vec3f_copy(&cmm_boundary_object[i]->oPosVec,&o->oPosVec);
            }
            cmm_boundary_object[0]->oPosY = 0.0f;
            cmm_boundary_object[1]->oPosY = 300.0f*32.0f;
            cmm_boundary_object[2]->oPosX = 0.0f;
            cmm_boundary_object[3]->oPosX = 300.0f*32.0f;
            cmm_boundary_object[4]->oPosZ = 0.0f;
            cmm_boundary_object[5]->oPosZ = 300.0f*32.0f;

            if (cmm_place_mode == CMM_PM_OBJ) {
                if (cmm_object_types[cmm_id_selection].param_max != 0) {
                    s16 max = cmm_object_types[cmm_id_selection].param_max;
                    cmm_param_selection = (cmm_param_selection+max)%max;
                }
                vec3f_copy(&cmm_preview_object->oPosX,&o->oPosX);
                cmm_preview_object->oPosY += cmm_object_types[cmm_id_selection].y_offset;
                obj_scale(cmm_preview_object, cmm_object_types[cmm_id_selection].scale);
                cmm_preview_object->header.gfx.sharedChild =  gLoadedGraphNodes[cmm_object_types[cmm_id_selection].model_id];
                cmm_preview_object->oFaceAngleYaw = cmm_rot_selection*0x4000;
                if (cmm_object_types[cmm_id_selection].billboarded) {
                    cmm_preview_object->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
                } else {
                    cmm_preview_object->header.gfx.node.flags &= ~GRAPH_RENDER_BILLBOARD;
                }
                if (cmm_object_types[cmm_id_selection].anim) {
                    cmm_preview_object->oAnimations = cmm_object_types[cmm_id_selection].anim;
                    super_cum_working(cmm_preview_object,0);
                }
                if (cmm_object_types[cmm_id_selection].disp_func) {
                    (cmm_object_types[cmm_id_selection].disp_func)(cmm_preview_object,cmm_param_selection);
                }
            } else {
                if (cmm_tile_types[cmm_id_selection].terrain) {
                    if (gPlayer1Controller->buttonPressed & L_JPAD) {
                        cmm_mat_selection --;
                    }
                    if (gPlayer1Controller->buttonPressed & R_JPAD) {
                        cmm_mat_selection ++;
                    }
                }
                cmm_mat_selection = (cmm_mat_selection+NUM_MATERIALS_PER_THEME)%NUM_MATERIALS_PER_THEME;
                cmm_preview_object->header.gfx.sharedChild =  gLoadedGraphNodes[MODEL_NONE];
            }

            if (!cmm_ui_do_render) {
                o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            } else {
                o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            }
        break;
        case 2://PLAY MODE

        break;
        case 3: //MAKE MODE TOOLBOX
            //TOOLBOX CONTROLS
            if (joystick != 0) {
                switch((joystick-1)%4) {
                    case 0:
                        cmm_toolbox_index--;
                    break;
                    case 1:
                        cmm_toolbox_index+=9;
                    break;
                    case 2:
                        cmm_toolbox_index++;
                    break;
                    case 3:
                        cmm_toolbox_index-=9;
                    break;
                }
            }
            cmm_toolbox_index = (cmm_toolbox_index+sizeof(cmm_toolbox))%sizeof(cmm_toolbox);

            //TOOLBAR CONTROLS
            if (gPlayer1Controller->buttonPressed & L_TRIG) {
                cmm_ui_index--;
            }
            if (gPlayer1Controller->buttonPressed & R_TRIG) {
                cmm_ui_index++;
            }
            cmm_id_selection = cmm_ui_buttons[cmm_ui_bar[cmm_ui_index]].id;
            cmm_place_mode = cmm_ui_buttons[cmm_ui_bar[cmm_ui_index]].isTile;
            cmm_ui_index = (cmm_ui_index+6)%6;

            //PRESS A TO MOVE FROM TOOLBOX TO TOOLBAR
            if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                //You can not put a blank button into the toolbox
                if ( cmm_toolbox[cmm_toolbox_index] != CMM_BUTTON_BLANK) {
                    cmm_param_selection = 0;
                    cmm_ui_bar[cmm_ui_index] = cmm_toolbox[cmm_toolbox_index];
                } else {
                    //error sound
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
            }

            if (gPlayer1Controller->buttonPressed & (START_BUTTON|B_BUTTON)) {
                o->oAction = 1;
                cmm_menu_state = CMM_MAKE_MAIN;
            }
        break;
        case 4: //settings
            if (joystick != 0) {
                switch((joystick-1)%4) {
                    case 0:
                        (*cmm_settings_buttons[cmm_settings_index].value) += cmm_settings_buttons[cmm_settings_index].size-1;
                        (*cmm_settings_buttons[cmm_settings_index].value) %= cmm_settings_buttons[cmm_settings_index].size;
                        cmm_settings_index_changed = TRUE;
                    break;
                    case 1:
                        cmm_settings_index++;
                    break;
                    case 2:
                        (*cmm_settings_buttons[cmm_settings_index].value) ++;
                        (*cmm_settings_buttons[cmm_settings_index].value) %= cmm_settings_buttons[cmm_settings_index].size;
                        cmm_settings_index_changed = TRUE;
                    break;
                    case 3:
                        cmm_settings_index+=SETTINGS_SIZE-1;
                    break;
                }
            }
            cmm_settings_index %= SETTINGS_SIZE;

            //hardcoded settings application
            if (cmm_settings_index_changed) {
                cmm_settings_index_changed = FALSE;
                switch(cmm_settings_index) {
                    case 3: //theme
                        generate_terrain_gfx();
                    break;
                    case 4: //sky box
                        load_segment_decompress_skybox(0xA,cmm_skybox_table[cmm_lopt_bg*2],cmm_skybox_table[cmm_lopt_bg*2+1]);
                    break;
                    case 5://bottom floor
                        generate_terrain_gfx();
                    break;
                }
            }

            if (gPlayer1Controller->buttonPressed & (START_BUTTON|B_BUTTON)) {
                o->oAction = 1;
                cmm_menu_state = CMM_MAKE_MAIN;
            }
        break;
        case 5: //trajectory maker
            //START MOVE CURSOR
            
            if (joystick != 0) {
                switch(((joystick-1)+cmm_camera_rot_offset)%4) {
                    case 0:
                        cmm_sbx++;
                        cursor_did_move = TRUE;
                    break;
                    case 1:
                        cmm_sbz--;
                        cursor_did_move = TRUE;
                    break;
                    case 2:
                        cmm_sbx--;
                        cursor_did_move = TRUE;
                    break;
                    case 3:
                        cmm_sbz++;
                        cursor_did_move = TRUE;
                    break;
                }
            }

            if (gPlayer1Controller->buttonPressed & U_CBUTTONS) {
                cmm_sby++;
                cursor_did_move = TRUE;
            }
            if (gPlayer1Controller->buttonPressed & D_CBUTTONS) {
                cmm_sby--;
                cursor_did_move = TRUE;
            }
            if (gPlayer1Controller->buttonPressed & R_CBUTTONS) {
                cmm_camera_rot_offset++;
            }
            if (gPlayer1Controller->buttonPressed & L_CBUTTONS) {
                cmm_camera_rot_offset--;
            }
            cmm_camera_rot_offset = (cmm_camera_rot_offset % 4)+4;

            //camera zooming
            if (gPlayer1Controller->buttonPressed & U_JPAD) {
                cmm_camera_zoom_index--;
            }
            if (gPlayer1Controller->buttonPressed & D_JPAD) {
                cmm_camera_zoom_index++;
            }
            cmm_camera_zoom_index = (cmm_camera_zoom_index+5)%5;

            cmm_sbx=(cmm_sbx+32)%32;
            cmm_sbz=(cmm_sbz+32)%32;
            cmm_sby=(cmm_sby+32)%32;
            //END MOVE CURSOR

            cmm_camera_foc[0] = lerp(cmm_camera_foc[0], cmm_sbx*300.0f, 0.2f);
            cmm_camera_foc[1] = lerp(cmm_camera_foc[1], cmm_sby*300.0f, 0.2f);
            cmm_camera_foc[2] = lerp(cmm_camera_foc[2], cmm_sbz*300.0f, 0.2f);

            vec3f_copy(&cmm_camera_pos,&cmm_camera_foc);
            vec3f_add(&cmm_camera_pos,&cam_pos_offset);

            o->oPosX = cmm_sbx*300.0f; 
            o->oPosY = cmm_sby*300.0f; 
            o->oPosZ = cmm_sbz*300.0f;

            if (o->oTimer == 0) {
                cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index*4 + 0] = cmm_trajectory_edit_index;
                cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index*4 + 1] = o->oPosX;
                cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index*4 + 2] = o->oPosY;
                cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index*4 + 3] = o->oPosZ;
                cmm_trajectory_edit_index++; 
            } else {
                if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                    cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index*4 + 0] = cmm_trajectory_edit_index;
                    cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index*4 + 1] = o->oPosX;
                    cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index*4 + 2] = o->oPosY;
                    cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index*4 + 3] = o->oPosZ;
                    cmm_trajectory_edit_index++;
                    generate_path_gfx();
                }
            }

            if ((gPlayer1Controller->buttonPressed & START_BUTTON)||(cmm_trajectory_edit_index == 39)) {
                cmm_trajectory_list[cmm_trajectory_to_edit][cmm_trajectory_edit_index*4 + 0] = -1;
                o->oAction = 1;
                cmm_menu_state = CMM_MAKE_MAIN;
                generate_path_gfx();
            }
        break;
    }
}

u8 string_runoff(s16 x, u8 * str) {
    s16 x1 = get_string_width(str);

    if (x+x1 > 320) {
        return TRUE;
    }
    return FALSE;
}

void print_maker_string_ascii(u16 x, u16 y, u8 * str, u8 highlight) {
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
    print_generic_string_ascii(x-1, y-1, str);
    switch(highlight) {
        case 0:
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        break;
        case 1:
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
        break;
        case 2:
            gDPSetEnvColor(gDisplayListHead++, 150, 150, 150, 255);
        break;
        case 3:
            gDPSetEnvColor(gDisplayListHead++, 150, 150, 0, 255);
        break;
    }
    print_generic_string_ascii(x, y, str);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

void print_maker_string(u16 x, u16 y, u8 * str, u8 highlight) {
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
    print_generic_string(x-1, y-1, str);
    if (highlight) {
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
    } else {
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    }
    print_generic_string(x, y, str);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

void draw_cmm_menu(void) {
    u8 i;
    u8 op;
    u8 yoff;
    u8 xi;
    u8 yi;

    u16 strx, stry;

    u16 decor_bar_offset = 36;
    if (cmm_menu_state == CMM_MAKE_TOOLBOX || cmm_menu_state == CMM_MAKE_SETTINGS) {
        decor_bar_offset = 235;
    }

    if (!cmm_ui_do_render) {
        cmm_ui_do_render = TRUE;
        return;
    }

    create_dl_translation_matrix(MENU_MTX_PUSH, 19, decor_bar_offset, 0);
    gDPSetEnvColor(gDisplayListHead++, 200, 200, 200, 150);
    gSPDisplayList(gDisplayListHead++, &bg_back_graund_mesh);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    for (i=0; i<9; i++) {
        op = 200;
        yoff = 20;
        if (i == cmm_ui_index) {
            op = 255;
            yoff = 25;
        }
        create_dl_translation_matrix(MENU_MTX_PUSH, 34+(i*32), yoff, 0);
        gDPSetEnvColor(gDisplayListHead++, op, op, op, 255);
        gSPDisplayList(gDisplayListHead++, cmm_ui_buttons[cmm_ui_bar[i]].material);//texture
        gSPDisplayList(gDisplayListHead++, &uibutton_button_mesh);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    }

    //TOOLBOX
    switch (cmm_menu_state) {
        case CMM_MAKE_MAIN:
            print_maker_string(15,45,cmm_ui_buttons[cmm_ui_bar[cmm_ui_index]].str,FALSE);
            if (cmm_ui_buttons[cmm_ui_bar[cmm_ui_index]].param_strings) {
                print_maker_string(30+get_string_width(cmm_ui_buttons[cmm_ui_bar[cmm_ui_index]].str),45,
                cmm_ui_buttons[cmm_ui_bar[cmm_ui_index]].param_strings[cmm_param_selection],TRUE);
            } else if (cmm_place_mode == CMM_PM_TILE && cmm_tile_types[cmm_id_selection].terrain) {
                print_maker_string(30+get_string_width(cmm_ui_buttons[cmm_ui_bar[cmm_ui_index]].str),45,
                cmm_theme_table[cmm_lopt_theme].mats[cmm_mat_selection].name,TRUE);
            }
        break;
        case CMM_MAKE_TOOLBOX:
        for (i=0; i<sizeof(cmm_toolbox); i++) {
            op = 255;
            yoff = 0;
            if (i == cmm_toolbox_index) {
                op = 100;
                yoff = 0;
            }
            xi = i%9;
            yi = i/9;
            create_dl_translation_matrix(MENU_MTX_PUSH, 34+(xi*32), 220-(yi*32), 0);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, op, 255);
            gSPDisplayList(gDisplayListHead++, cmm_ui_buttons[cmm_toolbox[i]].material);//texture
            gSPDisplayList(gDisplayListHead++, &uibutton_button_mesh);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);    
        }

        strx = 54+(cmm_toolbox_index%9)*32;
        stry = 215-(cmm_toolbox_index/9)*32;

        if (cmm_toolbox[cmm_toolbox_index] != CMM_BUTTON_BLANK) {
            //render selection box
            s16 sro = 0;
            if (string_runoff(strx,cmm_ui_buttons[cmm_toolbox[cmm_toolbox_index]].str)) {
                sro = -130;
            }

            create_dl_translation_matrix(MENU_MTX_PUSH, strx-2+sro, stry+16, 0);
            create_dl_scale_matrix(MENU_MTX_NOPUSH, 0.7f, 0.2f, 1.0f);
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
            gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            print_maker_string(strx+sro, stry ,cmm_ui_buttons[cmm_toolbox[cmm_toolbox_index]].str,TRUE);
            }

        break;

        case CMM_MAKE_SETTINGS:
            //PAINTING
            create_dl_translation_matrix(MENU_MTX_PUSH, 280, 200, 0);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
            gSPDisplayList(gDisplayListHead++, &mat_b_painting);//texture
            gSPDisplayList(gDisplayListHead++, &uibutton_button_mesh);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            //print_maker_string(15,210,txt_btn_2,FALSE);
            print_maker_string_ascii(15,210,&cmm_file_info.fname,FALSE);

            for (i=0;i<SETTINGS_SIZE;i++) {
                print_maker_string(15,180-(i*16),cmm_settings_buttons[i].str,(i==cmm_settings_index));
                print_maker_string(70,180-(i*16),cmm_settings_buttons[i].nametable[ *cmm_settings_buttons[i].value ],(i==cmm_settings_index));
            }
        break;

        case CMM_MAKE_TRAJECTORY:
            print_maker_string(20,210,cmm_txt_recording,TRUE);
        break;
    }
}

char cmm_mm_keyboard[] = {"1234567890abcdefghijklmnopqrstuvwxyz!'- "};
char cmm_mm_keyboard_caps[] = {"1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ!'- "};
char cmm_mm_keyboard_input[20];
u8 cmm_mm_keyboard_exit_mode = KXM_NEW_LEVEL;
u8 cmm_mm_keyboard_input_index = 0;
#define KEYBOARD_SIZE (sizeof(cmm_mm_keyboard)-1)
s8 cmm_mm_keyboard_index = 0;

char cmm_mm_comingsoon[] = {"Coming soon..."};
char cmm_mm_warning[] = \
{"WARNING!\n\
SD card emulation not detected.\n\
You will still be able to use\n\
the level editor, but you will\n\
not be able to save levels or\n\
download levels from other people.\n\
\n\
Press START to dismiss this message."};

char cmm_mm_btn1[] = {"Build"};
char cmm_mm_btn2[] = {"Play"};
char cmm_mm_btn3[] = {"Help"};
char cmm_mm_btn4[] = {"Credits"};
char * cmm_mm_btns[] = {
    &cmm_mm_btn1,
    &cmm_mm_btn2,
    &cmm_mm_btn3,
    &cmm_mm_btn4,
};
char * cmm_mm_btns_lim[] = {
    &cmm_mm_btn1,
    &cmm_mm_btn3,
    &cmm_mm_btn4,
};
char cmm_mm_play_btn1[] = {"Play Levels"};
char cmm_mm_play_btn2[] = {"Play Hacks"};
char * cmm_mm_play_btns[] = {
    &cmm_mm_play_btn1,
    &cmm_mm_comingsoon, //&cmm_mm_play_btn2,
};
char cmm_mm_make_btn1[] = {"New Level"};
char cmm_mm_make_btn2[] = {"Load Level"};
char cmm_mm_make_btn3[] = {"New Hack"};
char cmm_mm_make_btn4[] = {"Load Hack"};
char * cmm_mm_make_btns[] = {
    &cmm_mm_make_btn1,
    &cmm_mm_make_btn2,
    &cmm_mm_comingsoon, //&cmm_mm_make_btn3,
    &cmm_mm_comingsoon, //&cmm_mm_make_btn4,
};
char cmm_mm_lmode_btn1[] = {"Vanilla SM64"};
char cmm_mm_lmode_btn2[] = {"SM64 BTCM"};
char * cmm_mm_lmode_btns[] = {
    &cmm_mm_lmode_btn1,
    &cmm_mm_lmode_btn2,
};
char cmm_mm_help_btn1[] = {"SD Card Setup"};
char cmm_mm_help_btn2[] = {"Editor Controls"};
char cmm_mm_help_btn3[] = {"Version Info"};
char * cmm_mm_help_btns[] = {
    &cmm_mm_help_btn1,
    &cmm_mm_help_btn2,
    &cmm_mm_help_btn3,
};
char cmm_mm_help_page1[] = {TXT_MM_HELP_PAGE_1};
char cmm_mm_help_page2[] = {TXT_MM_HELP_PAGE_2};
char cmm_mm_help_page3[] = {TXT_MM_HELP_PAGE_3};
char cmm_mm_credits_page[] = {TXT_MM_CREDITS_PAGE};

char cmm_mm_txt_pages[] = {TXT_MM_PAGE};
char cmm_mm_txt_keyboard[] = {TXT_MM_KEYBOARD};

u8 cmm_mm_state = MM_INIT;
u8 cmm_mm_main_state = MM_MAIN;
s8 cmm_mm_index = 0;
s8 cmm_mm_pages = 0;
s8 cmm_mm_page = 0;
s8 cmm_mm_page_entries = 0;
char * cmm_mm_help_ptr = NULL;
#define PAGE_SIZE 5

void render_cmm_mm_menu(char * strlist[], u8 ct) {
    for (u8 i=0; i<ct; i++) {
        gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
        create_dl_translation_matrix(MENU_MTX_PUSH, 160, 200-(i*30), 0);
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 190);
        if (cmm_mm_index == i) {
            gDPSetEnvColor(gDisplayListHead++, 100, 100, 100, 190);
        }
        gSPDisplayList(gDisplayListHead++, &mm_btn2_mm_btn_mesh);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

        u8 grey_add = 0;
        if (strlist[i] == &cmm_mm_comingsoon) {
            grey_add = 2;
        }

        print_maker_string_ascii(120,192-(i*30),strlist[i],(cmm_mm_index == i)+grey_add);

    }
}

s32 cmm_main_menu(void) {
    u8 joystick = joystick_direction();
    switch(joystick) {
        case 2:
            cmm_mm_index++;
        break;
        case 4:
            cmm_mm_index--;
        break;
    }

    create_dl_ortho_matrix();

    switch(cmm_mm_state) {
        case MM_INIT:
            for (u8 i=0;i<sizeof(cmm_mm_keyboard_input);i++){
                cmm_mm_keyboard_input[i] = NULL;
            }
            if (mount_success == FR_OK) {
                cmm_mm_state = MM_MAIN;
            } else {
                cmm_mm_state = MM_NO_SD_CARD;
                cmm_mm_main_state = MM_MAIN_LIMITED;
            }
        break;
        case MM_NO_SD_CARD:
            shade_screen();
            print_maker_string_ascii(20,210,&cmm_mm_warning,FALSE);
            if (gPlayer1Controller->buttonPressed & START_BUTTON) {
                cmm_mm_state = MM_MAIN_LIMITED;
            }
        break;
        case MM_MAIN:
            cmm_mm_index = (cmm_mm_index+4)%4;
            render_cmm_mm_menu(&cmm_mm_btns,4);
            if (gPlayer1Controller->buttonPressed & (A_BUTTON|START_BUTTON)) {
                switch(cmm_mm_index) {
                    case 0:
                        cmm_mm_state = MM_MAKE;
                        cmm_mm_index = 0;
                    break;
                    case 1:
                        cmm_mm_state = MM_PLAY;
                        cmm_mm_index = 0;
                    break;
                    case 2:
                        cmm_mm_state = MM_HELP_MODE;
                        cmm_mm_index = 0;
                    break;
                    case 3:
                        cmm_mm_state = MM_CREDITS;
                    break;
                }
            }
        break;
        case MM_MAIN_LIMITED:
            cmm_mm_index = (cmm_mm_index+3)%3;
            render_cmm_mm_menu(&cmm_mm_btns_lim,3);
            if (gPlayer1Controller->buttonPressed & (A_BUTTON|START_BUTTON)) {
                switch(cmm_mm_index) {
                    case 0:
                        return 1;
                    break;
                    case 1:
                        cmm_mm_state = MM_HELP_MODE;
                        cmm_mm_index = 0;
                    break;
                    case 2:
                        cmm_mm_state = MM_CREDITS;
                    break;
                }
            }
        break;
        case MM_PLAY:
            cmm_mm_index = (cmm_mm_index+2)%2;
            render_cmm_mm_menu(&cmm_mm_play_btns,2);

            if (gPlayer1Controller->buttonPressed & (A_BUTTON|START_BUTTON)) {
                switch(cmm_mm_index) {
                    case 0: //play levels
                        cmm_mm_state = MM_FILES;
                        cmm_mm_index = 0;
                    break;
                    case 1: //play hacks
                        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                    break;
                }
            }

            if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                cmm_mm_state = cmm_mm_main_state;
                cmm_mm_index = 0;
            }
        break;
        case MM_MAKE:
            cmm_mm_index = (cmm_mm_index+4)%4;
            render_cmm_mm_menu(&cmm_mm_make_btns,4);
            if (gPlayer1Controller->buttonPressed & (A_BUTTON|START_BUTTON)) {
                switch(cmm_mm_index) {
                    case 0:
                        //make new level
                        cmm_mm_state = MM_MAKE_MODE;
                        cmm_mm_index = 0;
                    break;
                    case 1:
                        //load levels
                        cmm_mm_state = MM_FILES;
                        cmm_mm_index = 0;
                    break;
                    case 2://make new hack
                    case 3://load hack

                    break;
                }
            }
            if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                cmm_mm_state = cmm_mm_main_state;
                cmm_mm_index = 0;
            }
        break;
        case MM_MAKE_MODE:
            cmm_mm_index = (cmm_mm_index+2)%2;
            render_cmm_mm_menu(&cmm_mm_lmode_btns,2);
            if (gPlayer1Controller->buttonPressed & (A_BUTTON|START_BUTTON)) {
                cmm_mm_keyboard_exit_mode = KXM_NEW_LEVEL;
                cmm_mm_state = MM_KEYBOARD;

                switch(cmm_mm_index) {
                    case 0: //vanilla
                        cmm_lopt_game = 1;
                    break;
                    case 1: //btcm
                        cmm_lopt_game = 0;
                    break;
                }
            }
            if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                cmm_mm_state = cmm_mm_main_state;
                cmm_mm_index = 0;
            }
        break;
        case MM_HELP_MODE:
            cmm_mm_index = (cmm_mm_index+3)%3;
            render_cmm_mm_menu(&cmm_mm_help_btns,3);
            if (gPlayer1Controller->buttonPressed & (A_BUTTON|START_BUTTON)) {
                cmm_mm_state = MM_HELP;
                switch(cmm_mm_index) {
                    case 0:
                        cmm_mm_help_ptr = cmm_mm_help_page1;
                    break;
                    case 1:
                        cmm_mm_help_ptr = cmm_mm_help_page2;
                    break;
                    case 2:
                        cmm_mm_help_ptr = cmm_mm_help_page3;
                    break;
                }
            }
            if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                cmm_mm_state = cmm_mm_main_state;
                cmm_mm_index = 0;
            }
        break;
        case MM_HELP:
            shade_screen();
            print_maker_string(20,210,cmm_mm_help_ptr,FALSE);

            if (cmm_mm_help_ptr == cmm_mm_help_page1) {
                gSPDisplayList(gDisplayListHead++, &pl_scard_pl_scard_mesh);
            }

            if (gPlayer1Controller->buttonPressed & (A_BUTTON|B_BUTTON|START_BUTTON)) {
                cmm_mm_state = MM_HELP_MODE;
                cmm_mm_index = 0;
            }
        break;
        case MM_CREDITS:
            shade_screen();
            print_maker_string(20,210,cmm_mm_credits_page,FALSE);
            if (gPlayer1Controller->buttonPressed & (A_BUTTON|B_BUTTON|START_BUTTON)) {
                cmm_mm_state = cmm_mm_main_state;
                cmm_mm_index = 0;
            }
        break;
        case MM_KEYBOARD:
            switch(joystick) {
                case 1:
                    cmm_mm_keyboard_index--;
                break;
                case 2:
                    cmm_mm_keyboard_index+=10;
                break;
                case 3:
                    cmm_mm_keyboard_index++;
                break;
                case 4:
                    cmm_mm_keyboard_index-=10;
                break;
            }
            cmm_mm_keyboard_index = (cmm_mm_keyboard_index+KEYBOARD_SIZE)%KEYBOARD_SIZE;

            if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                if (gPlayer1Controller->buttonDown & Z_TRIG) {
                    //shift
                    cmm_mm_keyboard_input[cmm_mm_keyboard_input_index] = cmm_mm_keyboard_caps[cmm_mm_keyboard_index];
                } else {
                    cmm_mm_keyboard_input[cmm_mm_keyboard_input_index] = cmm_mm_keyboard[cmm_mm_keyboard_index];
                }
                cmm_mm_keyboard_input_index++;
            }

            if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                if (cmm_mm_keyboard_input_index > 0) {
                    cmm_mm_keyboard_input_index--;
                    cmm_mm_keyboard_input[cmm_mm_keyboard_input_index] = NULL;
                } else {
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
            }

            if (gPlayer1Controller->buttonPressed & START_BUTTON) {
                switch(cmm_mm_keyboard_exit_mode) {
                    case KXM_NEW_LEVEL:
                        bcopy(&cmm_mm_keyboard_input,&cmm_file_name,cmm_mm_keyboard_input_index);
                        //manually add file extension
                        cmm_file_name[cmm_mm_keyboard_input_index+0] = '.';
                        cmm_file_name[cmm_mm_keyboard_input_index+1] = 'm';
                        cmm_file_name[cmm_mm_keyboard_input_index+2] = 'b';
                        cmm_file_name[cmm_mm_keyboard_input_index+3] = '6';
                        cmm_file_name[cmm_mm_keyboard_input_index+4] = '4';
                        cmm_file_name[cmm_mm_keyboard_input_index+5] = NULL;
                        return 1;
                    break;
                }
            }

            if (gPlayer1Controller->buttonPressed & R_TRIG) {
                cmm_mm_state = cmm_mm_main_state;
                cmm_mm_index = 0;
            }

            shade_screen();
            print_maker_string_ascii(35,210,cmm_mm_keyboard_input,FALSE);
            print_maker_string(35,80,cmm_mm_txt_keyboard,FALSE);

            for (u8 i=0; i<(sizeof(cmm_mm_keyboard)-1); i++) {
                u16 x = i%10;
                u16 y = i/10;
                gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
                create_dl_translation_matrix(MENU_MTX_PUSH, 40+(x*25), 190-(y*25), 0);
                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
                if (cmm_mm_keyboard_index == i) {
                    gDPSetEnvColor(gDisplayListHead++, 100, 100, 100, 150);
                }
                gSPDisplayList(gDisplayListHead++, &mm_btn_sm_mm_btn_sm_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
                char single_char[2];
                if (gPlayer1Controller->buttonDown & Z_TRIG) {
                    //shift
                    single_char[0] = cmm_mm_keyboard_caps[i];
                } else {
                    single_char[0] = cmm_mm_keyboard[i];
                }
                single_char[1] = NULL;
                print_maker_string_ascii(37+(x*25),182-(y*25),single_char,(cmm_mm_keyboard_index == i));
            }
        break;
        case MM_FILES:
            if (cmm_level_entry_count == 0) {
                //no levels, do not render anything
                gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
                create_dl_translation_matrix(MENU_MTX_PUSH, 160, 210, 0);
                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
                gSPDisplayList(gDisplayListHead++, &mm_btn_lg_mm_btn_lg_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

                print_maker_string_ascii(55,200,"No levels currently loaded yet.",TRUE);

                if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                    cmm_mm_state = cmm_mm_main_state;
                    cmm_mm_index = 0;
                }
                return;
            }

            cmm_mm_index = (cmm_mm_index+cmm_level_entry_count)%cmm_level_entry_count;

            cmm_mm_pages = (cmm_level_entry_count/PAGE_SIZE)+1;
            cmm_mm_page = cmm_mm_index/PAGE_SIZE;
            cmm_mm_page_entries = PAGE_SIZE;
            if (cmm_mm_page == cmm_mm_pages-1) {
                cmm_mm_page_entries = cmm_level_entry_count-(cmm_mm_page*PAGE_SIZE);
            }

            if (gPlayer1Controller->buttonPressed & (A_BUTTON|START_BUTTON)) {
                for (u8 i=0; cmm_level_entries[cmm_mm_index].fname[i] != 0;i++) {
                    cmm_file_name[i] = cmm_level_entries[cmm_mm_index].fname[i];
                }
                return 1;
            }
            if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                cmm_mm_state = cmm_mm_main_state;
                cmm_mm_index = 0;
            }

            for (u8 i=0; i<cmm_mm_page_entries; i++) {
                gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
                create_dl_translation_matrix(MENU_MTX_PUSH, 160, 210-(i*36), 0);
                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
                if (cmm_mm_index-(cmm_mm_page*PAGE_SIZE) == i) {
                    gDPSetEnvColor(gDisplayListHead++, 100, 100, 100, 190);
                }
                gSPDisplayList(gDisplayListHead++, &mm_btn_lg_mm_btn_lg_mesh);

                //render painting
                create_dl_translation_matrix(MENU_MTX_PUSH, -108, -2, 0);
                    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                    gDPPipeSync(gDisplayListHead++);
                    gDPSetCombineLERP(gDisplayListHead++,ENVIRONMENT, 0, TEXEL0, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, TEXEL0, 0, 0, 0, 0, TEXEL0);
                    gSPGeometryMode(gDisplayListHead++,G_ZBUFFER | G_CULL_BACK, 0);
                    gSPTexture(gDisplayListHead++,65535, 65535, 0, 0, 1);
                    gDPSetTextureImage(gDisplayListHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, &cmm_level_entry_piktcher[i+(cmm_mm_page*PAGE_SIZE)]);
                    gSPDisplayList(gDisplayListHead++, &mptng_mptng_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                //


                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
                print_maker_string_ascii(75,200-(i*36),&cmm_level_entries[i+(cmm_mm_page*PAGE_SIZE)].fname,(cmm_mm_index == i));
            }

            //render pages
            create_dl_translation_matrix(MENU_MTX_PUSH, 90, 20, 0);
            gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
            gSPDisplayList(gDisplayListHead++, mm_btn2_mm_btn_mesh);
            gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
            int_to_str_slash(cmm_mm_page+1, cmm_mm_pages, &cmm_mm_txt_pages[6]);
            print_maker_string(42,12,&cmm_mm_txt_pages,FALSE);
        break;
    }

    return 0;
}