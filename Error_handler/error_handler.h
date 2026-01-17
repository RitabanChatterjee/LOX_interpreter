#include "TokenDef.h"
#include "parse_tree_def.h"
#include<stdio.h>

Literal unexpectedLiteral(char* expected,char* found,int line);
int isErrorLiteral(Literal l);