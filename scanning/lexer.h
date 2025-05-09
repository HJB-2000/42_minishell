#ifndef LEXER_H
#define Lexer_H

#pragma once
#include "../minishell.h"

#define flying_op_err "minishel syntax error near unexpected token `newline'"
#define flying_op_err1 "unclosed quotes"
/*
 * This is an enum data structure that defines the available tokens.
 * The tokens are organized in a hierarchy of precedence levels,
 * from the most important to the least important.
 * The "power" of a token is determined by its precedence and associativity.
 */

typedef enum {
    TOKEN_EOL,
    TOKEN_ERR,
    
    //identifiers
    TOKEN_ID,
    TOKEN_NUM,
    TOKEN_PATH,
    TOKEN_PARAM,
    TOKEN_DQUOTE,
    TOKEN_SQUOTE,
    
    //builtins
    TOKEN_CD,
    TOKEN_CLEAR,
    TOKEN_PWD,
    TOKEN_UNSET,
    TOKEN_HISTORY,
    TOKEN_EXIT,
    TOKEN_EXPORT,
    TOKEN_ENV,
    TOKEN_ECHO,

    //redirection
    TOKEN_INRE, // <
    TOKEN_OUTRE, // >
    TOKEN_HEREDOC, // << 
    TOKEN_APPEND, // >> 

    //operators
    TOKEN_PIPE,
    TOKEN_OR,
    TOKEN_AND,
}lexem_type;

/*
 * This struct defines a token object.
 * It describes the characteristics of a token through its members:
 *
 * @lexem_type: Represents the type of the token.
 * @line_pos:   Represents the position of the token in the command line.
 * @length:     Represents how many characters are in the token itself.
 * @start:      A pointer to the beginning of the token.
 *
 * Knowing the starting position and the length of a token allows us
 * to precisely identify the token as a distinct word.
 */

typedef struct s_lexem{
    lexem_type token_type;
    char* start;
    unsigned int lenght;
    int position;
}t_lexem;

/*
 * This struct contains elements that help us scan the command line
 * and keep track of the parser's position, avoiding loss or skipping of characters.
 *
 * @start:     A pointer to the beginning of the current token.
 * @current:   A pointer that helps us locate the current parser position.
 * @tokenpos:  An integer that indicates the position of the found token in the line.
 */

typedef struct s_parser{
    char* begining;
    char* current;
    int line_pos;
}t_parser;



typedef struct s_llist{
    t_lexem* lexem;
    unsigned int index;
}t_llist;

/***********************************************************/
char travel_line_curr(t_parser* parser, bool proceed, bool current, bool upcome);
#ifndef proceed_curr
#define proceed_curr(parser) travel_line_curr(parser, true, false, false)
#endif
#ifndef current_curr
#define current_curr(parser) travel_line_curr(parser, false, true, false)
#endif
#ifndef upcoming_curr
#define upcoming_curr(parser) travel_line_curr(parser, false, false, true)
#endif
char travel_line_beg(t_parser* parser, bool proceed, bool current, bool upcome);
#ifndef proceed_beg
#define proceed_beg(parser) travel_line_beg(parser, true, false, false)
#endif
#ifndef current_beg
#define current_beg(parser) travel_line_beg(parser, false, true, false)
#endif
#ifndef upcoming_beg
#define upcoming_beg(parser) travel_line_beg(parser, false, false, true)
#endif
/***********************************************************/
void    SkipWhiteSpace(t_parser* parser);
bool    isSpace(char c);
bool    isNum(char c);
bool    isAlpha(char c);
bool    isEnd(t_parser* parser);
/***********************************************************/
t_lexem* TokenGeneratore(t_parser* parser, lexem_type type);
t_lexem* UnxpectedToken(t_parser *parser, char *message);
/***********************************************************/
t_lexem* scanner(t_parser* parser);
void is_flying_token(t_parser* parser, char* msg, bool err);

/***********************************************************/
t_lexem* verify_id(t_parser *parser);
t_lexem* verify_num(t_parser* parser);
t_lexem* check_builtins(t_parser* parser);
t_lexem* comfirm(t_parser *parser, int lenght, char* rest, lexem_type type);
/***********************************************************/
t_lexem* ManageDquote(t_parser* parser);
t_lexem* MangeSquote(t_parser* parser);
/***********************************************************/
/***********************************************************/
void lexer(char* commad);
t_parser* InitParser(char* commad);
/***********************************************************/


#endif