#include "minishell.h"

void l(void){system("leaks a.out");}

int main(){
    int *num;
    char **table;
    table = _malloc(sizeof(char *) * 4, false, false);
    char *str1 = _malloc(sizeof(char)*10, false, false);
    char *str2 = _malloc(sizeof(char)*10, false, false);
    char *str3 = _malloc(sizeof(char)*10, false, false);
    num = _malloc(sizeof(int)*10, false, false);
    strncpy(str1, "hello wroldvsvecwqcqwcwfewfewew", 10);
    strncpy(str2, "hello wroldvewewcwqcq", 10);
    strncpy(str3, "hello wroldvewxwcqw", 10);
    table[0] = str1;
    table[1] = str2;
    table[2] = str3;
    table[3] = NULL;
    for(int i = 0; i < 10; i++){num[i] = i;}
    for(int i = 0; table[i]; i++){
        printf("%s\n", table[i]);
    }
    atexit(l);
}