#include <stdio.h>
#include <string.h>
#include "Environment.h"
#include "functionEnv.h"
#include "parser.h"
typedef struct {
    char* varname;
    char* val;
} testcase;

void bindVar(Environment* env, char* name, char* val)
{
    Literal v;
    v.t.tType = STRING;
    v.val.str = strdup(val);
    v.t.token_val.str = strdup(val);
    name=strdup(name);
    v.t.line = -1;
    v.t.lType = LIT_STRING;
    addToEnvironment(name, env, v);
}

void check(Environment* env, char* name, char* expect)
{
    Literal out;
    if (!expect) {
        if (getValue(name, env, &out))
            printf("❌ %-8s -> %s (expected not found)\n", name, out.val.str);
        else
            printf("✅ %-8s not found\n", name);
    } else {
        if (!getValue(name, env, &out))
            printf("❌ %-8s not found (expected %s)\n", name, expect);
        else if (strcmp(out.val.str, expect) != 0)
            printf("❌ %-8s -> %s (expected %s)\n", name, out.val.str, expect);
        else
            printf("✅ %-8s -> %s\n", name, out.val.str);
    }
}

int main()
{
   functionEnv* env=initFunctionStack(512);Stmt ret;
   Stmt function=parseStmt("fun main(){return 10+1;}",25);
    addFunctionToEnv(env,"main",0,function);
    if(getFunctionFromEnv(env,"main",0,&ret))
    {
        printf("Found");
    }
    else
    {
        printf("Not found");
    }
    functionTable ft=init_functionTable(10);
    putFunctionName("name",0,function,&ft);
    if(isFunctionDefined("name0",&ft))
    {
        if(getFunction("name",0,&ft).type!=STMT_ERROR)
        printf("Hashtable is fine");
        else
    {
        printf("HT is corrupfewt");
    }
    }
    else
    {
        printf("HT is corrupt");
    }
}
