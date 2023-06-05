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
#include "levels/castle_grounds/header.h"
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
#include "rovent.h"
#include "level_update.h"
#include "hud.h"

u8 letgo = FALSE;

f32 _spread;

u32 bicon_table[] = {
    &b0_Plane_001_mesh,
    &b1_Plane_001_mesh,
    &b2_Plane_001_mesh,
    &b3_Plane_001_mesh,
    &b4_Plane_001_mesh,
    &b5_Plane_001_mesh,
    &b6_Plane_001_mesh,
    &b7_Plane_001_mesh,
    &b8_Plane_001_mesh,
    &b9_Plane_001_mesh,
    &b10_Plane_001_mesh,
    &b11_Plane_001_mesh,

    &b12_Plane_mesh,
    &b13_Plane_mesh,
    &b14_Plane_mesh,
    &b15_Plane_mesh,
    &b16_Plane_mesh,
    &b17_Plane_mesh,
    &b18_Plane_mesh,
    &b19_Plane_mesh,
    &b20_Plane_mesh,
    &b21_Plane_mesh,
    &b22_Plane_mesh,
    &b23_Plane_mesh
};


u8 number_text[15];

u8 text1[] = { TEXT_CHAR_CHANGE };
u8 c1[] = {COSTUME1};
u8 c2[] = {COSTUME2};
u8 c3[] = {COSTUME3};
u8 c4[] = {COSTUME4};
u8 c5[] = {COSTUME5};
u8 c6[] = {COSTUME6};
u8 c7[] = {COSTUME7};
u8 c8[] = {COSTUME8};
u8 c9[] = {COSTUME9};
u8 c10[] = {COSTUME10};
u8 c11[] = {COSTUME11};
u8 c12[] = {COSTUME12};
u8 c13[] = {COSTUME13};
u8 c14[] = {COSTUME14};
u8 c15[] = {COSTUME15};
u8 *costume_text[] = { {c1},{c2},{c3},{c4},{c5},{c6},{c7},{c8},{c9},{c10},{c11},{c12},{c13},{c14},{c15}};


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
u8 b12[] = {BADGE12};
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

