#include "../minishell.h"

static char *extract_absolute_path(char *str)
{
    char *absolute_path;
	int count;
	int len;
	int start;

    count = 0;
    len = ft_strlen(str);
    while(str[len--] != '/')
        count++;
    start = ft_strlen(str) - count;
    absolute_path = alloc(count+1, 'i');
    if(!absolute_path)
    {
        cleanup('i');
    	return (NULL);
    }
	count = 0;
    while(str[start])
		absolute_path[count++] = str[start++];
    absolute_path[count] = '\0';
    return (absolute_path);
}

static char *prompt_generator(char *str1, char *str2, char *str3, char *str4)
{
    int len;
    char *prompt;
    int count;

    if(!str1 || !str2)
    	return (NULL);
    len = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3)
            + ft_strlen(str4) + 1;
    prompt = alloc(sizeof(char) * len, 'i');
    if(!prompt)
		return cleanup('i');
    count = 0;
    while(*str1 && count < len)
		  prompt[count++] = *str1++;
    while(*str2 && count < len)
		  prompt[count++] = *str2++;
    while(*str3 && count < len)
		  prompt[count++] = *str3++;
    while(*str4 && count < len)
		  prompt[count++] = *str4++;
    prompt[count] = '\0'; 
    return (prompt);
}


char *read_input(char *msg)
{
    char *line;
    char *prompt;

    if(!msg){
        prompt = prompt_generator(getenv("USER"), "==> ",
                    extract_absolute_path(getenv("PWD")), " $: ");
    }
    else
        prompt = msg;
    
    line = readline(prompt);
    if(!line)
        return(cleanup('i'));
    if(line && *line){
        if(!history(line, false, false)){
            printf("Error: history failed\n");
            exit(1);
        }
        remember(line, 'i');
        if(!strcmp(line, "history"))
            history(NULL, true, false);
        else if(!strcmp(line, "clear")){
            // cleanup('h');
            history(line, false, true);
        }
    }
    return (line);
}
