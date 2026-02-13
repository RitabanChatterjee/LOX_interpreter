#include "recursive_descent.h"
#include "parse_tree_def.h"
#include<string.h>

#define ERR_TOK (Token){-1,-1,-1,-1,""}

static Token get(Parser *p)
{
    if(p->pointer>=p->tokens.size) return ERR_TOK;
    return p->tokens.tokens[p->pointer];
}
static Token advance(Parser* p)
{
        p->pointer++;
        return get(p);
}

static Token peek(Parser* p)
{
    if(p->pointer>=p->tokens.size-1) return ERR_TOK;
    return p->tokens.tokens[p->pointer+1];
}
static Token consume(TokenType tT, Parser* p, char* errmsg)
{
    Token t=get(p);
    if(t.tType==tT) return advance(p);
    printf("%s",errmsg);
    return (Token){-2,-2,-2,-2,""};
}
static int match(Token t, TokenType m)
{
    
    return t.tType==m;

}
static Stmt throwErrorStmt(char* msg)
{
    Stmt st;st.type=STMT_ERROR;
    st.as.error.msg=strdup(msg);
    printf("%s",msg);
    return st;
}

static Literal initnull(Token t)
{
    Literal nullinit;
            nullinit.val.i=0;
            nullinit.t.token_val.i=0;
            nullinit.t.line=t.line;
            nullinit.t.tType=NIL;
            nullinit.t.lType=LIT_NONE;
        return nullinit;
}
Stmt variableDeclaration(Parser* p)
{
    Token t=get(p);//get identifier.
  
    Stmt st;
    st.type=STMT_VARDECL;
    st.as.vd.v.name=t;
    st.as.vd.init=NULL;
    if(peek(p).tType==EQUAL) // p is at identifier
    {
        st.as.vd.init=parseExpr(p);
    }
    else
    {
        advance(p);
    }
     Token res= consume(SEMICOLON,p,"expected ;");
    if(res.line==-2)
    {
        return throwErrorStmt("Expected semicolon");
    }
    return st;
}
Stmt expressionStatement(Parser* p)
{
    Stmt st;
    st.type=STMT_EXPRESSION;
    st.as.es.expr=parseExpr(p);
   Token res= consume(SEMICOLON,p,"expected ;");
    if(res.line==-2)
    {
        return throwErrorStmt("Expected semicolon");
    }
    return st;
}
Stmt printstatement(Parser* p)
{
    Stmt st;
    st.type=STMT_PRINT;
    
    st.as.ps.expr=parseExpr(p);
    Token res= consume(SEMICOLON,p,"expected ;");
    if(res.line==-2)
    {
        return throwErrorStmt("Expected semicolon");
    }
    return st;
}
Stmt parseBlock(Parser* p)
{
    Stmt ret;
    ret.type=STMT_BLOCK;
    advance(p);//consume left brace
    ret.as.bl.statements = NULL;

    ret.as.bl.count=0;
    while(get(p).tType!=RIGHT_BRACE && get(p).tType!=-1) //it will be -1 at eof
    {
        
        ret.as.bl.statements=(Stmt*)realloc(ret.as.bl.statements, sizeof(Stmt) *(ret.as.bl.count+1));
        //int count=;
        ret.as.bl.statements[ret.as.bl.count]=declaration(p);
        ret.as.bl.count++;
    }
    if(get(p).tType==RIGHT_BRACE)
    {advance(p);return ret;}
    else
    {
        Stmt ret;
        ret.type=STMT_ERROR;
        ret.as.error.msg="Missing }";
        return ret;
    }
}
Stmt parseFunction(Parser* p)
{
    advance(p); // consume FUN
    Stmt* st;
     st=(Stmt*)malloc(sizeof(Stmt));
    if(get(p).tType==IDENTIFIER)
    {
        st->as.fn.functname=get(p);advance(p);//consume function naem
    }
   // st.type=STMT_FUNCTION;
    st->as.fn.args.arguments=argArray_make();
   // st.as.fn.functionBody;
    consume(LEFT_PAREN,p,"Expected (");// consume left paren
    while(get(p).tType!=RIGHT_PAREN && get(p).tType !=-1)
    {
        if(get(p).tType==IDENTIFIER)
        {
            Variable v;v.name=get(p);
            argArray_push(&st->as.fn.args.arguments,v);
            advance(p);
            if(get(p).tType==RIGHT_PAREN)
            {
                break;
            }
            else
            consume(COMMA,p,"Expected comma between identifiers");
        }
        else
        {
            Stmt ret;ret.type=STMT_ERROR;
            ret.as.error.msg="Error, expected an identifier";
            return ret;
        }
    }
    if(get(p).tType==RIGHT_PAREN) advance(p);
    else
    {
        Stmt ret;ret.type=STMT_ERROR;
            ret.as.error.msg="Error, expected an )";
            return ret;
    }
   
    
 //   Stmt s=parseBlock(p);
    st->as.fn.functionBody=parseBlock(p).as.bl;
   // st->as.fn.
    st->type=STMT_FUNCTION;
    return *st;

}
Stmt otherStatements(Parser* p)
{
    if(get(p).tType==PRINT)
    {
        advance(p);
        return printstatement(p);
    }
    else if(get(p).tType==LEFT_BRACE)
    {
        
        return parseBlock(p);
    }
    else if(get(p).tType==FUN)
    {
        return parseFunction(p);
    }
    else
    {
        return expressionStatement(p);
    }
}
Stmt declaration(Parser* p)
{
    if(get(p).tType==VAR)
    {
        if(peek(p).tType==IDENTIFIER)
        {
            Token t=advance(p);// consume var
            return variableDeclaration(p);
        }
        // else throw some error
    }
    if(get(p).tType==RETURN)
    {
        Token t=advance(p);
        Expr* ex=parseExpr(p);
        Stmt st;
        st.type=STMT_RETURN;
        st.as.retpack.ex=ex;
        return st;
    }
    return otherStatements(p);
}

