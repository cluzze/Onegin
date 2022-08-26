#include "text.h"
#include "sort.h"
#include "myassert.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

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
		if (i != 0)
			fprintf(stdout, " - dif: %d", strings_cmp(&arr->lines[i], &arr->lines[i - 1]));
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