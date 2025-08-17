#include <ultra64.h>

#include "actors/common1.h"
#include "area.h"
#include "audio/external.h"
#include "camera.h"
#include "course_table.h"
#include "dialog_ids.h"
#include "engine/math_util.h"
#include "eu_translation.h"
#include "segment_symbols.h"
#include "game_init.h"
#include "gfx_dimensions.h"
#include "ingame_menu.h"
#include "level_update.h"
#include "memory.h"
#include "print.h"
#include "save_file.h"
#include "segment2.h"
#include "segment7.h"
#include "seq_ids.h"
#include "sm64.h"
#include "text_strings.h"
#include "types.h"
#include "config.h"
#include "puppycam2.h"
#include "main.h"
#include "puppycamold.h"
#include "src/game/mario_misc.h"
#include "actors/group0.h"
#include "actors/group14.h"
#include "level_update.h"
#include "hud.h"
#include "rendering_graph_node.h"
#include "mb64/main.h"

s8 tab_index = 0;
u16 menu_sintimer = 0;
s8 mindex = 0;

u8 letgo = FALSE;

f32 _spread;

Gfx *bicon_table[] = {
    b0_Plane_001_mesh,
    b1_Plane_001_mesh,
    b2_Plane_001_mesh,
    b3_Plane_001_mesh,
    b4_Plane_001_mesh,
    b5_Plane_001_mesh,
    b6_Plane_001_mesh,
    b7_Plane_001_mesh,
    b8_Plane_001_mesh,
    b9_Plane_001_mesh,
    b10_Plane_001_mesh,
    b12_Plane_001_mesh,
    b13_Plane_001_mesh,
    b14_Plane_001_mesh,
    b15_Plane_001_mesh,
    b16_Plane_001_mesh,
    b17_Plane_001_mesh,
    b18_Plane_001_mesh,
    b19_Plane_001_mesh,
    b20_Plane_001_mesh,
    b21_Plane_001_mesh,
    b22_Plane_001_mesh,
    b23_Plane_mesh
};

Gfx *geo_badge_material(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    Gfx *dlStart, *dlHead;
    struct Object *obj;
    struct GraphNodeGenerated *currentGraphNode;

    currentGraphNode = (struct GraphNodeGenerated *)node;

    if (callContext == GEO_CONTEXT_RENDER) {
        obj = (struct Object *) gCurGraphNodeObject;
        currentGraphNode->fnNode.node.flags = (currentGraphNode->fnNode.node.flags & 0xFF) | (LAYER_ALPHA << 8);

        dlHead = alloc_display_list(sizeof(Gfx) * (4));
        dlStart = dlHead;
        if (obj_get_model_id(obj) == MODEL_MAKER_IMBUE_BADGE) {
            gSPGeometryMode(dlHead++, G_ZBUFFER, 0);
        }
        gSPDisplayList(dlHead++,bicon_table[obj->oBehParams2ndByte]);
        gSPGeometryMode(dlHead++, 0, G_ZBUFFER);
        gSPEndDisplayList(dlHead++);
        return dlStart;
    }
    return NULL;
}

Gfx *geo_imbue_marker_color(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    Gfx *dlStart, *dlHead;
    struct Object *obj;
    struct GraphNodeGenerated *currentGraphNode;

    currentGraphNode = (struct GraphNodeGenerated *)node;

    if (callContext == GEO_CONTEXT_RENDER) {
        obj = (struct Object *) gCurGraphNodeObject;
        currentGraphNode->fnNode.node.flags = (currentGraphNode->fnNode.node.flags & 0xFF) | (LAYER_TRANSPARENT_INTER << 8);

        dlHead = alloc_display_list(sizeof(Gfx) * (2));
        dlStart = dlHead;
        u32 col = obj->oExtraVariable1;
        gDPSetPrimColor(dlHead++, 0,0,(col >> 24),(col >> 16) & 0xFF,(col >> 8) & 0xFF, col & 0xFF);
        gSPEndDisplayList(dlHead++);
        return dlStart;
    }
    return NULL;
}

