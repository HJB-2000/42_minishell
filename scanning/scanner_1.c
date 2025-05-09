#include "lexer.h"

t_lexem* TokenGeneratore(t_parser* parser, lexem_type type)
{
    t_lexem *token;
    
    token = alloc(sizeof(t_lexem), 's');
    token->token_type = type;
    token->start = parser->begining;
    token->lenght = parser->current - parser->begining;
    token->position = parser->line_pos++;
    return (token);
}
t_lexem* UnxpectedToken(t_parser *parser, char *message)
{
    t_lexem* err_token;

    err_token = alloc(sizeof(t_lexem), 's');
    err_token->token_type = TOKEN_ERR;
    err_token->start = message;
    err_token->lenght = ft_strlen(message);
    err_token->position = parser->line_pos;
    return (err_token);
}
