#include "parse_tree_def.h"
#include<stdio.h>
#include<string.h>
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
Expr* new_unary(Token op, Expr* expr)
{
    Expr* ret=(Expr*)(malloc(sizeof(Expr)));
    ret->type=EXPR_UNARY;
    ret->as.u.right=expr;
    ret->as.u.op=op;
    return ret;
}

Expr* new_binary(Token op, Expr* left,Expr* right)
{
     Expr* ret=(Expr*)(malloc(sizeof(Expr)));
      ret->type=EXPR_BINARY;
      ret->as.b.left=left;
      ret->as.b.op=op;
      ret->as.b.right=right;
    return ret;
}

Expr* new_literal(Token t,Value val)
{
    Expr* ret=(Expr*)(malloc(sizeof(Expr)));
    ret->type=EXPR_LITERAL;
    if(t.tType!=STRING)
    ret->as.l.val=val;
    else
    ret->as.l.val.str=strdup(val.str);
    ret->as.l.t=t;
    if(t.tType==TRUE)
    {
        ret->as.l.val.i=1;
    }
    if(t.tType==FALSE)
    {
        ret->as.l.val.i=0;
    }
    if(t.lType!=LIT_STRING)
    ret->as.l.t.token_val=ret->as.l.val;
    else
    {
        ret->as.l.t.token_val.str=strdup(ret->as.l.val.str);

    }
    return ret;
}
static void printBinary(Binary b)
{
    printf("(");
    printTree(b.left);
    printf(" %s ", token_repr[b.op.tType]);
    printTree(b.right);
    printf(")");

}
static void printUnary(Unary u)
{
    printf("  %s ",token_repr[u.op.tType]); printTree(u.right);
}
static void printPrimary( Literal l)
{   switch(l.t.tType)
    {
        case NUMBER:
        if(l.t.lType==LIT_INTEGER)
        {
            printf("%d",l.t.token_val.i);
        }
        else if(l.t.lType==LIT_FLOAT)
        {
            printf("%f", l.t.token_val.f);
        }
        
        else
        {
            //throw error for error handler, write error handler api
            
        }
        break;
        case STRING:
            if(l.t.lType==LIT_STRING)
            {
                printf("%s",l.t.token_val.str);
            }
            break;
        case NIL:
            printf("nil");
            break;
        case TRUE:
        printf("%s","true");break;
        case FALSE:
        printf("%s","false");break;
        case IDENTIFIER:
         if(l.t.identifier_name)
            printf("%s",l.t.identifier_name);break;
        
        default:
        printf("<unknown expr>");
        break;

    }
   
}
Expr* new_callee(Token fname, argExprArray passed)
{
    Expr* ret=(Expr*)(malloc(sizeof(Expr)));
    ret->type=EXPR_CALL;
    ret->as.fc.list=passed;
    ret->as.fc.name=fname;
    return ret;
}
static void printVariable(Variable v)
{
    printf("%s",v.name.identifier_name);
}
static void printAssignment(Assignment v)
{
   printf("("); printVariable(v.name);printf("= ");
    printTree(v.right);printf(")");
}
static void printCall(callee f)
{
  //  printf("argsize=%d\n",f.list.size);
    printf("%s(",f.name.identifier_name);
    
    for(int i=0;i<f.list.size;i++)
    {
        printTree(f.list.data[i]);printf(",");
    }
    printf(")");
}
void printTree(Expr* ex)
{   if(!ex) return;
    switch(ex->type)
    {
        case EXPR_BINARY:
            printBinary(ex->as.b);
            break;
        case EXPR_UNARY:
            printUnary(ex->as.u);
            break;
        case EXPR_LITERAL:
            printPrimary(ex->as.l);
            break;
        case EXPR_ASSIGN:
            printAssignment(ex->as.a);break;
        case EXPR_VARIABLE:
            printVariable(ex->as.v);
            break;
        case EXPR_CALL:
        {
            printCall(ex->as.fc);
        }break;
    }
}

