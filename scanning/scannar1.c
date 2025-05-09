#include "scannar1.h"

void InitScannar(Scannar* scanner, const char* cmd){
    scanner = _malloc(sizeof(scanner), NULL, false, false);
    scanner->start = cmd;
    scanner->current = cmd;
    scanner->tokenPos = 0;
}

bool EndLine(Scannar* scanner){
    if(*scanner->start == EOF)
        return true;
    return false;
}

bool Alpha(char c){
    return((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

bool Number(char c){
    return((c >= 48 && c <= 57));
}

bool Whitespace(char c){
    return ((c >= 9 && c <= 13)); 
}

char travel(Scannar* scanner, bool advance, bool current, bool next)
{
    if(advance){
        scanner->current++;
        return (scanner->current[-1]);
    }
    else if(current) return scanner->current[0];
    else if(next) return scanner->current[1];
    return 0;
}
#define Advance(scanner) travel(scanner, true, false, false)
#define PeekCurrent(scanner) travel(scanner, false, true, false)
#define PeekNext(scanner) travel(scanner, false, false, true)

void SkipWhitespace(Scannar* scanner){
    char c;
    if(EndLine(scanner)) return ;
    while(true) {
        c = PeekCurrent(scanner);
        if(Whitespace(c)) {
            c = Advance(scanner);
        }
        else if(c == '\n') { //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            // scanner->line++;
            c = Advance(scanner);
        }
        else
            break;
    }
}

Tokens* tokenConstractor(Scannar* scanner, token_type type){
    Tokens* lex = malloc(sizeof(Tokens));
    if(!lex) return NULL;
    lex->type = type;
    lex->start = scanner->start;
    lex->lenght = scanner->current - scanner->start;
    lex->position = scanner->tokenPos++;
    return lex;
}

Tokens* tokenError(Scannar* scanner, char* msg){
    Tokens* err = malloc(sizeof(Tokens));
    if(!err) return NULL;
    err->type = TOKEN_ERR;
    err->start = msg;
    err->lenght = ft_strlen(msg);
    err->position = scanner->tokenPos++;
    return err;
} 

char* BuiltinCheck(Scanner* scanner){
    int count = 0;
    for(int i = 0; Alpha(scanner->start[i]); i++)
        count++;
    char buffer[++count];
    char **builtins = {"echo", "pwd", "export", "clear", "unset", "history", "unset",
                        "cd", "exit", "env", ""};
    int i = 0;
    while(scanner->start[i] && i <= count){buffer[i] = scanner->current[i]; i++;}
    buffer[i] = '\0';
    i = 0;
    while(builtins[i]){
        if(ft_memcmp(buffer, builtins, count))
            break;
        i++;
    }
    if(builtins[i])
        return builtins[i];
    return NULL;
}




Tokens* ScanToken(Scannar* scanner){
    char c;
    SkipWhitespace(scanner);
    if(EndLine(scanner)) return tokenConstractor(scanner, TOKEN_EOL);
    if(Alpha(*scanner->start) && BuiltinCheck(scanner)) return Builtinconstractor(scanner); // Alpha , determine_id
    c = Advance(scanner);
    if(Alpha(c)) return determine_id(scanner); // Alpha , determine_id : check path , exectuble command absolute/relative , ...
    else if(Number(c)) return determine_num(scanner); // Number, determine_num
    else if(c == '&') {
        Advance(scanner);
        if(PeekCurrent(scanner) == '&') return tokenConstractor(scanner, TOKEM_AND);
        else return tokenError(scanner, "Unxepected chacter");
    } // AND    
    else if(c == '|'){
        Advance(scanner);
        if(PeekCurrent(scanner) == '|'){
            return tokenConstractor(scanner, TOKEN_OR);
        }
        else return tokenConstractor(scanner, TOKEN_PIPE);

    } // PIPE , OR   
    else if(c == '"'){
        return Dquotes_string(scanner);
    } // DOUBELE QUETES   
    else if(c == '\''){
        return single_string(scanner);
    } // SINGLE QUETES   
}

Ltokens* new_lexem(Tokens* token, int index){
    if(!token) return NULL;
    Ltokens* holder = malloc(sizeof(Ltokens));
    if(!holder) return NULL;
    holder->lexem = token;
    holder->line_order = index;
    holder->next = NULL;
    return holder;
}

void add_lexem(Ltokens** head, Ltokens* lexem){
    if(!head || !lexem) return ;
    if(!*head) {*head = lexem; return ;}
    Ltokens* tmp = *head;
    while(tmp->next) tmp = tmp->next;
    tmp->next = lexem;
}

void delete_lexem(Ltokens** head, token_type lexem_type, int lexem_pos){
    if(!head || !*head) return NULL;
    Ltokens* tmp = *head;
    Ltokens* current;
    while(tmp){
        if(tmp->next->lexem->type == lexem_type && tmp->next->line_order == lexem_pos){
            current = tmp->next;
            tmp = tmp->next->next;
            free(current);
            current = NULL;
            break;
        }
        tmp = tmp->next;
    }
}

Ltokens* find_lexem(Ltokens** head, token_type type, int pos){
    if(!head || !*head) return NULL;
    Ltokens* tmp = *head;
    while(tmp){
        if(tmp->line_order = pos && tmp->lexem->type == type){
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

void destroy_lexems(Ltokens** head){
    if(!head || !*head) return ;
    Ltokens* tmp = *head;
    Ltokens* current = *head;
    while(tmp){
        current = tmp;
        tmp = tmp->next;
        free(current);
        current = NULL;
    }
}

void compile_1(const char* cmdLine){
    Scannar* scanner;
    Ltokens* lexems_list;
    Tokens *lexem;
    int index;
    if(!cmdLine)return ;
    InitScanner(scanner, cmdLine);
    while(true) {
        lexem = ScanTokens(scanner);
        if(!lexem) exit(1);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        add_lexem(&lexems_list, new_lexem(lexem, index)); //add_lexem ; new_lexwem
        if(lexem == TOKEN_EOL) break;
        index++;
    }
    for(Ltokens* tmp = lexems_list; tmp; tmp->next){
        printf("%d |===> %s\n", tmp->line_order, tmp->lexem->start);
    }
}
