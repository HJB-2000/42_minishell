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
    dup = alloc(sizeof(char) * len, 'r');
    if(!dup)
        destroy;
    i = 0;
    while(*str)
        dup[i++] = *str++;
    dup[i] = '\0';
    return (dup);
}

char* ft_strjoin(char* str1, char* str2){
    if(!str1 || !str2) destroy;
    int len = ft_strlen(str1) + ft_strlen(str2) + 1;
    char* joined = alloc(sizeof(char) * len, 'r');
    if(!joined) destroy;
    int i = 0;
    int j = 0;
    while(str1[i] && i < len){joined[i] = str1[i]; i++;} 
    while(str2[j] && i < len){joined[i++] = str2[j++];}
    joined[i] = '\0';
    str1 = joined;
    return str1; 
}

int ft_memcmp(const void *dst, const void *src, size_t size) {
    (void)size;
    if (!dst && !src)
        return 0;
    else if (!dst || !src)
        return 0;
    size_t i = 0;
    const unsigned char *d = (const unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    while(s[i] || d[i]){
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
