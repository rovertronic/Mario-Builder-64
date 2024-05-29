// These can be updated to legacy structs whenever the memory layout changes.
#define Version_1_0_Save struct mb64_level_save_header
#define Version_1_0_Obj struct mb64_obj

// In the future we can have a lot of helper functions to assist with version reordering

void compat_upgrade_1_0_to_1_1(Version_1_0_Save *save, UNUSED void *tile_data, Version_1_0_Obj *obj_data) {
    append_puppyprint_log("Upgrading save file from version 1.0 to 1.1");
    for (s32 i = 0; i < save->object_count; i++) {
        if (obj_data[i].type == 92) { // 1.0 ID - Conveyor
            obj_data[i].bparam = 1; // Set BParam to 1 for full block conveyor
        }
    }
}


void mb64_perform_file_upgrade(struct mb64_level_save_header *save, void *tile_data, void *obj_data) {
    if (save->version < 1) {
        compat_upgrade_1_0_to_1_1(save, tile_data, obj_data);
        save->version = 1;
    }
    // more fields can be added in later updates...
}
