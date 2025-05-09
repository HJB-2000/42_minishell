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

static t_field* choose_garbage()
{   
    static t_field ptrs = {NULL, NULL, NULL, NULL};
    return &ptrs;
}
static void _free_all(t_field **ptrs)
{
    t_field *grc;
    grc = *ptrs;
    _free(&grc->history); grc->history=NULL;
    _free(&grc->input_cmd);grc->input_cmd = NULL;
    _free(&grc->scanner); grc->scanner =NULL;
    _free(&grc->helper_funcs); grc->helper_funcs =NULL;

}
void *_malloc(size_t size, void *non_allocted ,int behavior, char field)
{
    t_field *ptrs;
    static t_garbage **garbage;

    t_garbage *new_node;

    void *instence = NULL;
    static int i = 0;
    int err = 0;

    ptrs = choose_garbage();
    if(field == 'a')
    {
        _free_all(&ptrs);
    }
    else if(field == 'i')
        garbage = &ptrs->input_cmd;
    else if(field == 'h')
        garbage = &ptrs->history;
    else if(field == 's')
        garbage = &ptrs->scanner;
    else if(field == 'r')
    garbage = &ptrs->helper_funcs;
    else
        garbage = NULL;

    if(behavior == 2)
        err = 1;
    if(behavior == 1)
    {
        _free(garbage);
        return NULL;
    }
    if ((size > 0 || non_allocted) && behavior == 0)
    {
        if(size > 0 || !non_allocted)
            instence = allocate_memory(size);
        else
            instence = non_allocted;
        if (!instence)
            err = 1;
        new_node = new(instence, i);
        if (!new_node)
            err = 1;
        insertnode(garbage, new_node);
        i++;
    }
    if(err == 1)
    {
        if(instence)
        {
            free(instence);
            instence = NULL;
        }
        _free_all(&ptrs);
        exit(EXIT_FAILURE);       
    }
    return instence;   
}
