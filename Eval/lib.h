#ifndef LIB_H
#define LIB_H
#include "parser.h"
#include "TokenDef.h"
#include<string.h>
#include<stdlib.h>
#include "error_handler.h"
char* toString(Literal v);
Literal addLiterals(Literal a,Literal b);
Literal subtractNums(Literal a,Literal b);


//these two return Literals with Token.tType=TRUE or FALSE,and val=1 or 0. eq defines 
//behaviour on equality of the literals.
Literal compareNumbers(Literal a,Literal b,int eq);
Literal compareStrings(Literal a,Literal b,int eq);
Literal isEqualNumber(Literal a,Literal b);
Literal isEqualString(Literal a,Literal b);
Literal multiplyNumbers(Literal a,Literal b);
Literal divideNumbers(Literal a,Literal b);
Literal negateNum(Literal a);
Literal isTruthey(Literal a);

Literal boolInvert(Literal a);
#endif