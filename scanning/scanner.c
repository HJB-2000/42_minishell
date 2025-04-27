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
    else if (c == '\'' ) return SingleQ_string(scanner);
    else if (c == '"' ) return DoubleQ_string(scanner);
    else if (c == '(' ) return GroupingToken(scanner);
    else if (c == '*' ) {
        while (!isWhitespace(peek(scanner)) && !isAtEnd(scanner)) advance(scanner);
        return makeToken(scanner, TOKEN_ASTERISK);
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
    else if (c == '$' )
    {
        if(match(scanner, '?')) return makeToken(scanner, TOKEN_EXIT_STATUS);
        else if (isAlpha(peekNext(scanner)) || isDigit(peekNext(scanner))){
            while (isAlpha(peek(scanner)) || isDigit(peek(scanner))) advance(scanner);
            return makeToken(scanner, TOKEN_VAR_M);
        }
        else return makeToken(scanner, TOKEN_DOLLOR);
    }
    // else if (c == '?' ) return makeToken(scanner, TOKEN_QUESTION);
    // else if (c == '/' ) {
    //     if(!isWhitespace(peekNext(scanner))){
    //         while(!isWhitespace(peek(scanner)) && !isAtEnd(scanner))advance(scanner);
    //         return makeToken(scanner, TOKEN_PATH);
    //     }
    //     else return makeToken(scanner, TOKEN_SLASH_M);
    // }
    // else if (c == '~' ) {
    //     if (match(scanner, '/')) {
    //         while (isAlpha(peek(scanner)) || peek(scanner) == '/') advance(scanner);
    //         return makeToken(scanner, TOKEN_PATH);
    //     }
    //     else  return makeToken(scanner, TOKEN_TILDE); 
    // }
    // else if (c == '.' ) {
    //     if (c == '.' ) return makeToken(scanner, TOKEN_DOTDOT);
    //     else return makeToken(scanner, TOKEN_DOT_M);;
    // }
    // else if(c == '-')
    // {
    //     if(isAlpha(peek(scanner)))
    //     {
    //         while(isAlpha(peek(scanner)) && !isAtEnd(scanner))advance(scanner);
    //         return makeToken(scanner, TOKEN_OPTION);
    //     }
    //     else if(peek(scanner) == '-') {
    //         while(peek(scanner) == '-')advance(scanner);
    //         return makeToken(scanner, TOKEN_PATH);
    //     }
    //     else if(isWhitespace(peek(scanner)) || isAtEnd(scanner))
    //         return makeToken(scanner, TOKEN_PATH);
    
    // }
    return errorToken(scanner, "Unexpected character . ");
}


TokenList* newTokenNode(Token* token, int index){
    TokenList* node;
    if (!token) return NULL;
    node = _malloc(sizeof(Token), NULL, false, false);
    if(!node) _malloc(0, NULL, false, true);
    node->token = token;
    node->index = index;
    node->next = NULL;
    return node;
} 
void AddTokenNode(TokenList** head, TokenList* newNode){
    if(!head || !newNode) return;
    if(!*head) {*head = newNode; return ;}
    TokenList* tmp = *head;
    while(tmp->next){
        tmp = tmp->next;
    }
    tmp->next = newNode;
}

Token* TokenDup(Token *token){
    Token* token_dup;
    if(!token) return NULL;
    token_dup = _malloc(sizeof(Token), NULL, false, false);
    token_dup->length = token->length;
    token_dup->type = token->type;
    token_dup->line = token->line;
    token_dup->start = ft_strdup(token->start);
    return token_dup;
}


// Token scanToken_MINI(Scanner* scanner){
//     skipWhitespace(scanner);
//     scanner->current = scanner->start;
//     if(isAtEnd(scanner)) return makeToken(scanner, TOKEN_EOF_M);
//     if(isAlpha(scanner)) return identifier(scanner);
//     if(isDigit) return number(scanner);
// }

typedef struct s_Parser{
    Token current;
    Token previous;
    bool hadError;
    bool panicMode;
} Parser;

void advance_parser(Scanner* scanner, Parser* parser){
    parser->previous = parser->current;
    for(;;){
        parser->current = scanToken_MINI(scanner);
        if(parser->current.type != TOKEN_ERROR) break;
        // errorToken(scanner, parser->current.start);
    }
}

void errorAt(Parser* parser,Token* token, const char* message) {
    if(parser->panicMode)return;
    parser->panicMode = true;
    fprintf(stderr, "[line %d] Error", token->line);
    if(token->type == TOKEN_EOF_M) fprintf(stderr, "at end");
    else if(token->type == TOKEN_ERROR){}//NOTHING
    else 
        fprintf(stderr, " at '%.*s'", token->length, token->start);
    fprintf(stderr, ": %s\n", message);
    parser->hadError = true;  
}


void errorAtCurrent(Parser* parser, const char* message){
    errorAt(parser ,&parser->current, message);
}

void error(Parser* parser, const char* message){
    errorAt(parser, &parser->previous, message);
}

void consume(Parser* parser, Scanner* scanner ,TokenType type, const char* message){
    if(parser->current.type == type){
        advance_parser(scanner, parser);
        return;
    }
    errorAtCurrent(parser, message);
}


void compile(const char *source) {
    Scanner scanner;
    // Parser parser;
    // TokenList *tokenlist = NULL;

    // parser.panicMode = false;
    // parser.hadError = false;
    initScanner(&scanner ,source);
    // advance_parser(&scanner, &parser);
    // expression();
    // consume(&parser ,&scanner ,TOKEN_EOF_M, "Expect end of expression. ");
    // return !parser.hadError;

    int line = -1;
    // int i = 0;
    while (true) {
        Token token = scanToken_MINI(&scanner);
        // AddTokenNode(&tokenlist, newTokenNode(TokenDup(&token), i++));
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
    // for(TokenList *tmp = tokenlist; tmp; tmp = tmp->next){
    //     printf("%2d %.*s\n", tmp->token->type, tmp->token->length, tmp->token->start); 
    // }
}