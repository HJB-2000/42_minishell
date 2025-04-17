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

void l(void){system("leaks minishell");}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;
    char *line;
    int i = 20;
    while(i--)
    {
        line = read_input();
        printf("%s\n",line);
        free(line);
        line = NULL;
    }
    _malloc(0, NULL, true, false);
    history(NULL, false, true);
}
