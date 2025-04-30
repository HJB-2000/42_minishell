#include "scanner.h"

void swap(TokenList** node1, TokenList** node2){
    Token* token;
    token = (*node1)->token ;
    (*node1)->token = (*node2)->token;
    (*node2)->token = token;
}   

void PrecedeceLevel(TokenList* tokenlist){
    TokenList* tmp = tokenlist;
    while(tmp){
        if(tmp->token->type == 0) tmp->PowerLevel = level_1;
        else if(tmp->token->type == 1 ) tmp->PowerLevel = level_2;
        else if(tmp->token->type ==2 ) tmp->PowerLevel = level_3;
        else if(tmp->token->type == 3 ) tmp->PowerLevel = level_4;
        else if(tmp->token->type == 4 ) tmp->PowerLevel = level_5;
        else if(tmp->token->type == 5 ) tmp->PowerLevel = level_6;
        else if(tmp->token->type == 6 ) tmp->PowerLevel = level_7;
        else if(tmp->token->type == 7 ) tmp->PowerLevel = level_8;
        tmp = tmp->next;
    }
}

void AssociativityLevel(TokenList* tokenlist){
    TokenList* tmp = tokenlist;
    while(tmp){
        if(tmp->PowerLevel < level_3) tmp->PworType = left_right;
        else if(tmp->PowerLevel >= level_3 && tmp->PowerLevel < 6) tmp->PworType = nil_right;
        else if(tmp->PowerLevel >= 6  && tmp->PowerLevel <= 7) tmp->PworType = nil_nil;
        tmp = tmp->next;
    }
}

void reoderList1(TokenList** tokenlist) {
    if (!tokenlist || !*tokenlist || !(*tokenlist)->next) {
        return;
    }

    TokenList* tmp;
    TokenList* last = *tokenlist;
    bool swapped = true;
    while(swapped){
        swapped = false;
        tmp = *tokenlist;
        while(tmp->next && tmp->next != last){    
            if (tmp->next && tmp->token->type > tmp->next->token->type) {
                Token* tempToken = tmp->token;
                tmp->token = tmp->next->token;
                tmp->next->token = tempToken;           
                swapped = true;
            }
            tmp = tmp->next;
        }
        last = tmp;
    }
}

void prepereContainers(AST* tree){
    if(tree->lexem) {free(tree->lexem); tree->lexem = NULL;}
    else tree->lexem = NULL;
    tree->value = NULL;
    tree->left_node = NULL;
    tree->right_node = NULL;
}
// void StuffTree(AST* tree, TokenList* tokenlist){

// }


void recognizeToken(TokenList* tokenlist){
    PrecedeceLevel(tokenlist);
    AssociativityLevel(tokenlist);
    // reoderList1(&tokenlist);
    // AST* tree;
    // prepereContainers(tree);
    // StuffTree(tree , tokenlist);
}