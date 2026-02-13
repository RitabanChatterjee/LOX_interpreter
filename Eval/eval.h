#ifndef EVAL_H
#define EVAL_H

#include "lib.h"
#include "error_handler.h"
#include"Environment.h"
#include "functionTable.h"
#include "functionEnv.h"
enum retType{
    NONE,
    VALUE
};
typedef enum retType retType;
typedef struct Package
{
    retType rt;
    Literal val;
}Package;
typedef struct envpack
{
    Environment* curr;
    functionEnv* fcurr;
}envpack;
Literal eval(Expr* expr, envpack* curr);
Package evalStmt(Stmt st,envpack* curr);
static char* printPrimary(Literal ret);
#endif