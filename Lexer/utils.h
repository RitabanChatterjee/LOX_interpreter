#ifndef UTILS_H
#define UTILS_H
#include "TokenDef.h"


typedef struct TokenList
{
    int size;
    int capacity;
    Token* tokens;
}TokenList;
void freeList(TokenList* list);
void addToken(Token t,TokenList* list);
TokenList makeList();
char* substring(const char* source, size_t start,size_t length);
void printToken(Token t);
#endif

