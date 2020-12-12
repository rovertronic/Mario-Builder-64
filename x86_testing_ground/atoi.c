int s2d_atoi(char *s, char **s2) {
	int ret = 0;
	int isNegative = (*s == '-');
	if (isNegative) {s++; (*s2)++;}
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
#define SCALE     "\x80" // SCALE (some scale)
#define ROTATE    "\x81" // ROTATE (degrees) // TODO: maybe add axis?
#define TRANSLATE "\x82" // TRANSLATE (x) (y)

#define CH_SCALE     '\x80'
#define CH_ROT       '\x81'
#define CH_TRANSLATE '\x82'

#define CH_GET_NEXT(x) (*(++x))

int saved_degrees = 0;

int myScale = 1;
int myDegrees = 0;

char *t = "TEST" TRANSLATE "10 10CRINGE";

void s2d_print(int x, int y, const char *str) {
	char *p = str;
	if (*p == '\0') return;
	do {
		char r = *p;
		int s, rd, tx = 0, ty = 0;
		switch (r) {
			case CH_SCALE:
				s = CH_GET_NEXT(p);
				printf("%s\n", p);
				s = s2d_atoi(p, &p);
				printf("%d\n", s);
				myScale = s;
				break;
			case CH_ROT:
				rd = CH_GET_NEXT(p);
				saved_degrees = rd;
				myDegrees = rd;
				break;
			case CH_TRANSLATE:
				CH_GET_NEXT(p);
				tx = s2d_atoi(p, &p);
				printf("%d\n", tx);
				CH_GET_NEXT(p);
				CH_GET_NEXT(p);
				ty = s2d_atoi(p, &p);
				// CH_GET_NEXT(p);
				printf("%d\n", ty);
				break;

			default:
				printf("%c %d\n",r, myScale);
		}
		// myDegrees += saved_degrees;
	} while (*(++p) != '\0');
	myScale = 1;
	myDegrees = 0;
	saved_degrees = 0;
}


int main(void) {
	char *s = t;
	s++;
	s++;
	s++;
	s++;
	// printf("%d\n", s2d_atoi(s, &s));
	// printf("%s\n", s);
	s2d_print(0,0, t);
	// printf("%d\n", s2d_atoi("3582932j"));
}