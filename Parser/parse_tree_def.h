#ifndef PARSE_TREE_DEF_H
#define PARSE_TREE_DEF_H
#include "dynamic_arrays.h"
#include "TokenDef.h"
#include<string.h>


typedef enum {
    EXPR_LITERAL,
    EXPR_UNARY,
    EXPR_BINARY,
     EXPR_GROUPING,
     EXPR_VARIABLE,
     EXPR_ASSIGN,
     EXPR_CALL
} ExprType;

typedef enum{
    STMT_VARDECL,
    STMT_PRINT,
    STMT_EXPRESSION,
    STMT_ERROR,
    STMT_BLOCK,
    STMT_FUNCTION,
    STMT_RETURN,
    STMT_IF,
    STMT_WHILE,
    STMT_FOR,
    STMT_CLASS
}StmtType;
typedef enum{INDEXED_VAR,UNINDEXED_VAR}IndexType;
typedef enum{ELSE_ONLY, ELSE_IF, NO_ELSE} ElseType;

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
    IndexType type;
    Token name;
    Expr* indexp;   
}Variable;
typedef struct Assignment
{
    Variable name;Expr* right;
}Assignment;
DEFINE_ARRAY(Expr*, argExprArray)
typedef struct functionCall
{
    Token name;
    argExprArray list;
}callee;

typedef struct Expr {
    ExprType type;
    union {
        Unary u;
        Binary b;
        Literal l;
        Grouping g;
        Variable v;
        Assignment a;
        callee fc;
    } as;
} Expr;



typedef struct varDecl
{
   Variable v;
   Expr* init;
}varDecl;
typedef struct printStmt
{
    Expr* expr;
}printStmt;
typedef struct exprStmt
{
    Expr* expr;
}exprStmt;
typedef struct errorStmt
{
    char* msg;
}errorStmt;
typedef struct returnStmt
{
    Expr* ex;
}returnStmt;

typedef struct Stmt Stmt;
DEFINE_ARRAY(Variable,argArray);
typedef struct classStmt classStmt;
 struct Stmt
{
   StmtType type;
   union 
   {
     exprStmt es;
     varDecl vd;
    printStmt ps;
    errorStmt error;
    returnStmt retpack;
    struct block
    {
        Stmt* statements;
        int count;
    }bl;
    struct function
    {
        Token functname;

         struct arglist
        {
            argArray arguments;
        }args;

        struct block functionBody;
    }fn;
    struct ifStmt
    {
         ElseType type;
        Expr* cond;
        struct block condblock;
        struct elseStmt
        {   
            union
            {
                struct ifStmt* elif;
                struct block condblock;
            }as;
            
        }elb;
    }ifStmt;
    struct whileStmt
    {
        Expr* exp;
        struct block condblock;
    }whileSt;
    struct forStmt
    {
        Stmt* init;
        Stmt* cond;
        Stmt* inc;
        struct block blst;
    }forSt;

    struct classStmt
    {
        struct functions
        {
            struct function* functions;
            int size;
            int accessLevel;
        }inst_functions;

        struct vars
        {
            varDecl* declarations;
            int size;
            int accesslevel;
        }inst_vars;

        struct classStmt* base;

        struct function* constructor;
        
        
    }class_st;
   }as;
   
};






Expr* new_unary(Token op, Expr* expr);
Expr * new_binary(Token op, Expr* left, Expr* right);
Expr* new_literal(Token t,Value val);
Expr* new_variable( Token name,Expr* ex);
Expr* new_assign(Variable name, Expr* right);
Expr* new_callee(Token fname,argExprArray passed);
void printTree(Expr* ex);
void printStatementTree(Stmt st);
#endif

