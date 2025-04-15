#include "../minishell.h"

t_HISTORY *new_hist_entry(const char *line, int index_line)
{
    t_HISTORY *new_entry;

    if(!line)
        return (NULL);
    new_entry = malloc(sizeof(t_HISTORY));
    if(!new_entry)
        return (NULL);
    if(!(new_entry->line = ft_strdup(line)))
        return (NULL);
    new_entry->index_line = index_line;
    new_entry->next = NULL;
    return (new_entry);
}

void InsertEntry(t_HISTORY **hist, t_HISTORY *entry)
{
    t_HISTORY *tmp;

    if(!hist || !entry)
        return ;
    if(!*hist)
    {
        *hist = entry;
        return ;
    }
    tmp = *hist;
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = entry;
    return ;
}

void print_hist(t_HISTORY **hist)
{
    t_HISTORY *tmp;

    if(!hist || !*hist)
        return ;
    tmp = *hist;
    while(tmp)
    {
        printf("%d: %s\n", tmp->index_line, tmp->line);
        tmp = tmp->next;
    }
    return;
}

void clear_hist(t_HISTORY **hist)
{
    t_HISTORY *tmp;
    t_HISTORY *current;

    if(!hist || !*hist)
        return ;
    tmp = *hist;
    while(tmp)
    {
        current = tmp;
        free((void *)current->line);
        free(current);
        current = NULL;
        tmp = tmp->next;
    }
    *hist = NULL;
}

bool history(const char *line, bool display, bool clear)
{
    static t_HISTORY *hist = NULL;
    static int index = 1;
    t_HISTORY *tmp;

    if(display)
    {
        print_hist(&hist);
        return true;
    }
    if(clear)
    {
        rl_clear_history();
        clear_hist(&hist);
        index = 1;
        return true;
    }
    tmp = new_hist_entry(line, index);
    if(!tmp)
        return false; //handle the returnment in error case;
    add_history(line);
    InsertEntry(&hist, tmp);
    index++;
    return (true);
}
