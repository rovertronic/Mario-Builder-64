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
#include "rovent.h"
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
    //b11_Plane_001_mesh,
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

u8 number_text[15];

u8 b1[] = {BADGE1};
u8 b2[] = {BADGE2};
u8 b3[] = {BADGE3};
u8 b4[] = {BADGE4};
u8 b5[] = {BADGE5};
u8 b6[] = {BADGE6};
u8 b7[] = {BADGE7};
u8 b8[] = {BADGE8};
u8 b9[] = {BADGE9};
u8 b10[] = {BADGE10};
u8 b11[] = {BADGE11};
// u8 b12[] = {BADGE12};
u8 b13[] = {BADGE13};
u8 b14[] = {BADGE14};
u8 b15[] = {BADGE15};
u8 b16[] = {BADGE16};
u8 b17[] = {BADGE17};
u8 b18[] = {BADGE18};
u8 b19[] = {BADGE19};
u8 b20[] = {BADGE20};
u8 b21[] = {BADGE21};
u8 b22[] = {BADGE22};
u8 b23[] = {BADGE23};
u8 b24[] = {BADGE24};

u8 *badgenames[] = { b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,
b13,b14,b15,b16,b17,b18,b19,b20,b21,b22,b23,b24
};

u8 b1d[] = {BADGE1D};
u8 b2d[] = {BADGE2D};
u8 b3d[] = {BADGE3D};
u8 b4d[] = {BADGE4D};
u8 b5d[] = {BADGE5D};
u8 b6d[] = {BADGE6D};
u8 b7d[] = {BADGE7D};
u8 b8d[] = {BADGE8D};
u8 b9d[] = {BADGE9D};
u8 b10d[] = {BADGE10D};
u8 b11d[] = {BADGE11D};
// u8 b12d[] = {BADGE12D};
u8 b13d[] = {BADGE13D};
u8 b14d[] = {BADGE14D};
u8 b15d[] = {BADGE15D};
u8 b16d[] = {BADGE16D};
u8 b17d[] = {BADGE17D};
u8 b18d[] = {BADGE18D};
u8 b19d[] = {BADGE19D};
u8 b20d[] = {BADGE20D};
u8 b21d[] = {BADGE21D};
u8 b22d[] = {BADGE22D};
u8 b23d[] = {BADGE23D};
u8 b24d[] = {BADGE24D};
u8 *badgedescs[] = { b1d,b2d,b3d,b4d,b5d,b6d,b7d,b8d,b9d,b10d,b11d,
b13d,b14d,b15d,b16d,b17d,b18d,b19d,b20d,b21d,b22d,b23d,b24d };

u16 gDialogColorFadeTimer;
s8 gLastDialogLineNum;
s32 gDialogVariable;
u16 gDialogTextAlpha;
s16 gCutsceneMsgXOffset;
s16 gCutsceneMsgYOffset;
s16 gRedCoinsCollected = 0;
s16 gRedCoinsTotal = 0;
s16 gStarTriggersCollected = 0;
s16 gStarTriggersTotal = 0;

s16 gInGameLanguage = LANGUAGE_ENGLISH;
s16 gLoadedLanguage = LANGUAGE_ENGLISH;

void *languageTable[][3] = {
    {&seg2_dialog_table, &seg2_course_name_table, &seg2_act_name_table}, // In EU, this is just mirroring English.
#if MULTILANG
    {&dialog_table_eu_en, &course_name_table_eu_en, &act_name_table_eu_en},
    {&dialog_table_eu_fr, &course_name_table_eu_fr, &act_name_table_eu_fr},
    {&dialog_table_eu_de, &course_name_table_eu_de, &act_name_table_eu_de},
#endif
};

extern u8 gLastCompletedCourseNum;
extern u8 gLastCompletedStarNum;

enum DialogBoxState {
    DIALOG_STATE_OPENING,
    DIALOG_STATE_VERTICAL,
    DIALOG_STATE_HORIZONTAL,
    DIALOG_STATE_CLOSING
};

enum DialogBoxPageState {
    DIALOG_PAGE_STATE_NONE,
    DIALOG_PAGE_STATE_SCROLL,
    DIALOG_PAGE_STATE_END
};

enum DialogBoxType {
    DIALOG_TYPE_ROTATE, // used in NPCs and level messages
    DIALOG_TYPE_ZOOM    // used in signposts and wall signs and etc
};

#define DEFAULT_DIALOG_BOX_ANGLE 90.0f
#define DEFAULT_DIALOG_BOX_SCALE 19.0f

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

s8 gDialogBoxState = DIALOG_STATE_OPENING;
f32 gDialogBoxOpenTimer = DEFAULT_DIALOG_BOX_ANGLE;
f32 gDialogBoxScale = DEFAULT_DIALOG_BOX_SCALE;
s16 gDialogScrollOffsetY = 0;
s8 gDialogBoxType = DIALOG_TYPE_ROTATE;
s16 gDialogID = DIALOG_NONE;
s16 gLastDialogPageStrPos = 0;
s16 gDialogTextPos = 0;
s8 gDialogLineNum = 1;
s8 gLastDialogResponse = 0;
u8 gMenuHoldKeyIndex = 0;
u8 gMenuHoldKeyTimer = 0;
s32 gDialogResponse = DIALOG_RESPONSE_NONE;

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

#ifndef GBI_FLOATS
    matrix->m[0][0] = 0x00010000;    matrix->m[1][0] = 0x00000000;    matrix->m[2][0] = 0x00000000;    matrix->m[3][0] = 0x00000000;
    matrix->m[0][1] = 0x00000000;    matrix->m[1][1] = 0x00010000;    matrix->m[2][1] = 0x00000000;    matrix->m[3][1] = 0x00000000;
    matrix->m[0][2] = 0x00000001;    matrix->m[1][2] = 0x00000000;    matrix->m[2][2] = 0x00000000;    matrix->m[3][2] = 0x00000000;
    matrix->m[0][3] = 0x00000000;    matrix->m[1][3] = 0x00000001;    matrix->m[2][3] = 0x00000000;    matrix->m[3][3] = 0x00000000;
#else
    guMtxIdent(matrix);
#endif

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

