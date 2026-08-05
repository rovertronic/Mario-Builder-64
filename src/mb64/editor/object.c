#include "object.h"
#include "main.h"

#include "grid.h"
#include "mb64/gfx/gfx.h"
#include "trajectory.h"
#include "display_funcs.h"
#include "mb64/menu/misc.h"

#include "behavior_data.h"
#include "game/object_list_processor.h"
#include "game/spawn_object.h"
#include "game/object_helpers.h"
#include "audio/external.h"

struct mb64_obj mb64_object_data[MB64_MAX_OBJS];
u16 mb64_object_count = 0;
u16 mb64_object_limit_count = 0;
u16 mb64_total_coin_count = 0;

struct ExclamationBoxContents *mb64_exclamation_box_contents;

s32 mb64_count_stars(void) {
    s32 numStars = 0;
    for (s32 i = 0; i < mb64_object_count; i++) {
        if (mb64_object_type_list[mb64_object_data[i].type].flags & OBJ_TYPE_STAR) {
            numStars++;
        }
        if (mb64_object_data[i].imbue == IMBUE_STAR) {
            numStars++;
        }
    }
    return numStars;
}

void bhv_preview_object_init(void) {
    if (!o->oPreviewObjDisplayFunc) return;
    ((DisplayFunc)o->oPreviewObjDisplayFunc)(MB64_DF_CONTEXT_INIT);
}
void bhv_preview_object_loop(void) {
    if (!o->oPreviewObjDisplayFunc) return;
    ((DisplayFunc)o->oPreviewObjDisplayFunc)(MB64_DF_CONTEXT_MAIN);
}

void play_place_sound(u32 soundBits) {
    play_sound(soundBits, gGlobalSoundSource);
}

s32 get_extra_objects(u32 id, s32 param) {
    if (id == OBJECT_TYPE_FIRE_SPINNER) {
        return (param + 2) * 2;
    }
    if (id == OBJECT_TYPE_COIN_FORMATION) {
        return (param <= 1 ? 5 : 8);
    }
    return mb64_object_type_list[id].numExtraObjects;
}

s32 object_sanity_check(void) {
    struct mb64_object_info *info = &mb64_object_type_list[mb64_id_selection];

    if (mb64_object_limit_count + get_extra_objects(mb64_id_selection, mb64_param_selection) >= MB64_MAX_OBJS) {
        show_error("Object limit reached! (max 512)");
        return FALSE;
    }

    if (info->flags & OBJ_TYPE_TRAJECTORY) {
        if (mb64_trajectories_used >= MB64_MAX_TRAJECTORIES) {
            show_error("Trajectory limit reached! (max 20)");
            return FALSE;
        }
    }

    if (info->flags & OBJ_TYPE_STAR) {
        s32 numStars = mb64_count_stars();
        if (numStars >= 63) {
            show_error("Star limit reached! (max 63)");
            return FALSE;
        }
    }

    if (mb64_id_selection == OBJECT_TYPE_RED_COIN_STAR) {
        for (u32 i = 0; i < mb64_object_count; i++) {
            if (mb64_object_data[i].type == OBJECT_TYPE_RED_COIN_STAR) {
                show_error("Red Coin Star already placed!");
                return FALSE;
            }
        }
    }
    if (mb64_id_selection == OBJECT_TYPE_TRIGGER_STAR) {
        for (u32 i = 0; i < mb64_object_count; i++) {
            if (mb64_object_data[i].type == OBJECT_TYPE_TRIGGER_STAR) {
                show_error("Star Trigger star already placed!");
                return FALSE;
            }
        }
    }

    return TRUE;
}

struct Object *get_spawn_preview_object(void) {
    uintptr_t *behaviorAddr = segmented_to_virtual(bhvPreviewObject);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *obj = (struct Object *) listHead->next;

    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr
            && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED
            && obj != o
        ) {
            if (obj->header.gfx.sharedChild == gLoadedGraphNodes[MODEL_SPAWN]) {
                return obj;
            }
        }

        obj = (struct Object *) obj->header.next;
    }

    return NULL;
}

