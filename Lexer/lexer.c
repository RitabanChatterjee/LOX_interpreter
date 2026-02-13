#include "lexer.h"


#define INT_MAX 2147483647
#define INT_MIN -2147483648

const char* tokenStrings[] = {
    "and",
    "class",
    "else",
    "false",
    "fun",
    "for",
    "if",
    "nil",
    "or",
    "print",
    "return",
    "super",
    "this",
    "true",
    "var",
    "while"
};


TokenType checkKeyWord(char* str)
{
    for(int i=0;i<16;i++)
    {
        if(strcmp(str,tokenStrings[i])==0)
        {
            return AND+i;
        }
    }
    return IDENTIFIER;
}
static int parseInt(char* str,int* out)
{
    char* end;
    errno=0;
    long i=strtol(str,&end,10);
    if(str==end)
    {
        perror("No characters parsed");
        return 0;
    }
    if(errno==ERANGE)
    {
        perror("Out of Range");
        return 0;
    }
    if(i>INT_MAX || i<INT_MIN)
    {
        perror("Out of range");
        return 0;
    }
    *out=(int)i;
    return 1;
}
static int parseFloat(char *str,float* out)
{   char* end;
    errno=0;
    float f=strtof(str,&end);
    if(str==end)
    {
        perror("No characters parsed");
        return 0;
    }
    if(errno==ERANGE)
    {
        perror("Out of Range");
        return 0;
    }
    *out=f;
    return 1;
}
TokenList scanTokens(char* str, int len)
{
    int start=0;// start of current lexeme
    int current=0;
    // add logic for this later
    length=len;
    TokenList ans=makeList();
    while(current<len)
    {
        start=current;
        ScanResult res=scanToken(str,&current);
        Value values={0};
        if(res.t==IDENTIFIER)
        {
            char* temp=substring(str,start,current-start);
            TokenType t1=checkKeyWord(temp);
            addIdentifier(t1,LIT_NONE,values,&ans,temp);
            free(temp);
        }
        else if(res.l==LIT_STRING)
        {
            
            values.str=substring(str,start+1,current-start-2);
            addTok(res.t,res.l,values,&ans);
            free(values.str);
        }
        else if(res.l==LIT_NONE)
        {
            values.str="";
            addTok(res.t,res.l,values,&ans);
        }
        else if(res.l==LIT_FLOAT)
        {
            
            char* temp=substring(str,start,current-start);
            parseFloat(temp,&values.f);
            free(temp);
            addTok(res.t,res.l,values,&ans);
        }
        else if(res.l==LIT_INTEGER)
        {
            char* temp=substring(str,start,current-start);
           
            parseInt(temp,&values.i);
           free(temp);
            addTok(res.t,res.l,values,&ans);
        }
        
    }
    // Token tlast;
    // tlast.identifier_name="";
    // tlast.line=line;
    // tlast.lType=LIT_NONE;
    // tlast.tType=EOF;
    // tlast.token_val.i=0;
    // addToken(tlast,&ans);
    return ans;
}




