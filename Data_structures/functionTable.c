#include "functionTable.h"
#include <stdio.h>
// DEFINE_ARRAY(Variable,argArray);
// static Stmt copyStmt(Stmt val)
// {
//     Stmt ret;
//     ret.type=val.type;
//     ret.as.fn.functname.identifier_name=strdup(val.as.fn.functname.identifier_name);
//     ret.as.fn.functname.line=val.as.fn.functname.line;
//     ret.as.fn.functname.tType=IDENTIFIER;
//     ret.as.fn.functname.lType=LIT_NONE;
//     ret.as.fn.functname.token_val.str=strdup(val.as.fn.functname.identifier_name);
//     ret.as.fn.functionBody=malloc(sizeof(Stmt));
//     ret.as.fn.functionBody->as.bl.count = val.as.fn.functionBody->as.bl.count;

//     ret.as.fn.functionBody->as.bl.statements;
//     ret.as.fn.functionBody->as.bl.statements=(Stmt*)malloc(val.as.fn.functionBody->as.bl.count*sizeof(Stmt));
//     for(int i=0;i<val.as.fn.functionBody->as.bl.count;i++)
//     {
//         ret.as.fn.functionBody->as.bl.statements[i].type=val.as.fn.functionBody->as.bl.statements[i].type;

//         ret.as.fn.functionBody->as.bl.statements[i]=val.as.fn.functionBody->as.bl.statements[i];
//     }
//     ret.as.fn.args.arguments=argArray_make();
//     for(int i=0;i<val.as.fn.args.arguments.size;i++)
//     {
//         argArray_push(&ret.as.fn.args.arguments,val.as.fn.args.arguments.data[i]);
//     }
//     return ret;
// }
functionTable init_functionTable(int size)
{
    functionTable ret;
    ret.capacity=size;
    ret.buckets=(functionEntry**)malloc(size*sizeof(functionEntry*));
        for(int i = 0; i < size; i++)
        ret.buckets[i] = NULL;  

    ret.numkeys=0;
    return ret;
}

int hashFunction(const char *str, int capacity) 
{
    int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; 
    return hash % capacity;
}
static void addEntry(int ind, functionTable* ht,char* key,Stmt val) // returns last node if key not present
{
    functionEntry* e = malloc(sizeof(*e));
    e->name = strdup(key);          // copy the key to heap
    e->funct = val;// val is allocated on heap, never free anything.
    e->next = ht->buckets[ind];    // current head becomes next
    ht->buckets[ind] = e;          // new node is head
    ht->numkeys++;
}
int isFunctionDefined(char* key, functionTable* ht)
{
    int ind=hashFunction(key,ht->capacity);
    functionEntry* head=ht->buckets[ind];
    while(head)
    {
        if(!strcmp(key, head->name))
        {
            return 1;
        }
        head = head->next;  
    }
    return 0;
}
int putFunctionName(char* key,int num, Stmt f, functionTable* ht)
{
    char buffer[strlen(key)+16];
    snprintf(buffer,sizeof(buffer),"%s%d",key, num);
    if(isFunctionDefined(buffer,ht)) return 0;
    int ind=hashFunction(buffer,ht->capacity);
    addEntry(ind,ht,buffer,f);
    return 1;
}

Stmt getFunction(char* key, int num, functionTable* ht)
{
    char buffer[strlen(key)+16];
    snprintf(buffer,sizeof(buffer),"%s%d",key, num);
    int ind=hashFunction(buffer,ht->capacity);

    functionEntry* head=ht->buckets[ind];
    while(head)
    {
        if(!strcmp(head->name,buffer))
        {
            return head->funct;
        }
        head=head->next;
    }
    Stmt ret;
    ret.type=STMT_ERROR;
    ret.as.error.msg="Function not defined";
    return ret;
}