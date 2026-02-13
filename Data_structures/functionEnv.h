#ifndef FUNCTIONENV_H
#define FUNCTIONENV_H
#include "functionTable.h"
typedef struct functionEnv functionEnv;
struct functionEnv
{
    functionEnv* prev;
    functionEnv* next;
    functionTable fht;
    int isGlobal;
    functionEnv* global;
};
functionEnv* initFunctionStack(int size);
functionEnv* stackFunctions(functionEnv* base, int size);
int addFunctionToEnv(functionEnv* env,char* varname,int arity, Stmt funct);
int getFunctionFromEnv(functionEnv* env, char* varname, int arity, Stmt* funct );
#endif