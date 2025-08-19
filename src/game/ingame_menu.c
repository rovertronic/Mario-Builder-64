#include <ultra64.h>

#include "actors/common1.h"
#include "area.h"
#include "audio/external.h"
#include "camera.h"
#include "course_table.h"
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
    Mtx *matrix2 = (Mtx *) alloc_display_list(sizeof(Mtx));

    if (matrix == NULL || matrix2 == NULL) {
        return;
    }

    guOrtho(matrix, 0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT, -10.0f, 10.0f, 1.0f);
    guMtxIdent(matrix2);

    // Should produce G_RDPHALF_1 in Fast3D
    gSPPerspNormalize(gDisplayListHead++, 0xFFFF);

    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(matrix), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(matrix2), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
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

u8 mb64_ascii_lut[] = {
    0,0,0,0,0,0,0,0, // 0 - 7
    0,0,0xFE,0,0,0,0,0, // 8 - 15
    0x54,0x55,0x57,0x58,0x56,0x59,0,0, // 16 - 23
    0,0,0,0,0,0,0,0, // 24 - 31
    0x9E, /* */ 0xF2, /*!*/ 0xF6, /*"*/ 0xFA, /*#*/
    0xF9, /*$*/ 0xF3, /*%*/ 0xE5, /*&*/ 0x3E, /*'*/
    0xE1, /*(*/ 0xE3, /*)*/ 0x00, /***/ 0xE8, /*+*/
    0x6F, /*,*/ 0x9F, /*-*/ 0x3F, /*.*/ 0x70, /*/*/
    0x00, /*0*/ 0x01, /*1*/ 0x02, /*2*/ 0x03, /*3*/
    0x04, /*4*/ 0x05, /*5*/ 0x06, /*6*/ 0x07, /*7*/
    0x08, /*8*/ 0x09, /*9*/ 0xE6, /*:*/ 0x00, /*;*/
    0x52, /*<*/ 0xE9, /*=*/ 0x53, /*>*/ 0xF4, /*?*/
    0xFD, /*@*/ 0x0A, /*A*/ 0x0B, /*B*/ 0x0C, /*C*/
    0x0D, /*D*/ 0x0E, /*E*/ 0x0F, /*F*/ 0x10, /*G*/
    0x11, /*H*/ 0x12, /*I*/ 0x13, /*J*/ 0x14, /*K*/
    0x15, /*L*/ 0x16, /*M*/ 0x17, /*N*/ 0x18, /*O*/
    0x19, /*P*/ 0x1A, /*Q*/ 0x1B, /*R*/ 0x1C, /*S*/
    0x1D, /*T*/ 0x1E, /*U*/ 0x1F, /*V*/ 0x20, /*W*/
    0x21, /*X*/ 0x22, /*Y*/ 0x23, /*Z*/ 0x00, /*[*/
    0x00, /*\*/ 0x00, /*]*/ 0x50, /*^*/ 0xE7, /*_*/
    0x00, /*`*/ 0x24, /*a*/ 0x25, /*b*/ 0x26, /*c*/
    0x27, /*d*/ 0x28, /*e*/ 0x29, /*f*/ 0x2A, /*g*/
    0x2B, /*h*/ 0x2C, /*i*/ 0x2D, /*j*/ 0x2E, /*k*/
    0x2F, /*l*/ 0x30, /*m*/ 0x31, /*n*/ 0x32, /*o*/
    0x33, /*p*/ 0x34, /*q*/ 0x35, /*r*/ 0x36, /*s*/
    0x37, /*t*/ 0x38, /*u*/ 0x39, /*v*/ 0x3A, /*w*/
    0x3B, /*x*/ 0x3C, /*y*/ 0x3D, /*z*/ 0x00, /*{*/
    0x51, /*|*/ 0x00, /*}*/ 0x00, /*~*/
};

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