Expr* parseExpr(Parser *p)
{
    return parseAssign(p);
}
Expr* parseAssign(Parser* p)
{   
    Expr* ex=parseOr(p);
    Token t=get(p);
    if(match(t,EQUAL))
    {
        advance(p);
        if(ex && ex->type==EXPR_VARIABLE)
        {
            return new_assign(ex->as.v,parseAssign(p));
        }
        else
        return unexpectedExpr("Invalid lvalue", t.line);
    }
   return ex;
}
Expr* parseOr(Parser* p)
{
    Expr* ex=parseAnd(p);
    while(1)
    {
        Token t = get(p);
        if (!(match(t, OR)))
            break;

        advance(p);               // consume operator
        Expr* right = parseAnd(p);
        ex = new_binary(t, ex, right);
    }
    return ex;
}
Expr* parseAnd(Parser* p)
{
    Expr* ex=parseEquality(p);
    while(1)
    {
        Token t=get(p);
        if(!match(t,AND)) break;
        advance(p);               // consume operator
        Expr* right = parseEquality(p);
        ex = new_binary(t, ex, right);
    }
    return ex;
}
Expr* parseEquality(Parser* p)
{
    Expr* expr = parseComparison(p);

    while (1)
    {
        Token t = get(p);
        if (!(match(t, EQUAL_EQUAL) || match(t, BANG_EQUAL)))
            break;

        advance(p);               // consume operator
        Expr* right = parseComparison(p);
        expr = new_binary(t, expr, right);
    }

    return expr;
}


Expr* parseComparison(Parser *p)
{
    Expr* term=parseTerm(p);
    
    while(1)
    {
        Token t=get(p);
        
        if(!(match(t,GREATER) || match(t,GREATER_EQUAL) || match(t,LESS) || match(t,LESS_EQUAL)))
        {
            break;
        }
        advance(p);
        Expr* right=parseTerm(p);
        term=new_binary(t,term,right);
    }
    return term;
}
Expr* parseTerm(Parser* p)
{
    Expr* exp=parseFactor(p);
    while(1)
    {
        Token t=get(p);
        if(!(match(t,PLUS) || match(t,MINUS)))
        {
            break;
        }
        advance(p);
        Expr* right=parseFactor(p);
        exp=new_binary(t,exp,right);
    }
    return exp;
}
Expr* parseFactor(Parser* p)
{
    Expr* ex=parseUnary(p);
    while(1)
    {
        Token t=get(p);
        
        if(!(match(t,SLASH) || match(t,STAR)))
        {
            break;
        }
        advance(p);
        Expr* right=parseUnary(p);
        ex=new_binary(t,ex,right);
    }
    return ex;
}

Expr* parseUnary(Parser* p)
{
    Token t=get(p);
    if((match(t,BANG) || match(t,MINUS)) )
    {
        advance(p);
        Expr* right=parseUnary(p);
        
        return new_unary(t,right);
    }
    return parseLiteral(p);
    
}

Expr* parseLiteral(Parser* p)
{
    Token t=get(p);
    if(t.tType!=SEMICOLON )
    advance(p);
    if(t.tType==NUMBER || t.tType==STRING) return new_literal(t,t.token_val);
    else if(t.tType==IDENTIFIER)
    {
        if(get(p).tType==LEFT_PAREN)
        {
            //THIS IS A FUNCTION
            argExprArray pass=argExprArray_make();
            //advance(p);// now left paren logic will handle the rest.
            advance(p); //consume left paren
            while(get(p).tType!=RIGHT_PAREN && get(p).tType!=-1)
            {
                
                Expr* ex=parseExpr(p);
                if(ex)
                argExprArray_push(&pass,ex);
            }
            consume(RIGHT_PAREN,p,") expected");
            return new_callee(t,pass);
        }
         Value val;val.str="";
        // if(t.identifier_name)
        //     {int leng=strlen(t.identifier_name);
        //         t.identifier_name[leng]='\0';
        //         val.str = strdup(t.identifier_name);
        //     } // <-- copy string to heap
        // else
        //     val.str = NULL;
        return new_variable(t);
    }
    
    else if(t.tType==TRUE)
    {   
        t.token_val.i=1;
        return new_literal(t,t.token_val);
    }
    else if(t.tType==FALSE)
    {
        t.token_val.i=0;
        return new_literal(t,t.token_val);
    }
  
    else if(t.tType==NIL)
    {
        return new_literal(t,t.token_val);
    }
    
    else if(t.tType==LEFT_PAREN)
    {
        Expr* exp=parseExpr(p);
        advance(p);
        return exp;
    }
    
    return NULL;
}

