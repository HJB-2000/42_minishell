#ifndef SCANNAR1_H
#define SCANNAR1_H

#include "../minishell.h"


typedef enum Token_type{
    TOKEN_EOL,
    TOKEN_ERR,
    TOKEN_ID,
    TOKEN_DQ,
    TOKEN_SQ,
    TOKEN_PIPE,
    TOKEM_OR,
    TOKEM_AND
}token_type;

//TOKEN OBJECT
typedef struct token{
    token_type type;
    const char* start;
    int lenght;
    int position;
}Tokens;

/****************/



/*list of tokens*/
typedef struct List_of_tokens
{
    Tokens *lexem;
    int line_order;
    struct List_of_tokens* next;
    //precedence
    //associativity
}Ltokens;

Ltokens* new_lexem(Token* token, int index);
void add_lexem(Ltokens **head, Ltokens *lexem);
void delete_lexem(Ltokens **head, TokenType lexem_type, int lexem_pos);
Ltokens* find_lexem(Ltokens **head, TokenType lexem_type, int lexem_index);
void destroy_lexems(Ltokens **head);

/****************/


//scanner structer
typedef struct scanner {
    const char* start;
    const char* current;
    int tokenPos;
}Scannar;
/************/
void InitScannar(Scannar *scanner, const char* cmd);
Tokens* ScanToken(Scannar* scanner);
void compile_1(const char* cmdLine);

#endif