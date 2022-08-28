#include "text.h"
#include "sort.h"
#include "myassert.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

FILE *open_file(const char filename[])
{
	FILE *input_file = NULL;

	input_file = fopen(filename, "rb");

	MYASSERT(input_file != NULL)

	return input_file;
}

size_t find_filesize(FILE *fd)
{
	MYASSERT(fd != NULL)

	size_t size = 0;

	fseek(fd, 0, SEEK_END);
	size = (size_t)ftell(fd);
	fseek(fd, 0, SEEK_SET);

	return size;
}

char* read_text(FILE *fd, size_t filesize)
{
	MYASSERT(fd != NULL)

	char *buf = NULL;

	buf = (char*)calloc(filesize + 1, sizeof(char));
	MYASSERT(buf != NULL);
	*(buf + filesize) = '\r';

	fread(buf, sizeof(char), filesize, fd);

	return buf;
}

Line* get_lines_from_text(char *text, size_t nlines)
{
	Line* lines = NULL;
	size_t i = 0;

	lines = (Line*)calloc(nlines, sizeof(Line));
	MYASSERT(lines != NULL)

	char* end = text;

	for (i = 0; i < nlines; ++i)
	{
		end = strchr(text, '\r');
		*end = '\0';

		lines[i].line        = text;
		lines[i].line_length = (size_t)(end - text);

		text = end + 2;
	}

	return lines;
}

LinesArr* create_lines_arr(FILE *fd, size_t nlines)
{
	MYASSERT(fd != NULL)

	LinesArr *arr = (LinesArr*)calloc(1, sizeof(LinesArr));
	MYASSERT(arr != NULL)

	arr->nlines   = nlines;
	arr->lines    = (Line*)calloc(arr->nlines, sizeof(Line));
	MYASSERT(arr->lines != NULL)

	ssize_t line_length = 0;
	size_t n            = 0;
	char *lineptr       = NULL;
	int i               = 0;

	while ((line_length = getline(&lineptr, &n, fd)) != -1)
	{
		if (line_length > 1 && lineptr[line_length - 2] == '\r')
		{
			lineptr[line_length - 2] = '\0';
			line_length -= 2;
		}

		arr->lines[i].line_length = (size_t)line_length;

		arr->lines[i].line = (char*)calloc(arr->lines[i].line_length, sizeof(char));

		strcpy(arr->lines[i].line, lineptr);

		++i;
	}

	free(lineptr);

	return arr;
}

void destroy_lines_arr(LinesArr *arr)
{
	size_t i = 0;

	for (i = 0; i < arr->nlines; ++i)
	{
		free(arr->lines[i].line);
	}
	free(arr->lines);
	free(arr);
}

void print_lines_arr(LinesArr *arr)
{
	fprintf(stdout, "nlines: %lu\n", arr->nlines);

	size_t i = 0;
	size_t j = 0;
	for (i = 0; i < arr->nlines; ++i)
	{
		fprintf(stdout, "%lu: ", i + 1);
		for (j = 0; j < arr->lines[i].line_length; ++j)
		{
			fprintf(stdout, "%c", arr->lines[i].line[j]);
		}
/*		if (i != 0)
			fprintf(stdout, " - dif: %d", strings_cmp(&arr->lines[i], &arr->lines[i - 1]));*/
		fprintf(stdout, "\n");
	}
}

size_t find_nlines(FILE *fd)
{
	MYASSERT(fd != NULL)

	size_t nlines = 0;
	size_t size   = 0;
	char *lineptr = NULL;

	while (getline(&lineptr, &size, fd) != -1)
	{
		++nlines;
	}

	free(lineptr);

	fseek(fd, 0, SEEK_SET);

	return nlines;
}