#include <ultra64.h>
#include <PR/gs2dex.h>

extern uObjMtx stack[0x80];

extern u32 stack_top;

extern u32 s_isfull(void);
extern u32 s_isempty(void);
extern void s_push(uObjMtx *f);
extern uObjMtx *s_pop(void);
extern void s_clear(void);
