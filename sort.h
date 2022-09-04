//!@mainpage
//!Functions for sorting lines of text 

#ifndef _SORT_
#define _SORT_

#include "text.h"

/**
 *	\brief swaps elements
 *	\param[in] a, b - elements to swap
 */
void swap(Line *a, Line *b);

/**
 *	\brief compares two strings in lexicographical order ignoring punctuation marks
 *	\param[in] str1, str2 - strings to compare
 */
int strings_cmp(Line *str1, Line *str2);

/**
 *	\brief compares two strings in lexicographical order ignoring punctuation marks
 *	\param[in] str1, str2 - strings to compare
 */
int cmp_strings(Line *str1, Line *str2);

/**
 *  \brief builds heap
 *  \param[in] arr - array to sort
 *  \param[in] heap_size - size of heap
 *  \param[in] root - index of root node
 *  \param[in] cmp - comparator
 */
void build_heap(LinesArr *arr, int heap_size, int root, int (*cmp)(Line *str1, Line *str2));

/**
 *  \brief sorts arr using heap sort
 *  \param[in] arr - arr to sort
 *  \param[in] heap_size - size of array
 *  \param[in] cmp - comparator
 */
void heap_sort(LinesArr *arr, int heap_size, int (*cmp)(Line *str1, Line *str2));

#endif