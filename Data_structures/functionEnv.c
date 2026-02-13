#include "functionEnv.h"

functionEnv* initFunctionStack(int size)
{
    functionEnv* f=(functionEnv*)malloc(sizeof(functionEnv));
    f->prev=NULL;
    f->global=f;
    f->isGlobal=1;
    f->fht=init_functionTable(size);
    f->next=NULL;
    return f;
}

functionEnv* stackFunctions(functionEnv* base,int size)
{
    functionEnv* f=(functionEnv*)malloc(sizeof(functionEnv));
    f->prev=base;
    f->global=base->global;
    f->isGlobal=1;
    f->fht=init_functionTable(size);
    f->next=NULL;
    return f;
}

int getFunctionFromEnv(functionEnv* env, char* varname,int arity, Stmt* funct)
{
    Stmt ret=getFunction(varname,arity,&env->fht);
    if(ret.type==STMT_ERROR) return 0;
    *funct=ret;
    return 1;
}

int addFunctionToEnv(functionEnv* env, char* varname, int arity, Stmt funct)
{
    return putFunctionName(varname,arity,funct,&env->fht);
}