void create_dl_rotation_matrix(s8 pushOp, f32 a, f32 x, f32 y, f32 z) {
    Mtx *matrix = (Mtx *) alloc_display_list(sizeof(Mtx));

    if (matrix == NULL) {
        return;
    }

    guRotate(matrix, a, x, y, z);

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

// Unused
#if FALSE
static u8 *alloc_ia8_text_from_i1(u16 *in, s16 width, s16 height) {
    s32 inPos;
    u16 bitMask;
    u8 *out;
    s16 outPos = 0;

    out = (u8 *) alloc_display_list((u32) width * (u32) height);

    if (out == NULL) {
        return NULL;
    }

    for (inPos = 0; inPos < (width * height) / 16; inPos++) {
        bitMask = 0x8000;

        while (bitMask != 0) {
            if (in[inPos] & bitMask) {
                out[outPos] = 0xFF;
            } else {
                out[outPos] = 0x00;
            }

            bitMask /= 2;
            outPos++;
        }
    }

    return out;
}

void render_generic_char(u8 c) {
    void **fontLUT = segmented_to_virtual(main_font_lut);
    void *packedTexture = segmented_to_virtual(fontLUT[c]);
#if defined(VERSION_JP) || defined(VERSION_SH)
    void *unpackedTexture = alloc_ia8_text_from_i1(packedTexture, 8, 16);
#endif

#ifndef VERSION_EU
    gDPPipeSync(gDisplayListHead++);
#endif
#if defined(VERSION_JP) || defined(VERSION_SH)
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_IA, G_IM_SIZ_8b, 1, VIRTUAL_TO_PHYSICAL(unpackedTexture));
#else
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, VIRTUAL_TO_PHYSICAL(packedTexture));
#endif
    gSPDisplayList(gDisplayListHead++, dl_ia_text_tex_settings);
#ifdef VERSION_EU
    gSPTextureRectangleFlip(gDisplayListHead++, gDialogX << 2, (gDialogY - 16) << 2,
                            (gDialogX + 8) << 2, gDialogY << 2, G_TX_RENDERTILE, 8 << 6, 4 << 6, 1 << 10, 1 << 10);
#endif
}
#endif

Texture32 *alloc_ia4_tex_from_i1(Texture *in, s16 width, s16 height) {
    u32 size = (u32) width * (u32) height;
    s32 inPos;
    s16 outPos = 0;
    u8 bitMask;

    Texture *out = (Texture *) alloc_display_list(size);

    if (out == NULL) {
        return NULL;
    }

    for (inPos = 0; inPos < (width * height) / 4; inPos++) {
        bitMask = 0x80;

        while (bitMask != 0) {
            out[outPos] = (in[inPos] & bitMask) ? 0xF0 : 0x00;
            bitMask /= 2;
            out[outPos] = (in[inPos] & bitMask) ? out[outPos] + 0x0F : out[outPos];
            bitMask /= 2;
            outPos++;
        }
    }

    return (Texture32 *)out;
}

void render_generic_char(u8 c) {
    void **fontLUT = segmented_to_virtual(main_font_lut);
    void *packedTexture = segmented_to_virtual(fontLUT[c]);
#if MULTILANG
    void *unpackedTexture = alloc_ia4_tex_from_i1(packedTexture, 8, 8);

    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, VIRTUAL_TO_PHYSICAL(unpackedTexture));
#else
    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, VIRTUAL_TO_PHYSICAL(packedTexture));
#endif

    gSPDisplayList(gDisplayListHead++, dl_ia_text_tex_settings);
}


struct MultiTextEntry {
    u8 length;
    u8 str[4];
};

#define TEXT_THE_RAW ASCII_TO_DIALOG('t'), ASCII_TO_DIALOG('h'), ASCII_TO_DIALOG('e'), 0x00
#define TEXT_YOU_RAW ASCII_TO_DIALOG('y'), ASCII_TO_DIALOG('o'), ASCII_TO_DIALOG('u'), 0x00

enum MultiStringIDs { STRING_THE, STRING_YOU };

/*
 * Place the multi-text string according to the ID passed. (US, EU)
 * 0: 'the'
 * 1: 'you'
 */
void render_multi_text_string(s8 multiTextID) {
    s8 i;
    struct MultiTextEntry textLengths[2] = {
        { 3, { TEXT_THE_RAW } },
        { 3, { TEXT_YOU_RAW } },
    };

    for (i = 0; i < textLengths[multiTextID].length; i++) {
        render_generic_char(textLengths[multiTextID].str[i]);
        create_dl_translation_matrix(MENU_MTX_NOPUSH, (f32)(gDialogCharWidths[textLengths[multiTextID].str[i]]), 0.0f, 0.0f);
    }
}

#define MAX_STRING_WIDTH 16
#define CHAR_WIDTH_SPACE (f32)(gDialogCharWidths[DIALOG_CHAR_SPACE])
#define CHAR_WIDTH_DEFAULT (f32)(gDialogCharWidths[str[strPos]])

/**
 * Prints a generic white string.
 * In JP/EU a IA1 texture is used but in US a IA4 texture is used.
 */
