#ifndef PARSE_TREE_DEF_H
#define PARSE_TREE_DEF_H
#include "../Lexer/TokenDef.h"
#include<string.h>
typedef enum {
    EXPR_LITERAL,
    EXPR_UNARY,
    EXPR_BINARY,
     EXPR_GROUPING
} ExprType;



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

typedef struct Expr {
    ExprType type;
    union {
        Unary u;
        Binary b;
        Literal l;
        Grouping g;
    } as;
} Expr;

Expr* new_unary(Token op, Expr* expr);
Expr * new_binary(Token op, Expr* left, Expr* right);
Expr* new_literal(Token t,Value val);
void printTree(Expr* ex);
#endif