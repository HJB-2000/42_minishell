#ifndef MALLOC_H
#define MALLOC_H

typedef struct s_garbage
{
	void				*_malloc;
	int					index;
	struct s_garbage	*next;
}	t_garbage;

void	*_malloc(size_t size, bool trigger_free, bool exit_on_fail);
#endif