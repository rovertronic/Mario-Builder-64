#include <ultra64.h>
#include <PR/gs2dex.h>

#include "s2d_draw.h"
#include "s2d_print.h"

int saved_degrees = 0;

void s2d_print(int x, int y, const char *str, uObjMtx *buf) {
	char *p = str;
	if (*p == '\0') return;
	do {
		char r = *p;
		char s, rd, tx, ty;
		switch (r) {
			case CH_SCALE:
				s = CH_GET_NEXT(p);
				myScale = s;
				break;
			case CH_ROT:
				rd = CH_GET_NEXT(p);
				saved_degrees = rd;
				myDegrees = rd;
				break;
			case CH_TRANSLATE:
				tx = CH_GET_NEXT(p);
				ty = CH_GET_NEXT(p);
				break;

			default:
				draw_s2d_glyph(r, x += (8 * myScale), y, (buf++));
		}
		myDegrees += saved_degrees;
	} while (*(p++) != '\0');
	myScale = 1;
	myDegrees = 0;
	saved_degrees = 0;
}