void print_generic_string(s16 x, s16 y, const u8 *str) {
    s8 mark = DIALOG_MARK_NONE; // unused in EU
    s32 strPos = 0;
    u8 lineNum = 1;

    s16 colorLoop;
    ColorRGBA rgbaColors = { 0x00, 0x00, 0x00, 0x00 };
    u8 customColor = 0;
    u8 diffTmp     = 0;

    create_dl_translation_matrix(MENU_MTX_PUSH, x, y, 0.0f);

    while (str[strPos] != DIALOG_CHAR_TERMINATOR) {
        switch (str[strPos]) {
            case DIALOG_CHAR_COLOR:
                customColor = 1;
                strPos++;
                for (colorLoop = (strPos + 8); strPos < colorLoop; ++strPos) {
                    diffTmp = 0;
                    if ((str[strPos] >= 0x24)
                     && (str[strPos] <= 0x29)) {
                        diffTmp = 0x1A;
                    } else if (str[strPos] >= 0x10) {
                        customColor = 2;
                        strPos = (colorLoop - 8);
                        for (diffTmp = 0; diffTmp < 8; ++diffTmp) {
                            if (str[strPos + diffTmp] != 0x9F) {
                                break;
                            }
                        }
                        if (diffTmp == 8) {
                            strPos += diffTmp;
                        }
                        break;
                    }
                    if (((8 - (colorLoop - strPos)) % 2) == 0) {
                        rgbaColors[(8 - (colorLoop - strPos)) / 2] = (((str[strPos] - diffTmp) & 0x0F) << 4);
                    } else {
                        rgbaColors[(8 - (colorLoop - strPos)) / 2] += ((str[strPos] - diffTmp) & 0x0F);
                    }
                }
                strPos--;
                if (customColor == 1) {
                    gDPSetEnvColor(gDisplayListHead++, rgbaColors[0],
                                                    rgbaColors[1],
                                                    rgbaColors[2],
                                                    rgbaColors[3]);
                } else if (customColor == 2) {
                    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255); // TODO: Is it possible to retrieve the original color that was set before print_generic_string was called?
                    customColor = 0;
                }
                break;
            case DIALOG_CHAR_DAKUTEN:
                mark = DIALOG_MARK_DAKUTEN;
                break;
            case DIALOG_CHAR_PERIOD_OR_HANDAKUTEN:
                mark = DIALOG_MARK_HANDAKUTEN;
                break;
            case DIALOG_CHAR_NEWLINE:
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                create_dl_translation_matrix(MENU_MTX_PUSH, x, y - (lineNum * MAX_STRING_WIDTH), 0.0f);
                lineNum++;
                break;
            case DIALOG_CHAR_PERIOD:
                create_dl_translation_matrix(MENU_MTX_PUSH, -2.0f, -5.0f, 0.0f);
                render_generic_char(DIALOG_CHAR_PERIOD_OR_HANDAKUTEN);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                break;
            case DIALOG_CHAR_SLASH:
                create_dl_translation_matrix(MENU_MTX_NOPUSH, (f32)(gDialogCharWidths[DIALOG_CHAR_SPACE] * 2), 0.0f, 0.0f);
                break;
            case DIALOG_CHAR_MULTI_THE:
                render_multi_text_string(STRING_THE);
                break;
            case DIALOG_CHAR_MULTI_YOU:
                render_multi_text_string(STRING_YOU);
                break;
            case DIALOG_CHAR_SPACE:
                // create_dl_translation_matrix(MENU_MTX_NOPUSH, (f32)(gDialogCharWidths[DIALOG_CHAR_SPACE]), 0.0f, 0.0f);
                create_dl_translation_matrix(MENU_MTX_NOPUSH, CHAR_WIDTH_SPACE, 0.0f, 0.0f);
                break;
            default:
                render_generic_char(str[strPos]);
                if (mark != DIALOG_MARK_NONE) {
                    create_dl_translation_matrix(MENU_MTX_PUSH, 5.0f, 5.0f, 0.0f);
                    render_generic_char(DIALOG_CHAR_MARK_START + mark);
                    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                    mark = DIALOG_MARK_NONE;
                }

                create_dl_translation_matrix(MENU_MTX_NOPUSH, CHAR_WIDTH_DEFAULT, 0.0f, 0.0f);
                break;
        }

        strPos++;
    }

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
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


/**
 * Prints a hud string depending of the hud table list defined.
 */
void print_hud_lut_string(s8 hudLUT, s16 x, s16 y, const u8 *str) {
    s32 strPos = 0;
    void **hudLUT1 = segmented_to_virtual(menu_hud_lut); // Japanese Menu HUD Color font
    void **hudLUT2 = segmented_to_virtual(main_hud_lut); // 0-9 A-Z HUD Color Font
    u32 curX = x;
    u32 curY = y;

    u32 xStride; // X separation

    if (hudLUT == HUD_LUT_JPMENU) {
        xStride = 16;
    } else { // HUD_LUT_GLOBAL
        xStride = 12; //? Shindou uses this.
    }

    while (str[strPos] != GLOBAR_CHAR_TERMINATOR) {
        switch (str[strPos]) {
            case GLOBAL_CHAR_SPACE:
                curX += 8;
                break;
            default:
                gDPPipeSync(gDisplayListHead++);

                if (hudLUT == HUD_LUT_JPMENU) {
                    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hudLUT1[str[strPos]]);
                }

                if (hudLUT == HUD_LUT_GLOBAL) {
                    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hudLUT2[str[strPos]]);
                }

                gSPDisplayList(gDisplayListHead++, dl_rgba16_load_tex_block);
                gSPTextureRectangle(gDisplayListHead++, curX << 2, curY << 2, (curX + 16) << 2,
                                    (curY + 16) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

                curX += xStride;
        }
        strPos++;
    }
}


void print_menu_generic_string(s16 x, s16 y, const u8 *str) {
    UNUSED s8 mark = DIALOG_MARK_NONE; // unused in EU
    s32 strPos = 0;
    u32 curX = x;
    u32 curY = y;
    void **fontLUT = segmented_to_virtual(menu_font_lut);

    while (str[strPos] != DIALOG_CHAR_TERMINATOR) {
        switch (str[strPos]) {
            case DIALOG_CHAR_DAKUTEN:
                mark = DIALOG_MARK_DAKUTEN;
                break;
            case DIALOG_CHAR_PERIOD_OR_HANDAKUTEN:
                mark = DIALOG_MARK_HANDAKUTEN;
                break;
            case DIALOG_CHAR_SPACE:
                curX += 4;
                break;
            default:
                gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_IA, G_IM_SIZ_8b, 1, fontLUT[str[strPos]]);
                gDPLoadSync(gDisplayListHead++);
                gDPLoadBlock(gDisplayListHead++, G_TX_LOADTILE, 0, 0, 8 * 8 - 1, CALC_DXT(8, G_IM_SIZ_8b_BYTES));
                gSPTextureRectangle(gDisplayListHead++, curX << 2, curY << 2, (curX + 8) << 2,
                                    (curY + 8) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

                if (mark != DIALOG_MARK_NONE) {
                    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_IA, G_IM_SIZ_8b, 1, fontLUT[DIALOG_CHAR_MARK_START + mark]);
                    gDPLoadSync(gDisplayListHead++);
                    gDPLoadBlock(gDisplayListHead++, G_TX_LOADTILE, 0, 0, 8 * 8 - 1, CALC_DXT(8, G_IM_SIZ_8b_BYTES));
                    gSPTextureRectangle(gDisplayListHead++, (curX + 6) << 2, (curY - 7) << 2,
                                        (curX + 6 + 8) << 2, (curY - 7 + 8) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

                    mark = DIALOG_MARK_NONE;
                }
                curX += gDialogCharWidths[str[strPos]];
        }
        strPos++;
    }
}

