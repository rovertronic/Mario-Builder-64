#include <ultra64.h>
#include <PR/gs2dex.h>

#include "s2d_draw.h"
#include "s2d_print.h"

void s2d_print(int x, int y, const char *str, uObjMtx *buf) {
	char *p = str;
	do {
		char r = *p;
		char s, rd, tx, ty;
		if (*p == '\0') break;
		switch (r) {
			case CH_SCALE:
				s = CH_GET_NEXT(p);
				myScale = s;
				break;
			case CH_ROT:
				rd = CH_GET_NEXT(p);
				degrees = rd;
				break;
			case CH_TRANSLATE:
				tx = CH_GET_NEXT(p);
				ty = CH_GET_NEXT(p);

			default:
				draw_s2d_glyph(r, x += (29 * myScale), y, (buf++));
		}
	} while (*(p++) != '\0');
	myScale = 1;
}

