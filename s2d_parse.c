#include <ultra64.h>
#include <PR/gs2dex.h>
#include <PR/gu.h>
#include <stdarg.h>

#include "config.h"

#include "s2d_draw.h"
#include "s2d_print.h"
#include "s2d_ustdlib.h"

void s2d_snprint(int x, int y, int align, const char *str, uObjMtx *buf, int len) {
	char *p = str;
	int tmp_len = 0;
	int orig_x = x;
	int orig_y = y;
	int line = 0;

	if (*p == '\0') return;

	s2d_rdp_init();

	// resets parameters
	s2d_red = s2d_green = s2d_blue = 255;
	s2d_alpha = 255;
	drop_shadow = FALSE;

	switch (align) {
		case ALIGN_CENTER:
			x = orig_x - s2d_width(str, line, len) / 2;
			break;
		case ALIGN_RIGHT:
			x = orig_x - s2d_width(str, line, len);
	}

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
				orig_x = s2d_atoi(p, &p);
				line++;
				switch (align) {
					case ALIGN_LEFT:
						x = orig_x;
						break;
					case ALIGN_CENTER:
						x = orig_x - s2d_width(str, line, len) / 2;
						break;
					case ALIGN_RIGHT:
						x = orig_x - s2d_width(str, line, len);
				}
				CH_SKIP(p);
				CH_SKIP(p);
				orig_y = s2d_atoi(p, &p);
				y = orig_y;
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
				line++;
				switch (align) {
					case ALIGN_LEFT:
						x = orig_x;
						break;
					case ALIGN_CENTER:
						x = orig_x - s2d_width(str, line, len) / 2;
						break;
					case ALIGN_RIGHT:
						x = orig_x - s2d_width(str, line, len);
				}
				y += TEX_HEIGHT / TEX_RES;
				break;
			case '\t':
				x += TAB_WIDTH_H / TEX_RES;
				break;
			case '\v':
				x += TAB_WIDTH_V / TEX_RES;
				y += TEX_HEIGHT / TEX_RES;
				break;
			// case CH_SEPARATOR:
			// 	CH_SKIP(p);
			// 	break;
			case CH_RESET:
				s2d_red = s2d_green = s2d_blue = 255;
				s2d_alpha = 255;
				drop_shadow = FALSE;
				myScale = 1;
				myDegrees = 0;
				break;
			default:
				if (current_char != '\0' && current_char != CH_SEPARATOR) {
					draw_s2d_glyph(current_char, x, y, (buf++));
					(x += (s2d_kerning_table[current_char] * myScale));
				}
		}
		if (*p == '\0') break;
		p++;
		tmp_len++;
	} while (tmp_len < len);
	myScale = 1;
	myDegrees = 0;
}

void s2d_print(int x, int y, int align, const char *str, uObjMtx *buf) {
	s2d_snprint(x, y, align, str, buf, s2d_strlen(str));
}

void s2d_print_alloc(int x, int y, int align, const char *str) {
	uObjMtx *b = alloc(sizeof(uObjMtx) * s2d_strlen(str));
	s2d_snprint(x, y, align, str, b, s2d_strlen(str));
}

void s2d_type_print(int x, int y, int align, const char *str, uObjMtx *buf, int *pos) {
	int len = s2d_strlen(str);

	s2d_snprint(x, y, align, str, buf, *pos);
	if (s2d_timer % 2 == 0) {
		if (*pos < len) {
			(*pos)++;
		}
	}
}

int s2d_width(const char *str, int line, int len) {
	char *p = str;
	int tmp_len = 0;
	int curLine = 0;
	int width = 0;
	int scale = 1;

	if (*p == '\0') return width;

	do {
		char current_char = *p;
		switch (current_char) {
			case CH_SCALE:
				CH_SKIP(p);
				scale = s2d_atoi(p, &p);
				break;
			case CH_ROT:
				CH_SKIP(p);
				s2d_atoi(p, &p);
				break;
			case CH_TRANSLATE:
				CH_SKIP(p);
				s2d_atoi(p, &p);
				curLine++;
				CH_SKIP(p);
				CH_SKIP(p);
				s2d_atoi(p, &p);
				break;
			case CH_COLOR:
				CH_SKIP(p);
				s2d_atoi(p, &p);
				CH_SKIP(p); CH_SKIP(p);
				s2d_atoi(p, &p);
				CH_SKIP(p); CH_SKIP(p);
				s2d_atoi(p, &p);
				CH_SKIP(p); CH_SKIP(p);
				s2d_atoi(p, &p);
				break;
			case CH_DROPSHADOW:
			case CH_RESET:
				break;
			case '\n':
				curLine++;
				break;
			case '\t':
				if (curLine == line)
					width += TAB_WIDTH_H / TEX_RES;
				break;
			case '\v':
				if (curLine == line)
					width += TAB_WIDTH_V / TEX_RES;
				break;
			default:
				if (current_char != '\0' && curLine == line)
					width += s2d_kerning_table[current_char] * scale;
		}
		if (*p == '\0') break;
		p++;
		tmp_len++;
	} while (tmp_len < len && curLine <= line);
	return width;
}

// void s2d_vsprint(int x, int y, int align, uObjMtx *buf, const char *str, ...) {
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


