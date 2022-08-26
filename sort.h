#ifndef _SORT_
#define _SORT_

#include "text.h"

void swap(Line *a, Line *b);

int strings_cmp(Line *str1, Line *str2);

void build_heap(LinesArr *arr, int heap_size, int root, int (*cmp)(Line *str1, Line *str2));

void heap_sort(LinesArr *arr, int heap_size);

#endif