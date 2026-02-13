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
Literal eval(Expr* expr, envpack* curr)
{
    if(!expr)
    {
        Literal ret;
        ret.val.str=";";
        ret.t.token_val.str=";";
        ret.t.tType=SEMICOLON;
        ret.t.lType=LIT_NONE;
        ret.t.line=0;
        return ret;
    }
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
             if(isErrorLiteral(left)) return left;
            if(isErrorLiteral(right)) return right;
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
        case EXPR_CALL:
        {   
            Stmt holdf;
            if(getFunctionFromEnv(curr->fcurr,expr->as.fc.name.identifier_name,expr->as.fc.list.size,&holdf))
            {
                // we must first inject arguments into new scope. 
                Environment* nested=getNestedEnvironment(curr->curr,512);
                
                for(int i=0;i<expr->as.fc.list.size;i++)
                {
                    addToEnvironment(holdf.as.fn.args.arguments.data[i].name.identifier_name,
                        nested,
                        eval(expr->as.fc.list.data[i],curr));
                        Literal check;check.val.i=0;check.t.tType=NIL;
                        getValue(holdf.as.fn.args.arguments.data[i].name.identifier_name,nested,&check);
                     //   printf("injected %d",check.val.i);
                       // printPrimary(check);
                       //printf("\n");

                }
                envpack* nesterpack=(envpack*)malloc(sizeof(envpack));
                nesterpack->curr=nested;
                nesterpack->fcurr=curr->fcurr;
                Package retfrom;
                for(int i=0;i<holdf.as.fn.functionBody.count;i++)
                {
                    retfrom=evalStmt(holdf.as.fn.functionBody.statements[i],nesterpack);
                     if (retfrom.rt != NONE) break;
                }
                if(retfrom.rt!=NONE)
                {
                    return retfrom.val;
                }
                else
                {
                    Literal retnul;
                    retnul.val.i=0;
                    retnul.t.line=-1;
                    retnul.t.lType=LIT_NONE;
                    retnul.t.tType=NIL;
                    retnul.t.token_val.i=0;
                    return retnul;
                }
            }
            else
            {
                printf("Function not defined");
                 Literal retnul;
                    retnul.val.i=0;
                    retnul.t.line=-1;
                    retnul.t.lType=LIT_NONE;
                    retnul.t.tType=NIL;
                    retnul.t.token_val.i=0;
                    return retnul; 
            }
        }break;
        case EXPR_ASSIGN:
        {
            Token name=expr->as.a.name.name;
            Literal right=eval(expr->as.a.right,curr);
            if(isErrorLiteral(right)) return right;
            Literal wast;
            if(modifyVariable(name.identifier_name,curr->curr,right))
            {

            }
            else
            return unexpectedLiteral("Variable declare before use","Nope",0);
            return right;
        }break;
        case EXPR_VARIABLE:
        {   Literal ret;
            if(!getValue(expr->as.v.name.identifier_name, curr->curr, &ret))
            {
                return unexpectedLiteral("Variable declare before use","Nope",0);
            }
            return ret;
        }
        default:
            return unexpectedLiteral("idk not weird shit like this","weird shit",0);
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

static char* printPrimary( Literal l)
{   
    switch(l.t.tType)
    {
        case NUMBER:
        if(l.t.lType==LIT_INTEGER)
        {   
            char*buff=(char*)malloc(12);
            snprintf(buff,12,"%d",l.t.token_val.i);
            return buff;
        }
        else if(l.t.lType==LIT_FLOAT)
        {
            char* buff=(char*)malloc(32);
            snprintf(buff,32,"%f", l.t.token_val.f);
            return buff;
        }
        
        else
        {
            //throw error for error handler, write error handler api
            return "numerror";
        }
        break;
        case STRING:
            if(l.t.lType==LIT_STRING)
            {
                int len=strlen(l.t.token_val.str);
                char* buff=(char*)malloc(len+1);
                snprintf(buff,len+1,"%s",l.t.token_val.str);
                return buff;
            }
            break;
        case NIL:
            return "nil";
            break;
        case TRUE:
        return "true";break;
        case FALSE:
        return "false";break;
        case IDENTIFIER:
         if(l.t.identifier_name)
            {
                int len=strlen(l.t.identifier_name);
                char* buff=(char*)malloc(len+1);
                snprintf(buff,len+1,"%s",l.t.identifier_name);
                return buff;
                break;
            }
        
        default:
       return "<unknown expr>";
        break;

    }
   
}

Package evalStmt(Stmt st, envpack* curr)
{
   Literal empty;
   empty.val.i=0;
   empty.t.line=-1;
   empty.t.lType=LIT_NONE;
   empty.t.tType=NIL;
   empty.t.token_val.i=0;
    switch(st.type)
    {
        case STMT_EXPRESSION:
        {
           eval(st.as.es.expr,curr);
            //return ;
        }
        break;

        case STMT_PRINT:
        {
            Literal l=eval(st.as.ps.expr,curr);
            Literal ret;
            ret.val.str=printPrimary(l);
            printf("%s",ret.val.str);
          //  return;
            // ret.t.token_val.str=strdup(ret.val.str);
            // ret.t.line=l.t.line;
            // ret.t.lType=LIT_STRING;
            // ret.t.tType=STRING;
            // return ret;

        }break;
        case STMT_VARDECL:
        {   Literal ret;
            ret.t.token_val.i=0;
             ret.t.line=-2;
            ret.t.lType=LIT_NONE;
             ret.t.tType=NIL;
            // return ret;
            addToEnvironment(st.as.vd.v.name.identifier_name,curr->curr,ret);
            if(st.as.vd.init)
            eval(st.as.vd.init,curr);
            
            //return ;
        }
        break;
        case STMT_ERROR:
        {
            printf("Error");
            //return ;
        }
        break;
        case STMT_BLOCK:
        {
            Environment* nest=getNestedEnvironment(curr->curr,512);
            //functionEnv* fnest=stackFunctions(curr->fcurr,curr->fcurr->fht.capacity);
            envpack en;
            en.curr=nest;
            en.fcurr=curr->fcurr;
            for(int i=0;i<st.as.bl.count;i++)
            {

                Package ret=evalStmt(st.as.bl.statements[i],&en);
                if(ret.rt==VALUE) return ret;
            }
            freeEnvironment(nest);
            
           // return ;
        }break;
        case STMT_FUNCTION:
        {   Stmt check;
            if(!getFunctionFromEnv(curr->fcurr,st.as.fn.functname.identifier_name,st.as.fn.args.arguments.size,&check))
            addFunctionToEnv(curr->fcurr,st.as.fn.functname.identifier_name,st.as.fn.args.arguments.size,st);
            else {printf("Already defined");}

        }break;
        case STMT_RETURN:
        {
            Literal send=eval(st.as.retpack.ex,curr);
            Package p;
            p.rt=VALUE;
            p.val=send;
            return p;
        }break;
        case STMT_IF:
        {
            if(boolify(eval(st.as.ifStmt.cond,curr)).t.tType==TRUE)
            {
                Stmt exe;
                exe.type=STMT_BLOCK;
                exe.as.bl=st.as.ifStmt.condblock;
                return evalStmt(exe,curr);
            }
            else if(st.as.ifStmt.type==ELSE_ONLY)
            {
                Stmt exe;
                exe.type=STMT_BLOCK;
                exe.as.bl=st.as.ifStmt.elb.as.condblock;
                return evalStmt(exe,curr);
            }
            else if(st.as.ifStmt.type==ELSE_IF)
            {
                Stmt exe;
                exe.type=STMT_IF;
                exe.as.ifStmt=*st.as.ifStmt.elb.as.elif;
                return evalStmt(exe,curr);
            }
            
        }break;
    }
    return (Package){NONE, empty};
}