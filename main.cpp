#include "text.h"
#include "sort.h"
#include "myassert.h"

#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 16

int main()
{
	LinesArr arr;

	const char filename[] = "Texts/text.txt";
	FILE *input_file = open_file(filename);

	arr.nlines = find_nlines(input_file);
	arr.text.line_length = find_filesize(input_file);
	arr.text.line = read_text(input_file, arr.text.line_length);

	printf("%s\n\n\n", arr.text.line);

	arr.lines = get_lines_from_text(arr.text.line, arr.nlines);

	for (size_t i = 0; i < arr.nlines; i++)
	{
		printf("%lu: %s\n", i, arr.lines[i].line);
	}

	free(arr.lines);
	free(arr.text.line);
	//printf("nlines: %lu\n", nlines);

	//arr = create_lines_arr(input_file, nlines);

	//print_lines_arr(arr);

	heap_sort(&arr, (int)arr.nlines, strings_cmp);

	printf("\n\nSorted:\n");

	for (size_t i = 0; i < arr.nlines; i++)
	{
		printf("%lu: %s\n", i, arr.lines[i].line);
	}
	//print_lines_arr(arr);

	printf("\n");

	heap_sort(&arr, (int)arr.nlines, cmp_strings);

	printf("\n\nReverse sorted:\n");

	for (size_t i = 0; i < arr.nlines; i++)
	{
		printf("%lu: %s\n", i, arr.lines[i].line);
	}

	printf("\n\nOriginal:\n");
	for (size_t i = 0; i < arr.text.line_length; ++i)
	{
		int c = arr.text.line[i];
		switch (c)
		{
			case '\0':
				printf("\r");
				break;
			default:
				printf("%c", c);
				break;
		}
	}

	printf("\n");

/******************************CLEAN UP******************************/
	//destroy_lines_arr(arr);

	fclose(input_file);
	
	/*char **arr = (char**)calloc(10, sizeof(char*));

	for (int i = 0; i < 10; i++)
	{
		arr[i] = (char*)calloc(10, sizeof(char));
		for (int j = 0; j < 8; j++)
		{
			char c = '0' + rand() % 10;
			arr[i][j] = c;
		}
		if (i != 9)
		{
			arr[i][8] = '\r';
			arr[i][9] = '\n';
		}
	}

	int N = 10;
	printArray(arr, N);
	heap_sort(arr, N);
	printf("Sorted array is\n");
	printArray(arr, N);

	for (int i = 0; i < 10; i++)
	{
		free(arr[i]);
		
	}
	free(arr);*/

	return 0;
}


