#include <ultra64.h>
#include <PR/gs2dex.h>
#include "stack.h"
// #include "fixedpoint.h"
#include <PR/gu.h>

#define ftoq FTOFIX32
#define qtof FIX32TOF

void mat2_dst_mul(uObjMtx *dst, uObjMtx *m1, uObjMtx *m2) {
	dst->m.A = ftoq((qtof(m1->m.A) * qtof(m2->m.A)) + (qtof(m1->m.B) * qtof(m2->m.C)));
	dst->m.B = ftoq((qtof(m1->m.A) * qtof(m2->m.B)) + (qtof(m1->m.B) * qtof(m2->m.D)));
	dst->m.C = ftoq((qtof(m1->m.C) * qtof(m2->m.A)) + (qtof(m1->m.D) * qtof(m2->m.C)));
	dst->m.D = ftoq((qtof(m1->m.C) * qtof(m2->m.B)) + (qtof(m1->m.D) * qtof(m2->m.D)));
}

void mat2_dst_add(uObjMtx *dst, uObjMtx *m1, uObjMtx *m2) {
	dst->m.A = (m1->m.A + m2->m.A);
	dst->m.B = (m1->m.B + m2->m.B);
	dst->m.C = (m1->m.C + m2->m.C);
	dst->m.D = (m1->m.D + m2->m.D);
}

void mat2_copy(uObjMtx *dst, uObjMtx *src) {
	dst->m.A = src->m.A;
	dst->m.B = src->m.B;
	dst->m.C = src->m.C;
	dst->m.D = src->m.D;
	dst->m.X = src->m.X;
	dst->m.Y = src->m.Y;
}

void mat2_ident(uObjMtx *dst, int scale) {
	dst->m.A = scale << 16;
	dst->m.B = 0;
	dst->m.C = 0;
	dst->m.D = scale << 16;

	dst->m.X = 0;
	dst->m.Y = 0;
}
// cos -sin sin cos
void mat2_rotate(uObjMtx *dst, f32 degrees) {
	dst->m.A = ftoq(cosf(degrees));
	dst->m.B = ftoq(sinf(degrees));
	dst->m.C = ftoq(-sinf(degrees));
	dst->m.D = ftoq(cosf(degrees));
}

void mat2_mul(uObjMtx *m1, uObjMtx *m2) {
	mat2_dst_mul(m1, m1, m2);
}

void mat2_add(uObjMtx *m1, uObjMtx *m2) {
	mat2_dst_mul(m1, m1, m2);
}

void mat2_scale(uObjMtx *dst, int scale) {
	dst->m.A *= scale;
	// dst->m.B *= scale;
	// dst->m.C *= scale;
	dst->m.D *= scale;
}

#define	FTOFIX16(x)	(long)((x) * (float)(1 << 2))
#define	FIX16TOF(x)	((float)(x) * (1.0f / (float)(1 << 2)))
void mat2_translate(uObjMtx *m, int x, int y) {
	m->m.X = x<<2;
	m->m.Y = y<<2;
}


void mat2_translate_vec(uObjMtx *m, f32 degrees, f32 mag) {
	m->m.X += FTOFIX16(mag * cosf(degrees));
	m->m.Y += FTOFIX16(mag * sinf(degrees));
}

void get_final_mat(uObjMtx *dst) {
	u32 s_temp_top = stack_top;
	if (s_isempty()) return;

	while (s_temp_top != 0) {
		mat2_mul(dst, &stack[s_temp_top]);
	}
}

typedef float Mat4[4][4];
void gu_to_gs2dex(uObjMtx *m1, Mat4 m2) {
	m1->m.A = FTOFIX32(m2[0][0]);
	m1->m.B = FTOFIX32(m2[0][1]);
	m1->m.C = FTOFIX32(m2[1][0]);
	m1->m.D = FTOFIX32(m2[1][1]);

	m1->m.X = FTOFIX16(m2[3][0]);
	m1->m.Y = FTOFIX16(m2[3][1]);
}