u8 *badgenames[] = { {b1},{b2},{b3},{b4},{b5},{b6},{b7},{b8},{b9},{b10},{b11},{b12},
{b13},{b14},{b15},{b16},{b17},{b18},{b19},{b20},{b21},{b22},{b23},{b24}
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
u8 b12d[] = {BADGE12D};
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
u8 *badgedescs[] = { {b1d},{b2d},{b3d},{b4d},{b5d},{b6d},{b7d},{b8d},{b9d},{b10d},{b11d},{b12d},
{b13d},{b14d},{b15d},{b16d},{b17d},{b18d},{b19d},{b20d},{b21d},{b22d},{b23d},{b24d} };

u8 txt_on[] = {TEXT_OPTION_ON};
u8 txt_off[] = {TEXT_OPTION_OFF};

u8 txt_warp[] = {TEXT_WARPTOLEVEL};

u8 txt_prog1[] = {TEXT_PROGRESS_1};
u8 txt_prog2[] = {TEXT_PROGRESS_2};

u8 magictext[] = {MAGICTEXT};
u8 cheattext[] = {CHEATTEXT};
u8 optiontext[] = {OPTIONTEXT};
u8 magictext_c[] = {MAGICCOST};
u8 tab1[] = {TAB1};
u8 tab2[] = {TAB2};
u8 tab3[] = {TAB3};
u8 tab4[] = {TAB4};
u8 tab5[] = {TAB5};
u8 tab6[] = {TAB6};
u8 *tabs[] = { {tab1},{tab2},{tab3},{tab4},{tab5},{tab6} };
u8 tablist[] = {0,0,0,0,0};
u8 tablist_count = 0;
u16 progress_table[12];

u8 upgradetext[] = {TEXT_UPGRADE};
u8 upgradeyes[] = {TEXT_UPGRADE_YES};
u8 upgradeno[] = {TEXT_UPGRADE_NO};

u8 badgecolors[24][3] = {
    {255,0x00,0x00},
    {0x9C,0x43,0x22},
    {0x19,0x6B,0xC7},
    {0xDF,0x4A,0x18},
    {0x6C,0xC6,0xD7},
    {0x6C,0xC6,0xD7},
    {0x72,0xC6,0xAE},
    {0xF9,0x8D,0xCF},
    {0xF8,0xB6,0x4B},
    {0x4A,0x52,0x8C},
    {0x44,0xC6,0x53},
    {0xF9,0xD6,0x4B},

    {0xEA,0x55,0x20},
    {0x46,0x4D,0xBE},
    {0x60,0x8E,0xA0},
    {0xAC,0x6E,0x56},
    {0x44,0xAF,0x19},
    {0x21,0xE9,0xA1},
    {0x57,0xFF,0x4C},
    {0x4B,0x6D,0x7A},
    {0xDF,0x4A,0x18},
    {0xA0,0x00,0x00},
    {0xA0,0x00,0x00},
    {0xA0,0x00,0x00},
};

//Cost (coins) //Cost (stars) //Max Stat //BP
u16 UPGRADE_TABLE[][4] = {
{0,0,5,0},
{0,0,7,1},
{10,1,10,2},
{50,5,12,3},
{150,15,13,3},
{250,20,14,4},
{300,30,15,4},
{400,45,16,5},
{600,70,20,6},
{999,999,0,0},
};

//brah! expensive as hell.

#ifdef VERSION_EU
#undef LANGUAGE_FUNCTION
#define LANGUAGE_FUNCTION gInGameLanguage
#endif

u16 gDialogColorFadeTimer;
s8 gLastDialogLineNum;
s32 gDialogVariable;
u16 gDialogTextAlpha;
s16 gCutsceneMsgXOffset;
s16 gCutsceneMsgYOffset;
s8 gRedCoinsCollected;
#if defined(WIDE) && !defined(PUPPYCAM)
u8 textCurrRatio43[] = { TEXT_HUD_CURRENT_RATIO_43 };
u8 textCurrRatio169[] = { TEXT_HUD_CURRENT_RATIO_169 };
u8 textPressL[] = { TEXT_HUD_PRESS_L };
#endif

#if MULTILANG
#define seg2_course_name_table course_name_table_eu_en
#define seg2_act_name_table act_name_table_eu_en
#define seg2_dialog_table dialog_table_eu_en
#endif

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
    6,  6,  5,  6,  6,  5,  8,  8,  6,  6,  6,  6,  6,  5,  6,  6,
    8,  7,  6,  6,  6,  5,  5,  6,  5,  5,  6,  5,  4,  5,  5,  3,
    7,  5,  5,  5,  6,  5,  5,  5,  5,  5,  7,  7,  5,  5,  4,  4,
    8,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    8,  8,  8,  8,  7,  7,  6,  7,  7,  0,  0,  0,  0,  0,  0,  0,
#ifdef VERSION_EU
    6,  6,  6,  0,  6,  6,  6,  0,  0,  0,  0,  0,  0,  0,  0,  4,
    5,  5,  5,  5,  6,  6,  6,  6,  0,  0,  0,  0,  0,  0,  0,  0,
    5,  5,  5,  0,  6,  6,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  5,  5,  0,  0,  6,  6,  0,  0,  0,  0,  0,  0,  0,  5,  6,
    0,  4,  4,  0,  0,  5,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,
#else
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,
    8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  5,  6,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
#endif
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    7,  5, 10,  5,  9,  8,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  5,  7,  7,  6,  6,  8,  0,  8, 10,  6,  4, 10,  0,  0
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

void display_icon(Gfx* dl, f32 x, f32 y) {
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
        if ((gPlayer3Controller->rawStickY >  60) || (gPlayer3Controller->buttonDown & (U_CBUTTONS | U_JPAD))) index++;
        if ((gPlayer3Controller->rawStickY < -60) || (gPlayer3Controller->buttonDown & (D_CBUTTONS | D_JPAD))) index += 2;
    } else if (scrollDirection == MENU_SCROLL_HORIZONTAL) {
        if ((gPlayer3Controller->rawStickX >  60) || (gPlayer3Controller->buttonDown & (R_CBUTTONS | R_JPAD))) index += 2;
        if ((gPlayer3Controller->rawStickX < -60) || (gPlayer3Controller->buttonDown & (L_CBUTTONS | L_JPAD))) index++;
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
        if (gCurrLevelNum == LEVEL_RR) {
            gDialogBoxType = DIALOG_TYPE_ROTATE;
            //more hardcoded bullshit
        }
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
                colorFade = (gSineTable[gDialogColorFadeTimer >> 4] * 50.0f) + 200.0f;
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

s16 gMenuMode = MENU_MODE_NONE;

u8 gEndCutsceneStrEn0[] = { TEXT_FILE_MARIO_EXCLAMATION };
u8 gEndCutsceneStrEn1[] = { TEXT_POWER_STARS_RESTORED };
u8 gEndCutsceneStrEn2[] = { TEXT_THANKS_TO_YOU };
u8 gEndCutsceneStrEn3[] = { TEXT_THANK_YOU_MARIO };
u8 gEndCutsceneStrEn4[] = { TEXT_SOMETHING_SPECIAL };
u8 gEndCutsceneStrEn5[] = { TEXT_LISTEN_EVERYBODY };
u8 gEndCutsceneStrEn6[] = { TEXT_LETS_HAVE_CAKE };
u8 gEndCutsceneStrEn7[] = { TEXT_FOR_MARIO };
u8 gEndCutsceneStrEn8[] = { TEXT_FILE_MARIO_QUESTION };

u8 *gEndCutsceneStringsEn[] = {
    gEndCutsceneStrEn0,
    gEndCutsceneStrEn1,
    gEndCutsceneStrEn2,
    gEndCutsceneStrEn3,
    gEndCutsceneStrEn4,
    gEndCutsceneStrEn5,
    gEndCutsceneStrEn6,
    gEndCutsceneStrEn7,
    // This [8] string is actually unused. In the cutscene handler, the developers do not
    // set the 8th one, but use the first string again at the very end, so Peach ends up
    // saying "Mario!" twice. It is likely that she was originally meant to say "Mario?" at
    // the end but the developers changed their mind, possibly because the line recorded
    // sounded more like an exclamation than a question.
    gEndCutsceneStrEn8,
    NULL
};


u16 gCutsceneMsgFade        =  0;
s16 gCutsceneMsgIndex       = -1;
s16 gCutsceneMsgDuration    = -1;
s16 gCutsceneMsgTimer       =  0;
s8  gDialogCameraAngleIndex = CAM_SELECTION_MARIO;
s8  gDialogCourseActNum     =  1;

#define SHOP_OFFSET 158
#define SHOP_INVERSE_OFFSET -42

#define DIAG_VAL1  16
#define DIAG_VAL3 132 // US & EU
#define DIAG_VAL4   5
#define DIAG_VAL2 240 // JP & US

u16 shoptable[12][6] = {
    {BADGE_FALL,25,BADGE_DEFENSE,70,BADGE_MAGNET,125},//shop 0 main*
    {12,0,13,0,14,0},//upgrade station [UNUSED]
    {BADGE_MANA,100,BADGE_FALL,10,BADGE_DEFENSE,30},//shop 2 secret*
    {BADGE_LAVA,40,BADGE_FALL,30,BADGE_BURN,150},//shop 3 reservoir*
    {BADGE_FINS,50,BADGE_GILLS,150,BADGE_STAR,200},//ghost ship shop*
    {BADGE_DAMAGE,170,BADGE_MANA,120,BADGE_BURN,75},//floor 2 (castle outdoor) shop*
    {BADGE_HP,300,BADGE_GREED,250,BADGE_TIME,420},//floor 2 extra shop*
    {BADGE_FEET,80,BADGE_STICKY,200,BADGE_FEATHER,400},//KTQ Thwomp Towers Shop*
    {BADGE_LAVA,100,BADGE_DEFENSE,100,BADGE_FALL,100},//tutorial shop  //{0,0,0,0,0,0},//executive (HUB 3) shop
    {BADGE_SQUISH,120,BADGE_WEIGHT,50,BADGE_BURN, 180},//floor 1 alternative shop
    {BADGE_BRITTLE,1,BADGE_WITHER,1,BADGE_HARDCORE,1},//burden shop (ALL FOR 1 DOLLAR LOL!)
    {BADGE_HEAL,300,BADGE_BOTTOMLESS,200,BADGE_SLAYER,50}//starfair final shop
};

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

    shopid = gMarioState->ShopID;

    //toll bridge
    if (gDialogID == 33) {
        if (gPlayer1Controller->buttonPressed & A_BUTTON) {
            if ((gMarioState->numGlobalCoins >= 10)&&(!gMarioState->TollPaid)) {
                gMarioState->gGlobalCoinGain -= 10;
                play_sound(SOUND_GENERAL_COIN_WATER, gGlobalSoundSource);
                gMarioState->TollPaid = TRUE;
                save_file_set_stats();
                save_file_do_save(gCurrSaveFileNum - 1);
            }
        }
    }

    //ATM
    if (gDialogID == 40) {
        if (gPlayer1Controller->buttonDown & A_BUTTON) {
            if ((gMarioState->numCoins > 0)&&(gMarioState->numMaxGlobalCoins > gMarioState->numGlobalCoins)) {
                gMarioState->numGlobalCoins ++;
                gMarioState->numCoins --;
                gHudDisplay.coins = gMarioState->numCoins;
                play_sound(SOUND_GENERAL_COIN_WATER, gGlobalSoundSource);
            }
        }
    }

    //only do shop shit if dialog id is 1
    if (gDialogID == 1) {
        //SHOP CONTROLS
        if ((gPlayer1Controller->rawStickX > 60)&&(letgo == FALSE)) {
            shopselection ++;
            if (shopselection > 2) {
                shopselection = 0;
                }
            play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
            letgo = TRUE;
            }
        if ((gPlayer1Controller->rawStickX < -60)&&(letgo == FALSE)) {
            shopselection --;
            play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
            if (shopselection > 253) {
                shopselection = 2;
                }
            letgo = TRUE;
            }
        if ((gPlayer1Controller->rawStickX > -60)&&(gPlayer1Controller->rawStickX < 60)) {
            letgo = FALSE;
            }

        shoptable[1][1] = (gMarioState->Level+1)*50;
        shoptable[1][3] = (gMarioState->Level+1)*50;
        shoptable[1][5] = (gMarioState->Level+1)*50;

        if ((gPlayer1Controller->buttonPressed & A_BUTTON)&&(gMarioState->gGlobalCoinGain == 0)) { //no buying while coins are moving
            if ((gMarioState->numGlobalCoins >= shoptable[shopid][1+(shopselection*2)])
            || (!(save_file_get_flags() & SAVE_FLAG_FREE_BADGE))) { //you can claim your free badge here
                if (!(save_file_get_badge_unlock() & (1<<shoptable[shopid][(shopselection*2)]) )) {//only buy badge if not already owned
                    play_sound(SOUND_GENERAL_COIN_WATER, gGlobalSoundSource);
                    gMarioState->gGlobalCoinGain -= shoptable[shopid][1+(shopselection*2)];
                    save_file_set_flags(SAVE_FLAG_FREE_BADGE); // no more free loading bitch,.
                    save_file_set_badge_unlock( (1<<shoptable[shopid][(shopselection*2)]) );
                }
            }
        }



        //RENDER SHOP
        display_icon(&shopgui_Plane_001_mesh, SHOP_OFFSET, 110);
        display_icon(&shopselect_Plane_002_mesh, SHOP_OFFSET-48+(48*shopselection), 110);
        if (!(save_file_get_badge_unlock() & (1<<shoptable[shopid][0]) )) {//only display badge if not already owned
            display_icon(bicon_table[shoptable[shopid][0]], SHOP_OFFSET-48, 110);
            }
        if (!(save_file_get_badge_unlock() & (1<<shoptable[shopid][2]) )) {//only display badge if not already owned
            display_icon(bicon_table[shoptable[shopid][2]], SHOP_OFFSET, 110);
            }
        if (!(save_file_get_badge_unlock() & (1<<shoptable[shopid][4]) )) {//only display badge if not already owned
            display_icon(bicon_table[shoptable[shopid][4]], SHOP_OFFSET+48, 110);
            }

        if (save_file_get_flags() & SAVE_FLAG_FREE_BADGE) {
            //normal
            print_text_fmt_int(130+SHOP_INVERSE_OFFSET,34,"$%d",shoptable[shopid][1+(shopselection*2)]);
        } else {
            //free!
            print_text_fmt_int(130+SHOP_INVERSE_OFFSET,34,"$%d",0);
        }

        print_text_fmt_int(194+SHOP_INVERSE_OFFSET,34, ",%d", gMarioState->numGlobalCoins);

        gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
        print_generic_string(get_str_x_pos_from_center(SHOP_OFFSET,badgenames[shoptable[shopid][shopselection*2]],0.0f)-1, 58-1, badgenames[shoptable[shopid][shopselection*2]]);
        //gDPSetEnvColor(gDisplayListHead++, badgecolors[shoptable[shopid][shopselection*2]][0], badgecolors[shoptable[shopid][shopselection*2]][1], badgecolors[shoptable[shopid][shopselection*2]][2], 255);
        //^ that looks bad unfortunately
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        print_generic_string(get_str_x_pos_from_center(SHOP_OFFSET,badgenames[shoptable[shopid][shopselection*2]],0.0f), 58, badgenames[shoptable[shopid][shopselection*2]]);
        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

        //print badge descs
        gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
        print_generic_string(get_str_x_pos_from_center(160,badgedescs[shoptable[shopid][shopselection*2]],0.0f)-1, 145-1, badgedescs[shoptable[shopid][shopselection*2]]);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        print_generic_string(get_str_x_pos_from_center(160,badgedescs[shoptable[shopid][shopselection*2]],0.0f), 145, badgedescs[shoptable[shopid][shopselection*2]]);
        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    }

    u8 in_an_interact_menu = (gDialogID == 1)||(gDialogID == 3)||(gDialogID == 40);
    u32 button_cond = (gPlayer3Controller->buttonPressed & (A_BUTTON|B_BUTTON));

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

            if (in_an_interact_menu) {
                button_cond = (gPlayer3Controller->buttonPressed & B_BUTTON);
            }

            if (button_cond) {
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
                play_sound(SOUND_MENU_MESSAGE_DISAPPEAR, gGlobalSoundSource);

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

    _spread = 0.0f;
    if ((gCurrLevelNum == LEVEL_SSL)&&(gDialogID>49)) {
        _spread = 2.0f;
    }
    handle_dialog_text_and_pages(0, dialog, lowerBound);

    if (gLastDialogPageStrPos == -1 && gLastDialogResponse == 1) {
        render_dialog_triangle_choice();
    }
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 2, 2, SCREEN_WIDTH - gBorderHeight / 2, SCREEN_HEIGHT - gBorderHeight / 2);
    if (gLastDialogPageStrPos != -1 && gDialogBoxState == DIALOG_STATE_VERTICAL) {
        render_dialog_triangle_next(dialog->linesPerBox);
    }
}

// Calls a gMenuMode value defined by render_menus_and_dialogs cases
void set_menu_mode(s16 mode) {
    if (gMenuMode == MENU_MODE_NONE) {
        gMenuMode = mode;
    }
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

void do_cutscene_handler(void) {
    // is a cutscene playing? do not perform this handler's actions if so.
    if (gCutsceneMsgIndex == -1) {
        return;
    }
    
    create_dl_ortho_matrix();

    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gCutsceneMsgFade);

    // get the x coordinate of where the cutscene string starts.
    s16 x = get_str_x_pos_from_center(gCutsceneMsgXOffset, gEndCutsceneStringsEn[gCutsceneMsgIndex], 10.0f);
    print_generic_string(x, 240 - gCutsceneMsgYOffset, gEndCutsceneStringsEn[gCutsceneMsgIndex]);

    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

    // if the timing variable is less than 5, increment
    // the fade until we are at full opacity.
    if (gCutsceneMsgTimer < 5) {
        gCutsceneMsgFade += 50;
    }

    // if the cutscene frame length + the fade-in counter is
    // less than the timer, it means we have exceeded the
    // time that the message is supposed to remain on
    // screen. if (message_duration = 50) and (msg_timer = 55)
    // then after the first 5 frames, the message will remain
    // on screen for another 50 frames until it starts fading.
    if (gCutsceneMsgDuration + 5 < gCutsceneMsgTimer) {
        gCutsceneMsgFade -= 50;
    }

    // like the first check, it takes 5 frames to fade out, so
    // perform a + 10 to account for the earlier check (10-5=5).
    if (gCutsceneMsgDuration + 10 < gCutsceneMsgTimer) {
        gCutsceneMsgIndex = -1;
        gCutsceneMsgFade = 0;
        gCutsceneMsgTimer = 0;
        return;
    }

    gCutsceneMsgTimer++;
}

#define PEACH_MESSAGE_TIMER 250

#define STR_X  38
#define STR_Y 142

// "Dear Mario" message handler
void print_peach_letter_message(void) {
#ifdef VERSION_EU
    void **dialogTable;
    gInGameLanguage = eu_get_language();
    switch (gInGameLanguage) {
        default:
        case LANGUAGE_ENGLISH: dialogTable = segmented_to_virtual(dialog_table_eu_en); break;
        case LANGUAGE_FRENCH:  dialogTable = segmented_to_virtual(dialog_table_eu_fr); break;
        case LANGUAGE_GERMAN:  dialogTable = segmented_to_virtual(dialog_table_eu_de); break;
    }
#else
    void **dialogTable = segmented_to_virtual(seg2_dialog_table);
#endif
    struct DialogEntry *dialog = segmented_to_virtual(dialogTable[gDialogID]);
    u8 *str = segmented_to_virtual(dialog->str);

    create_dl_translation_matrix(MENU_MTX_PUSH, 97.0f, 118.0f, 0);

    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gCutsceneMsgFade);
    gSPDisplayList(gDisplayListHead++, castle_grounds_seg7_dl_0700EA58);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 20, 20, 20, gCutsceneMsgFade);

    print_generic_string(STR_X, STR_Y, str);
