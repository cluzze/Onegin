#include "text.h"
#include "sort.h"
#include "myassert.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
	LinesArr arr = {0, {0, NULL}, NULL};

	const char input_filename[]  = "Texts/Hamlet.txt";
	const char output_filename[] = "Texts/Output.txt";

	FILE *input_file  = open_file(input_filename);
	FILE *output_file = fopen(output_filename, "wb");

	MYASSERT(output_file != NULL)

	init_arr(input_file, &arr);

	heap_sort(&arr, (int)arr.nlines, strings_cmp);
	fprintf(output_file, "************************SORTED************************\n");
	print_sorted(output_file, &arr);

	heap_sort(&arr, (int)arr.nlines, cmp_strings);
	fprintf(output_file, "\n\n************************REVERSE SORTED************************\n");
	print_sorted(output_file, &arr);

	fprintf(output_file, "\n\n************************SORTED************************\n");
	print_original(output_file, &arr);

/******************************CLEAN UP******************************/

	free_lines(&arr);

	fclose(input_file);
	fclose(output_file);

	return 0;
}


