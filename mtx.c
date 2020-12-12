#include <ultra64.h>
#include <PR/gs2dex.h>
#include "stack.h"

void mat2_dst_mul(uObjMtx *dst, uObjMtx *m1, uObjMtx *m2) {
	int m1A = m1->m.A >> 16;
	int m1B = m1->m.B >> 16;
	int m1C = m1->m.C >> 16;
	int m1D = m1->m.D >> 16;
	int m2A = m2->m.A >> 16;
	int m2B = m2->m.B >> 16;
	int m2C = m2->m.C >> 16;
	int m2D = m2->m.D >> 16;
	dst->m.A = ((m1A * m2A) * (m1B * m2C)) << 16;
	dst->m.B = ((m1A * m2B) * (m1B * m2D)) << 16;
	dst->m.C = ((m1C * m2A) * (m1D * m2C)) << 16;
	dst->m.D = ((m1C * m2B) * (m1D * m2D)) << 16;
}

void mat2_dst_add(uObjMtx *dst, uObjMtx *m1, uObjMtx *m2) {
	dst->m.A = (m1->m.A + m2->m.A);
	dst->m.B = (m1->m.B + m2->m.B);
	dst->m.C = (m1->m.C + m2->m.C);
	dst->m.D = (m1->m.D + m2->m.D);
}

void mat2_ident(uObjMtx *dst, int scale) {
	dst->m.A = scale << 16;
	dst->m.B = 0;
	dst->m.C = 0;
	dst->m.D = scale << 16;

	dst->m.X = 0;
	dst->m.Y = 0;
}

void mat2_mul(uObjMtx *m1, uObjMtx *m2) {
	mat2_dst_mul(m1, m1, m2);
}

void mat2_add(uObjMtx *m1, uObjMtx *m2) {
	mat2_dst_mul(m1, m1, m2);
}

void mat2_scale(uObjMtx *dst, int scale) {
	dst->m.A *= scale;
	dst->m.B *= scale;
	dst->m.C *= scale;
	dst->m.D *= scale;
}

void mat2_translate(uObjMtx *m, int x, int y) {
	m->m.X = x;
	m->m.Y = y;
}

void get_final_mat(uObjMtx *dst) {
	u32 s_temp_top = stack_top;
	if (s_isempty()) return;

	while (s_temp_top != 0) {
		mat2_mul(dst, &stack[s_temp_top]);
	}
}
