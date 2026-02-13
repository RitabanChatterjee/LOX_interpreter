#include "Environment.h"

Environment* initEnvironmentStack(int hashtsize)
{
    Environment* env=malloc(sizeof(Environment));
    env->global=env;
    env->ht=init_hashtable(hashtsize);
    env->isGlobal=1;
    env->next=NULL;
    env->prev=NULL;
    return env;
}
int modifyVariable(char* varname, Environment* curr,Literal val)
{
    Environment* head=curr;Literal ret;
    while(head)
    {
        if( get(varname,&head->ht,&ret)) break;
        head=head->prev;
    }
    if(head)
    {
        put(varname,val, &head->ht);
        return 1;
    }
    else
    {
        return 0;
    }
}
int addToEnvironment(char* varname, Environment* env, Literal val)
{   
    put(varname,val,&env->ht);
    return 0;
}

int getValue(char* varname, Environment* env, Literal *out)
{
    Environment* head=env;
    while(head)
    {
       if( get(varname,&head->ht,out)) return 1;
        head=head->prev;
    }
    return 0;
}

Environment* getNestedEnvironment(Environment* toNestwith, int htsize)
{
    Environment* env=malloc(sizeof(Environment));
    env->global=toNestwith->global;
    env->ht=init_hashtable(htsize);
    env->isGlobal=0;
    env->next=NULL;
    env->prev=toNestwith;
    return env;
}

Environment* freeEnvironment(Environment* env)
{
    Environment* pre=env->prev;
    freeHashTable(&env->ht);
    free(env);env=NULL;
    return pre;
}