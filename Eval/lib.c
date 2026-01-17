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
    str=(char*)malloc(l*sizeof(char));
    
    snprintf(str,l,"%s%s",a,b);
    return str;
}
Literal addLiterals(Literal a,Literal b)
{
    
    if(a.t.lType ==b.t.lType)
    {
        Literal ret;ret.t=a.t;
        if(a.t.lType==LIT_STRING)
        {   
            ret.val.str=concat(a.val.str,b.val.str);
            ret.t.token_val.str=ret.val.str;
            return ret;
        }
        else if(a.t.lType==LIT_FLOAT )
        {
            Value v;
            v.f=a.val.f+b.val.f;
            ret.val.f=v.f;
            ret.t.token_val.f=v.f;
            return ret;
        }
        else if(a.t.lType==LIT_INTEGER)
        {
            Value v;
            v.i=a.val.i+b.val.i;
            ret.val.i=v.i;
            ret.t.token_val.i=v.i;
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
        ret.t.token_val.f=ret.t.token_val.f;
        return ret;
    }
    else if(a.t.tType == STRING || b.t.tType==STRING)
    {   
        if((a.t.tType!=NUMBER && a.t.tType!=STRING) || (b.t.tType!=NUMBER && b.t.tType!=STRING))
        return unexpectedLiteral("String+NUMBER, or number +number or string+string","heh",a.t.line);//For now,if something wrong, then tType will show -1
        Literal ret;
        ret.t.token_val=a.t.token_val;
        ret.t.line=a.t.line;
        
        ret.t.lType=LIT_STRING;
        ret.t.tType=STRING;
        Value s;
        char* a_str=toString(a);
        char* b_str=toString(b);
        char* merged=concat(a_str,b_str);
        
        free(a_str);
        free(b_str);
        ret.val.str=merged;//printf("%s",ret.val.str);
        ret.t.token_val.str=merged;
        return ret;
    }   
    else 
    {
        /*Make error handler
        */
       return unexpectedLiteral("String+NUMBER, or number +number or string+string","heh",a.t.line);//For now,if something wrong, then tType will show -1
    }
}
char* toString(Literal l)
{
    
    switch(l.t.lType)
    {
        case LIT_FLOAT:
        {
             char* buff=(char*)malloc(64*sizeof(char));
            snprintf(buff,64,"%g",l.val.f);
            return buff;
        }
        break;
        
        case LIT_INTEGER:
        {
            char* buff=(char*)malloc(64*sizeof(char));
            snprintf(buff,64,"%d",l.val.i);
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

// Literals are of same tType=NUMBER to be sure
Literal compareNumbers(Literal a,Literal b,int eq)
{
    if(a.t.tType!=b.t.tType) return unexpectedLiteral("same type, string or num","Nope\n",a.t.line);

    //printf("In function \n Literaltype l %d r %d",a.t.lType,b.t.lType);
    if(a.t.lType==LIT_FLOAT)
    {
        if(b.t.lType==LIT_FLOAT)
        {
            
            Literal ret; ret.t.line=a.t.line;
            ret.t.lType=LIT_NONE;
            ret.t.tType=((a.t.token_val.f>b.t.token_val.f) || (a.t.token_val.f==b.t.token_val.f && eq))?TRUE:FALSE;
             ret.val.i=ret.t.tType==TRUE?1:0;ret.t.token_val=ret.val;
             // printf("%d/n",ret.t.tType);
            return ret;
        }
        else if(b.t.lType==LIT_INTEGER)
        {
            Literal ret; ret.t.line=a.t.line;
            ret.t.lType=LIT_NONE;
            ret.t.tType=((a.t.token_val.f>b.t.token_val.i) || (a.t.token_val.f==b.t.token_val.i && eq))?TRUE:FALSE;
            ret.val.i=ret.t.tType==TRUE?1:0;ret.t.token_val=ret.val;
            // printf("%d/n",ret.t.tType);
            return ret;
        }
        else
        {
            return unexpectedLiteral("strings or nums (of same type)","invalid comparison",a.t.line);
        }
    }
    else if(a.t.lType==LIT_INTEGER)
    {
        if(b.t.lType==LIT_FLOAT)
            {
                Literal ret; ret.t.line=a.t.line;
                ret.t.lType=LIT_NONE;
                ret.t.tType=((a.t.token_val.i>b.t.token_val.f) || (a.t.token_val.i==b.t.token_val.f && eq))?TRUE:FALSE;
                ret.val.i=ret.t.tType==TRUE?1:0;ret.t.token_val=ret.val;
               //  printf("%d/n",ret.t.tType);
                return ret;
            }
            else if(b.t.lType==LIT_INTEGER)
            {
                Literal ret; ret.t.line=a.t.line;
                ret.t.lType=LIT_NONE;
                ret.t.tType=((a.t.token_val.i>b.t.token_val.i) || (a.t.token_val.i==b.t.token_val.i && eq))?TRUE:FALSE;
            //    printf("%d/n",ret.t.tType);
                ret.val.i=ret.t.tType==TRUE?1:0;
                ret.t.token_val=ret.val;
                return ret;
            }
            else
            {
                return unexpectedLiteral("strings or nums (of same type)","invalid comparison",a.t.line);
            }
            
        
    }
    return unexpectedLiteral("strings or nums (of same type)","invalid comparison",a.t.line);
}

Literal compareStrings(Literal a,Literal b,int eq)
{
     if(a.t.tType!=b.t.tType) return unexpectedLiteral("same type, string or num","Nope\n",a.t.line);

    int l1=strlen(a.val.str);
    int l2=strlen(b.val.str);
    char* s1=a.val.str;
    char* s2=b.val.str;
    int lesser=l1>=l2?l2:l1;
    int isTrue=0;
    int ran=0;
    for(int i=0;i<lesser;i++)
    {
        if(s1[i]!=s2[i])
        {
            isTrue=(s1[i]>s2[i]) || (s1[i]==s2[i]&&eq);
            ran=1;
            break;
        }
    }
    if(!ran)
    {
        if(l1>l2)
        {
            isTrue=1;
        }
        if(l1==l2)
        {
            isTrue=eq;
        }
    }
    Literal ret;
    ret.t.line=a.t.line;
    ret.t.lType=LIT_NONE;
    ret.t.tType=isTrue?TRUE:FALSE;
    ret.val.i=ret.t.tType==TRUE?1:0;
    ret.t.token_val=ret.val;
    return ret;
}