/*
 * Copyright (C) 2011 <fwhacking|gmail:com>
 *
 * This is free software, licensed under the GNU General Public License v2.
 * See /LICENSE for more information.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

static void print_usage(const char *name)
{
	printf("Usage: %s file\n", name);
}

int main(int argc, char **argv)
{
	FILE *fd;
	long size;

	if (argc != 2)
	{
		print_usage(argv[0]);
		exit(1);
	}

	fd = fopen(argv[1], "rb");
	if (fd == NULL)
	{
		printf("Could not read the file '%s'\n", argv[1]);
		print_usage(argv[0]);
		exit(1);
	}

	size = fseek(fd, 0L, SEEK_END);
	size = ftell(fd);
	fclose(fd);

	printf("%ld\n", size);

	exit(0);
}
