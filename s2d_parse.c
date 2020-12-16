#include <ultra64.h>
#include <PR/gs2dex.h>
#include <PR/gu.h>

#include "config.h"

#include "s2d_draw.h"
#include "s2d_print.h"
#include "s2d_ustdlib.h"

int saved_degrees = 0;



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
			default:
				if (myDegrees == 0)
					draw_s2d_glyph(r, (x += (8 * myScale)) + tx, y + ty, (buf++));
				else
					draw_s2d_glyph(r, (x += ((8 * myScale))) + tx, y + ty, (buf++));
		}
		// myDegrees += saved_degrees;
		if (*p == '\0') break;
		p++;
	} while (*p != '\0');
	myScale = 1;
	myDegrees = 0;
	// saved_degrees = 0;
	tx = 0;
	ty = 0;
}

void s2d_type_print(int x, int y, char *str, uObjMtx *buf, int *pos) {
	char *temp_str = str;
	char tmp = temp_str[*pos];
	int len = s2d_strlen(str);
	switch(tmp) {
		case CH_SCALE:
			(*pos) += s2d_ilen(str + *pos + 2);
			break;
		case CH_ROT:
			(*pos) += s2d_ilen(str + *pos + 2);
			break;
	}
	temp_str[*pos] = '\0';
	s2d_print(x, y, temp_str, buf);
	temp_str[*pos] = tmp;

	if (s2d_timer % 2 == 0) {
		if (*pos < len) (*pos)++;
	}
}