#ifdef VERSION_JP
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
#else
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    gDPSetEnvColor(gDisplayListHead++, 200, 80, 120, gCutsceneMsgFade);
    gSPDisplayList(gDisplayListHead++, castle_grounds_seg7_us_dl_0700F2E8);
#endif

    // at the start/end of message, reset the fade.
    if (gCutsceneMsgTimer == 0) {
        gCutsceneMsgFade = 0;
    }

    // we're less than 20 increments, so increase the fade.
    if (gCutsceneMsgTimer < 20) {
        gCutsceneMsgFade += 10;
    }

    // we're after PEACH_MESSAGE_TIMER increments, so decrease the fade.
    if (gCutsceneMsgTimer > PEACH_MESSAGE_TIMER) {
        gCutsceneMsgFade -= 10;
    }

    // 20 increments after the start of the decrease, we're
    // back where we are, so reset everything at the end.
    if (gCutsceneMsgTimer > (PEACH_MESSAGE_TIMER + 20)) {
        gCutsceneMsgIndex = -1;
        gCutsceneMsgFade = 0; //! uselessly reset since the next execution will just set it to 0 again.
        gDialogID = DIALOG_NONE;
        gCutsceneMsgTimer = 0;
        return; // return to avoid incrementing the timer
    }

    gCutsceneMsgTimer++;
}

/**
 * Renders the cannon reticle when Mario is inside a cannon.
 * Formed by four triangles.
 */
void render_hud_cannon_reticle(void) {
    create_dl_translation_matrix(MENU_MTX_PUSH, 160.0f, 120.0f, 0);

    gDPSetEnvColor(gDisplayListHead++, 50, 50, 50, 180);
    create_dl_translation_matrix(MENU_MTX_PUSH, -20.0f, -8.0f, 0);
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    create_dl_translation_matrix(MENU_MTX_PUSH, 20.0f, 8.0f, 0);
    create_dl_rotation_matrix(MENU_MTX_NOPUSH, 180.0f, 0, 0, 1.0f);
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    create_dl_translation_matrix(MENU_MTX_PUSH, 8.0f, -20.0f, 0);
    create_dl_rotation_matrix(MENU_MTX_NOPUSH, DEFAULT_DIALOG_BOX_ANGLE, 0, 0, 1.0f);
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    create_dl_translation_matrix(MENU_MTX_PUSH, -8.0f, 20.0f, 0);
    create_dl_rotation_matrix(MENU_MTX_NOPUSH, -DEFAULT_DIALOG_BOX_ANGLE, 0, 0, 1.0f);
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void reset_red_coins_collected(void) {
    gRedCoinsCollected = 0;
}

void change_dialog_camera_angle(void) {
    if (cam_select_alt_mode(0) == CAM_SELECTION_MARIO) {
        gDialogCameraAngleIndex = CAM_SELECTION_MARIO;
    } else {
        gDialogCameraAngleIndex = CAM_SELECTION_FIXED;
    }
}

void shade_screen(void) {

    // This is a bit weird. It reuses the dialog text box (width 130, height -80),
    // so scale to at least fit the screen.
    if (1) { // axo: what?
        create_dl_translation_matrix(MENU_MTX_PUSH, GFX_DIMENSIONS_FROM_LEFT_EDGE(0), SCREEN_HEIGHT, 0);
        create_dl_scale_matrix(MENU_MTX_NOPUSH, 2.6f, 3.4f, 1.0f);
        
    }
    else
    {
        create_dl_translation_matrix(MENU_MTX_PUSH, -500.0f, SCREEN_HEIGHT, 0);
        create_dl_scale_matrix(MENU_MTX_NOPUSH, 8.0f, 8.0f, 1.0f); //widde screen
    }

    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 110);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void print_animated_red_coin(s16 x, s16 y) {
    s32 globalTimer = gGlobalTimer;

    create_dl_translation_matrix(MENU_MTX_PUSH, x, y, 0);
    create_dl_scale_matrix(MENU_MTX_NOPUSH, 0.2f, 0.2f, 1.0f);
    gDPSetRenderMode(gDisplayListHead++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);

#ifdef IA8_30FPS_COINS
    switch (globalTimer & 0x7) {
        case 0: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_0     ); break;
        case 1: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_22_5  ); break;
        case 2: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_45    ); break;
        case 3: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_67_5  ); break;
        case 4: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_90    ); break;
        case 5: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_67_5_r); break;
        case 6: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_45_r  ); break;
        case 7: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_22_5_r); break;
    }
#else
    switch (globalTimer & 0x6) {
        case 0: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_front     ); break;
        case 2: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_tilt_right); break;
        case 4: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_side      ); break;
        case 6: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_tilt_left ); break;
    }
#endif

    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void render_pause_red_coins(void) {
    s8 x;//PENIS!!!!!!
    //you need you YOUSE I!!!!!!!

    //i will punish you by deleting your code fuckface.

    for (x = 0; x < gRedCoinsCollected; x++) {
        print_animated_red_coin(GFX_DIMENSIONS_FROM_RIGHT_EDGE(30) - x * 20, 16);
    }
}

/// By default, not needed as puppycamera has an option, but should you wish to revert that, you are legally allowed.

#if defined(WIDE) && !defined(PUPPYCAM)
void render_widescreen_setting(void) {
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    if (!gConfig.widescreen) {
        print_generic_string(10, 20, textCurrRatio43);
        print_generic_string(10,  7, textPressL);
    } else {
        print_generic_string(10, 20, textCurrRatio169);
        print_generic_string(10,  7, textPressL);
    }
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    if (gPlayer1Controller->buttonPressed & L_TRIG){
        gConfig.widescreen ^= 1;
        save_file_set_widescreen_mode(gConfig.widescreen);
    }
}
#endif

#if defined(VERSION_JP) || defined(VERSION_SH)
    #define CRS_NUM_X1 93
#elif defined(VERSION_US)
    #define CRS_NUM_X1 100
#elif defined(VERSION_EU)
    #define CRS_NUM_X1 get_string_width(LANGUAGE_ARRAY(textCourse)) + 51
#endif

#ifdef VERSION_EU
    #define TXT_COURSE_X      48
    #define TXT_STAR_X        89
    #define ACT_NAME_X        107
    #define LVL_NAME_X        108
    #define SECRET_LVL_NAME_X get_str_x_pos_from_center(159, &courseName[3], 10.0f)
    #define MYSCORE_X         48
#else
    #define TXT_COURSE_X      63
    #define TXT_STAR_X        98
    #define ACT_NAME_X        116
    #define LVL_NAME_X        117
    #define SECRET_LVL_NAME_X 94
    #define MYSCORE_X         62
#endif

void render_pause_my_score_coins(void) {
    u8 textCourse[] = { TEXT_COURSE };
    u8 textMyScore[] = { TEXT_MY_SCORE };
    u8 textStar[] = { TEXT_STAR };
    u8 textUnfilledStar[] = { TEXT_UNFILLED_STAR };

    u8 strCourseNum[4];

    void **courseNameTbl = segmented_to_virtual(languageTable[gInGameLanguage][1]);
    void    **actNameTbl = segmented_to_virtual(languageTable[gInGameLanguage][2]);

    u8 courseIndex = COURSE_NUM_TO_INDEX(gCurrCourseNum);
    u8 starFlags = save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(gCurrCourseNum));

    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);

    if (courseIndex <= COURSE_NUM_TO_INDEX(COURSE_STAGES_MAX)) {
        print_hud_my_score_coins(1, gCurrSaveFileNum - 1, courseIndex, 178, 103);
        print_hud_my_score_stars(gCurrSaveFileNum - 1, courseIndex, 118, 103);
    }

    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);

    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);

    if (courseIndex <= COURSE_NUM_TO_INDEX(COURSE_STAGES_MAX)
        && (save_file_get_course_star_count(gCurrSaveFileNum - 1, courseIndex) != 0)) {
        print_generic_string(MYSCORE_X, 121, LANGUAGE_ARRAY(textMyScore));
    }

    u8 *courseName = segmented_to_virtual(courseNameTbl[courseIndex]);

    if (courseIndex <= COURSE_NUM_TO_INDEX(COURSE_STAGES_MAX)) {
        print_generic_string(TXT_COURSE_X, 157, LANGUAGE_ARRAY(textCourse));
        int_to_str(gCurrCourseNum, strCourseNum);
        print_generic_string(CRS_NUM_X1, 157, strCourseNum);

        u8 *actName = segmented_to_virtual(actNameTbl[COURSE_NUM_TO_INDEX(gCurrCourseNum) * 7 + gDialogCourseActNum - 1]);

        if (starFlags & (1 << (gDialogCourseActNum - 1))) {
            print_generic_string(TXT_STAR_X, 140, textStar);
        } else {
            print_generic_string(TXT_STAR_X, 140, textUnfilledStar);
        }

        print_generic_string(ACT_NAME_X, 140, actName);
        print_generic_string(LVL_NAME_X, 157, &courseName[3]);
    } else {
        print_generic_string(SECRET_LVL_NAME_X, 157, &courseName[3]);
    }

    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

#define TXT1_X 3
#define TXT2_X 119
#define Y_VAL7 2

