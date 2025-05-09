#include "lexer.h"

t_parser* InitParser(char* commad)
{
    t_parser* parser;

    parser = alloc(sizeof(t_parser), 's');
    parser->begining = commad;
    parser->current = commad;
    parser->line_pos = 0;
    return (parser);
}

void lexer(char* commad)
{
    t_lexem* token;
    t_parser* parser;
    
    parser = InitParser(commad);
    while(true){
        token = scanner(parser);
        printf("%2d |==> %.*s\n", token->token_type, token->lenght ,token->start);
        // printf("%2d %.*s\n", token->token_type, token->lenght, token->start);
        // cleanup('r'); 
        if(token->token_type == TOKEN_EOL)
        break;
    }
    cleanup('s'); 
}








