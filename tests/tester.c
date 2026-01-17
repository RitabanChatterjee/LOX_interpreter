#include "eval.h"



void testAdd()
{
    char* tests[] = {
        "\"abc\" + 4",
    "\"hello\" + \"world\"",
    "\"num:\" + 123",
    "123 + \"num\"",
    "\"\" + 0",
    "\"0\" + 0",
    "\"\" + \"\"",
    "\"test\" + true",
    "false + \"test\"",
    "\"newline\\n\" + \"tab\\t\"",
   // "\"quote\\\"\" + \"end\"",
    "\"emoji🙂\" + \"test\"",
    "\"a\" + -1",
    "-1 + \"a\"",
    "\"long\" + 999999999",
    "\"123\" + 456",
    "0 + \"zero\"",
    "\"true\" + false",
    "\" \" + \"space\"",
    "\"NaN\" + 0",
    "4+34",
    "3.14+2.7182"

};
    
    
    for(int i=0;i<20;i++)
    {
        TokenList tokens=scanTokens(tests[i],strlen(tests[i]));
        for(int i=0;i<tokens.size;i++)
        {
            printToken(tokens.tokens[i]);fflush(stdout);
        }
        //printf("%s %d",tests[i],i);fflush(stdout);
        Expr* ex=parse(tests[i],strlen(tests[i]));
       // printTree(ex);fflush(stdout);
        if(!ex)
        {
            printf("ex null"); fflush(stdout);
        }
        else if(!(ex->as.b.left))
        {
            printf("left null %d",i);fflush(stdout);
        }
        else if(!(ex->as.b.right))
        {
            printf("right null %d",i);fflush(stdout);
        }
        
        Literal ans=addLiterals(ex->as.b.left->as.l,ex->as.b.right->as.l);
        if(isErrorLiteral(ans))
        {
            printf("On line %d there is an error\n",i+1);continue;
        }
        Expr* dof=new_literal(ans.t,ans.val);
        printTree(dof);fflush(stdout);
        printf("\n");
    }

}

