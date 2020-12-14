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

extern u32 gGlobalTimer;

void s2d_print(int x, int y, const char *str, uObjMtx *buf) {
	char *p = str;
	int tx = 0, ty = 0;
	// int r = 0, g = 0, b = 0, a = 0;
	if (*p == '\0') return;
	do {
		char r = *p;
		int s, rd;
		switch (r) {
			case CH_SCALE:
				CH_SKIP(p);
				s = s2d_atoi(p, &p);
				myScale = s;
				break;
			case CH_ROT:
				CH_SKIP(p);
				rd = s2d_atoi(p, &p);
				saved_degrees = rd;
				myDegrees = rd;
				break;
			case CH_TRANSLATE:
				CH_SKIP(p);
				x = s2d_atoi(p, &p);
				CH_SKIP(p);
				CH_SKIP(p);
				y = s2d_atoi(p, &p);
				break;
			case CH_COLOR:
				CH_SKIP(p);
				s2d_red = s2d_atoi(p, &p);
				CH_SKIP(p);	CH_SKIP(p);

				s2d_green = s2d_atoi(p, &p);
				CH_SKIP(p);	CH_SKIP(p);

				s2d_blue = s2d_atoi(p, &p);
				CH_SKIP(p);	CH_SKIP(p);
				
				s2d_alpha = s2d_atoi(p, &p);
				break;
				
				break;
			default:
				if (myDegrees == 0)
					draw_s2d_glyph(r, (x += (8 * myScale)) + tx, y + ty, (buf++));
				else
					draw_s2d_glyph(r, (x += ((8 * myScale))) + tx, y + ty, (buf++));
		}
		// myDegrees += saved_degrees;
		p++;
	} while (*p != '\0');
	myScale = 1;
	myDegrees = 0;
	saved_degrees = 0;
	tx = 0;
	ty = 0;
}

void s2d_type_print(int x, int y, char *str, uObjMtx *buf, int pos) {
	char t = str[pos];
	str[pos] = '\0';
	s2d_print(x, y, str, buf);
	str[pos] = t;
}

