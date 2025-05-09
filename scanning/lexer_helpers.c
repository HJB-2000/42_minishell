#include "lexer.h"


bool isEnd(t_parser* parser)
{
    if(!*parser->current)
        return true;
    return(false); 
}

bool isAlpha(char c)
{
    return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

bool isNum(char c)
{
    return (c >= 48 && c <= 57);
}

bool isSpace(char c)
{
    return(c == 32 || (c <= 13 && c >= 9));
}

void SkipWhiteSpace(t_parser* parser)
{
    char c;
    if(!parser->begining || !*parser->begining || isEnd(parser))
        return ;
    while(true)
    {
        c = current_curr(parser);
        if(isSpace(c)){
            proceed_curr(parser);
        }
        else
            break;
    }
    
}