u32 can_place(s8 pos[3], u32 occupyFlags) {
    u32 type = get_grid_tile(pos)->type;
    if (type != TILE_TYPE_EMPTY && type != TILE_TYPE_WATER) {
        u32 tileFlags = get_tile_occupy_flags(type);
        if (tileFlags & occupyFlags) return FALSE;
    }
    for (u32 i = 0; i < mb64_object_count; i++) {
        struct mb64_obj *obj = &mb64_object_data[i];
        if (obj->x == pos[0] && obj->y == pos[1] && obj->z == pos[2]) {
            u32 objFlags = mb64_object_type_list[obj->type].occupy;
            if (obj->type == OBJECT_TYPE_COIN_FORMATION) {
                if (obj->bparam == 2) objFlags = OBJ_OCCUPY_OUTER;
            }

            if (objFlags & occupyFlags) return FALSE;
        }
    }
    return TRUE;
}

u32 can_place_tile(s8 pos[3]) {
    u32 type = get_grid_tile(pos)->type;
    if (type != TILE_TYPE_EMPTY && type != TILE_TYPE_WATER) return FALSE;

    u32 flags = get_tile_occupy_flags(mb64_id_selection);
    return can_place(pos, flags);
}

u32 can_place_object(s8 pos[3]) {
    u32 flags = mb64_object_type_list[mb64_id_selection].occupy;
    if (mb64_id_selection == OBJECT_TYPE_COIN_FORMATION) {
        if (mb64_param_selection == 2) flags = OBJ_OCCUPY_OUTER;
    } else if (mb64_id_selection == OBJECT_TYPE_TRIGGER) {
        return FALSE;
    }
    return can_place(pos, flags);
}

struct Object *spawn_preview_object(s8 pos[3], s32 rot, s32 param, struct mb64_object_info *info, const BehaviorScript *script) {
    struct Object *preview_object = spawn_object(gMarioObject, info->model_id, script);
    preview_object->oPosX = GRID_TO_POS(pos[0]);
    preview_object->oPosY = GRID_TO_POS(pos[1]) - TILE_SIZE/2 + info->y_offset;
    preview_object->oPosZ = GRID_TO_POS(pos[2]);
    preview_object->oFaceAngleYaw = rot*0x4000;
    preview_object->oBehParams2ndByte = param;
    preview_object->oBehParams = (param << 16);
    preview_object->oPreviewObjDisplayFunc = info->disp_func;
    preview_object->oOpacity = 255;
    obj_scale(preview_object, info->scale);
    if (info->flags & OBJ_TYPE_BILLBOARD) {
        preview_object->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
    }
    if (info->anim) {
        preview_object->oAnimations = (struct Animation **)info->anim;
        obj_init_animation(preview_object,0);
        preview_object->header.gfx.animInfo.animAccel = 0.0f;
    }
    if ((info->flags & OBJ_TYPE_TRAJECTORY)
        && (script != bhvCurrPreviewObject)
        && (info->behavior != bhvLoopingPlatform)) {
        rotate_obj_toward_trajectory_angle(preview_object,param);
    }
    return preview_object;
}

void unload_all_preview_objs(void) {
    uintptr_t *behaviorAddr = segmented_to_virtual(bhvPreviewObject);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *obj = (struct Object *) listHead->next;

    while (obj != (struct Object *) listHead) {
        struct Object *nextobj = (struct Object *) obj->header.next;
        if (obj->behavior == behaviorAddr) {
            unload_object(obj);
        }
        obj = nextobj;
    }
}

