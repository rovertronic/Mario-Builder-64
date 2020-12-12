#include <ultra64.h>
#include <PR/gs2dex.h>

#include "s2d_draw.h"

#define SCALE     '\x80'
#define ROT       '\x81'
#define TRANSLATE '\x82'

#define CH_GET_NEXT(x) (*(++x))






void s2d_parse(const char *str) {
	char *p = str;
	while (*(p++) != '\0') {
		char r = *p;
		char s, t, x, y;
		switch (r) {
			case SCALE:
				s = CH_GET_NEXT(p);
				myScale = s;
				break;
			case ROT:
				t = CH_GET_NEXT(p);
				degrees = t;
				break;
			case TRANSLATE:
				x = CH_GET_NEXT(p);
				y = CH_GET_NEXT(p);

			default:
				x = 0;
				// print(r);
		}
	}
}
