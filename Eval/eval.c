#include "eval.h"

static  char *token_repr[] = {
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
Literal eval(Expr* expr, Environment* curr)
{
    ExprType e=expr->type;
    switch(e)
    {
        case EXPR_BINARY:
        {   
            Token op=expr->as.b.op;
            switch(op.tType)
            {
                case AND:
                {
                    Literal left=eval(expr->as.b.left,curr);
                     if(isErrorLiteral(left)) return unexpectedLiteral("Bool literal","Error",left.t.line);;
                    left=boolify(left);
                    
                    if(!left.val.i)
                    { 
                        return makeBoolLit(0,left);
                    }
                    Literal right=eval(expr->as.b.right,curr);
                    if(isErrorLiteral(right)) return unexpectedLiteral("Bool literal","Error",left.t.line);;
                    right=boolify(right);
                    
                    if(!right.val.i)
                    {
                        
                        return makeBoolLit(0,left);
                    }
                    return makeBoolLit(1,left);

                }break;
                case OR:
                {
                     Literal left=eval(expr->as.b.left,curr);
                      if(isErrorLiteral(left)) return unexpectedLiteral("Bool literal","Error",left.t.line);;
                    left=boolify(left);
   
                    if(left.val.i)
                    {
                        return makeBoolLit(1,left);
                    }
                      Literal right=eval(expr->as.b.right,curr);
                    if(isErrorLiteral(right)) return unexpectedLiteral("Bool literal","Error",left.t.line);;

                    right=boolify(right);
                    if(right.val.i)
                    {
                        return makeBoolLit(1,left);
                    }
                    return makeBoolLit(0,left);
                }break;
            }
            Literal left=eval(expr->as.b.left,curr);
            Literal right=eval(expr->as.b.right,curr);
            
            switch(op.tType)
            {
                case PLUS:
                {
                    return addLiterals(left,right);
                }
                break;
                case MINUS:
                {
                    if(left.t.tType==TRUE || left.t.tType==FALSE)
                    left=toInteger(left);
                    if(right.t.tType==TRUE || right.t.tType==FALSE)
                    right=toInteger(right);
                    if(left.t.tType==right.t.tType && left.t.tType==NUMBER)
                    {
                        return subtractNums(left,right);
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
                    // if(left.t.tType!=right.t.tType)
                    // {
                    //     /* Throw some error*/
                    //     char* expected="Same types for comparison operators";
                    //     char found[64];
                    //     snprintf(found,"%s > %s",token_repr[left.t.tType],token_repr[right.t.tType]);
                    //     return unexpectedLiteral(expected,found,left.t.line);
                    // }
                    Literal ret=compareLiterals(left,right,0);
                    if(!isErrorLiteral(ret))
                    {
                        return ret;
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
                    // if(left.t.tType!=right.t.tType)
                    // {
                    //     /* Throw some error*/
                    //      char* expected="Same types for comparison operators";
                    //     char found[64];
                    //     snprintf(found,"%s >= %s",token_repr[left.t.tType],token_repr[right.t.tType]);
                    //     return unexpectedLiteral(expected,found,left.t.line);
                    // }
                     Literal ret=compareLiterals(left,right,1);
                    if(!isErrorLiteral(ret))
                    {
                        return ret;
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
                    // if(left.t.tType!=right.t.tType)
                    // {
                    //     /* Throw some error*/
                    //     char* expected="Same types for comparison operators";
                    //     char found[64];
                    //     snprintf(found,"%s < %s",token_repr[left.t.tType],token_repr[right.t.tType]);
                    //     return unexpectedLiteral(expected,found,left.t.line);
                    // }
                     Literal ret=compareLiterals(right,left,0);
                    if(!isErrorLiteral(ret))
                    {
                        return ret;
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
                    // if(left.t.tType!=right.t.tType)
                    // {
                    //     /* Throw some error*/
                    //      char* expected="Same types for comparison operators";
                    //     char found[64];
                    //     snprintf(found,"%s < %s",token_repr[left.t.tType],token_repr[right.t.tType]);
                    //     return unexpectedLiteral(expected,found,left.t.line);
                    // }
                     Literal ret=compareLiterals(right,left,1);
                    if(!isErrorLiteral(ret))
                    {
                        return ret;
                    }
                    else
                    {
                        /* throw some error*/
                        return unexpectedLiteral("Either both Numbers or Strings",token_repr[left.t.tType],left.t.line);
                    }
                }
                break;
                case EQUAL_EQUAL:
                {
                    
                    Literal ret=isEqualLiteral(left,right);
                    if(!isErrorLiteral(ret))
                    return ret;
                    else
                    {
                        /* throw some error*/
                        return unexpectedLiteral("Either both Numbers or Strings",token_repr[left.t.tType],left.t.line);
                    }
                }break;
                case BANG_EQUAL:
                {
                    Literal ret=isEqualLiteral(left,right);
                    if(!isErrorLiteral(ret))
                    return boolInvert(ret);
                    else
                    {
                        /* throw some error*/
                        return unexpectedLiteral("Either both Numbers or Strings",token_repr[left.t.tType],left.t.line);
                    }
                }
                break;
                case STAR:
                {
                    if(left.t.tType==TRUE || left.t.tType==FALSE)
                    left=toInteger(left);
                    if(right.t.tType==TRUE || right.t.tType==FALSE)
                    right=toInteger(right);
                    if(left.t.tType!=NUMBER || right.t.tType!=NUMBER)
                    {
                        /* throw some error*/
                         char found[64];
                        snprintf(found,128,"%s * %s",token_repr[left.t.tType],token_repr[right.t.tType]);
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
                    if(left.t.tType==TRUE || left.t.tType==FALSE)
                    left=toInteger(left);
                    if(right.t.tType==TRUE || right.t.tType==FALSE)
                    right=toInteger(right);
                    if(left.t.tType!=NUMBER || right.t.tType!=NUMBER)
                    {
                        /* throw some error*/
                        char found[64];
                        snprintf(found,128,"%s * %s",token_repr[left.t.tType],token_repr[right.t.tType]);
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
            Literal right=eval(expr->as.u.right,curr);
            Token op=expr->as.u.op;
            switch(op.tType)
            {
                case BANG:
                {
                    if(right.t.tType==STRING || right.t.tType==NUMBER || right.t.tType==TRUE || right.t.tType==FALSE || right.t.tType==NIL)
                    return boolInvert(right);
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
        }break;
        case EXPR_ASSIGN:
        {
            Token name=expr->as.a.name.name;
            Literal right=eval(expr->as.a.right,curr);
            addToEnvironment(name.identifier_name,curr,right);
            return right;
        }break;
        case EXPR_VARIABLE:
        {   Literal ret;
            if(!getValue(expr->as.v.name.identifier_name, curr, &ret))
            {
                return unexpectedLiteral("Variable declare before use","Nope",0);
            }
            return ret;
        }
    }
}


/*
    case AND:
                {
                    left=boolify(left);
   
                    if(left.val.i)
                    {
                        return makeBoolLit(0,left);
                    }
                    right=boolify(right);
                    if(right.val.i)
                    {
                        return makeBoolLit(0,left);
                    }
                    return makeBoolLit(1,left);

                }break;
                case OR:
                {
                    left=boolify(left);
   
                    if(left.val.i)
                    {
                        return makeBoolLit(0,left);
                    }
                    right=boolify(right);
                    if(right.val.i)
                    {
                        return makeBoolLit(0,left);
                    }
                    return makeBoolLit(1,left);
                }break;
*/