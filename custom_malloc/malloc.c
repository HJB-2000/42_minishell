#include "malloc.h"

static t_garbage	*new_node(void *ptr, int i)
{
	t_garbage	*new;

	if (!ptr)
		return (NULL);
	new = malloc(sizeof(t_garbage));
	if (!new)
		return (NULL);
	new->_malloc = ptr;
	new->index = i;
	new->next = NULL;
	return (new);
}

void	add_node(t_garbage **head, t_garbage *new_node)
{
	t_garbage	*tmp;

	if (!*head)
	{
		(*head) = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	_free(t_garbage **list)
{
	t_garbage	*tmp;

	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp->_malloc);
		free(tmp);
		tmp = NULL;
	}
	*list = NULL;
}

void	*treat_ptr(size_t size)
{
	void	*instant;

	instant = NULL;
	if (size > 0)
    {
		instant = malloc(size);
		if (!instant)
			return (NULL);
	}
	return (instant);
}

void	*_malloc(size_t size, bool trigger_free, bool exit_on_fail)
{
	static t_garbage	*head = NULL;
	t_garbage			*new;
	static int			i = 0;
	void				*instant;

	if (trigger_free)
		return (_free(&head), NULL);
	if (!exit_on_fail)
    {
        instant = treat_ptr(size);
	    if (!instant)
		    exit_on_fail = true;
    }
	if (exit_on_fail)
	{
		_free(&head);
		perror("problem at allocation");
		exit(EXIT_FAILURE);
	}
	new = new_node(instant, i);
	i++;
	if (!new)
	{
		_free(&head);
		perror("we faced a problem");
		exit(EXIT_FAILURE);
	}
	add_node(&head, new);
	return (instant);
}
