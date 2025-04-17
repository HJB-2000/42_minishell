/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahmida <jbahmida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:05:57 by jbahmida          #+#    #+#             */
/*   Updated: 2025/04/14 21:36:18 by jbahmida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void *allocate_memory(size_t size)
{
    void *holder;

    holder = malloc(size);
    if (!holder)
        return NULL;
    return holder;
}

static t_garbage *new(void *pointer, int index)
{
    t_garbage *new_node = NULL;
    if(!pointer)
        return NULL;
    new_node = malloc(sizeof(t_garbage));
    if(!new_node)
        return NULL;
    new_node->allocted = pointer;
    new_node->index = index;
    new_node->next = NULL;
    return new_node;
}
static void insertnode(t_garbage **head, t_garbage *node)
{
    t_garbage *tmp;

    if(!head || !node)
        return ;
    if(!*head) 
    {
        *head = node;
        return;
    }
    tmp = *head;
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = node;    
}
static void _free(t_garbage **head)
{
    t_garbage *tmp;
    t_garbage *current;

    if(!head || !*head)
        return ;
    tmp = *head;
    while(tmp)
    {
        current = tmp;
        tmp = tmp->next;
        free(current->allocted);
        current->allocted = NULL;
        free(current);
        current = NULL;
    }
    *head = NULL;
}
void *_malloc(size_t size, void *non_allocted ,bool trigger_free, bool error_free)
{
    //create a garabage node to hold the alloceted memory address and it index of allocation
    //add this created node to the static linked list
    // we need a free function for this list in case we needed to free

    void *instence = NULL;
    t_garbage *new_node;
    static t_garbage *garbage;
    static int i = 0;

    if(trigger_free)
    {
        _free(&garbage);
        return NULL;
    }
    if ((size > 0 || non_allocted) && !error_free)
    {
        if(size > 0 || !non_allocted)
            instence = allocate_memory(size);
        else
            instence = non_allocted;
        if (!instence)
            error_free = true;
        new_node = new(instence, i);
        if (!new_node)
            error_free = true;
        insertnode(&garbage, new_node);
        i++;
    }
    if(error_free)
    {
        if(instence)
        {
            free(instence);
            instence = NULL;
        }
        _free(&garbage);
        garbage = NULL;
        perror("allocation problem");
        exit(EXIT_FAILURE);       
    }
    return instence;   
}