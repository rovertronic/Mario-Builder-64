#include "file.h"
#include "editor/main.h"
#include "editor/object.h"
#include "mb64/menu/misc.h"
#include "mb64/menu/toolbox.h"
#include "compatibility.h"

#include "game/segment2.h"
#include "game/emutest.h"
#include "buffers/framebuffers.h"
#include "game/puppyprint.h"
#include <string.h>

#include "levels/menu/header.h"
#include "actors/bigpainting2/header.h"

char mb64_file_name[MAX_FILE_NAME_SIZE];
FIL mb64_file;
FILINFO mb64_file_info;

char file_header_string[] = "MB64-v1.1";

FATFS fs;
FRESULT gMountSuccess;
FRESULT gDirectorySuccess;
FILINFO mb64_dir_info;

struct mb64_level_save_header temp_mb64_save;
struct mb64_level_save_header mb64_save;


u8 mb64_level_entry_count = 0;
FRESULT global_code;

TCHAR *mb64_level_dir_name = "/Mario Builder 64 Levels";
TCHAR *mb64_hack_dir_name = "/Mario Builder 64 Hacks";

struct mb64_sram_config mb64_sram_configuration;

void create_level_file_path(TCHAR *buffer, TCHAR *filename, TCHAR *suffix) {
    TCHAR *s;
    s = mb64_level_dir_name;
    while (*s) {
        *buffer++ = *s++;
    }
    *buffer++ = '/';
    s = filename;
    while (*s) {
        *buffer++ = *s++;
    }
    if (suffix) {
        s = suffix;
        while (*s) {
            *buffer++ = *s++;
        }
    }
    *buffer++ = '\0';
}

struct mb64_level_save_header * get_level_info_from_filename(char * filename) {
    u32 bytes_read;
    FIL read_file;
    TCHAR path[256];
    create_level_file_path(path, filename, NULL);
    f_open(&read_file,path, FA_READ);
    f_read(&read_file,&temp_mb64_save,sizeof(temp_mb64_save),&bytes_read);
    f_close(&read_file);

    return &temp_mb64_save;
}

char filename_with_mb64[31];
u8 level_file_exists(char * filename) {
    FILINFO fno;
    TCHAR path[256];
    create_level_file_path(path, filename, ".mb64");
    return (f_stat(path, &fno) == FR_OK);
}

u8 mb64_level_entry_version[MAX_FILES];
void load_level_files_from_sd_card(void) {
    DIR dir;
    f_opendir(&dir,mb64_level_dir_name);

    // LEVEL ENTRIES ARE LOADED IN FILE SELECT
    FILINFO * level_entries_ptr = segmented_to_virtual(mb64_level_entries);
    u16 (*u16_array)[MAX_FILES][64][64] = segmented_to_virtual(mb64_level_entry_thumbnail);

    s16 i = -1;
    do {
        i++;
        if ((f_readdir(&dir,&level_entries_ptr[i]) == FR_OK)) {
            if (level_entries_ptr[i].fname[0] == 0) {
                // Reached end of directory
                continue;
            }
            s32 filenamelen = strlen(level_entries_ptr[i].fname);
            if (filenamelen > MAX_FILE_NAME_SIZE - 1) {
                // Too long level name, skip
                i--;
                continue;
            }
            if ((filenamelen > 5) && (strcmp(level_entries_ptr[i].fname + (filenamelen - 5), ".mb64"))) {
                // File is not an .mb64 file
                i--;
                continue;
            }
            struct mb64_level_save_header * level_info = get_level_info_from_filename(level_entries_ptr[i].fname);

            s16 x;
            s16 y;
            for (x = 0; x < 64; x++) {
                for (y = 0; y < 64; y++) {
                    (*u16_array)[i][y][x] = level_info->thumbnail[y][x];
                } 
            }
            mb64_level_entry_version[i] = level_info->version;
        }

    } while ((level_entries_ptr[i].fname[0] != 0) && (i<MAX_FILES-1));

    mb64_level_entry_count = i;

    f_closedir(&dir);
}

void mb64_file_init(void) {
    //init mb64 file structure
    cart_init();
    gMountSuccess = f_mount(&fs, "", 1);
    if (gMountSuccess == FR_OK) {
        //mount is successful

        //create directory if not exist
        gDirectorySuccess = f_stat(mb64_level_dir_name,&mb64_dir_info);
        if (gDirectorySuccess == FR_NO_FILE) {
            //does not exist, therefore make
            f_mkdir(mb64_level_dir_name);
        }
        
    }
}

void update_painting() {
    s16 x;
    s16 y;
    u16 *u16_array = segmented_to_virtual(bigpainting2_bigger_painting_rgba16);
    for (x = 0; x < 64; x++) {
        for (y = 0; y < 64; y++) {
            u16_array[(y*64)+x] = mb64_save.thumbnail[y][x];
        } 
    }
}

