#include "lexer.h"

char* line_continue(char* msg)
{
    char* new_line;

    new_line = read_input(msg);
    if(!new_line)
        return NULL;
    return new_line;
}

void is_flying_token(t_parser* parser, char* msg, bool err)
{
    char* line;

    line = NULL;
    SkipWhiteSpace(parser);
    if(isEnd(parser)){
        if(err)
            printf("%s\n" ,msg);
        else
            line = line_continue(msg);
    }
    if(!line)
        return ;
    parser->begining = ft_strjoin(parser->begining, line);
    parser->current = ft_strjoin(parser->current, line);
}

t_lexem *scanner(t_parser* parser)
{
    t_lexem *token;
    char c;
    SkipWhiteSpace(parser);
    parser->begining = parser->current;
    if(isEnd(parser))
        return (TokenGeneratore(parser, TOKEN_EOL));
    c = proceed_curr(parser);
    if(isAlpha(c) || c == '-')
        return (verify_id(parser));
    else if(isNum(c))
    {
        token = verify_num(parser);
        return (token);
    }
    else if(c == '|')
    {
        if(current_curr(parser) == '|')
        {
            proceed_curr(parser);
            token = TokenGeneratore(parser, TOKEN_OR);
            is_flying_token(parser, "cmdor> ", false);
            return (token);
        }
        else
        {
            token = TokenGeneratore(parser, TOKEN_PIPE);
            is_flying_token(parser, "pipe> ", false);
            return token;
        }
    }
    else if(c == '&')
    {
        if(current_curr(parser) == '&')
        {
            proceed_curr(parser);
            token = TokenGeneratore(parser, TOKEN_AND);
            is_flying_token(parser, "cmdand> ", false);
            return token;
        }
        else
        return UnxpectedToken(parser, "Unxpected char");
    }
    else if(c == '>')
    {
        if(current_curr(parser) == '>'){
           proceed_curr(parser);
           token = TokenGeneratore(parser, TOKEN_APPEND);
           is_flying_token(parser, flying_op_err, true);
           return token;
        }
        else
        {
            proceed_curr(parser);
            token = TokenGeneratore(parser, TOKEN_OUTRE);
            is_flying_token(parser, flying_op_err, true);
            return token;
        }
    }
    else if(c == '<'){
        if(current_curr(parser) == '<'){
            proceed_curr(parser);
            token = TokenGeneratore(parser, TOKEN_HEREDOC);
            is_flying_token(parser, flying_op_err, true);
            return token;
        }
        else
        {
            proceed_curr(parser);
            token = TokenGeneratore(parser, TOKEN_INRE);
            is_flying_token(parser, flying_op_err, true);
            return token;
        }
    }
    else if(c == '"')
        return (ManageDquote(parser));
    else if(c == '\'')
        return (MangeSquote(parser));
    return UnxpectedToken(parser, "Unxpected char");
}
