#ifndef PARSE_TREE_DEF_H
#define PARSE_TREE_DEF_H
#include "TokenDef.h"
#include<string.h>
typedef enum {
    EXPR_LITERAL,
    EXPR_UNARY,
    EXPR_BINARY,
     EXPR_GROUPING,
     EXPR_VARIABLE,
     EXPR_ASSIGN
} ExprType;

typedef enum{
    STMT_VARDECL,
    STMT_PRINT,
    STMT_EXPRESSION
}StmtType;


typedef struct Expr Expr;

typedef struct {
    Token op;
    Expr* right;
} Unary;

typedef struct {
    Expr* left;
    Token op;
    Expr* right;
} Binary;

typedef struct {
    Value val;
    Token t;
} Literal;

typedef struct {
    Expr* expression;
} Grouping;
typedef struct Variable
{
    Token name;   
}Variable;
typedef struct Assignment
{
    Variable name;Expr* right;
}Assignment;
typedef struct Expr {
    ExprType type;
    union {
        Unary u;
        Binary b;
        Literal l;
        Grouping g;
        Variable v;
        Assignment a;
    } as;
} Expr;






Expr* new_unary(Token op, Expr* expr);
Expr * new_binary(Token op, Expr* left, Expr* right);
Expr* new_literal(Token t,Value val);
Expr* new_variable( Token name);
Expr* new_assign(Variable name, Expr* right);
void printTree(Expr* ex);

#endif
