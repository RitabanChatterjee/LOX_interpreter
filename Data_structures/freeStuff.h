#ifndef FREESTUFF_H
#define FREESTUFF_H
#include "TokenDef.h"
#include "parse_tree_def.h"
//void freeVal(Value* val);
void freeToken(Token* t);
void freeLiteral(Literal* l);


#endif