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
	Line text     = {0, NULL};
	Line *lines   = NULL;
} LinesArr;

FILE *open_file(const char filename[]);

size_t find_filesize(FILE *fd);

char* read_text(FILE *fd, size_t filesize);

Line* get_lines_from_text(char *text, size_t nlines);

void print_lines_arr(LinesArr *arr);

LinesArr* create_lines_arr(FILE *fd, size_t nlines);

void destroy_lines_arr(LinesArr *arr);

size_t find_nlines(FILE *fd);

#endif