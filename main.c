/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahmida <jbahmida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:06:16 by jbahmida          #+#    #+#             */
/*   Updated: 2025/04/15 16:33:11 by jbahmida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
void l(void){system("leaks minishell");}

int main(int argc, char **argv, char **envp)
{
    HISTORY_STATE *len;
    char *line;
    // int i = 10;
    while(true)
    {
        line = read_input();
        if(line && *line){
            history(line, false, false);
            _malloc(0, len, false, false);
            if(!strcmp(line, "history"))
                history(NULL, true, false);
            else if(!strcmp(line, "clear"))
                history(NULL, false, true);
            else
                printf("%s\n",line);
        }
    }
    atexit(l);
}
