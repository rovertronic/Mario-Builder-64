#ifndef S2D_DRAW_H
#define S2D_DRAW_H
#include <ultra64.h>

extern int myScale;
extern int degrees;
extern uObjMtx final_mtx, rot_mtx;

extern void setup_font(int idx);

extern void mtx_pipeline(uObjMtx *m, int x, int y);

extern void print_s2d(char c);

#endif