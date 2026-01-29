#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "hashtable.h"
typedef struct Environment Environment;
 struct Environment
{   
    Environment* prev; 
    Environment* next;
    Environment* global; //each Environment points directly also to the global env
    int isGlobal;
    hashtable ht;
};

Environment* initEnvironmentStack(int hashTsize); //create global environment
Environment* getNestedEnvironment(Environment* toNestWith,int hashTsize);
//create new environment tied to any parent environment. You can tie to global, or to 
//the environment corresponding a class, etc. 

int addToEnvironment(char* varname, Environment* current,Literal val);
int getValue(char* varname, Environment* current,Literal* out);
Environment* freeEnvironment(Environment* env);// returns previous environment
#endif