#include <ultra64.h>
#include <PR/gs2dex.h>
#include <PR/gu.h>
#include <stdarg.h>

#include "config.h"

#include "s2d_draw.h"
#include "s2d_print.h"
#include "s2d_ustdlib.h"

int saved_degrees = 0;
int s2d_colorFrames = 0;


extern u32 gGlobalTimer;

void s2d_snprint(int x, int y, const char *str, uObjMtx *buf, int len) {
	char *p = str;
	int tx = 0, ty = 0;
	int tmp_len = 0;
	int orig_x = x;
	int orig_y = y;
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
				s2d_colorFrames++;
				CH_SKIP(p);
				s2d_red = s2d_atoi(p, &p);
				CH_SKIP(p);	CH_SKIP(p);

				s2d_green = s2d_atoi(p, &p);
				CH_SKIP(p);	CH_SKIP(p);

				s2d_blue = s2d_atoi(p, &p);
				CH_SKIP(p);	CH_SKIP(p);
				
				s2d_alpha = s2d_atoi(p, &p);
				break;
			case '\n':
				x = orig_x;
				y += TEX_HEIGHT;
				break;
			default:
				// if (s2d_colorFrames > 2) {
				// 	s2d_colorFrames = 0;
				// 	s2d_red = s2d_green = s2d_blue = 255;
				// 	s2d_alpha = 255;
				// }
				if (r != '\0') {
					if (myDegrees == 0)
						draw_s2d_glyph(r, (x += (8 * myScale)) + tx, y + ty, (buf++));
					else
						draw_s2d_glyph(r, (x += ((8 * myScale))) + tx, y + ty, (buf++));
				}
		}
		// myDegrees += saved_degrees;
		if (*p == '\0') break;
		p++;
		tmp_len++;
	} while (tmp_len < len);
	myScale = 1;
	myDegrees = 0;
	// saved_degrees = 0;
	tx = 0;
	ty = 0;
}

void s2d_print(int x, int y, const char *str, uObjMtx *buf) {
	s2d_snprint(x, y, str, buf, s2d_strlen(str));
}

void s2d_type_print(int x, int y, const char *str, uObjMtx *buf, int *pos) {
	int len = s2d_strlen(str);

	s2d_snprint(x, y, str, buf, *pos);
	if (s2d_timer % 2 == 0) {
		if (*pos < len) {
			(*pos)++;
		}
	}
}

void s2d_vsprint(int x, int y, uObjMtx *buf, const char *str, ...) {
	va_list args;
	va_start(args, str);
	// vsprintf(str, )
}


