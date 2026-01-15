#include "error_handler.h"

static Literal getErrorLiteral(int line) //an error literal's token's lType is set to -1
{
    Literal ret;
    ret.val.str="Error in eval stage";
    ret.t.line=line;
    ret.t.lType=-1;
    ret.t.tType=-1;
    ret.t.identifier_name="";
    ret.t.token_val.str="";
    return ret;
}
Literal unexpectedLiteral(char* exp, char* found,int line)
{
    printf("On line %d, Expected: %s, Found: %s",line,exp,found);
    
    return getErrorLiteral(line);
}

int isErrorLiteral(Literal l)
{
    return l.t.lType==-1;
}