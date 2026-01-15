#include "eval.h"

static const char *token_repr[] = {
    /* Single-character tokens */
    "(", ")", "{", "}",
    ",", ".", "-", "+", ";", "/", "*",

    /* One or two character tokens */
    "!", "!=",
    "=", "==",
    ">", ">=",
    "<", "<=",

    /* Literals */
    "IDENTIFIER", "STRING", "NUMBER",

    /* Keywords */
    "and", "class", "else", "false", "fun", "for", "if", "nil", "or",
    "print", "return", "super", "this", "true", "var", "while",

    "EOF"
};
Literal eval(Expr* expr)
{
    ExprType e=expr->type;
    switch(e)
    {
        case EXPR_BINARY:
        {
            Literal left=eval(expr->as.b.left);
            Literal right=eval(expr->as.b.right);
            Token op=expr->as.b.op;
            
            switch(op.tType)
            {
                case PLUS:
                {
                    return addLiterals(left,right);
                }
                break;
                case MINUS:
                {
                    if(left.t.tType==right.t.tType && left.t.tType==NUMBER)
                    {
                        subtractNums(left,right);
                    }
                    else
                    {
                        /* Throw some error*/
                        if(left.t.tType!=NUMBER)
                            return unexpectedLiteral("Number",token_repr[left.t.tType],left.t.line);
                        else
                        {
                            return unexpectedLiteral("Number",token_repr[right.t.tType],right.t.line);
                        }
                    }
                }
                break;
                case GREATER:
                {
                    if(left.t.tType!=right.t.tType)
                    {
                        /* Throw some error*/
                        char* expected="Same types for comparison operators";
                        char found[64];
                        snprintf(found,"%s > %s",token_repr[left.t.tType],token_repr[right.t.tType]);
                        return unexpectedLiteral(expected,found,left.t.line);
                    }
                    if( left.t.tType==NUMBER)
                    {
                        return compareNumbers(left,right,0);
                    }
                    else if(left.t.tType==STRING)
                    {
                        return compareStrings(left,right,0);
                    }
                    else
                    {
                        /* throw some error*/
                        return unexpectedLiteral("Either both Numbers or Strings",token_repr[left.t.tType],left.t.line);
                    }
                }
                break;
                case GREATER_EQUAL:
                {
                    if(left.t.tType!=right.t.tType)
                    {
                        /* Throw some error*/
                         char* expected="Same types for comparison operators";
                        char found[64];
                        snprintf(found,"%s >= %s",token_repr[left.t.tType],token_repr[right.t.tType]);
                        return unexpectedLiteral(expected,found,left.t.line);
                    }
                    if( left.t.tType==NUMBER)
                    {
                        return compareNumbers(left,right,1);
                    }
                    else if(left.t.tType==STRING)
                    {
                        return compareStrings(left,right,1);
                    }
                    else
                    {
                        /* throw some error*/
                        return unexpectedLiteral("Either both Numbers or Strings",token_repr[left.t.tType],left.t.line);
                        
                    }
                }
                break; 
                case LESS:
                {
                    if(left.t.tType!=right.t.tType)
                    {
                        /* Throw some error*/
                        char* expected="Same types for comparison operators";
                        char found[64];
                        snprintf(found,"%s < %s",token_repr[left.t.tType],token_repr[right.t.tType]);
                        return unexpectedLiteral(expected,found,left.t.line);
                    }
                    if( left.t.tType==NUMBER)
                    {
                        return boolInvert(compareNumbers(left,right,0));
                    }
                    else if(left.t.tType==STRING)
                    {
                        return boolInvert(compareStrings(left,right,0));
                    }
                    else
                    {
                        /* throw some error*/
                        return unexpectedLiteral("Either both Numbers or Strings",token_repr[left.t.tType],left.t.line);
                    }
                }
                break;
                case LESS_EQUAL:
                {
                    if(left.t.tType!=right.t.tType)
                    {
                        /* Throw some error*/
                         char* expected="Same types for comparison operators";
                        char found[64];
                        snprintf(found,"%s < %s",token_repr[left.t.tType],token_repr[right.t.tType]);
                        return unexpectedLiteral(expected,found,left.t.line);
                    }
                    if( left.t.tType==NUMBER)
                    {
                        return boolInvert(compareNumbers(left,right,1));
                    }
                    else if(left.t.tType==STRING)
                    {
                        return boolInvert(compareStrings(left,right,1));
                    }
                    else
                    {
                        /* throw some error*/
                        return unexpectedLiteral("Either both Numbers or Strings",token_repr[left.t.tType],left.t.line);
                    }
                }
                break;
                case EQUAL:
                {
                    if(left.t.tType!=right.t.tType)
                    {
                        /* throw some error*/
                        char* expected="Same types for comparison operators";
                        char found[64];
                        snprintf(found,"%s == %s",token_repr[left.t.tType],token_repr[right.t.tType]);
                        return unexpectedLiteral(expected,found,left.t.line);
                    }
                    if(left.t.lType!=right.t.lType && left.t.tType==NUMBER)
                    {
                        return isEqualNumber(left,right);
                    }
                    else if(left.t.tType==STRING)
                    {
                        return isEqualString(left,right);
                    }
                    else
                    {
                        /* throw some error*/
                        return unexpectedLiteral("Either both Numbers or Strings",token_repr[left.t.tType],left.t.line);
                    }
                }
                case STAR:
                {
                    if(left.t.tType!=NUMBER || right.t.tType!=NUMBER)
                    {
                        /* throw some error*/
                         char found[64];
                        snprintf(found,"%s * %s",token_repr[left.t.tType],token_repr[right.t.tType]);
                        return unexpectedLiteral("Both numbers",found,left.t.line);
                    }
                    else
                    {
                        return multiplyNumbers(left, right);
                    }
                }
                break;
                case SLASH:
                {
                    if(left.t.tType!=NUMBER || right.t.tType!=NUMBER)
                    {
                        /* throw some error*/
                        char found[64];
                        snprintf(found,"%s * %s",token_repr[left.t.tType],token_repr[right.t.tType]);
                        return unexpectedLiteral("Both numbers",found,left.t.line);
                    }
                    else
                    {
                        return divideNumbers(left,right);
                    }
                }break;
                default:
                return unexpectedLiteral("Binary operator",token_repr[op.tType],op.line);

            }
        }
        break;
        case EXPR_UNARY:
        {
            Literal right=eval(expr->as.u.right);
            Token op=expr->as.u.op;
            switch(op.tType)
            {
                case BANG:
                {
                    if(right.t.tType==STRING || right.t.tType==NUMBER || right.t.tType==TRUE || right.t.tType==FALSE || right.t.tType==NIL)
                    return boolInvert(isTruthey(right));
                    else
                    {
                        return unexpectedLiteral("Everything is truthey/falsey","Something Horrible has happened",right.t.line);
                    }
                }break;
                case MINUS:
                {
                    if(right.t.tType!=NUMBER)
                    {
                        return unexpectedLiteral("Numeric literal",token_repr[right.t.tType],right.t.line);
                    }
                    else
                    {
                        return negateNum(right);
                    }
                }break;
            }
        }
        break;
        case EXPR_LITERAL:
        {
            return expr->as.l;
        }
    }
}