s16 gRedCoinsCollected = 0;
s16 gRedCoinsTotal = 0;
s16 gStarTriggersCollected = 0;
s16 gStarTriggersTotal = 0;


u8 gDialogCharWidths[256] = { // TODO: Is there a way to auto generate this?
    7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  6,  6,  6,  6,  6,  6,
    6,  7,  4,  6,  6,  5,  6,  6,  6,  6,  7,  6,  6,  6,  6,  6,
    6,  6,  6,  6,  5,  5,  5,  5,  5,  6,  6,  5,  2,  5,  5,  4,
    6,  5,  5,  5,  5,  5,  5,  5,  5,  6,  6,  6,  6,  5,  3,  3,
    8,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    8,  8,  8,  8,  7,  7,  7,  7,  7,  7,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,
    8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  5,  6,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    7,  4,  8,  4,  9,  7,  3,  8,  6,  6,  0,  0,  0,  0,  0,  0,
    0,  0,  4,  8,  7,  6,  6,  6,  0,  9,  9,  7,  4,  9,  0,  0
};

void display_icon(Gfx* dl, int x, int y) {
    Mtx *mtx;

    mtx = alloc_display_list(sizeof(Mtx));

    if (mtx == NULL) {
        return;
    }

    guTranslate(mtx, x,y, 0);
    gDPSetRenderMode(gDisplayListHead++,G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx++),G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);

        gSPDisplayList(gDisplayListHead++, dl);

    gSPPopMatrix(gDisplayListHead++, 0);
}


void create_dl_identity_matrix(void) {
    Mtx *matrix = (Mtx *) alloc_display_list(sizeof(Mtx));

    if (matrix == NULL) {
        return;
    }

    matrix->m[0][0] = 0x00010000;    matrix->m[1][0] = 0x00000000;    matrix->m[2][0] = 0x00000000;    matrix->m[3][0] = 0x00000000;
    matrix->m[0][1] = 0x00000000;    matrix->m[1][1] = 0x00010000;    matrix->m[2][1] = 0x00000000;    matrix->m[3][1] = 0x00000000;
    matrix->m[0][2] = 0x00000001;    matrix->m[1][2] = 0x00000000;    matrix->m[2][2] = 0x00000000;    matrix->m[3][2] = 0x00000000;
    matrix->m[0][3] = 0x00000000;    matrix->m[1][3] = 0x00000001;    matrix->m[2][3] = 0x00000000;    matrix->m[3][3] = 0x00000000;

    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(matrix), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(matrix), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
}

void create_dl_translation_matrix(s8 pushOp, f32 x, f32 y, f32 z) {
    Mtx *matrix = (Mtx *) alloc_display_list(sizeof(Mtx));

    if (matrix == NULL) {
        return;
    }

    guTranslate(matrix, x, y, z);

    if (pushOp == MENU_MTX_PUSH) {
        gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(matrix), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    }

    if (pushOp == MENU_MTX_NOPUSH) {
        gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(matrix), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    }
}

void create_dl_scale_matrix(s8 pushOp, f32 x, f32 y, f32 z) {
    Mtx *matrix = (Mtx *) alloc_display_list(sizeof(Mtx));

    if (matrix == NULL) {
        return;
    }

    guScale(matrix, x, y, z);

    if (pushOp == MENU_MTX_PUSH) {
        gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(matrix), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    }

    if (pushOp == MENU_MTX_NOPUSH) {
        gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(matrix), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    }
}

void create_dl_ortho_matrix(void) {
    Mtx *matrix = (Mtx *) alloc_display_list(sizeof(Mtx));

    if (matrix == NULL) {
        return;
    }

    create_dl_identity_matrix();

    guOrtho(matrix, 0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT, -10.0f, 10.0f, 1.0f);

    // Should produce G_RDPHALF_1 in Fast3D
    gSPPerspNormalize(gDisplayListHead++, 0xFFFF);

    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(matrix), G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
}

void render_generic_char(u8 c) {
    void **fontLUT = segmented_to_virtual(main_font_lut);
    void *packedTexture = segmented_to_virtual(fontLUT[c]);

    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, VIRTUAL_TO_PHYSICAL(packedTexture));

    gSPDisplayList(gDisplayListHead++, dl_ia_text_tex_settings);
}

