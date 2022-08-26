#ifndef _MY_ASSERT_
#define _MY_ASSERT_

#include <stdio.h>
#include <stdlib.h>

#define MYASSERT(condition)																		\
	if (!(condition))																			\
	{																							\
		fprintf(stderr, "Error: %s\nAccured in function: %s, from file: %s, on line: %d\n",		\
			#condition, __PRETTY_FUNCTION__, __FILE__, __LINE__);								\
		abort();																				\
	}			

#endif