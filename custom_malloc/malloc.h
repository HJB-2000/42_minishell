#ifndef MALLOC_H
#define MALLOC_H

#include <stdlib.h>
#include <stdbool.h>


typedef struct s_garbage
{
	void				*_malloc;
	int					index;
	struct s_garbage	*next;
}	t_garbage;

#endif