#ifndef LEXER_H
#define LEXER_H
#include "TokenDef.h"
#include "utils.h"
#include <errno.h>
#include<stdlib.h>
#include<stdio.h>
#include "lexer_utils.h"
TokenList scanTokens(char* str,int len);
#endif