Expr* new_variable( Token name,Expr* ex)
{
    Expr* ret=malloc(sizeof(Expr));
    ret->as.v.type=(ex)?INDEXED_VAR:UNINDEXED_VAR;
    ret->as.v.name=name;
    ret->as.v.indexp=ex;
    ret->type=EXPR_VARIABLE;
    return ret;
    
}
Expr* new_assign(Variable name, Expr* right)
{
    Expr* ret=malloc(sizeof(Expr));
    ret->type=EXPR_ASSIGN;
    ret->as.a.name=name;
    ret->as.a.right=right;
    return ret;
}
void printVardecl(varDecl vd)
{
    printf(" var %s",vd.v.name.identifier_name);
    if(vd.init)
    {
        printf(" = ");printTree(vd.init);
    }
    printf(" ;");
}
void printPrintStatement(printStmt ps)
{
    printf("print ");
    printTree(ps.expr);
    printf(" ;");
}
void printExprStatement(exprStmt es)
{
    printTree(es.expr);
    printf(" ;");
}
void printBlock(Stmt st)
{
     printf("{");
            for(int i=0;i<st.as.bl.count;i++)
            {   printf("\n");
                printStatementTree(st.as.bl.statements[i]);
                
            }
            printf("\n}");
}
void printStatementTree(Stmt st)
{
    switch(st.type)
    {
        case STMT_VARDECL:
        {
            printVardecl(st.as.vd);
        }
        break;
        case STMT_PRINT:
        {
            printPrintStatement(st.as.ps);
        }break;
        case STMT_EXPRESSION:
        {
            printExprStatement(st.as.es);
        }break;
        case STMT_ERROR:
        {
            printf("Error in parsing statement");
        }break;
        case STMT_BLOCK:
        {
            printf("{");
            for(int i=0;i<st.as.bl.count;i++)
            {   printf("\n");
                printStatementTree(st.as.bl.statements[i]);
                
            }
            printf("\n}");
        }break;
        case STMT_FUNCTION:
        {
            printf("%s",st.as.fn.functname.identifier_name);
            printf("(");
            for(int i=0;i<st.as.fn.args.arguments.size;i++)
            {
                printf("%s,",st.as.fn.args.arguments.data[i].name.identifier_name);
            }
            printf(")");
            Stmt st1;
            st1.type=STMT_BLOCK;
            st1.as.bl=st.as.fn.functionBody;
            printStatementTree(st1);
        }break;
        case STMT_RETURN:
        {
            printf("return ");
            printTree(st.as.retpack.ex);
            printf(";");
        }break;
        case STMT_IF:
        {
            printf("if (");printTree(st.as.ifStmt.cond);printf(")");
            printf("{");
            for(int i=0;i<st.as.ifStmt.condblock.count;i++)
            {
                printStatementTree(st.as.ifStmt.condblock.statements[i]);
                printf("\n");
            }
            printf("}\n");
            if(st.as.ifStmt.type==NO_ELSE)return;
            if(st.as.ifStmt.type==ELSE_ONLY)
            {
                printf("ELSE\n{");
                for(int i=0;i<st.as.ifStmt.elb.as.condblock.count;i++)
                {
                    printStatementTree(st.as.ifStmt.elb.as.condblock.statements[i]);
                    printf("\n");
                }
            }
            else if(st.as.ifStmt.type==ELSE_IF)
            {
                Stmt pr;
                pr.type=STMT_IF;
                pr.as.ifStmt=*st.as.ifStmt.elb.as.elif;
                printStatementTree(pr);
            }
            
        }break;
        case STMT_WHILE:
        {
            printf("while(");
            printTree(st.as.whileSt.exp);
            printf(")");
            Stmt bls;
            bls.type=STMT_BLOCK;
            bls.as.bl=st.as.whileSt.condblock;
            printStatementTree(bls);
        }break;
        case STMT_FOR:
        {
            printf("for(");
            printStatementTree(*st.as.forSt.init);
            printStatementTree(*st.as.forSt.cond);
            printStatementTree(*st.as.forSt.inc);
            printf(")");
            Stmt bls;
            bls.type=STMT_BLOCK;
            bls.as.bl=st.as.forSt.blst;
            printStatementTree(bls);
        }break;
    }
}