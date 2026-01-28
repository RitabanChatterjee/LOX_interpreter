#include "freeStuff.h"
void freeToken(Token* t)
{
    if(t->tType==STRING)
    {
        free(t->token_val.str);
        t->token_val.str=NULL;
    }
    else if(t->tType==IDENTIFIER)
    {
        free(t->identifier_name);
        t->identifier_name=NULL;
    }
}
void freeLiteral(Literal* val)
{
    if(val->t.tType==STRING)
    {
        free(val->val.str);
        val->val.str=NULL;
    }
    freeToken(&val->t);
    
}