void render_pause_camera_options(s16 x, s16 y, s8 *index, s16 xIndex) {
    u8 textLakituMario[] = { TEXT_LAKITU_MARIO };
    u8 textLakituStop[] = { TEXT_LAKITU_STOP };
    u8 textNormalUpClose[] = { TEXT_NORMAL_UPCLOSE };
    u8 textNormalFixed[] = { TEXT_NORMAL_FIXED };

    handle_menu_scrolling(MENU_SCROLL_HORIZONTAL, index, 1, 2);

    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);

    print_generic_string(x +     14, y +  2, textLakituMario);
    print_generic_string(x + TXT1_X, y - 13, LANGUAGE_ARRAY(textNormalUpClose));
    print_generic_string(x +    124, y +  2, textLakituStop);
    print_generic_string(x + TXT2_X, y - 13, LANGUAGE_ARRAY(textNormalFixed));

    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    create_dl_translation_matrix(MENU_MTX_PUSH, ((*index - 1) * xIndex) + x, y + Y_VAL7, 0);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    switch (*index) {
        case CAM_SELECTION_MARIO:
            cam_select_alt_mode(CAM_SELECTION_MARIO);
            break;
        case CAM_SELECTION_FIXED:
            cam_select_alt_mode(CAM_SELECTION_FIXED);
            break;
    }
}

#define X_VAL8 4
#define Y_VAL8 2

void render_pause_course_options(s16 x, s16 y, s8 *index, s16 yIndex) {
    u8 textContinue[] = { TEXT_CONTINUE };
    u8 textExitCourse[] = { TEXT_EXIT_COURSE };
    u8 textCameraAngleR[] = { TEXT_CAMERA_ANGLE_R };

    handle_menu_scrolling(MENU_SCROLL_VERTICAL, index, 1, 2);

    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);

    print_generic_string(x + 10, y - 2, LANGUAGE_ARRAY(textContinue));
    print_generic_string(x + 10, y - 17, LANGUAGE_ARRAY(textExitCourse));

    if (*index != MENU_OPT_CAMERA_ANGLE_R) {
        // print_generic_string(x + 10, y - 33, LANGUAGE_ARRAY(textCameraAngleR));
        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

        create_dl_translation_matrix(MENU_MTX_PUSH, x - X_VAL8, (y - ((*index - 1) * yIndex)) - Y_VAL8, 0);

        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
        gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    }

    if (*index == MENU_OPT_CAMERA_ANGLE_R) {
        render_pause_camera_options(x - 42, y - 42, &gDialogCameraAngleIndex, 110);
    }
}

void render_pause_castle_menu_box(s16 x, s16 y) {
    create_dl_translation_matrix(MENU_MTX_PUSH, x - 78, y - 32, 0);
    create_dl_scale_matrix(MENU_MTX_NOPUSH, 1.2f, 0.8f, 1.0f);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 105);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    create_dl_translation_matrix(MENU_MTX_PUSH, x + 6, y - 28, 0);
    create_dl_rotation_matrix(MENU_MTX_NOPUSH, DEFAULT_DIALOG_BOX_ANGLE, 0, 0, 1.0f);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    create_dl_translation_matrix(MENU_MTX_PUSH, x - 9, y - 101, 0);
    create_dl_rotation_matrix(MENU_MTX_NOPUSH, 270.0f, 0, 0, 1.0f);
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void render_empty_box(s16 x, s16 y) {
    create_dl_translation_matrix(MENU_MTX_PUSH, x - 78, y - 32, 0);
    create_dl_scale_matrix(MENU_MTX_NOPUSH, 1.2f, 0.8f, 1.0f);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 105);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void highlight_last_course_complete_stars(void) {
    u8 doneCourseIndex;

    if (gLastCompletedCourseNum == COURSE_NONE) {
        doneCourseIndex = COURSE_NUM_TO_INDEX(COURSE_MIN);
    } else {
        doneCourseIndex = COURSE_NUM_TO_INDEX(gLastCompletedCourseNum);

        if (doneCourseIndex >= COURSE_NUM_TO_INDEX(COURSE_BONUS_STAGES)) {
            doneCourseIndex = COURSE_NUM_TO_INDEX(COURSE_BONUS_STAGES);
        }
    }

    gDialogLineNum = doneCourseIndex;
}

void print_hud_pause_colorful_str(void) {
    u8 textPause[] = { TEXT_PAUSE };

    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);

    print_hud_lut_string(HUD_LUT_GLOBAL, 150, 4, textPause);

    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);
}

u8 MainCourseWarpTable[] = {
    LEVEL_BOB,
    LEVEL_WF,
    LEVEL_JRB,
    //switched!
    LEVEL_BBH,
    LEVEL_CCM,
    //switched!
    LEVEL_HMC,
    LEVEL_LLL,
    LEVEL_SSL,
    LEVEL_DDD,
    LEVEL_SL,
    LEVEL_WDW,
    LEVEL_TTM,
    LEVEL_THI,
    LEVEL_TTC,
    LEVEL_RR,
};

void render_pause_castle_course_stars(s16 x, s16 y, s16 fileIndex, s16 courseIndex) {
    s16 hasStar = 0;

    u8 str[COURSE_STAGES_COUNT * 2];

    u8 textStar[] = { TEXT_STAR };

    u8 starFlags = save_file_get_star_flags(fileIndex, courseIndex);
    u16 starCount = save_file_get_course_star_count(fileIndex, courseIndex);

    u16 nextStar = 0;

    if (starFlags & STAR_FLAG_ACT_100_COINS) {
        starCount--;
        print_generic_string(x + 89, y - 5, textStar);
    }

    while (hasStar != starCount) {
        if (starFlags & (1 << nextStar)) {
            str[nextStar * 2] = DIALOG_CHAR_STAR_FILLED;
            hasStar++;
        } else {
            str[nextStar * 2] = DIALOG_CHAR_STAR_OPEN;
        }

        str[nextStar * 2 + 1] = DIALOG_CHAR_SPACE;
        nextStar++;
    }

    if (starCount == nextStar && starCount != 6) {
        str[nextStar * 2] = DIALOG_CHAR_STAR_OPEN;
        str[nextStar * 2 + 1] = DIALOG_CHAR_SPACE;
        nextStar++;
    }

    str[nextStar * 2] = DIALOG_CHAR_TERMINATOR;

    print_generic_string(x + 14, y + 13, str);
}

void render_pause_castle_main_strings(s16 x, s16 y) {
    void **courseNameTbl = segmented_to_virtual(languageTable[gInGameLanguage][1]);

    u8 textCoin[] = { TEXT_COIN_X };

    void *courseName;

    u8 strVal[8];
    s16 prevCourseIndex = gDialogLineNum;


    handle_menu_scrolling(
        MENU_SCROLL_VERTICAL, &gDialogLineNum,
        COURSE_NUM_TO_INDEX(COURSE_MIN) - 1, COURSE_NUM_TO_INDEX(COURSE_BONUS_STAGES) + 1
    );

    if (gDialogLineNum == COURSE_NUM_TO_INDEX(COURSE_BONUS_STAGES) + 1) {
        gDialogLineNum = COURSE_NUM_TO_INDEX(COURSE_MIN); // Exceeded max, set to min
    }

    if (gDialogLineNum == COURSE_NUM_TO_INDEX(COURSE_MIN) - 1) {
        gDialogLineNum = COURSE_NUM_TO_INDEX(COURSE_BONUS_STAGES); // Exceeded min, set to max
    }

    if (gDialogLineNum != COURSE_NUM_TO_INDEX(COURSE_BONUS_STAGES)) {
        while (save_file_get_course_star_count(gCurrSaveFileNum - 1, gDialogLineNum) == 0) {
            if (gDialogLineNum >= prevCourseIndex) {
                gDialogLineNum++;
            } else {
                gDialogLineNum--;
            }

            if (gDialogLineNum == COURSE_NUM_TO_INDEX(COURSE_STAGES_MAX) + 1
             || gDialogLineNum == COURSE_NUM_TO_INDEX(COURSE_MIN) - 1) {
                gDialogLineNum = COURSE_NUM_TO_INDEX(COURSE_BONUS_STAGES);
                break;
            }
        }
    }

    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);

    if (gDialogLineNum <= COURSE_NUM_TO_INDEX(COURSE_STAGES_MAX)) { // Main courses
        courseName = segmented_to_virtual(courseNameTbl[gDialogLineNum]);
        render_pause_castle_course_stars(x, y, gCurrSaveFileNum - 1, gDialogLineNum);
        print_generic_string(x + 34, y - 5, textCoin);

        int_to_str(save_file_get_course_coin_score(gCurrSaveFileNum - 1, gDialogLineNum), strVal);
        print_generic_string(x + 54, y - 5, strVal);

        //only render if not on agamemnon
        if (save_file_get_progression() != PROG_ON_AGAMEMNON) {
            //render the "press A to go to level" thing
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, gDialogTextAlpha);
            print_generic_string(x-18, y-46, txt_warp);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
            print_generic_string(x-17, y-45, txt_warp);

            if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                level_set_transition(0, 0);
                play_sound(SOUND_MENU_PAUSE_CLOSE, gGlobalSoundSource);
                gMenuMode = -1;
                gDialogBoxState = DIALOG_STATE_OPENING;

                initiate_warp(MainCourseWarpTable[gDialogLineNum], 1, 0x0A, 0);
                fade_into_special_warp(0, 0);
            }
        }
    } else { // Castle secret stars
        u8 textStarX[] = { TEXT_STAR_X };
        courseName = segmented_to_virtual(courseNameTbl[COURSE_MAX]);
        print_generic_string(x + 40, y + 13, textStarX);
        int_to_str(save_file_get_total_star_count(gCurrSaveFileNum - 1,
                                                  COURSE_NUM_TO_INDEX(COURSE_BONUS_STAGES),
                                                  COURSE_NUM_TO_INDEX(COURSE_MAX)),
                                                  strVal);
        print_generic_string(x + 60, y + 13, strVal);
    }

    print_generic_string(x - 9, y + 30, courseName);

    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

s8 gCourseCompleteCoinsEqual = FALSE;
s32 gCourseDoneMenuTimer = 0;
s32 gCourseCompleteCoins = 0;
s8 gHudFlash = HUD_FLASH_NONE;

s8 tab_index = 0;
u16 menu_sintimer = 0;
s8 mindex = 0;

#define btxoff 50

void add_tab(u8 tab_to_add) {
    if (tablist_count < 5) {
        tablist[tablist_count] = tab_to_add;
        tablist_count++;
    }

}

