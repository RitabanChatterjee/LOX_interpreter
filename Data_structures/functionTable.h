#ifndef FUNCTIONTABLE_H
#define FUNCTIONTABLE_H
#include "parse_tree_def.h"

typedef struct functionEntry functionEntry;
struct functionEntry
{
    char* name;
    //int num;// number of entries
    Stmt funct;
    functionEntry* next;
};
typedef struct functionTable
{
    functionEntry** buckets;
     int numkeys;
    int capacity;
}functionTable;

functionTable init_functionTable(int size);
int isFunctionDefined(char* key, functionTable* ht);
int putFunctionName(char* key,int num, Stmt f, functionTable* ht);
Stmt getFunction(char* key, int num, functionTable* ht);

#endif