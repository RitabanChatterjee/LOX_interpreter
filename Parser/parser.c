
#include "parser.h"
#include "../Lexer/utils.h"
TokenList tokens;
Expr* parse(char* str, int len)
{
   tokens=scanTokens(str,len);
    // for (int i = 0; i < tokens.size; i++) {
    //     Token t = tokens.tokens[i];
    //     printToken(t);
    // }
    Parser p;
    p.tokens=tokens;
    p.pointer=0;
    Expr* exp=parseExpr(&p);
    return exp;
}
Stmt parseStmt(char* str,int len)
{
    tokens= scanTokens(str,len);
    Parser p;
    p.tokens=tokens;
    p.pointer=0;
    return declaration(&p);
}