extern u16 sRenderedFramebuffer;
#define INSTANT_INPUT_WHITELIST (EMU_PARALLEL_LAUNCHER | EMU_PROJECT64 | EMU_MUPEN)
void save_level(void) {
    //bzero(&mb64_save, sizeof(mb64_save)); // should be safe to not need this right?
    if (mb64_vtx_total >= MB64_VTX_SIZE) {
        show_error("Save Failed - Vertex limit exceeded.");
        return;
    }

    //file header
    strncpy(mb64_save.file_header, file_header_string, 10);

    //author
    if ((mb64_sram_configuration.author[0] != '\0') && (mb64_save.author[0] == '\0')) {
        strncpy(mb64_save.author, mb64_sram_configuration.author, MAX_USERNAME_SIZE);
    }

    mb64_save.tile_count = mb64_tile_count;
    mb64_save.object_count = mb64_object_count;

    mb64_save.costume = mb64_lopt_costume;
    mb64_save.seq[0] = mb64_lopt_seq[0];
    mb64_save.seq[1] = mb64_lopt_seq[1];
    mb64_save.seq[2] = mb64_lopt_seq[2];
    mb64_save.envfx = mb64_lopt_envfx;
    mb64_save.theme = mb64_lopt_theme;
    mb64_save.bg = mb64_lopt_bg;
    mb64_save.boundary_mat = mb64_lopt_boundary_mat;
    mb64_save.boundary = mb64_lopt_boundary;
    mb64_save.boundary_height = mb64_lopt_boundary_height;
    mb64_save.coinstar = mb64_lopt_coinstar;
    mb64_save.size = mb64_lopt_size;
    mb64_save.waterlevel = mb64_lopt_waterlevel;
    mb64_save.secret = mb64_lopt_secret;
    mb64_save.game = mb64_lopt_game;

    for (s32 i = 0; i < MB64_MAX_TRAJECTORIES; i++) {
        for (s32 j = 0; j < MB64_TRAJECTORY_LENGTH; j++) {
            mb64_save.trajectories[i][j].t = mb64_trajectory_list[i][j].flags;
            mb64_save.trajectories[i][j].x = POS_TO_GRID(mb64_trajectory_list[i][j].pos[0]);
            mb64_save.trajectories[i][j].y = POS_TO_GRID(mb64_trajectory_list[i][j].pos[1]);
            mb64_save.trajectories[i][j].z = POS_TO_GRID(mb64_trajectory_list[i][j].pos[2]);
        }
    }

    // If in screenshot mode
    if (mb64_prepare_level_screenshot) {
        u8 screenshot_failure = TRUE;

        for (s32 x=0;x<64;x++) {
            for (s32 y=0;y<64;y++) {
                int i = (y*64)+x;
                //take a "screenshot" of the level & burn in a painting frame
                if (mb64_painting_frame[(i*2)+1]==0x00) {
                    // Take samples (double resolution)
                    u16 sample[4];
                    for (s32 sx=0;sx<2;sx++) {
                        for (s32 sy=0;sy<2;sy++) {
                            if (!(gEmulator & INSTANT_INPUT_WHITELIST)) {
                                sample[sy*2+sx] = (gFramebuffers[(sRenderedFramebuffer+2)%3][ ((s32)((y*2+sy)*1.875f))*320 + (s32)((x*2+sx)*1.875f+40) ] | 1);
                            } else {
                                sample[sy*2+sx] = (gFramebuffers[0][ ((s32)((y*2+sy)*1.875f))*320 + (s32)((x*2+sx)*1.875f+40) ] | 1);
                            }
                        }
                    }

                    // Average 4 samples into single pixel
                    f32 avgColor[3] = {0.0f,0.0f,0.0f}; //floating point is overkill but might as well make it accurate as possible
                    for (int c = 0; c < 3; c++) {
                        int shift;
                        switch(c) {
                            case 0: shift=11;break;
                            case 1: shift=6;break;
                            case 2: shift=1;break;
                        }
                        for (int s = 0; s < 4; s++) {
                            avgColor[c] += (f32)((sample[s] >> shift) & 0x1F);
                        }
                        avgColor[c] /= 4.0f; //average of 4 samples
                    }

                    mb64_save.thumbnail[y][x] = ((u16)avgColor[0] << 11) | ((u16)avgColor[1] << 6) | ((u16)avgColor[2] << 1) | 1;
                    //mb64_save.thumbnail[y][x] = sample[0];

                    if (mb64_save.thumbnail[y][x] > 1) { //assumes all fb rgba16 values is initialized to 1 or 0
                        screenshot_failure = FALSE;
                    }
                } else {
                    //painting frame
                    mb64_save.thumbnail[y][x] = ((mb64_painting_frame[(i*2)]<<8) | mb64_painting_frame[(i*2)+1]);
                }
            }
        }

        if (screenshot_failure) {
            //framebuffer emulation not enabled, use ?
            show_error("Screenshot failed.\nMake sure framebuffer emulation (FBE) is enabled.");
            bcopy(&mb64_painting_unknown,&mb64_save.thumbnail,sizeof(mb64_save.thumbnail));
        }

        update_painting();
    }

    if (mb64_save.thumbnail[0][0] == 0) { //0 is a transparent pixel in rgba16
        //use mystery painting if no screenshot has been taken yet
        bcopy(&mb64_painting_unknown,&mb64_save.thumbnail,sizeof(mb64_save.thumbnail));
    }
    bcopy(&mb64_curr_custom_theme,&mb64_save.custom_theme,sizeof(struct mb64_custom_theme));
    bcopy(&mb64_toolbar, &mb64_save.toolbar, sizeof(mb64_save.toolbar));
    bcopy(&mb64_toolbar_params, &mb64_save.toolbar_params, sizeof(mb64_save.toolbar_params));

    TCHAR path[256];
    create_level_file_path(path, mb64_file_name, NULL);
    UINT bytes_written;
    f_open(&mb64_file,path, FA_READ | FA_WRITE | FA_CREATE_ALWAYS);
    //write header
    f_write(&mb64_file,&mb64_save,sizeof(mb64_save),&bytes_written);
    //write tiles
    f_write(&mb64_file,&mb64_tile_data,(sizeof(mb64_tile_data[0])*mb64_tile_count),&bytes_written);
    //write objects
    f_write(&mb64_file,&mb64_object_data,(sizeof(mb64_object_data[0])*mb64_object_count),&bytes_written);

    f_close(&mb64_file);
}

