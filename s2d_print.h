#include <ultra64.h>
#include <PR/gs2dex.h>

#define SCALE     "\x80"
#define ROT       "\x81"
#define TRANSLATE "\x82"

#define CH_SCALE     '\x80'
#define CH_ROT       '\x81'
#define CH_TRANSLATE '\x82'

#define CH_GET_NEXT(x) (*(++x))

extern void s2d_print(int x, int y, const char *str, uObjMtx *buf);
