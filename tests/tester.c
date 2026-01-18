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
       
             //printf("In this thingy, please print mf");
            ans=compareLiterals(ex->as.b.left->as.l,ex->as.b.right->as.l,0);
        
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
        
             //printf("In this thingy, please print mf");
        ans=compareLiterals(ex->as.b.left->as.l,ex->as.b.right->as.l,1);
        
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
void testEquals()
{
    char* eqTests[] = {
    "0 == 0",
    "0 == 1",
    "1 == 0",
    "-1 == -1",
    "-1 == 1",
    "42 == 42",
    "42 == 43",
    "3.14 == 3.14",
    "3.14 == 3.140",
    "2.71 == 3.14",
    "0.0 == 0",
    "0.0 == 0.0",
    "-0.0 == 0.0",
    "-2.5 == -2.5",
    "-2.5 == 2.5",

    "\"\" == \"\"",
    "\"\" == \"a\"",
    "\"a\" == \"\"",
    "\"a\" == \"a\"",
    "\"a\" == \"b\"",
    "\"abc\" == \"abc\"",
    "\"abc\" == \"ab\"",
    "\"ab\" == \"abc\"",
    "\"hello\" == \"hello\"",
    "\"hello\" == \"Hello\"",
    "\"Hello\" == \"hello\"",
    "\"123\" == \"123\"",
    "\"123\" == \"0123\"",
    "\"space\" == \"space \"",
    "\" \" == \"\""
};
    for(int i=0;i<30;i++)
    {
        Expr* ex=parse(eqTests[i],strlen(eqTests[i]));
        printf("%s: ",eqTests[i]);
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
        Literal a=ex->as.b.left->as.l;
        Literal b=ex->as.b.right->as.l;
        Literal ans=isEqualLiteral(a,b);
         if(isErrorLiteral(ans))
        {
            printf("On line %d there is an error\n",i+1);continue;
        }
        Expr* dof=new_literal(ans.t,ans.val);
        printTree(dof);fflush(stdout);
        printf("\n");
    }
}
void testBoolify()
{
   char* gt_tests[]={ 
         "0",            // integer zero
        "42",           // positive integer
        "1",           // negative integer
        "0.0",          // float zero
        "3.14",         // positive float
        "2.71",        // negative float
        "\"\"",         // empty string
        "\"a\"",        // single char string
        "\"hello\"",    // longer string
        "nil",          // nil value
        "0",           // inversion of zero
        "42",          // inversion of positive integer
        "-1",          // inversion of negative integer
        "0.0",         // inversion of float zero
        "3.14",        // inversion of positive float
        "-2.71",       // inversion of negative float
        "\"\"",        // inversion of empty string
        "\"a\"",       // inversion of single char string
        "\"hello\"",   // inversion of longer string
        "nil"          // inversion of nil
   };
    for (int i=0;i<20;i++)
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
        else if(!(ex))
        {
            printf("left null %d",i);fflush(stdout);
        }
        Literal inv=boolify(ex->as.l);
        Expr* dof=new_literal(inv.t,inv.val);
        printTree(dof);
        printf("\n");

    }
}
void testInvert()
{
    char* gt_tests[]=
    {
        "!0",            // integer zero
        "!42",           // positive integer
        "!1",           // negative integer
        "!0.0",          // float zero
        "!3.14",         // positive float
        "!2.71",        // negative float
        "!\"\"",         // empty string
        "!\"a\"",        // single char string
        "!\"hello\"",    // longer string
        "!nil",          // nil value
        "!0",           // inversion of zero
        "!42",          // inversion of positive integer
        "!-1",          // inversion of negative integer
        "!0.0",         // inversion of float zero
        "!3.14",        // inversion of positive float
        "!-2.71",       // inversion of negative float
        "!\"\"",        // inversion of empty string
        "!\"a\"",       // inversion of single char string
        "!\"hello\"",   // inversion of longer string
        "!nil"          // inversion of nil

    };
    for (int i=0;i<20;i++)
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
        Literal inv=boolInvert(ex->as.u.right->as.l);
        Expr* dof=new_literal(inv.t,inv.val);
        printTree(dof);
        printf("\n");

    }

}

void testNegation()
{
    char* negTests[] = {
    "-0",
    "-1",
    "-42",
    "-2147483648",
    "-2147483647",
    "-0.0",
    "-0.5",
    "-1.0",
    "-3.14",
    "-2.71828",
    "-1000000",
    "-99999.999",
    "-1e3",
    "-1E3",
    "-1e-3",
    "-0.0001",
    "-123456789",
    "-987654321",
    "-0.0000001",
    "-9999999.0",
    "-5",
    "-10.5",
    "-7.777",
    "-42.42",
    "-0.25",
    "-8",
    "-6.022",
    "-9.81",
    "-100.001",
    "-0.0000000001"
};
    for(int i=0;i<20;i++)
    {   Expr* ex=parse(negTests[i],strlen(negTests[i]));
        //Literal ans;
       // printTree(ex);fflush(stdout);
        printf("%s :", negTests[i]);
     //   printf("%s:",negTests[i]);
        if(!ex)
        {
            printf("ex null"); fflush(stdout);
        }
        else if(!(ex->as.u.right))
        {
            printf("left null %d",i);fflush(stdout);
        }
        Literal ans=negateNum(ex->as.u.right->as.l);
        if(isErrorLiteral(ans))
        {
            continue;
        }
        Expr* dof=new_literal(ans.t,ans.val);
        printTree(dof);printf(" test case no %d",i);
        printf("\n");
    }
}

