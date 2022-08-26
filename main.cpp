#include "text.h"
#include "sort.h"
#include "myassert.h"

#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 16

int main()
{
	LinesArr *arr    = NULL;
	FILE *input_file = NULL;
	const char input_filename[] = "Texts/text.txt";

	input_file = fopen(input_filename, "rb");

	MYASSERT(input_file != NULL)

	size_t nlines = 0;

	nlines = find_nlines(input_file);

	//printf("nlines: %lu\n", nlines);

	arr = create_lines_arr(input_file, nlines);

	print_lines_arr(arr);

	heap_sort(arr, (int)arr->nlines);

/*	Line l1 = {0, "\'as by lot, god wot, \'"};
	Line l2 = {0, "A slave that is not twentieth part the tithe"};

	printf("%d\n", strings_cmp(&l1, &l2));*/

	printf("Sorted:\n");
	print_lines_arr(arr);

/******************************CLEAN UP******************************/
	destroy_lines_arr(arr);

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