void build_tabs(void) {
    tablist_count = 0;
    add_tab(0);
    /*
    //add the magic tab if wearing wizard hat or cheat enabled
    if ((gMarioState->Cheats & (1 << 3))||(0)) {
        //add_tab(4);//magic
    }
    //MAGIC TAB SCRAPPED
    */

    if (gCurrCourseNum >= COURSE_MIN && gCurrCourseNum <= COURSE_MAX) {
        //course
        if (gMarioState->nearVendor > 0) {
            //can equip badges when near vendors
            add_tab(1);
        }
        if (save_file_check_progression(PROG_POSTPOST_GAME)) {
            add_tab(5);//cheats
        }
    } else {
        //castle
        add_tab(1);
        if (gMarioState->Level != 8) {
            add_tab(2);
        }

        if (save_file_check_progression(PROG_POSTPOST_GAME)) {
            add_tab(5);//cheats
        }
    }

    add_tab(3);
}

#define total_spells 3
#define vpxo 70
#define vpyo 72
f32 winpercent;


#define badge_location_x 42+((i%8)*34)
#define badge_location_y (224+soffset)-((i/8)*34)

//for level up message.
u8 lvbuf[4];

s32 render_pause_courses_and_castle(void) {
    s16 index;
    s8 soffset;
    u16 i;
    f32 sine;
    s8 tab;
    u8 *changetext;
    u16 prog_thing;
    u16 prog_max;
    u32 hour = save_file_get_time()/3600;
    u32 minute = (save_file_get_time()/60)%60;
    u32 second = save_file_get_time()%60;

    menu_sintimer += 1200;
    sine = sins(menu_sintimer);
    if (tab_index > tablist_count) {
        tab_index = tablist_count-1;
    }
    tab = tablist[tab_index];

    if (gDialogBoxState == DIALOG_STATE_OPENING) {
        gDialogLineNum = MENU_OPT_DEFAULT;
        gDialogTextAlpha = 0;
        level_set_transition(-1, NULL);

        play_sound(SOUND_MENU_PAUSE_OPEN, gGlobalSoundSource);
        mindex = 0;//reset menu index when opening
        tab_index = 0;//also set tab to 0 when opening

        build_tabs();
        tab = tablist[tab_index];

        progress_table[0] = save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1);
        progress_table[1] = 120;
        progress_table[2] = count_u16_bits( save_file_get_costume_unlock() );
        progress_table[3] = 15;
        progress_table[4] = count_u16_bits(save_file_get_wallet_unlock());
        progress_table[5] = 12;
        progress_table[6] = count_u32_bits( save_file_get_badge_unlock() );
        progress_table[7] = 24;
        progress_table[8] = gMarioState->Level;
        progress_table[9] = 8;
        progress_table[10] = ((save_file_get_flags() & SAVE_FLAG_HAVE_YELLOW)>0)+((save_file_get_flags() & SAVE_FLAG_HAVE_VANISH_CAP)>0)+((save_file_get_flags() & SAVE_FLAG_HAVE_METAL_CAP)>0)+((save_file_get_flags() & SAVE_FLAG_HAVE_WING_CAP)>0);
        progress_table[11] = 4;

        prog_thing = progress_table[0]+progress_table[2]+progress_table[4]+progress_table[6]+progress_table[8]+progress_table[10];
        prog_max = progress_table[1]+progress_table[3]+progress_table[5]+progress_table[7]+progress_table[9]+progress_table[11];
        winpercent = ((f32)prog_thing/(f32)prog_max)*100.0f;

        if ((s32)winpercent >= 100) {
            //At 100% completion, initiate post post game mode
            if (!save_file_check_progression(PROG_POSTPOST_GAME)) {
                save_file_set_progression(PROG_POSTPOST_GAME);
                save_file_do_save(gCurrSaveFileNum - 1);
            }
        }

        if (gCurrCourseNum >= COURSE_MIN
         && gCurrCourseNum <= COURSE_MAX) {
            change_dialog_camera_angle();
            gDialogBoxState = DIALOG_STATE_VERTICAL;
        } else {
            highlight_last_course_complete_stars();
            gDialogBoxState = DIALOG_STATE_HORIZONTAL;
        }
    }

    switch(tab) {
        case 0:
            switch (gDialogBoxState) {
                case DIALOG_STATE_VERTICAL:
                    shade_screen();
                    render_pause_my_score_coins();
                    //render_pause_red_coins();
                    //HA HA HA. Deleted, bitch. How does it feel?
#ifndef DISABLE_EXIT_COURSE
#ifdef EXIT_COURSE_WHILE_MOVING
                    if ((gMarioStates[0].action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER | ACT_FLAG_PAUSE_EXIT))
                        || (gMarioStates[0].pos[1] <= gMarioStates[0].floorHeight))
#else
                    if (gMarioStates[0].action & ACT_FLAG_PAUSE_EXIT)
#endif
                    {
                        render_pause_course_options(99, 93, &gDialogLineNum, 15);
                    }
#endif

                    if (gPlayer3Controller->buttonPressed & (A_BUTTON | START_BUTTON)) {
                        level_set_transition(0, NULL);
                        play_sound(SOUND_MENU_PAUSE_CLOSE, gGlobalSoundSource);
                        gDialogBoxState = DIALOG_STATE_OPENING;
                        gMenuMode = MENU_MODE_NONE;

                        if (gDialogLineNum == MENU_OPT_EXIT_COURSE) {
                            //restore hp and mana on course exit
                            gMarioState->health = 255 + (255*gMarioState->numMaxHP);
                            gMarioState->numBadgePoints = gMarioState->numMaxFP;
                            index = gDialogLineNum;
                        } else { // MENU_OPT_CONTINUE or MENU_OPT_CAMERA_ANGLE_R
                            index = MENU_OPT_DEFAULT;
                        }

                        return index;
                    }
                    break;
                case DIALOG_STATE_HORIZONTAL:
                    shade_screen();
                    render_pause_castle_menu_box(160+vpxo, 143+vpyo);
                    render_pause_castle_main_strings(104+vpxo, 60+vpyo);


                    //print game progress
                    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
                        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, gDialogTextAlpha);
                        int_to_str_spaces((s32)winpercent,number_text);
                        string_insert(11,3,number_text,txt_prog1);
                        print_generic_string(23, 184, txt_prog1);

                        int_to_str_time(hour,minute,second,&number_text);
                        print_generic_string(23, 20, number_text);

                        for (i=0;i<6;i++) {
                            int_to_str_slash(progress_table[i*2], progress_table[(i*2)+1], number_text);
                            print_generic_string(84, 169-(i*16), number_text);
                        }

                        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
                        if (save_file_check_progression(PROG_POSTPOST_GAME)) {
                            gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, gDialogTextAlpha);
                            }
                        print_generic_string(24, 185, txt_prog1);

                        int_to_str_time(hour,minute,second,&number_text);
                        print_generic_string(24, 21, number_text);

                        for (i=0;i<6;i++) {
                            int_to_str_slash(progress_table[i*2], progress_table[(i*2)+1], number_text);
                            print_generic_string(85, 170-(i*16), number_text);
                        }

                    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
                    break;
            }

            if (gDialogTextAlpha < 250) {
                gDialogTextAlpha += 25;
            }
            break;
        case 1:
            shade_screen();

            //CONTROL
            if ((gPlayer1Controller->rawStickX > 60)&&(letgo == FALSE)) {
                gMarioState->numBadgeSelect ++;
                gMarioState->numBadgeSelect = (24+gMarioState->numBadgeSelect)%24;
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
                letgo = TRUE;
                }
            if ((gPlayer1Controller->rawStickX < -60)&&(letgo == FALSE)) {
                gMarioState->numBadgeSelect --;
                gMarioState->numBadgeSelect = (24+gMarioState->numBadgeSelect)%24;
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
                letgo = TRUE;
                }
            if ((gPlayer1Controller->rawStickY > 60)&&(letgo == FALSE)) {
                gMarioState->numBadgeSelect -=8;
                gMarioState->numBadgeSelect = (24+gMarioState->numBadgeSelect)%24;
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
                letgo = TRUE;
                }
            if ((gPlayer1Controller->rawStickY < -60)&&(letgo == FALSE)) {
                gMarioState->numBadgeSelect +=8;
                gMarioState->numBadgeSelect = (24+gMarioState->numBadgeSelect)%24;
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
                letgo = TRUE;
                }
            if ((gPlayer1Controller->rawStickX > -60)&&(gPlayer1Controller->rawStickX < 60)&&(gPlayer1Controller->rawStickY > -60)&&(gPlayer1Controller->rawStickY < 60)) {
                letgo = FALSE;
                }

            if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                if (save_file_get_badge_unlock() & (1<<gMarioState->numBadgeSelect)) {


                    if (save_file_get_badge_equip() & (1<<gMarioState->numBadgeSelect)) {
                        save_file_set_badge_unequip( (1<<gMarioState->numBadgeSelect) );
                        play_sound(SOUND_MENU_MESSAGE_DISAPPEAR, gGlobalSoundSource);
                        gMarioState->numEquippedBadges --;
                        gMarioState->numMaxBP = UPGRADE_TABLE[gMarioState->Level][3] + get_evil_badge_bonus();


                        if (!(gMarioState->Cheats & (1 << 6))) {
                            if (gMarioState->numEquippedBadges > gMarioState->numMaxBP) {
                                //badge overflow! unequip all badges.
                                gMarioState->numEquippedBadges = 0;
                                save_file_set_badge_unequip_all();
                            }
                        }
                    }else{//not equppied, therefore equip
                        if ((gMarioState->numEquippedBadges < gMarioState->numMaxBP)||(gMarioState->Cheats & (1 << 6))) {
                            save_file_set_badge_equip( (1<<gMarioState->numBadgeSelect) );
                            play_sound(SOUND_MENU_MESSAGE_APPEAR, gGlobalSoundSource);
                            gMarioState->numEquippedBadges ++;

                            gMarioState->numMaxBP = UPGRADE_TABLE[gMarioState->Level][3] + get_evil_badge_bonus();
                            }
                            else
                            {
                            play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                            }
                        }
                    }
                    else
                    {
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                    }
                }

            /*
            if (gPlayer1Controller->buttonPressed == Z_TRIG) {
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
                save_file_set_badge_unlock( (1<<gMarioState->numBadgeSelect) );
                }
            */

            //print_text_fmt_int(20, 56, "%d" , (save_file_get_badge_equip() & (1<<gMarioState->numBadgeSelect)));

            //MysteryBadge_Plane_001_mesh

            //print badge capacity
            print_text_fmt_int2(90, 30, "BP %dQ%d", gMarioState->numEquippedBadges, gMarioState->numMaxBP);

            for (i=0;i<24;i++) {
                soffset = -40;
                if (i == gMarioState->numBadgeSelect) {
                    soffset = -40+(sine*4.0f);
                    }

                if (save_file_get_badge_unlock() & (1<<i)) {
                    display_icon(bicon_table[i], badge_location_x, badge_location_y );
                    }else{
                    display_icon(&MysteryBadge_Plane_001_mesh, badge_location_x, badge_location_y);
                    }
                if ((save_file_get_badge_equip() & (1<<i))) {
                    display_icon(&bE_Plane_001_mesh, badge_location_x, badge_location_y);
                    }
            }


            //print badge info if badge is unlocked
            if (save_file_get_badge_unlock() & (1<<gMarioState->numBadgeSelect)) {
                gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
                print_generic_string(get_str_x_pos_from_center(160,badgenames[gMarioState->numBadgeSelect],0.0f)-1, 125-1-btxoff, badgenames[gMarioState->numBadgeSelect]);
                print_generic_string(get_str_x_pos_from_center(160,badgedescs[gMarioState->numBadgeSelect],0.0f)-1, 108-1-btxoff, badgedescs[gMarioState->numBadgeSelect]);
                gDPSetEnvColor(gDisplayListHead++, badgecolors[gMarioState->numBadgeSelect][0], badgecolors[gMarioState->numBadgeSelect][1], badgecolors[gMarioState->numBadgeSelect][2], 255);
                print_generic_string(get_str_x_pos_from_center(160,badgenames[gMarioState->numBadgeSelect],0.0f), 125-btxoff, badgenames[gMarioState->numBadgeSelect]);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                print_generic_string(get_str_x_pos_from_center(160,badgedescs[gMarioState->numBadgeSelect],0.0f), 108-btxoff, badgedescs[gMarioState->numBadgeSelect]);
                gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
                }
        break;
        case 2://upgradestation
            shade_screen();
            render_hud_power_meter();
            print_text_fmt_int(25+(gMarioState->numMaxHP*8), 20, "BP %d", gMarioState->numMaxBP);

            gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);

            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
            
            print_generic_string(30,140,upgradetext);
            if ((gMarioState->numGlobalCoins >= UPGRADE_TABLE[gMarioState->Level+1][0])&&(gMarioState->numStars>=UPGRADE_TABLE[gMarioState->Level+1][1])) {
                print_generic_string(30,75,upgradeyes);
            } else {
                print_generic_string(30,75,upgradeno);
            }

            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);

            print_generic_string(31,141,upgradetext);
            if ((gMarioState->numGlobalCoins >= UPGRADE_TABLE[gMarioState->Level+1][0])&&(gMarioState->numStars>=UPGRADE_TABLE[gMarioState->Level+1][1])) {
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(31,76,upgradeyes);
            } else {
                gDPSetEnvColor(gDisplayListHead++, 255, 0, 0, 255);
                print_generic_string(31,76,upgradeno);
            }

            gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

            print_text_fmt_int2(30, 100, "COST $%d ^%d", UPGRADE_TABLE[gMarioState->Level+1][0], UPGRADE_TABLE[gMarioState->Level+1][1]);
            if (gPlayer1Controller->buttonPressed & (A_BUTTON|B_BUTTON)) {
                if ((gMarioState->numGlobalCoins >= UPGRADE_TABLE[gMarioState->Level+1][0])&&(gMarioState->numStars>=UPGRADE_TABLE[gMarioState->Level+1][1])) {
                    
                    play_sound(SOUND_CUSTOM_PEACH_SOMETHING_SPECIAL, gGlobalSoundSource);

                    gMarioState->numGlobalCoins -= UPGRADE_TABLE[gMarioState->Level+1][0];
                    gMarioState->Level++;
                    gMarioState->numMaxHP = UPGRADE_TABLE[gMarioState->Level][2];
                    gMarioState->numMaxFP = UPGRADE_TABLE[gMarioState->Level][2];
                    gMarioState->numMaxBP = UPGRADE_TABLE[gMarioState->Level][3] + get_evil_badge_bonus();
                    save_file_set_stats();
                    save_file_do_save(gCurrSaveFileNum - 1);

                    int_to_str(gMarioState->Level,&lvbuf);
                    rtext_insert_pointer[0] = lvbuf;
                    run_event(EVENT_LVUP);
                    
                    gMarioState->healCounter = 99;
                    gMarioState->numBadgePoints = gMarioState->numMaxFP;

                    level_set_transition(0, 0);
                    gMenuMode = -1;
                    gDialogBoxState = DIALOG_STATE_OPENING;
                    return 1;
                }
            }

        break;
        case 3://options menu
            shade_screen();

            if ((gPlayer1Controller->rawStickY > 60)&&(letgo == FALSE)) {
                mindex--;
                if (mindex < 0) {
                    mindex = 6;
                }
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
                letgo = TRUE;
                }
            if ((gPlayer1Controller->rawStickY < -60)&&(letgo == FALSE)) {
                mindex++;
                if (mindex > 6) {
                    mindex = 0;
                }
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
                letgo = TRUE;
                }
            if ((gPlayer1Controller->rawStickX > -60)&&(gPlayer1Controller->rawStickX < 60)&&(gPlayer1Controller->rawStickY > -60)&&(gPlayer1Controller->rawStickY < 60)) {
                letgo = FALSE;
                }

            create_dl_translation_matrix(MENU_MTX_PUSH, 22, 181-(16*mindex), 0);
            create_dl_scale_matrix(MENU_MTX_NOPUSH, 1.5f, 0.2f, 1.0f);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 120+(sine*90));
            gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
            //is toggled on??
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
            print_generic_string(44,165, optiontext);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
            print_generic_string(45,166, optiontext);


            for (i=0;i<7;i++) {
                changetext = txt_off;
                if (gMarioState->Options &  (1 << i)) {
                    changetext = txt_on;
                }

                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
                print_generic_string(24,165-(i*16), changetext);
                gDPSetEnvColor(gDisplayListHead++, 255, 0, 0, 255);
                if (gMarioState->Options &  (1 << i)) {
                    gDPSetEnvColor(gDisplayListHead++, 0, 255, 0, 255);
                }
                print_generic_string(25,166-(i*16), changetext);
            }

            gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

            //do cheats
            if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                gMarioState->Options ^= (1 << mindex);
                save_file_set_stats();
            }

        break;
        case 4://magic
            shade_screen();
            render_hud_power_meter();

            if ((gPlayer1Controller->rawStickY > 60)&&(letgo == FALSE)) {
                mindex--;
                if (mindex < 0) {
                    mindex = total_spells-1;
                }
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
                letgo = TRUE;
                }
            if ((gPlayer1Controller->rawStickY < -60)&&(letgo == FALSE)) {
                mindex++;
                if (mindex > total_spells-1) {
                    mindex = 0;
                }
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
                letgo = TRUE;
                }
            if ((gPlayer1Controller->rawStickX > -60)&&(gPlayer1Controller->rawStickX < 60)&&(gPlayer1Controller->rawStickY > -60)&&(gPlayer1Controller->rawStickY < 60)) {
                letgo = FALSE;
                }

            create_dl_translation_matrix(MENU_MTX_PUSH, 22, 181-(16*mindex), 0);
            create_dl_scale_matrix(MENU_MTX_NOPUSH, 1.5f, 0.2f, 1.0f);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 120+(sine*90));
            gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
            //spell cost
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
            print_generic_string(34,165, magictext);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
            print_generic_string(35,166, magictext);
            //spell desc
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
            print_generic_string(24,165, magictext_c);
            gDPSetEnvColor(gDisplayListHead++, 140, 140, 255, 255);
            print_generic_string(25,166, magictext_c);

            gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

            //do spells
            if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                switch(mindex) {
                    case 0:
                        if (gMarioState->numBadgePoints > 1) {
                            gMarioState->health += 768;
                            gMarioState->numBadgePoints -= 2;
                        }
                    break;
                    case 1:
                        if (gMarioState->numBadgePoints > 0) {
                            gMarioState->numBadgePoints -= 1;
                            gMarioState->flags |= MARIO_VANISH_CAP;
                            gMarioState->flags &= ~MARIO_CAP_ON_HEAD;
                            gMarioState->capTimer = 500;
                            gMarioState->flags |= MARIO_CAP_ON_HEAD;
                            mario_update_hitbox_and_cap_model(gMarioState);
                        }
                    break;
                    case 2:
                        if (gMarioState->numBadgePoints > 2) {
                            gMarioState->numBadgePoints -= 3;
                            gMarioState->flags |= (MARIO_METAL_CAP|MARIO_VANISH_CAP);
                            gMarioState->flags &= ~MARIO_CAP_ON_HEAD;
                            gMarioState->capTimer = 500;
                            gMarioState->flags |= MARIO_CAP_ON_HEAD;
                            mario_update_hitbox_and_cap_model(gMarioState);
                        }
                    break;
                    case 3:
                        if (gMarioState->numBadgePoints > 0) {
                            gMarioState->numBadgePoints -= 1;
                        }
                    break;
                }
            }
        break;
        case 5://cheat menu
            shade_screen();

            if ((gPlayer1Controller->rawStickY > 60)&&(letgo == FALSE)) {
                mindex--;
                if (mindex < 0) {
                    mindex = 7;
                }
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
                letgo = TRUE;
                }
            if ((gPlayer1Controller->rawStickY < -60)&&(letgo == FALSE)) {
                mindex++;
                if (mindex > 7) {
                    mindex = 0;
                }
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
                letgo = TRUE;
                }
            if ((gPlayer1Controller->rawStickX > -60)&&(gPlayer1Controller->rawStickX < 60)&&(gPlayer1Controller->rawStickY > -60)&&(gPlayer1Controller->rawStickY < 60)) {
                letgo = FALSE;
                }

            create_dl_translation_matrix(MENU_MTX_PUSH, 22, 181-(16*mindex), 0);
            create_dl_scale_matrix(MENU_MTX_NOPUSH, 1.5f, 0.2f, 1.0f);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 120+(sine*90));
            gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
            //is toggled on??
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
            print_generic_string(44,165, cheattext);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
            print_generic_string(45,166, cheattext);

            
            //cheat desc

            for (i=0;i<8;i++) {
                changetext = txt_off;
                if (gMarioState->Cheats &  (1 << i)) {
                    changetext = txt_on;
                }

                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
                print_generic_string(24,165-(i*16), changetext);
                gDPSetEnvColor(gDisplayListHead++, 255, 0, 0, 255);
                if (gMarioState->Cheats &  (1 << i)) {
                    gDPSetEnvColor(gDisplayListHead++, 0, 255, 0, 255);
                }
                print_generic_string(25,166-(i*16), changetext);
            }

            gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

            //do cheats
            if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                gMarioState->Cheats ^= (1 << mindex);
                build_tabs();
            }

        break;
    }

    if (gDialogBoxState != DIALOG_STATE_OPENING) {
        //tab control
        if (gPlayer1Controller->buttonPressed == R_TRIG) {
            mindex = 0;
            tab_index += 1;
            tab_index %= tablist_count;
        }
        if (gPlayer1Controller->buttonPressed == L_TRIG) {
            mindex = 0;
            tab_index -= 1;
            if (tab_index < 0) {
                tab_index = tablist_count-1;
            }
        }

        //exit control
        if (gPlayer3Controller->buttonPressed & START_BUTTON) {
            level_set_transition(0, 0);
            play_sound(SOUND_MENU_PAUSE_CLOSE, gGlobalSoundSource);
            gMenuMode = -1;
            gDialogBoxState = DIALOG_STATE_OPENING;

            return 1;
        }

        //print tab boxes
        for (i=0;i<5;i++) {
            create_dl_translation_matrix(MENU_MTX_PUSH, 19+(i*60), 226, 0);
            create_dl_scale_matrix(MENU_MTX_NOPUSH, .4f, 0.2f, 1.0f);
            gDPSetEnvColor(gDisplayListHead++, 20, 20, 20, 255);
            if (tab_index==i) {
                gDPSetEnvColor(gDisplayListHead++, 60, 60, 60, 255);
            }
            if (i > tablist_count-1) {
                gDPSetEnvColor(gDisplayListHead++, 20, 20, 20, 150);
            }
            gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
        }

        gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
        //print tab names
        for (i=0;i<tablist_count;i++) {
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
            print_generic_string(20+(i*60), 210, tabs[tablist[i]]);
        }
        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    }


    return MENU_OPT_NONE;
}

