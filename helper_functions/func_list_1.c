#include "../minishell.h"

/*
    *ft_strlen : calculate the lenght of a string
    *ft_strdup : duplicate a string
*/

int ft_strlen(char *str)
{
    int count = 0;
    while(*str++)
        count++;
    return count;
}

char *ft_strdup(const char *str)
{
    char *dup;
    int len;
    int i;

    if(!str)
        return (NULL);
    len = ft_strlen((char *)str) + 1;
    dup = malloc(sizeof(char) * len);
    if(!dup)
        return (NULL);
    i = 0;
    while(*str)
        dup[i++] = *str++;
    dup[i] = '\0';
    return (dup);
}
