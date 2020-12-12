#include <ultra64.h>
#include "config.h"
#include "mtx.h"

int myScale = 1;
int degrees = 0;
uObjMtx final_mtx, rot_mtx;

static Gfx s2d_init_dl[] = {
	gsDPPipeSync(),
	gsDPSetTexturePersp(G_TP_NONE),
	gsDPSetTextureLOD(G_TL_TILE),
	gsDPSetTextureLUT(G_TT_NONE),
	gsDPSetTextureConvert(G_TC_FILT),
	gsDPSetAlphaCompare(G_AC_THRESHOLD),
	gsDPSetBlendColor(0, 0, 0, 0x01),
	gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
	gsSPEndDisplayList(),
};

void setup_font(int idx) {
	gDPPipeSync(gDisplayListHead++);
	gSPDisplayList(gDisplayListHead++, s2d_init_dl);
	gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
	gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SPRITE, G_RM_XLU_SPRITE2);
	gSPObjRenderMode(gDisplayListHead++, G_OBJRM_XLU | G_OBJRM_BILERP);
	gSPObjLoadTxtr(gDisplayListHead++, &s2d_tex[idx]);
}// 32 32

void mtx_pipeline(uObjMtx *m, int x, int y) {
	mat2_ident(m, 1);
	mat2_ident(&rot_mtx, 1);
	// mat2_translate(&rot_mtx, 50, 50);
	mat2_scale(m, myScale);
	// mat2_mul(m, &rot_mtx);
	mat2_translate(m, x, y);
	gSPObjMatrix(gDisplayListHead++, m);
}

void print_s2d(char c) {
	setup_font(c);
	mtx_pipeline(&final_mtx, 50, 50);
	// gSPObjMatrix(gDisplayListHead++, &s2d_mat);
	gSPObjSprite(gDisplayListHead++, &s2d_font);
}