void testMultiply()
{
    char* mulTests[] = {
    "0 * 0",
    "0 * 1",
    "1 * 0",
    "1 * 1",
    "2 * 3",
    "3 * 2",
    "5 * 7",
    "7 * 5",
    "10 * 10",
    "12 * 4",
    "6 * 8",
    "100 * 2",
    "2 * 100",
    "50 * 50",
    "25 * 4",
    "4 * 25",
    "3.0 * 2",
    "2 * 3.0",
    "3.5 * 2",
    "2 * 3.5",
    "1.5 * 2.5",
    "2.5 * 1.5",
    "0.5 * 0.5",
    "10.0 * 0.1",
    "0.1 * 10.0",
    "1000 * 0.001",
    "0.001 * 1000",
    "123.45 * 2",
    "2 * 123.45",
    "1.2345 * 10"
};
   
    for(int i=0;i<30;i++)
    {
        Expr* ex=parse(mulTests[i],strlen(mulTests[i]));
        printf("%s: ",mulTests[i]);
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
        Literal a=ex->as.b.left->as.l;
        Literal b=ex->as.b.right->as.l;
        Literal ans=multiplyNumbers(a,b);
         if(isErrorLiteral(ans))
        {
            printf("On line %d there is an error\n",i+1);continue;
        }
        Expr* dof=new_literal(ans.t,ans.val);
        printTree(dof);fflush(stdout);
        printf("\n");
    }
}
void testDivide()
{
    char* divTests[] = {
    "1 / 1",
    "2 / 1",
    "1 / 2",
    "4 / 2",
    "2 / 4",
    "10 / 5",
    "5 / 10",
    "100 / 10",
    "10 / 100",
    "50 / 5",
    "5 / 50",
    "12 / 0",
    "3 / 12",
    "25 / 5",
    "5 / 25",
    "2.0 / 1",
    "1 / \"2.0\"",
    "3.0 / 2",
    "2 / 3.0",
    "5.5 / 2",
    "2 / 5.5",
    "10.0 / 0.5",
    "0.5 / 10.0",
    "1000 / 10",
    "10 / 1000",
    "123.45 / 5",
    "5 / 123.45",
    "1.2345 / 1",
    "1 / 1.2345",
    "0.1 / 0.01"
};
 for(int i=0;i<30;i++)
    {
        Expr* ex=parse(divTests[i],strlen(divTests[i]));
        printf("%s: ",divTests[i]);
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
        Literal a=ex->as.b.left->as.l;
        Literal b=ex->as.b.right->as.l;
        Literal ans=divideNumbers(a,b);
         if(isErrorLiteral(ans))
        {
            printf("On line %d there is an error\n",i+1);continue;
        }
        Expr* dof=new_literal(ans.t,ans.val);
        printTree(dof);fflush(stdout);
        printf("\n");
    }

}

void testSubtract()
{
    char* sub_tests[] = {
    "5 - 3",       // 2
    "3 - 5",       // -2
    "0 - 0",       // 0
    "1.01 - 2",      // 8
    "2 - 2",       // 0
    "-1 - -1",     // 0 (requires unary minus implementation)
    "-1 - 2",      // -3 (requires unary minus)
    "2 - -2",      // 4 (requires unary minus)
};
    for(int i=0;i<8;i++)
    {
        Expr* ex=parse(sub_tests[i],strlen(sub_tests[i]));
        printf("%s: ",sub_tests[i]);
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
        Literal a=ex->as.b.left->as.l;
        Literal b=ex->as.b.right->as.l;
        Literal ans=subtractNums(a,b);
         if(isErrorLiteral(ans))
        {
            printf("On line %d there is an error\n",i+1);continue;
        }
        Expr* dof=new_literal(ans.t,ans.val);
        printTree(dof);fflush(stdout);
        printf("\n");
    }

}


int testAND()
{
    char* tests[] = {
    "1 and 2",         // both non-zero → TRUE
    "0 and 1",         // left false → FALSE (short-circuit)
    "0 and 0",         // both false → FALSE
    "5 and 0",         // right false → FALSE
    "7 and 3",         // both non-zero → TRUE
    "\"hello\" and 1", // string is truthy → TRUE
    "0 and \"world\"", // left false → FALSE
    "\"\" and 1",      // empty string might be false depending on boolify
    "0 and \"\"",      // left false → FALSE
    "\"34\" and 0",    // right false → FALSE
    "\"abc\" and \"def\"" // both strings → TRUE
};
int numTests = sizeof(tests) / sizeof(tests[0]);

    for(int i=0;i<8;i++)
    {
       //  TokenList tokens=scanTokens(tests[i],strlen(tests[i]));
        // for(int i=0;i<tokens.size;i++)
        // {
        //     printToken(tokens.tokens[i]);fflush(stdout);
        // }
        Expr* ex=parse(tests[i],strlen(tests[i]));
       // printTree(ex);fflush(stdout);
        printf("%s: ",tests[i]);
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
        Literal a=ex->as.b.left->as.l;
        Literal b=ex->as.b.right->as.l;
        Literal ans=AndLiterals(a,b);
         if(isErrorLiteral(ans))
        {
            printf("On line %d there is an error\n",i+1);continue;
        }
        Expr* dof=new_literal(ans.t,ans.val);
        printTree(dof);fflush(stdout);
        printf("\n");
    }
}
int main()
{
    //testComparison();
    //testAdd();
   // testInvert();
    //testBoolify();
    //testEquals();
    //testNegation();
    //testMultiply();
   // testDivide();
  // testSubtract();
  testAND();
}