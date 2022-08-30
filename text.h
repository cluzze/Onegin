//!@mainpage
//!Functions for working with text, and getting lines from it to sort

#ifndef _TEXT_
#define _TEXT_

#include <stdio.h>

//! Single line of text
typedef struct 
{
	size_t line_length = 0;
	char *line         = NULL;
} Line;

//!number of lines in text, whole text in form of big buffer of chars and pointer into that buffer for sorting
typedef struct 
{
	size_t nlines = 0;
	Line text     = {0, NULL};
	Line *lines   = NULL;
} LinesArr;

/**
 *	\brief open a file to read
 *	\param[in] filename - file to open
 */
FILE *open_file(const char filename[]);

/**
 *	\brief initializes all fields of arr
 *	\param[in] fd - text file
 *  \param[out] arr - struct to init
 */
void init_arr(FILE *fd, LinesArr *arr);

/**
 *	\brief frees all allocated memory
 *	\param[in] arr - pointer to struct
 */
void free_lines(LinesArr *arr);

/**
 *	\brief finds size of file in bytes
 *	\param[in] filename - file
 */
size_t find_filesize(FILE *fd);

/**
 *	\brief read data from file to allocated char*
 *	\param[in] fd - file to read from
 *  \param[in] filesize - amount of memory to allocate
 */
char* read_text(FILE *fd, size_t filesize);

/**
 *	\brief set pointer into text buf for sorting
 *	\param[in] text - text buf
 *  \param[in] nlines - number of lines in text
 */
Line* get_lines_from_text(char *text, size_t nlines);

/**
 *	\brief finds number of lines in file
 *	\param[in] fd - file
 */
size_t find_nlines(FILE *fd);

/**
 *	\brief prints pointers to lines in specific order into fd
 *	\param[in] output_filename - file in which 
 */
void print_sorted(FILE *output_filename, LinesArr *arr);

/**
 *	\brief prints original text
 *	\param[in] filename - file to open
 */
void print_original(FILE *output_filename, LinesArr *arr);

#endif