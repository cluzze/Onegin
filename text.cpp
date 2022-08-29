#include "text.h"
#include "sort.h"
#include "myassert.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

void init_arr(FILE *fd, LinesArr *arr)
{
	arr->nlines           = find_nlines(fd);
	arr->text.line_length = find_filesize(fd);
	arr->text.line        = read_text(fd, arr->text.line_length);
	arr->lines            = get_lines_from_text(arr->text.line, arr->nlines);
}

void free_lines(LinesArr *arr)
{
	free(arr->lines);
	free(arr->text.line);
}

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
	size_t i    = 0;

	lines = (Line*)calloc(nlines, sizeof(Line));
	MYASSERT(lines != NULL)

	char* end = text;

	for (i = 0; i < nlines; ++i)
	{
		end  = strchr(text, '\r');
		*end = '\0';

		lines[i].line        = text;
		lines[i].line_length = (size_t)(end - text);

		text = end + 2;
	}

	return lines;
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

void print_sorted(FILE *output_file, LinesArr *arr)
{
	for (size_t i = 0; i < arr->nlines; i++)
	{
		fprintf(output_file, "%lu: %s\n", i, arr->lines[i].line);
	}

	fprintf(output_file, "\n");

}

void print_original(FILE *output_file, LinesArr *arr)
{
	for (size_t i = 0; i < arr->text.line_length; ++i)
	{
		int c = arr->text.line[i];
		switch (c)
		{
			case '\0':
				fprintf(output_file, "\r");
				break;
			default:
				fprintf(output_file, "%c", c);
				break;
		}
	}
}