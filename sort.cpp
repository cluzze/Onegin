#include "sort.h"
#include "myassert.h"
#include "text.h"

#include <string.h>
#include <ctype.h>

void swap(Line *a, Line *b)
{
	MYASSERT(a != NULL)
	MYASSERT(b != NULL)

	Line temp = *a;
	*a        = *b;
	*b        = temp;

	return;
}

int strings_cmp(Line *str1, Line *str2)
{
	//return strcmp(str1->line, str2->line);
	char *s1 = str1->line;
	char *s2 = str2->line;

	size_t i = 0;
	size_t j = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		while (!isalnum(s1[i]))
		{
			++i;
			if (s1[i] == '\0')
				break;
		}
		while (!isalnum(s2[j]))
		{
			++j;
			if (s2[j] == '\0')
				break;
		}

		//printf("%c, %c\n", s1[i], s2[j]);

		if (s1[i] != s2[j])
		{
			//printf("q\n");
			break;
		}


		//printf("hi\n");

		++i;
		++j;
	}

	//printf("s1: %c - %d, s2: %c - %d\n", s1[i], s1[i], s2[j], s2[j]);

	if (s1[i] == '\0')
		return -1;

	if (s2[j] == '\0')
		return 1;

	return ((int)(unsigned char)(*s1) - (int)(unsigned char)(*s2));
}

void build_heap(LinesArr *arr, int heap_size, int root, int (*cmp)(Line *str1, Line *str2))
{
	MYASSERT(arr)
	MYASSERT(heap_size >= 0)

	int new_root    = root;
	int left_child  = 2 * root + 1;
	int right_child = 2 * root + 2;

	if (left_child < heap_size && cmp(&arr->lines[left_child], &arr->lines[new_root]) > 0)
	{
		new_root = left_child;
	}

	if (right_child < heap_size && cmp(&arr->lines[right_child], &arr->lines[new_root]) > 0)
	{
		new_root = right_child;
	}

	if (new_root != root)
	{
		swap(&arr->lines[root], &arr->lines[new_root]);
		build_heap(arr, heap_size, new_root, cmp);
	}
}

void heap_sort(LinesArr *arr, int heap_size)
{
	MYASSERT(arr)

	for (int i = heap_size / 2 - 1; i >= 0; i--)
	{
		build_heap(arr, heap_size, i, strings_cmp);
	}

	for (int i = heap_size - 1; i >= 0; i--)
	{
		swap(&arr->lines[0], &arr->lines[i]);
		build_heap(arr, i, 0, strings_cmp);
	}
}