void load_level(void) {
    u8 fresh = FALSE;

    bzero(&mb64_save, sizeof(mb64_save));
    bzero(&mb64_grid_data, sizeof(mb64_grid_data));

    TCHAR path[256];
    create_level_file_path(path, mb64_file_name, NULL);
    FRESULT code = f_stat(path,&mb64_file_info);
    if (code == FR_OK) {
        UINT bytes_read;
        //file exists, load it
        f_open(&mb64_file,path, FA_READ | FA_WRITE);
        //read header
        f_read(&mb64_file,&mb64_save,sizeof(mb64_save),&bytes_read);
        //read tiles
        f_read(&mb64_file,&mb64_tile_data,sizeof(mb64_tile_data[0])*mb64_save.tile_count,&bytes_read);
        //read objects
        f_read(&mb64_file,&mb64_object_data,sizeof(mb64_object_data[0])*mb64_save.object_count,&bytes_read);

        f_close(&mb64_file);
    } else {
        //Load into a fresh level
        fresh = TRUE;
        strncpy(mb64_file_info.fname,mb64_file_name,MAX_FILE_NAME_SIZE);

        //Set version
        mb64_save.version = MB64_VERSION;

        //Place spawn location
        mb64_save.object_count = 1;
        mb64_object_data[0].x = 32;
        mb64_object_data[0].z = 32;
        mb64_object_data[0].y = mb64_templates[mb64_lopt_template].spawnHeight;
        mb64_object_data[0].type = OBJECT_TYPE_MARIO_SPAWN;

        mb64_save.game = mb64_lopt_game;
        mb64_save.size = mb64_lopt_size;

        mb64_save.seq[0] = mb64_templates[mb64_lopt_template].music[mb64_lopt_game];
        mb64_save.seq[1] = 1;
        mb64_save.seq[2] = 10;
        if (mb64_lopt_game == MB64_GAME_BTCM) {
            mb64_save.seq[2] = 22;
        }
        mb64_save.envfx = mb64_templates[mb64_lopt_template].envfx;
        mb64_save.theme = mb64_templates[mb64_lopt_template].theme;
        mb64_save.bg = mb64_templates[mb64_lopt_template].bg;
        mb64_save.boundary_mat = mb64_templates[mb64_lopt_template].boundaryMat;
        mb64_save.waterlevel = mb64_templates[mb64_lopt_template].water;
        mb64_save.boundary = mb64_templates[mb64_lopt_template].boundary;
        mb64_save.boundary_height = mb64_templates[mb64_lopt_template].boundaryHeight;

        bcopy(&mb64_toolbar_defaults,&mb64_save.toolbar,sizeof(mb64_save.toolbar));
        bzero(&mb64_save.toolbar_params,sizeof(mb64_save.toolbar_params));

        if (mb64_templates[mb64_lopt_template].platform) {
            u8 i = 0;
            for (s32 x = -1; x <= 1; x++) {
                for (s32 z = -1; z <= 1; z++) {
                    mb64_tile_data[i].x = 32+x;
                    mb64_tile_data[i].y = mb64_templates[mb64_lopt_template].spawnHeight - 3;
                    mb64_tile_data[i].z = 32+z;
                    mb64_tile_data[i].type = TILE_TYPE_BLOCK;
                    mb64_tile_data[i].mat = mb64_templates[mb64_lopt_template].platformmat;
                    i++;
                }
            }
            mb64_save.tile_count = i;
        }

        bcopy(&mb64_default_custom,&mb64_save.custom_theme,sizeof(struct mb64_custom_theme));
        strncpy(mb64_save.author, mb64_sram_configuration.author, MAX_USERNAME_SIZE);
    }

    if (mb64_save.version < MB64_VERSION) {
        append_puppyprint_log("Performing upgrade from version %d", mb64_save.version);
        mb64_perform_file_upgrade(&mb64_save, &mb64_tile_data, &mb64_object_data);
    }

    mb64_save.author[MAX_USERNAME_SIZE - 1] = '\0'; // memory leak prevention
    mb64_tile_count = mb64_save.tile_count;
    mb64_object_count = mb64_save.object_count;

    mb64_lopt_costume = mb64_save.costume;

    mb64_lopt_seq[0] = mb64_save.seq[0];
    mb64_lopt_seq[1] = mb64_save.seq[1];
    mb64_lopt_seq[2] = mb64_save.seq[2];
    mb64_lopt_envfx = mb64_save.envfx;
    mb64_lopt_theme = mb64_save.theme;
    mb64_lopt_bg = mb64_save.bg;

    mb64_lopt_boundary_mat = mb64_save.boundary_mat;
    mb64_lopt_boundary = mb64_save.boundary;
    mb64_lopt_boundary_height = mb64_save.boundary_height;
    mb64_lopt_coinstar = mb64_save.coinstar;
    mb64_lopt_size = mb64_save.size;
    mb64_lopt_waterlevel = mb64_save.waterlevel;
    mb64_lopt_secret = mb64_save.secret;

    switch (mb64_lopt_size) {
        case 0:
            mb64_grid_min = 16;
            mb64_grid_size = 32;
            break;
        case 1:
            mb64_grid_min = 8;
            mb64_grid_size = 48;
            break;
        case 2:
            mb64_grid_min = 0;
            mb64_grid_size = 64;
            break;
    }

    mb64_lopt_game = mb64_save.game;

    //copy toolbar
    bcopy(&mb64_save.toolbar,&mb64_toolbar,sizeof(mb64_toolbar));
    bcopy(&mb64_save.toolbar_params,&mb64_toolbar_params,sizeof(mb64_toolbar_params));

    // copy custom theme
    bcopy(&mb64_save.custom_theme,&mb64_curr_custom_theme,sizeof(struct mb64_custom_theme));
    update_custom_theme();

    u32 oldIndex = 0;
    bzero(&mb64_tile_data_indices,sizeof(mb64_tile_data_indices));
    // Load tiles and build index list. Assume all tiles are in order
    for (int i = 0; i < mb64_tile_count; i++) {
        //bcopy(&mb64_save.tiles[i],&mb64_tile_data[i],sizeof(mb64_tile_data[i]));
        u32 curIndex = get_tiletype_index(mb64_tile_data[i].type, mb64_tile_data[i].mat);

        if (curIndex != oldIndex) {
            // These tiles do not exist in the level so fill in the indices
            mb64_tile_data_indices[oldIndex + 1] = i;
            for (u32 j = oldIndex + 1; j < curIndex; j++) {
                mb64_tile_data_indices[j + 1] = mb64_tile_data_indices[j];
            }
            oldIndex = curIndex;
        }

        s8 pos[3];
        vec3_set(pos, mb64_tile_data[i].x, mb64_tile_data[i].y, mb64_tile_data[i].z);

        place_terrain_data(pos, mb64_tile_data[i].type, mb64_tile_data[i].rot, mb64_tile_data[i].mat);
        get_grid_tile(pos)->waterlogged = mb64_tile_data[i].waterlogged;
    }
    // Fill in remaining indices that were unused
    for (u32 i = oldIndex + 1; i < ARRAY_COUNT(mb64_tile_data_indices); i++) {
        mb64_tile_data_indices[i] = mb64_tile_count;
    }

    init_trajectories();
    init_toolbox();

    mb64_min_coord = (mb64_grid_min - 32) * TILE_SIZE;
    mb64_max_coord = (mb64_grid_min + mb64_grid_size - 32) * TILE_SIZE;
    if (!(mb64_curr_boundary & MB64_BOUNDARY_OUTER_FLOOR)) {
        mb64_min_coord -= 8*TILE_SIZE;
        mb64_max_coord += 8*TILE_SIZE;
    }

    if (!fresh) {
        update_painting();
    }
}
