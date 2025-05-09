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

typedef struct s_field 
{
	t_garbage *input_cmd; // i
	t_garbage *history; // h
	t_garbage *scanner; // s
	t_garbage *helper_funcs;// r
}t_field;


#ifndef alloc
#define alloc(size, c) _malloc(size, NULL, 0,c)
#endif
#ifndef remember
#define remember(ptr, c) _malloc(0, ptr, 0, c)
#endif
#ifndef cleanup
#define cleanup(c) _malloc(0, NULL, 1,c)
#endif
#ifndef destroy
#define destroy _malloc(0, NULL, 2, '\0')
#endif

void *_malloc(size_t size, void *non_allocted ,int behavior, char field);


#endif
