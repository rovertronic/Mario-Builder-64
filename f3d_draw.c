#include "config.h"
#ifdef DRAW_F3D

#include <ultra64.h>
#include "mtx.h"
#include "debug.h"

float myScale = 1.0f;
int myDegrees = 0;
uObjMtx final_mtx, rot_mtx;
int s2d_red = 255, s2d_green = 255, s2d_blue = 255, s2d_alpha = 255;
int drop_shadow = FALSE;
int drop_x = 0;
int drop_y = 0;

#define s(sprite) ((uObjSprite *)seg2virt(&sprite))
#define t(texture) ((uObjTxtr *)seg2virt(&texture))

void f3d_rdp_init(void) {
    gDPPipeSync(gdl_head++);
    gDPSetCycleType(gdl_head++, G_CYC_1CYCLE);
    // gDPSetRenderMode(gdl_head++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetCombineLERP(gdl_head++,
        0, 0, 0, ENVIRONMENT,
        0, 0, 0, TEXEL0,
        0, 0, 0, ENVIRONMENT,
        0, 0, 0, TEXEL0
    );
}

void setup_font_texture(int idx) {
    gDPPipeSync(gdl_head++);


    gDPSetEnvColor(gdl_head++, s2d_red, s2d_green, s2d_blue, s2d_alpha);

    gDPLoadTextureBlock(
        gdl_head++,
        t(s2d_tex[idx])->block.image,
        s(s2d_font)->s.imageFmt,
        G_IM_SIZ_8b,
        s(s2d_font)->s.imageW >> 5,
        s(s2d_font)->s.imageH >> 5,
        s(s2d_font)->s.imagePal,
        s(s2d_font)->s.imageFlags,
        s(s2d_font)->s.imageFlags,
        G_TX_NOMASK,
        G_TX_NOMASK,
        G_TX_NOLOD,
        G_TX_NOLOD);
    gDPLoadSync(gdl_head++);
}

#define CLAMP_0(x) ((x < 0) ? 0 : x)

void cpu_quad(int x, int y, float scale) {
    Vtx *v0 = alloc(sizeof(Vtx) * 4);
    bzero(v0, sizeof(Vtx) * 4);

    v0[0].v.ob[0] =
    v0[2].v.ob[0] = x;
    v0[1].v.ob[0] =
    v0[3].v.ob[0] = x + ((f32) (s(s2d_font)->s.imageW >> 5) * scale);

    v0[0].v.ob[1] =
    v0[1].v.ob[1] = y;
    v0[2].v.ob[1] =
    v0[3].v.ob[1] = y + ((f32) (s(s2d_font)->s.imageW >> 5) * scale);

    v0[0].v.tc[0] = 0;
    v0[0].v.tc[1] = 0;

    v0[1].v.tc[0] = (s(s2d_font)->s.imageW >> 5);
    v0[1].v.tc[1] = 0;

    v0[2].v.tc[0] = 0;
    v0[2].v.tc[1] = (s(s2d_font)->s.imageH >> 5);

    v0[3].v.tc[0] = (s(s2d_font)->s.imageW >> 5);
    v0[3].v.tc[1] = (s(s2d_font)->s.imageH >> 5);

    gSPVertex(gdl_head++, v0, 4, 0);
    gSP2Triangles(gdl_head++, 0, 1, 2, 0, 1, 3, 2, 0);
}

void draw_f3d_dropshadow(char c, int x, int y, uObjMtx *ds) {
    setup_font_texture(c);

    if (s2d_red != 0
        && s2d_green != 0
        && s2d_blue != 0
    ) {
        gDPPipeSync(gdl_head++);
        gDPSetEnvColor(gdl_head++,
                   CLAMP_0(s2d_red - 100),
                   CLAMP_0(s2d_green - 100),
                   CLAMP_0(s2d_blue - 100),
                   s2d_alpha);
        cpu_quad(x, 240 - y, myScale);
        gDPPipeSync(gdl_head++);
        gDPSetEnvColor(gdl_head++, s2d_red, s2d_green, s2d_blue, s2d_alpha);
    }
}

void draw_f3d_glyph(char c, int x, int y, uObjMtx *mt) {
    setup_font_texture(c);

    cpu_quad(x, 240 - y, myScale);
    gDPPipeSync(gdl_head++);
}

#undef s
#undef t

#endif
