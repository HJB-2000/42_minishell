#ifndef SCANNER_H
#define SCANNER_H
#include "../minishell.h"

// typedef enum {
// // Single-character tokens.
//   TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
//   TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE,
//   TOKEN_COMMA, TOKEN_DOT, TOKEN_MINUS, TOKEN_PLUS,
//   TOKEN_SEMICOLON, TOKEN_SLASH, TOKEN_STAR,
// // One or two character tokens.
//   TOKEN_BANG, TOKEN_BANG_EQUAL,
//   TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,
//   TOKEN_GREATER, TOKEN_GREATER_EQUAL,
//   TOKEN_LESS, TOKEN_LESS_EQUAL,
// // Literals.
//   TOKEN_IDENTIFIER, TOKEN_STRING, TOKEN_NUMBER,
// // Keywords.
//   TOKEN_AND, TOKEN_CLASS, TOKEN_ELSE, TOKEN_FALSE,
//   TOKEN_FOR, TOKEN_FUN, TOKEN_IF, TOKEN_NIL, TOKEN_OR,
//   TOKEN_PRINT, TOKEN_RETURN, TOKEN_SUPER, TOKEN_THIS,
//   TOKEN_TRUE, TOKEN_VAR, TOKEN_WHILE, TOKEN_PIPE,

//   TOKEN_ERROR, TOKEN_EOF
// } TokenType;

typedef enum {
//level 1
  TOKEN_OR_M, TOKEN_AND_M,
  
  //level 2
  TOKEN_PIPE_M,
//level 3
  TOKEN_REDIR_IN , TOKEN_REDIR_OUT,
  TOKEN_HEREDOC , TOKEN_REDIR_APPEND,
// level 4
  TOKEN_ASTERISK, TOKEN_QUESTION,
  TOKEN_SLASH_M, TOKEN_TILDE,
  TOKEN_DOT_M, TOKEN_DOTDOT,
  TOKEN_LPAREN, TOKEN_RPAREN,
  TOKEN_SQUOTE, TOKEN_DQUOTE,
  TOKEN_DOLLOR, TOKEN_DASH,
  TOKEN_OPTION,
  TOKEN_VAR_M, TOKEN_EXIT_STATUS,
  TOKEN_HASH, TOKEN_EOF_M,
//level 5
  // TOKEN_BUILTIN,
  TOKEN_PWD, TOKEN_UNSET, TOKEN_HISTORY,
  TOKEN_EXIT, TOKEN_ENV, TOKEN_EXPORT,
  TOKEN_ECHO, TOKEN_CD, TOKEN_CLEAR,
//level 6
  TOKEN_GROUP,
  TOKEN_PATH,
  TOKEN_IDENTIFIER,
  TOKEN_NUMBER , TOKEN_STRING,
  TOKEN_ERROR
} TokenType;

typedef enum{
	level_1,
	level_2,
	level_3,
	level_4,
	level_5,
	level_6
}precedence;




typedef enum {
	WORD_IDENTIFIER,
	L_P, R_P, L_B, R_B,
	REDIRECTION_IN,
	REDIRECTION_OUT,
	REDIRECTION_APPEND,
	REDIRECTION_ERR,
	AND_IF,
	AND_OR,
}Token_;




typedef struct s_Scanner {
    const char* start;
    const char* current;
    int line;
} Scanner;

typedef struct s_Token{
    TokenType type;
    const char* start;
    int length;
    int line;
} Token;

typedef struct s_tokens{
  Token *token;
  precedence PowerLevel;
  int index;
  struct s_tokens *next;
} TokenList;




void compile(const char *source);


bool isDigit(char c);
bool isAlpha(char c);
bool isAtEnd(Scanner* Scanner);
char advance(Scanner* scanner);
char peek(Scanner* Scanner) ;
char peekNext(Scanner* Scanner) ;
void skipWhitespace(Scanner* scanner);
bool match(Scanner* Scanner, char expected);

Token makeToken(Scanner* Scanner, TokenType type);
Token errorToken(Scanner* Scanner, const char* message);
TokenType checkKeyword(Scanner* Scanner,int start, int length,
const char* rest, TokenType type);
TokenType identifierType(Scanner* Scanner);
Token identifier(Scanner* scanner) ;
Token number(Scanner* scanner);
Token string(Scanner* scanner);

void initScanner(Scanner* scanner, const char* source);
Token scanToken(Scanner *Scanner);
void compile(const char *source);
void recognizeToken(TokenList* tokenlist);

Token SingleQ_string(Scanner* scanner);
Token DoubleQ_string(Scanner* scanner);
Token GroupingToken(Scanner* scanner) ;
#endif