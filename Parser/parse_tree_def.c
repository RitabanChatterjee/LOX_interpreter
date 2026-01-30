#include "parse_tree_def.h"
#include<stdio.h>
#include<string.h>
static const char *token_repr[] = {
    /* Single-character tokens */
    "(", ")", "{", "}",
    ",", ".", "-", "+", ";", "/", "*",

    /* One or two character tokens */
    "!", "!=",
    "=", "==",
    ">", ">=",
    "<", "<=",

    /* Literals */
    "IDENTIFIER", "STRING", "NUMBER",

    /* Keywords */
    "and", "class", "else", "false", "fun", "for", "if", "nil", "or",
    "print", "return", "super", "this", "true", "var", "while",

    "EOF"
};
Expr* new_unary(Token op, Expr* expr)
{
    Expr* ret=(Expr*)(malloc(sizeof(Expr)));
    ret->type=EXPR_UNARY;
    ret->as.u.right=expr;
    ret->as.u.op=op;
    return ret;
}

Expr* new_binary(Token op, Expr* left,Expr* right)
{
     Expr* ret=(Expr*)(malloc(sizeof(Expr)));
      ret->type=EXPR_BINARY;
      ret->as.b.left=left;
      ret->as.b.op=op;
      ret->as.b.right=right;
    return ret;
}

Expr* new_literal(Token t,Value val)
{
    Expr* ret=(Expr*)(malloc(sizeof(Expr)));
    ret->type=EXPR_LITERAL;
    if(t.tType!=STRING)
    ret->as.l.val=val;
    else
    ret->as.l.val.str=strdup(val.str);
    ret->as.l.t=t;
    if(t.tType==TRUE)
    {
        ret->as.l.val.i=1;
    }
    if(t.tType==FALSE)
    {
        ret->as.l.val.i=0;
    }
    if(t.lType!=LIT_STRING)
    ret->as.l.t.token_val=ret->as.l.val;
    else
    {
        ret->as.l.t.token_val.str=strdup(ret->as.l.val.str);

    }
    return ret;
}
static void printBinary(Binary b)
{
    printf("(");
    printTree(b.left);
    printf(" %s ", token_repr[b.op.tType]);
    printTree(b.right);
    printf(")");

}
static void printUnary(Unary u)
{
    printf("  %s ",token_repr[u.op.tType]); printTree(u.right);
}
static void printPrimary( Literal l)
{   switch(l.t.tType)
    {
        case NUMBER:
        if(l.t.lType==LIT_INTEGER)
        {
            printf("%d",l.t.token_val.i);
        }
        else if(l.t.lType==LIT_FLOAT)
        {
            printf("%f", l.t.token_val.f);
        }
        
        else
        {
            //throw error for error handler, write error handler api
            
        }
        break;
        case STRING:
            if(l.t.lType==LIT_STRING)
            {
                printf("%s",l.t.token_val.str);
            }
            break;
        case NIL:
            printf("nil");
            break;
        case TRUE:
        printf("%s","true");break;
        case FALSE:
        printf("%s","false");break;
        case IDENTIFIER:
         if(l.t.identifier_name)
            printf("%s",l.t.identifier_name);break;
        
        default:
        printf("<unknown expr>");
        break;

    }
   
}
static void printVariable(Variable v)
{
    printf("%s",v.name.identifier_name);
}
static void printAssignment(Assignment v)
{
   printf("("); printVariable(v.name);printf("= ");
    printTree(v.right);printf(")");
}
void printTree(Expr* ex)
{   if(!ex) return;
    switch(ex->type)
    {
        case EXPR_BINARY:
            printBinary(ex->as.b);
            break;
        case EXPR_UNARY:
            printUnary(ex->as.u);
            break;
        case EXPR_LITERAL:
            printPrimary(ex->as.l);
            break;
        case EXPR_ASSIGN:
            printAssignment(ex->as.a);break;
        case EXPR_VARIABLE:
            printVariable(ex->as.v);
    }
}

Expr* new_variable( Token name)
{
    Expr* ret=malloc(sizeof(Expr));
    ret->as.v.name=name;
    ret->type=EXPR_VARIABLE;
    return ret;
    
}
Expr* new_assign(Variable name, Expr* right)
{
    Expr* ret=malloc(sizeof(Expr));
    ret->type=EXPR_ASSIGN;
    ret->as.a.name=name;
    ret->as.a.right=right;
    return ret;
}