void generate_object_preview(void) {
    s32 totalCoins = 0;
    s32 curExtraCoins = 0;
    s32 doubleCoins = FALSE;
    mb64_object_limit_count = 0;

    unload_all_preview_objs();

    for(u32 i = 0; i < mb64_object_count; i++){
        if (gFreeObjectList.next == NULL) break;
        s32 curType = mb64_object_data[i].type;
        struct mb64_object_info *info = &mb64_object_type_list[curType];
        s32 param = mb64_object_data[i].bparam;

        s8 pos[3];
        vec3_set(pos, mb64_object_data[i].x, mb64_object_data[i].y, mb64_object_data[i].z);
        curExtraCoins = 0;

        spawn_preview_object(pos, mb64_object_data[i].rot, param, info, bhvPreviewObject);
        curExtraCoins += info->numCoins;
        if (curType == OBJECT_TYPE_EXCL_BOX) {
            curExtraCoins += mb64_exclamation_box_contents[param].numCoins;
        }
        if (curType == OBJECT_TYPE_BADGE && param == 8) {
            doubleCoins = TRUE;
        }

        s32 extraObjs = get_extra_objects(curType, param);
        if (curType == OBJECT_TYPE_COIN_FORMATION) {
            curExtraCoins += extraObjs;
        }

        s32 curImbue = mb64_object_data[i].imbue;
        if (curImbue != IMBUE_NONE) {
            int badgeid = 0;
            if (curImbue >= IMBUE_BADGE_BASE) {
                badgeid = curImbue - IMBUE_BADGE_BASE;
                curImbue = IMBUE_BADGE_BASE;
            }

            struct Object * imbue_marker = spawn_object(gMarioObject,imbue_table[curImbue].model,bhvPreviewObject);
            imbue_marker->oBehParams2ndByte = badgeid;
            imbue_marker->oExtraVariable1 = imbue_table[curImbue].color;
            imbue_marker->oPreviewObjDisplayFunc = df_hide_during_screenshot;
            imbue_marker->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
            imbue_marker->oPosX = GRID_TO_POS(pos[0]);
            imbue_marker->oPosY = GRID_TO_POS(pos[1]);
            imbue_marker->oPosZ = GRID_TO_POS(pos[2]);
            mb64_object_limit_count ++;
            curExtraCoins = imbue_table[curImbue].coins;
            if (curType == OBJECT_TYPE_SHOWRUNNER) {
                curExtraCoins += info->numCoins;
            }
        }

        mb64_object_limit_count += extraObjs + 1;
        totalCoins += curExtraCoins;
    }
    if (doubleCoins) totalCoins *= 2;

    u32 length = MIN(totalCoins / 20, 50);
    mb64_lopt_coinstar_max = length;

    if (mb64_lopt_coinstar > length) {
        mb64_lopt_coinstar = length;
    }
    mb64_total_coin_count = totalCoins;

    generate_trajectory_gfx();
}

void generate_objects_to_level(void) {
    struct Object *obj;
    u32 i;
    mb64_play_stars_max = 0;
    for(i=0;i<mb64_object_count;i++){
        struct mb64_object_info *info = &mb64_object_type_list[mb64_object_data[i].type];
        s32 param = mb64_object_data[i].bparam;
        if (info->behavior == NULL) {
            continue;
        }

        obj = spawn_object(gMarioObject, info->model_id, info->behavior);
        obj->oPosX = GRID_TO_POS(mb64_object_data[i].x);
        obj->oPosY = GRID_TO_POS(mb64_object_data[i].y) - TILE_SIZE/2 + info->y_offset;
        obj->oPosZ = GRID_TO_POS(mb64_object_data[i].z);
        obj->oFaceAngleYaw = mb64_object_data[i].rot*0x4000;
        obj->oMoveAngleYaw = mb64_object_data[i].rot*0x4000;
        obj->oBehParams2ndByte = param;
        obj->oBehParams = (param << 16);
        obj->oImbue = mb64_object_data[i].imbue;

        if ((info->flags & OBJ_TYPE_STAR)||(mb64_object_data[i].imbue == IMBUE_STAR)) {
            if (mb64_play_stars_max < 63) {
                obj->oBehParams = ((mb64_play_stars_max << 24)|(o->oBehParams2ndByte << 16));
                mb64_play_stars_max++;
            }
        }
    }
    if (mb64_lopt_coinstar > 0) mb64_play_stars_max++;
}

void delete_object(s32 index) {
    if (mb64_object_type_list[mb64_object_data[index].type].flags & OBJ_TYPE_TRAJECTORY) {
        remove_trajectory(mb64_object_data[index].bparam);
    }

    mb64_object_count--;
    for (u32 i = index; i < mb64_object_count; i++) {
        mb64_object_data[i] = mb64_object_data[i+1];
    }
    generate_object_preview();
}