void print_credits_string(s16 x, s16 y, const u8 *str) {
    s32 strPos = 0;
    void **fontLUT = segmented_to_virtual(main_credits_font_lut);
    u32 curX = x;
    u32 curY = y;

    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0,
                G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD);
    gDPTileSync(gDisplayListHead++);
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 0, G_TX_RENDERTILE, 0,
                G_TX_CLAMP, 3, G_TX_NOLOD, G_TX_CLAMP, 3, G_TX_NOLOD);
    gDPSetTileSize(gDisplayListHead++, G_TX_RENDERTILE, 0, 0, (8 - 1) << G_TEXTURE_IMAGE_FRAC, (8 - 1) << G_TEXTURE_IMAGE_FRAC);

    while (str[strPos] != GLOBAR_CHAR_TERMINATOR) {
        switch (str[strPos]) {
            case GLOBAL_CHAR_SPACE:
                curX += 4;
                break;
            default:
                gDPPipeSync(gDisplayListHead++);
                gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fontLUT[str[strPos]]);
                gDPLoadSync(gDisplayListHead++);
                gDPLoadBlock(gDisplayListHead++, G_TX_LOADTILE, 0, 0, 8 * 8 - 1, CALC_DXT(8, G_IM_SIZ_16b_BYTES));
                gSPTextureRectangle(gDisplayListHead++, curX << 2, curY << 2, (curX + 8) << 2,
                                    (curY + 8) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
                curX += 7;
                break;
        }
        strPos++;
    }
}

void handle_menu_scrolling(s8 scrollDirection, s8 *currentIndex, s8 minIndex, s8 maxIndex) {
    u8 index = 0;

    if (scrollDirection == MENU_SCROLL_VERTICAL) {
        if ((gPlayer1Controller->rawStickY >  60) || (gPlayer1Controller->buttonDown & (U_CBUTTONS | U_JPAD))) index++;
        if ((gPlayer1Controller->rawStickY < -60) || (gPlayer1Controller->buttonDown & (D_CBUTTONS | D_JPAD))) index += 2;
    } else if (scrollDirection == MENU_SCROLL_HORIZONTAL) {
        if ((gPlayer1Controller->rawStickX >  60) || (gPlayer1Controller->buttonDown & (R_CBUTTONS | R_JPAD))) index += 2;
        if ((gPlayer1Controller->rawStickX < -60) || (gPlayer1Controller->buttonDown & (L_CBUTTONS | L_JPAD))) index++;
    }

    if (((index ^ gMenuHoldKeyIndex) & index) == 2) {
        if (*currentIndex != maxIndex) {
            play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
            (*currentIndex)++;
        }
    }

    if (((index ^ gMenuHoldKeyIndex) & index) == 1) {
        if (*currentIndex != minIndex) {
            play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
            (*currentIndex)--;
        }
    }

    if (gMenuHoldKeyTimer == 10) {
        gMenuHoldKeyTimer = 8;
        gMenuHoldKeyIndex = 0;
    } else {
        gMenuHoldKeyTimer++;
        gMenuHoldKeyIndex = index;
    }

    if ((index & 3) == 0) {
        gMenuHoldKeyTimer = 0;
    }
}

