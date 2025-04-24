#include "../minishell.h"

static char *extract_absolute_path(char *str)
{
    char *absolute_path;
	int count;
	int len;
	int start;

    count = 0;
    len = ft_strlen(str) - 1;
    while(str[len--] != '/')
        count++;
    start = ft_strlen(str) - count;
    // absolute_path = _malloc(sizeof(char) * count +1, NULL, false, false);
    absolute_path = ALLOCATE(sizeof(char) * count +1, NULL, false, false);
    if(!absolute_path)
    {
        // _malloc(0, NULL, false, false);
        ALLOCATE(0, NULL, true, false);
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
    // prompt = _malloc(sizeof(char) * len, NULL, false, false);
    prompt = ALLOCATE(sizeof(char) * len, NULL, false, false);
    if(!prompt)
		return ALLOCATE(0, NULL, true, false);
		// return _malloc(0, NULL, true, false);
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

char *read_input(void)
{
    char *line;
    char *prompt;

    prompt = prompt_generator(getenv("USER"), "==> ",
                extract_absolute_path(getenv("PWD")), " $: ");
    line = readline(prompt);
    if(!line)
        return(ALLOCATE(0, NULL, true, false));
        // return(_malloc(0, NULL, true, false));
    if(line && *line){
        if(!history(line, false, false)){
            printf("Error: history failed\n");
            exit(1);
        }
        // _malloc(0, line, false, false);
        ALLOCATE(0, line, false, false);
        if(!strcmp(line, "history"))
            history(NULL, true, false);
        else if(!strcmp(line, "clear"))
            history(line, false, true);
    }
    return (line);
}
