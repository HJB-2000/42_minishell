#ifndef READ_INPUT_AND_HISTORY_H
#define READ_INPUT_AND_HISTORY_H

#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_HISTORY{
    const char *line;
    int  index_line;
    struct s_HISTORY *next;
}t_HISTORY;


char *read_input(void);

bool history(const char *line, bool display, bool clear);
// t_HISTORY *new_hist_entry(const char *line, int index_line);
// void InsertEntry(t_HISTORY **hist, t_HISTORY *entry);
// void print_hist(t_HISTORY **hist);


#endif