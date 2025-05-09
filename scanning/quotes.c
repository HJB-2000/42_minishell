#include "lexer.h"

t_lexem* ManageDquote(t_parser* parser)
{
    // char *line;
    while(current_curr(parser) != '"')
    {
        if(isEnd(parser)){
            is_flying_token(parser, flying_op_err1, true);
            break;
        }
        proceed_curr(parser);
    }
    if(isEnd(parser))
        return UnxpectedToken(parser, "inclosed quotes !!");
    proceed_curr(parser);
    return TokenGeneratore(parser, TOKEN_DQUOTE);    
}
t_lexem* MangeSquote(t_parser* parser)
{
    // char* line;
    while(current_curr(parser) != '\'')
    {
        if(isEnd(parser)){
            is_flying_token(parser, flying_op_err1, true);
            break;
        }
        proceed_curr(parser);       
    }
    if(isEnd(parser))
        return UnxpectedToken(parser, "inclosed quotes !!");
    proceed_curr(parser);
    return TokenGeneratore(parser, TOKEN_SQUOTE);
}

