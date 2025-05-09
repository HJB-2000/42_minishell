#include "lexer.h"

t_lexem* verify_num(t_parser* parser)
{
    while (isNum(current_curr(parser))) proceed_curr(parser);  
    if (current_curr(parser) == '.' && isNum(upcoming_curr(parser))) 
    {
        proceed_curr(parser);   
        while (isNum(current_curr(parser)))
            proceed_curr(parser);
    }
    return TokenGeneratore(parser, TOKEN_NUM);
}
