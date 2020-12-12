#include <ultra64.h>
#include <PR/gs2dex.h>
#include <PR/gu.h>

#include "s2d_draw.h"
#include "s2d_print.h"

int saved_degrees = 0;

int s2d_atoi(char *s, char **s2) {
	int ret = 0;
	int isNegative = (*s == '-');
	if (isNegative) {
		s++;
		(*s2)++;
	}
	for (; *s != '\0' && *s != ' ' && *s >= '0' && *s <= '9'; s++) {
		ret *= 10;
		if (*s >= '0' && *s <= '9')
			ret += *s - '0';
		else break;
		if (!(*(s+1) != '\0' && *(s+1) != ' ' && *(s+1) >= '0' && *(s+1) <= '9')) break;
		(*s2)++;
	}
	if (isNegative) ret *= -1;
	return ret;
}

void s2d_print(int x, int y, const char *str, uObjMtx *buf) {
	char *p = str;
	int tx = 0, ty = 0;
	if (*p == '\0') return;
	do {
		char r = *p;
		int s, rd;
		switch (r) {
			case CH_SCALE:
				CH_GET_NEXT(p);
				s = s2d_atoi(p, &p);
				myScale = s;
				break;
			case CH_ROT:
				CH_GET_NEXT(p);
				rd = s2d_atoi(p, &p);
				saved_degrees = rd;
				myDegrees = rd;
				break;
			case CH_TRANSLATE:
				CH_GET_NEXT(p);
				tx = s2d_atoi(p, &p);
				CH_GET_NEXT(p);
				CH_GET_NEXT(p);
				ty = s2d_atoi(p, &p);
				break;

			default:
				if (myDegrees == 0)
					draw_s2d_glyph(r, (x += (8 * myScale)) + tx, y + ty, (buf++));
				else
					draw_s2d_glyph(r, (x += ((8 * myScale))) + tx, y + ty, (buf++));
		}
		// myDegrees += saved_degrees;
	} while (*(++p) != '\0');
	myScale = 1;
	myDegrees = 0;
	saved_degrees = 0;
	tx = 0;
	ty = 0;
}

