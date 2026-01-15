#include "lib.h"

/* for convenience
typedef struct Token
{
    TokenType tType;
    LiteralType lType;
    Value token_val;
    int line;
    char * identifier_name;

}Token;
*/
static char* concat(char* a,char* b)
{
    char* str;
    int l=strlen(a)+strlen(b)+1;
    str=(char*)malloc(l);
    str[l]='\0';
    snprintf(str,l,"%s%s",a,b);
    return str;
}
Literal addLiterals(Literal a,Literal b)
{
    
    if(a.t.lType ==b.t.lType)
    {
        Literal ret;ret.t=a.t;
        if(a.t.lType==LIT_STRING)
        {   Value v;int l=strlen(a.val.str)+strlen(b.val.str)+1;
            v.str=(char*)malloc(l);
            v.str[l]='\0';
            snprintf(v.str,l,"%s%s",a.val.str,b.val.str);
            ret.val.str=v.str;
            return ret;
        }
        else if(a.t.lType==LIT_FLOAT )
        {
            Value v;
            v.f=a.val.f+b.val.f;
            ret.val.f=v.f;
            return ret;
        }
        else if(a.t.lType==LIT_INTEGER)
        {
            Value v;
            v.i=a.val.i+b.val.i;
            ret.val.i=v.i;
            return ret;
        }
    }
    else if(a.t.tType==NUMBER && b.t.tType==NUMBER)
    {
        Literal ret;ret.t=a.t;
        ret.t.lType=LIT_FLOAT;

        Value fl=(a.t.lType==LIT_FLOAT)?a.val:b.val;
        Value in=(a.t.lType==LIT_INTEGER)?a.val:b.val;
        ret.val.f=fl.f+in.i;
        return ret;
    }
    else if(a.t.tType == STRING || b.t.tType==STRING)
    {
        Literal ret;
        ret.t=a.t;
        ret.t.lType=LIT_STRING;
        ret.t.tType=STRING;
        Value s;
        char* a_str=toString(a);
        char* b_str=toString(b);
        char* merged=concat(a_str,b_str);
        free(a_str);
        free(b_str);
        s.str=merged;ret.val=s;
        return ret;
    }   
    else 
    {
        /*Make error handler
        */
       a.t.tType=-1; 
       return a; //For now,if something wrong, then tType will show -1
    }
}
char* toString(Literal l)
{
    
    switch(l.t.lType)
    {
        case LIT_FLOAT:
        {
            char buff[64];
            snprintf(buff,64,"%g",l.val.f);
            return buff;
        }
        break;
        
        case LIT_INTEGER:
        {
            char buff[64];
            snprintf(buff,64,l.val.i);
            return buff;
        }
        break;

        case LIT_STRING:
        {
            char *ret=strdup(l.val.str);
            return ret;
        }
    }
}