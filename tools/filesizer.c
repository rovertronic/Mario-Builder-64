#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fptr;
FILE *fptr2;
int insize;
int cmpsize;
unsigned char *bz;

void writeint4(int val)
{
	fputc((val & 0x00ff000000) >> 24, fptr2);
	fputc((val & 0x0000ff0000) >> 16, fptr2);
	fputc((val & 0x000000ff00) >>  8, fptr2);
	fputc((val & 0x00000000ff) >>  0, fptr2);
}

int main(int argc, const char **argv)
{
    char src[999];
	char dest[999];

    if( argc < 3 ) {
        printf("Two arguments expected.\n");
        printf("Filesizer\n");
        printf("Usage: [infile] [outfile]\n");
		return 1;
    }

	strcpy(src, argv[1]);
    strcpy(dest, argv[2]);
	
	if ((fptr = fopen(src, "rb")) == NULL)
	{
		fprintf(stderr, "FILE OPEN ERROR![%s]\n", src);
		return 1;
	}
    
	if ((fptr2 = fopen(argv[2], "r+")) == NULL)
	{
		fprintf(stderr, "FILE APPEND ERROR![%s]\n", dest);
		exit(1);
	}
	
	fseek(fptr, 0, SEEK_END);
	fseek(fptr2, 0, SEEK_END);
	insize = ftell(fptr);
    writeint4(0);
    cmpsize = ftell(fptr2);
    int numZeros = 0x10 - (cmpsize % 0x10);
    for(int i = 0; i < numZeros; i++)
    {
        fputc(0, fptr2);
    }
    fseek(fptr2, -0x4, SEEK_END);
	writeint4(insize);
	fclose(fptr);
	fclose(fptr2);

	return 0;
}