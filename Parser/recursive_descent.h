#ifndef RECURSIVE_DESCENT_H
#define RECURSIVE_DESCENT_H
#include "parse_tree_def.h"
#include "utils.h"


typedef struct Parser
{
    TokenList tokens;
    int pointer;
}Parser;
//GRAMMAR FOR PARSING EXPRESSIONS
//-------------------------------------------------------------------------------------

Expr* parseExpr(Parser* p);
Expr* parseEquality(Parser* p);
Expr* parseComparison(Parser* p);
Expr* parseTerm(Parser* p);
Expr* parseFactor(Parser* p);
Expr* parseUnary(Parser* p);
Expr* parseLiteral(Parser* p);//parses Literals
// ---------------------------------------------------------------------------------------------------


#endif /*recursive_descent.h*/