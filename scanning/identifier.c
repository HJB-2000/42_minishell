#include "lexer.h"
t_lexem *comfirm(t_parser *parser, int lenght, char* expected, lexem_type type)
{
    (void)lenght;
    if(!ft_memcmp((const void *)parser->begining, (const void *)expected, lenght))
        return TokenGeneratore(parser, type);
    return TokenGeneratore(parser, TOKEN_ID);
}

t_lexem* check_builtins(t_parser* parser)
{
    char curr;

    curr = current_beg(parser);
    if(curr == 'p')
        return (comfirm(parser, 3, "pwd", TOKEN_PWD));
    else if(curr == 'u')
        return (comfirm(parser, 5, "unset", TOKEN_UNSET));
    else if(curr == 'h')
        return (comfirm(parser, 7,"history", TOKEN_HISTORY));
    else if(curr == 'c' )
    {
        if(upcoming_beg(parser) == 'd'){
                return (comfirm(parser, 7, "cd", TOKEN_CD));
        }
        else if(upcoming_beg(parser) == 'l')
            return (comfirm(parser, 5, "clear", TOKEN_CLEAR));
    }
    else if(curr == 'e')
    {
        if(upcoming_beg(parser) == 'c')
        {
            return(comfirm(parser, 4, "echo", TOKEN_ECHO));
        }
        else if(upcoming_beg(parser) == 'n')
        {
            return(comfirm(parser, 3, "env", TOKEN_ENV));
        }
        else if(upcoming_beg(parser) == 'x')
        {
            if(parser->begining[2] == 'p')
            {
                return (comfirm(parser, 6,"export", TOKEN_EXPORT));
            }
            else if(parser->begining[2] == 'i') 
            {
                return (comfirm(parser, 4, "exit", TOKEN_EXIT));
            }
        }
    }
    return(TokenGeneratore(parser, TOKEN_ID));
}
bool isWhitespace(char c){
    if(c == 32 || (c >= 9 && c <= 13))
        return true;
    return false;
}
t_lexem* verify_id(t_parser *parser)
{
    int path = 0;
    int param = 0;
    if(current_beg(parser) == '-')
        param = 1;
    while(isAlpha(current_curr(parser)) || isNum(current_curr(parser)) || current_curr(parser) == '/' ||
          current_curr(parser) == '-')
    {
        if(current_curr(parser) == '/')
            path = 1;
        proceed_curr(parser);
    }
    if(path && param)
        return (check_builtins(parser));
    if(path)
        return TokenGeneratore(parser, TOKEN_PATH);
    if(param)
        return TokenGeneratore(parser, TOKEN_PARAM);
    return (check_builtins(parser));
}