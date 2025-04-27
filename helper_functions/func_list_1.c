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

int ft_memcmp(const void *dst, const void *src, size_t size) {
    if (!dst && !src)
        return 0;
    else if (!dst || !src)
        return size;
    size_t i = 0;
    const unsigned char *d = (const unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    while((s[i] || d[i]) && i < size){
        if(s[i] != d[i]){
            return d[i] - s[i];
        }
        i++;
    }
    return 0;
}

// void *ft_memmove(void *dst, void *src, size_t size) {
//     if (!dst || !src)
//         return NULL;
//     size_t i = 0;
//     unsigned char *d = (unsigned char *)dst;
//     const unsigned char *s = (const unsigned char *)src;

//     if (s < d && s + size > d) {
//         while (size--)
//             d[size] = s[size];
//     } else {
//         while( i < size){
//             d[i] = s[i];
//             i++;
//         }
//     }
//     return dst;
// }
