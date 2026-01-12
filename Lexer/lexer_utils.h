#ifndef LEXER_UTILS_H
#define LEXER_UTILS_H

#include "TokenDef.h"
#include "utils.h"
#include<stdio.h>
extern int length;
extern int line;

typedef struct {
    TokenType t;
    LiteralType l;
} ScanResult;
void addTok(TokenType t1,LiteralType lt1,Value val,TokenList* list);
ScanResult scanToken(char* str, int* current);
void addIdentifier(TokenType t1,LiteralType lt1,Value val,TokenList* list,char* id);
#endif