#define TXT_HISCORE_X 109
#define TXT_HISCORE_Y  36
#define TXT_CONGRATS_X 70
#define TXT_CONGRATS_Y 67

enum HUDCourseCompleteStringIDs {
    HUD_PRINT_HISCORE,
    HUD_PRINT_CONGRATULATIONS
};

void print_hud_course_complete_string(s8 str) {
    u8 textHiScore[] = { TEXT_HUD_HI_SCORE };
    u8 textCongratulations[] = { TEXT_HUD_CONGRATULATIONS };

    u8 colorFade = sins(gDialogColorFadeTimer) * 50.0f + 200.0f;

    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);
    gDPSetEnvColor(gDisplayListHead++, colorFade, colorFade, colorFade, 255);

    if (str == HUD_PRINT_HISCORE) {
        print_hud_lut_string(HUD_LUT_GLOBAL, TXT_HISCORE_X,  TXT_HISCORE_Y,  LANGUAGE_ARRAY(textHiScore));
    } else { // HUD_PRINT_CONGRATULATIONS
        print_hud_lut_string(HUD_LUT_GLOBAL, TXT_CONGRATS_X, TXT_CONGRATS_Y, LANGUAGE_ARRAY(textCongratulations));
    }

    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);
}

void print_hud_course_complete_coins(s16 x, s16 y, u8 maincourse) {
    u8 courseCompleteCoinsStr[4];
    u8 hudTextSymCoin[] = { GLYPH_COIN, GLYPH_SPACE };
    u8 hudTextSymX[] = { GLYPH_MULTIPLY, GLYPH_SPACE };

    if (maincourse) {
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);

    print_hud_lut_string(HUD_LUT_GLOBAL, x +  0, y, hudTextSymCoin);
    print_hud_lut_string(HUD_LUT_GLOBAL, x + 16, y, hudTextSymX);

    int_to_str(gCourseCompleteCoins, courseCompleteCoinsStr);
    print_hud_lut_string(HUD_LUT_GLOBAL, x + 32, y, courseCompleteCoinsStr);

    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);
    } else {
        print_text_fmt_int2(x, y, ",%dQ%d", gMarioState->numGlobalCoins, gMarioState->numMaxGlobalCoins);
    }

    if (gCourseCompleteCoins >= gHudDisplay.coins) {
        gCourseCompleteCoinsEqual = TRUE;
        gCourseCompleteCoins = gHudDisplay.coins;

        if (gGotFileCoinHiScore) {
            print_hud_course_complete_string(HUD_PRINT_HISCORE);
        }
    } else {
        if ((gCourseDoneMenuTimer & 1) || gHudDisplay.coins > 70) { //above 70 coins is every frame, below 70 coins is every other frame
            gCourseCompleteCoins++;

            if (gMarioState->numGlobalCoins < gMarioState->numMaxGlobalCoins) {
                gMarioState->numGlobalCoins++;
                if (count_u16_bits(save_file_get_wallet_unlock()) >= 12) { //If you collect all 12 wallets, you get a bonus.
                    gMarioState->numGlobalCoins++;
                    if (gMarioState->numGlobalCoins > gMarioState->numMaxGlobalCoins) {
                        //slightly redundant clamp, whateverz
                        gMarioState->numGlobalCoins = gMarioState->numMaxGlobalCoins;
                    }
                }
                save_file_set_stats();
            }

            play_sound(SOUND_MENU_YOSHI_GAIN_LIVES, gGlobalSoundSource);

#ifndef DISABLE_LIVES
            // if (gCourseCompleteCoins && ((gCourseCompleteCoins % 50) == 0)) {
            //     play_sound(SOUND_GENERAL_COLLECT_1UP, gGlobalSoundSource);
            //     gMarioState->numLives++;
            // }
#endif
        }

        if ((gHudDisplay.coins == gCourseCompleteCoins) && gGotFileCoinHiScore) {
            play_sound(SOUND_MENU_HIGH_SCORE, gGlobalSoundSource);
        }
    }
}

