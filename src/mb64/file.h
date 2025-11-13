#pragma once

#include "libcart/include/cart.h"
#include "libcart/ff/ff.h"

#include "structs.h"

#define MB64_VERSION 1
#define MAX_FILE_NAME_SIZE 41
#define MAX_FILE_NAME_INPUT (MAX_FILE_NAME_SIZE - 6)
#define MAX_USERNAME_SIZE 31
#define MAX_USERNAME_INPUT (MAX_USERNAME_SIZE - 1)

#define MB64_MAX_TRAJECTORIES 20
#define MB64_TRAJECTORY_LENGTH 50

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



struct mb64_custom_theme {
    u8 mats[NUM_MATERIALS_PER_THEME];
    u8 topmats[NUM_MATERIALS_PER_THEME];
    u8 topmatsEnabled[NUM_MATERIALS_PER_THEME];
    u8 fence;
    u8 pole;
    u8 bars;
    u8 water;
};

//compressed trajectories
struct mb64_comptraj {
    s8 t;
    u8 x;
    u8 y;
    u8 z;
};

struct mb64_level_save_header {
    char file_header[10];
    u8 version;
    char author[MAX_USERNAME_SIZE];
    u16 piktcher[64][64];

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