void testGreater()
{
    char* gt_tests[] = {
    "5 > 3",
    "3 > 5",
    "0 > 0",
    "10 > 2",
    "2 > 2",
    "3.14 > 2.71",
    "2.71 > 3.14",
    "5 > 5.0",
    "5.0 > 4",
    "0.0 > 0.1",
    "\"\" > \"\"",
    "\"a\" > \"b\"",
    "\"abc\" > \"ab\"",
    "\"ab\" > \"abc\"",
    "\"same\" > \"same\"",
    "\"\" > \"a\"",
    "\"z\" > \"aa\"",
    "\"10\" > \"2\"",
    "10 > \"2\"",        // ❌ invalid
    "\"abc\" > 5"        // ❌ invalid
};
    for(int i=0;i<20;i++)
    {
        TokenList tokens=scanTokens(gt_tests[i],strlen(gt_tests[i]));
        for(int i=0;i<tokens.size;i++)
        {
            //printToken(tokens.tokens[i]);fflush(stdout);
        }
        //printf("%s %d",tests[i],i);fflush(stdout);
        Expr* ex=parse(gt_tests[i],strlen(gt_tests[i]));
        Literal ans;
       // printTree(ex);fflush(stdout);
        printf("%s:",gt_tests[i]);
        if(!ex)
        {
            printf("ex null"); fflush(stdout);
        }
        else if(!(ex->as.b.left))
        {
            printf("left null %d",i);fflush(stdout);
        }
        else if(!(ex->as.b.right))
        {
            printf("right null %d",i);fflush(stdout);
        }
        if(ex->as.b.left->as.l.t.tType==ex->as.b.right->as.l.t.tType)
        {
             //printf("In this thingy, please print mf");
            if(ex->as.b.left->as.l.t.tType==NUMBER )
            {   
                Literal left;
                Literal right;
               // printf("In this inner thingy, please print mf");
                ans=compareNumbers(ex->as.b.left->as.l,ex->as.b.right->as.l,0);
            }
            else if(ex->as.b.right->as.l.t.tType==STRING)
            {
                Literal left=ex->as.b.left->as.l;
                Literal right=ex->as.b.right->as.l;
                ans=compareStrings(left,right,0);
            }
            else
            {
                 unexpectedLiteral("Same type comparisons","Nope\n",0);
                 continue;
            }
        }
        else
        {
             unexpectedLiteral("Same type comparisons","Nope\n",0);
                 continue;
        }
     //   printf("%d\n",ans.t.tType);
        if(isErrorLiteral(ans))
        {
            printf("On line %d there is an error\n",i+1);continue;
        }
        Expr* dof=new_literal(ans.t,ans.val);
        printTree(dof);fflush(stdout);
        printf("\n");
    }
}
void testGreaterE()
{
    char* gt_tests[] = {
        "5 >= 3",
    "3 >= 5",
    "0 >= 0",
    "10 >= 2",
    "2 >= 2",
    "3.14 >= 2.71",
    "2.71 >= 3.14",
    "5 >= 5.0",
    "5.0 >= 4",
    "0.0 >= 0.1",
    "-1 >= -1",
    "-1 >= -2",
    "-2 >= -1",
    "\"\" >= \"\"",
    "\"a\" >= \"b\"",
    "\"abc\" >= \"ab\"",
    "\"ab\" >= \"abc\"",
    "\"same\" >= \"same\"",
    "\"\" >= \"a\"",
    "\"z\" >= \"aa\"",
    "\"10\" >= \"2\"",
    "\"a\" >= \"A\"",
    "\"A\" >= \"a\"",
    "\"abc\" >= \"abc \"",
    "\"abc \" >= \"abc\"",
    "10 >= \"2\"",        // ❌ invalid
    "\"abc\" >= 5",       // ❌ invalid
    "true >= true",       // ❌ invalid
    "nil >= nil",         // ❌ invalid
    "(5 >= 3) >= 2",      // ❌ invalid
    "5 >= (3 >= 2)"       // ❌ invalid

};
    for(int i=0;i<30;i++)
    {
        TokenList tokens=scanTokens(gt_tests[i],strlen(gt_tests[i]));
        for(int i=0;i<tokens.size;i++)
        {
           // printToken(tokens.tokens[i]);fflush(stdout);
        }
        //printf("%s %d",tests[i],i);fflush(stdout);
        Expr* ex=parse(gt_tests[i],strlen(gt_tests[i]));
        Literal ans;
       // printTree(ex);fflush(stdout);
        printf("%s:",gt_tests[i]);
        if(!ex)
        {
            printf("ex null"); fflush(stdout);
        }
        else if(!(ex->as.b.left))
        {
            printf("left null %d",i);fflush(stdout);
        }
        else if(!(ex->as.b.right))
        {
            printf("right null %d",i);fflush(stdout);
        }
        if(ex->as.b.left->as.l.t.tType==ex->as.b.right->as.l.t.tType)
        {
             //printf("In this thingy, please print mf");
            if(ex->as.b.left->as.l.t.tType==NUMBER )
            {   
                Literal left;
                Literal right;
               // printf("In this inner thingy, please print mf");
                ans=compareNumbers(ex->as.b.left->as.l,ex->as.b.right->as.l,1);
            }
            else if(ex->as.b.right->as.l.t.tType==STRING)
            {
                Literal left=ex->as.b.left->as.l;
                Literal right=ex->as.b.right->as.l;
                ans=compareStrings(left,right,1);
            }
            else
            {
                 unexpectedLiteral("Same type comparisons","Nope\n",0);
                 continue;
            }
        }
        else
        {
             unexpectedLiteral("Same type comparisons","Nope\n",0);
                 continue;
        }
     //   printf("%d\n",ans.t.tType);
        if(isErrorLiteral(ans))
        {
            printf("On line %d there is an error\n",i+1);continue;
        }
        Expr* dof=new_literal(ans.t,ans.val);
        printTree(dof);fflush(stdout);
        printf("\n");
    }
}
void testComparison()
{
    testGreater();
    testGreaterE();
}




int main()
{
    testComparison();
    //testAdd();
}