/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahmida <jbahmida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:05:50 by jbahmida          #+#    #+#             */
/*   Updated: 2025/04/14 20:54:57 by jbahmida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
#define MALLOC_H

typedef struct s_garbage
{
	void				*allocted;
	int					index;
	struct s_garbage	*next;
}	t_garbage;

void *_malloc(size_t size, void *non_allocted ,bool trigger_free, bool error_free);
static void _free(t_garbage **head);
static void insertnode(t_garbage **head, t_garbage *node);
static t_garbage *new(void *pointer, int index);
static void *allocate_memory(size_t size);

#endif