void play_star_fanfare_and_flash_hud(s32 arg, u8 starNum) {
    if (gHudDisplay.coins == gCourseCompleteCoins && (gCurrCourseStarFlags & starNum) == 0 && gHudFlash == HUD_FLASH_NONE) {
        play_star_fanfare();
        gHudFlash = arg;
    }
}

#define TXT_NAME_X1 71
#define TXT_NAME_X2 TXT_NAME_X1 - 2
#define CRS_NUM_X2 104
#define CRS_NUM_X3 CRS_NUM_X2 - 2
#define TXT_CLEAR_X1 get_string_width(name) + 81
#define TXT_CLEAR_X2 TXT_CLEAR_X1 - 2

void render_course_complete_lvl_info_and_hud_str(void) {
    u8 textCourse[] = { TEXT_COURSE };
    u8 textClear[] = { TEXT_CLEAR };
    u8 textSymStar[] = { GLYPH_STAR, GLYPH_SPACE };

    u8 *name;

    u8 strCourseNum[4];

    void **actNameTbl    = segmented_to_virtual(languageTable[gInGameLanguage][2]);
    void **courseNameTbl = segmented_to_virtual(languageTable[gInGameLanguage][1]);

    if (gLastCompletedCourseNum <= COURSE_STAGES_MAX) { // Main courses
        print_hud_course_complete_coins(65, 103,TRUE);
        print_text_fmt_int2(150, 121, ",%dQ%d", gMarioState->numGlobalCoins, gMarioState->numMaxGlobalCoins);
        play_star_fanfare_and_flash_hud(HUD_FLASH_STARS, (1 << (gLastCompletedStarNum - 1)));

        // if (gLastCompletedStarNum == 7) {
        //     name = segmented_to_virtual(actNameTbl[COURSE_STAGES_MAX * 6 + 1]);
        // } else {
        name = segmented_to_virtual(actNameTbl[COURSE_NUM_TO_INDEX(gLastCompletedCourseNum) * 7 + gLastCompletedStarNum - 1]);
        // }

        // Print course number
        gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);

        int_to_str(gLastCompletedCourseNum, strCourseNum);

        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, gDialogTextAlpha);
        print_generic_string(65, 165, LANGUAGE_ARRAY(textCourse));
        print_generic_string(CRS_NUM_X2, 165, strCourseNum);

        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
        print_generic_string(63, 167, LANGUAGE_ARRAY(textCourse));
        print_generic_string(CRS_NUM_X3, 167, strCourseNum);

        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    } else if (gLastCompletedCourseNum == COURSE_BITDW || gLastCompletedCourseNum == COURSE_BITFS) { // Bowser courses
        name = segmented_to_virtual(courseNameTbl[COURSE_NUM_TO_INDEX(gLastCompletedCourseNum)]);

        // Print course name and clear text
        gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);

        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, gDialogTextAlpha);
        print_generic_string(TXT_NAME_X1, 130, name);
        print_generic_string(TXT_CLEAR_X1, 130, textClear);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
        print_generic_string(TXT_NAME_X2, 132, name);
        print_generic_string(TXT_CLEAR_X2, 132, textClear);
        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

        print_hud_course_complete_string(HUD_PRINT_CONGRATULATIONS);
        print_hud_course_complete_coins(118, 111,FALSE);
        play_star_fanfare_and_flash_hud(HUD_FLASH_KEYS, 0);
        return;
    } else { // Castle secret stars
        name = segmented_to_virtual(actNameTbl[COURSE_STAGES_MAX * 7]);

        print_hud_course_complete_coins(118, 130,FALSE);
        play_star_fanfare_and_flash_hud(HUD_FLASH_STARS, 1 << (gLastCompletedStarNum - 1));
    }

    // Print star glyph
    /*
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);

    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    if (gLastCompletedStarNum == 7) {
        if (gDialogTextAlpha > 200) {
            print_text_fmt_int(55,147,".",0);
        }
    } else {
        print_hud_lut_string(HUD_LUT_GLOBAL, 55, 77, textSymStar);
    }

    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);
    */

    //A cheap way to solve the problem of different levels having cosmic seeds, and different levels having regular stars,
    //is to not render the glyph at all! Kind of lazy, but CBA. Cosmic seed and power star distingishing is so hardcoded
    //it hurts. curse you artie!!! forcing me to do weird and unusual story progression! (it was worth it)

    // Print act name and catch text
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);

    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, gDialogTextAlpha);
    print_generic_string(76, 145, name);

    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    print_generic_string(74, 147, name);

    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

