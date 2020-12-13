#include <ultra64.h>
#include <PR/gs2dex.h>

#define SCALE     "\x80" // SCALE (some scale)
#define ROTATE    "\x81" // ROTATE (degrees) // TODO: maybe add axis?
#define TRANSLATE "\x82" // TRANSLATE (x) (y)
#define COLOR     "\x83" // COLOR (r) (g) (b) (a)

#define CH_SCALE     '\x80'
#define CH_ROT       '\x81'
#define CH_TRANSLATE '\x82'
#define CH_COLOR     '\x83'

#define CH_GET_NEXT(x) (*(++x))

extern void s2d_print(int x, int y, const char *str, uObjMtx *buf);
