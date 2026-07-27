#include <PR/ultratypes.h>

#include "game/memory.h"
#include "game/segment2.h"
#include "game/segment7.h"
#include "engine/math_util.h"
#include "intro_geo.h"
#include "sm64.h"
#include "types.h"
#include "src/engine/math_util.h"

// frame counts for the zoom in, hold, and zoom out of title model
#define INTRO_STEPS_ZOOM_IN 20
#define INTRO_STEPS_HOLD_1 75
#define INTRO_STEPS_ZOOM_OUT 91

// intro geo bss
static s16 sIntroFrameCounter;
static s32 sTmCopyrightAlpha;


// u8 TitleState = 0;

f32 logo_opacity = 0.0f;
u8 rovert_logo_timer = 0;

/**
 * Geo callback to render the "Super Mario 64" logo on the title screen
 */
Gfx *geo_intro_super_mario_64_logo(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    struct GraphNode *graphNode = node;
    Gfx *dl = NULL;
    Gfx *dlIter = NULL;


    if (callContext != GEO_CONTEXT_RENDER) {
        sIntroFrameCounter = 0;
        // TitleState = 0;
        logo_opacity = 0.0f;
        rovert_logo_timer = 0;
    } else if (callContext == GEO_CONTEXT_RENDER) {

        // if (TitleState == 0) {
        //     return dl;
        // }

        f32 *scaleTable1 = segmented_to_virtual(intro_seg7_table_scale_1);
        f32 *scaleTable2 = segmented_to_virtual(intro_seg7_table_scale_2);
        SET_GRAPH_NODE_LAYER(graphNode->flags, LAYER_OPAQUE);
        Mtx *scaleMat = alloc_display_list(sizeof(*scaleMat));
        dl = alloc_display_list(9 * sizeof(*dl));
        dlIter = dl;
        Vec3f scale;

        // determine scale based on the frame counter
        if (sIntroFrameCounter >= 0 && sIntroFrameCounter < INTRO_STEPS_ZOOM_IN) {
            // zooming in
            vec3f_copy(scale, &scaleTable1[sIntroFrameCounter * 3]);
        } else if (sIntroFrameCounter >= INTRO_STEPS_ZOOM_IN && sIntroFrameCounter < INTRO_STEPS_HOLD_1) {
            // holding
            vec3_same(scale, 1.0f);
        } else if (sIntroFrameCounter >= INTRO_STEPS_HOLD_1 && sIntroFrameCounter < INTRO_STEPS_ZOOM_OUT) {
            // zooming out
            vec3f_copy(scale, &scaleTable2[(sIntroFrameCounter - INTRO_STEPS_HOLD_1) * 3]);
        } else {
            // disappeared
            vec3_zero(scale);
        }
        guScale(scaleMat, scale[0], scale[1], scale[2]);

        gSPMatrix(dlIter++, scaleMat, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);

        graphNode->flags = (graphNode->flags & 0xFF) | 0x100;
        gDPSetEnvColor(dlIter++, 255, 255, 255, 255);

        gSPDisplayList(dlIter++, &ts1_letter_R_mesh); //NEW
        gSPDisplayList(dlIter++, &ts4_MARIO_mesh); //NEW

        gSPPopMatrix(dlIter++, G_MTX_MODELVIEW);
        gSPEndDisplayList(dlIter);
    }
    return dl;
}

u8 yvel = 5;
u8 y = 80;