void place_number_spawner_check(s8 pos[3], s32 spawnerType, s32 objType, s32 objImbue) {
    s32 objectCount = 0;
    s32 hasSpawner = FALSE;
    for (s32 i = 0; i < mb64_object_count; i++) {
        if (mb64_object_data[i].type == spawnerType) {
            hasSpawner = TRUE;
        } else if ((mb64_object_data[i].type == objType) ||
                    (mb64_object_data[i].imbue == objImbue)) {
            objectCount++;
        }
    }
    if (hasSpawner) df_spawn_number(pos, objectCount);
}

void should_spawn_place_number(s8 pos[3]) {
    if (mb64_id_selection == OBJECT_TYPE_RED_COIN) {
        place_number_spawner_check(pos, OBJECT_TYPE_RED_COIN_STAR, OBJECT_TYPE_RED_COIN, IMBUE_RED_COIN);
    } else if (mb64_id_selection == OBJECT_TYPE_TRIGGER) {
        place_number_spawner_check(pos, OBJECT_TYPE_TRIGGER_STAR, OBJECT_TYPE_TRIGGER, IMBUE_TRIGGER);
    } else if ((mb64_object_type_list[mb64_id_selection].flags & OBJ_TYPE_STAR)) {
        s32 starCount = 0;
        for (s32 i = 0; i < mb64_object_count; i++) {
            if ((mb64_object_type_list[mb64_object_data[i].type].flags & OBJ_TYPE_STAR) ||
                (mb64_object_data[i].imbue == IMBUE_STAR)){
                starCount++;
            }
        }
        df_spawn_number(pos, starCount);
    }
}

void place_object(s8 pos[3]) {
    if (mb64_id_selection == OBJECT_TYPE_MARIO_SPAWN) {
        for (int i = 0; i < mb64_object_count; i++) {
            if (mb64_object_data[i].type == OBJECT_TYPE_MARIO_SPAWN) {
                delete_object(i);
                break;
            }
        }
    }

    mb64_object_data[mb64_object_count].x = pos[0];
    mb64_object_data[mb64_object_count].y = pos[1];
    mb64_object_data[mb64_object_count].z = pos[2];
    mb64_object_data[mb64_object_count].type = mb64_id_selection;
    mb64_object_data[mb64_object_count].rot = mb64_rot_selection;
    mb64_object_data[mb64_object_count].imbue = IMBUE_NONE;

    if (mb64_object_type_list[mb64_id_selection].flags & OBJ_TYPE_TRAJECTORY) {
        begin_editing_trajectory();
    } else if (mb64_object_type_list[mb64_id_selection].flags & OBJ_TYPE_HAS_DIALOG) {
        mb64_object_data[mb64_object_count].bparam = 0;
    } else {
        mb64_object_data[mb64_object_count].bparam = mb64_param_selection;
    }

    if (mb64_id_selection == OBJECT_TYPE_MONEYBAG) {
        mb64_object_data[mb64_object_count].imbue = IMBUE_THREE_COINS;
    } else if (mb64_id_selection == OBJECT_TYPE_BOO) {
        mb64_object_data[mb64_object_count].imbue = IMBUE_ONE_COIN;
    }

    mb64_object_count++;

    play_place_sound(mb64_object_type_list[mb64_id_selection].soundBits);
    should_spawn_place_number(pos);
}

