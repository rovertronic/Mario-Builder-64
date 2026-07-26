#pragma once

#include "libcart/include/cart.h"
#include "libcart/ff/ff.h"

#include "mb64/gfx/tile.h"
#include "mb64/editor/trajectory.h"

struct mb64_template {
    u8 music[2];
    u32 envfx:3;
    u32 bg:4;
    u32 theme:4;
    u32 boundaryMat:4;
    u32 boundaryHeight:6;
    u32 boundary:3;
    u32 water:6;

    u32 spawnHeight:6;
    u32 platform:1;
    u32 platformmat:4;
};

extern struct mb64_template mb64_templates[];

#define SRAM_MAGIC 0x0203DD10

#define MB64_VERSION 1
#define MAX_FILE_NAME_SIZE 41
#define MAX_FILE_NAME_INPUT (MAX_FILE_NAME_SIZE - 6)
#define MAX_USERNAME_SIZE 31
#define MAX_USERNAME_INPUT (MAX_USERNAME_SIZE - 1)

struct mb64_sram_config {
    char author[MAX_USERNAME_SIZE];
    u8 option_flags;
    u32 magic;
    u64 pad;
};

#define MAX_FILES 251
extern u8 mb64_level_entry_version[MAX_FILES];
extern FRESULT gMountSuccess;
extern FRESULT global_code;
extern u8 mb64_level_entry_count;
extern TCHAR *mb64_level_dir_name;
extern TCHAR *mb64_hack_dir_name;
extern struct mb64_sram_config mb64_sram_configuration;
extern struct mb64_level_save_header mb64_save;

extern char mb64_file_name[MAX_FILE_NAME_SIZE];
extern FILINFO mb64_file_info;

#define gSDCard (gMountSuccess == FR_OK)

void mb64_file_init(void);
void save_level(void);
void load_level(void);

void create_level_file_path(TCHAR * buffer, TCHAR * filename, TCHAR * suffix);
struct mb64_level_save_header * get_level_info_from_filename(char * filename);
void load_level_files_from_sd_card(void);
u8 level_file_exists(char * filename);

struct mb64_level_save_header {
    char file_header[10];
    u8 version;
    char author[MAX_USERNAME_SIZE];
    u16 thumbnail[64][64];

    // Level options
    u8 costume;
    u8 seq[5];
    u8 envfx;
    u8 theme;
    u8 bg;
    u8 boundary_mat;
    u8 boundary;
    u8 boundary_height;
    u8 coinstar;
    u8 size;
    u8 waterlevel;
    u8 secret;
    u8 game;

    u8 toolbar[9];
    u8 toolbar_params[9];
    u16 tile_count;
    u16 object_count;

    struct mb64_custom_theme custom_theme;
    struct mb64_comptraj trajectories[MB64_MAX_TRAJECTORIES][MB64_TRAJECTORY_LENGTH];

    u64 pad;
};
