#ifndef _TEXT_
#define _TEXT_

#include <stdio.h>

typedef struct 
{
	size_t line_length = 0;
	char *line         = NULL;
} Line;

typedef struct 
{
	size_t nlines = 0;
	Line *lines   = NULL;
} LinesArr;

void print_lines_arr(LinesArr *arr);

LinesArr* create_lines_arr(FILE *fd, size_t nlines);

void destroy_lines_arr(LinesArr *arr);

size_t find_nlines(FILE *fd);

#endif