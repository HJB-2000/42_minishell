#include "scanner.h"

// void swap(TokenList* tokenlist){

// }

void reoderList(TokenList* tokenlist){
    TokenList* tmp = tokenlist;
    while(tmp){
        if(tmp->token->type < 2){tmp->PowerLevel = level_1;}
        else if(tmp->token->type == 2){tmp->PowerLevel = level_2;}
        else if(tmp->token->type > 2 && tmp->token->type < 7){tmp->PowerLevel = level_3;}
        else if(tmp->token->type > 7 && tmp->token->type < 23){tmp->PowerLevel = level_4;}
        else if(tmp->token->type > 23 && tmp->token->type < 33){tmp->PowerLevel = level_5;}
        else {tmp->PowerLevel = level_6;}
        
        tmp = tmp->next;
    }
}
void reoderList1(TokenList** tokenlist) {
    if (!tokenlist || !*tokenlist || !(*tokenlist)->next) {
        return;
    }

    int swapped;
    TokenList* current;
    TokenList* prev = NULL;
    while (1) {
        swapped = 0;
        current = *tokenlist;
        prev = NULL;
        while (current && current->next) {
            if (current->PowerLevel > current->next->PowerLevel) {
                // Swap the nodes
                TokenList* nextNode = current->next;
                current->next = nextNode->next;
                nextNode->next = current;

                if (prev) {
                    prev->next = nextNode;
                } else {
                    *tokenlist = nextNode;  // Update head if swapping first node
                }

                prev = nextNode;
                swapped = 1;
            } else {
                prev = current;
                current = current->next;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void recognizeToken(TokenList* tokenlist){
    reoderList(tokenlist);
    reoderList1(&tokenlist);
}