s32 get_str_x_pos_from_center(s16 centerPos, u8 *str, UNUSED f32 scale) {
    s16 strPos = 0;
    f32 spacesWidth = 0.0f;

    while (str[strPos] != DIALOG_CHAR_TERMINATOR) {
        spacesWidth += gDialogCharWidths[str[strPos]];
        strPos++;
    }
    // return the x position of where the string starts as half the string's
    // length from the position of the provided center.
    return (s16)(centerPos - (s16)(spacesWidth / 2.0f));
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

u8 gHudSymCoin[] = { GLYPH_COIN, GLYPH_SPACE };
u8 gHudSymX[] = { GLYPH_MULTIPLY, GLYPH_SPACE };

void print_hud_my_score_coins(s32 useCourseCoinScore, s8 fileIndex, s8 courseIndex, s16 x, s16 y) {
    u8 strNumCoins[4];
    s16 numCoins;

    if (!useCourseCoinScore) {
        numCoins = (u16)(save_file_get_max_coin_score(courseIndex) & 0xFFFF);
    } else {
        numCoins = save_file_get_course_coin_score(fileIndex, courseIndex);
    }

    if (numCoins != 0) {
        print_hud_lut_string(HUD_LUT_GLOBAL, x +  0, y, gHudSymCoin);
        print_hud_lut_string(HUD_LUT_GLOBAL, x + 16, y, gHudSymX);
        int_to_str(numCoins, strNumCoins);
        print_hud_lut_string(HUD_LUT_GLOBAL, x + 32, y, strNumCoins);
    }
}

void print_hud_my_score_stars(s8 fileIndex, s8 courseIndex, s16 x, s16 y) {
    u8 strStarCount[4];
    u8 textSymStar[] = { GLYPH_STAR, GLYPH_SPACE };
    u8 textSymX[] = { GLYPH_MULTIPLY, GLYPH_SPACE };

    s16 starCount = save_file_get_course_star_count(fileIndex, courseIndex);

    if (starCount != 0) {
        print_hud_lut_string(HUD_LUT_GLOBAL, x +  0, y, textSymStar);
        print_hud_lut_string(HUD_LUT_GLOBAL, x + 16, y, textSymX);
        int_to_str(starCount, strStarCount);
        print_hud_lut_string(HUD_LUT_GLOBAL, x + 32, y, strStarCount);
    }
}

void int_to_str(s32 num, u8 *dst) {
    s32 digit[3];

    s8 pos = 0;

    if (num > 999) {
        dst[0] = 0x00;
        dst[1] = DIALOG_CHAR_TERMINATOR;
        return;
    }

    digit[0] = (num / 100);
    digit[1] = ((num - (digit[0] * 100)) / 10);
    digit[2] = ((num - (digit[0] * 100)) - (digit[1] * 10));

    if (digit[0] != 0) {
        dst[pos++] = digit[0];
    }

    if ((digit[1] != 0)
     || (digit[0] != 0)) {
        dst[pos++] = digit[1];
    }

    dst[pos++] = digit[2];
    dst[pos] = DIALOG_CHAR_TERMINATOR;
}

void int_to_str_spaces(s32 num, u8 *dst) {
    s32 digit1;
    s32 digit2;
    s32 digit3;

    s8 pos = 0;

    dst[0] = DIALOG_CHAR_SPACE;
    dst[1] = DIALOG_CHAR_SPACE;
    dst[2] = DIALOG_CHAR_SPACE;

    if (num > 999) {
        dst[0] = 0x00; dst[1] = DIALOG_CHAR_SPACE;
        return;
    }

    digit1 = num / 100;
    digit2 = (num - digit1 * 100) / 10;
    digit3 = (num - digit1 * 100) - (digit2 * 10);

    if (digit1 != 0) {
        dst[pos++] = digit1;
    }

    if (digit2 != 0 || digit1 != 0) {
        dst[pos++] = digit2;
    }

    dst[pos] = digit3;
}

u8 slashstring[4];

void int_to_str_slash(s32 num, s32 num2, u8 *dst) {
    s32 digit1;
    s32 digit2;
    s32 digit3;

    s8 pos = 0;

    if (num > 999) {
        dst[0] = 0x00; dst[1] = DIALOG_CHAR_TERMINATOR;
        return;
    }

    digit1 = num / 100;
    digit2 = (num - digit1 * 100) / 10;
    digit3 = (num - digit1 * 100) - (digit2 * 10);

    if (digit1 != 0) {
        dst[pos++] = digit1;
    }

    if (digit2 != 0 || digit1 != 0) {
        dst[pos++] = digit2;
    }

    dst[pos++] = digit3;
    dst[pos++] = 0x70;

    int_to_str(num2,slashstring);

    dst[pos++] = slashstring[0];
    dst[pos++] = slashstring[1];
    dst[pos++] = slashstring[2];


    dst[pos] = DIALOG_CHAR_TERMINATOR;
}

void int_to_str_time(s32 num, s32 num2, s32 num3, u8 *dst) {
    s32 digit[3];
    u8 i;
    digit[0] = num;
    digit[1] = num2;
    digit[2] = num3;

    for (i=0;i<3;i++) {
        int_to_str(digit[i],slashstring);
        if (digit[i] > 9) {
            dst[(i*3)] = slashstring[0];
            dst[(i*3)+1] = slashstring[1];
            dst[(i*3)+2] = 0xE6;
        } else {
            dst[(i*3)] = 0;
            dst[(i*3)+1] = slashstring[0];
            dst[(i*3)+2] = 0xE6;
        }
    }
    dst[8] = DIALOG_CHAR_TERMINATOR;
}

void string_insert(s32 pos, s32 amount, u8 *str, u8 *dst) {
    u8 i;
    for (i=0; i<amount;i++) {
        dst[i+pos] = str[i];
    }
}

s32 get_dialog_id(void) {
    return gDialogID;
}

void create_dialog_box(s16 dialog) {
    if (gDialogID == DIALOG_NONE) {
        gDialogID = dialog;
        gDialogBoxType = DIALOG_TYPE_ROTATE;
    }
}

void create_dialog_box_with_var(s16 dialog, s32 dialogVar) {
    if (gDialogID == DIALOG_NONE) {
        gDialogID = dialog;
        gDialogVariable = dialogVar;
        gDialogBoxType = DIALOG_TYPE_ROTATE;
    }
}

void create_dialog_inverted_box(s16 dialog) {
    if (gDialogID == DIALOG_NONE) {
        gDialogID = dialog;
        gDialogBoxType = DIALOG_TYPE_ZOOM;
        // if (gCurrLevelNum == LEVEL_RR) {
        //     gDialogBoxType = DIALOG_TYPE_ROTATE;
        //     //more hardcoded bullshit
        // }
    }
}

void create_dialog_box_with_response(s16 dialog) {
    if (gDialogID == DIALOG_NONE) {
        gDialogID = dialog;
        gDialogBoxType = DIALOG_TYPE_ROTATE;
        gLastDialogResponse = 1;
    }
}

void reset_dialog_render_state(void) {
    level_set_transition(0, NULL);

    gDialogBoxScale = 19.0f;
    gDialogBoxOpenTimer = 90.0f;
    gDialogBoxState = DIALOG_STATE_OPENING;
    gDialogID = DIALOG_NONE;
    gDialogTextPos = 0;
    gLastDialogResponse = 0;
    gLastDialogPageStrPos = 0;
    gDialogResponse = DIALOG_RESPONSE_NONE;
}

void render_dialog_box_type(struct DialogEntry *dialog, s8 linesPerBox) {
    create_dl_translation_matrix(MENU_MTX_NOPUSH, dialog->leftOffset, dialog->width, 0);

    switch (gDialogBoxType) {
        case DIALOG_TYPE_ROTATE: // Renders a dialog black box with zoom and rotation
            if ((gDialogBoxState == DIALOG_STATE_OPENING)
             || (gDialogBoxState == DIALOG_STATE_CLOSING)) {
                create_dl_scale_matrix(MENU_MTX_NOPUSH, (1.0f / gDialogBoxScale), (1.0f / gDialogBoxScale), 1.0f);
                // convert the speed into angle
                create_dl_rotation_matrix(MENU_MTX_NOPUSH, (gDialogBoxOpenTimer * 4.0f), 0, 0, 1.0f);
            }
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
            break;
        case DIALOG_TYPE_ZOOM: // Renders a dialog white box with zoom
            if (gDialogBoxState == DIALOG_STATE_OPENING || gDialogBoxState == DIALOG_STATE_CLOSING) {
                create_dl_translation_matrix(MENU_MTX_NOPUSH, (65.0f - (65.0f / gDialogBoxScale)), ((40.0f / gDialogBoxScale) - 40), 0);
                create_dl_scale_matrix(MENU_MTX_NOPUSH, (1.0f / gDialogBoxScale), (1.0f / gDialogBoxScale), 1.0f);
            }
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 150);
            break;
    }

    create_dl_translation_matrix(MENU_MTX_PUSH, -7.0f, 5.0f, 0);
    create_dl_scale_matrix(MENU_MTX_NOPUSH, 1.2f, (((f32) linesPerBox / 5.0f) + 0.1f), 1.0f);

    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void change_and_flash_dialog_text_color_lines(s8 colorMode, s8 lineNum, u8 *customColor) {
    u8 colorFade;

    if (colorMode == 1) {
        if (lineNum == 1) {
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        } else {
            if (lineNum == gDialogLineNum) {
                colorFade = 0;//(gSineTable[gDialogColorFadeTimer >> 4] * 50.0f) + 200.0f;
                gDPSetEnvColor(gDisplayListHead++, colorFade, colorFade, colorFade, 255);
            } else {
                gDPSetEnvColor(gDisplayListHead++, 200, 200, 200, 255);
            }
        }
    } else {
        switch (gDialogBoxType) {
            case DIALOG_TYPE_ROTATE:
                if (*customColor == 2) {
                    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                    *customColor = 0;
                }
                break;
            case DIALOG_TYPE_ZOOM:
                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
                break;
        }
    }
}

#define X_VAL3 0.0f
#define Y_VAL3 16

void handle_dialog_scroll_page_state(s8 lineNum, s8 totalLines, s8 *pageState, s8 *xMatrix, s16 *linePos) {
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    if (lineNum == totalLines) {
        *pageState = DIALOG_PAGE_STATE_SCROLL;
        return;
    }
    create_dl_translation_matrix(MENU_MTX_PUSH, 0.0f, 2 - (lineNum * 16), 0);

    *linePos = 0;
    *xMatrix = 1;
}

void render_star_count_dialog_text(s8 *xMatrix, s16 *linePos) {
    s8 tensDigit = gDialogVariable / 10;
    s8 onesDigit = gDialogVariable - (tensDigit * 10); // remainder

    if (tensDigit != 0) {
        if (*xMatrix != 1) {
            create_dl_translation_matrix(MENU_MTX_NOPUSH, (f32)(gDialogCharWidths[DIALOG_CHAR_SPACE] * *xMatrix), 0, 0);
        }

        render_generic_char(tensDigit);
        create_dl_translation_matrix(MENU_MTX_NOPUSH, (f32) gDialogCharWidths[tensDigit], 0, 0);
        *xMatrix = 1;
        (*linePos)++;
    }

    if (*xMatrix != 1) {
        create_dl_translation_matrix(MENU_MTX_NOPUSH, (f32)(gDialogCharWidths[DIALOG_CHAR_SPACE] * (*xMatrix - 1)), 0, 0);
    }

    render_generic_char(onesDigit);
    create_dl_translation_matrix(MENU_MTX_NOPUSH, (f32) gDialogCharWidths[onesDigit], 0, 0);
    (*linePos)++;
    *xMatrix = 1;
}

void render_multi_text_string_lines(s8 multiTextId, s8 lineNum, s16 *linePos, s8 linesPerBox, s8 xMatrix, s8 lowerBound) {
    s8 i;
    struct MultiTextEntry textLengths[2] = {
        { 3, { TEXT_THE_RAW } },
        { 3, { TEXT_YOU_RAW } },
    };

    if (lineNum >= lowerBound && lineNum <= (lowerBound + linesPerBox)) {
        if (*linePos != 0 || xMatrix != 1) {
            create_dl_translation_matrix(MENU_MTX_NOPUSH, (gDialogCharWidths[DIALOG_CHAR_SPACE] * (xMatrix - 1)), 0, 0);
        }
        for (i = 0; i < textLengths[multiTextId].length; i++) {
            render_generic_char(textLengths[multiTextId].str[i]);
            create_dl_translation_matrix(MENU_MTX_NOPUSH, (gDialogCharWidths[textLengths[multiTextId].str[i]]), 0, 0);
        }
    }
    linePos += textLengths[multiTextId].length;
}

u32 ensure_nonnegative(s16 value) {
    return ((value < 0) ? 0 : value);
}

void handle_dialog_text_and_pages(s8 colorMode, struct DialogEntry *dialog, s8 lowerBound) {
    u8 strChar;
    s16 colorLoop;
    ColorRGBA rgbaColors = { 0x00, 0x00, 0x00, 0x00 };
    u8 customColor = 0;
    u8 diffTmp = 0;
    u8 *str = segmented_to_virtual(dialog->str);
    s8 lineNum = 1;
    s8 totalLines;
    s8 pageState = DIALOG_PAGE_STATE_NONE;
    UNUSED s8 mark = DIALOG_MARK_NONE; // unused in US and EU
    s8 xMatrix = 1;
    s8 linesPerBox = dialog->linesPerBox;
    s16 strIdx;
    s16 linePos = 0;

    if (gDialogBoxState == DIALOG_STATE_HORIZONTAL) {
        // If scrolling, consider the number of lines for both
        // the current page and the page being scrolled to.
        totalLines = linesPerBox * 2 + 1;
    } else {
        totalLines = linesPerBox + 1;
    }

    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    strIdx = gDialogTextPos;

    if (gDialogBoxState == DIALOG_STATE_HORIZONTAL) {
        create_dl_translation_matrix(MENU_MTX_NOPUSH, 0, (f32) gDialogScrollOffsetY, 0);
    }

    create_dl_translation_matrix(MENU_MTX_PUSH, X_VAL3, 2 - lineNum * Y_VAL3, 0);

    while (pageState == DIALOG_PAGE_STATE_NONE) {
        if (customColor == 1) {
            gDPSetEnvColor(gDisplayListHead++, rgbaColors[0], rgbaColors[1], rgbaColors[2], rgbaColors[3]);
        } else {
            change_and_flash_dialog_text_color_lines(colorMode, lineNum, &customColor);
        }
        strChar = str[strIdx];

        switch (strChar) {
            case DIALOG_CHAR_TERMINATOR:
                pageState = DIALOG_PAGE_STATE_END;
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                break;
            case DIALOG_CHAR_COLOR:
                customColor = 1;
                strIdx++;
                for (colorLoop = (strIdx + 8); strIdx < colorLoop; ++strIdx) {
                    diffTmp = 0;
                    if ((str[strIdx] >= 0x24) && (str[strIdx] <= 0x29)) {
                        diffTmp = 0x1A;
                    } else if (str[strIdx] >= 0x10) {
                        customColor = 2;
                        strIdx = (colorLoop - 8);
                        for (diffTmp = 0; diffTmp < 8; ++diffTmp) {
                            if (str[strIdx + diffTmp] != 0x9F) {
                                break;
                            }
                        }
                        if (diffTmp == 8) {
                            strIdx += diffTmp;
                        }
                        break;
                    }
                    if (((8 - (colorLoop - strIdx)) % 2) == 0) {
                        rgbaColors[(8 - (colorLoop - strIdx)) / 2] = (((str[strIdx] - diffTmp) & 0x0F) << 4);
                    } else {
                        rgbaColors[(8 - (colorLoop - strIdx)) / 2] += ((str[strIdx] - diffTmp) & 0x0F);
                    }
                }
                strIdx--;
                break;
            case DIALOG_CHAR_NEWLINE:
                lineNum++;
                handle_dialog_scroll_page_state(lineNum, totalLines, &pageState, &xMatrix, &linePos);
                break;
            case DIALOG_CHAR_DAKUTEN:
                mark = DIALOG_MARK_DAKUTEN;
                break;
            case DIALOG_CHAR_PERIOD_OR_HANDAKUTEN:
                mark = DIALOG_MARK_HANDAKUTEN;
                break;
            case DIALOG_CHAR_SPACE:
                xMatrix++;
                linePos++;
                break;
            case DIALOG_CHAR_SLASH:
                xMatrix += 2;
                linePos += 2;
                break;
            case DIALOG_CHAR_MULTI_THE:
                render_multi_text_string_lines(STRING_THE, lineNum, &linePos, linesPerBox, xMatrix, lowerBound);
                xMatrix = 1;
                break;
            case DIALOG_CHAR_MULTI_YOU:
                render_multi_text_string_lines(STRING_YOU, lineNum, &linePos, linesPerBox, xMatrix, lowerBound);
                xMatrix = 1;
                break;
            case DIALOG_CHAR_STAR_COUNT:
                render_star_count_dialog_text(&xMatrix, &linePos);
                break;
            default: // any other character
                if ((lineNum >= lowerBound) && (lineNum <= (lowerBound + linesPerBox))) {
                    if (linePos || xMatrix != 1) {
                        create_dl_translation_matrix(
                            MENU_MTX_NOPUSH, (f32)(gDialogCharWidths[DIALOG_CHAR_SPACE] * (xMatrix - 1))+_spread, 0, 0);
                    }

                    render_generic_char(strChar);
                    create_dl_translation_matrix(MENU_MTX_NOPUSH, (f32)(gDialogCharWidths[strChar]), 0, 0);
                    xMatrix = 1;
                    linePos++;
                }
        }


        strIdx++;
    }

    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

    if (gDialogBoxState == DIALOG_STATE_VERTICAL) {
        if (pageState == DIALOG_PAGE_STATE_END) {
            gLastDialogPageStrPos = -1;
        } else {
            gLastDialogPageStrPos = strIdx;
        }
    }

    gLastDialogLineNum = lineNum;
}

#define X_VAL4_1 56
#define X_VAL4_2 47
#define Y_VAL4_1  2
#define Y_VAL4_2 16

void render_dialog_triangle_choice(void) {
    if (gDialogBoxState == DIALOG_STATE_VERTICAL) {
        handle_menu_scrolling(MENU_SCROLL_HORIZONTAL, &gDialogLineNum, 1, 2);
    }

    create_dl_translation_matrix(MENU_MTX_NOPUSH, (gDialogLineNum * X_VAL4_1) - X_VAL4_2, Y_VAL4_1 - (gLastDialogLineNum * Y_VAL4_2), 0);

    if (gDialogBoxType == DIALOG_TYPE_ROTATE) {
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    } else {
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
    }

    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
}

#define X_VAL5 125.0f
#define Y_VAL5_1 -16
#define Y_VAL5_2 5
#define X_Y_VAL6 0.8f

void render_dialog_triangle_next(s8 linesPerBox) {
    s32 globalTimer = gGlobalTimer;

    if (globalTimer & 0x8) {
        return;
    }

    create_dl_translation_matrix(MENU_MTX_PUSH, X_VAL5, (linesPerBox * Y_VAL5_1) + Y_VAL5_2, 0);
    create_dl_scale_matrix(MENU_MTX_NOPUSH, X_Y_VAL6, X_Y_VAL6, 1.0f);
    create_dl_rotation_matrix(MENU_MTX_NOPUSH, -DEFAULT_DIALOG_BOX_ANGLE, 0, 0, 1.0f);

    if (gDialogBoxType == DIALOG_TYPE_ROTATE) { // White Text
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    } else { // Black Text
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
    }

    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void handle_special_dialog_text(s16 dialogID) { // dialog ID tables, in order
    // King Bob-omb (Start), Whomp (Start), King Bob-omb (throw him out), Eyerock (Start), Wiggler (Start)
    s16 dialogBossStart[] = { DIALOG_017, DIALOG_114, DIALOG_128, DIALOG_117, DIALOG_150 };
    // Koopa the Quick (BoB), Koopa the Quick (THI), Penguin Race, Fat Penguin Race (120 stars)
    s16 dialogRaceSound[] = { DIALOG_005, DIALOG_009, DIALOG_055, DIALOG_164             };
    // Red Switch, Green Switch, Blue Switch, 100 coins star, Bowser Red Coin Star
    s16 dialogStarSound[] = { DIALOG_010, DIALOG_011, DIALOG_012, DIALOG_013, DIALOG_014 };
    // King Bob-omb (Start), Whomp (Defeated), King Bob-omb (Defeated, missing in JP), Eyerock (Defeated), Wiggler (Defeated)
    s16 dialogBossStop[]  = { DIALOG_017, DIALOG_115, DIALOG_116, DIALOG_118, DIALOG_152 };
    s16 i;

    for (i = 0; i < (s16) ARRAY_COUNT(dialogBossStart); i++) {
        if (dialogBossStart[i] == dialogID) {
            seq_player_unlower_volume(SEQ_PLAYER_LEVEL, 60);
            play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_BOSS), 0);
            return;
        }
    }

    for (i = 0; i < (s16) ARRAY_COUNT(dialogRaceSound); i++) {
        if (dialogRaceSound[i] == dialogID && gDialogLineNum == 1) {
            play_race_fanfare();
            return;
        }
    }

    for (i = 0; i < (s16) ARRAY_COUNT(dialogStarSound); i++) {
        if (dialogStarSound[i] == dialogID && gDialogLineNum == 1) {
            play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
            return;
        }
    }

    for (i = 0; i < (s16) ARRAY_COUNT(dialogBossStop); i++) {
        if (dialogBossStop[i] == dialogID) {
            seq_player_fade_out(SEQ_PLAYER_LEVEL, 1);
            return;
        }
    }
}


