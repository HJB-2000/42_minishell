#include "scanner.h"

void initScanner(Scanner* scanner, const char* source) {
    scanner->start = source;
    scanner->current = source;
    scanner->line = 1;
}

bool isWhitespace(char c) {
    if((c >=9 && c <= 13) || c == 32) return true;
    return false;
}

Token scanToken_MINI(Scanner* scanner){
    skipWhitespace(scanner);

    scanner->start = scanner->current;
    if(isAtEnd(scanner)) return makeToken(scanner, TOKEN_EOF_M);
    char c = advance(scanner);
    if (isAlpha(c)) return identifier(scanner);
    if (isDigit(c)) return number(scanner);
    else if(c == '-')
    {
        if(isAlpha(peek(scanner)))
        {
            while(isAlpha(peek(scanner)) && !isAtEnd(scanner))advance(scanner);
            return makeToken(scanner, TOKEN_OPTION);
        }
        else if(peek(scanner) == '-') {
            while(peek(scanner) == '-')advance(scanner);
            return makeToken(scanner, TOKEN_PATH);
        }
        else if(isWhitespace(peek(scanner)) || isAtEnd(scanner))
            return makeToken(scanner, TOKEN_PATH);
            
    }
    else if (c == '*' ) {
        while (!isWhitespace(peek(scanner)) && !isAtEnd(scanner)) advance(scanner);
        return makeToken(scanner, TOKEN_ASTERISK);
    }
    else if (c == '?' ) return makeToken(scanner, TOKEN_QUESTION);
    else if (c == '(' ) return makeToken(scanner, TOKEN_LPAREN);
    else if (c == ')' ) return makeToken(scanner, TOKEN_RPAREN); 
    else if (c == '/' ){
        if(!isWhitespace(peekNext(scanner))){
            while(!isWhitespace(peek(scanner)) && !isAtEnd(scanner))advance(scanner);
            return makeToken(scanner, TOKEN_PATH);
        }
        else return makeToken(scanner, TOKEN_SLASH_M);
    }
    else if (c == '~' ) {
        if (match(scanner, '/')) {
            while (isAlpha(peek(scanner)) || peek(scanner) == '/') advance(scanner);
            return makeToken(scanner, TOKEN_PATH);
        }
        else  return makeToken(scanner, TOKEN_TILDE); 
    }
    else if (c == '|' ){
        if(match(scanner, '|')) return makeToken(scanner, TOKEN_OR_M);
        else return makeToken(scanner, TOKEN_PIPE_M);
    }
    else if (c == '&') {
        if(match(scanner, '&')) return makeToken(scanner, TOKEN_AND_M);
        else return errorToken(scanner, "Unexpected character . ");
    }
    else if (c == '<' ) {
        if (match(scanner, '<')) return makeToken(scanner, TOKEN_HEREDOC);
        else return makeToken(scanner, TOKEN_REDIR_IN);
    }
    else if (c == '>' ){
        if (match(scanner, '>')) return makeToken(scanner, TOKEN_REDIR_APPEND);
        else return makeToken(scanner, TOKEN_REDIR_OUT);;
    }
    else if (c == '.' ) {
        if (c == '.' ) return makeToken(scanner, TOKEN_DOTDOT);
        else return makeToken(scanner, TOKEN_DOT_M);;
    }
    else if (c == '\'' ) return SingleQ_string(scanner);
    else if (c == '"' ) return DoubleQ_string(scanner);
    
    else if (c == '$' )
    {
        if(match(scanner, '?')) return makeToken(scanner, TOKEN_EXIT_STATUS);
        else if (isAlpha(peekNext(scanner)) || isDigit(peekNext(scanner))){
                while (isAlpha(peek(scanner)) || isDigit(peek(scanner))) advance(scanner);
            return makeToken(scanner, TOKEN_VAR_M);
        }
        else return makeToken(scanner, TOKEN_DOLLOR);
    }
    return errorToken(scanner, "Unexpected character . ");
}


typedef struct s_tokens{
    Token *token;
    int index;
    struct s_tokens *next;
} TokenList;


TokenList* newTokenNode(Token* token, int index){
    TokenList* node;
    if (!token) return NULL;
    node = _malloc(sizeof(Token), NULL, false, false);
    if(!node) _malloc(0, NULL, false, true);
    node->token = token;
    node->index = index;
    return node;
} 
void AddTokenNode(TokenList** head, TokenList* newNode){
    if(!head || !newNode) return NULL;
    if(!*head) {*head = newNode; return ;}
    else
        TokenList* tmp = *head;

}



Token scanToken_MINI(Scanner* scanner){
    skipWhitespace(scanner);
    scanner->current = scanner->start;
    if(isAtEnd(scanner)) return makeToken(scanner, TOKEN_EOF_M);
    if(isAlpha(scanner)) return identifier(scanner);
    if(isDigit) return number(scanner);
}


void compile(const char *source) {
    Scanner scanner;
    initScanner(&scanner ,source);
    int line = -1;
    while (true) {
        Token token = scanToken_MINI(&scanner);
        if (token.line != line) {
            printf("%4d ", token.line);
            line = token.line;
        } 
        else {
            printf("   | ");
        }
        printf("%2d %.*s\n", token.type, token.length, token.start); 
        if (token.type == TOKEN_EOF_M) break;
    }
}