#define MAX_STRING_WIDTH 16
#define CHAR_WIDTH_SPACE (f32)(gDialogCharWidths[DIALOG_CHAR_SPACE])
#define CHAR_WIDTH_DEFAULT (f32)(gDialogCharWidths[str[strPos]])

/**
 * Prints a generic white string.
 * In JP/EU a IA1 texture is used but in US a IA4 texture is used.
 */
void print_generic_string(s16 x, s16 y, const u8 *str) {

}

extern u8 mb64_ascii_lut[];
void print_generic_string_ascii(s16 x, s16 y, const char *str) {
    s32 strPos = 0;
    u8 lineNum = 1;

    create_dl_translation_matrix(MENU_MTX_PUSH, x, y, 0.0f);

    while (str[strPos] != 0) {
        switch(str[strPos]) {
            case ' ':
                create_dl_translation_matrix(MENU_MTX_NOPUSH, CHAR_WIDTH_SPACE, 0.0f, 0.0f);
            break;
            case '\n':
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                create_dl_translation_matrix(MENU_MTX_PUSH, x, y - (lineNum * MAX_STRING_WIDTH), 0.0f);
                lineNum++;
            break;
            default:
                render_generic_char(mb64_ascii_lut[(u8)str[strPos]]);
                create_dl_translation_matrix(MENU_MTX_NOPUSH, gDialogCharWidths[mb64_ascii_lut[(u8)str[strPos]]], 0.0f, 0.0f);
            break;
        }
        strPos++;
    }

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void print_generic_string_ascii_nofileext(s16 x, s16 y, const char *str) {
    // This function assumes that the string has the correct file extension
    char buf[MAX_FILE_NAME_SIZE];
    strcpy(buf, str);
    buf[strlen(str) - 5] = '\0';
    print_generic_string_ascii(x, y, buf);
}

s32 get_string_width_ascii(char *str) {
    s16 strPos = 0;
    s16 width = 0;

    while (str[strPos] != 0) {
        width += gDialogCharWidths[mb64_ascii_lut[(u8)str[strPos]]];
        strPos++;
    }
    return width;
}

void print_hud_string_ascii(s16 x, s16 y, char *str) {
    s32 strPos = 0;
    void **hudLUT = segmented_to_virtual(main_hud_lut);
    y = SCREEN_HEIGHT - y;
    int kerning;

    while (str[strPos] != 0) {
        kerning = 0;
        switch (str[strPos]) {
            case ' ':
                kerning = 8;
                break;
            case '#':
            case '@':
            case '&':
            case '*':
                kerning += 4;
                // fallthrough
            default:
                gDPPipeSync(gDisplayListHead++);
                gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hudLUT[str[strPos] - ' ']);
                gSPDisplayList(gDisplayListHead++, dl_rgba16_load_tex_block);
                gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + 16) << 2,
                                    (y + 16) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

                kerning += 12;
        }
        x += kerning;
        strPos++;
    }
}

s32 get_hud_string_width_ascii(char *str) {
    s32 width = 0;
    s16 strPos = 0;

    while (str[strPos] != 0) {
        switch (str[strPos]) {
            case ' ':
                width += 8;
                break;
            case '#':
            case '@':
            case '&':
            case '*':
                width += 4;
                // fallthrough
            default:
                width += 12;
        }
        strPos++;
    }
    return width;
}

s32 get_string_width(u8 *str) {
    s16 strPos = 0;
    s16 width = 0;

    while (str[strPos] != DIALOG_CHAR_TERMINATOR) {
        width += gDialogCharWidths[str[strPos]];
        strPos++;
    }
    return width;
}

void reset_red_coins_collected(void) {
    gRedCoinsCollected = 0;
    gRedCoinsTotal = 0;
    gStarTriggersCollected = 0;
    gStarTriggersTotal = 0;
}

void render_menus_and_dialogs(void) {
    gMarioState->GlobalPaused = TRUE;
    if (sCurrPlayMode == PLAY_MODE_PAUSED) {
        gMarioState->GlobalPaused = TRUE;
    }

    render_menu();
}