u16 gCutsceneMsgFade        =  0;
s16 gCutsceneMsgIndex       = -1;
s16 gCutsceneMsgDuration    = -1;
s16 gCutsceneMsgTimer       =  0;
s8  gDialogCameraAngleIndex = CAM_SELECTION_MARIO;
s8  gDialogCourseActNum     =  1;

#define SHOP_OFFSET 200

#define DIAG_VAL1  16
#define DIAG_VAL3 132 // US & EU
#define DIAG_VAL4   5
#define DIAG_VAL2 240 // JP & US


u8 shopid;
u8 shopselection;

void render_dialog_entries(void) {

    s8 lowerBound = 0;
    void **dialogTable = segmented_to_virtual(languageTable[gInGameLanguage][0]);
    struct DialogEntry *dialog = segmented_to_virtual(dialogTable[gDialogID]);

    // if the dialog entry is invalid, set the ID to DIALOG_NONE.
    if (segmented_to_virtual(NULL) == dialog) {
        gDialogID = DIALOG_NONE;
        return;
    }

    switch (gDialogBoxState) {
        case DIALOG_STATE_OPENING:
            if (gDialogBoxOpenTimer == DEFAULT_DIALOG_BOX_ANGLE) {
                play_dialog_sound(gDialogID);
                play_sound(SOUND_MENU_MESSAGE_APPEAR, gGlobalSoundSource);
            }

            if (gDialogBoxType == DIALOG_TYPE_ROTATE) {
                gDialogBoxOpenTimer -= 7.5f;
                gDialogBoxScale -= 1.5f;
            } else {
                gDialogBoxOpenTimer -= 10.0f;
                gDialogBoxScale -= 2.0f;
            }

            if (gDialogBoxOpenTimer == 0.0f) {
                gDialogBoxState = DIALOG_STATE_VERTICAL;
                gDialogLineNum = 1;
            }
            lowerBound = 1;
            break;

        case DIALOG_STATE_VERTICAL:
            gDialogBoxOpenTimer = 0.0f;

            if (gPlayer1Controller->buttonPressed & (A_BUTTON | B_BUTTON)) {
                if (gLastDialogPageStrPos == -1) {
                    handle_special_dialog_text(gDialogID);
                    gDialogBoxState = DIALOG_STATE_CLOSING;
                } else {
                    gDialogBoxState = DIALOG_STATE_HORIZONTAL;
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                }
            }
            lowerBound = 1;
            break;
        case DIALOG_STATE_HORIZONTAL: // scrolling
            gDialogScrollOffsetY += (dialog->linesPerBox * 2);

            if (gDialogScrollOffsetY >= dialog->linesPerBox * DIAG_VAL1) {
                gDialogTextPos = gLastDialogPageStrPos;
                gDialogBoxState = DIALOG_STATE_VERTICAL;
                gDialogScrollOffsetY = 0;
            }
            lowerBound = (gDialogScrollOffsetY / DIAG_VAL1) + 1;
            break;

        case DIALOG_STATE_CLOSING:
            if (gDialogBoxOpenTimer == 20.0f) {
                level_set_transition(0, NULL);
                if (gDialogID != DIALOG_013) { // exit level after all stars dialog
                    play_sound(SOUND_MENU_MESSAGE_DISAPPEAR, gGlobalSoundSource);
                }

                gDialogResponse = gDialogLineNum;
            }

            gDialogBoxOpenTimer = gDialogBoxOpenTimer + 10.0f;
            gDialogBoxScale = gDialogBoxScale + 2.0f;

            if (gDialogBoxOpenTimer == DEFAULT_DIALOG_BOX_ANGLE) {
                gDialogBoxState = DIALOG_STATE_OPENING;
                gDialogID = DIALOG_NONE;
                gDialogTextPos = 0;
                gLastDialogResponse = 0;
                gLastDialogPageStrPos = 0;
                gDialogResponse = DIALOG_RESPONSE_NONE;
            }
            lowerBound = 1;
            break;
    }

    render_dialog_box_type(dialog, dialog->linesPerBox);


    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE,
                  // Horizontal scissoring isn't really required and can potentially mess up widescreen enhancements.
                  0,
                  ensure_nonnegative(DIAG_VAL2 - dialog->width),
                  SCREEN_WIDTH,
                  ensure_nonnegative(240 + ((dialog->linesPerBox * 80) / DIAG_VAL4) - dialog->width));

    handle_dialog_text_and_pages(0, dialog, lowerBound);

    if (gLastDialogPageStrPos == -1 && gLastDialogResponse == 1) {
        render_dialog_triangle_choice();
    }
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 2, 2, SCREEN_WIDTH - gBorderHeight / 2, SCREEN_HEIGHT - gBorderHeight / 2);
    if (gLastDialogPageStrPos != -1 && gDialogBoxState == DIALOG_STATE_VERTICAL) {
        render_dialog_triangle_next(dialog->linesPerBox);
    }
}