void imbue_action(void) {
    for (u32 i=0;i<mb64_object_count;i++) {
        s32 objType = mb64_object_data[i].type;
        s32 canbeImbued = (mb64_object_type_list[objType].flags & OBJ_TYPE_IMBUABLE);
        if (mb64_id_selection == OBJECT_TYPE_TRIGGER) {
            canbeImbued |= (mb64_object_type_list[objType].flags & OBJ_TYPE_IMBUABLE_TRIGGER);
        }
        if (canbeImbued && (mb64_object_data[i].x == mb64_cursor_pos[0])&&(mb64_object_data[i].y == mb64_cursor_pos[1])&&(mb64_object_data[i].z == mb64_cursor_pos[2])) {
            u8 imbue_success = FALSE;
            if (!object_sanity_check()) break;
            u8 oldImbue = mb64_object_data[i].imbue;

            switch(mb64_id_selection) {
                case OBJECT_TYPE_STAR:
                    ;s32 numStars = mb64_count_stars();
                    if (numStars >= 63) {
                        show_error("Star limit reached! (max 63)");
                        imbue_success = FALSE;
                        break;
                    }
                    mb64_object_data[i].imbue = IMBUE_STAR;
                    imbue_success = TRUE;
                    break;
                case OBJECT_TYPE_BLUE_COIN:
                    if (mb64_object_type_list[objType].flags & OBJ_TYPE_IMBUABLE_COINS) {
                        mb64_object_data[i].imbue = IMBUE_BLUE_COIN;
                        imbue_success = TRUE;
                    }
                    break;
                case OBJECT_TYPE_COIN:
                case OBJECT_TYPE_COIN_FORMATION:
                    if (mb64_object_type_list[objType].flags & OBJ_TYPE_IMBUABLE_COINS) {
                        if ((objType == OBJECT_TYPE_BBOX_NORMAL) ||
                            (objType == OBJECT_TYPE_RFBOX) ||
                            (objType == OBJECT_TYPE_MONEYBAG)) {
                            mb64_object_data[i].imbue = IMBUE_THREE_COINS;
                        } else {
                            mb64_object_data[i].imbue = IMBUE_ONE_COIN;
                        }
                        imbue_success = TRUE;
                    }
                    break;

                case OBJECT_TYPE_BUTTON:
                    mb64_object_data[i].imbue = IMBUE_RED_SWITCH;
                    if (mb64_param_selection == 1) {
                        mb64_object_data[i].imbue = IMBUE_BLUE_SWITCH;
                    }
                    imbue_success = TRUE;
                    break;

#define generic_imbue(obj, imbueType) \
                case obj: \
                    mb64_object_data[i].imbue = imbueType; \
                    imbue_success = TRUE; \
                    break;

                generic_imbue(OBJECT_TYPE_RED_COIN, IMBUE_RED_COIN);
                generic_imbue(OBJECT_TYPE_TRIGGER, IMBUE_TRIGGER);
                generic_imbue(OBJECT_TYPE_CROWBAR, IMBUE_CROWBAR);
                generic_imbue(OBJECT_TYPE_MASK, IMBUE_BULLET_MASK);
                generic_imbue(OBJECT_TYPE_GREEN_COIN, IMBUE_GREEN_COIN);
                generic_imbue(OBJECT_TYPE_BADGE, IMBUE_BADGE_BASE + mb64_param_selection);
            }

            if (imbue_success && (oldImbue != mb64_object_data[i].imbue)) {
                if (objType == OBJECT_TYPE_EXCL_BOX && mb64_object_data[i].bparam <= 3) {
                    mb64_object_data[i].bparam = 4;
                }

                play_place_sound(mb64_object_type_list[mb64_id_selection].soundBits);
                generate_object_preview();
                should_spawn_place_number(mb64_cursor_pos);
                return;
            }
            break;
        }
    }
    if (mb64_id_selection == OBJECT_TYPE_TRIGGER) {
        show_error("Star Triggers must be placed in other objects!");
    }
}

void place_thing_action(void) {
    if (mb64_place_mode == MB64_PM_TILE) {
        if (tile_sanity_check()) {
            if (mb64_id_selection == TILE_TYPE_WATER) {
                place_water(mb64_cursor_pos);
            } else if (can_place_tile(mb64_cursor_pos)) {
                place_tile(mb64_cursor_pos);
            } else {
                return;
            }
            generate_terrain_gfx();
        }
    } else if (mb64_place_mode == MB64_PM_OBJ) {
        if (can_place_object(mb64_cursor_pos)) {
            if (object_sanity_check()) {
                place_object(mb64_cursor_pos);
                generate_object_preview();
            }
        } else {
            imbue_action();
        }
    }
}

void delete_preview_object(void) {
    struct Object *previewObj = cur_obj_nearest_object_with_behavior(bhvCurrPreviewObject);
    while (previewObj) {
        unload_object(previewObj);
        previewObj = cur_obj_nearest_object_with_behavior(bhvCurrPreviewObject);
    }
}
