#include "recursive_descent.h"
#include "parse_tree_def.h"
#include<string.h>
#define ERR_TOK (Token){-1,-1,-1,-1,""}
static Token get(Parser *p)
{
    if(p->pointer>=p->tokens.size) return ERR_TOK;
    return p->tokens.tokens[p->pointer];
}
static Token advance(Parser* p)
{
        p->pointer++;
        return get(p);
    
}
static int match(Token t, TokenType m)
{
    return t.tType==m;

}
Expr* parseExpr(Parser *p)
{
    return parseEquality(p);
}
Expr* parseEquality(Parser* p)
{
    Expr* expr = parseComparison(p);

    while (1)
    {
        Token t = get(p);
        if (!(match(t, EQUAL_EQUAL) || match(t, BANG_EQUAL)))
            break;

        advance(p);               // consume operator
        Expr* right = parseComparison(p);
        expr = new_binary(t, expr, right);
    }

    return expr;
}


Expr* parseComparison(Parser *p)
{
    Expr* term=parseTerm(p);
    
    while(1)
    {
        Token t=get(p);
        
        if(!(match(t,GREATER) || match(t,GREATER_EQUAL) || match(t,LESS) || match(t,LESS_EQUAL)))
        {
            break;
        }
        advance(p);
        Expr* right=parseTerm(p);
        term=new_binary(t,term,right);
    }
    return term;
}
Expr* parseTerm(Parser* p)
{
    Expr* exp=parseFactor(p);
    while(1)
    {
        Token t=get(p);
        if(!(match(t,PLUS) || match(t,MINUS)))
        {
            break;
        }
        advance(p);
        Expr* right=parseFactor(p);
        exp=new_binary(t,exp,right);
    }
    return exp;
}
Expr* parseFactor(Parser* p)
{
    Expr* ex=parseUnary(p);
    while(1)
    {
        Token t=get(p);
        
        if(!(match(t,SLASH) || match(t,STAR)))
        {
            break;
        }
        advance(p);
        Expr* right=parseUnary(p);
        ex=new_binary(t,ex,right);
    }
    return ex;
}

Expr* parseUnary(Parser* p)
{
    Token t=get(p);
    if((match(t,BANG) || match(t,MINUS)) )
    {
        advance(p);
        Expr* right=parseUnary(p);
        
        return new_unary(t,right);
    }
    return parseLiteral(p);
    
}

Expr* parseLiteral(Parser* p)
{
    Token t=get(p);advance(p);
    if(t.tType==NUMBER || t.tType==STRING) return new_literal(t,t.token_val);
    else if(t.tType==IDENTIFIER)
    {
        
        Value val;
        if(t.identifier_name)
            {int leng=strlen(t.identifier_name);
                t.identifier_name[leng]='\0';
                val.str = strdup(t.identifier_name);
            } // <-- copy string to heap
        else
            val.str = NULL;
        return new_literal(t, val);
    }
    else if(t.tType==TRUE)
    {   
        t.token_val.i=1;
        return new_literal(t,t.token_val);
    }
    else if(t.tType==FALSE)
    {
        t.token_val.i=0;
        return new_literal(t,t.token_val);
    }
  
    else if(t.tType==NIL)
    {
        return new_literal(t,t.token_val);
    }
    else if(t.tType==LEFT_PAREN)
    {
        Expr* exp=parseExpr(p);
        advance(p);
        return exp;
    }
    return NULL;
}