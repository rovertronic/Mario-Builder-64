#include <ultra64.h>
#include <PR/gs2dex.h>
#include <PR/gu.h>
#include <stdarg.h>

#include "config.h"

#include "s2d_draw.h"
#include "s2d_print.h"
#include "s2d_ustdlib.h"

void s2d_snprint(int x, int y, const char *str, uObjMtx *buf, int len) {
	char *p = str;
	int tx = 0, ty = 0;
	int tmp_len = 0;
	int orig_x = x;
	int orig_y = y;

	if (*p == '\0') return;

	// resets parameters
	s2d_red = s2d_green = s2d_blue = 255;
	s2d_alpha = 255;
	drop_shadow = FALSE;
	do {
		char current_char = *p;

		switch (current_char) {
			case CH_SCALE:
				CH_SKIP(p);
				myScale = s2d_atoi(p, &p);
				break;
			case CH_ROT:
				CH_SKIP(p);
				myDegrees = s2d_atoi(p, &p);
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
			case CH_DROPSHADOW:
				drop_shadow ^= 1;
				// CH_SKIP(p);
				break;
			case '\n':
				x = orig_x;
				y += TEX_HEIGHT;
				break;
			case '\t':
				x += TAB_WIDTH_H;
				break;
			case '\v':
				x += TAB_WIDTH_V;
				y += TEX_HEIGHT;
				break;
			default:
				if (current_char != '\0') {
					if (myDegrees == 0)
						draw_s2d_glyph(current_char, (x += (8 * myScale)) + tx, y + ty, (buf++));
					else
						draw_s2d_glyph(current_char, (x += ((8 * myScale))) + tx, y + ty, (buf++));
				}
		}
		if (*p == '\0') break;
		p++;
		tmp_len++;
	} while (tmp_len < len);
	myScale = 1;
	myDegrees = 0;
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

// void s2d_vsprint(int x, int y, uObjMtx *buf, const char *str, ...) {
// 	int last_chr;
// 	va_list args;
// 	char *dst = alloc(s2d_strlen(str) * 2);
// 	va_start(args, str);
// 	last_chr = vsprintf(dst, str, str, args);
// 	if (last_chr >= 0) {
// 		dst[last_chr] = '\0';
// 	}
// 	s2d_print(x, y, dst, buf);
// }


