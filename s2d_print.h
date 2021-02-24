#include <ultra64.h>
#include <PR/gs2dex.h>

#define SCALE      "\x80" // SCALE (some scale)
#define ROTATE     "\x81" // ROTATE (degrees) // TODO: maybe add axis?
#define TRANSLATE  "\x82" // TRANSLATE (x) (y)
#define COLOR      "\x83" // COLOR (r) (g) (b) (a)
#define DROPSHADOW "\x84" // DROPSHADOW (no params)
#define BACKGROUND "\x85" // BACKGROUND (w) (h) (alpha)
#define SEPARATOR  "\x86"
#define RESET      "\x87"

#define CH_SCALE      '\x80'
#define CH_ROT        '\x81'
#define CH_TRANSLATE  '\x82'
#define CH_COLOR      '\x83'
#define CH_DROPSHADOW '\x84'
#define CH_BACKGROUND '\x85'
#define CH_SEPARATOR  '\x86'
#define CH_RESET      '\x87'

// ASCII standard escape codes
#define CH_NEWLINE   '\n'

#define CH_GET_NEXT(x) (*(++x))
#define CH_SKIP(x) {x++;}

#define ALIGN_LEFT 0
#define ALIGN_CENTER 1
#define ALIGN_RIGHT 2

extern void s2d_snprint(int x, int y, int align, const char *str, uObjMtx *buf, int len);
extern void s2d_print(int x, int y, int align, const char *str, uObjMtx *buf);
extern void s2d_type_print(int x, int y, int align, const char *str, uObjMtx *buf, int *pos);
extern void s2d_vsprint(int x, int y, int align, uObjMtx *buf, const char *str, ...);