void render_dialog_entry_preview(u8 dialog_id) {
    void **dialogTable = segmented_to_virtual(languageTable[gInGameLanguage][0]);
    struct DialogEntry *dialog = segmented_to_virtual(dialogTable[dialog_id]);
    gDialogBoxScale = 1.0f;

    render_dialog_box_type(dialog, dialog->linesPerBox);

    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE,
                  // Horizontal scissoring isn't really required and can potentially mess up widescreen enhancements.
                  0,
                  ensure_nonnegative(DIAG_VAL2 - dialog->width),
                  SCREEN_WIDTH,
                  ensure_nonnegative(240 + ((dialog->linesPerBox * 80) / DIAG_VAL4) - dialog->width));

    handle_dialog_text_and_pages(0, dialog, 1);
}

void reset_cutscene_msg_fade(void) {
    gCutsceneMsgFade = 0;
}

void dl_rgba16_begin_cutscene_msg_fade(void) {
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gCutsceneMsgFade);
}

void dl_rgba16_stop_cutscene_msg_fade(void) {
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);

    if (gCutsceneMsgFade < 250) {
        gCutsceneMsgFade += 25;
    } else {
        gCutsceneMsgFade = 255;
    }
}

u32 ascii_to_credits_char(u8 c) {
    if (c >= 'A' && c <= 'Z') return (c - ('A' - 0xA));
    if (c >= 'a' && c <= 'z') return (c - ('a' - 0xA)); // remap lower to upper case
    if (c == ' ') return GLOBAL_CHAR_SPACE;
    if (c == '.') return 0x24;
    if (c == '3') return ASCII_TO_DIALOG('3');
    if (c == '4') return ASCII_TO_DIALOG('4');
    if (c == '6') return ASCII_TO_DIALOG('6');

    return GLOBAL_CHAR_SPACE;
}

void print_credits_str_ascii(s16 x, s16 y, const char *str) {
    s32 pos = 0;
    u8 c = str[pos];
    u8 creditStr[100];

    while (c != 0) {
        creditStr[pos++] = ascii_to_credits_char(c);
        c = str[pos];
    }

    creditStr[pos] = GLOBAR_CHAR_TERMINATOR;

    print_credits_string(x, y, creditStr);
}

void set_cutscene_message(s16 xOffset, s16 yOffset, s16 msgIndex, s16 msgDuration) {
    // is message done printing?
    if (gCutsceneMsgIndex == -1) {
        gCutsceneMsgIndex = msgIndex;
        gCutsceneMsgDuration = msgDuration;
        gCutsceneMsgTimer = 0;
        gCutsceneMsgXOffset = xOffset;
        gCutsceneMsgYOffset = yOffset;
        gCutsceneMsgFade = 0;
    }
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
        gDialogColorFadeTimer = (s16) gDialogColorFadeTimer + 0x1000;
    } else if (gDialogID != DIALOG_NONE) {
        render_dialog_entries();
        gDialogColorFadeTimer = (s16) gDialogColorFadeTimer + 0x1000;
    }

    render_menu();
}
