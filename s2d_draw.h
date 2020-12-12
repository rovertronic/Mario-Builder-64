#ifndef S2D_DRAW_H
#define S2D_DRAW_H
#include <ultra64.h>

extern int myScale;
extern int degrees;
extern uObjMtx final_mtx, rot_mtx;

extern void setup_font(int idx);

extern void mtx_pipeline(uObjMtx *m, int x, int y);

extern void draw_s2d_glyph(char c, int x, int y, uObjMtx *mt);

#endif