Gfx *geo_title_screen2(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    struct GraphNode *graphNode; // sp4c
    Gfx *displayList;            // sp48
    Gfx *displayListIter;        // sp44
    Mtx *scaleMat;               // sp40
    f32 *scaleTable1;            // sp3c
    f32 *scaleTable2;            // sp38
    f32 scaleX;                  // sp34
    f32 scaleY;                  // sp30
    f32 scaleZ;                  // sp2c
    graphNode = node;
    displayList = NULL;
    displayListIter = NULL;

    scaleTable1 = segmented_to_virtual(intro_seg7_table_scale_1);
    scaleTable2 = segmented_to_virtual(intro_seg7_table_scale_2);


    if (callContext != GEO_CONTEXT_RENDER) {
        sIntroFrameCounter = 0;
    } else if (callContext == GEO_CONTEXT_RENDER) {

        // if (TitleState == 0) {
        //     return displayList;
        // }

        graphNode->flags = (graphNode->flags & 0xFF) | 0x100;
        scaleMat = alloc_display_list(sizeof(*scaleMat));
        displayList = alloc_display_list(9 * sizeof(*displayList));
        displayListIter = displayList;

        if (sIntroFrameCounter >= 0 && sIntroFrameCounter < INTRO_STEPS_ZOOM_IN) {
            scaleX = scaleTable1[sIntroFrameCounter * 3];
            scaleY = scaleTable1[sIntroFrameCounter * 3 + 1];
            scaleZ = scaleTable1[sIntroFrameCounter * 3 + 2];
        } else if (sIntroFrameCounter >= INTRO_STEPS_ZOOM_IN && sIntroFrameCounter < INTRO_STEPS_HOLD_1) {
            scaleX = 1.0f;
            scaleY = 1.0f;
            scaleZ = 1.0f;
        } else if (sIntroFrameCounter >= INTRO_STEPS_HOLD_1
                   && sIntroFrameCounter < INTRO_STEPS_ZOOM_OUT) {
            scaleX = scaleTable2[(sIntroFrameCounter - INTRO_STEPS_HOLD_1) * 3];
            scaleY = scaleTable2[(sIntroFrameCounter - INTRO_STEPS_HOLD_1) * 3 + 1];
            scaleZ = scaleTable2[(sIntroFrameCounter - INTRO_STEPS_HOLD_1) * 3 + 2];
        } else {
            scaleX = 0.0f;
            scaleY = 0.0f;
            scaleZ = 0.0f;
        }

        y += yvel;
        if (y>80) {
            yvel --;
            }
            else
            {
            yvel ++;
            }

        guScale(scaleMat, scaleX, scaleY, scaleZ);
        gSPMatrix(displayListIter++, scaleMat, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);

        gDPSetEnvColor(displayListIter++, 255, 255, 255, 255);

        graphNode->flags = (graphNode->flags & 0xFF) | 0x500;
        gDPSetRenderMode(displayListIter++, G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);

        gSPDisplayList(displayListIter++, &ts2_grid_mesh);

        gSPPopMatrix(displayListIter++, G_MTX_MODELVIEW);
        gSPEndDisplayList(displayListIter);


        sIntroFrameCounter++;

        if (sIntroFrameCounter >= 0x13) {
            sTmCopyrightAlpha += 0x1a;
            if (sTmCopyrightAlpha >= 0x100) {
                sTmCopyrightAlpha = 0xFF;
            }
        }

    }
    return displayList;
}

Gfx *geo_title_screen3(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    struct GraphNode *graphNode; // sp4c
    Gfx *displayList;            // sp48
    Gfx *displayListIter;        // sp44
    Mtx *scaleMat;               // sp40
    f32 *scaleTable1;            // sp3c
    f32 *scaleTable2;            // sp38
    f32 scaleX;                  // sp34
    f32 scaleY;                  // sp30
    f32 scaleZ;                  // sp2c
    graphNode = node;
    displayList = NULL;
    displayListIter = NULL;
    scaleTable1 = segmented_to_virtual(intro_seg7_table_scale_1);
    scaleTable2 = segmented_to_virtual(intro_seg7_table_scale_2);

    if (callContext != GEO_CONTEXT_RENDER) {
        sIntroFrameCounter = 0;
    } else if (callContext == GEO_CONTEXT_RENDER) {

        // if (TitleState == 0) {
        //     return displayList;
        // }

        graphNode->flags = (graphNode->flags & 0xFF) | 0x100;
        scaleMat = alloc_display_list(sizeof(*scaleMat));
        displayList = alloc_display_list(9 * sizeof(*displayList));
        displayListIter = displayList;
        if (sIntroFrameCounter >= 0 && sIntroFrameCounter < INTRO_STEPS_ZOOM_IN) {
            scaleX = scaleTable1[sIntroFrameCounter * 3];
            scaleY = scaleTable1[sIntroFrameCounter * 3 + 1];
            scaleZ = scaleTable1[sIntroFrameCounter * 3 + 2];
        } else if (sIntroFrameCounter >= INTRO_STEPS_ZOOM_IN && sIntroFrameCounter < INTRO_STEPS_HOLD_1) {
            scaleX = 1.0f;
            scaleY = 1.0f;
            scaleZ = 1.0f;
        } else if (sIntroFrameCounter >= INTRO_STEPS_HOLD_1
                   && sIntroFrameCounter < INTRO_STEPS_ZOOM_OUT) {
            scaleX = scaleTable2[(sIntroFrameCounter - INTRO_STEPS_HOLD_1) * 3];
            scaleY = scaleTable2[(sIntroFrameCounter - INTRO_STEPS_HOLD_1) * 3 + 1];
            scaleZ = scaleTable2[(sIntroFrameCounter - INTRO_STEPS_HOLD_1) * 3 + 2];
        } else {
            scaleX = 0.0f;
            scaleY = 0.0f;
            scaleZ = 0.0f;
        }

        guScale(scaleMat, scaleX, scaleY, scaleZ);
        gSPMatrix(displayListIter++, scaleMat, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);

        graphNode->flags = (graphNode->flags & 0xFF) | 0x400;
        gDPSetEnvColor(displayListIter++, 255, 255, 255, 255);
        gDPSetRenderMode(displayListIter++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);

        gSPDisplayList(displayListIter++, &ts3_eyes_mesh);

        gSPPopMatrix(displayListIter++, G_MTX_MODELVIEW);
        gSPEndDisplayList(displayListIter);

    }
    return displayList;
}