#define X_VAL9 x
#define TXT_SAVEOPTIONS_X x + 12
#define TXT_SAVECONT_Y 0
#define TXT_SAVEQUIT_Y 20
#define TXT_CONTNOSAVE_Y 40

void render_save_confirmation(s16 x, s16 y, s8 *index, s16 yPos) {
    u8 textSaveAndContinue[] = { TEXT_SAVE_AND_CONTINUE };
    u8 textSaveAndQuit[] = { TEXT_SAVE_AND_QUIT };
    // u8 textContinueWithoutSave[] = { TEXT_CONTINUE_WITHOUT_SAVING };

    handle_menu_scrolling(MENU_SCROLL_VERTICAL, index, 1, 2);

    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);

    print_generic_string(TXT_SAVEOPTIONS_X, y + TXT_SAVECONT_Y, LANGUAGE_ARRAY(textSaveAndContinue));
    print_generic_string(TXT_SAVEOPTIONS_X, y - TXT_SAVEQUIT_Y, LANGUAGE_ARRAY(textSaveAndQuit));
    // print_generic_string(TXT_SAVEOPTIONS_X, y - TXT_CONTNOSAVE_Y, LANGUAGE_ARRAY(textContinueWithoutSave));

    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

    create_dl_translation_matrix(MENU_MTX_PUSH, X_VAL9, y - ((*index - 1) * yPos), 0);

    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

s32 render_course_complete_screen(void) {
    switch (gDialogBoxState) {
        case DIALOG_STATE_OPENING:
            render_course_complete_lvl_info_and_hud_str();
            if (gCourseDoneMenuTimer > 100 && gCourseCompleteCoinsEqual) {
                gDialogBoxState = DIALOG_STATE_VERTICAL;
                level_set_transition(-1, NULL);
                gDialogTextAlpha = 0;
                gDialogLineNum = MENU_OPT_DEFAULT;
            }
            break;

        case DIALOG_STATE_VERTICAL:
            shade_screen();
            render_course_complete_lvl_info_and_hud_str();
            render_save_confirmation(100, 86, &gDialogLineNum, 20);

            if (gCourseDoneMenuTimer > 110 && (gPlayer3Controller->buttonPressed & (A_BUTTON | START_BUTTON))) {
                level_set_transition(0, NULL);
                play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
                gDialogBoxState = DIALOG_STATE_OPENING;
                gMenuMode = MENU_MODE_NONE;
                gCourseDoneMenuTimer = 0;
                gCourseCompleteCoins = 0;
                gCourseCompleteCoinsEqual = FALSE;
                gHudFlash = HUD_FLASH_NONE;

                gMarioState->numCoins = 0;
                gHudDisplay.coins = 0;

                return gDialogLineNum;
            }
            break;
    }

    if (gDialogTextAlpha < 250) {
        gDialogTextAlpha += 25;
    }

    gCourseDoneMenuTimer++;

    return MENU_OPT_NONE;
}

u8 intensity;

u8 text_precredits_1[] = {PRE_CREDITS_1};
u8 text_precredits_2[] = {PRE_CREDITS_2};
u8 text_precredits_3[] = {PRE_CREDITS_3};
u8 text_precredits_4[] = {PRE_CREDITS_4};
u8 text_precredits_5[] = {PRE_CREDITS_5};
u8 text_precredits_6[] = {PRE_CREDITS_6};
u8 text_precredits_7[] = {PRE_CREDITS_7};
u8 text_precredits_8[] = {PRE_CREDITS_8};
u8 text_precredits_9[] = {PRE_CREDITS_9};
u8 text_precredits_10[] = {PRE_CREDITS_10};
u8 text_precredits_11[] = {PRE_CREDITS_11};
u8 text_precredits_12[] = {PRE_CREDITS_12};
u8 text_precredits_13[] = {PRE_CREDITS_13};
u8 text_precredits_14[] = {PRE_CREDITS_14};
u8 text_precredits_15[] = {PRE_CREDITS_15};
u8 text_precredits_16[] = {PRE_CREDITS_16};
u8 text_precredits_17[] = {PRE_CREDITS_17};
u8 text_precredits_18[] = {PRE_CREDITS_18};


u8 *precredits_ptr[] = {
    &text_precredits_1,
    &text_precredits_2,
    &text_precredits_3,
    &text_precredits_4,
    &text_precredits_5,
    &text_precredits_6,
    &text_precredits_7,
    &text_precredits_8,
    &text_precredits_9,
    &text_precredits_10,
    &text_precredits_11,
    &text_precredits_12,
    &text_precredits_13,
    &text_precredits_14,
    &text_precredits_15,
    &text_precredits_16,
    &text_precredits_17,
    &text_precredits_18,
};

u8 start_precredits = FALSE;
u8 precredits_index = 0;
u16 precredits_timer = 0;
s16 precredits_alpha = 0;

void render_pre_credits() {
    if (!start_precredits) {
        precredits_index = 0;
        precredits_alpha = 0;
        precredits_timer = 0;
        return;
    }

    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, precredits_alpha);


    print_generic_string(get_str_x_pos_from_center(160,precredits_ptr[precredits_index],0), 50, precredits_ptr[precredits_index]);

    create_dl_scale_matrix(MENU_MTX_PUSH, 2.0f, 2.0f, 0.0f);
        print_generic_string(get_str_x_pos_from_center(80,precredits_ptr[precredits_index+1],0), 10, precredits_ptr[precredits_index+1]);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);



    precredits_timer++;
    if (precredits_timer < 150) {
        precredits_alpha += 4;
        if (precredits_alpha > 255) {
            precredits_alpha = 255;
        }
    } else {
        precredits_alpha -= 4;
        if (precredits_alpha < 0) {
            precredits_alpha = 0;
            precredits_timer = 0;
            precredits_index += 2;

            if (precredits_index >= 18) {
                start_precredits = FALSE;
            }
        }

    }

    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    return;
}

s32 render_menus_and_dialogs(void) {
    s32 mode = MENU_OPT_NONE;
    // s16 camangle;
    // struct Camera *camcam;

    create_dl_ortho_matrix();

    render_pre_credits();

    if (gMarioState->Options & (1<<OPT_MUSIC)) {
        fade_volume_scale(SEQ_PLAYER_LEVEL,100,1);
        }else{
        fade_volume_scale(SEQ_PLAYER_LEVEL,0,1);
        }

    //screen tint
    if (gCurrentArea->index == 0x04&&gCurrLevelNum==0x05) { //removing screen tint until further notice (exepct for bos)
        create_dl_translation_matrix(MENU_MTX_PUSH, 0, 400, 0);
        create_dl_scale_matrix(MENU_MTX_NOPUSH, 5.0f, 5.0f, 0.0f);
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 0);
        switch (gCurrLevelNum) {
            case 0x06:
            if (gCurrentArea->index == 0x01) {
                gDPSetEnvColor(gDisplayListHead++, 50, 0, 255, 12);
                }
            break;
            case 0x09:
            gDPSetEnvColor(gDisplayListHead++, 255, 30, 0, 45);
            break;
            case 0x05:
            gDPSetEnvColor(gDisplayListHead++, 0x2A, 0x89, 0x6B, 20);
            if (gCurrentArea->index == 0x04) {
                gDPSetEnvColor(gDisplayListHead++, 12, 6, 0, 100);
                if (gMarioState->BossHealth == 1) {
                    gDPSetEnvColor(gDisplayListHead++, 100, 6, 0, 100);
                    intensity = 0;
                    }
                if (gMarioState->BossHealth < 1) {
                    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, intensity);
                    if (intensity < 250) {
                        if (sCurrPlayMode == 0) {
                            intensity ++;
                            }
                        }
                        else
                        {
                        gMarioState->pos[0] = 0.0f;
                        gMarioState->pos[1] = 0.0f;
                        gMarioState->pos[2] = 0.0f;

                        gMarioState->marioObj->oPosX = gMarioState->pos[0];
                        gMarioState->marioObj->oPosY = gMarioState->pos[1];
                        gMarioState->marioObj->oPosZ = gMarioState->pos[2];

                        //camangle = gMarioState->area->camera->yaw;
                        //camcam = gMarioState->area->camera;
                        //change_area(0x05);
                        //gMarioState->area->camera->yaw = camangle;
                        //gMarioState->area->camera = camcam;

                        initiate_warp(LEVEL_CCM, 5, 0x0A, 0);
                        fade_into_special_warp(0, 0);
                        }
                    }
                }
            break;
            }
        gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
        gDPSetEnvColor(gDisplayListHead++, 255,255,255, 255);
        }
    //screen tint

    //portal screen tint
    if (gMarioState->PortalTint > 0.05f) {
        create_dl_translation_matrix(MENU_MTX_PUSH, 0, 400, 0);
        create_dl_scale_matrix(MENU_MTX_NOPUSH, 5.0f, 5.0f, 0.0f);
        gDPSetEnvColor(gDisplayListHead++, 0x77, 0x57, 0x92, (u8)(gMarioState->PortalTint*255.0f));

        gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
        gDPSetEnvColor(gDisplayListHead++, 255,255,255,255);

        gMarioState->PortalTint *= .96;
    }

    if (gMarioState->MenuToRender == 1) {
        render_empty_box(160, 183+70);
        gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        print_generic_string(90, 120+70, text1);
        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
        //print_text_fmt_int(100, 96+70, CostumeNames[gMarioState->CostumeID], 0);


        gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        print_hud_lut_string(HUD_LUT_GLOBAL, 84, 60, costume_text[gMarioState->CostumeID]);
        gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);
    }   


    gMarioState->GlobalPaused = TRUE;
    if (gMenuMode != -1) {//
        gMarioState->GlobalPaused = TRUE;
        switch (gMenuMode) {
            case MENU_MODE_UNUSED_0:
                mode = render_pause_courses_and_castle();
                break;
            case MENU_MODE_RENDER_PAUSE_SCREEN:
                mode = render_pause_courses_and_castle();
                break;
            case MENU_MODE_RENDER_COURSE_COMPLETE_SCREEN:
                mode = render_course_complete_screen();
                break;
            case MENU_MODE_UNUSED_3:
                mode = render_course_complete_screen();
                break;
        }

        gDialogColorFadeTimer = (s16) gDialogColorFadeTimer + 0x1000;
    } else if (gDialogID != DIALOG_NONE) {
        // The Peach "Dear Mario" message needs to be repositioned separately
        if (gDialogID == DIALOG_020) {
            print_peach_letter_message();
            return mode;
        }

        render_dialog_entries();
        gDialogColorFadeTimer = (s16) gDialogColorFadeTimer + 0x1000;
    }

    return mode;
}
