#include <ultra64.h>
#include <PR/gs2dex.h>
// My matrix stack for S2DEX transformations.
// Probably doesnt need to be 0x80 long
#define ARRAY_COUNT(x) (sizeof(x) / sizeof(x[0]))


uObjMtx stack[0x80];

u32 stack_top = 0;

u32 s_isfull(void) {
	return (stack_top >= ARRAY_COUNT(stack));
}

u32 s_isempty(void) {
	return (stack_top == 0);
}

void s_push(uObjMtx *f) {
	if (!s_isfull())
		stack[++stack_top] = *f;
}

uObjMtx *s_pop(void) {
	if (!s_isempty())
		return &stack[stack_top--];
}

void s_clear(void) {
	stack_top = 0;
}

